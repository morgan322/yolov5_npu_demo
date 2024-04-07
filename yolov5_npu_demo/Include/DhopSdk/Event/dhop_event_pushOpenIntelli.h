/*******************************************************************************
* dhop_event_pushOpenIntelli.h
*
* Copyright (C) 2015-2022 ZheJiang Dahua Technology CO.,LTD.
*
* Description: 推送开放智能事件。
*
*******************************************************************************/

#ifndef __DHOP_EVENT_PUSHOPENINTELLI_H__
#define __DHOP_EVENT_PUSHOPENINTELLI_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
#include "dhop_event_common.h"
/*******************************************************************************/

// 开放智能对应的Event Data的类型
typedef enum
{
    DHOP_EVT_OPEN_DATA_JSON = 0,                                            // 透传的JSON数据类型
    DHOP_EVT_OPEN_DATA_STRUCT,                                              // 结构化过的数据类型
} DHOP_EVT_OpenEvtDataType;

#if (__SIZEOF_POINTER__ == 4)                                               // 32位系统下结构体定义

// 开放算法用户数据
typedef struct
{
    DH_Uint16               cbSize;                                         // 结构体大小，由调用者填写
    DH_Uint16               res0;                                           // 预留位
    DH_Int32                alarmId;                                        // 自定义报警id
} DHOP_EVT_UserData;

// 开放算法目标属性
typedef struct
{
    DH_Uint16               cbSize;                                         // 结构体大小，由调用者填写
    DH_Uint16               res0;                                           // 预留位
    DH_Char                 name[DHOP_EVT_OBJECT_ATTRIBUTE_NAME_LEN];       // 属性类型名称
    DH_Char                 value[DHOP_EVT_OBJECT_ATTRIBUTE_VALUE_LEN];     // 属性值名称
} DHOP_EVT_OpenObjectAttr;

// 开放算法检测目标信息
typedef struct
{
    DH_Uint16               cbSize;                                          // 结构体大小，由调用者填写
    DH_Uint16               res0;                                            // 预留位
    DHOP_EVT_Rect           box;                                             // 目标包围盒 矩形类型;8192坐标系
    DH_Char                 name[DHOP_EVT_OBJECT_NAME_LEN];                  // 目标类型名称
    DH_Int32                id;                                              // 目标id
    DH_Uint32               attrCnt;                                         // 目标属性个数
    DHOP_EVT_OpenObjectAttr *attrList;                                       // 目标属性数组
} DHOP_EVT_OpenObject;

// 开放算法某种规则对应的结构化过的Event Data
typedef struct
{
    DH_Uint16               cbSize;                                           // 结构体大小，由调用者填写
    // 当前不需要结构化的定义，建议使用JSON透传, 后续有需要再添加
} DHOP_EVT_OpenEventData;

// 开放智能事件
typedef struct
{
    DH_Uint16               cbSize;                                           // 结构体大小，由调用者填写
    DH_Uint16               state;                                            // 事件状态，定义参见DHOP_EVT_State
    DH_Uint16               channel;                                          // 事件事件通道号,默认为0
    DH_Uint16               evtDataType;                                      // Event Data的类型，参考DHOP_EVT_OpenEvtDataType
    DH_Uint32               objCnt;                                           // 检测到的目标个数
    DH_Uint32               picCnt;                                           // 事件图片个数,picList的个数.
    DH_Char                 algorithmId[DHOP_EVT_ALG_ID_LEN];                 // 所属开放算法的Id
    DH_Char                 algorithmName[DHOP_EVT_ALG_NAME_LEN];             // 所属开放算法的名称
    DH_Char                 ruleName[DHOP_EVT_ALG_RULE_NAME_LEN];             // 所属开放算法的规则名称
    DH_Uint32               jsDataSize;                                       // Event Data(透传的json)的数据大小
    DH_String               pJsEvtData;                                       // ruleName对应的Event Data(透传的json)，DHOP_EVT_OpenEvtDataType为DHOP_EVT_OPEN_DATA_JSON时有效
    DHOP_EVT_OpenEventData* pStEvtData;                                       // ruleName对应的Event Data(结构化的数据)，DHOP_EVT_OpenEvtDataType为DHOP_EVT_OPEN_DATA_STRUCT时有效
    DHOP_EVT_OpenObject     *objList;                                         // 检测到的目标属性信息列表
    DHOP_EVT_PicInfo        *picList;                                         // 事件图片组合列表,picType:0-全景图
    DHOP_EVT_UserData       *userdata;                                        // 开放算法用户数据
    DHOP_EVT_Handler        *handler;                                         // 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32               resv[8];                                          // 预留位
} DHOP_EVT_OpenIntelliInfo;

