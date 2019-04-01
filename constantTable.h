#ifndef __CONSTANT_TABLE_H__
#define __CONSTANT_TABLE_H__

#include <stdint.h>

#define WAVETABLE_ATTACK_LEN 1630
#define WAVETABLE_LEN 1758
#define WAVETABLE_LOOP_LEN (WAVETABLE_LEN - WAVETABLE_ATTACK_LEN)

extern uint16_t PitchIncrementTable[];
extern uint8_t EnvelopeTable[256];
extern int8_t WaveTable[];

#endif