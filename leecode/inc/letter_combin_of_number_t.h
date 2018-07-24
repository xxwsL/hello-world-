#ifndef _letter_combin_of_number_t_h_
#define _letter_combin_of_number_t_h_
#include <iostream>
#include <vector>

using namespace std;

vector<string> letter_combin_of_number_t_fi(string digits)
{
    cout << "this is letter_combin_of_number test\n";
    if(digits.size() == 0) return vector<string>();
    vector<string> res(1);
    string dict[] = {"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    for(uint i = 0; i<digits.size(); ++i){
        uint res_size = res.size();
        string dict_element = dict[digits[i] - '2'];
        for(uint j = 0; j<res_size; j++){
            string str_tp = res.front();
            res.erase(res.begin());
            for(uint k = 0; k<dict_element.size(); k++){
                res.push_back(str_tp + dict_element[k]);
            }
        }
    }
    return res;
}
#endif