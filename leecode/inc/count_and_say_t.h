#ifndef _count_and_say_h_
#define _count_and_say_h_
#include <iostream>

using namespace std;
string count_and_say_t_fi(const int& n)
{
    if(n < 1) return 0;
    string re_str;
    if(n == 1) return "1";
    else{
        string get_str = count_and_say_t_fi(n - 1);
        uint count = 1; char temp_c = get_str[0];
        for(uint i = 1; i < get_str.size(); ++i){
            if(temp_c != get_str[i]){
                re_str.push_back(count+48);
                re_str.push_back(temp_c);
                temp_c = get_str[i];
                count = 0;
            }
            count++;
        }
        re_str.push_back(count+48);
        re_str.push_back(temp_c);
    }
    return re_str;
}

#endif