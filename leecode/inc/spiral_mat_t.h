#ifndef _spiral_mat_t_h_
#define _spiral_mat_t_h_
#include <iostream>
#include <vector>

using namespace std;

vector<int> spiral_mat_t_fi0(vector<vector<int>>& matrix)
{
    cout << "this is spiral_mat test 0\n";
    if(matrix.empty()) return vector<int>();
    uint cols = matrix.size(), rows = matrix[0].size();
    uint element_size = cols * rows;
    uint pos[2] = {0,0};
    vector<int> re_vec;
    for(uint count = 0; count!=element_size;){
        uint i;
        for(i = 0; i!=rows; ++i){
            re_vec.push_back(matrix[pos[0]][pos[1]]);
            count++;
            pos[1]++;
        }
        if(count == element_size) return re_vec;
        pos[0]++; pos[1]--; cols--;
        
        for(i = 0; i!=cols; ++i){
            re_vec.push_back(matrix[pos[0]][pos[1]]);
            count++;
            pos[0]++;
        }
        if(count == element_size) return re_vec;
        pos[0]--; rows--;

        for(i = 0; i!=rows; ++i){
            pos[1]--;
            re_vec.push_back(matrix[pos[0]][pos[1]]);
            count++;
        }
        if(count == element_size) return re_vec;
        cols--;

        for(i = 0; i!=cols; ++i){
            pos[0]--;
            re_vec.push_back(matrix[pos[0]][pos[1]]);
            count++;
        }
        if(count == element_size) return re_vec;
        pos[1]++; rows--;
    }
}

vector<vector<int>> spiral_mat_t_fi1(const int& n)
{
    cout << "this apiral_mat_test 1\n";
    vector<vector<int>> res(n,vector<int>(n));
    uint size = n*n, cols = n, rows = n, pos[2] = {0,0};
    char  direct_flag = 0;
    for(uint i = 1; i<=size;){
        switch(direct_flag){
            uint j;
            case 0:
            for(j = 0; j!=rows; j++){
                res[pos[0]][pos[1]] = i;
                i++;
                pos[1]++;
            }
            cols--; pos[0]++; pos[1]--; direct_flag = 1;
            break;
            case 1:
            for(j = 0; j!=cols; j++){
                res[pos[0]][pos[1]] = i;
                i++;
                pos[0]++;
            }
            rows--; pos[0]--; pos[1]--; direct_flag = 2;
            break;
            case 2:
            for(j = 0; j!=rows; j++){
                res[pos[0]][pos[1]] = i;
                i++; 
                pos[1]--;
            }
            cols--; pos[0]--; pos[1]++; direct_flag = 3;
            break;
            case 3:
            for(j = 0; j!=cols; j++){
                res[pos[0]][pos[1]] = i;
                i++;
                pos[0]--;
            }
            rows--; pos[0]++; pos[1]++; direct_flag = 0;
            break;
        }
    }
    return res;
}
#endif