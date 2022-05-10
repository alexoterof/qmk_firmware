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
#include <unistd.h>

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
        // Host Keyboard LED Status
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.caps_lock ? PSTR("\nCAPS!!!\n\n") : PSTR("\n       \n\n"), false);
    } else {
        int timer = 0;
        char wpm_text[5];
        int x = 31;
        int currwpm = 0;

        //USER CONFIG PARAMS
        float max_wpm = 110.0f; //WPM value at the top of the graph window
        int graph_refresh_interval = 80; //in milliseconds
        int graph_area_fill_interval = 3; //determines how dense the lines under the graph line are; lower = more dense
        //get current WPM value
        currwpm = get_current_wpm();
    
        //check if it's been long enough before refreshing graph
        if(timer_elapsed(timer) > graph_refresh_interval){

            // main calculation to plot graph line
            x = 32 - ((currwpm / max_wpm) * 32);

            //first draw actual value line
            oled_write_pixel(1, x, true);

            //then fill in area below the value line
            for(int i = 32; i > x; i--){
                if(i % graph_area_fill_interval == 0){
                    oled_write_pixel(1, i, true);
                }
            }

            //then move the entire graph one pixel to the right
            oled_pan(false);

            //refresh the timer for the next iteration
            timer = timer_read();

        }

        //format current WPM value into a printable string
        sprintf(wpm_text,"%i", currwpm);

        //formatting for triple digit WPM vs double digits, then print WPM readout
        if(currwpm >= 100){
            oled_set_cursor(14, 3);
            oled_write("WPM: ", false);
            oled_set_cursor(18, 3);
            oled_write(wpm_text, false);
        } else if (currwpm >= 10){
            oled_set_cursor(15, 3);
            oled_write("WPM: ", false);
            oled_set_cursor(19, 3);
            oled_write(wpm_text, false);
        } else if (currwpm > 0) {
            oled_set_cursor(16, 3);
            oled_write("WPM: ", false);
            oled_set_cursor(20, 3);
            oled_write(wpm_text, false);
        }
    }
    return false;
}
#endif
