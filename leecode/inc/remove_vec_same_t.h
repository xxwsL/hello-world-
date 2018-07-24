#ifndef _remove_vec_t_h_
#define _remove_vec_t_h_
#include <iostream>
#include <vector>
#include <hash_map>

using namespace std;
using namespace __gnu_cxx;

int remove_vec_t_fi(vector<int>& nums){
    cout << "this is remove_vec_same test\n";
    if(nums.size() == 0) return 0;
    hash_map<int,int> hash0;
    hash0[nums[0]] = 0;
    for(auto iter = nums.begin() + 1; iter!=nums.end();){
        if(hash0.find(*iter) != hash0.end()){
            iter = nums.erase(iter);
        }
        else{
            hash0[*iter] = iter - nums.begin();
            ++iter;
        }
    }
    return nums.size();
}

    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        
        int len = nums.size();
        int pos = 0;
        for (size_t i = 1ull; i < len; ++i) {
            if (nums[pos] != nums[i]) {
                nums[++pos] = nums[i];
            }
        }

        return pos + 1;
    }
#endif