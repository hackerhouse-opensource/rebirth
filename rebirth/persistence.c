//
//  persistence.c
//  rebirth
//
//  Created by User on 25/11/2019.
//  Copyright © 2019 HackerHouse. All rights reserved.
//
#include "persistence.h"

/* 11.3 apfs snapshots
 bash-3.2# ioreg -p IODeviceTree -l | grep boot-manifest-hash
     | |   "boot-manifest-hash" = <cc574d249ec4457b63007116ce6cd9ab1407932e>
 bash-3.2# mount | grep com.apple
 com.apple.os.update-CC574D249EC4457B63007116CE6CD9AB1407932E@/dev/disk0s1s1 on / (apfs, local, nosuid, read-only, journaled, noatime)
 
 -rwxr-xr-x  1 root  wheel  522176 Mar 13  2018 /System/Library/Filesystems/apfs.fs/apfs.util
 -rwxr-xr-x  1 root  wheel   36912 Mar 13  2018 /System/Library/Filesystems/apfs.fs/apfs_stats
 -rwxr-xr-x  1 root  wheel  690032 Mar 13  2018 /System/Library/Filesystems/apfs.fs/fsck_apfs
 -rwxr-xr-x  1 root  wheel   37392 Mar 13  2018 /System/Library/Filesystems/apfs.fs/mount_apfs
 -rwxr-xr-x  1 root  wheel  554352 Mar 13  2018 /System/Library/Filesystems/apfs.fs/newfs_apfs
 
 bash-3.2# /System/Library/Filesystems/apfs.fs/apfs.util -p /dev/disk0s1s1
 System
 bash-3.2# /System/Library/Filesystems/apfs.fs/apfs.util -p /dev/disk0s1s2
 Data
 bash-3.2# /System/Library/Filesystems/apfs.fs/apfs.util -p /dev/disk0s1s3
 Baseband Data
 bash-3.2#
*/
int do_create(int dirfd, const char *vol, const char *snap) {
    int ret = fs_snapshot_create(dirfd, snap, 0);
    if (ret != 0)
        printf("fs_snapshot_create error\n");
    return ret;
}

int do_rename(int dirfd, const char *vol, const char *snap, const char *nw) {
    int ret = fs_snapshot_rename(dirfd, snap, nw, 0);
    if (ret != 0)
        printf("fs_snapshot_rename error\n");
    return ret;
}

int check_snapshot(int dirfd, const char *vol, const char *snap) {
    struct attrlist alist = {0};
    char abuf[2048];
    alist.commonattr = ATTR_BULK_REQUIRED;
    // invalid argument
    int count = fs_snapshot_list(dirfd, &alist, &abuf[0], sizeof(abuf), 0);
    if (count < 0) {
        perror("fs_snapshot_list error\n");
        return -1;
    }
    char *p = &abuf[0];
    for (int i = 0; i < count; i++) {
        char *field = p;
        uint32_t len = *(uint32_t *)field;
        field += sizeof(uint32_t);
        attribute_set_t attrs = *(attribute_set_t *)field;
        field += sizeof(attribute_set_t);
        if (attrs.commonattr & ATTR_CMN_NAME) {
            attrreference_t ar = *(attrreference_t *)field;
            const char *name = field + ar.attr_dataoffset;
            field += sizeof(attrreference_t);
            if (strcmp(name, snap) == 0) {
                return 1;
            }
        }
        p += len;
    }
    return 0;
}

char *find_system_snapshot(int dirfd) {
    struct attrlist alist = {0};
    char abuf[2048];
    alist.commonattr = ATTR_BULK_REQUIRED;
    int count = fs_snapshot_list(dirfd, &alist, &abuf[0], sizeof(abuf), 0);
    if (count < 0) {
        printf("fs_snapshot_list error\n");
        return NULL;
    }
    char *p = &abuf[0];
    for (int i = 0; i < count; i++) {
        char *field = p;
        uint32_t len = *(uint32_t *)field;
        field += sizeof(uint32_t);
        attribute_set_t attrs = *(attribute_set_t *)field;
        field += sizeof(attribute_set_t);
        if (attrs.commonattr & ATTR_CMN_NAME) {
            attrreference_t ar = *(attrreference_t *)field;
            const char *name = field + ar.attr_dataoffset;
            field += sizeof(attrreference_t);
            if (strstr(name, "com.apple.os.update-")) {
                return strdup(name);
            }
        }
        p += len;
    }
    return NULL;
}

