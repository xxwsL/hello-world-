#ifndef _add_binary_t_h_
#define _add_binary_t_h_
#include <iostream>

using namespace std;

string add_binary_t_fi(const string& a, const string& b)
{
    string re_str = a.size() > b.size() ? a : b;
    auto iter_a = a.rbegin(), iter_b = b.rbegin();
    char a_v, b_v, pop = 48;
    for(auto iter_r = re_str.rbegin(); iter_r!=re_str.rend(); ++iter_r){
        if(iter_a == a.rend()){
            a_v = '0';
        }
        else{
            a_v = *iter_a;
            iter_a++;
        }
        if(iter_b == b.rend()){
            b_v = '0';
        }
        else{
            b_v = *iter_b;
            iter_b++;
        }
        switch(a_v + b_v + pop){
            case 144:*iter_r = '0'; pop = 48;break;
            case 145:*iter_r = '1'; pop = 48;break;
            case 146:*iter_r = '0'; pop = 49;break;
            case 147:*iter_r = '1'; pop = 49;break;
        }
    }
    if(pop == '1'){
        re_str.insert(re_str.begin(),1,'1');
    }
    return re_str;
}

#endif