//
/*
 * Copyright (c) 2017 Powerinfo. All rights reserved.
 */
//


#import <Foundation/Foundation.h>

#import "Logger.h"

@interface PIiOSLogger : NSObject <PILogger>

+ (PIiOSLogger*)instance;

+ (void)logSevere:(NSString*)tag content:(NSString*)content;
+ (void)logError:(NSString*)tag content:(NSString*)content;

+ (void)setLogToConsole:(bool)toConsole;

@end
