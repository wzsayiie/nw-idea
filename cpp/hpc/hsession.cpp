#include "hsession.h"
#include "danycast.h"
#include "dbytes.h"
#include "hlow.h"

namespace hpc {

//args_session:

args_session::args_session() {
    _sid = hpc_session_create();
}

args_session::args_session(const args_session &that) {
    _sid = hpc_session_retain(that._sid);
}

args_session::args_session(args_session &&that) {
    _sid = that._sid;
    that._sid = 0;
}

args_session::~args_session() {
    hpc_session_release(_sid);
}

void args_session::reset(int64_t sid) {
    hpc_session_release(_sid);
    _sid = hpc_session_retain(sid);
}

int64_t args_session::sid() const {
    return _sid;
}

void args_session::set_proc_name(const char *name) {
    hpc_session_set_proc_name(_sid, name);
}

std::string args_session::proc_name() const {
    return hpc_session_proc_name(_sid);
}

void args_session::set_callback_id(int64_t callback_id) {
    hpc_session_set_callback_id(_sid, callback_id);
}

int64_t args_session::callback_id() const {
    return hpc_session_callback_id(_sid);
}

void args_session::set_args(const std::map<std::string, std::any> &args) {
    for (auto &[key, value] : args) {
        set_arg(key.c_str(), value);
    }
}

void args_session::set_args(const std::vector<std::any> &args) {
    int index = 0;
    for (auto &value : args) {
        set_arg(++index, value);
    }
}

void args_session::set_arg(const char *k, const std::any &v) {
    const std::type_info &type = v.type();
    
    if /**/ (type == typeid(bool   )) { hpc_session_set_arg_bool   (_sid, k, d_cast(bool   ) v); }
    else if (type == typeid(int    )) { hpc_session_set_arg_int64  (_sid, k, d_cast(int64_t) v); }
    else if (type == typeid(int64_t)) { hpc_session_set_arg_int64  (_sid, k, d_cast(int64_t) v); }
    else if (type == typeid(float  )) { hpc_session_set_arg_float64(_sid, k, d_cast(double ) v); }
    else if (type == typeid(double )) { hpc_session_set_arg_float64(_sid, k, d_cast(double ) v); }

    else if (type == typeid(std::string)) {
        auto str = d_cast(std::string) v;
        hpc_session_set_arg_string(_sid, k, str.c_str());
    }

    else if (type == typeid(dash::bytes)) {
        auto bytes = d_cast(dash::bytes) v;
        hpc_session_set_arg_bytes(_sid, k, bytes->data(), (int64_t)bytes->size());
    }
}

std::any args_session::arg(const char *key) const {
    int64_t type = hpc_session_arg_type(_sid, key);

    switch (type) {
        case hpc_type_bool   : return hpc_session_arg_bool   (_sid, key);
        case hpc_type_int64  : return hpc_session_arg_int64  (_sid, key);
        case hpc_type_float64: return hpc_session_arg_float64(_sid, key);

        case hpc_type_string: {
            const char *str = hpc_session_arg_string(_sid, key);
            return std::string(str);
        }

        case hpc_type_bytes: {
            auto data = hpc_session_arg_bytes_data(_sid, key);
            auto size = hpc_session_arg_bytes_size(_sid, key);
            return dash::make_bytes(data, (size_t)size);
        }

        default: return std::any();
    }
}

void args_session::set_arg(int index, const std::any &value) {
    set_arg(std::to_string(index).c_str(), value);
}

std::any args_session::arg(int index) const {
    return arg(std::to_string(index).c_str());
}

void args_session::set_ret(const std::any &value) {
    set_arg(hpc_key_ret, value);
}

std::any args_session::ret() const {
    return arg(hpc_key_ret);
}

//session:

void session::callback(const std::map<std::string, std::any> &args) const {
    args_session obj;

    //IMPORTANT: the call's callback-id and callback's, must be same.
    obj.set_callback_id(this->callback_id());
    obj.set_args(args);

    hpc_callback(obj.sid());
}

void session::callback(const std::vector<std::any> &args) const {
    args_session obj;

    obj.set_callback_id(this->callback_id());
    obj.set_args(args);

    hpc_callback(obj.sid());
}

} //end hpc.
