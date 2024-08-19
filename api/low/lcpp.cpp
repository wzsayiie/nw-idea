#include "lcpp.h"
#include <map>
#include "dlazy.h"
#include "lcall.h"

namespace low {

static dash::lazy<std::map<int, void (*)()>> _procs;

static void generic_proc(int id) {
    auto it = _procs->find(id);
    if (it != _procs->end()) {
        it->second();
    }
}

setter::setter(const char *name, void (*proc)()) {
    auto id = (int)_procs->size();
    _procs->insert({ id, proc });
    set(name, generic_proc, id);
}

} //end low.
