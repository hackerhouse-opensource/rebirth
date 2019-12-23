//
//  multipath_targets.c
//  rebirth
//
//  Created by User on 12/06/2018.
//  Copyright © 2018 HackerHouse. All rights reserved.
//
#include "targets.h"

const int targetno_11_3_1 = 23; // iPad 6th gen shipped
const int targetno_11_2_6 = 22;
const int targetno_11_2_2 = 22;
const int targetno_11_1_2 = 22; // iPhone X introduced
const int targetno_11_0_3 = 21;

// 11.3 - 11.3.1 targets by devices
struct target targets_11_3_1[] = {
    { // iPad Air 2
        "iPad5,3 iPad5,4", // iPad_64bit_TouchID_11.3.1_15E302_Restore.ipsw
        0xfffffff0074c5d44 // kernelcache.release.ipad5b
        // 0882c7dec9c970c1ede1aa43babdff63f0149eb0
    },
    { // iPad Air
        "iPad4,1 iPad4,2 iPad4,3", // iPad_64bit_11.3.1_15E302_Restore.ipsw
        0xfffffff0074b9aa0 // kernelcache.release.ipad4
        // a883eb5343947d70df7b68f7fa7ca76649710114
    },
    { // iPad Pro (12.9-inch)
        "iPad6,7 iPad6,8", // iPadPro_12.9_11.3.1_15E302_Restore.ipsw
        0xfffffff0074bf3cc // kernelcache.release.ipad6d
        //a58524a05fe3f58e363437167f7fbea33175eb3f
    },
    { // iPad Pro (9.7-inch)
        "iPad6,3 iPad6,4", // iPadPro_9.7_11.3.1_15E302_Restore.ipsw
        0xfffffff0074bf3cc // kernelcache.release.ipad6b
        // f5a659e8356d1d70d6ba63597864b9e84c1877e5
    },
    { //iPad (5th generation)
        "iPad6,11 iPad6,12", // iPad_64bit_TouchID_ASTC_11.3.1_15E302_Restore.ipsw
        0xfffffff0074bf3cc   // kernelcache.release.ipad6f
        //aad6ac807ff8729aadd42351d322f6b930ce9393
    },
    { //iPad (6th generation)
        "iPad7,5 iPad7,6", // iPad_64bit_TouchID_ASTC_11.3.1_15E302_Restore.ipsw
        0xfffffff007508ac0 // kernelcache.release.ipad7b
        //aad6ac807ff8729aadd42351d322f6b930ce9393
    },
    { //iPad Pro (12.9-inch, 2nd generation)
        "iPad7,1 iPad7,2", // iPad_Pro_HFR_11.3.1_15E302_Restore.ipsw
        0xfffffff007508b1c // kernelcache.release.ipad7
        // c22014ec414d44437f32d7c342aeeb5e6eda8e2e
    },
    { //iPad Pro (10.5-inch)
        "iPad7,3 iPad7,4", // iPad_Pro_HFR_11.3.1_15E302_Restore.ipsw
        0xfffffff007508b1c // kernelcache.release.ipad7
        // c22014ec414d44437f32d7c342aeeb5e6eda8e2e
    },
    
