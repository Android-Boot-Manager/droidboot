#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lvgl_common.h"


#include "../lvgl/lvgl.h"
#include "platform/lk/device.h"

lv_obj_t *menu = NULL;

void * tick_thread (void *args)
{
      while(1) {
        platform_sleep(10);   /*Sleep for 5 millisecond*/
        lv_tick_inc(10);      /*Tell LVGL that 5 milliseconds were elapsed*/
    }
}

void * task_thread (void *args)
{
    while(1) {
        lv_task_handler();
        platform_sleep(10);
    }
}

void droidboot_init()
{
    lvgl_common_init();
    platform_droidboot_init();
    platform_sleep(300);
    platform_create_lvgl_threads();
    platform_disp_clear();


}
