//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: jar:file:libs/XiRoom-sources.jar!com/powerinfo/pi_iroom/PIiRoomPeerShared.java
//

#include "J2ObjC_header.h"

#pragma push_macro("INCLUDE_ALL_PIiRoomPeerShared")
#ifdef RESTRICT_PIiRoomPeerShared
#define INCLUDE_ALL_PIiRoomPeerShared 0
#else
#define INCLUDE_ALL_PIiRoomPeerShared 1
#endif
#undef RESTRICT_PIiRoomPeerShared

#if !defined (PIiRoomPeerShared_) && (INCLUDE_ALL_PIiRoomPeerShared || defined(INCLUDE_PIiRoomPeerShared))
#define PIiRoomPeerShared_

#define RESTRICT_PeerBase 1
#define INCLUDE_PIPeerBase 1
#include "PeerBase.h"

@class IOSLongArray;
@class PIErrorReporter;
@class PIJsonConverter;
@class PIRsCacheManager;
@class PIUiMemSafePeerCallback;
@protocol PIBatteryManager;
@protocol PICapability;
@protocol PILibraryVersionUtilApi;
@protocol PILogger;
@protocol PIReachability;
@protocol PIUiTaskRunner;
@protocol PIiLiveBaseApi;

@interface PIiRoomPeerShared : PIPeerBase {
 @public
  jboolean mPreviewAtStart_;
  jint mRole_;
}

#pragma mark Public

- (instancetype)initWithPICapability:(id<PICapability>)capability
                  withPIReachability:(id<PIReachability>)reachability
                  withPIiLiveBaseApi:(id<PIiLiveBaseApi>)pIiLiveBaseApi
           withLibraryVersionUtilApi:(id<PILibraryVersionUtilApi>)libraryVersionUtilApi
                 withPIJsonConverter:(PIJsonConverter *)jsonConverter
                  withPIUiTaskRunner:(id<PIUiTaskRunner>)uiTaskRunner
                        withPILogger:(id<PILogger>)logger
                  withRsCacheManager:(PIRsCacheManager *)rsCacheManager
                withClientSdkVersion:(NSString *)clientSdkVersion
                        withDeviceId:(NSString *)deviceId
                             withUid:(NSString *)uid
                          withVeName:(NSString *)veName
                            withRole:(jint)role
                  withPreviewAtStart:(jboolean)previewAtStart
                        withCallback:(PIUiMemSafePeerCallback *)callback
                   withErrorReporter:(PIErrorReporter *)errorReporter
                  withBatteryManager:(id<PIBatteryManager>)batteryManager;

- (void)changeRole:(jlong)rid
           newRole:(jint)newRole;

- (void)joiniRoomInternal:(IOSLongArray *)roomIds;

- (void)joiniRoomInternal:(jlong)primaryRoom
                mergeRoom:(jboolean)mergeRoom
                  roomIds:(IOSLongArray *)roomIds;

- (void)leaveiRoomInternal:(IOSLongArray *)roomIds;

- (void)leaveiRoomInternal:(jlong)oldPrimaryRoom
                 splitRoom:(jboolean)splitRoom
                   roomIds:(IOSLongArray *)roomIds;

@end

J2OBJC_EMPTY_STATIC_INIT(PIiRoomPeerShared)

inline NSString *PIiRoomPeerShared_get_TAG(void);
/*! INTERNAL ONLY - Use accessor function from above. */
FOUNDATION_EXPORT NSString *PIiRoomPeerShared_TAG;
J2OBJC_STATIC_FIELD_OBJ_FINAL(PIiRoomPeerShared, TAG, NSString *)

FOUNDATION_EXPORT void PIiRoomPeerShared_initWithPICapability_withPIReachability_withPIiLiveBaseApi_withLibraryVersionUtilApi_withPIJsonConverter_withPIUiTaskRunner_withPILogger_withRsCacheManager_withClientSdkVersion_withDeviceId_withUid_withVeName_withRole_withPreviewAtStart_withCallback_withErrorReporter_withBatteryManager_(PIiRoomPeerShared *self, id<PICapability> capability, id<PIReachability> reachability, id<PIiLiveBaseApi> pIiLiveBaseApi, id<PILibraryVersionUtilApi> libraryVersionUtilApi, PIJsonConverter *jsonConverter, id<PIUiTaskRunner> uiTaskRunner, id<PILogger> logger, PIRsCacheManager *rsCacheManager, NSString *clientSdkVersion, NSString *deviceId, NSString *uid, NSString *veName, jint role, jboolean previewAtStart, PIUiMemSafePeerCallback *callback, PIErrorReporter *errorReporter, id<PIBatteryManager> batteryManager);

J2OBJC_TYPE_LITERAL_HEADER(PIiRoomPeerShared)

@compatibility_alias ComPowerinfoPi_iroomPIiRoomPeerShared PIiRoomPeerShared;

#endif

#pragma pop_macro("INCLUDE_ALL_PIiRoomPeerShared")