    { //iPad mini 2
        "iPad4,4 iPad4,5 iPad4,6", // iPad_64bit_11.3.1_15E302_Restore.ipsw
        0xfffffff0074b9aa0 // kernelcache.release.ipad4b
        // a883eb5343947d70df7b68f7fa7ca76649710114
    },
    { // iPad mini 3
        "iPad4,7 iPad4,8 iPad4,9", // iPad_64bit_TouchID_11.3.1_15E302_Restore.ipsw
        0xfffffff0074b9aa0 // kernelcache.release.ipad4bm
        // 0882c7dec9c970c1ede1aa43babdff63f0149eb0
    },
    { // iPad mini 4
        "iPad5,2 iPad5,1", // iPad_64bit_TouchID_11.3.1_15E302_Restore.ipsw
        0xFFFFFFF0074c5d08 // kernelcache.release.ipad5
        // 0882c7dec9c970c1ede1aa43babdff63f0149eb0
    },
    { // iPhone 5s
        "iPhone6,1 iPhone6,2", // iPhone_4.0_64bit_11.3.1_15E302_Restore.ipsw
        0xfffffff0074b9aa0 // kernelcache.release.iphone6
        // dd1d1c8ff8afcd1d5f6f4cf30eb3d12a777beb3e
    },
    { //iPhone 6
        "iPhone7,2", // iPhone_4.7_11.3.1_15E302_Restore.ipsw
        0xfffffff0074c5d08  // kernelcache.release.iphone7
        //dae0911e040a9717233e4c751939985ede6c7bf8
    },
    { //iPhone 6s
        "iPhone8,1", // iPhone_4.7_11.3.1_15E302_Restore.ipsw
        0xfffffff0074bf3cc // kernelcache.release.n71
    }, // dae0911e040a9717233e4c751939985ede6c7bf8
    { //iPhone 6 Plus
        "iPhone7,1", // iPhone_5.5_11.3.1_15E302_Restore
        0xfffffff0074c5d08 // kernelcache.release.iphone7
        // 706a0d92aaa759aef92e8622d8807b28bf05900d
    },
    { //iPhone 6s Plus
        "iPhone8,2", // iPhone_5.5_11.3.1_15E302_Restore
        0xfffffff0074bf3cc // kernelcache.release.n66
    }, // 706a0d92aaa759aef92e8622d8807b28bf05900d
    { //iPhone 7
        "iPhone9,1 iPhone9,3", // iPhone_4.7_P3_11.0_11.3.1_15E302_Restore.ipsw
        0xfffffff007508ac0 //
        // 00f8a05f2e1480e3f4d92932081a35d00b7980cd
    },
    { // iPhone 7 Plus
        "iPhone9,2 iPhone9,4", // iPhone_5.5_P3_11.0_11.3.1_15E302_Restore.ipsw
        0xfffffff007508ac0   // kernelcache.release.iphone9
        // d8f80e4696d50112b0561989a88155c16bdf52e7
    },
    { // iPhone 8
        "iPhone10,1 iPhone10,4", // iPhone_4.7_P3_11.0_11.3.1_15E302_Restore.ipsw
        0xfffffff007529a1c // kernelcache.release.iphone10
        // 00f8a05f2e1480e3f4d92932081a35d00b7980cd
    },
    { //iPhone 8 Plus
        "iPhone10,2 iPhone10,5", // iPhone_5.5_P3_11.0_11.3.1_15E302_Restore.ipsw
        0xfffffff007529a1c // kernelcache.release.iphone10
        // d8f80e4696d50112b0561989a88155c16bdf52e7
    },
    { // iPhone SE
        "iPhone8,4", // iPhone_4.0_64bit_11.3.1_15E302_Restore.ipsw
        0xfffffff0074bf3cc // kernelcache.release.iphone8b
        // dd1d1c8ff8afcd1d5f6f4cf30eb3d12a777beb3e
    },
    { // iPhone X
        "iPhone10,3 iPhone10,6", // iPhone10,3,iPhone10,6_11.3.1_15E302_Restore.ipsw
        0xfffffff007529a1c       // kernelcache.release.iphone10b (obfuscated entry?)
        // be04218488a3b785174664ba8914968cb0b3fcee
    },
    { // iPod touch (6th generation)
        "iPod7,1", // iPodtouch_11.3.1_15E302_Restore.ipsw
        0xfffffff0074c5d08 // kernelcache.release.n102
        // 4b2d5b75f2cd7e87b7016e73b4eac6b240433188
    }
};

