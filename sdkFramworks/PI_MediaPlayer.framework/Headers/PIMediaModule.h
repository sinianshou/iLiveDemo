/*
 * PIMediaModule.h
 */

#import <Foundation/Foundation.h>
#import "PIPrefix.h"

PI_EXTERN @interface PIMediaModule : NSObject

+ (PIMediaModule *)sharedModule;

@property(atomic, getter=isAppIdleTimerDisabled)            BOOL appIdleTimerDisabled;
@property(atomic, getter=isMediaModuleIdleTimerDisabled)    BOOL mediaModuleIdleTimerDisabled;

@end
