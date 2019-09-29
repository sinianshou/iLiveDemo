
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AVFoundation/AVCaptureVideoPreviewLayer.h>
#import <UIKit/UIKit.h>
#import "libdatabase.h"

@protocol TranscoderDelegate <NSObject>

/*!
 @method captureOutput:didOutputSampleBuffer:fromConnection:
 @abstract
 Called whenever an AVCaptureVideoDataOutput instance outputs a new video frame.
 
 @param captureOutput
 The AVCaptureVideoDataOutput instance that output the frame.
 @param sampleBuffer
 A CMSampleBuffer object containing the video frame data and additional information about the frame, such as its format and presentation time.
 @param connection
 The AVCaptureConnection from which the video was received.
 @param isNew
 The CMSampleBuffer returned is new alloc or original.If is new alloc,set *isNew = 1. If is not, don't set or set *isNew = 0. 
 
 @discussion
 Delegates receive this message whenever the output captures and outputs a new video frame, decoding or re-encoding it as specified by its videoSettings property. Delegates can use the provided video frame in conjunction with other APIs for further processing. This method will be called on the dispatch queue specified by the output's sampleBufferCallbackQueue property. This method is called periodically, so it must be efficient to prevent capture performance problems, including dropped frames.
 
 Clients that need to reference the CMSampleBuffer object outside of the scope of this method must CFRetain it and then CFRelease it when they are finished with it.
 
 Note that to maintain optimal performance, some sample buffers directly reference pools of memory that may need to be reused by the device system and other capture inputs. This is frequently the case for uncompressed device native capture where memory blocks are copied as little as possible. If multiple sample buffers reference such pools of memory for too long, inputs will no longer be able to copy new samples into memory and those samples will be dropped. If your application is causing samples to be dropped by retaining the provided CMSampleBuffer objects for too long, but it needs access to the sample data for a long period of time, consider copying the data into a new buffer and then calling CFRelease on the sample buffer if it was previously retained so that the memory it references can be reused.
 */
- (CMSampleBufferRef)PI_captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection andSampleBufferIsNew:(int*)isNew;

@optional
/**
 * return YES means libp31 will not call system setVideoOrientation. That means you may change orientation by yourself.
 */
- (BOOL)PI_DisableSystemChangeOrientation;

/**
 * return YES means libp31 will not call system mirror pushing stream. That means you may change by yourself.
 */
- (BOOL)PI_DisableSystemMirrorPushingStream;

/**
 * AudioData callback.
 @field          channelnum
 The number of interleaved channels in the buffer.
 @field          mSize
 The number of bytes in the buffer pointed at by mData.
 @field          mData
 A pointer to the buffer of audio data.
 */
/**
 CaptureData means audiodata from micphone.
 */
- (void)PI_AudioCallback_CaptureData:(void*)mData withDataSize:(UInt32)mSize withChannelNum:(UInt32)channelnum;
/**
 MusicData means audiodata from music you setted and played by "-(int)setMixerEnable:(BOOL)flag andsource:(NSString*) src andEcho:(BOOL) echoflag;" function.
 */
- (void)PI_AudioCallback_MusicData:(void*)mData withDataSize:(UInt32)mSize withChannelNum:(UInt32)channelnum withChannelSerial:(UInt32)channelserial;
/**
 MixedData means audiodata before pushing stream,which micphone audio data and music audio data are mixed.
 *@field        mTimeStamp
 The timestamp of audio data send to pushing stream.If you change this,return the changed timestamp.Or return mTimeStamp.
 */
- (int64_t)PI_AudioCallback_MixedData:(void*)mData withDataSize:(UInt32)mSize withChannelNum:(UInt32)channelnum andTimeStamp:(int64_t)mTimeStamp;

@end

/**
 **Availability**
 iOS 8.0+
 ----
 #Program Guide
 
 ##introduction of Transcoder
 * Transcoder class is the interface of libP31, there are interfaces for audio capture, video capture, audio encode and video encode. for each model, such as audio capture or encoder, you always have several choice for different requirements or Applications Scenarios.
 
 ##Directions for Transcoder
 * before you ready to use Transcoder, you need alloc Transcoder, but before alloc, you should know which interfaces Model you will used, more details about type of Applications Scenarios you can see directions of `allocwithtype`.
 * after alloc Transcoder, setparam to it, define refer to the struct of INTERFACE_SET_PARAMS
 
 */
@interface Transcoder : NSObject

@property (weak, nonatomic) id<TranscoderDelegate> delegate;

#pragma mark - Transcoder's construction and init
/**
 @name Transcoder's construction and init
 */
