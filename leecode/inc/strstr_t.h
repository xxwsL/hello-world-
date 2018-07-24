#ifndef _strstr_t_h_
#define _strstr_t_h_
#include <iostream>

using namespace std;

int strstr_t_fi(const string& haystack, const string& needle)
{
    cout << ">> this is strstr test\n";
        auto i = haystack.find(needle);
        if(i != haystack.npos){
            return i;
        }
        return -1; 
}
#endif