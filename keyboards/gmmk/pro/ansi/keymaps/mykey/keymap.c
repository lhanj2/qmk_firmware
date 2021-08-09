/* 20210806 HJLee - macro, mapping, knob layer added. 
   20210807 HJLee - knob function changed(brightness)
   20210808 HJLee - RGB works with RGB_TOG
   20210809 HJLee - (macro not working)
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


/******If use Via, should reset EEPROM(because enabling via saves your keymap to your EEPROM)*****/
// EEPROM RESET : Plug cable with pressing ESC
#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"

#define ARRAYSIZE(arr)  sizeof(arr)/sizeof(arr[0])

enum custom_layers {
    _BASE,
    _FN1,
    _MO2,
    _MO3,
};

enum nob_layers {
    _WHEEL,
    _MUSIC,
    _VOLUME
};
enum nob_layers nob_layer_state = _WHEEL;

enum custom_keycodes {
    NOB_LAYER_INC = SAFE_RANGE,
    KC_00,
    KC_WINLCK,  // Toggles Win key on and off
    RGB_TOI,    // Timeout idle time up
    RGB_TOD,    // Timeout idle time down
    MY_KNOBFNKEY,
    MY_SLEEP,
};

// Tap Dance Definitions
enum custom_tapdance {
    TD_LSFT_CAPSLOCK,
    TD_WIN,
};

qk_tap_dance_action_t tap_dance_actions[] = {//NOT SUPPORT USER CUSTOM KEY!!!
  // Tap once for shift, twice for Caps Lock
  [TD_LSFT_CAPSLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  // Tap once for Win, twice for File Explorer
  [TD_WIN]           = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_E)),
};

#define KC_LSFTCAPS TD(TD_LSFT_CAPSLOCK)
#define KC_LGUI TD(TD_WIN)

bool _isWinKeyDisabled = false;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Ins           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MPLY,          NOB_LAYER_INC,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PSCR,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN1),C(KC_RGUI), KC_LEFT, KC_DOWN, KC_RGHT
    ),//set RGUI to move virtual desktop because LGUI used to doubletap 

    [_FN1] = LAYOUT(
        MY_SLEEP, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, KC_CALC,          _______,
        _______, DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_TOG,
        _______, _______, RGB_VAI, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______, _______, RESET,            KC_HOME,
        TT(_MO2), _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          KC_END,
        _______,          _______, RGB_HUI, _______, _______, _______, KC_NLCK, _______, RGB_TOD, RGB_TOI, _______,          _______, RGB_MOD, _______,
        _______, KC_WINLCK, _______,                            _______,                          _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),

    [_MO2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, _______,          _______,
        _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, KC_TAB,  KC_P4,   KC_P5,   KC_P6,   KC_PDOT, _______, _______, _______,          KC_HOME,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_NO,   KC_PAST,          KC_PENT,          KC_END,
        _______,          KC_NO,   KC_DEL,  KC_INS,  KC_NO,   KC_NO,   KC_NO,   KC_P0, KC_00, KC_PDOT, KC_PSLS,         _______, RCTL(KC_PGUP), _______,
        _______, _______, _______,                            KC_BSPC,                            _______, _______, _______, RCTL(KC_LEFT), RCTL(KC_PGDN), RCTL(KC_RIGHT)
    ),

   [_MO3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

};


// TIMEOUTS
#define TIMEOUT_THRESHOLD_DEFAULT   5    // default timeout minutes
#define TIMEOUT_THRESHOLD_MAX       140  // upper limits (2 hours and 10 minutes -- no rgb indicators above this value)
static uint16_t timeout_timer = 0;
static uint16_t timeout_counter = 0;  //in minute intervals
static uint16_t timeout_threshold = TIMEOUT_THRESHOLD_DEFAULT;
static bool     Shift_Pressed = false;  // for knob custom 210807
static bool     RGB_TOGGLED = false;

void timeout_reset_timer(void) {
    timeout_timer = timer_read();
    timeout_counter = 0;
};

