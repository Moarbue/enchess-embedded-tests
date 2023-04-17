#ifndef ENCHESS_TMC2209_TEST_H
#define ENCHESS_TMC2209_TEST_H

#include "enchess_pinout.h"
#include "tmc2209.h"
#include "util.h"

#define TMC2209_STALLGUARD_THRS      90
#define TMC2209_PRINT_INTERVALL      1000

unsigned long tmc2209_last_printed;

tmc2209_t s_x, s_y;

static inline void tmc2209_test_setup(void)
{
    LOG_MSG("Setting up Stepper Driver's...");
    tmc2209_full(&s_x, ENCHESS_PIN_S1_EN, ENCHESS_PIN_S1_DIR, ENCHESS_PIN_S1_STEP,
                       ENCHESS_PIN_S_RX,  ENCHESS_PIN_S_TX,   ENCHESS_PIN_S1_MS1, ENCHESS_PIN_S1_MS2, TMC2209_ADDRESS_0, 0.11f);
    tmc2209_full(&s_y, ENCHESS_PIN_S2_EN, ENCHESS_PIN_S2_DIR, ENCHESS_PIN_S2_STEP,
                       ENCHESS_PIN_S_RX,  ENCHESS_PIN_S_TX,   ENCHESS_PIN_S2_MS1, ENCHESS_PIN_S2_MS2, TMC2209_ADDRESS_1, 0.11f);

    if (!tmc2209_check_connection(&s_x)) {
        LOG_MSG("Failed to setup UART communication with S1!");
        delay(500);
        abort();
    }
    LOG_MSG("Set up UART communication with S1!");
    if (!tmc2209_check_connection(&s_y)) {
        LOG_MSG("Failed to setup UART communication with S2!");
        delay(500);
        abort();
    }
    LOG_MSG("Set up UART communication with S2!");
    
    tmc2209_enable(&s_x);
    tmc2209_enable(&s_y);
    tmc2209_toff(&s_x, 4);
    tmc2209_blank_time(&s_x, 24);
    tmc2209_rms_current(&s_x, 1000);
    tmc2209_set_microsteps(&s_x, TMC2209_MICROSTEPS_64);
    tmc2209_tcoolthrs(&s_x, 0xFFFFF);
    tmc2209_semin(&s_x, 5);
    tmc2209_semax(&s_x, 2);
    tmc2209_sedn(&s_x, 0b01);
    tmc2209_stallguard_thrs(&s_x, TMC2209_STALLGUARD_THRS);
    tmc2209_toff(&s_y, 4);
    tmc2209_blank_time(&s_y, 24);
    tmc2209_rms_current(&s_y, 400);
    tmc2209_set_microsteps(&s_y, TMC2209_MICROSTEPS_16);
    tmc2209_tcoolthrs(&s_y, 0xFFFFF);
    tmc2209_semin(&s_y, 5);
    tmc2209_semax(&s_y, 2);
    tmc2209_sedn(&s_y, 0b01);
    tmc2209_stallguard_thrs(&s_y, TMC2209_STALLGUARD_THRS);

    tmc2209_set_rpm(&s_x, 60);
    tmc2209_set_rpm(&s_y, 60);
}

bool dir = false;
static inline void tmc2209_test_run(void)
{
    unsigned long mills = millis();

    tmc2209_rotate(&s_x, (dir ? 1 : -1) * 720);
    tmc2209_rotate(&s_y, (dir ? 1 : -1) * 720);

    if (mills - tmc2209_last_printed > TMC2209_PRINT_INTERVALL) {
        tmc2209_last_printed = mills;
        dir = !dir;

        LOG_MSG("X: %u / %u", tmc2209_stallguard_result(&s_x), TMC2209_STALLGUARD_THRS);
        LOG_MSG("Y: %u / %u", tmc2209_stallguard_result(&s_y), TMC2209_STALLGUARD_THRS);
        
        if (tmc2209_is_stalling(&s_x)) {
            LOG_MSG("X is stalling!");
        }
        if (tmc2209_is_stalling(&s_y)) {
            LOG_MSG("Y is stalling!");
        }
    }
}

#endif // ENCHESS_TMC2209_TEST_H