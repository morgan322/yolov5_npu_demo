/*******************************************************************************
 * dhop_app.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义APP相关的数据结构与API，本模块设计到的信息均为当前APP相关的
 *              信息。
 *
 *******************************************************************************/

#ifndef __DHOP_APP_H__
#define __DHOP_APP_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"


/*******************************************************************************/

/* max path length */
#define DHOP_APP_PATH_MAX_LENGTH       128

/* max partition num */
#define DHOP_APP_PARTITION_NUM         8

#define DHOP_APP_UPDATE_MSG_LEN         32

#define DHOP_MAX_PROCESS_NAME_LENGTH    (16)
#define DHOP_MAX_CPU_INFO_COUNT         (8)

#define DHOP_MAX_ACCOUNT_USR_LEN        32
#define DHOP_MAX_ACCOUNT_PWD_LEN        32

/*******************************************************************************/

/* 存储空间类型 */
typedef enum
{
    DHOP_APP_DIR_TYPE_UNKNOWN = 0,              /* 未知 */
    DHOP_APP_DIR_TYPE_FLASH,                    /* FLASH存储空间(可持久化) */
    DHOP_APP_DIR_TYPE_MEMORY,                   /* 内存存储空间(不可持久化) */
    DHOP_APP_DIR_TYPE_SDCARD,                   /* SD卡存储空间 */
    DHOP_APP_DIR_TYPE_NAS,                      /* NAS网络存储空间 */
} DHOP_APP_DirType;

/* URL升级的包类型 */
typedef enum
{
    DHOP_APP_URL_TYPE_LICENSE = 0,              /* URL地址指向License文件 */
    DHOP_APP_URL_TYPE_APPPKG,                   /* URL地址指向APP数据包文件 */
    DHOP_APP_URL_TYPE_OS_FIRMWARE,              /* URL地址指向OS固件包文件，需要License授权许可 */
    DHOP_APP_URL_TYPE_MAX,
} DHOP_APP_UpdateUrlType;

/* APP Package校验的方式 */
typedef enum
{
    DHOP_APP_PKG_VERIFY_NONE  = 0,
    DHOP_APP_PKG_VERIFY_MD5,                    /* 采用MD5算法对程序包进行哈希校验,MD5值为16进制字符串*/
} DHOP_APP_PkgVerifyMethod;

/* APP上次退出的状态码 */
typedef enum
{
    DHOP_APP_LAST_EXIT_CODE_UNKNOWN = 0,
    DHOP_APP_LAST_EXIT_CODE_NONE,               /* APP首次启动，无退出码 */
    DHOP_APP_LAST_EXIT_CODE_NORMAL,             /* APP正常退出 */
    DHOP_APP_LAST_EXIT_CODE_ABNORMAL,           /* APP未能及时正常退出而被强制退出 */
    DHOP_APP_LAST_EXIT_CODE_UPGRADE,            /* APP因升级导致退出 */
    DHOP_APP_LAST_EXIT_CODE_CRASH,              /* APP因异常崩溃退出 */
    DHOP_APP_LAST_EXIT_CODE_POWERDOWN,          /* APP因设备断电而退出 */
    DHOP_APP_LAST_EXIT_CODE_OS_CRASH,           /* APP因OS崩溃而退出 */
    DHOP_APP_LAST_EXIT_CODE_OS_REBOOT,          /* APP因OS正常重启而退出 */
    DHOP_APP_LAST_EXIT_CODE_OS_RESTORE,         /* APP因OS恢复默认退出 */
    DHOP_APP_LAST_EXIT_CODE_RESTART_SELF,       /* APP因自己调用重启接口而退出 */
} DHOP_APP_LastExitCode;

