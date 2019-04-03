#include "SynthCore.h"
#include <stdint.h>
#include <stdio.h>

#define TEST_LOOP_NUN 200

Synthesizer synthesizerC;
Synthesizer synthesizerASM;


void TestInit(void)
{
    SynthInit(&synthesizerC);
    SynthInit(&synthesizerASM);
}

void PrintParameters(Synthesizer* synth)
{
    SoundUnitUnion* soundUnionList;
    printf("MixOut:%d\n",synth->mixOut);
    soundUnionList=&(synth->SoundUnitUnionList[0]);

    printf("%12s","Chn Val");
    for(uint8_t k=0;k<POLY_NUM;k++)
    {
        printf("%6d ",soundUnionList[k].combine.val);
    }
    printf("\n");

    printf("%12s","Chn Sample");
    for(uint8_t k=0;k<POLY_NUM;k++)
    {
        printf("%6d ",soundUnionList[k].combine.sampleVal);
    }
    printf("\n");

    printf("%12s","Chn EnvLevel");
    for(uint8_t k=0;k<POLY_NUM;k++)
    {
        printf("%6d ",soundUnionList[k].combine.envelopeLevel);
    }
    printf("\n");


    printf("%12s","Chn WavePos");
    for(uint8_t k=0;k<POLY_NUM;k++)
    {
        printf("%6d ",soundUnionList[k].combine.wavetablePos_int);
    }
    printf("\n");

    printf("%12s","Chn EnvlPos");
    for(uint8_t k=0;k<POLY_NUM;k++)
    {
        printf("%6d ",soundUnionList[k].combine.envelopePos);
    }
    printf("\n");

    printf("%12s","Chn NoteIncr");
    for(uint8_t k=0;k<POLY_NUM;k++)
    {
        printf("%6x ",soundUnionList[k].combine.increment);
    }
    printf("\n");
       
}

void TestProcess(void)
{
    TestInit();
    for(uint8_t i=0;i<POLY_NUM;i++)
    {
        NoteOn(&synthesizerC,i%56);
        NoteOnAsm(&synthesizerASM,i%56);
    }
    for(uint8_t i=0;i<TEST_LOOP_NUN;i++)
    {
        Synth(&synthesizerASM);
        SynthC(&synthesizerC);
        GenDecayEnvlope(&synthesizerC);
        GenDecayEnvlopeAsm(&synthesizerASM);
        printf("=============%d==============\n",i);
        printf("Synth C:\n");
        PrintParameters(&synthesizerC);
        printf("Synth ASM:\n");
        PrintParameters(&synthesizerASM);
    }
}
