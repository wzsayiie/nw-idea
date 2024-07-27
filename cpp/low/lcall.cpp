#include "lcall.h"
#include <map>
#include <string>
#include "dlazy.h"

namespace low {

struct lambda {
    void (*proc)(void *);
    void *param;
};

static dash::lazy<std::map<std::string, lambda>> _lambdas;

void set(const char *name, void (*proc)(void *), void *param) {
    if (!name || !proc || !param) {
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
