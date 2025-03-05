#pragma once

#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"
#include "joint.hpp"

namespace oswaldo
{
  class claw : protected joint
  {

  public:
    claw(ledc_channel_t ch, ledc_timer_t tmr, int p) : joint(ch, tmr, p) {}
    void open();
    void close();

  private:
    static void task_open(void *params);
    static void task_close(void *params);
  };
};
