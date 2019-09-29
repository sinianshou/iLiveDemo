//
//  pscocosremotectrlbuffer.hpp
//  PSCocosEngine
//
//  Created by swj-macbook on 2019/1/18.
//  Copyright © 2019 sjdd. All rights reserved.
//

#ifndef pscocosremotectrlbuffer_h
#define pscocosremotectrlbuffer_h

#include <stdio.h>
#include <string.h>
#include "pscocos_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int bufferSize;        //当前缓冲区数据大小
    int bufferSt;
    int bufferEd;
    char bufferArray[PSCOCOS_REMOTE_CTRL_MAXSIZE][PSCOCOS_REMOTE_CTRL_LENGTH_LIMIT];    //缓冲区数据
    int bufferLen[PSCOCOS_REMOTE_CTRL_MAXSIZE];
    int tagListSize;    //tagList长度
    int64_t tagList[PSCOCOS_REMOTE_PLAYER_LIMIT];    //推流端接收回传数据的播放器TAG列表
    int flagList[PSCOCOS_REMOTE_PLAYER_LIMIT];    //推流端接收回传数据的播放器是否接受，1接受，0不接受，开始默认关闭
    
    void *bufferMutex;          //读写缓冲区数据的互斥锁
    void *bufferCond;           //缓冲区写入数据时发送信号
    void *stopCond;
    int abort;                  //缓冲区开始关闭flag
    int stopFlag;                   //缓冲区正式关闭flag
} PSCOCOS_REMOTE_CTRL_BUFFER;

int pscocos_remote_ctrl_buffer_create(PSCOCOS_REMOTE_CTRL_BUFFER **result_ptr);  //构造缓冲区

int pscocos_remote_ctrl_buffer_destroy(PSCOCOS_REMOTE_CTRL_BUFFER **result_ptr); //析构缓冲区

int pscocos_remote_ctrl_buffer_read(PSCOCOS_REMOTE_CTRL_BUFFER *buffer, char **result_str, int *result_len, int time_ms);    //用于读取缓冲区数据
int pscocos_remote_ctrl_buffer_write(PSCOCOS_REMOTE_CTRL_BUFFER *buffer, int64_t TAG, char *data, int dataSize);    //由PSPlayer回调，用于向缓冲区写入数据

int pscocos_remote_ctrl_buffer_get_tag_list(PSCOCOS_REMOTE_CTRL_BUFFER *buffer, int64_t ** result_ptr, int *len_ptr);    //用于读取写入该缓冲区的播放器列表
int pscocos_remote_ctrl_buffer_register_tag(PSCOCOS_REMOTE_CTRL_BUFFER *buffer, int64_t tag, int flag);    //在缓冲区中添加新的播放器TAG以及设置接收数据的状态flag
int pscocos_remote_ctrl_buffer_unregister_tag(PSCOCOS_REMOTE_CTRL_BUFFER *buffer, int64_t tag);    //在缓冲区中删除播放器TAG
int pscocos_remote_ctrl_buffer_set_flag(PSCOCOS_REMOTE_CTRL_BUFFER *buffer, int64_t tag, int flag);    //在缓冲区中设置接收数据的状态flag

#ifdef __cplusplus
}
#endif

#endif /* pscocosremotectrlbuffer_h */
