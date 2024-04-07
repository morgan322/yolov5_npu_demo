/*******************************************************************************
* dhop_event_pushCustom.h
*
* Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
*
* Description: 推送用户自定义事件。
*
*******************************************************************************/

#ifndef __DHOP_EVENT_PUSHCUSTOM_H__
#define __DHOP_EVENT_PUSHCUSTOM_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
#include "dhop_event_common.h"
/*******************************************************************************/

#define DHOP_EVT_CUSTOMEVENT_CLASS_LEN          32

#if (__SIZEOF_POINTER__ == 4)           // 32位系统下结构体定义
/// APP自定义事件
typedef struct
{
    DH_Byte                 name[DHOP_EVT_NAME_LEN];        /// 用户自定义 ,可用于事件名称，或者规则名称
    DH_Uint16               state;                          /// 事件状态，定义参见DHOP_EVT_State
    DH_Uint16               channel;                        /// 事件事件通道号,默认为0
    DH_Uint32               id;                             /// 事件编号,标识事件的唯一性
    DH_Uint32               utc;                            /// 事件的本地时间,秒
    DH_Uint32               utcms;                          /// 事件的本地事件,毫秒
    DH_Uint32               srcIdx;                         /// 事件触发源ID
    DH_String               data;                           /// 用户自定义数据(ASCII编码字符串),以0为结束符,最大2048
    DH_Uint32               dataSize;                       /// 用户自定义数据大小
    DH_Uint8                *picData;                       /// 事件图片数据(标准JPEG数据)，选填
    DH_Uint32               picSize;                        /// 事件图片数据大小，选填
    DHOP_EVT_Handler        *handler;                       /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint64               pts;                            /// 事件相对时间戳
    DH_Byte                 iclass[DHOP_EVT_CUSTOMEVENT_CLASS_LEN];/// 事件所属类别
    DH_Uint32               res[22];
} DHOP_EVT_CustomInfo;
#endif

#if (__SIZEOF_POINTER__ == 8)                // 64位系统下结构体定义
/// APP自定义事件
typedef struct
{
    DH_Byte                 name[DHOP_EVT_NAME_LEN];        /// 用户自定义 ,可用于事件名称，或者规则名称
    DH_Uint16               state;                          /// 事件状态，定义参见DHOP_EVT_State
    DH_Uint16               channel;                        /// 事件事件通道号,默认为0
    DH_Uint32               id;                             /// 事件编号,标识事件的唯一性
    DH_Uint32               utc;                            /// 事件的本地时间,秒
    DH_Uint32               utcms;                          /// 事件的本地事件,毫秒
    DH_Uint32               srcIdx;                         /// 事件触发源ID
    DH_String               data;                           /// 用户自定义数据(ASCII编码字符串),以0为结束符,最大2048
    DH_Uint32               dataSize;                       /// 用户自定义数据大小
    DH_Uint8                *picData;                       /// 事件图片数据(标准JPEG数据)，选填
    DH_Uint32               picSize;                        /// 事件图片数据大小，选填
    DHOP_EVT_Handler        *handler;                       /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint64               pts;                            /// 事件相对时间戳
    DH_Byte                 iclass[DHOP_EVT_CUSTOMEVENT_CLASS_LEN];/// 事件所属类别
    DH_Uint32               res[22];
} DHOP_EVT_CustomInfo;
#endif

/***************************************************************
* function name : DHOP_EVT_pushCustom
*
* description   : 推送用户自定义事件(发送给通过Dahua标准接入协议接入的订阅者)
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
DH_Int32 DHOP_EVT_pushCustom(const DHOP_EVT_CustomInfo *infos, DH_Uint32 num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __DHOP_EVENT_PUSHCUSTOM_H__
