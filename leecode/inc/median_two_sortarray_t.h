#ifndef _media_two_sortarray_t_h_
#define _media_two_sortarray_t_h_
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double median_two_sortarray_t_fi(vector<int>& nums1, vector<int>& nums2)
{
    cout<< "this median_two_sortarray test\n";
    nums1.insert(nums1.end(), nums2.begin(), nums2.end());
    sort(nums1.begin(), nums1.end());
    uint len = nums1.size();
    if(len & 1) return nums1[len / 2];
    else return 0.5 * (nums1[len / 2] + nums1[len / 2 - 1]);
}

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	int l1 = 0, l2 = 0, r1 = nums1.size() - 1, r2 = nums2.size() - 1, count = 0;
	double answer;
	vector<int> nums(nums1.size() + nums2.size(), 0);
	while(l1 <= r1 && l2 <= r2)
	{
		nums[count++] = nums1[l1]<nums2[l2] ? nums1[l1++] : nums2[l2++];
		
	}
	while ((l1 == r1+1 ) && l2 <= r2)
	{
		nums[count++] = nums2[l2++];
		
	}
	while ((l2 == r2+1 ) && l1 <= r1)
	{
		nums[count++] = nums1[l1++];
		
	}
	int size = nums.size();
        
	//if (size % 2 == 1) answer = nums[size / 2 ];
	//if (size % 2 == 0) answer = ((double)nums[size / 2-1] + (double)nums[size / 2 ]) / 2.0;
        return size%2?nums[size / 2 ]:((double)nums[size / 2-1] + (double)nums[size / 2 ]) / 2.0;
    }
    
#endif