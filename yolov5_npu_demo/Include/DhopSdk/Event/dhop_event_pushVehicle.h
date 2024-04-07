/*******************************************************************************
* dhop_event_common.h
*
* Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
*
* Description: 推送车辆检测事件。
*
*******************************************************************************/

#ifndef __DHOP_EVENT_PUSHVEHICLE_H__
#define __DHOP_EVENT_PUSHVEHICLE_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
#include "dhop_event_common.h"
/*******************************************************************************/

/// 安全带标识
typedef enum
{
    DHOP_EVT_SeatUnknown,
    DHOP_EVT_SeatWithSafeBelt,
    DHOP_EVT_SeatWithoutSafeBelt,
} DHOP_EVT_SeatFlag;

#if (__SIZEOF_POINTER__ == 4)           // 32位系统下结构体定义
/// 车辆特征属性
typedef struct
{
    DH_Uint32               id;                             /// 车辆唯一id
    DH_Uint32               recNo;                          /// 记录编号
    DH_Uint32               createTime;                     /// 创建时间
    DH_Uint8                plateNo[32];                    /// 车牌号码,UTF8编码."Unknown"表示未知
    DHOP_EVT_Rect           plateBox;                       /// 车牌包围框
    DH_Uint8                plateType[32];                  /// 号牌类型
    /// "Normal" :蓝牌
    /// "Yellow":黄牌
    /// "DoubleYellow":双层黄尾牌
    /// "Police":警牌
    /// "Armed":武警牌
    /// "SAR":港澳特区号牌
    /// "Trainning":教练车号牌
    /// "Personal":个性号牌
    /// "Agri":农用牌
    /// "Embassy":使馆号牌
    /// "Moto":摩托车号牌
    /// "Tractor":拖拉机号牌
    /// "OfficialCar":公务车
    /// "PersonalCar":私家车
    /// "WarCar":军用
    /// "Civilaviation":民航号牌
    /// "Black":黑牌
    /// "PureNewEnergyMicroCar":纯电动新能源小车
    /// "MixedNewEnergyMicroCar":混合新能源小车
    /// "PureNewEnergyLargeCar":纯电动新能源大车
    /// "MixedNewEnergyLargeCar":混合新能源大车
    /// "Emergency":应急号牌
    /// "ElectricTricycle":电动三轮车号牌
    DH_Uint8                plateColor[32];                 /// 车牌颜色
    /// "Unknown": – 未知
    /// "Blue"
    /// "Yellow"
    /// "White"
    /// "Black"
    /// "Green"
    /// "YellowbottomBlackText": 黄底黑字
    /// "BluebottomWhiteText": 蓝底白字
    /// "BlackBottomWhiteText": 黑底白字
    /// "ShadowGreen": –渐变绿
    /// "YellowGreen": –黄绿双拼
    /// "Other": – 其他
    DH_Uint8                vehicleColor[16];               /// 车身颜色
    DH_Uint8                vehicleColorShade[16];          /// 车身深浅色."Light","Dark"
    DHOP_EVT_Rect           vehicleBox;                     /// 车辆包围框
    DH_Int32                speed;                          /// 车辆速度, km/h
    DHOP_EVT_SeatFlag       mainSeat;                       /// 主驾驶座位安全带 参见枚举DHOP_EVT_SeatFlag
    DHOP_EVT_SeatFlag       secondSeat;                      /// 副驾驶座位安全带 参见枚举DHOP_EVT_SeatFlag
    DH_Uint8                brand[32];                      /// 车辆品牌."Audi"-奥迪, "Honda"-本田 ...
    DH_Uint8                subBrand[128];                  /// 车辆子品牌,UTF8编码."Unknown"表示未知,"A8L" ...
    DH_Uint8                category[32];                   /// 车辆子类型,UTF8编码.如"Unknown"表示未知,机动车(Motor),公交车(Bus)
} DHOP_EVT_VehicleAttr;

/// 车辆检测事件信息
typedef struct
{
    DH_Byte                 name[DHOP_EVT_NAME_LEN];        /// 事件名称，用户自定义
    DH_Uint16               state;                          /// 事件状态，定义参见DHOP_EVT_State(车辆一般为Once)
    DH_Uint16               channel;                        /// 事件事件通道号,默认为0
    DH_Uint32               id;                             /// 事件编号,标识事件的唯一性
    DH_Int32                groupId;                        /// 事件组ID，一个事件对应的一组图片,组id相同
    DH_Uint32               res1;
    DH_Uint32               utc;                            /// 事件的本地时间,秒
    DH_Uint32               utcms;                          /// 事件的本地事件,毫秒
    DH_Uint32               picCnt;                         /// 事件图片个数,picList的个数
    DH_Uint32               res2;
    DHOP_EVT_PicInfo        *picList;                       /// 事件图片组合列表,picType:0-原始图 1-车牌图 2-车身图
    DHOP_EVT_VehicleAttr    *vehicleAttr;                   /// 事件对应的属性
    DHOP_EVT_Handler        *handler;                       /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32               res[15];
} DHOP_EVT_VehicleInfo;
#endif

