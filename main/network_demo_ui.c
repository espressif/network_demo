/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "bsp/esp-bsp.h"
#include "lvgl.h"

// LVGL image declare
LV_IMG_DECLARE(esp_logo)

#define APP_SCREEN_H    (BSP_LCD_V_RES-110)
#define APP_SCREEN_W    (BSP_LCD_H_RES-50)
#define APP_OVERVIEW_H  (APP_SCREEN_H/5-5)
#define APP_OVERVIEW_W  (APP_SCREEN_W/4-10)

static lv_obj_t * app_tab2_nodes = NULL;

typedef struct
{
    uint8_t id;
    bool    status;
} app_node_t;

void app_disp_update_nodes(app_node_t * nodes)
{
    lv_obj_t * node_obj = NULL;
    lv_obj_t * led;
    lv_obj_t * label;
    char node_name[30];
    
    lv_obj_clean(app_tab2_nodes);
    
    while(nodes && nodes->id)
    {
        snprintf(node_name, sizeof(node_name), "Node %d: %s", nodes->id, (nodes->status ? "Active" : "Inactive"));
        node_obj = lv_obj_create(app_tab2_nodes);
        lv_obj_set_scrollbar_mode(node_obj, LV_SCROLLBAR_MODE_OFF);
        lv_obj_set_size(node_obj, 2*APP_OVERVIEW_W-10, 20);
        lv_obj_set_style_border_width(node_obj, 0, 0);
        lv_obj_set_style_bg_opa(node_obj, LV_OPA_MIN, 0);
        lv_obj_set_style_pad_all(node_obj, 5, 0);
        lv_obj_set_flex_flow(node_obj, LV_FLEX_FLOW_ROW);
        led  = lv_led_create(node_obj);
        lv_obj_set_size(led, 10, 10);
        label = lv_label_create(node_obj);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
        lv_label_set_text(label, node_name);
        
        if (nodes->status) {
            lv_led_set_color(led, lv_palette_main(LV_PALETTE_GREEN));
        } else {
            lv_led_set_color(led, lv_palette_main(LV_PALETTE_RED));
        }
        
        nodes++;
    }
}

void app_disp_update_chart(lv_obj_t * scr)
{
    /*Create a chart*/
    lv_obj_t * chart;
    chart = lv_chart_create(scr);
    lv_obj_set_size(chart, 1.5*APP_OVERVIEW_W, 2*APP_OVERVIEW_H-50);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_series_t * ser1 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
    
    uint32_t i;
    for(i = 0; i < 10; i++) {
        /*Set the next points on 'ser1'*/
        lv_chart_set_next_value(chart, ser1, lv_rand(10, 50));
    }

    lv_chart_refresh(chart); /*Required after direct set*/
}

static void add_disp_tab1_content(lv_obj_t * scr)
{
    /* Create image - logo */
    lv_obj_t * img_logo = lv_img_create(scr);
    lv_img_set_src(img_logo, &esp_logo);
    lv_obj_center(img_logo);
    //lv_obj_align(img_logo, LV_ALIGN_TOP_RIGHT, 0, 10);
    
}

