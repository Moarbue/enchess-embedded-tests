#ifndef ENCHESS_EL_MAG_TEST_H
#define ENCHESS_EL_MAG_TEST_H

#include "enchess_pinout.h" 
#include "util.h"

#define EL_MAG_BLINK_INTERVAL 2000
static unsigned long el_mag_last_blinked;
static uint8_t el_mag_state = 0;

static inline void el_mag_test_setup(void)
{
    LOG_MSG("Setting up electromagnet...");
    pinMode(ENCHESS_PIN_EL_MAG, OUTPUT);
    el_mag_last_blinked = millis();
}

static inline void el_mag_test_run(void)
{
    unsigned long mills = millis();

    if (mills - el_mag_last_blinked > EL_MAG_BLINK_INTERVAL) {
        el_mag_last_blinked = mills;
        digitalWrite(ENCHESS_PIN_EL_MAG, el_mag_state);
        el_mag_state = !el_mag_state;
    }
}

#endif // ENCHESS_EL_MAG_TEST_H