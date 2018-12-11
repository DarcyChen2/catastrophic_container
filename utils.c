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