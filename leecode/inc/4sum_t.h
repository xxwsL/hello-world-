#ifndef _4sum_t_h_
#define _4sum_t_h_
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> _4sum_t_fi(vector<int>& nums, int target)
{
    cout << "this is _4sum test\n";
    vector<vector<int>> res;
    int len = nums.size() - 1;
    if(len < 3) return res;
    sort(nums.begin(), nums.end());
    for(uint i = 0; i<len-2; i++){
        int sum3_target = target - nums[i];
        for(uint j = i+1; j<len-1;){
            uint start = j+1, end = len;
            int sum2_target = sum3_target - nums[j];
            while(start < end){
                int sum2 = nums[start] + nums[end];
                if(sum2 == sum2_target){
                    res.push_back({nums[i], nums[j], nums[start], nums[end]});
                    start++;
                    while(start<end && nums[start] == nums[start - 1])
                        start++;
                    end--;
                    while(start<end && nums[end] == nums[end + 1])
                        end--;
                } 
                else if(sum2 < sum2_target){
                    start++;
                    while(start<end && nums[start] == nums[start - 1])
                        start++;
                }
                else{
                    end--;
                    while(start<end && nums[end] == nums[end + 1])
                        end--;                    
                }
            }
            j++;
            while(j < len-1 && nums[j] == nums[j - 1])
                j++;
        }
    }
    return res;
}

    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        int size = nums.size();
        if(size < 4)
            return res;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < size - 3; ++i)         // 外循环，四数之和转化为三数之和
        {
            if(i > 0 && nums[i] == nums[i - 1])     // 如果两个数相等，去重
                continue;
            if(nums[i] + nums[size-1] + nums[size-2] + nums[size-3] < target)   // 由于有序，如果当前数加最后三个数都比target小，那肯定不符合
                continue;
            if(nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target)  // 如果连续四个数都比target大，后面肯定没有符合要求的情况，直接return
                return res;
            for(int j = i + 1; j < size - 2; ++j) // 内循环三数之和（从第二个数开始，后面每个数都是从前面一个数的后面开始遍历）
            {
                if(j > i + 1 && nums[j] == nums[j - 1])   // 如果两个数相等，去重
                    continue;
                if(nums[i] + nums[j] + nums[size-1] + nums[size-2] < target)  // 前两个数确定，加上最后两个数都比target小，那肯定不符合
                    continue; 
                if(nums[i] + nums[j] + nums[j+1] + nums[j+2] > target)    //  前两个数确定，如果后面连续两个数和比target大，不符合条件
                    break;
                int left = j + 1, right = size - 1;
                while(left < right)   // 两数之和
                {
                    int sum = nums[i] + nums[j] + nums[left] + nums[right];
                    if(sum == target)
                    {
                       res.push_back({nums[i], nums[j], nums[left], nums[right]}); 
                        ++left;
                        while(left < right && nums[left] == nums[left - 1])
                            ++left;
                        
                        --right;
                        while(left < right && nums[right] == nums[right + 1])
                            --right;
                    }
                    else if(sum > target)
                        --right;
                    else
                        ++left;
                }
            }
        }
        return res;
    }

#endif
