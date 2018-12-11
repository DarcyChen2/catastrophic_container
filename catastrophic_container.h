/**
 * CS 296 MP catastrophic container 
*/

#pragma once

#define _GNU_SOURCE 
#include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "includes/utils.h"


int child(void *args);
