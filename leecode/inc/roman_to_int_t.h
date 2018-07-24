#ifndef _roman_to_int_t_h_
#define _roman_to_int_t_h_
#include <iostream>

using namespace std;

int roman_to_int_t_fi(const string& s)
{
    cout << ">> this is roman_to_int test\n";
    uint i = 0;
    int y = 0;
    char temp_c = '0';
    while(s[i]){
        switch(s[i]){
            case 'I':y += 1; temp_c = s[i];break;
            case 'V':
                if(temp_c == 'I'){
                    y += 3; temp_c = '0';
                }
                else{
                    y += 5; temp_c = '0';
                }
            break;
            case 'X':
                if(temp_c == 'I'){
                    y += 8; temp_c = '0';
                }
                else{
                    y += 10; temp_c = 'X';
                }
            break;
            case 'L':
                if(temp_c == 'X'){
                    y += 30; temp_c = '0';
                }
                else{
                    y += 50; temp_c = '0';
                }
            break;
            case 'C':
                if(temp_c == 'X'){
                    y += 80; temp_c = '0';
                }
                else{
                    y += 100; temp_c = 'C';
                }
            break;
            case 'D':
                if(temp_c == 'C'){
                    y += 300; temp_c = '0';  
                }
                else{
                    y += 500;
                }
            break;
            case 'M':
                if(temp_c == 'C'){
                    y += 800; temp_c = '0';
                }
                else{
                    y += 1000;
                }
            break;
        }
        i++;
    }
    return y;
}

 int roman2int(char roman){
        if(roman=='I') return 1;
        else if(roman=='V') return 5;
        else if(roman=='X') return 10;
        else if(roman=='L') return 50;
        else if(roman=='C') return 100;
        else if(roman=='D') return 500;
        else if(roman=='M') return 1000;
    }
    int romanToInt(string s) {
        int last=1;
        int self;
        int sum=0;
        
        for(auto riter=s.rbegin();riter!=s.rend();riter++){
            self=roman2int(*riter);
            if(self>=last){
                sum+=self;
            }
            else{
                sum-=self;
            }
            last = self;
            
        }
        return sum;
    }

#endif