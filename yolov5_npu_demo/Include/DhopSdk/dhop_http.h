/*******************************************************************************
 * dhop_http.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 本模块定义HTTP服务相关的API以及数据结构
 *              协议格式定义参见https://developer.mozilla.org/en-US/docs/Web/HTTP
 *
 *******************************************************************************/

#ifndef __DHOP_HTTP_H__
#define __DHOP_HTTP_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"
#include "dhop_version.h"

/*******************************************************************************/

/* 
    HTTP标准状态码
    参考https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
*/
typedef enum
{
    DHOP_HTTP_StatusCode_100_Continue                           = 100,
    DHOP_HTTP_StatusCode_101_Switching_Protocols,
    DHOP_HTTP_StatusCode_102_Processing,
    DHOP_HTTP_StatusCode_103_Early_Hints,

    DHOP_HTTP_StatusCode_200_OK                                 = 200,
    DHOP_HTTP_StatusCode_201_Created,
    DHOP_HTTP_StatusCode_202_Accepted,
    DHOP_HTTP_StatusCode_203_Non_Authoritative_Information,
    DHOP_HTTP_StatusCode_204_No_Content,
    DHOP_HTTP_StatusCode_205_Reset_Content,
    DHOP_HTTP_StatusCode_206_Partial_Content,
    DHOP_HTTP_StatusCode_207_Multi_Status,
    DHOP_HTTP_StatusCode_208_Already_Reported,
    DHOP_HTTP_StatusCode_226_IM_Used                            = 226,

    DHOP_HTTP_StatusCode_300_Multiple_Choices                   = 300,
    DHOP_HTTP_StatusCode_301_Moved_Permanently,
    DHOP_HTTP_StatusCode_302_Found,
    DHOP_HTTP_StatusCode_303_See_Other,
    DHOP_HTTP_StatusCode_304_Not_Modified,
    DHOP_HTTP_StatusCode_307_Temporary_Redirect                 = 307,    
    DHOP_HTTP_StatusCode_308_Permanent_Redirect,

    DHOP_HTTP_StatusCode_400_Bad_Request                        = 400,
    DHOP_HTTP_StatusCode_401_Unauthorized,
    DHOP_HTTP_StatusCode_402_Payment_Required,
    DHOP_HTTP_StatusCode_403_Forbidden,
    DHOP_HTTP_StatusCode_404_Not_Found,
    DHOP_HTTP_StatusCode_405_Method_Not_Allowed,
    DHOP_HTTP_StatusCode_406_Not_Acceptable,
    DHOP_HTTP_StatusCode_407_Proxy_Authentication_Required,
    DHOP_HTTP_StatusCode_408_Request_Timeout,
    DHOP_HTTP_StatusCode_409_Conflict,
    DHOP_HTTP_StatusCode_410_Gone,
    DHOP_HTTP_StatusCode_411_Length_Required,
    DHOP_HTTP_StatusCode_412_Precondition_Failed,
    DHOP_HTTP_StatusCode_413_Payload_Too_Large,
    DHOP_HTTP_StatusCode_414_URI_Too_Long,
    DHOP_HTTP_StatusCode_415_Unsupported_Media_Type,
    DHOP_HTTP_StatusCode_416_Range_Not_Satisfiable,
    DHOP_HTTP_StatusCode_417_Expectation_Failed,
    DHOP_HTTP_StatusCode_418_Im_a_teapot,
    DHOP_HTTP_StatusCode_421_Misdirected_Request                = 421,
    DHOP_HTTP_StatusCode_422_Unprocessable_Entity,
    DHOP_HTTP_StatusCode_423_Locked,
    DHOP_HTTP_StatusCode_424_Failed_Dependency,
    DHOP_HTTP_StatusCode_425_Too_Early,
    DHOP_HTTP_StatusCode_426_Upgrade_Required,
    DHOP_HTTP_StatusCode_428_Precondition_Required              = 428,
    DHOP_HTTP_StatusCode_429_Too_Many_Requests,
    DHOP_HTTP_StatusCode_431_Request_Header_Fields_Too_Large    = 431,
    DHOP_HTTP_StatusCode_451_Unavailable_For_Legal_Reasons      = 451,

    DHOP_HTTP_StatusCode_500_Internal_Server_Error              = 500,
    DHOP_HTTP_StatusCode_501_Not_Implemented,
    DHOP_HTTP_StatusCode_502_Bad_Gateway,
    DHOP_HTTP_StatusCode_503_Service_Unavailable,
    DHOP_HTTP_StatusCode_504_Gateway_Timeout,
    DHOP_HTTP_StatusCode_505_HTTP_Version_Not_Supported,
    DHOP_HTTP_StatusCode_506_Variant_Also_Negotiates,
    DHOP_HTTP_StatusCode_507_Insufficient_Storage,
    DHOP_HTTP_StatusCode_508_Loop_Detected,
    DHOP_HTTP_StatusCode_510_Not_Extended                       = 510,
    DHOP_HTTP_StatusCode_511_Network_Authentication_Required,
} DHOP_HTTP_StatusCode;

