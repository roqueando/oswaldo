#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "driver/ledc.h"

#include "esp_err.h"
//#include "Claw.hpp"

#define SERVO_GPIO 0
#define SERVO_MIN_PULSEWIDTH 500
#define SERVO_MAX_PULSEWIDTH 2500
#define SERVO_FREQUENCY 50
#define LEDC_RESOLUTION LEDC_TIMER_14_BIT

uint32_t angle_to_pulsewidth(int angle)
{
    return SERVO_MIN_PULSEWIDTH + (angle * (SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH)) / 180;
}

void move_servo(int angle)
{
    uint32_t max_duty = (1 << LEDC_RESOLUTION) - 1;
    uint32_t duty = (angle_to_pulsewidth(angle) * max_duty) / 20000;

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

void servo_task(void *pvParameters)
{
    while (true)
    {
        move_servo(0);
        vTaskDelay(pdMS_TO_TICKS(2000));

        move_servo(180);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main()
{
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_RESOLUTION,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = SERVO_FREQUENCY};
    ledc_timer_config(&timer_conf);

    ledc_channel_config_t channel_conf = {
        .gpio_num = SERVO_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0};
    ledc_channel_config(&channel_conf);

    while(true);
    //xTaskCreate(&servo_task, "servo_task", 2048, NULL, 5, NULL);
}
