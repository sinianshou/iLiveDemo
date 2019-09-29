//
/*
 * Copyright (c) 2017 Powerinfo. All rights reserved.
 */
//

#import <Foundation/Foundation.h>

@interface PIJ2ObjCUtils : NSObject

+ (id)arrayToList:(NSArray*)array;
+ (NSArray*)listToArray:(id)list;
+ (NSDictionary*)mapToDic:(id)map;

+ (NSArray*)iOSLongArrayToArray:(id)longArray;
+ (id)arrayToiOSLongArray:(NSArray*)array;
+ (id)longToJavaLanglong:(int64_t)num;
@end
