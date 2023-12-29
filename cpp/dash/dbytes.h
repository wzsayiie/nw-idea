#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace dash {

typedef std::vector<uint8_t>   bytes;
typedef std::shared_ptr<bytes> bytes_ptr;

bytes_ptr make_bytes(const uint8_t *begin, const uint8_t *end);
bytes_ptr make_bytes(const uint8_t *data, size_t size);
bytes_ptr make_bytes(size_t size);
bytes_ptr make_bytes();

} //end dash.
