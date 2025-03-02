#include "config.hpp"
#include "driver/ledc.h"

void oswaldo_init()
{
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_RESOLUTION,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = DEFAULT_MOTOR_FREQUENCY};
    ledc_timer_config(&timer_conf);
}

uint32_t angle_to_pulsewidth(int angle)
{
    return DEFAULT_MIN_PULSEWIDTH + (angle * (DEFAULT_MAX_PULSEWIDTH - DEFAULT_MIN_PULSEWIDTH)) / 180;
}

void move(int percent, ledc_channel_t channel, int total_angle)
{
    uint32_t max_duty = (1 << LEDC_RESOLUTION) - 1;
    int result;
    uint32_t duty;

    if (percent != 0) {
        result = percent * total_angle / 100;
        duty = (angle_to_pulsewidth(result) * max_duty) / 20000;
    } else {
        duty = (angle_to_pulsewidth(1) * max_duty) / 20000;
    }

    ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, channel);
}

