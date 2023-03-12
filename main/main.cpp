#include "Arduino.h"
#include "enchess_pinout.h"

#include "led_test.h"
#include "el_mag_test.h"
#include "tmc_test.h"
#include "tmc2209_test.h"


void setup()
{
    led_test_setup();
    el_mag_test_setup();
    tmc_test_setup();
    tmc2209_test_setup();
}

void loop()
{
    led_test_run();
    el_mag_test_run();
    tmc_test_run();
    tmc2209_test_run();
    delay(1);
}