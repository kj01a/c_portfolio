#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"
#include "edi_parser.h"

int print_file(char *arg_file[]){
    FILE *fp = fopen(arg_file, 'r');
    char *parsed_line = malloc(BUF_SIZE);
    check(fp != NULL, "Failed to open file");

    if (fgets(parsed_line, BUF_SIZE, fp) != NULL){
        printf("%s", parsed_line);
    }

    free(parsed_line);
    fclose(fp);

    return 0;
error:
    return -1;
}
