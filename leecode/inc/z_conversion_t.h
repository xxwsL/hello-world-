#ifndef _z_conversion_t_h_
#define _z_conversion_t_h_
#include <iostream>
#include <vector>

using namespace std;

string z_conversion_t_fi(string s, int numRows){
    cout << ">> this is z_conversion test\n";
    if(numRows == 1) return s;
    //create str_vec save string for every lines 
    vector<string> str_vec(min((int)s.size(), numRows));
    int index_row = 0;
    bool down_direct = 0;
    //traver s
    for(char str_c : s){
        str_vec[index_row] += str_c;
        if(index_row == 0 || index_row == numRows - 1){
            down_direct = !down_direct;
        }
        index_row += down_direct ? 1 : -1;
    }
    string re_str;
    for(string row_str : str_vec){
        re_str += row_str;
    }
    return re_str;
}

#endif