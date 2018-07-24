#ifndef _3sum_t_h_
#define _3sum_t_h_
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> _2sum(vector<int>& nums, int start, int target)
{
    vector<vector<int>> res;
    int end = nums.size() - 1;
    while(start < end){
        int y = nums[start]+nums[end];
        if(y == target){
            vector<int> vec_tp = {-target,nums[start], nums[end]};
            res.push_back(vec_tp);
            start++;
            while(start < end && nums[start] == nums[start-1]){
                start++;
            }
            end--;
            while(start < end && nums[end] == nums[end+1]){
                end--;
            }
        }
        else if(y > target){
            end--;
            while(start < end && nums[end] == nums[end+1])
                end--;
        }
        else{
            start++;
            while(start < end && nums[start] == nums[start-1])
                start++;            
        }
    }
    return res;
}

vector<vector<int>> _3sum_t_fi(vector<int>& nums)
{
    cout << "this is _3sum test\n";
    vector<vector<int>> res;
    if(nums.size() < 3) return res;
    sort(nums.begin(), nums.end());
    uint len = nums.size()-2;
    for(uint i = 0; i!=len;){
        vector<vector<int>> vec_tp = _2sum(nums, i+1, -nums[i]);
        res.insert(res.end(), vec_tp.begin(), vec_tp.end());
        i++;
        while(i!=len && nums[i] == nums[i - 1])
            i++;
    }
    return res;
}

    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        for (int k = 0; k < nums.size(); ++k) {
            if (nums[k] > 0) break;
            if (k > 0 && nums[k] == nums[k - 1]) continue;
            int target = 0 - nums[k];
            int i = k + 1, j = nums.size() - 1;
            while (i < j) {
                if (nums[i] + nums[j] == target) {
                    res.push_back({nums[k], nums[i], nums[j]});
                    while (i < j && nums[i] == nums[i + 1]) ++i;
                    while (i < j && nums[j] == nums[j - 1]) --j;
                    ++i; --j;
                } else if (nums[i] + nums[j] < target) ++i;
                else --j;
            }
        }
        return res;
    }

#endif