/**
 * CS 296 MP catastrophic container
*/


// make
// ./container run <cmd> <params>


#include "catastrophic_container.h"

#define LOG_ON

#define DEFAULT_MODE 0777


static char child_stack[STACKSIZE];


// void temp_dir_set_up(){

//     char template[] = "container-XXXXXX";
//     char *dir_name = NULL;
//     if((dir_name = mkdtemp(template)) == NULL){
//         perror_die("mktemp():");
//     }

//     print_temp_directory(template);

//     int ret = 0;
//     if((ret = chmod(dir_name, DEFAULT_MODE)) == -1){
//         perror_die("chmode:");
//     }

//     char buf[PATH_MAX];
//     sprintf(buf, "%s/", ROOT_DIR);

//     if((ret = chdir (template)) == -1){
//         perror_die("chdir():");
//     }

//     return;
// }


int child_exec(void *args){

    printf("running pid as seen in the child: %d\n", getpid());

    clone_args_t *clone_args = (clone_args_t*)args;

    const char *new_hostname = HOSTNAME;
    if(sethostname(new_hostname, strlen(new_hostname)) == -1){
        perror_die("sethostname():");
    }

    // if (umount("/proc") != 0) {
    //         fprintf(stderr, "failed unmount /proc %s\n",
    //                 strerror(errno));
    //         exit(-1);
    // }

    // if (mount("proc", "/proc", "proc", 0, "") != 0) {
    //     perror_die("mount /proc");
    // }

    // if (mount("sys", "/sys", "sysfs", 0, NULL)) {
    //     perror_die("mount /sys");
    // }


    // char template[] = "container-XXXXXX";
    // char *dir_name = NULL;
    // if((dir_name = mkdtemp(template)) == NULL){
    //     perror_die("mktemp():");
    // }

    // print_temp_directory(template);

    // int ret = 0;
    // if((ret = chmod(dir_name, DEFAULT_MODE)) == -1){
    //     perror_die("chmode():");
    // }

    // if(chdir(dir_name) == -1){
    //     perror_die("chdir():");
    // }

    if(chroot("rootfs") == -1){
        perror_die("chroot():");
    }

    if(chdir("/") == -1){
        perror_die("chdir():");
    }

    if(execvp(clone_args->argv[0], clone_args->argv) != 0){
        fprintf(stderr, "failed to execvp argments %s\n", strerror(errno));
    }

    exit(EXIT_FAILURE); // shuold never reach this line
}


int main(int argc, char **argv){

    if(argc < 2){
        print_usage();
        exit(EXIT_FAILURE);
    }

    clone_args_t args;
    args.argv = &argv[1];

    // int namespace = 0;
    int namespace = CLONE_NEWUTS // hostname
                   |CLONE_NEWPID;
                //    |CLONE_NEWUSER
                //    |CLONE_NEWNS
                //    |CLONE_NEWNET;
    // int namespace = CLONE_NEWUTS
//                   | CLONE_NEWPID
//                   | CLONE_NEWIPC
//                   | CLONE_NEWNS
//                   | CLONE_NEWNET;
                //   | CLONE_NEWCGROUP; // undefined?
    pid_t child_pid = clone(child_exec, child_stack + STACKSIZE, namespace|SIGCHLD, &args);
    if(child_pid == -1){
        perror_die("clone");
    }  

    if(waitpid(child_pid, NULL, 0) == -1){
        fprintf(stderr, "failed to wait pid %d\n", child_pid);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
