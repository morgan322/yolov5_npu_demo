/*******************************************************************************
 * dhop_sys.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义系统相关的数据结构与API，本模块设计到的信息均为设备平台相关的
 *              信息。
 *
 *******************************************************************************/

#ifndef __DHOP_SYS_H__
#define __DHOP_SYS_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"
#include "dhop_version.h"
#include <limits.h>

/*******************************************************************************/

#define DHOP_MAX_IP_ADDR_LENGTH         (48)
#define DHOP_MAX_MAC_LENGTH             (32)
#define DHOP_MAX_DEV_SERIAL_LENGTH      (32)
#define DHOP_MAX_ETH_NAME_LENGTH        (8)                                         /* 设备上网卡名称最大长度 */
#define DHOP_MAX_SYS_ACCOUNT_LENGTH     (32)                                        /* 用户名密码的最大长度为31字节 */

/*******************************************************************************/

/* 平台信息 */
typedef enum
{
    DHOP_SYS_PLAT_VOLT = 1,                                                         /* 伏特平台 */
    DHOP_SYS_PLAT_NOBEL,                                                            /* 诺贝尔平台 */
    DHOP_SYS_PLAT_FAFNIR,                                                           /* 达芬奇平台 */
    DHOP_SYS_PLAT_DARWIN,                                                           /* 达尔文平台 */
    DHOP_SYS_PLAT_COPERNICUS,                                                       /* 哥白尼平台 */
    DHOP_SYS_PLAT_HIMALAYA,                                                         /* HIMALAYA平台 */
    DHOP_SYS_PLAT_FARADAY,                                                          /* 法拉第平台 */
} DHOP_SYS_PlatformType;

/* 网络带宽 */
typedef enum
{
    DHOP_SYS_NET_Unknown = 0,
    DHOP_SYS_NET_10Mbps,
    DHOP_SYS_NET_100Mbps,                                                           /* 百兆带宽 */
    DHOP_SYS_NET_1000Mbps,                                                          /* 千兆带宽 */
    DHOP_SYS_NET_2500Mbps,
    DHOP_SYS_NET_10000Mbps,
} DHOP_SYS_NetworkBandWidth;

/* 网络类型 */
typedef enum
{
    DHOP_SYS_NIT_Unknown = 0,
    DHOP_SYS_NIT_WIRE,                                                              /* 有线网卡 */
    DHOP_SYS_NIT_WIFI,                                                              /* Wifi网络 */
    DHOP_SYS_NIT_4G,                                                                /* 无线4G网络 */
    DHOP_SYS_NIT_5G,                                                                /* 无线5G网络 */
} DHOP_SYS_NetworkType;

/* 恢复默认类型 */
typedef enum
{
    DHOP_SYS_RESTORE_DEFAULT        = 0,                                            /* 恢复所有配置到默认 */
    DHOP_SYS_RESTORE_EXCEPT_IP      = (1 << 0),                                     /* 恢复默认但保留IP地址 */
    DHOP_SYS_RESTORE_EXCEPT_ACCOUNT = (1 << 1),                                     /* 恢复默认但保留账号信息 */
    DHOP_SYS_RESTORE_MAX            = (ULLONG_MAX)
} DHOP_SYS_restoreType;

/* 系统帐号类型 */
typedef enum
{
    DHOP_SYS_ACCOUNT_UPGRADE = 0,                                                   /* 用于设备固件升级帐号 */
    DHOP_SYS_ACCOUNT_MAX
} DHOP_SYS_AccountType;

