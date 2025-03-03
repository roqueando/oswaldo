#pragma once

#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

#define ELB_TOTAL_ANGLE 80

namespace oswaldo
{
  class elbow
  {
  private:
    ledc_channel_t channel;
    ledc_timer_t timer;
    int pin;

    static void to_up_task(void *params);
    static void to_down_task(void *params);

  public:
    elbow(ledc_channel_t ch, ledc_timer_t tmr, int p);

    void slowly_up();
    void slowly_down();
    void up();
    void down();
    void half_up();
    void start_task();
    static void stepped_up_down_elbow(void *params);

    void from_up();
    void from_down();
    void to_up();
    void to_down();
  };
};
