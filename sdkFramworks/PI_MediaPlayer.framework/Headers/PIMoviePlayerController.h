/*
 * PIMoviePlayerController.h
 */

#import "PIMonitor.h"
#import "PIOptions.h"
#import "PIMoviePlayerGroup.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>
#import "PIPrefix.h"
#import "PSCocosEngine/pscocosremotectrlbuffer.h"




// -----------------------------------------------------------------------------
//  MPMediaPlayback.h

PI_EXTERN NSString * const CompletePlayerSnapShot;
PI_EXTERN NSString * const PlayerSnapShotError;

PI_EXTERN NSString *const PZSPChannelEndNotification;
PI_EXTERN NSString *const PZSPInteractADVNotification;
PI_EXTERN NSString *const PZSPViewChangeEndNotification;
PI_EXTERN NSString *const PZSPViewChangedNotification;
PI_EXTERN NSString *const PZSPHttpOpenRequestBeginNotification;
PI_EXTERN NSString *const PZSPHttpRenderingStartAfterOpenRequestBeginNotification;
PI_EXTERN NSString *const PZSPRecordEndNotification;
PI_EXTERN NSString *const PZSPDecErrNotification;
PI_EXTERN NSString *const PIMoviePlayerPlaybackShutdownDidFinish;
PI_EXTERN NSString *const PIMoviePlayerPlaybackInitNeedRetry;

// Posted when the prepared state changes of an object conforming to the MPMediaPlayback protocol changes.
// This supersedes MPMoviePlayerContentPreloadDidFinishNotification.
PI_EXTERN NSString *const PIMediaPlaybackIsPreparedToPlayDidChangeNotification;

// -----------------------------------------------------------------------------
//  MPMoviePlayerController.h
//  Movie Player Notifications

// Posted when the scaling mode changes.
PI_EXTERN NSString* const PIMoviePlayerScalingModeDidChangeNotification;

// Posted when movie playback ends or a user exits playback.
PI_EXTERN NSString* const PIMoviePlayerPlaybackDidFinishNotification;
PI_EXTERN NSString* const PIMoviePlayerPlaybackDidFinishReasonUserInfoKey; // NSNumber (PIMovieFinishReason)

// Posted when the playback state changes, either programatically or by the user.
PI_EXTERN NSString* const PIMoviePlayerPlaybackStateDidChangeNotification;

// Posted when the network load state changes.
PI_EXTERN NSString* const PIMoviePlayerLoadStateDidChangeNotification;

// Posted when the movie player begins or ends playing video via AirPlay.
PI_EXTERN NSString* const PIMoviePlayerIsAirPlayVideoActiveDidChangeNotification;

// -----------------------------------------------------------------------------
// Movie Property Notifications

// Calling -prepareToPlay on the movie player will begin determining movie properties asynchronously.
// These notifications are posted when the associated movie property becomes available.
PI_EXTERN NSString* const PIMovieNaturalSizeAvailableNotification;

// -----------------------------------------------------------------------------
//  Extend Notifications

PI_EXTERN NSString *const PIMoviePlayerVideoDecoderOpenNotification;
PI_EXTERN NSString *const PIMoviePlayerFirstVideoFrameRenderedNotification;
PI_EXTERN NSString *const PIMoviePlayerFirstAudioFrameRenderedNotification;
PI_EXTERN NSString *const PIMoviePlayerHttpOpenRequestBeginNotification;


PI_EXTERN NSString *const PIMoviePlayerFlowKBytesUpdateNotification;

PI_EXTERN NSString *const PIMoviePlayerDidSeekCompleteNotification;
PI_EXTERN NSString *const PIMoviePlayerDidSeekCompleteTargetKey;
PI_EXTERN NSString *const PIMoviePlayerDidSeekCompleteErrorKey;


typedef enum PILogLevel {
    k_PI_LOG_UNKNOWN = 0,
    k_PI_LOG_DEFAULT = 1,
    
    k_PI_LOG_VERBOSE = 2,
    k_PI_LOG_DEBUG   = 3,
    k_PI_LOG_INFO    = 4,
    k_PI_LOG_WARN    = 5,
    k_PI_LOG_ERROR   = 6,
    k_PI_LOG_FATAL   = 7,
    k_PI_LOG_SILENT  = 8,
} PILogLevel;


