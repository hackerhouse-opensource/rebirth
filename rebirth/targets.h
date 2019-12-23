//
//  multipath_targets.h
//  rebirth
//
//  Created by User on 12/06/2018.
//  Copyright © 2018 HackerHouse. All rights reserved.
//
#ifndef targets_h
#define targets_h

#include <stdio.h>

extern const int targetno_11_3_1;
extern const int targetno_11_3;
extern const int targetno_11_2_6;
extern const int targetno_11_2_2;
extern const int targetno_11_1_2;
extern const int targetno_11_0_3;

struct target {
    char* name;
    uint64_t kernel_base;
};

extern struct target targets_11_3_1[];
extern struct target targets_11_2_6[];
extern struct target targets_11_2_2[];
extern struct target targets_11_1_2[];
extern struct target targets_11_0_3[];


#endif /* multipath_targets_h */