/**
 @brief construction of Transcoder, you can construct Transcoder and get its point through this function.
 
 ### **Description of type**
 * the first number means audio capture:
 * 1 means do not need libP31 capture audio, and the audio buffer struct you captured is `CMSampleBufferRef`
 * 2 means do not need libP31 capture audio, and the audio buffer you captured are bytes
 * 3 means do not need libP31 capture audio, and the audio buffer struct you captured is `CMSampleBufferRef`,used by Replaykit!
 * 5 means need libP31 capture audio, and libP31 will capture audio through `AudioUnit`
 * 6 means need libP31 capture audio, and libP31 will capture audio through `AVCaptureSession`
 * the second number means audio encoder:
 * 1 means libP31 do audio encoder through `AudioConvert`, and encoder params are ready when starting
 * 2 means libP31 do audio encoder through `AudioConvert`, and encoder params are not ready when starting, relevant interface refer to pragma mark **interface for no audio params when starting**
 * the thrid number means video capture:
 * 1 means do not need libP31 capture video, and the video buffer you captured is `CMSampleBufferRef`, relevant interface refer to pragma mark **interface for no video capture in lib**
 * 5 means need libP31 capture video, libP31 capture video default with back camera
 * 6 means need libP31 capture video, libP31 capture video default with front camera
 * 3 means need libP31 capture video, libP31 capture video default with back camera, with delegate for avcapture enable.AVCapture setting dataoutput is kCVPixelFormatType_420YpCbCr8BiPlanarFullRange;
 * 4 means need libP31 capture video, libP31 capture video default with front camera, with delegate for avcapture enable.AVCapture setting dataoutput is kCVPixelFormatType_420YpCbCr8BiPlanarFullRange;
 * 7 means need libP31 capture video, libP31 capture video default with back camera, with delegate for avcapture enable.AVCapture setting dataoutput is kCVPixelFormatType_32BGRA;
 * 8 means need libP31 capture video, libP31 capture video default with front camera, with delegate for avcapture enable.AVCapture setting dataoutput is kCVPixelFormatType_32BGRA.
 * 9 means do not need video capture at all.(most likely to be used in pure audio push)
 * the fourth number means video encoder:
 * 1 means libP31 will encode video with `VideoToolBox`, and encode is a sync process
 * 2 means libP31 will encode video with `VideoToolBox`, and encode is a async process
 
 * for example, if we want use `CMSampleBufferRef` for audio and video, `AudioConvert` for audio encoder, `VideoToolBox` for video encoder, then we should set type to 1111. if we do not want do capture myself, then we can set type to 6151. thus, libP31SDK will do capture
 
 @param type type is consist of 4 number, such as 5152, each stands for a different meaning. more details see **Description of type**
 @since iOS 8.0+
 */
+ (void) setLogApplicationGroup:(NSString*) group;
+ (void) clearScreencastLog:(NSString*) group;
+ (void) transcoderGlobalInit;
+ (void) transcoderGlobalInitWithLogPath:(char*) logPath;
+ (void) allocwithtype:(int) type;
+ (void) allocwithAudioCapture:(PS_AudioCaptureMode) audioCaptureMode
                andAudioEncode:(PS_AudioEncodeMode) audioEncodeMode
               andVideoCapture:(PS_VideoCaptureMode) videoCaptureMode
                andVideoEncode:(PS_VideoEncodeMode) videoEncodeMode;

+ (void) allocWithAudioCapture: (PS_AudioCaptureType) audioType
               andVideoCapture: (PS_VideoCaptureType) videoType
                    andOptions: (PS_InitOptionType) options;

+ (void) allocWithAudioDataSources:(NSArray *) audioDataSources andVideoDataSources:(NSArray *) videoDataSources;

+ (void) transcoderGlobalRelease;

#pragma mark - App switch between background and foreground
/**
 @name App switch between background and foreground
 */
/**
 @brief should call this functions while app switch to background
 */
- (void) settoBackground;
- (void) settoBackground: (PS_PushBackgroundBehaviour) backgroundChoice;

/**
 @brief should call this functions while app switch to foreground
 
 @return 0 for success, -1 for retrieving audio permission failed
 
 */
- (PS_Transcoder_Errorcode) settoForeground;
- (PS_Transcoder_Errorcode) settoForeground:(PS_PushForegroundBehaviour) foregroundChoice;

- (int) settoForegroundNoResume;

- (void) audioSessionInterrupt;

- (PS_Transcoder_Errorcode) audioSessionResume;

#pragma mark - Common Functions
/**
 @name Common Functions
 */
#pragma mark get class point
/**
 @name get class point
 */
