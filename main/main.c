#include "enchess_pinout.h"
#include "util.h"

#include "led_test.h"
#include "el_mag_test.h"

static int64_t mills;

void app_main(void)
{
    mills = millis();

    led_test_setup(mills);
    el_mag_test_setup(mills);

    while(1) {
        mills = millis();

        led_test_run(mills);
        el_mag_test_run(mills);
    }
}