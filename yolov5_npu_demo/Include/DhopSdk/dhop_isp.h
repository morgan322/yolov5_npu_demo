/*******************************************************************************
 * dhop_isp.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义ISP模块的数据结构与API。
 *
 *******************************************************************************/

#ifndef __DHOP_ISP_H__
#define __DHOP_ISP_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"

/*******************************************************************************/


/* ISP功能模块ID */
typedef enum
{
    DHOP_ISP_MODULE_ID_ROI_EXP   = 0,           /* 参考感兴趣区域统计信息进行曝光 */
    DHOP_ISP_MODULE_ID_WDR,                     /* 图像宽动态 */
    DHOP_ISP_MODULE_ID_3DNR,                    /* 图像3D降噪 */
    DHOP_ISP_MODULE_ID_MAX,
} DHOP_ISP_ModuleID;


/* 画面感兴趣区域曝光模式 */
typedef enum
{
    /* 画面整体的曝光参考依据为指定ROI区域的图像信息 */
    DHOP_ISP_ROI_EXP_MODE_GLOBAL = 0,

    /* 画面整体的曝光参考依据为画面整体的图像信息，ROI区域的曝光参数独立计算设置 */
    DHOP_ISP_ROI_EXP_MODE_REGION,
} DHOP_ISP_RoiExpMode;


/* 设备支持的画面感兴趣区域曝光模式能力集 */
typedef enum
{
    DHOP_ISP_ROI_EXP_MASK_GLOBAL = (1 << DHOP_ISP_ROI_EXP_MODE_GLOBAL),
    DHOP_ISP_ROI_EXP_MASK_REGION = (1 << DHOP_ISP_ROI_EXP_MODE_REGION),
} DHOP_ISP_RoiExpMask;

/* 配置文件类型 */
typedef enum
{
    DHOP_ISP_CONFIG_FILE_TYPE_DAY = 0,            /* 白天 */
    DHOP_ISP_CONFIG_FILE_TYPE_NIGHT,              /* 夜晚 */
    DHOP_ISP_CONFIG_FILE_TYPE_COMMON,             /* 普通 */

    DHOP_ISP_CONFIG_TYPE_MAX,
} DHOP_ISP_ConfigFileType;

/* 配置文件类型掩码 */
typedef enum
{
    DHOP_ISP_CONFIG_FILE_TYPE_MASK_DAY = (1 << DHOP_ISP_CONFIG_FILE_TYPE_DAY),
    DHOP_ISP_CONFIG_FILE_TYPE_MASK_NIGHT = (1 << DHOP_ISP_CONFIG_FILE_TYPE_NIGHT),
    DHOP_ISP_CONFIG_FILE_TYPE_MASK_COMMON = (1 << DHOP_ISP_CONFIG_FILE_TYPE_COMMON),
} DHOP_ISP_ConfigFileTypeMask;
/*******************************************************************************/


#if (__SIZEOF_POINTER__ == 4)                     // 32位系统下结构体定义
/* ISP模块矩形框结构体 */
typedef struct
{
    DH_Uint16               x;                    /* 左上角水平x坐标，归一化坐标系8192 */
    DH_Uint16               y;                    /* 左上角垂直y坐标，归一化坐标系8192 */
    DH_Uint16               w;                    /* 水平宽度，归一化坐标系8192 */
    DH_Uint16               h;                    /* 水平高度，归一化坐标系8192 */
} DHOP_ISP_Rect;


/* ISP模块打开参数 */
typedef struct
{
    /* 通道ID，取值范围[0,n)，最大值n为DHOP_ISP_getChannelNum接口返回的值,调用者必填 */
    DH_Uint8                channelId;
    DH_Uint8                resByte[3];           /* 保留字段 */
    DH_Int32                reserved[7];          /* 保留字段 */
} DHOP_ISP_OpenParam;


