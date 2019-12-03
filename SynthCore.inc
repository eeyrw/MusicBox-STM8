
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
pLastSoundUnit=SoundUnitSize*POLY_NUM+2


ENVELOP_LEN=256
POLY_NUM=2

DECAY_TIME_FACTOR=150
