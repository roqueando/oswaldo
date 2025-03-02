#include "claw.hpp"
#include "config.hpp"
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

oswaldo::claw::claw(ledc_channel_t ch, ledc_timer_t tmr, int p) : channel(ch), timer(tmr), pin(p)
{
    ledc_channel_config_t channel_conf = {
        .gpio_num = pin,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = channel,
        .timer_sel = timer,
        .duty = 0
    };
    ledc_channel_config(&channel_conf);
}

void oswaldo::claw::open()
{
    move(100, channel, CLW_TOTAL_ANGLE);
}

void oswaldo::claw::half_open()
{
    move(50, channel, CLW_TOTAL_ANGLE);
}

void oswaldo::claw::close()
{
    move(0, channel, CLW_TOTAL_ANGLE);
}


void oswaldo::claw::stepped_open_close_claw(void* params)
{
    oswaldo::claw* instance = static_cast<oswaldo::claw*>(params);

    while (true)
    {
        instance->open();
        vTaskDelay(pdMS_TO_TICKS(2000));

        instance->half_open();
        vTaskDelay(pdMS_TO_TICKS(2000));

        instance->close();
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void oswaldo::claw::start_task()
{
    xTaskCreate(stepped_open_close_claw, "Stepped Open Close Claw", 1024, this, 1, NULL);
}
