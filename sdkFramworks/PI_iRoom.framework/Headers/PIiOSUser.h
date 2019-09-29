//
//  PIiOSUser.h
//  PI_iRoom
//
//  Created by kun on 2019/7/7.
//  Copyright © 2019 Beijing Powerinfo Software Co., Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Cap.h"

NS_ASSUME_NONNULL_BEGIN

@interface PIiOSUser : PICap_User <NSCopying>
@property NSString *uid;
@property NSString *ve_name;

- (instancetype)initWithUid:(NSString*)uid
                 WithVeName:(NSString*)veName;
@end

NS_ASSUME_NONNULL_END



