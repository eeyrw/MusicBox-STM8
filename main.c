#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stm8s.h>
#include <uart.h>
#include <delay.h>
#include "Player.h"

#define RUN_FUNC_MAX_SIZE_256

#define OUTPUT_PIN 5

#define MEASURE_S PB_ODR |= (1 << OUTPUT_PIN)
#define MEASURE_E PB_ODR &= ~(1 << OUTPUT_PIN)

extern void TestProcess(void);
extern const unsigned char Score[];

Player mainPlayer;
extern void timer_isr() __interrupt(TIM4_ISR);

// void timer4_isr() __interrupt(TIM4_ISR)
// {
// 	TIM4_SR &= ~(1 << TIM4_SR_UIF);
// 	MEASURE_S;
// 	//Player32kProc(&mainPlayer);
// 	MEASURE_E;
// }

void uart1_isr() __interrupt(UART1_RXC_ISR)
{
	NoteOnAsm(UART1_DR & 0b00111111);
}

void HardwareInit(void)
{
	CLK_CKDIVR = 0x00;
	uart_init();
	UART1_CR2 |= (1 << 5);
	/* Set PD3 as output */
	PB_DDR |= (1 << OUTPUT_PIN);
	PB_CR1 |= (1 << OUTPUT_PIN);

	PC_DDR |= (1 << 4);
	PC_CR1 |= (1 << 4);

	/* Prescaler = 4 */
	TIM4_PSCR = 0b00000010;

	/* Frequency = F_CLK / (2 * prescaler * (1 + ARR))
     *           = 16 MHz / (2 * 4 * (1 + 124)) = 32000 Hz */
	TIM4_ARR = 124;
	TIM4_IER |= (1 << TIM4_IER_UIE); // Enable Update Interrupt
	TIM4_CR1 |= (1 << TIM4_CR1_CEN); // Enable TIM4

	TIM2_CCMR3 |= 0X70; //设置定时器2三通道(PD2)输出比较三模式
	TIM2_CCMR3 |= 0X04; //输出比较3预装载使能

	TIM2_CCMR2 |= 0X70; //设置定时器2二通道(PD3)输出比较三模式
	TIM2_CCMR2 |= 0X04; //输出比较3预装载使能

	TIM2_CCER1 |= (0x03 << 4); //通道2使能，低电平有效，配置为输出
	TIM2_CCER2 |= 0x03;		   //通道3使能，低电平有效，配置为输出

	// Set TIM2 prescaler value to 1
	TIM2_PSCR = 0X00;
	// Initialization of auto-reload register
	TIM2_ARRH = 0;
	TIM2_ARRL = 0xFF;
	// Set comparison register of TIM2
	TIM2_CCR3H = 0;
	TIM2_CCR3L = 122;
	TIM2_CCR2H = 0;
	TIM2_CCR2L = 123;

	// Enable TIM2 and disable interrupt of TIM2

	TIM2_IER = 0x00;
	TIM2_CR1 |= 0x81;

	PD_DDR |= (1 << 2 | 1 << 3);
	PD_CR1 |= (1 << 2 | 1 << 3);
	enable_interrupts();
}

// #ifdef RUN_FUNC_MAX_SIZE_256
// uint8_t f_ram[256];
// volatile uint8_t RAM_SEG_LEN;
// inline void get_ram_section_length() {
    // __asm__("mov _RAM_SEG_LEN, #l_RAM_SEG");
// }
// #else
// uint8_t f_ram[512];
// volatile uint16_t RAM_SEG_LEN;
// inline void get_ram_section_length() {
    // __asm
        // pushw x
        // ldw x, #l_RAM_SEG
        // ldw _RAM_SEG_LEN, x
        // popw x
    // __endasm;
// }
// #endif


// void ram_cpy() {
    // get_ram_section_length();
    // for (uint8_t i = 0; i < RAM_SEG_LEN; i++)
        // f_ram[i] = ((uint8_t *) SynthAsm)[i];
    // ram_SynthAsm = (void (*)(const char *)) &f_ram;
// }

void main()
{
	//ram_cpy();
	PlayerInit(&mainPlayer,&synthForAsm);
	HardwareInit();
#ifndef RUN_TEST
	PlayerPlay(&mainPlayer,Score);
#else
	TestProcess();
#endif

	while (1)
	{
		PlayerProcess(&mainPlayer);
	}
}
