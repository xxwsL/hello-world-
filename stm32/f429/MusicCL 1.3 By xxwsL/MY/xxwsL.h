#ifndef _xxwsL_h
#define _xxwsL_h

/*syslib*/
#include "stdio.h"
#include "stdlib.h"
#include "stm32f4xx.h"

/*userlib*/
#include "led.h"   
#include "delay.h"
#include "usart.h"
#include "lcd_rgb.h"
#include "lcd_fonts.h"
#include "crealight.h"
#include "tim4.h"
#include "ADC.h"
#include "voiceot.h"
#include "Kalm.h"

#define xxwsL sysinit()
#define XX runtask()   

#define true    1
#define false   0
#define error  -1

#endif