// 11.2.6 - 11.2.5
struct target targets_11_2_6[] = {
    { // iPad Air
        "iPad4,1 iPad4,2 iPad4,3",
        0xfffffff0074a0bc0  // kernelcache.release.ipad4
    },
    { //  iPad Air 2
        "iPad5,3 iPad5,4",
        0xfffffff0074ace34  // kernelcache.release.ipad5b
    },
    { // iPad Pro (12.9-inch)
        "iPad6,7 iPad6,8",
        0xfffffff0074a6330 // kernelcache.release.ipad6d
    },
    { // iPad Pro (9.7-inch)
        "iPad6,3 iPad6,4",
        0xfffffff0074a6330 // kernelcache.release.ipad6b
    },
    { // iPad (5th generation)
        "iPad6,11 iPad6,12",
        0xfffffff0074a6330 // kernelcache.release.ipad6f
    },
    { // iPad Pro (12.9-inch, 2nd generation)
        "iPad7,1 iPad7,2",
        0xfffffff0074ef87c //  kernelcache.release.ipad7.decompressed
    },
    { // iPad Pro (10.5-inch)
        "iPad7,3 iPad7,4",
        0xfffffff0074ef87c //  kernelcache.release.ipad7.decompressed
    },
    { // iPhone 5s
        "iPhone6,1 iPhone6,2",
        0xfffffff0074a0bc0 // kernelcache.release.iphone6.decompressed
    },
    { // iPhone 6
        "iPhone7,2",
        0xfffffff0074ace04 // kernelcache.release.iphone7
    },
    { // iPhone 6s
        "iPhone8,1",
        0xfffffff0074a6330   // kernelcache.release.n71
    },
    { // iPhone 6 Plus
        "iPhone7,1",
        0xfffffff0074ace04 // kernelcache.release.iphone7
    },
    { // iPhone 6s Plus
        "iPhone8,2",
        0xfffffff0074a6330  // kernelcache.release.n66
    },
    { // iPhone 7
        "iPhone9,1 iPhone9,3",
        0xfffffff0074ef84c  // kernelcache.release.iphone9
    },
    { // iPhone 7 Plus
        "iPhone9,2 iPhone9,4",
        0xfffffff0074ef84c  // kernelcache.release.iphone9
    },
    { // iPhone 8
        "iPhone10,1 iPhone10,4",
        0xfffffff007511c68 //  kernelcache.release.iphone10
    },
    { // iPhone 8 Plus
        "iPhone10,2 iPhone10,5",
        0xfffffff007511c68 // kernelcache.release.iphone10
    },
    { // iPhone X
      "iPhone10,3 iPhone10,6",
      0xfffffff007511c68 //  kernelcache.release.iphone10b
    },
    { // iPhone SE
        "iPhone8,4",
        0xfffffff0074a6330 //  kernelcache.release.iphone8b
    },
    { // iPad mini 2
        "iPad4,4 iPad4,5 iPad4,6",
        0xfffffff0074a0bc0 // kernelcache.release.ipad4b
    },
    { // iPad mini 3
        "iPad4,7 iPad4,8 iPad4,9",
        0xfffffff0074a0bc0  // kernelcache.release.ipad4bm
    },
    { // iPad mini 4
        "iPad 5,1 iPad5,2",
        0xfffffff0074ace04  // kernelcache.release.ipad5
    },
    { // iPod touch (6th generation)
        "iPod 7,1",
        0xfffffff0074ace04  //  kernelcache.release.n102
    }
};


// 11.2.2 - 11.2
struct target targets_11_2_2[] = {
    { // iPad Air
        "iPad4,1 iPad4,2 iPad4,3",
        0xfffffff0074a0b08  // kernelcache.release.ipad4
    },
    { //  iPad Air 2
        "iPad5,3 iPad5,4",
        0xfffffff0074acd7c // kernelcache.release.ipad5b
    },
    { // iPad Pro (12.9-inch)
        "iPad6,7 iPad6,8",
        0xfffffff0074a634c // kernelcache.release.ipad6d
    },
    { // iPad Pro (9.7-inch)
        "iPad6,3 iPad6,4",
        0xfffffff0074a634c  // kernelcache.release.ipad6b
    },
    { // iPad (5th generation)
        "iPad6,11 iPad6,12",
        0xfffffff0074a634c // kernelcache.release.ipad6f
    },
    { // iPad Pro (12.9-inch, 2nd generation)
        "iPad7,1 iPad7,2",
        0xfffffff0074ef898 //  kernelcache.release.ipad7.decompressed
    },
    { // iPad Pro (10.5-inch)
        "iPad7,3 iPad7,4",
        0xfffffff0074ef898 //  kernelcache.release.ipad7.decompressed
    },
    { // iPhone 5s
        "iPhone6,1 iPhone6,2",
        0xfffffff0074a0b08 // kernelcache.release.iphone6.decompressed
    },
    { // iPhone 6
        "iPhone7,2",
        0xfffffff0074acd4c // kernelcache.release.iphone7
    },
    { // iPhone 6s
        "iPhone8,1",
        0xfffffff0074a634c // kernelcache.release.n71
    },
    { // iPhone 6 Plus
        "iPhone7,1",
        0xfffffff0074acd4c // kernelcache.release.iphone7
    },
    { // iPhone 6s Plus
        "iPhone8,2",
        0xfffffff0074a634c  // kernelcache.release.n66
    },
    { // iPhone 7
        "iPhone9,1 iPhone9,3",
        0xfffffff0074ef868 // kernelcache.release.iphone9
    },
    { // iPhone 7 Plus
        "iPhone9,2 iPhone9,4",
        0xfffffff0074ef868 // kernelcache.release.iphone9
    },
    { // iPhone 8
        "iPhone10,1 iPhone10,4",
        0xfffffff007511cb8 //  kernelcache.release.iphone10
    },
    { // iPhone 8 Plus
        "iPhone10,2 iPhone10,5",
        0xfffffff007511cb8 // kernelcache.release.iphone10
    },
    { // iPhone SE
        "iPhone8,4",
        0xfffffff0074a634c //  kernelcache.release.iphone8b
    },
    { // iPhone X
        "iPhone10,3 iPhone10,6",
        0xfffffff007511cb8 //  kernelcache.release.iphone10b
    },
    { // iPad mini 2
        "iPad4,4 iPad4,5 iPad4,6",
        0xfffffff0074a0b08  // kernelcache.release.ipad4b
    },
    { // iPad mini 3
        "iPad4,7 iPad4,8 iPad4,9",
        0xfffffff0074a0b08  // kernelcache.release.ipad4bm
    },
    { // iPad mini 4
        "iPad 5,1 iPad5,2",
        0xfffffff0074acd4c // kernelcache.release.ipad5
    },
    { // iPod touch (6th generation)
        "iPod 7,1",
        0xfffffff0074acd4c  //  kernelcache.release.n102
    }
};

