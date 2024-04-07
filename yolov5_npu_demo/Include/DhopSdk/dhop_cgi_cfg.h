/*******************************************************************************
 * dhop_cgi_cfg.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义CGI配置相关的数据结构结构与API
 *
 *******************************************************************************/

#ifndef __DHOP_CFG_H__
#define __DHOP_CFG_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"
#include "dhop_version.h"

/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)               // 32位系统下结构体定义
typedef struct
{
    const DH_Char       *key;
    const DH_Char       *value;
} DHOP_CFG_KeyValue;
#endif
#if (__SIZEOF_POINTER__ == 8)               // 64位系统下结构体定义
typedef struct
{
    const DH_Char       *key;
    const DH_Char       *value;
} DHOP_CFG_KeyValue;
#endif

/********************************推荐使用V2系列接口********************************************/


/***************************************************************
* function name : DHOP_CFG_KeyValueCallback
*
* description   : function pointer used for set config callback.
                  when use POST method, only support format [x-www-form-urlencoded].
                  otherwise, use ConfigContentCallback
*
* input         : url     -- request url, null-terminator.
                : data    -- config input from cgi, array of DHOP_KeyValue
                : amount  -- element count of content array.
                          -- In DHOP_KeyValue, both key and value are null-terminator.
*
* output        : result  -- pre-allocated memory for writing config result
*               : size    -- result memory size, never copy data into result
*                            larger than size,max(1024)
*
* return value  : = 0     -- process success, result will send back to cgi
*                            resposne. stop to invoke next callback
*                 > 0     -- process success, result will send back to cgi
*                            resposne. keep invoke next callback
*                 < 0     -- process failed, result ignored. stop to invoke
*                            next callback
***************************************************************/
typedef DH_Int32 (*DHOP_CFG_KeyValueCallback)(const DH_Char            *url,
                                              const DHOP_CFG_KeyValue  *data,
                                              DH_Uint32                 amount,
                                              DH_Char                  *result,
                                              DH_Uint32                 size);


/***************************************************************
* function name : ConfigContentCallback
*
* description   : function pointer used for set config callback.
                : only get POST body. Can not handle binary data, use ConfigCallback instead

* input         : url           -- request url, null-terminator.
                : data          -- config input from cgi, POST body
                : data_size     -- data size

*
* output        : result        -- pre-allocated memory for writing config result
*               : result_size   -- result memory size, never copy data into result
*                                  larger then size.max(1024)
*
* return value  : = 0           -- process success, result will send back to cgi
*                                  resposne. stop to invoke next callback
*                 > 0           -- process success, result will send back to cgi
*                                  resposne. keep invoke next callback
*                 < 0           -- process failed, result ignored. stop to invoke
*                                  next callback
***************************************************************/
typedef DH_Int32 (*DHOP_CFG_ContentCallback)(const DH_Char         *url,
                                             const DH_Char         *data,
                                             DH_Uint32              data_size,
                                             DH_Char               *result,
                                             DH_Uint32              result_size);



/*******************************************************************************/

#if (DHOP_SDK_VERSION < DHOP_versionSet(1,0,2))


/***************************************************************
* function name : DHOP_CFG_regKeyValueCallback
*
* description   : set callback of configuration, call this multi times to
*                 register multi callbacks, callbacks will be invoked by sequential
*
* input         : callback -- name of callback function, see ConfigContentCallback
*
* output        : None
*
* return value  : None
***************************************************************/
DH_Void DHOP_CFG_regKeyValueCallback(DHOP_CFG_KeyValueCallback callback);


/***************************************************************
* function name : DHOP_CFG_regContentCallback
*
* description   : set callback of configuration, call this multi times to
*                 register multi callbacks, callbacks will be invoked by sequential
*
* input         : callback -- name of callback function, see ConfigContentCallback
*
* output        : None
*
* return value  : None
***************************************************************/
DH_Void DHOP_CFG_regContentCallback(DHOP_CFG_ContentCallback callback);

#endif

/*************************version 2.0**************************************/

/// app cgi回复信息结构体
typedef struct
{
    DH_Char                 *buf;           /// 数据buffer,app可以直接向该buffer写入回复数据
    DH_Uint32               bufSize;        /// 数据buffer的大小.写入的数据不可超过bufSize.不要修改它
    DH_Uint32               rspSize;        /// 回复数据的大小.即写入buffer的实际大小
    DH_Uint32               withHead;       /// app的回复中是否包含完整的自定义http头，0: 不包含, !0: 包含
    const DH_Char           *reqHeader;     /// http请求的头字段列表,json格式
    DH_Uint32               reqHeaderLen;   /// http请求的头数据长度
    DH_Uint32               res[5];
} DHOP_CGI_RspInfo;

/***************************************************************
* function name : DHOP_CFG_KeyValueCallback_V2
*
* description   : app相应cgi请求的回调函数指针(key-value形式)
*
* input         : url           -- 客户端请求的url.app可以根据url区分不同的请求.
*               : data          -- 将请求参数解析为key-value键值对
*               : count         -- 键值对的个数.
*
* output        : rspInfo       -- app回复的数据信息
*
* return value  : >0 : 数据未完成，会继续回调(暂不支持)
*                 =0 : 数据完成，不会继续回调,将数据回复给客户端
*                 <0 : 失败,不会继续回调,数据将被丢弃
***************************************************************/
typedef DH_Int32(*DHOP_CFG_KeyValueCallback_V2)(const DH_Char           *url,
                                                const DHOP_CFG_KeyValue *data,
                                                DH_Uint32               count,
                                                DHOP_CGI_RspInfo        *rspInfo);


/***************************************************************
* function name : DHOP_CFG_ContentCallback_V2
*
* description   : app相应cgi请求的回调函数指针(content形式)
*
* input         : url           -- 客户端请求的url.app可以根据url区分不同的请求.
*               : content       -- 请求的content数据
*               : size          -- content数据长度
*
* output        : rspInfo       -- app回复的数据信息
*
* return value  : >0 : 数据未完成，会继续回调(暂不支持)
*                 =0 : 数据完成，不会继续回调,将数据回复给客户端
*                 <0 : 失败,不会继续回调,数据将被丢弃
*
***************************************************************/
typedef DH_Int32(*DHOP_CFG_ContentCallback_V2)( const DH_Char       *url,
                                                const DH_Char       *content,
                                                DH_Uint32           size,
                                                DHOP_CGI_RspInfo    *rspInfo);


/***************************************************************
* function name : DHOP_CFG_regKeyValueCallback_V2
*
* description   : app注册key-value请求的响应回调函数
*
* input         : callback -- key-value请求的响应回调函数
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : None
***************************************************************/
DH_Void DHOP_CFG_regKeyValueCallback_V2(DHOP_CFG_KeyValueCallback_V2 callback);


/***************************************************************
* function name : DHOP_CFG_regContentCallback_V2
*
* description   : app注册content请求的响应回调函数
*
* input         : callback -- content请求的响应回调函数
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : None
***************************************************************/
DH_Void DHOP_CFG_regContentCallback_V2(DHOP_CFG_ContentCallback_V2 callback);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_CFG_H__


