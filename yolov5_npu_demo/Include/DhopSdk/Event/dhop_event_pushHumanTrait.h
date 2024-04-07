/*******************************************************************************
* dhop_event_pushHumanTrait.h
*
* Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
*
* Description: 推送人员检测事件。
*
*******************************************************************************/

#ifndef __DHOP_EVENT_PUSHHUMANTRAIT_H__
#define __DHOP_EVENT_PUSHHUMANTRAIT_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
#include "dhop_event_common.h"
#include "dhop_event_pushFace.h"
/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)           // 32位系统下结构体定义
/// 人体属性
typedef struct
{
    DH_Uint8                coatColor[16];                  /// 上衣颜色
    DH_Uint8                trousersColor[16];              /// 裤子颜色
    DH_Uint8                coatType;                       /// 0: 未知.1: 长袖.2: 短袖
    DH_Uint8                trousersType;                   /// 0: 未知.1: 长裤.2: 短裤.3: 裙子
    DH_Uint8                hasHat;                         /// 0: 未知.1: 不带帽子.2: 有带帽子
    DH_Uint8                hasBag;                         /// 0: 未知.1: 不带包.2: 带包
    DHOP_EVT_Rect           box;                            /// 包围盒
    DHOP_EVT_Point          center;                         /// 物体型心
    DH_Uint8                angle;                          /// 0: 未知.1: – 正面（前面）.2: – 侧面（旁边）.3: – 背面（后面）
    DH_Uint8                hasUmbrella;                    /// 0: 未知.1: – 未打伞.2: – 打伞
    DH_Uint8                bag;                            /// 0: – 未知.1: – 手提包.2: – 肩包.3: – 背包.4: – 拉杆箱.5: – 斜跨包
    DH_Uint8                backBag;                        /// 0-未识别 1-无 2-有
    DH_Uint8                carrierBag;                     /// 0-未识别 1-无 2-有
    DH_Uint8                shoulderBag;                    /// 0-未识别 1-无 2-有
    DH_Uint8                messengerBag;                   /// 0-未识别 1-无 2-有
    DH_Uint8                upperPattern;                   /// 0: – 未知.1: – 纯色.2: – 条纹.3: – 图案.4: – 缝隙.5: – 格子
    DH_Uint8                hairStyle;                      /// 0: – 未知.1: – 长发.2: – 短发.3: – 马尾.4: – 盘发.5: – 头部被遮挡
    DH_Uint8                cap;                            /// 0: – 未知1: – 普通帽子.2: – 头盔.3: – 安全帽
    DH_Uint8                rainCoat;                       /// 0:-未识别.1:-无 2:-有
    DH_Uint8                holdBaby;                       /// 0:-未识别.1:- 未抱.2:-抱
    DH_Uint8                res[8];
} DHOP_EVT_HumanAttr;

/// 人员检测事件信息
typedef struct
{
    DH_Byte                 name[DHOP_EVT_NAME_LEN];        /// 事件名称，用户自定义
    DH_Uint16               channel;                        /// 事件事件通道号,默认为0
    DH_Uint16               res0;
    DH_Uint32               id;                             /// 事件编号,标识事件的唯一性
    DH_Uint64               pts;                            /// 事件相对时间戳
    DH_Uint32               ruleId;                         /// 事件触发规则id
    DH_Uint32               groupId;                        /// 事件组ID，一个事件对应的一组图片,组id相同
    DH_Uint32               utc;                            /// 事件的本地时间,秒
    DH_Uint32               utcms;                          /// 事件的本地事件,毫秒
    DH_Uint32               picCnt;                         /// 事件图片个数,picList的个数
    DHOP_EVT_PicInfo        *picList;                       /// 事件图片组合列表,picType:0-全景图 1-人体图 2-人脸图
    DHOP_EVT_FaceAttr       *face;                          /// 人脸属性
    DHOP_EVT_HumanAttr      *human;                         /// 人体属性
    DHOP_EVT_Handler        *handler;                       /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32               res[15];
} DHOP_EVT_HumanInfo;
#endif