/**
 @brief you can get Transcoder's point through it
 */
+ (Transcoder*) tcs;

#pragma mark set param
/**
 @name set param
 */
/**
 @brief set param to `Transcoder`
 @param param refer to struct `PINTERFACE_SET_PARAMS`
 @return list as follow
 
 * 0 for success
 * other for failed
 */
- (int) setparam:(PINTERFACE_SET_PARAMS) param;

#pragma mark get status
/**
 @name get status
 */
/**
 @brief get param to show capturing or encoding or streaming status
 @return 0 if success
 */
- (PINTERFACE_GET_PARAMS) getparam;

- (PINTERFACE_GET_PARAMS) getparamWithStreamId:(int)streamid;

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

//return 0 for success, other for fail
- (int) getMpathUsage:(uint64_t*)totalsize andMpathn:(unsigned int*)mpathn andMpathUsage:(uint64_t*)mpath_usage andMpathName:(char*)mpathName;

- (int) getMpathUsage:(uint64_t*)totalsize andMpathn:(unsigned int*)mpathn andMpathUsage:(uint64_t*)mpath_usage andMpathName:(char*)mpathName streamid:(int)streamid;

/**
 @brief return live streaming State
 @return list as follow
 
 * 1 means live streaming is on
 * 0 means live streaming is off
 */
- (int) getrunningstat;

- (int)getrunningstat:(int) streamid;

- (int) getpushingstatus;

/**
 0 means not pushing
 1 means pushing
 */
- (int) getpushingstat;

/**
 @brief useful when live streaming is on, check if there are no video and audio data are inserted to `PSLStreaming`
 
 @return list as follow
 
 * -1  no video&audio data are inserted to `PSLStreaming`
 * 0   insert normal or not started
 
 */
- (int) getdatastatus;

- (void) addPZBInfo:(char*) url andContent:(char*) content;

#pragma mark interface for streaming
/**
 @name start or stop interface
 */
/**
 @brief start encoder and packer,
 @return list as follow
 
 * 0 means success
 * 1 means already started
 * other value means failed
 */
- (PS_Transcoder_Errorcode) start;

- (int) addStreamWithStreamParam:(PINTERFACE_SET_PARAMS) param;

- (int) addStreamWithPIProcessParam:(PIProcessSetParam*) param;

/**
 @brief stop encoder and packer
 @return list as follow
 
 * 0 for success
 * other for failed
 */
- (int) stop;

- (int) stopWithStreamId:(int)streamid;

/**
 * @brief stop encoder and packer with reason PSL_STOPREASON_SYSTEMINTERRUPT. 
 *        It is designed for restart.
 * @return
 * 0 for success
 * other for failed
 */
- (int) stopForRestart;

/**
 * @brief reset the key frame duration during the stream is on
 * @param duration: the key frame duration in seconds
 * @return
 * 0 for success
 * others for failed
 */
- (int) resetKeyFrameDuration:(float) duration;

/**
 * @brief reset the key frame duration during the stream is on
 * @param duration: the key frame duration in seconds
 * @param streamid: id of the stream
 * @return
 * 0 for success
 * others for failed
 */
- (int) resetKeyFrameDuration:(float) duration withStreamId:(int) streamid;

#pragma mark write log to lib's log system
/**
 @name write log to lib's log system
 */
/**
 @brief write log to file through `PSLStreaming`
 @param log the string that write to file
 */
- (void) LogToFile:(char*) log;

- (void) LogToFile:(char*) log atLevel:(PS_LogLevel) level;

#pragma mark - AudioUnit Cap Mode
/**
 @name AudioUnit Cap Mode
 */

#pragma mark AudioRoute Support
/**
 @name AudioRoute
 */
/**
 @brief recheck audio input route when audio route changed
 */
-(void)switchAudioRoute;

/**
 @brief restart audio capture, only avaliable when using audio unit.
 */
- (void) stopAudioCapture;

- (void) restartAudioCapture;

#pragma mark echo suppression
/**
 @name echo suppression
 */
/**
 @brief to open or close Echo suppression. used before streaming start, in addition, audio capture type should be 5 -- AudioUnit capture, if not, it will never be effective, more details see **Description of type**
 @param flag true for open Echo, false for close Echo
 */
- (void)setEcho:(BOOL)flag;

/**
 @brief will return Echo suppression status. only used when audio cap type is 5 -- AudioUnit capture, if not, it will return 0 always, more details see **Description of type**
 @return return current echo status, 0 for close, 1 for open
 */
- (int)getEchoflag;

#pragma mark transcoder Mixer

