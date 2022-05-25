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
        static const char PROGMEM idealista_logo[] = {
            0,  0,  0,  0,  0,  0,224,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,224,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,224,224,224,224,224,224,  0,  0,  0,  0,  0,  0,224,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,224,224,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,240,240,240,241,241,241,241,  0,  0,  0,128,128,128,240,240,240,240,240,240,248,255,255,255,255,  0,  0,128,128,128,240,240,240,240,240,240,240,240,128,128,128,  0,  0,  0,  0,  0,  0,240,240,240,240,240,240,240,128,128,128,  0,  0,  0,  1,  1,  1,255,255,255,255,  0,  0,  0,240,240,240,241,241,241,241,  0,  0,  0,128,128,128,240,240,240,240,240,240,240,240,240,240,112,  0,  0,240,240,240,255,255,255,255,248,240,240,240,  0,  0,  0,  0,  0,112,240,240,240,240,240,240,240,128,128,128,  0,  0,  0,
            0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,255,255,255,255, 60, 60, 60, 60, 60, 60, 63,127, 63, 63,  0,  0,128,192,192,192,252, 60, 60, 60, 60, 60,255,255,255,255,187,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  7,  7,  7, 63, 60, 60, 60, 60, 60,124,224,192,192,192,  0,  0,  0,  0,  0,255,255,255,255,  0,  0,  0,  0,  0,  0,192,192,192,232,124, 60, 60, 60, 60, 60,255,255,255,255,  0,  0,  0,
            0,  0,  0,  0,  0,  0, 31, 31, 31, 31,  0,  0,  0,  3,  3,  3, 31, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31,  0,  0,  1,  3,  3, 15, 30, 30, 30, 30, 30, 30, 30,  0,  0,  0,  0,  0,  1,  3,  3,  3, 31, 30, 30, 30, 30, 30, 31, 31, 31, 31, 15,  0,  0,  0,  0,  0, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0, 31, 31, 31, 31,  0,  0,  0, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,  3,  3,  3,  1,  0,  0,  0,  0,  0,  1,  3,  3,  3, 30, 30, 30, 30,  0,  0,  1,  3,  3, 11, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31,  0,  0,  0,
        };
        oled_write_P(PSTR("\n\n"), false);
        oled_write_raw_P(idealista_logo, sizeof(idealista_logo));
    }
    return false;
}
#endif


#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return false;
}
#endif
