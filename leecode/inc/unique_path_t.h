#ifndef _unique_path_t_h_
#define _unique_path_t_h_
#include <iostream>

using namespace std;

int unique_path_t_fi(int m,int n)
{
    cout << "this is unique_path test\n";
    double dom = 1;
    double dedom = 1;
    int small = m<n? m-1:n-1;
    int big = m<n? n-1:m-1;
    for(int i=1;i<=small;i++)
    {
        dedom *= i;
        dom *= small+big+1-i;
    }
    return (int)(dom/dedom);
}

#endif