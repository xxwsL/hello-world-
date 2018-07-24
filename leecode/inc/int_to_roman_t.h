#ifndef _int_to_roman_t_h_
#define _int_to_roman_t_h_
#include <iostream>
#include <string>

using namespace std;

string get_roman_single(int num, char flag)
{
    string res;
    while(num--){
        switch(flag){
            case 0: res += 'I'; break;
            case 1: res += "X"; break;
            case 2: res += "C"; break;
            case 3: res += 'M'; break;
        }
    }
    return res;
}

string int_to_roman_t_fi(int num)
{
    cout << "this is int_to_roman test\n";
    string res;
    int rema = 0;
    char flag = 0;
    while(num != 0){
        rema = num % 10;
        if(rema == 4){
            switch(flag){
                case 0: res += "VI"; break;
                case 1: res += "LX"; break;
                case 2: res += "DC"; break;
            }
        }
        else if(rema == 9){
            switch(flag){
                case 0: res += "XI"; break;
                case 1: res += "CX"; break;
                case 2: res += "MC"; break;
            }
        }
        else if(rema >=5){
            rema -= 5;
            res += get_roman_single(rema, flag);
            switch(flag){
                case 0: res += 'V'; break;
                case 1: res += "L"; break;
                case 2: res += "D"; break;
            }
        }
        else{
            res += get_roman_single(rema, flag);   
        }
        num /= 10;
        flag++;
    }
    reverse(res.begin(), res.end());
    return res;
}

#endif