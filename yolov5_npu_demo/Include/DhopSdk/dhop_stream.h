/*******************************************************************************
 * dhop_stream.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义音视频码流相关的数据结构与API。
 *
 *******************************************************************************/

#ifndef __DHOP_STREAM_H__
#define __DHOP_STREAM_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/

#include "dhop_type_def.h"


/*******************************************************************************/

typedef DH_Handle  DHOP_STREAM_Handle;                  // 音视频码流句柄

typedef enum
{
    DHOP_STREAM_STREAM_MAIN             = 0,            // 主码流
    DHOP_STREAM_STREAM_EXTRA1,                          // 辅码流
    DHOP_STREAM_STREAM_EXTRA2,
    DHOP_STREAM_STREAM_EXTRA3,
    DHOP_STREAM_STREAM_PICTURE          = 0x10,         // 图片流
    DHOP_STREAM_STREAM_MAX
} DHOP_STREAM_Stream;

//码流的格式
typedef enum
{
    DHOP_STREAM_FORMAT_UNKNOWN          = 0,
    DHOP_STREAM_FORMAT_VIDEO_UNKNOWN    = 0x1000,
    DHOP_STREAM_FORMAT_VIDEO_H264,
    DHOP_STREAM_FORMAT_VIDEO_H265,
    DHOP_STREAM_FORMAT_VIDEO_MJEPG,
    DHOP_STREAM_FORMAT_VIDEO_MAX,
    DHOP_STREAM_FORMAT_AUDIO_UNKNOWN    = 0x2000,
    DHOP_STREAM_FORMAT_AUDIO_PCM,
    DHOP_STREAM_FORMAT_AUDIO_G711A,
    DHOP_STREAM_FORMAT_AUDIO_G711MU,
    DHOP_STREAM_FORMAT_AUDIO_MAX,
    DHOP_STREAM_FORMAT_PICTURE_UNKNOWN  = 0x3000,
    DHOP_STREAM_FORMAT_PICTURE_JPEG,
    DHOP_STREAM_FORMAT_PICTURE_MAX,
    DHOP_STREAM_FORMAT_MAX,
} DHOP_STREAM_Format;

typedef enum
{
    DHOP_STREAM_FRAME_I = 0,
    DHOP_STREAM_FRAME_P,
    DHOP_STREAM_FRAME_B,
} DHOP_STREAM_FrameType;                                // 帧格式

typedef enum
{
    DHOP_STREAM_AUDIO_MODE_MONO = 0,
    DHOP_STREAM_AUDIO_MODE_STEREO,
} DHOP_STREAM_AudioMode;                                // 音频模式：单声道/立体声

typedef enum
{
    // 不限定类型，与DHOP_STREAM_MEDIA_TYPE_MIXTURE等价
    DHOP_STREAM_MEDIA_TYPE_AUTO    = 0,

    // 视频流数据
    DHOP_STREAM_MEDIA_TYPE_VIDEO   = (1 << 0),

    // 音频流数据
    DHOP_STERAM_MEDIA_TYPE_AUDIO   = (1 << 1),

    // 混合流媒体数据，包含音频和视频，与DHOP_STREAM_MEDIA_TYPE_AUTO等价
    DHOP_STREAM_MEDIA_TYPE_MIXTURE = (DHOP_STREAM_MEDIA_TYPE_VIDEO | DHOP_STERAM_MEDIA_TYPE_AUDIO),
} DHOP_STREAM_MediaType;


/*******************************************************************************/

/* 码流时间戳，精确到秒 */
typedef struct
{
    DH_Uint16                       year;               // 年
    DH_Uint8                        month;              // 月
    DH_Uint8                        day;                // 日
    DH_Uint8                        hour;               // 时
    DH_Uint8                        min;                // 分
    DH_Uint8                        sec;                // 秒
    DH_Uint8                        res;                // 保留字段
} DHOP_STREAM_TimeStamp;

typedef struct
{
    DH_Uint16          cbSize;        /* 结构体大小，由调用者填写 */
    DH_Int32           preRecord;     /* 预录时间 [0-5]s */
    DH_Int32           timeoutMs;     /* -1：阻塞。 0：非阻塞。正值：超时时间，以ms为单位 */

    DH_Int32           res[16];       /* 保留字段 */
}DHOP_STREAM_Option;

