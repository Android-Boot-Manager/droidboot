#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pm8x41.h>
#include <pm8x41_hw.h>
#include <kernel/thread.h>
#include <dev/fbcon.h>
#include <target.h>
#include <lib/lvgl.h>
#include <aboot/aboot.h>

bool up = false;
bool down = false;
bool enter = false;
bool p = false;

void platform_sleep(int time){
    thread_sleep(time);
}

void platform disp_clear(){
    fbcon_clear();
}

bool platform_keyboard_read(lv_indev_drv_t * drv, lv_indev_data_t*data){
	uint32_t volume_up_pressed = target_volume_up();
	uint32_t volume_down_pressed = target_volume_down();
	uint32_t power_button_pressed = pm8x41_get_pwrkey_is_pressed();
    if(volume_up_pressed){
        up=true;
        p=true;
    }
    if(power_button_pressed){
        enter=true;
        p=true;
    }
    if(volume_down_pressed){
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
        //printf("release\n");
        up=false;
        down=false;
        enter=false;
    }
  return false; /*No buffering now so no more data read*/
}

void platform_fbcon_disp_flush(lv_disp_t * disp,
    const lv_area_t * area, lv_color_t * color_p) {
    uint x, y;
    for (y = area -> y1; y <= area -> y2; y++) {
      for (x = area -> x1; x <= area -> x2; x++) {
        fbcon_draw_pixel(x, y, 0xff << 24 | color_p->ch.red << 16 | color_p->ch.green << 8 | color_p->ch.blue  ); /* Put a pixel to the display.*/
        color_p++;
      }
    }
    fbcon_flush(); //Flush fbcon, to show evrything on screen
    lv_disp_flush_ready(disp); /* Indicate you are ready with the flushing*/
}

