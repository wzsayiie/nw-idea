#include "dprint.h"
#include "denviron.h"

#if D_OS_ANDROID
    #include <android/log.h>

    void dash::print_string(const char *str) {
        __android_log_write(ANDROID_LOG_INFO, "zzz", str);
    }

#else
    #include <cstdio>

    void dash::print_string(const char *str) {
        puts(str);
    }

#endif