/* APP账户的权限掩码 */
typedef enum
{
    DHOP_APP_Account_Auth_None          = 0,
    DHOP_APP_Account_Auth_UserMgr       = 0x1,      /* 用户管理 */
    DHOP_APP_Account_Auth_Monitor       = 0x2,      /* 实时预览 */
    DHOP_APP_Account_Auth_Replay        = 0x4,      /* 回放 */
    DHOP_APP_Account_Auth_SysCfg        = 0x8,      /* 系统管理 */
    DHOP_APP_Account_Auth_SysInfo       = 0x10,     /* 系统信息 */
    DHOP_APP_Account_Auth_ManuCtr       = 0x20,     /* 手动控制 */
    DHOP_APP_Account_Auth_Backup        = 0x40,     /* 文件备份 */
    DHOP_APP_Account_Auth_StoreCfg      = 0x80,     /* 存储管理 */
    DHOP_APP_Account_Auth_EventCfg      = 0x100,    /* 事件管理 */
    DHOP_APP_Account_Auth_NetCfg        = 0x200,    /* 网络管理 */
    DHOP_APP_Account_Auth_Peripheral    = 0x400,    /* 外设管理 */
    DHOP_APP_Account_Auth_AVParam       = 0x800,    /* 音视频参数 */
    DHOP_APP_Account_Auth_Security      = 0x1000,   /* 安全管理 */
    DHOP_APP_Account_Auth_Maintence     = 0x2000,   /* 设备维护 */
} DHOP_APP_AccountAuthMask;

/* 自定义数据回调的类型 */
typedef enum
{
    DHOP_APP_Custom_Data_Desc = 1,              /* 自定义数据的描述, 由App自己解析 */
    DHOP_APP_Custom_Data_Body,                  /* 自定义数据, 由App自己处理 */
    DHOP_APP_Custom_Data_End,                   /* 自定义数据完成 */
} DHOP_APP_Custom_DataType;

/* APP访问的路径类型 */
typedef enum
{
    DHOP_APP_WorkPath_Bin = 0,                  /* APP程序区 */
    DHOP_APP_WorkPath_Max,
} DHOP_APP_WorkPath;

/* APP访问的权限 */
typedef enum
{
    DHOP_APP_PathMode_ReadOnly = 0,              /* APP只读权限 */
    DHOP_APP_PathMode_ReadWrite,                 /* APP读写权限 */
    DHOP_APP_PathMode_Max,
} DHOP_APP_PathMode;
/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)                   // 32位系统下结构体定义
/* DHOP_APP_Version 结构体 */
typedef struct
{
    DH_String                   version;        /* 版本信息，打包时Configure中AppVersion字段，调用者无需填写，由接口内部赋值 */
    DH_Uint32                   reserved[15];   /* 保留字段 */
} DHOP_APP_Version;


typedef struct
{
    DH_Uint8                    path[DHOP_APP_PATH_MAX_LENGTH];      /* 文件夹路径 */
    DH_Uint64                   tBytes;         /* 可存储空间大小 */
    DH_Uint64                   fBytes;         /* 剩余空闲空间大小*/
    DH_Uint8                    type;           /* 目录类型. 参考DHOP_APP_DirType */
    DH_Uint8                    res[3];         /* 保留字段 */
    DH_Uint32                   reserved[5];    /* 保留字段 */
} DHOP_APP_Directory;

/* DHOP_APP_PathInfo 结构体 */
typedef struct
{
    DH_Uint8                    count;          /* APP可访问的路径个数，最大8，调用者无需填写，由接口内部赋值*/
    DHOP_APP_Directory          parts[DHOP_APP_PARTITION_NUM];       /* 路径信息，调用者无需填写，由接口内部赋值 */
} DHOP_APP_PathInfo;


typedef struct
{
    DH_Bool                     watchdog;       /* 当前进程是否使能看门狗进行监测，TRUE--使能，调用者选填*/
    DH_Char                     res[3];         /* 保留字段 */
    DH_Uint32                   urllen;         /* weburl字符串长度，调用者选填*/

    /*
    APP配置首页的路径，采用相对地址，相对路径根为Package/web/。
    比如在APP打包工程中Package/web目录下，有一个index.html文件，则weburl填写为"index.html"
    */
    DH_Char*                    weburl;         /* 调用者选填（urllen与weburl必须配合使用） */
    DH_Char*                    previewUrl;     /* 调用者选填 */
    DH_Uint8                    disableFaultRecovery;   /* 当该字段非0时，表示DHOP_OS将忽略APP的故障监测和恢复,由APP自行处理.不推荐使用，调用者选填*/
    DH_Uint8                    reserve[27];    /* 保留字段 */
} DHOP_APP_ConfigParam;


