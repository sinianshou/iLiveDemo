//
/*
 * Copyright (c) 2017 Powerinfo. All rights reserved.
 */
//


#import <Foundation/Foundation.h>

@interface PIPzvt : NSObject

+ (void)pzvtInit:(int)pNdSelect;
+ (int64_t)getOffset;
// 0 for pzvt frequency when pushing and receiving; 1 for pzvt frequency when no
// pushing or receiving; 2 for pzvt frequency when hibernating.
+ (void)togglePzvtFrequency:(int)frequencyChoice;
+ (void)hibernatePzvt;
+ (void)stopPzvt;
+ (int)resumePzvt;

@end
