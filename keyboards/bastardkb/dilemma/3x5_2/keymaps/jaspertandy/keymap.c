/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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
#include "transactions.h"
#include <string.h>

#ifdef OLED_ENABLE
#include "oled_driver.h"

void oled_pan_section(bool left, uint16_t y_start, uint16_t y_end,
                      uint16_t x_start, uint16_t x_end);

#ifndef OLED_WPM_GRAPH_MAX_WPM
#define OLED_WPM_GRAPH_MAX_WPM 120
#endif
#ifndef OLED_WPM_GRAPH_REFRESH_INTERVAL
#define OLED_WPM_GRAPH_REFRESH_INTERVAL 300
#endif
#ifndef OLED_WPM_GRAPH_AREA_FILL_INTERVAL
#define OLED_WPM_GRAPH_AREA_FILL_INTERVAL 3
#endif
#ifndef OLED_WPM_GRAPH_VERTCAL_LINE_INTERVAL
#define OLED_WPM_GRAPH_VERTCAL_LINE_INTERVAL 3
#endif
#ifndef OLED_WPM_GRAPH_GRAPH_LINE_THICKNESS
#define OLED_WPM_GRAPH_GRAPH_LINE_THICKNESS 2
#endif

#define OLED_RENDER_WPM_COUNTER "WPM: "

#define OLED_ANIM_SIZE 36
#define OLED_ANIM_ROWS 4
#define OLED_ANIM_MAX_FRAMES 3

#define OLED_SLEEP_FRAMES 2
#define OLED_SLEEP_SPEED 10 // below this wpm value your animation will idle

#define OLED_WAKE_FRAMES 2               // uncomment if >1
#define OLED_WAKE_SPEED OLED_SLEEP_SPEED // below this wpm value your animation will idle

#define OLED_KAKI_FRAMES 3
#define OLED_KAKI_SPEED 40 // above this wpm value typing animation to triggere

#define OLED_RTOGI_FRAMES 2

deferred_token kittoken;

#endif // ends OLED_ENABLE

#define LTL4 LT(3, KC_Z)
#define LTL3 MT(MOD_LSFT, KC_ESC)
#define LTL2 LT(2, KC_SPC)
#define LTL1 LT(1, KC_X)

#define LTR1 LT(4, KC_ENT)
#define LTR2 LT(5, KC_BSPC)
#define LTR3 LT(6, KC_DOT)
#define LTR4 LT(7, KC_SLSH)

#define A_MT MT(MOD_LCTL, KC_A)
#define S_MT MT(MOD_LALT, KC_S)
#define D_MT MT(MOD_LGUI, KC_D)
#define F_MT MT(MOD_LSFT, KC_F)
#define J_MT MT(MOD_RSFT, KC_J)
#define K_MT MT(MOD_RGUI, KC_K)
#define L_MT MT(MOD_RALT, KC_L)
#define C5_MT MT(MOD_RCTL, KC_QUOT)

enum userspace_keycodes {
    TMUXPN = SAFE_RANGE,
    TMUXPP,
    VIM_VP,
    VIM_VR,
    VIM_QN,
    VIM_QP,
};

