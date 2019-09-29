//
//  Header.h
//  PI_Process
//
//  Created by HUO on 2018/9/5.
//  Copyright © 2018 sjdd. All rights reserved.
//

#ifndef PIProcess_h
#define PIProcess_h
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AVFoundation/AVCaptureVideoPreviewLayer.h>
#import <UIKit/UIKit.h>
#import "PIProcessDefines.h"

@interface PIProcess: NSObject

+ (int) globalInit;

+ (int) globalInitWithLogPath: (char*) logpath;

#pragma mark - Interfaces for only one stream

- (int) startStreamWithParam: (PIProcessSetParam *) param;

- (void) stopStream;

- (void) pauseStream:(PS_PushBackgroundBehaviour) pauseOption;

- (int) resumeStream;

- (int) sendDataFrame:(uint8_t*) dataframe andSize:(size_t) size andTimestamp:(int64_t) timestamp andFlag:(uint32_t) flag;
- (int) sendDataFrame:(uint8_t*) dataframe andSize:(size_t) size andTimestamp:(int64_t) timestamp andFlag:(uint32_t) flag withStreamid:(int) streamid;

- (int) sendVideoRawFrame:(CMSampleBufferRef) videoframe;
- (int) sendVideoRawFrame:(CMSampleBufferRef) videoframe withDataSource: (int32_t)ds_index;
- (int) sendVideoEncodedFrame:(unsigned char*) videoframe withSize:(size_t) size withTimestamp:(int64_t) timestamp withifIframe:(BOOL)ifIframe withDataSource:(int32_t) ds_index;
- (int) sendVideoRawFrame:(CVImageBufferRef) videoframe withPts:(CMTime) pts withDuration:(CMTime) duration withDateSource:(int32_t) ds_index;

//By calling this function, PIProcess will make the current physical time the timestamp of this frame.
- (int) sendAudioRawFrame:(int16_t *) audioframe andSize:(size_t) size andExtraTs: (int64_t) extrats;

- (int) sendAudioRawFrame:(int16_t *) audioframe andSize:(size_t) size andTimestamp:(int64_t) timestamp andExtraTs:(int64_t) extrats;
- (int) sendAudioRawFrame:(int16_t *) audioframe andSize:(size_t) size andTimestamp:(int64_t) timestamp andExtraTs:(int64_t) extrats withDataSource:(int32_t)ds_index;

- (int) sendAudioRawFrame:(CMSampleBufferRef) audioframe;

- (PINTERFACE_GET_PARAMS) getParam;

/**
 type should be 7, when success, return value will be 0, then valid socketbuffer statistic data will be returned.
 @param type        should be 7 for now
 @param seqIndex    data index, when data get updated, this number will add 1
 @param calCount    sample number for this statistic period
 @param avg         average value
 @param max         maximum value
 @param min         minimum value
 @param streamid    the stream index id. if only one stream should exist at the same time, streamid should be 0.
 */

- (int) getSampleInfoStats: (int) type withSeqIndex: (unsigned int*) seqIndex withSampleCount: (int*) calCount withAvg: (int64_t*) avg withMax: (int64_t*) max withMin: (int64_t*) min withStreamid: (int) streamid;

/**
 set push callbacks.One of the following callbacks that start with 'setPushStatusCallback_' will be called every time there is one frame of video or audio is pushed.
 */
//push success
- (void) setPushStatusCallback_SendSuccess: (void(^)())sendSuccessCallback;
//push fail due to network reason
- (void) setPushStatusCallback_NetworkFailed: (void(^)())networkFailCallback;
//push success, but delay is too large
- (void) setPushStatusCallback_DelayTooLarge: (void(^)())delayTooLargeCallback;
//push fail due to the push has not started
- (void) setPushStatusCallback_StartFailed: (void(^)())startFailedCallback;
//push fail due to no video data
- (void) setPushStatusCallback_NoVideoData: (void(^)())noVideoDataCallback;
//push fail due to no audio data
- (void) setPushStatusCallback_NoAudioData: (void(^)())noAudioDataCallback;
//push fail for other reasons
- (void) setPushStatusCallback_SendFail: (void(^)())sendFailCallback;

//this will be called once push has started
- (void) setPushSuccessCallback: (void(^)())pushSuccessCallback;
//this will be called when push starts again
- (void) setRePushSuccessCallback: (void(^)())rePushSuccessCallback;

//whis will be called when msc status changes
/*
 status:
 0   success
 1   fail due to server resources failure
 2   fail due to lack of source data
 3   fail due to lack of meta information
 4   fail due to no video data or video data decode failure
 5   fail due to no audio data or audio data decode failure
 6   fail due to resolution beyond template restriction
 255 fail due to unknown reason
 */
