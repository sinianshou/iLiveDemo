
#ifndef libdatabase_h
#define libdatabase_h

//#define LOWLATENCY_AUDIOENC
//#define MPATH_VERSION

//avcapturepreset

#import <PI_Process/PIProcessDefines.h>

#define LIBP31_VERSION "1.9.2.0--201909181045"



#define PROGRESS_IN_MS 0
#define PROGRESS_IN_PERCENTAGE 1

#define TRANSCODER_METRO_ELEMENT_MAX_COUNT 8

typedef void (*VOLUMECALLBACK) (float volume);


typedef NS_ENUM(NSInteger, PS_AudioCaptureType)
{
    AudioCaptureExternalWithCMSampleBuffer = 1,
    AudioCaptureExternalWithBytes = 2,
    AudioCaptureAudioUnit = 5,
    AudioCaptureAVCaptureSession = 6,
};

typedef NS_ENUM(NSInteger, PS_VideoCaptureType)
{
    VideoCaptureExternalWithCMSampleBuffer = 1,
    VideoCaptureWithBackCamera = 5,
    VideoCaptureWithFrontCamera = 6,
};

typedef NS_ENUM(NSInteger, PS_InitOptionType)
{
    VideoDelegateWith420YpCbCr8BiPlanarFullRange = 0x01,
    VideoDelegateWith32BGRA = 0x02,
    AudioEncodeParameterReadyAfterStreaming = 0x04,
    VideoEncodeSyncProcess = 0x08,
};

typedef NS_ENUM(NSInteger, PS_AudioSampleType)
{
    PS_SampleBufferTypeAudioApp = 1,
    PS_SampleBufferTypeAudioMic = 2,
};

typedef NS_ENUM(NSInteger, PS_AudioStopReason)
{
    PS_Stop = 1,
    PS_SetToBackGround = 2,
};

typedef NS_ENUM(NSInteger, PS_NetworkStatus) {
    // Apple NetworkStatus Compatible Names.
    PS_NotReachable = 0,
    PS_ReachableViaWiFi = 2,
    PS_ReachableViaWWAN = 1
};

typedef NS_ENUM(NSInteger, PS_PushStatus) {
    PS_StatusSuccess = 0,
    PS_StatusInputNullBuff = -1,
    PS_StatusDelayTooLarge = 11,
    PS_StatusNetworkFailed = 12,
    PS_StatusPerformanceNotEnough = 13,
    PS_StatusNoVideoData = 31,
    PS_StatusNoAudioData = 32,
    PS_StatusNoAudioAndVideoData = 40
};

typedef NS_ENUM(NSInteger, PS_LogLevel)
{
    FLOG_OFF = 0,
    FLOG_ERR = 1,
    FLOG_INF = 2,
    FLOG_WAR = 3
};

typedef NS_ENUM(NSInteger, PS_VideoCaptureResolution)
{
    AVCAPPRESET1280x720 = 0,
    AVCAPPRESET640x480 = 1,
    AVCAPPRESET352x288 = 2,
    AVCAPPRESET960x540 = 3
};

typedef NS_ENUM(NSInteger, PS_SnapshotResult)
{
    PS_SnapshotSuccess = 0,
    PS_SnapshotFail = 1
};


typedef NS_ENUM(NSInteger, PS_AudioCaptureMode)
{
    PS_ACapDontCaptureSampleBuffer = 1,    //do not need libP31 capture audio, and the audio buffer struct you captured is `CMSampleBufferRef`
    PS_ACapDontCaptureBytes = 2,    //means do not need libP31 capture audio, and the audio buffer you captured are bytes
    PS_ACapDontCaptureSampleBufferReplaykit = 3,    //means do not need libP31 capture audio, and the audio buffer struct you captured is `CMSampleBufferRef`,used by Replaykit!
    PS_ACapDoCaptureAudioUnit = 5,     //means need libP31 capture audio, and libP31 will capture audio through `AudioUnit`
    PS_ACapDoCaptureAVCaptureSession = 6,    //means need libP31 capture audio, and libP31 will capture audio through `AVCaptureSession`
    PS_ACapDoCaptureReplaykit = 7       //means need libP31 capture audio, and libP31 will capture audio through `replaykit`
};

