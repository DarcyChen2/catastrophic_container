/**
 * CS 296 MP catastrophic container
*/


#include "catastrophic_container.h"


int child(void *args){
    printf("pid as seen in the child: %d\n", getpid());
    system("bash");
}


int main(){
    int namespace = CLONE_NEWUTS|CLONE_NEWPID|CLONE_NEWIPC|CLONE_NEWNS|CLONE_NEWNET;
    pid_t p = clone(child, malloc(4096)+4096, SIGCHLD|namespace, NULL);
    if(p == -1){
        perror_die("clone");
    }
    printf("child pid: %d./na   \n", p);
    waitpid(p, NULL, 0);
    return 0;
}