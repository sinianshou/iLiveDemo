//
//  psunityplayer.h
//  PSCocosEngine
//
//  Created by swj-macbook on 2019/7/19.
//  Copyright © 2019 sjdd. All rights reserved.
//

#ifndef psunityplayer_hpp
#define psunityplayer_hpp

#include <stdio.h>
#include "pscocosframe.h"
#include "pscocosvector.h"

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct {
    int        _version;    //结构版本(_version)：以确保播放模块与父模块一致，取值
    CCFVECTOR *frame_queue;        //客户端新增队列，用于保存未解压的unity场景信息
    PSCOCOS_FRAME* ijk_pscocos_player_receiver_popFrame_buf_frame; //输出解压后的场景帧的缓冲区
    void* psunity_frame_queue_mutex;
    void* psunity_frame_queue_cond;
    int abort;
    char pscocos_player_newFrame_buf[PSCOCOS_SCENE_FULLSIZE];   //场景解码的缓存区
} PSUNITY_PLAYER;

int psunity_player_init(int _version, PSUNITY_PLAYER* player);

int psunity_player_clean(PSUNITY_PLAYER* player);

int psunity_player_get_version(PSUNITY_PLAYER* player, int* version);
    
#ifdef __cplusplus
}
#endif

#endif /* psunityplayer_h */
