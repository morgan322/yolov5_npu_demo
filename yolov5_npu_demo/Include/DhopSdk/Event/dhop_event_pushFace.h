/*******************************************************************************
* dhop_event_pushFace.h
*
* Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
*
* Description: 推送人脸事件。
*
*******************************************************************************/

#ifndef __DHOP_EVENT_PUSHFACE_H__
#define __DHOP_EVENT_PUSHFACE_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
#include "dhop_event_common.h"
/*******************************************************************************/

/// 表情状态
typedef enum
{
    DHOP_EVENT_EMOTION_UNKNOWN,                             /// 未知
    DHOP_EVENT_EMOTION_SMILE,                               /// 微笑
    DHOP_EVENT_EMOTION_ANGER,                               /// 愤怒
    DHOP_EVENT_EMOTION_SADNESS,                             /// 悲伤
    DHOP_EVENT_EMOTION_DISGUST,                             /// 厌恶
    DHOP_EVENT_EMOTION_FEAR,                                /// 害怕
    DHOP_EVENT_EMOTION_SURPRISE,                            /// 惊讶
    DHOP_EVENT_EMOTION_NEUTRAL,                             /// 正常
    DHOP_EVENT_EMOTION_LAUGH,                               /// 大笑
    DHOP_EVENT_EMOTION_HAPPY,                               /// 高兴
    DHOP_EVENT_EMOTION_CONFUSED,                            /// 困惑
    DHOP_EVENT_EMOTION_SCREAM,                              /// 尖叫
} DHOP_EVENT_EMOTION;

#if (__SIZEOF_POINTER__ == 4)           // 32位系统下结构体定义
/// 人脸属性
typedef struct
{
    DH_Uint32               id;                             /// 目标id
    DHOP_EVT_Point          center;                         /// 目标中心点
    DHOP_EVT_Rect           box;                            /// 目标框
    DH_Uint8                sex;                            /// 0: 未知,1:男,2:女
    DH_Uint8                age;                            /// 0: 未知
    DH_Uint8                argFS;                          /// 0: 未识别,1: 黄色的,2: 黑色的,3: 白色的
    DH_Uint8                eye;                            /// 0: 未做识别,1: 闭眼,2: 睁眼
    DH_Uint8                mouth;                          /// 0: 未做识别,1: 闭嘴,2: 张嘴
    DH_Uint8                mask;                           /// 0: 未做识别,1: 不戴口罩,2: 戴口罩
    DH_Uint8                beard;                          /// 0: 未识别,1: 没胡子,2: 有胡子
    DH_Uint8                attractive;                     /// 0: 未识别,识别时范围1-100,得分高魅力高
    DH_Uint8                nation;                         /// 0: 未识别
    DH_Uint8                glass;                          /// 0: 未知,1:未戴,2:戴常规眼镜,3:戴太阳镜,4: 戴黑框眼镜
    DH_Uint8                strabismus;                     /// 0: 未知,1:正常,2:斜视
    DH_Uint8                emotion;                        /// 表情状态，定义参见DHOP_EVENT_EMOTION
    DH_Uint8                res[4];
    DH_Uint32               res1[16];
} DHOP_EVT_FaceAttr;

/// 人脸事件信息
typedef struct
{
    DH_Byte                 name[DHOP_EVT_NAME_LEN];        /// 事件名称，用户自定义
    DH_Uint16               state;                          /// 事件状态，定义参见DHOP_EVT_State,人脸事件请使用DHOP_EVT_Start/DHOP_EVT_Stop.
    DH_Uint16               channel;                        /// 事件事件通道号,默认为0
    DH_Uint32               id;                             /// 事件编号,标识事件的唯一性
    DH_Int32                groupId;                        /// 事件组ID，一个事件对应的一组图片,组id相同
    DH_Int16                countInGroup;                   /// 事件对应的一组图片的总数
    DH_Int16                indexInGroup;                   /// 本次图片在组中的序号,从1开始
    DH_Uint32               utc;                            /// 事件的本地时间,秒
    DH_Uint32               utcms;                          /// 事件的本地事件,毫秒
    DH_Uint32               picType;                        /// 0-普通 1-合成 2-抠图
    DH_Uint32               picSize;                        /// 事件图片数据大小
    DH_Uint8                *picData;                       /// 事件图片数据(标准JPEG数据)
    DHOP_EVT_FaceAttr       *picAttr;                       /// 事件人脸小图对应的属性,人脸大图不需要填此字段
    DHOP_EVT_Handler        *handler;                       /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32               res[15];
} DHOP_EVT_FaceInfo;
#endif

