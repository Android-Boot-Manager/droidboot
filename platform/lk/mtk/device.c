#include "../../../../lvgl/lvgl.h"
#include <kernel/thread.h>
#include <platform/mtk_key.h>
#include <target/cust_key.h>
#include <sys/types.h>
#include <reg.h>
#include <debug.h>
#include <err.h>
#include <reg.h>
#include <lib/fs.h>
#include <video.h>
#include <platform/mt_typedefs.h>
#include <platform/boot_mode.h>
#include <platform/mt_reg_base.h>
#include <platform/mt_gpt.h>
#include <platform/mtk_wdt.h>
#include <lib/bio.h>
#include <part_interface.h>
#include <block_generic_interface.h>
#include <lib/partition.h>
#include "storage/storage.h"

bool up = false;
bool down = false;
bool enter = false;
bool p = false;

void platform_sleep(int time){
    thread_sleep(time);
}

void platform_disp_clear(){
    video_clean_screen();
}

bool platform_keyboard_read(lv_indev_drv_t * drv, lv_indev_data_t*data){
    if(mtk_detect_key(MT65XX_MENU_SELECT_KEY)){
        up=true;
        p=true;
    }
    if(mtk_detect_key(MTK_PMIC_PWR_KEY)){
        enter=true;
        p=true;
    }
    if(mtk_detect_key(MT65XX_MENU_OK_KEY)){
        down=true;
        p=true;
    }
    if(up){
        data->key = LV_KEY_UP;            /*Get the last pressed or released key*/
    }
    if(enter){
        data->key = LV_KEY_ENTER;            /*Get the last pressed or released key*/
    }

    if(down){
        data->key = LV_KEY_DOWN;            /*Get the last pressed or released key*/
    }

    if(p){
        data->state = LV_INDEV_STATE_PR;
        p=false;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
        up=false;
        down=false;
        enter=false;
    }
  return false; /*No buffering now so no more data read*/
}

static int tick_thread(void * arg) {
  /*Handle LitlevGL tasks (tickless mode)*/
  while (1) {
    lv_tick_inc(1);
    thread_sleep(1);
  }

  return 0;
}

static int task_thread(void * arg) {
  /*Handle LitlevGL tasks (tickless mode)*/
  while (1) {
    lv_task_handler();
    thread_sleep(1);
  }

  return 0;
}

void platform_create_lvgl_threads(){
    thread_t *task;
    task=thread_create("task", & task_thread, NULL, HIGHEST_PRIORITY, 16*1024);
    thread_resume(task);
    thread_t *tick;
    tick=thread_create("tick", & tick_thread, NULL, HIGHEST_PRIORITY, 16*1024);
    thread_resume(tick);
}



void platform_fbcon_disp_flush(lv_disp_t * disp,
    const lv_area_t * area, lv_color_t * color_p) {
    uint x, y;
    for (y = area -> y1; y <= area -> y2; y++) {
        for (x = area -> x1; x <= area -> x2; x++) {
          video_draw_pixel(x, y, 0xff << 24 | color_p->ch.red << 16 | color_p->ch.green << 8 | color_p->ch.blue ); /* Put a pixel to the display.*/
          color_p++;
        }
    }
  mt_disp_update(0, 0, 1080, 2340);
  lv_disp_flush_ready(disp); /* Indicate you are ready with the flushing*/
}

int platform_droidboot_init(){
    platform_storage_init();
    mtk_wdt_disable();
    return 0;
}


