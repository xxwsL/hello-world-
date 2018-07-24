#ifndef _climb_stair_t_h_
#define _climb_stair_t_h_
#include <iostream>

using namespace std;
int climb_stair_t_fi(const int& n)
{
    cout << "this is climb_stair test\n";
    if(n == 1) return 1;
    int buf[3] = {1,2};
    for(uint i = 2; i<n; ++i){
        buf[2] = buf[0] + buf[1];
        buf[0] = buf[1];
        buf[1] = buf[2]; 
    }
    return buf[1];  
}

#endif