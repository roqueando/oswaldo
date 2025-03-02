#pragma once

#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

#define TOTAL_ANGLE 80

namespace oswaldo
{
  class elbow
  {
    private:
      ledc_channel_t channel;
      ledc_timer_t timer;
      int pin;

    public:
      elbow(ledc_channel_t ch, ledc_timer_t tmr, int p);

      void up();
      void down();
      void half_up();
      void start_task();
      static void stepped_up_down_elbow(void *params);
  };
};


