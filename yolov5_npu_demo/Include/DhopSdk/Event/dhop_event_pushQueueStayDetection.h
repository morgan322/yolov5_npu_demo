/*******************************************************************************
* dhop_event_pushQueueStayDetection.h
*
* Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
*
* Description: 推送排队滞留检测事件。
*
*******************************************************************************/

#ifndef __DHOP_EVENT_PUSHQUEUESTAYDETECTION_H__
#define __DHOP_EVENT_PUSHQUEUESTAYDETECTION_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
#include "dhop_event_common.h"
/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)           // 32位系统下结构体定义
/// 排队滞留检测事件
typedef struct
{
    DH_Byte               name[DHOP_EVT_NAME_LEN];                 /// 事件名称
    DH_Byte               iclass[DHOP_EVT_INTELLI_CLASS_LEN];      /// 智能事件所属大类
    DH_Uint16             channel;                                 /// 事件通道号,默认为0
    DH_Uint16             state;                                   /// 事件状态，定义参见DHOP_EVT_State
    DH_Uint32             groupId;                                 /// 事件组ID，一个事件对应的一组图片,组id相同
    DH_Uint32             countInGroup;                            /// 事件对应的一组图片的总数
    DH_Uint32             indexInGroup;                            /// 本次图片在组中的序号,从1开始
    DH_Uint32             eventId;                                 /// 事件编号，标识事件的唯一性
    DH_Uint32             utc;                                     /// 事件发生时间，秒
    DH_Uint32             utcms;                                   /// 事件发生时间，毫秒
    DH_Uint32             areaId;                                  /// 区域ID
    DH_Uint32             regPointCnt;                             /// 检测区域点个数
    DH_Uint64             pts;                                     /// 相对事件时间戳，毫秒
    DHOP_EVT_PicInfo      picInfo;                                 /// 事件图片组合列表,picType:0-全景图
    DHOP_EVT_Point        *region;                                 /// 检测区域,多边形
    DHOP_EVT_Handler      *handler;                                /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32             res[16];
}DHOP_EVT_QueueStayDetection;
#endif

#if (__SIZEOF_POINTER__ == 8)                // 64位系统下结构体定义
/// 排队滞留检测事件
typedef struct
{
    DH_Byte               name[DHOP_EVT_NAME_LEN];                 /// 事件名称
    DH_Byte               iclass[DHOP_EVT_INTELLI_CLASS_LEN];      /// 智能事件所属大类
    DH_Uint16             channel;                                 /// 事件通道号,默认为0
    DH_Uint16             state;                                   /// 事件状态，定义参见DHOP_EVT_State
    DH_Uint32             groupId;                                 /// 事件组ID，一个事件对应的一组图片,组id相同
    DH_Uint32             countInGroup;                            /// 事件对应的一组图片的总数
    DH_Uint32             indexInGroup;                            /// 本次图片在组中的序号,从1开始
    DH_Uint32             eventId;                                 /// 事件编号，标识事件的唯一性
    DH_Uint32             utc;                                     /// 事件发生时间，秒
    DH_Uint32             utcms;                                   /// 事件发生时间，毫秒
    DH_Uint32             areaId;                                  /// 区域ID
    DH_Uint32             regPointCnt;                             /// 检测区域点个数
    DH_Uint32             res1;
    DH_Uint64             pts;                                     /// 相对事件时间戳，毫秒
    DHOP_EVT_PicInfo      picInfo;                                 /// 事件图片组合列表,picType:0-全景图
    DHOP_EVT_Point        *region;                                 /// 检测区域,多边形
    DHOP_EVT_Handler      *handler;                                /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32             res[16];
}DHOP_EVT_QueueStayDetection;
#endif

/***************************************************************
* function name : DHOP_EVT_pushQueueStayDetection
*
* description   : 排队滞留检测事件
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
DH_Int32 DHOP_EVT_pushQueueStayDetection(const DHOP_EVT_QueueStayDetection *infos, DH_Uint32 num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __DHOP_EVENT_PUSHQUEUESTAYDETECTION_H__
