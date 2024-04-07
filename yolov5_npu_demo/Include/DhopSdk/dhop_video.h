/*******************************************************************************
 * dhop_video.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义视频参数相关的数据结构与API。
 *
 *******************************************************************************/

#ifndef __DHOP_VIDEO_H__
#define __DHOP_VIDEO_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"


/*******************************************************************************/

/* 设备通道号 */
typedef enum
{
    DHOP_VIDEO_CHN_0 = 0,
    DHOP_VIDEO_CHN_MAX,
} DHOP_VIDEO_ChnId;

/* Video模块通道码流号 */
typedef enum
{
    DHOP_VIDEO_CHN_STREAM_0 = 0,
    DHOP_VIDEO_CHN_STREAM_1,
    DHOP_VIDEO_CHN_STREAM_2,
    DHOP_VIDEO_CHN_STREAM_3,
    DHOP_VIDEO_CHN_STREAM_4,
    DHOP_VIDEO_CHN_STREAM_MAX,
} DHOP_VIDEO_ChnStreamId;

/* 码流分辨率类型 */
typedef enum
{
    DHOP_VIDEO_RESOLUTION_TYPE_3840x2160 = 0, /* 3840x2160 */
    DHOP_VIDEO_RESOLUTION_TYPE_3072x2048,     /* 3072x2048 */
    DHOP_VIDEO_RESOLUTION_TYPE_3072x1728,     /* 3072x1728 */
    DHOP_VIDEO_RESOLUTION_TYPE_2592x1944,     /* 2592x1944 */
    DHOP_VIDEO_RESOLUTION_TYPE_2688x1520,     /* 2688x1520 */
    DHOP_VIDEO_RESOLUTION_TYPE_2560x1440,     /* 2560x1440 */
    DHOP_VIDEO_RESOLUTION_TYPE_3M,            /* 2048x1536 */
    DHOP_VIDEO_RESOLUTION_TYPE_2304x1296,     /* 2304x1296 */
    DHOP_VIDEO_RESOLUTION_TYPE_1080P,         /* 1920x1080 */
    DHOP_VIDEO_RESOLUTION_TYPE_1_3M,          /* 1280x960 */
    DHOP_VIDEO_RESOLUTION_TYPE_720P,          /* 1280x720 */
    DHOP_VIDEO_RESOLUTION_TYPE_D1,            /* 704x576 */
    DHOP_VIDEO_RESOLUTION_TYPE_VGA,           /* 640x480 */
    DHOP_VIDEO_RESOLUTION_TYPE_CIF,           /* 352x288 */

    DHOP_VIDEO_RESOLUTION_TYPE_MAX,
} DHOP_VIDEO_ResolutionType;

/*******************************************************************************/


/*******************************************************************************/
#if (__SIZEOF_POINTER__ == 4)           // 32位系统下结构体定义

/* 模块能力 */
typedef struct
{
    DH_Uint16       chnNum;                 /* 通道个数 */
    DH_Uint16       resByte;                /* 保留字段 */
    DH_Uint32       reserved[16];           /* 保留字段 */
} DHOP_VIDEO_Capability;

/* 通道能力 */
typedef struct
{
    DH_Uint16       streamNum;              /* 码流个数 */
    DH_Uint16       resByte;                /* 保留字段 */
    DH_Uint32       reserved[16];           /* 保留字段 */
} DHOP_VIDEO_ChnCaps;

/* 码流启动参数 */
typedef struct
{
    DH_Uint16       chnId;                  /* 通道号,[0, chnNum),chuNum可通过DHOP_VIDEO_getCapbility()获取,调用者必填 */
    DH_Uint16       streamId;               /* 码流号,参考DHOP_VIDEO_ChnStreamId,调用者必填 */
    DH_Uint32       reserved[16];           /* 保留字段 */
} DHOP_VIDEO_OpenParam;

