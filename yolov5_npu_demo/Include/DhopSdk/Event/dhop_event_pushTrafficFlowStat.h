/*******************************************************************************
* dhop_event_pushTrafficFlowStat.h
*
* Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
*
* Description: 推送车辆流量事件信息。
*
*******************************************************************************/

#ifndef __DHOP_EVENT_PUSHTRAFFICFLOWSTAT_H__
#define __DHOP_EVENT_PUSHTRAFFICFLOWSTAT_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
#include "dhop_event_common.h"
/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)           // 32位系统下结构体定义
/// 车流量信息
typedef struct
{
    ///1: 流量过大(拥堵)
    ///2: 流量过大恢复(略堵)
    ///3: 正常
    ///4: 流量过小(通畅)
    ///5: 流量过小恢复(良好)
    DH_Uint32             state;                                  ///流量状态
    DH_Uint32             lane;                                   ///车道号
    DH_Uint32             flow;                                   ///流量值，单位：辆
    DH_Uint32             period;                                 ///流量值对应的统计时间，分钟
    DH_Float64            timeOccupyRatio;                        /// 时间占有率
    DH_Float64            spaceOccupyRatio;                       /// 空间占有率
    DH_Uint32             res[8];
}DHOP_EVT_FlowState;

/// 车辆流量事件信息
typedef struct
{
    DH_Byte               name[DHOP_EVT_NAME_LEN];                 /// 事件名称
    DH_Uint16             channel;                                 /// 事件通道号,默认为0
    DH_Uint16             state;                                   /// 事件状态，定义参见DHOP_EVT_State
    DH_Uint32             eventId;                                 /// 事件编号，标识事件的唯一性
    DH_Uint32             utc;                                     /// 事件发生时间，秒
    DH_Uint32             utcms;                                   /// 事件发生时间，毫秒
    DH_Uint32             ruleId;                                  /// 事件触发规则编号
    DH_Uint32             res0;                                    ///
    DH_Uint64             pts;                                     /// 相对事件时间戳，毫秒
    DHOP_EVT_FlowState    flowInfo;                                /// 流量信息
    DHOP_EVT_PicInfo      picInfo;                                 /// 事件图片,picType:0-原始图
    DHOP_EVT_Handler      *handler;                                /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32             res[16];
}DHOP_EVT_TrafficFlowStat;
#endif

#if (__SIZEOF_POINTER__ == 8)                // 64位系统下结构体定义
/// 车流量信息
typedef struct
{
    /// 1: 流量过大(拥堵)
    /// 2: 流量过大恢复(略堵)
    /// 3: 正常
    /// 4: 流量过小(通畅)
    /// 5: 流量过小恢复(良好)
    DH_Uint32             state;                                  ///流量状态
    DH_Uint32             lane;                                   ///车道号
    DH_Uint32             flow;                                   ///流量值，单位：辆
    DH_Uint32             period;                                 ///流量值对应的统计时间，分钟
    DH_Float64            timeOccupyRatio;                        /// 时间占有率
    DH_Float64            spaceOccupyRatio;                       /// 空间占有率
    DH_Uint32             res[8];
}DHOP_EVT_FlowState;

/// 车辆流量事件信息
typedef struct
{
    DH_Byte               name[DHOP_EVT_NAME_LEN];                 /// 事件名称
    DH_Uint16             channel;                                 /// 事件通道号,默认为0
    DH_Uint16             state;                                   /// 事件状态，定义参见DHOP_EVT_State
    DH_Uint32             eventId;                                 /// 事件编号，标识事件的唯一性
    DH_Uint32             utc;                                     /// 事件发生时间，秒
    DH_Uint32             utcms;                                   /// 事件发生时间，毫秒
    DH_Uint32             ruleId;                                  /// 事件触发规则编号
    DH_Uint32             res0;                                    ///
    DH_Uint64             pts;                                     /// 相对事件时间戳，毫秒
    DHOP_EVT_FlowState    flowInfo;                                /// 流量信息
    DHOP_EVT_PicInfo      picInfo;                                 /// 事件图片,picType:0-原始图
    DHOP_EVT_Handler      *handler;                                /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32             res[16];
}DHOP_EVT_TrafficFlowStat;
#endif

/***************************************************************
* function name : DHOP_EVT_pushTrafficFlowStat
*
* description   : 推送车辆流量事件信息
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
DH_Int32 DHOP_EVT_pushTrafficFlowStat(const DHOP_EVT_TrafficFlowStat *infos, DH_Uint32 num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __DHOP_EVENT_PUSHTRAFFICFLOWSTAT_H__
