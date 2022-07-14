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
        //Layer info
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:
                oled_write_P(PSTR("QWERTY"), false);
                break;
            case 1:
                oled_write_P(PSTR("Mov   "), false);
                break;
            case 2:
                oled_write_P(PSTR("Sym   "), false);
                break;
            case 3:
                oled_write_P(PSTR("FN    "), false);
                break;
            case 4:
                oled_write_P(PSTR("Meta  "), false);
                break;
            default:
                oled_write_P(PSTR("null  "), false);
        }

        //Caps
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.caps_lock ? PSTR(" CAPS! ") : PSTR("       "), false);

        //Graph
        const float MAX_WPM = 150.0f; //WPM value at the top of the graph window
        const int REFRESH_INTERVAL = 16; //in milliseconds
        const int SCREEN_HEIGHT = 64;
        int timer = 0;
        char wpm_str[5];
        int height = 5;
        int currwpm = get_current_wpm();

        //format current WPM value into a printable string
        itoa(currwpm, wpm_str, 10);
        oled_write_P(PSTR("WPM->"), false);
        oled_write(wpm_str, false);


        //check if it's been long enough before refreshing graph
        if(timer_elapsed(timer) > REFRESH_INTERVAL){
            //Line height
            height = SCREEN_HEIGHT-((currwpm / MAX_WPM) * SCREEN_HEIGHT);
            //paint line
            for(int i = SCREEN_HEIGHT; i >= height; i--){
                oled_write_pixel(1, i, true);
            }
            //move the hole graph one pixel to the left
            oled_pan(false);
            //timer refresh
            timer = timer_read();
        }
    } else {
        static const char PROGMEM raw_logo[] = {
                                               0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                               0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,240,252,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                               0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,254,255,255, 63,  1,  0,  0,  0,192,240,240,240, 16,  0,128,192,224,240,240,112, 48, 16,  0,128,240,240,240,112,112,112,112,112,112,112,112,  0,  0,128,240,240,240,112,112,112,112,240,240,224,224,128,  0,  0,  0,224,240,240,240,112,112,112,112,240,240,224,192,  0,  0,  0,  0,  0,  0,  0,192,224,240,240,240,224,  0,  0,  0,  0,  0,  0,  0,  0,240,240,240,112,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                               0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,255,255,255,255,255,255,126,  0,  0,  0,248,255,255,127,255,254,255,239,135,  3,  1,  0,  0,  0,  0,248,255,255,255, 63, 56, 56, 56, 56, 56, 56,  0,  0,  0,240,255,255,255,127,112,240,248,248,188, 63, 31, 31,  7,  0,192,252,255,255,127, 57, 56, 56, 56,124,255,255,239,135,  0,  0,  0,192,240,252,255,255,207,195,223,255,255,254,192,  0,  0,  0,  0,224,255,255,255, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                               0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,128,192,224,242,255,255,255,255,255,239,207,192,128,144,159,159,159,135,128,128,129,135,143,159,159, 28, 16,  0,  0, 31, 31, 31, 31, 28, 28, 28, 28, 28, 28, 28, 28,  0,  0, 30, 31, 31, 31,  0,  0,  0,  1,  7, 31, 31, 30, 24,  0,  0, 24, 31, 31, 31, 31, 28, 28, 28, 28, 30, 31, 15, 15,  3,  1, 24, 30, 31, 31, 15,  3,  1,  1,  1,  1,  1,  7, 31, 31, 31, 24,  0,  0, 30, 31, 31, 31, 29, 28, 28, 28, 28, 28, 28, 28,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                               0,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3,  3,  3,  7,  7, 15,255,255,255,255, 63, 31, 15, 15,  7,  3,  3,  3,  3,  3,  3,195,227,227, 99, 35,227,227, 35,227,195,195,227,227,227,  3,195,227, 99, 99,227,227,163,163, 35,  3,  3,  3,  3,  3,  3,  3,  3,131,227,227,227,227,  3,227,227,227,227,  3,227,227, 35,227,195,131,227, 99, 99, 99,  3,227,227,227,227,  3,131,227,227,227,  3,131,227,227,195,227,227, 35,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  2,  2,  2,  2,  2,  2,  0,  0,  0,
                                               0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,  7,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12, 13, 15, 15,  0, 15, 15,  3,  3, 12, 15,  7, 15, 15,  8, 15, 15, 12,  8, 15, 15,  9,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 15,  3,  3,  1, 14, 15,  3, 15, 13,  0, 15, 15, 12, 15,  7,  7, 15,  9, 15, 15, 14, 15,  3, 15, 13,  8, 15,  7,  7, 15, 14, 15, 15,  3,  3, 15, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                               0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                               };

        oled_write_raw_P(raw_logo, sizeof(raw_logo));
        //oled_scroll_right();
        //oled_scroll_set_speed(3);
    }
    return false;
}
#endif


#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
          tap_code16(C(KC_Y));
        } else {
          tap_code16(C(KC_Z));
        }
    }
    return true;
}
#endif
