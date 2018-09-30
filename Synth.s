.module SYNTH

;typedef struct _SoundUnit
;{
;	uint16_t increment;
;	uint16_t wavetablePos;
;	uint8_t envelopeLevel;
;	uint8_t envelopePos;
;} SoundUnit;

SoundUnitSize=6
pIncrement=0
pWavetablePos=2
pEnvelopeLevel=4
pEnvelopePos=5

ENVELOP_LEN=128
POLY_NUM=5
WAVETABLE_ATTACK_LEN=1630
WAVETABLE_LEN=1758
WAVETABLE_LOOP_LEN=(WAVETABLE_LEN - WAVETABLE_ATTACK_LEN)

.area DATA
; "General registers"
 _RU8:
    .ds 8
 _RU16:
    .ds 8

_lastSoundUnitOffest:
	.dw 0

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
	
	addw x,(3,sp) 		; Do calculation :[pWavetablePos]+=[pIncrement], (3,sp) is always the latest element in stack
	addw sp,#2 			; Pop the temporal variable

	cpw x,WAVETABLE_LEN 	; Compare x (wavetablePos) with WAVETABLE_LEN C=1 when WAVETABLE_LEN>x
	jrc branch0$			; Jump if WAVETABLE_LEN is great than x
	subw x,WAVETABLE_LOOP_LEN ; Subtract x with WAVETABLE_LOOP_LEN
branch0$:
	pushw x 				;Save wavetablePos
	
	
	ldw x,#_WaveTable	; Load base address of WaveTable to x
	addw x,(3,sp)		; Calculate sample address with saved wavetablePos
	addw sp,#2 ;		; Pop the temporal variable
	
	push a 				; Save register A
	ld a,(x)			; Load sample to A
	ldw x,y				; Read envelopeLevel of sound unit to reg x.
    ldw x,(pEnvelopeLevel,x);
	mul x,a				; Mutiple envelopeLevel with sample
	pop a				; Pop A
	
	addw x,(3,sp)		; Add sum of accumlator in stack to x
	ldw (3,sp),x		; Save x to stack
	


    inc a
	addw y,SoundUnitSize
    jra loopSynth$
loopSynth_end$:
addw sp,#2 ;
    ret

_NoteOn:
	ldw x,#_PitchIncrementTable		; Load pitch increment table to register X.
	addw x,(3,sp)					; Get address by argument uint8_t note
	ldw x,(x)						; Load value
	ldw y, x						; Save value for further use

	ldw x,#_Sounds 		; Load sound unit pointer to register X.
	addw x,_lastSoundUnitOffest
	ldw (pIncrement,x),y ;Save value to mem
	ld a,#0
	ld (pEnvelopePos,x),a ;Set envlope pos to 0
	ld a,#0xff
	ld (pEnvelopeLevel,x),a ;Set envlope level to 255

	ldw x,_lastSoundUnitOffest
	addw x,#SoundUnitSize

	cpw x,POLY_NUM*SoundUnitSize
	jrc branch_NoteOn1$
branch_NoteOn0$:
	ldw y,_lastSoundUnitOffest
	addw y,#SoundUnitSize
	jra branchEnd_NoteOn1$
branch_NoteOn1$:
	clrw y
	ldw _lastSoundUnitOffest,y
branchEnd_NoteOn1$:	
	ret

