#include "sencodable.h"

namespace sjson {

typedef std::map<std::string             , encodable_field *> fields_t;
typedef std::map<const encodable_object *, fields_t        *> bucket_t;

static bucket_t  _bucket ;
static fields_t *_active = nullptr;

encodable_field::encodable_field(const char *name) {
    if (!name || *name == '\0') {
        return;
    }
    if (_active == nullptr) {
        return;
    }

    _active->insert({ name, this });
}

encodable_object::encodable_object() {
    if (_active) {
        //this branch will not run if normal.
        delete _active;
    }
    _active = new fields_t;
}

encodable_object::~encodable_object() {
    _bucket.erase(this);
}

const std::map<std::string, encodable_field *> &encodable_object::fields() const {
    auto it = _bucket.find(this);
    if (it != _bucket.end()) {
        return *it->second;
    }
    
    //this branch will not run if normal.
    static std::map<std::string, encodable_field *> empty;
    return empty;
}

void encodable_object::collect() {
    if (_active) {
        if (!_active->empty()) {
            _bucket.insert({ this, _active });
        } else {
            delete _active;
        }
    }
    _active = nullptr;
}

} //end sjson.
