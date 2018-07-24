#ifndef _merge_interval_t_h_
#define _merge_interval_t_h_
#include <iostream>
#include <vector>
#include <algorithm>

#include "interval.h" 

using namespace std;
 bool compare(Interval &a, Interval &b) {return a.start < b.start;}

vector<Interval> merge_interval_t_fi(vector<Interval>& intervals)
{
    cout << "this is merge_interval test\n";
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end(), compare);
    vector<Interval> res{intervals[0]};
    for (int i = 1; i < intervals.size(); ++i) {
        if (res.back().end < intervals[i].start) {
            res.push_back(intervals[i]);
        } else {
            res.back().end = max(res.back().end, intervals[i].end);
        }
    }   
    return res;
}

#endif