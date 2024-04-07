/*******************************************************************************
* dhop_event_common.h
*
* Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
*
* Description: DHOP事件公共结构体定义。
*
*******************************************************************************/

#ifndef __DHOP_EVENT_COMMON_H__
#define __DHOP_EVENT_COMMON_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
#include "dhop_type_def.h"
/*******************************************************************************/

#define DHOP_EVT_NAME_LEN                   128
#define DHOP_EVT_ATTR_COUNT                 8
#define DHOP_EVT_MAX_CHANNELS               32
#define DHOP_EVT_CUSTOMUP_STATE_LEN         32
#define DHOP_EVT_CUSTOMCMD_TYPE_LEN         64
#define DHOP_EVT_CUSTOMCMD_UUID_LEN         64
#define DHOP_EVT_INTELLI_CLASS_LEN          16
#define DHOP_EVT_OBJECT_TYPE_LEN            16
#define DHOP_EVT_OBJECT_NAME_LEN            32
#define DHOP_EVT_AUDIO_FILE_NAME_LEN        64
#define DHOP_EVT_ALG_ID_LEN                 32
#define DHOP_EVT_ALG_NAME_LEN               32
#define DHOP_EVT_ALG_RULE_NAME_LEN          32
#define DHOP_EVT_OBJECT_ATTRIBUTE_NAME_LEN  32
#define DHOP_EVT_OBJECT_ATTRIBUTE_VALUE_LEN 32

/// 事件状态
typedef enum
{
    // 有状态事件上报模式
    DHOP_EVT_Start = 1,                                     /// 事件开始
    DHOP_EVT_Update,                                        /// 事件更新,必须在start和stop之间
    DHOP_EVT_Stop,                                          /// 事件结束,开始和结束必须配对

    // 无状态单次触发模式
    DHOP_EVT_Once,                                          /// 事件脉冲，单次事件，和start/stop无关
} DHOP_EVT_State;

/// 警戒灯状态
typedef enum
{
    DHOP_EVT_LIGHT_ON = 1,                                  /// 警戒灯打开
    DHOP_EVT_LIGHT_OFF,                                     /// 警戒灯关闭
    DHOP_EVT_LIGHT_FLICKER,                                 /// 警戒灯闪烁
} DHOP_EVT_LightState;

#if (__SIZEOF_POINTER__ == 4)           // 32位系统下结构体定义
/// 坐标点(8192坐标系)
typedef DH_Point32 DHOP_EVT_Point;

/// 包围框
typedef DH_Rect32  DHOP_EVT_Rect;

/// 音频联动文件信息
typedef struct
{
    DH_Char                 audioName[DHOP_EVT_AUDIO_FILE_NAME_LEN];    /// 音频文件名称
    DH_Uint8                audioId;                                    /// 音频文件编号，用于联动音频，从0开始
    DH_Int8                 res[31];
} DHOP_EVT_AudioInfo;

/// 音频联动项
typedef struct
{
    DH_Uint8                audioEnable;                                /// 是否触发音频联动：0为不触发， 1为触发
    DH_Uint8                audioPlayTimes;                             /// 音频播放次数，从1开始
    DH_Uint8                audioId;                                    /// 音频播放序号，通过DHOP_EVT_getAudioList获取
    DH_Uint8                res[5];
}DHOP_EVT_AudioHandler;

/// 警戒灯联动项
typedef struct
{
    DH_Uint32               lightLatch;                                 /// 警戒灯持续时间，范围[0,3600]，单位：秒
    DH_Float32              lightFlickerInterval;                       /// 闪烁周期，警戒灯为闪烁时才生效，单位为0.1s，最小值为0.1
    DH_Uint8                lightState;                                 /// 设置警戒灯状态：参考DHOP_EVT_LightState
    DH_Uint8                res[7];
}DHOP_EVT_LightHandler;