/* 系统账户的权限 */
typedef enum
{
    DHOP_SYS_ACCOUNT_AUTH_MONITOR,                                                  /* 实时预览 */
    DHOP_SYS_ACCOUNT_AUTH_REPLAY,                                                   /* 录像回放 */
    DHOP_SYS_ACCOUNT_AUTH_SYSCFG,                                                   /* 系统管理 */
    DHOP_SYS_ACCOUNT_AUTH_SYSINFO,                                                  /* 系统信息 */
    DHOP_SYS_ACCOUNT_AUTH_MANUCTR,                                                  /* 手动控制 */
    DHOP_SYS_ACCOUNT_AUTH_BACKUP,                                                   /* 文件备份 */
    DHOP_SYS_ACCOUNT_AUTH_STORECFG,                                                 /* 存储管理 */
    DHOP_SYS_ACCOUNT_AUTH_EVENTCFG,                                                 /* 事件管理 */
    DHOP_SYS_ACCOUNT_AUTH_NETCFG,                                                   /* 网络管理 */
    DHOP_SYS_ACCOUNT_AUTH_PERIPHERAL,                                               /* 外设管理 */
    DHOP_SYS_ACCOUNT_AUTH_AVPARAM,                                                  /* 音视频参数 */
    DHOP_SYS_ACCOUNT_AUTH_SECURITY,                                                 /* 安全管理 */
    DHOP_SYS_ACCOUNT_AUTH_MAINTENCE,                                                /* 设备维护 */
    DHOP_SYS_ACCOUNT_AUTH_MAXVALUE,                                                 /* 边界值，无效值 */
} DHOP_SYS_AccountAuthType;

/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)           // 32位系统下结构体定义
/* DHOP系统初始化 */
typedef struct
{
    DH_Uint32                           version;                                    /* 调用者直接赋值DHOP_SDK_VERSION, 定义见dhop_version.h */

    /* 当DHOP-OS需要停止APP运行时，通过该回调告知APP，APP在回调函数内实现有序退出，超时未返回，则
     * DHOP-APP-Manager将对该APP进行强制退出操作。
     * 注意：强制退出可能会出现未知风险，请APP做好有序退出。
     *
     * 该字段不允许NULL
     */
    DH_Void                             (*onExitCallback)(DH_Void);                 /* APP停止运行时触发，由调用者填写,不可缺省 */
    DH_Uint32            reserved[30];                                              /* 保留字段 */
} DHOP_SYS_InitParam;


/* 版本信息 */
typedef struct
{
    DHOP_SDK_Version                    sdkVer;                                     /* DHOP_SDK版本信息，具体信息参见DHOP_SDK_Version */
    DHOP_SDK_Version                    osVer;                                      /* DHOP_OS版本信息，具体信息参见DHOP_SDK_Version */
} DHOP_SYS_VerInfo;

/* 兼容v1.0.2版本以下的接口使用，v1.0.2以上版本不建议用_V2接口 */
typedef DHOP_SYS_VerInfo DHOP_SYS_VerInfo_V2;


/* 系统能力:cpu/memory/flash... */
typedef struct
{
    DH_Uint32                           reserved[32];                               /* 保留字段 */
} DHOP_SYS_Caps;


/* 设备信息 */
typedef struct
{
    DH_Uint8                            ipAddr[DHOP_MAX_IP_ADDR_LENGTH];            /* 设备IP地址 */
    DH_Uint8                            mac[DHOP_MAX_MAC_LENGTH];                   /* 设备MAC地址 */
    DH_Uint8                            serial[DHOP_MAX_DEV_SERIAL_LENGTH];         /* 设备序列号，跟设备铭牌信息一致 */
    DH_Uint16                           devType;                                    /* 设备类型, 未启用 */
    DH_Uint16                           platType;                                   /* 平台类型, 定义参见DHOP_SYS_PlatformType */
    DH_Uint32                           res[4];                                     /* reserved */
} DHOP_SYS_DevInfo;