const uint16_t PROGMEM combo_tab[] = {KC_D, KC_F, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_tab, KC_TAB)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_split_3x5_2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                  KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      A_MT,    S_MT,    D_MT,    F_MT,    KC_G,                                   KC_H,    J_MT,    K_MT,    L_MT,   C5_MT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LTL4,    LTL1,    KC_C,   KC_V,    KC_B,                                    KC_N,    KC_M,   KC_COMM, LTR3,    LTR4,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          LTL3,     LTL2,                LTR1,    LTR2
                                      //`--------------------------'  `-----------------'

  ),

  [1] = LAYOUT_split_3x5_2( // MEDIA
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______,                               _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                               KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,                               _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,                      KC_MPLY, KC_MUTE
                                      //`--------------------------'  `--------------------------'
  //    *
  ),

  [2] = LAYOUT_split_3x5_2( // NAV
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______,                               CW_TOGG, KC_CAPS, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                               KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_COLON,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,                               KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,                      KC_TAB, _______
                                      //`--------------------------'  `--------------------------'
                                      //              *
  ),

  [3] = LAYOUT_split_3x5_2( // MOUSE
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______,                               _______, _______, _______,DPI_RMOD, DPI_MOD,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                               LCTL(KC_LEFT), _______, _______, LCTL(KC_RIGHT), _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, SNIPING, DRGSCRL,                               _______, _______, _______,S_D_RMOD, S_D_MOD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_BTN1, KC_BTN2,                       KC_BTN1, KC_BTN2
                                      //`--------------------------'  `--------------------------'
                                      //                       *
  ),

  [4] = LAYOUT_split_3x5_2( // SYM
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_EXLM,                               _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LBRC, KC_RBRC, KC_DLR,   KC_BSLS, KC_PIPE,                               _______, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LT,   KC_PERC, KC_EQL,  KC_GT,   LALT(KC_3),                            _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_MINS, KC_SPC,                      _______, _______
                                      //`--------------------------'  `--------------------------'
                                      //                                   *
  ),

  [5] = LAYOUT_split_3x5_2( // NUM
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ASTR, KC_7,    KC_8,    KC_9,    KC_PLUS,                               _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_SLSH, KC_4,    KC_5,    KC_6,    KC_MINS,                               _______, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_UNDS,                               _______, KC_EQL, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_0,    KC_SPC,                      _______, _______
                                      //`--------------------------'  `--------------------------'
                                      //                                            *
  ),

  [6] = LAYOUT_split_3x5_2( // FUN
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_F12,  KC_F7,   KC_F8,   KC_F9,   _______,                               QK_BOOT, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_F11,  KC_F4,   KC_F5,   KC_F6,   _______,                               _______, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_F10,  KC_F1,   KC_F2,   KC_F3,   _______,                               _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,                       _______, _______
                                      //`--------------------------'  `--------------------------'
                                      //                                                     *
  ),

  [7] = LAYOUT_split_3x5_2( // BUTTON
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      LAG(KC_BSLS), LCTL(KC_SPC), LCA(KC_SPC), _______, _______,                 _______, _______, _______, _______, _______,           // 1Password, Things, Fantastical
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      VIM_QP, VIM_QN, _______, VIM_VP,  TMUXPP,                                  LSG(KC_1), LSG(KC_2), LSG(KC_3), LSG(KC_4),  _______,  // Screenshots
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, VIM_VR,  TMUXPN,                                  LSG(KC_5), _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,                       _______, _______                   // *
                                      //`--------------------------'  `--------------------------'
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TMUXPN:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("b")"o");
      }
      return false;
      break;
    case TMUXPP:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("b")"p");
      }
      return false;
      break;
    case VIM_VP:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESCAPE)"\\vp");
      }
      return false;
      break;
    case VIM_VR:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESCAPE)"\\r");
      }
      return false;
      break;
    case VIM_QN:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESCAPE)")"SS_DELAY(50)"q"SS_TAP(X_ESCAPE));
      }
      return false;
      break;
    case VIM_QP:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESCAPE)"("SS_DELAY(50)"q"SS_TAP(X_ESCAPE));
      }
      return false;
      break;
  }
  return true;
}

#ifdef OLED_ENABLE

static uint8_t animation_frame = 0;
static uint8_t animation_type  = 0;