void timeout_update_threshold(bool increase) {
    if (increase && timeout_threshold < TIMEOUT_THRESHOLD_MAX) timeout_threshold++;
    if (!increase && timeout_threshold > 0) timeout_threshold--;
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //All of keycodes need return true or false (meaning of send origin keycode after action)
    switch (keycode) {
    case KC_00:
        if (record->event.pressed) {
            // when keycode KC_00 is pressed
            SEND_STRING("00");
        } else {
            // when keycode KC_00 is released
        }
        return false;
    case KC_WINLCK:
        if (record->event.pressed) {
            _isWinKeyDisabled = !_isWinKeyDisabled; //toggle status
            if(_isWinKeyDisabled) {
                process_magic(GUI_OFF, record);
            } else {
                process_magic(GUI_ON, record);
            }
        } else  unregister_code16(keycode);
        return false;
    case RGB_TOI:
        if(record->event.pressed) {
            timeout_update_threshold(true);
        } else  unregister_code16(keycode);
        return false;
    case RGB_TOD:
        if(record->event.pressed) {
             timeout_update_threshold(false);  //decrease timeout
        } else  unregister_code16(keycode);
        return false;
    case NOB_LAYER_INC://SHIFT KNOB
        if ((record->event.pressed) && (Shift_Pressed == false)) {
            nob_layer_state++;
        } else if ((record->event.pressed) && (Shift_Pressed == true)) {
            tap_code(KC_MUTE);
        }
        //If want to use Knob Layer 3, change 2 to 3
        if (nob_layer_state == 2) nob_layer_state = 0;
        return false;
    case KC_RSFT:  // FOR RSFT KNOB VOLUME
        record->event.pressed ? (Shift_Pressed = true) : (Shift_Pressed = false);
        return true;
    case KC_LSFT:  // FOR LSFT KNOB VOLUME
        record->event.pressed ? (Shift_Pressed = true) : (Shift_Pressed = false);
        return true;
    case MY_KNOBFNKEY:  // 210809 test
        if (record->event.pressed) {
            tap_code(KC_PSCR);
            printf("CALC");
        } else {
            (Shift_Pressed = false);
            printf("CALC");
        }
        return false;
        //break;
    case MY_SLEEP:
        if (record->event.pressed) tap_code(KC_SLEP);
        return false;
    case RGB_TOG:
        if (record->event.pressed && !RGB_TOGGLED) {  // reset activity timer
            #ifdef RGB_MATRIX_ENABLE //if rgb enabled
            rgb_matrix_enable();
            RGB_TOGGLED = true;
            #endif
            timeout_reset_timer();
        } else if (record->event.pressed && RGB_TOGGLED) {
            #ifdef RGB_MATRIX_ENABLE //if rgb enabled
            rgb_matrix_disable_noeeprom();
            RGB_TOGGLED = false;
            #endif
            timeout_reset_timer();
        }
        return false;
    default:
        return true;
    }
};

void matrix_scan_user(void) {
    //if (timeout_threshold > 0) {
    //    if (timer_elapsed(timeout_timer) >= 60000) { // 1 minute tick
    //        timeout_counter++;
    //        timeout_timer = timer_read();
    //    }
    //    #ifdef RGB_MATRIX_ENABLE
    //        if (timeout_threshold > 0 && timeout_counter >= timeout_threshold) {
    //            rgb_matrix_disable_noeeprom();
    //        }
    //    #endif
    //} // timeout_threshold = 0 will disable timeout
};


#ifdef ENCODER_ENABLE       // Encoder Function
    bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (nob_layer_state) {
        case _WHEEL:
            if (clockwise && Shift_Pressed)                 tap_code(KC_VOLU);
            else if (!clockwise && Shift_Pressed)         tap_code(KC_VOLD);
            else if (clockwise && !Shift_Pressed)           tap_code(KC_WH_D);
            else if (!clockwise && !Shift_Pressed)        tap_code(KC_WH_U);
            break;
        case _MUSIC:
            if (clockwise && Shift_Pressed)                 tap_code(KC_VOLU);
            else if (!clockwise && Shift_Pressed)         tap_code(KC_VOLD);
            else if (clockwise && !Shift_Pressed)           tap_code16(KC_MNXT);
            else if (!clockwise && !Shift_Pressed)        tap_code16(KC_MPRV);
            break;
        case _VOLUME:  // 210807 not use
            clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
            break;
    }
    return true;
}
#endif

