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
        oled_write_P(PSTR("Kyria de Alex\n\n"), false);
        // Host Keyboard Layer Status
        oled_write_P(PSTR("Capa -> "), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:
                oled_write_P(PSTR("QWERTY\n"), false);
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
                oled_write_P(PSTR("Desconocida\n"), false);
        }

        //oled_write_P(PSTR("\n\n"), false);

        //char wpm_str[100];
        int wpm = get_current_wpm();
        char wpm_str[3];
        itoa(wpm, wpm_str, 10   );

        oled_write_P(PSTR("\nWPM -> "), false);
        oled_write(wpm_str, false);

        // Host Keyboard LED Status
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.caps_lock ? PSTR("\nCAPS!!!\n\n") : PSTR("\n       \n\n"), false);
    } else {
        static const char PROGMEM raw_logo[] = {
            0,  0,  0,  0,  0,  0,224,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,224,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,224,224,224,224,224,224,  0,  0,  0,  0,  0,  0,224,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,240,240,240,241,241,241,241,  0,  0,  0,128,128,128,240,240,240,240,240,240,248,255,255,255,255,  0,  0,128,128,128,240,240,240,240,240,240,240,240,128,128,128,  0,  0,  0,  0,  0,  0,240,240,240,240,240,240,240,128,128,128,  0,  0,  0,  1,  1,  1,255,255,255,255,  0,  0,  0,240,240,240,241,241,241,241,  0,  0,  0,128,128,128,240,240,240,240,240,240,240,240,240,240,112,  0,  0,240,240,240,255,255,255,255,248,240,240,240,  0,  0,  0,  0,  0,112,240,240,240,240,240,240,240,128,128,128,  0,  0,  0,
            0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,255,255,255,255, 60, 60, 60, 60, 60, 60, 63,127, 63, 63,  0,  0,128,192,192,192,252, 60, 60, 60, 60, 60,255,255,255,255,187,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  7,  7,  7, 63, 60, 60, 60, 60, 60,124,224,192,192,192,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,192,192,192,232,124, 60, 60, 60, 60, 60,255,255,255,255,  0,  0,  0,
            0,  0,  0,  0,  0,  0, 31, 31, 31, 31,  0,  0,  0,  3,  3,  3, 31, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31,  0,  0,  1,  3,  3, 15, 30, 30, 30, 30, 30, 30, 30,  0,  0,  0,  0,  0,  1,  3,  3,  3, 31, 30, 30, 30, 30, 30, 31, 31, 31, 31, 15,  0,  0,  0,  0,  0, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0, 31, 31, 31, 31,  0,  0,  0, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  3,  3,  3,  1,  0,  0,  0,  0,  0,  1,  3,  3,  3, 30, 30, 30, 30,  0,  0,  1,  3,  3, 11, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31,  0,  0,  0,
        };
        oled_write_P(PSTR("\n\n"), false);
        oled_write_raw_P(raw_logo, sizeof(raw_logo));
    }
    return false;
}
#endif