uint32_t kitty_animation_phases(uint32_t triger_time, void *cb_arg) {
    static uint32_t anim_frame_duration = 500;
    {
#ifdef WPM_ENABLE
        if (get_current_wpm() <= OLED_SLEEP_SPEED) {
#endif
            animation_frame     = (animation_frame + 1) % OLED_SLEEP_FRAMES;
            animation_type      = 0;
            anim_frame_duration = 500;
#ifdef WPM_ENABLE
        } else if (get_current_wpm() > OLED_WAKE_SPEED) {
            animation_frame     = (animation_frame + 1) % OLED_WAKE_FRAMES;
            animation_type      = 1;
            anim_frame_duration = 800;
        } else if (get_current_wpm() >= OLED_KAKI_SPEED) {
            animation_frame     = (animation_frame + 1) % OLED_KAKI_FRAMES;
            animation_type      = 2;
            anim_frame_duration = 500;
        }
#endif
    }
    return anim_frame_duration;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    kittoken = defer_exec(3000, kitty_animation_phases, NULL);

    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240, 24, 12,  4,  6,  4, 12, 24,240,192,192,112, 16, 24, 12,  4,  4,  6,  6,  6,  4,  4,  4, 12, 24, 16,112,192,128,  0,128,224, 48, 24,  8, 12,  4,  6,  6,  2,  2,  6,  6,  4, 12, 12, 24, 48,224,  0,224,248, 12,  4,  4,  6,  6,  6,  6,  6,  6,  6,  4,  4,  4, 12, 24, 16,112,192,224,248, 12,  4,  4,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  4, 12,152,240,224,248, 12,  4,  4,  6,  6,  6,  6,  6,  6,  6,  6,  4,  4, 12, 12, 24, 48,224,128,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0,  0,  0,  0,255,255,  0,  0,  0,  0,  0,  0,  0, 24, 28, 28, 24,  0,  0,  0,  0,  0,  0,  0,255,252,127,240,192,128,  0,  0,  0,  0,  0,  4,  4,  4,  0,  0,  0, 16, 56,124,255, 63,255,255,  0,  0,  0,  0,  0,  0,  0, 28, 28, 28, 24,  0,  0,  0,  0,  0,  0,227,255,255,  0,  0,  0,  0,  0,  0,  0,  4,  4,  4,  4,  4, 12, 12, 60,254, 63, 31,255,255,  0,  0,  0,  0,  0,  0,  0, 28, 28, 28, 28, 24,  0,  0,  0,  0,  0,  0,255,254,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,224,240, 24, 12, 12,  6,  7,  0,  0,  0,  0,  0,192,240,255,255,  0,  0,  0,  0,  0,  0,128,224,224,224,224,128,  0,  0,  0,  0,  0,  0,255,255,254,131,  3,  1,  1,  0,  0,  4, 12,  8,  8,  0,  0,  0,  0,  0,  0,128,225,255,255,255,  0,  0,  0,  0,  0,  0,128,224,224,224,240,240,240,240,248,124, 63, 31,255,255,  0,  0,  0,  0,  0,  0,  0, 12, 12, 12, 12, 12, 12, 14, 15, 31, 63,224,255,255,  0,  0,  0,  0,  0,  0,128,240,224,224,128,  0,  0,  0,  0,  0,  4, 15, 63,231,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  1, 31, 60,124,120,120,124,124,124, 62, 62, 31, 15,  7,  3, 31, 62,124,120,120,124,124, 63, 31,  7,  1,  3, 31, 60,124,120,120,124,126, 63, 31,  7, 15, 31, 62, 60,124,120,120,248,248,248,248,120,124,124, 62, 63, 31, 15,  7,  1, 31, 62,124,120,120,124,124, 63, 31,  3,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1, 31, 62,124,120,120,120,120,120,120,120,120,120,120,120,120,124,124, 63, 31,  7, 31, 62,124,120,120,124,124, 63, 31,  3,  3,  7, 31, 62,124,120,120,124,124, 63, 31,  7,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
    oled_set_cursor(0, 5);
}

//=============  USER CONFIG PARAMS  ===============
// wpm graph originally designed by john-ezra

// for 128x128:
// max_lines_graph          = 54;
// vertical_offset          = 64;
// for 128x64:
// max_lines_graph          = 64;
// vertical_offset          = 0;

