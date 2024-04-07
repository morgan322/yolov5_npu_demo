/*******************************************************************************
 * dhop_version.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: DHOP SDK版本信息定义
 *
 *******************************************************************************/

#ifndef __DHOP_VERSION_H__
#define __DHOP_VERSION_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/

#include "dhop_type_def.h"

/*******************************************************************************/
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define CC_DEPRECATED_ATTRIBUTE             __attribute__((deprecated))
#define CC_DEPRECATED_ATTRIBUTE_TEXT(text)   __attribute__((deprecated(text)))
#elif _MSC_VER >= 1400 //vs 2005 or higher
#define CC_DEPRECATED_ATTRIBUTE             __declspec(deprecated)
#define CC_DEPRECATED_ATTRIBUTE_TEXT(text)  __declspec(deprecated(text))
#else
#define CC_DEPRECATED_ATTRIBUTE
#define CC_DEPRECATED_ATTRIBUTE_TEXT(text)
#endif


#define DHOP_SDK_VER_MAJOR              1
#define DHOP_SDK_VER_MINOR              2
#define DHOP_SDK_VER_REVISION           5

#define DHOP_versionSet(major, minor, revision)  \
        ((((major) & 0x0ff) << 24U) | (((minor) & 0x0ffff) << 8U) | ((revision) & 0x0ff))

/*
头文件版本号，只要头文件有不兼容修改，就需要修改版本号。
用户通过该版本号获取APP中引用的头文件版本号；
通过API DHOP_SYS_getVersion()获取设备运行时库的版本
*/
#define DHOP_SDK_VERSION    (DHOP_versionSet(DHOP_SDK_VER_MAJOR, DHOP_SDK_VER_MINOR, DHOP_SDK_VER_REVISION))

#define DHOP_SDK_VER_GET_MAJOR(v)       (((v) >> 24) & 0xFF)
#define DHOP_SDK_VER_GET_MINOR(v)       (((v) >> 8) & 0xFFFF)
#define DHOP_SDK_VER_GET_REVERSION(v)   (((v) & 0xFF)


/*******************************************************************************/

/* 版本信息 */
typedef struct
{
    DH_Uint32                           ID;             // 特征号
    DH_Uint32                           revision;       // 修订版本号
    DH_Uint32                           minor;          // 次版本号
    DH_Uint32                           major;          // 主版本号

    /* 版权、版本描述等信息，信息存放在DHOP内部，调用者仅供引用或只读 */
    DH_String                           description;
} DHOP_SDK_Version;

typedef DHOP_SDK_Version DHOP_SDK_Version_V2; /* 即将废弃"_V2"的类型定义 */

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_VERSION_H__


