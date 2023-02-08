#ifndef ENCHESS_EL_MAG_TEST_H
#define ENCHESS_EL_MAG_TEST_H

#include "enchess_pinout.h" 
#include "util.h"

#define EL_MAG_BLINK_INTERVAL 2000
static int64_t el_mag_last_blinked;
static uint8_t el_mag_state = 0;

static inline void el_mag_test_setup(int64_t mills)
{
    pin_mode(ENCHESS_PIN_EL_MAG, GPIO_MODE_OUTPUT);
    el_mag_last_blinked = mills;
}

static inline void el_mag_test_run(int64_t mills)
{
    if (mills - el_mag_last_blinked > EL_MAG_BLINK_INTERVAL) {
        el_mag_last_blinked = mills;
        digital_write(ENCHESS_PIN_EL_MAG, el_mag_state);
        el_mag_state = !el_mag_state;
    }
}

#endif // ENCHESS_EL_MAG_TEST_H