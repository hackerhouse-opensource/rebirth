//
//  fingerprint.m
//  rebirth
//
//  Created by User on 13/06/2018.
//  Copyright © 2018 HackerHouse. All rights reserved.
//
#import <Foundation/Foundation.h>
#include "fingerprint.h"

NSString* deviceName()
{
    struct utsname systemInfo;
    uname(&systemInfo);
    return [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
}

NSString* versionInfo()
{
    struct utsname versionInfo;
    uname(&versionInfo);
    return [NSString stringWithCString:versionInfo.version encoding:NSUTF8StringEncoding];
}

void fingerprint(){
    NSString *device = deviceName();
    NSString *device_version = versionInfo();
    struct target* targetp = NULL;
    int targetindex = 0;
    NSString *ver113 = @"xnu-4570.52.2~8"; // 11.3 - 11.3.1
    NSString *ver113beta = @"xnu-4570.52.2~3"; // 11.3 beta 6
    NSString *ver1125 = @"xnu-4570.40.9~7"; // 11.2.5 - 11.2.6
    NSString *ver112 = @"xnu-4570.32.1~1"; // 11.2 - 11.2.2
    NSString *ver111 = @"xnu-4570.20.62~4"; //11.1 - 11.1.2 
    NSString *ver110 = @"xnu-4570.2.5~167"; // 11.0 - 11.0.3
    if([device_version containsString:ver113]||[device_version containsString:ver113beta]){
        printf("Found a valid 11.3 - 11.3.1 target\n");
        targetindex = targetno_11_3_1;
        targetp = (struct target *)&targets_11_3_1;
    }
    else if([device_version containsString:ver1125]){
        printf("Found a valid 11.2.5 - 11.2.6 target\n");
        targetindex = targetno_11_2_6;
        targetp = (struct target *)&targets_11_2_6;
    }
    else if([device_version containsString:ver112]){
        printf("Found a valid 11.2 - 11.2.2 target\n");
        targetindex = targetno_11_2_2;
        targetp = (struct target *)&targets_11_2_2;
    }
    else if([device_version containsString:ver111]){
        printf("Found a valid 11.1 - 11.1.2 target\n");
        targetindex = targetno_11_1_2;
        targetp = (struct target *)&targets_11_1_2;
    }
    else if([device_version containsString:ver110]){
        printf("Found a valid 11.0 - 11.0.3 target\n");
        targetindex = targetno_11_0_3;
        targetp = (struct target *)&targets_11_0_3;
    }
    if(targetindex!=0 & targetp != NULL){
        for(int count = 0; count < targetindex; count++){
            NSString *target = @(targetp[count].name);
            if ([target rangeOfString:device].location == NSNotFound) {
            } else {
                printf("Found a valid device target\n");
                kernel_base = targetp[count].kernel_base;
            }
        }
    }
    NSLog(@"%@",device_version);
}
