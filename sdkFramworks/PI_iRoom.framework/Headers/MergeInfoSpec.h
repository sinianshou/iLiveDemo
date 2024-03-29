//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: jar:file:libs/XiRoom-sources.jar!com/powerinfo/pi_iroom/data/MergeInfoSpec.java
//

#include "J2ObjC_header.h"

#pragma push_macro("INCLUDE_ALL_MergeInfoSpec")
#ifdef RESTRICT_MergeInfoSpec
#define INCLUDE_ALL_MergeInfoSpec 0
#else
#define INCLUDE_ALL_MergeInfoSpec 1
#endif
#undef RESTRICT_MergeInfoSpec

#if __has_feature(nullability)
#pragma clang diagnostic push
#pragma GCC diagnostic ignored "-Wnullability-completeness"
#endif

#if !defined (PIMergeInfoSpec_) && (INCLUDE_ALL_MergeInfoSpec || defined(INCLUDE_PIMergeInfoSpec))
#define PIMergeInfoSpec_

@class ComGoogleGsonGson;
@class ComGoogleGsonTypeAdapter;
@class JavaUtilArrayList;

@interface PIMergeInfoSpec : NSObject

#pragma mark Public

- (instancetype)init;

+ (PIMergeInfoSpec *)createWithLong:(jlong)primaryRoom
              withJavaUtilArrayList:(JavaUtilArrayList *)rooms;

+ (PIMergeInfoSpec *)createMergeInfoSpecWithPrimaryRoom:(NSString *)primaryRoom
                                              withRooms:(JavaUtilArrayList *)rooms;

- (NSString *)primary_sroom;

- (JavaUtilArrayList *)srooms;

+ (ComGoogleGsonTypeAdapter *)typeAdapterWithComGoogleGsonGson:(ComGoogleGsonGson *)gson;

@end

J2OBJC_EMPTY_STATIC_INIT(PIMergeInfoSpec)

FOUNDATION_EXPORT void PIMergeInfoSpec_init(PIMergeInfoSpec *self);

FOUNDATION_EXPORT ComGoogleGsonTypeAdapter *PIMergeInfoSpec_typeAdapterWithComGoogleGsonGson_(ComGoogleGsonGson *gson);

FOUNDATION_EXPORT PIMergeInfoSpec *PIMergeInfoSpec_createWithLong_withJavaUtilArrayList_(jlong primaryRoom, JavaUtilArrayList *rooms);

FOUNDATION_EXPORT PIMergeInfoSpec *PIMergeInfoSpec_createMergeInfoSpecWithPrimaryRoom_withRooms_(NSString *primaryRoom, JavaUtilArrayList *rooms);

J2OBJC_TYPE_LITERAL_HEADER(PIMergeInfoSpec)

@compatibility_alias ComPowerinfoPi_iroomDataMergeInfoSpec PIMergeInfoSpec;

#endif


#if __has_feature(nullability)
#pragma clang diagnostic pop
#endif
#pragma pop_macro("INCLUDE_ALL_MergeInfoSpec")
