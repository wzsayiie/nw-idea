#include "hpclow.h"
#include <map>
#include <string>
#include <vector>
#include "dbytes.h"
#include "dlazy.h"

struct hpc_value {
    int64_t     type = hpc_type_void;
    int64_t     word = 0;
    std::string str  ;
    dash::bytes bytes;
};

struct hpc_session {
    int64_t     retain_count  = 1;
    std::string procedure_name;
    int64_t     callback_id   = 0;

    std::map<std::string, hpc_value> param;
};

int64_t hpc_session_create() {
    return (int64_t)new hpc_session;
}

int64_t hpc_session_retain(int64_t sid) {
    if (auto obj = (hpc_session *)sid) {
        obj->retain_count += 1;
    }
    return sid;
}

void hpc_session_release(int64_t sid) {
    if (auto obj = (hpc_session *)sid) {
        if (--(obj->retain_count) <= 0) {
            delete obj;
        }
    }
}

void hpc_session_set_procedure_name(int64_t sid, const char *name) {
    if (auto obj = (hpc_session *)sid) {
        obj->procedure_name = name ? name : "";
    }
}

const char *hpc_session_procedure_name(int64_t sid) {
    if (auto obj = (hpc_session *)sid) {
        return obj->procedure_name.c_str();
    }
    return "";
}

void hpc_session_set_callback_id(int64_t sid, int64_t callback_id) {
    if (auto obj = (hpc_session *)sid) {
        obj->callback_id = callback_id;
    }
}

int64_t hpc_session_callback_id(int64_t sid) {
    static int64_t id_count = 0;

    if (auto obj = (hpc_session *)sid) {
        //IMPORTANT: if callback-id is 0, generate a one.
        if (obj->callback_id == 0) {
            obj->callback_id = ++id_count;
        }
        return obj->callback_id;
    }
    return 0;
}

static void set_param(int64_t sid, const char *key, const hpc_value &value) {
    if (auto obj = (hpc_session *)sid) {
        if (key && *key) {
            obj->param[key] = value;
        }
    }
}

void hpc_session_set_param_bool(int64_t sid, const char *key, bool value) {
    set_param(sid, key, {
        .type = hpc_type_bool,
        .word = (int64_t)value,
    });
}

void hpc_session_set_param_int64(int64_t sid, const char *key, int64_t value) {
    set_param(sid, key, {
        .type = hpc_type_int64,
        .word = value,
    });
}

void hpc_session_set_param_float64(int64_t sid, const char *key, double value) {
    set_param(sid, key, {
        .type = hpc_type_float64,
        .word = *(int64_t *)&value,
    });
}

void hpc_session_set_param_string(int64_t sid, const char *key, const char *value) {
    set_param(sid, key, {
        .type = hpc_type_string,
        .str  = value ? value : "",
    });
}

void hpc_session_set_param_bytes(int64_t sid, const char *key, const void *value, int64_t size) {
    set_param(sid, key, {
        .type  = hpc_type_string,
        .bytes = dash::make_bytes(value, (size_t)size),
    });
}

static const hpc_value &param(int64_t sid, const char *key) {
    static hpc_value nil;

    auto obj = (hpc_session *)sid;
    if (!obj) {
        return nil;
    }

    if (!key || !*key) {
        return nil;
    }

    auto it = obj->param.find(key);
    if (it == obj->param.end()) {
        return nil;
    }

    return it->second;
}

int64_t hpc_session_param_type(int64_t sid, const char *key) {
    const hpc_value &value = param(sid, key);
    return value.type;
}

bool hpc_session_param_bool(int64_t sid, const char *key) {
    const hpc_value &value = param(sid, key);
    if (value.type == hpc_type_bool) {
        return (bool)value.word;
    }
    return false;
}

int64_t hpc_session_param_int64(int64_t sid, const char *key) {
    const hpc_value &value = param(sid, key);
    if (value.type == hpc_type_int64) {
        return value.word;
    }
    return 0;
}

double hpc_session_param_float64(int64_t sid, const char *key) {
    const hpc_value &value = param(sid, key);
    if (value.type == hpc_type_float64) {
        return *(double *)&value.word;
    }
    return 0;
}

const char *hpc_session_param_string(int64_t sid, const char *key) {
    const hpc_value &value = param(sid, key);
    if (value.type == hpc_type_string) {
        return value.str.c_str();
    }
    return "";
}

const void *hpc_session_param_bytes_data(int64_t sid, const char *key) {
    const hpc_value &value = param(sid, key);
    if (value.type == hpc_type_bytes) {
        return value.bytes->data();
    }
    return nullptr;
}

int64_t hpc_session_param_bytes_size(int64_t sid, const char *key) {
    const hpc_value &value = param(sid, key);
    if (value.type == hpc_type_bytes) {
        return (int64_t)value.bytes->size();
    }
    return 0;
}

static dash::lazy<std::vector<bool (*)(int64_t)>> _call_procedures;
static dash::lazy<std::vector<bool (*)(int64_t)>> _callback_procedures;

static void add(std::vector<bool (*)(int64_t)> *procedures, bool(*item)(int64_t sid)) {
    if (item) {
        procedures->push_back(item);
    }
}

static void call(const std::vector<bool (*)(int64_t)> &procedures, int64_t sid) {
    for (auto &item : procedures) {
        bool finished = item(sid);

        if (finished) {
            break;
        }
    }
}

void hpc_add_call_procedure    (bool(*p)(int64_t)) { if (p) { add(&*_call_procedures    , p); } }
void hpc_add_callback_procedure(bool(*p)(int64_t)) { if (p) { add(&*_callback_procedures, p); } }

void hpc_call    (int64_t sid) { call(*_call_procedures    , sid); }
void hpc_callback(int64_t sid) { call(*_callback_procedures, sid); }
