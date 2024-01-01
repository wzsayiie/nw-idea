#include "dbytes.h"

namespace dash {

bytes_ptr make_bytes(const uint8_t *begin, const uint8_t *end) {
    if (begin && begin < end) {
        return std::make_shared<std::vector<uint8_t>>(begin, end);
    }
    return make_bytes();
}

bytes_ptr make_bytes(const uint8_t *data, size_t size) {
    if (data && size > 0) {
        return std::make_shared<std::vector<uint8_t>>(data, data + size);
    }
    return make_bytes();
}

bytes_ptr make_bytes(size_t size) {
    if (size > 0) {
        return std::make_shared<std::vector<uint8_t>>(size);
    }
    return make_bytes();
}

bytes_ptr make_bytes() {
    return std::make_shared<std::vector<uint8_t>>();
}

} //end dash.
