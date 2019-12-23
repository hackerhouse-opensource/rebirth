//
//  ViewController.h
//  rebirth
//
//  Created by User on 12/06/2018.
//  Copyright © 2018 HackerHouse. All rights reserved.
//
#import <UIKit/UIKit.h>
#include "multipath_exploit.h"
#include "kernel_helpers.h"
#include "QiLin.h"
#include "payload.h"
#include "webserver.h"
#include "targets.h"
#include "persistence.h"

@interface ViewController : UIViewController
@property NSPipe* pipe;
@property NSFileHandle* pipeHandle;
@property bool isRunning;
@property (weak, nonatomic) IBOutlet UIButton *LaunchButton;
@property (weak, nonatomic) IBOutlet UITextView *textView;
- (IBAction)didTouchUp:(id)sender;
- (void) buttonPress;
@end
