/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap.h"
#include "keymap_french.h"
#include "helpers.h"
#include "french_symbols.h"



// TAP DANCE

void dance_layers_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
    layer_move(3);
  } else if (state->count == 2) {
    layer_move(0);
  } else if (state->count == 1) {
    SEND_STRING(SS_TAP(X_TAB));
  }
}

// void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
//   if (state->count == 1) {
//     unregister_code (KC_LCTL);
//     unregister_code (KC_SCLN);
//   } else {
//     unregister_code (KC_SCLN);
//   }
// }

// qk_tap_dance_action_t tap_dance_actions[] = {
//  [CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset)
// };

tap_dance_action_t tap_dance_actions[] = {
    [TD_LAYERS] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_layers_finished, NULL)
};


// -------------------------------------------------------------------------

// bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
//     for (uint8_t i = led_min; i < led_max; i++) {
//         switch(get_highest_layer(layer_state|default_layer_state)) {
//             case 0:
//                 rgb_matrix_set_color(i, RGB_RED);
//                 break;
//             // case 1:
//             //     rgb_matrix_set_color(i, RGB_YELLOW);
//             //     break;
//             case 1:
//                 rgb_matrix_set_color(i, RGB_BLUE);
//                 break;
//             case 2:
//                 rgb_matrix_set_color(i, RGB_YELLOW);
//                 break;
//             case 3:
//                 rgb_matrix_set_color(i, RGB_GREEN);
//                 break;
//             default:
//                 break;
//         }
//     }
//     return false;
// }




// ================================ OLED DISPLAY ==============================================
#ifdef OLED_ENABLE

// // rotate oled
// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//   return OLED_ROTATION_90;
// }

// Draw to OLED
bool oled_task_user() {
  // Set cursor position
  oled_set_cursor(0,1);

  // // Write text to OLED
  // oled_write("Hello World!", false);

  switch (get_highest_layer(layer_state)){
    case 0 :
      oled_write("COLEMAK FR ", false);
      break;
    case 1 :
      oled_write("ACCENTS      ", false);
      break;
    case 2 :
      oled_write("SHIFT        ", false);
      break;
    case 3 :
      oled_write("QUERTY REG   ", false);
      break;
    case 4 :
      oled_write("NUMPAD       ", false);
      break;
    case 5 :
      oled_write("SPECIAL_CHAR ", false);
      break;
    case 6 :
      oled_write("RGB          ", false);
      break;
    // case 4 :
    //   oled_write("", false);
    //   break;
  }
  
  return false;
}

#endif


// #define MY_LCTL ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_ESC)
#define MY_LCTL KC_LCTL
#define MY_LSFT LM(2, MOD_LSFT)

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &ko_make_with_layers(MOD_MASK_SHIFT, FR_COMM, FR_DLR,  1 << 2), 
    &ko_make_with_layers(MOD_MASK_SHIFT, FR_DOT,  FR_COLN, 1 << 2),
    &ko_make_with_layers(MOD_MASK_SHIFT, FR_QUES, FR_EXLM, 1 << 2),
    &ko_make_with_layers(MOD_MASK_SHIFT, FR_QUOT, FR_SCLN, 1 << 2),
    // &ko_make_with_layers(MOD_MASK_SHIFT, FR_AT,   FR_AGRV, 1 << 2);
    
    NULL // Null terminate the array of overrides!
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        
        case HT_E:
	        if (record->tap.count) { // tapped
	        	if (!record->event.pressed) {
	        		return false;
	        	}

	        	if (is_accent_layer()) {
	        		tap_e_grave();
	        	} else {
	        		tap_code(KC_E);
	        	}
	        } else { // held
	        	if (!record->event.pressed) {
	        		return false;
	        	}
        
	        	if (is_accent_layer()) {
	        		tap_e_circ();
	        	} else {
	        		tap_e_aigue();
	        	}
	        }
	
	        return false;
            
        case HT_C:
	        if (record->tap.count) {
	        	if (record->event.pressed) {
	        		tap_code(KC_C);
	        	}
	        } else {
	        	if (record->event.pressed) {
	        		tap_c_ced();
	        	}
	        }
	        return false;
	
        case HT_A:
            if (record->tap.count) {
                if (record->event.pressed) {
                    tap_a_grave();
                }
            } else {
                if (record->event.pressed) {
                    tap_a_circ();
                }
            }
        
            return false;
        
        case HT_U:
	        if (record->tap.count) {
	        	if (!record->event.pressed) {
	        		return false;
	        	}
        
	        	if (is_accent_layer()) {
	        		tap_u_grave();
	        	} else {
	        		tap_code(KC_U);
	        	}
	        } else {
	        	if (!record->event.pressed) {
	        		return false;
	        	}
        
	        	if (is_accent_layer()) {
	        		tap_u_circ();
	        	} else {
	        		tap_u_grave();
	        	}
	        }
        
	        return false;
        
        case HT_I:
	        if (record->tap.count) {
	        	if (!record->event.pressed) {
	        		return false;
	        	}
        
	        	if (is_accent_layer()) {
	        		tap_i_trema();
	        	} else {
	        		tap_code(KC_I);
	        	}
	        } else {
	        	if (record->event.pressed) {
	        		tap_i_circ();
	        	}
	        }
        
	        return false;

        case HT_O:
        	if (record->tap.count) {
        		if (!record->event.pressed) {
        			return false;
        		}
        
        		if (is_accent_layer()) {
        			tap_o_circ();
        		} else {
        			tap_code(KC_O);
        		}
        	} else {
        		if (record->event.pressed) {
        			tap_o_circ();
        		}
        	}
        
        	return false;
    }
    
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // _COLEMAK_FR
    [_COLEMAK_FR] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
TD(TD_LAYERS),    FR_Q,    FR_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_BSPC, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    FR_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O, FR_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MY_LSFT,    FR_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    FR_M, FR_COMM,  FR_DOT, FR_QUES,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(4),  KC_SPC,     KC_ENT,   MO(5), KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),
   // _ACCENTS_COLEMAK_FR
    [_ACCENTS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'

  ),
   // _SFT_LR_COLEMAK_FR
    [_SFT_COLEMAK_FR] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,---------------------------          --------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______,           _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+          --------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______,           _______, _______,MY_QUOTE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+          --------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, MY_POINT_VIRGULE,  _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+          --------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'

  ),

    // QWERTY REG, especially for keybr.com
    [_QWERTY_REG] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
TD(TD_LAYERS),    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MY_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(4),  KC_SPC,     KC_ENT,   MO(5), KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

    [_NUMPAD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT,   MO(6), KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),
    [_SPECIAL_CHAR] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(6),  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),
    [_RGB] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};