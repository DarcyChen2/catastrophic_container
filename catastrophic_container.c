/**
 * CS 296 MP catastrophic container
*/


#include "catastrophic_container.h"

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


void set_up_temp_dir(){

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


int process_init(){

    int namespace = CLONE_NEWUTS|CLONE_NEWPID|CLONE_NEWIPC|CLONE_NEWNS|CLONE_NEWNET;
    pid_t pid = clone(child_exec, child_stack + STACKSIZE, namespace|SIGCHLD, NULL);
    if(pid == -1){
        perror_die("clone");
    }   
    
    return pid;
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

    set_up_temp_dir();

    // mount make private

    // TODO: create container images (i.e. directory)
            // use pivot_root switch the current dir to be the new root and mounts the current
            // root in oldroot

            // move to the new root

    pid_t child = process_init();    

    // TODO: bind and mount dir + source code
    // if bind and mount == -1{
    //     perror_die("bind and mount");
    // }

    // TODO: Wait pid
    // printf("child pid: %d./na   \n", pid);
    // if(waitpid(pid, NULL, 0) == -1){
    //     fprintf(stderr, "failed to wait pid %d\n", pid);
    //     exit(EXIT_FAILURE);
    // }

    // TODO: cleanup
    cleanup();



    return EXIT_SUCCESS;
}
