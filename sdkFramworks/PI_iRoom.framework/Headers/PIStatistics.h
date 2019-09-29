//
/*
 * Copyright (c) 2017 Powerinfo. All rights reserved.
 */
//

#import <Foundation/Foundation.h>

#import "Statistics.h"
#import "PIiRoom.h"

@interface PIStatistics : NSObject

- (instancetype)initWithStatisticsInternal:
    (PIStatisticsInternal*)statisticsInternal;

- (void)saveTS:(StatisticsEvent)eventId andTs:(int64_t)ts;
- (void)saveTS:(StatisticsEvent)eventId;

- (int64_t)getTS:(StatisticsEvent)eventId;
- (void)log;

@end
