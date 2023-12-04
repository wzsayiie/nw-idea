#include "mapp.h"
#include "dlazy.h"
#include "rdefine.h"

static dash::lazy<std::vector<reflect::function<void ()>::ptr>> sResumeListeners;
static dash::lazy<std::vector<reflect::function<void ()>::ptr>> sUpdateListeners;
static dash::lazy<std::vector<reflect::function<void ()>::ptr>> sPauseListeners ;

static void MCallListeners(const std::vector<reflect::function<void ()>::ptr> &listeners) {
    for (const auto &func : listeners) {
        func->call();
    }
}

void _MAppResume() { MCallListeners(sResumeListeners); }
void _MAppUpdate() { MCallListeners(sUpdateListeners); }
void _MAppPause () { MCallListeners(sPauseListeners ); }

define_reflectable_function(MAppAddResumeListener, "args:listener")
void MAppAddResumeListener(const reflect::function<void ()>::ptr &listener) {
    if (listener) {
        sResumeListeners->push_back(listener);
    }
}

define_reflectable_function(MAppAddUpdateListener, "args:listener")
void MAppAddUpdateListener(const reflect::function<void ()>::ptr &listener) {
    if (listener) {
        sUpdateListeners->push_back(listener);
    }
}

define_reflectable_function(MAppAddPauseListener, "args:listener")
void MAppAddPauseListener(const reflect::function<void ()>::ptr &listener) {
    if (listener) {
        sPauseListeners->push_back(listener);
    }
}
