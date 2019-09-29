//
//  pscocosframe.h
//  IJKMediaPlayer
//
//  Created by swj-macbook on 2018/11/6.
//  Copyright © 2018 PowerInfo. All rights reserved.
//

#ifndef pscocosframe_h
#define pscocosframe_h

#include <stdio.h>
#include <string.h>
#include "pscocos_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int        _version;
    int        _type;
    unsigned int _flags;
    int32_t _sequenceno;
    int64_t _timestamp;
    int32_t _framesize, _frameLimit;
    int32_t _originalsize;
    char    *_framebuf;
} PSCOCOS_FRAME;

//method of PSCOCOS_FRAME
int pscocos_alloc_frame(PSCOCOS_FRAME**ppframe, int framesize);
int pscocos_destroy_frame(PSCOCOS_FRAME**ppframe);

int pscocos_init_frame(PSCOCOS_FRAME* frame);    //初始化PSCOCOS_FRAME
int pscocos_clean_frame(PSCOCOS_FRAME* frame);    //回收PSCOCOS_FRAME的内存
    
int pscocos_zip_frame(PSCOCOS_FRAME* frame, int zip_level, char *pscocos_zip_frame_pBuf);    //将PSCOCOS_FRAME中_framebuf的数据做zip压缩，zip_level为压缩等级。
int pscocos_unzip_frame(PSCOCOS_FRAME* frame, char *pscocos_unzip_frame_pBuf);    //将PSCOCOS_FRAME中_framebuf的数据做zip解压
    
int pscocos_set_frame_status(PSCOCOS_FRAME* frame, int32_t _version, int32_t _type, int32_t flag, int32_t _sequenceno, int64_t _timestamp);    //设置PSCOCOS_FRAME的状态
    
int pscocos_set_frame_buf(PSCOCOS_FRAME* frame, int size, const char* buf); //向PSCOCOS_FRAME缓冲区中写入数据

int pscocos_free(char*);
    
int pscocos_log(int level,char* s);

#ifdef __cplusplus
}
#endif

#endif /* pscocosframe_h */
