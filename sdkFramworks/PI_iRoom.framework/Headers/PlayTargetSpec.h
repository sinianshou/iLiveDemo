//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: jar:file:libs/XiRoom-sources.jar!com/powerinfo/pi_iroom/data/PlayTargetSpec.java
//

#include "J2ObjC_header.h"

#pragma push_macro("INCLUDE_ALL_PlayTargetSpec")
#ifdef RESTRICT_PlayTargetSpec
#define INCLUDE_ALL_PlayTargetSpec 0
#else
#define INCLUDE_ALL_PlayTargetSpec 1
#endif
#undef RESTRICT_PlayTargetSpec

#if __has_feature(nullability)
#pragma clang diagnostic push
#pragma GCC diagnostic ignored "-Wnullability-completeness"
#endif

#if !defined (PIPlayTargetSpec_) && (INCLUDE_ALL_PlayTargetSpec || defined(INCLUDE_PIPlayTargetSpec))
#define PIPlayTargetSpec_

@class ComGoogleGsonGson;
@class ComGoogleGsonTypeAdapter;
@class JavaLangInteger;
@class JavaLangLong;
@class PIPlayTargetSpec_Builder;
@protocol JavaUtilList;

@interface PIPlayTargetSpec : NSObject

#pragma mark Public

- (instancetype)init;

- (NSString *)br_name;

+ (PIPlayTargetSpec_Builder *)builder;

- (jint)diffnum;

- (NSString *)enc_pzb_data;

- (NSString *)enc_url;

- (jboolean)force_start;

- (NSString *)from_uid;

- (NSString *)getKeySafely;

- (NSString *)getSrid;

+ (jboolean)isValidWithPIPlayTargetSpec:(PIPlayTargetSpec *)target
                           withNSString:(NSString *)selfUid;

+ (jboolean)isValidAfterRefinedWithPIPlayTargetSpec:(PIPlayTargetSpec *)target
                                       withNSString:(NSString *)selfUid;

- (NSString *)key;

- (NSString *)link_extra_params;

- (NSString *)link_pzb_data;

- (NSString *)link_url;

- (jint)mode;

- (jboolean)noNeedUpdateToWithPIPlayTargetSpec:(PIPlayTargetSpec *)that;

- (jint)play_stream_mode;

- (jint)push_tcs_mode;

- (id<JavaUtilList>)pzb_data;

- (jint)render_mode;

- (NSString *)render_mode_param;

- (jlong)rid;

- (jint)sid;

- (jint)slot;

- (NSString *)srid;

- (JavaLangLong *)stream_group;

- (jlong)streamGroupSafely;

- (NSString *)to_uid;

- (PIPlayTargetSpec_Builder *)toBuilder;

+ (ComGoogleGsonTypeAdapter *)typeAdapterWithComGoogleGsonGson:(ComGoogleGsonGson *)gson;

- (id<JavaUtilList>)url;

- (NSString *)ve_name;

- (JavaLangInteger *)ve_slot;

- (jint)veSlotSafely;

- (PIPlayTargetSpec *)withVe_nameWithNSString:(NSString *)ve_name;

@end

J2OBJC_EMPTY_STATIC_INIT(PIPlayTargetSpec)

inline NSString *PIPlayTargetSpec_get_KEY_SEPARATOR(void);
/*! INTERNAL ONLY - Use accessor function from above. */
FOUNDATION_EXPORT NSString *PIPlayTargetSpec_KEY_SEPARATOR;
J2OBJC_STATIC_FIELD_OBJ_FINAL(PIPlayTargetSpec, KEY_SEPARATOR, NSString *)

inline NSString *PIPlayTargetSpec_get_KEY_SPLIT_SEPARATOR(void);
/*! INTERNAL ONLY - Use accessor function from above. */
FOUNDATION_EXPORT NSString *PIPlayTargetSpec_KEY_SPLIT_SEPARATOR;
J2OBJC_STATIC_FIELD_OBJ_FINAL(PIPlayTargetSpec, KEY_SPLIT_SEPARATOR, NSString *)

inline jint PIPlayTargetSpec_get_VE_POSITION_IN_KEY(void);
#define PIPlayTargetSpec_VE_POSITION_IN_KEY 6
J2OBJC_STATIC_FIELD_CONSTANT(PIPlayTargetSpec, VE_POSITION_IN_KEY, jint)

