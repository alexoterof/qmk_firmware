/*
Copyright 2022 Thomas Baart <thomas@splitkb.com>

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

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID    0x8D1D
#define PRODUCT_ID   0x9D9D
#define DEVICE_VER   0x0002
#define MANUFACTURER splitkb
#define PRODUCT      Kyria rev2

/* key matrix size */
/* Rows are doubled up */
#define MATRIX_ROWS  8
#define MATRIX_COLS  8

// wiring
#define MATRIX_ROW_PINS { F6, F7, B1, B3 }
#define MATRIX_COL_PINS { B2, B6, B5, B4, E6, D7, C6, D4 }
#define MATRIX_ROW_PINS_RIGHT { D4, C6, D7, E6 }
#define MATRIX_COL_PINS_RIGHT { B4, B5, B6, B2, B3, B1, F7, F6 }
#define UNUSED_PINS

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }
#define ENCODERS_PAD_A_RIGHT { F5 }
#define ENCODERS_PAD_B_RIGHT { F4 }

#define ENCODER_RESOLUTIONS { 2, 1 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

// Side detection
// col 4 row 3 on right-hand-side
#define SPLIT_HAND_MATRIX_GRID E6, B3 // row first because the board is col2row
#define SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT
#define MATRIX_MASKED // actual mask is defined by `matrix_mask` in `rev2.c`

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE        5

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */


#    define RGB_DI_PIN D3
#    define SOFT_SERIAL_PIN D2

#define RGBLED_SPLIT \
    { 10, 10 }
#define RGBLED_NUM 20

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define SPLIT_OLED_ENABLE
#endif

/* RGB matrix support */
#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#    define DRIVER_LED_TOTAL RGBLED_NUM // Number of LEDs
#    define RGB_MATRIX_SPLIT { 10, 10 }
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 170
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif

//Fix pcb
#define SPLIT_USB_DETECT
