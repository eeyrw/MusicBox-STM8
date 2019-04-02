#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stm8s.h>
#include <uart.h>
#include <delay.h>
#include "SynthCore.h"
#include "Player.h"

void Player32kProc(Player* player)
{
    Synth(&(player->mainSynthesizer));
    player->scoreTick+=1;
    if(player->decayGenTick<50)
        player->decayGenTick+=1;
}

uint16_t DecodeScore(uint8_t* scorePointer,uint8_t* note,uint32_t* duration)
{

}

void PlayerProcess(Player* player)
{
    uint8_t note;
    uint32_t duration;
    uint16_t scoreReadLen;
    if(player->status==STATUS_PLAYING)
    {
        if(player->decayGenTick>=50)
        {
            GenDecayEnvlope(&(player->mainSynthesizer));
            player->decayGenTick=0;
        }
        do
        {
           scoreReadLen=DecodeScore(player->scorePointer,&note,&duration);

        } while (0);
        

        

    }
    else if(player->status==STATUS_REDAY_TO_PLAY)
    {

    }
    else if(player->status==STATUS_STOP)
    {
        
    }
}

void PlayerInit(Player* player)
{
    player->status=STATUS_STOP;
    player->scoreTick=0;
    player->decayGenTick=0;
    SynthInit(&(player->mainSynthesizer));
}