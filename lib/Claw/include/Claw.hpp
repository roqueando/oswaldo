#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include <stdio.h>

class Claw
{
private:
    int pin;
    int min_pulsewidth;
    int max_pulsewidth;
    TaskHandle_t clawTaskHandle;
    static void taskFunction(void *pvParameters);

public:
    Claw(int servo_pin, int min_pulse = 500, int max_pulse = 2500);
    void open();
    void close();
    void move(int angle);
};
