#ifndef _vaild_number_t_h_
#define _vaild_number_t_h_
#include <iostream>

using namespace std;

bool vaild_number_t_fi(const string& s)
{
        enum InputType
    {
        invalid, space, sign, digit, dot, eE, len
    };
    int trans[][len] =
    {
        -1, 0, 1, 2, 3,-1,
        -1,-1,-1, 2, 3,-1,
        -1, 4,-1, 2, 5, 6,
        -1,-1,-1, 5,-1,-1,
        -1, 4,-1,-1,-1,-1,
        -1, 4,-1, 5,-1, 6,
        -1,-1, 7, 8,-1,-1,
        -1,-1,-1, 8,-1,-1,
        -1, 4,-1, 8,-1,-1,
    };
    int state = 0 ,i = 0;
    while(s[i] !='\0')
    {
        InputType inputType = invalid;
        if(s[i] == ' ')
            inputType = space;
        else if(s[i] == '+' || s[i] == '-')
            inputType = sign;
        else if(isdigit(s[i]))
            inputType = digit;
        else if(s[i] == '.')
            inputType = dot;
        else if(s[i] == 'e' || s[i] == 'E')
            inputType = eE;
        state = trans[state][inputType];
        if (state == -1)
            return false;
        i++;
    }
    return state==2 || state==4 || state==5 || state==8;
}

#endif