/* 本地时间 */
typedef struct
{
    DH_Uint32                           sec;                                        /* 本地时间: 秒 - 取值区间为[0,59] */
    DH_Uint32                           min;                                        /* 本地时间: 分 - 取值区间为[0,59] */
    DH_Uint32                           hour;                                       /* 本地时间: 时 - 取值区间为[0,23] */
    DH_Uint32                           mday;                                       /* 本地时间: 日期 - 取值区间为[1,31] */
    DH_Uint32                           mon;                                        /* 本地时间: 月份 - 取值区间为[1,12] */
    DH_Uint32                           year;                                       /* 本地时间: 年份 - 取值区间为[1900,~) */
    DH_Uint32                           wday;                                       /* 本地时间: 星期 - 取值区间为[0,6], 0表示星期天，1表示星期一 */
    DH_Int32                            tz_delta;                                   /* 时差，相对0时区的UTC正负时间偏移，单位(秒) */
    DH_Uint32                           reserve[8];                                 /* 保留 */
} DHOP_SYS_LocalTime;


/* UTC时间 (GMT) */
typedef struct
{
    DH_Uint32                           sec;                                        /* GMT时间: 秒 */
    DH_Uint32                           msec;                                       /* GMT时间: 毫秒 - 取值区间为[0,999] */
} DHOP_SYS_UtcTime;


/* 系统网络信息 */
typedef struct
{
    /* 网络节点名称，如: eth0/eth1:0 */
    DH_Char                             name[DHOP_MAX_ETH_NAME_LENGTH];
    DHOP_SYS_NetworkType                type;                                       /* 网络接入类型，定义参见DHOP_SYS_NetworkType */
    DHOP_SYS_NetworkBandWidth           bandwidth;                                  /* 系统网络带宽，定义参见DHOP_SYS_NetworkBandWidth */
    DH_Uint64                           rx;                                         /* 接收流量，单位: 字节 */
    DH_Uint64                           tx;                                         /* 发送流量，单位: 字节 */
    DH_Uint32                           res[12];
} DHOP_SYS_NetInfo;

/* 系统账户的能力描述 */
typedef struct
{
    DH_Uint32                           maxNum;                                     /* APP可管理的最大账户数量 */
    DH_Uint32                           reserved[31];
} DHOP_SYS_AccountCapability;

/* 系统帐号信息 */
typedef struct
{
    DH_Uint32                           type;                                       /* 帐号类型，参见DHOP_SYS_AccountType */
    DH_Char                             username[DHOP_MAX_SYS_ACCOUNT_LENGTH];      /* 用户名，调用填写的数据保证以0结束 */
    DH_Char                             password[DHOP_MAX_SYS_ACCOUNT_LENGTH];      /* 明文密码，调用填写的数据保证以0结束 */
    DH_Uint32                           authMask;                                   /* 权限掩码，掩码值: (1 << DHOP_SYS_AccountAuthType) 表示对应权限有效 */
    DH_Uint32                           reserved[11];                               /* 保留字段 */
} DHOP_SYS_Account;

/* 系统帐号列表信息 */
typedef struct
{
    DH_Uint32                           listNum;                                    /* 调用者填写list列表长度 */
    DH_Uint32                           accountNum;                                 /* 实际获取到的账户个数 */
    DHOP_SYS_Account*                   list;                                       /* 账户数组信息, 内存由调用者提供 */
    DH_Uint32                           rsv[13];                                    /* 预留位 */
} DHOP_SYS_AccountList;

#endif
#if (__SIZEOF_POINTER__ == 8)            // 64位系统下结构体定义
/* DHOP系统初始化 */
typedef struct
{
    DH_Uint32                           version;                                    /* 调用者直接赋值DHOP_SDK_VERSION, 定义见dhop_version.h */
    DH_Uint32                           resWord;                                    /* 保留字段 */
    /* 当DHOP-OS需要停止APP运行时，通过该回调告知APP，APP在回调函数内实现有序退出，超时未返回，则
     * DHOP-APP-Manager将对该APP进行强制退出操作。
     * 注意：强制退出可能会出现未知风险，请APP做好有序退出。
     *
     * 该字段不允许NULL
     */
    DH_Void                             (*onExitCallback)(DH_Void);                 /* APP停止运行时触发，由调用者填写,不可缺省 */
    DH_Uint32                           reserved[30];                               /* 保留字段 */
} DHOP_SYS_InitParam;


