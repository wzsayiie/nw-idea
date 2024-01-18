#include "hpcsession.h"
#include "hpclow.h"

static void HPCSession_callback(HPCSession *self, const HPCParam::ptr &param) {
    //IMPORTANT: the call's callback-id and callback's, must be same.
    param->setCallbackID(self->callbackID());
    hpc_callback(param->sessionID());
}

void HPCSession::callback(const std::map<std::string, std::any> &args) {
    auto param = HPCParam::create();
    param->setValues(args);
    HPCSession_callback(this, param);
}

void HPCSession::callback(const std::vector<std::any> &args) {
    auto param = HPCParam::create();
    param->setValues(args);
    HPCSession_callback(this, param);
}
