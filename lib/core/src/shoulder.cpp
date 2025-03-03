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
        .duty = 0};
    ledc_channel_config(&channel_conf);
    move(50, channel, SHO_TOTAL_ANGLE);
}

void oswaldo::shoulder::from_front()
{
    for (int i = 0; i < 50; i++)
    {
        move(i, channel, SHO_TOTAL_ANGLE);
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void oswaldo::shoulder::from_back()
{
    for (int i = 100; i > 50; i--)
    {
        move(i, channel, SHO_TOTAL_ANGLE);
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void oswaldo::shoulder::to_front_task(void *params)
{
    oswaldo::shoulder *instance = static_cast<oswaldo::shoulder *>(params);

    for (int i = 50; i <= 100; i++)
    {
        move(i, instance->channel, SHO_TOTAL_ANGLE);
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    vTaskDelete(NULL);
}

void oswaldo::shoulder::to_back_task(void *params)
{
    oswaldo::shoulder *instance = static_cast<oswaldo::shoulder *>(params);

    for (int i = 50; i >= 0; i--)
    {
        move(i, instance->channel, SHO_TOTAL_ANGLE);
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    vTaskDelete(NULL);
}

void oswaldo::shoulder::to_front()
{
    xTaskCreate(to_front_task, "To Front Task", 1024, this, 1, NULL);
}

void oswaldo::shoulder::to_back()
{
    xTaskCreate(to_back_task, "To Back Task", 1024, this, 1, NULL);
}

void oswaldo::shoulder::slowly_front()
{
    for (int i = 0; i < 100; i++)
    {
        move(i, channel, SHO_TOTAL_ANGLE);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void oswaldo::shoulder::slowly_back()
{
    for (int i = 100; i > 0; i--)
    {
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

void oswaldo::shoulder::stepped_front_back_shoulder(void *params)
{
    oswaldo::shoulder *instance = static_cast<oswaldo::shoulder *>(params);

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
    xTaskCreate(stepped_front_back_shoulder, "Stepped Front Back Shoulder", 1024, this, 1, NULL);
}
