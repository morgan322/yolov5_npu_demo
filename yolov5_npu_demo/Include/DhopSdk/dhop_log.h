/*******************************************************************************
 * dhop_log.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义LOG模块相关的数据结构与API
 *
 *******************************************************************************/

#ifndef __DHOP_LOG_H__
#define __DHOP_LOG_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "dhop_type_def.h"


/*******************************************************************************/

/* 错误级别打印：输出内容包含行号和函数名，字体为红色 */
#define DHOP_LOG_ERROR(fmt, ...)   \
    DHOP_LOG_print(DHOP_LOG_LEVEL_ERROR, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

/* 警告级别打印：输出内容包含行号和函数名，字体为黄色 */
#define DHOP_LOG_WARN(fmt, ...)    \
    DHOP_LOG_print(DHOP_LOG_LEVEL_WARN, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

/* 提示级别打印：输出内容包含行号和函数名，字体为绿色 */
#define DHOP_LOG_INFO(fmt, ...)    \
    DHOP_LOG_print(DHOP_LOG_LEVEL_INFO, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

/* 调试级别打印：输出内容包含行号和函数名，字体为绿色 */
#define DHOP_LOG_DEBUG(fmt, ...)    \
    DHOP_LOG_print(DHOP_LOG_LEVEL_DEBUG, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)


#define DHOP_LOG_SIZE_MAX (4 * 1024 * 1024)             /* 日志文件的最大大小 */

/*******************************************************************************/

/* 日志打印级别 */
typedef enum
{
    DHOP_LOG_LEVEL_ERROR = 0,                    /* 错误级别 */
    DHOP_LOG_LEVEL_WARN,                         /* 警告级别 */
    DHOP_LOG_LEVEL_INFO,                         /* 提示级别 */
    DHOP_LOG_LEVEL_DEBUG,                        /* 调试级别 */

    DHOP_LOG_LEVEL_BUTT
} DHOP_LOG_Level;


/* 日志输出目的地 */
typedef enum
{
    DHOP_LOG_DEST_WEB  = 0,                     /* 输出到web端 */
    DHOP_LOG_DEST_TTY,                          /* 输出到控制台端 */
    DHOP_LOG_DEST_FILE,                         /* 输出到本地日志文件 */

    DHOP_LOG_DEST_NUM,
} DHOP_LOG_OutDestn;

/* 日志的前缀 */
typedef enum
{
    DHOP_LOG_PREFIX_TIME     = 1,                  /* 打印日志的时间 */
    DHOP_LOG_PREFIX_TID      = 1 << 1,             /* 打印日志的线程号syscall(SYS_gettid) */
    DHOP_LOG_PREFIX_APPNAME  = 1 << 2,             /* 打印日志的app名 */
    DHOP_LOG_PREFIX_APPID    = 1 << 3,             /* 打印日志的appId */
    DHOP_LOG_PREFIX_PROCNAME = 1 << 4,             /* 打印日志的程序名 */
} DHOP_LOG_PreFix;

/*******************************************************************************/


/***************************************************************
* function name : DHOP_LOG_print
*
* description   : APP日志打印，注意避免直接调用，应使用 DHOP_LOG_ERROR、DHOP_LOG_WARN、DHOP_LOG_INFO、DHOP_LOG_DEBUG 封装过的宏定义
*
* input         : level  -- 打印等级，见 DHOP_LOG_Level
*                 pcFunc -- 函数名
*                 line   -- 行号
*                 pFmt   -- 格式化打印正文
*                 ...    -- 格式化打印参数
* output        : None
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : None
***************************************************************/
DH_Void  DHOP_LOG_print(DHOP_LOG_Level level, const DH_Char *pcFunc, DH_Int32 line, const DH_Char *pFmt, ...);


/***************************************************************
* function name : DHOP_LOG_setLevel
*
* description   : 设置LOG输出到指定目的端的优先级等级，各目的端的默认等级如下:
*                 -- web端默认为DHOP_LOG_LEVEL_ERROR
*                 -- 本地日志默认等级为DHOP_LOG_LEVEL_ERROR
*                 -- 控制台终端默等级为DHOP_LOG_LEVEL_INFO
*
* input         : nLevel  -- LOG输出等级
*                 nDest   -- LOG输出目标地
* output        : None
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : None
***************************************************************/
DH_Int32 DHOP_LOG_setLevel(DHOP_LOG_Level nLevel, DHOP_LOG_OutDestn nDest);

/***************************************************************
* function name : DHOP_LOG_setSilence
*
* description   : 设置log输出终端为静默，即无打印输出
*
* input         : nDest   -- LOG输出目标地
*
* output        : None
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : None
***************************************************************/

DH_Int32 DHOP_LOG_setSilence(DHOP_LOG_OutDestn nDest);

/***************************************************************
* function name : DHOP_LOG_setRecordSize
*
* description   : 设置LOG输出到日志文件的记录大小
*                 -- LOG日志的最大日志大小DHOP_LOG_SIZE_MAX
*
* input         : kBytes    -- LOG日志的文件大小
*
* output        : None
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : None
***************************************************************/
DH_Int32 DHOP_LOG_setRecordSize(DH_Uint32 kBytes);

/***************************************************************
* function name : DHOP_LOG_setPrefix
*
* description   : 设置LOG日志可添加的前缀
*
* input         : prefixMask
*                 -- LOG日志前缀mask，具体mask值详见DHOP_LOG_PreFix
*
* output        : None
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : None
***************************************************************/
DH_Int32 DHOP_LOG_setPrefix(DH_Uint32 prefixMask);


/***************************************************************
* function name : DHOP_LOG_getFileData
*
* description   : 获取记录日志的数据
*
* input         : pBuf         -- 用户指定要存放的内存指针
*                 bytes        -- 想要读取的LOG日志大小
*
* output        : None
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_FAILED  -- 读取日志数据失败
*                 >= 0         -- 实际读取的数据大小
***************************************************************/

DH_Int32 DHOP_LOG_getRecordData(DH_Char *pBuf, DH_Int32 bytes);



#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_LOG_H__


