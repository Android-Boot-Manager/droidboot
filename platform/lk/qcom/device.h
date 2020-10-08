void platform_sleep(int time);
void platform disp_clear();
bool keyboard_read(lv_indev_drv_t * drv, lv_indev_data_t*data);
void qcom_fbcon_disp_flush(lv_disp_t * disp,
    const lv_area_t * area, lv_color_t * color_p);
