#include "hsession.h"
#include "hlow.h"

static void HSession_callback(HSession *self, const HParam::ptr &param) {
    //IMPORTANT: the call's callback-id and callback's, must be same.
    param->setCallbackID(self->callbackID());
    h_callback(param->sessionID());
}

void HSession::callback(const std::map<std::string, std::any> &args) {
    auto param = HParam::create();
    param->setValues(args);
    HSession_callback(this, param);
}

void HSession::callback(const std::vector<std::any> &args) {
    auto param = HParam::create();
    param->setValues(args);
    HSession_callback(this, param);
}
