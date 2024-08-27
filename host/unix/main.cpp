#include <cstdlib>
#include "denviron.h"
#include "lcall.h"
#include "lreg.h"

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

#ifdef custom_main
    void custom_main();
#endif

void on_exit();

int main() {
    //line mode.
    #ifdef custom_main
        custom_main();
        return 0;
    #endif

    //loop mode.
    low::call("_MAppStart");
    low::call("_MAppResume");
    atexit(on_exit);

    low::call("_MAppUpdateInterval");
    double sec = low::dr;

    while (true) {
        low::call("_MAppUpdate");
        sleep_sec(sec);
    }

    return 0;
}

void on_exit() {
    low::call("_MAppPause");
    low::call("_MAppStop");
}
