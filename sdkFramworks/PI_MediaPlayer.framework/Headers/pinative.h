#ifndef PIPLAYER__NATIVE__EXPORT_H
#define PIPLAYER__NATIVE__EXPORT_H


#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>


typedef int(*hwctx_cbfunc)(void *opaque, int type, void *hwctx);


/**
 根据 userdata 以及视频输出格式进行视频渲染的准备工作

 调用时机: 播放器创建不久后, 在准备视频输出环境的步骤中. 只调用一次

 @param userdata 设置视频回调时传入的 userdata
 @param format fourcc 形式的视频输出格式， @see https://www.fourcc.org/yuv.php
    如果开启了硬解码，则 format 的值为 _AMC (android mediacodec)或 _VTB (ios videotoolbox)
 @return 执行成功返回0，否则返回非0值。
 */
typedef int (*piplayer_vout_create)(void *userdata, uint32_t format);


/**
 释放视频输出回调相关资源

 调用时机: 播放器结束的时候, 只调用一次

 @param userdata 设置视频回调时传入的 userdata
 @return 执行成功返回0，否则返回非0值。
 */
typedef int (*piplayer_vout_free)(void *userdata);


/**
 视频帧输出回调, 此回调函数中应该立即进行视频渲染。
 此函数会重复多次被调用.
 函数一旦返回, 指针类型的参数不可被继续使用

 调用时机: piplayer_vout_create 成功执行之后. piplayer_vout_free 执行之前. 每次有视频帧需要渲染的时候

 @param userdata 设置视频回调时传入的userdata
 @param duration 距离上次回调被调用的时间间隔，第一次调用值为0
 @param pts present timestamp 视频内容时间戳
 @param w 视频像素宽度
 @param h 视频像素高度
 @param planes 视频像素 plane 大小
 @param linesize 数组长度为 planes, 内容为每个 plane 像素内容的 byte 长度
 @param pixels 数组长度为 planes,
 @param privatedata 硬解码时使用
 @return 执行成功返回0，否则返回非0值。
 */
typedef int (*piplayer_vout_draw)(void *userdata, int64_t duration, int64_t pts, int w, int h, int planes, uint16_t *linesize, uint8_t **pixels, void *privatedata);


/**
 设置播放器视频回调

 @param player 播放器指针
 @param userdata 回调需要使用的userdata, 会作为回调的参数
 @param piplayer_vout_create 视频回调准备资源
 @param piplayer_vout_create 视频回调释放资源
 @param piplayer_vout_draw 视频帧渲染回调函数
 这三个回调函数都会在同一个线程中被调用
 */

#if !HIJK_WINDOWS
__attribute__((visibility ("default")))
int piplayer_enable_native_video_callback(void *player, void *userdata,
                                           piplayer_vout_create func_create, piplayer_vout_free func_free, piplayer_vout_draw func_draw);
#endif

/**
 * 获取播放器的音效时间戳
 * @param player  the pointer get from PIMediaPlayer#getNativePIMediaPlayer (android)
 *                or property nativePlayer of PIMoviePlayerController (ios)
 * @return extrats
 */
int64_t piplayer_get_extrats(void *player);


#ifdef __cplusplus
}
#endif

#endif // PIPLAYER__NATIVE__EXPORT_H
