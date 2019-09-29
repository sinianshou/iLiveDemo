//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: jar:file:libs/XiRoom-sources.jar!com/powerinfo/pi_iroom/data/AutoValue_CheckedUser.java
//

#include "J2ObjC_header.h"

#pragma push_macro("INCLUDE_ALL_AutoValue_CheckedUser")
#ifdef RESTRICT_AutoValue_CheckedUser
#define INCLUDE_ALL_AutoValue_CheckedUser 0
#else
#define INCLUDE_ALL_AutoValue_CheckedUser 1
#endif
#undef RESTRICT_AutoValue_CheckedUser

#if __has_feature(nullability)
#pragma clang diagnostic push
#pragma GCC diagnostic ignored "-Wnullability-completeness"
#endif

#if !defined (PIAutoValue_CheckedUser_) && (INCLUDE_ALL_AutoValue_CheckedUser || defined(INCLUDE_PIAutoValue_CheckedUser))
#define PIAutoValue_CheckedUser_

#define RESTRICT_$AutoValue_CheckedUser 1
#define INCLUDE_PI_AutoValue_CheckedUser 1
#include "$AutoValue_CheckedUser.h"

@interface PIAutoValue_CheckedUser : PI_AutoValue_CheckedUser

#pragma mark Package-Private

- (instancetype)initWithNSString:(NSString *)uid
                    withNSString:(NSString *)ve_name
                     withBoolean:(jboolean)streaming;

@end

J2OBJC_EMPTY_STATIC_INIT(PIAutoValue_CheckedUser)

FOUNDATION_EXPORT void PIAutoValue_CheckedUser_initWithNSString_withNSString_withBoolean_(PIAutoValue_CheckedUser *self, NSString *uid, NSString *ve_name, jboolean streaming);

FOUNDATION_EXPORT PIAutoValue_CheckedUser *new_PIAutoValue_CheckedUser_initWithNSString_withNSString_withBoolean_(NSString *uid, NSString *ve_name, jboolean streaming) NS_RETURNS_RETAINED;

FOUNDATION_EXPORT PIAutoValue_CheckedUser *create_PIAutoValue_CheckedUser_initWithNSString_withNSString_withBoolean_(NSString *uid, NSString *ve_name, jboolean streaming);

J2OBJC_TYPE_LITERAL_HEADER(PIAutoValue_CheckedUser)

@compatibility_alias ComPowerinfoPi_iroomDataAutoValue_CheckedUser PIAutoValue_CheckedUser;

#endif

#if !defined (PIAutoValue_CheckedUser_GsonTypeAdapter_) && (INCLUDE_ALL_AutoValue_CheckedUser || defined(INCLUDE_PIAutoValue_CheckedUser_GsonTypeAdapter))
#define PIAutoValue_CheckedUser_GsonTypeAdapter_

#define RESTRICT_TypeAdapter 1
#define INCLUDE_ComGoogleGsonTypeAdapter 1
#include "TypeAdapter.h"

@class ComGoogleGsonGson;
@class ComGoogleGsonJsonElement;
@class ComGoogleGsonStreamJsonReader;
@class ComGoogleGsonStreamJsonWriter;
@class JavaIoReader;
@class PICheckedUser;

@interface PIAutoValue_CheckedUser_GsonTypeAdapter : ComGoogleGsonTypeAdapter

#pragma mark Public

- (instancetype)initWithComGoogleGsonGson:(ComGoogleGsonGson *)gson;

- (PICheckedUser *)fromJsonTreeWithComGoogleGsonJsonElement:(ComGoogleGsonJsonElement *)arg0;

- (PICheckedUser *)fromJsonWithJavaIoReader:(JavaIoReader *)arg0;

- (PICheckedUser *)fromJsonWithNSString:(NSString *)arg0;

- (PICheckedUser *)readWithComGoogleGsonStreamJsonReader:(ComGoogleGsonStreamJsonReader *)jsonReader;

- (void)writeWithComGoogleGsonStreamJsonWriter:(ComGoogleGsonStreamJsonWriter *)jsonWriter
                                        withId:(PICheckedUser *)object;

// Disallowed inherited constructors, do not use.

- (instancetype)init NS_UNAVAILABLE;

@end

J2OBJC_EMPTY_STATIC_INIT(PIAutoValue_CheckedUser_GsonTypeAdapter)

FOUNDATION_EXPORT void PIAutoValue_CheckedUser_GsonTypeAdapter_initWithComGoogleGsonGson_(PIAutoValue_CheckedUser_GsonTypeAdapter *self, ComGoogleGsonGson *gson);

FOUNDATION_EXPORT PIAutoValue_CheckedUser_GsonTypeAdapter *new_PIAutoValue_CheckedUser_GsonTypeAdapter_initWithComGoogleGsonGson_(ComGoogleGsonGson *gson) NS_RETURNS_RETAINED;

FOUNDATION_EXPORT PIAutoValue_CheckedUser_GsonTypeAdapter *create_PIAutoValue_CheckedUser_GsonTypeAdapter_initWithComGoogleGsonGson_(ComGoogleGsonGson *gson);

J2OBJC_TYPE_LITERAL_HEADER(PIAutoValue_CheckedUser_GsonTypeAdapter)

#endif


#if __has_feature(nullability)
#pragma clang diagnostic pop
#endif
#pragma pop_macro("INCLUDE_ALL_AutoValue_CheckedUser")