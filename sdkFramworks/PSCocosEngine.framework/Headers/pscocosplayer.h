//
//  pscocosplayer.h
//  IJKMediaPlayer
//
//  Created by swj-macbook on 2018/10/31.
//  Copyright © 2018 PowerInfo. All rights reserved.
//

#ifndef pscocosplayer_h
#define pscocosplayer_h

#include <stdio.h>
#include <string.h>
#include "pscocosframe.h"
#include "pscocosvector.h"
#include "pscocos_macro.h"

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int        _version;    //结构版本(_version)：以确保播放模块与父模块一致，取值
    
    int        _fps;        //播放帧率
    
    int        _width;        //webview界面宽度
    int        _height;    //webview界面高度
    
    char keyList[PSCOCOS_KEYLIST_MAXSIZE][PSCOCOS_KEYLENGTH_MAXSIZE];     //场景树节点关键字列表
    int        _keyListSize;    //关键字列表长度
    int     keyLen[PSCOCOS_KEYLIST_MAXSIZE];
    char* _oldScene[PSCOCOS_SCENE_MAXSIZE][PSCOCOS_KEYWORD_MAXSIZE];    //保存旧场景每个节点信息的字符串数组
    int _oldSceneSize;    //旧场景节点个数
    int _oldSceneLimit[PSCOCOS_SCENE_MAXSIZE][PSCOCOS_KEYWORD_MAXSIZE];
    int _oldSceneLen[PSCOCOS_SCENE_MAXSIZE][PSCOCOS_KEYWORD_MAXSIZE];
    int *children[PSCOCOS_SCENE_MAXSIZE];
    int childrenLimit[PSCOCOS_SCENE_MAXSIZE];
    int childrenLen[PSCOCOS_SCENE_MAXSIZE];
    
    //收流端属性
    
    int        _originalWidth;        //场景数据webview界面原始高度
    int        _originalHeight;    //场景数据webview界面原始高度
    
    int     _bufferLimit;    //picture_queue大小限制（单位帧）
    CCFVECTOR *frame_queue;        //客户端新增队列，用于保存未解码（解压）的cocos场景信息
    CCFVECTOR *picture_queue;    //客户端新增队列，用于保存已解码（解压）的cocos场景信息
    int speedFlag[PSCOCOS_FRAME_VECTOR_MAXSIZE];
    
    int64_t playStamp;            //从外部获取的当前时间，用于播放控制
    int64_t current_stamp;        //当前播放的场景的时间戳
    int64_t target_stamp;        //目标时间戳，用于jump状态下的播放控制
    int64_t target_delay;        //目标延迟，单位毫秒，用于播放控制
    int currentState;        //当前状态，0（normal)，1(speed)，2(jump)
    int abort;
    int64_t speed_threshold;    //speed状态的阈值，当frame_queue和picture_queue中的场景总时长大与该值时进入speed状态，speed状态下已解码的画面会加速播放
    int64_t jump_threshold;        //jump状态的阈值，当frame_queue和picture_queue中的场景总时长大与该值时进入jump状态，jump状态下会直接跳到目标时间戳target_stamp之后的第一个关键帧
    int rcp;
    
    char *pscocos_unzip_frame_pBuf; //保存unzip数据缓冲区
    
    
    int pscocos_player_node_sequence[PSCOCOS_SCENE_MAXSIZE][PSCOCOS_KEYWORD_MAXSIZE];   //不同节点不同属性的更新状态
    
    char pscocos_player_newFrame_buf[PSCOCOS_SCENE_FULLSIZE];   //场景解码的缓存区
    
    PSCOCOS_FRAME* ijk_pscocos_player_receiver_popFrame_buf_frame; //输出解码后的场景帧的缓冲区
    
    void* pscocos_decode_thread;
    void* pscocos_frame_queue_mutex;
    void* pscocos_picture_queue_mutex;
    void* pscocos_pop_frame_cond;
    void* pscocos_push_frame_cond;
    void* pscocos_pop_picture_cond;
    void* pscocos_push_picture_cond;
    void* pscocos_decodeFrame_mutex;
    
    int queue[PSCOCOS_SCENE_MAXSIZE];
    
    int wait_i;
    int ms_to_pass;
    int severed[256];

    char music_info[PSCOCOS_MUSIC_SIZE][5][PSCOCOS_MUSIC_INFO_SIZE];
    int music_len[PSCOCOS_MUSIC_SIZE][5];
    int music_update[PSCOCOS_MUSIC_SIZE];
} PSCOCOS_PLAYER;


int pscocos_player_init(int _version, int _width, int _height, int _fps, int _originalWidth, int _originalHeight, PSCOCOS_PLAYER* player);
//用于获得空的播放器；_version为版本号，当传递参数为-1时使用缺省值；_userType为0时，APP为推流端，为1时，APP为收流端；_interval关键帧间隔，(_width, _height)为浏览器在屏幕上的尺寸，_fps为帧率，游戏引擎本身要求渲染画面必为30或60帧，可从JS界面获得。
//当推流端调用时，宽度、高度、fps等参数应由Object-C或Java调用webview的响应接口获得，而屏幕原始尺寸则为无效数据，不做处理即可，同时应将调用参数在获得场景数据前上传到服务器。
//当收流端调用时，宽度、高度仍从JS界面获得,原始尺寸、fps等参数由父模块获得

int pscocos_player_clean(PSCOCOS_PLAYER* player);
//回收PSCOCOS_PLAYER内存

#define PSCOCOS_CTRLCODE_PLAYPAUSE     1
#define PSCOCOS_CTRLCODE_RESET        2
#define PSCOCOS_CTRLCODE_SPEED        3

int pscocos_player_controlPlayer(PSCOCOS_PLAYER* player, int ctrl_code, int ctrl_value, char*param_string); //提供控制接口（暂停/播放，重置，其他待扩展）

int pscocos_player_get_width(PSCOCOS_PLAYER* player, int* width);    //获取JS界面宽度
int pscocos_player_get_height(PSCOCOS_PLAYER* player, int* height);    //获取JS界面高度
int pscocos_player_get_fps(PSCOCOS_PLAYER* player, int* fps);            //获取JS界面fps
int pscocos_player_get_version(PSCOCOS_PLAYER* player, int* version);        //获取播放器版本

int pscocos_player_setPlayStamp(PSCOCOS_PLAYER* player, int64_t playstamp);  //设置当前播放时间戳，控制播放流程

int pscocos_player_cocos_getPlayStatus(PSCOCOS_PLAYER* player, int* decstatus, int*playstatus, int*buffer_ms, unsigned int* sequence_no, int64_t* played_timestamp);    //（GetPlayStatus解码状态、播放状态、缓冲数据时长、当前播放帧序号、stamp、播放延迟）

#ifdef __cplusplus
}
#endif
    
#endif /* cocosplayer_h */
