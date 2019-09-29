//
//  pscocosvector.h
//  IJKMediaPlayer
//
//  Created by swj-macbook on 2018/11/6.
//  Copyright © 2018 PowerInfo. All rights reserved.
//

#ifndef pscocosvector_h
#define pscocosvector_h

#include <stdio.h>
#include "pscocos_macro.h"
#include "pscocosframe.h"
#include "pscocosvector.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int st;                                            //队列开头
    int ed;                                            //队列结尾
    int size;                                        //队列元素个数
    int limit;
    PSCOCOS_FRAME data[PSCOCOS_FRAME_VECTOR_MAXSIZE];                            //保存队列中PSCOCOS_FRAME的数组
} CCFVECTOR;
    
int pscocos_vector_alloc(CCFVECTOR**list, int default_framesize);
int pscocos_vector_destroy(CCFVECTOR**list);
    
int pscocos_vector_init(CCFVECTOR* list);    //初始化CCFVECTOR
int pscocos_vector_clean(CCFVECTOR* list);    //回收CCFVECTOR内存
    
int pscocos_vector_push_frame_withbuf(CCFVECTOR* list, PSCOCOS_FRAME* frame, char*framebuf, int framesize);
    
int pscocos_vector_push_frame(CCFVECTOR* list, PSCOCOS_FRAME* frame);//向队列结尾添加PSCOCOS_FRAME
int pscocos_vector_pop_frame(CCFVECTOR* list, PSCOCOS_FRAME* frame);    //从队列开头获得PSCOCOS_FRAME，并从队列中删除开头的元素

#ifdef __cplusplus
};
#endif

#endif /* pscocosvector_h */
