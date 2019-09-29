//
//  PICocosRemotePusher.h
//  transcoder
//
//  Created by swj-macbook on 2019/1/24.
//  Copyright © 2019 powersmart. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WebKit/WebKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface PICocosRemoteController : NSObject <WKScriptMessageHandler>
- (void) testPzvt;
@end

NS_ASSUME_NONNULL_END
