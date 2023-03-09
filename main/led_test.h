#ifndef ENCHESS_LED_TEST_H
#define ENCHESS_LED_TEST_H

#include "enchess_pinout.h" 
#include "util.h"

#define LED1_BLINK_INTERVAL 1000
#define LED2_BLINK_INTERVAL 800
#define LED3_BLINK_INTERVAL 600
static unsigned long led1_last_blinked;
static unsigned long led2_last_blinked;
static unsigned long led3_last_blinked;
static uint8_t led1_state = 0;
static uint8_t led2_state = 0;
static uint8_t led3_state = 0;

static inline void led_test_setup(void)
{
    LOG_MSG("Setting up LED's...");
    pinMode(ENCHESS_PIN_LED1, OUTPUT);
    pinMode(ENCHESS_PIN_LED2, OUTPUT);
    pinMode(ENCHESS_PIN_LED3, OUTPUT);

    led1_last_blinked = led2_last_blinked = led3_last_blinked = millis();
}

static inline void led_test_run(void)
{
    unsigned long mills = millis();

    if (mills - led1_last_blinked > LED1_BLINK_INTERVAL) {
        led1_last_blinked = mills;
        digitalWrite(ENCHESS_PIN_LED1, led1_state);
        led1_state = !led1_state;
    }
    if (mills - led2_last_blinked > LED2_BLINK_INTERVAL) {
        led2_last_blinked = mills;
        digitalWrite(ENCHESS_PIN_LED2, led2_state);
        led2_state = !led2_state;
    }
    if (mills - led3_last_blinked > LED3_BLINK_INTERVAL) {
        led3_last_blinked = mills;
        digitalWrite(ENCHESS_PIN_LED3, led3_state);
        led3_state = !led3_state;
    }
}

#endif // ENCHESS_LED_TEST_H