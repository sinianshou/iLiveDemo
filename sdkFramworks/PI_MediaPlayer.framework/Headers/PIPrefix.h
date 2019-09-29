//
//  PIPrefix.h
//  PIMediaPlayer
//
//  Created on 2019/01/08.
//  Copyright © 2019 PowerInfo. All rights reserved.
//

#ifndef PI_MEDIA_PLAYER_PREFIX_H
#define PI_MEDIA_PLAYER_PREFIX_H

#ifdef __cplusplus
#define PI_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define PI_EXTERN extern __attribute__((visibility ("default")))
#endif

#endif //PI_MEDIA_PLAYER_PREFIX_H
