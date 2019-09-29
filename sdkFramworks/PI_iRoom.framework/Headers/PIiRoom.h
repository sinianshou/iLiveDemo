//
/*
 * Copyright (c) 2017 Powerinfo. All rights reserved.
 */
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <transcoder/libdatabase.h>

#import "PIiRoomShared.h"
#import "PIUserWindowUpdateListener.h"
#import "Statistics.h"
#import "PIiRoomMessage.h"
#import "RsCacheManager.h"
#import "CmdSpec.h"
#import "ChangeRefreshRequestSpec.h"
#import "ChangeRefreshResultSpec.h"
#import "LayoutController.h"

#define PI_iRoomVersion @"1.9.2.0-20190926-1900R"

typedef NS_ENUM(NSInteger, AecMode) {
    // 强制关闭 AEC，各种情况都不使用 AEC
    AEC_FORCE_OFF = PIiRoomShared_AEC_FORCE_OFF,
    // 又推又收时使用 AEC
    AEC_FORCE_ON = PIiRoomShared_AEC_FORCE_ON,
    // SDK 自动开关 AEC，又推又收且未戴耳机时使用 AEC，否则不使用 AEC
    AEC_AUTO = PIiRoomShared_AEC_AUTO,
    // 只推不收时，不使用 AEC，又推又收时，即使戴耳机也使用 AEC
    AEC_PREFER_ON = PIiRoomShared_AEC_PREFER_ON,
    // 推流时，不戴耳机时开 AEC，戴耳机时关闭 AEC
    AEC_EARPHONE = PIiRoomShared_AEC_EARPHONE,
};

typedef NS_ENUM(NSInteger, MixType) {
    // 节拍器
    MIX_TYPE_METRONOME = PIiRoomShared_MIX_TYPE_METRONOME,
    // 音乐
    MIX_TYPE_MUSIC = PIiRoomShared_MIX_TYPE_MUSIC,
    // 同步节拍器
    MIX_TYPE_SYNC_METRONOME = PIiRoomShared_MIX_TYPE_SYNC_METRONOME,
    // 同步音乐
    MIX_TYPE_SYNC_MUSIC = PIiRoomShared_MIX_TYPE_SYNC_MUSIC,
};

typedef NS_ENUM(NSInteger, StatusFunctionType) {
    // 用 pzvt 算出来的采集到播放的延迟
    STATUS_FUNCTION_TYPE_PZVT_DELAY = PIiRoomShared_STATUS_FUNCTION_TYPE_PZVT_DELAY,
};

typedef NS_ENUM(NSInteger, ConnectionType) {
    CONNECTION_UNKNOWN = PIiRoomShared_CONNECTION_UNKNOWN,
    CONNECTION_ETHERNET = PIiRoomShared_CONNECTION_ETHERNET,
    CONNECTION_WIFI = PIiRoomShared_CONNECTION_WIFI,
    CONNECTION_4G = PIiRoomShared_CONNECTION_4G,
    CONNECTION_3G = PIiRoomShared_CONNECTION_3G,
    CONNECTION_2G = PIiRoomShared_CONNECTION_2G,
    CONNECTION_UNKNOWN_CELLULAR = PIiRoomShared_CONNECTION_UNKNOWN_CELLULAR,
    CONNECTION_BLUETOOTH = PIiRoomShared_CONNECTION_BLUETOOTH,
    CONNECTION_NONE = PIiRoomShared_CONNECTION_NONE,
};

typedef NS_ENUM(NSInteger, ProtoMode) {
    PROTO_MODE_PSP = PIiRoomShared_PROTO_MODE_PSP,
    PROTO_MODE_PDP_PROXY = PIiRoomShared_PROTO_MODE_PDP_PROXY,
    PROTO_MODE_PDP_PURE = PIiRoomShared_PROTO_MODE_PDP_PURE,
};

typedef NS_ENUM(NSInteger, LeaveReason) {
    REASON_LEAVE_ROOM = PIiRoomShared_REASON_LEAVE_ROOM,    // 离开房间
    REASON_KICK_OUT = PIiRoomShared_REASON_KICK_OUT,        // 被踢出
    REASON_MAIN_VE_LEFT = PIiRoomShared_REASON_MAIN_VE_LEFT,    // 主视角离开
};

