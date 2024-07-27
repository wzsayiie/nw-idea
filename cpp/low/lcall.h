#pragma once

namespace low {

void set (const char *name, void (*proc)(void *), void *param);
void call(const char *name);

} //end low.
