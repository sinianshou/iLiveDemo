//
//  AppDelegate.m
//  iLiveDemo
//
//  Created by Easer Liu on 2019/9/29.
//  Copyright © 2019 Easer Liu. All rights reserved.
//

#import "AppDelegate.h"

#import <PI_iRoom/PIiRoom.h>
//#import <PI_iRoom/PIiOSLogger.h>

@interface AppDelegate ()

@end

@implementation AppDelegate

void uncaughtExceptionHandler(NSException* exception) {
    NSLog(@"CRASH: %@", exception);
    NSLog(@"Stack Trace: %@", [exception callStackSymbols]);
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    NSSetUncaughtExceptionHandler(&uncaughtExceptionHandler);
    
    [self config];
    
    // Override point for customization after application launch.
    return YES;
}
-(void)config{

//    [PIiOSLogger setLogToConsole:true];

    NSString *logPath = NSTemporaryDirectory();
    [PIiRoom initialize:@"iRoom" andNdSelect:999 andRSPort:80 andPISPort:81 andDomain:@"" andRSTimeoutThreshold:5000 andLogPath:logPath];
}
@end
