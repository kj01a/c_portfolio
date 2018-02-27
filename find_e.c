#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include "factorial.h"

double calc_e(){
    int i = 0; //counter
    double e = 0;
    for (i = 0; i < 13; i++){
        e = e + 1.0 / factorial(i);
        debug("%lf\n", e);
    }

    return e;
}

int main(int argc, char *argv[]){
    check(argc = 1, "USAGE: ./find_e <number of digits>");
    
    int digit = atoi(argv[1]) - 1;
    check(digit < 6, "No more than 6 digits can be returned.");
    
    double e = calc_e(); 

    printf("%.*lf\n", digit, e);

    return 0;
error:
    return -1;
}