void render_wpm_graph(uint8_t max_lines_graph, uint8_t vertical_offset) {
#ifdef WPM_ENABLE
    static uint16_t timer   = 0;
    static uint8_t  x       = OLED_DISPLAY_HEIGHT - 1;
    uint8_t         currwpm = get_current_wpm();
    float           max_wpm = OLED_WPM_GRAPH_MAX_WPM;

    if (timer_elapsed(timer) > OLED_WPM_GRAPH_REFRESH_INTERVAL) {                  // check if it's been long enough before refreshing graph
        x = (max_lines_graph - 1) - ((currwpm / max_wpm) * (max_lines_graph - 1)); // main calculation to plot graph line
        for (uint8_t i = 0; i <= OLED_WPM_GRAPH_GRAPH_LINE_THICKNESS - 1; i++) {   // first draw actual value line
            oled_write_pixel(3, x + i + vertical_offset, true);
        }
#    ifdef OLED_WPM_GRAPH_VERTICAL_LINE
        static uint8_t vert_count = 0;
        if (vert_count == OLED_WPM_GRAPH_VERTCAL_LINE_INTERVAL) {
            vert_count = 0;
            while (x <= (max_lines_graph - 1)) {
                oled_write_pixel(3, x + vertical_offset, true);
                x++;
            }
        } else {
            for (uint8_t i = (max_lines_graph - 1); i > x; i--) {
                if (i % OLED_WPM_GRAPH_AREA_FILL_INTERVAL == 0) {
                    oled_write_pixel(3, i + vertical_offset, true);
                }
            }
            vert_count++;
        }
#    else
        for (int i = (max_lines_graph - 1); i > x; i--) {
            if (i % OLED_WPM_GRAPH_AREA_FILL_INTERVAL == 0) {
                oled_write_pixel(3, i + vertical_offset, true);
            }
        }
#    endif
#    include <math.h>
        uint8_t y_start  = ceil(vertical_offset / 8);
        uint8_t y_length = y_start + ceil(max_lines_graph / 8);
        oled_pan_section(false, y_start, y_length, 3, 125); // then move the entire graph one pixel to the right
        timer = timer_read();                               // refresh the timer for the next iteration
    }
#endif
}

static void render_wpm(uint8_t padding, uint8_t col, uint8_t line) {
#ifdef WPM_ENABLE
  oled_set_cursor(col, line);
  oled_write_P(PSTR(OLED_RENDER_WPM_COUNTER), false);
  if (padding) {
    for (uint8_t n = padding; n > 0; n--) {
      oled_write_P(PSTR(" "), false);
    }
  }
  oled_write(get_u8_str(get_current_wpm(), ' '), false);
#endif
}

