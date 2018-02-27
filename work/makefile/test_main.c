#include <stdio.h>
#include "dbg.h"
#include "edi_parser.h"

int main(int argc, char *argv[]){
    check(argc != 1, "USAGE: ./test_name <filename>");
    
    print_file(argv[1]);

    return 0; 
error: 
    return -1;
}
