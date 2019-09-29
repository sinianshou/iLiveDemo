//
//  PSAudioUnitPlayer.h
//  audioUnitPlayDemo
//
//  Created by HUO on 2019/3/18.
//  Copyright © 2019 sjdd. All rights reserved.
//

#ifndef PSAudioUnitPlayer_h
#define PSAudioUnitPlayer_h

#define PSAudioUnitPlayerType_RemoteIO 0
#define PSAudioUnitPlayerType_VPIO 1

typedef struct PSAudioUnitPlayerParam {
    int type;  // PSAudioUnitPlayerType_RemoteIO or PSAudioUnitPlayerType_VPIO
    int samplerate;  // 44100 or 48000
    int channelnum;
    BOOL ifLoop;
} PSAudioUnitPlayerParam;

typedef void (^onAudioPlayComplete)(void);

@interface PSAudioUnitPlayer : NSObject
@property(nonatomic, assign) BOOL isPause;

- (int)prepareToPlay:(NSString*)filePath
               withParam:(PSAudioUnitPlayerParam*)param
    withCompleteCallback:(onAudioPlayComplete)completeCallback;

- (int)play;

- (int)stop;

- (int)pause;

- (int)resume;

- (int)resume:(int)IOType;

@end

#endif /* PSAudioUnitPlayer_h */
