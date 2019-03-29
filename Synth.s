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
;} SoundUnit;

SoundUnitSize=9
pIncrement_frac=0
pIncrement_int=1
pWavetablePos_frac=2;
pWavetablePos_int_l=3;
pWavetablePos_int_h=4;
pEnvelopeLevel=5
pEnvelopePos=6
pVal=7

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

loopSynth$:
    cp a,#POLY_NUM
    jreq loopSynth_end$
	push a				; Keep a as temporary variable
; loop body
		ldw x,y
		ldw x,(pWavetablePos_int_l,x)	; Get a sample by pWavetablePos_int and save to a
		ld a,(_WaveTable,x)

		push a
		ld a,(pEnvelopeLevel,y); Load evnvlopelevel to xl
		ld xl,a
		pop a

		tnz a				; Test if a<0
		jrmi branch1_end$	; Do signed mutiple with unsigned MUL
		mul x,a
		jra branch2_end$	
	branch1_end$:
		neg a				;Do signed mutiple with unsigned MUL
		mul x,a				; Mutiple envelopeLevel with sample
		negw x
	branch2_end$:

		addw x,_mixOutAsm;

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
		ldw (pWavetablePos_int_l,y),x ;
						

	pop a
    inc a
	addw y,#SoundUnitSize
    jra loopSynth$

loopSynth_end$:

	ldw x,_mixOutAsm
	sraw x
	cpw x,#253
	jrslt branch_lt_253$
	ldw x,#253
branch_lt_253$:
	cpw x,#-255
	jrsgt branch_lt_gt_end$
	ldw x,#-255
branch_lt_gt_end$:	

	;sraw x
	;ror	T2H			;
	;mov	EL, T2L			;
	;subi	EL, 0x80		;
	;mov	EH, EL			;
	;com	EH			;
	;sbrc	T2H, 7			;
	;inc	EL			;
	;sts OCR1AL,EL
	;sts OCR1BL,EH

		ret


