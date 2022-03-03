#include <execinfo.h>
#include <unistd.h>
#include <cctype>
#include <cerrno>
#include <csignal>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_FILE_PATH 1024
#define MAX_MAP_ITEMS 512
#define MAX_FRAMES 64

struct MapItem {
  uint64_t start;
  uint64_t end;
  char path[MAX_FILE_PATH];
};

int PrintMsg(const char *fmt, ...) {
  va_list args;
  int ret;
  va_start(args, fmt);
  ret = vfprintf(stderr, fmt, args);
  va_end(args);
  return ret;
}

void ReadMaps(MapItem *items, int *items_count, int id) {
  char buf[1536] = {0};
  FILE *fp = nullptr;
  int read_count = 0;
  int len;
  char *p;

  if (id < 0)
    id = getpid();

  snprintf(buf, 1535, "/proc/%d/maps", id);
  fp = fopen(buf, "rb");
  if (fp == nullptr) {
    *items_count = 0;
  }

  while(fgets(buf, sizeof(buf) - 1, fp) != nullptr) {
    len = strlen(buf);
    if (buf[len - 1] == '\n') {
      buf[len - 1] = '\0';
    }

    items[read_count].start = strtoull(buf, nullptr, 16);

    p = strchr(buf, '-');
    if (p == nullptr) {
      continue;
    }
    p++;
    items[read_count].end = strtoull(p, nullptr, 16);

    p = strstr(p, "      ");
    if (p == nullptr) {
      continue;
    }
    while (isblank(*p))
      p++;
    strncpy(items[read_count].path, p, MAX_FILE_PATH - 1);

    read_count++;
  } // while

  *items_count = read_count;
  fclose(fp);
}

int MatchFile(const MapItem *items, int items_count, void *addr) {
  for (int i = 0; i < items_count; i++) {
    if ((uint64_t) addr >= items[i].start && (uint64_t) addr < items[i].end) {
      return i;
    }
  }
  return -1;
}

int AddrToLine(void *addr, const char *path, char *buf_out, int buf_size) {
  char buf[1536] = {0};
  char buf_func[512] = {0};
  int line = -1;
  FILE *fp;
  char *p;
  char m_addr2line_path[MAX_FILE_PATH] = "addr2line";

  snprintf(buf, sizeof(buf), "%s -C -e %s -f -i %p", m_addr2line_path, path, addr);

  fp = popen(buf, "r");
  if (fp == nullptr) {
    return -1;
  }

  //function name
  fgets(buf_func, sizeof(buf_func) - 1, fp);

  //file and line
  fgets(buf, sizeof(buf) - 1, fp);

  if (buf_func[0] == '?' && buf[0] == '?') {
    pclose(fp);
    return -1;
  }

  if (buf_func[0] == '?')
    strncpy(buf_func, "unknown", sizeof(buf_func) - 1);
  if (buf[0] == '?')
    strncpy(buf, "unknown", sizeof(buf) - 1);

  if (buf_func[strlen(buf_func) - 1] == '\n')
    buf_func[strlen(buf_func) - 1] = '\0';

  p = buf;

  while (*p != ':' && p < buf + sizeof(buf) - 1) {
    p++;
  }
  *p++ = 0;

  if (sscanf(p, "%d", &line) == 1 && line >= 0) {
    snprintf(buf_out, buf_size, "func: %s, file: %s L%d, module: %s", buf_func, buf, line, path);
  }
  else {
    snprintf(buf_out, buf_size, "func: %s, file: %s, module: %s", buf_func, buf, path);
  }
  pclose(fp);
  return 0;
}

void Callstack(int max_frames) {
  char exe_path[MAX_FILE_PATH] = {0};
  void *samples[MAX_FRAMES];
  MapItem *items;
  int items_count;
  int frames;

  char buf[1536] = {0};
  char *addr;
  char *addr_conv;
  int index;

  if (readlink("/proc/self/exe", exe_path, sizeof(exe_path)) < 0) {
    exe_path[0] = '\0';
  }

  items = (MapItem *) malloc(sizeof(MapItem) * MAX_MAP_ITEMS);
  if (items == nullptr) {
    return;
  }
  items_count = MAX_MAP_ITEMS;

  ReadMaps(items, &items_count, -1);

  frames = backtrace(samples, (max_frames > 0 && max_frames > MAX_FRAMES) ? max_frames : MAX_FRAMES);
  for (int i = 1; i < frames; i++) {
    addr = static_cast<char *>(samples[i]);
    addr_conv = addr;

    index = MatchFile(items, items_count, addr);
    if (index >= 0) {
      if (AddrToLine(addr_conv, items[index].path, buf, sizeof(buf)) == 0) {
        goto OK;
      }
      addr_conv -= items[index].start;
      if (AddrToLine(addr_conv, items[index].path, buf, sizeof(buf)) == 0) {
        goto OK;
      }
    }
    OK:
    PrintMsg("[%1d] %-16p %-16p %s\n", i, addr, addr_conv, buf);
  }

  free(items);
}

void SignalHandler(int signum, siginfo_t *info, void *ptr) {
  Callstack(-1);
}

int RegisterSignal(int signum) {
  struct sigaction action{};
  memset(&action, 0, sizeof(action));
  action.sa_sigaction = SignalHandler;
  action.sa_flags = SA_SIGINFO | SA_ONSTACK;
  sigaction(signum, &action, nullptr);
  return 0;
}