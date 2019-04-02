.module SYNTH
.globl _Synth

;typedef struct _SoundUnit
;{
;	uint8_t increment_frac;
;	uint8_t increment_int;
;	uint8_t  wavetablePos_frac;
;	uint16_t  wavetablePos_int;
;	uint8_t envelopeLevel;
;	uint8_t envelopePos;
;	int16_t val;
;	int8_t sampleVal;
;} SoundUnit;


;typedef struct _Synthesizer
;{
;    SoundUnitUnion SoundUnitUnionList[POLY_NUM];
;	int16_t mixOut;
;    uint8_t lastSoundUnit;
;}Synthesizer;

SoundUnitSize=10

pIncrement_int=0
pIncrement_frac=1
pWavetablePos_frac=2
pWavetablePos_int_h=3
pWavetablePos_int_l=4
pEnvelopeLevel=5
pEnvelopePos=6
pVal=7
pSampleVal=9

pMixOut=SoundUnitSize*POLY_NUM


ENVELOP_LEN=128
POLY_NUM=5
WAVETABLE_ATTACK_LEN=1630
WAVETABLE_LEN=1758
WAVETABLE_LOOP_LEN=(WAVETABLE_LEN - WAVETABLE_ATTACK_LEN)


REG_TIM2_CCR2L=0x314+0x5000;
REG_TIM2_CCR3L=0x316+0x5000;


.area DATA
_mixOutAsm::
	.ds 2

.area CODE

_Synth:

	clr a				; Register A as loop index.
	ldw y,(0x03, sp) 		; Load sound unit pointer to register Y. (0x03, sp) is synthesizer object's address.
	clrw x
	ldw _mixOutAsm,x

loopSynth$:
    cp a,#POLY_NUM
    jreq loopSynth_end$
	push a				; Keep a as temporary variable
; loop body
		ldw x,y
		ldw x,(pWavetablePos_int_h,x)	; Get a sample by pWavetablePos_int and save to a
		ld a,(_WaveTable,x)

		
		ld (pSampleVal,y),a

		push a
		ld a,(pEnvelopeLevel,y); Load evnvlopelevel to xl
		ld xl,a
		pop a

		tnz a				; Test if a<0
		jrmi branch1_end$	; Do signed mutiple with unsigned MUL
		mul x,a
		ld a,xh				; Div with 0xFF
		ld xl,a
		ld a,#0
		ld xh,a
		jra branch2_end$	
	branch1_end$:
		neg a				;Do signed mutiple with unsigned MUL
		mul x,a				; Mutiple envelopeLevel with sample
		ld a,xh				; Div with 0xFF
		ld xl,a
		ld a,#0
		ld xh,a
		negw x
	branch2_end$:

		ldw (pVal,y),x

		addw x,_mixOutAsm
		ldw _mixOutAsm,x

		; Do calculation :[pWavetablePos]+=[pIncrement]
		ld a,(pIncrement_frac,y) ; Get frac part of increment.
		add a,(pWavetablePos_frac,y) ; Add frac part of increment with frac part of wavetablePos.
		ld (pWavetablePos_frac,y),a ; Save frac result to frac part of wavetablePos.

		ld a,(pIncrement_int,y) ; Get integer part of increment.
		adc a,(pWavetablePos_int_l,y) ; Add integer part of increment with integer part L of wavetablePos and carrier from frac.
		ld (pWavetablePos_int_l,y),a ; Save integer result to integer part L of wavetablePos.
		ld xl,a		; Let X hold value of integer part of wavetablePos

		ld a,(pWavetablePos_int_h,y) ; integer part H of wavetablePos
		adc a,#0 ; integer part H of wavetablePos with carrier from integer part L.
		ld (pWavetablePos_int_h,y),a ; Save integer result  to integer part H of wavetablePos.
		ld xh,a   ; Let X hold value of integer part of wavetablePos

	branch0_start$:
		cpw x,#WAVETABLE_LEN 	; Compare x (wavetablePos) with WAVETABLE_LEN C=1 when WAVETABLE_LEN>x
		jrc branch0_end$			; Jump if WAVETABLE_LEN is great than x
		subw x,#WAVETABLE_LOOP_LEN ; Subtract x with WAVETABLE_LOOP_LEN
	branch0_end$:
		ldw (pWavetablePos_int_h,y),x ;
						

	pop a
    inc a
	addw y,#SoundUnitSize
    jra loopSynth$

loopSynth_end$:
	ldw y,(0x03, sp) 
	ldw x,_mixOutAsm
	ldw (pMixOut,y),x
	;sraw x
	cpw x,#253
	jrslt branch_lt_253$
	ldw x,#253
branch_lt_253$:
	cpw x,#-255
	jrsgt branch_lt_gt_end$
	ldw x,#-255
branch_lt_gt_end$:	

	sraw x
	ld a,xl
	sub a,#0x80
	ld REG_TIM2_CCR2L,a
	cpl a
	ld REG_TIM2_CCR3L,a	

	ret


