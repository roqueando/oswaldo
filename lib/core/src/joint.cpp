#include "joint.hpp"

namespace oswaldo
{
    joint::joint(ledc_channel_t ch, ledc_timer_t tmr, int p) : channel(ch), timer(tmr), pin(p)
    {
        ledc_channel_config_t channel_conf = {
            .gpio_num = pin,
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .channel = channel,
            .timer_sel = timer,
            .duty = 0};
        ledc_channel_config(&channel_conf);
        move(default_position, channel);
    }

    void joint::move(int percent, ledc_channel_t ch)
    {
        int result;
        uint32_t duty;

        uint32_t max_duty = (1 << LEDC_RESOLUTION) - 1;

        if (percent != 0)
        {
            result = percent * total_angle / 100;
            duty = (angle_to_pulsewidth(result) * max_duty) / 20000;
        }
        else
        {
            duty = (angle_to_pulsewidth(1) * max_duty) / 20000;
        }

        ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, channel);
    }

    void joint::normal_delay()
    {
        vTaskDelay(pdMS_TO_TICKS(30));
    }

    uint32_t joint::angle_to_pulsewidth(int angle)
    {
        return DEFAULT_MIN_PULSEWIDTH + (angle * (DEFAULT_MAX_PULSEWIDTH - DEFAULT_MIN_PULSEWIDTH)) / 180;
    }

    // Getters
    ledc_channel_t joint::get_channel() const
    {
        return channel;
    }

    ledc_timer_t joint::get_timer() const
    {
        return timer;
    }

    int joint::get_pin() const
    {
        return pin;
    }

    int joint::get_total_angle() const
    {
        return total_angle;
    }

    int joint::get_default_position() const
    {
        return default_position;
    }

}