/*void remountRootAsRW(){
  char *devpath = strdup(“/dev/disk0s1s1”);
  uint64_t devVnode = getVnodeAtPath(devpath);
  writeKern(devVnode + off_v_specflags, 0); // clear dev vnode’s v_specflags

  // 1. make a new mount of the device of root partition
  char *newMPPath = strdup(“/private/var/mobile/tmp”);
  createDirAtPath(newMPPath);
  mountDevAtPathAsRW(devPath, newMPPath);

  // 2. Get mnt_data from the new mount
  uint64_t newMPVnode = getVnodeAtPath(newMPPath);
  uint64_t newMPMount = readKern(newMPVnode + off_v_mount);
  uint64_t newMPMountData = readKern(newMPMount + off_mnt_data);

  // 3. Modify root mount’s flag and remount
  uint64_t rootVnode = getVnodeAtPath(“/”);
  uint64_t rootMount = readKern(rootVnode + off_v_mount);
  uint32_t rootMountFlag = readKern(rootMount + off_mnt_flag);
  writeKern(rootMount + off_mnt_flag, rootMountFlag & ~ ( MNT_NOSUID | MNT_RDONLY | MNT_ROOTFS));
  mount(“apfs”, “/”, MNT_UPDATE, &devpath);

  // 4. Replace root mount’s mnt_data with new mount’s mnt_data
  writeKern(rootMount + off_mnt_data, newMPMountData);
} */

int postsnapshot_remount(){
    char *dev_path = "/dev/disk0s1s1";
    char *mnt_path = "/var/rootmnt";
    struct hfs_mount_args mntargs;
    uint64_t ucred = get_kern_cred();
    printf("Attempting to remount rootFS...\n");
    // "/private/var/MobileSoftwareUpdate/mnt1"
    uint64_t rootVnodeAddr = getVnodeByPathName(dev_path);
    // implement - "a better kernel arbitrary call gadget"
    // must be able to call kernel functions for this to succeed.
    // need the specinfo flags of the proper vnode.
    printf("vnode is at %llx\n",rootVnodeAddr); // needs to be disk0s1s1 vnode
    uint64_t specInfo = rk64(rootVnodeAddr + 116);
    wk32((specInfo + 16), 0); // specinfo::si_flags
    if(access(mnt_path,F_OK)){
        printf("cleaning up old dir\n");
        rmdir(mnt_path);
    }
    mkdir(mnt_path, 0755);
    chown(mnt_path, 0, 0);
    bzero(&mntargs, sizeof(struct hfs_mount_args));
    mntargs.fspec = dev_path;
    mntargs.hfs_mask = 1;
    gettimeofday(NULL, &mntargs.hfs_timezone);
    int rvtmp = mount("apfs", mnt_path, 0, (void *)&mntargs);
    printf("mount: %d\n", rvtmp);
    int dirfd = open(mnt_path, O_RDONLY, 0);
    restore_cred(ucred);
    if (dirfd < 0) {
        perror("open mnt_path");
        return -1;
    }
    if(check_snapshot(dirfd, "/", "rebirth_system_snapshot")==1) {
        printf("already renamed snapshot, nothing todo.\n");
        return -2;
    }
    // check for BootKey snapshot
    printf("finding system snapshot\n");
    char *system_snapshot = find_system_snapshot(dirfd);
    printf("system_snapshot: %s\n", system_snapshot);
    //int rvrename = do_rename(ROOTFSMNT, systemSnapshot, newSystemSnapshot);
    unmount(mnt_path,0);
    rmdir(mnt_path);
    return 0;
}

int presnapshot_remount(){
    uint64_t rootVnodeAddr = findKernelSymbol("_rootvnode");
    uint64_t *actualVnodeAddr;
    struct vnode *rootvnode = 0;
    char *v_mount;
    printf("Attempting to remount rootFS...\n");
    readKernelMemory(rootVnodeAddr, sizeof(void *), (void*)&actualVnodeAddr);
    readKernelMemory(*actualVnodeAddr, sizeof(struct vnode), (void*)&rootvnode);
    readKernelMemory((uint64_t)rootvnode->v_mount, 0x100, (void*)&v_mount);
    // Disable MNT_ROOTFS momentarily, remounts , and then flips the flag back
    uint32_t mountFlags = (*(uint32_t * )(v_mount + 0x70)) & ~(MNT_ROOTFS | MNT_RDONLY);
    writeKernelMemory(((uint64_t)rootvnode->v_mount) + 0x70 ,sizeof(mountFlags), &mountFlags);
    char *opts = strdup("/dev/disk0s1s1");
    // Not enough to just change the MNT_RDONLY flag - we have to call
    // mount(2) again, to refresh the kernel code paths for mounting..
    int rc = mount("apfs", "/", MNT_UPDATE, (void *)&opts);
    printf("RC: %d (flags: 0x%x) %s \n", rc, mountFlags, strerror(errno));
    mountFlags |= MNT_ROOTFS;
    writeKernelMemory(((uint64_t)rootvnode->v_mount)+0x70,sizeof(mountFlags),&mountFlags);
    int fd = open ("/.xxx", O_TRUNC| O_CREAT);
    if (fd < 0) {
        printf("Failed to remount /");
        return -1;
    }
    else {
        printf("Successfully remounted rootFS\n");
        unlink("/.xxx"); // clean up
    }
    return 0;
}

int remount_root(int snapshot_enabled){
    if(snapshot_enabled==1){
        postsnapshot_remount();
    }
    else{
        presnapshot_remount();
    }
    return 0;
}
