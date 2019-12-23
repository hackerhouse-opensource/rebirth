//
//  ViewController.m
//  rebirth
//
//  Created by User on 12/06/2018.
//  Copyright © 2018 HackerHouse. All rights reserved.
//
#import "ViewController.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    _textView.text = @"rebirth iOS 11.0 - 11.3.1 jailbreak utility\nwritten by https://hacker.house\npowered by QiLin framework\n";
    _pipe = [NSPipe pipe];
    _pipeHandle = [_pipe fileHandleForReading];
    dup2([[_pipe fileHandleForWriting] fileDescriptor], fileno(stderr));
    dup2([[_pipe fileHandleForWriting] fileDescriptor], fileno(stdout));
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(handleNotification:) name: NSFileHandleReadCompletionNotification object: _pipeHandle] ;
    [_pipeHandle readInBackgroundAndNotify] ;
    _textView.layoutManager.allowsNonContiguousLayout = NO;
    _textView.scrollEnabled = TRUE;
    _textView.userInteractionEnabled = TRUE;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)didTouchUp:(id)sender {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self buttonPress];
    });
}

-(void)handleNotification:(NSNotification *)notification{
    [_pipeHandle readInBackgroundAndNotify];
    NSString *str = [[NSString alloc] initWithData: [[notification userInfo] objectForKey: NSFileHandleNotificationDataItem] encoding: NSASCIIStringEncoding] ;
    _textView.text = [_textView.text stringByAppendingString: str];
    [_textView scrollRangeToVisible:NSMakeRange(_textView.text.length - 1, 1)];
}

- (void) buttonPress {
    if(!_isRunning){
        _isRunning = true;
        multipath_exploit();
        uint64_t kernel_base = 0;
        kernel_base = dump_kernel(tfp0, kernel_base);
        //uint64_t kaslr = kernel_base + 0xFF8FFC000;
        initQiLin(tfp0, kernel_base);
        rootifyMe();
        ShaiHuludMe(0); // simple fix
        platformizeMe();
        printf("borrowing entitlements...\n");
        borrowEntitlementsFromDonor("/usr/bin/sysdiagnose","-u");
        sleep(4);
        printf("castrate AMFID...\n");
        castrateAmfid(); // code signing disabled!*/
        char* amfidebilitate = NULL;
        char* bundle_root = bundle_path();
        asprintf(&amfidebilitate, "%s/binpack/amfidebilitate", bundle_root);
        chmod(amfidebilitate, 0655);
        spawnAndPlatformize(amfidebilitate,0,0,0,0,0);
        remount_root(apfs_snapshot);
        drop_payload();
/*      pid_t pid = fork(); // enable debug web server
        if(pid){
            drop_payload();
        } else{
            init_ws(tfp0, kernel_base);
            wsmain(0);
        }*/
    }
}
@end
