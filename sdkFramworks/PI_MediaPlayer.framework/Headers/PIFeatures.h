/*
 * PIOptions.h
 *
 * Copyright (c) 2018 Bai Shuai <baishuai.io@gmail.com>
 */

#import <Foundation/Foundation.h>


typedef NS_ENUM(NSInteger, PIFeature) {
    PI_FID_MIN_GUARD = 0,
    
    /**
     * only support set value before prepare
     */
    PI_FID_BEFORE_PREPARE_START_GUARD = 1,
    PI_FID_PS_AUDIO_TIME_STRETCH,
    PI_FID_PS_DECODER_A50,
    PI_FID_PS_DECODER_A50_DETAIL_LOG,
    PI_FID_PS_COMFORT_NOISE,
    PI_FID_PS_DETECT_CREATOR_NETWORK,
    PI_FID_PS_ANDROID_NEW_AEC,
    PI_FID_PS_AUDIO_FILLER,
    PI_FID_PS_FREEZE_JUMP,
    PI_FID_PS_SHOW_BLACK_IF_NO_VIDEO,
    PI_FID_PS_AUTO_HDECODE,
    PI_FID_PS_CUSTOM_MSG,
    PI_FID_BEFORE_PREPARE_END_GUARD,
    
    /**
     * support disable during playing, but not support enable
     */
    PI_FID_CAN_DISABLE_AFTER_PREPARE_START_GUARD = 201,
    PI_FID_PS_UPLOAD_PULL_STATUS,
    PI_FID_CAN_DISABLE_AFTER_PREPARE_END_GUARD,
    
    
    /**
     * support set value during the whole life circle
     */
    PI_FID_CAN_SET_WHOLE_LIFE_START_GUARD = 401,
    PI_FID_PS_MSC_DETECT_SPEAKER_AND_VOLUME,
    PI_FID_PS_DISPLAY_AUTO_FLIP,
    PI_FID_CAN_SET_WHOLE_LIFE_END_GUARD,
    
    PI_FID_MAX_GUARD = 599,
};