static void add_disp_tab2_content(lv_obj_t * scr)
{
    lv_obj_t * cell;
    lv_obj_t * label;
    static int32_t col_dsc[] = {APP_OVERVIEW_W, APP_OVERVIEW_W, APP_OVERVIEW_W, APP_OVERVIEW_W, LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {APP_OVERVIEW_H, 2*APP_OVERVIEW_H, 2*APP_OVERVIEW_H, LV_GRID_TEMPLATE_LAST};
    
    /*Create a container with grid*/
    lv_obj_t * cont = lv_obj_create(scr);
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_set_style_bg_opa(cont, LV_OPA_MIN, 0);
    lv_obj_set_style_pad_all(cont, 0, 0);
    lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
    lv_obj_set_size(cont, APP_SCREEN_W, APP_SCREEN_H);
    
    /* == ROW 1 == */
    /*Cell to 0;0 and align to to the start (left/top) horizontally and vertically too*/
    cell = lv_obj_create(cont);
    lv_obj_set_size(cell, APP_OVERVIEW_W, APP_OVERVIEW_H);
    lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, 0, 3, LV_GRID_ALIGN_START, 0, 1);
    
    label = lv_label_create(cell);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_30, 0);
    lv_label_set_text_static(label, "System Overview");
    
    label = lv_label_create(cell);
    lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
    lv_label_set_text_static(label, "Last updated: 111111");
    
    
    /*Cell to 1;0 and align to to the start (left/top) horizontally and vertically too*/
    cell = lv_obj_create(cont);
    lv_obj_set_size(cell, APP_OVERVIEW_W, APP_OVERVIEW_H);
    lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, 3, 1, LV_GRID_ALIGN_START, 0, 1);
    lv_obj_set_style_pad_all(cell, 0, 0);
    lv_obj_set_scrollbar_mode(cell, LV_SCROLLBAR_MODE_OFF);
    /* Create image - logo */
    lv_obj_t * img_logo = lv_img_create(cell);
    lv_img_set_zoom(img_logo, 150);
    lv_img_set_src(img_logo, &esp_logo);
    lv_obj_center(img_logo);
    lv_obj_update_layout(img_logo);
    
    /* == ROW 2 == */
    /*Cell to 0;1 and align to to the start (left/top) horizontally and vertically too*/
    cell = lv_obj_create(cont);
    lv_obj_set_size(cell, APP_OVERVIEW_W, APP_OVERVIEW_H);
    lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_STRETCH, 1, 1);
    lv_obj_set_flex_flow(cell, LV_FLEX_FLOW_COLUMN);
    
    label = lv_label_create(cell);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0);
    lv_label_set_text_static(label, LV_SYMBOL_WIFI" Network Status");
    
    label = lv_label_create(cell);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
    lv_label_set_text_static(label, "Connected Devices: 4\nNetwork: IoT_Demo_Network\nSignal Strength: ");
    
    /*Cell to 1;1 and align to to the start (left/top) horizontally and vertically too*/
    cell = lv_obj_create(cont);
    lv_obj_set_size(cell, APP_OVERVIEW_W, APP_OVERVIEW_H);
    lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, 2, 2, LV_GRID_ALIGN_STRETCH, 1, 1);
    lv_obj_set_flex_flow(cell, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scrollbar_mode(cell, LV_SCROLLBAR_MODE_OFF);
    
    label = lv_label_create(cell);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0);
    lv_label_set_text_static(label, LV_SYMBOL_BARS" Node Status");
    
    app_tab2_nodes = lv_obj_create(cell);
    lv_obj_set_width(app_tab2_nodes, 2*APP_OVERVIEW_W-10);
    lv_obj_set_style_border_width(app_tab2_nodes, 0, 0);
    lv_obj_set_style_bg_opa(app_tab2_nodes, LV_OPA_MIN, 0);
    lv_obj_set_style_pad_all(app_tab2_nodes, 0, 0);
    lv_obj_set_flex_flow(app_tab2_nodes, LV_FLEX_FLOW_COLUMN);
    
    /* == ROW 3 == */
    /*Cell to 2;0 and align to to the start (left/top) horizontally and vertically too*/
    cell = lv_obj_create(cont);
    lv_obj_set_size(cell, APP_OVERVIEW_W, APP_OVERVIEW_H);
    lv_obj_set_grid_cell(cell, LV_GRID_ALIGN_STRETCH, 0, 4, LV_GRID_ALIGN_STRETCH, 2, 1);
    lv_obj_set_flex_flow(cell, LV_FLEX_FLOW_ROW);
    
    
    app_disp_update_chart(cell);
    app_disp_update_chart(cell);
    app_disp_update_chart(cell);
    
}

static void add_disp_tab3_content(lv_obj_t * scr)
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
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "System Overview");
    lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "I forgot...");
    
    add_disp_tab1_content(tab1);
    add_disp_tab2_content(tab2);
    add_disp_tab3_content(tab3);
    
    app_node_t nodes[] = {
        {1, true},
        {2, false},
        {3, true},
        {4, true},
        {0, NULL}
    };
    
    app_disp_update_nodes(nodes);
}