/* ISP模块能力集,调用者无需填写*/
typedef struct
{
    DH_Uint32               modMask;              /* 当前设备支持的ISP模块,  参考DHOP_ISP_ModuleID */
    DH_Int16                maxRoiExpNum;         /* 当前设备支持的最大ROI区域个数 */
    DH_Int16                roiExpMask;           /* 当前设备支持的曝光模式，参考DHOP_ISP_RoiExpMask */
    DH_Int16                minBright;            /* 当前设备支持的最小亮度 */
    DH_Int16                maxBright;            /* 当前设备支持的最大亮度 */
    DH_Int16                min3DnrVal;           /* 当前设备支持的最小3D降噪设置值 */
    DH_Int16                max3DnrVal;           /* 当前设备支持的最大3D降噪设置值 */
    DH_Int16                minWdrVal;            /* 当前设备支持的最小WDR设置值 */
    DH_Int16                maxWdrVal;            /* 当前设备支持的最大WDR设置值 */
    DH_Uint32               cfgFileTypeMask;      /* 当前设备支持的配置文件类型掩码 */
    DH_Int32                reserved[10];         /* 保留字段 */
} DHOP_ISP_Capalitity;


/* ISP模块YUV参数 */
typedef struct
{
    DH_Uint16               width;                /* YUV宽度 */
    DH_Uint16               height;               /* YUV高度 */
    DH_Uint16               stride;               /* YUV跨距 */
    DH_Uint16               resBytes;             /* 保留字段 */
    DH_Uint8                *virAddr;             /* YUV数据的虚拟地址 */
} DHOP_ISP_YuvParam;


/* ISP模块中ROI曝光区域 */
typedef struct
{
    DH_Int8                 expMode;              /* 画面感兴趣区域曝光模式，参考DHOP_ISP_RoiExpMode */
    DH_Int8                 regionNum;            /* 曝光ROI区域个数，不允许超过最大个数DHOP_ISP_Capalitity.maxRoiExpNum*/
    DH_Uint8                intelliFps;           /* 算法检测帧率 */
    DH_Int8                 resBytes;             /* 保留字段 */
    DHOP_ISP_Rect           *rect;                /* 曝光ROI区域列表 */
    DHOP_ISP_YuvParam       yuv;                  /* 感兴趣区域所在帧的YUV数据信息 */
    DH_Int32                reserved[14];         /* 保留字段 */
} DHOP_ISP_RoiExpRegion;


/* ISP模块ROI曝光参数 */
typedef struct
{
    DH_Int8                 bright;               /* 曝光亮度,取值范围 [0-100].默认值为50 */
    DH_Int8                 resBytes;             /* 保留字段 */
    DH_Uint16               interval;             /* 区域曝光亮度保持的时间 [0,65536) 单位:秒.默认值为5*/
    DH_Int32                reserved[7];
} DHOP_ISP_RoiExpParam;

/* ISP模块WDR参数  */
typedef struct
{
    DH_Uint8                cfgFileType;          /* 配置文件类型,参考DHOP_ISP_ConfigFileType,调用者必填 */
    DH_Uint8                value;                /* WDR强度,调用者必填 */
    DH_Uint16               resByte;              /* 保留字段 */
    DH_Uint32               reserved[4];          /* 保留字段 */
} DHOP_ISP_WdrParam;

/* ISP模块3D降噪参数  */
typedef struct
{
    DH_Uint8                cfgFileType;          /* 配置文件类型,参考DHOP_ISP_ConfigFileType */
    DH_Uint8                value;                /* 3D降噪强度 */
    DH_Uint8                res[2];               /* 保留字段 */
    DH_Uint32               reserved[4];          /* 保留字段 */
} DHOP_ISP_3DnrParam;

/* ISP模块图像属性 */
typedef struct
{
    DH_Uint8                cfgFileType;          /* 配置文件类型,参考DHOP_ISP_ConfigFileType */
    DH_Uint8                bright;               /* 图像亮度 */
    DH_Uint16               resBytes;             /* 保留字段 */
    DH_Uint32               reserved[16];         /* 保留字段 */
} DHOP_ISP_ImgParam;

/* ISP模块配置参数 */
typedef struct
{
    DH_Uint8                type;                 /* 配置文件类型,参考DHOP_ISP_ConfigFileType */
    DH_Uint8                res[3];               /* 保留字段 */
    DH_Uint32               reserved[32];         /* 保留字段 */
} DHOP_ISP_ConfigFileParam;