-(int)prepareMixerWithSource:(NSString *)src;
-(int)prepareMixerWithSource:(NSString *)src andCompletion:(void(^)())completionBlock;
-(int)setifSendMixedData:(bool)ifSend;
-(int)startMixer;
-(int)setMixerMusicVolume:(int)volume;
-(int)pauseMixer;
-(int)resumeMixer;
-(int)stopMixer;
-(int)enableMixerTimestamp:(bool)ifEnable datasourceid:(int) ds_index;
// for callback, parameter refer to ds_index, return value is the related extra timestamp
-(void)setAudioExttimestampCallback:(int64_t(^)(int)) callback forDatasource:(int) ds_index;
/**
 * @brief set microphone sound echo to headset. default set to true.
 * @param ifEnable: true to enable, false to disable
 */
-(int)setMicEchoEnable:(int) ifEnable;
/**
 @param seekTime: time in ms
 @discussion: if no mixer, return -1; if mixer is running, return 1, if mixer is not running, return 2
 */
-(int)seekMixer:(int64_t)seekTime;

//default set to YES
-(int)enableMixerAutoSync:(BOOL)ifEnable;


/**
 @brief to get progress of the Music playing
 @param If 'format' is 0 or PROGRESS_IN_MS, function returns the progress in millisecond.
 If 'format' is 1 or PROGRESS_IN_PERCENTAGE, function returns the progress in percentage.
 @name transcoder Mixer suppression
 */
-(float) getMixerMusicProgress:(int)format;

/**
 *@brief get total length of the Music playting
 @return total length of the music playing in millisecond
 */
-(float) getMixerMusicLengthMs;

/**
 @brief used to enable Mixer or disable Mixer. used when streaming is on, in addition, only used when audio cap type should be 5 -- AudioUnit capture, if not, it will do Null, more details see **Description of type**
 @param flag true to enable Mixer or false to disable Mixer
 @param src if flag is true, set audio src to Mixer, else, set nil.
 @param block you may set flag to false to shut down mix, or you may change src to change music playing!
 @return value
 
 * 0 for success
 * other for failed
 */
-(int)setMixerEnable:(BOOL)flag andsource:(NSString*) src;
-(int)setMixerEnable:(BOOL)flag andsource:(NSString*) src andCompletion:(void(^)())block;

/**
 * @brief Pause and resume music mixer
 * @param Set 'pause' 'YES' to pause mixer music, and 'NO' to resume mixer.
 */

-(void)pauseMixer:(BOOL)pause;

/**
 * @brief check if there is a headset
 * @return true means have headset
 */
+ (BOOL)isHeadsetPluggedIn;

/**
 * @brief Mute the microphone.
 * @param Set muteflag to YES to mute the microphone, NO to turn it on.
 * @return 0 for success.
 */
- (int) setMicMute:(BOOL)muteflag;

/**
 * @brief Mute the microphone and set audio encode bitrate.
 * @param Set muteflag to YES to mute the microphone, NO to turn it on.
 * @param when muteflag is YES, if bitrate set to 0, bitrate won't be changed.
 *        when muteflag is NO, if bitrate set to 0, audio bitrate will change to default bitrate set at the very beginning.
 */
- (int) setMicMute:(BOOL)muteflag audioBitrate:(int) bitrate;

/**
 * @brief set and get mic volume
 * @param  volume [0,100] 0 is MIN volume(no voice), 100 is MAX volume.Default is 50.
 */
- (void)setMic_volume:(int)volume;
- (int)getMic_volume;

/**
 * @brief set and get music volume
 * @param  volume [0,100] 0 is MIN volume(no voice), 100 is MAX volume.Default is 50.
 * @param  cnum is the number of which music channel.
 */
- (void)setMusic_volume:(int)volume atChannelNum:(int)cnum;
- (int)getMusic_volumeAtChannelNum:(int)cunm;

#pragma mark transcoder Metronome
- (int) startMetronome:(int) samplerate andChannels:(int) channels andNote:(int) note andRate:(int) rate andBeats:(int) beats andBeatsArray:(char*) beats_array andElementSize:(int*) element_size andElementRhythm:(char*[TRANSCODER_METRO_ELEMENT_MAX_COUNT])element_rhythm;
- (void) toggleIfSendMetronome:(BOOL) ifSend;
- (int) pauseMetronome;
- (int) resumeMetronome;
- (int) stopMetronome;
// volume should be [0, 100], where 0 means silence, and 100 means max volume
- (int) setMetronome_volume:(int)volume;

#pragma mark AudioVolume
/**
 @brief setVolume Callback function
 @param volumeCallback if need volume info, set a callback function
 if not, set nil
 */