typedef NS_ENUM(NSInteger, PIMovieScalingMode) {
    PIMovieScalingModeNone,       // No scaling
    PIMovieScalingModeAspectFit,  // Uniform scale until one dimension fits
    PIMovieScalingModeAspectFill, // Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
    PIMovieScalingModeFill,        // Non-uniform scale. Both render dimensions will exactly match the visible bounds
    PIMovieScalingModeFillWidthOnTop  // Uniform scale until the width dimension fits, renderer content on top of self view
};


typedef NS_ENUM(NSInteger, PIMoviePlaybackState) {
    PIMoviePlaybackStateStopped,
    PIMoviePlaybackStatePlaying,
    PIMoviePlaybackStatePaused,
    PIMoviePlaybackStateInterrupted,
    PIMoviePlaybackStateSeekingForward,
    PIMoviePlaybackStateSeekingBackward
};

typedef NS_OPTIONS(NSUInteger, PIMovieLoadState) {
    PIMovieLoadStateUnknown        = 0,
    PIMovieLoadStatePlayable       = 1 << 0,
    PIMovieLoadStatePlaythroughOK  = 1 << 1, // Playback will be automatically started in this state when shouldAutoplay is YES
    PIMovieLoadStateStalled        = 1 << 2, // Playback will be automatically paused in this state, if started
};

typedef NS_ENUM(NSInteger, PIMediaEvent) {
    
    // Notify Events
    PIMediaEvent_WillHttpOpen         = 1,       // attr: url
    PIMediaEvent_DidHttpOpen          = 2,       // attr: url, error, http_code
    PIMediaEvent_WillHttpSeek         = 3,       // attr: url, offset
    PIMediaEvent_DidHttpSeek          = 4,       // attr: url, offset, error, http_code
    // Control Message
    PIMediaCtrl_WillTcpOpen           = 0x20001, // PIMediaUrlOpenData: no args
    PIMediaCtrl_DidTcpOpen            = 0x20002, // PIMediaUrlOpenData: error, family, ip, port, fd
    PIMediaCtrl_WillHttpOpen          = 0x20003, // PIMediaUrlOpenData: url, segmentIndex, retryCounter
    PIMediaCtrl_WillLiveOpen          = 0x20005, // PIMediaUrlOpenData: url, retryCounter
    PIMediaCtrl_WillConcatSegmentOpen = 0x20007, // PIMediaUrlOpenData: url, segmentIndex, retryCounter
};

typedef NS_ENUM(NSInteger, PIMovieTimeOption) {
    PIMovieTimeOptionNearestKeyFrame,
    PIMovieTimeOptionExact
};

typedef NS_ENUM(NSInteger, PIMovieFinishReason) {
    PIMovieFinishReasonPlaybackEnded,
    PIMovieFinishReasonPlaybackError,
    PIMovieFinishReasonUserExited
};


typedef NS_ENUM(NSInteger, PIEventType) {
    PIET_EXTRA_TS_BREAK_CHANGED     = 110011,
    PIET_VIDEO_PRESENT              = 110009,
    PIET_NEED_RETRY                 = 110006,
    // extra 参数是 char *，可尝试转换成 NSString *
    PIET_CORE_STATUS                = 321000,
};

@class PIMoviePlayerController;

@protocol PIEventHandler <NSObject>

@required
- (void) onEventforPlayer:(PIMoviePlayerController *)player withType:(int)type andArg1:(int)arg1 andArg2:(int)arg2 andExtra:(void *)extra;

@end

// event of PIMediaUrlOpenEvent_xxx
@interface PIMediaUrlOpenData: NSObject

- (id)initWithUrl:(NSString *)url
            event:(PIMediaEvent)event
     segmentIndex:(int)segmentIndex
     retryCounter:(int)retryCounter;