/* 功能模块使能开关参数 */
typedef struct
{
    /* 对应BIT位的定义参见DHOP_ISP_ModuleID，比如使能ROI曝光模块和其它模块，可以采用如下方式：
     *      enableMask = (1 << DHOP_ISP_MODULE_ID_ROI_EXP) | (1 << DHOP_ISP_MODULE_ID_xxx);
     * 如果enableMask跟disableMask同时存在对应bit位被置1，则disableMask被采用。
     */
    DH_Uint64               enableMask;           /* 对应使能模块的ID掩码，可以支持多个模块同时使能 */
    DH_Uint64               disableMask;          /* 对应使能模块的ID掩码，可以支持多个模块同时关闭 */
} DHOP_ISP_EnableParam;
#endif

#if (__SIZEOF_POINTER__ == 8)                     // 64位系统下结构体定义
/* ISP模块矩形框结构体 */
typedef struct
{
    DH_Uint16               x;                   /* 左上角水平x坐标，归一化坐标系8192 */
    DH_Uint16               y;                   /* 左上角垂直y坐标，归一化坐标系8192 */
    DH_Uint16               w;                   /* 水平宽度，归一化坐标系8192 */
    DH_Uint16               h;                   /* 水平高度，归一化坐标系8192 */
} DHOP_ISP_Rect;


/* ISP模块打开参数 */
typedef struct
{
    /* 通道ID，取值范围[0,n), 最大值n为DHOP_ISP_getChannelNum接口返回的值,调用者必填 */
    DH_Uint8                channelId;
    DH_Uint8                resByte[3];          /* 保留字段 */
    DH_Int32                reserved[7];         /* 保留字段 */
} DHOP_ISP_OpenParam;


/* ISP模块能力集, 调用者无需填写 */
typedef struct
{
    DH_Uint32               modMask;             /* 当前设备支持的ISP模块,  参考DHOP_ISP_ModuleID */
    DH_Int16                maxRoiExpNum;        /* 当前设备支持的最大ROI区域个数 */
    DH_Int16                roiExpMask;          /* 当前设备支持的曝光模式，参考DHOP_ISP_RoiExpMask */
    DH_Int16                minBright;           /* 当前设备支持的最小亮度 */
    DH_Int16                maxBright;           /* 当前设备支持的最大亮度 */
    DH_Int16                min3DnrVal;          /* 当前设备支持的最小3D降噪设置值 */
    DH_Int16                max3DnrVal;          /* 当前设备支持的最大3D降噪设置值 */
    DH_Int16                minWdrVal;           /* 当前设备支持的最小WDR设置值 */
    DH_Int16                maxWdrVal;           /* 当前设备支持的最大WDR设置值 */
    DH_Uint32               cfgFileTypeMask;     /* 当前设备支持的配置文件类型掩码 */
    DH_Int32                reserved[12];        /* 保留字段 */
} DHOP_ISP_Capalitity;


/* ISP模块YUV参数 */
typedef struct
{
    DH_Uint16               width;               /* YUV宽度 */
    DH_Uint16               height;              /* YUV高度 */
    DH_Uint16               stride;              /* YUV跨距 */
    DH_Uint16               resBytes;            /* 保留字段 */
    DH_Uint8                *virAddr;            /* YUV数据的虚拟地址 */
} DHOP_ISP_YuvParam;


/* ISP模块中ROI曝光区域 */
typedef struct
{
    DH_Int8                 expMode;             /* 画面感兴趣区域曝光模式，参考DHOP_ISP_RoiExpMode,调用者必填 */
    DH_Int8                 regionNum;           /* 曝光ROI区域个数，不允许超过最大个数DHOP_ISP_Capalitity.maxRoiExpNum,调用者必填*/
    DH_Uint8                intelliFps;          /* 算法检测帧率,调用者必填 */
    DH_Int8                 res8;
    DH_Uint16               resBytes[2];         /* 保留字段 */
    DHOP_ISP_Rect           *rect;               /* 曝光ROI区域列表,调用者必填 */
    DHOP_ISP_YuvParam       yuv;                 /* 感兴趣区域所在帧的YUV数据信息,调用者必填 */
    DH_Int32                reserved[14];        /* 保留字段 */
} DHOP_ISP_RoiExpRegion;