-(void) setVolumeCallback:(VOLUMECALLBACK)volumeCallback;

#pragma mark - audio effect
/**
 * @brief set and get mic pitch
 * @param  effidx [-12,12]. -12 is MIN pitch,12 is MAX pitch.0 for close.Default is 0.
 */
- (void)setMic_pitch_effidx:(int)effidx;
- (int)getMic_pitch_effidx;

/**
 * @brief set and get music pitch
 * @param  effidx [-12,12]. -12 is MIN pitch,12 is MAX pitch.0 for close.Default is 0.
 */
- (void)setMusic_pitch_effidx:(int)effidx;
- (int)getMusic_pitch_effidx;

#pragma mark - interface for Camera
/**
 @name interface for Camera
 */
#pragma mark common functions
/**
 @brief return point of preview which camera captured, used after camera starting up. if videocapflag is set to 9, nil will be returned.
 @return AVCaptureVideoPreviewLayer point, preview that camera captured
 */
- (AVCaptureVideoPreviewLayer*) getpreviewlayer;

/**
 @brief start camera
 @see stopcamera
 */

- (void) setCameraParam:(PINTERFACE_CAMERA_PARAMS) param;

- (void) setPresetMode:(PS_WorkingMode) pushmode;

- (void) startcamera;

- (void) startcamera:(CALayer*)parentPreviewLayer;

/**
 @brief close camera
 @see startcamera
 */
- (void) stopcamera;

- (void) enableCameraCrop: (BOOL) ifEnable;

/**
 @brief when iphone's orientation is changed, this function need to be called
 */
- (void) change_orientation;

/**
 @brief Adjust camera‘s orientation accorting to device's orientation. in addtion, it will return current orientation of device
 */
- (int) getorientation;

/**
 @brief to change camera from back to front or from front to back
 */
- (int) camera_trans;

#pragma mark torch switch
/**
 @name torch switch
 */
/**
 @brief change torch status while using background camera
 @param flag 0 for torch off, 1 for torch on
 */
- (void) torchonoff:(int) flag;

/**
 @brief return camera direction
 @return 0 for front camera, 1 for back camera
 */
- (int) getcameradirection;

#pragma mark interface for Bias
/**
 @name interface for Bias
 */
/**
 @brief get the min ExposureBias value iphone support
 @return list as follow
 
 * -2, if camera is not inited
 * a float value that mean minBias
 */
-(float)getminBias;

/**
 @brief get the max ExposureBias value iphone support
 @return list as follow
 
 * return -2, if camera is not inited
 * a float value that mean maxBias
 */
-(float)getmaxBias;

/**
 @brief set ExposureBias value you want
 @param Bias Bias value will set
 @return list as follow
 
 * 0 for success
 * -1 for failed
 */
-(int)setBias:(float)Bias;

//get AVCapture queue
- (dispatch_queue_t)getAVCapQueue;

#pragma mark interface for zoom
/**
 @name interface for zoom
 */
/**
 @brief Begins a smooth transition from the current zoom factor to another.
 @param factor The new magnification factor.
 */
- (void) rampvideozoom:(UIPinchGestureRecognizer *)recognizer;

- (void) cameraZoom:(float) zoomScale;

/**
 @brief called before camera start
 @param zoom float value in scale [1.0, 6.5];
 */
- (void) setdefaultzoom:(CGFloat) zoom;

- (int) taptoExposeX:(CGFloat) X andY:(CGFloat) Y;

#pragma mark interface for focus
/**
 @name interface for focus
 */
/**
 @brief tap screen to make camera focus on the area that tapped
 @param X the x position of taped point on screen, scale [0.0, 1.0]
 @param Y the y position of taped point on screen, scale [0.0, 1.0]
 @return list as follow
 
 * 0 for successed
 * -1 for lock device failed
 * -2 for device not supprot tap focus
 * -3 for capture not init
 */
- (int)taptoFocusX:(CGFloat) X andY:(CGFloat) Y;

/**
 @brief changeCamera's FocusMode
 @param mode can set: `AVCaptureFocusModeLocked` or `AVCaptureFocusModeAutoFocus`
 @return list as follow
 
 * AVCaptureFocusMode for set success
 * -1 for failed
 * -2 mode not supported
 
 @see AVCaptureFocusMode
 */
- (AVCaptureFocusMode)setFocusMode:(AVCaptureFocusMode)mode;

/**
 @brief used when focus mode is `AVCaptureFocusModeLocked`
 @param value can set a value between 0.0 and 1.0
 @return list as follow
 
 * 0 for set success
 * -1 for set failed
 * -2 for focus mode is not `AVCaptureFocusModeLocked`
 
 @see AVCaptureFocusMode
 */