// 事件联动选项
typedef struct
{
    DH_Uint8                logEnable;                                  /// 是否记录系统日志：0为不记录， 1为记录
    DH_Uint8                mailEnable;                                 /// 是否触发系统邮件：0为不发送，1为发送
    DH_Uint8                alarmEnable;                                /// 是否触发系统报警输出: 0为不触发，1为触发
    DH_Uint8                snapEnable;                                 /// 是否触发系统抓图: 0为不触发，1为触发
    DH_Uint8                recordEnable;                               /// 是否触发系统录像: 0为不触发，1为触发
    DH_Uint8                alarmChnCnt;                                /// 报警输出通道个数:alarmChnList数组使用个数
    DH_Uint8                snapChnCnt;                                 /// 系统抓图通道个数:snapChnList数组使用个数
    DH_Uint8                recordChnCnt;                               /// 系统录像通道个数:recordChnList数组使用个数
    DH_Uint8                alarmChnList[DHOP_EVT_MAX_CHANNELS];        /// 系统报警输出通道列表，从0开始
    DH_Uint8                snapChnList[DHOP_EVT_MAX_CHANNELS];         /// 系统抓图通道列表，从0开始
    DH_Uint8                recordChnList[DHOP_EVT_MAX_CHANNELS];       /// 系统录像通道列表，从0开始
    DH_Uint32               alarmLatch;                                 /// 系统报警输出延时：范围[10,300], 单位：秒
    DH_Uint32               recordLatch;                                /// 系统录像延时：范围[10,300], 单位：秒
    DH_Uint32               snapTimes;                                  /// 系统抓拍次数：0表示持续抓拍，直到事件结束
    DHOP_EVT_AudioHandler   audioHandler;                               /// 音频联动项，请参考DHOP_EVT_AudioHandler
    DHOP_EVT_LightHandler   lightHandler;                               /// 警戒灯联动项，请参考DHOP_EVT_LightHandler
    DH_Uint32               res[27];
} DHOP_EVT_Handler;

/// 事件联动能力
typedef struct
{
    DH_Uint16               cbSize;                                     /// 当前结构体大小，sizeof(DHOP_EVT_HandlerCaps)，调用者必填
    DH_Uint8                alarmOutEnable;                             /// 是否支持联动报警输出
    DH_Uint8                mailEnable;                                 /// 是否支持联动邮件发送
    DH_Uint8                recordEnable;                               /// 是否支持联动系统录像
    DH_Uint8                snapEnable;                                 /// 是否支持联动系统抓图
    DH_Uint8                voiceEnable;                                /// 是否支持联动音频播放
    DH_Uint8                voiceTimesMin;                              /// 音频播放次数范围最小值
    DH_Uint8                voiceTimesMax;                              /// 音频播放次数范围最大值
    DH_Uint8                snapTimesMin;                               /// 系统抓图张数范围最小值.0表示不限制
    DH_Uint8                snapTimesMax;                               /// 系统抓图张数范围最大值.0表示不限制
    DH_Uint8                alarmOutChnCnt;                             /// 报警输出通道数
    DH_Uint8                videoInChnCnt;                              /// 视频输入通道数
    DH_Uint8                res0[3];
    DH_Uint32               alarmOutLatchMin;                           /// 报警输出延时范围最小值
    DH_Uint32               alarmOutLatchMax;                           /// 报警输出延时范围最大值
    DH_Uint32               recordLatchMin;                             /// 系统录像延时范围最小值
    DH_Uint32               recordLatchMax;                             /// 系统录像延时范围最大值
    DH_Uint32               resv[8];
} DHOP_EVT_HandlerCaps;

/// 事件图片信息
typedef struct
{
    DH_Uint32               picType;                        /// 具体值含义由事件描述
    DH_Uint32               picSize;                        /// 图片数据大小
    DH_Uint8                *picData;                       /// 图片数据(标准JPEG数据)
} DHOP_EVT_PicInfo;
#endif

#if (__SIZEOF_POINTER__ == 8)                // 64位系统下结构体定义
/// 坐标点(8192坐标系)
typedef DH_Point32 DHOP_EVT_Point;

/// 包围框
typedef DH_Rect32  DHOP_EVT_Rect;

/// 音频联动文件信息
typedef struct
{
    DH_Char                 audioName[DHOP_EVT_AUDIO_FILE_NAME_LEN];    /// 音频文件名称
    DH_Uint8                audioId;                                    /// 音频文件编号，用于联动音频，从0开始
    DH_Int8                 res[31];
} DHOP_EVT_AudioInfo;

/// 音频联动项
typedef struct
{
    DH_Uint8                audioEnable;                                /// 是否触发音频联动：0为不触发， 1为触发
    DH_Uint8                audioPlayTimes;                             /// 音频播放次数，从1开始
    DH_Uint8                audioId;                                    /// 音频播放序号，通过DHOP_EVT_getAudioList获取
    DH_Uint8                res[5];
}DHOP_EVT_AudioHandler;

/// 警戒灯联动项
typedef struct
{
    DH_Uint32               lightLatch;                                 /// 警戒灯持续时间，范围[0,3600]，单位：秒
    DH_Float32              lightFlickerInterval;                       /// 闪烁周期，警戒灯为闪烁时才生效，单位为0.1s，最小值为0.1
    DH_Uint8                lightState;                                 /// 设置警戒灯状态：参考DHOP_EVT_LightState
    DH_Uint8                res[7];
}DHOP_EVT_LightHandler;

