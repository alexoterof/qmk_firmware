/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)


// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_LGUI, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_ESC, KC_LALT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, MO(1), MO(3), TO(1), KC_LCTL, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT, KC_MPLY, MO(4), KC_BSPC, KC_SPC, KC_TAB, KC_LGUI, LALT_T(KC_ENT), MO(2), MO(4), LGUI(KC_SPC)),
	[1] = LAYOUT(KC_TRNS, KC_BTN5, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, KC_DEL, KC_HOME, KC_UP, KC_END, KC_NO, KC_TRNS, KC_TRNS, KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_INS, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN3, KC_TRNS, KC_TRNS, KC_ACL1, KC_ACL2, TO(0), KC_TRNS, KC_NO, LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT(KC_TRNS, KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, KC_PIPE, KC_BSLS, KC_7, KC_8, KC_9, KC_ASTR, KC_CAPS, KC_TRNS, KC_HASH, KC_DLR, KC_LPRN, KC_RPRN, KC_AMPR, KC_EQL, KC_4, KC_5, KC_6, KC_PLUS, KC_GRV, KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_1, KC_2, KC_3, KC_MINS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[3] = LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, LAG(KC_4), KC_TRNS, SGUI(KC_LEFT), LGUI(KC_UP), SGUI(KC_RGHT), KC_TRNS, KC_TRNS, KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_TRNS, KC_TRNS, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_RGHT), KC_TRNS, KC_TRNS, KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[4] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS, KC_TRNS, KC_MRWD, KC_MPLY, KC_MFFD, KC_TRNS, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};
