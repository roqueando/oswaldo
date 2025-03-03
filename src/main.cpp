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
#include <memory>
// #include "pickup_garbage.hpp"

void pickup_garbage(std::shared_ptr<oswaldo::base> bas, std::shared_ptr<oswaldo::shoulder> sho, std::shared_ptr<oswaldo::elbow> elb, std::shared_ptr<oswaldo::claw> clw)
{
    bas->to_left();
    sho->to_back();
    clw->open();
}

extern "C" void app_main()
{
    oswaldo_init();

    /*
    std::shared_ptr<oswaldo::base> bas = std::make_shared<oswaldo::base>(LEDC_CHANNEL_0, LEDC_TIMER_0, 3);
    std::shared_ptr<oswaldo::shoulder> sho = std::make_shared<oswaldo::shoulder>(LEDC_CHANNEL_1, LEDC_TIMER_0, 2);
    std::shared_ptr<oswaldo::elbow> elb = std::make_shared<oswaldo::elbow>(LEDC_CHANNEL_2, LEDC_TIMER_0, 1);
    std::shared_ptr<oswaldo::claw> clw = std::make_shared<oswaldo::claw>(LEDC_CHANNEL_4, LEDC_TIMER_0, 0);
    */
    oswaldo::base bas(LEDC_CHANNEL_0, LEDC_TIMER_0, 3);
    oswaldo::shoulder sho(LEDC_CHANNEL_1, LEDC_TIMER_0, 2);
    oswaldo::elbow elb(LEDC_CHANNEL_2, LEDC_TIMER_0, 1);
    oswaldo::claw clw(LEDC_CHANNEL_4, LEDC_TIMER_0, 0);

    // pickup_garbage(bas, sho, elb, clw);
    //  oswaldo::pickup_garbage pg(sho, elb, bas, clw);
    //   pg.run();
    //      clw.start_task();
    //      elb.start_task();
    //      sho.start_task();
    //      bas.start_task();
}