/* APP更新升级的参数 */
typedef struct
{
    DHOP_APP_UpdateUrlType      type;           /* URL指向的升级文件类型，调用者必填 */
    /*
        url目前支持的协议包含: http/https/file/，举例：
        file:///etc/a.txt -- 路径为绝对路径/etc/a.txt;
        file://etc/a.txt  -- 路径为APP相对安装目录下的<APP_ROOT_DIR>/etc/a.txt
    */
    DH_String url;                              /* 升级文件的URL地址，以'\0'结束，调用者必填 */
    struct
    {
        DHOP_APP_PkgVerifyMethod    method;     /* 升级包校验方法，APP升级功能，则调用者必填 */
        DH_Char                     *code;      /* 校验码,16进制字符串,'\0'结束，APP升级功能并选择MD5校验方式，则调用者必填*/
    } verify;  
    DH_Uint8                    reserved[32];
} DHOP_APP_UpdateParam;

/* 最后一次升级的结果，调用者无需填写，由接口内部赋值 */
typedef struct
{
    DH_Char                     stateMsg[DHOP_APP_UPDATE_MSG_LEN];      /* 升级状态 */
    DH_Uint32                   priv;                                   /* 当前状态的标识，可以通过priv是否变化来判定状态是否更新 */
    DH_Char                     reserved[32];                           /* 保留字段 */
} DHOP_APP_UpState;

/* APP进程的CPU占用率 */
typedef struct
{
    DH_Uint8             rate;                               /* CPU占用率,百分比, 例如12表示占用率为12%，调用者无需填写，由接口内部赋值 */
    DH_Uint8             res[3];
    DH_Char              name[DHOP_MAX_PROCESS_NAME_LENGTH]; /* 进程名称，调用者无需填写，由接口内部赋值 */
} DHOP_APP_CpuUsage;

/* APP可用的账户信息 */
typedef struct
{
    DH_Char                     username[DHOP_MAX_ACCOUNT_USR_LEN];     /* 用户名，调用者无需填写，由接口内部赋值 */
    DH_Char                     password[DHOP_MAX_ACCOUNT_PWD_LEN];     /* 密码，调用者无需填写，由接口内部赋值 */
    DH_Uint32                   authMask;                               /* 权限掩码，由APP证书定义，见DHOP_APP_AccountAuthMask，调用者无需填写，由接口内部赋值 */
    DH_Uint32                   expired;                                /* 有效时间(ms), 由APP证书定义，调用者无需填写，由接口内部赋值*/
    DH_Char                     res[32];
} DHOP_APP_Account;

/// APP运行统计信息
typedef struct
{
    DH_Uint16                   cbSize;                 // 当前结构体大小，sizeof(DHOP_APP_RunStats),调用者提供
    DH_Uint16                   res;                    // 保留字段
    DH_Uint32                   startupTimes;           // APP启动次数，设备重启后，次数会重新从0开始计
} DHOP_APP_RunStats;

#endif
#if (__SIZEOF_POINTER__ == 8)                   // 64位系统下结构体定义
/* DHOP_APP_Version 结构体 */
typedef struct
{
    DH_String                   version;        /* 版本信息，打包时Configure中AppVersion字段，调用者无需填写，由接口内部赋值*/
    DH_Uint32                   reserved[16];   /* 保留字段 */
} DHOP_APP_Version;


typedef struct
{
    DH_Uint8                    path[DHOP_APP_PATH_MAX_LENGTH];      /* 文件夹路径 */
    DH_Uint64                   tBytes;         /* 可存储空间大小 */
    DH_Uint64                   fBytes;         /* 剩余空闲空间大小*/
    DH_Uint8                    type;           /* 目录类型. 参考DHOP_APP_DirType */
    DH_Uint8                    res[3];         /* 保留字段 */
    DH_Uint32                   reserved[5];    /* 保留字段 */
} DHOP_APP_Directory;

/* DHOP_APP_PathInfo 结构体 */
typedef struct
{
    DH_Uint8                    count;                               /* APP可访问的路径个数，最大8，调用者无需填写，由接口内部赋值*/
    DHOP_APP_Directory          parts[DHOP_APP_PARTITION_NUM];       /* 路径信息，调用者无需填写，由接口内部赋值*/
} DHOP_APP_PathInfo;


