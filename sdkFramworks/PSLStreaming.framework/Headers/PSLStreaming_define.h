//
//  PSLStreaming_define.h
//
//  Created on 14-5-5.
//  Copyright (c) 2014年 LuoHan. All rights reserved.
//

#ifndef PSLStreaming_define_h
#define PSLStreaming_define_h

#ifdef NT_VERSION
#if defined(SELF_PSLSTREAMING_DLL)
#define PSLSTREAMING_API __declspec(dllexport)
#else
#define PSLSTREAMING_API __declspec(dllimport)
#endif
#else
#define PSLSTREAMING_API 
#endif

#if (defined ANDROID_VERSION)

#include <android/log.h>

#define DEBUG 1
#define TAG   "POWERSMART_PACKER"
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

#if DEBUG
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#else
#define ALOGV(...)
#endif

#endif

#if (defined ANDROID_VERSION || defined NT_VERSION)

#define MAX_VIDEO_TRACK 1
#define MAX_AUDIO_TRACK 5
#define MAX_DATA_TRACK  1

#endif

#define NALU_QUEUE_LENGTH 3
#define NALU_INIT_SIZE    2000

#define TXTYPE_HTTPPORT 0
#define TXTYPE_MPTX     1


//typedef unsigned char BYTE;

//the audio capture device number
#define MIC_NUM 1

#define VIDEO_KEYFRAME 0x00000001
//interface for packer's callback function, so that packer can get data infos

//define the callbackfunc of packer
//typedef void* (*packercallback)(unsigned char*, PBUFFER_INFO);

#endif

