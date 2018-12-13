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

    process_num_limit();
        printf("pass\n");
    clone_args_t *clone_args = (clone_args_t*)args;

    const char *new_hostname = HOSTNAME;
    if(sethostname(new_hostname, strlen(new_hostname)) == -1){
        perror_die("sethostname():");
    }

    // if(chroot("rootfs") == -1){
    //     perror_die("chroot():");
    // }

    // if(chdir("/") == -1){
    //     perror_die("chdir():");
    // }

    /* ensure that changes to our mount namespace do not "leak" to
     * outside namespaces (what mount --make-rprivate / does)
     */
    // if (mount("", "/", NULL, MS_REC|MS_PRIVATE, NULL) == -1){
    //     perror_die("mount /");
    // }
    
    // if (umount("/proc") != 0) {
    //     perror_die("umount /proc: ");
    // }

    // if (mount("none", "/proc", NULL, MS_PRIVATE|MS_REC, NULL)) {
    //     printf("Cannot umount proc! errno=%i", errno);
    //     exit(1);
    // }

    if (mount("proc", "/proc", "proc", 0, NULL) != 0) {
        perror_die("mount /proc: ");
    }

    // if (umount("/sys") != 0) {
    //     perror_die("umount /sys: ");
    // }    

    if (mount("sys", "/sys", "sysfs", 0, NULL)) {
        perror_die("mount /sys");
    }

    // if (umount("/dev") != 0) {
    //     perror_die("umount /sys: ");
    // }  

    if (mount("/dev", "/dev", NULL, MS_BIND, NULL)) {
        perror_die("mount /dev");
    }

    if(chroot("rootfs") == -1){
        perror_die("chroot():");
    }

    if(chdir("/") == -1){
        perror_die("chdir():");
    }

    int ret = 0;
    if((ret = execvp(clone_args->argv[0], clone_args->argv)) != 0){
        fprintf(stderr, "failed to execvp argments %s\n", strerror(errno));
    }

    return ret;
}


void file_create_and_write(char *filename, char *buf, size_t len){

    FILE *fp = fopen(filename, "w+");
    if(fp == NULL){
        perror_die("fopen:");
    }
    printf("buf contains %s\n", buf);
    if(fwrite(buf, 1, len, fp) < 0){
        fprintf(stderr, "fwrite pids.max failed\n");
        exit(EXIT_FAILURE);
    }
    printf("pass fwrite\n");
    return;

}


void process_num_limit(){

    char cwd_buff[PATH_MAX];
    getcwd(cwd_buff, PATH_MAX);
    printf("%s\n", cwd_buff);

    const char *cgroups = "/sys/fs/cgroup/pids";
    if(chdir(cgroups) == -1){
        perror_die("chdir(cgroups):");
    }
    if(mkdir(HOSTNAME, DEFAULT_MODE) == -1){
        perror_die("mkdir(HOSTNAME)");
    }
    if(chdir(HOSTNAME) == -1){
        perror_die("chdir(HOSTNAME):");
    }

    // within the HOSTNAME file
    char *buf = "30";
    file_create_and_write("pids.max", buf, strlen(buf)+1);
    // file_create_and_write("notify_on_release", "1", 2);

    // char buf[100];
    // sprintf(buf, "%ld", (long)getpid());
    // printf("%s\n", buf);
    // file_create_and_write("cgroup.procs", buf, sizeof(pid_t));

    chdir(cwd_buff);
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
                   |CLONE_NEWPID
                   |CLONE_NEWNS; // namespace for mount
                //    |CLONE_NEWUSER
                //    |CLONE_NEWNS
                //    |CLONE_NEWNET;

    // // Doesn't work?
    if(unshare(CLONE_NEWNS | CLONE_FS) == -1){
        perror_die("unshare");
    }

    pid_t child_pid = clone(child_exec, child_stack + STACKSIZE, namespace|SIGCHLD, &args);
    if(child_pid == -1){
        perror_die("clone");
    }  

    if(waitpid(child_pid, NULL, 0) == -1){
        fprintf(stderr, "failed to wait pid %d\n", child_pid);
        exit(EXIT_FAILURE);
    }

    const char *cgroups = "/sys/fs/cgroup/pids";
    if(chdir(cgroups) == -1){
        perror_die("chdir(cgroups):");
    }    

    if(rmdir(HOSTNAME) == -1){
        perror_die("mkdir(HOSTNAME)");
    }

    // wired cwd
    // char buf[1024];
    // getcwd(buf, 1024);
    // printf("cwd is: %s\n", buf); // debug

    return EXIT_SUCCESS;
}
