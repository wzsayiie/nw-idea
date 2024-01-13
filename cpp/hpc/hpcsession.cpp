#include "hpcsession.h"
#include "danycast.h"
#include "dbytes.h"
#include "hpclow.h"

void HPCSession::callback(const std::map<std::string, std::any> &args) const {
    HPCParam param;

    //IMPORTANT: the call's callback-id and callback's, must be same.
    param.setCallbackID(this->callbackID());
    param.setValues(args);

    hpc_callback(param.sessionID());
}

void HPCSession::callback(const std::vector<std::any> &args) const {
    HPCParam param;

    param.setCallbackID(this->callbackID());
    param.setValues(args);

    hpc_callback(param.sessionID());
}
