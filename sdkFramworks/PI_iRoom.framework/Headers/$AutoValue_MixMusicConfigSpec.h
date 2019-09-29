//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: jar:file:libs/XiRoom-sources.jar!com/powerinfo/pi_iroom/data/$AutoValue_MixMusicConfigSpec.java
//

#include "J2ObjC_header.h"

#pragma push_macro("INCLUDE_ALL_$AutoValue_MixMusicConfigSpec")
#ifdef RESTRICT_$AutoValue_MixMusicConfigSpec
#define INCLUDE_ALL_$AutoValue_MixMusicConfigSpec 0
#else
#define INCLUDE_ALL_$AutoValue_MixMusicConfigSpec 1
#endif
#undef RESTRICT_$AutoValue_MixMusicConfigSpec

#if !defined (PI_AutoValue_MixMusicConfigSpec_) && (INCLUDE_ALL_$AutoValue_MixMusicConfigSpec || defined(INCLUDE_PI_AutoValue_MixMusicConfigSpec))
#define PI_AutoValue_MixMusicConfigSpec_

#define RESTRICT_MixMusicConfigSpec 1
#define INCLUDE_PIMixMusicConfigSpec 1
#include "MixMusicConfigSpec.h"

@interface PI_AutoValue_MixMusicConfigSpec : PIMixMusicConfigSpec

#pragma mark Public

- (jboolean)isEqual:(id)o;

- (NSUInteger)hash;

- (jboolean)music_sync_fix;

- (jlong)pzvt;

- (jboolean)remix;

- (NSString *)source;

- (jint)ssrc;

- (jboolean)streaming;

- (NSString *)description;

- (jint)volume;

#pragma mark Package-Private

- (instancetype)initWithInt:(jint)ssrc
                   withLong:(jlong)pzvt
                    withInt:(jint)volume
                withBoolean:(jboolean)streaming
                withBoolean:(jboolean)remix
                withBoolean:(jboolean)music_sync_fix
               withNSString:(NSString *)source;

@end

J2OBJC_EMPTY_STATIC_INIT(PI_AutoValue_MixMusicConfigSpec)

FOUNDATION_EXPORT void PI_AutoValue_MixMusicConfigSpec_initWithInt_withLong_withInt_withBoolean_withBoolean_withBoolean_withNSString_(PI_AutoValue_MixMusicConfigSpec *self, jint ssrc, jlong pzvt, jint volume, jboolean streaming, jboolean remix, jboolean music_sync_fix, NSString *source);

J2OBJC_TYPE_LITERAL_HEADER(PI_AutoValue_MixMusicConfigSpec)

@compatibility_alias ComPowerinfoPi_iroomData$AutoValue_MixMusicConfigSpec PI_AutoValue_MixMusicConfigSpec;

#endif

#pragma pop_macro("INCLUDE_ALL_$AutoValue_MixMusicConfigSpec")