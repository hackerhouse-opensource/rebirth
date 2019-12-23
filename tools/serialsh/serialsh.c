#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <sys/event.h>
#include <spawn.h>

int main(int argc, char *argv[]){
        if(argc < 2){
          	printf("supply full path for command e.g. bash");
		exit(0);
        }
        char* argvp[] = {argv[1], NULL};
        char* envp[] = {"PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/libexec", NULL};
        struct termios tty;
        int serial_fd = open ("/dev/tty.debug-console", O_RDWR | O_NOCTTY | O_SYNC);
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (serial_fd, &tty) != 0)
                return -1;
	printf("ready to tty and speed set\n");
        cfsetospeed (&tty, B115200); // set speed
        // set control options
/*        tty.c_cflag &= ~CRTSCTS;        // disable hardware flow control
        tty.c_cflag |= CLOCAL;          // local line - do not change "owner" of port
        tty.c_cflag &= ~CSIZE;          // clean data bits
        tty.c_cflag |= CS8;             // set 8 data bits
        tty.c_cflag &= ~PARENB;         // clean parity bit
        tty.c_cflag &= ~CSTOPB;         // set 1 stop bits by cleaning CSTOPB
        // set output options
        tty.c_oflag &= ~OPOST;          // set raw output
        if (tcsetattr (serial_fd, TCSANOW, &tty) != 0)
                return -1;
	printf("set attributes\n");*/
        write(serial_fd,"[-] console shell opened\n",strlen("[-] console shell opened\n"));
        posix_spawn_file_actions_t actions;
        posix_spawn_file_actions_init(&actions);
        posix_spawn_file_actions_adddup2(&actions, serial_fd, 0);
        posix_spawn_file_actions_adddup2(&actions, serial_fd, 1);
        posix_spawn_file_actions_adddup2(&actions, serial_fd, 2);
        pid_t spawned_pid = 0;
        int spawn_err = posix_spawn(&spawned_pid, argv[1], &actions, NULL, argvp, envp);
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
