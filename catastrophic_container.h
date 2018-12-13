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
#include <linux/limits.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include "includes/utils.h"

#define STACKSIZE (1024*1024)

#define HOSTNAME "catastrophic_container : < "
#define ROOT_DIR "ROOT_FOR_CONTAINER"

// TODO: a user map?

typedef struct{
    char **argv;
} clone_args_t;

// typedef struct{
//     char stack[STACKSIZE];
// } clone_stack_t;

typedef struct{
    char *directores;
    char *hostname;
    // Add anything
} container_config_t;

typedef struct{
    // Add anything
    // char *id;
    container_config_t *config_file;
    // clone_stack_t stack;
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


void process_num_limit();


void file_create_and_write(char *filename, char *buf, size_t len);


/**
 * @brief setup some directories for the container 
*/
// void temp_dir_set_up();
void dir_set_up();


/**
 * @brief create an init process
 * @return pid of the process
*/
int process_init();


/**
 * @brief set up room for a stack
*/
char *stack_set_up();


/**
 * @brief change the root directory for all process in a new mnt namespace, effectively
 *  jailing the process inside the roofts.
 * @param put_old - directory to move the current process root filesystem to
 *        new_root - new root filesystem
*/
void pivot_root(const char *put_old, const char *new_root);


/**
 * @brief mount filesystem
*/
void mount_fs();


/**
 * @brief umount filesystem
 * @param target - the topmost filesystem this directory is mounted on will be removed
*/
void unmount_fs();


/**
 * @brief handle uid map
*/
int handle_uid_map(pid_t child_pid);

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
