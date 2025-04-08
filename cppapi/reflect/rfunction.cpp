#include "rfunction.h"
#include "dlazy.h"

namespace reflect {

struct stack_frame {
    std::vector<any> args;
    any returned;
};
static dash::lazy<std::vector<stack_frame>> g_frames;

int get_arg_count() {
    if (!g_frames->empty()) {
        std::vector<any> &args = g_frames->back().args;
        return (int)args.size();
    }
    return 0;
}

any get_arg_value(int index) {
    if (g_frames->empty()) {
        return nullptr;
    }

    std::vector<any> &args = g_frames->back().args;
    if (index < 0 || (int)args.size() <= index) {
        return nullptr;
    }

    return args.at(index);
}

void return_value(const any &value) {
    if (!g_frames->empty()) {
        g_frames->back().returned = value;
    }
}

any generic_function::call_with_args(const std::vector<any> &args) const {
    stack_frame frame = { args };
    g_frames->push_back(frame);

    on_call();

    any returned = g_frames->back().returned;
    g_frames->pop_back();
    return returned;
}

} //end reflect.
