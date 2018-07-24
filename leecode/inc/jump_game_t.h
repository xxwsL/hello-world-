#ifndef _jump_game_t_h_
#define _jimp_game_t_h_
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool jump_game_t_fi(const vector<int>& nums)
{
    if(nums.empty()) return NULL;
    else if(nums.size() == 1) return true;
    uint flag = 0;
    for(int i = nums.size() - 2; i>=0; --i){
        if(nums[i] > flag) {
            flag = 0;
        }
        else if(nums[i] <= flag){
            flag++;
        }
    }
    if(flag == 0) return true;
    else return NULL;
}

#endif