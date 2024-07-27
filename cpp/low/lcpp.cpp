#include "lcpp.h"
#include "lcall.h"

namespace low {

static void generic_proc(void *param) {
    auto proc = (void (*)())param;
    proc();
}

setter::setter(const char *name, void (*proc)()) {
    set(name, generic_proc, (void *)proc);
}

} //end low.
