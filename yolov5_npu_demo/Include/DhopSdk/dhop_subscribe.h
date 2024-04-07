/*******************************************************************************
 * dhop_subscribe.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: APP订阅消息的相关定义。
 *
 *******************************************************************************/

#ifndef __DHOP_SUBSCRIBE_H__
#define __DHOP_SUBSCRIBE_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
#include "dhop_type_def.h"
/*******************************************************************************/

/* APP订阅的事件类型 */
typedef enum
{
    DHOP_SUBSC_EVT_ALARMLOCAL = 1,                         /// 本地报警事件

    DHOP_SUBSC_EVT_STORAGE_NOEXIST,                        /// 存储盘不存在事件
    DHOP_SUBSC_EVT_STORAGE_LOWSPACE,                       /// 存储盘空间不足事件
    DHOP_SUBSC_EVT_STORAGE_FAILURE,                        /// 存储盘出错事件
    DHOP_SUBSC_EVT_LICENSE_UPDATE,                         /// 算法证书更新事件

    DHOP_SUBSC_EVT_MAX,                                    /// 无效值,枚举界限
} DHOP_SUBSC_EVT_Type;

/****************************************************************/

/*
    功能: 接收处理订阅事件的回调函数。当用户订阅的事件发生时，触发该回调
    参数: type        -- <in>   事件类型
    参数: evtJson     -- <in>   事件描述,json文本格式,具体格式参考用户手册
    参数: evtSize     -- <in>   事件描述的长度
    返回值: < 0: 处理失败. = 0： 处理成功
*/
typedef DH_Int32(*DHOP_SUBSC_onEvtNotify)(DHOP_SUBSC_EVT_Type type, DH_String evtJson, DH_Uint32 evtSize);

/***************************************************************
* function name : DHOP_SUBSC_startListenEvt
*
* description   : 订阅指定的事件类型
*
* input         : type:   订阅的事件类型
*               : proc:   事件通知回调
*
* output        : none
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SUBSC_startListenEvt(DHOP_SUBSC_EVT_Type type, DHOP_SUBSC_onEvtNotify proc);

/***************************************************************
* function name : DHOP_SUBSC_stopListenEvt
*
* description   : 取消订阅指定的事件类型
*
* input         : type:   取消订阅的事件类型
*
* output        : none
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SUBSC_stopListenEvt(DHOP_SUBSC_EVT_Type type);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __DHOP_SUBSCRIBE_H__
