#ifndef _remove_element_h_
#define _remove_element_h_
#include <iostream>
#include <vector>

using namespace std;

int remove_element_t_fi(vector<int>& nums, int val)
{
    int len = nums.size();
    if(len == 0) return 0;
    len -= 1;
    int i = 0;
    do{
        if(nums[i] == val){
            while(nums[len] == val){
                len -= 1;
                if(len < i) return i;
            }
            nums[i] = nums[len];
            nums[len] = val;
            len -= 1;
        }
        ++i;
    }while(i <= len);
    return i; 
}

    int removeElement(vector<int>& nums, int val) {
        int tmp = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != val)
                nums[tmp++] = nums[i];
        }
        return tmp;
    }
#endif