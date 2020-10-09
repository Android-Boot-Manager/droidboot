#include <lvgl/lvgl.h>
void platform_sleep(int time);
void platform_disp_clear();
bool platform_keyboard_read(lv_indev_drv_t * drv, lv_indev_data_t*data);
void platform_fbcon_disp_flush(lv_disp_t * disp,
    const lv_area_t * area, lv_color_t * color_p);
void platform_create_lvgl_threads();
int platform_droidboot_init();
