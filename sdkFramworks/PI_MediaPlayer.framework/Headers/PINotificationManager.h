/*
 * PINotificationManager.h
 */

#import <Foundation/Foundation.h>
#import "PIPrefix.h"

PI_EXTERN @interface PINotificationManager : NSObject

- (nullable instancetype)init;

- (void)addObserver:(nonnull id)observer
           selector:(nonnull SEL)aSelector
               name:(nullable NSString *)aName
             object:(nullable id)anObject;

- (void)removeAllObservers:(nonnull id)observer;

@end
