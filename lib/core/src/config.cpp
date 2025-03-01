#include "config.hpp"
#include "driver/ledc.h"

void oswaldo_init()
{
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_RESOLUTION,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = SERVO_FREQUENCY};
    ledc_timer_config(&timer_conf);
}

uint32_t angle_to_pulsewidth(int angle)
{
    return DEFAUL_MIN_PULSEWIDTH + (angle * (DEFAULT_MAX_PULSEWIDTH - DEFAULT_MIN_PULSEWIDTH)) / 180;
}