/* 
    HTTP METHOD
    参考https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
*/
typedef enum
{
    DHOP_HTTP_METHOD_UNKNOWN = 0,
    DHOP_HTTP_METHOD_GET,
    DHOP_HTTP_METHOD_POST,
    DHOP_HTTP_METHOD_HEAD,
    DHOP_HTTP_METHOD_PUT,
    DHOP_HTTP_METHOD_DELETE,
} DHOP_HTTP_RequestMethod;

/* 
    HTTP VERSION
    参考https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
*/
typedef enum
{
    DHOP_HTTP_VERSION_UNKNOWN = 0,
    DHOP_HTTP_VERSION_1_0,
    DHOP_HTTP_VERSION_1_1,
    DHOP_HTTP_VERSION_2_0,
} DHOP_HTTP_Version;

/*
    功能: 读取请求的Content数据
    参数: token     -- <in>       请求的唯一标识
    参数: pBuffer   -- <in/out>   本次读取到的Content内容
    参数: pSize     -- <in/out>   in:用户指定的buffer大小.out: 本次读取到的数据大小
    返回值: != 0: 读取失败，ref DHOP_ErrorCode. = 0： 读取成功
    说明:如果数据没有一次性接收完成,可以重复读取
*/
typedef DH_Int32(*DHOP_HTTP_readContent)(const DH_Char* token, DH_Byte* pBuffer, DH_Uint32* pSize);

/*******************************************************************************/

/*
    功能: 设置回复的状态码
    参数: token     -- <in>  请求的唯一标识
    参数: code      -- <in>  回复的状态码,,参考DHOP_HTTP_StatusCode
    返回值: != 0: 设置失败，ref DHOP_ErrorCode. = 0： 设置成功
    说明： 必须在writeContent前调用
*/
typedef DH_Int32(*DHOP_HTTP_setStatusCode)(const DH_Char* token, DHOP_HTTP_StatusCode code);

/*
    功能: 设置回复的Content-Length
    参数: token     -- <in>  请求的唯一标识
    参数: length    -- <in>  Content-Length 值
    返回值: != 0: 设置失败，ref DHOP_ErrorCode. = 0： 设置成功
    说明： 必须在writeContent前调用
*/
typedef DH_Int32(*DHOP_HTTP_setContentLength)(const DH_Char* token, DH_Uint64 length);

/*
    功能: 设置回复的Header中的字段值.
    参数: token     -- <in>  请求的唯一标识
    参数: key       -- <in>  Header的字段名称,如"Content-Length"
    参数: value     -- <in>  Header的字段值,如 1024
    返回值: != 0: 设置失败，ref DHOP_ErrorCode. = 0： 设置成功
    说明： 必须在writeContent前调用
*/
typedef DH_Int32(*DHOP_HTTP_addHeader)(const DH_Char* token, const DH_Char* key, const DH_Char* value);

/*
    功能: 写入回复的Content数据
    参数: token    -- <in>  请求的唯一标识
    参数: pData    -- <in>  本次写入的回复Content数据
    参数: size     -- <in>  本次写入的回复Content数据长度
    返回值: != 0: 发送失败，ref DHOP_ErrorCode. = 0： 发送成功
    说明:如果数据无法一次性发送完成,可以重复写入.但是必须和Content-Length保持一致
        如果Header中没有指定Content-Length或为0， 则需要通过writeEnd调用来明确结束本次请求处理过程。
        如果Header中设置了Content-Length且大于0， 则写入的数据长度达到Content-Length或者调用writeEnd时,会结束本次请求处理过程。
*/
typedef DH_Int32(*DHOP_HTTP_writeContent)(const DH_Char* token, const DH_Byte* pData, DH_Uint32 size);

/*
    功能: 设置请求处理结束标识.该接口调用后,表示这一请求处理结束了,token即将被释放.
    参数: token     -- <in>  请求的唯一标识
    返回值: != 0: 设置失败，ref DHOP_ErrorCode. = 0： 设置成功
*/
typedef DH_Int32(*DHOP_HTTP_writeEnd)(const DH_Char* token);

/*******************************************************************************/

/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)                   // 32位系统下结构体定义

/* HTTP 头的键值对定义 */ 
typedef struct
{
    DH_String       key;
    DH_String       value;
} DHOP_HTTP_KeyValue;

