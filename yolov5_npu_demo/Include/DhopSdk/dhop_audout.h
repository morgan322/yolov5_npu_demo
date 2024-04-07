/*******************************************************************************
 * dhop_audout.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义音频输出相关的数据结构与API
 *
 *******************************************************************************/

#ifndef __DHOP_AUDOUT_H__
#define __DHOP_AUDOUT_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/

#include "dhop_type_def.h"

/*******************************************************************************/

/* 音频格式 */
typedef enum
{
    DHOP_AUDOUT_FORMAT_PCM = 0,
    DHOP_AUDOUT_FORMAT_ADPCM,
    DHOP_AUDOUT_FORMAT_G711A,
    DHOP_AUDOUT_FORMAT_G711MU,
    DHOP_AUDOUT_FORMAT_G726,
    DHOP_AUDOUT_FORMAT_MPEG2LAYER1,
    DHOP_AUDOUT_FORMAT_AMR,
    DHOP_AUDOUT_FORMAT_AAC,
    DHOP_AUDOUT_FORMAT_MPEG2LAYER2,
    DHOP_AUDOUT_FORMAT_OGGVORBIS,
    DHOP_AUDOUT_FORMAT_MP3,
    DHOP_AUDOUT_FORMAT_G722_1,
    DHOP_AUDOUT_FORMAT_G729,
    DHOP_AUDOUT_FORMAT_OPUS,
    DHOP_AUDOUT_FORMAT_G723,
    DHOP_AUDOUT_FORMAT_TTS,
    DHOP_AUDOUT_FORMAT_MAX,                                       /* 边界值 */
} DHOP_AUDOUT_Format;

/* 音频采样位深 */
typedef enum
{
    DHOP_AUDOUT_DEPTH_8 = 0,
    DHOP_AUDOUT_DEPTH_16,
    DHOP_AUDOUT_DEPTH_24,
    DHOP_AUDOUT_DEPTH_MAX,                                        /* 边界值 */
} DHOP_AUDOUT_Depth;

/* 音频播放状态 */
typedef enum
{
    DHOP_AUDOUT_STATUS_INIT = 0,                                   /* 未开始播放 */
    DHOP_AUDOUT_STATUS_WORK,                                       /* 正在播放 */
    DHOP_AUDOUT_STATUS_END,                                        /* 播放完成 */
    DHOP_AUDOUT_STATUS_MAX,                                        /* 边界值 */
} DHOP_AUDOUT_Status;

/*******************************************************************************/
#if (__SIZEOF_POINTER__ == 4)                                   /* 32位系统下结构体定义 */

/* 音频播放能力*/
typedef struct
{
    DH_Uint16       cbSize;                                     /* 结构体大小 */
    DH_Uint8        format;                                     /* 播放格式, 参考DHOP_AUDOUT_Format */
    DH_Uint8        depth;                                      /* 采样位深, 参考  DHOP_AUDOUT_Depth */
    DH_Uint32       frequency;                                  /* 采样率，Hz为单位，比如44100Hz */
    DH_Uint32       rsv[8];                                     /* 保留字段 */
} DHOP_AUDOUT_Capability;

/* 播放创建参数 */
typedef struct
{
    DH_Uint16       cbSize;                                     /* 当前结构体大小 */
    DH_Uint8        format;                                     /* 播放格式, 参考DHOP_AUDOUT_Format */
    DH_Uint8        depth;                                      /* 采样位深, 参考  DHOP_AUDOUT_Depth */
    DH_Uint32       frequency;                                  /* 采样率，Hz为单位，比如44100Hz */
    DH_Uint32       channel;                                    /* 播放通道 */
    DH_Uint32       rsv[7];                                     /* 保留字段 */
} DHOP_AUDOUT_CreateParam;

#endif

#if (__SIZEOF_POINTER__ == 8)                                   /* 64位系统下结构体定义 */

