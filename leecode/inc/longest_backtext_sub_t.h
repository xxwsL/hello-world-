#ifndef _longest_backtext_sub_t_h_
#define _longest_backtext_sub_t_h_
#include <iostream>

using namespace std;

int find_backtext(string s, int left, int right)
{
    while(left >= 0 && right!=s.size() && s[left] == s[right]){
        left--;
        right++;
    }
    return right - left - 1;
}

string longest_backtext_t_fi(string s)
{
    cout << "this is longest_backtext test\n";
    int l_tmp = 0, r_tmp = 0;
    for(uint i = 0; i!=s.size(); i++){
        int len1 = find_backtext(s, i, i);
        int len2 = find_backtext(s, i, i+1);
        len1 = len1 > len2 ? len1 : len2;
        if(len1 > r_tmp - l_tmp){
            l_tmp = i - (len1-1) / 2;
            r_tmp = i + len1 / 2;
        }
    }
    return s.substr(l_tmp, r_tmp - l_tmp + 1);
}

#endif