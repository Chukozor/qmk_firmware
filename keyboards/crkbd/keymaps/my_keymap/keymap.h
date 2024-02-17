#pragma once

#define HT_E TT(16) // aliases
#define HT_C TT(17)
#define HT_A TT(18)
#define HT_U TT(19)
#define HT_I TT(20)
#define HT_O TT(21)

enum {
 TD_LAYERS = 0,
//  CT_CLN,
//  CT_EGG,
//  CT_FLSH,
//  X_TAP_DANCE
};

enum layers{
    _COLEMAK_FR,
    _ACCENTS,
    _SFT_COLEMAK_FR,
    _QWERTY_REG,
    _NUMPAD,
    _SPECIAL_CHAR,
    _RGB
};

enum custom_keycodes {
    MY_QUOTE = SAFE_RANGE,
    MY_POINT_VIRGULE,
};