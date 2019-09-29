//
//  PIProcessDefines.h
//  PI_Process
//
//  Created by HUO on 2018/9/5.
//  Copyright © 2018 sjdd. All rights reserved.
//

#ifndef PIProcessDefines_h
#define PIProcessDefines_h

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AVFoundation/AVCaptureVideoPreviewLayer.h>
#import <UIKit/UIKit.h>

#define PIPROCESS_VERSION   "1.9.2.0--201909261635"

typedef unsigned char BYTE;

typedef void(^pushStatusCallback)();
typedef void(^mscStatusCallback)(int);
typedef void(^psUsrMsgCallback)(const char *);
typedef void(^onCoreSdkStatus)(int, int, const char *);

typedef void(^pushStatusCallbackWithId)(int streamid);
typedef void(^mscStatusCallbackWithId)(int streamid, int callbackdata);
typedef void(^psUsrMsgCallbackWithId)(int streamid, const char *);

extern NSString * const PS_MediaServiceRestartedNotification;
extern NSString * const PS_PZVTSnapShotCompleteNotification;
extern NSString * const PS_PZVTSnapShotFailNotification;
extern NSString * const PS_NetworkStatusChangedNotification;
extern NSString * const PS_CaptureStatusChangedNotification;
extern NSString * const PS_StreamingRestartedNotification;
extern NSString * const PS_VideoEncodeSlowNotification;
extern NSString * const PS_CameraRestartNotification;
extern NSString * const PS_NetworkStatusChangedTypeKey;
extern NSString * const PS_CaptureStatusChangedTypeKey;
extern NSString * const PS_StreamPushSuccessNotification;
extern NSString * const PS_US_NeedGetReport_Push;
extern NSString * const PS_ReplaykitNoTimeNoAudioNotification;
extern NSString * const PS_ReplaykitPermissionDenied;
extern NSString * const PS_ReplaykitScreenCaptureFailed;
extern NSString * const PSAudioSamplerateWrongNotification;
extern NSString * const PS_StreamingDownNotification;
extern NSString * const PS_StreamingUpNotification;
extern NSString * const PS_StreamingDelayTooLargeNotification;
extern NSString * const PS_StreamingDelayReturnNormalNotification;


#define DATASOURCEID_RAW_MIC_AUDIO               30121
#define DATASOURCEID_MIC_DATA_AFTER_CALLBACK     30122
#define DATASOURCEID_RAW_MUSIC                   30123
#define DATASOURCEID_MIXED_AUDIO                 30124
#define DATASOURCEID_REPLAYKIT_MIC               30131
#define DATASOURCEID_REPLAYKIT_APP               30132
#define DATASOURCEID_REPLAYKIT_MIXED             30133

#define DATASOURCEID_RAW_VIDEO                   31121
#define DATASOURCEID_BEAUTIFIED_VIDEO            31122
#define DATASOURCEID_REPLAYKIT_VIDEO             31131

typedef NS_ENUM(NSInteger, PS_Audio_Encoder)
{
    PS_Audio_AAC = 0,
    PS_Audio_HEAAC = 1,
    PS_Audio_OPUS = 2
};

typedef NS_ENUM(NSInteger, PS_Video_Encoder)
{
    PS_Video_H264 = 0,
    PS_Video_HEVC = 1
    
};

extern NSString * const PS_PushFailedNotFoundKeyFrame;


typedef NS_ENUM(NSInteger, PS_PushMode)
{
    PS_PushAudioAndVideo = 0,
    PS_PushAudioOnly = 1,
    PS_PushReplaykit = 2
};

typedef NS_ENUM(NSInteger, PS_WorkingMode)
{
    // 普通模式，SDK 采集音视频，SDK 编码推流
    PS_WorkingMode_Normal = 1,
    
    // 纯音频仅编码模式，APP 采集音频，SDK 编码推流（例如 APP 录音混音的纯音频推流模式）
    PS_WorkingMode_AudioOnly_AEncode = 4,
    
    // SDK 负责音频编码、传输，视频传输；APP 负责音频采集，视频采集、预览、编码
    PS_WorkingMode_Normal_AEncode = 5,
    
    // 音视频仅编码模式，APP 采集音视频、预览视频，SDK 编码推流
    PS_WorkingMode_Normal_AEncode_VEncode = 6,
    
    // 纯音频模式，SDK 仅对音频进行采集、编码、推流处理，不涉及视频相关内容
    PS_WorkingMode_AudioOnly_ACapEncode = 8,
    
    // 视频仅编码模式，SDK 采集音频，APP 采集视频、预览视频，SDK 编码推流
    PS_WorkingMode_Normal_VEncode_ACapEncode = 9,
    
    // cocos 游戏推流模式，SDK 采集 cocos 数据（包括图像、音效）、音频数据，SDK 编码推流
    PS_WorkingMode_CocosGame = 20,
    
    // replaykit 录屏直播模式，SDK 采集音视频，SDK 编码推流
    PS_WorkingMode_ReplaykitScreenCast = 30
};

