#include "lcall.h"
#include <map>
#include <functional>
#include <string>
#include "dlazy.h"

namespace low {

static dash::lazy<std::map<std::string, std::function<void ()>>> g_procs;

void set(const char *name, void (*proc)(int), int param) {
    if (! name || ! proc) {
        return;
    }

    std::function<void ()> lambda = [=]() {
        proc(param);
    };
    g_procs->insert({ name, lambda });
}

void call(const char *name) {
    if (! name) {
        return;
    }

    auto it = g_procs->find(name);
    if (it == g_procs->end()) {
        return;
    }

    it->second();
}

} //end low.
