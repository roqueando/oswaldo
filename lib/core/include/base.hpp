#pragma once

#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

namespace oswaldo
{
  class base
  {
    private:
      ledc_channel_t channel;
      ledc_timer_t timer;
      int pin;

    public:
      base(ledc_channel_t ch, ledc_timer_t tmr, int p);

      void left();
      void right();
      void center();
      void start_task();
      static void stepped_left_right_base(void *params);
  };
};


