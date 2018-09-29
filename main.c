#include <stdint.h>
#include <stm8s.h>
#include <delay.h>

#define OUTPUT_PIN 3

extern uint16_t PitchIncrementTable[];
extern uint8_t EnvelopeTable[256];
extern int8_t WaveTable[];
typedef struct _SoundUnit
{
	uint16_t wavetablePos;
	uint8_t envelopePos;
	uint8_t pitch;

} SoundUnit;

uint16_t globalTimer = 0;

#define POLY_NUM 5

SoundUnit Sounds[POLY_NUM];

#define WAVETABLE_ATTACK_LEN 1630
#define WAVETABLE_LEN 1758
#define WAVETABLE_LOOP_LEN (WAVETABLE_LEN - WAVETABLE_ATTACK_LEN)

uint8_t playstatus=0;


void Play()
{
	if(playstatus==0)
	{
		playstatus=1;

	}
}

void NoteOn(uint8_t note)
{

}

void GenDecayEnvlope()
{
	static uint8_t TimeCnt=0;
	if(TimeCnt!=255)
		TimeCnt++;
	else
	{
		TimeCnt=0;
		for (uint8_t i = 0; i < POLY_NUM; i++)
		{
			if (Sounds[i].wavetablePos >= WAVETABLE_ATTACK_LEN &&
				Sounds[i].wavetablePos < sizeof(EnvelopeTable) - 1)
			{
				Sounds[i].envelopePos += 1;
			}
		}
	}
}

void Synth(void)
{
	int16_t rawMixOut = 0;
	for (uint8_t i = 0; i < POLY_NUM; i++)
	{
		Sounds[i].wavetablePos += PitchIncrementTable[Sounds[i].pitch];
		if (Sounds[i].wavetablePos >= WAVETABLE_LEN)
		{
			Sounds[i].wavetablePos -= WAVETABLE_LOOP_LEN;
		}
		rawMixOut += EnvelopeTable[Sounds[i].envelopePos] * WaveTable[Sounds[i].wavetablePos];
	}
}

void timer_isr() __interrupt(TIM4_ISR)
{
	PD_ODR ^= (1 << OUTPUT_PIN);
	TIM4_SR &= ~(1 << TIM4_SR_UIF);
	Synth();
	GenDecayEnvlope();
}

void main()
{

 	CLK_CKDIVR=0x00;

	enable_interrupts();



	/* Set PD3 as output */
	PD_DDR |= (1 << OUTPUT_PIN);
	PD_CR1 |= (1 << OUTPUT_PIN);

	/* Prescaler = 4 */
	TIM4_PSCR = 0b00000010;

	/* Frequency = F_CLK / (2 * prescaler * (1 + ARR))
     *           = 16 MHz / (2 * 4 * (1 + 124)) = 32000 Hz */
	TIM4_ARR = 124;

	TIM4_IER |= (1 << TIM4_IER_UIE); // Enable Update Interrupt
	TIM4_CR1 |= (1 << TIM4_CR1_CEN); // Enable TIM4

	while (1)
	{
		// do nothing
	}
}
