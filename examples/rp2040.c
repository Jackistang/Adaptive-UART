#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "abr.h"

#include <stdio.h>
#include <assert.h>

#define RP2040_UART_RX  5

uint32_t abr_soft_get_timestamp(void)
{
    return time_us_32();
}

static void (*g_abr_irq_handler)(void);
static void rp2040_gpio_irq_callback(uint gpio, uint32_t events)
{
    g_abr_irq_handler();
}

void abr_soft_pin_irq_rising(void (*irq_handler)(void))
{
    gpio_pull_up(RP2040_UART_RX);
    gpio_set_irq_enabled_with_callback(RP2040_UART_RX, GPIO_IRQ_EDGE_RISE, true, rp2040_gpio_irq_callback);
    g_abr_irq_handler = irq_handler;
}

int main(void)
{
    stdio_init_all();
    abr_init();

    printf("rp2040 example start\n");

    while (1) {
        uint32_t baudrate = abr_get_baudrate();
        printf("Baudrate: %d\n", baudrate);
    }
}