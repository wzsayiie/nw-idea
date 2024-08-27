#include <cstdlib>
#include "denviron.h"

#if D_OS_WINDOWS
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

void sleep_sec(double sec) {
    #if D_OS_WINDOWS
        Sleep((DWORD)(sec * 1000));
    #else
        usleep((useconds_t)(sec * 1000 * 1000));
    #endif
}

namespace low {
    void call(const char *name);
    extern double dr;
}

void on_exit();

int main() {
    low::call("_MAppStart");
    low::call("_MAppResume");

    atexit(on_exit);

    low::call("_MAppUpdateInterval");
    double sec = low::dr;

    while (true) {
        low::call("_MAppUpdate");
        sleep_sec(sec);
    }
}

void on_exit() {
    low::call("_MAppPause");
    low::call("_MAppStop");
}