- (int)setfocusPosition:(float)value;

/**
 @brief set slider and lebal to capture module, then capture can update it while needed
 */
-(void)setfocusslider:(id)slider andfocuslebal:(id)lebal;

/**
 @brief set flag to tell capture module if UI params update is neccessary
 @param updateflag false for no need update, true for need update
 */
-(void)setupdateflag:(BOOL)updateflag;


#pragma mark - interface for no video capture in lib
/**
 @name interface for no video capture in lib
 */
/**
 @brief used when no need lib capture video, send video frame to libP31
 @param samplebuf video data in `CMSampleBufferRef` to be encoded and sended
 */
- (void) sendvideoframe:(CMSampleBufferRef) samplebuf;

- (void) sendvideoframe:(CMSampleBufferRef) samplebuf streamid:(int)streamid;

- (void) sendvideoframe:(CMSampleBufferRef) samplebuf withDataSource:(int) ds_index;

- (void) sendvideoframe:(CVImageBufferRef) videoframe withPts:(CMTime) pts withDuration:(CMTime) duration withDateSource:(int32_t) ds_index;

/**
 @name interface for no audio capture in lib
 */
/**
 @brief used when no need lib capture audio, send audio frame to libP31
 @param samplebuf audio data in `CMSampleBufferRef` to be encoded and sended
 */
- (void)sendaudioframe:(CMSampleBufferRef)samplebuf;

- (void)sendaudioframe:(CMSampleBufferRef)samplebuf streamid:(int)streamid;

/**
 @brief used when no need lib capture audio, set audio data to libP31
 @param buffer audio buffer to be encoded and sender
 @param size samples of audio buffer had
 */
- (void) sendaudioframe:(int16_t*) buffer andsize:(int) size;

- (void) sendaudioframe:(int16_t*) buffer andsize:(int) size streamid:(int)streamid;

- (void) sendaudioframe:(int16_t*) buffer andsize:(int) size andExtraTs:(int64_t) extraTs;

- (void) sendaudioframe:(int16_t*) buffer andsize:(int) size andExtraTs:(int64_t) extraTs streamid:(int)streamid;

- (void) sendaudioframe:(int16_t*) buffer andsize:(int) size andExtraTs:(int64_t) extraTs datasource:(int)ds_index;

/**
 * For replaykit to use
 */
- (void)sendaudioframe:(CMSampleBufferRef)samplebuf withType:(PS_AudioSampleType)type;

- (void)sendaudioframe:(CMSampleBufferRef)samplebuf withType:(PS_AudioSampleType)type withStreamid:(int) streamid;

#pragma mark - interface for no audio params when starting
/**
 @name interface for no audio params when starting
 */
/**
 @brief used when no need lib capture audio, set audio params to libP31
 @param config is a point of struct `ENCODE_AUDIO_CONFIG`
 */
- (int) setAudioParams:(void*)config;

#pragma mark - Unity Game Project Used
/**
 @name Unity Game Project Used
 */
/**
 @brief used by Unity Game, set current encoder's number to libP31
 @param num num of encoders
 */
- (void) setmonitor2:(int) num;

/**
 @brief may be used when no need lib capture video, get encoder's `CVPixelBufferPoolRef` from libP31 if needed
 */
- (CVPixelBufferPoolRef) getpiexlpool;

#pragma mark -- interface for dns
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

/**
 * @brief return the audio delay time
 */
- (double) getAudioDelay;

/**
 @brief reset the audio delay detection
 */

/**
 @brief set preview to mirror or not,defalult is disable,which means that the receiving stream picture is the same as pushing stream picture. Only useful for front camera！
 @param mirrorenable true for enable, false for disable
 */
- (void)setPushingStreamMirror:(BOOL)mirrorenable;

/**
 * @brief return the AVCaptureSession
 */
- (AVCaptureSession*)getAVCaptureSession;


#pragma mark -- interface for libp31 render preview
/**
 * @brief init PSGLpreview with frame
 */
- (void)initPI_PreviewWithFrame:(CGRect)frame;
/**
 * @brief release PSGLpreview
 */
- (void)releasePI_Preview;
/**
 * @brief return PSGLpreview
 */
- (UIView*)getPI_Preview;
/**
 * @brief render with CImage.Please make sure you call this function in main thread!
 */
- (void)renderWithCImage:(CIImage *)image;
/**
 * @brief render with Pixelbuffer.Please make sure you call this function in main thread!
 */