#if (__SIZEOF_POINTER__ == 4)                           // 32位系统下结构体定义
typedef struct
{
    DH_Uint32                       format;             // 音视频编码格式，参见DHOP_STREAM_Format
    DH_Uint32                       seq;                // 帧序号，通过帧序号的连续性可以判定是否丢帧
    DH_Uint32                       timestamp;          // 当前数据包的数据源采集时间戳，能和DHOP_YUV_FrameData 或DHOP_YUV_FrameData2 中的yuvStamp字段匹配
    DH_DateTime                     time;               // 当前帧的绝对日期和时间，若msec返回0xffff，则表示只能精确到秒
    DH_Uint32                       resWord[5];         // 保留字段
    union
    {
        struct
        {
            DH_Uint32               chnl;               // 音频通道号
            DH_Uint32               frequency;          // 采样率，Hz为单位，比如44100Hz
            DH_Uint8                depth;              // 采样位深，支持8位，16位
            DH_Uint8                resByte[3];         // 保留字段
            DH_Uint32               mode;               // 工作模式，单声道/立体声，参见DHOP_STREAM_AudioMode
        } audio;
        struct
        {
            DH_Uint16               width;              // 图像宽度
            DH_Uint16               height;             // 图像高度
            float                   fps;                // 帧率
            DH_Uint32               frameType;          // I/P/B帧，参见DHOP_STREAM_FrameType
        } video;
        struct
        {
            DH_Uint16               width;              // 图像宽度
            DH_Uint16               height;             // 图像高度
        } picture;
        DH_Uint32                   res1[8];            // 保留字段
    } desc;
    DH_Uint32                       packetSize;         // 音视频流数据包大小
    DH_Uint8*                       packetData;         // 音视频流数据，由接口内部填写，调用DHOP_STREAM_releasePacket接口释放
    DH_Uint32                       reserved[8];        // 保留字段
} DHOP_STREAM_Packet; //数据包

typedef struct
{
    DH_Uint32                       equipId;            // 设备号，应与DHOP_STREAM_getChannelN接口填入的设备号一致
    DH_Uint32                       chnl;               // 通道号，应与DHOP_STREAM_getChnStreamNum接口填入的通道号一致
    DH_Uint32                       strm;               // 码流号，参见DHOP_STREAM_Stream
    DH_Uint16                       mediaType;          // 媒体数据类型，参见DHOP_STREAM_MediaType
    DH_Uint16                       res;                // 保留字段

    /*
    当打开的数据为历史存储录像，begin,end 指定待打开的录像时间段，
    当begin<=end 时，表示正向读取；当begin>end 时，表示倒向读取。
    如果期望打开的是实时录像，begin和end请填写为NULL。
    */
    DHOP_STREAM_TimeStamp           *begin;             // 录像查询的起始时间
    DHOP_STREAM_TimeStamp           *end;               // 录像查询的结束时间

    DHOP_STREAM_Option              *option;            // 可选项
    DH_Uint32                       reserved[7];        // 保留字段
} DHOP_STREAM_OpenParam; // 打开码流信息描述

#endif

#if (__SIZEOF_POINTER__ == 8)           // 64位系统下结构体定义
typedef struct
{
    DH_Uint32                       format;             // 音视频编码格式，参见DHOP_STREAM_Format
    DH_Uint32                       seq;                // 帧序号，通过帧序号的连续性可以判定是否丢帧
    DH_Uint32                       timestamp;          // 当前数据包的数据源采集时间戳，能和DHOP_YUV_FrameData 或DHOP_YUV_FrameData2 中的yuvStamp字段匹配
    DH_DateTime                     time;               // 当前帧的绝对日期和时间，若msec一直返回为0，则表示只能精确到秒
    DH_Uint32                       resWord[5];         // 保留字段
    union
    {
        struct
        {
            DH_Uint32               chnl;               // 音频通道号
            DH_Uint32               frequency;          // 采样率，Hz为单位，比如44100Hz
            DH_Uint8                depth;              // 采样位深，支持8位，16位
            DH_Uint8                resByte[3];         // 保留字段
            DH_Uint32               mode;               // 工作模式，单声道/立体声，参见DHOP_STREAM_AudioMode
        } audio;
        struct
        {
            DH_Uint16               width;              // 图像宽度
            DH_Uint16               height;             // 图像高度
            float                   fps;                // 帧率
            DH_Uint32               frameType;          // I/P/B帧，参见DHOP_STREAM_FrameType
        } video;
        struct
        {
            DH_Uint16               width;              // 图像宽度
            DH_Uint16               height;             // 图像高度
        } picture;
        DH_Uint32                   res1[8];            // 保留字段
    } desc;
    DH_Uint32                       packetSize;         // 音视频流数据包大小
    DH_Uint32                       res2;               // 保留字段
    DH_Uint8                        *packetData;        // 音视频流数据。由接口内部填写，调用DHOP_STREAM_releasePacket接口释放
    DH_Uint32                       reserved[8];        // 保留字段
}DHOP_STREAM_Packet; //数据包

typedef struct
{
    DH_Uint32                       equipId;            // 设备号，应与DHOP_STREAM_getChannelN接口填入的设备号一致
    DH_Uint32                       chnl;               // 通道号，应与DHOP_STREAM_getChnStreamNum接口填入的通道号一致
    DH_Uint32                       strm;               // 码流号，参见DHOP_STREAM_Stream
    DH_Uint16                       mediaType;          // 媒体数据类型，参见DHOP_STREAM_MediaType
    DH_Uint16                       res;                // 保留字段

    /*
    当打开的数据为历史存储录像，begin,end 指定待打开的录像时间段，
    当begin<=end 时，表示正向读取；当begin>end 时，表示倒向读取。
    如果期望打开的是实时录像，begin和end请填写为NULL。
    */
    DHOP_STREAM_TimeStamp           *begin;             // 录像查询的起始时间
    DHOP_STREAM_TimeStamp           *end;               // 录像查询的结束时间

    DHOP_STREAM_Option              *option;            // 可选项
    DH_Uint32                       reserved[7];        // 保留字段
} DHOP_STREAM_OpenParam; // 打开码流信息描述

