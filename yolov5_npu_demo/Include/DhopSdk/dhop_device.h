/*******************************************************************************
 * dhop_device.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 本模块提供产品外设相关的操作
 *
 *******************************************************************************/

#ifndef __DHOP_DEVICE_H__
#define __DHOP_DEVICE_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/

#include <limits.h>
#include "dhop_type_def.h"


/*******************************************************************************/

/* 外设句柄 */
typedef DH_Handle DHOP_DEVICE_Handle;

/*******************************************************************************/

/* 外设类型 */
typedef enum
{
    // atsha204a加密芯片，对应的详细定义参见“device/atsha204a.h”
    DHOP_DEVICE_TYPE_IIC_ATSHA204A  = 0,
    DHOP_DEVICE_TYPE_PHOTORESISTOR,
    DHOP_DEVICE_TYPE_SCREEN,
    DHOP_DEVICE_TYPE_PANEL_ALARM_IN,
    DHOP_DEVICE_TYPE_PANEL_ALARM_OUT,
    DHOP_DEVICE_TYPE_PANEL_ANTI_DISMANTLE_ALARM,
    DHOP_DEVICE_TYPE_PANEL_PROXIMITY_SENSOR,
    DHOP_DEVICE_TYPE_PANEL_BUTTON,
    DHOP_DEVICE_TYPE_PANEL_LIGHT,
    DHOP_DEVICE_TYPE_RS485,
    DHOP_DEVICE_TYPE_ZIGBEE,
    DHOP_DEVICE_TYPE_ETHERNET,
    DHOP_DEVICE_TYPE_WIFI,
    DHOP_DEVICE_TYPE_FLASHLIGHT,
    DHOP_DEVICE_TYPE_NUM
} DHOP_DEVICE_Type;                 //外设类型

/*******************************************************************************/
#if (__SIZEOF_POINTER__ == 4)                       // 32位系统下结构体定义
#endif
#if (__SIZEOF_POINTER__ == 8)                       // 64位系统下结构体定义
#endif

/*******************************************************************************/


/*******************************************************************************
* function name : DHOP_DEVICE_getNum
*
* description   : 获取指定类型device的个数
*
* input         : devType       -- 设备类型，定义参见DHOP_DEVICE_Type
*
* output        : num           -- 设备个数
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : DHOP_ERR_INVALID_PARMETER - devType传入不支持的类型
*               : DHOP_ERR_PARAM_IS_NULL - num是NULL
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_DEVICE_getNum(DHOP_DEVICE_Type devType, DH_Uint32 *num);


/*******************************************************************************
* function name : DHOP_DEVICE_open
*
* description   : 打开指定的外设
*
* input         : devType       -- 设备类型，定义参见DHOP_DEVICE_Type
*                 index         -- 如果当前产品上同类外设存在多个，通过index指定。
*                                  下标取值[0,N)，N的取值通过DHOP_DEVICE_getNum获知
*
* output        : hDevice       -- 外设操作句柄
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : DHOP_ERR_INVALID_PARMETER - devType传入不支持的类型
*               : DHOP_ERR_OUT_OF_RANGE - index值超出支持范围
*               : DHOP_ERR_PARAM_IS_NULL - hDevice是NULL
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_DEVICE_open(DHOP_DEVICE_Type devType, DH_Uint32 index, DHOP_DEVICE_Handle *hDevice);


/*******************************************************************************
* function name : DHOP_DEVICE_close
*
* description   : 关闭已经打开的外设句柄，关闭后句柄不可用，内部置NULL
*
* input         : hDevice       -- 外设操作句柄，通过DHOP_DEVICE_open打开
*
* output        : None
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : DHOP_ERR_PARAM_IS_NULL - hDevice是NULL
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_DEVICE_close(DHOP_DEVICE_Handle *hDevice);


/*******************************************************************************
* function name : DHOP_DEVICE_read
*
* description   : 设备读操作
*
* input         : hDevice       -- 外设操作句柄，通过DHOP_DEVICE_open打开
*                 buffer        -- 读取数据的存储buffer空间，内存由用户分配
*                 count         -- buffer空间的大小
*
* output        : None
*
* return value  : 大于等于0     - 成功读取的数据量
*               : DHOP_ERR_INVALID_HANDLE - hDevice是无效的操作句柄
*               : DHOP_ERR_PARAM_IS_NULL - buffer是NULL
*               : 其他         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_DEVICE_read(DHOP_DEVICE_Handle hDevice, DH_Byte* buffer, DH_Uint32 count);


/*******************************************************************************
* function name : DHOP_DEVICE_write
*
* description   : 设备写操作
*
* input         : hDevice       -- 外设操作句柄，通过DHOP_DEVICE_open打开
*                 buffer        -- 写出数据的存储buffer空间，内存由用户分配
*                 count         -- buffer空间的大小
*
* output        : None
*
* return value  : 大于等于0     - 成功写出的数据量
*               : DHOP_ERR_INVALID_HANDLE - hDevice是无效的操作句柄
*               : DHOP_ERR_PARAM_IS_NULL - buffer是NULL
*               : 其他         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_DEVICE_write(DHOP_DEVICE_Handle hDevice, DH_Byte* buffer, DH_Uint32 count);


/*******************************************************************************
* function name : DHOP_DEVICE_control
*
* description   : 设备控制操作
*
* input         : hDevice       -- 外设操作句柄，通过DHOP_DEVICE_open打开
*                 cmd           -- 外设控制命令，见各外设头文件中的定义
*                 args          -- 外设控制命令参数，见各外设头文件中的定义
*
* output        : None
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : DHOP_ERR_INVALID_HANDLE - hDevice是无效的操作句柄
*               : DHOP_ERR_INVALID_PARMETER - cmd参数传入不支持的类型
*               : DHOP_ERR_PARAM_IS_NULL - args是NULL
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_DEVICE_control(DHOP_DEVICE_Handle hDevice, DH_Uint32 cmd, DH_Ptr args);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_DEVICE_H__


