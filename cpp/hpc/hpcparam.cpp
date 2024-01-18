#include "hpcparam.h"
#include "hpclow.h"

HPCParam::~HPCParam() {
    hpc_session_release(_sessionID);
}

void HPCParam::setSessionID(int64_t sid) {
    hpc_session_release(_sessionID);
    _sessionID = hpc_session_retain(sid);
}

int64_t HPCParam::sessionID() {
    if (!_sessionID) {
        _sessionID = hpc_session_create();
    }
    return _sessionID;
}

void HPCParam::setProcedureName(const char *name) {
    hpc_session_set_procedure_name(sessionID(), name);
}

std::string HPCParam::procedureName() {
    return hpc_session_procedure_name(sessionID());
}

void HPCParam::setCallbackID(int64_t callback_id) {
    hpc_session_set_callback_id(sessionID(), callback_id);
}

int64_t HPCParam::callbackID() {
    return hpc_session_callback_id(sessionID());
}

static void HPCParam_setValue(HPCParam *self, const char *key, const std::any &value) {
    const std::type_info &type = value.type();

    if /**/ (type == typeid(bool   )) { self->setValue(key, std::any_cast<bool   >(value)); }
    else if (type == typeid(int    )) { self->setValue(key, std::any_cast<int    >(value)); }
    else if (type == typeid(int64_t)) { self->setValue(key, std::any_cast<int64_t>(value)); }
    else if (type == typeid(float  )) { self->setValue(key, std::any_cast<float  >(value)); }
    else if (type == typeid(double )) { self->setValue(key, std::any_cast<double >(value)); }

    else if (type == typeid(std::string)) {
        auto str = std::any_cast<std::string>(value);
        self->setValue(key, str.c_str());
    }

    else if (type == typeid(dash::bytes)) {
        auto bytes = std::any_cast<dash::bytes>(value);
        self->setValue(key, bytes);
    }
}

void HPCParam::setValues(const std::map<std::string, std::any> &values) {
    for (auto &[key, value] : values) {
        HPCParam_setValue(this, key.c_str(), value);
    }
}

void HPCParam::setValues(const std::vector<std::any> &values) {
    int index = 0;
    for (auto &value : values) {
        std::string key = std::to_string(++index);
        HPCParam_setValue(this, key.c_str(), value);
    }
}

void HPCParam::setValue(const char *k, bool        v) { hpc_session_set_param_bool   (sessionID(), k, v); }
void HPCParam::setValue(const char *k, int         v) { hpc_session_set_param_int64  (sessionID(), k, v); }
void HPCParam::setValue(const char *k, int64_t     v) { hpc_session_set_param_int64  (sessionID(), k, v); }
void HPCParam::setValue(const char *k, float       v) { hpc_session_set_param_float64(sessionID(), k, v); }
void HPCParam::setValue(const char *k, double      v) { hpc_session_set_param_float64(sessionID(), k, v); }
void HPCParam::setValue(const char *k, const char *v) { hpc_session_set_param_string (sessionID(), k, v); }

void HPCParam::setValue(const char *key, const std::string &value) {
    hpc_session_set_param_string(sessionID(), key, value.c_str());
}

void HPCParam::setValue(const char *key, const dash::bytes &value) {
    hpc_session_set_param_bytes(sessionID(), key, value->data(), (int64_t)value->size());
}

std::any HPCParam::value(const char *key) {
    int64_t type = hpc_session_param_type(sessionID(), key);

    if (type == hpc_type_bool   ) { return hpc_session_param_bool   (sessionID(), key); }
    if (type == hpc_type_int64  ) { return hpc_session_param_int64  (sessionID(), key); }
    if (type == hpc_type_float64) { return hpc_session_param_float64(sessionID(), key); }

    if (type == hpc_type_string) {
        const char *str = hpc_session_param_string(sessionID(), key);
        return std::string(str);
    }

    if (type == hpc_type_bytes) {
        auto data = hpc_session_param_bytes_data(sessionID(), key);
        auto size = hpc_session_param_bytes_size(sessionID(), key);
        return dash::make_bytes(data, (size_t)size);
    }

    return std::any();
}

void HPCParam::setValue(int i, bool               v) { setValue(std::to_string(i).c_str(), v); }
void HPCParam::setValue(int i, int                v) { setValue(std::to_string(i).c_str(), v); }
void HPCParam::setValue(int i, int64_t            v) { setValue(std::to_string(i).c_str(), v); }
void HPCParam::setValue(int i, float              v) { setValue(std::to_string(i).c_str(), v); }
void HPCParam::setValue(int i, double             v) { setValue(std::to_string(i).c_str(), v); }
void HPCParam::setValue(int i, const char        *v) { setValue(std::to_string(i).c_str(), v); }
void HPCParam::setValue(int i, const std::string &v) { setValue(std::to_string(i).c_str(), v); }
void HPCParam::setValue(int i, const dash::bytes &v) { setValue(std::to_string(i).c_str(), v); }

std::any HPCParam::value(int index) {
    std::string key = std::to_string(index);
    return value(key.c_str());
}

void HPCParam::returnValue(bool               v) { setValue(hpc_key_return, v); }
void HPCParam::returnValue(int                v) { setValue(hpc_key_return, v); }
void HPCParam::returnValue(int64_t            v) { setValue(hpc_key_return, v); }
void HPCParam::returnValue(float              v) { setValue(hpc_key_return, v); }
void HPCParam::returnValue(double             v) { setValue(hpc_key_return, v); }
void HPCParam::returnValue(const char        *v) { setValue(hpc_key_return, v); }
void HPCParam::returnValue(const std::string &v) { setValue(hpc_key_return, v); }
void HPCParam::returnValue(const dash::bytes &v) { setValue(hpc_key_return, v); }

std::any HPCParam::returned() {
    return value(hpc_key_return);
}
