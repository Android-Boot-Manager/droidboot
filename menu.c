#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include "../lvgl/lvgl.h"
#include "platform/lk/mtk/device.h"

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
    lv_init();
    platform_droidboot_init();
    static lv_disp_buf_t disp_buf;
    static lv_color_t buf[LV_HOR_RES_MAX * 10]; /*Declare a buffer for 10 lines*/
    lv_disp_buf_init( & disp_buf, buf, NULL, LV_HOR_RES_MAX * 10); /*Initialize the display buffer*/
    lv_disp_drv_t disp_drv; /*Descriptor of a display driver*/
    lv_disp_drv_init( & disp_drv); /*Basic initialization*/
    disp_drv.flush_cb = platform_fbcon_disp_flush; /*Set your driver function*/
    disp_drv.buffer = & disp_buf; /*Assign the buffer to the display*/
    lv_disp_drv_register( & disp_drv); /*Finally register the driver*/
    platform_sleep(300);
    platform_create_lvgl_threads();
    platform_disp_clear();


}
