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
#include "kyria.h"

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria "), false);
#if defined(KEYBOARD_splitkb_kyria_rev1)
        oled_write_P(PSTR("rev1\n\n"), false);
#elif defined(KEYBOARD_splitkb_kyria_rev2)
        oled_write_P(PSTR("rev2\n\n"), false);
#endif
        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer -> "), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:
                oled_write_P(PSTR("Escritura\n"), false);
                break;
            case 1:
                oled_write_P(PSTR("Mov\n"), false);
                break;
            case 2:
                oled_write_P(PSTR("Simbolos\n"), false);
                break;
            case 3:
                oled_write_P(PSTR("Funcion\n"), false);
                break;
            case 4:
                oled_write_P(PSTR("Meta\n"), false);
                break;
            default:
                oled_write_P(PSTR("Desconocina\n"), false);
        }

        // Host Keyboard LED Status
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,224,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,224,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,224,224,224,224,224,224,  0,  0,  0,  0,  0,  0,224,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,240,240,240,241,241,241,241,  0,  0,  0,128,128,128,240,240,240,240,240,240,248,255,255,255,255,  0,  0,128,128,128,240,240,240,240,240,240,240,240,128,128,128,  0,  0,  0,  0,  0,  0,240,240,240,240,240,240,240,128,128,128,  0,  0,  0,  1,  1,  1,255,255,255,255,  0,  0,  0,240,240,240,241,241,241,241,  0,  0,  0,128,128,128,240,240,240,240,240,240,240,240,240,240,112,  0,  0,240,240,240,255,255,255,255,248,240,240,240,  0,  0,  0,  0,  0,112,240,240,240,240,240,240,240,128,128,128,  0,  0,  0,
        0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,255,255,255,255, 60, 60, 60, 60, 60, 60, 63,127, 63, 63,  0,  0,128,192,192,192,252, 60, 60, 60, 60, 60,255,255,255,255,187,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  7,  7,  7, 63, 60, 60, 60, 60, 60,124,224,192,192,192,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,192,192,192,232,124, 60, 60, 60, 60, 60,255,255,255,255,  0,  0,  0,
        0,  0,  0,  0,  0,  0, 31, 31, 31, 31,  0,  0,  0,  3,  3,  3, 31, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31,  0,  0,  1,  3,  3, 15, 30, 30, 30, 30, 30, 30, 30,  0,  0,  0,  0,  0,  1,  3,  3,  3, 31, 30, 30, 30, 30, 30, 31, 31, 31, 31, 15,  0,  0,  0,  0,  0, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0, 31, 31, 31, 31,  0,  0,  0, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  3,  3,  3,  1,  0,  0,  0,  0,  0,  1,  3,  3,  3, 30, 30, 30, 30,  0,  0,  1,  3,  3, 11, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
    }
    return false;
}
#endif
