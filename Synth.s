.module SYNTH
.globl _Synth
;typedef struct _SoundUnit
;{
;	uint16_t increment;
;	uint16_t wavetablePos;
;	uint8_t envelopeLevel;
;	uint8_t envelopePos;
;	int16_t val;
;} SoundUnit;

SoundUnitSize=8
pIncrement=0
pWavetablePos=2
pEnvelopeLevel=4
pEnvelopePos=5
pVal=6

ENVELOP_LEN=128
POLY_NUM=5
WAVETABLE_ATTACK_LEN=1630
WAVETABLE_LEN=1758
WAVETABLE_LOOP_LEN=(WAVETABLE_LEN - WAVETABLE_ATTACK_LEN)

.area DATA


.area CODE

_Synth:

	clr a				; Register A as loop index.
	ldw y,#_Sounds 		; Load sound unit pointer to register Y.
	clrw x				; Keep an int16 variable in stack as accumlator
	pushw x				;
	
loopSynth$:
    cp a,#POLY_NUM
    jreq loopSynth_end$
; loop body
	ldw x,y				; Read icnrement of sound unit to reg x.
    ldw x,(pIncrement,x);
	pushw x				; Save in stack temporarily.
	
	ldw x,y				; Read wavetablePos of sound unit to reg x.
    ldw x,(pWavetablePos,x);
	pushw x
	
	addw x,(3,sp) 		; Do calculation :[pWavetablePos]+=[pIncrement], (1,sp) is always the latest element in stack

branch0_start$:
	cpw x,#WAVETABLE_LEN 	; Compare x (wavetablePos) with WAVETABLE_LEN C=1 when WAVETABLE_LEN>x
	jrc branch0_end$			; Jump if WAVETABLE_LEN is great than x
	subw x,#WAVETABLE_LOOP_LEN ; Subtract x with WAVETABLE_LOOP_LEN
branch0_end$:
	ldw (pWavetablePos,y),x ; Save wavetablePos to mem
	
	
	ldw x,#_WaveTable	; Load base address of WaveTable to x
	addw x,(1,sp)		; Calculate sample address with saved wavetablePos
	addw sp,#4 ;		; Pop the temporal variable
	
	push a 				; Save register A
	ld a,(x)			; Load sample to A

	rlc a		;Get signed bit
	ld a,(x);	;Reload a

	push a					; Load evnvlopelevel to xl
    ld a,(pEnvelopeLevel,y); 
	ld xl,a
	pop a


	
	jrnc branch1_end$	; Do signed mutiple with unsigned MUL
	neg a				;
	mul x,a				; Mutiple envelopeLevel with sample
	negw x
	scf	; Set C=1
branch1_end$:	
	jrc branch2_end$
	mul x,a
branch2_end$:



	pop a					; Pop A



	ldw (pVal,y),x ; Save wavetablePos to mem
	;addw x,(1,sp)		; Add sum of accumlator in stack to x
	;ldw (1,sp),x		; Save x to stack

    inc a
	addw y,#SoundUnitSize
    jra loopSynth$

loopSynth_end$:
	;ldw x,(1,sp)
	;ldw y,#_mixOutAsm
	;ldw (y),x
	addw sp,#2 ;


		ret


