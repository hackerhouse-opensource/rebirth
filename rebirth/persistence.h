//
//  persistence.h
//  rebirth
//
//  Created by User on 25/11/2019.
//  Copyright © 2019 HackerHouse. All rights reserved.
//
#ifndef persistence_h
#define persistence_h

#include <fcntl.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/attr.h>
#include <sys/snapshot.h>
#include <mach/mach.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <CoreFoundation/CoreFoundation.h>
#include "QiLin.h"
#include "kernel_helpers.h"
#include "kernel_patching.h"
#include <sys/mount.h>
#include <sys/queue.h>

LIST_HEAD(buflists, buf);

typedef void *kauth_action_t;

struct specinfo {
    struct vnode **si_hashchain;
    struct vnode *si_specnext;
    long si_flags;
    dev_t si_rdev;
};

typedef struct {
    uint64_t x[2];
} lck_mtx_t;

struct hfs_mount_args {
    char *fspec;            /* block special device to mount */
    uid_t hfs_uid;          /* uid that owns hfs files (standard HFS only) */
    gid_t hfs_gid;          /* gid that owns hfs files (standard HFS only) */
    mode_t hfs_mask;        /* mask to be applied for hfs perms  (standard HFS only) */
    u_int32_t hfs_encoding; /* encoding for this volume (standard HFS only) */
    struct timezone hfs_timezone; /* user time zone info (standard HFS only) */
    int flags;                    /* mounting flags, see below */
    int journal_tbuffer_size;     /* size in bytes of the journal transaction buffer */
    int journal_flags;            /* flags to pass to journal_open/create */
    int journal_disable;          /* don't use journaling (potentially dangerous) */
};


struct vnode {
    lck_mtx_t v_lock;            /* vnode mutex */
    TAILQ_ENTRY(vnode) v_freelist;        /* vnode freelist */
    TAILQ_ENTRY(vnode) v_mntvnodes;        /* vnodes for mount point */
    TAILQ_HEAD(, namecache) v_ncchildren;  /* name cache entries for parent */
    LIST_HEAD(, namecache) v_nclinks;   /* name cache entries that name this vnode */
    vnode_t     v_defer_reclaimlist;    /* in case we have to defer the reclaim to avoid recursion */
    uint32_t v_listflag;            /* flags protected by the vnode_list_lock (see below) */
    uint32_t v_flag;            /* vnode flags (see below) */
    uint16_t v_lflag;            /* vnode local and named ref flags */
    uint8_t     v_iterblkflags;        /* buf iterator flags */
    uint8_t     v_references;            /* number of times io_count has been granted */
    int32_t     v_kusecount;            /* count of in-kernel refs */
    int32_t     v_usecount;            /* reference count of users */
    int32_t     v_iocount;            /* iocounters */
    void *   v_owner;            /* act that owns the vnode */
    uint16_t v_type;            /* vnode type */
    uint16_t v_tag;                /* type of underlying data */
    uint32_t v_id;                /* identity of vnode contents */
    union {
        struct mount    *vu_mountedhere;/* ptr to mounted vfs (VDIR) */
        struct socket    *vu_socket;    /* unix ipc (VSOCK) */
        struct specinfo    *vu_specinfo;    /* device (VCHR, VBLK) */
        struct fifoinfo    *vu_fifoinfo;    /* fifo (VFIFO) */
        struct ubc_info *vu_ubcinfo;    /* valid for (VREG) */
    } v_un;
    struct    buflists v_cleanblkhd;        /* clean blocklist head */
    struct    buflists v_dirtyblkhd;        /* dirty blocklist head */
    struct klist v_knotes;            /* knotes attached to this vnode */
    kauth_cred_t    v_cred;            /* last authorized credential */
    kauth_action_t    v_authorized_actions;    /* current authorized actions for v_cred */
    int        v_cred_timestamp;    /* determine if entry is stale for MNTK_AUTH_OPAQUE */
    int        v_nc_generation;
    int32_t        v_numoutput;            /* num of writes in progress */
    int32_t        v_writecount;            /* reference count of writers */
    const char *v_name;            /* name component of the vnode */
    vnode_t v_parent;            /* pointer to parent vnode */
    struct lockf    *v_lockf;        /* advisory lock list head */
    int     (**v_op)(void *);        /* vnode operations vector */
    mount_t v_mount;            /* ptr to vfs we are in */
    void *    v_data;                /* private data for fs */
    struct label *v_label;            /* MAC security label */
};

int remount_root(int);
#endif /* persistence_h */
