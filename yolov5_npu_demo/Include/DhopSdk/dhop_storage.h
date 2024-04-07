/*******************************************************************************
 * dhop_storage.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义存储设备操作相关的数据结构与API。
 *
 *******************************************************************************/

#ifndef __DHOP_STORAGE_H__
#define __DHOP_STORAGE_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/

#include "dhop_type_def.h"

/********************************************************************************/

#define DHOP_STORAGE_NAME_MAX_LEN       64
#define DHOP_STORAGE_PART_MAX_NUM       8

/*******************************************************************************/

/* 存储设备类型 */
typedef enum
{
    DHOP_STORAGE_DT_UNKNOW = 0,              // 未知类型
    DHOP_STORAGE_EXTDEV,                     // 外部插入的设备用于数据存储，如u盘、移动硬盘
    DHOP_STORAGE_INNERDEV                    // 内部存储设备，如硬盘保留空间、eMMC
} DHOP_STORAGE_DevType;


/* 存储介质类型 */
typedef enum
{
    DHOP_STORAGE_MT_UNKNOW = 0,              // 未知介质
    DHOP_STORAGE_U_DISK,                     // U盘
    DHOP_STORAGE_MOBILE_DISK,                // 移动硬盘
    DHOP_STORAGE_SD_CARD,                    // SD卡
    DHOP_STORAGE_ESATA_DISK,                 // esata备份盘
    DHOP_STORAGE_DISK,                       // 硬盘
    DHOP_STORAGE_NAS                         // 网络存储
} DHOP_STORAGE_MediaType;


/* 文件系统类型 */
typedef enum
{
    DHOP_STORAGE_FST_UNKOWN = 0,             // 未知格式
    DHOP_STORAGE_FAT32,                      // FAT32
    DHOP_STORAGE_NTFS,                       // NTFS
    DHOP_STORAGE_XFS,                        // XFS
    DHOP_STORAGE_NFS,                        // NFS
    DHOP_STORAGE_SMB,                        // SMB
    DHOP_STORAGE_EXT4,                       // EXT4
    DHOP_STORAGE_TMPFS                       // TMPFS
} DHOP_STORAGE_FSType;


/* 存储设备状态类型 */
typedef enum
{
    DHOP_STORAGE_STATUS_UNKNOW = 0,         //未知状态
    DHOP_STORAGE_STATUS_LOAD,               //加载(比如插入SD卡,启用NAS)
    DHOP_STORAGE_STATUS_UNLOAD,             //卸载(比如拔出SD卡,禁用NAS)
    DHOP_STORAGE_STATUS_ABNORMAL            //异常状态

} DHOP_STORAGE_StatusType;

/* 存储设备访问权限 */
typedef enum
{
    DHOP_STORAGE_DEVMODE_READ  = 1 << 0,   // 存储设备读权限
    DHOP_STORAGE_DEVMODE_WRITE = 1 << 1,   // 存储设备写权限
} DHOP_STORAGE_DevMode;
/*******************************************************************************/


/*******************************************************************************/



#if (__SIZEOF_POINTER__ == 4)                       // 32位系统下结构体定义

/* 存储设备分类 */
typedef struct
{
    DH_Uint16               cbSize;          // 当前结构体大小，sizeof(DHOP_STORAGE_Category),调用者提供
    DH_Uint16               res0;            // 保留字段
    DH_Uint32               mask;            // 支持的存储设备分类，DHOP_STORAGE_DevType掩码
    DH_Uint32               res[7];          // 保留字段
} DHOP_STORAGE_Category;

/* 存储设备结构 */
typedef struct
{
    DH_Uint16               cbSize;                                 // 当前结构体大小，sizeof(DHOP_STORAGE_Dev),调用者提供
    DH_Uint16               res0;                                   // 保留字段
    DH_Char                 devName[DHOP_STORAGE_NAME_MAX_LEN];     // 设备名称
    DH_Uint32               res[8];                                 // 保留字段
} DHOP_STORAGE_Dev;

/* 存储设备分区结构 */
typedef struct
{
    DH_Char                 name[DHOP_STORAGE_NAME_MAX_LEN];        // 分区名称
    DH_Uint16               fsType;                                 // 文件系统类型，定义见 DHOP_STORAGE_FSType
    DH_Uint16               mode;                                   // 访问权限掩码值，可见DHOP_STORAGE_DevMode，仅支持SD卡
    DH_Uint32               totalCapa;                              // 总容量，单位:MB
    DH_Uint32               remainCapa;                             // 剩余容量，单位:MB
    DH_Char                 mountDir[DHOP_STORAGE_NAME_MAX_LEN];    // 挂载路径，为APP实际可以访问的路径
    DH_Uint32               reserved[8];                            // 保留字段
} DHOP_STORAGE_Partition;