- (void) setMscStatusCallback: (void(^)(int status))mscStatusCallback;

- (void) setUsrMsgCallback: (void(^)(const char *)) msgCallback;

#pragma mark - Interfaces for more than one stream

/*
 if the return value lower than 0, start stream error, else the return value equals the stream id.
 */
- (int) addStreamWithParam: (PIProcessSetParam *) param;

- (void) stopStreamWithStreamid:(int) streamid;

- (void) pauseStream:(PS_PushBackgroundBehaviour) pauseOption WithStreamid:(int) streamid ;

- (int) resumeStreamWithStreamid:(int) streamid;

- (void) pauseBackgroundPureAudioStream:(int) streamid;

- (void) resumeBackgroundPureAudioStream:(int) streamid;

- (int) sendVideoRawFrame:(CMSampleBufferRef)videoframe withStreamid:(int) streamid;

//By calling this function, PIProcess will make the current physical time the timestamp of this frame.
- (int) sendAudioRawFrame:(int16_t *)audioframe andSize:(size_t)size andTimestamp:(int64_t) timestamp  andExtraTs: (int64_t) extrats withStreamid:(int) streamid;

- (int) sendAudioRawFrame:(int16_t *)audioframe andSize:(size_t)size  andExtraTs: (int64_t) extrats withStreamid:(int) streamid;

- (int) sendAudioRawFrame:(CMSampleBufferRef) audioframe withStreamid:(int) streamid;

- (PINTERFACE_GET_PARAMS) getParamWithStreamid:(int) streamid;

//return 0 for success, other for fail
- (int) getMpathUsage:(uint64_t*)totalsize andMpathn:(unsigned int*)mpathn andMpathUsage:(uint64_t*)mpath_usage andMpathName:(char*)mpathName;

- (int) getMpathUsage:(uint64_t*)totalsize andMpathn:(unsigned int*)mpathn andMpathUsage:(uint64_t*)mpath_usage andMpathName:(char*)mpathName streamid:(int)streamid;

//push success
- (void) setPushStatusCallback_SendSuccess: (void(^)())sendSuccessCallback streamid:(int) streamid;
//push fail due to network reason
- (void) setPushStatusCallback_NetworkFailed: (void(^)())networkFailCallback streamid:(int) streamid;
//push success, but delay is too large
- (void) setPushStatusCallback_DelayTooLarge: (void(^)())delayTooLargeCallback streamid:(int) streamid;
//push fail due to the push has not started
- (void) setPushStatusCallback_StartFailed: (void(^)())startFailedCallback streamid:(int) streamid;
//push fail due to no video data
- (void) setPushStatusCallback_NoVideoData: (void(^)())noVideoDataCallback streamid:(int) streamid;
//push fail due to no audio data
- (void) setPushStatusCallback_NoAudioData: (void(^)())noAudioDataCallback streamid:(int) streamid;
//push fail for other reasons
- (void) setPushStatusCallback_SendFail: (void(^)())sendFailCallback streamid:(int) streamid;

//this will be called once push has started
- (void) setPushSuccessCallback: (void(^)())pushSuccessCallback streamid:(int) streamid;
//this will be called when push starts again
- (void) setRePushSuccessCallback: (void(^)())rePushSuccessCallback streamid:(int) streamid;


- (void) setPushStatusCallback_SendSuccess_withid: (void(^)(int))sendSuccessCallback streamid:(int) streamid;
- (void) setPushStatusCallback_NetworkFailed_withid: (void(^)(int))networkFailCallback streamid:(int) streamid;
- (void) setPushStatusCallback_DelayTooLarge_withid: (void(^)(int))delayTooLargeCallback streamid:(int) streamid;
- (void) setPushStatusCallback_StartFailed_withid: (void(^)(int))startFailedCallback streamid:(int) streamid;
- (void) setPushStatusCallback_NoVideoData_withid: (void(^)(int))noVideoDataCallback streamid:(int) streamid;
- (void) setPushStatusCallback_NoAudioData_withid: (void(^)(int))noAudioDataCallback streamid:(int) streamid;
- (void) setPushStatusCallback_SendFail_withid: (void(^)(int))sendFailCallback streamid:(int) streamid;

- (void) setPushSuccessCallback_withid: (void(^)(int))pushSuccessCallback streamid:(int) streamid;
- (void) setRePushSuccessCallback_withid: (void(^)(int))rePushSuccessCallback streamid:(int) streamid;

