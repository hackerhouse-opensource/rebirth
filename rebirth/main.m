//  rebirth
//  =======
//  security research and development tool for exploring iOS based devices
//  using tfp0 related exploits. Provides interfaces and exploration tools
//  to assist in finding kernel symbols, dumping memory, acquiring contacts
//  and interacting with vulnerable devices. This is the iOS agent component
//  to be deployed onto an affected device.
//
//  The following peoples code has been re-used in parts of rebirth or are
//  credited for techniques used by this utility. Thank you Ian Beer, comex,
//  Johnathan Levin, Johnathan Swain, p0sixninja, Bryce Bearchell, CoolStar
//  & jakeajames.

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

int main(int argc, char * argv[]) {
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