/* 存储设备详细信息 */
typedef struct
{
    DH_Uint16               cbSize;                                 // 当前结构体大小，sizeof(DHOP_STORAGE_DevInfo),调用者提供
    DH_Uint16               mediaType;                              // 介质类型，定义见 DHOP_STORAGE_MediaType
    DH_Uint16               partitionNum;                           // 实际有效分区个数
    DH_Int8                 lifePercent;                            // 剩余寿命长度，仅支持SD卡，范围在[-1, 100]，0表示所有块都损坏, 100表示无坏块，-1代表不支持
    DH_Char                 res0;                                   // 保留字段
    DH_Char                 devName[DHOP_STORAGE_NAME_MAX_LEN];     // 设备名称
    DHOP_STORAGE_Partition  partition[DHOP_STORAGE_PART_MAX_NUM];   // 分区信息，目前最大支持8个分区
    DH_Uint32               reserved[8];                            // 保留字段
} DHOP_STORAGE_DevInfo;


/* 存储设备状态通知信息 */
typedef struct
{
    DH_Uint16               cbSize;                                 // 当前结构体大小，sizeof(DHOP_STORAGE_DevInfo),调用者提供
    DH_Uint16               mediaType;                              // 介质类型,参考DHOP_STORAGE_MediaType
    DH_Uint16               statusType;                             // 状态类型,参考DHOP_STORAGE_StatusType
    DH_Uint16               res16;                                  // 保留字段
    DH_Char                 devName[DHOP_STORAGE_NAME_MAX_LEN];     // 设备名称
    DH_Uint32               res32[16];                              // 保留字段
} DHOP_STORAGE_NotifyState;

#endif

/*******************************************************************************/

/*******************************************************************************/
#if (__SIZEOF_POINTER__ == 8)                       // 64位系统下结构体定义

/* 存储设备分类 */
typedef struct
{
    DH_Uint16               cbSize;          // 当前结构体大小，sizeof(DHOP_STORAGE_Category),调用者提供
    DH_Uint16               res0;            // 保留字段
    DH_Uint32               mask;            // 支持的存储设备分类，DHOP_STORAGE_DevType掩码
    DH_Uint32               res[7];          // 保留字段
} DHOP_STORAGE_Category;

/* 存储设备结构 */
typedef struct
{
    DH_Uint16               cbSize;                                 // 当前结构体大小，sizeof(DHOP_STORAGE_Dev),调用者提供
    DH_Uint16               res0[3];                                // 保留字段
    DH_Char                 devName[DHOP_STORAGE_NAME_MAX_LEN];     // 设备名称
    DH_Uint32               res[8];                                 // 保留字段
} DHOP_STORAGE_Dev;

/* 存储设备分区结构 */
typedef struct
{
    DH_Char                 name[DHOP_STORAGE_NAME_MAX_LEN];        // 分区名称
    DH_Uint16               fsType;                                 // 文件系统类型，定义见 DHOP_STORAGE_FSType
    DH_Uint16               mode;                                   // 访问权限掩码值，仅支持SD卡，可见DHOP_STORAGE_DevMode
    DH_Uint32               res0;                                   // 保留字段
    DH_Uint32               totalCapa;                              // 总容量，单位:MB
    DH_Uint32               remainCapa;                             // 剩余容量，单位:MB
    DH_Char                 mountDir[DHOP_STORAGE_NAME_MAX_LEN];    // 挂载路径，为APP实际可以访问的路径
    DH_Uint32               reserved[8];                            // 保留字段
} DHOP_STORAGE_Partition;


/* 存储设备详细信息 */
typedef struct
{
    DH_Uint16               cbSize;                                 // 当前结构体大小，sizeof(DHOP_STORAGE_DevInfo),调用者提供
    DH_Uint16               mediaType;                              // 介质类型，定义见 DHOP_STORAGE_MediaType
    DH_Uint16               partitionNum;                           // 实际有效分区个数
    DH_Int8                 lifePercent;                            // 剩余寿命长度，仅支持SD卡，范围在[-1, 100.0]，0表示所有块都损坏, 100表示无坏块，-1代表不支持
    DH_Char                 res0;                                   // 保留字段
    DH_Char                 devName[DHOP_STORAGE_NAME_MAX_LEN];     // 设备名称
    DHOP_STORAGE_Partition  partition[DHOP_STORAGE_PART_MAX_NUM];   // 分区信息，目前最大支持8个分区
    DH_Uint32               reserved[8];                            // 保留字段
} DHOP_STORAGE_DevInfo;


/* 存储设备状态通知信息 */
typedef struct
{
    DH_Uint16               cbSize;                                 // 当前结构体大小，sizeof(DHOP_STORAGE_DevInfo),调用者提供
    DH_Uint16               mediaType;                              // 介质类型,参考DHOP_STORAGE_MediaType
    DH_Uint16               statusType;                             // 状态类型,参考DHOP_STORAGE_StatusType
    DH_Uint16               res16;                                  // 保留字段
    DH_Char                 devName[DHOP_STORAGE_NAME_MAX_LEN];     // 设备名称
    DH_Uint32               res32[16];                              // 保留字段
} DHOP_STORAGE_NotifyState;