typedef NS_ENUM(NSUInteger, PS_NetworkStatusChangedType)
{
    PS_NetworkStatusChangedTypeOK    = 1,
    PS_NetworkStatusChangedTypeFail  = 0,
};


typedef NS_ENUM(NSInteger, PS_CaptureStatusChangedType)
{
    PS_CaptureStatusChangedTypeOK            = 0,
    PS_CaptureStatusChangedTypeNoVideo       = -1,
    PS_CaptureStatusChangedTypeNoAudio       = -2,
    PS_CaptureStatusChangedTypeNoAudioVideo  = -3,
};

typedef NS_ENUM(NSInteger, PS_PushBackgroundBehaviour)
{
    PS_BackgroundStop = 1,    // stop streaming in background
    PS_BackgroundPushAudio = 2    //switch to pure audio streaming in background
};

typedef NS_ENUM(NSInteger, PS_PushForegroundBehaviour)
{
    PS_BackgroundPureAudio = 1,    // resume to pure audio streaming in foreground
    PS_ForegroundResumeStreaming = 2    // resume to normal streaming in foreground
};


#define STREAMING_NUM 8

#define AUDIO_PUSH_SWITCH_NO_AUDIO  0
#define AUDIO_PUSH_SWITCH_AAC       1
#define AUDIO_PUSH_SWITCH_HEAAC     2
#define AUDIO_PUSH_SWITCH_OPUS      3

@interface PIProcessAudioSetParam : NSObject
/**
 audio params
 audio bitrate unit: bps
 audio samplerate unit: Hz
 
 matters that need atention:
 if the value between channelnum and bitrate is not matching, the audio encoder's init function will return a error. for example, if audio channelnum is 2, then audio bitrate should be larger than 64000.
 
 */
@property(nonatomic,assign) int audio_bitrate;
@property(nonatomic,assign) int samplerate;
@property(nonatomic,assign) int audio_channelnum;
/**
 push switch
 if switch is 0, that mean PSLStreaming will not push the data of this type.
 if switch is !0, that mean PSLStreaming will push the data of this type, the value indicates the codec format.
 if audio_push_switch==1, AAC is used
 if audio_push_switch==2, HEAAC is used
 if audio_push_switch==3, OPUS is used
 */
@property(nonatomic,assign) int audio_push_switch;

@property(nonatomic,assign) int audio_data_source_id;
@end



#define VIDEO_PUSH_SWITCH_NO_VIDEO  0
#define VIDEO_PUSH_SWITCH_H264      1
#define VIDEO_PUSH_SWITCH_HEVC     2

@interface PIProcessVideoSetParam: NSObject
/**
 video bitrate, unit: kb/s
 */
@property(nonatomic,assign) int video_bitrate;
/**
 video resolution
 the width and height of the video you want to send to viewer
 you need not consider the rotation of video here, the value of width should always larger than value of height
 for example, if you want set 800x450(landscape) or 450x800(portrait), just set width=800 and height=450
 */
@property(nonatomic,assign) int width;
@property(nonatomic,assign) int height;

/**
 crop video resolution
 you need not consider the rotation of video here, the value of width should always larger than value of height
 for example, if you want set 800x450(landscape) or 450x800(portrait), just set width=800 and height=450
 0 if no crop needed
 */
@property(nonatomic,assign) int crop_width;
@property(nonatomic,assign) int crop_height;
/**
 video fps
 can set video fps frome 1 to 30
 */
@property(nonatomic,assign) int video_fps;

/**
 enable/disable B frames in encoder. 0 disable
 */