typedef NS_ENUM(NSInteger, StreamMode) {
    STREAM_MODE_NONE = PIiRoomShared_STREAM_MODE_NONE, // 不推/收任何流 1
    STREAM_MODE_ALL = PIiRoomShared_STREAM_MODE_ALL, // 推/收全部流 2
    STREAM_MODE_PARTIAL = PIiRoomShared_STREAM_MODE_PARTIAL, // 部分推收 3
    STREAM_MODE_ONLY_ONE = PIiRoomShared_STREAM_MODE_ONLY_ONE, // 收任意一个流 4
};

typedef NS_ENUM(NSInteger, PIiRoomRole) {
    ROLE_NORMAL = PIiRoomShared_ROLE_NORMAL,  //  参与者 2
    ROLE_VIEWER = PIiRoomShared_ROLE_VIEWER,  //  观众 3
    ROLE_FLEX = PIiRoomShared_ROLE_FLEX,      // 灵活的角色，不再受限于观众、参与者 4
};

typedef NS_ENUM(NSInteger, PlayStreamMode) {
    PLAY_STREAM_MODE_MULTI_STREAM = PIiRoomShared_PLAY_STREAM_MODE_MULTI_STREAM, // 1
    PLAY_STREAM_MODE_LOW_DELAY = PIiRoomShared_PLAY_STREAM_MODE_LOW_DELAY, // 2
    PLAY_STREAM_MODE_TRANS_SEG = PIiRoomShared_PLAY_STREAM_MODE_TRANS_SEG, // 3
    PLAY_STREAM_MODE_MSC = PIiRoomShared_PLAY_STREAM_MODE_MSC, // 4
    PLAY_STREAM_MODE_EXTERNAL_CDN = PIiRoomShared_PLAY_STREAM_MODE_EXTERNAL_CDN, // 5
};

typedef NS_ENUM(NSInteger, PIiRoomMessageType) {
    PEER_JOINED = PIiRoomMessage_PEER_JOINED, // 用户加入 54
    PEER_LEFT = PIiRoomMessage_PEER_LEFT, // 用户离开 56
    IROOM_DESTROYED = PIiRoomMessage_IROOM_DESTROYED, // 房间销毁 57
};

typedef NS_ENUM(NSInteger, PIiRoomError) {
    ERR_FEATURE_GROUP_CHAT =
        PIiRoomShared_ERR_FEATURE_GROUP_CHAT,  // 群聊（连麦）功能不支持 2000
    ERR_INVALID_MESSAGE = PIiRoomShared_ERR_INVALID_MESSAGE,  // 消息类型不存在 2004
    ERR_RS_CHANGE_ROLE =
        PIiRoomShared_ERR_RS_CHANGE_ROLE,  // 切换角色为参与者失败 2009
    ERR_HB_TIMEOUT = PIiRoomShared_ERR_HB_TIMEOUT,      // 心跳超时 2010
    ERR_PUSH_TIMEOUT = PIiRoomShared_ERR_PUSH_TIMEOUT,  // 推流超时 2011
    ERR_BACKGROUND_TIMEOUT =
        PIiRoomShared_ERR_BACKGROUND_TIMEOUT,  // 切换后台超时 2012
    // RS 返回（或者长连接收到）的收流数据不合法 2013
    ERR_INVALID_PLAY_TARGET = PIiRoomShared_ERR_INVALID_PLAY_TARGET,
    ERR_ALLOC_WINDOW_FAIL = PIiRoomShared_ERR_ALLOC_WINDOW_FAIL, // 绑定窗口为空

    ERR_TRANSCODER_FATAL = PIiRoomShared_ERR_TRANSCODER_FATAL,
    ERR_INVALID_LAYOUT_CONFIG = PIiRoomShared_ERR_INVALID_LAYOUT_CONFIG,
    ERR_MULTIPLE_PEER = PIiRoomShared_ERR_MULTIPLE_PEER,
    ERR_WRONG_NAME = PIiRoomShared_ERR_WRONG_NAME,
};

typedef NS_ENUM(NSInteger, StatisticsEvent) {
    START_JOIN = PIStatisticsInternal_START_JOIN,
    RS_REQUEST = PIStatisticsInternal_RS_REQUEST,
    RS_RESPONSE = PIStatisticsInternal_RS_RESPONSE,
    PUSH_SUCCESS = PIStatisticsInternal_PUSH_SUCCESS,
    FIRST_RECEIVE_SUCCESS = PIStatisticsInternal_FIRST_RECEIVE_SUCCESS,
    SIG_CONN_START = PIStatisticsInternal_SIG_CONN_START,
    SIG_CONN_SUCCESS = PIStatisticsInternal_SIG_CONN_SUCCESS
};