#endif



/*
    功能: 存储设备状态通知回调函数。当存储设备状态发生改变时，触发该回调
    参数: pNotify  -- <in>   状态通知信息
    返回值: < 0: 处理失败. = 0: 处理成功
*/
typedef DH_Int32(*DHOP_STORAGE_onStatusNotify)(const DHOP_STORAGE_NotifyState *pNotify);
/*******************************************************************************/


/*******************************************************************************
* function name : DHOP_STORAGE_getCategory
*
* description   : 获取支持的存储设备分类
*
* output        : category                   -- 设备支持的分类，DHOP_STORAGE_Type类型掩码
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS               -  成功
*               : DHOP_FAILED                -  失败
*******************************************************************************/
DH_Int32 DHOP_STORAGE_getCategory(DHOP_STORAGE_Category *category);


/*******************************************************************************
* function name : DHOP_STORAGE_getDevList
*
* description   : 获取存储设备列表
*
* input         : type                      -- 存储设备类型，见DHOP_STORAGE_Type，调用者给定
*
* output        : pDevices                  -- 设备列表信息
* input/output  : maxNum                    -- maxNum 传入的值是pDevices数组的元素个数，传出的值是实际取到的个数。
*                                              如果实际返回的个数大于数组长度，则只取传入的长度的个数。
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS              -  成功
*               : DHOP_FAILED               -  失败
*******************************************************************************/
DH_Int32 DHOP_STORAGE_getDevList(DHOP_STORAGE_DevType type, DHOP_STORAGE_Dev *pDevices, DH_Uint32 *maxNum);


/*******************************************************************************
* function name : DHOP_STORAGE_mount
*
* description   : 挂载存储设备
*
* input         : devName                   -- 需要挂载的设备名称，从DHOP_STORAGE_getDevList返回的DHOP_STORAGE_Dev中的devName字段获取
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS              -  成功
*               : DHOP_FAILED               -  失败
*               : DHOP_ERR_PARAM_IS_NULL    -  name是NULL或是空字符串
*               : 其它                      -  参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_STORAGE_mount(const DH_Char *devName);


/*******************************************************************************
* function name : DHOP_STORAGE_getDevInfo
*
* description   : 获取存储设备详细信息
*
* input         : devName                   -- 设备名称，从DHOP_STORAGE_getDevList返回的DHOP_STORAGE_Dev中的devName字段获取
*
* output        : pInfo                     -- 设备详细信息
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS              -  成功
*               : DHOP_FAILED               -  失败
*******************************************************************************/
DH_Int32 DHOP_STORAGE_getDevInfo(const DH_Char *devName, DHOP_STORAGE_DevInfo *pInfo);


/*******************************************************************************
* function name : DHOP_STORAGE_umount
*
* description   : 卸载存储设备
*
* input         : devName                   -- 需要挂载的设备名称，从DHOP_STORAGE_getDevList返回的DHOP_STORAGE_Dev中的devName字段获取
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS              -  成功
*               : DHOP_FAILED               -  失败
*               : DHOP_ERR_PARAM_IS_NULL    -  name是NULL或是空字符串
*               : 其它                      -  参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_STORAGE_umount(const DH_Char *devName);


/*******************************************************************************
* function name : DHOP_STORAGE_format
*
* description   : 格式化存储设备
*
* input         : devName                   -- 需要格式化的设备名称，从DHOP_STORAGE_getDevList返回的DHOP_STORAGE_Dev中的devName字段获取
*                 fsType                    -- 文件系统类型
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS              -  成功
*               : DHOP_FAILED               -  失败
*               : DHOP_ERR_PARAM_IS_NULL    -  name是NULL或是空字符串
*               : 其它                      -  参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_STORAGE_format(const DH_Char *devName, const DHOP_STORAGE_FSType fsType);


/*******************************************************************************
* function name : DHOP_STORAGE_startListenStatus
*
* description   : 订阅存储设备状态
*
* input         : mediaType - 介质类型
*                 proc - 事件回调
*
* notice        : 1. 接口线程安全.
*                 2. 如果在进程内多次调用该接口订阅相同介质类型存储设备状态,以最后一次调用为准
*
* return value  : DHOP_SUCCESS              -  成功
*               : 非DHOP_SUCCESS             -  失败,参考错误码
*******************************************************************************/
DH_Int32 DHOP_STORAGE_startListenStatus(DHOP_STORAGE_MediaType mediaType, DHOP_STORAGE_onStatusNotify proc);


/*******************************************************************************
* function name : DHOP_STORAGE_stopListenStatus
*
* description   : 取消订阅存储设备状态
*
* input         : mediaType - 介质类型
*
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS              -  成功
*               : 非DHOP_SUCCESS             -  失败,参考错误码
*******************************************************************************/
DH_Int32 DHOP_STORAGE_stopListenStatus(DHOP_STORAGE_MediaType mediaType);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_STORAGE_H__



