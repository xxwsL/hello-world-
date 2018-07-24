#include <iostream>
#include "pailndrome_number_t.h"

using namespace std;

bool pailndrome_number_t_fi(int x)
{
    cout << ">> this is pailndrome_number test\n";
    if(x < 0) return NULL;
    int y = 0, x_temp = x, pop;
    while(x_temp != 0){
        pop = x_temp % 10;
        x_temp = x_temp / 10;
        y = y * 10 + pop;
    }
    if(y != x) return NULL;
    else return true;   
}