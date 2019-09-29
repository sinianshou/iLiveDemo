//
/*
 * Copyright (c) 2017 Powerinfo. All rights reserved.
 */
//

#import <Foundation/Foundation.h>
#import <PI_MediaPlayer/PIMoviePlayerController.h>
#import <transcoder/libtranscoder.h>

#import "PIiRoom.h"
#import "RsCallback.h"
#import "PINSResult.h"
#import "MetronomeChannelConfigSpec.h"
#import "PIiRoomPeerShared.h"
#import "PIiRoomConfig.h"
#import "PIStatistics.h"


@protocol PeerDelegate<PIiRoomShared_PeerCallback>
@end

@protocol MixerDelegate<PIMixerCallback>
@end

@protocol RsCallbackDelegate<PIRsCallback>
@end

@interface PIiRoomPeer : PIiRoomPeerShared

/**
 开启网络状态测试
 */
+ (void)startNSTest;

/**
 关闭网络状态测试
 */
+ (void)stopNSTest;

/**
 获取网络状态测试结果
 */
+ (PINSResult*)getNSTestResult;

/**
 检测是否带蓝牙耳机
 */
+ (BOOL)isBluetoothHeadsetOn;

/**
 检测是否带有线耳机
 */
+ (BOOL)isWiredHeadsetOn;

/**
 检测是否插声卡
 */
+ (BOOL)isSoundCardOn;


/**
 * 观众加入房间前，调用该接口，不访问 RoomServer，本地构造数据。
 * 已减少观众秒开时间。
 * 此接口内部会访问网络，为同步执行，需在子线程调用。
 *
 * @param uid 用户 uid
 * @param creatorUid 要收的主播 uid
 * @param roomId 房间号
 * @param playStreamMode 收流模式
 * @param url 收流 url
 */
+ (void)preloadWithUid:(NSString*)uid
        withCreatorUid:(NSString*)creatorUid
            withRoomId:(NSString*)roomId
    withPlayStreamMode:(int)playStreamMode
               withUrl:(NSString*)url;

+ (void)preloadWithUid:(NSString*)uid
        withCreatorUid:(NSString*)creatorUid
            withRoomId:(NSString*)roomId
    withPlayStreamMode:(int)playStreamMode
               withUrl:(NSString*)url
       withSkipOnExist:(BOOL)skipOnExist;

+ (void)publishPrepareToJoin:(AVAudioSessionCategoryOptions)options;

+ (void)viewerPrepareToJoin:(AVAudioSessionCategoryOptions)options;

/**
 初始化 peer

 @param uid uid
 @param role 角色 ROLE_NORMAL 或者 ROLE_VIEWER
 @param callback PeerDelegate 回调，iRoom 事件回调，建议实现 PeerDelegate 时继承自 SimplePeerDelegate，
 这样可以只实现感兴趣的回调接口，且以后 SDK 增加回调，可以不用修改代码。
 @return self
 */
- (instancetype)initWithUid:(NSString*)uid
                   withRole:(PIiRoomRole)role
               withCallback:(id<PeerDelegate>)callback;

/**
 初始化 peer

 @param uid uid
 @param previewAtStart 是否开启预览
 @param callback PeerDelegate 回调，iRoom 事件回调，建议实现 PeerDelegate 时继承自 SimplePeerDelegate，
 这样可以只实现感兴趣的回调接口，且以后 SDK 增加回调，可以不用修改代码。
 @return self
 */
- (instancetype)initWithUid:(NSString*)uid
         withPreviewAtStart:(bool)previewAtStart
               withCallback:(id<PeerDelegate>)callback;

/**
 初始化 peer

 @param uid uid
 @param veName 视角名
 @param previewAtStart 是否开启预览
 @param callback PeerDelegate 回调
 @return self
 */
- (instancetype)initWithUid:(NSString*)uid
                 withVeName:(NSString*)veName
         withPreviewAtStart:(bool)previewAtStart
               withCallback:(id<PeerDelegate>)callback;

/**
 配置房间和用户信息（无美颜）

 @param roomConfig 房间配置
 @param previewParam 预览配置
 @param encParam 编码配置
 @param viewConfig 视图配置
 */
- (void)configurePIiRoomConfig:(PIPIiRoomConfig*)roomConfig
               previewParam:(INTERFACE_CAMERA_PARAMS*)previewParam
            processSetParam:(PIProcessSetParam*)processSetParam
             roomViewConfig:(PIiRoomViewConfig*)viewConfig;

