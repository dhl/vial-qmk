/* Copyright 2023 Cyboard LLC (@Cyboard-DigitalTailor)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include QMK_KEYBOARD_H
#include "features/achordion.h"

// HOME ROW MOD
const uint16_t HM_F = LSFT_T(KC_F);
const uint16_t HM_D = LCTL_T(KC_D);
const uint16_t HM_S = LALT_T(KC_S);
const uint16_t HM_A = LGUI_T(KC_A);

const uint16_t HM_J = LSFT_T(KC_J);
const uint16_t HM_K = LCTL_T(KC_K);
const uint16_t HM_L = LALT_T(KC_L);
const uint16_t HM_SCLN = LGUI_T(KC_SCLN);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_fun(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LCTL, KC_A,    HM_S,    HM_D,    HM_F,    KC_G,                              KC_H,    HM_J,    HM_K,    HM_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_LGUI, KC_LALT, KC_SPC,  KC_DEL,  KC_ESC,         KC_GRAVE, KC_BSPC, KC_ENT,  KC_LBRC, KC_RBRC,
                                            KC_LGUI, KC_HOME, KC_END,         KC_CAPS,  KC_BSPC,  MO(1)
    ),

    [1] = LAYOUT_fun(
        QK_BOOT, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                           _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______,
        _______, _______, _______, _______, _______, _______,                           _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
        _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______,
                                            _______, _______, _______,         _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_achordion(keycode, record)) { return false; }

    return true;
}

void matrix_scan_user(void) {
    achordion_task();
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HM_F:
        case HM_J:
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
}

bool achordion_eager_mod(uint8_t mod) {
    switch (mod) {
        case MOD_LSFT:
        case MOD_RSFT:
        case MOD_LCTL:
        case MOD_RCTL:
            return true;  // Eagerly apply Shift and Ctrl mods.

        default:
            return false;
    }
}
