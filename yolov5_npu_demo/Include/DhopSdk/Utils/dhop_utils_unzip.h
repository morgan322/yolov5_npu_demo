/*******************************************************************************
* dhop_utils_unzip.h
*
* Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
*
* Description: APP Package 解压工具
*
*
*******************************************************************************/

#ifndef __DHOP_UTILS_UNZIP_H__
#define __DHOP_UTILS_UNZIP_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************典型调用流程**********************/
/*
          start
            |
    DHOP_UTILS_createUnzip
            |
 ----DHOP_UTILS_unzip
 |          |
 |          |-------------DHOP_UTILS_UnzipProc
 |----------|
     DHOP_UTILS_unzipEnd
            |
    DHOP_UTILS_destroyUnzip
            |
           end
*/
/*******************典型调用流程**********************/

/*******************************************************************************/


#include "../dhop_type_def.h"

/*******************************************************************************/

/* 回调数据的类型 */
typedef enum
{
    DHOP_UTILS_UNZIP_Data_Meta = 1,       /* 压缩文件的原始信息 参考 DHOP_UTILS_DataDesc meta 定义*/
    DHOP_UTILS_UNZIP_Data_Header,         /* 表示新文件数据的开始, 参考 DHOP_UTILS_DataDesc header 定义 */
    DHOP_UTILS_UNZIP_Data_Body,           /* 参考 DHOP_UTILS_DataDesc data 定义 */
    DHOP_UTILS_UNZIP_Data_Tail,           /* 仅表示当前文件数据的结束 */
} DHOP_UTILS_UNZIP_DataType;

/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)                   // 32位系统下结构体定义

/* 回调数据的描述 */
typedef union
{
    struct
    {
        DH_Uint32           unzipSize;  /* 压缩包解压后的总大小 */
        DH_Uint32           res[3];
    } meta;                             /* DHOP_UTILS_Data_Meta 压缩文件的原始信息 */

    struct
    {
        DH_Char*            name;       /* 新文件对应的文件名称 */
        DH_Uint32           size;       /* 新文件对应的文件大小 */
        DH_Uint32           res[2];
    } header;                           /* DHOP_UTILS_Data_Header 表示新文件数据的开始 */

    struct
    {
        DH_Uint8*           data;       /* 当前有效的解压后数据 */
        DH_Uint32           size;       /* 当前有效的解压后数据大小 */
        DH_Uint32           res[2];
    } data;                             /* DHOP_UTILS_Data_Body 有效的解压数据 */

} DHOP_UTILS_UNZIP_DataDesc;

#endif

#if (__SIZEOF_POINTER__ == 8)                   // 64位系统下结构体定义

/* 回调数据的描述 */
typedef union
{
    struct
    {
        DH_Uint32           unzipSize;  /* 压缩包解压后的总大小 */
        DH_Uint32           res[5];
    } meta;                             /* DHOP_UTILS_Data_Meta 压缩文件的原始信息 */

    struct
    {
        DH_Char*            name;       /* 新文件对应的文件名称 */
        DH_Uint32           size;       /* 新文件对应的文件大小 */
        DH_Uint32           res[3];
    } header;                           /* DHOP_UTILS_Data_Header 表示新文件数据的开始 */

    struct
    {
        DH_Uint8*           data;       /* 当前有效的解压后数据 */
        DH_Uint32           size;       /* 当前有效的解压后数据大小 */
        DH_Uint32           res[3];
    } data;                             /* DHOP_UTILS_Data_Body 有效的解压数据 */

} DHOP_UTILS_UNZIP_DataDesc;

#endif

/*******************************************************************************/

/***************************************************************
* function name : DHOP_Utils_UnzipProc
*
* description   : 解压数据的回调函数
*
* input         : None
*
* output        : None
*
* return value  : =0成功,非0失败
***************************************************************/
typedef DH_Int32(*DHOP_UTILS_UnzipProc)(DHOP_UTILS_UNZIP_DataType type, const DHOP_UTILS_UNZIP_DataDesc* desc);


/***************************************************************
* function name : DHOP_UTILS_createUnzip
*
* description   : 创建一个解压缩句柄
*
* input         : proc: 解压缩的数据回调
*
* output        : pHandle: 解压缩句柄
*
* return value  : DHOP_SUCCESS - 成功
*               : 其它         - 参考DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_UTILS_createUnzip(DHOP_UTILS_UnzipProc proc, DH_Handle *pHandle);


/***************************************************************
* function name : DHOP_UTILS_destroyUnzip
*
* description   : 销毁一个解压缩句柄
*
* input         : handle: 解压缩句柄
*
* output        : 无
*
* return value  : DHOP_SUCCESS - 成功
*               : 其它         - 参考DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_UTILS_destroyUnzip(DH_Handle handle);


/***************************************************************
* function name : DHOP_UTILS_unzip
*
* description   : 解压缩数据
*
* input         : handle: 解压缩句柄
* input         : zipData: 压缩数据
* input         : zipSize: 压缩数据大小
*
* output        :
*
* return value  : DHOP_SUCCESS - 成功
*               : 其它         - 参考DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_UTILS_unzip(DH_Handle handle, DH_Byte* zipData, DH_Uint32 zipSize);

/***************************************************************
* function name : DHOP_UTILS_unzipEnd
*
* description   : 压缩数据结束
*
* input         : handle: 解压缩句柄
*
* output        :
*
* return value  : DHOP_SUCCESS - 成功
*               : 其它         - 参考DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_UTILS_unzipEnd(DH_Handle handle);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_APP_H__


