//
//  PINSResult.h
//  PI_iRoom
//
//  Created by kun on 2019/7/18.
//  Copyright © 2019 Beijing Powerinfo Software Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <sys/socket.h>


NS_ASSUME_NONNULL_BEGIN

@interface PINSResult : NSObject

@property NSString* targetAddr;
@property double lossRate;
@property double rttMin;
@property double rttMax;
@property double rttAvg;
@property double rttStd;

- (instancetype)initWithAddr:(NSString*)targetAddr
                  withLossRate:(double)lossRate
                  withRttMin:(double)rttMin
                  withRttMax:(double)rttMax
                  withRttAvg:(double)rttAvg
                  withRttStd:(double)rttStd;


@end

NS_ASSUME_NONNULL_END
