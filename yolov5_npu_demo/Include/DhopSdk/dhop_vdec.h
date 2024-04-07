/*******************************************************************************
 * dhop_vdec.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义解码相关的数据结构与API
 *
 *******************************************************************************/

#ifndef __DHOP_VDEC_H__
#define __DHOP_VDEC_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"
#include "dhop_yuv.h"

/*******************************************************************************/

typedef enum
{
    DHOP_VDEC_TYPE_JPEG_TO_YUV = 0,              /* 解码jpeg图片到YUV色彩空间 */
    DHOP_VDEC_TYPE_H264_TO_YUV,                  /* 解码h264码流到YUV色彩空间 */
    DHOP_VDEC_TYPE_H265_TO_YUV,                  /* 解码H265图片到YUV色彩空间 */

    DHOP_VDEC_TYPE_BUTT,
} DHOP_VDEC_ConvertType;

/* 解码能力 */
typedef struct
{
    DH_Uint32               cbSize;          /* 当前结构体大小，便于后续扩展时兼容与识别，调用者必填 */
    DH_Uint16               maxWidth;        /* 设备支持的最大解码宽度 */
    DH_Uint16               maxHeight;       /* 设备支持的最大解码高度 */
    DH_Uint16               minWidth;        /* 设备支持的最小解码宽度 */
    DH_Uint16               minHeight;       /* 设备支持的最小解码高度 */
    DH_Uint16               alignW;          /* 解码宽度对齐要求 */
    DH_Uint16               alignH;          /* 解码高度对齐要求 */
    DH_Uint16               vdecTypeMask;    /* 解码类型掩码,一位代表一种解码类型,参考DHOP_VDEC_ConvertType */
    DH_Uint16               outFmtMask;      /* 解码结果类型掩码,一位代表一种解码结果类型,参考DHOP_YUV_Format */
    DH_Uint16               maxDecoderNum;   /* 支持最多创建多少个解码器 */
    DH_Uint16               frameBufCnt;     /* 解码图像帧存个数 */
    DH_Uint32               streamBufSize;   /* 发送缓存大小 */
    DH_Uint16               maxFps;          /* 解码的最大帧率 */
    DH_Uint16               reversed[9];     /* 保留字段 */
} DHOP_VDEC_CapsInfo;

/* 解码创建参数 */
typedef struct
{
    DH_Uint32               cbSize;          /* 当前结构体大小，便于后续扩展时兼容与识别，调用者必填 */
    DH_Uint16               type;            /* 解码类型,参考DHOP_VDEC_Type */
    DH_Uint16               fps;             /* 解码帧率 */
    DH_Uint16               max_width;       /* 待解码帧最大宽度 */
    DH_Uint16               max_height;      /* 待解码帧最大高度 */
    DH_Uint16               outFmt;          /* 解码得到的YUV的色域空间,暂时只支持NV21 */
    DH_Uint16               reserved[5];     /* 保留字段 */
} DHOP_VDEC_CreateParam;

/* 解码请求 */
typedef struct
{
    /*
        1. 建议使用DHOP_MEM_blockAlloc申请的内存用于存放解码前的视频流
    */
    DH_Uint32               cbSize;           /* 当前结构体大小，便于后续扩展时兼容与识别，调用者必填 */
    DH_Uint32               size;             /* 数据长度 */
    DH_Uint8 *              pVirAddr;         /* 要解码的视频流的存放的虚拟地址 */
    DH_Uint8 *              pPhyAddr;         /* 如果待解码帧数据来自内存块DHOP_MEM_blockAlloc,指明内存物理地址 */
    DH_Uint32               reserved[8];      /* 保留字段 */
} DHOP_VDEC_Stream;

typedef DHOP_YUV_FrameData2 DHOP_VDEC_Frame;

/* 解码器状态信息 */
typedef struct
{
    DH_Uint32               cbSize;             /* 当前结构体大小，便于后续扩展时兼容与识别，调用者必填 */
    DH_Uint32               leftBytes;          /* 码流buffer中待解码的byte数，包括正在解码的当前帧中未解码的byte */
    DH_Uint32               leftFrames;         /* 码流buffer中待解码的帧数，不包括正在解码的当前帧 */
    DH_Uint32               leftPics;           /* 待获取的yuv数 */
    DH_Uint32               reserved[4];        /* 保留字段 */
}DHOP_VDEC_Status;

/***************************************************************
* function name : DHOP_VDEC_getCaps
*
* description   : get decoder capabilities
*
* input         : pCapInfo -- 只填写cbSize
*
* output        : pCapInfo -- 输出设备的解码能力信息
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_VDEC_getCaps(DHOP_VDEC_CapsInfo *pCapInfo);


/***************************************************************
* function name : DHOP_VDEC_create
*
* description   : create decoder
*
* input         : pParam  -- create parameters
*
* output        : hDecoder -- decoder handle.
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : 0: success
*                Non 0:  fail -- ref DHOP_ErrorCode
* note :
*
***************************************************************/
DH_Int32 DHOP_VDEC_create(DHOP_VDEC_CreateParam *pParam, DH_Handle * hDecoder);


/***************************************************************
* function name : DHOP_VDEC_destroy
*
* description   : destroy decoder
*
* input         : hDecoder -- decoder handle.
*
* output        : None
*
* notice        : 1. 线程安全
*                 2. 句柄非安全
*                 3. 同步接口
*
* return value  : 0: success
*                Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_VDEC_destroy(DH_Handle *hDecoder);


/***************************************************************
* function name : DHOP_VDEC_sendStream
*
* description   : send stream or frame to decoder.
*
* input         : pStream -- the decode stream.
*                timeoutMs -- timeout参数
*                -1：阻塞。
*                0：非阻塞。
*                正值：超时时间，以ms为单位
*
* notice        : 1. 线程安全
*                 2. 句柄安全
*                 3. 同步接口
*
* return value  : 0: success
*                Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_VDEC_sendStream(DH_Handle hDecoder, DHOP_VDEC_Stream* pStream, DH_Int32 timeoutMs);

/***************************************************************
* function name : DHOP_VDEC_getFrame
*
* description   : get frame from decoder.
*
* input         : pFrame -- the decode frame.
*                timeoutMs -- timeout参数
*                -1：阻塞。
*                0：非阻塞。
*                正值：超时时间，以ms为单位
*
* output        : pStream -- 输出解码结果
*
* notice        : 1. 线程安全
*                 2. 句柄安全
*                 3. 同步接口
*
* return value  : 0: success
*                Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_VDEC_getFrame(DH_Handle hDecoder, DHOP_VDEC_Frame* pFrame, DH_Int32 timeoutMs);


/***************************************************************
* function name : DHOP_VDEC_releaseFrame
*
* description   : release frame of decoder.
*
* input         : pFrame -- the decode frame.
*
* notice        : 1. 线程安全
*                 2. 句柄安全
*                 3. 同步接口
*
* return value  : 0: success
*                Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_VDEC_releaseFrame(DH_Handle hDecoder, DHOP_VDEC_Frame* pFrame);


/***************************************************************
* function name : DHOP_VDEC_queryStatus
*
* description   : query status of decoder.
*
* input         : pStatus -- 只填写cbSize
*
* output        : pStatus -- 输出解码器状态信息
*
* notice        : 1. 线程安全
*                 2. 句柄安全
*                 3. 同步接口
*
* return value  : 0: success
*                Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_VDEC_queryStatus(DH_Handle hDecoder, DHOP_VDEC_Status* pStatus);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_CODEC_H__
