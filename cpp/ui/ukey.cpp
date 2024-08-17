#include "ukey.h"
#include "rdefine.h"

define_reflectable_enum_const(UKey, Null   )
define_reflectable_enum_const(UKey, Back   )
define_reflectable_enum_const(UKey, Tab    )
define_reflectable_enum_const(UKey, Enter  )
define_reflectable_enum_const(UKey, Esc    )
define_reflectable_enum_const(UKey, Space  )
define_reflectable_enum_const(UKey, Quota  )
define_reflectable_enum_const(UKey, Comma  )
define_reflectable_enum_const(UKey, Sub    )
define_reflectable_enum_const(UKey, Period )
define_reflectable_enum_const(UKey, Slash  )
define_reflectable_enum_const(UKey, N0     )
define_reflectable_enum_const(UKey, N1     )
define_reflectable_enum_const(UKey, N2     )
define_reflectable_enum_const(UKey, N3     )
define_reflectable_enum_const(UKey, N4     )
define_reflectable_enum_const(UKey, N5     )
define_reflectable_enum_const(UKey, N6     )
define_reflectable_enum_const(UKey, N7     )
define_reflectable_enum_const(UKey, N8     )
define_reflectable_enum_const(UKey, N9     )
define_reflectable_enum_const(UKey, Semi   )
define_reflectable_enum_const(UKey, Equal  )
define_reflectable_enum_const(UKey, FtBrack)
define_reflectable_enum_const(UKey, BkSlash)
define_reflectable_enum_const(UKey, BkBrack)
define_reflectable_enum_const(UKey, Grave  )
define_reflectable_enum_const(UKey, A      )
define_reflectable_enum_const(UKey, B      )
define_reflectable_enum_const(UKey, C      )
define_reflectable_enum_const(UKey, D      )
define_reflectable_enum_const(UKey, E      )
define_reflectable_enum_const(UKey, F      )
define_reflectable_enum_const(UKey, G      )
define_reflectable_enum_const(UKey, H      )
define_reflectable_enum_const(UKey, I      )
define_reflectable_enum_const(UKey, J      )
define_reflectable_enum_const(UKey, K      )
define_reflectable_enum_const(UKey, L      )
define_reflectable_enum_const(UKey, M      )
define_reflectable_enum_const(UKey, N      )
define_reflectable_enum_const(UKey, O      )
define_reflectable_enum_const(UKey, P      )
define_reflectable_enum_const(UKey, Q      )
define_reflectable_enum_const(UKey, R      )
define_reflectable_enum_const(UKey, S      )
define_reflectable_enum_const(UKey, T      )
define_reflectable_enum_const(UKey, U      )
define_reflectable_enum_const(UKey, V      )
define_reflectable_enum_const(UKey, W      )
define_reflectable_enum_const(UKey, X      )
define_reflectable_enum_const(UKey, Y      )
define_reflectable_enum_const(UKey, Z      )
define_reflectable_enum_const(UKey, F1     )
define_reflectable_enum_const(UKey, F2     )
define_reflectable_enum_const(UKey, F3     )
define_reflectable_enum_const(UKey, F4     )
define_reflectable_enum_const(UKey, F5     )
define_reflectable_enum_const(UKey, F6     )
define_reflectable_enum_const(UKey, F7     )
define_reflectable_enum_const(UKey, F8     )
define_reflectable_enum_const(UKey, F9     )
define_reflectable_enum_const(UKey, F10    )
define_reflectable_enum_const(UKey, F11    )
define_reflectable_enum_const(UKey, F12    )
define_reflectable_enum_const(UKey, Left   )
define_reflectable_enum_const(UKey, Right  )
define_reflectable_enum_const(UKey, Up     )
define_reflectable_enum_const(UKey, Down   )

define_reflectable_const(UModifier_Alt  )
define_reflectable_const(UModifier_Caps )
define_reflectable_const(UModifier_Cmd  )
define_reflectable_const(UModifier_Ctrl )
define_reflectable_const(UModifier_Shift)

static char GetShiftChar(char ch) {
    static char m[128] = {0};
    if (m['a'] == 0) {
        for (char c = 'a'; c <= 'z'; c++) {
            m[c] = c - 'a' + 'A';
        }
        m['\''] = '"';
        m[',' ] = '<';
        m['-' ] = '_';
        m['.' ] = '>';
        m['/' ] = '?';
        m['0' ] = '!';
        m['1' ] = '@';
        m['2' ] = '#';
        m['3' ] = '$';
        m['4' ] = '%';
        m['5' ] = '^';
        m['6' ] = '&';
        m['7' ] = '*';
        m['8' ] = '(';
        m['9' ] = ')';
        m[';' ] = ':';
        m['=' ] = '+';
        m['[' ] = '{';
        m['\\'] = '|';
        m[']' ] = ']';
        m['`' ] = '~';
    }

    if (0 <= ch && ch <= 127) {
        return m[ch];
    }
    return 0;
}

define_reflectable_function(UGetChar, "args:key,modifiers")
char UGetChar(UKey key, UModifiers modifiers) {
    auto ch = (char)key;

    if (modifiers | UModifier_Caps) {
        if ('a' <= ch && ch <= 'z') {
            return ch - 'a' + 'A';
        }
    }
    if (modifiers | UModifier_Shift) {
        return GetShiftChar(ch);
    }

    return 0;
}
