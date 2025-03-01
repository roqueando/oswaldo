
#include "Claw.hpp"
static const uint32_t SERVO_FREQUENCY = 50;

Claw::Claw(int servo_pin, int min_pulse, int max_pulse) : pin(servo_pin), min_pulsewidth(min_pulse), max_pulsewidth(max_pulse)
{
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_6_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = SERVO_FREQUENCY};
    ledc_timer_config(&timer_conf);

    ledc_channel_config_t channel_conf = {
        .gpio_num = pin,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0};
    ledc_channel_config(&channel_conf);

    xTaskCreate(&taskFunction, "claw_task", 2048, this, 5, NULL);
}

void Claw::move(int angle)
{
    uint32_t pulse_width = min_pulsewidth + ((max_pulsewidth - min_pulsewidth) * angle / 180);
    uint32_t duty = (pulse_width * 65535) / 20000;

    printf("moving angle %d with duty %lu\n", angle, duty);
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

void Claw::open()
{
    printf("opening claw...\n");
    move(45);
}

void Claw::close()
{
    printf("closing claw...\n");
    move(135);
}

void Claw::open_close_for_2_seconds(void *pvParameters)
{
    while (true)
    {
        open();
        vTaskDelay(pdMS_TO_TICKS(2000));

        close();
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
void Claw::taskFunction(void *pvParameters)
{
    Claw *clawInstance = static_cast<Claw *>(pvParameters);

    // TODO: here will be something to do with claw
    // for now, is just opening and closing
    while (true)
    {
        clawInstance->open();
        vTaskDelay(pdMS_TO_TICKS(2000));

        clawInstance->close();
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