-(void)renderWithPixelbuffer:(CVPixelBufferRef)pixelbuffer;
/**
 * @brief Creates a new image referencing the contents of the GL texture object
 * with identifier 'name'. The texture should have dimensions as defined
 * by 'size'. If 'flipped' is true, then the contents of the texture are
 * flipped vertically when referenced. 'colorSpace' defines the color space
 * that the image is defined in, if nil, the texture is not color matched.
 * Please make sure you call this function in main thread!
 */
- (void)renderWithTexture:(unsigned int)name
                     size:(CGSize)size
                  flipped:(BOOL)flipped
      applyingOrientation:(int)orientation;

#pragma mark - save video frame
/**
 * @brief Save a video frame as UIImage. Return it through callback block.
 */
- (void)saveFrame:(void(^)(UIImage*))block;

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

- (int)startRecordingwithResolution:(int)resolution withBitrate:(int)bitrate withFps:(int)fps withFilesize:(int) filesize withType:(int) type withDirection:(int) direction withFileName:(NSString*) FileName;
- (void)stopRecording;

/**
 * @brief stop recording video
 */
- (void)stopSecondStreamWithStreamid:(int) streamid;
- (void)stopSecondStream;

#pragma mark - interruption
/**
 * @brief pause the transcoder, stop pslstreaming, but keep capture and encoder
 */
- (int)pause;

/**
 * @brief resume the transcoder, restart pslstreaming, no need for restart of capture or encoder
 */
- (void)resume;

/**
 * @brief switch using bluetooth headphone
 * @param  flag defines if to open bluetooth or close bluetooth. 1 means to open and 0 means to close.
 */
- (void)switchBluetooth:(bool) flag;


#pragma mark - VR timestamp offset

/**
 * @brief add offset to audio and video pts. specially used for vr push. the unit of the parameters is 100 nanoseconds. Therefore if want to set audioOffset to 0.2 second, parameter audioOffset should be set to 200*10000LL. This function should be called immediately after [[Transcoder tcs] start] is called.
 * @param  audioOffset the offset of audio pts.
 * @param  videoOffset the offset of video pts.
 */
- (void) setAudioOffset:(int64_t) audioOffset andVideoOffset:(int64_t) videoOffset;

#pragma mark - Snapshot with pzvt
/**
 * @brief take a screenshot of the captured image at the given pzvt time and offset. This file will be saved under the Document folder.
 * @param  pzvttime: the pzvttime to take the screenshot.
 * @param  fileName: the fileName to save. CAUTION: fileName should be file name with absolute file path. Otherwise, it will fail.
 */
- (void) SnapshotWithPZVT:(int64_t) pzvttime withFileName:(NSString*) fileName;

//ifsuccess==0 means snapshot success, ifsuccess==-1 means snapshot fail, and image will be nil
- (int) SnapshotWithPZVT:(int64_t) pzvttime withFileName:(NSString*) fileName finishCallback:(void (^)(UIImage *image, int taskid, PS_SnapshotResult ifsuccess))finishCallback;
- (void) stopSnapshotTask:(int) taskid;

#pragma mark - set packer target delay
//return 0 for success, -1 for error
- (int) setPackerTargetDelay:(int) delay;

- (int) setPackerTargetDelay:(int) delay withStreamid:(int) streamid;


#pragma mark - post event
//post event
//return 0 for success, -1 for not success
- (int) postEventIAwithEventId:(int) eventId andEventBody:(char *) eventBody andEventSize:(int) eventSize andStamp:(int64_t) stamp;

//return number of event posted
- (int) postEventIAwithEventId:(int) eventId andEventBody:(char *) eventBody andEventSize:(int) eventSize andStamp:(int64_t) stamp streamid:(int)streamid;

#pragma mark - change settings when streaming

- (int) resetModewithWorkingMode:(PTRANSCODER_WORKING_MODE) workmode
                        andParam:(PINTERFACE_SET_PARAMS) param;

- (int) resetModewithParam:(PINTERFACE_SET_PARAMS) param
               andStreamid:(int) streamid;

- (int) resetWorkingModeWithParam:(PIProcessSetParam *) param;

- (int) resetWorkingModeWithParam:(PIProcessSetParam *) param withStreamid:(int) streamid;

- (void) resetVideoConfig:(int) bitrate withFps:(int) fps withHeight:(int) height withWidth:(int) width;

#pragma mark - set callbacks
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

- (void) setUsrMsgCallback: (void(^)(const char *)) msgCallback streamid:(int) streamid;