@property(nonatomic,assign) int video_bflag;
/**
 video push switch
 if switch is 1, the video encode will be H.264
 if switch is 2, the video encode will be HEVC
 */
@property(nonatomic,assign) int video_push_switch;

/**
 keyframeinterval: video frames between each key frame, we usually set 2*video_fps to it
 */
@property(nonatomic,assign) int keyframeinterval;

/**
 threshold params, use absolute value
 fps_min: the min fps you can accept
 br_max: the max bitrate you can accept
 br_min: the min bitrate you can accept
 */
@property(nonatomic,assign) int fps_min;
@property(nonatomic,assign) int br_max;
@property(nonatomic,assign) int br_min;
/**
 threshold params in ratio. Value should be positive.
 */
@property(nonatomic,assign) int fps_min_ratio;
@property(nonatomic,assign) int br_max_ratio;
@property(nonatomic,assign) int br_min_ratio;

/**
 Set to 0xffff to disable bandwidth adaption.
 other values, please contact developer support.
 */
@property(nonatomic,assign) int adjust_ratio;

@property(nonatomic,assign) int video_data_source_id;

/**
 0 for data sent to piprocess is raw data, encoding is needed
 1 for data sent to piprocess is already encoded, no more encoding is needed
 */
@property(nonatomic,assign) int video_data_encoded;
@end

@interface PIProcessDataSetParam : NSObject
@property(nonatomic,assign) int datasource;
@property(nonatomic,assign) int format;
@property(nonatomic,assign) int width;
@property(nonatomic,assign) int height;
@property(nonatomic,assign) int fps;
@property(nonatomic,assign) float keyinterval_sec;
@property(nonatomic,assign) int adjust_fps_min_ratio;
@end


/**
 @brief App set params to libP31 through this class
 */
@interface PIProcessSetParam : NSObject
/**
 set the address you want to PSLStreaming push stream to
 more info refering to url rule document
 */
@property(nonatomic,assign) char *url;
/**
 Must be 1;
 */
@property(nonatomic,assign) int txtype;

/**
 the max Delay that lib can accept, if delay is larger than this value, lib will not send video data
 unit: millisecond
 */
@property(nonatomic,assign) int maxDelayThreshold;

@property(nonatomic,strong) NSArray<PIProcessVideoSetParam*> *video_param;

@property(nonatomic,strong) NSArray<PIProcessAudioSetParam*> *audio_param;

@property(nonatomic,strong) NSArray<PIProcessDataSetParam*> *data_param;

@property(nonatomic,assign) PS_WorkingMode working_mode;
@end

/**
 @brief params return to surface
 */
typedef struct _INTERFACE_GET_PARAMS
{
    /**
     info of bitrate, unit: kbps
     databr: the bitrate of data come from encoder
     netbr: the bitrate of data that send success
     */
    int         databr;
    int         netbr;
    
    /**
     if networkstatus is false, that mean push module anomaly
     if networkstatus is true, that mean push module work allright
     */
    bool        networkstatus;
    
    /* params about delay:
     delaysstatus: if current delay is larger than maxDelayThreshold, delaystatus is false, else delaystatus is true
     delayms: current delayms in push module
     */
    bool         delaystatus;
    int          delayms;
    
    /**
     totaldatasent: get the current network total sent data, unit byte.
     packetloserate: get the current network packet loss rate
     totalframesent: get the number of total frames sent
     currentfps: get the current frame rate sent per second
     frameloasecount: get the number of frames dropped
     */
    
    uint64_t    totaldatasent;
    double      packetloserate;
    uint64_t    totalframesent;
    int         currentfps;
    int         framelosecount;
    
    /**
     if capturestatus = -1,that mean video capture is error
     if capturestatus = -2,that mean audio capture is error
     if capturestatus =  0,that mean capture is alright
     */
    int          capturestatus;
    /**
     pushStatus return the status of the last pushed frame. for its value defination please refer to PSPushStatus defined in libdatabase.h
     */
    int          pushStatus;
    
    //#ifdef MPATH_VERSION
    uint64_t    totalsize;
    unsigned int mpathn;
    uint64_t     mpathusage[8];
    char        mpathName[1024];
    //#endif
    
}INTERFACE_GET_PARAMS, *PINTERFACE_GET_PARAMS;

#endif /* PIProcessDefines_h */
