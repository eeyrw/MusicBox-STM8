#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stm8s.h>
#include <uart.h>
#include <delay.h>
#include "Player.h"

#define OUTPUT_PIN 5

#define MEASURE_S PB_ODR |= (1 << OUTPUT_PIN)
#define MEASURE_E PB_ODR &= ~(1 << OUTPUT_PIN)

extern void TestProcess(void);

Player mainPlayer;

void timer_isr() __interrupt(TIM4_ISR)
{
	TIM4_SR &= ~(1 << TIM4_SR_UIF);
	MEASURE_S;
	Player32kProc(&mainPlayer);
	MEASURE_E;
}

void HardwareInit(void)
{
	CLK_CKDIVR = 0x00;
	uart_init();
	enable_interrupts();

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


   TIM2_CCMR3 |=   0X70;   //设置定时器2三通道(PD2)输出比较三模式
    TIM2_CCMR3 |= 0X04;     //输出比较3预装载使能


   TIM2_CCMR2 |=   0X70;   //设置定时器2二通道(PD3)输出比较三模式
    TIM2_CCMR2 |= 0X04;     //输出比较3预装载使能


    TIM2_CCER1 |= (0x03<<4);     //通道2使能，低电平有效，配置为输出
	TIM2_CCER2 |= 0x03;     //通道3使能，低电平有效，配置为输出

    //初始化时钟分频器为1，即计数器的时钟频率为Fmaster=8M/64=0.125MHZ
    TIM2_PSCR = 0X00;   
    //初始化自动装载寄存器，决定PWM 方波的频率，Fpwm=0.125M/62500=2HZ
    TIM2_ARRH = 0;
    TIM2_ARRL = 0xFF;
    //初始化比较寄存器，决定PWM 方波的占空比：5000/10000 = 50%
    TIM2_CCR3H = 0;
    TIM2_CCR3L = 122;
    TIM2_CCR2H = 0;
    TIM2_CCR2L = 123;

    // 启动计数;更新中断失能

    TIM2_IER = 0x00; 
	TIM2_CR1 |= 0x81;
/*设置为推挽输出,PD2接了LED灯*/

    PA_DDR |= 0X08;             //设置PA3端口为输出模式
    PA_CR1 |= 0X08;             //设置PA3端口为推挽输出模式
    //PA_CR2 |= 0XF7;

	PD_DDR |=(1<<2|1<<3);
	PD_CR1 |=(1<<2|1<<3);
	
}

void main()
{

	PlayerInit(&mainPlayer);
	HardwareInit();
	//TestProcess();
	PlayerPlay(&mainPlayer);

	while (1)
	{
		for (uint8_t i = 0; i < 56; i++)
		{
			//NoteOn(&(mainPlayer.mainSynthesizer),i);
			//delay_ms(20);
		}
		PlayerProcess(&mainPlayer);
	}
}
