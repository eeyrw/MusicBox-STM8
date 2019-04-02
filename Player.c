#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stm8s.h>
#include <uart.h>
#include <delay.h>
#include "SynthCore.h"
#include "Player.h"

extern unsigned char Score[];

void Player32kProc(Player* player)
{
    Synth(&(player->mainSynthesizer));
    player->currentTick++;
    if(player->decayGenTick<50)
        player->decayGenTick+=1;
}


void PlayerProcess(Player* player)
{

    uint8_t temp;
    uint32_t tempU32;
    if(player->status==STATUS_PLAYING)
    {
        if(player->decayGenTick>=50)
        {
            GenDecayEnvlope(&(player->mainSynthesizer));
            player->decayGenTick=0;
        }


        if((player->currentTick>>8)>=player->lastScoreTick)
        {
           do
           {
               temp=*(player->scorePointer);
               player->scorePointer++;
               NoteOn(&(player->mainSynthesizer),temp);
           } while ((temp&0x80)!=0);
           if(temp==0xFF)
           {
               player->status=STATUS_STOP;
           }
           tempU32=player->lastScoreTick;
            do
           {
               temp=*(player->scorePointer);
               player->scorePointer++;
               tempU32+=temp;
           } while (temp==0xFF);
           player->lastScoreTick=tempU32;
        }

    }
}

void PlayerPlay(Player* player)
{
    player->currentTick=0;
    player->lastScoreTick=0;
    player->decayGenTick=0;
    player->scorePointer=Score;
    player->status=STATUS_PLAYING;
}

void PlayerInit(Player* player)
{
    player->status=STATUS_STOP;
    player->currentTick=0;
    player->lastScoreTick=0;
    player->decayGenTick=0;
    player->scorePointer=Score;
    SynthInit(&(player->mainSynthesizer));
}