/* HTTP头信息 */
typedef struct 
{
    DH_Uint16                       cbSize;                         // sizeof(DHOP_HTTP_RequestHeader)，调用者无需填写，由接口内部赋值

    DH_Uint8                        version;                        // HTTP协议版本,参见枚举类型DHOP_HTTP_Version，调用者无需填写，由接口内部赋值

    DH_Uint8                        method;                         // HTTP请求方法,参见枚举类型 DHOP_HTTP_RequestMethod，调用者无需填写，由接口内部赋值

    DH_Uint16                       numOfHeader;                    // HTTP请求头字段个数，调用者无需填写，由接口内部赋值

    DH_Uint16                       reserved;                       // 预留字段

    DH_String                       url;                            // HTTP请求URL，调用者无需填写，由接口内部赋值

    DHOP_HTTP_KeyValue              *headers;                       // headers指向一个key-value结构体数组,个数为numOfHeader，调用者无需填写，由接口内部赋值

    DH_Uint64                       rsv[4];
} DHOP_HTTP_RequestHeader;

/* HTTP请求信息 */
typedef struct
{
    DH_Uint16                       cbSize;                         // sizeof(DHOP_HTTP_Request)，调用者无需填写，由接口内部赋值

    DH_Uint16                       res0;                           // 保留字段

    DH_String                       token;                          // 请求的唯一标识，调用者无需填写，由接口内部赋值

    DHOP_HTTP_RequestHeader         *header;                        // 请求Header信息，调用者无需填写，由接口内部赋值

    DHOP_HTTP_readContent           readContent;                    // 读取请求Content信息，调用者无需填写，由接口内部赋值

    DH_Uint64                       reserved[16];                   // 保留字段

} DHOP_HTTP_Request;

/* HTTP回复信息 */
typedef struct
{
    DH_Uint16                       cbSize;                         // sizeof(DHOP_HTTP_Response)，调用者无需填写，由接口内部赋值

    DH_Uint16                       res0;                           // 保留字段

    DHOP_HTTP_setStatusCode         setCode;                        // 设置响应码，调用者无需填写，由接口内部赋值

    DHOP_HTTP_addHeader             addHeader;                      // 设置回复Header字段，调用者无需填写，由接口内部赋值

    DHOP_HTTP_writeContent          writeContent;                   // 写入回复的Content数据，调用者无需填写，由接口内部赋值

    DHOP_HTTP_setContentLength      setContentLength;               // 设置回复的Content-Length，调用者无需填写，由接口内部赋值

    DHOP_HTTP_writeEnd              writeEnd;                       // 设置请求处理结束标识,当ContentLength不设置或为0时，需要调用它，调用者无需填写，由接口内部赋值

    DH_Uint64                       reserved[16];                   // 保留字段

} DHOP_HTTP_Response;

/*
    功能: 服务响应函数.
    参数: request     -- <in>  请求处理
    参数: response    -- <in>  回复处理
    返回值: != 0: 服务响应失败. = 0： 服务响应成功
*/
typedef DH_Int32 (*DHOP_HTTP_ServletRequest)(const DHOP_HTTP_Request* request, const DHOP_HTTP_Response* response);

/* HTTP服务信息内容定义 */
typedef struct
{
    DH_Uint16                       cbSize;                         // sizeof(DHOP_HTTP_AppDefinition)，调用者必填

    DH_Uint16                       res0;                           // 保留字段

    DH_Uint32                       timeout;                        // 请求响应的超时时间.单位: 毫秒.如果为0，则默认3秒超时，调用者选填

    DHOP_HTTP_ServletRequest        servlet;                        // 服务响应函数，调用者必填

    DH_Uint64                       reserved[14];                   // 保留字段

} DHOP_HTTP_AppDefinition;

#endif
#if (__SIZEOF_POINTER__ == 8)                   // 64位系统下结构体定义

/* HTTP 头的键值对定义 */ 
typedef struct
{
    DH_String       key;
    DH_String       value;
} DHOP_HTTP_KeyValue;

/* HTTP头信息 */
typedef struct 
{
    DH_Uint16                       cbSize;                         // sizeof(DHOP_HTTP_RequestHeader)，调用者无需填写，由接口内部赋值

    DH_Uint8                        version;                        // HTTP协议版本,参见枚举类型DHOP_HTTP_Version，调用者无需填写，由接口内部赋值

    DH_Uint8                        method;                         // HTTP请求方法,参见枚举类型 DHOP_HTTP_RequestMethod，调用者无需填写，由接口内部赋值

    DH_Uint16                       numOfHeader;                    // HTTP请求头字段个数，调用者无需填写，由接口内部赋值

    DH_Uint16                       reserved;                       // 预留字段

    DH_String                       url;                            // HTTP请求URL，调用者无需填写，由接口内部赋值

    DHOP_HTTP_KeyValue              *headers;                       // headers指向一个key-value结构体数组,个数为numOfHeader，调用者无需填写，由接口内部赋值

    DH_Uint64                       rsv[4];
} DHOP_HTTP_RequestHeader;

