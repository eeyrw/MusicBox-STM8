#include "SynthCore.h"
#include <stdint.h>
#include <stdio.h>
#include "WaveTable_Celesta_C5.h"
#include "WaveTable_Celesta_C6.h"
#include "stm8s.h"


void SynthInit(Synthesizer* synth)
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
		soundUnionList[i].combine.waveTableAddress = (uint16_t)WaveTable_Celesta_C5;
		soundUnionList[i].combine.waveTableLen = WAVETABLE_CELESTA_C5_LEN;
		soundUnionList[i].combine.waveTableLoopLen = WAVETABLE_CELESTA_C5_LOOP_LEN;
		soundUnionList[i].combine.waveTableAttackLen = WAVETABLE_CELESTA_C5_ATTACK_LEN;
	}
    synth->lastSoundUnit=0;
}
#ifdef RUN_TEST
void NoteOnC(Synthesizer* synth,uint8_t note)
{
	uint8_t lastSoundUnit = synth->lastSoundUnit;

	disable_interrupts();
	synth->SoundUnitUnionList[lastSoundUnit].combine.increment = WaveTable_Celesta_C5_Increment[note&0x7F];
	synth->SoundUnitUnionList[lastSoundUnit].combine.wavetablePos_frac = 0;
	synth->SoundUnitUnionList[lastSoundUnit].combine.wavetablePos_int = 0;
	synth->SoundUnitUnionList[lastSoundUnit].combine.waveTableAddress = (uint16_t)WaveTable_Celesta_C5;
	synth->SoundUnitUnionList[lastSoundUnit].combine.waveTableLen = WAVETABLE_CELESTA_C5_LEN;
	synth->SoundUnitUnionList[lastSoundUnit].combine.waveTableLoopLen = WAVETABLE_CELESTA_C5_LOOP_LEN;
	synth->SoundUnitUnionList[lastSoundUnit].combine.waveTableAttackLen = WAVETABLE_CELESTA_C5_ATTACK_LEN;

	enable_interrupts();

	lastSoundUnit++;

	if (lastSoundUnit== POLY_NUM)
		lastSoundUnit = 0;

    synth->lastSoundUnit=lastSoundUnit;
}

void SynthC(Synthesizer* synth)
{
    synth->mixOut=0;
    SoundUnitUnion* soundUnionList=&(synth->SoundUnitUnionList[0]);
	int8_t* pWaveTable;
    for(uint8_t i=0;i<POLY_NUM;i++)
    {
		pWaveTable=(int8_t*)soundUnionList[i].combine.waveTableAddress;
        soundUnionList[i].combine.val=soundUnionList[i].combine.envelopeLevel*pWaveTable[soundUnionList[i].combine.wavetablePos_int]/255;
        soundUnionList[i].combine.sampleVal=pWaveTable[soundUnionList[i].combine.wavetablePos_int];
		uint32_t waveTablePos=soundUnionList[i].combine.increment+
                             soundUnionList[i].combine.wavetablePos_frac+
                             ((uint32_t)soundUnionList[i].combine.wavetablePos_int<<8); 

        uint16_t waveTablePosInt= waveTablePos>>8;
        if(waveTablePosInt>soundUnionList[i].combine.waveTableLen)
           waveTablePosInt-=soundUnionList[i].combine.waveTableLoopLen;
        soundUnionList[i].combine.wavetablePos_int= waveTablePosInt;
        soundUnionList[i].combine.wavetablePos_frac=0xFF&waveTablePos;
        synth->mixOut+=soundUnionList[i].combine.val;
    }
}

void GenDecayEnvlopeC(Synthesizer* synth)
{
    SoundUnitUnion* soundUnionList=&(synth->SoundUnitUnionList[0]);
	for (uint8_t i = 0; i < POLY_NUM; i++)
	{
		if(soundUnionList[i].combine.wavetablePos_int >= soundUnionList[i].combine.waveTableAttackLen &&
				soundUnionList[i].combine.envelopePos <sizeof(EnvelopeTable)-1)
		{
			soundUnionList[i].combine.envelopeLevel = EnvelopeTable[soundUnionList[i].combine.envelopePos];
			soundUnionList[i].combine.envelopePos += 1;
		}
	}
}
#endif