typedef struct
{
    DH_Bool                     watchdog;       /* 当前进程是否使能看门狗进行监测，TRUE--使能，调用者选填*/
    DH_Char                     res[3];         /* 保留字段 */
    DH_Uint32                   urllen;         /* weburl字符串长度，调用者选填*/

    /*
    APP配置首页的路径，采用相对地址，相对路径根为Package/web/。
    比如在APP打包工程中Package/web目录下，有一个index.html文件，则weburl填写为"index.html"
    */
    DH_Char*                    weburl;         /* 调用者选填（urllen与weburl必须配合使用）*/
    DH_Char*                    previewUrl;     /* 调用者选填 */
    DH_Uint8                    disableFaultRecovery;   /* 当该字段非0时，表示DHOP_OS将忽略APP的故障监测和恢复,由APP自行处理.不推荐使用，调用者选填*/
    DH_Uint8                    reserve[23];    /* 保留字段 */
} DHOP_APP_ConfigParam;


/* APP更新升级的参数 */
typedef struct
{
    DHOP_APP_UpdateUrlType      type;           /* URL指向的升级文件类型，调用者必填 */
    DH_Uint8                    res[4];         /* 保留字段 */
    DH_String url;                              /* 升级文件的URL地址，以'\0'结束，调用者必填 */
    struct
    {
        DHOP_APP_PkgVerifyMethod method;        /* 升级包校验方法，APP升级功能，则调用者必填 */
        DH_Uint8                    res[4];     /* 保留字段 */
        DH_Char *code;                          /* 校验码,16进制字符串,'\0'结束，APP升级功能并选择MD5校验方式，则调用者必填*/
    } verify;                                   
    DH_Uint8                    reserved[32];
} DHOP_APP_UpdateParam;

/* 最后一次升级的结果，调用者无需填写，由接口内部赋值 */
typedef struct
{
    DH_Char                     stateMsg[DHOP_APP_UPDATE_MSG_LEN];      /* 升级状态 */
    DH_Uint32                   priv;                                   /* 当前状态的标识，可以通过priv是否变化来判定状态是否更新 */
    DH_Char                     reserved[32];                           /* 保留字段 */
} DHOP_APP_UpState;

/* APP进程的CPU占用率 */
typedef struct
{
    DH_Uint8             rate;                               /* CPU占用率,百分比, 例如12表示占用率为12%，调用者无需填写，由接口内部赋值 */
    DH_Uint8             res[3];
    DH_Char              name[DHOP_MAX_PROCESS_NAME_LENGTH]; /* 进程名称，调用者无需填写，由接口内部赋值*/
} DHOP_APP_CpuUsage;

/* APP可用的账户信息 */
typedef struct
{
    DH_Char                     username[DHOP_MAX_ACCOUNT_USR_LEN];     /* 用户名，调用者无需填写，由接口内部赋值 */
    DH_Char                     password[DHOP_MAX_ACCOUNT_PWD_LEN];     /* 密码，调用者无需填写，由接口内部赋值 */
    DH_Uint32                   authMask;                               /* 权限掩码，由APP证书定义，见DHOP_APP_AccountAuthMask，调用者无需填写，由接口内部赋值 */
    DH_Uint32                   expired;                                /* 有效时间(ms), 由APP证书定义*/
    DH_Char                     res[32];
} DHOP_APP_Account;

/// APP运行统计信息
typedef struct
{
    DH_Uint16                   cbSize;                 // 当前结构体大小，sizeof(DHOP_APP_RunStats),调用者提供
    DH_Uint16                   res;                    // 保留字段
    DH_Uint32                   startupTimes;           // APP启动次数，设备重启后，次数会重新从0开始计
} DHOP_APP_RunStats;

#endif

/*******************************************************************************/


/***************************************************************
* function name : DHOP_APP_getVersion
*
* description   : 获取当前APP的版本信息
*
* input         : none
*
* output        : pInfo -- App版本信息，接口内部赋值
*
* notice        : 1. 接口线程安全.
*
* example       : ----------------------------------------------
*                 DHOP_APP_Version   ver;
*                 ret = DHOP_APP_getVersion(&ver);
*                 ----------------------------------------------
*
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_APP_getVersion(DHOP_APP_Version * pInfo);


/***************************************************************
* function name : DHOP_APP_setWatchdog(use setAppConfig)
*
* description   : this API is used to enable or disable agent watchdog
*                 if agent not set, wathdog will be disable by default
*
* input         : enable -- 0:disable agent watchdog, 1:enable agent watchdog
*
* output        : None
* notice        : 1. 接口线程安全. 2. 不建议调用,看门狗开关，建议使用DHOPAPP_SetConfig
*
* return value  : None
***************************************************************/
DH_Void DHOP_APP_setWatchdog(DH_Bool32 enable);


