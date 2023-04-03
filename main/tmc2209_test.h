#ifndef ENCHESS_TMC2209_TEST_H
#define ENCHESS_TMC2209_TEST_H

#include "enchess_pinout.h"
#include "tmc2209.h"
#include "util.h"

#define TMC2209_STALLGUARD_THRS      100
#define TMC2209_PRINT_INTERVALL      100

unsigned long tmc2209_last_printed;

tmc2209_t s_x, s_y;

static inline void tmc2209_test_setup(void)
{
    LOG_MSG("Setting up Stepper Driver's...\r\n");
    tmc2209_full(&s_x, ENCHESS_PIN_S1_EN, ENCHESS_PIN_S1_DIR, ENCHESS_PIN_S1_STEP,
                       ENCHESS_PIN_S_RX,  ENCHESS_PIN_S_TX,   ENCHESS_PIN_S1_MS1, ENCHESS_PIN_S1_MS2, TMC2209_ADDRESS_0);
    tmc2209_full(&s_y, ENCHESS_PIN_S2_EN, ENCHESS_PIN_S2_DIR, ENCHESS_PIN_S2_STEP,
                       ENCHESS_PIN_S_RX,  ENCHESS_PIN_S_TX,   ENCHESS_PIN_S2_MS2, ENCHESS_PIN_S2_MS2, TMC2209_ADDRESS_1);

    while(!tmc2209_check_connection(&s_x) && !tmc2209_check_connection(&s_y)) {
        LOG_MSG("Failed setting up UART communication with drivers!");
    }
    
    tmc2209_stallguard_thrs(&s_x, TMC2209_STALLGUARD_THRS);
    tmc2209_stallguard_thrs(&s_y, TMC2209_STALLGUARD_THRS);
}

static inline void tmc2209_test_run(void)
{
    tmc2209_update(&s_x);
    tmc2209_update(&s_y);

    tmc2209_rotate(&s_x, 360);
    tmc2209_rotate(&s_y, 360);

    unsigned long mills = millis();

    if (mills - tmc2209_last_printed > TMC2209_PRINT_INTERVALL) {
        tmc2209_last_printed = mills;

        if (tmc2209_is_stalling(&s_x)) {
            tmc2209_step_reset(&s_x);
            LOG_MSG("X is stalling!");
        }
        if (tmc2209_is_stalling(&s_y)) {
            tmc2209_step_reset(&s_y);
            LOG_MSG("Y is stalling!");
        }
    }
}

#endif // ENCHESS_TMC2209_TEST_H