#ifndef ABR
#define ABR

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void abr_init(void);
extern uint32_t abr_get_baudrate(void);

extern uint32_t abr_soft_get_timestamp(void);
extern void abr_soft_pin_irq_rising(void (*irq_handler)(void));

#ifdef __cplusplus
}
#endif

#endif /* ABR */