// rs_result
typedef NS_ENUM(NSInteger, PIRSResult) {
    RS_RESULT_SUCCESS = PIiRoomShared_RS_RESULT_SUCCESS, // 成功 0
    RS_RESULT_ERROR_INVALID_ROOM_ID = PIiRoomShared_RS_RESULT_ERROR_INVALID_ROOM_ID, // 无效的房间ID 1001
    RS_RESULT_ERROR_INVALID_UID = PIiRoomShared_RS_RESULT_ERROR_INVALID_UID, // 无效的UID 1002
    RS_RESULT_ERROR_OPERATION_NOT_ALLOWED =  PIiRoomShared_RS_RESULT_ERROR_OPERATION_NOT_ALLOWED, // 不允许此操作 1009
    RS_RESULT_ERROR_OPERATION_FAIL = PIiRoomShared_RS_RESULT_ERROR_OPERATION_FAIL, // 操作失败 1010

    RS_RESULT_ERROR_JOIN_NOT_EXIST_ROOM = PIiRoomShared_RS_RESULT_ERROR_JOIN_NOT_EXIST_ROOM, // （观众）加入不存在的房间 1101
    RS_RESULT_ERROR_LEAVE_NOT_EXIST_ROOM = PIiRoomShared_RS_RESULT_ERROR_LEAVE_NOT_EXIST_ROOM, // 离开不存在的房间 1102
    RS_RESULT_ERROR_LEAVE_NOT_JOINED_ROOM = PIiRoomShared_RS_RESULT_ERROR_LEAVE_NOT_JOINED_ROOM, // 离开自己没有加入的房间 1103
    RS_RESULT_ERROR_JOIN_FULL_ROOMS = PIiRoomShared_RS_RESULT_ERROR_JOIN_FULL_ROOMS, // 加入的房间人数已达上限 1104
    RS_RESULT_ERROR_LEAVE_ORIGIN_ALLOC_NEW_FAIL = PIiRoomShared_RS_RESULT_ERROR_LEAVE_ORIGIN_ALLOC_NEW_FAIL, // leave origin alloc new 时，无法 alloc 1105
    RS_RESULT_ERROR_INTERNAL_DATA_INCONSISTENT = PIiRoomShared_RS_RESULT_ERROR_INTERNAL_DATA_INCONSISTENT, // 数据发生不一致，比如用户的房间列表有这个房间，但房间内没有这个用户的信息 1106

    ERR_RS_API_TIMEOUT = PIiRoomShared_ERR_RS_API_TIMEOUT, // RS 访问超时 10000
    ERR_RS_UNKNOWN = PIiRoomShared_ERR_RS_UNKNOWN, // RS 未知错误 10001
};

typedef NS_ENUM(NSInteger, PIUserWindowError) {
    // 窗口索引重复错误 2018
    ERR_WINDOW_DUPLICATE_ZINDEX = PIiRoomShared_ERR_WINDOW_DUPLICATE_ZINDEX,
    // 多个全屏窗口错误 2019
    ERR_MULTIPLE_FULLSCREEN_WINDOW = PIiRoomShared_ERR_MULTIPLE_FULLSCREEN_WINDOW,
    // 全屏窗口索引不为 0 错误 2020
    ERR_FULLSCREEN_WINDOW_WITH_WRONG_ZINDEX = PIiRoomShared_ERR_FULLSCREEN_WINDOW_WITH_WRONG_ZINDEX,
    // 窗口与控件不匹配错误 2021
    ERR_USERWINDOW_AND_VIEW_MISMATCH = PIiRoomShared_ERR_USERWINDOW_AND_VIEW_MISMATCH,
};

// leave_origin_behavior
typedef NS_ENUM(NSInteger, PILeaveOriginBehavior) {
    LEAVE_ORIGIN_BEHAVIOR_LEAVE_ALL = PIiRoomShared_LEAVE_ORIGIN_BEHAVIOR_LEAVE_ALL, // 离开 origin room 则离开所有房间
    LEAVE_ORIGIN_BEHAVIOR_ALLOC_NEW_SLOT = PIiRoomShared_LEAVE_ORIGIN_BEHAVIOR_ALLOC_NEW_SLOT // 离开 origin room 后在指定房间新分配 slot，从 alloc_slot_room_id 指定的 room 中分配槽位
};

