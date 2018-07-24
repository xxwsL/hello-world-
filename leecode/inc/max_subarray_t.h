#ifndef _max_subarray_t_h_
#define _max_subarray_t_h_
#include <iostream>
#include <vector>

using namespace std;

int maxSubArray(vector<int>& nums) {
        return maxsequence2(nums,0,nums.size() - 1);
}
    
int maxsequence2(vector<int>& a, int l, int u)
{
    if (l > u) return 0;
    if (l == u) return a[l];
    int m = (l + u) / 2;
 
    /*求横跨左右的最大连续子序列左半部分*/   
    int lmax=a[m], lsum=0;
    for (int i=m; i>=l; i--) {
        lsum += a[i];
        if (lsum > lmax)
            lmax = lsum;
    }
    
    /*求横跨左右的最大连续子序列右半部分*/
    int rmax=a[m+1], rsum = 0; 
    for (int i=m+1; i<=u; i++) { 
        rsum += a[i];
        if (rsum > rmax) 
            rmax = rsum; 
    }
    //返回三者最大值
    return max3(lmax+rmax, maxsequence2(a, l, m), maxsequence2(a, m+1, u)); 
}
int max3(int i, int j, int k)
{
    if (i>=j && i>=k)
        return i;
    return max3(j, k, i);
}

    int max_subarray(vector<int>& nums) {
        int n = nums.size();
        int dp[n];
        dp[0] = nums[0];
        int res = dp[0];
        
        for(int i = 1; i < n; i++){
            dp[i] = nums[i] + (dp[i - 1] > 0 ? dp[i - 1] : 0);
            res = max(res, dp[i]);
        }
        
        return res;
    }

#endif