//
//  pscocossender.h
//  P31-Link
//
//  Created by swj-macbook on 2018/11/16.
//  Copyright © 2018 PowerSmart. All rights reserved.
//

#ifndef pscocossender_h
#define pscocossender_h

#include "pscocosplayer.h"
#include "pscocostrie.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    int        _version;    //结构版本(_version)：以确保播放模块与父模块一致，取值
        
    CCFVECTOR* list;  //PSCOCOS_FRAME的队列，在推流端，用于缓冲从JS界面获取的，经过压缩的场景数据。
        
    int     _interval;    //关键帧间隔，单位ms
    int        _fps;        //播放帧率
    int64_t frame_interval;
    int64_t currentStamp;
    int        _width;        //webview界面宽度
    int        _height;    //webview界面高度
        
    char       keyList[PSCOCOS_KEYLIST_MAXSIZE][PSCOCOS_KEYLENGTH_MAXSIZE];     //场景树节点关键字列表
    int        _keyListSize;    //关键字列表长度
    int        keyLen[PSCOCOS_KEYLIST_MAXSIZE];
    int64_t     _keyFrameStamp;
    int64_t        _keyFrameStameEachInterval;
        
        
    //推流端属性
    char* _oldScene[PSCOCOS_SCENE_MAXSIZE][PSCOCOS_KEYWORD_MAXSIZE];    //保存旧场景每个节点信息的字符串数组
    int _oldSceneLimit[PSCOCOS_SCENE_MAXSIZE][PSCOCOS_KEYWORD_MAXSIZE];
    int _oldSceneLen[PSCOCOS_SCENE_MAXSIZE][PSCOCOS_KEYWORD_MAXSIZE];
    int64_t     _keyStamp;    //推流端下一个强制设为关键帧的时刻
    int64_t        _keyStampEachInterval;    //下一个定期产生关键帧的时刻
    
    char *pscocos_zip_frame_pBuf;   //保存zip数据的缓冲区
    PSCOCOS_FRAME* pscocos_sender_insertFrame_buf_Frame;    //插入帧的缓冲区
    int* match_point;                //用于解析场景数据的辅助数组
    PSCOCOSTRIE pscocos_sender_trie;    //常量关键字组成的字典树
    int pscocos_sender_updateOldSceneNodeAddFlag[PSCOCOS_KEYWORD_MAXSIZE];  //用于标记单个节点属性变化的数组
    int sender_last_sequence_no;    //最后发送的帧编号
    
    char music_info[PSCOCOS_MUSIC_SIZE][5][PSCOCOS_MUSIC_INFO_SIZE];
    int music_len[PSCOCOS_MUSIC_SIZE][5];
    bool music_updateFlag[5];

} PSCOCOS_SENDER;

int pscocos_sender_init(int _version, int _interval, int _width, int _height, int _fps, PSCOCOS_SENDER* sender);
//用于获得空的播放器；_version为版本号，当传递参数为-1时使用缺省值；；_interval关键帧间隔，(_width, _height)为浏览器在屏幕上的尺寸，_fps为帧率，游戏引擎本身要求渲染画面必为30或60帧，可从JS界面获得。

int pscocos_sender_clean(PSCOCOS_SENDER* sender);
//回收PSCOCOS_SENDER内存
//int pscocos_sender_controlPlayer(PSCOCOS_PLAYER* player, int ctrl_code, int ctrl_value, char*param_string); //提供控制接口（暂停/播放，重置，其他待扩展）

int pscocos_sender_compress_with_old_scene(PSCOCOS_FRAME *frame, PSCOCOS_SENDER* sender,int keyFlag);
int pscocos_sender_insertFrame(PSCOCOS_SENDER* sender, const char* frame, int64_t currentStamp);
int pscocos_sender_popFrame(PSCOCOS_SENDER* sender, PSCOCOS_FRAME* frame);

int PSCOCOS_sender_set_key_frame(PSCOCOS_SENDER* sender, int _keyflag, int64_t _timestamp);    //由推流端使用，设定_timestamp时刻场景数据为关键帧，的PSCOCOS_PLAYER*，_keyflag区分是否为关键帧。要求_timestamp仍在队列中或尚未进入队列。为-1时，获得当前渲染的场景数据。
int PSCOCOS_sender_set_interval(PSCOCOS_SENDER* sender, int _interval);                        //设置关键帧间隔
int64_t get_currentTime_of_cocos_sender();
    
#ifdef __cplusplus
}
#endif

#endif /* pscocossender_h */
