#include <iostream>
#include <vector>
#include <csignal>
#include <unistd.h>
#include "src/symbolize.h"

using namespace google;

# define ARRAYSIZE(a) (sizeof(a) / sizeof(*(a)))
#define CHECK_ERR(invocation)                                          \
PLOG_IF(FATAL, GOOGLE_PREDICT_BRANCH_NOT_TAKEN((invocation) == -1))    \
        << #invocation

const struct {
    int number;
    const char *name;
} kFailureSignals[] = {
        { SIGSEGV, "SIGSEGV" },
        { SIGILL, "SIGILL" },
        { SIGFPE, "SIGFPE" },
        { SIGABRT, "SIGABRT" },
#if !defined(OS_WINDOWS)
        { SIGBUS, "SIGBUS" },
#endif
        { SIGTERM, "SIGTERM" },
};

class MinimalFormatter {
public:
    MinimalFormatter(char *buffer, int size)
            : buffer_(buffer),
              cursor_(buffer),
              end_(buffer + size) {
    }

    // Returns the number of bytes written in the buffer.
    int num_bytes_written() const { return (int) (cursor_ - buffer_); }

    // Appends string from "str" and updates the internal cursor.
    void AppendString(const char* str) {
        int i = 0;
        while (str[i] != '\0' && cursor_ + i < end_) {
            cursor_[i] = str[i];
            ++i;
        }
        cursor_ += i;
    }

    // Formats "number" in "radix" and updates the internal cursor.
    // Lowercase letters are used for 'a' - 'z'.
    void AppendUint64(uint64_t number, int radix) {
        int i = 0;
        while (cursor_ + i < end_) {
            const int tmp = number % radix;
            number /= radix;
            cursor_[i] = (tmp < 10 ? '0' + tmp : 'a' + tmp - 10);
            ++i;
            if (number == 0) {
                break;
            }
        }
        // Reverse the bytes written.
        std::reverse(cursor_, cursor_ + i);
        cursor_ += i;
    }

    // Formats "number" as hexadecimal number, and updates the internal
    // cursor.  Padding will be added in front if needed.
    void AppendHexWithPadding(uint64_t number, int width) {
        char* start = cursor_;
        AppendString("0x");
        AppendUint64(number, 16);
        // Move to right and add padding in front if needed.
        if (cursor_ < start + width) {
            const int64_t delta = start + width - cursor_;
            std::copy(start, cursor_, start + delta);
            std::fill(start, start + delta, ' ');
            cursor_ = start + width;
        }
    }

private:
    char *buffer_;
    char *cursor_;
    const char * const end_;
};

void WriteToStderr(const char* data, int size) {
    if (write(STDERR_FILENO, data, size) < 0) {
        // Ignore errors.
    }
}

// The writer function can be changed by InstallFailureWriter().
void (*g_failure_writer)(const char* data, int size) = WriteToStderr;

void DumpTimeInfo() {
    time_t time_in_sec = time(NULL);
    char buf[256];  // Big enough for time info.
    MinimalFormatter formatter(buf, sizeof(buf));
    formatter.AppendString("*** Aborted at ");
    formatter.AppendUint64(time_in_sec, 10);
    formatter.AppendString(" (unix time)");
    formatter.AppendString(" try \"date -d @");
    formatter.AppendUint64(time_in_sec, 10);
    formatter.AppendString("\" if you are using GNU date ***\n");
    g_failure_writer(buf, formatter.num_bytes_written());
}