/**
 配置房间和用户信息（有美颜）

 @param roomConfig 房间配置
 @param previewParam 预览配置
 @param encParam 编码推流配置
 @param viewConfig 视图配置
 @param preview 美颜视图，需要将视图传入 iRoom 层管理
 @param transcoderDelegate 美颜数据采集回调
 */

- (void)configurePIiRoomConfig:(PIPIiRoomConfig*)roomConfig
               previewParam:(INTERFACE_CAMERA_PARAMS*)previewParam
            processSetParam:(PIProcessSetParam*)processSetParam
             roomViewConfig:(PIiRoomViewConfig*)viewConfig
                    preview:(UIView*)preview
         transcoderDelegate:(id<TranscoderDelegate>)transcoderDelegate;

/**
 变更推收流行为
 
 @param append 是否为增量模式，true 为增量，false 为全量
 @param cmds 所有目标房间的 Cmd
 */
- (void)changeBehavior:(bool)append cmds:(NSArray*)cmds;

/**
 变更推收流行为
 
 @param append 是否为增量模式，true 为增量，false 为全量
 @param cmds 所有目标房间的 Cmd
 @param allVe 是否操作全部视角（使用多视角功能才会用到）
 @param rsReqId rsReqId id,用于标记是哪次 changeBehavior 操作
 */
- (void)changeBehavior:(bool)append cmds:(NSArray*)cmds allVe:(BOOL)allVe rsReqId:(NSString*)rsReqId;

/**
 变更推收流行为
 
 @param append 是否为增量模式，true 为增量，false 为全量
 @param cmds 所有目标房间的 Cmd
 @param mergeInfo 房间合并信息
 @param splitInfo 房间拆分信息
 @param allVe 是否操作全部视角（使用多视角功能才会用到）
 @param rsReqId rsReqId id,用于标记是哪次 changeBehavior 操作
 */
- (void)changeBehavior:(bool)append
                  cmds:(NSArray*)cmds
             mergeInfo:(NSString*)mergeInfo
             splitInfo:(NSString*)splitInfo;
/**
 变更推收流行为

 @param append 是否为增量模式
 @param cmds 所有目标房间的 Cmd
 @param mergeInfo 合并参数
 @param splitInfo 拆分参数
 @param allVe 是否操作全部视角
 */
- (void)changeBehavior:(bool)append
                  cmds:(NSArray*)cmds
             mergeInfo:(NSString*)mergeInfo
             splitInfo:(NSString*)splitInfo
                 allVe:(BOOL)allVe
               rsReqId:(NSString*)rsReqId;

/**
 加入房间前提前设置回声抑制模式，配置 AVAudioSession catagory 和 options
 
 @param aecMode  要设置的回声抑制模式
 @return false：失败，true：成功
 */
- (bool)prepareTojoin:(AecMode)aecMode;

/**
 重设布局模式
 
 @param windows 使用 SDK 布局控制时将要使用的 UserWindows 数组
 @param onFinish 切换完成的回调，会在主线程被触发，APP 可用于最后调整布局
 */
- (void)changeLayoutType:(PILayoutType)layoutType
                 windows:(NSArray<PIUserWindow*>*)windows
                onFinish:(void (^)(void))onFinish;

/**
 获取当前分配给用户的 UserWindow 列表
 
 注意，获取到的是 SDK 内部状态的深拷贝，可以修改某个 UserWindow 的配置
 但必须调用 `- (void)resetUserWindows:(NSArray*)windows;` 才会生效
 
 @return 当前分配给用户的 UserWindow 数组
 */
- (NSArray*)getUsedUserWindows;

/**
 重设窗口布局
 
 @param windows 传入的 UserWindows 数组
 */
- (void)resetUserWindows:(NSArray<PIUserWindow*>*)windows;


/**
 开启本地录制
 本地录制不会推流
 
 @param fileName    录制的文件名称
 @param resolution  录制的分辨率
 @param bitrate     录制的码率  单位kb/s
 @param fps         录制的帧率
 @param size        录制的文件最大size，单位mb
 @param direction   录制的流的方向，0：horizontal，1：vertical
 @return 是否成功开启录制，true是成功，其它失败
 */
- (bool)recordLocally:(NSString*)fileName
       withResolution:(int)resolution
          withBitrate:(int)bitrate
              withFps:(int)fps
         withFilesize:(int)size
        withDirection:(int)direction;

/**
 停止本地录制
 */
- (void)stopRecordingLocally;

