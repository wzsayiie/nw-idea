#include "sencodable.h"

namespace sjson {

typedef std::map<std::string  , base_field   *> store_fields;
typedef std::map<base_object *, store_fields *> store_bucket;

static store_bucket  _bucket ;
static store_fields *_active = nullptr;

void encodable::on_encode() {}
void encodable::on_decode() {}

base_field::base_field(const char *name) {
    if (!name || *name == '\0') {
        return;
    }
    if (_active == nullptr) {
        return;
    }

    _active->insert({ name, this });
}

base_object::base_object() {
    //"_active" should be null when entering this function.
    _active = new store_fields;
}

base_object::~base_object() {
    _bucket.erase(this);
}

const std::map<std::string, base_field *> &base_object::fields() {
    //"s" should be nonnull.
    store_fields *s = _bucket[this];
    return *s;
}

void base_object::collect() {
    //"_active" should be nonnull.
    if (!_active->empty()) {
        _bucket.insert({ this, _active });
    }
    _active = nullptr;
}

} //end sjson.