// 11.1 - 11.1.2 (using 11.1 offsets)
struct target targets_11_1_2[] = {
    { // iPad Air
        "iPad4,1 iPad4,2 iPad4,3",
        0xfffffff007491894 // kernelcache.release.ipad4
    },
    { //  iPad Air 2
        "iPad5,3 iPad5,4", // iPad_64bit_TouchID_11.1_15B93_Restore
        0xfffffff0074a1b04 // kernelcache.release.ipad5b
        // 6f30c5e0cd49b3612c1685e8edefedd065436b3c
    },
    { // iPad Pro (12.9-inch)
        "iPad6,7 iPad6,8",
        0xfffffff00748a5f0 // kernelcache.release.ipad6d
    },
    { // iPad Pro (9.7-inch)
        "iPad6,3 iPad6,4",
        0xfffffff00748a5f0 // kernelcache.release.ipad6b
    },
    { // iPad (5th generation)
        "iPad6,11 iPad6,12",
        0xfffffff00748a5f0 // kernelcache.release.ipad6f
    },
    { // iPad Pro (12.9-inch, 2nd generation)
        "iPad7,1 iPad7,2",
        0xfffffff0074d4584 //  kernelcache.release.ipad7.decompressed
    },
    { // iPad Pro (10.5-inch)
        "iPad7,3 iPad7,4",
        0xfffffff0074d4584 //  kernelcache.release.ipad7.decompressed
    },
    { // iPhone 5s
        "iPhone6,1 iPhone6,2",
        0xfffffff007491894 // kernelcache.release.iphone6.decompressed
    },
    { // iPhone 6
        "iPhone7,2",
        0xfffffff0074a1af4 // kernelcache.release.iphone7
    },
    { // iPhone 6s
        "iPhone8,1",
        0xffffff00748a5f0 // kernelcache.release.n71
    },
    { // iPhone 6 Plus
        "iPhone7,1",
        0xfffffff0074a1af4 // kernelcache.release.iphone7
    },
    { // iPhone 6s Plus
        "iPhone8,2",
        0xfffffff00748a5f0 // kernelcache.release.n66
    },
    { // iPhone 7
        "iPhone9,1 iPhone9,3",
        0xfffffff0074d4574 // kernelcache.release.iphone9
    },
    { // iPhone 7 Plus
        "iPhone9,2 iPhone9,4",
        0xfffffff0074d4574  // kernelcache.release.iphone9
    },
    { // iPhone 8
        "iPhone10,1 iPhone10,4",
        0xfffffff0074f6548 //  kernelcache.release.iphone10
    },
    { // iPhone 8 Plus
        "iPhone10,2 iPhone10,5",
        0xfffffff0074f6548 // kernelcache.release.iphone10
    },
    { // iPhone SE
        "iPhone8,4",
        0xfffffff00748a5f0 //  kernelcache.release.iphone8b
    },
    { // iPhone X
        "iPhone10,3 iPhone10,6",
        0xfffffff0074f6548 //  kernelcache.release.iphone10b
    },
    { // iPad mini 2
        "iPad4,4 iPad4,5 iPad4,6",
        0xfffffff007491894 // kernelcache.release.ipad4b
    },
    { // iPad mini 3
        "iPad4,7 iPad4,8 iPad4,9",
        0xfffffff007491894 // kernelcache.release.ipad4bm
    },
    { // iPad mini 4
        "iPad 5,1 iPad5,2",
        0xfffffff0074a1af4 // kernelcache.release.ipad5
    },
    { // iPod touch (6th generation)
        "iPod 7,1",
        0xfffffff0074a1af4  //  kernelcache.release.n102
    }
};

