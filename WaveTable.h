#ifndef __WAVETABLE__
#define __WAVETABLE__
// Sample name: Xylophone C5
// Sample's base frequency: 522.0361701697199 Hz
// Sample's sample rate: 32000 Hz

#include <stdint.h>

extern const uint16_t WAVETABLE_LEN;
extern const uint16_t WAVETABLE_ATTACK_LEN;
extern const uint16_t WAVETABLE_LOOP_LEN;

extern const int8_t WaveTable[];
extern const uint16_t WaveTable_Increment[];

#endif