#include "lcall.h"
#include <map>
#include <string>
#include "dlazy.h"

namespace low {

struct lambda {
    void (*proc)(int);
    int param;
};

static dash::lazy<std::map<std::string, lambda>> _lambdas;

void set(const char *name, void (*proc)(int), int param) {
    if (!name || !proc) {
        return;
    }

    lambda lmd = {
        .proc  = proc,
        .param = param,
    };
    _lambdas->insert({ name, lmd });
}

void call(const char *name) {
    if (!name) {
        return;
    }

    auto it = _lambdas->find(name);
    if (it == _lambdas->end()) {
        return;
    }

    it->second.proc(it->second.param);
}

} //end low.
