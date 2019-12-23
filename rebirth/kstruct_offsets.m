//
//  kstruct_offsets.m
//  rebirth
//
//  Created by User on 12/06/2018.
//  Copyright © 2018 HackerHouse. All rights reserved.
//
#import <Foundation/Foundation.h>
#include "kstruct_offsets.h"

int* offsets = NULL;
uint64_t kernel_base = (uint64_t)NULL;
int apfs_snapshot = 0;

int kstruct_offsets_11_0[] = {
    0xb,   // KSTRUCT_OFFSET_TASK_LCK_MTX_TYPE,
    0x10,  // KSTRUCT_OFFSET_TASK_REF_COUNT,
    0x14,  // KSTRUCT_OFFSET_TASK_ACTIVE,
    0x20,  // KSTRUCT_OFFSET_TASK_VM_MAP,
    0x28,  // KSTRUCT_OFFSET_TASK_NEXT,
    0x30,  // KSTRUCT_OFFSET_TASK_PREV,
    0x308, // KSTRUCT_OFFSET_TASK_ITK_SPACE
    0x368, // KSTRUCT_OFFSET_TASK_BSD_INFO,
    0x0,   // KSTRUCT_OFFSET_IPC_PORT_IO_BITS,
    0x4,   // KSTRUCT_OFFSET_IPC_PORT_IO_REFERENCES,
    0x40,  // KSTRUCT_OFFSET_IPC_PORT_IKMQ_BASE,
    0x50,  // KSTRUCT_OFFSET_IPC_PORT_MSG_COUNT,
    0x60,  // KSTRUCT_OFFSET_IPC_PORT_IP_RECEIVER,
    0x68,  // KSTRUCT_OFFSET_IPC_PORT_IP_KOBJECT,
    0x88,  // KSTRUCT_OFFSET_IPC_PORT_IP_PREMSG,
    0x90,  // KSTRUCT_OFFSET_IPC_PORT_IP_CONTEXT,
    0xa0,  // KSTRUCT_OFFSET_IPC_PORT_IP_SRIGHTS,
    0x10,  // KSTRUCT_OFFSET_PROC_PID,
    0x108, // KSTRUCT_OFFSET_PROC_P_FD
    0x0,   // KSTRUCT_OFFSET_FILEDESC_FD_OFILES
    0x8,   // KSTRUCT_OFFSET_FILEPROC_F_FGLOB
    0x38,  // KSTRUCT_OFFSET_FILEGLOB_FG_DATA
    0x10,  // KSTRUCT_OFFSET_SOCKET_SO_PCB
    0x10,  // KSTRUCT_OFFSET_PIPE_BUFFER
    0x14,  // KSTRUCT_OFFSET_IPC_SPACE_IS_TABLE_SIZE
    0x20,  // KSTRUCT_OFFSET_IPC_SPACE_IS_TABLE
    0x6c,  // KFREE_ADDR_OFFSET
};

int kstruct_offsets_11_3[] = {
    0xb,   // KSTRUCT_OFFSET_TASK_LCK_MTX_TYPE,
    0x10,  // KSTRUCT_OFFSET_TASK_REF_COUNT,
    0x14,  // KSTRUCT_OFFSET_TASK_ACTIVE,
    0x20,  // KSTRUCT_OFFSET_TASK_VM_MAP,
    0x28,  // KSTRUCT_OFFSET_TASK_NEXT,
    0x30,  // KSTRUCT_OFFSET_TASK_PREV,
    0x308, // KSTRUCT_OFFSET_TASK_ITK_SPACE
    0x368, // KSTRUCT_OFFSET_TASK_BSD_INFO,
    0x0,   // KSTRUCT_OFFSET_IPC_PORT_IO_BITS,
    0x4,   // KSTRUCT_OFFSET_IPC_PORT_IO_REFERENCES,
    0x40,  // KSTRUCT_OFFSET_IPC_PORT_IKMQ_BASE,
    0x50,  // KSTRUCT_OFFSET_IPC_PORT_MSG_COUNT,
    0x60,  // KSTRUCT_OFFSET_IPC_PORT_IP_RECEIVER,
    0x68,  // KSTRUCT_OFFSET_IPC_PORT_IP_KOBJECT,
    0x88,  // KSTRUCT_OFFSET_IPC_PORT_IP_PREMSG,
    0x90,  // KSTRUCT_OFFSET_IPC_PORT_IP_CONTEXT,
    0xa0,  // KSTRUCT_OFFSET_IPC_PORT_IP_SRIGHTS,
    0x10,  // KSTRUCT_OFFSET_PROC_PID,
    0x108, // KSTRUCT_OFFSET_PROC_P_FD
    0x0,   // KSTRUCT_OFFSET_FILEDESC_FD_OFILES
    0x8,   // KSTRUCT_OFFSET_FILEPROC_F_FGLOB
    0x38,  // KSTRUCT_OFFSET_FILEGLOB_FG_DATA
    0x10,  // KSTRUCT_OFFSET_SOCKET_SO_PCB
    0x10,  // KSTRUCT_OFFSET_PIPE_BUFFER
    0x14,  // KSTRUCT_OFFSET_IPC_SPACE_IS_TABLE_SIZE
    0x20,  // KSTRUCT_OFFSET_IPC_SPACE_IS_TABLE
    0x7c,  // KFREE_ADDR_OFFSET
};

int koffset(enum kstruct_offset offset) {
    if (offsets == NULL) {
        printf("need to call offsets_init() prior to querying offsets\n");
        return 0;
    }
    return offsets[offset];
}

void offsets_init() {
    if (@available(iOS 11.4, *)) {
        printf("this bug is patched in iOS 11.4 and above\n");
        exit(EXIT_FAILURE);
    } else if (@available(iOS 11.3, *)) {
        fingerprint();
        if(kernel_base){
            offsets = kstruct_offsets_11_3;
            apfs_snapshot = 1;
        }
        else{
            exit(EXIT_FAILURE);
        }
        printf("kernel offsets selected for iOS 11.3 or above\n");
        
    } else if (@available(iOS 11.0, *)) {
        fingerprint();
        if(kernel_base){
            offsets = kstruct_offsets_11_0;
            apfs_snapshot = 0;
        }
        else{
           exit(EXIT_FAILURE);
        }
        printf("kernel offsets selected for iOS 11.0 to 11.2.6\n");
    } else {
        printf("iOS version too low, 11.0 and above required\n");
        exit(EXIT_FAILURE);
    }
}