@property(nonatomic, readonly) PIMediaEvent event;
@property(nonatomic, readonly) int segmentIndex;
@property(nonatomic, readonly) int retryCounter;

@property(nonatomic, retain) NSString *url;
@property(nonatomic, assign) int fd;
@property(nonatomic, strong) NSString *msg;
@property(nonatomic) int error; // set a negative value to indicate an error has occured.
@property(nonatomic, getter=isHandled)    BOOL handled;     // auto set to YES if url changed
@property(nonatomic, getter=isUrlChanged) BOOL urlChanged;  // auto set to YES by url changed

@end

@protocol PIMediaUrlOpenDelegate <NSObject>

- (void)willOpenUrl:(PIMediaUrlOpenData*) urlOpenData;

@end

@protocol PIMediaNativeInvokeDelegate <NSObject>

- (int)invoke:(PIMediaEvent)event attributes:(NSDictionary *)attributes;

@end


PI_EXTERN @interface PIMoviePlayerController : NSObject

@property(nonatomic, readonly)  UIView *view;
@property(nonatomic)            NSTimeInterval currentPlaybackTime;
@property(nonatomic, readonly)  NSTimeInterval duration;
@property(nonatomic, readonly)  NSTimeInterval playableDuration;
@property(nonatomic, readonly)  NSInteger bufferingProgress;

@property(nonatomic, readonly)  BOOL isPreparedToPlay;
@property(nonatomic, readonly)  PIMoviePlaybackState playbackState;
@property(nonatomic, readonly)  PIMovieLoadState loadState;

@property (nonatomic, setter = setScalingMode:) PIMovieScalingMode scalingMode;
@property (nonatomic, setter = setShouldAutoplay:) BOOL shouldAutoplay;
@property(nonatomic, readonly) int64_t numberOfBytesTransferred;

@property(nonatomic, readonly) CGSize naturalSize;

@property (nonatomic) BOOL allowsMediaAirPlay;
@property (nonatomic) BOOL isDanmakuMediaAirPlay;
@property (nonatomic, readonly) BOOL airPlayMediaActive;

@property (nonatomic) float playbackRate;
@property (nonatomic) float playbackVolume;

- (UIImage *)thumbnailImageAtCurrentTime;

@property (atomic, readonly, getter=getNativePlayer) void * nativePlayer;

/**
 * @brief Initialize with stream_group and slot.
 *
 * @param url Stream url.
 *
 * @param options Could be nil.
 *
 * @param slot,
 * in the same group,
 * should be 0 for main stream,
 * and [1, 8] for sub stream,
 * should not repeat.
 *
 * @param stream_group ,
 * should be nil for main stream,
 * and main stream_group for sub stream.
 *
 * @param vr_flag VR flag.
 *
 * @return Instance of player.
 */
- (id)initWithURL:(NSURL *)url
      withOptions:(PIOptions *)options
         withSlot:(int)slot
  withStreamGroup:(void *)stream_group
    withPSOptions:(NSMutableDictionary *)ps_options;


/**
 * @brief Initialize with psdemux pointer and stream index.
 *
 * @param url Stream url.
 *
 * @param options Could be nil.
 *
 * @param stream_id Stream index,
 * should be 0 for main stream,
 * and [1, 8] for sub stream,
 * should not repeat.
 *
 * @param psdemux Psdemux pointer,
 * should be nil for main stream,
 * and main stream's psdemux pointer for sub stream.
 *
 * @param vr_flag VR flag.
 *
 * @return Instance of player.
 */
- (id)initWithURL:(NSURL *)url
      withOptions:(PIOptions *)options
     withStreamID:(int)stream_id
      withPointer:(void *)psdemux
    withPSOptions:(NSMutableDictionary *)ps_options DEPRECATED_MSG_ATTRIBUTE("This method is replace by initWithURL: withOptions:withSlot:withStreamGroup:withPSOptions:");

/**
 * @brief Get psdemux pointer,
 * should be called with main stream.
 *
 * @return Psdemux pointer.
 */
- (void *)getPsdemux;

