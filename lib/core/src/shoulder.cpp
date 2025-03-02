#include "shoulder.hpp"
#include "config.hpp"
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"


oswaldo::shoulder::shoulder(ledc_channel_t ch, ledc_timer_t tmr, int p) : channel(ch), timer(tmr), pin(p)
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

void oswaldo::shoulder::slowly_front()
{
    for (int i = 0; i < 100; i++) {
        move(i, channel, SHO_TOTAL_ANGLE);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void oswaldo::shoulder::slowly_back()
{
    for (int i = 100; i > 0; i--) {
        move(i, channel, SHO_TOTAL_ANGLE);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void oswaldo::shoulder::front()
{
    move(100, channel, SHO_TOTAL_ANGLE);
}

void oswaldo::shoulder::half_front()
{
    move(90, channel, SHO_TOTAL_ANGLE);
}

void oswaldo::shoulder::back()
{
    move(0, channel, SHO_TOTAL_ANGLE);
}


void oswaldo::shoulder::stepped_front_back_shoulder(void* params)
{
    oswaldo::shoulder* instance = static_cast<oswaldo::shoulder*>(params);

    while (true)
    {
        instance->slowly_back();
        vTaskDelay(pdMS_TO_TICKS(2000));

        instance->slowly_front();
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void oswaldo::shoulder::start_task()
{
    xTaskCreate(stepped_front_back_shoulder, "Stepped Front Back Claw", 1024, this, 1, NULL);
}
