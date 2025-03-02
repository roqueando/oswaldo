#include "elbow.hpp"
#include "config.hpp"
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

oswaldo::elbow::elbow(ledc_channel_t ch, ledc_timer_t tmr, int p) : channel(ch), timer(tmr), pin(p)
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

void oswaldo::elbow::up()
{
    move(5, channel);
}

void oswaldo::elbow::half_up()
{
    move(15, channel);
}

void oswaldo::elbow::down()
{
    move(10, channel);
}


void oswaldo::elbow::stepped_up_down_elbow(void* params)
{
    oswaldo::elbow* instance = static_cast<oswaldo::elbow*>(params);

    while (true)
    {
        instance->up();
        vTaskDelay(pdMS_TO_TICKS(2000));

        instance->half_up();
        vTaskDelay(pdMS_TO_TICKS(2000));

        instance->down();
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void oswaldo::elbow::start_task()
{
    xTaskCreate(stepped_up_down_elbow, "Stepped Up Down Claw", 1024, this, 1, NULL);
}
