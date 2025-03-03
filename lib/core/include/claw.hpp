#pragma once

#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

#define CLW_TOTAL_ANGLE 180

namespace oswaldo
{
  class claw
  {
  private:
    ledc_channel_t channel;
    ledc_timer_t timer;
    int pin;

  public:
    claw(ledc_channel_t ch, ledc_timer_t tmr, int p);

    void open();
    void close();
    void half_open();
    void start_task();
    static void stepped_open_close_claw(void *params);
  };
};
