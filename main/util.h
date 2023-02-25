#ifndef ENCHESS_UTIL_H
#define ENCHESS_UTIL_H

#include <inttypes.h>
#include "driver/gpio.h"
#include "esp_timer.h"

#define pin_mode gpio_set_direction
#define digital_write gpio_set_level
static inline int64_t millis()
{
    return (unsigned long) (esp_timer_get_time() / 1000ULL);
}

#endif // ENCHESS_UTIL_H