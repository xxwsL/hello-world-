#pragma once
#ifndef _XXWSL_H_
#define _XXWSL_H_

//windows
#define WINDOWS
#ifdef WINDOWS
#include <Windows.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#endif 

#define debug_show

typedef unsigned int uint;

//#include <back_fi.h>

namespace xxwsL{
//flag√∂æŸ
enum flag{NO,YES};
//xxwsL¿‡
class xxwsL_c {
};
};


#endif // !_XXWSl_H_