- (int64_t)psGetTimestamp;
- (int) updateParam:(int) recover withParam:(NSString *) param;

- (void)setDisplayArea:(CGRect*)area;
- (void)setFlipDisplayVertical:(bool)vertical andHorizontal:(bool)horizontal;
- (NSString *)popCocosFrame;
- (void)setCocosView:(WKWebView *)webView;

- (int64_t) get_PSPlayer_TAG; //获取TAG用于切换播放器
- (int) set_pscocos_remote_ctrl_buffer:(PSCOCOS_REMOTE_CTRL_BUFFER*)buffer _tag:(int64_t)tag ;

/**
 * @brief Global initialization,
 * should be called after App launch for only once.
 *
 * @param log_path The output path of log file,
 * could be the return value of NSTemporaryDirectory function.
 */
+ (void)psglobal_init:(NSString *)log_path;

+ (void)psglobal_pdpinit:(void *)param;

+ (void)psglobal_stop_psdns:(int)stop;

+ (void)psglobal_pzbcinfo:(NSString *)url withContent:(NSString*)ctx;



/**
 播放器SDK的版本号

 @return 返回 NSString 形式的播放器字符串版本号
 */
+ (NSString *) versionName;

/**
 * @brief Global preload function,
 * called to parse the stream url to ip address in advance.
 *
 * @param url Stream url to be parsed.
 */
+ (void)psglobal_preload:(NSString *)url;

/**
 * @brief Global refresh,
 * should be called when network environment change(e.g. WiFi -> 4G).
 */
+ (void)psglobal_refresh;

/**
 * @brief Global release,
 * should be called before App terminate for only once.
 */
+ (void)psglobal_release;

/**
 * @brief Toggle voice processing.
 *
 * @param val Toggle value.
 *
 ** 0 disable voice processing
 ** 1 enable voice processing
 */
+ (void)toggle_voice_processing:(int)val;

+ (BOOL)set_toggle_voice_audio_session_options:(int)options;

/**
 * @brief Initialize mode param.
 *
 * @param mode Mode.
 *
 ** 1 Multi Stream
 ** 2 Low Delay
 */
- (void)psinit_mode:(int)mode withContent:(NSString*)ctx;

/**
 * @brief Initialize hardware decode param.
 *
 * @param xhard Toggle value.
 *
 ** 0 disable hardware decode
 ** 1 enable hardware decode
 */
- (void)psinit_xhard:(int)xhard;

/**
 * @brief Open audio.
 */
- (void)psaudio_open;

/**
 * @brief Close audio.
 */
- (void)psaudio_close;


/**
 * @brief Control audio mute status.
 */
- (void)psaudio_mute:(BOOL)enable;

/**
 * @brief This api is deprecated
 * use
 * PIOptions *options = [[PIOptions alloc] init];
 * [options setPlayerOptionIntValue:0 forKey:@"audio-mode"];
 *
 * @param mode
 *
 ** 0 for audio unit
 ** 1 for audio queue
 */
- (void)psaudio_mode:(int)mode DEPRECATED_MSG_ATTRIBUTE("use PIOptions instead");

- (int)force_audio_open_with_parameters:(bool)force_flag sampleRate:(int)sr channels:(int)ch;
/**
 * @brief Get stream's bitrate adaptive status.
 * This only works on the pzsp stream format.
 *
 * @return Return bitrate adaptive status.
 *
 ** 0 fixed bitrate
 ** 1 adaptive bitrate
 */
- (int)get_adaptive;


- (void)setFeature:                 (BOOL)enable forKey:(PIFeature)features;



/**
 * @brief Get node(server) ip address.
 * This only works on the pzsp stream format.
 * Get the ip address of the server where the player get the media data
 *
 * @return The node ip address or nil if failed.
 */
- (NSString *)get_node_ip;

/**
 * @brief Get max view number of stream.
 * This view is not the Ui view.
 *
 * @return Return max view number of stream.
 */
- (int)get_max_view;

/**
 * @brief Get specified view name by serial number.
 *
 * @param view_no The specified serial number of view.
 *
 * @return The specified view name or nil if failed.
 */
