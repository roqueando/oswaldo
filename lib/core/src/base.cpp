#include "base.hpp"
#include "config.hpp"
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

#define DEFAULT_WAIT pdMS_TO_TICKS(30)

oswaldo::base::base(ledc_channel_t ch, ledc_timer_t tmr, int p) : channel(ch), timer(tmr), pin(p)
{
    ledc_channel_config_t channel_conf = {
        .gpio_num = pin,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = channel,
        .timer_sel = timer,
        .duty = 0};
    ledc_channel_config(&channel_conf);
    move(50, channel, TOTAL_ANGLE);
}

void oswaldo::base::to_right_task(void *params)
{
    oswaldo::base *instance = static_cast<oswaldo::base *>(params);
    for (int i = 50; i <= 100; i++)
    {
        move(i, instance->channel, TOTAL_ANGLE);
        vTaskDelay(DEFAULT_WAIT);
    }
}

void oswaldo::base::to_right()
{
    xTaskCreate(to_right_task, "To Right Task", 1024, this, 1, NULL);
}

void oswaldo::base::to_left_task(void *params)
{

    oswaldo::base *instance = static_cast<oswaldo::base *>(params);
    for (int i = 50; i >= 0; i--)
    {
        move(i, instance->channel, TOTAL_ANGLE);
        vTaskDelay(DEFAULT_WAIT);
    }
    vTaskDelete(NULL);
}

void oswaldo::base::to_left()
{
    xTaskCreate(to_left_task, "To Left Task", 1024, this, 3, NULL);
}

void oswaldo::base::from_left()
{
    for (int i = 0; i <= 50; i++)
    {
        move(i, channel, TOTAL_ANGLE);
        vTaskDelay(DEFAULT_WAIT);
    }
}

void oswaldo::base::from_right()
{
    for (int i = 100; i >= 50; i--)
    {
        move(i, channel, TOTAL_ANGLE);
        vTaskDelay(DEFAULT_WAIT);
    }
}

void oswaldo::base::left()
{
    move(0, channel, TOTAL_ANGLE);
}

void oswaldo::base::center()
{
    move(50, channel, TOTAL_ANGLE);
}

void oswaldo::base::right()
{
    move(100, channel, TOTAL_ANGLE);
}

void oswaldo::base::stepped_left_right_base(void *params)
{
    oswaldo::base *instance = static_cast<oswaldo::base *>(params);

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
