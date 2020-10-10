#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "platform/lk/device.h" //for keyboard
#include "../lvgl/lvgl.h"

lv_obj_t *menu = NULL;

static void menu_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        int index = lv_list_get_btn_index(NULL, obj);
    }
}

void draw_menu_screen()
{
    menu = lv_obj_create(NULL, NULL);
    lv_scr_load(menu);
    lv_obj_t * win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Boot menu"); 
    lv_obj_t * list1 = lv_list_create(win, NULL);
    lv_group_t * g1 = lv_group_create();
    lv_group_add_obj(g1, list1);
    lv_group_focus_obj(list1);
    lv_obj_set_size(list1, 1074, 2060);
    lv_obj_align(list1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_list_set_anim_time(list1, 0);
    lv_win_set_scrollbar_mode(win, LV_SCRLBAR_MODE_OFF);
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);      /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = platform_keyboard_read;
    lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv);
    lv_indev_set_group(my_indev, g1);
    
    lv_obj_t * list_btn;
    lv_obj_set_state(list1, LV_STATE_DEFAULT);
    //list_btn = lv_list_add_btn(list1, LV_SYMBOL_FILE, entry_list->title);
    //lv_obj_set_event_cb(list_btn, menu_screen_handler);
    /*int i;
    for (i = 1; i < num_of_boot_entries; i++) {
        list_btn = lv_list_add_btn(list1,  LV_SYMBOL_FILE, (entry_list + i)->title);
        lv_obj_set_event_cb(list_btn, event_handler);
    }*/
    list_btn = lv_list_add_btn(list1,  LV_SYMBOL_FILE, "Extras");
    lv_obj_set_event_cb(list_btn, menu_handler);
}
