/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
#include <keymap_finnish.h>
// clang-format off
enum layers{
  BASE,
  NAV,
  WIN_BASE,
  WIN_FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_iso_83(
        KC_ESC,          KC_F1,   KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,      KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_DEL,            KC_MUTE,
        FI_SECT,         FI_1,    FI_2,       FI_3,     FI_4,     FI_5,     FI_6,       FI_7,     FI_8,     FI_9,     FI_0,     FI_PLUS,   FI_ACUT,  KC_BSPC,           KC_PGUP,
        KC_TAB,          FI_Q,    FI_W,       FI_E,     FI_R,     FI_T,     FI_Y,       FI_U,     FI_I,     FI_O,     FI_P,     FI_ARNG,   FI_DIAE,  KC_ENT,            KC_PGDN,
        LT(NAV, KC_ESC), FI_A,    FI_S,       FI_D,     FI_F,     FI_G,     FI_H,       FI_J,     FI_K,     FI_L,     FI_ODIA,  FI_ADIA,             FI_QUOT,           KC_HOME,
        KC_LSFT,         FI_LABK, FI_Z,       FI_X,     FI_C,     FI_V,     FI_B,       FI_N,     FI_M,     FI_COMM,  FI_DOT,   FI_MINS,             KC_RSFT,  KC_UP,
        KC_LCTL,         KC_LGUI, KC_LALT,                                  KC_SPC,                                   KC_RALT,  MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN, KC_RGHT),

    [NAV] = LAYOUT_iso_83(
        KC_ESC,          KC_F1,    KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,      KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_DEL,            KC_MUTE,
        XXXXXXX,         XXXXXXX,  FI_AT,      XXXXXXX,  FI_DLR,   XXXXXXX,  XXXXXXX,    FI_LCBR,  FI_LBRC,  FI_RBRC,  FI_RCBR,  FI_BSLS,   XXXXXXX,  KC_BSPC,           KC_PGUP,
        KC_TAB,          XXXXXXX,  C(KC_RGHT), XXXXXXX,  XXXXXXX,  XXXXXXX,  C(KC_C),    C(KC_Z),  XXXXXXX,  XXXXXXX,  C(KC_V),  XXXXXXX,   FI_TILD,  KC_ENT,            KC_PGDN,
        KC_ESC,          XXXXXXX,  XXXXXXX,    C(KC_X),  XXXXXXX,  XXXXXXX,  KC_LEFT,    KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  XXXXXXX,             XXXXXXX,           KC_HOME,
        KC_LSFT,         FI_PIPE,  XXXXXXX,    KC_DEL,   XXXXXXX,  XXXXXXX,  C(KC_LEFT), XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,             KC_RSFT,  KC_UP,
        KC_LCTL,         KC_LGUI,  KC_LALT,                                  XXXXXXX,                                  KC_RALT,  MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN, KC_RGHT),

    [WIN_BASE] = LAYOUT_iso_83(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,             KC_MUTE,
        FI_SECT,  FI_1,     FI_2,     FI_3,     FI_4,     FI_5,     FI_6,     FI_7,     FI_8,     FI_9,     FI_0,     FI_PLUS,  FI_ACUT,  KC_BSPC,            KC_PGUP,
        KC_TAB,   FI_Q,     FI_W,     FI_E,     FI_R,     FI_T,     FI_Y,     FI_U,     FI_I,     FI_O,     FI_P,     FI_ARNG,  FI_DIAE,  KC_ENT,             KC_PGDN,
        KC_ESC,   FI_A,     FI_S,     FI_D,     FI_F,     FI_G,     FI_H,     FI_J,     FI_K,     FI_L,     FI_ODIA,  FI_ADIA,            FI_QUOT,            KC_HOME,
        KC_LSFT,  FI_LABK,  FI_Z,     FI_X,     FI_C,     FI_V,     FI_B,     FI_N,     FI_M,     FI_COMM,  FI_DOT,   FI_MINS,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_iso_83(
        KC_TRNS,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,            RGB_TOG,
        KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_END,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [NAV] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)}
};
#endif // ENCODER_MAP_ENABLE

// Combos
const uint16_t PROGMEM ctxmenu_combo[] = {KC_RALT, KC_RCTL, COMBO_END};
const uint16_t PROGMEM backsp_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM at_combo[] = {FI_1, FI_2, COMBO_END};
const uint16_t PROGMEM dlr_combo[] = {FI_3, FI_4, COMBO_END};
const uint16_t PROGMEM bsls_combo[] = {FI_PLUS, FI_ACUT, COMBO_END};
const uint16_t PROGMEM tild_combo[] = {FI_ARNG, FI_DIAE, COMBO_END};
const uint16_t PROGMEM pipe_combo[] = {FI_LABK, FI_Z, COMBO_END};
const uint16_t PROGMEM lcbr_combo[] = {FI_6, FI_7, COMBO_END};
const uint16_t PROGMEM lbrc_combo[] = {FI_7, FI_8, COMBO_END};
const uint16_t PROGMEM rbrc_combo[] = {FI_9, FI_0, COMBO_END};
const uint16_t PROGMEM rcbr_combo[] = {FI_0, FI_PLUS, COMBO_END};

combo_t key_combos[] = {
    COMBO(ctxmenu_combo, KC_APP),
    COMBO(backsp_combo, KC_BSPC),
    COMBO(del_combo, KC_DEL),
    COMBO(at_combo, FI_AT),
    COMBO(dlr_combo, FI_DLR),
    COMBO(bsls_combo, FI_BSLS),
    COMBO(tild_combo, FI_TILD),
    COMBO(pipe_combo, FI_PIPE),
    COMBO(lcbr_combo, FI_LCBR),
    COMBO(rcbr_combo, FI_RCBR),
    COMBO(lbrc_combo, FI_LBRC),
    COMBO(rbrc_combo, FI_RBRC),
};

uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(*key_combos);
