#include "cencodable.h"
#include <cassert>
#include "ddefine.h"
#include "dlazy.h"

namespace cson {

static d_define(_objects, dash::lazy<
    std::map<const encodable_object *, std::map<std::string, encodable_field *> *>
>);

static d_define(*_collecting_fields = nullptr,
    std::map<std::string, encodable_field *>
);

encodable_field::encodable_field(const char *name) {
    //STEP 2: insert fields:
    if (!name || *name == '\0') {
        return;
    }

    assert(_collecting_fields != nullptr);
    _collecting_fields->insert({ name, this });
}

encodable_object::encodable_object() {
    //STEP 1: prepare fields collection.
    assert(_collecting_fields == nullptr);
    _collecting_fields = new std::map<std::string, encodable_field *>;
}

encodable_object::~encodable_object() {
    //STEP 4: clean:
    auto it = _objects->find(this);
    assert(it != _objects->end());

    delete it->second;
    _objects->erase(it);
}

const std::map<std::string, encodable_field *> &encodable_object::fields() const {
    auto it = _objects->find(this);
    if (it != _objects->end()) {
        return *it->second;
    }

    static std::map<std::string, encodable_field *> empty;
    return empty;
}

void encodable_object::collect() {
    //STEP 3: bind collected fields to the object:
    assert(_collecting_fields != nullptr);

    if (!_collecting_fields->empty()) {
        _objects->insert({ this, _collecting_fields });
    } else {
        delete _collecting_fields;
    }
    _collecting_fields = nullptr;
}

} //end cson.
