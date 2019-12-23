//
//  webserver.h
//  rebirth
//
//  Created by User on 12/06/2018.
//  Copyright © 2018 HackerHouse. All rights reserved.
//
#ifndef webserver_h
#define webserver_h
#include <dirent.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<signal.h>
#include<fcntl.h>
#include <mach/vm_types.h>
#include "kernel_helpers.h"

extern void proc_name(int pid, char * buf, int size);

void dump_pointer(mach_port_t tfp0, addr64_t addr, uint64_t max_size);
void ps_html(int sfd);
void init_ws(mach_port_t tfp0, uint64_t kernel_base);
void* wsmain(void*);
void error(char *);
void startServer(char *);
int respond(int, mach_port_t);

#endif /* webserver_h */