- (void) setPushStatusCallback_SendSuccess_withid: (void(^)(int))sendSuccessCallback streamid:(int) streamid;
- (void) setPushStatusCallback_NetworkFailed_withid: (void(^)(int))networkFailCallback streamid:(int) streamid;
- (void) setPushStatusCallback_DelayTooLarge_withid: (void(^)(int))delayTooLargeCallback streamid:(int) streamid;
- (void) setPushStatusCallback_StartFailed_withid: (void(^)(int))startFailedCallback streamid:(int) streamid;
- (void) setPushStatusCallback_NoVideoData_withid: (void(^)(int))noVideoDataCallback streamid:(int) streamid;
- (void) setPushStatusCallback_NoAudioData_withid: (void(^)(int))noAudioDataCallback streamid:(int) streamid;
- (void) setPushStatusCallback_SendFail_withid: (void(^)(int))sendFailCallback streamid:(int) streamid;

- (void) setPushSuccessCallback_withid: (void(^)(int))pushSuccessCallback streamid:(int) streamid;
- (void) setRePushSuccessCallback_withid: (void(^)(int))rePushSuccessCallback streamid:(int) streamid;

- (void) setMscStatusCallback_withid: (void(^)(int streamid, int status))mscStatusCallback streamid:(int) streamid;

- (void) setUsrMsgCallback_withid: (void(^)(int streamid, const char *)) msgCallback streamid:(int) streamid;

- (void) setCoreSdkStatusCallback: (onCoreSdkStatus) callback;
//true for running, false for not running
- (BOOL) getCameraStatus;


#pragma mark - unity
- (size_t) getLastFrameData:(void*) data;

- (int) getLastFrameWidth;

- (int) getLastFrameHeight;

- (int64_t) getLastFrameTimestamp;

- (void) enableUnityPreview:(bool) ifEnable;


- (void) usePzvtTimestamp:(bool) usepzvt;

#pragma iLiveA50

- (void) NSTest_ProbeRule:(int) pid andParam:(NSString*) param;

//return nil if fail
- (NSString*) NSTest_ReportCapablity:(int) pid;

- (int) US_EnablePush:(int) pid andState:(int) state;

- (NSString*) US_ReportPushState:(int) pid;

- (int) usDevice_ReportCapablity:(int) pid;

- (int) setMasterSlave:(int) pid withState:(int) state;

- (void) setReplaykitStartImage:(UIImage*) image;

- (void) setReplaykitStartImage:(UIImage*) image withStreamid:(int)streamid;

- (void) toggleSendAppAudio:(bool) ifSend;

- (void) toggleSendAppAudio:(bool) ifSend withStreamid:(int) streamid;

- (void) setReplaykitCaptureMode:(bool) ifCaptureAppAudio with:(bool) ifCaptureMicAudio with:(bool) ifCaptureAppScreen;

- (void) restartReplaykit;

- (void) replaykitMixAppAudio: (int) percentage;

- (void) setAudioTrackid:(int) trackid forDataSourceid:(int) datasourceid;

- (void) setVideoTrackid:(int) trackid forDataSourceid:(int) datasourceid;

- (void) changeDataSource:(int) datasourceid forAudioEncoder:(int) encoderIndex;


- (void) setEnableCompensateAudioData:(bool) ifEnableCompensate;

- (void) setEnableResetAudioTimestamp:(bool) ifEnableReset;

- (int) sendDataFrame:(uint8_t*) dataframe andSize:(size_t) size andTimestamp:(int64_t) timestamp andFlag:(uint32_t) flag;

- (int) sendDataFrame:(uint8_t*) dataframe andSize:(size_t) size andTimestamp:(int64_t) timestamp andFlag:(uint32_t) flag withStreamid:(int) streamid;

- (void) disableReplaykitPushScreenVideo;

- (void) enableReplaykitPushScreenVideo;

- (void) setUpdateFpsUpdateInterval: (int) updateInterval calculateInterval: (int) calculateInterval;

- (void) setUpdateFpsUpdateInterval: (int) updateInterval calculateInterval: (int) calculateInterval withStreamid:(int) streamid;

// this method should be called after transcoder inited
- (void) reportJoinRoom: (int64_t) joinTick;

- (void) reportJoinRoom: (int64_t) joinTick withStreamid:(int) streamid;

- (void) setTargetAudioSessionOption:(unsigned long) targetOption;

- (void) setLargeDelayNotificationThreshold:(int) thresholdms;

- (void) setLargeDelayNotificationThreshold:(int) thresholdms withStreamid: (int) streamid;

// unit: s
- (void) setPushFailTime:(float) failTime;

+ (void) setAudioCaptureMode:(PS_TranscoderAudioCaptureMode) mode;

+ (void) externListenForInterruption:(bool) ifListen;

+ (void) getTranscoderVersion:(char*) version;

@end