/* 码流能力 */
typedef struct
{
    DH_Uint16       minFps;                 /* 最小帧率 */
    DH_Uint16       maxFps;                 /* 最大帧率 */
    DH_Uint16       maxGop;                 /* 最大I帧间隔 */
    DH_Uint16       minBitRate;             /* 最小帧率,单位(Kb/s) */
    DH_Uint16       maxBitRate;             /* 最大码率,单位(Kb/s) */
    DH_Uint16       resolutionNum;          /* 支持分辨率个数 */
    DH_Uint16      *pResolution;            /* 支持的分辨率 */
    DH_Uint32       reserved[16];           /* 保留字段 */
} DHOP_VIDEO_StreamCaps;

/* 码流配置 */
typedef struct
{
    DH_Uint16       resolution;             /* 分辨率 */
    DH_Uint16       fps;                    /* 帧率 */
    DH_Uint16       gop;                    /* I帧间隔,最小值为帧率,通常使用帧率x2,最大值为mxGop */
    DH_Uint16       bitRate;                /* 码率,单位(Kb/s) */
    DH_Uint32       reserved[16];           /* 保留字段 */
} DHOP_VIDEO_StreamCfg;

/* 码流码率范围 */
typedef struct
{
    DH_Uint16       min;                    /* 最小参考码率 */
    DH_Uint16       max;                    /* 最大参考码率 */
    DH_Uint16       suggest;                /* 建议码率 */
    DH_Uint16       resBytes;               /* 保留字段 */
    DH_Uint32       reserved[8];            /* 保留字段 */
} DHOP_VIDEO_StreamBitRateRange;

#endif

#if (__SIZEOF_POINTER__ == 8)           // 64位系统下结构体定义

/* 模块能力,调用者无需填写 */
typedef struct
{
    DH_Uint16       chnNum;                 /* 通道个数 */
    DH_Uint16       resByte[3];             /* 保留字段 */
    DH_Uint64       reserved[8];            /* 保留字段 */
} DHOP_VIDEO_Capability;

/* 通道能力,调用者无需填写 */
typedef struct
{
    DH_Uint16       streamNum;              /* 码流个数 */
    DH_Uint16       resByte[3];             /* 保留字段 */
    DH_Uint64       reserved[8];            /* 保留字段 */
} DHOP_VIDEO_ChnCaps;

/* 码流启动参数 */
typedef struct
{
    DH_Uint16       chnId;                  /* 通道号,[0, chnNum),chuNum可通过DHOP_VIDEO_getCapbility()获取,调用者必填 */
    DH_Uint16       streamId;               /* 通道码流号,参考DHOP_VIDEO_ChnStreamId,调用者必填 */
    DH_Uint16       resBytes[2];            /* 保留字段 */
    DH_Uint64       reserved[8];            /* 保留字段 */
} DHOP_VIDEO_OpenParam;

/* 码流能力 */
typedef struct
{
    DH_Uint16       minFps;                 /* 最小帧率 */
    DH_Uint16       maxFps;                 /* 最大帧率 */
    DH_Uint16       maxGop;                 /* 最大I帧间隔 */
    DH_Uint16       minBitRate;             /* 最小帧率,单位(Kb/s) */
    DH_Uint16       maxBitRate;              /* 最大码率,单位(Kb/s) */
    DH_Uint16       resolutionNum;           /* 支持的分辨率个数 */
    DH_Uint32       resBytes;                /* 保留字段 */
    DH_Uint16      *pResolution;             /* 支持的分辨率 */
    DH_Uint64       reserved[8];             /* 保留字段 */
} DHOP_VIDEO_StreamCaps;

/* 码流配置 */
typedef struct
{
    DH_Uint16       resolution;              /* 分辨率 */
    DH_Uint16       fps;                     /* 帧率 */
    DH_Uint16       gop;                     /* I帧间隔,最小值为帧率,通常使用帧率x2,最大值为mxGop */
    DH_Uint16       bitRate;                 /* 码率,单位(Kb/s) */
    DH_Uint64       reserved[8];             /* 保留字段 */
} DHOP_VIDEO_StreamCfg;

