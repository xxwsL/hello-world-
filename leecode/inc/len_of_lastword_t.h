#ifndef _len_of_lastword_t_h_
#define _len_of_lastword_t_h_
#include <iostream>

using namespace std;

int len_of_lastword_t_fi(const string& s)
{
    cout << "this is len_of_lastword test\n";
    if(s.empty()) return 0;
    auto iter = s.rbegin();
    while(*iter == ' ' && iter != s.rend()){
        iter++;
    }
    if(iter == s.rend()) return 0;
    auto iter_pos = iter;
    for(; iter != s.rend(); ++iter){
        if(*iter == ' '){
            return iter - iter_pos;
        }
    }
    return iter - iter_pos;
}

    int lengthOfLastWord(string s) {
        int cur_len = 0;
        for (int i = s.length() - 1; i >= 0; i--){
            if (cur_len == 0 && s[i] == ' ')
                continue;
            else if (cur_len != 0 && s[i] == ' ')
                return cur_len;
            else
                cur_len++;
        }
        return cur_len;
    }
#endif