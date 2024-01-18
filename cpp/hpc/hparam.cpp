#include "hparam.h"
#include "hlow.h"

HParam::~HParam() {
    h_session_release(_sessionID);
}

void HParam::setSessionID(int64_t sid) {
    h_session_release(_sessionID);
    _sessionID = h_session_retain(sid);
}

int64_t HParam::sessionID() {
    if (!_sessionID) {
        _sessionID = h_session_create();
    }
    return _sessionID;
}

void HParam::setProcedureName(const char *name) {
    h_session_set_procedure_name(sessionID(), name);
}

std::string HParam::procedureName() {
    return h_session_procedure_name(sessionID());
}

void HParam::setCallbackID(int64_t callback_id) {
    h_session_set_callback_id(sessionID(), callback_id);
}

int64_t HParam::callbackID() {
    return h_session_callback_id(sessionID());
}

static void HParam_setValue(HParam *self, const char *key, const std::any &value) {
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

void HParam::setValues(const std::map<std::string, std::any> &values) {
    for (auto &[key, value] : values) {
        HParam_setValue(this, key.c_str(), value);
    }
}

void HParam::setValues(const std::vector<std::any> &values) {
    int index = 0;
    for (auto &value : values) {
        std::string key = std::to_string(++index);
        HParam_setValue(this, key.c_str(), value);
    }
}

void HParam::setValue(const char *k, bool        v) { h_session_set_param_bool   (sessionID(), k, v); }
void HParam::setValue(const char *k, int         v) { h_session_set_param_int64  (sessionID(), k, v); }
void HParam::setValue(const char *k, int64_t     v) { h_session_set_param_int64  (sessionID(), k, v); }
void HParam::setValue(const char *k, float       v) { h_session_set_param_float64(sessionID(), k, v); }
void HParam::setValue(const char *k, double      v) { h_session_set_param_float64(sessionID(), k, v); }
void HParam::setValue(const char *k, const char *v) { h_session_set_param_string (sessionID(), k, v); }

void HParam::setValue(const char *key, const dash::bytes &value) {
    h_session_set_param_bytes(sessionID(), key, value->data(), (int64_t)value->size());
}

std::any HParam::value(const char *key) {
    int64_t type = h_session_param_type(sessionID(), key);

    if (type == h_type_bool   ) { return h_session_param_bool   (sessionID(), key); }
    if (type == h_type_int64  ) { return h_session_param_int64  (sessionID(), key); }
    if (type == h_type_float64) { return h_session_param_float64(sessionID(), key); }

    if (type == h_type_string) {
        const char *str = h_session_param_string(sessionID(), key);
        return std::string(str);
    }

    if (type == h_type_bytes) {
        auto data = h_session_param_bytes_data(sessionID(), key);
        auto size = h_session_param_bytes_size(sessionID(), key);
        return dash::make_bytes(data, (size_t)size);
    }

    return std::any();
}

void HParam::setValue(int i, bool               v) { setValue(std::to_string(i).c_str(), v); }
void HParam::setValue(int i, int                v) { setValue(std::to_string(i).c_str(), v); }
void HParam::setValue(int i, int64_t            v) { setValue(std::to_string(i).c_str(), v); }
void HParam::setValue(int i, float              v) { setValue(std::to_string(i).c_str(), v); }
void HParam::setValue(int i, double             v) { setValue(std::to_string(i).c_str(), v); }
void HParam::setValue(int i, const char        *v) { setValue(std::to_string(i).c_str(), v); }
void HParam::setValue(int i, const dash::bytes &v) { setValue(std::to_string(i).c_str(), v); }

std::any HParam::value(int index) {
    std::string key = std::to_string(index);
    return value(key.c_str());
}

void HParam::returnValue(bool               v) { setValue(h_key_return, v); }
void HParam::returnValue(int                v) { setValue(h_key_return, v); }
void HParam::returnValue(int64_t            v) { setValue(h_key_return, v); }
void HParam::returnValue(float              v) { setValue(h_key_return, v); }
void HParam::returnValue(double             v) { setValue(h_key_return, v); }
void HParam::returnValue(const char        *v) { setValue(h_key_return, v); }
void HParam::returnValue(const dash::bytes &v) { setValue(h_key_return, v); }

std::any HParam::returned() {
    return value(h_key_return);
}
