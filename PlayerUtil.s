.module PLAYER_UTILS
.globl _UpdateTick

; typedef struct _Player
; {
; 	uint8_t status;
;     uint32_t  currentTick;
; 	uint32_t  lastScoreTick;
; 	uint8_t  decayGenTick;
;     uint8_t* scorePointer;
;     Synthesizer mainSynthesizer;
; } Player;

pStatus=0
pCurrentTick_b3=1
pCurrentTick_b2=2
pCurrentTick_b1=3
pCurrentTick_b0=4
pLastScoreTick_b3=5
pLastScoreTick_b2=6
pLastScoreTick_b1=7
pLastScoreTick_b0=8
pDecayGenTick=9
pScorePointer=10
pMainSynthesizer=11
.area DATA

.area CODE

_UpdateTick:
; void Player32kProc(Player* player)
; {
;     Synth(&(player->mainSynthesizer));
;     player->currentTick++;
;     if(player->decayGenTick<200)
;         player->decayGenTick+=1;
; }
	ldw y,(0x03, sp) 		; Load sound unit pointer to register Y. (0x03, sp) is player object's address.
    ldw x,y
    ldw x,(pCurrentTick_b1,x)
    addw x,#1
    ldw (pCurrentTick_b1,y),x
    jrnc updateCurrentTickEnd$ 
    ldw x,y
    ldw x,(pCurrentTick_b3,x)
    addw x,#1
    ldw (pCurrentTick_b1,y),x    
updateCurrentTickEnd$:

ld a,(pDecayGenTick,y)
cp a,#200
jruge updateDecayGenTickEnd$
inc (pDecayGenTick,y)

updateDecayGenTickEnd$:

ret


