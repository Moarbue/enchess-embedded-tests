#ifndef ENCHESS_TMC2209_TEST_H
#define ENCHESS_TMC2209_TEST_H

#include "enchess_pinout.h"
#include "TMCStepper.h"
#include "util.h"

#define TMC2209_BAUDRATE             115200
#define TMC2209_DRIVER_ADDRESS1      0b00 
#define TMC2209_R_SENSE              0.11f
#define TMC2209_MAX_STEPS            5000

HardwareSerial stepper_serial(1);
TMC2209Stepper s1(&stepper_serial, TMC2209_R_SENSE, TMC2209_DRIVER_ADDRESS1);

bool shaft = false;
uint16_t step = 0;

static inline void tmc2209_test_setup(void)
{
    LOG_MSG("Setting up Stepper Driver's...");
    pinMode(ENCHESS_PIN_S1_EN,   OUTPUT);
    pinMode(ENCHESS_PIN_S1_MS1,  OUTPUT);
    pinMode(ENCHESS_PIN_S1_MS2,  OUTPUT);
    pinMode(ENCHESS_PIN_S1_DIR,  OUTPUT);
    pinMode(ENCHESS_PIN_S1_STEP, OUTPUT);

    pinMode(ENCHESS_PIN_S2_EN,   OUTPUT);
    pinMode(ENCHESS_PIN_S2_MS1,  OUTPUT);
    pinMode(ENCHESS_PIN_S2_MS2,  OUTPUT);
    pinMode(ENCHESS_PIN_S2_DIR,  OUTPUT);
    pinMode(ENCHESS_PIN_S2_STEP, OUTPUT);
    
    pinMode(ENCHESS_PIN_S_CLK,   OUTPUT);
    
    digitalWrite(ENCHESS_PIN_S1_EN,  LOW);
    digitalWrite(ENCHESS_PIN_S1_MS1, LOW);
    digitalWrite(ENCHESS_PIN_S1_MS2, LOW);

    digitalWrite(ENCHESS_PIN_S2_EN,  LOW);
    digitalWrite(ENCHESS_PIN_S2_MS1, HIGH);
    digitalWrite(ENCHESS_PIN_S2_MS2, LOW);

    stepper_serial.begin(115200, SERIAL_8N1, ENCHESS_PIN_S_RX, ENCHESS_PIN_S_TX);

    s1.begin();
    s1.toff(5);
    s1.rms_current(600);
    s1.microsteps(16);
    s1.pwm_autoscale(true);
}

static inline void tmc2209_test_run(void)
{
    if (step++ < TMC2209_MAX_STEPS) {
        digitalWrite(ENCHESS_PIN_S1_STEP, HIGH);
        delayMicroseconds(160);
        digitalWrite(ENCHESS_PIN_S1_STEP, LOW);
        delayMicroseconds(160);
    } else {
        shaft = !shaft;
        s1.shaft(shaft);
        step = 0;
    }
}

#endif // ENCHESS_TMC2209_TEST_H