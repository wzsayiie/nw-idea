#include "mapp.h"
#include "dlazy.h"
#include "hpccenter.h"
#include "rdefine.h"

static dash::lazy<std::vector<reflect::function<void ()>::ptr>> sResumeListeners;
static dash::lazy<std::vector<reflect::function<void ()>::ptr>> sUpdateListeners;
static dash::lazy<std::vector<reflect::function<void ()>::ptr>> sPauseListeners ;

HPCCallableProcedure(_MAppLaunch)
void _MAppLaunch() {
}

HPCCallableProcedure(_MAppResume)
HPCCallableProcedure(_MAppUpdate)
HPCCallableProcedure(_MAppPause )

void _MAppResume() { for (const auto f : *sResumeListeners) { f->call(); } }
void _MAppUpdate() { for (const auto f : *sUpdateListeners) { f->call(); } }
void _MAppPause () { for (const auto f : *sPauseListeners ) { f->call(); } }

HPCCallableProcedure(_MAppUpdateInterval)
double _MAppUpdateInterval() {
    return 0.1;
}

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
        sPauseListeners ->push_back(listener);
    }
}