#if (__SIZEOF_POINTER__ == 8)                // 64位系统下结构体定义
/// 人体属性
typedef struct
{
    DH_Uint8                coatColor[16];                  /// 上衣颜色
    DH_Uint8                trousersColor[16];              /// 裤子颜色
    DH_Uint8                coatType;                       /// 0: 未知.1: 长袖.2: 短袖
    DH_Uint8                trousersType;                   /// 0: 未知.1: 长裤.2: 短裤.3: 裙子
    DH_Uint8                hasHat;                         /// 0: 未知.1: 不带帽子.2: 有带帽子
    DH_Uint8                hasBag;                         /// 0: 未知.1: 不带包.2: 带包
    DHOP_EVT_Rect           box;                            /// 包围盒
    DHOP_EVT_Point          center;                         /// 物体型心
    DH_Uint8                angle;                          /// 0: 未知.1: – 正面（前面）.2: – 侧面（旁边）.3: – 背面（后面）
    DH_Uint8                hasUmbrella;                    /// 0: 未知.1: – 未打伞.2: – 打伞
    DH_Uint8                bag;                            /// 0: – 未知.1: – 手提包.2: – 肩包.3: – 背包.4: – 拉杆箱.5: – 斜跨包
    DH_Uint8                backBag;                        /// 0-未识别 1-无 2-有
    DH_Uint8                carrierBag;                     /// 0-未识别 1-无 2-有
    DH_Uint8                shoulderBag;                    /// 0-未识别 1-无 2-有
    DH_Uint8                messengerBag;                   /// 0-未识别 1-无 2-有
    DH_Uint8                upperPattern;                   /// 0: – 未知.1: – 纯色.2: – 条纹.3: – 图案.4: – 缝隙.5: – 格子
    DH_Uint8                hairStyle;                      /// 0: – 未知.1: – 长发.2: – 短发.3: – 马尾.4: – 盘发.5: – 头部被遮挡
    DH_Uint8                cap;                            /// 0: – 未知1: – 普通帽子.2: – 头盔.3: – 安全帽
    DH_Uint8                rainCoat;                       /// 0:-未识别.1:-无 2:-有
    DH_Uint8                holdBaby;                       /// 0:-未识别.1:- 未抱.2:-抱
    DH_Uint8                res[8];
} DHOP_EVT_HumanAttr;

/// 人员检测事件信息
typedef struct
{
    DH_Byte                 name[DHOP_EVT_NAME_LEN];        /// 事件名称，用户自定义
    DH_Uint16               channel;                        /// 事件事件通道号,默认为0
    DH_Uint16               res0;
    DH_Uint32               id;                             /// 事件编号,标识事件的唯一性
    DH_Uint64               pts;                            /// 事件相对时间戳
    DH_Uint32               ruleId;                         /// 事件触发规则id
    DH_Uint32               groupId;                        /// 事件组ID，一个事件对应的一组图片,组id相同
    DH_Uint32               utc;                            /// 事件的本地时间,秒
    DH_Uint32               utcms;                          /// 事件的本地事件,毫秒
    DH_Uint32               picCnt;                         /// 事件图片个数,picList的个数
    DHOP_EVT_PicInfo        *picList;                       /// 事件图片组合列表,picType:0-全景图 1-人体图 2-人脸图
    DHOP_EVT_FaceAttr       *face;                          /// 人脸属性
    DHOP_EVT_HumanAttr      *human;                         /// 人体属性
    DHOP_EVT_Handler        *handler;                       /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32               res[14];
} DHOP_EVT_HumanInfo;
#endif

/***************************************************************
* function name : DHOP_EVT_pushHumanTrait
*
* description   : 推送人员检测事件(发送给通过Dahua标准接入协议接入的订阅者)
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
DH_Int32 DHOP_EVT_pushHumanTrait(const DHOP_EVT_HumanInfo *infos, DH_Uint32 num);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __DHOP_EVENT_PUSHHUMANTRAIT_H__