#ifdef RGB_MATRIX_ENABLE
    // Capslock, Scroll lock and Numlock  indicator on Left side lights.
    void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
        if (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) {
            rgb_matrix_set_color(LED_L1, RGB_GREEN);
            rgb_matrix_set_color(LED_L2, RGB_GREEN);
        }
        if (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) {   // Num Lock indicator
            rgb_matrix_set_color(LED_L3, RGB_MAGENTA);
            rgb_matrix_set_color(LED_L4, RGB_MAGENTA);
        }
        if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
            rgb_matrix_set_color(LED_L5, RGB_RED);
            rgb_matrix_set_color(LED_L6, RGB_RED);
            rgb_matrix_set_color(LED_L7, RGB_RED);
        }
        if (_isWinKeyDisabled) {
            rgb_matrix_set_color(LED_LWIN, RGB_RED);  //light up Win key when disabled
        }
        switch(get_highest_layer(layer_state)){  // special handling per layer
        case _FN1:  // on Fn layer select what the encoder does when pressed
            rgb_matrix_set_color(LED_R2, RGB_RED);
            rgb_matrix_set_color(LED_R3, RGB_RED);
            rgb_matrix_set_color(LED_R4, RGB_RED);
            rgb_matrix_set_color(LED_FN, RGB_RED); //FN key

            // Add RGB Timeout Indicator -- shows 0 to 139 using F row and num row;  larger numbers using 16bit code
            if (timeout_threshold <= 10) rgb_matrix_set_color(LED_LIST_FUNCROW[timeout_threshold], RGB_RED);
            else if (timeout_threshold < 140) {
                rgb_matrix_set_color(LED_LIST_FUNCROW[(timeout_threshold / 10)], RGB_RED);
                rgb_matrix_set_color(LED_LIST_NUMROW[(timeout_threshold % 10)], RGB_RED);
            } else { // >= 140 minutes, just show these 3 lights
                rgb_matrix_set_color(LED_LIST_NUMROW[10], RGB_RED);
                rgb_matrix_set_color(LED_LIST_NUMROW[11], RGB_RED);
                rgb_matrix_set_color(LED_LIST_NUMROW[12], RGB_RED);
            }
            break;
        case _MO2:
            for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_NUMPAD); i++) {
                rgb_matrix_set_color(LED_LIST_NUMPAD[i], RGB_MAGENTA);
            }
            rgb_matrix_set_color(LED_R4, RGB_MAGENTA);
            rgb_matrix_set_color(LED_R5, RGB_MAGENTA);
            rgb_matrix_set_color(LED_R6, RGB_MAGENTA);
            break;
        case _MO3:
            rgb_matrix_set_color(LED_R6, RGB_GREEN);
            rgb_matrix_set_color(LED_R7, RGB_GREEN);
            rgb_matrix_set_color(LED_R8, RGB_GREEN);
            break;
        default:
            break;
        }
    }
    //LED SLEEP 210809 remarked
    //void suspend_power_down_user(void) {
    //    rgb_matrix_set_suspend_state(true);
    //}

    //void suspend_wakeup_init_user(void) {
    //    rgb_matrix_set_suspend_state(false);
    //}
#endif


void keyboard_post_init_user(void) {

    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) { // turn on Num lock by default so that the numpad layer always has predictable results
        tap_code(KC_NUMLOCK);
    }
    timeout_timer = timer_read(); // set inital time for ide timeout
    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_set_color_all(RGB_NAUTILUS); // Default startup colour
    #endif
}
