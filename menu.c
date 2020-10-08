#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef platform_qcom
#include <lvgl/lvgl.h>
#include "platform/lk/qom/device.h"
#elif defined platform_mtk
#include "../lvgl/lvgl.h"
#include "platform/lk/qom/device.h"
#endif

void droidboot_init()
{
    platform_droidboot_init();
    platform_disp_clear();
    while(1);
}
