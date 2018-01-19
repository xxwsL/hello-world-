#ifndef _pass_h_
#define _pass_h_
#include "sys.h"

#define PassMaxDef 400
#define PassNewDef 0

#define HinNums 15
#define LinNums 14

#define Hin GPIO_PIN_15
#define Lin GPIO_PIN_14

typedef struct
{
	int16_t PassNew;
}PassDef;

int16_t pass_task(void);
void Pass_init(void);
void pass_gpio_init(void);
int16_t pass_action(void);
int8_t comman_pass(void) ;
void pass_display(void);
	
#endif

