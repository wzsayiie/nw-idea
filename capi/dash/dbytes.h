#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace dash {

typedef std::vector<uint8_t>   u8vec;
typedef std::shared_ptr<u8vec> bytes;

bytes make_bytes(const void *begin, const void *end);
bytes make_bytes(const void *data, size_t size);
bytes make_bytes(size_t size);
bytes make_bytes();

} //end dash.
