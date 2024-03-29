//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: jar:file:libs/XiRoom-sources.jar!com/powerinfo/pi_iroom/data/$AutoValue_ChangeRefreshRequestSpec.java
//

#include "J2ObjC_header.h"

#pragma push_macro("INCLUDE_ALL_$AutoValue_ChangeRefreshRequestSpec")
#ifdef RESTRICT_$AutoValue_ChangeRefreshRequestSpec
#define INCLUDE_ALL_$AutoValue_ChangeRefreshRequestSpec 0
#else
#define INCLUDE_ALL_$AutoValue_ChangeRefreshRequestSpec 1
#endif
#undef RESTRICT_$AutoValue_ChangeRefreshRequestSpec

#if __has_feature(nullability)
#pragma clang diagnostic push
#pragma GCC diagnostic ignored "-Wnullability-completeness"
#endif

#if !defined (PI_AutoValue_ChangeRefreshRequestSpec_) && (INCLUDE_ALL_$AutoValue_ChangeRefreshRequestSpec || defined(INCLUDE_PI_AutoValue_ChangeRefreshRequestSpec))
#define PI_AutoValue_ChangeRefreshRequestSpec_

#define RESTRICT_ChangeRefreshRequestSpec 1
#define INCLUDE_PIChangeRefreshRequestSpec 1
#include "ChangeRefreshRequestSpec.h"

@protocol JavaUtilList;

@interface PI_AutoValue_ChangeRefreshRequestSpec : PIChangeRefreshRequestSpec

#pragma mark Public

- (jboolean)append;

- (jint)arrc;

- (NSString *)client_sdk_version;

- (NSString *)device;

- (jboolean)isEqual:(id)o;

- (NSString *)group_id;

- (NSUInteger)hash;

- (NSString *)mc_profile;

- (NSString *)merge_info;

- (id<JavaUtilList>)rooms;

- (NSString *)split_info;

- (NSString *)description;

- (NSString *)uid;

- (id<JavaUtilList>)us_caps;

- (NSString *)ve_name;

#pragma mark Package-Private

- (instancetype)initWithNSString:(NSString *)client_sdk_version
                    withNSString:(NSString *)device
                    withNSString:(NSString *)group_id
                    withNSString:(NSString *)uid
                    withNSString:(NSString *)ve_name
                         withInt:(jint)arrc
                     withBoolean:(jboolean)append
                withJavaUtilList:(id<JavaUtilList>)rooms
                    withNSString:(NSString *)merge_info
                    withNSString:(NSString *)split_info
                withJavaUtilList:(id<JavaUtilList>)us_caps
                    withNSString:(NSString *)mc_profile;

@end

J2OBJC_EMPTY_STATIC_INIT(PI_AutoValue_ChangeRefreshRequestSpec)

FOUNDATION_EXPORT void PI_AutoValue_ChangeRefreshRequestSpec_initWithNSString_withNSString_withNSString_withNSString_withNSString_withInt_withBoolean_withJavaUtilList_withNSString_withNSString_withJavaUtilList_withNSString_(PI_AutoValue_ChangeRefreshRequestSpec *self, NSString *client_sdk_version, NSString *device, NSString *group_id, NSString *uid, NSString *ve_name, jint arrc, jboolean append, id<JavaUtilList> rooms, NSString *merge_info, NSString *split_info, id<JavaUtilList> us_caps, NSString *mc_profile);

J2OBJC_TYPE_LITERAL_HEADER(PI_AutoValue_ChangeRefreshRequestSpec)

@compatibility_alias ComPowerinfoPi_iroomData$AutoValue_ChangeRefreshRequestSpec PI_AutoValue_ChangeRefreshRequestSpec;

#endif

#if !defined (PI_AutoValue_ChangeRefreshRequestSpec_Builder_) && (INCLUDE_ALL_$AutoValue_ChangeRefreshRequestSpec || defined(INCLUDE_PI_AutoValue_ChangeRefreshRequestSpec_Builder))
#define PI_AutoValue_ChangeRefreshRequestSpec_Builder_

#define RESTRICT_ChangeRefreshRequestSpec 1
#define INCLUDE_PIChangeRefreshRequestSpec_Builder 1
#include "ChangeRefreshRequestSpec.h"

@class PIChangeRefreshRequestSpec;
@protocol JavaUtilList;

@interface PI_AutoValue_ChangeRefreshRequestSpec_Builder : PIChangeRefreshRequestSpec_Builder

#pragma mark Public

- (PIChangeRefreshRequestSpec_Builder *)append:(jboolean)append;

- (PIChangeRefreshRequestSpec_Builder *)arrc:(jint)arrc;

- (PIChangeRefreshRequestSpec *)Builder;

- (PIChangeRefreshRequestSpec_Builder *)client_sdk_version:(NSString *)client_sdk_version;

- (PIChangeRefreshRequestSpec_Builder *)device:(NSString *)device;

- (PIChangeRefreshRequestSpec_Builder *)group_id:(NSString *)group_id;

- (PIChangeRefreshRequestSpec_Builder *)mc_profile:(NSString *)mc_profile;

- (PIChangeRefreshRequestSpec_Builder *)merge_info:(NSString *)merge_info;

- (PIChangeRefreshRequestSpec_Builder *)rooms:(id<JavaUtilList>)rooms;

- (PIChangeRefreshRequestSpec_Builder *)split_info:(NSString *)split_info;

- (PIChangeRefreshRequestSpec_Builder *)uid:(NSString *)uid;

- (PIChangeRefreshRequestSpec_Builder *)us_caps:(id<JavaUtilList>)us_caps;

- (PIChangeRefreshRequestSpec_Builder *)ve_name:(NSString *)ve_name;

#pragma mark Package-Private

- (instancetype)init;

@end

J2OBJC_EMPTY_STATIC_INIT(PI_AutoValue_ChangeRefreshRequestSpec_Builder)

FOUNDATION_EXPORT void PI_AutoValue_ChangeRefreshRequestSpec_Builder_init(PI_AutoValue_ChangeRefreshRequestSpec_Builder *self);

FOUNDATION_EXPORT PI_AutoValue_ChangeRefreshRequestSpec_Builder *new_PI_AutoValue_ChangeRefreshRequestSpec_Builder_init(void) NS_RETURNS_RETAINED;

FOUNDATION_EXPORT PI_AutoValue_ChangeRefreshRequestSpec_Builder *create_PI_AutoValue_ChangeRefreshRequestSpec_Builder_init(void);

J2OBJC_TYPE_LITERAL_HEADER(PI_AutoValue_ChangeRefreshRequestSpec_Builder)

#endif


#if __has_feature(nullability)
#pragma clang diagnostic pop
#endif
#pragma pop_macro("INCLUDE_ALL_$AutoValue_ChangeRefreshRequestSpec")
