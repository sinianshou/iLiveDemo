//
/*
 * Copyright (c) 2017 Powerinfo. All rights reserved.
 */
//


#import <Foundation/Foundation.h>

#import "RsCallback.h"

@interface PIPostUtil : NSObject

- (instancetype)initWithUid:(NSString*)uid;

- (void)postRoomServerWithUrl:(NSString*)url
                         body:(NSString*)body
                     callback:(id<PIRsCallback>)callback;

@end
