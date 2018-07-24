#ifndef _contain_most_water_t_h_
#define _contain_most_water_t_h_
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// static auto x = []() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     return 0;
// }();

int contain_most_water_t_fi(vector<int>& height)
{
    cout << "this is contain_most_water test\n";
    uint len = height.size(), area = 0, widht = 0, lenght = 0;
    int l_ans = 0, r_ans = len - 1;
    while(l_ans != r_ans){
        widht = r_ans - l_ans;
        if(height[l_ans] < height[r_ans]){
            lenght = height[l_ans];
            l_ans++;
        }
        else{
            lenght = height[r_ans];
            r_ans--;
        }
        uint area_tp = widht * lenght;
        area = max(area, area_tp); 
    }
    return area;
}


#endif