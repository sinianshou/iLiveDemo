//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: jar:file:libs/XiRoom-sources.jar!com/powerinfo/pi_iroom/api/SocketIOApi.java
//

#include "J2ObjC_header.h"

#pragma push_macro("INCLUDE_ALL_SocketIOApi")
#ifdef RESTRICT_SocketIOApi
#define INCLUDE_ALL_SocketIOApi 0
#else
#define INCLUDE_ALL_SocketIOApi 1
#endif
#undef RESTRICT_SocketIOApi

#if !defined (PISocketIOApi_) && (INCLUDE_ALL_SocketIOApi || defined(INCLUDE_PISocketIOApi))
#define PISocketIOApi_

@class PIChangeRefreshResultSpec_Sig;
@protocol PISocketIOCallback;

@protocol PISocketIOApi < JavaObject >

- (void)connect:(PIChangeRefreshResultSpec_Sig *)sigConfig
   WithCallback:(id<PISocketIOCallback>)callback;

- (void)registerWithMessage:(NSString *)message;

- (void)sendMessageWithType:(NSString *)type
                withMessage:(NSString *)message;

- (void)disconnect;

@end

J2OBJC_EMPTY_STATIC_INIT(PISocketIOApi)

inline NSString *PISocketIOApi_get_TAG(void);
/*! INTERNAL ONLY - Use accessor function from above. */
FOUNDATION_EXPORT NSString *PISocketIOApi_TAG;
J2OBJC_STATIC_FIELD_OBJ_FINAL(PISocketIOApi, TAG, NSString *)

J2OBJC_TYPE_LITERAL_HEADER(PISocketIOApi)

#define ComPowerinfoPi_iroomApiSocketIOApi PISocketIOApi

#endif

#if !defined (PISocketIOCallback_) && (INCLUDE_ALL_SocketIOApi || defined(INCLUDE_PISocketIOCallback))
#define PISocketIOCallback_

@class PISigMessage;

@protocol PISocketIOCallback < JavaObject >

- (void)onMessage:(PISigMessage *)sigMessage;

- (void)onRegister:(PISigMessage *)sigMessage;

- (void)onConnectSuccess;

- (void)onDisconnect;

- (void)onReconnectFailed;

@end

J2OBJC_EMPTY_STATIC_INIT(PISocketIOCallback)

J2OBJC_TYPE_LITERAL_HEADER(PISocketIOCallback)

#endif

#pragma pop_macro("INCLUDE_ALL_SocketIOApi")
