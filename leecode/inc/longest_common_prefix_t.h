#ifndef _longest_common_prefix_h_
#define _longest_common_prefix_h_
#include <iostream>
#include <vector>

using namespace std;

string longest_common_prefix_t_fi(const vector<string>& strs)
{
    cout << ">> this is longest_common_prefix test\n ";
    string re_str;
    if(strs.empty()) return re_str;
    re_str = strs[0];
        for(auto iter = strs.begin() + 1; iter != strs.end(); ++iter){        
            uint i = 0;
            while(re_str[i] != '\0' && (*iter)[i] != '\0' && (re_str[i] == (*iter)[i])){                
                ++i;
            }
            re_str.assign(re_str.begin(), re_str.begin() + i);
        }    
    return re_str;
}

string longestCommonPrefix(vector<string>& strs) {
    if( !strs.size() ) return string();
    if( strs.size() == 1 )return strs[0];
    string res;
        
    for( int i = 0; i < strs[0].size(); ++i )
    {
        for(int j = 1; j < strs.size(); ++j )
        {
            if(strs[j][i] != strs[0][i] ) return res;
        }
        res.push_back(strs[0][i]);
    }
    return res;
}
#endif