/* 版本信息 */
typedef struct
{
    DHOP_SDK_Version                    sdkVer;                                     /* DHOP_SDK版本信息，具体信息参见DHOP_SDK_Version */
    DHOP_SDK_Version                    osVer;                                      /* DHOP_OS版本信息，具体信息参见DHOP_SDK_Version */
} DHOP_SYS_VerInfo;

/* 兼容v1.0.2版本一下的接口使用，v1.0.2以上版本不建议用_V2接口 */
typedef DHOP_SYS_VerInfo DHOP_SYS_VerInfo_V2;


/* 系统能力:cpu/memory/flash... */
typedef struct
{
    DH_Uint32                           reserved[32];                               /* 保留字段 */
} DHOP_SYS_Caps;


/* 设备信息 */
typedef struct
{
    DH_Uint8                            ipAddr[DHOP_MAX_IP_ADDR_LENGTH];            /* 设备IP地址 */
    DH_Uint8                            mac[DHOP_MAX_MAC_LENGTH];                   /* 设备MAC地址 */
    DH_Uint8                            serial[DHOP_MAX_DEV_SERIAL_LENGTH];         /* 设备序列号，跟设备铭牌信息一致 */
    DH_Uint16                           devType;                                    /* 设备类型, 未启用 */
    DH_Uint16                           platType;                                   /* 平台类型, 定义参见DHOP_SYS_PlatformType */
    DH_Uint32                           res[4];                                     /* reserved */
} DHOP_SYS_DevInfo;


/* 本地时间 */
typedef struct
{
    DH_Uint32                           sec;                                        /* 本地时间: 秒 - 取值区间为[0,59] */
    DH_Uint32                           min;                                        /* 本地时间: 分 - 取值区间为[0,59] */
    DH_Uint32                           hour;                                       /* 本地时间: 时 - 取值区间为[0,23] */
    DH_Uint32                           mday;                                       /* 本地时间: 日期 - 取值区间为[1,31] */
    DH_Uint32                           mon;                                        /* 本地时间: 月份 - 取值区间为[1,12] */
    DH_Uint32                           year;                                       /* 本地时间: 年份 - 取值区间为[1900,~) */
    DH_Uint32                           wday;                                       /* 本地时间: 星期 - 取值区间为[0,6], 0表示星期天，1表示星期一 */
    DH_Int32                            tz_delta;                                   /* 时差，相对0时区的UTC正负时间偏移，单位(秒) */
    DH_Uint32                           reserve[8];                                 /* 保留 */
} DHOP_SYS_LocalTime;


/* UTC时间 (GMT) */
typedef struct
{
    DH_Uint32                           sec;                                        /* GMT时间: 秒 */
    DH_Uint32                           msec;                                       /* GMT时间: 毫秒 - 取值区间为[0,999] */
} DHOP_SYS_UtcTime;

/* 系统网络信息 */
typedef struct
{
    /* 网络节点名称，如: eth0/eth1:0 */
    DH_Char                             name[DHOP_MAX_ETH_NAME_LENGTH];
    DHOP_SYS_NetworkType                type;                                       /* 网络接入类型，定义参见DHOP_SYS_NetworkType */
    DHOP_SYS_NetworkBandWidth           bandwidth;                                  /* 系统网络带宽，定义参见DHOP_SYS_NetworkBandWidth */
    DH_Uint64                           rx;                                         /* 接收流量，单位: 字节 */
    DH_Uint64                           tx;                                         /* 发送流量，单位: 字节 */
    DH_Uint32                           res[12];
} DHOP_SYS_NetInfo;

/* 系统账户的能力描述 */
typedef struct
{
    DH_Uint32                           maxNum;                                     /* APP可管理的最大账户数量 */
    DH_Uint32                           reserved[31];
} DHOP_SYS_AccountCapability;