FOUNDATION_EXPORT void PIPlayTargetSpec_init(PIPlayTargetSpec *self);

FOUNDATION_EXPORT ComGoogleGsonTypeAdapter *PIPlayTargetSpec_typeAdapterWithComGoogleGsonGson_(ComGoogleGsonGson *gson);

FOUNDATION_EXPORT jboolean PIPlayTargetSpec_isValidWithPIPlayTargetSpec_withNSString_(PIPlayTargetSpec *target, NSString *selfUid);

FOUNDATION_EXPORT jboolean PIPlayTargetSpec_isValidAfterRefinedWithPIPlayTargetSpec_withNSString_(PIPlayTargetSpec *target, NSString *selfUid);

FOUNDATION_EXPORT PIPlayTargetSpec_Builder *PIPlayTargetSpec_builder(void);

J2OBJC_TYPE_LITERAL_HEADER(PIPlayTargetSpec)

@compatibility_alias ComPowerinfoPi_iroomDataPlayTargetSpec PIPlayTargetSpec;

#endif

#if !defined (PIPlayTargetSpec_Builder_) && (INCLUDE_ALL_PlayTargetSpec || defined(INCLUDE_PIPlayTargetSpec_Builder))
#define PIPlayTargetSpec_Builder_

@class JavaLangInteger;
@class JavaLangLong;
@class PIPlayTargetSpec;
@protocol JavaUtilList;

@interface PIPlayTargetSpec_Builder : NSObject

#pragma mark Public

- (instancetype)init;

- (PIPlayTargetSpec_Builder *)br_name:(NSString *)br_name;

- (PIPlayTargetSpec *)build;

- (PIPlayTargetSpec_Builder *)diffnum:(jint)diffnum;

- (PIPlayTargetSpec_Builder *)enc_pzb_dataWithNSString:(NSString *)enc_pzb_data;

- (PIPlayTargetSpec_Builder *)enc_urlWithNSString:(NSString *)enc_url;

- (PIPlayTargetSpec_Builder *)force_start:(jboolean)force_start;

- (PIPlayTargetSpec_Builder *)from_uid:(NSString *)from_uid;

- (PIPlayTargetSpec_Builder *)key:(NSString *)key;

- (PIPlayTargetSpec_Builder *)link_extra_params:(NSString *)link_extra_params;

- (PIPlayTargetSpec_Builder *)link_pzb_dataWithNSString:(NSString *)link_pzb_data;

- (PIPlayTargetSpec_Builder *)link_urlWithNSString:(NSString *)link_url;

- (PIPlayTargetSpec_Builder *)mode:(jint)mode;

- (PIPlayTargetSpec_Builder *)play_stream_mode:(jint)play_stream_mode;

- (PIPlayTargetSpec_Builder *)push_tcs_mode:(jint)push_tcs_mode;

- (PIPlayTargetSpec_Builder *)pzb_data:(id<JavaUtilList>)pzb_data;

- (PIPlayTargetSpec_Builder *)render_mode:(jint)render_mode;

- (PIPlayTargetSpec_Builder *)render_mode_param:(NSString *)render_mode_param;

- (PIPlayTargetSpec_Builder *)ridWithLong:(jlong)rid;

- (PIPlayTargetSpec_Builder *)sid:(jint)sid;

- (PIPlayTargetSpec_Builder *)slot:(jint)slot;

- (PIPlayTargetSpec_Builder *)srid:(NSString *)rid;

- (PIPlayTargetSpec_Builder *)stream_group:(JavaLangLong *)stream_group;

- (PIPlayTargetSpec_Builder *)to_uid:(NSString *)to_uid;

- (PIPlayTargetSpec_Builder *)url:(id<JavaUtilList>)url;

- (PIPlayTargetSpec_Builder *)ve_name:(NSString *)ve_name;

- (PIPlayTargetSpec_Builder *)ve_slot:(JavaLangInteger *)ve_slot;

@end

J2OBJC_EMPTY_STATIC_INIT(PIPlayTargetSpec_Builder)

FOUNDATION_EXPORT void PIPlayTargetSpec_Builder_init(PIPlayTargetSpec_Builder *self);

J2OBJC_TYPE_LITERAL_HEADER(PIPlayTargetSpec_Builder)

#endif


#if __has_feature(nullability)
#pragma clang diagnostic pop
#endif
#pragma pop_macro("INCLUDE_ALL_PlayTargetSpec")