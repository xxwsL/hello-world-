#ifndef _search_insert_pos_t_h_
#define _search_insert_pos_t_h_
#include <iostream>
#include <vector>

using namespace std;

int search_insert_pos_t_fi(const vector<int>& nums, const int& target)
{
    if(nums.empty()) return 0;
    uint i;
    for(i = 0; i < nums.size(); ++i){
        if(nums[i] >= target){
            return i;
        }
    }
    return i;
}
#endif