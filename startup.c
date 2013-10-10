#include <stdint.h>

/* Addresses pulled in from the linker script */
extern uint32_t _end_stack;
extern uint32_t _end_text;
extern uint32_t _start_data;
extern uint32_t _end_data;
extern uint32_t _start_bss;
extern uint32_t _end_bss;

/* Application main() called in reset handler */
extern int main(void);

#define WEAK_ALIAS(x) __attribute__ ((weak, alias(#x)))

/* Cortex M0 core interrupt handlers */
void Reset_Handler(void);
void NMI_Handler(void) WEAK_ALIAS(Dummy_Handler);
void HardFault_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SVC_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PendSV_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SysTick_Handler(void) WEAK_ALIAS(Dummy_Handler);

/* LPC11xx specific interrupt handlers */
void WAKEUP0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WAKEUP1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WAKEUP2_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WAKEUP3_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WAKEUP4_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WAKEUP5_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WAKEUP6_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WAKEUP7_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WAKEUP8_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WAKEUP9_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WAKEUP10_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WAKEUP11_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WAKEUP12_Handler(void) WEAK_ALIAS(Dummy_Handler);
void CAN_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SSP1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void I2C_Handler(void) WEAK_ALIAS(Dummy_Handler);
void TIMER_16_0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void TIMER_16_1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void TIMER_32_0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void TIMER_32_1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SSP0_Handler(void) WEAK_ALIAS(Dummy_Handler);
void UART_Handler(void) WEAK_ALIAS(Dummy_Handler);
void ADC_Handler(void) WEAK_ALIAS(Dummy_Handler);
void WDT_Handler(void) WEAK_ALIAS(Dummy_Handler);
void BOD_Handler(void) WEAK_ALIAS(Dummy_Handler);
void EINT3_Handler(void) WEAK_ALIAS(Dummy_Handler);
void EINT2_Handler(void) WEAK_ALIAS(Dummy_Handler);
void EINT1_Handler(void) WEAK_ALIAS(Dummy_Handler);
void EINT0_Handler(void) WEAK_ALIAS(Dummy_Handler);

void Dummy_Handler(void);

/* Stack top and vector handler table */
void *vector_table[] __attribute__ ((section(".vectors"))) = {
	&_end_stack,
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	SVC_Handler,
	0,
	0,
	PendSV_Handler,
	SysTick_Handler,

	/* LPC11xx specific interrupt vectors */
    WAKEUP0_Handler,
    WAKEUP1_Handler,
    WAKEUP2_Handler,
    WAKEUP3_Handler,
    WAKEUP4_Handler,
    WAKEUP5_Handler,
    WAKEUP6_Handler,
    WAKEUP7_Handler,
    WAKEUP8_Handler,
    WAKEUP9_Handler,
    WAKEUP10_Handler,
    WAKEUP11_Handler,
    WAKEUP12_Handler,
    CAN_Handler,
    SSP1_Handler,
    I2C_Handler,
    TIMER_16_0_Handler,
    TIMER_16_1_Handler,
    TIMER_32_0_Handler,
    TIMER_32_1_Handler,
    SSP0_Handler,
    UART_Handler,
    Dummy_Handler,  /* Reserved */
    Dummy_Handler,  /* Reserved */
    ADC_Handler,
    WDT_Handler,
    BOD_Handler,
    Dummy_Handler,  /* Reserved */
    EINT3_Handler,
    EINT2_Handler,
    EINT1_Handler,
    EINT0_Handler,
};

void Reset_Handler(void) {
	uint32_t *src, *dst;

	/* Copy data section from flash to RAM */
	src = &_end_text;
	dst = &_start_data;
	while (dst < &_end_data)
		*dst++ = *src++;

	/* Clear the bss section */
	dst = &_start_bss;
	while (dst < &_end_bss)
		*dst++ = 0;

	main();
}

void Dummy_Handler(void) {
	while (1)
		;
}