/* ISP模块ROI曝光参数 */
typedef struct
{
    DH_Int8                 bright;              /* 曝光亮度,取值范围 [0-100].默认值为50,调用者选填 */
    DH_Int8                 resBytes;            /* 保留字段 */
    DH_Uint16               interval;            /* 区域曝光亮度保持的时间 [0,65536) 单位:秒.默认值为5,调用者选填 */
    DH_Int32                reserved[7];
} DHOP_ISP_RoiExpParam;

/* ISP模块WDR参数  */
typedef struct
{
    DH_Uint8                cfgFileType;         /* 配置文件类型,参考DHOP_ISP_ConfigFileType */
    DH_Uint8                value;               /* WDR强度 */
    DH_Uint16               resByte;             /* 保留字段 */
    DH_Uint32               reserved[5];         /* 保留字段 */
} DHOP_ISP_WdrParam;

/* ISP模块3D降噪参数  */
typedef struct
{
    DH_Uint8                cfgFileType;         /* 配置文件类型,参考DHOP_ISP_ConfigFileType */
    DH_Uint8                value;               /* 3D降噪强度 */
    DH_Uint8                res[2];              /* 保留字段 */
    DH_Uint32               reserved[5];         /* 保留字段 */
} DHOP_ISP_3DnrParam;

/* ISP模块图像参数 */
typedef struct
{
    DH_Uint8                cfgFileType;         /* 配置文件类型,参考DHOP_ISP_ConfigFileType */
    DH_Uint8                bright;              /* 图像亮度 */
    DH_Uint16               resBytes;            /* 保留字段 */
    DH_Uint32               reserved[17];        /* 保留字段 */
} DHOP_ISP_ImgParam;

/* ISP模块光照参数 */
typedef struct
{
    DH_Uint8                type;                /* 配置文件类型,参考DHOP_ISP_ConfigFileType */
    DH_Uint8                res[3];              /* 保留字段 */
    DH_Uint32               reserved[33];        /* 保留字段 */
} DHOP_ISP_ConfigFileParam;

/* 功能模块使能开关参数 */
typedef struct
{
    /* 对应BIT位的定义参见DHOP_ISP_ModuleID，比如使能ROI曝光模块和其它模块，可以采用如下方式：
     *      enableMask = (1 << DHOP_ISP_MODULE_ID_ROI_EXP) | (1 << DHOP_ISP_MODULE_ID_xxx);
     * 如果enableMask跟disableMask同时存在对应bit位被置1，则disableMask被采用。
     */
    DH_Uint64               enableMask;         /* 对应使能模块的ID掩码，可以支持多个模块同时使能 */
    DH_Uint64               disableMask;        /* 对应使能模块的ID掩码，可以支持多个模块同时关闭 */
} DHOP_ISP_EnableParam;


#endif


/*******************************************************************************/

