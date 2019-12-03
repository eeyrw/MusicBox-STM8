_SynthAsm:
	clr a				
	push a			; Keep a loop index in stack
	clrw x
	pushw x				; Keep mixOut result in stack
	; The stack layout is:
	; (0x01,sp)=mixOut
	; (0x03,sp)=loop index
	; (0x04,sp)=PCH
	; (0x05,sp)=PCL
	; (0x06,sp)=synthesizer object's address.
	
	ldw y,(0x06, sp) 	; Load sound unit pointer to register Y.

loopSynth$:
	ld a,(0x03,sp)
    cp a,#POLY_NUM
    jreq loopSynth_end$
; loop body
		ldw x,y
		ldw x,(pWavetablePos_int_h,x)	; Get a sample by pWavetablePos_int and save to a
		ld a,(_WaveTable,x)
		ld (pSampleVal,y),a

		ld a,(pEnvelopeLevel,y); Load evnvlopelevel to xl
		ld xl,a
		ld a,(pSampleVal,y)

		tnz a				; Test if a<0
		jrmi branch1_end$	; Do signed mutiple with unsigned MUL
		mul x,a
		swapw x				; Div with 0xFF
		ld a,#0
		ld xh,a
		jra branch2_end$	
	branch1_end$:
		neg a				;Do signed mutiple with unsigned MUL
		mul x,a				; Mutiple envelopeLevel with sample
		swapw x				; Div with 0xFF
		ld a,#0
		ld xh,a
		negw x
	branch2_end$:

		ldw (pVal,y),x

		addw x,(0x01,sp)
		ldw (0x01,sp),x

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
						
    inc (0x03,sp)
	addw y,#SoundUnitSize
    jra loopSynth$

loopSynth_end$:
	ldw y,(0x06, sp) 
	ldw x,(0x01,sp)
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

	addw sp,#3



