#ifndef _xxwsL_status_h_
#define _xxwsL_status_h_

#define Simulation		//·ÂÕæÄ£Ê½ºê

#define true 1
#define false 0
#define error -1

typedef struct BitStruct {
	int8_t bit0 : 1;
    int8_t bit1 : 1;
	int8_t bit2 : 1;
	int8_t bit3 : 1;
	int8_t bit4 : 1;
	int8_t bit5 : 1;
	int8_t bit6 : 1;
	int8_t bit7 : 1;
}BitStr;

typedef struct Status {
	BitStr status;
}StatusStr;

#endif


