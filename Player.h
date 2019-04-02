#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdint.h>
#include "SynthCore.h"


enum PLAY_STATUS{
    STATUS_STOP=0,
    STATUS_REDAY_TO_PLAY=1,
    STATUS_PLAYING=2
};

typedef struct _Player
{
	uint8_t status;
	uint32_t  scoreTick;
	uint8_t  decayGenTick;
    uint8_t* scorePointer;
    Synthesizer mainSynthesizer;
} Player;


extern void PlayerInit(Player* player);
extern void Player32kProc(Player* player);
extern void PlayerProcess(Player* player);


#endif