#endif

/*******************************************************************************/

/*******************************************************************************
* function name : DHOP_STREAM_getChannelNum
*
* description   : 获取设备支持的视频流通道数，在DHOP环境中音频作为视频的附加数据提供，
*                 所以音频在“流”的概念范畴中，不提供单独的通道。
*
* input         : equipId    -- 设备编号，无特殊需求填写0，表示当前设备，特殊产品详见手册
*
* output        : chnlNum    -- 获得当前设备号的通道数量
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : DHOP_ERR_EQUIPMENT_NOT_EXIST - 编号equipId设备不存在
*               : DHOP_ERR_PARAM_IS_NULL - chnlNum是NULL
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_STREAM_getChannelNum(DH_Uint32 equipId, DH_Uint32 *chnlNum);


/*******************************************************************************
* function name : DHOP_STREAM_getChnStreamNum
*
* description   : 获取设备指定视频通道支持的码流数，在DHOP环境中音频作为视频的附加数据提供，
*                 所以音频在“流”的概念范畴中，不提供单独的通道。
*
* input         : equipId    -- 设备编号，调用者无特殊需求填写0，表示当前设备
*                 chnl       -- 设备通道号，取值范围为[0 ~ chnlNum-1]，
*                               调用者根据DHOP_STREAM_getChannelNum接口的chnlNum确定总数
*
* output        : strmNum    -- 码流数量
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS: success
*               : DHOP_FAILED:  fail
*               : DHOP_ERR_EQUIPMENT_NOT_EXIST - 编号equipId设备不存在
*               : DHOP_ERR_OUT_OF_RANGE - chnl的通道号超出范围
*               : DHOP_ERR_PARAM_IS_NULL - strmNum是NULL
*               : 其它 - ref DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_STREAM_getChnStreamNum(DH_Uint32 equipId, DH_Uint32 chnl, DH_Uint32 *strmNum);


/*******************************************************************************
* function name : DHOP_STREAM_open
*
* description   : 打开音视频码流，在DHOP环境中音频作为视频的附加数据提供，所以音频在“流”的
*                 概念范畴中，不提供单独的通道。
*                 如果要指定打开音频，在这里指打开指定视频流中的附加音频。
*
* input         : param     -- 需要打开的码流参数，由调用者填写
*                 填写时请参见DHOP_STREAM_OpenParam
*
* output        : hStream   -- 码流操作句柄
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. open成功后返回有效的stream操作句柄
*                    每个app只能打开一次同一路流
*                 4.获取到的操作句柄仅在同进程内有效
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : DHOP_ERR_PARAM_IS_NULL - param或hStream是NULL
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_STREAM_open(DHOP_STREAM_OpenParam *param, DHOP_STREAM_Handle *hStream);


/*******************************************************************************
* function name : DHOP_STREAM_close
*
* description   : 关闭码流
*
* input         : hStream       -- 码流操作句柄，通过DHOP_STREAM_open打开
*
* output        : None
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. close成功后关闭当前流
*                    不能重复关闭
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : DHOP_ERR_PARAM_IS_NULL - hStream是NULL
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_STREAM_close(DHOP_STREAM_Handle *hStream);


/*******************************************************************************
* function name : DHOP_STREAM_getPacket
*
* description   : 获取码流数据
*
* input         : hStream       -- 码流操作句柄，通过DHOP_STREAM_open打开
*
* output        : packet        -- 码流数据
*
*notice        : 1. 线程安全
*                2. 支持多线程调用
*                   超时时间通过open时传入的option timeoutMs决定
*                   缓存时间通过open时传入的option preRecord决定
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : DHOP_ERR_INVALID_HANDLE - hStream是无效的码流操作句柄
*               : DHOP_ERR_PARAM_IS_NULL - packet是NULL
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_STREAM_getPacket(DHOP_STREAM_Handle hStream, DHOP_STREAM_Packet *packet);


/*******************************************************************************
* function name : DHOP_STREAM_releasePacket
*
* description   : 释放码流内存
*
* input         : hStream       -- 码流操作句柄，通过DHOP_STREAM_open打开
*               : packet        -- 码流数据，由DHOP_STREAM_getPacket接口获得
*
* output        : None
*
*notice        : 1. 线程安全
*                2. 支持多线程调用
*                3. 不可重复对同一个packet多次调用
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : DHOP_ERR_INVALID_HANDLE - hStream是无效的码流操作句柄
*               : DHOP_ERR_PARAM_IS_NULL - packet是NULL
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_STREAM_releasePacket(DHOP_STREAM_Handle hStream, DHOP_STREAM_Packet *packet);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_STREAM_H__


