//
//  kernel_patching.h
//  rebirth
//
//  Created by User on 13/07/2018.
//  Copyright © 2018 HackerHouse. All rights reserved.
//
#include "kernel_helpers.h"

#ifndef kernel_patching_h
#define kernel_patching_h

boolean_t unsandbox(pid_t pid);
uint64_t get_kern_cred(void);
uint64_t restore_cred(uint64_t ucred);

#endif /* kernel_patching_h */