typedef NS_ENUM(NSInteger, PS_AudioEncodeMode)
{
    PS_AEncParamsReady = 1,    //do audio encoder through `AudioConvert`, and encoder params are ready when starting
    PS_AEncParamsNotReady = 2,    //do audio encoder through `AudioConvert`, and encoder params are not ready when starting, relevant interface refer to pragma mark **interface for no audio params when starting**
};

typedef NS_ENUM(NSInteger, PS_VideoCaptureMode)
{
    PS_VCapDontCaptureSampleBuffer = 1,    //do not need libP31 capture video, and the video buffer you captured is `CMSampleBufferRef`, relevant interface refer to pragma mark **interface for no video capture in lib**
    PS_VCapDoCaptureBackCamWithDelegate420YpCbCr8BiPlanarFullRange = 3,    //need libP31 capture video, libP31 capture video default with back camera, with delegate for avcapture enable.AVCapture setting dataoutput is kCVPixelFormatType_420YpCbCr8BiPlanarFullRange;
    PS_VCapDoCaptureFrontCamWithDelegate420YpCbCr8BiPlanarFullRange = 4,     //need libP31 capture video, libP31 capture video default with front camera, with delegate for avcapture enable.AVCapture setting dataoutput is kCVPixelFormatType_420YpCbCr8BiPlanarFullRange;
    PS_VCapDoCaptureBackCamWithoutDelegateDefault = 5,    //need libP31 capture video, libP31 capture video default with back camera
    PS_VCapDoCaptureFrontCamWithoutDelegateDefault = 6,     //need libP31 capture video, libP31 capture video default with front camera
    PS_VCapDoCaptureBackCamWithDelegate32BGRA = 7,      //need libP31 capture video, libP31 capture video default with back camera, with delegate for avcapture enable.AVCapture setting dataoutput is kCVPixelFormatType_32BGRA;
    PS_VCapDoCaptureFrontCamWithDelegate32BGRA = 8,     //need libP31 capture video, libP31 capture video default with front camera, with delegate for avcapture enable.AVCapture setting dataoutput is kCVPixelFormatType_32BGRA.
    PSVCapDontCaptureAtAll = 9,   //do not need video capture at all.(most likely to be used in pure audio push)
    PS_VCapDoCaptureReplaykitStartCamera = 10,   //need libP31 capture video using replaykit, camera is allowed to start
    PS_VCapDoCaptureReplaykitNoCamera = 11,  //need libp31 capture video using replaykit, camera is not allowd to start
    PS_VCapDoCaptureReplaykitStartCameraWithDelegate = 12   //need libP31 capture video using replaykit, camera is allowed to start

};

typedef NS_ENUM(NSInteger, PS_VideoEncodeMode)
{
    PS_VEncVideoToolBoxSync = 1,    //encode video with `VideoToolBox`, and encode is a sync process
    PS_VEncVideoToolBoxAsync = 2    //encode video with `VideoToolBox`, and encode is a async process
};

typedef struct _TRANSCODER_WORKING_MODE
{
    PS_AudioCaptureMode audioCapMode;
    PS_AudioEncodeMode audioEncMode;
    PS_VideoCaptureMode videoCapMode;
    PS_VideoEncodeMode videoEncMode;
}TRANSCODER_WORKING_MODE, *PTRANSCODER_WORKING_MODE;

typedef NS_ENUM(NSInteger, PS_VideoPushSwitch)
{
    PS_NoVideoPush = 0,
    PS_VideoPushH264 = 1,
    PS_VideoPushHEVC = 2
};

typedef NS_ENUM(NSInteger, PS_Transcoder_Errorcode)
{
    PS_NoErr = 0,
    PS_ErrFailToStartAudioEncoder = -1,
    PS_ErrFailToStartAudioCapture = -2,
    PS_ErrFailToStartVideoEncoder = -3,
    PS_ErrFailToStartVideoCapture = -4,
    PS_ErrFailToStartPush = -5,
    PS_ErrFailPushingAlready = -6,
    PS_ErrForegroundAlready = -7,
    PS_ErrTranscoderInBackground = -8,
    PS_ErrParameterError = -9,
};

typedef NS_ENUM(NSInteger, PS_TranscoderAudioCaptureMode)
{
    PS_AudioCaptureNormal = 0,
    PS_AudioCaptureEnableMixer = 1,
};

