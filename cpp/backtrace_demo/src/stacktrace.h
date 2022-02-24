#ifndef BACKTRACE_DEMO_STACKTRACE_H_
#define BACKTRACE_DEMO_STACKTRACE_H_

#include <bfd.h>
#include <cxxabi.h>
#include <execinfo.h>
#include <link.h>

#include <csignal>
#include <cstdarg>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace stack {

struct LineData {
  asymbol **symbol_table{};
  bfd_vma addr{};
  std::string filename;
  std::string function_name;
  unsigned int line{};
  int line_found{};
};

struct MatchData {
  bfd_vma addr;
  std::string filename;
  bfd_vma addr_in_file;
};

class StacktraceAddresses {
public:
  StacktraceAddresses() : impl_stacktrace_depth(0) {}
  void add_addresses(void *const *_stacktrace_buffer, int _size, int _impl_stacktrace_depth) {
    this->stacktrace_buffer.clear();
    this->impl_stacktrace_depth = _impl_stacktrace_depth;
    for (int i = 0; i < _size; i++)
      this->stacktrace_buffer.push_back((bfd_vma) _stacktrace_buffer[i]);
  }
  bfd_vma get_address(int i) const {
    return this->stacktrace_buffer[i];
  }
  int get_size() const {
    return this->stacktrace_buffer.size();
  }
  int get_impl_stacktrace_depth() const {
    return this->impl_stacktrace_depth;
  }
private:
  std::vector<bfd_vma> stacktrace_buffer{};
  int impl_stacktrace_depth;
};

bool IsWhitespaceChar(const char c) {
  return c == ' ' || c == '\t';
}

std::string RemoveLeadingWhitespace(const std::string &str) {
  if (str.length() && IsWhitespaceChar(str[0])) {
    int first_nonwhitespace_index = 0;
    for (int i = 0; i < static_cast<int>(str.length()); ++i) {
      if (!IsWhitespaceChar(str[i])) {
        first_nonwhitespace_index = i;
        break;
      }
    }
    return str.substr(first_nonwhitespace_index);
  }
  return str;
}

std::string ReadLineFromFile(const std::string& filename, unsigned int line_number) {
  std::ifstream in(filename.c_str());
  if (!in.is_open()) {
    return "";
  }
  if (line_number == 0) {
    return "Line number must be positive";
  }
  unsigned int n = 0;
  std::string line;
  while (n < line_number) {
    if (in.eof())
      return "Line not found";
    getline(in, line);
    n += 1;// loop update
  }
  return line;
}

std::string DemangleFunctionName(const std::string& name) {
  std::string s;

  if (name.length() == 0) {
    s = "??";
  } else {
    int status = 0;
    char *d = nullptr;
    d = abi::__cxa_demangle(name.c_str(), 0, 0, &status);
    if (d) {
      s = d;
      free(d);
      if (!s.empty()) {
        if (s[s.size() - 1] != ')') {
          s = name + "()";
        }
      }
    } else {
      s = name + "()";
    }
  }

  return s;
}

void ProcessSection(bfd *abfd, asection *section, void *_data) {
  auto *data = (LineData *) _data;
  if (data->line_found) {
    // If we already found the line, exit
    return;
  }
  if ((bfd_get_section_flags(abfd, section) & SEC_ALLOC) == 0) {
    return;
  }

  bfd_vma section_vma = bfd_get_section_vma(abfd, section);
  if (data->addr < section_vma) {
    return;
  }

  bfd_size_type section_size = bfd_section_size(abfd, section);
  if (data->addr >= section_vma + section_size) {
    return;
  }

  bfd_vma offset = data->addr - section_vma - 1;
  const char *filename = NULL, *function_name = NULL;
  data->line_found = bfd_find_nearest_line(abfd, section, data->symbol_table,
                                           offset, &filename, &function_name, &data->line);

  if (filename == NULL)
    data->filename = "";
  else
    data->filename = filename;

  if (function_name == NULL)
    data->function_name = "";
  else
    data->function_name = function_name;
}

int LoadSymbolTable(bfd *abfd, LineData *data) {
  if ((bfd_get_file_flags(abfd) & HAS_SYMS) == 0) {
    return 0;
  }

  void **symbol_table_ptr = reinterpret_cast<void **>(&data->symbol_table);
  long n_symbols;
  unsigned int symbol_size;
  n_symbols = bfd_read_minisymbols(abfd, false, symbol_table_ptr, &symbol_size);
  if (n_symbols == 0) {
    if (data->symbol_table != NULL)
      free(data->symbol_table);
    n_symbols = bfd_read_minisymbols(abfd, true, symbol_table_ptr, &symbol_size);
  }

  if (n_symbols < 0) {
    return 1;
  }
  return 0;
}

