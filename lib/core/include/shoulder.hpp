#pragma once

#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

#define TOTAL_ANGLE 180

namespace oswaldo
{
  class shoulder
  {
    private:
      ledc_channel_t channel;
      ledc_timer_t timer;
      int pin;

    public:
      shoulder(ledc_channel_t ch, ledc_timer_t tmr, int p);

      void slowly_front();
      void slowly_back();
      void front();
      void back();
      void half_front();
      void start_task();
      static void stepped_front_back_shoulder(void *params);
  };
};