/***************************************************************
* function name : DHOP_APP_getCurrentPath
*
* description   : get current program path
*
* input         : path -- pre-allocated memory to store path
*                 size -- memory size, in bytes
*
* output        : path -- current path string, null-terminator
* notice        : 1. 接口线程安全.
*
* return value  : DH_TRUE:  success
*                 DH_FALSE: fail
***************************************************************/
DH_Bool DHOP_APP_getCurrentPath(DH_Char *path, DH_Uint32 size);

/***************************************************************
* function name : DHOP_setAppConfig
*
* description   : this API is used to set the app configs
*
* input         : config -- APP参数，由调用者填写；
*                           填写要求可参考DHOP_APP_ConfigParam注释；
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : None
***************************************************************/
DH_Void DHOP_APP_setConfig(DHOP_APP_ConfigParam* config);

/***************************************************************
* function name : DHOP_APP_getPathInfo
*
* description   : this API is used to get storage info for agent read/write files
*
* input         : info -- 调用者提供未赋值的《DHOP_APP_PathInfo》结构体，以指针形式传入
*
* output        : info -- 存储路径信息，由接口内部赋值
* 
* notice        : 1. 接口线程安全. 2. 同步接口, 不建议调用频率过高
*
* return value  : DHOP_SUCCESS: success
*               : DHOP_FAILED:  fail
*               : other: ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_APP_getPathInfo(DHOP_APP_PathInfo* info);

/***************************************************************
* function name : DHOP_APP_ExitCallback
*
* description   : function pointer used for abnormal exiting
*
* input         : None
*
* output        : None
*
* return value  : None
***************************************************************/
typedef DH_Void (*DHOP_APP_ExitCallback)(DH_Void);

/***************************************************************
* function name : DHOP_APP_regExitCallback
*
* description   : this API is used to register a callback function
*                 to do something(resources recovery, etc) for abnormal exiting
*
* input         : callback -- callback function, see ExitCallback
*
* output        : None
* notice        : 1. 接口线程安全.2. 不建议调用,退出回调在DHOP_SYS_Init中指定即可
*
* return value  : None
***************************************************************/
DH_Void DHOP_APP_regExitCallback(DHOP_APP_ExitCallback callback);