/* 系统帐号信息 */
typedef struct
{
    DH_Uint32                           type;                                       /* 帐号类型，参见DHOP_SYS_AccountType */
    DH_Uint32                           res1;                                       /* 保留字段 */
    DH_Char                             username[DHOP_MAX_SYS_ACCOUNT_LENGTH];      /* 用户名，调用填写的数据保证以0结束 */
    DH_Char                             password[DHOP_MAX_SYS_ACCOUNT_LENGTH];      /* 明文密码，调用填写的数据保证以0结束 */
    DH_Uint32                           authMask;                                   /* 权限掩码，掩码值: (1 << DHOP_SYS_AccountAuthType) 表示对应权限有效 */
    DH_Uint32                           reserved[11];                               /* 保留字段 */
} DHOP_SYS_Account;

/* 系统帐号列表信息 */
typedef struct
{
    DH_Uint32                           listNum;                                    /* 调用者填写list列表长度 */
    DH_Uint32                           accountNum;                                 /* 实际获取到的账户个数 */
    DHOP_SYS_Account*                   list;                                       /* 账户数组信息, 内存由调用者提供 */
    DH_Uint32                           rsv[12];                                    /* 预留位 */
} DHOP_SYS_AccountList;

#endif

/*******************************************************************************/

/***************************************************************
* function name : DHOP_SYS_init
*
* description   : DHOP system initialization, this API should be called before using any other API, using any other
*                 API before using DHOP_init may cause unpredicted error.
*
* input         : pParam -- initialized parameters.
*
* output        : None
*
* notice        : 1. 接口线程不安全. 2. 进程内不可重复调用
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_init(DHOP_SYS_InitParam *pParam);


/***************************************************************
* function name : DHOP_SYS_deInit
*
* description   : DHOP system deinitial, After initialization, if user application needs to stop, this API should
*                 be called before exit.
*
* input         : None
*
* output        : None
*
* notice        : 1. 接口线程安全. 2. 接口调用后，进程需要退出
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_deInit();


/***************************************************************
* function name : DHOP_SYS_getInfo
*
* description   : this API may be used to retrieve device informations.
*
* input         : None
*
* output        : pDevInfo -- device information, see DHOP_SYS_DevInfo
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_getDevInfo(DHOP_SYS_DevInfo *pDevInfo);


/***************************************************************
* function name : DHOP_SYS_getLocalTime
*
* description   : 获取设备本地时间
*
* input         : None
*
* output        : pLocalTime -- 本地时间
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_getLocalTime(DHOP_SYS_LocalTime *pLocalTime);


/***************************************************************
* function name : DHOP_SYS_setLocalTime
*
* description   : 设置设备本地时间
*
* input         : pLocalTime -- 本地时间
*
* output        : None
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 DHOP_ERR_PARAM_IS_NULL - pLocalTime是NULL
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_setLocalTime(DHOP_SYS_LocalTime *pLocalTime);


/***************************************************************
* function name : DHOP_SYS_getUtcTime
*
* description   : 获取GMT-UTC时间
*
* input         : 无
*
* output        : pUtcTime   -- UTC时间
*
* notice        : 1. 接口线程安全. 2. 基于系统的时区信息
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_getUtcTime(DHOP_SYS_UtcTime *pUtcTime);


/***************************************************************
* function name : DHOP_getSysCaps
*
* description   : this API may be used to retrieve system capabilities of the device.
*
* input         : None
*
* output        : pSysCaps -- system capabilities, see DHOP_SYS_Caps
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_getCaps(DHOP_SYS_Caps *pSysCaps);


/***************************************************************
* function name : DHOP_SYS_getTimeOfJiffies
*
* description   : this API is used to get a timestamp value, which is monotonically increasing
*
* input         : None
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : timestamp, milliseconds
***************************************************************/
DH_Uint64 DHOP_SYS_getTimeOfJiffies();