/**
 开始收流录制
 
 @param roomId  播放器用户所在房间号
 @param uid     播放器对应的用户uid
 @param path    录制的文件名称
 @return 是否成功开启，0是成功，其它失败
 */
- (bool)startRecordPlay2:(NSString*)roomId
                 withUid:(NSString*)uid
                withPath:(NSString*)path;

/**
 停止收流录制
 
 @return true：成功，false：失败
 */
- (bool)stopRecordPlay2:(NSString*)roomId withUid:(NSString*)uid;

/**
 开始推流录制
 会边推流边录制
 
 @param fileName    录制的文件名称
 @param resolution  录制的分辨率
 @param bitrate     录制的码率  单位kb/s
 @param fps         录制的帧率
 @param size        录制的文件最大size，单位mb
 @param direction   录制的流的方向，0：horizontal，1：vertical
 @return 是否成功开启录制，ttrue是成功，其它失败
 */
- (bool)startRecordPush:(NSString*)fileName
         withResolution:(int)resolution
            withBitrate:(int)bitrate
                withFps:(int)fps
           withFilesize:(int)size
          withDirection:(int)direction;

/**
 停止推流录制
 */
- (void)stopRecordPush;

/**
 每帧数据混音处理后，编码推流
 
 @param data 音频数据
 @param length 音频数据长度
 @param extraTs 需要额外打入的时间戳，例如歌词时间戳，单位：百纳秒
 */
- (void)encodeAudioData:(int16_t*)data
                 length:(int)length
                extraTs:(int64_t)extraTs;

/**
 获取所有的推流Id
 
 @return 流Id数组
 */
- (NSArray<NSNumber*>*)getPslIds;

/**
 获取状态信息
 目前支持获取推流延迟数据
 
 @param status_type  传STATUS_FUNCTION_TYPE_PZVT_DELAY返回延迟数据，其它返回nil
 @param params       自定义参数
 @return statusInfo 数组
 */
- (id)getStatusInfoWithStatusType:(int)status_type
                       withParams:(NSDictionary*)params;

/**
 回声抑制切换回调
 
 @param preCallback   回声抑制切换开始回调
 @param postCallback  回声抑制切换结束回调
 */
- (void)setAecSwitchPreCallback:(void (^)(bool))preCallback
                   postCallback:(void (^)(bool))postCallback;

/**
 获取指定用户的播放器
 
 @param roomId 房间号
 @param uid 用户 uid
 @return 播放器
 */
- (PIMoviePlayerController*)getPlayer2:(NSString*)roomId andUid:(NSString*)uid;

/**
 获取指定用户的播放器
 
 @param roomId 房间号
 @param uid 用户 id
 @param veName 视角名称
 @return 播放器
 */
- (PIMoviePlayerController*)getPlayer2:(NSString*)roomId
                                andUid:(NSString*)uid
                             andVeName:(NSString*)veName;

/**
 获取所有的播放器用户uid
 此接口目前不适用于多视角
 
 @return 播放器的用户Uid数组
 */
- (NSArray*)getAllPlayers;

/**
 获取所有的播放器用户uid,venName

 
 @return 播放器的用户id数组
 */
- (NSArray*)getAllPlayers2;

/**
 获取指定播放器的 url
 
 @param rid  播放器所在房间号
 @param uid  播放器对应的用户uid
 @param veName  播放器对应的视角名
 @return 播放器URL
 */
- (NSArray*)getPlayUrlWithRid:(NSString *)rid
                      withUid:(NSString *)uid
                   withVeName:(NSString *)veName;

/**
 获取房间内所有的播放器的URL
 
 返回值是NSDictionary 其中key是用户uid，value是NSDictionary，value对应的NSDictionary key是veName，veName若为null则是空字符串，value是播放器URL
 
 @param rid  房间号
 @return 播放器URL
 */
- (NSDictionary*)getAllPlayUrl:(NSString*)rid;

/**
 获取用户自己已加入的房间
 
 @return 房间号列表
 */
- (NSArray*)getJoinedRooms;

/**
 查看用户是否在推流
 
 @param roomId  房间号
 @param users   要查看的用户Uid
 @param callback  RS访问回调
 */
- (void)checkUsersStreamingWithRoomId:(NSString*)roomId
                            withUsers:(NSArray*)users
                         withCallback:(id<PIRsCallback>)callback;

/**
 在工作线程执行任务
 
 @param block  要执行的任务
 */
- (void)runOnWorkerThread:(void (^)(void))block;

