//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: jar:file:libs/XiRoom-sources.jar!com/powerinfo/pi_iroom/data/AutoValue_PushTargetConfigSpec.java
//

#include "J2ObjC_header.h"

#pragma push_macro("INCLUDE_ALL_AutoValue_PushTargetConfigSpec")
#ifdef RESTRICT_AutoValue_PushTargetConfigSpec
#define INCLUDE_ALL_AutoValue_PushTargetConfigSpec 0
#else
#define INCLUDE_ALL_AutoValue_PushTargetConfigSpec 1
#endif
#undef RESTRICT_AutoValue_PushTargetConfigSpec

#if !defined (PIAutoValue_PushTargetConfigSpec_) && (INCLUDE_ALL_AutoValue_PushTargetConfigSpec || defined(INCLUDE_PIAutoValue_PushTargetConfigSpec))
#define PIAutoValue_PushTargetConfigSpec_

#define RESTRICT_$AutoValue_PushTargetConfigSpec 1
#define INCLUDE_PI_AutoValue_PushTargetConfigSpec 1
#include "$AutoValue_PushTargetConfigSpec.h"

@interface PIAutoValue_PushTargetConfigSpec : PI_AutoValue_PushTargetConfigSpec

#pragma mark Package-Private

- (instancetype)initWithInt:(jint)tcs_mode
                    withInt:(jint)preview_width
                    withInt:(jint)preview_height
                    withInt:(jint)fps
                    withInt:(jint)min_fps
                    withInt:(jint)width
                    withInt:(jint)height
                    withInt:(jint)bitrate
                    withInt:(jint)max_br
                    withInt:(jint)min_br
                    withInt:(jint)video_codec;

@end

J2OBJC_EMPTY_STATIC_INIT(PIAutoValue_PushTargetConfigSpec)

FOUNDATION_EXPORT void PIAutoValue_PushTargetConfigSpec_initWithInt_withInt_withInt_withInt_withInt_withInt_withInt_withInt_withInt_withInt_withInt_(PIAutoValue_PushTargetConfigSpec *self, jint tcs_mode, jint preview_width, jint preview_height, jint fps, jint min_fps, jint width, jint height, jint bitrate, jint max_br, jint min_br, jint video_codec);

FOUNDATION_EXPORT PIAutoValue_PushTargetConfigSpec *new_PIAutoValue_PushTargetConfigSpec_initWithInt_withInt_withInt_withInt_withInt_withInt_withInt_withInt_withInt_withInt_withInt_(jint tcs_mode, jint preview_width, jint preview_height, jint fps, jint min_fps, jint width, jint height, jint bitrate, jint max_br, jint min_br, jint video_codec) NS_RETURNS_RETAINED;

FOUNDATION_EXPORT PIAutoValue_PushTargetConfigSpec *create_PIAutoValue_PushTargetConfigSpec_initWithInt_withInt_withInt_withInt_withInt_withInt_withInt_withInt_withInt_withInt_withInt_(jint tcs_mode, jint preview_width, jint preview_height, jint fps, jint min_fps, jint width, jint height, jint bitrate, jint max_br, jint min_br, jint video_codec);

J2OBJC_TYPE_LITERAL_HEADER(PIAutoValue_PushTargetConfigSpec)

@compatibility_alias ComPowerinfoPi_iroomDataAutoValue_PushTargetConfigSpec PIAutoValue_PushTargetConfigSpec;

#endif

#if !defined (PIAutoValue_PushTargetConfigSpec_GsonTypeAdapter_) && (INCLUDE_ALL_AutoValue_PushTargetConfigSpec || defined(INCLUDE_PIAutoValue_PushTargetConfigSpec_GsonTypeAdapter))
#define PIAutoValue_PushTargetConfigSpec_GsonTypeAdapter_

#define RESTRICT_TypeAdapter 1
#define INCLUDE_ComGoogleGsonTypeAdapter 1
#include "TypeAdapter.h"

@class ComGoogleGsonGson;
@class ComGoogleGsonJsonElement;
@class ComGoogleGsonStreamJsonReader;
@class ComGoogleGsonStreamJsonWriter;
@class JavaIoReader;
@class PIPushTargetConfigSpec;

@interface PIAutoValue_PushTargetConfigSpec_GsonTypeAdapter : ComGoogleGsonTypeAdapter

#pragma mark Public

- (instancetype)initWithComGoogleGsonGson:(ComGoogleGsonGson *)gson;

- (PIPushTargetConfigSpec *)fromJsonTreeWithComGoogleGsonJsonElement:(ComGoogleGsonJsonElement *)arg0;

- (PIPushTargetConfigSpec *)fromJsonWithJavaIoReader:(JavaIoReader *)arg0;

- (PIPushTargetConfigSpec *)fromJsonWithNSString:(NSString *)arg0;

- (PIPushTargetConfigSpec *)readWithComGoogleGsonStreamJsonReader:(ComGoogleGsonStreamJsonReader *)jsonReader;

- (void)writeWithComGoogleGsonStreamJsonWriter:(ComGoogleGsonStreamJsonWriter *)jsonWriter
                                        withId:(PIPushTargetConfigSpec *)object;

// Disallowed inherited constructors, do not use.

- (instancetype)init NS_UNAVAILABLE;

@end

J2OBJC_EMPTY_STATIC_INIT(PIAutoValue_PushTargetConfigSpec_GsonTypeAdapter)

FOUNDATION_EXPORT void PIAutoValue_PushTargetConfigSpec_GsonTypeAdapter_initWithComGoogleGsonGson_(PIAutoValue_PushTargetConfigSpec_GsonTypeAdapter *self, ComGoogleGsonGson *gson);

FOUNDATION_EXPORT PIAutoValue_PushTargetConfigSpec_GsonTypeAdapter *new_PIAutoValue_PushTargetConfigSpec_GsonTypeAdapter_initWithComGoogleGsonGson_(ComGoogleGsonGson *gson) NS_RETURNS_RETAINED;

FOUNDATION_EXPORT PIAutoValue_PushTargetConfigSpec_GsonTypeAdapter *create_PIAutoValue_PushTargetConfigSpec_GsonTypeAdapter_initWithComGoogleGsonGson_(ComGoogleGsonGson *gson);

J2OBJC_TYPE_LITERAL_HEADER(PIAutoValue_PushTargetConfigSpec_GsonTypeAdapter)

#endif

#pragma pop_macro("INCLUDE_ALL_AutoValue_PushTargetConfigSpec")