//dumb but fast :)

#include <stddef.h>
#include <stdlib.h>

int get_digit_num(int n){
    if (n < 0) n = abs(n);
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    
    return 10;
}
int find_longest(int *numbers, size_t numbers_size){
    int i = 0;
    
    for (i = 0; i < numbers_size - 1; i++){
      if (get_digit_num(numbers[0]) < get_digit_num(numbers[i+1])){
        numbers[0] = numbers[i+1];
      }
    }
    
    return numbers[0];
}