/**
 PIMetronomeChannelConfigSpec 构造函数，用于节拍器
 
 @param ssrc 混音源的唯一标识，需要大于 0
 @param note 音符
 @param rate 频率
 @param beat_count 每小节拍数
 @param volume  节拍器音量，取值范围 [0, 100]
 @param streaming  混音源是否参与推流
 @param syncFix  否自动校正播放进度
 @param source  节拍器资源文件名
 @param beats   每拍的素材，值为其数据在 elementRhythm 里的一维下标
 */
- (PIMetronomeChannelConfigSpec*)createMetronomeConfigWithSsrc:(int)ssrc
                                                      withNote:(int)note
                                                      withRate:(int)rate
                                                 withBeatCount:(int)beat_count
                                                    withVolume:(int)volume
                                                 withStreaming:(BOOL)streaming
                                                   withSyncFix:(BOOL)syncFix
                                                    withSource:(NSArray*)source
                                                     withBeats:(NSArray*)beats;

/**
 获取预览视图

 @return 预览视图
 */
- (UIView*)getPreview;

/**
 设置预览 View
 
 @param externalPreview 预览视图
 @return 设置是否成功
 */
- (bool)setExternalPreview:(UIView*)externalPreview;

/**
 获取打点统计器

 @return 打点统计器
 */
- (PIStatistics*)getStatistics;

/**
 获取 Transcoder 状态
 */
- (NSArray*)getTranscoderStatus;


- (NSMutableDictionary*)capMapToDic:(id<JavaUtilMap>)caps;

- (BOOL)prepareTojoin:(PIiRoomRole)role
            andIsLink:(BOOL)isLink  // joining room ? true : false
         andAECStatus:(AecMode)aecStatus DEPRECATED_ATTRIBUTE;

- (void)joiniRoom:(NSArray*)rooms DEPRECATED_ATTRIBUTE;

- (void)joiniRoom:(int64_t)primaryRoom
        mergeRoom:(bool)mergeRoom
            rooms:(NSArray*)rooms DEPRECATED_ATTRIBUTE;

- (void)leaveiRoom:(NSArray*)rooms DEPRECATED_ATTRIBUTE;

- (void)leaveiRoom:(int64_t)oldPrimaryRoom
             split:(bool)split
             rooms:(NSArray *)rooms DEPRECATED_ATTRIBUTE;

- (PIMoviePlayerController*)getPlayer:(int64_t)roomId andUid:(NSString*)uid DEPRECATED_ATTRIBUTE;

- (PIMoviePlayerController*)getPlayer:(int64_t)roomId andUid:(NSString*)uid andVeName:(NSString*)veName DEPRECATED_ATTRIBUTE;

/**
 开始收流录制
 */
- (bool)startRecordPlay:(int64_t)roomId
                withUid:(NSString*)uid
               withPath:(NSString*)path DEPRECATED_ATTRIBUTE;

/**
 停止收流录制
 */
- (bool)stopRecordPlay:(int64_t)roomId withUid:(NSString*)uid DEPRECATED_ATTRIBUTE;

- (void)configureRoomConfig:(PIiRoomConifg*)roomConfig
           transcoderConfig:(INTERFACE_SET_PARAMS*)transcoderConfig
             roomViewConfig:(PIiRoomViewConfig*)viewConfig DEPRECATED_ATTRIBUTE;

- (void)configureRoomConfig:(PIiRoomConifg*)roomConfig
               previewParam:(INTERFACE_CAMERA_PARAMS*)previewParam
            processSetParam:(PIProcessSetParam*)processSetParam
             roomViewConfig:(PIiRoomViewConfig*)viewConfig DEPRECATED_ATTRIBUTE;

- (void)configureRoomConfig:(PIiRoomConifg*)roomConfig
           transcoderConfig:(INTERFACE_SET_PARAMS*)transcoderConfig
             roomViewConfig:(PIiRoomViewConfig*)viewConfig
                    preview:(UIView*)preview
         transcoderDelegate:(id<TranscoderDelegate>)transcoderDelegate DEPRECATED_ATTRIBUTE;

- (void)configureRoomConfig:(PIiRoomConifg*)roomConfig
               previewParam:(INTERFACE_CAMERA_PARAMS*)previewParam
            processSetParam:(PIProcessSetParam*)processSetParam
             roomViewConfig:(PIiRoomViewConfig*)viewConfig
                    preview:(UIView*)preview
         transcoderDelegate:(id<TranscoderDelegate>)transcoderDelegate DEPRECATED_ATTRIBUTE;
@end
