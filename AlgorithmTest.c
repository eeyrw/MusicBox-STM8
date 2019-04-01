#include "SynthCore.h"
#include <stdint.h>
#include <stdio.h>

#define TEST_LOOP_NUN 100

Synthesizer synthesizerC;
Synthesizer synthesizerASM;


void TestInit(void)
{
    SynthInit(&synthesizerC,0);
    SynthInit(&synthesizerASM,1);
}


void TestProcess(void)
{
    SoundUnitUnion* soundUnionList;
    TestInit();
    for(uint8_t i=0;i<TEST_LOOP_NUN;i++)
    {
        NoteOn(&synthesizerC,i);
        NoteOn(&synthesizerASM,i);
        Synth();
        SynthC(&synthesizerC);
        GenDecayEnvlope(&synthesizerC);
        GenDecayEnvlope(&synthesizerASM);

        printf("=============%d==============\n",i);
        printf("Synth C: MixOut: %6d EachChn: ",mixOutC);
        soundUnionList=&(synthesizerC.SoundUnitUnionList[0]);
        for(uint8_t k=0;k<POLY_NUM;k++)
        {
            printf("%6d ",soundUnionList[k].combine.val);
        }
        printf("\n");

        printf("Synth A: MixOut: %6d EachChn: ",mixOutAsm);
        soundUnionList=&(synthesizerASM.SoundUnitUnionList[0]);
        for(uint8_t k=0;k<POLY_NUM;k++)
        {
            printf("%6d ",soundUnionList[k].combine.val);
        }
        printf("\n");
    }
}