#endif

#if (__SIZEOF_POINTER__ == 8)                                                 // 64位系统下结构体定义

// 开放算法用户数据
typedef struct
{
    DH_Uint16               cbSize;                                           // 结构体大小，由调用者填写
    DH_Uint16               res0;                                             // 预留位
    DH_Int32                alarmId;                                          // 自定义报警id
} DHOP_EVT_UserData;

// 开放算法目标属性
typedef struct
{
    DH_Uint16               cbSize;                                          // 结构体大小，由调用者填写
    DH_Uint16               res0[3];                                         // 预留位
    DH_Char                 name[DHOP_EVT_OBJECT_ATTRIBUTE_NAME_LEN];        // 属性类型名称
    DH_Char                 value[DHOP_EVT_OBJECT_ATTRIBUTE_VALUE_LEN];      // 属性值名称
} DHOP_EVT_OpenObjectAttr;

// 开放算法检测目标信息
typedef struct
{
    DH_Uint16               cbSize;                                          // 结构体大小，由调用者填写
    DH_Uint16               res0[3];                                         // 预留位
    DHOP_EVT_Rect           box;                                             // 目标包围盒 矩形类型;8192坐标系
    DH_Char                 name[DHOP_EVT_OBJECT_NAME_LEN];                  // 目标类型名称
    DH_Int32                id;                                              // 目标id
    DH_Uint32               attrCnt;                                         // 目标属性个数
    DHOP_EVT_OpenObjectAttr *attrList;                                       // 目标属性数组
} DHOP_EVT_OpenObject;

// 开放算法某种规则对应的结构化过的Event Data
typedef struct
{   
    DH_Uint16               cbSize;                                          // 结构体大小，由调用者填写
    // 当前不需要结构化的定义，建议使用JSON透传, 后续有需要再添加
} DHOP_EVT_OpenEventData;

// 开放智能事件
typedef struct
{
    DH_Uint16               cbSize;                                           // 结构体大小，由调用者填写
    DH_Uint16               state;                                            // 事件状态，定义参见DHOP_EVT_State
    DH_Uint16               channel;                                          // 事件事件通道号,默认为0
    DH_Uint16               evtDataType;                                      // Event Data的类型，参考DHOP_EVT_OpenEvtDataType
    DH_Uint32               objCnt;                                           // 检测到的目标个数
    DH_Uint32               picCnt;                                           // 事件图片个数,picList的个数.
    DH_Char                 algorithmId[DHOP_EVT_ALG_ID_LEN];                 // 所属开放算法的Id
    DH_Char                 algorithmName[DHOP_EVT_ALG_NAME_LEN];             // 所属开放算法的名称
    DH_Char                 ruleName[DHOP_EVT_ALG_RULE_NAME_LEN];             // 所属开放算法的规则名称
    DH_Uint32               jsDataSize;                                       // Event Data(透传的json)的数据大小
    DH_Uint32               res0;                                             // 预留位, 内存对齐
    DH_String               pJsEvtData;                                       // ruleName对应的Event Data(透传的json)，DHOP_EVT_OpenEvtDataType为DHOP_EVT_OPEN_DATA_JSON时有效
    DHOP_EVT_OpenEventData* pStEvtData;                                       // ruleName对应的Event Data(结构化的数据)，DHOP_EVT_OpenEvtDataType为DHOP_EVT_OPEN_DATA_STRUCT时有效
    DHOP_EVT_OpenObject     *objList;                                         // 检测到的目标属性信息列表
    DHOP_EVT_PicInfo        *picList;                                         // 事件图片组合列表,picType:0-全景图
    DHOP_EVT_UserData       *userdata;                                        // 开放算法用户数据
    DHOP_EVT_Handler        *handler;                                         // 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32               resv[8];                                          // 预留位
} DHOP_EVT_OpenIntelliInfo;

#endif

/***************************************************************
* function name : DHOP_EVT_pushOpenIntelli
*
* description   : 推送开放智能事件(发送给通过Dahua标准接入协议接入的订阅者)
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
DH_Int32 DHOP_EVT_pushOpenIntelli(const DHOP_EVT_OpenIntelliInfo *infos, DH_Uint32 num);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __DHOP_EVENT_PUSHOPENINTELLI_H__
