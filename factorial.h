#include <stdio.h>

unsigned long int factorial(unsigned long int digit){
    if (digit == 0){
        return 1;
    }

    return digit * factorial(digit - 1);

}