/**
 @brief App set params to libP31 through this class
 */
@interface INTERFACE_SET_PARAMS : NSObject

@property(nonatomic, assign) PS_AudioCaptureMode audioCapMode;

@property(nonatomic, assign) PS_AudioEncodeMode audioEncMode;

@property(nonatomic, assign) PS_VideoCaptureMode videoCapMode;

@property(nonatomic, assign) PS_VideoEncodeMode videoEncMode;

@property(nonatomic, assign) PS_PushBackgroundBehaviour backgroundPushOption;
/**
 video bitrate, unit: kb/s
 */
@property(nonatomic,assign) int video_bitrate;

/**
 the max Delay that lib can accept, if delay is larger than this value, lib will not send video data
 unit: millisecond
 */
@property(nonatomic,assign) int maxDelayThreshold;

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
 set the address you want to PSLStreaming push stream to
 more info refering to url rule document
 */
@property(nonatomic,assign) char *url;

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
 Must be 1;
 */
@property(nonatomic,assign) int txtype;

/**
 push switch
 if switch is 0, that mean PSLStreaming will not push the data of this type.
 if switch is !0, that mean PSLStreaming will push the data of this type, the value indicates the codec format.
 */
@property(nonatomic,assign) int audio_push_switch;
/**
 video push switch
 if switch is 1, the video encode will be H.264
 if switch is 2, the video encode will be HEVC
 */
@property(nonatomic,assign) int video_push_switch;

/**
 threshold params, use absolute value
 fps_min: the min fps you can accept
 br_max: the max bitrate you can accept
 br_min: the min bitrate you can accept
 keyframeinterval: video frames between each key frame, we usually set 2*video_fps to it
 */
@property(nonatomic,assign) int fps_min;
@property(nonatomic,assign) int br_max;
@property(nonatomic,assign) int br_min;
@property(nonatomic,assign) int keyframeinterval;

/**
 threshold params in ratio. Value should be positive.
 */
@property(nonatomic,assign) int fps_min_ratio;
@property(nonatomic,assign) int br_max_ratio;
@property(nonatomic,assign) int br_min_ratio;

/**
 set sessionPreset for avcapturesession
 0 for AVCaptureSessionPreset1280x720
 1 for AVCaptureSessionPreset640x480
 2 for AVCaptureSessionPreset352x288
 3 for AVCaptureSessionPresetiFrame960x540
 */
@property(nonatomic,assign) int avcap_preset;

/**
 set camera direction
 0 for front camera
 1 for back camera
 */
@property(nonatomic,assign) int cam_direction;

/**
 Set to 0xffff to disable bandwidth adaption.
 other values, please contact developer support.
 */
@property(nonatomic,assign) int adjust_ratio;

//0 for no external process, 1 for use external process
@property(nonatomic,assign) int audio_external_process;
@end

typedef INTERFACE_SET_PARAMS* PINTERFACE_SET_PARAMS;

@interface INTERFACE_CAMERA_PARAMS : NSObject
/**
 set sessionPreset for avcapturesession
 0 for AVCaptureSessionPreset1280x720
 1 for AVCaptureSessionPreset640x480
 2 for AVCaptureSessionPreset352x288
 3 for AVCaptureSessionPresetiFrame960x540
 */
@property(nonatomic,assign) int avcap_preset;

/**
 set camera direction
 0 for front camera
 1 for back camera
 */
@property(nonatomic,assign) int cam_direction;

@property(nonatomic,assign) int capture_fps;

/**
 set format for the captured video data format
 0 for kCVPixelFormatType_32BGRA
 1 for kCVPixelFormatType_420YpCbCr8BiPlanarFullRange
 */
@property(nonatomic,assign) int capture_format;

/**
 set if video capture will callback for external process
 */
@property(nonatomic,assign) BOOL video_external_process;

@property(nonatomic,assign) int a50Mode;

@property(nonatomic,assign) int lpcStatus;


@end

typedef INTERFACE_CAMERA_PARAMS* PINTERFACE_CAMERA_PARAMS;

@interface INTERFACE_MICROPHONE_PARAMS : NSObject

@property(nonatomic,assign) int samplerate;

@property(nonatomic,assign) int channel_num;

@property(nonatomic,assign) int ifEnableMixer;

@end


#endif
