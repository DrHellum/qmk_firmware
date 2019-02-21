#include QMK_KEYBOARD_H

//Tap Dance Declarations
enum {
  TD_LSFT_CAPS = 0,
  TD_RSFT_CAPS = 1,
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_LSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  [TD_RSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* ISO 5x1u layout (ISO German keyboard layout shown)
   *
   * This layout starts from a standard ISO 60% layout, but replaces the
   * four 1.25u modifier keys in the bottom right corner with five 1u keys,
   * enabling the user to have VIM-style arrows on this area of the board.
   * ,-----------------------------------------------------------------------------------------.
   * | Esc | 1 ! | 2 " | 3 § | 4 $ | 5 % | 6 & | 7 / | 8 ( | 9 ) | 0 = | ß ? | ´ ` | Del | Bck |
   * |-----------------------------------------------------------------------------------------|
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Z  |  U  |  I  |  O  |  P  |  Ä  | + * | Enter  |
   * |----------------------------------------------------------------------------------       |
   * | Layer_1 |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  Ö  |  Ü  | # ' |       |
   * |-----------------------------------------------------------------------------------------|
   * | Shift | < > |  Y  |  X  |  C  |  V  |  B  |  N  |  M  | , ; | . : | - _ | Shift         |
   * |-----------------------------------------------------------------------------------------|
   * | LCtl  | LGUI  | LAlt  |            Space                  |RAlt |Left |Down | Up  |Right|
   * `-----------------------------------------------------------------------------------------'
   */
  LAYOUT_60_b_iso( 
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL, KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
    MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
    TD(TD_LSFT_CAPS), KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TD(TD_RSFT_CAPS), KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,    KC_SPC, KC_SPC,          KC_RALT, KC_RCTL, KC_LEFT, KC_RIGHT, KC_DOWN
  ),


  LAYOUT_60_b_iso(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, KC_DEL,
    KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT,   RESET,  KC_NO,  KC_NO, KC_PGUP, KC_NO, KC_PGDN,  KC_PSCR, KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_VOLD, KC_VOLU, KC_MUTE, KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END,  KC_DEL,  KC_NO,   KC_NO,
    KC_LSFT, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_NO, KC_NO, KC_NO,   KC_RSFT, KC_PGUP,
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,    KC_BSPC, KC_SPC,                            KC_RALT,  KC_RCTRL, KC_HOME, KC_END, KC_PGDN
  ),

};

// Set underglow RGB leds to yellow
// Find the list of available colors in quantum/rgblight_list.h
void matrix_init_user(void) {
  rgblight_sethsv_noeeprom_yellow();
  DDRB |= (1 << 2);
  PORTB &= ~(1 << 2);
}

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    PORTB |= (1 << 2);
    rgblight_sethsv (0, 0, 255);
  } else {
    PORTB &= ~(1 << 2);
    rgblight_sethsv (255,255,255);
  }
}

