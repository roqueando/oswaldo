#pragma once

#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

namespace oswaldo
{
  class claw
  {
    private:
      ledc_channel_t channel;
      ledc_timer_t timer;
      uint32_t pin;

    public:
      claw(ledc_channel_t ch, ledc_timer_t tmr, uint32_t p);

      void open(double percent);
      void close(double percent);
  }
};


