//
//  kernel_helpers.h
//  rebirth
//
//  Created by User on 12/06/2018.
//  Copyright © 2018 HackerHouse. All rights reserved.
//
#ifndef kernel_helpers_h
#define kernel_helpers_h

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/proc.h>
#include <sys/ucred.h>
#include <mach/mach.h>
#include <sys/mount.h>
#include <copyfile.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "kstruct_offsets.h"

extern mach_port_t tfp0;
extern mach_port_t kmem_read_port;
extern uint64_t cached_task_self_addr;

kern_return_t mach_vm_read(
                           vm_map_t target_task,
                           mach_vm_address_t address,
                           mach_vm_size_t size,
                           vm_offset_t *data,
                           mach_msg_type_number_t *dataCnt);

kern_return_t mach_vm_write(
                            vm_map_t target_task,
                            mach_vm_address_t address,
                            vm_offset_t data,
                            mach_msg_type_number_t dataCnt);

kern_return_t mach_vm_read_overwrite(
                                     vm_map_t target_task,
                                     mach_vm_address_t address,
                                     mach_vm_size_t size,
                                     mach_vm_address_t data,
                                     mach_vm_size_t *outsize);
void wk32(uint64_t, uint32_t);
void wk64(uint64_t, uint64_t);
uint32_t rk32(uint64_t);
uint64_t rk64(uint64_t);
uint64_t dump_kernel(mach_port_t tfp0, uint64_t kernel_base);
uint64_t find_port_via_proc_pidlistuptrs_bug(mach_port_t port, int disposition);
extern uint64_t find_port_via_kmem_read(mach_port_name_t port);
uint64_t task_self_addr(void);
uint64_t proc_for_pid(uint32_t pid);
size_t kread(uint64_t where, void *p, size_t size);
uint32_t kread32(uint64_t where);
uint64_t kread64(uint64_t where);
size_t kwrite(uint64_t where, const void *p, size_t size);
void kwrite32(uint64_t where, uint32_t what);
void kwrite64(uint64_t where, uint64_t what);


#endif /* kernel_helpers_h */
