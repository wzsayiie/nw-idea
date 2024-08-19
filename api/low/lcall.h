#pragma once

namespace low {

void set (const char *name, void (*proc)(int), int param);
void call(const char *name);

} //end low.
