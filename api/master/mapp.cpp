#include "mapp.h"
#include "dlazy.h"
#include "lcpp.h"
#include "lreg.h"
#include "rdefine.h"

static dash::lazy<std::map<char, std::vector<reflect::function<void ()>::ptr>>> gListeners;

static void Add(char event, const reflect::function<void ()>::ptr &listener) {
    if (listener) {
        (*gListeners)[event].push_back(listener);
    }
}

static void Call(char event) {
    for (auto it : (*gListeners)[event]) {
        it->call();
    }
}

define_reflectable_function(MAppAddResumeListener, "args:listener")
define_reflectable_function(MAppAddUpdateListener, "args:listener")
define_reflectable_function(MAppAddPauseListener , "args:listener")

void MAppAddResumeListener(const reflect::function<void ()>::ptr &l) { Add('R', l); }
void MAppAddUpdateListener(const reflect::function<void ()>::ptr &l) { Add('U', l); }
void MAppAddPauseListener (const reflect::function<void ()>::ptr &l) { Add('P', l); }

define_low_function(_MAppLaunch)
void _MAppLaunch() {
}

define_low_function(_MAppResume)
define_low_function(_MAppUpdate)
define_low_function(_MAppPause )

void _MAppResume() { Call('R'); }
void _MAppUpdate() { Call('U'); }
void _MAppPause () { Call('P'); }

define_low_function(_MAppUpdateInterval)
void _MAppUpdateInterval() {
    low::dr = 0.1;
}
