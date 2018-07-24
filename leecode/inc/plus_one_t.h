#ifndef _plus_one_t_h_
#define _plus_one_t_h_
#include <iostream>
#include <vector>

using namespace std;

vector<int> plus_one_t_fi(vector<int>& digits)
{
    cout << "this is plus_one test\n";
    if(digits.empty()) return digits;
    auto iter = digits.rbegin();
    for(; iter!=digits.rend(); ++iter){
        if(*iter != 9){
            (*iter)++;
            return digits;
        }
        (*iter) = 0;
    }
    if(iter == digits.rend()){
        digits[0] = 1;
        digits.push_back(0);
    }
    return digits;
}

#endif