// 11.0.3 - 11.0
struct target targets_11_0_3[] = {
    { // iPad Air
        "iPad4,1 iPad4,2 iPad4,3",
        0xfffffff007490eb4 // kernelcache.release.ipad4
    },
    { //  iPad Air 2
        "iPad5,3 iPad5,4",
        0xfffffff0074a1124 // kernelcache.release.ipad5b
    },
    { // iPad Pro (12.9-inch)
        "iPad6,7 iPad6,8",
        0xfffffff007489ca8 // kernelcache.release.ipad6d
    },
    { // iPad Pro (9.7-inch)
        "iPad6,3 iPad6,4",
        0xfffffff007489ca8 // kernelcache.release.ipad6b
    },
    { // iPad (5th generation)
        "iPad6,11 iPad6,12",
        0xfffffff007489ca8 // kernelcache.release.ipad6f
    },
    { // iPad Pro (12.9-inch, 2nd generation)
        "iPad7,1 iPad7,2",
        0xfffffff0074d3cb //  kernelcache.release.ipad7.decompressed
    },
    { // iPad Pro (10.5-inch)
        "iPad7,3 iPad7,4",
        0xfffffff0074d3cb //  kernelcache.release.ipad7.decompressed
    },
    { // iPhone 5s
        "iPhone6,1 iPhone6,2",
        0xfffffff007490eb4 // kernelcache.release.iphone6.decompressed
    },
    { // iPhone 6
        "iPhone7,2",
        0xfffffff0074a1114 // kernelcache.release.iphone7
    },
    { // iPhone 6s
        "iPhone8,1",
        0xfffffff007489ca8   // kernelcache.release.n71
    },
    { // iPhone 6 Plus
        "iPhone7,1",
        0xfffffff0074a1114 // kernelcache.release.iphone7
    },
    { // iPhone 6s Plus
        "iPhone8,2",
        0xfffffff007489ca8 // kernelcache.release.n66
    },
    { // iPhone 7
        "iPhone9,1 iPhone9,3",
        0xfffffff0074d3cac // kernelcache.release.iphone9
    },
    { // iPhone 7 Plus
        "iPhone9,2 iPhone9,4",
        0xfffffff0074d3cac // kernelcache.release.iphone9
    },
    { // iPhone 8
        "iPhone10,1 iPhone10,4",
        0xfffffff0074f5d74 //  kernelcache.release.iphone10
    },
    { // iPhone 8 Plus
        "iPhone10,2 iPhone10,5",
        0xfffffff0074f5d74 // kernelcache.release.iphone10
    },
    { // iPhone SE
        "iPhone8,4",
        0xfffffff007489ca8 //  kernelcache.release.iphone8b
    },
    { // iPad mini 2
        "iPad4,4 iPad4,5 iPad4,6",
        0xfffffff007490eb4 // kernelcache.release.ipad4b
    },
    { // iPad mini 3
        "iPad4,7 iPad4,8 iPad4,9",
        0xfffffff007490eb4  // kernelcache.release.ipad4bm
    },
    { // iPad mini 4
        "iPad 5,1 iPad5,2",
        0xfffffff0074a1114  // kernelcache.release.ipad5
    },
    { // iPod touch (6th generation)
        "iPod 7,1",
        0xfffffff0074a1114 //  kernelcache.release.n102
    }
};
