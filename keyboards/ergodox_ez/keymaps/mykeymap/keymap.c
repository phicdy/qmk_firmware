#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

#define C_S(kc) kc | 0x0100 | 0x0200 // `Ctrl + Shift + kc`(= `kc | 0x1400`)
#define A(kc) LALT(kc) // Alt + kc
#define C(kc) LCTL(kc) // Ctrl + kc
#define G(kc) LGUI(kc) // Cmd + kc
#define S(kc) LSFT(kc) // Shift + kc
#define Cm_S(kc) kc | 0x0800 | 0x0200 // `Cmd + Shift + kc`

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   +    |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |   (  |   )  |   _    |
 * |   =    |   1  |   2  |   3  |   4  |   5  |  {   |           |  }   |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   @    |
 * |--------+------+------+------+------+------|  (   |           |  )   |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |   "    |
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      | Eisu |           | Kana |      |      |   <  |   >  |   ?  |        |
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |(LCmd)|           |(RCmd)|   N  |   M  |   ,  |   .  |//Ctrl|   L2   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |AltSpc|Cmd +c|Cmd +v| Alt  | LCmd |                                       |   :  |   *  |   [  |   ]  |   \  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Left | Right|       |  `   |  ~   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |  Up  |       |  Del |        |      |
 *                                 |LShift|Space |------|       |------|  Esc   |Enter |
 *                                 |      |      | Down |       |  BSP |  /L1   |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LCBR,
        KC_TAB,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_LPRN,
        KC_LCTL,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   KC_LGUI,
        A(KC_SPC),      G(KC_C),      G(KC_V),KC_LALT,KC_LGUI,
                                                      KC_LEFT,KC_RGHT,
                                                              KC_UP,
                                              KC_LSFT,KC_SPC, KC_DOWN,
        // right hand
		KC_RCBR,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,           KC_MINS,
		KC_RPRN,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,           KC_AT,
				KC_H,   KC_J,   KC_K,   KC_L,   S(KC_SCLN),     KC_QUOT,
		KC_RGUI,KC_N,   KC_M,   KC_COMM,KC_DOT, CTL_T(KC_SLSH), TG(MDIA),
						KC_SCLN,KC_ASTR,KC_LBRC,KC_RBRC,        KC_BSLS,
		KC_GRV,KC_TILD,
		KC_DEL,
		KC_BSPC,LT(SYMB, KC_ESC), KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Eisu/Kana| F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Reset  |      |      |      |      |      |      |           |      |      |      |      |      |   ^  |   F12  |
 * |--------+------+------+------+------+------|  [   |           |   ]  |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|Ctrl+←|     |      |Ctrl+→|     |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |  <   |           |   >  |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,---------------.       ,-------------.
 *                                        |Cmd+Sht|Cmd+Sht|       |      |      |
 *                                        |+Left  |+Right |       |      |      |
 *                                 ,------|-------|-------|       |------+------+------.
 *                                 |      |       |Cmd+Sht|       |      |      |      |
 *                                 |      |       |  +Up  |       |      |      |      |
 *                                 |      |       |-------|       |------|      |      |
 *                                 |      |       |Cmd+Sht|       |      |      |      |
 *                                 |      |       | +Down |       |      |      |      |
 *                                 `----------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       A(KC_GRV),   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       RESET,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_LBRC,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,S(KC_COMM),
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       Cm_S(KC_LEFT),Cm_S(KC_RGHT),
                                               Cm_S(KC_UP),
                               KC_TRNS,KC_TRNS,Cm_S(KC_DOWN),
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_RBRC, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_CIRC, KC_F12,
                C(KC_LEFT),KC_TRNS,KC_TRNS,C(KC_RGHT),KC_TRNS,KC_TRNS,
       S(KC_DOT),KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Windows and Ubuntu 
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   !  |   "  |   #  |   $  |   %  |      |           |      |   &  |   '  |   (  |   )  |   ~  |   =    |
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   @    |
 * |--------+------+------+------+------+------|  {   |           |  }   |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |  +   |        |
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  | ;/ L1|        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      | Eisu |           | Eisu |      |      |   <  |   >  |   ?  |        |
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  | Kana |           | Kana |   N  |   M  |   ,  |   .  |//Ctrl|   L2   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |Ctrl+c|Ctrl+v| Alt  |LShift|                                       |   :  |   *  |   [  |   ]  |   \  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Left | Right|       |   `  |  ~   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |  Up  |       |  Del |        |      |
 *                                 |LShift|Space |------|       |------| Esc/L1 |Enter |
 *                                 |      |      | Down |       |  BSP |        |      |
 *                                 `--------------------'       `----------------------'
 */
// Windows and Ubuntu 
[MDIA] = LAYOUT_ergodox(
        // left hand
        KC_TRNS, KC_1,        KC_2,   KC_3,   KC_4,   KC_5, KC_TRNS,
        KC_TAB,  KC_Q,        KC_W,   KC_E,   KC_R,   KC_T, KC_RCBR,
        KC_LCTL, KC_A,        KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT, CTL_T(KC_Z), KC_X,   KC_C,   KC_V,   KC_B, A(KC_GRV),
        KC_TRNS, C(KC_C),     C(KC_V),KC_LALT,KC_LSFT,
                                                      KC_LEFT,KC_RGHT,
                                                              KC_UP,
                                              KC_LSFT,KC_SPC, KC_DOWN,
        // right hand
		KC_TRNS, KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
		KC_PIPE, KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_LBRC,
				 KC_H,   KC_J,   KC_K,   KC_L,   LT(SYMB, KC_SCLN),KC_TRNS,
		A(KC_GRV),KC_N, KC_M,   KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_TRNS,
						 KC_QUOT,LSFT(KC_QUOT),KC_RBRC,KC_BSLS,    KC_JYEN,
		KC_LCBR, KC_RPRN,
		KC_DEL,
		KC_BSPC, LT(SYMB, KC_ESC), KC_ENT
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
	case 0:
	if (record->event.pressed) {
	  SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
	}
	break;
	case 1:
	if (record->event.pressed) { // For resetting EEPROM
	  eeconfig_init();
	}
	break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case SYMB:
            ergodox_right_led_1_on();
            break;
        case MDIA:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
