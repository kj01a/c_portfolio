#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"

int main(int argc, char *argv[]){
    const char pi[] = "3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067";
    char *new_pi = calloc(sizeof(pi), 1);
    char *end;
    int num_of_digits = strtol(argv[1], &end, 10);

    check(new_pi, "Memory not allocated");
    check(argc == 2, "USAGE: ./pi_n_digit <number of digits>");
    check(num_of_digits <= 100, "No more than 100 digitts can be returned.");
    check(num_of_digits > 0, "Please choose a number between 1 and 100");
    
    if(num_of_digits == 1){
        memcpy(new_pi, pi, num_of_digits);
    }
    else{
        memcpy(new_pi, pi, num_of_digits + 1);        
    }
    
    printf("%s\n", new_pi);
    
    free(new_pi);
    return 0;

error:
    free(new_pi);
    return -1;
}