// transcoder mode
typedef NS_ENUM(NSInteger, PITranscoderMode) {
    // 普通模式，SDK 采集音视频，SDK 编码推流
    MODE_NORMAL = 1,
    // 仅视频模式，SDK 采集视频，APP 采集音频，SDK 编码推流（例如 APP 录音的混音模式）
    MODE_VIDEO_ONLY = 2,
    // 纯音频仅编码模式，APP 采集音频，SDK 编码推流（例如 APP 录音混音的纯音频推流模式）
    MODE_A_ENCODE_ONLY = 4,
    // SDK 负责音频编码、传输，视频传输；APP 负责音频采集，视频采集、预览、编码
    MODE_A_ENCODE_V_SEND = 5,
    // 音视频仅编码模式，APP 采集音视频、预览视频，SDK 编码推流，其中视频数据用 Surface 传入
    MODE_AV_ENCODE_ONLY_TEX = 6,
    // 音视频仅编码模式，APP 采集音视频、预览视频，SDK 编码推流，其中视频数据传 YUV
    MODE_AV_ENCODE_ONLY_YUV = 7,
    // 纯音频模式，SDK 仅对音频进行采集、编码、推流处理，不涉及视频相关内容
    MODE_AUDIO_ONLY = 8,
};

// 后台行为
typedef NS_ENUM(NSInteger, BackgroundBehavior) {
    STOP_ACTION_STOP_STREAMING = 0,
    STOP_ACTION_KEEP_AUDIO = 1
};

// partial 推收流过滤模式
typedef NS_ENUM(NSInteger, TargetsFilterMode) {
    // 指定的 targets 是要推收的，默认模式
    TARGET_FILTER_MODE_ACCEPT = PIiRoomShared_TARGETS_FILTER_MODE_ACCEPT,
    // 指定的 targets 是不要推收的，非指定的都推收
    TARGETS_FILTER_MODE_REJECT = PIiRoomShared_TARGETS_FILTER_MODE_REJECT
};

typedef NS_ENUM(NSInteger, SDKPlayMode) {
    // SDK 播放音视频
    SDK_PLAY_BOTH = PIiRoomShared_SDK_PLAY_BOTH,
    // SDK 只播放视频
    SDK_PLAY_VIDEO_ONLY = PIiRoomShared_SDK_PLAY_VIDEO_ONLY,
    // SDK 只播放音频
    SDK_PLAY_AUDIO_ONLY = PIiRoomShared_SDK_PLAY_AUDIO_ONLY,
    // SDK 都不播放
    SDK_PLAY_NONE = PIiRoomShared_SDK_PLAY_NONE,
};

typedef NS_ENUM(NSInteger, ScenePlayType) {
    SCENE_PLAY_TYPE_NONE_ONE = PIiRoomShared_SCENE_PLAY_TYPE_NONE_ONE, // 不收自己的子视角，收其他用户的一个视角
    SCENE_PLAY_TYPE_NONE_ALL = PIiRoomShared_SCENE_PLAY_TYPE_NONE_ALL, // 不收自己的子视角，收其他用户所有视角
    SCENE_PLAY_TYPE_ONE_ONE = PIiRoomShared_SCENE_PLAY_TYPE_ONE_ONE,   // 收自己的一个子视角，收其他用户的一个视角
    SCENE_PLAY_TYPE_ONE_ALL = PIiRoomShared_SCENE_PLAY_TYPE_ONE_ALL,   // 收自己的一个子视角，收其他用户所有视角
    SCENE_PLAY_TYPE_ALL_ONE = PIiRoomShared_SCENE_PLAY_TYPE_ALL_ONE,   // 收自己的所有子视角，收其他用户的一个视角
    SCENE_PLAY_TYPE_ALL_ALL = PIiRoomShared_SCENE_PLAY_TYPE_ALL_ALL     // 收自己的所有子视角，收其他用户所有视角
};

typedef NS_ENUM(NSInteger, AxMode) {
    AX_A200 = PIiRoomShared_AX_A200,
    AX_ADL_BASE = PIiRoomShared_AX_ADL_BASE,
    AX_A50_BASE = PIiRoomShared_AX_A50_BASE,
    AX_A40_BASE = PIiRoomShared_AX_A40_BASE,
};

typedef NS_ENUM(NSInteger, A50State) {
    A50_STATE_DISABLE = PIiRoomShared_A50_STATE_DISABLE,
    A50_STATE_A1 = PIiRoomShared_A50_STATE_A1,
    A50_STATE_A2 = PIiRoomShared_A50_STATE_A2,
    A50_STATE_A3 = PIiRoomShared_A50_STATE_A3,
    A50_STATE_A4 = PIiRoomShared_A50_STATE_A4,
};

typedef NS_ENUM(NSInteger, PILayoutType) {
    PI_LAYOUT_TYPE_APP = PIiRoomShared_LAYOUT_TYPE_APP,
    PI_LAYOUT_TYPE_SDK = PIiRoomShared_LAYOUT_TYPE_SDK,
};

