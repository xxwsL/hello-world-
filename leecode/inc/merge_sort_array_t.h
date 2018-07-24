#ifndef _merge_sort_array_t_h_
#define _merge_sort_array_t_h_
#include <iostream>
#include <vector>

using namespace std;

void merge_sort_array_t_fi(vector<int>& nums1, vector<int>& nums2)
{
    auto iter1 = nums1.begin(), iter2 = nums2.begin();
    uint i = 0;
    while(iter2 != nums2.end()){
        cout << *nums1.end();
        if(iter1 == nums1.end()){
            nums1.insert(iter1,iter2,nums2.end());
            return;
        }
        else if(*iter1 > *iter2){
            nums1.insert(iter1,1,*iter2);
            iter2++;
        }
        else{
            i++;
            iter1 = nums1.begin() + i;
        }
    }
} 

#endif