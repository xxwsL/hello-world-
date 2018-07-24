#ifndef _my_sqrt_t_h_
#define _my_sqrt_t_h_
#include <iostream>

using namespace std;

int my_sqrt_t_fi(int x)
{
    if(x == 0) return 0;
    if(x < 4) return 1;
    if(x == 4) return 2;
    int l = 0, m = x / 2, r = x, m_ago = 0, m_cache;
    while(1){
        if(m > x/m){
            m_cache = (l + m) / 2;
            if(m_cache == m_ago) return m_ago;
            m_ago = m;
            r = m;
            m = m_cache;
        }
        else{
            m_cache = (r + m) / 2;
            if(m_cache == m_ago) return m_cache;
            m_ago = m;
            l = m;
            m = m_cache;
        }
    }
    return m;
}

#endif