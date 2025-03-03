#pragma once

#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

#define SHO_TOTAL_ANGLE 180

namespace oswaldo
{
  class shoulder
  {
  private:
    ledc_channel_t channel;
    ledc_timer_t timer;
    int pin;

    static void to_front_task(void *params); // Adicione esta linha
    static void to_back_task(void *params);  // Adicione esta linha

  public:
    shoulder(ledc_channel_t ch, ledc_timer_t tmr, int p);

    void slowly_front();
    void slowly_back();
    void front();
    void back();
    void half_front();
    void start_task();
    static void stepped_front_back_shoulder(void *params);

    void from_front();
    void from_back();
    void to_front();
    void to_back();
  };
};
