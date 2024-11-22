#include "lcpp.h"
#include <map>
#include "dlazy.h"
#include "lcall.h"

namespace low {

static dash::lazy<std::map<int, void (*)()>> g_procs;

static void generic_proc(int id) {
    auto it = g_procs->find(id);
    if (it != g_procs->end()) {
        it->second();
    }
}

setter::setter(const char *name, void (*proc)()) {
    auto id = (int)g_procs->size();
    g_procs->insert({ id, proc });
    set(name, generic_proc, id);
}

} //end low.
