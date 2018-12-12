/**
 * CS 296 MP catastrophic container 
*/

#pragma once

#define _GNU_SOURCE 
#include <sched.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include "includes/utils.h"

#define STACKSIZE (1024*1024)


// TODO: a user map?

typedef struct{
    char stack[STACKSIZE];
} clone_stack_t;

typedef struct{
    char *directores;
    char *host_name;
    // Add anything
} container_config_t;

typedef struct{
    // Add anything
    // char *id;
    container_config_t *config_file;
    clone_stack_t stack;
} container_t;




/**
 * @brief create a container with all the initialization
 * @return NULL on failed creation or new struct container_t on a succesfull
 * creation.
*/
container_t *container_new();



/**
 * @brief delete a container
*/
void container_free(container_t *container);


/**
 * @brief setup some directories for the container 
*/
void set_up_temp_dir();


/**
 * @brief create an init process
 * @return pid of the process
*/
int process_init();


/**
 * TODO:
 * @brief start a container 
 * @return the pid of the init process of the container
*/
// bool container_start(pid_t *init_process);


/**
 * Question: need it? need it?
 * TODO:
 * @brief run the hostname cmd
*/
// void container_exec(char cmd);


/**
 * @brief: do the cleanup work
*/
void cleanup();


/**
 * TODO:
 * @brief init process cleanup orphans
*/
// void orphan_cleanup(void *args);


// TODO: make mount read only


// TODO: make mount write only


// TODO: remount /dev, /prov, /sys, Mnt namespace


// TODO: assign an ip address, ip link set


/**
 * TODO:
 * @brief tries to bind mount a path from host to container
 * 
 * Any missing parent paths will be created
 * 
 * @return SUCCESS if everything worked as expected, FAILURE otherwise
*/
// bool bind_mount_container(const char &path_in_host, const char &path_in_container, bool read_only);


// TODO: need it? useful?
// create_command_job(); 