#if (__SIZEOF_POINTER__ == 8)                // 64位系统下结构体定义
/// 车辆特征属性
typedef struct
{
    DH_Uint32               id;                             /// 车辆唯一id
    DH_Uint32               recNo;                          /// 记录编号
    DH_Uint32               createTime;                     /// 创建时间
    DH_Uint8                plateNo[32];                    /// 车牌号码,UTF8编码."Unknown"表示未知
    DHOP_EVT_Rect           plateBox;                       /// 车牌包围框
    DH_Uint8                plateType[32];                  /// 号牌类型
    /// "Normal" :蓝牌
    /// "Yellow":黄牌
    /// "DoubleYellow":双层黄尾牌
    /// "Police":警牌
    /// "Armed":武警牌
    /// "SAR":港澳特区号牌
    /// "Trainning":教练车号牌
    /// "Personal":个性号牌
    /// "Agri":农用牌
    /// "Embassy":使馆号牌
    /// "Moto":摩托车号牌
    /// "Tractor":拖拉机号牌
    /// "OfficialCar":公务车
    /// "PersonalCar":私家车
    /// "WarCar":军用
    /// "Civilaviation":民航号牌
    /// "Black":黑牌
    /// "PureNewEnergyMicroCar":纯电动新能源小车
    /// "MixedNewEnergyMicroCar":混合新能源小车
    /// "PureNewEnergyLargeCar":纯电动新能源大车
    /// "MixedNewEnergyLargeCar":混合新能源大车
    /// "Emergency":应急号牌
    /// "ElectricTricycle":电动三轮车号牌
    DH_Uint8                plateColor[32];                 /// 车牌颜色
    /// "Unknown": – 未知
    /// "Blue"
    /// "Yellow"
    /// "White"
    /// "Black"
    /// "Green"
    /// "YellowbottomBlackText": 黄底黑字
    /// "BluebottomWhiteText": 蓝底白字
    /// "BlackBottomWhiteText": 黑底白字
    /// "ShadowGreen": –渐变绿
    /// "YellowGreen": –黄绿双拼
    /// "Other": – 其他
    DH_Uint8                vehicleColor[16];               /// 车身颜色
    DH_Uint8                vehicleColorShade[16];          /// 车身深浅色."Light","Dark"
    DHOP_EVT_Rect           vehicleBox;                     /// 车辆包围框
    DH_Int32                speed;                          /// 车辆速度, km/h
    DHOP_EVT_SeatFlag       mainSeat;                       /// 主驾驶座位安全带 参见枚举DHOP_EVT_SeatFlag
    DHOP_EVT_SeatFlag       secondSeat;                      /// 副驾驶座位安全带 参见枚举DHOP_EVT_SeatFlag
    DH_Uint8                brand[32];                      /// 车辆品牌."Audi"-奥迪, "Honda"-本田 ...
    DH_Uint8                subBrand[128];                  /// 车辆子品牌,UTF8编码."Unknown"表示未知,"A8L" ...
    DH_Uint8                category[32];                   /// 车辆子类型,UTF8编码.如"Unknown"表示未知,机动车(Motor),公交车(Bus)
} DHOP_EVT_VehicleAttr;

/// 车辆检测事件信息
typedef struct
{
    DH_Byte                 name[DHOP_EVT_NAME_LEN];        /// 事件名称，用户自定义
    DH_Uint16               state;                          /// 事件状态，定义参见DHOP_EVT_State(车辆一般为Once)
    DH_Uint16               channel;                        /// 事件事件通道号,默认为0
    DH_Uint32               id;                             /// 事件编号,标识事件的唯一性
    DH_Int32                groupId;                        /// 事件组ID，一个事件对应的一组图片,组id相同
    DH_Uint32               res1;
    DH_Uint32               utc;                            /// 事件的本地时间,秒
    DH_Uint32               utcms;                          /// 事件的本地事件,毫秒
    DH_Uint32               picCnt;                         /// 事件图片个数,picList的个数
    DH_Uint32               res2;
    DHOP_EVT_PicInfo        *picList;                       /// 事件图片组合列表,picType:0-原始图 1-车牌图 2-车身图
    DHOP_EVT_VehicleAttr    *vehicleAttr;                   /// 事件对应的属性
    DHOP_EVT_Handler        *handler;                       /// 联动选项,定义参见DHOP_EVT_Handler
    DH_Uint32               res[14];
} DHOP_EVT_VehicleInfo;
#endif

/***************************************************************
* function name : DHOP_EVT_pushVehicle
*
* description   : 推送车辆检测事件(发送给通过Dahua标准接入协议接入的订阅者)
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
DH_Int32 DHOP_EVT_pushVehicle(const DHOP_EVT_VehicleInfo *infos, DH_Uint32 num);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __DHOP_EVENT_PUSHVEHICLE_H__
