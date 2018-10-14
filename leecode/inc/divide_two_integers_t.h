#ifndef _divide_two_integers_t_h_
#define _divide_two_integers_t_h_

#include <iostream>

int32_t divide_two_integers_t_fi(int32_t dividend, int32_t divisor){
    std::cout << "this is divide_two_integers test" << std::endl;
    int32_t iSum = 0, iCount = 0;
    int cSymbol = dividend > 0 ? 0 : 2;
    cSymbol += divisor > 0 ? 0 : 1;
    switch(cSymbol){
            case 0:{
                dividend -= divisor;
            }break;
            case 1:{
                dividend = -dividend - divisor;
            }break;
            case 2:{
                dividend = dividend + divisor;
            }break;
            case 3:{
                if(dividend == -2147483648){
                    dividend = -(dividend - divisor + 1);
                }
                else{
                    dividend = -(dividend - divisor);
                } 
            }break;
    }
    while(1){
        switch(cSymbol){
            case 0:{
                if(iSum <= dividend){
                    iSum += divisor;
                    iCount++;
                }
                else{
                    return iCount;
                }
            }break;
            case 1:{
                if(iSum >= dividend){
                    iSum += divisor;
                    iCount--;
                }
                else{
                    return iCount;
                }
            }break;
            case 2:{
                if(iSum >= dividend){
                    iSum -= divisor;
                    iCount--;
                }
                else{
                    return iCount;
                }
            }break;
            case 3:{
                if(iSum <= dividend){
                    iSum -= divisor;
                    iCount++;
                }
                else{
                    return iCount;
                }
            }break;
        }
    } 
    return iCount;
}
#endif