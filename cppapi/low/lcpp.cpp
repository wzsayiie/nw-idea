#include "lcpp.h"
#include <map>
#include "dlazy.h"
#include "lcall.h"

namespace low {

static dash::lazy<std::map<int, void (*)()>> g_funcs;

static void generic_func(int id) {
    auto it = g_funcs->find(id);
    if (it != g_funcs->end()) {
        it->second();
    }
}

setter::setter(const char *name, void (*func)()) {
    auto id = (int)(intptr_t)func;

    g_funcs->insert({ id, func });
    set(name, generic_func, id);
}

} //end low.