- (NSString *)get_view:(int)view_no;

/**
 * @brief Get current view name.
 *
 * @return Current view name or nil if failed.
 */
- (NSString *)get_current_view;

/**
 * @brief Request to switch to specified view.
 *
 * @param view The specified view name to be switched to.
 */
- (void)set_view:(NSString *)view;

/**
 Use this interface to switch a stream as fast as we can.
 Except return value is "-9",it will post a notifation PZSPViewChangeEndNotification with "retcode" and "lastview" in lew one second or few seconds,it means success if retcode is zero,others failed
 @param view The specified view name(or a url) to be switched to.
 @return 0 success,-9 switching, other fails need more log to locate
 */
- (int)set_view2:(NSString *)view;

- (int)record:(int)enable withFileName:(NSString*)fn withMaxSize:(int)max_size withStamp:(int64_t)vstamp withDuration:(int)duration;

/**
 * @brief Get max audio number of stream.
 *
 * @return Return max audio number of stream.
 */
- (int)get_max_audio;


/**
 * @brief Get specified audio name by serial number.
 *
 * @param audio_no The specified serial number of audio.
 *
 * @return The specified audio name or nil if failed.
 */
- (NSString *)get_audio:(int)audio_no;

/**
 * @brief Get current audio name.
 *
 * @return Current audio name or nil if failed.
 */
- (NSString *)get_current_audio;

/**
 * @brief Request to switch to specified audio.
 *
 * @param audio The specified audio name to be switched to.
 */
- (void)set_audio:(NSString *)audio;

/**
 * @brief Get max bitrate number of stream.
 *
 * @return Return max bitrate number of stream.
 */
- (int)get_max_bitrate;

/**
 * @brief Get specified bitrate name by serial number.
 *
 * @param bitrate_no The specified serial number of bitrate.
 *
 * @return The specified bitrate name or nil if failed.
 */
- (NSString *)get_bitrate:(int)bitrate_no;

/**
 * @brief Get current bitrate name.
 *
 * @return Current bitrate name or nil if failed.
 */
- (NSString *)get_current_bitrate;

/**
 * @brief Request to switch to specified bitrate.
 *
 * @param bitrate The specified bitrate name to be switched to,
 * if user wants to switch to adaptive bitrate, "auto" should be passed.
 */
- (void)set_bitrate:(NSString *)bitrate;

/**
 * @brief Request to switch to specified play mode.
 *
 * @param mode Specified mode to be switched to, list as follows
 *
 ** 0 None
 ** 1 Multi Stream
 ** 2 Low Delay
 *
 * @param url New url to be switched to,
 * could be nil if there is no new url.
 *
 * @return Return code, list as follows
 *
 ** 0 success
 ** -1 failed
 */
- (int)set_mode:(int)mode
        withURL:(NSString *)url;


/**
 * @brief Set background mode.
 *
 * @param val Specified background mode, list as follows
 *
 ** 0 Foreground
 ** 1 Background
 */
- (void)set_background:(int)val;


- (BOOL)audioSessionInterruptEnd;
- (void)audioSessionInterruptBegin;


//TODO @baishuai
- (void)add_to_group:(PIMoviePlayerGroup *)group;
- (void)unbind_from_group:(PIMoviePlayerGroup *)group;

- (int64_t)get_extrats;
- (int)get_pzvtdelay;
- (int)setMasterSlaveState:(int)state;
- (int)userString:(NSString*)usrstr;
- (int)arrcTarget;
- (int)setArrcTarget:(int)players targets:(int[8]) targets;
- (int)streamState;

- (int)nstest_rules:(NSString*)rules;

- (NSString*)nstest_caps;

- (int)usEnablePlay:(int)state;

- (NSString*)usReportPlayState;

- (int)usFixDelay:(int)state FixDelay:(int)delay;



