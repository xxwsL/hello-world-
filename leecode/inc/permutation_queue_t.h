#ifndef _permutation_queue_t_h_
#define _permutation_queue_t_h_
#include <iostream>

using namespace std;

string permutation_queue_t_fi(int n, int k)
{
    string res(n,' '), save_str;
    uint size = 1, temp_n;
    save_str.push_back('1');
    for(temp_n = 2; temp_n<=n; temp_n++){
        size *= temp_n;
        save_str.push_back(temp_n + 48);
    }
    for(uint i = 0; i!=n; ++i){
        size /= (n - i);
        uint index = (k - 1) / size;
        res[i]= save_str[index];
        save_str.erase(index,1);
        k -= index*size; 
    }
    return res;
}

int factorial(int n)
{
    int res = 1;
    for(int i = 2; i <= n; i++)
    res *= i;
    return res;
}     

string getPermutation(int n, int k) {
    int total = factorial(n);
    string candidate = string("123456789").substr(0, n);
    string res(n,' ');
    for(int i = 0; i < n; i++){
        total /= (n-i);
        int index = (k-1) / total;
        res[i] = candidate[index];
        candidate.erase(index, 1);
        k -= index*total;
    }
    return res;
}

#endif