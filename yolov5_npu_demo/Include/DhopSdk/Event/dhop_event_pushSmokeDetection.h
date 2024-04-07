/*******************************************************************************
* dhop_event_pushSmokeDetection.h
*
* Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
*
* Description: 推送烟雾报警事件信息。
*
*******************************************************************************/

#ifndef __DHOP_EVENT_PUSHSMOKEDETECTION_H__
#define __DHOP_EVENT_PUSHSMOKEDETECTION_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
#include "dhop_event_common.h"
#include "dhop_event_pushVehicle.h"
/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)           // 32位系统下结构体定义
/// 烟雾报警事件信息
typedef struct
{
    DH_Byte               name[DHOP_EVT_NAME_LEN];                 /// 事件名称
    DH_Byte               iclass[DHOP_EVT_INTELLI_CLASS_LEN];      /// 智能事件所属大类, "Normal"
    DH_Uint16             channel;                                 /// 事件通道号,默认为0
    DH_Uint16             state;                                   /// 事件状态，定义参见DHOP_EVT_State
    DH_Uint32             eventId;                                 /// 事件编号，标识事件的唯一性
    DH_Uint32             groupId;                                 /// 事件组ID，一个事件对应的一组图片,组id相同
    DH_Uint32             countInGroup;                            /// 事件对应的一组图片的总数
    DH_Uint32             indexInGroup;                            /// 本次图片在组中的序号,从1开始
    DH_Uint32             utc;                                     /// 事件发生时间，秒
    DH_Uint32             utcms;                                   /// 事件发生时间，毫秒
    DH_Uint32             ruleId;                                  /// 事件触发规则编号
    DH_Uint64             pts;                                     /// 相对事件时间戳，毫秒
    DHOP_EVT_PicInfo      picInfo;                                 /// 事件图片组合列表,picType:0-原始图
    DHOP_EVT_VehicleAttr  *vehicleAttr;                            /// 事件目标对应的属性
    DHOP_EVT_Handler      *handler;                                /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32             res[16];
}DHOP_EVT_SmokeDetection;
#endif

#if (__SIZEOF_POINTER__ == 8)                // 64位系统下结构体定义
/// 烟雾报警事件信息
typedef struct
{
    DH_Byte               name[DHOP_EVT_NAME_LEN];                 /// 事件名称
    DH_Byte               iclass[DHOP_EVT_INTELLI_CLASS_LEN];      /// 智能事件所属大类, "Normal"
    DH_Uint16             channel;                                 /// 事件通道号,默认为0
    DH_Uint16             state;                                   /// 事件状态，定义参见DHOP_EVT_State
    DH_Uint32             eventId;                                 /// 事件编号，标识事件的唯一性
    DH_Uint32             groupId;                                 /// 事件组ID，一个事件对应的一组图片,组id相同
    DH_Uint32             countInGroup;                            /// 事件对应的一组图片的总数
    DH_Uint32             indexInGroup;                            /// 本次图片在组中的序号,从1开始
    DH_Uint32             utc;                                     /// 事件发生时间，秒
    DH_Uint32             utcms;                                   /// 事件发生时间，毫秒
    DH_Uint32             ruleId;                                  /// 事件触发规则编号
    DH_Uint64             pts;                                     /// 相对事件时间戳，毫秒
    DHOP_EVT_PicInfo      picInfo;                                 /// 事件图片组合列表,picType:0-原始图
    DHOP_EVT_VehicleAttr  *vehicleAttr;                            /// 事件目标对应的属性
    DHOP_EVT_Handler      *handler;                                /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32             res[16];
}DHOP_EVT_SmokeDetection;
#endif

/***************************************************************
* function name : DHOP_EVT_pushSmokeDetection
*
* description   : 推送烟雾报警事件信息
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
DH_Int32 DHOP_EVT_pushSmokeDetection(const DHOP_EVT_SmokeDetection *infos, DH_Uint32 num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __DHOP_EVENT_PUSHSMOKEDETECTION_H__
