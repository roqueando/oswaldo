#include "base.hpp"
#include "config.hpp"
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

oswaldo::base::base(ledc_channel_t ch, ledc_timer_t tmr, int p) : channel(ch), timer(tmr), pin(p)
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

void oswaldo::base::left()
{
    move(0, channel);
}

void oswaldo::base::center()
{
    move(50, channel);
}

void oswaldo::base::right()
{
    move(100, channel);
}


void oswaldo::base::stepped_left_right_base(void* params)
{
    oswaldo::base* instance = static_cast<oswaldo::base*>(params);

    while (true)
    {
        instance->left();
        vTaskDelay(pdMS_TO_TICKS(2000));

        instance->center();
        vTaskDelay(pdMS_TO_TICKS(2000));

        instance->right();
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void oswaldo::base::start_task()
{
    xTaskCreate(stepped_left_right_base, "Stepped Left Right Claw", 1024, this, 1, NULL);
}
