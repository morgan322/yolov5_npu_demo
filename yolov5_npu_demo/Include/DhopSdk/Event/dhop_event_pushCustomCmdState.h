/*******************************************************************************
* dhop_event_pushCustomCmdState.h
*
* Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
*
* Description: 推送自定义信令状态事件。
*
*******************************************************************************/

#ifndef __DHOP_EVENT_PUSHCUSTOMCMDSTATE_H__
#define __DHOP_EVENT_PUSHCUSTOMCMDSTATE_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
#include "dhop_event_common.h"
/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)           // 32位系统下结构体定义
/// 自定义升级状态
typedef struct
{
    DH_Byte                 state[DHOP_EVT_CUSTOMUP_STATE_LEN]; /// 升级状态
    DH_Uint32               progress;                           /// 升级进度
    DH_Uint32               res[7];
} DHOP_EVT_CustomUpState;

/// 自定义信令状态事件
typedef struct
{
    DH_Byte                 type[DHOP_EVT_CUSTOMCMD_TYPE_LEN];  /// 自定义信令名称
    DH_Byte                 uuid[DHOP_EVT_CUSTOMCMD_UUID_LEN];  /// 信令uuid
    union
    {
        DHOP_EVT_CustomUpState  state;                          /// 自定义升级状态
        DH_Uint32               res[16];
    }                       detail;                             /// 信令状态详情
} DHOP_EVT_CustomCmdState;
#endif

#if (__SIZEOF_POINTER__ == 8)                // 64位系统下结构体定义
/// 自定义升级状态
typedef struct
{
    DH_Byte                 state[DHOP_EVT_CUSTOMUP_STATE_LEN]; /// 升级状态
    DH_Uint32               progress;                           /// 升级进度
    DH_Uint32               res[7];
} DHOP_EVT_CustomUpState;

/// 自定义信令状态事件
typedef struct
{
    DH_Byte                 type[DHOP_EVT_CUSTOMCMD_TYPE_LEN];  /// 自定义信令名称
    DH_Byte                 uuid[DHOP_EVT_CUSTOMCMD_UUID_LEN];  /// 信令uuid
    union
    {
        DHOP_EVT_CustomUpState  state;                          /// 自定义升级状态
        DH_Uint32               res[16];
    }                       detail;                             /// 信令状态详情
} DHOP_EVT_CustomCmdState;
#endif

/***************************************************************
* function name : DHOP_EVT_pushCustomCmdState
*
* description   : 推送自定义信令状态事件
*
* input         : state:  自定义信令状态
*
* output        : none
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_EVT_pushCustomCmdState(const DHOP_EVT_CustomCmdState *state);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __DHOP_EVENT_PUSHCUSTOMCMDSTATE_H__
