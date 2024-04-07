/*******************************************************************************
 * rs485.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: rs485操作
 *
 *******************************************************************************/

#ifndef __DHOP_DEVICE_RS485_H__
#define __DHOP_DEVICE_RS485_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/

#include "dhop_type_def.h"

/// DHOP_DEVICE_control接口对Rs485参数设置时，支持使用掩码作为接口cmd的入参
/// 如，若cmd参数为3(对应二进制为0011)，则意味着设置波特率和数据位
typedef enum
{
    DHOP_DEVICE_RS485_CMD_SET_BAUDRATE = 1<<0,       /// 设置波特率
    DHOP_DEVICE_RS485_CMD_SET_DATABITS = 1<<1,       /// 设置数据位
    DHOP_DEVICE_RS485_CMD_SET_PARITY   = 1<<2,       /// 设置奇偶校验位
    DHOP_DEVICE_RS485_CMD_SET_STOPBITS = 1<<3,       /// 设置停止位
} DHOP_RS485_CmdType;

/*******************************************************************************/


/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)                       // 32位系统下结构体定义
/// 调用者根据自己设置的DHOP_RS485_CmdType（以下注释简称cmdtype），填写DHOP_RS485_CmdArgs结构体对应参数
typedef struct
{
    DH_Uint32  baudRate;        //波特率，调用者若设置的cmdtype波特率掩码为1则必填
    DH_Char    dataBits;        //数据位数，调用者若设置的cmdtype数据位掩码为1则必填
    DH_Char    parity;          //奇偶校验，1，奇校验；2，偶校验，其余值为无，调用者若设置的cmdtype奇偶校验位掩码为1则必填
    DH_Char    stopBits;        //停止位，调用者若设置的cmdtype停止位掩码为1则必填
    DH_Char    reserved[33];
} DHOP_RS485_CmdArgs;
#endif
#if (__SIZEOF_POINTER__ == 8)                       // 64位系统下结构体定义
/// 调用者根据自己设置的DHOP_RS485_CmdType（以下注释简称cmdtype），填写DHOP_RS485_CmdArgs结构体对应参数
typedef struct
{
    DH_Uint32  baudRate;        //波特率，调用者若设置的cmdtype波特率掩码为1则必填
    DH_Char    dataBits;        //数据位数，调用者若设置的cmdtype数据位掩码为1则必填
    DH_Char    parity;          //奇偶校验，1，奇校验；2，偶校验，其余值为无，调用者若设置的cmdtype奇偶校验位掩码为1则必填
    DH_Char    stopBits;        //停止位，调用者若设置的cmdtype停止位掩码为1则必填
    DH_Char    reserved[33];
} DHOP_RS485_CmdArgs;
#endif

/*******************************************************************************/


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_DEVICE_RS485_H__


