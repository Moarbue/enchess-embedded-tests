#ifndef ENCHESS_TMC2209_TEST_H
#define ENCHESS_TMC2209_TEST_H

#include "enchess_pinout.h"
#include "TMC2209.h"

#define TMC2209_BAUDRATE             115200
#define TMC2209_RUN_CURRENT          50
#define TMC2209_HOLD_CURRENT         10
#define TMC2209_HOLD_DELAY           0
#define TMC2209_VELOCITY             20000
#define TMC2209_STALLGUARD_THRESHOLD 50

TMC2209 s1;
TMC2209 s2;

static inline void tmc2209_test_setup()
{
    pinMode(ENCHESS_PIN_S1_EN,   GPIO_MODE_OUTPUT);
    pinMode(ENCHESS_PIN_S1_MS1,  GPIO_MODE_OUTPUT);
    pinMode(ENCHESS_PIN_S1_MS2,  GPIO_MODE_OUTPUT);
    pinMode(ENCHESS_PIN_S1_DIR,  GPIO_MODE_OUTPUT);
    pinMode(ENCHESS_PIN_S1_STEP, GPIO_MODE_OUTPUT);

    pinMode(ENCHESS_PIN_S2_EN,   GPIO_MODE_OUTPUT);
    pinMode(ENCHESS_PIN_S2_MS1,  GPIO_MODE_OUTPUT);
    pinMode(ENCHESS_PIN_S2_MS2,  GPIO_MODE_OUTPUT);
    pinMode(ENCHESS_PIN_S2_DIR,  GPIO_MODE_OUTPUT);
    pinMode(ENCHESS_PIN_S2_STEP, GPIO_MODE_OUTPUT);
    
    pinMode(ENCHESS_PIN_S_CLK,   GPIO_MODE_OUTPUT);
    
    digitalWrite(ENCHESS_PIN_S1_EN,  LOW);
    digitalWrite(ENCHESS_PIN_S1_MS1, LOW);
    digitalWrite(ENCHESS_PIN_S1_MS2, LOW);

    digitalWrite(ENCHESS_PIN_S2_EN,  LOW);
    digitalWrite(ENCHESS_PIN_S2_MS1, HIGH);
    digitalWrite(ENCHESS_PIN_S2_MS2, LOW);

    s1.setup(Serial1, 115200, TMC2209::SERIAL_ADDRESS_0);
    if (!s1.isSetupAndCommunicating()) {
        return;
    }
    s1.setRunCurrent(TMC2209_RUN_CURRENT);
    s1.setHoldCurrent(TMC2209_HOLD_CURRENT);
    s1.setHoldDelay(TMC2209_HOLD_DELAY);
    s1.enableAutomaticGradientAdaptation();
    s1.setStallGuardThreshold(TMC2209_STALLGUARD_THRESHOLD);
    s1.enableCoolStep();
    s1.enable();

    s1.moveAtVelocity(TMC2209_VELOCITY);
}

static inline void tmc2209_test_run()
{
}

#endif // ENCHESS_TMC2209_TEST_H