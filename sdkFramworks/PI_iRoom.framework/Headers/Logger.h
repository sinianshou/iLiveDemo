//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: jar:file:libs/XiRoom-sources.jar!com/powerinfo/pi_iroom/api/Logger.java
//

#include "J2ObjC_header.h"

#pragma push_macro("INCLUDE_ALL_Logger")
#ifdef RESTRICT_Logger
#define INCLUDE_ALL_Logger 0
#else
#define INCLUDE_ALL_Logger 1
#endif
#undef RESTRICT_Logger

#if !defined (PILogger_) && (INCLUDE_ALL_Logger || defined(INCLUDE_PILogger))
#define PILogger_

@protocol PILogger < JavaObject >

- (void)severe:(NSString *)tag
       content:(NSString *)content;

- (void)error:(NSString *)tag
      content:(NSString *)content;

@end

J2OBJC_EMPTY_STATIC_INIT(PILogger)

J2OBJC_TYPE_LITERAL_HEADER(PILogger)

#define ComPowerinfoPi_iroomApiLogger PILogger

#endif

#pragma pop_macro("INCLUDE_ALL_Logger")
