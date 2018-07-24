#ifndef _ach_atoi_t_h_
#define _ach_atoi_t_h_
#include <iostream>
#include <climits>

using namespace std;

// int ach_atoi_t_fi(string str)
// {
//     cout << "this is ach_atoi test\n";
//     uint index = 0;
//     int res = 0 , bol = 1;
//     char flag = 0;
//     for(uint i = 0; i!=str.size(); i++){
//         if(flag == 0 && str[i] == ' ') continue;
//         if(flag == 0 && (str[i] == '+' || str[i] == '-') && i!=str.size() - 1 && str[i+1] >= '0' && str[i + 1] <= '9'){
//                 bol = str[i] == '-' ? -1 : 1; 
//                 i = i + 1;
//                 res = bol * (str[i] - '0');  
//                 flag = 1;
//                 continue;
//         }
//         if(str[i] >= '0' && str[i] <= '9'){
//             flag = 1;
//             if(res > INT_MAX/10 || (res == INT_MAX/10 && str[i] > '7')) return INT_MAX;
//             if(res < INT_MIN/10 || (res == INT_MIN/10 && str[i] > '8')) return INT_MIN;
//             res = res * 10 + bol * (str[i] - '0');
                    
//         }
//         else{
//             return res;
//         }
//     }
//     return res;
// }

int ach_atoi_t_fi(string str)
{
    cout << "this is ach_atoi test\n";
    int res = 0 , bol = 1;
    char flag = 0;
    for(uint i = 0; i!=str.size(); i++){
        if(flag == 0 && str[i] == ' ') continue;
        else if(flag == 0 && str[i] == '+'){
            bol = 1;
            flag = 1;
        }
        else if(flag == 0 && str[i] == '-'){
            bol = 1;
            flag = 1;
        }
        else if(str[i] >= '0' && str[i] <= '9'){
            flag = 1;
            if(res > INT_MAX/10 || (res == INT_MAX/10 && str[i] > '7')) return INT_MAX;
            if(res < INT_MIN/10 || (res == INT_MIN/10 && str[i] > '8')) return INT_MIN;
            res = res * 10 + bol * (str[i] - '0');
        }
        else{
            break;
        }
    }
    return res;
}

#endif