/***************************************************************
* function name : DHOP_ISP_getChannelNum
*
* description   : 获取当前设备支持的ISP通道数
*
* input         : 无
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 需调用DHOP_SYS_init()初始化DHOP系统
*
* return value  : >= 0 : 通道个数
*                 < 0:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_getChannelNum(DH_Void);


/***************************************************************
* function name : DHOP_ISP_open
*
* description   : 开启ISP通道
*
* input         : pParam -- 启动参数
*                 hIsp -- 操作句柄指针
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 需调用DHOP_SYS_init()初始化DHOP系统
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_open(DHOP_ISP_OpenParam * pParam, DH_Handle * hIsp);


/***************************************************************
* function name : DHOP_ISP_close
*
* description   : 关闭ISP通道,失能ISP操作句柄
*
* input         : hIsp -- 操作句柄指针
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_close(DH_Handle *hIsp);


/***************************************************************
* function name : DHOP_ISP_getCapability
*
* description   : 获取当前设备ISP通道支持的能力集
*
* input         : hIsp -- 操作句柄
*                 pCapInfo -- 通道能力信息
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_getCapability(DH_Handle hIsp, DHOP_ISP_Capalitity * pCapInfo);


/***************************************************************
* function name : DHOP_ISP_setRoiExpRegion
*
* description   : 设置感兴趣曝光区域
*
* input         : hIsp -- 操作句柄
*                 pRegion -- 曝光区域
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*                 4. 操作句柄使能了感兴趣区域曝光
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_setRoiExpRegion(DH_Handle hIsp, DHOP_ISP_RoiExpRegion * pRegion);


/***************************************************************
* function name : DHOP_ISP_clrRoiExpRegion
*
* description   : 清除已设置的曝光区域
*
* input         : hIsp -- 操作句柄
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*                 4. 操作句柄使能了感兴趣区域曝光
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_clrRoiExpRegion(DH_Handle hIsp);


/***************************************************************
* function name : DHOP_ISP_setRoiExpParam
*
* description   : 设置感兴趣区域曝光参数
*
* input         : hIsp -- 操作句柄
*                 pParam -- 参数信息
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*                 4. 操作句柄使能了感兴趣区域曝光
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_setRoiExpParam(DH_Handle hIsp, DHOP_ISP_RoiExpParam * pParam);


/***************************************************************
* function name : DHOP_ISP_setWdrParam
*
* description   : 设置宽动态参数
*
* input         : hIsp -- ISP操作句柄
*                 pParam -- 宽动态参数
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_setWdrParam(DH_Handle hIsp, DHOP_ISP_WdrParam *pParam);


/***************************************************************
* function name : DHOP_ISP_getWdrParam
*
* description   : 获取宽动态参数
*
* input         : hIsp -- ISP操作句柄
*                 pParam -- 宽动态参数
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_getWdrParam(DH_Handle hIsp, DHOP_ISP_WdrParam *pParam);


/***************************************************************
* function name : DHOP_ISP_set3DnrParam
*
* description   : 设置3D降噪参数
*
* input         : hIsp -- ISP操作句柄
*                 pParam -- 3D降噪参数
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_set3DnrParam(DH_Handle hIsp, DHOP_ISP_3DnrParam *pParam);


/***************************************************************
* function name : DHOP_ISP_get3DnrParam
*
* description   : 获取3D降噪参数
*
* input         : hIsp -- ISP操作句柄
*                 pParam -- 3D降噪参数
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_get3DnrParam(DH_Handle hIsp, DHOP_ISP_3DnrParam *pParam);


/***************************************************************
* function name : DHOP_ISP_setImgParam
*
* description   : 设置图像参数
*
* input         : hIsp -- ISP操作句柄
*                 pParam -- 图像参数
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_setImgParam(DH_Handle hIsp, DHOP_ISP_ImgParam *pParam);


/***************************************************************
* function name : DHOP_ISP_getImgParam
*
* description   : 获取图像参数
*
* input         : hIsp -- ISP操作句柄
*                 pParam -- 图像参数
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_getImgParam(DH_Handle hIsp, DHOP_ISP_ImgParam *pParam);


/***************************************************************
* function name : DHOP_ISP_getCfgFileParam
*
* description   : 获取配置文件参数
*
* input         : hIsp -- ISP操作句柄
*                 pParam -- 文件参数
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_getCfgFileParam(DH_Handle hIsp, DHOP_ISP_ConfigFileParam *pParam);


/***************************************************************
* function name : DHOP_ISP_setCfgFileParam
*
* description   : 设置配置文件参数
*
* input         : hIsp -- ISP操作句柄
*                 pParam -- 文件参数
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_setCfgFileParam(DH_Handle hIsp, DHOP_ISP_ConfigFileParam *pParam);


/***************************************************************
* function name : DHOP_ISP_setModuleEnable
*
* description   : 对指定的ISP功能进行开关控制
*
* input         : hIsp -- ISP操作句柄
*                 pParam -- 模块使能参数
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*                 4. 开关当前设备生效配置文件下的3D降噪和宽动态功能
*                 5. 感兴趣区域曝光功能为独占资源,不支持重复开启
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_setModuleEnable(DH_Handle hIsp, DHOP_ISP_EnableParam * pParam);


/***************************************************************
* function name : DHOP_ISP_getModuleEnable
*
* description   : 获取指定模块的使能状态
*
* input         : hIsp -- ISP操作句柄
*                 pParam -- 模块使能参数
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄安全
*                 4. 获取当前设备生效配置文件下的3D降噪和宽动态开关状态
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_ISP_getModuleEnable(DH_Handle hIsp, DHOP_ISP_EnableParam * pParam);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_ISP_H__


