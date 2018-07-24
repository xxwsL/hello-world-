#ifndef _interval_h_
#define _interval_h_
#include <iostream>
#include <vector>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {};
    Interval(int s, int e) : start(s), end(e) {}
};

vector<Interval> interval_t_fi(void)
{
    vector<Interval> re_vec;
    re_vec.push_back(Interval(1,3));
    re_vec.push_back(Interval(2,6));
    re_vec.push_back(Interval(8,10));
    re_vec.push_back(Interval(9,12));
    return re_vec;
}

#endif