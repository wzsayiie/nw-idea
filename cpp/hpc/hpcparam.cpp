#include "hpcparam.h"
#include "danycast.h"
#include "dbytes.h"
#include "hpclow.h"

HPCParam::HPCParam() {
    _sessionID = hpc_session_create();
}

HPCParam::HPCParam(const HPCParam &that) {
    _sessionID = hpc_session_retain(that._sessionID);
}

HPCParam::HPCParam(HPCParam &&that) {
    _sessionID = that._sessionID;
    that._sessionID = 0;
}

HPCParam::~HPCParam() {
    hpc_session_release(_sessionID);
}

void HPCParam::reset(int64_t sid) {
    hpc_session_release(_sessionID);
    _sessionID = hpc_session_retain(sid);
}

int64_t HPCParam::sessionID() const {
    return _sessionID;
}

void HPCParam::setProcedureName(const char *name) {
    hpc_session_set_procedure_name(_sessionID, name);
}

std::string HPCParam::procedureName() const {
    return hpc_session_procedure_name(_sessionID);
}

void HPCParam::setCallbackID(int64_t callback_id) {
    hpc_session_set_callback_id(_sessionID, callback_id);
}

int64_t HPCParam::callbackID() const {
    return hpc_session_callback_id(_sessionID);
}

void HPCParam::setValues(const std::map<std::string, std::any> &values) {
    for (auto &[key, value] : values) {
        setValue(key.c_str(), value);
    }
}

void HPCParam::setValues(const std::vector<std::any> &values) {
    int index = 0;
    for (auto &value : values) {
        setValue(++index, value);
    }
}

void HPCParam::setValue(const char *k, const std::any &v) {
    const std::type_info &type = v.type();
    
    if /**/ (type == typeid(bool   )) { hpc_session_set_param_bool   (_sessionID, k, d_cast(bool   ) v); }
    else if (type == typeid(int    )) { hpc_session_set_param_int64  (_sessionID, k, d_cast(int64_t) v); }
    else if (type == typeid(int64_t)) { hpc_session_set_param_int64  (_sessionID, k, d_cast(int64_t) v); }
    else if (type == typeid(float  )) { hpc_session_set_param_float64(_sessionID, k, d_cast(double ) v); }
    else if (type == typeid(double )) { hpc_session_set_param_float64(_sessionID, k, d_cast(double ) v); }

    else if (type == typeid(std::string)) {
        auto str = d_cast(std::string) v;
        hpc_session_set_param_string(_sessionID, k, str.c_str());
    }

    else if (type == typeid(dash::bytes)) {
        auto bytes = d_cast(dash::bytes) v;
        hpc_session_set_param_bytes(_sessionID, k, bytes->data(), (int64_t)bytes->size());
    }
}

void HPCParam::setValue(int index, const std::any &value) {
    setValue(std::to_string(index).c_str(), value);
}

std::any HPCParam::value(const char *key) const {
    int64_t type = hpc_session_param_type(_sessionID, key);

    switch (type) {
        case hpc_type_bool   : return hpc_session_param_bool   (_sessionID, key);
        case hpc_type_int64  : return hpc_session_param_int64  (_sessionID, key);
        case hpc_type_float64: return hpc_session_param_float64(_sessionID, key);

        case hpc_type_string: {
            const char *str = hpc_session_param_string(_sessionID, key);
            return std::string(str);
        }

        case hpc_type_bytes: {
            auto data = hpc_session_param_bytes_data(_sessionID, key);
            auto size = hpc_session_param_bytes_size(_sessionID, key);
            return dash::make_bytes(data, (size_t)size);
        }

        default: return std::any();
    }
}

std::any HPCParam::value(int index) const {
    return value(std::to_string(index).c_str());
}

void HPCParam::setReturned(const std::any &value) {
    setValue(hpc_key_return, value);
}

std::any HPCParam::returned() const {
    return value(hpc_key_return);
}