void render_kitty(uint8_t col, uint8_t line) {
    // Images credit j-inc(/James Incandenza) and pixelbenny.
    // Credit to obosob for initial animation approach.
    // heavily modified by drashna because he's a glutton for punishment

    // clang-format off
    static const char PROGMEM animation[4][OLED_ANIM_MAX_FRAMES][OLED_ANIM_ROWS][OLED_ANIM_SIZE] = {
        // sleep frames
        {
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0xa8, 0x48, 0xa8, 0x18, 0x08, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x80, 0x44, 0x84, 0x06, 0x05, 0x04, 0x80, 0x40, 0x20, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x18, 0x04, 0x04, 0x02, 0x7a, 0x86, 0x01, 0x80, 0x80, 0x01, 0x03, 0x05, 0x07, 0x01, 0x00, 0x00, 0x80, 0x83, 0x45, 0xfa, 0x3c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x33, 0x24, 0x28, 0x28, 0x29, 0x29, 0x29, 0x3a, 0x18, 0x1c, 0x39, 0x24, 0x24, 0x3a, 0x2d, 0x26, 0x31, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00 }
            },
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x3a, 0x2a, 0x26, 0x22, 0x80, 0xc0, 0x80, 0x00, 0x24, 0x34, 0x2c, 0xe4, 0x60, 0x10, 0x70, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x38, 0x04, 0x02, 0x02, 0x01, 0x79, 0x87, 0x01, 0x80, 0x81, 0x83, 0x05, 0x05, 0x03, 0x01, 0x00, 0x00, 0x80, 0x43, 0x05, 0xfa, 0x3c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x33, 0x24, 0x28, 0x28, 0x28, 0x29, 0x29, 0x3a, 0x18, 0x1c, 0x39, 0x24, 0x24, 0x3a, 0x2d, 0x26, 0x31, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00 }
            }
        },
        // wake frames
        {
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x08, 0x10, 0x60, 0x80, 0x00, 0x80, 0x60, 0x10, 0x08, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x40, 0x40, 0x5c, 0x00, 0x01, 0x41, 0x01, 0x00, 0x5c, 0x40, 0x40, 0x80, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x80, 0xe1, 0x12, 0x0a, 0x06, 0x00, 0x80, 0x00, 0x06, 0x0a, 0x12, 0xe1, 0x80, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x11, 0x10, 0x10, 0x14, 0x14, 0x1f, 0x1c, 0x14, 0x14, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00 }
            },
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x08, 0x10, 0x60, 0x80, 0x00, 0x80, 0x60, 0x10, 0x08, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x90, 0x12, 0x0a, 0x02, 0xf4, 0x09, 0x0d, 0xf1, 0x04, 0x02, 0x0a, 0x12, 0x90, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x80, 0xe1, 0x12, 0x0a, 0x06, 0x01, 0x81, 0x00, 0x06, 0x0a, 0x12, 0xe1, 0x80, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x11, 0x10, 0x10, 0x14, 0x14, 0x1f, 0x1c, 0x14, 0x14, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00 }
            }
        },
        // kaki frames
        {
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x80, 0x80, 0x00, 0xfc, 0x84, 0x08, 0x08, 0x10, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1e, 0x60, 0x80, 0x00, 0x00, 0x91, 0xa1, 0x80, 0x00, 0x00, 0x22, 0x84, 0x40, 0x50, 0x48, 0xc1, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x41, 0x82, 0xe2, 0x12, 0x0a, 0x06, 0x00, 0x80, 0x88, 0x4f, 0x02, 0x22, 0xe2, 0x9f, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x14, 0x10, 0x10, 0x10, 0x10, 0x10, 0x14, 0x14, 0x1f, 0x1a, 0x0a, 0x0a, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 }
            },
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x06, 0x1a, 0x22, 0xc2, 0x04, 0x04, 0x04, 0x07, 0x00, 0xc0, 0x20, 0x10, 0x80, 0x80, 0x01, 0x01, 0x02, 0xfc, 0xfe, 0x02, 0x3c, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x8d, 0x55, 0x50, 0x94, 0xf0, 0x10, 0x09, 0x08, 0x00, 0x80, 0x00, 0x06, 0x09, 0x1b, 0xee, 0x00, 0x00, 0x00, 0x00, 0x81, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x19, 0x18, 0x1c, 0x14, 0x16, 0x15, 0x14, 0x14, 0x14, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00 }
            },
            {
                { 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x01, 0x02, 0x04, 0x04, 0x03, 0x80, 0x40, 0x40, 0x20, 0x00, 0x01, 0x02, 0x8c, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0d, 0x8d, 0x55, 0x50, 0x94, 0xf0, 0x10, 0x0a, 0x0e, 0x1d, 0x95, 0x24, 0x24, 0x27, 0x13, 0xe1, 0x01, 0x01, 0x01, 0x01, 0x02, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1f, 0x14, 0x14, 0x10, 0x10, 0x11, 0x1f, 0x10, 0x10, 0x18, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x19, 0x18, 0x1c, 0x14, 0x14, 0x17, 0x14, 0x14, 0x14, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00 }
            }
        },
        // rtogi frames
        {
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x10, 0x10, 0x08, 0x04, 0x02, 0x01, 0x0f, 0x90, 0x10, 0x20, 0xf0, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x48, 0x47, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x88, 0xc7, 0xc4, 0x62, 0x23, 0x11, 0x3f, 0x00, 0x00, 0x00, 0x00 },
                { 0x80, 0x40, 0x20, 0x10, 0x88, 0xcc, 0x43, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0x80, 0x80, 0xc0, 0xe1, 0xfe, 0xb8, 0x88, 0x0c, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x06, 0x04, 0x04, 0x04, 0x04, 0x05, 0x04, 0x04, 0x04, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
            },
            {
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x10, 0x10, 0x08, 0x04, 0x02, 0x01, 0x1f, 0xa0, 0x20, 0x40, 0x80, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x48, 0x47, 0x88, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x28, 0x6b, 0x40, 0xa0, 0x99, 0x86, 0xff, 0x00, 0x00, 0x00, 0x00 },
                { 0x0f, 0x11, 0x22, 0x44, 0x48, 0x4c, 0x43, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0x80, 0x80, 0xc0, 0xe1, 0xfe, 0xb8, 0x88, 0x0c, 0x04, 0x06, 0x06, 0x06, 0x0e, 0x0e, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x06, 0x04, 0x04, 0x04, 0x04, 0x05, 0x04, 0x04, 0x04, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
            }
        }
    };
    // clang-format on

    for (uint8_t i = 0; i < 4; i++) {
        oled_set_cursor(col, line + i);
        oled_write_raw_P(animation[animation_type][animation_frame][i], OLED_ANIM_SIZE);
    }
}