//whis will be called when msc status changes
/*
 status:
 0   success
 1   fail due to server resources failure
 2   fail due to lack of source data
 3   fail due to lack of meta information
 4   fail due to no video data or video data decode failure
 5   fail due to no audio data or audio data decode failure
 6   fail due to resolution beyond template restriction
 255 fail due to unknown reason
 */
- (void) setMscStatusCallback: (void(^)(int status))mscStatusCallback streamid:(int) streamid;

- (void) setMscStatusCallback_withid: (void(^)(int streamid, int status))mscStatusCallback streamid:(int) streamid;

- (void) setUsrMsgCallback: (void(^)(const char *)) msgCallback streamid:(int) streamid;

- (void) setUsrMsgCallback_withid: (void(^)(int streamid, const char *)) msgCallback streamid:(int) streamid;

- (void) setCoreSdkStatusCallback: (onCoreSdkStatus) callback;

#pragma mark - General interfaces

+ (PIProcess *) theProcess;

- (void) setVideoCaptureDevice:(void *) device;

- (void) enableTimeAsTimestamp:(bool) ifenable;

//post event
//return 0 for success, -1 for not success
- (int) postEventIAwithEventId:(int) eventId andEventBody:(char *) eventBody andEventSize:(int) eventSize andStamp:(int64_t) stamp;

//return number of event posted
- (int) postEventIAwithEventId:(int) eventId andEventBody:(char *) eventBody andEventSize:(int) eventSize andStamp:(int64_t) stamp streamid:(int)streamid;

/**
 * @brief reset the key frame duration during the stream is on
 * @param duration : the key frame duration in seconds
 * @return
 * 0 for success
 * others for failed
 */
- (int) resetKeyFrameDuration:(float) duration;

/**
 * @brief reset the key frame duration during the stream is on
 * @param duration : the key frame duration in seconds
 * @param streamid : id of the stream
 * @return
 * 0 for success
 * others for failed
 */
- (int) resetKeyFrameDuration:(float) duration withStreamId:(int) streamid;

//enable when using replaykit to capture video
- (void) enableResetVideoFrameTimestamp: (bool)ifenable;

- (void) setReplaykitStartImage:(UIImage*) image;

- (void) setReplaykitStartImage:(UIImage*) image withStreamid:(int)streamid;

/**
 * @brief called this function when network changed, such as, network changed from wifi to 4G, or from wifi to another wifi, or from 4G to wifi
 * @pparam status: if network changed from wifi to 4G, or from wifi to another wifi, or from 4G to wifi, status should be 1; if network is down, status should be 0
 */
- (void) OnNetworkChange:(int) status;

/**
 * @param recover 1 表示 reset param，0 表示 set param
 */
- (int) updateStreamParam: (int) pslId withRecover: (int) recover withParam: (char*) param;

/**
 * @brief return server ip that streaming pushed to
 * @return if already connected, return ip string
 *         if not connected server, return nil
 */
- (NSString*) getServerIp;

- (NSString*) getServerIpWithStreamId:(int)streamid;

- (void) addPZBInfo:(char*) url andContent:(char*) content;

- (int) changeOrientation:(int) orientation;

#pragma mark - extension log
+ (void) setLogApplicationGroup:(NSString*) group;
+ (void) clearScreencastLog:(NSString*) group;

#pragma mark - streaming related
- (int) getdatastatus;

- (int) getdatastatus:(int) streamid;

- (void) usePzvtTimestamp: (bool) usepzvt;


#pragma mark - record video

/**
 * @brief preset video recording parameter
 * @param  resolution resolution defines the resolution, it can only be set to 1080, 720, 540, 450, and 360.
 * @param  bitrate bitrate defines the bitrate, the unit is kb/s.
 * @param  fps fps defines the fps.
 * @param  filesize filesize defines the maximum filesize, unit is mb.
 * @param  type type defines the type of this stream. 0 means it's for record, while 1 means it's for live.
 * @param  direction direction defines the direction of this stream. 0 means it's for horizontal, while 1 means it's vertical.
 
 * @if return 0, it means the second stream is already started, else if return -1, it means the second stream is not started, and should be tried later.
 */
- (int)startSecondStreamwithResolution:(int)resolution withBitrate:(int)bitrate withFps:(int)fps withFilesize:(int) filesize withType:(int) type withDirection:(int) direction withFileName:(NSString*) FileName;

- (int)startSecondStreamwithResolution:(int)resolution withBitrate:(int)bitrate withFps:(int)fps withFilesize:(int) filesize withType:(int) type withDirection:(int) direction withFileName:(NSString*) FileName withStreamid:(int) streamid;

