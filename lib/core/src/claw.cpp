#include "claw.hpp"
#include "config.hpp"
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

void oswaldo::claw::task_open(void *params)
{

    oswaldo::claw *instance = static_cast<oswaldo::claw *>(params);
    for (int i = 0; i <= 100; i++)
    {
        move(i, instance->get_channel());
        normal_delay();
    }
}

void oswaldo::claw::open()
{

    xTaskCreate(task_open, "Open Task", 1024, this, 1, NULL);
}

void oswaldo::claw::task_close(void *params)
{

    oswaldo::claw *instance = static_cast<oswaldo::claw *>(params);
    for (int i = 100; i <= 0; i--)
    {
        move(i, instance->get_channel());
        normal_delay();
    }
}

void oswaldo::claw::close()
{
    xTaskCreate(task_close, "Close Task", 1024, this, 1, NULL);
}
