//
//  IJKFFmpegApi.h
//  IJKMediaPlayer
//
//  Created by Bai Shuai on 2019/6/17.
//  Copyright © 2019 PowerInfo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PIFFmpegApi : NSObject

+ (long) GetMediaDuration:(NSString *)url  withHeader:(NSString * _Nullable)header withUserAgent:(NSString * _Nullable)user_agent;

@end

NS_ASSUME_NONNULL_END
