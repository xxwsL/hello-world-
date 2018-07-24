#ifndef _3sum_closest_t_h_
#define _3sum_closest_t_h_
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int _3um_closest_t_fi(vector<int>& nums, int target)
{ 
    cout << "this is 3sum_closest test\n";
    uint len = nums.size();
    sort(nums.begin(), nums.end());
    int start, end, min_dist;
    char flag = 1;
    for(uint i = 0; i<len - 2; i++){
        uint target_dist = target - nums[i];
        start = i + 1; end = len - 1;
        while(start < end){
            int dist_tp =  nums[start] + nums[end] - target_dist;
            if(flag){
                min_dist = dist_tp;
                flag = 0;
            }
            else if(dist_tp > 0){
                min_dist = abs(min_dist) <= dist_tp ? min_dist : dist_tp;
                end--;
                while(start < end && nums[end] == nums[end + 1])
                    end--;
            }
            else if(dist_tp < 0){
                min_dist = abs(min_dist) <= -dist_tp ? min_dist : dist_tp;
                start++;
                    while(start < end && nums[start] == nums[start - 1])
                        start++;
            }
            else return target;
        }
    }
    return min_dist + target;
}

    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        if (n < 3)
            runtime_error("No solution");
        
        sort(nums.begin(), nums.end());
        int nsum = nums[0] + nums[1] + nums[2];
        for (int l = 0; l < n - 2; l++) {
            int m = l + 1, r = n - 1;
            if (l && nums[l] == nums[l-1]) continue;
            if (nums[l] * 3 > target) break;
            while(m < r) {
                int sum = nums[l] + nums[m] + nums[r];
                if (sum == target)
                    return target;
                else if (sum < target)
                    m++;
                else
                    r--;
                if (abs(sum - target) < abs(nsum - target))
                        nsum = sum;
            } 
        }
        return nsum;
    }

#endif