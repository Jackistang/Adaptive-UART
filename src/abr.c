#include "abr.h"
#include <stdio.h>

volatile static uint8_t irq_flag = 0;
volatile static uint32_t g_start_us = 0;
volatile static uint32_t g_delta_us = 0;

static void abr_soft_pin_irq_handler(void)
{
    if (irq_flag == 0) {
        g_start_us = abr_soft_get_timestamp();
        irq_flag = 1;
        // printf("start_us: %u, ", g_start_us);
    } else {
        g_delta_us = abr_soft_get_timestamp() - g_start_us;
        irq_flag = 0;
        // printf("delta_us: %u\n", g_delta_us);
    }
}

void abr_init(void)
{
    abr_soft_pin_irq_rising(abr_soft_pin_irq_handler);
}


uint32_t abr_get_baudrate(void)
{
    uint32_t baudrate = 0;

    /* Wait for irq. */
    while (g_delta_us == 0) ;
    
    baudrate = 1000000 / (g_delta_us / 8.0);

    /* Clear status */
    g_start_us = g_delta_us = 0;

    return baudrate;
}