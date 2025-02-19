/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "lvgl.h"

// LVGL image declare
LV_IMG_DECLARE(esp_logo)


void add_tab1_content(lv_obj_t * scr)
{
    /* Create image - logo */
    lv_obj_t * img_logo = lv_img_create(scr);
    lv_img_set_src(img_logo, &esp_logo);
    lv_obj_align(img_logo, LV_ALIGN_TOP_RIGHT, 0, 10);
    
}

void add_tab2_content(lv_obj_t * scr)
{
    
}

void add_tab3_content(lv_obj_t * scr)
{
    
}

void network_demo_ui(lv_obj_t *scr)
{
    /*Create a Tab view object*/
    lv_obj_t * tabview;
    tabview = lv_tabview_create(scr);
    lv_tabview_set_tab_bar_position(tabview, LV_DIR_BOTTOM);
    
    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "Presentation");
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Overview");
    lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "I forgot...");
    
    add_tab1_content(tab1);
    add_tab2_content(tab2);
    add_tab3_content(tab3);
}