/**
 * @brief preset video recording parameter
 * @param  resolution resolution defines the resolution, it can only be set to 1080, 720, 540, 450, and 360.
 * @param  bitrate bitrate defines the bitrate, the unit is kb/s.
 * @param  fps fps defines the fps.
 * @param  filesize filesize defines the maximum filesize, unit is mb.
 * @param  type type defines the type of this stream. 0 means it's for record, while 1 means it's for live.
 * @param  direction direction defines the direction of this stream. 0 means it's for horizontal, while 1 means it's vertical.
 
 * @if return 0, it means the second stream is already successfully started, else  means the second stream is not started.
 */
- (int)startSecondStreamwithResolution:(int)resolution withBitrate:(int)bitrate withFps:(int)fps withFilesize:(int) filesize withType:(int) type withDirection:(int) direction withFullFilePath:(NSString*) filePath;

- (int)startSecondStreamwithResolution:(int)resolution withBitrate:(int)bitrate withFps:(int)fps withFilesize:(int) filesize withType:(int) type withDirection:(int) direction withFullFilePath:(NSString*) filePath withStreamid:(int) streamid;

/**
 * @brief stop recording video
 */
- (void)stopSecondStreamWithStreamid:(int) streamid;
- (void)stopSecondStream;

#pragma mark - VR timestamp offset

/**
 * @brief add offset to audio and video pts. specially used for vr push. the unit of the parameters is 100 nanoseconds. Therefore if want to set audioOffset to 0.2 second, parameter audioOffset should be set to 200*10000LL. This function should be called immediately after [[Transcoder tcs] start] is called.
 * @param  audioOffset the offset of audio pts.
 * @param  videoOffset the offset of video pts.
 */
- (void) setAudioOffset:(int64_t) audioOffset andVideoOffset:(int64_t) videoOffset;

#pragma mark - set packer target delay
//return 0 for success, -1 for error
- (int) setPackerTargetDelay:(int) delay;

- (int) setPackerTargetDelay:(int) delay withStreamid:(int) streamid;

// unit: s
- (void) setPushFailTime:(float) failTime;

#pragma iLiveA50

- (int) getTargetCaptureFps;

- (void) NSTest_ProbeRule:(int) pid andParam:(NSString*) param;

//return nil if fail
- (NSString*) NSTest_ReportCapablity:(int) pid;

- (int) US_EnablePush:(int) pid andState:(int) state;

- (NSString*) US_ReportPushState:(int) pid;

- (int) usDevice_ReportCapablity:(int) pid; 

- (void) setAudioTrackid:(int) trackid forDataSourceid:(int) datasourceid;

- (void) setVideoTrackid:(int) trackid forDataSourceid:(int) datasourceid;

- (void) changeDataSource:(int) datasourceid forAudioEncoder:(int) encoderIndex;

- (int) setMasterSlave:(int)pid withState:(int) state;


#pragma audio data compensation

- (void) setEnableCompensateAudioData:(bool) ifEnableCompensate;

- (void) setEnableResetAudioTimestamp:(bool) ifEnableReset;

- (void) setUpdateFpsUpdateInterval: (int) updateInterval calculateInterval: (int) calculateInterval;

- (void) setUpdateFpsUpdateInterval: (int) updateInterval calculateInterval: (int) calculateInterval withStreamid:(int) streamid;

- (void) reportJoinRoom: (int64_t) joinTick;

- (void) reportJoinRoom: (int64_t) joinTick withStreamid:(int) streamid;

- (void) setLargeDelayNotificationThreshold:(int) thresholdms;

- (void) setLargeDelayNotificationThreshold:(int) thresholdms withStreamid:(int) streamid;

- (int) resetWorkingModeWithParam:(PIProcessSetParam *) param;

- (int) resetWorkingModeWithParam:(PIProcessSetParam *) param withStreamid:(int) streamid;

- (int) recoveryUsState: (int) did;

#define PIPUSHING_CAMERA_FACING_UNKNOWN          0
#define PIPUSHING_CAMERA_FACING_FRONT            1
#define PIPUSHING_CAMERA_FACING_BACK             2
- (int) setCameraFacing: (int) facing;
- (int) setCameraFacing: (int) facing withStreamid:(int) streamid;
/**
 * @brief Mute the microphone and set audio encode bitrate.
 * @param Set muteflag to YES to mute the microphone, NO to turn it on.
 * @param when muteflag is YES, if bitrate set to 0, bitrate won't be changed.
 *        when muteflag is NO, if bitrate set to 0, audio bitrate will change to default bitrate set at the very beginning.
 */
- (int) setAudioMute:(BOOL)muteflag audioBitrate:(int) bitrate;

+ (void) getPIProcessVersion:(char*) version;

@end


#endif /* PIProcess_h */
