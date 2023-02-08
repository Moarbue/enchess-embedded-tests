#ifndef ENCHESS_UTIL_H
#define ENCHESS_UTIL_H

#include <inttypes.h>
#include "driver/gpio.h"
#include <sys/time.h>

#define pin_mode(pin, direction) ESP_ERROR_CHECK(gpio_set_direction(pin, direction))
#define digital_write(pin, value) ESP_ERROR_CHECK(gpio_set_level(pin, value))

static inline int64_t millis()
{
    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    return (int64_t)tv_now.tv_sec * 1000000L + (int64_t)tv_now.tv_usec;
}

#endif // ENCHESS_UTIL_H