/***************************************************************
* function name : DHOP_SYS_getVersion
*
* description   : 获取当前APP运行时，DHOP_SDK/DHOP_OS的版本信息
*
* input         : none
*
* output        : pInfo -- version info
*
* notice        : 1. 接口线程安全.
* example       : ----------------------------------------------
*                 DHOP_SYS_VerInfo   ver;
*                 ret = DHOP_SYS_getVersion(&ver);
*                 printf("ver info: %s\n", ver.description);
*                 ----------------------------------------------
*
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_getVersion(DHOP_SYS_VerInfo *pInfo);


/***************************************************************
* function name : DHOP_SYS_getVersion_V2
*
* description   : 获取当前APP运行时，DHOP_SDK/DHOP_OS的版本信息
*                 即将废弃，请采用DHOP_SYS_getVersion接口
*
* input         : none
*
* output        : pInfo -- version info
* notice        : 1. 接口线程安全.
*
* example       : ----------------------------------------------
*                 DHOP_SYS_VerInfo_V2   ver;
*                 ret = DHOP_SYS_getVersion_V2(&ver);
*                 printf("ver info: %s\n", ver.description);
*                 ----------------------------------------------
*
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_getVersion_V2(DHOP_SYS_VerInfo_V2 *pInfo);


/***************************************************************
* function name : DHOP_SYS_reboot
*
* description   : 系统重启接口
*
* input         : none
*
* output        : none
*
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_reboot();

/***************************************************************
* function name : DHOP_SYS_getNetInfo
*
* description   : 获取系统网络信息
*
* input         : none
*
* output        : info --- 系统网络信息
*
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_getNetInfo(DHOP_SYS_NetInfo* info);

/***************************************************************
* function name : DHOP_SYS_getCpuUsage
*
* description   : 获取系统CPU占用率
*
* input         : none
*
* output        : rate --- 系统CPU占用率,例如12，表示系统CPU占用率为12%
*
* notice        : 1. 接口线程安全. 2. 接口为同步接口，不建议调用频率过高,会影响效率
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_getCpuUsage(DH_Uint32* rate);


/***************************************************************
* function name : DHOP_SYS_restoreDefault
*
* description   : 系统恢复默认
*
* input         : type  -- 恢复类型，具体参见DHOP_SYS_restoreType
*
* output        : none
*
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 DHOP_ERR_INVALID_PARMETER - type传入不支持的类型
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_restoreDefault(DHOP_SYS_restoreType type);


/***************************************************************
* function name : DHOP_SYS_updateAccount
*
* description   : 更新帐号
*
* input         : oldAccount -- 旧帐号
*               : newAccount -- 新帐号
*
* output        : none
*
* notice        : 1. 接口线程安全.
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 DHOP_ERR_PARAM_IS_NULL - oldAccount或newAccount是NULL
*                 DHOP_ERR_RESOURCE_BUSY - 当前帐号正在使用
*                 DHOP_ERR_SYS_USERNAME_MODIFY_UNSUPPORT - DHOP_SYS_ACCOUNT_UPGRADE帐号的username不支持修改
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_updateAccount(const DHOP_SYS_Account *oldAccount, const DHOP_SYS_Account *newAccount);

/*******************************************************************************
* function name  : DHOP_SYS_syncTimeByNtpImmediately
*
* description    : 主动触发系统Ntp时间同步
*
* input          : None
*
* output         : None
*
* notice        : 1. 接口线程安全. 2. 同步接口，不建议频繁调用。返回值即执行结果
* return value   : DHOP_SUCCESS - 成功
*                : 其他  - 失败
*                : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_SYS_syncTimeByNtpImmediately();

/***************************************************************
* function name : DHOP_SYS_getAppRunEnv
*
* description   : 获取App的运行环境(受License的权限控制)
*                 当获取成功后，需要通过DHOP_SYS_keepAppRunEnv进行保活,一般周期是2-3秒
*
* input         : app       --- 指定的App
* input         : pAddr     --- 存放返回结果的Buffer，Buffer由调用者提供
* input         : pSize     --- Buffer大小，由调用者指定
*
* output        : pAddr     --- 返回的运行环境地址
* output        : pSize     --- 地址长度
* notice        : 1. 接口线程安全.
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_getAppRunEnv(const DH_String app, DH_Byte* pAddr, DH_Uint32* pSize);

/***************************************************************
* function name : DHOP_SYS_keepAppRunEnv
*
* description   : 保活正在访问的App运行环境
*
* input         : app       --- 保活的App
*
* notice        : 1. 接口线程安全.
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_keepAppRunEnv(const DH_String app);

/***************************************************************
* function name : DHOP_SYS_getAccountCapability
*
* description   : 获取系统账户管理的能力
*
* input         : none
*
* output        : pCapability       --- 系统账户管理的能力
*
* notice        : 1. 接口线程安全.
*                 2. 接口受证书权限控制
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_getAccountCapability(DHOP_SYS_AccountCapability* pCapability);

/***************************************************************
* function name : DHOP_SYS_addUser
*
* description   : 添加新的系统账户
*
* input         : pInfo       --- 新的账户信息
*
* notice        : 1. 接口线程安全.
*                 2. 接口受证书权限控制
*                 3. 同一个app所有者能添加的最大账户个数可以通过DHOP_SYS_getAccountCapability获取
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_addUser(const DHOP_SYS_Account* pInfo);

/***************************************************************
* function name : DHOP_SYS_deleteUser
*
* description   : 删除指定的用户
*
* input         : username       --- 指定的用户名
*
* notice        : 1. 接口线程安全.
*                 2. 接口受证书权限控制
*                 3. 只能删除DHOP_SYS_addUser添加的用户
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_deleteUser(const DH_Char* username);

/***************************************************************
* function name : DHOP_SYS_modifyPassword
*
* description   : 修改指定用户的密码,支持修改admin账户密码
*
* input         : username       --- 指定待修改密码的账户名称
* input         : oldPassword    --- 该账户的密码.修改用户密码，需要先校验老密码
* input         : newPassword    --- 指定的新密码
*
* notice        : 1. 接口线程安全.
*                 2. 新密码长度最大DHOP_MAX_SYS_ACCOUNT_LENGTH-1字节.
*                 3. 接口受证书权限控制
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_modifyPassword(const DH_Char* username, const DH_Char* oldPassword, const DH_Char* newPassword);

/***************************************************************
* function name : DHOP_SYS_modifyUser
*
* description   : 修改指定的用户信息
*
* input         : username       --- 指定待修改的账户名称
* input         : oldPassword    --- 该账户的密码.修改用户信息，需要校验密码
* input         : pInfo          --- 新的账户信息
*
* notice        : 1. 接口线程安全.
*                 2. 该接口不能修改用户名和密码.
*                 3. 如果修改密码，请使用DHOP_SYS_modifyPassword.
*                 4. 接口受证书权限控制
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_modifyUser(const DH_Char* username, const DH_Char* oldPassword, const DHOP_SYS_Account* pInfo);

/***************************************************************
* function name : DHOP_SYS_getUser
*
* description   : 获取指定的系统账户的信息
*
* input         : username       --- 指定的账户名
* output        : pInfo          --- 返回的账户信息
*
* notice        : 1. 接口线程安全.
*                 2. 返回的账户信息中不包含密码
*                 3. 接口受证书权限控制
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_getUser(const DH_Char* username, DHOP_SYS_Account* pInfo);

/***************************************************************
* function name : DHOP_SYS_getAllUser
*
* description   : 获取APP所属的所有系统账户信息
*
* input         : pList       --- 用户指定的账户列表缓存
* output        : pList       --- 返回的账户信息列表
*
* notice        : 1. 接口线程安全.
*                 2. 返回的账户信息中不包含密码
*                 3. 接口受证书权限控制
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_SYS_getAllUser(DHOP_SYS_AccountList* pList);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_SYS_H__


