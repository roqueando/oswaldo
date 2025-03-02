#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"

#include "driver/ledc.h"
#include "esp_err.h"

#include "config.hpp"
#include "claw.hpp"
#include "elbow.hpp"
#include "shoulder.hpp"
#include "base.hpp"
#include "pickup_garbage.hpp"

extern "C" void app_main()
{
    oswaldo_init();

    oswaldo::base bas(LEDC_CHANNEL_0, LEDC_TIMER_0, 3);
    oswaldo::shoulder sho(LEDC_CHANNEL_1, LEDC_TIMER_0, 2);
    oswaldo::elbow elb(LEDC_CHANNEL_2, LEDC_TIMER_0, 1);
    oswaldo::claw clw(LEDC_CHANNEL_3, LEDC_TIMER_0, 0);

    oswaldo::pickup_garbage pg(sho, elb, bas, clw);
    pg.run();
    //   clw.start_task();
    //   elb.start_task();
    //   sho.start_task();
    //   bas.start_task();
}
