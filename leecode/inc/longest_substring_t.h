#ifndef _longest_substring_t_h_
#define _longest_substring_t_h_
#include <iostream>
#include <map>

using namespace std;

// int longest_substring_t_fi(string s)
// {
//     uint len = s.size();
//     if(len == 0) return 0;
//     map<char,int> map_0;
//     uint index = 0, count = 1, size_0 = 0, size_1 = 0;
//     for(uint i = 0; i!=len; i++){
//         if(map_0.find(s[i]) == map_0.end() || (map_0[s[i]] < index)){
//             map_0[s[i]] = i;
//             size_1++;
//         }
//         else if(map_0[s[i]] >= index){
//             size_0 = i - map_0[s[i]];
//             size_0 = size_0 > size_1 ? size_0 : size_1;
//             if(size_0 > count) count = size_0;
//             size_1 = i - map_0[s[i]];
//             index = map_0[s[i]] + 1;
//             map_0[s[i]] = i;
//         }
//     }
//     if(size_1 > count) return size_1;
//     return count;
// }

int longest_substring_t_fi(string s)
{
   map<int,char> m;
    uint index = 0, count = 0;
    for(uint i = 0; i!=s.size(); i++){
        if(m.find(s[i]) == m.end() || m[s[i]] < index){
            count = max(count,i - index + 1);
        }
        else{
            index = m[s[i]] + 1;
        }
        m[s[i]] = i;
    }
    return count;
}



    int lengthOfLongestSubstring(string s) {
        int m[256] = {0}, res = 0, left = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (m[s[i]] == 0 || m[s[i]] < left) {
                res = max(res, i - left + 1);
            } else {
                left = m[s[i]];
            }
            m[s[i]] = i + 1;
        }
        return res;
    }
#endif