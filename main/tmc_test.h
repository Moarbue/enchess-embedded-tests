#ifndef ENCHESS_TMC_TEST_H
#define ENCHESS_TMC_TEST_H

#include "enchess_pinout.h"
#include "util.h"

#define is_bit_set(value, bit) (((value) & (1 << bit)) >> bit)

#define TMC_INTERVAL 300

static int64_t tmc_last_queried;
static uint8_t tmc_index = 0;

static inline void tmc_test_setup(int64_t mills)
{
    pin_mode(ENCHESS_PIN_TMC_0, GPIO_MODE_OUTPUT);
    pin_mode(ENCHESS_PIN_TMC_1, GPIO_MODE_OUTPUT);
    pin_mode(ENCHESS_PIN_TMC_2, GPIO_MODE_OUTPUT);
    pin_mode(ENCHESS_PIN_TMC_3, GPIO_MODE_OUTPUT);
    pin_mode(ENCHESS_PIN_TMC_4, GPIO_MODE_OUTPUT);
    pin_mode(ENCHESS_PIN_TMC_5, GPIO_MODE_OUTPUT);

    tmc_last_queried = mills;
}

static inline void tmc_test_run(int64_t mills)
{
    if (mills - tmc_last_queried > TMC_INTERVAL) {
        tmc_last_queried = mills;

        digital_write(ENCHESS_PIN_TMC_0, is_bit_set(tmc_index, 0));
        digital_write(ENCHESS_PIN_TMC_1, is_bit_set(tmc_index, 1));
        digital_write(ENCHESS_PIN_TMC_2, is_bit_set(tmc_index, 2));
        digital_write(ENCHESS_PIN_TMC_3, is_bit_set(tmc_index, 3));
        digital_write(ENCHESS_PIN_TMC_4, is_bit_set(tmc_index, 4));
        digital_write(ENCHESS_PIN_TMC_5, is_bit_set(tmc_index, 5));

        tmc_index++;
    }
}

#endif // ENCHESS_TMC_TEST_H