// 事件联动选项
typedef struct
{
    DH_Uint8                logEnable;                                  /// 是否记录系统日志：0为不记录， 1为记录
    DH_Uint8                mailEnable;                                 /// 是否触发系统邮件：0为不发送，1为发送
    DH_Uint8                alarmEnable;                                /// 是否触发系统报警输出: 0为不触发，1为触发
    DH_Uint8                snapEnable;                                 /// 是否触发系统抓图: 0为不触发，1为触发
    DH_Uint8                recordEnable;                               /// 是否触发系统录像: 0为不触发，1为触发
    DH_Uint8                alarmChnCnt;                                /// 报警输出通道个数:alarmChnList数组使用个数
    DH_Uint8                snapChnCnt;                                 /// 系统抓图通道个数:snapChnList数组使用个数
    DH_Uint8                recordChnCnt;                               /// 系统录像通道个数:recordChnList数组使用个数
    DH_Uint8                alarmChnList[DHOP_EVT_MAX_CHANNELS];        /// 系统报警输出通道列表，从0开始
    DH_Uint8                snapChnList[DHOP_EVT_MAX_CHANNELS];         /// 系统抓图通道列表，从0开始
    DH_Uint8                recordChnList[DHOP_EVT_MAX_CHANNELS];       /// 系统录像通道列表，从0开始
    DH_Uint32               alarmLatch;                                 /// 系统报警输出延时：范围[10,300], 单位：秒
    DH_Uint32               recordLatch;                                /// 系统录像延时：范围[10,300], 单位：秒
    DH_Uint32               snapTimes;                                  /// 系统抓拍次数：0表示持续抓拍，直到事件结束
    DHOP_EVT_AudioHandler   audioHandler;                               /// 音频联动项，请参考DHOP_EVT_AudioHandler
    DHOP_EVT_LightHandler   lightHandler;                               /// 警戒灯联动项，请参考DHOP_EVT_LightHandler
    DH_Uint32               res[27];
} DHOP_EVT_Handler;

/// 事件联动能力
typedef struct
{
    DH_Uint16               cbSize;                                     /// 当前结构体大小，sizeof(DHOP_EVT_HandlerCaps)，调用者必填
    DH_Uint8                alarmOutEnable;                             /// 是否支持联动报警输出
    DH_Uint8                mailEnable;                                 /// 是否支持联动邮件发送
    DH_Uint8                recordEnable;                               /// 是否支持联动系统录像
    DH_Uint8                snapEnable;                                 /// 是否支持联动系统抓图
    DH_Uint8                voiceEnable;                                /// 是否支持联动音频播放
    DH_Uint8                voiceTimesMin;                              /// 音频播放次数范围最小值
    DH_Uint8                voiceTimesMax;                              /// 音频播放次数范围最大值
    DH_Uint8                snapTimesMin;                               /// 系统抓图张数范围最小值.0表示不限制
    DH_Uint8                snapTimesMax;                               /// 系统抓图张数范围最大值.0表示不限制
    DH_Uint8                alarmOutChnCnt;                             /// 报警输出通道数
    DH_Uint8                videoInChnCnt;                              /// 视频输入通道数
    DH_Uint8                res0[3];
    DH_Uint32               alarmOutLatchMin;                           /// 报警输出延时范围最小值
    DH_Uint32               alarmOutLatchMax;                           /// 报警输出延时范围最大值
    DH_Uint32               recordLatchMin;                             /// 系统录像延时范围最小值
    DH_Uint32               recordLatchMax;                             /// 系统录像延时范围最大值
    DH_Uint32               resv[8];
} DHOP_EVT_HandlerCaps;

/// 事件图片信息
typedef struct
{
    DH_Uint32               picType;                        /// 具体值含义由事件描述
    DH_Uint32               picSize;                        /// 图片数据大小
    DH_Uint8                *picData;                       /// 图片数据(标准JPEG数据)
} DHOP_EVT_PicInfo;
#endif

/***************************************************************
* function name : DHOP_EVT_getHandlerCaps
*
* description   : 获取当前系统支持的事件联动项
*
* input         : pCaps:  调用者指定的能力结构体
*
* output        : pCaps: 返回的系统支持的事件联动项
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_EVT_getHandlerCaps(DHOP_EVT_HandlerCaps* pCaps);

/***************************************************************
* function name : DHOP_EVT_getAudioList
*
* description   : 获取当前系统支持的音频列表
*
* input         : pInfo:  调用者指定音频信息结构体
*                 num:    调用者获取音频信息数量
*
* output        : pInfo:  返回的系统支持的音频信息
*                 num:    返回实际获取的音频信息
*
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_EVT_getAudioList(DHOP_EVT_AudioInfo* pInfo, DH_Uint32* num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __DHOP_EVENT_COMMON_H__