std::string Addr2Str(const std::string& file_name, bfd_vma addr) {
  bfd *abfd;
  abfd = bfd_openr(file_name.c_str(), NULL);
  if (abfd == NULL)
    return "Cannot open the binary file '" + file_name + "'\n";
  if (bfd_check_format(abfd, bfd_archive))
    return "Cannot get addresses from the archive '" + file_name + "'\n";
  char **matching;
  if (!bfd_check_format_matches(abfd, bfd_object, &matching))
    return "Unknown format of the binary file '" + file_name + "'\n";
  LineData data;
  data.addr = addr;
  data.symbol_table = NULL;
  data.line_found = false;
  if (LoadSymbolTable(abfd, &data) == 1)
    return "Failed to load the symbol table from '" + file_name + "'\n";
  bfd_map_over_sections(abfd, ProcessSection, &data);
  if (data.symbol_table != NULL) free(data.symbol_table);
  bfd_close(abfd);

  std::ostringstream s;
  if (!data.line_found) {
    s << "  File unknown, address: 0x" << (long long unsigned int) addr;
  } else {
    std::string name = DemangleFunctionName(data.function_name);
    if (data.filename.length() > 0) {
      // Nicely format the filename + function name + line
      s << "  File \"" << data.filename << "\", line "
        << data.line << ", in " << name;
      const std::string line_text = RemoveLeadingWhitespace(
              ReadLineFromFile(data.filename, data.line));
      if (line_text != "") {
        s << "\n    " << line_text;
      }
    } else {
      s << "  File unknown, in " << name;
    }
  }
  s << "\n";
  return s.str();
}

int SharedLibCallback(struct dl_phdr_info *info, size_t size, void *_data) {
  auto *data = (struct MatchData *) _data;
  for (int i = 0; i < info->dlpi_phnum; i++) {
    if (info->dlpi_phdr[i].p_type == PT_LOAD) {
      ElfW(Addr) min_addr = info->dlpi_addr + info->dlpi_phdr[i].p_vaddr;
      ElfW(Addr) max_addr = min_addr + info->dlpi_phdr[i].p_memsz;
      if ((data->addr >= min_addr) && (data->addr < max_addr)) {
        data->filename = info->dlpi_name;
        data->addr_in_file = data->addr - info->dlpi_addr;
        return 1;
      }
    }
  }
  return 0;
}

std::string Stacktrace2Str(const StacktraceAddresses &stacktrace_addresses) {
  int stack_depth = stacktrace_addresses.get_size() - 1;

  std::string full_stacktrace_str("Traceback (most recent call last):\n");

  bfd_init();
  const int stack_depth_start = stack_depth;
  const int stack_depth_end = stacktrace_addresses.get_impl_stacktrace_depth();
  for (int i = stack_depth_start; i >= stack_depth_end; i--) {
    struct MatchData match;
    match.addr = stacktrace_addresses.get_address(i);
    if (dl_iterate_phdr(SharedLibCallback, &match) == 0) {
      return "dl_iterate_phdr() didn't find a match\n";
    }

    if (match.filename.length() > 0) {
      full_stacktrace_str += Addr2Str(match.filename, match.addr_in_file);
    } else {
      full_stacktrace_str += Addr2Str("/proc/self/exe", match.addr_in_file);
    }
  }
  return full_stacktrace_str;
}

void get_stacktrace_addresses(int impl_stacktrace_depth,
                              StacktraceAddresses &stacktrace_addresses) {
  const int STACKTRACE_ARRAY_SIZE = 100;
  void *stacktrace_array[STACKTRACE_ARRAY_SIZE];
  const size_t stacktrace_size = backtrace(stacktrace_array,
                                           STACKTRACE_ARRAY_SIZE);
  stacktrace_addresses.add_addresses(stacktrace_array, stacktrace_size,
                                     impl_stacktrace_depth + 1);
}

std::string get_stacktrace(int impl_stacktrace_depth) {
  StacktraceAddresses addresses;
  get_stacktrace_addresses(impl_stacktrace_depth + 1, addresses);
  return Stacktrace2Str(addresses);
}


void show_stacktrace() {
  const int impl_stacktrace_depth = 1;
  std::cout << get_stacktrace(impl_stacktrace_depth);
}

void SigsegvCallback(int signum) {
  std::cout << "SigsegvCallback:" << signum << std::endl;
  show_stacktrace();
  signal(SIGABRT, SIG_DFL);
  abort();
}

void SabrtCallback(int signum) {
  std::cout << "SabrtCallback:" << signum << std::endl;
  show_stacktrace();
}

void InstallFailureSignalHandler() {
  signal(SIGSEGV, SigsegvCallback);
  signal(SIGABRT, SabrtCallback);
}


}// namespace stack


#endif//BACKTRACE_DEMO_STACKTRACE_H_
