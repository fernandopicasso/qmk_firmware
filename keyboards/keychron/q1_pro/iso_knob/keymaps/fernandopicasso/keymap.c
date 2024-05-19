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
#include <config.h>
// clang-format off
enum layers{
  BASE,
  NAV,
  WIN_BASE,
  WIN_FN
};

// Tap Dance keycodes
enum td_keycodes {
    LSFT_LPRN,    // `LSFT` when held, `(` when tapped.
    RSFT_RPRN,    // `RSFT` when held, `)` when tapped.
    LCTL_LCBR,   // `LCTL` when held, `{` when tapped.
    RCTL_RCBR,   // `RCTL` when held, `}` when tapped.
    LALT_LBRC,  // `LALT` when held, `[` when tapped.
    RALT_RBRC,  // `RALT` when held, `]` when tapped.
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void laltlb_finished(tap_dance_state_t *state, void *user_data);
void laltlb_reset(tap_dance_state_t *state, void *user_data);

//------------------------------------------------------------
// Keymap
//------------------------------------------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_iso_83(
        KC_ESC,          KC_F1,   KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,      KC_F7,    KC_F8,    KC_F9,    KC_F10,       KC_F11,    KC_F12,       KC_DEL,               KC_MUTE,
        FI_SECT,         FI_1,    FI_2,       FI_3,     FI_4,     FI_5,     FI_6,       FI_7,     FI_8,     FI_9,     FI_0,         FI_PLUS,   FI_ACUT,      KC_BSPC,              KC_PGUP,
        KC_TAB,          FI_Q,    FI_W,       FI_E,     FI_R,     FI_T,     FI_Y,       FI_U,     FI_I,     FI_O,     FI_P,         FI_ARNG,   FI_DIAE,      KC_ENT,               KC_PGDN,
        LT(NAV, KC_ESC), FI_A,    FI_S,       FI_D,     FI_F,     FI_G,     FI_H,       FI_J,     FI_K,     FI_L,     FI_ODIA,      FI_ADIA,                 FI_QUOT,              KC_HOME,
        TD(LSFT_LPRN),   FI_LABK, FI_Z,       FI_X,     FI_C,     FI_V,     FI_B,       FI_N,     FI_M,     FI_COMM,  FI_DOT,       FI_MINS,                 TD(RSFT_RPRN), KC_UP,
        TD(LCTL_LCBR),   KC_LGUI, TD(LALT_LBRC),                            KC_SPC,                                   TD(RALT_RBRC),MO(WIN_FN),TD(RCTL_RCBR), KC_LEFT,     KC_DOWN, KC_RGHT),

    [NAV] = LAYOUT_iso_83(
        KC_ESC,          KC_F1,    KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,      KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_DEL,            KC_MUTE,
        XXXXXXX,         XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  KC_BSPC,           KC_PGUP,
        KC_TAB,          XXXXXXX,  C(KC_RGHT), XXXXXXX,  XXXXXXX,  XXXXXXX,  C(KC_C),    C(KC_Z),  XXXXXXX,  XXXXXXX,  C(KC_V),  XXXXXXX,   XXXXXXX,  KC_ENT,            KC_PGDN,
        KC_ESC,          XXXXXXX,  XXXXXXX,    C(KC_X),  XXXXXXX,  XXXXXXX,  KC_LEFT,    KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  XXXXXXX,             XXXXXXX,           KC_HOME,
        KC_LSFT,         XXXXXXX,  XXXXXXX,    KC_DEL,   XXXXXXX,  XXXXXXX,  C(KC_LEFT), XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,             KC_RSFT,  KC_UP,
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

//--------------------------------------------------------------------
// Combos
//--------------------------------------------------------------------
const uint16_t PROGMEM ctxmenu_combo[] = {KC_RALT, KC_RCTL, COMBO_END};
const uint16_t PROGMEM backsp_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_D, KC_F, COMBO_END};

combo_t key_combos[] = {
    COMBO(ctxmenu_combo, KC_APP),
    COMBO(backsp_combo, KC_BSPC),
    COMBO(del_combo, KC_DEL),
};

uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(*key_combos);

//--------------------------------------------------------------------
// Tap dance
//--------------------------------------------------------------------
// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

void lsftlprn_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(FI_LPRN);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `{{` within tapping term
            tap_code16(FI_LPRN);
            register_code16(FI_LPRN);
            break;
        default:
            break;
    }
}

void lsftlprn_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(FI_LPRN);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(FI_LPRN);
            break;
        default:
            break;
    }
}

void rsftrprn_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(FI_RPRN);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RSFT));
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `{{` within tapping term
            tap_code16(FI_RPRN);
            register_code16(FI_RPRN);
            break;
        default:
            break;
    }
}

void rsftrprn_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(FI_RPRN);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RSFT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(FI_RPRN);
            break;
        default:
            break;
    }
}
//FI_LCBR ALGR(FI_7)    // {
void lctllcbr_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(FI_LCBR);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `{{` within tapping term
            tap_code16(FI_LCBR);
            register_code16(FI_LCBR);
            break;
        default:
            break;
    }
}

void lctllcbr_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(FI_LCBR);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(FI_LCBR);
            break;
        default:
            break;
    }
}

void rctlrcbr_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(FI_RCBR);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `{{` within tapping term
            tap_code16(FI_RCBR);
            register_code16(FI_RCBR);
            break;
        default:
            break;
    }
}

void rctlrcbr_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(FI_RCBR);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RCTL));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(FI_RCBR);
            break;
        default:
            break;
    }
}

//FI_LCBR ALGR(FI_7)    // {
//FI_LBRC ALGR(FI_8)    // [
// Handle the possible states for each tapdance keycode you define:

void laltlbrc_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(FI_LBRC);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT));
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(FI_LBRC);
            register_code16(FI_LBRC);
            break;
        default:
            break;
    }
}

void laltlbrc_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(FI_LBRC);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(FI_LBRC);
            break;
        default:
            break;
    }
}

void raltrbrc_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(FI_RBRC);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RALT));
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `))` within tapping term
            tap_code16(FI_RBRC);
            register_code16(FI_RBRC);
            break;
        default:
            break;
    }
}

void raltrbrc_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(FI_RBRC);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RALT));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(FI_RBRC);
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [LSFT_LPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsftlprn_finished, lsftlprn_reset),
    [RSFT_RPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rsftrprn_finished, rsftrprn_reset),

    [LCTL_LCBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lctllcbr_finished, lctllcbr_reset),
    [RCTL_RCBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rctlrcbr_finished, rctlrcbr_reset),

    [LALT_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, laltlbrc_finished, laltlbrc_reset),
    [RALT_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, raltrbrc_finished, raltrbrc_reset)
};
