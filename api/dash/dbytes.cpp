#include "dbytes.h"

namespace dash {

bytes make_bytes(const void *begin, const void *end) {
    if (begin && begin < end) {
        return std::make_shared<u8vec>((uint8_t *)begin, (uint8_t *)end);
    }
    return std::make_shared<u8vec>();
}

bytes make_bytes(const void *data, size_t size) {
    if (data && size > 0) {
        return std::make_shared<u8vec>((uint8_t *)data, (uint8_t *)data + size);
    }
    return std::make_shared<u8vec>();
}

bytes make_bytes(size_t size) {
    return std::make_shared<u8vec>(size);
}

bytes make_bytes() {
    return std::make_shared<u8vec>();
}

} //end dash.
