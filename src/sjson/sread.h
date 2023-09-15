#pragma once

#include <string>

namespace sjson {

void already_read_context(const std::string &text);
std::string last_read_error();

} //end sjson.