//mpath
- (int)getmpathusageWithMpathn:(int *)mpathn mpath_usage:(unsigned long long *)mpath_usage mpath_name:(char *)mpath_name;
- (int)getopentimeWithTotaltick:(int *)totaltick pzbtick:(int *)pzbtick conntick:(int *)conntick responsetick:(int *)responsetick probetick:(int *)probetick starttick:(int *)starttick bufferingtick:(int *)bufferingtick playingtick:(int *)playingtick;
- (int)getopenerrorcodeWithErrorcode:(int *)errorcode;

//reconnect
- (int)reconnectWithStatus:(int)status;

- (int)forceReconnect;

- (int)retryNoWait;

//networkStateChanged
- (void)networkStateChanged:(int)status;

/**
 open/close custom rendering callback
 
 @param openRenderingFlag true to open, false close
 @param autoDestoryFlag ture means PIPlayer will destory the CVPixelBufferRef automatically , false won't
 @param callback  callback will give a CVPixelBufferRef
 @return 0 success,others failed
 */
- (int)switchRenderingWithOpenRenderingFlag:(bool)openRenderingFlag withAutoDestoryFlag:(bool)autoDestoryFlag withCallback:(void(^)(CVPixelBufferRef pb))callback;

- (int)setVideoCallback:(void(^)(CVPixelBufferRef pb))callback;

/**
 this interface is to detected the bitrate change
 
 @param openFlag true to open,false close
 @param callback it contain a NSString, may be md(lowest) hd(normal) ud(hight)
 @return 0 success, others failed
 */
- (int)switchBitRateCallbackWithOpenFlag:(bool)openFlag callback:(void(^)(NSString *bitrateName))callback;


/**
 * Ctrl player to receive audio stream or both video and audio stream
 * @param ctrlcode 1 only audio stream, 0 both audio and video stream
 * @return 0 on success, or other value if failed
 */
- (int)ps_stream_ctrl:(int)ctrlcode;

/**
 detect volume
 
 @param openFlag 是否打开
 @param threshold 回调阈值(超过该阈值才会返回)，阈值范围1到2^15-1
 @param interval 回调间隔,单位s,需>=0.1s,有误差(一般在10ms以内)
 @param callback 回调
 @return 是否成功 0成功，others失败
 */
- (int)switchVolumeWithOpenFlag:(bool)openFlag threshold:(int16_t)threshold callbackInterval:(float)interval callback:(void(^)(int16_t currentVolume))callback;
- (int)switchVolumeWithOpenFlag:(bool)openFlag threshold:(int16_t)threshold callback:(void(^)(int16_t currentVolume))callback DEPRECATED_MSG_ATTRIBUTE("Use method \"(int)switchVolumeWithOpenFlag: threshold:callbackInterval:callback:\" instead.");





/**
 save audio data(befefore decoder,after decoder, sdl_audio_callback) to file
 
 @return 0 sucdess, others failed
 */
- (int)recordAudioFile;


- (int)psUpdatePzbInfoWithMode:(int)mode url:(NSString *)url pzbinfo:(NSString *)info;


- (void) addPIEventHandler:(id<PIEventHandler>) handler;
- (void) removePIEventHandler:(id<PIEventHandler>) handler;

/**
 音频数据回调函数
 @param handle userdata, 设置回调的时候传入的 handle
 @param sampleRate 音频采样率
 @param channel 音频声道数
 @param samplefmt 音频数据格式
 @param stamp 音频时间戳
 @param data 音频数据， raw data
 @param data_len 音频数据长度，in bytes
 @param extrats 额外时间戳信息，参考文档extrats 相关内容
 @return 返回1，音频数据不在原输出设备输出。返回0，依旧使用原始音频设备进行声音播放
 */
typedef int(*PIP_Audio_Callback)(void *handle, int sampleRate, int channel, int samplefmt, int64_t stamp, uint8_t *data, int data_len, int64_t extrats);


/**
 设置音频回调
 @param enable 0 关闭音频回调，1 打开播放源的音频回调
 @param handle userdata 作为回调的参数传出
 @param callback 回调函数
 @return 0 设置成功。负数，设置失败
 */
- (int)setAudioCallback:(int)enable handle:(void *)handle callback:(PIP_Audio_Callback)callback;


