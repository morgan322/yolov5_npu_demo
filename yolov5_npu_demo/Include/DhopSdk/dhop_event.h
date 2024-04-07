/*******************************************************************************
 * dhop_event.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: APP事件上报相关结构的定义。
 *
 *******************************************************************************/

#ifndef __DHOP_EVENT_H__
#define __DHOP_EVENT_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
#include "dhop_type_def.h"
#include "Event/dhop_event_pushCustom.h"
#include "Event/dhop_event_pushCustomCmdState.h"
#include "Event/dhop_event_pushFace.h"
#include "Event/dhop_event_pushHumanTrait.h"
#include "Event/dhop_event_pushVehicle.h"
#include "Event/dhop_event_pushPackBrokenDetection.h"
#include "Event/dhop_event_pushPackLandDetection.h"
#include "Event/dhop_event_pushPackOpenDetection.h"
#include "Event/dhop_event_pushSmokeDetection.h"
#include "Event/dhop_event_pushTrafficFlowStat.h"
#include "Event/dhop_event_pushTrafficParking.h"
#include "Event/dhop_event_pushTrafficRetrograde.h"
#include "Event/dhop_event_pushQueueStayDetection.h"
#include "Event/dhop_event_pushRoadObstacleDetection.h"
#include "Event/dhop_event_pushOpenIntelli.h"

/*******************************************************************************/

/***************************************************************/
/// > null: 老版本符号兼容定义,请勿使用.事件订阅请使用dhop_subscribe.h
typedef enum
{
    DHOP_EVT_ATTACH_ALARMLOCAL = 1,                         /// 本地报警事件
    DHOP_EVT_ATTACH_MAX,                                    /// 无效值,枚举界限
} DHOP_EVT_Type;
typedef DH_Int32(*DHOP_EVT_onEvtNotify)(DHOP_EVT_Type type, DH_String evtJson, DH_Uint32 evtSize);
DH_Int32 DHOP_EVT_subscribe(DHOP_EVT_Type type, DHOP_EVT_onEvtNotify proc);
DH_Int32 DHOP_EVT_unSubscribe(DHOP_EVT_Type type);
/***************************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __DHOP_EVENT_H__
