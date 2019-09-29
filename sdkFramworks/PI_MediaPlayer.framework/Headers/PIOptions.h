/*
 * PIOptions.h
 */

#import <Foundation/Foundation.h>
#import "PIFeatures.h"
#import "PIPrefix.h"

/*!
 @brief set arrc params for each options
 @code [ffoptions setPlayerOptionValue:@"helloworld" forKey:PS_OPT_ARRC_PARAM];
 */
PI_EXTERN NSString * const PS_OPT_ARRC_PARAM;
PI_EXTERN NSString * const PS_OPTK_PRE_INIT_TYPE;
PI_EXTERN NSString * const PS_OPTK_PRE_INIT_BEHAVIOR_TICK;
PI_EXTERN NSString * const PS_OPTK_PRE_INIT_CONNCTION_TICK;
PI_EXTERN NSString * const PS_OPTK_PRE_INIT_ALLOCPLAYER_TICK;

PI_EXTERN NSString * const PS_IGNORE_AUDIO_INTERRUPT;

typedef NS_ENUM(NSInteger, PIOverlayFormat) {
    PI_OVERLAY_FMT_BGRA32 = 0x41524742,
    PI_OVERLAY_FMT_I420   = 0x30323449
};

typedef enum PIOptionCategory {
    kPIOptionCategoryFormat = 1,
    kPIOptionCategoryCodec  = 2,
    kPIOptionCategorySws    = 3,
    kPIOptionCategoryPlayer = 4,
    kPIOptionCategorySwr    = 5,
    kPIOptionCategoryPsp    = 6,
} PIOptionCategory;

// for codec option 'skip_loop_filter' and 'skip_frame'
typedef enum PIAVDiscard {
    /* We leave some space between them for extensions (drop some
     * keyframes for intra-only or drop just some bidir frames). */
    PI_AVDISCARD_NONE    =-16, ///< discard nothing
    PI_AVDISCARD_DEFAULT =  0, ///< discard useless packets like 0 size packets in avi
    PI_AVDISCARD_NONREF  =  8, ///< discard all non reference
    PI_AVDISCARD_BIDIR   = 16, ///< discard all bidirectional frames
    PI_AVDISCARD_NONKEY  = 32, ///< discard all frames except keyframes
    PI_AVDISCARD_ALL     = 48, ///< discard all
} PIAVDiscard;


PI_EXTERN @interface PIOptions : NSObject

+(PIOptions *)optionsByDefault;


/**
 Apply all the option values into the mediaPlayer.
 Only succeed if the state of mediaPlayer is IDLE
 
 @param mediaPlayer not null, before call prepared
 TODO baishuai hide IjkMediaPlayer
 */

- (void)setOptionValue:(NSString *)value
                forKey:(NSString *)key
            ofCategory:(PIOptionCategory)category;

- (void)setOptionIntValue:(int64_t)value
                   forKey:(NSString *)key
               ofCategory:(PIOptionCategory)category;

/**
 Set option about ffmpeg libformat
 
 @param value the option value in libformat
 @param key the option key in libforamt
 */
-(void)setFormatOptionValue:       (NSString *)value forKey:(NSString *)key;
-(void)setCodecOptionValue:        (NSString *)value forKey:(NSString *)key;
-(void)setSwsOptionValue:          (NSString *)value forKey:(NSString *)key;
-(void)setPlayerOptionValue:       (NSString *)value forKey:(NSString *)key;
-(void)setSwrOptionValue:          (NSString *)value forKay:(NSString *)key;

-(void)setFormatOptionIntValue:    (int64_t)value forKey:(NSString *)key;
-(void)setCodecOptionIntValue:     (int64_t)value forKey:(NSString *)key;
-(void)setSwsOptionIntValue:       (int64_t)value forKey:(NSString *)key;
-(void)setPlayerOptionIntValue:    (int64_t)value forKey:(NSString *)key;
-(void)setSwrOptionIntValue:       (int64_t)value forKey:(NSString *)key;

-(int64_t)getPlayerOptionIntValue:(NSString *)key;

-(void)enableFeature:              (PIFeature)feature;
-(void)disableFeature:             (PIFeature)feature;

@property(nonatomic) BOOL showHudView;

@end