#if (__SIZEOF_POINTER__ == 8)                // 64位系统下结构体定义
/// 人脸属性
typedef struct
{
    DH_Uint32               id;                             /// 目标id
    DHOP_EVT_Point          center;                         /// 目标中心点
    DHOP_EVT_Rect           box;                            /// 目标框
    DH_Uint8                sex;                            /// 0: 未知,1:男,2:女
    DH_Uint8                age;                            /// 0: 未知
    DH_Uint8                argFS;                          /// 0: 未识别,1: 黄色的,2: 黑色的,3: 白色的
    DH_Uint8                eye;                            /// 0: 未做识别,1: 闭眼,2: 睁眼
    DH_Uint8                mouth;                          /// 0: 未做识别,1: 闭嘴,2: 张嘴
    DH_Uint8                mask;                           /// 0: 未做识别,1: 不戴口罩,2: 戴口罩
    DH_Uint8                beard;                          /// 0: 未识别,1: 没胡子,2: 有胡子
    DH_Uint8                attractive;                     /// 0: 未识别,识别时范围1-100,得分高魅力高
    DH_Uint8                nation;                         /// 0: 未识别
    DH_Uint8                glass;                          /// 0: 未知,1:未戴,2:戴常规眼镜,3:戴太阳镜,4: 戴黑框眼镜
    DH_Uint8                strabismus;                     /// 0: 未知,1:正常,2:斜视
    DH_Uint8                emotion;                        /// 表情状态，定义参见DHOP_EVENT_EMOTION
    DH_Uint8                res[4];
    DH_Uint32               res1[17];
} DHOP_EVT_FaceAttr;

/// 人脸事件信息
typedef struct
{
    DH_Byte                 name[DHOP_EVT_NAME_LEN];        /// 事件名称，用户自定义
    DH_Uint16               state;                          /// 事件状态，定义参见DHOP_EVT_State,人脸事件请使用DHOP_EVT_Start/DHOP_EVT_Stop.
    DH_Uint16               channel;                        /// 事件事件通道号,默认为0
    DH_Uint32               id;                             /// 事件编号,标识事件的唯一性
    DH_Int32                groupId;                        /// 事件组ID，一个事件对应的一组图片,组id相同
    DH_Int16                countInGroup;                   /// 事件对应的一组图片的总数
    DH_Int16                indexInGroup;                   /// 本次图片在组中的序号,从1开始
    DH_Uint32               utc;                            /// 事件的本地时间,秒
    DH_Uint32               utcms;                          /// 事件的本地事件,毫秒
    DH_Uint32               picType;                        /// 0-普通 1-合成 2-抠图
    DH_Uint32               picSize;                        /// 事件图片数据大小
    DH_Uint8                *picData;                       /// 事件图片数据(标准JPEG数据)
    DHOP_EVT_FaceAttr       *picAttr;                       /// 事件人脸小图对应的属性,人脸大图不需要填此字段
    DHOP_EVT_Handler        *handler;                       /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32               res[14];
} DHOP_EVT_FaceInfo;
#endif

/***************************************************************
* function name : DHOP_EVT_pushFace
*
* description   : 推送人脸大小图事件(发送给通过Dahua标准接入协议接入的订阅者)
*
* input         : infos:  事件列表
*               : num:    事件个数
*
* output        : none
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_EVT_pushFace(const DHOP_EVT_FaceInfo *infos, DH_Uint32 num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __DHOP_EVENT_PUSHFACE_H__
