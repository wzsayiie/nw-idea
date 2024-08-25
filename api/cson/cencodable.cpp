#include "cencodable.h"
#include <cassert>
#include "dlazy.h"

namespace cson {

static dash::lazy<std::map<const encodable_object *, std::map<std::string, encodable_field *> *>> g_objects;
static std::map<std::string, encodable_field *> *g_collecting_fields = nullptr;

encodable_field::encodable_field(const char *name) {
    //STEP 2: insert fields:
    if (!name || *name == '\0') {
        return;
    }

    assert(g_collecting_fields != nullptr);
    g_collecting_fields->insert({ name, this });
}

encodable_object::encodable_object() {
    //STEP 1: prepare fields collection.
    assert(g_collecting_fields == nullptr);
    g_collecting_fields = new std::map<std::string, encodable_field *>;
}

encodable_object::~encodable_object() {
    //STEP 4: clean:
    auto it = g_objects->find(this);
    assert(it != g_objects->end());

    delete it->second;
    g_objects->erase(it);
}

const std::map<std::string, encodable_field *> &encodable_object::fields() const {
    auto it = g_objects->find(this);
    if (it != g_objects->end()) {
        return *it->second;
    }

    static std::map<std::string, encodable_field *> empty;
    return empty;
}

void encodable_object::collect() {
    //STEP 3: bind collected fields to the object:
    assert(g_collecting_fields != nullptr);

    if (!g_collecting_fields->empty()) {
        g_objects->insert({ this, g_collecting_fields });
    } else {
        delete g_collecting_fields;
    }
    g_collecting_fields = nullptr;
}

} //end cson.
