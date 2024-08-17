#pragma once

#include "rdeclare.h"

declare_reflectable_enum(UKey)
enum class UKey {
    Null    = 0x00, //  0

    Back    = 0x08, //  8
    Tab     = 0x09, //  9
    Enter   = 0x0A, // 10
    Esc     = 0x1B, // 27
    Space   = 0x20, // 32

    Quota   = '\'', // 39, shift " ( 34)
    Comma   = ',' , // 44, shift < ( 60)
    Sub     = '-' , // 45, shift _ ( 95)
    Period  = '.' , // 46, shift > ( 62)
    Slash   = '/' , // 47, shift ? ( 63)

    N0      = '0' , // 48, shift ! ( 33)
    N1      = '1' , // 49, shift @ ( 64)
    N2      = '2' , // 50, shift # ( 35)
    N3      = '3' , // 51, shift $ ( 36)
    N4      = '4' , // 52, shift % ( 37)
    N5      = '5' , // 53, shift ^ ( 94)
    N6      = '6' , // 54, shift & ( 38)
    N7      = '7' , // 55, shift * ( 42)
    N8      = '8' , // 56, shift ( ( 40)
    N9      = '9' , // 57, shift ) ( 41)

    Semi    = ';' , // 59, shift : ( 58)
    Equal   = '=' , // 61, shift + ( 43)

    FtBrack = '[' , // 91, shift { (123)
    BkSlash = '\\', // 92, shift | (124)
    BkBrack = ']' , // 93, shift ] (125)
    Grave   = '`' , // 96, shift ~ (126)

    A       = 'a' , // 97, shift A ( 65)
    B       = 'b' , // 98, shift B ( 66)
    C       = 'c' , // 99, shift C ( 67)
    D       = 'd' , //100, shift D ( 68)
    E       = 'e' , //101, shift E ( 69)
    F       = 'f' , //102, shift F ( 70)
    G       = 'g' , //103, shift G ( 71)
    H       = 'h' , //104, shift H ( 72)
    I       = 'i' , //105, shift I ( 73)
    J       = 'j' , //106, shift J ( 74)
    K       = 'k' , //107, shift K ( 75)
    L       = 'l' , //108, shift L ( 76)
    M       = 'm' , //109, shift M ( 77)
    N       = 'n' , //110, shift N ( 78)
    O       = 'o' , //111, shift O ( 79)
    P       = 'p' , //112, shift P ( 80)
    Q       = 'q' , //113, shift Q ( 81)
    R       = 'r' , //114, shift R ( 82)
    S       = 's' , //115, shift S ( 83)
    T       = 't' , //116, shift T ( 84)
    U       = 'u' , //117, shift U ( 85)
    V       = 'v' , //118, shift V ( 86)
    W       = 'w' , //119, shift W ( 87)
    X       = 'x' , //120, shift X ( 88)
    Y       = 'y' , //121, shift Y ( 89)
    Z       = 'z' , //122, shift Z ( 90)

    F1      = 0x80, //128
    F2      = 0x81, //129
    F3      = 0x82, //130
    F4      = 0x83, //131
    F5      = 0x84, //132
    F6      = 0x85, //133
    F7      = 0x86, //134
    F8      = 0x87, //135
    F9      = 0x88, //136
    F10     = 0x89, //137
    F11     = 0x8A, //138
    F12     = 0x8B, //139

    Left    = 0x8C, //140
    Right   = 0x8D, //141
    Up      = 0x8E, //142
    Down    = 0x8F, //143
};

typedef int UModifiers;

const int UModifier_Alt   = 1 << 0;
const int UModifier_Caps  = 1 << 1;
const int UModifier_Cmd   = 1 << 2;
const int UModifier_Ctrl  = 1 << 3;
const int UModifier_Shift = 1 << 4;

char UGetChar(UKey key, UModifiers modifiers);
