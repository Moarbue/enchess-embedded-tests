#ifndef ENCHESS_TMC_TEST_H
#define ENCHESS_TMC_TEST_H

#include "enchess_pinout.h"
#include "util.h"

#define is_bit_set(value, bit) (((value) & (1 << bit)) ? HIGH : LOW)

#define TMC_INTERVAL 1000

static uint64_t tmc_last_queried;
static uint8_t tmc_index = 0;

static inline void tmc_test_setup(void)
{
    LOG_MSG("Setting up sensors...");
    pinMode(ENCHESS_PIN_TMC_0, OUTPUT);
    pinMode(ENCHESS_PIN_TMC_1, OUTPUT);
    pinMode(ENCHESS_PIN_TMC_2, OUTPUT);
    pinMode(ENCHESS_PIN_TMC_3, OUTPUT);
    pinMode(ENCHESS_PIN_TMC_4, OUTPUT);
    pinMode(ENCHESS_PIN_TMC_5, OUTPUT);

    tmc_last_queried = millis();
}

static inline void tmc_test_run(void)
{
    unsigned long mills = millis();

    if (mills - tmc_last_queried > TMC_INTERVAL) {
        tmc_last_queried = mills;

        digitalWrite(ENCHESS_PIN_TMC_0, is_bit_set(tmc_index, 0));
        digitalWrite(ENCHESS_PIN_TMC_1, is_bit_set(tmc_index, 1));
        digitalWrite(ENCHESS_PIN_TMC_2, is_bit_set(tmc_index, 2));
        digitalWrite(ENCHESS_PIN_TMC_3, is_bit_set(tmc_index, 3));
        digitalWrite(ENCHESS_PIN_TMC_4, is_bit_set(tmc_index, 4));
        digitalWrite(ENCHESS_PIN_TMC_5, is_bit_set(tmc_index, 5));

        LOG_MSG("Sensor %u = %s", tmc_index, digitalRead(ENCHESS_PIN_TMC_OUT) ? "EMPTY" : "OCCUPIED");

        tmc_index = tmc_index < 64 ? tmc_index + 1 : 0;
    }
}

#endif // ENCHESS_TMC_TEST_H