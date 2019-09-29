/*
 * Copyright (c) 2018 Bai Shuai <baishuai.io@gmail.com>
 *
 * This file is part of hijkPlayer.
 *
 * hijkPlayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * hijkPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ijkPlayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */


#import <Foundation/Foundation.h>
#import "PIPrefix.h"

#define SYNC_TYPE_MEDIA_TIMELINE      1
#define SYNC_TYPE_PZSP_PZVT           2

PI_EXTERN @interface PIMoviePlayerGroup : NSObject

- (instancetype)initWithCount:(int)count andType:(int)sync_type;

@end
