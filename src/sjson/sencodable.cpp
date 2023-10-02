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
    //"_active" should be null when entering this function.
    _active = new fields_t;
}

encodable_object::~encodable_object() {
    _bucket.erase(this);
}

const std::map<std::string, encodable_field *> &encodable_object::fields() const {
    //"map" should be nonnull.
    fields_t *map = _bucket[this];
    return *map;
}

void encodable_object::collect() {
    //"_active" should be nonnull.
    if (!_active->empty()) {
        _bucket.insert({ this, _active });
    }
    _active = nullptr;
}

} //end sjson.