/* HTTP请求信息 */
typedef struct
{
    DH_Uint16                       cbSize;                         // sizeof(DHOP_HTTP_Request)，调用者无需填写，由接口内部赋值

    DH_Uint16                       res0[3];                        // 保留字段

    DH_String                       token;                          // 请求的唯一标识，调用者无需填写，由接口内部赋值

    DHOP_HTTP_RequestHeader         *header;                        // 请求Header信息，调用者无需填写，由接口内部赋值

    DHOP_HTTP_readContent           readContent;                    // 读取请求Content信息，调用者无需填写，由接口内部赋值

    DH_Uint64                       reserved[16];                   // 保留字段

} DHOP_HTTP_Request;

/* HTTP回复信息 */
typedef struct
{
    DH_Uint16                       cbSize;                         // sizeof(DHOP_HTTP_Response)，调用者无需填写，由接口内部赋值

    DH_Uint16                       res0[3];                        // 保留字段

    DHOP_HTTP_setStatusCode         setCode;                        // 设置响应码，调用者无需填写，由接口内部赋值

    DHOP_HTTP_addHeader             addHeader;                      // 设置回复Header字段，调用者无需填写，由接口内部赋值

    DHOP_HTTP_writeContent          writeContent;                   // 写入回复的Content数据，调用者无需填写，由接口内部赋值

    DHOP_HTTP_setContentLength      setContentLength;               // 设置回复的Content-Length，调用者无需填写，由接口内部赋值

    DHOP_HTTP_writeEnd              writeEnd;                       // 设置请求处理结束标识,当ContentLength不设置或为0时，需要调用它，调用者无需填写，由接口内部赋值

    DH_Uint64                       reserved[16];                   // 保留字段

} DHOP_HTTP_Response;

/*
    功能: 服务响应函数.
    参数: request     -- <in>  请求处理
    参数: response    -- <in>  回复处理
    返回值: != 0: 服务响应失败. = 0： 服务响应成功
*/
typedef DH_Int32 (*DHOP_HTTP_ServletRequest)(const DHOP_HTTP_Request* request, const DHOP_HTTP_Response* response);

/* HTTP服务信息内容定义 */
typedef struct
{
    DH_Uint16                       cbSize;                         // sizeof(DHOP_HTTP_AppDefinition)，调用者必填

    DH_Uint16                       res0;                           // 保留字段

    DH_Uint32                       timeout;                        // 请求响应的超时时间.单位: 毫秒.如果为0，则默认3秒超时，调用者选填

    DHOP_HTTP_ServletRequest        servlet;                        // 服务响应函数，调用者必填

    DH_Uint64                       reserved[14];                   // 保留字段

} DHOP_HTTP_AppDefinition;

#endif

/*******************************************************************************/

/***************************************************************
* function name : DHOP_HTTP_online
*
* description   : Http服务上线，一个APP(一个或多个进程组成)仅可上线一个HTTP服务。
*                 首次调用DHOP_HTTP_onLine有效，当服务上线后再次调用本接口会返回错误
*
* input         : pInfo   -- Http服务上线信息
*
* output        : None
*
* return value  : DHOP_SUCCESS : 成功
*               : 其它           : 参考 DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_HTTP_online(const DHOP_HTTP_AppDefinition * pInfo);


/***************************************************************
* function name : DHOP_HTTP_offline
*
* description   : 对HTTP服务进行下线
*
* input         : None
*
* output        : None
*
* return value  : DHOP_SUCCESS : 成功
*               : 其它           : 参考 DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_HTTP_offline();

/***************************************************************
* function name : DHOP_HTTP_urlDecode
*
* description   : 将编码的结果进行解码，如: %20转换为 '空格'
*
* input         : src        -- 编码的内容          
*
* output        : outbuf     -- 结果缓冲区的大小         
*                 bufsize    -- 结果地址的缓冲区大小
*
* return value  : 成功:outbuf返回的字节长度
*     其它        : 失败:DHOP_ERR_PARAM_IS_NULL
***************************************************************/
DH_Int32 DHOP_HTTP_urlDecode(const DH_Char* src, DH_Char* outbuf, DH_Int32* bufsize);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_HTTP_H__


