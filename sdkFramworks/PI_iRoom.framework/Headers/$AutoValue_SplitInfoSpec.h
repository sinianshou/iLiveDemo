//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: jar:file:libs/XiRoom-sources.jar!com/powerinfo/pi_iroom/data/$AutoValue_SplitInfoSpec.java
//

#include "J2ObjC_header.h"

#pragma push_macro("INCLUDE_ALL_$AutoValue_SplitInfoSpec")
#ifdef RESTRICT_$AutoValue_SplitInfoSpec
#define INCLUDE_ALL_$AutoValue_SplitInfoSpec 0
#else
#define INCLUDE_ALL_$AutoValue_SplitInfoSpec 1
#endif
#undef RESTRICT_$AutoValue_SplitInfoSpec

#if !defined (PI_AutoValue_SplitInfoSpec_) && (INCLUDE_ALL_$AutoValue_SplitInfoSpec || defined(INCLUDE_PI_AutoValue_SplitInfoSpec))
#define PI_AutoValue_SplitInfoSpec_

#define RESTRICT_SplitInfoSpec 1
#define INCLUDE_PISplitInfoSpec 1
#include "SplitInfoSpec.h"

@class JavaUtilArrayList;

@interface PI_AutoValue_SplitInfoSpec : PISplitInfoSpec

#pragma mark Public

- (jboolean)isEqual:(id)o;

- (NSUInteger)hash;

- (NSString *)old_primary_sroom;

- (JavaUtilArrayList *)split;

- (NSString *)description;

#pragma mark Package-Private

- (instancetype)initWithNSString:(NSString *)old_primary_sroom
           withJavaUtilArrayList:(JavaUtilArrayList *)split;

@end

J2OBJC_EMPTY_STATIC_INIT(PI_AutoValue_SplitInfoSpec)

FOUNDATION_EXPORT void PI_AutoValue_SplitInfoSpec_initWithNSString_withJavaUtilArrayList_(PI_AutoValue_SplitInfoSpec *self, NSString *old_primary_sroom, JavaUtilArrayList *split);

J2OBJC_TYPE_LITERAL_HEADER(PI_AutoValue_SplitInfoSpec)

@compatibility_alias ComPowerinfoPi_iroomData$AutoValue_SplitInfoSpec PI_AutoValue_SplitInfoSpec;

#endif

#pragma pop_macro("INCLUDE_ALL_$AutoValue_SplitInfoSpec")