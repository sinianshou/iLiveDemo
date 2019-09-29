//
//  CocosReceiver.h
//  IJKMediaPlayer
//
//  Created on 2018/12/13.
//  Copyright © 2018 PowerInfo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>
#import "PIPrefix.h"

//@protocol IJKMediaPlayback;
@class PIMoviePlayerController;

PI_EXTERN @interface PICocosReceiver : NSObject <WKScriptMessageHandler>

+ (instancetype)initWithWebView:(WKWebView*) webView
      withMediaPlayer:(PIMoviePlayerController *) mediaPlayer;

- (void)stopEngine;

- (void)setMediaPlayer:(PIMoviePlayerController *) _mediaPlayer;

@end
