#pragma once

#include <vector>
#include "sencodable.h"

namespace sjson {

void prepare_read_context(const std::string &text);
std::string last_read_error();

} //end sjson.