/* 音频播放能力*/
typedef struct
{
    DH_Uint16       cbSize;                                     /* 结构体大小 */
    DH_Uint8        format;                                     /* 播放格式, 参考DHOP_AUDOUT_Format */
    DH_Uint8        depth;                                      /* 采样位深, 参考  DHOP_AUDOUT_Depth */
    DH_Uint32       frequency;                                  /* 采样率，Hz为单位，比如44100Hz */
    DH_Uint32       rsv[8];                                     /* 保留字段 */
} DHOP_AUDOUT_Capability;

/* 播放创建参数 */
typedef struct
{
    DH_Uint16       cbSize;                                     /* 当前结构体大小 */
    DH_Uint8        format;                                     /* 播放格式, 参考DHOP_AUDOUT_Format */
    DH_Uint8        depth;                                      /* 采样位深, 参考  DHOP_AUDOUT_Depth */
    DH_Uint32       frequency;                                  /* 采样率，Hz为单位，比如44100Hz */
    DH_Uint32       channel;                                    /* 播放通道 */
    DH_Uint32       rsv[7];                                     /* 保留字段 */
} DHOP_AUDOUT_CreateParam;

#endif

/*******************************************************************************/

/***************************************************************
* function name : DHOP_AUDOUT_getChnNum
*
* description   : 获取播放通道数
*
* input         :  none
*
* output        : pNum ---- 音频播放输出的通道数
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : 其它         - 参考DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_AUDOUT_getChnNum(DH_Uint32* pNum);


/***************************************************************
* function name : DHOP_AUDOUT_getChnCaps
*
* description   : 获取指定通道的播放能力
*
* input         : channel --  通道号
*                 pCaps ---- 调用者指定的存放能力的数组
*                 pNum ---- 调用者指定的能力数组大小
*
* output        : pCaps -- 实际返回的播放能力
*                 pNum ---- 实际返回的能力个数
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : 其它         - 参考DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_AUDOUT_getChnCaps(DH_Uint32 channel, DHOP_AUDOUT_Capability *pCaps, DH_Uint32* pNum);


/***************************************************************
* function name : DHOP_AUDOUT_create
*
* description   : 创建播放句柄
*
* input         : pParam  -- 播放参数
*
* output        : hDecoder -- 可用的播放句柄
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : 其它         - 参考DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_AUDOUT_create(DHOP_AUDOUT_CreateParam *pParam, DH_Handle * hDecoder);


/***************************************************************
* function name : DHOP_AUDOUT_destroy
*
* description   : 销毁播放句柄
*
* input         : hDecoder -- 待销毁的句柄
*
* output        : None
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : 其它         - 参考DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_AUDOUT_destroy(DH_Handle hDecoder);


/***************************************************************
* function name : DHOP_AUDOUT_putData
*
* description   : 送入播放数据
*
* input         : hDecoder -- 播放句柄
*                 pData -- 待播放的数据
*                 size -- 待播放的数据大小
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : 其它         - 参考DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_AUDOUT_putData(DH_Handle hDecoder, DH_Byte* pData, DH_Uint32 size);

/***************************************************************
* function name : DHOP_AUDOUT_getStatus
*
* description   : 获取播放状态
*
* input         : hDecoder -- 播放句柄
*
* output        : status -- 播放状态，值参考DHOP_AUDOUT_Status
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : 其它         - 参考DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_AUDOUT_getStatus(DH_Handle hDecoder, DH_Uint32* status);

/***************************************************************
* function name : DHOP_AUDOUT_setVolume
*
* description   : 设置音频播放的音量
*
* input         : hDecoder -- 播放句柄
*                 volume -- 播放音量 [0-100]
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : 其它         - 参考DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_AUDOUT_setVolume(DH_Handle hDecoder, DH_Uint32 volume);

/***************************************************************
* function name : DHOP_AUDOUT_setSpeed
*
* description   : 设置音频播放的速度
*
* input         : hDecoder -- 播放句柄
*                 speed -- 播放速度 0.5表示半速播放 1.0表示原速播放，2.0表示两倍速播放
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : 其它         - 参考DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_AUDOUT_setSpeed(DH_Handle hDecoder, DH_Float32 speed);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_AUDOUT_H__