/* 码流码率范围 */
typedef struct
{
    DH_Uint16       min;                      /* 最小参考码率 */
    DH_Uint16       max;                      /* 最大参考码率 */
    DH_Uint16       suggest;                  /* 建议码率 */
    DH_Uint16       resBytes;                 /* 保留字段 */
    DH_Uint64       reserved[4];              /* 保留字段 */
} DHOP_VIDEO_StreamBitRateRange;

#endif

/***************************************************************
* function name : DHOP_VIDEO_getCapbility
*
* description   : 获取VIDEO模块能力
*
* input         : pCapbility -- 模块能力信息
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 需要调用DHOP_SYS_init()初始化DHOP系统
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VIDEO_getCapbility(DHOP_VIDEO_Capability *pCapbility);

/***************************************************************
* function name : DHOP_VIDEO_getChnCaps
*
* description   : 获取VIDEO模块某设备通道能力
*
* input         : chnId -- 通道编号
*                 pChnCap -- 通道能力
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 需要调用DHOP_SYS_init()初始化DHOP系统
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VIDEO_getChnCaps(DH_Uint16 chnId, DHOP_VIDEO_ChnCaps *pChnCap);

/***************************************************************
* function name : DHOP_VIDEO_getStreamCaps
*
* description   : 获取VIDEO模块某设备通道下某码流能力
*
* input         : chnId -- 通道编号
*                 streamId -- 码流编号
*                 pCaps -- 码流能力
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 需要调用DHOP_SYS_init()初始化DHOP系统
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VIDEO_getStreamCaps(DH_Uint16 chnId, DH_Uint16 streamId, DHOP_VIDEO_StreamCaps *pCaps);

/***************************************************************
* function name : DHOP_VIDEO_open
*
* description   : 开启VIDEO服务(某通道下的某路码流)
*
* input         : pParam -- 启动参数
*                 ppHandle -- 操作句柄指针
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 需要调用DHOP_SYS_init()初始化DHOP系统
*                 4. 开启成功后,可以获取或修改对应码流配置
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VIDEO_open(DHOP_VIDEO_OpenParam *pParam, DH_Handle *ppHandle);

/***************************************************************
* function name : DHOP_VIDEO_close
*
* description   : 关闭VIDEO服务(某通道下的某路码流)
*
* input         : ppHandle -- 操作句柄指针
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VIDEO_close(DH_Handle *ppHandle);

/***************************************************************
* function name : DHOP_VIDEO_getStreamCfg
*
* description   : 获取操作句柄对应码流配置
*
* input         : pHandle -- 操作句柄
*                 pCfg -- 码流配置
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VIDEO_getStreamCfg(DH_Handle pHandle, DHOP_VIDEO_StreamCfg *pCfg);

/***************************************************************
* function name : DHOP_VIDEO_getBitRateRange
*
* description   : 根据输入的码流配置参数(分辨率、帧率、I帧间隔),
*                 计算该配置下码率参考范围和建议值.
*
* input         : pHandle -- 操作句柄
*                 pCfg -- 要设置的码流配置
*                 pRange -- 参考码率范围
*
* output        : 无
*
* notice        : 1. 暂不支持
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VIDEO_getBitRateRange(DH_Handle pHandle, DHOP_VIDEO_StreamCfg *pCfg,
                                    DHOP_VIDEO_StreamBitRateRange *pRange);

/***************************************************************
* function name : DHOP_VIDEO_setStreamCfg
*
* description   : 设置操作句柄对应的码流配置
*
* input         : pHandle -- 操作句柄
*                 pCfg -- 码流配置
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VIDEO_setStreamCfg(DH_Handle pHandle, DHOP_VIDEO_StreamCfg *pCfg);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_VIDEO_H__



