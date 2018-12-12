/**
 * CS 296 MP
*/

#include <stdio.h>
#include <stdlib.h>

#include "includes/utils.h"


void perror_die(char *args){
    perror(args);
    exit(EXIT_FAILURE);
}

void print_usage(){
    printf("./container <TODOs: something goes in here>");
}

void print_temp_directory(char *temp_directory){
    fprintf(stdout, "%s\n", temp_directory);
}