/**
 control the cache of audio
 if current audio cache over maxDuration, will drop audio frame to make audio cache descend to targetDuration
 if current audio cache near maxDuration but doesn't reach maxDuration, it will speedup to decrease the cahe of audio
 
 @param maxDuration the maxValue allowed of audio cache
 @param targetDuration the idea value allowed of audio cache
 @param parameterStr only supported "Ix8SIBY7DxImMA8BAQ0WRSAKEiEQPAhbeW8UQ0FdVVIzC0pwQnle" currently
 @return 0 success, others failed
 */
- (int)setMaxAudioDuration:(int64_t)maxDuration targetDuration:(int64_t)targetDuration parameterStr:(char *)parameterStr;
- (bool)resetUrl:(NSString *)newUrl withTime:(NSTimeInterval)time;



/**
 * @brief Set VR motion mode,
 * this interface could reset display status.
 *
 * @param val Specified motion mode, list as follows
 *
 ** 0 Manual
 ** 1 Auto
 */
- (void)psSetVRMotion:(int)val;

- (void)renderIntervalWithPixelBuffer:(CVPixelBufferRef)pb;

- (int)PlayerSnapshotWithPZVT:(int64_t)PZVT filename:(NSString*)filename successCallback:(void(^)(UIImage *image))successCallback failCallback:(void(^)())failcallback;
- (Boolean)cancelSanpShotWithID:(int)ID;


- (id)initWithContentURL:(NSURL *)aUrl
             withOptions:(PIOptions *)options;

- (id)initWithContentURLString:(NSString *)aUrlString
                   withOptions:(PIOptions *)options;

- (void)prepareToPlay;
- (void)play;
- (void)pause;
- (void)stop;
- (BOOL)isPlaying;
- (void)shutdown;
- (void)setPauseInBackground:(BOOL)pause;
- (BOOL)isVideoToolboxOpen;

+ (void)setLogReport:(BOOL)preferLogReport;
+ (void)setLogLevel:(PILogLevel)logLevel;
+ (BOOL)checkIfFFmpegVersionMatch:(BOOL)showAlert;
+ (BOOL)checkIfPlayerVersionMatch:(BOOL)showAlert
                          version:(NSString *)version;

+ (BOOL)checkSupportHttpStream;

@property(nonatomic, readonly) CGFloat fpsInMeta;
@property(nonatomic, readonly) CGFloat fpsAtOutput;
@property(nonatomic) BOOL shouldShowHudView;

- (void)setOptionValue:(NSString *)value
                forKey:(NSString *)key
            ofCategory:(PIOptionCategory)category;

- (void)setOptionIntValue:(int64_t)value
                   forKey:(NSString *)key
               ofCategory:(PIOptionCategory)category;

- (void)setFormatOptionValue:       (NSString *)value forKey:(NSString *)key;
- (void)setCodecOptionValue:        (NSString *)value forKey:(NSString *)key;
- (void)setSwsOptionValue:          (NSString *)value forKey:(NSString *)key;
- (void)setPlayerOptionValue:       (NSString *)value forKey:(NSString *)key;

- (void)setFormatOptionIntValue:    (int64_t)value forKey:(NSString *)key;
- (void)setCodecOptionIntValue:     (int64_t)value forKey:(NSString *)key;
- (void)setSwsOptionIntValue:       (int64_t)value forKey:(NSString *)key;
- (void)setPlayerOptionIntValue:    (int64_t)value forKey:(NSString *)key;

@property (nonatomic, retain) id<PIMediaUrlOpenDelegate> segmentOpenDelegate;
@property (nonatomic, retain) id<PIMediaUrlOpenDelegate> tcpOpenDelegate;
@property (nonatomic, retain) id<PIMediaUrlOpenDelegate> httpOpenDelegate;
@property (nonatomic, retain) id<PIMediaUrlOpenDelegate> liveOpenDelegate;

@property (nonatomic, retain) id<PIMediaNativeInvokeDelegate> nativeInvokeDelegate;

#pragma mark KVO properties
@property (nonatomic, readonly) PIMonitor *monitor;

@end