/***************************************************************
* function name : DHOP_APP_updateByURL
*
* description   : 通过外部提供URL升级包地址的方式，让DHOP进行数据升级，
*                 该接口负责将参数提供给DHOP，接口返回仅代表参数下发，
*                 升级过程由异步方式实现，升级过程中会有短暂的结束APP运行，
*                 随后自动启动APP继续运行。
*
* input         : pParam   -- 更新升级的参数，由调用者填写，填写注意事项可参考DHOP_APP_UpdateParam结构体注释
*
* output        : None
*
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS : 成功
*               : DHOP_FAILED  : 失败
*               : 其它         : 参考 DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_APP_updateByURL(DHOP_APP_UpdateParam * pParam);

/***************************************************************
* function name : DHOP_APP_resetWatchdog
*
* description   : 在watchdog enable后，默认无超时.如果需要watchdog有超时机制,则调用此接口
*                 watchdog在超时后,则会主动退出进程,并重启进程
*                 因此用户在watchdog enable后，设置了超时时间,则需要在超时时间内主动reset watchdog.并设置下次超时的时间
*
* input         : timeout -- 下次超时的时间(单位秒),如果为0表示永不超时
*
* output        : none
* notice        : 1. 接口线程安全.
*
* example       : ----------------------------------------------
*                 DHOP_APP_setWatchdog(true);
*                 DHOP_APP_resetWatchdog(3);
*                 while(1)
*                 {
*                       /// do something
*                       /// ...
*                       DHOP_APP_resetWatchdog(3);
*                 }
*                 ----------------------------------------------
*
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_APP_resetWatchdog(DH_Uint32 timeout);


/***************************************************************
* function name : DHOP_APP_getCpuUsage
*
* description   : 获取当前APP各进程的CPU使用率。
*
* input         : szUsage   -- 各进程cpu占用率信息的数组buffer
*                 count     -- 入参szUsage的数组元素个数,一般和app进程个数一致
*
* output        : szUsage   -- 各进程的cpu占用率信息。
*               : count     -- 出参数组szUsage的实际有效元素个数
* notice        : 1. 接口线程安全. 2. 接口为同步接口，不建议调用频率过高,会影响效率
*
* example       : ----------------------------------------------
*                 DHOP_APP_CpuUsage   cpuinfo[8];
*                 DH_Uint32 count = 8;
*                 int ret = DHOP_APP_getCpuUsage(cpuinfo, &count);
*                 for (int i = 0; i < count; i++)
*                 {
*                       printf("%s : %d\n", cpuinfo[i].name, cpuinfo[i].rate);
*                 }
*                 ----------------------------------------------
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_APP_getCpuUsage(DHOP_APP_CpuUsage *szUsage, DH_Uint32 *count);

/***************************************************************
* function name : DHOP_APP_getLastExitCode
*
* description   : 获取当前APP最后一次的退出码。
*
* input         : none
*
* output        : code   -- 退出码
* notice        : 1. 接口线程安全.
*
*
* return value  : none
***************************************************************/
DH_Void DHOP_APP_getLastExitCode(DHOP_APP_LastExitCode* code);

/***************************************************************
* function name : DHOP_APP_getDahuaAccount
*
* description   : APP获取一个临时受限的dahua账户。
*
* input         : none
*
* output        : info   -- 临时受限的dahua账户信息。
* notice        : 1. 接口线程安全.
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_APP_getDahuaAccount(DHOP_APP_Account* info);

/***************************************************************
* function name : DHOP_APP_restart
*
* description   : 重启App
*
* input         : delayMs --- 延时时间,毫秒(ms)。即延时多长时间后重启app,0表示马上重启
*
* output        : none
* notice        : 1. 接口线程安全.
*               : 2: 接口返回值仅表示命令下发成功
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_APP_restart(DH_Uint32 delayMs);

/***************************************************************
* function name : DHOP_APP_chmod
*
* description   : 修改App访问路径的权限。注意当App重启后,权限会恢复为默认。
*
* input         : mode --- 权限描述,参考DHOP_APP_BinMode
*
* output        : none
* notice        : 1. 接口线程安全.
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_APP_chmod(DHOP_APP_WorkPath path, DHOP_APP_PathMode mode);

/***************************************************************
* function name : DHOP_APP_getLicValue
*
* description   : 获取当前App所用的license信息。
*
* input         : key     --- license中的字段名称
* input         : pBuffer --- 存放结果的buffer，Buffer由调用者提供
* input         : pSize   --- 存放结果的buffer大小，由调用者指定
*
* output        : pBuffer --- 结果内容
* output        : pSize   --- 结果大小
* notice        : 1. 接口线程安全.
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_APP_getLicValue(const DH_String key, DH_Byte* pBuffer, DH_Uint32* pSize);

/***************************************************************
* function name : DHOP_APP_getAppName
*
* description   : 获取当前App的名字。
*
* input         : pNameBuf --- 用于存放APP名字的buffer，由调用者提供
* input         : pSize    --- 存放APP名字的buffer大小
*
* output        : pNameBuf --- APP名字，字符串结尾含有'\0'
* output        : pSize    --- APP名字实际长度，包括结束符
*
* notice        : 1. 接口线程安全.
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_APP_getAppName(DH_Byte* pNameBuf, DH_Uint32* pSize);

/***************************************************************
* function name : DHOP_APP_getRunStats
*
* description   : 获取当前App运行统计信息
*
* input         : info  ---  存放APP运行状态信息
*
* output        : info ---   APP运行统计信息
*
* notice        : 1. 接口线程安全.
*
* return value  : =0表示成功
*                 <0表示其它错误，参见DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_APP_getRunStats(DHOP_APP_RunStats *info);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_APP_H__


