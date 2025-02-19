/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "bsp/esp-bsp.h"
#include "lvgl.h"
#include "esp_log.h"

extern void network_demo_ui(lv_obj_t *scr);

void app_main(void)
{
    /* Initialize display + LVGL */
    bsp_display_start();

    bsp_display_lock(0);
    lv_obj_t *scr = lv_disp_get_scr_act(NULL);
    network_demo_ui(scr);

    bsp_display_unlock();
    bsp_display_backlight_on();
}
