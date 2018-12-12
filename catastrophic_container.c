/**
 * CS 296 MP catastrophic container
*/


#include "catastrophic_container.h"

#define LOG_ON

#define DEFAULT_MODE 0777


void cleanup(){
    // TODOs:
    // Add things to cleanup here
    return;
}


container_t *container_new(){

    container_t *new_cont = malloc(sizeof(container_t));
    return new_cont;

}


void container_free(container_t *container){

    free(container);
    return;

}


void temp_dir_set_up(){

    char template[] = "container-XXXXXX";
    char *dir_name = NULL;
    if((dir_name = mkdtemp(template)) == NULL){
        perror_die("mktemp():");
    }

    print_temp_directory(template);

    int ret = 0;
    if((ret = chmod(dir_name, DEFAULT_MODE)) == -1){
        perror_die("chmode:");
    }

    if((ret = chdir (template)) == -1){
        perror_die("chdir():");
    }

    return;
}


void pivot_root(const char *put_old, const char *new_root){

    if(syscall(SYS_pivot_root, new_root, put_old) == -1){
        perror_die("pivot_root():");
    }

}


int process_init(){

    int namespace = CLONE_NEWUTS
                  | CLONE_NEWPID
                  | CLONE_NEWIPC
                  | CLONE_NEWNS
                  | CLONE_NEWNET;
                  | CLONE_NEWCGROUP;
    pid_t pid = clone(child_exec, child_stack + STACKSIZE, namespace|SIGCHLD, NULL);
    if(pid == -1){
        perror_die("clone");
    }  
#ifdef LOG_ON
    printf("process init %d\n", pid);
#endif   
    return pid;
}


char *stack_set_up(){
    char *stack;
    if((stack = malloc(STACK_SIZE)) == NULL){
        fprintf(stderr, "malloc failed, out of memory?");
        exit(EXIT_FAILURE);
    }    
}


int main(int argc, char **argv){

    if(argc < 2){
        print_usage();
        exit(EXIT_FAILURE);
    }

    // TODOs: parse argv
        // arguments: 
            // 1. root user
            // 2. sudo privileges
            // 3. create container without being root(i.e. use the set-uid bit)
            // 4. namespace
        

    container_t *cont = container_new();

    // TODOs: setting cgroups, memory, cpu, pid, blkio

    // TODOs: remounting

    // TODOs: setting rlimit

    set_up_temp_dir();

    // TODOs: bind mount there

    // TODOs: pivot_root

    // TODOs: nmount old root

    // TODOs: trying a user namespace

    // TODOs: switching to uid 0 / gid 0

    // TODOs: dropping capacities, bounding, inheritable

    // TODOs: filter syscalls

    // TODO: load/create container images (i.e. directory)
            // use pivot_root switch the current dir to be the new root and mounts the current
            // root in oldroot

            // move to the new root

    pid_t child_pid = process_init(); 

    // TODO: mount and pivot_root bind and mount dir + source code
    // if bind and mount == -1{
    //     perror_die("bind and mount");
    // }

    if(waitpid(chil_pid, NULL, 0) == -1){
        fprintf(stderr, "failed to wait pid %d\n", pid);
        exit(EXIT_FAILURE);
    }

    // TODO: cleanup
    cleanup();



    return EXIT_SUCCESS;
}
