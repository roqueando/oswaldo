#include "config.hpp"
#include "claw.hpp"
#include "elbow.hpp"
#include "shoulder.hpp"
#include "base.hpp"
#include "pickup_garbage.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

oswaldo::pickup_garbage::pickup_garbage(oswaldo::shoulder sho, oswaldo::elbow elb, oswaldo::base bas, oswaldo::claw clw) : sho(sho), elb(elb), bas(bas), clw(clw) {}

void oswaldo::pickup_garbage::run()
{
    xTaskCreate(task_pickup_garbage, "task_pickup_garbage", 1024, this, 5, NULL);
}

void oswaldo::pickup_garbage::task_pickup_garbage(void *params)
{
    oswaldo::pickup_garbage *instance = static_cast<oswaldo::pickup_garbage *>(params);
    // instance->bas.to_left();
    instance->clw.open();
    //   instance->sho.to_back();
    //  instance->elb.to_down();
    vTaskDelay(pdMS_TO_TICKS(2000));
    // instance->bas.from_left();
    // vTaskDelay(pdMS_TO_TICKS(2000));
    // instance->bas.to_right();
    // vTaskDelay(pdMS_TO_TICKS(2000));
    // instance->bas.from_right();
    // vTaskDelay(pdMS_TO_TICKS(2000));
    /*
    while (true)
    {
        // turn left and lay down the claw
        // instance->sho.to_back();
        // instance->elb.to_down();

        // go back
        // instance->bas.from_left();
        // instance->sho.from_back();
        // instance->elb.from_down();
        // vTaskDelay(pdMS_TO_TICKS(2000));
    }
        */
    vTaskDelete(NULL);
}
