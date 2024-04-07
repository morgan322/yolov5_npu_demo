/*******************************************************************************
 * dhop_cfg_os.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: app设置到dhop os的相关配置项
 *
 *******************************************************************************/

#ifndef __DHOP_CFG_OS_H__
#define __DHOP_CFG_OS_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"

/*******************************************************************************
* function name : DHOP_OSCFG_setGB28181
*
* description   : 配置国标GB28181接入协议
*
* input         : jsonText  -- Json格式配置内容(json格式详见用户手册)
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS - 成功
*               : 其他  - 失败
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_OSCFG_setGB28181(DH_String jsonText); //VSP_GAYS_SERVER

/*******************************************************************************
* function name : DHOP_OSCFG_setRTMP
*
* description   : 配置RTMP推流信息
*
* input         : jsonText  -- Json格式配置内容(json格式详见用户手册)
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS - 成功
*               : 其他  - 失败
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_OSCFG_setRTMP(DH_String jsonText); //RTMP

/*******************************************************************************
* function name : DHOP_OSCFG_setThermometryRule
*
* description   : 配置测温规则信息
*
* input         : jsonText  -- Json格式配置内容(json格式详见用户手册)
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS - 成功
*               : 其他  - 失败
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_OSCFG_setThermometryRule(DH_String jsonText); //ThermometryRule

/*******************************************************************************
* function name : DHOP_OSCFG_getThermometryRule
*
* description   : 获取测温规则信息
*
* input         : jsonBuf  -- Json格式配置内容,Buffer由调用者准备(json格式详见用户手册)
*               : bufSize  -- 存放配置的buffer大小
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS - 成功
*               : 其他  - 失败
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_OSCFG_getThermometryRule(DH_String jsonBuf, DH_Uint32 bufSize); //ThermometryRule

/*******************************************************************************
* function name : DHOP_OSCFG_setLiveDelay
*
* description   : 设置实时码流延时策略
*
* input         : jsonText  -- Json格式配置内容(json格式详见用户手册)
*                 该接口设置完成后，系统会重启，新时间重启后生效
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS - 成功
*               : 其他  - 失败
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_OSCFG_setLiveDelay(DH_String jsonText);

/*******************************************************************************
* function name : DHOP_OSCFG_setStrobeLight
*
* description   : 设置频闪灯的属性配置
*
* input         : jsonText  -- Json格式配置内容(json格式详见用户手册)
*
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS - 成功
*               : 其他  - 失败
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_OSCFG_setStrobeLight(DH_String jsonText);

/*******************************************************************************
* function name : DHOP_OSCFG_setFlashLamp
*
* description   : 设置爆闪灯的属性配置
*
* input         : jsonText  -- Json格式配置内容(json格式详见用户手册)
*
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS - 成功
*               : 其他  - 失败
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_OSCFG_setFlashLamp(DH_String jsonText);

/*******************************************************************************
* function name : DHOP_OSCFG_setNtp
*
* description   : 设置系统Ntp时间同步服务器配置
*
* input         : jsonText  -- Json格式配置内容(json格式详见用户手册)
*
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS - 成功
*               : 其他  - 失败
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_OSCFG_setNtp(DH_String jsonText);

/*******************************************************************************
* function name : DHOP_OSCFG_setPicOverlay
*
* description   : 设置BMP图片叠加到码流上面
*
* input         : jsonText  -- Json格式配置内容(json格式详见用户手册)，示例如下
*                   {
*                        "EncodeBlend" : true            /// 是否使能图片叠加
*                        "Rect"        : [0,0,1000,1000] /// 图片放入的位置区域,8192相对坐标体系
*                   }
*               : pData     -- bmp图片数据，图片数据不得超过16K
*               : dataSize  -- bmp图片数据大小，图片数据大小不得超过16*1024
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS - 成功
*               : 其他  - 失败
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_OSCFG_setPicOverlay(DH_String jsonText, DH_Char* pData, DH_Uint16 dataSize);

/*******************************************************************************
 * function name : DHOP_OSCFG_setGB28181ExtInfo
 *
 * description   : 配置国标接入扩展信息，需和DHOP_OSCFG_setGB28181配合使用
 *
 * input         : jsonText  -- Json格式配置内容(json格式详见用户手册)，示例如下:
 *                   {
 *                    "sipServer": [{                            /// 服务器信息数组，最大支持5个
 *                           "streamType": {                     /// 码流类型，用于信令中无码流类型时，读取配置中设置的码流类型。
 *                               "liveStreamType": 0,            /// 实时流码流类型。必填项---0：主码流1;辅码流1;2：辅码流2;...
 *                           }
 *                       },…{}]
 *                   }
 *
 * output        : None
 * notice        : 1. 接口线程安全.
 *
 * return value  : DHOP_SUCCESS - 成功
 *               : 其他  - 失败
 *               : 其它         - 参考DHOP_ErrorCode
 *******************************************************************************/
DH_Int32 DHOP_OSCFG_setGB28181ExtInfo(DH_String jsonText); //VSP_GAYS_CUSTOM

/*******************************************************************************
* function name : DH_Int32 DHOP_OSCFG_setBackLightMode(DH_Uint16 chnId, DH_String jsonText);
*
* description   : 设置背光模式，包括背光补偿、强光抑制、宽动态、场景自适应，该接口只在全时模式下生效，调用该接口前，用户需手动在web界面设置工作模式为全时模式
*
* input         : chnId  -- 视频通道号
*               : jsonText  -- Json格式配置内容(json格式详见用户手册)
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS - 成功
*               : 其他  - 失败
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_OSCFG_setBackLightMode(DH_Uint32 chnId, DH_String jsonText);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_CFG_OS_H__


