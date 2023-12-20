/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#pragma once

#define DEBOUNCE 5
#define TAPPING_TERM 180
#define OLED_DISPLAY_128X64
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_WPM_ENABLE
#define SPLIT_TRANSACTION_IDS_USER RPC_TRANSACTION_CAPS_WORD_SYNC
#define COMBO_COUNT 1
#undef CIRQUE_PINNACLE_TAP_ENABLE
#undef POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#undef CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
#define OLED_DISPLAY_HEIGHT 128

#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
