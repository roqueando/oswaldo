#pragma once

#define DEFAULT_MOTOR_FREQUENCY 50
#define DEFAULT_MIN_PULSEWIDTH 500
#define DEFAULT_MAX_PULSEWIDTH 2500
#define LEDC_RESOLUTION LEDC_TIMER_14_BIT

void oswaldo_init();
uint32_t angle_to_pulsewidth(int angle);
void move(double percent);