bool oled_task_user(void) {
    render_logo();
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("MEDIA\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("NAV\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("MOUSE\n"), false);
            break;
        case 4:
            oled_write_P(PSTR("SYM\n"), false);
            break;
        case 5:
            oled_write_P(PSTR("NUM\n"), false);
            break;
        case 6:
            oled_write_P(PSTR("FUN\n"), false);
            break;
        case 7:
            oled_write_P(PSTR("MACRO\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined\n"), false);
    }


    led_t led_state = host_keyboard_led_state();
    oled_write_P(is_caps_word_on() ? PSTR("CWRD ") : PSTR("     "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("     "), false);
    oled_write_ln_P(PSTR("\n"), false);

    oled_write_P("\n", false);
    oled_write_P("\n", false);
    oled_write_P("\n", false);

    render_wpm(1, 0, 10);
    render_kitty(13, 8);
    render_wpm_graph(32, 96);

    return false;
}

bool is_caps_on = false;

void caps_word_sync_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    // if buffer length matches size of data structure (simple error checking)
    if (in_buflen == sizeof(is_caps_on)) {
        // copy data from master into local data structure
        memcpy(&is_caps_on, in_data, in_buflen);
    }
}

void keyboard_post_init_user(void) {
    // register sync handler
    transaction_register_rpc(RPC_TRANSACTION_CAPS_WORD_SYNC, caps_word_sync_slave_handler);
}
void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        // update values
        // copy local variable to sync data structure
        is_caps_on = is_caps_word_on();

        // sync values
        static uint32_t last_sync = 0;
        static bool last_user_state = false;
        static bool needs_sync = false;

        // if value is different, then needs syncing
        if (memcmp(&is_caps_on, &last_user_state, sizeof(is_caps_on))) {
            needs_sync = true;
            // copy local user state to verify changes
            memcpy(&last_user_state, &is_caps_on, sizeof(is_caps_on));
        }
        // Send to slave every 250ms regardless of state change
        if (timer_elapsed32(last_sync) > 250) {
            needs_sync = true;
        }

        // if it needs syncing:
        if (needs_sync) {
            // send user_data stuct over to slave
            if(transaction_rpc_send(RPC_TRANSACTION_CAPS_WORD_SYNC, sizeof(is_caps_on), &is_caps_on)) {
                // reset sync checks
                last_sync = timer_read32();
                needs_sync = false;
            }
        }

    } else { // not master:
        // copy value from data structure to local variable
        if (is_caps_on) {
            caps_word_on();
        } else {
            caps_word_off();
        }
    }
}

#endif // OLED_ENABLE
