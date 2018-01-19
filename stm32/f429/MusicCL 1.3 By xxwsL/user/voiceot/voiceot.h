#ifndef _voiceot_h_
#define _voiceot_h_
#include "xxwsL.h"

#define LowVStDef 790
#define LowVMinDef 860
#define LowVMidDef 900
#define LowVMaxDef 960
#define LowVMaxhDef 1000

#define HightVStDef  1250
#define HightVMinDef 1300
#define HightVMidDef 1400
#define HightVMaxDef 1500
#define HightVMaxhDef 1570

typedef struct VoiceBase
{
	uint16_t VoiceBaseSt;
	uint16_t VoiceBaseMin;
	uint16_t VoiceBaseMid;
	uint16_t VoiceBaseMax;
	uint16_t VoiceBaseMaxh;
	uint16_t VoiceBaseStep;
}VB;

int8_t voiveot_value(uint16_t voicei,VB *VBstr_p);

void voiceot_init(void);
int8_t voice_lowot(uint16_t voicei);
int8_t voice_hightot(uint16_t voicei);
int8_t DO_ot(void);

#endif