void DumpSignalInfo(int signal_number, siginfo_t *siginfo) {
    // Get the signal name.
    const char* signal_name = NULL;
    for (size_t i = 0; i < ARRAYSIZE(kFailureSignals); ++i) {
        if (signal_number == kFailureSignals[i].number) {
            signal_name = kFailureSignals[i].name;
        }
    }

    char buf[256];  // Big enough for signal info.
    MinimalFormatter formatter(buf, sizeof(buf));

    formatter.AppendString("*** ");
    if (signal_name) {
        formatter.AppendString(signal_name);
    } else {
        // Use the signal number if the name is unknown.  The signal name
        // should be known, but just in case.
        formatter.AppendString("Signal ");
        formatter.AppendUint64(signal_number, 10);
    }
    formatter.AppendString(" (@0x");
    formatter.AppendUint64(reinterpret_cast<uintptr_t>(siginfo->si_addr), 16);
    formatter.AppendString(")");
    formatter.AppendString(" received by PID ");
    formatter.AppendUint64(getpid(), 10);
    formatter.AppendString(" (TID 0x");
    // We assume pthread_t is an integral number or a pointer, rather
    // than a complex struct.  In some environments, pthread_self()
    // returns an uint64 but in some other environments pthread_self()
    // returns a pointer.  Hence we use C-style cast here, rather than
    // reinterpret/static_cast, to support both types of environments.
    formatter.AppendUint64((uintptr_t)pthread_self(), 16);
    formatter.AppendString(") ");
    // Only linux has the PID of the signal sender in si_pid.
#ifdef OS_LINUX
    formatter.AppendString("from PID ");
  formatter.AppendUint64(siginfo->si_pid, 10);
  formatter.AppendString("; ");
#endif
    formatter.AppendString("stack trace: ***\n");
    g_failure_writer(buf, formatter.num_bytes_written());
}

void DumpStackFrameInfo(const char* prefix, void* pc) {
    // Get the symbol name.
//    std::cout << "-----DumpStackFrameInfo-----" << std::endl;
    const char *symbol = "(unknown)";
    char symbolized[1024];  // Big enough for a sane symbol.
    // Symbolizes the previous address of pc because pc may be in the
    // next function.
    if (Symbolize(reinterpret_cast<char *>(pc) - 1, symbolized, sizeof(symbolized))) {
        symbol = symbolized;
    }
    std::cout << "-----222----" << symbol << std::endl;

    char buf[1024];  // Big enough for stack frame info.
    MinimalFormatter formatter(buf, sizeof(buf));

    formatter.AppendString(prefix);
    formatter.AppendString("@ ");
    const int width = 2 * sizeof(void*) + 2;  // + 2  for "0x".
    formatter.AppendHexWithPadding(reinterpret_cast<uintptr_t>(pc), width);
    formatter.AppendString(" ");
    formatter.AppendString(symbol);
    formatter.AppendString("\n");
    g_failure_writer(buf, formatter.num_bytes_written());
}

void FailureSignalHandler(int signal_number,
                          siginfo_t *signal_info,
                          void *ucontext) {
//    std::cout << "-----FailureSignalHandler-----" << std::endl;
    DumpTimeInfo();
    void *stack[32];
//    const int depth = GetStackTrace(stack, ARRAYSIZE(stack), 1);
    int depth = 6;
    DumpSignalInfo(signal_number, signal_info);
    for (int i = 0; i < depth; ++i) {
        DumpStackFrameInfo("    ", stack[i]);
    }
//    FlushLogFilesUnsafe(0);
//    InvokeDefaultSignalHandler(signal_number);
}

void InstallFailureSignalHandler() {
  struct sigaction sig_action;
  memset(&sig_action, 0, sizeof(sig_action));
  sigemptyset(&sig_action.sa_mask);
  sig_action.sa_flags |= SA_SIGINFO;
  sig_action.sa_sigaction = &FailureSignalHandler;
    for (size_t i = 0; i < ARRAYSIZE(kFailureSignals); ++i) {
//        CHECK_ERR(sigaction(kFailureSignals[i].number, &sig_action, nullptr));
        sigaction(kFailureSignals[i].number, &sig_action, nullptr);
    }
}

int main(int argc, const char* argv[]) {
    std::cout << "Hello, libunwind!" << std::endl;
    InstallFailureSignalHandler();
    std::vector<int> a;
    a.push_back(1);
    std::cout << a.at(1000) << std::endl;
    std::cout << "0---------------" << std::endl;
    return 0;
}
