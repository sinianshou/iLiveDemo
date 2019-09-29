/*
 * PIKVOController.h
 */

#import <Foundation/Foundation.h>
#import "PIPrefix.h"

PI_EXTERN @interface PIKVOController : NSObject

- (id)initWithTarget:(NSObject *)target;

- (void)safelyAddObserver:(NSObject *)observer
               forKeyPath:(NSString *)keyPath
                  options:(NSKeyValueObservingOptions)options
                  context:(void *)context;
- (void)safelyRemoveObserver:(NSObject *)observer
                  forKeyPath:(NSString *)keyPath;

- (void)safelyRemoveAllObservers;

@end
