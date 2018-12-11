/**
 * CS 296 MP catastrophic container
*/


#include "catastrophic_container.h"

#define STACKSIZE (1024*1024)
static char child_stack[STACKSIZE];


int child_exec(void *stuff){

    printf("pid as seen in the child: %d\n", getpid());

    struct clone_args *args = (struct clone_args *)stuff;
    if(execvp(args->argv[0], args->argv) != 0){
        fprintf(stderr, "failed to execvp argments %s\n", strerror(errno));
    }
    // system("bash");

    // Should never reach this line
    exit(EXIT_FAILURE);
}


int main(int argc, char **argv){

    struct clone_args args;
    args.argv = &argv[1];

    // int namespace = CLONE_NEWUTS|CLONE_NEWPID|CLONE_NEWIPC|CLONE_NEWNS|CLONE_NEWNET;
    int namespace = CLONE_NEWUSER;
    // int namespace = CLONE_NEWNET;
    // int namespace = CLONE_NEWPID;
    // int namespace = CLONE_NEWIPC;
    // int namespace = CLONE_NEWNS;

    pid_t pid = clone(child_exec, child_stack + STACKSIZE, namespace|SIGCHLD, &args);
    // pid_t p = clone(child, malloc(4096)+4096, SIGCHLD|namespace, NULL);
    if(pid == -1){
        perror_die("clone");
    }

    printf("child pid: %d./na   \n", pid);
    if(waitpid(pid, NULL, 0) == -1){
        fprintf(stderr, "failed to wait pid %d\n", pid);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
