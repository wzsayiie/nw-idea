#include "robject.h"

namespace reflect {

void object::dispose() {
    if (!_disposed) {
        _disposed = true;
        on_dispose();
    }
}

void object::on_dispose() {
}

} //end reflect.