typedef NS_ENUM(NSInteger, PINetworkDeviceType) {
    PI_NETWORK_DEVICE_MOBILE =
        PIiRoomShared_NETWORK_DEVICE_MOBILE,  // 移动蜂窝网络设备
    PI_NETWORK_DEVICE_WIFI =
        PIiRoomShared_NETWORK_DEVICE_WIFI,  // WiFi 网络设备
};

typedef NS_ENUM(NSInteger, PISigMode) {
    PI_APP_SIG = PIiRoomShared_APP_SIG,
    PI_SDK_SIG = PIiRoomShared_SDK_SIG,
    PI_MIX_SIG = PIiRoomShared_MIX_SIG,
};

typedef NS_ENUM(NSInteger, MixError) {
    ERR_MIX_PZVT_ERROR_INITIATIVE = PIiRoomShared_ERR_MIX_PZVT_ERROR_INITIATIVE,
    ERR_MIX_PZVT_ERROR_PASSIVITY = PIiRoomShared_ERR_MIX_PZVT_ERROR_PASSIVITY,
    ERR_MIX_START_RS_ERROR = PIiRoomShared_ERR_MIX_START_RS_ERROR,
    ERR_MIX_STOP_RS_ERROR = PIiRoomShared_ERR_MIX_STOP_RS_ERROR,
};

// 访问 RoomServer 默认超时时间
#define DEFAULT_RS_TIMEOUT_THRESHOLD PIiRoomShared_DEFAULT_RS_TIMEOUT_THRESHOLD

@interface PIiRoomConifg : PIiRoomShared_Config

+ (instancetype)createConfig;

- (instancetype)init NS_UNAVAILABLE;

@property PS_AudioCaptureMode audioCaptureMode;
@property PS_AudioEncodeMode audioEncodeMode;
@property PS_VideoCaptureMode videoCaptureMode;
@property PS_VideoEncodeMode videoEncodeMode;

@end

@interface PIiRoomViewConfig : NSObject

@property PILayoutType layoutType;

@property UIView* context;
@property id<PIUserWindowUpdateListener> __weak userWindowUpdateListener;
@property NSArray* windows;

@property id<PILayoutController> __weak layoutController;

@property bool draggable;

@end

@interface PIiRoom : PIiRoomShared
+ (int)initialize:(NSString*)groupId
      andNdSelect:(int)ndSelect
        andRSPort:(int)rsPort
       andPISPort:(int)pisPort;

+ (int)initialize:(NSString*)appKey
andRSTimeoutThreshold:(int)rsTimeoutThreshold
           andLogPath:(NSString*)logPath;

+ (int)initialize:(NSString*)groupId
               andNdSelect:(int)ndSelect
                 andRSPort:(int)rsPort
                andPISPort:(int)pisPort
                 andDomain:(NSString*)domain
     andRSTimeoutThreshold:(int)rsTimeoutThreshold;

+ (int)initialize:(NSString*)groupId
               andNdSelect:(int)ndSelect
                 andRSPort:(int)rsPort
                andPISPort:(int)pisPort
                 andDomain:(NSString*)domain
     andRSTimeoutThreshold:(int)rsTimeoutThreshold
                andLogPath:(NSString*)logPath;

+ (void)setGroupId:(NSString*)groupId;
+ (void)setRSTimeout:(int)timeoutThreshold;
+ (void)setRsPostMaxTimes:(int)rsPostMaxTimes;

+ (PIRsCacheManager*)rsCacheManager;
+ (void)setRsCacheTTL:(int64_t)ttl;
+ (void)setRsCacheCapacity:(int32_t)bytes;

+ (void)preloadWithNdSelect:(int)ndSelect
                    groupId:(NSString*)groupId
                    request:(PIChangeRefreshRequestSpec*)request
                     result:(PIChangeRefreshResultSpec*)result
                skipOnExist:(bool)skipOnExist;

+ (void)preloadWithNdSelect:(int)ndSelect
                    groupId:(NSString*)groupId
                        uid:(NSString*)uid
                       cmds:(NSArray<PICmdSpec*>*)cmds;

/**
 * 获取网络设备是否可用
 *
 * @param deviceType PI_NETWORK_DEVICE_MOBILE 或 PI_NETWORK_DEVICE_WIFI
 * @return true 表示可用，false 表示不可用
 */
+ (bool)getNetworkDeviceAvailable:(PINetworkDeviceType)deviceType;

@end
