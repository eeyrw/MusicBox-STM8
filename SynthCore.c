#include "SynthCore.h"
#include <stdint.h>
#include <stdio.h>
#include "constantTable.h"

int16_t mixOutAsm;
int16_t mixOutC;
uint16_t asmSoundListAddress;

void SynthInit(Synthesizer* synth,uint8_t isUseAsmSynth)
{
    SoundUnitUnion* soundUnionList=&(synth->SoundUnitUnionList[0]);
	for (uint8_t i = 0; i < POLY_NUM; i++)
	{
		soundUnionList[i].combine.increment = 0;
		soundUnionList[i].combine.wavetablePos_frac = 0;
		soundUnionList[i].combine.wavetablePos_int = 0;
		soundUnionList[i].combine.envelopeLevel = 255;
		soundUnionList[i].combine.envelopePos = 0;
        soundUnionList[i].combine.val = 0;
	}
    synth->lastSoundUnit=0;

    if(isUseAsmSynth!=0)
        asmSoundListAddress=(uint16_t)soundUnionList;
}

void NoteOn(Synthesizer* synth,uint8_t note)
{
	uint8_t lastSoundUnit = synth->lastSoundUnit;

	synth->SoundUnitUnionList[lastSoundUnit].combine.increment = PitchIncrementTable[note];
	synth->SoundUnitUnionList[lastSoundUnit].combine.wavetablePos_frac = 0;
	synth->SoundUnitUnionList[lastSoundUnit].combine.wavetablePos_int = 0;
	synth->SoundUnitUnionList[lastSoundUnit].combine.envelopePos = 0;
	synth->SoundUnitUnionList[lastSoundUnit].combine.envelopeLevel = 255;

	if (lastSoundUnit + 1 == POLY_NUM)
		lastSoundUnit = 0;
	else
		lastSoundUnit++;

    synth->lastSoundUnit=lastSoundUnit;
}

void SynthC(Synthesizer* synth)
{
    mixOutC=0;
    SoundUnitUnion* soundUnionList=&(synth->SoundUnitUnionList[0]);
    for(uint8_t i=0;i<POLY_NUM;i++)
    {
        soundUnionList[i].combine.val=soundUnionList[i].combine.envelopeLevel*WaveTable[soundUnionList[i].combine.wavetablePos_int]/255;
        soundUnionList[i].combine.sampleVal=WaveTable[soundUnionList[i].combine.wavetablePos_int];
		uint32_t waveTablePos=soundUnionList[i].combine.increment+
                             soundUnionList[i].combine.wavetablePos_frac+
                             ((uint32_t)soundUnionList[i].combine.wavetablePos_int<<8); 

        uint16_t waveTablePosInt= waveTablePos>>8;
        if(waveTablePosInt>WAVETABLE_LEN)
           waveTablePosInt-=WAVETABLE_LOOP_LEN;
        soundUnionList[i].combine.wavetablePos_int= waveTablePosInt;
        soundUnionList[i].combine.wavetablePos_frac=0xFF&waveTablePos;
        mixOutC+=soundUnionList[i].combine.val;
    }
}

void GenDecayEnvlope(Synthesizer* synth)
{
    SoundUnitUnion* soundUnionList=&(synth->SoundUnitUnionList[0]);
	for (uint8_t i = 0; i < POLY_NUM; i++)
	{
		if(soundUnionList[i].combine.wavetablePos_int >= WAVETABLE_ATTACK_LEN &&
				soundUnionList[i].combine.envelopePos < sizeof(EnvelopeTable)-1)
		{
			soundUnionList[i].combine.envelopeLevel = EnvelopeTable[soundUnionList[i].combine.envelopePos];
			soundUnionList[i].combine.envelopePos += 1;
		}
	}
}
