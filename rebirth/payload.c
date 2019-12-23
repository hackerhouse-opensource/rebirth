//
//  bind_shell.c
//  rebirth
//
//  Created by User on 12/06/2018.
//  Copyright © 2018 HackerHouse. All rights reserved.
//
#include "payload.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <CoreFoundation/CoreFoundation.h>
#include "QiLin.h"
#include "kernel_patching.h"

char* bundle_path() {
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    int len = 4096;
    char* path = malloc(len);
    CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8*)path, len);
    return path;
}

char* prepare_directory(char* dir_path) {
    DIR *dp;
    struct dirent *ep;
    char* in_path = NULL;
    char* bundle_root = bundle_path();
    asprintf(&in_path, "%s/binpack/%s", bundle_root, dir_path);
    dp = opendir(in_path);
    if (dp == NULL) {
        printf("unable to open payload directory: %s\n", in_path);
        return NULL;
    }
    while ((ep = readdir(dp))) {
        char* entry = ep->d_name;
        char* full_entry_path = NULL;
        asprintf(&full_entry_path, "%s/binpack/%s/%s", bundle_root, dir_path, entry);
        printf("preparing: %s\n", full_entry_path);
        int chmod_err = chmod(full_entry_path, 0655);
        if (chmod_err != 0){
            printf("chmod failed\n");
        }
        free(full_entry_path);
    }
    closedir(dp);
    free(bundle_root);
    return in_path;
}

char* prepare_payload() {
    char* path = calloc(4096, 1);
    strcpy(path, "PATH=");
    char* dir;
    dir = prepare_directory("bin");
    strcat(path, dir);
    strcat(path, ":");
    free(dir);
    dir = prepare_directory("sbin");
    strcat(path, dir);
    strcat(path, ":");
    free(dir);
    dir = prepare_directory("usr/bin");
    strcat(path, dir);
    strcat(path, ":");
    free(dir);
    dir = prepare_directory("usr/local/bin");
    strcat(path, dir);
    strcat(path, ":");
    free(dir);
    dir = prepare_directory("usr/sbin");
    strcat(path, dir);
    strcat(path, ":");
    free(dir);
    strcat(path, "/bin:/sbin:/usr/bin:/usr/sbin:/usr/libexec");
    return path;
}

/* // debug bind shell routine for tcp port
void do_bind_shell(char* env, int port) {
    char* bundle_root = bundle_path();
    char* shell_path = NULL;
    asprintf(&shell_path, "%s/binpack/bin/bash", bundle_root);
    char* argv[] = {shell_path, NULL};
    char* envp[] = {env, NULL};
    struct sockaddr_in sa;
    sa.sin_len = 0;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = INADDR_ANY;
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    bind(sock, (struct sockaddr*)&sa, sizeof(sa));
    listen(sock, 1);
    printf("shell listening on port %d\n", port);
    for(;;) {
        int conn = accept(sock, 0, 0);
        posix_spawn_file_actions_t actions;
        posix_spawn_file_actions_init(&actions);
        posix_spawn_file_actions_adddup2(&actions, conn, 0);
        posix_spawn_file_actions_adddup2(&actions, conn, 1);
        posix_spawn_file_actions_adddup2(&actions, conn, 2);
        pid_t spawned_pid = 0;
        int spawn_err = posix_spawn(&spawned_pid, shell_path, &actions, NULL, argv, envp);
        if (spawn_err != 0){
            perror("shell spawn error");
        } else {
            printf("shell posix_spawn success!\n");
        }
        posix_spawn_file_actions_destroy(&actions);
        printf("our pid: %d\n", getpid());
        printf("spawned_pid: %d\n", spawned_pid);
        int wl = 0;
        while (waitpid(spawned_pid, &wl, 0) == -1 && errno == EINTR);
    }
}*/

int startSSH(char* env_path){
    int rc = 0, fd =0;
    pid_t spawned_pid = 0;
    char *shell_path = NULL, *ssh_path = NULL;
    char* bundle_root = bundle_path();
    asprintf(&shell_path, "%s/binpack/bin/bash", bundle_root);
    asprintf(&ssh_path, "%s/binpack/usr/local/bin/dropbear", bundle_root);
    char* argv[] = {"dropbear","-R","-c",shell_path, NULL};
    char* envp[] = {env_path, NULL};
    printf("starting SSH...\n");
    mkdir("/tmp/dropbear",0755);
    // add shell_path to /tmp/dropbear/shell
    unlink("/tmp/dropbear/shell");
    fd = open("/tmp/dropbear/shell",O_RDWR|O_CREAT,0700);
    rc = write(fd,shell_path,strlen(shell_path));
    close(fd);
    if(rc > 0){
        printf("wrote dropbear shell configuration");
    }
    unlink("/private/var/root/.bashrc");
    fd = open("/private/var/root/.bashrc",O_RDWR|O_CREAT,0700);
    rc = write(fd,env_path,strlen(env_path));
    close(fd);
    if(rc > 0){
        printf("wrote root .bashrc for path configuration");
    }
    rc = posix_spawn(&spawned_pid, ssh_path, NULL, NULL, argv, envp);
    uint64_t ssh_proc =  getProcStructForPid(spawned_pid);
    rootifyPid(spawned_pid);
    unsandbox(spawned_pid);
    return rc;
}

void drop_payload() {
    char* env_path = prepare_payload();
    printf("will launch a shell with this environment: %s\n", env_path);
    if(startSSH(env_path)!=0)
        printf("failed to start SSH...\n");
    //do_bind_shell(env_path, 31337);
    free(env_path);
}
