/*******************************************************************************
 * atsha204a.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: atsha204a加密芯片操作
 *
 *******************************************************************************/

#ifndef __DHOP_DEVICE_ATSHA204A_H__
#define __DHOP_DEVICE_ATSHA204A_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"

typedef enum
{
    DHOP_DEVICE_ATSHA204A_CMD_RESET,
    DHOP_DEVICE_ATSHA204A_CMD_I2C_READ,
    DHOP_DEVICE_ATSHA204A_CMD_I2C_WRITE,
} ATSHA204A_CmdType;


/*******************************************************************************/

typedef struct
{
    DH_Byte*      pBuf;
    DH_Uint32     count;
    DH_Uint32     reserved;
} ATSHA204A_CmdArgs;
/*******************************************************************************/


/*******************************************************************************/



#if (__SIZEOF_POINTER__ == 4)                       // 32位系统下结构体定义
#endif
#if (__SIZEOF_POINTER__ == 8)                       // 64位系统下结构体定义
#endif

/*******************************************************************************/



#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_DEVICE_ATSHA204A_H__


