//
//  PICocosPusher.h
//  IJKMediaFramework
//
//  Created by swj-macbook on 2018/12/14.
//  Copyright © 2018 PowerInfo. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>
#import "PSCocosEngine/pscocosremotectrlbuffer.h"


@interface PICocosPusher : NSObject <WKScriptMessageHandler>
+ (instancetype)initWithWebView:(WKWebView*)webview;
- (void)stopEngine;
- (void)start_read_nsthread;
- (int) get_pscocos_remote_ctrl_buffer:(PSCOCOS_REMOTE_CTRL_BUFFER **)result_ptr ;
- (int) get_pscocos_remote_ctrl_tag_list:(int64_t **)result_ptr :(int*)len_ptr ;
- (int) set_pscocos_remote_ctrl_flag:(int64_t)tag :(int)flag ;
@end
