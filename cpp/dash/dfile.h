#pragma once

#include <cstddef>
#include <functional>

namespace dash {

void read_file (const char *path, const std::function<void *(size_t size)> &buffer);
void write_file(const char *path, const void *bytes, size_t size);

} //end dash.
