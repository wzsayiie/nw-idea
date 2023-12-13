#include "mapp.h"
#include "dlazy.h"
#include "rdefine.h"

static dash::lazy<std::vector<reflect::function<void ()>::ptr>> sResumeListeners;
static dash::lazy<std::vector<reflect::function<void ()>::ptr>> sUpdateListeners;
static dash::lazy<std::vector<reflect::function<void ()>::ptr>> sPauseListeners ;

void _MAppLaunch() {
}

static void MCall(const std::vector<reflect::function<void ()>::ptr> &list) {
    for (const auto &item : list) {
        item->call();
    }
}

void _MAppResume() { MCall(sResumeListeners); }
void _MAppUpdate() { MCall(sUpdateListeners); }
void _MAppPause () { MCall(sPauseListeners ); }

define_reflectable_function(MAppAddResumeListener, "args:listener")
define_reflectable_function(MAppAddUpdateListener, "args:listener")
define_reflectable_function(MAppAddPauseListener , "args:listener")

static void MPush(
    std::vector<reflect::function<void ()>::ptr> *list,
    const reflect::function<void ()>::ptr        &item)
{
    list->push_back(item);
}

void MAppAddResumeListener(const reflect::function<void ()>::ptr &i) { MPush(&sResumeListeners, i); }
void MAppAddUpdateListener(const reflect::function<void ()>::ptr &i) { MPush(&sUpdateListeners, i); }
void MAppAddPauseListener (const reflect::function<void ()>::ptr &i) { MPush(&sPauseListeners , i); }

define_reflectable_function(MAppUpdateInterval)
double MAppUpdateInterval() {
    return 0.1;
}
