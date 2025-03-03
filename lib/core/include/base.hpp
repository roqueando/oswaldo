#pragma once

#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

#define TOTAL_ANGLE 180

namespace oswaldo
{
  class base
  {
  private:
    ledc_channel_t channel;
    ledc_timer_t timer;
    int pin;

    static void to_right_task(void *params);
    static void to_left_task(void *params);

  public:
    base(ledc_channel_t ch, ledc_timer_t tmr, int p);

    void left();
    void right();
    void center();
    void from_right();
    void from_left();
    void to_right();
    void to_left();
    void start_task();
    static void stepped_left_right_base(void *params);
  };
};
