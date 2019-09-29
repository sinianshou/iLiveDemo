//
//  psunitysender.h
//  PSCocosEngine
//
//  Created by swj-macbook on 2019/7/19.
//  Copyright © 2019 sjdd. All rights reserved.
//

#ifndef psunitysender_h
#define psunitysender_h

#include <stdio.h>
#include "pscocosframe.h"
#include "pscocosvector.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int        _version;    //结构版本(_version)：以确保播放模块与父模块一致，取值    
    CCFVECTOR* list;  //PSCOCOS_FRAME的队列，在推流端，用于缓冲从JS界面获取的，经过压缩的场景数据。
    char *psunity_zip_frame_pBuf;   //保存zip数据的缓冲区
    PSCOCOS_FRAME* psunity_sender_insertFrame_buf_Frame;    //插入帧的缓冲区
    int sender_last_sequence_no;    //最后发送的帧编号
} PSUNITY_SENDER;

int psunity_sender_init(int _version, PSUNITY_SENDER* sender);
//用于获得空的播放器；_version为版本号，当传递参数为-1时使用缺省值；

int psunity_sender_clean(PSUNITY_SENDER* sender);
//回收PSUnity_SENDER内存
//int pscocos_sender_controlPlayer(PSCOCOS_PLAYER* player, int ctrl_code, int ctrl_value, char*param_string); //提供控制接口（暂停/播放，重置，其他待扩展）

int psunity_sender_insertFrame(PSUNITY_SENDER* sender, const char* frame, int keyFlag, int64_t currentStamp);
int psunity_sender_popFrame(PSUNITY_SENDER* sender, PSCOCOS_FRAME* frame);
    
#ifdef __cplusplus
}
#endif


#endif /* psunitysender_hpp */
