#ifndef __SYNTH_CORE_H__
#define __SYNTH_CORE_H__

#include <stdint.h>

#define POLY_NUM 5

typedef struct _SoundUnit
{
	uint16_t increment;
	uint8_t  wavetablePos_frac;
	uint16_t  wavetablePos_int;
	uint8_t envelopeLevel;
	uint8_t envelopePos;
	int16_t val;
} SoundUnit;

typedef struct _SoundUnitSplit
{
	uint16_t increment;
	uint8_t increment_frac;
	uint8_t increment_int;
	uint8_t  wavetablePos_frac;
	uint16_t  wavetablePos_int;
	uint8_t envelopeLevel;
	uint8_t envelopePos;
	int16_t val;
} SoundUnitSplit;


typedef union _SoundUnitUnion
{
	SoundUnit combine;
	SoundUnitSplit split; 
}SoundUnitUnion;


typedef struct _Synthesizer
{
    SoundUnitUnion SoundUnitUnionList[POLY_NUM];
    uint8_t lastSoundUnit;
}Synthesizer;

extern int16_t mixOutAsm;
extern int16_t mixOutC;
extern uint16_t asmSoundListAddress;

void SynthInit(Synthesizer* synth,uint8_t isUseAsmSynth);
void NoteOn(Synthesizer* synth,uint8_t note);
void SynthC(Synthesizer* synth);
void GenDecayEnvlope(Synthesizer* synth);


#endif