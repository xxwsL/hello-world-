#ifndef _xxwsL_status_h_
#define _xxwsL_status_h_

typedef struct BitStruct{
	char bit0 : 1;
    char bit1 : 1;
	char bit2 : 1;
	char bit3 : 1;
	char bit4 : 1;
	char bit5 : 1;
	char bit6 : 1;
	char bit7 : 1;
}BitStr;

typedef struct Status{
	BitStr status;
}StatusStr;

#define true 1
#define false 0
#define error -1

#endif
