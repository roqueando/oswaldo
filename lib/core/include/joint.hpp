#pragma once

#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

#define DEFAULT_MIN_PULSEWIDTH 500
#define DEFAULT_MAX_PULSEWIDTH 2500
#define LEDC_RESOLUTION LEDC_TIMER_14_BIT

namespace oswaldo
{

    class joint
    {
    private:
        ledc_channel_t channel;
        ledc_timer_t timer;
        int pin;
        int total_angle = 180;
        int default_position = 0;
        uint32_t angle_to_pulsewidth(int angle);

    public:
        joint(ledc_channel_t ch, ledc_timer_t tmr, int p);

        void move(int percent, ledc_channel_t channel);
        void normal_delay();

        // Getters
        ledc_channel_t get_channel() const;
        ledc_timer_t get_timer() const;
        int get_pin() const;
        int get_total_angle() const;
        int get_default_position() const;
    };

} // namespace oswaldo
