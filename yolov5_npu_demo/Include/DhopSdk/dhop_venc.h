/*******************************************************************************
 * dhop_venc.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义编码相关的数据结构与API
 *
 *******************************************************************************/

#ifndef __DHOP_VENC_H__
#define __DHOP_VENC_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"
#include "dhop_yuv.h"

/*******************************************************************************/

/* 编码类型 */
typedef enum
{
    DHOP_VENC_YUV_TO_JPEG = 0,             /* jpeg编码 */
    DHOP_VENC_YUV_TO_H264,                 /* h264编码,暂不支持. */
    DHOP_VENC_YUV_TO_H265,                 /* h265编码,暂不支持. */
} DHOP_VENC_Type;

/* JPEG编码质量 */
typedef enum
{
    DHOP_VENC_JPEG_QUALITY_DEFAULT = 0,
    DHOP_VENC_JPEG_QUALITY_LOW,
    DHOP_VENC_JPEG_QUALITY_HIGHT,
} DHOP_VENC_JPEG_Quality;

/* JPEG编码请求类型 */
typedef enum
{
    DHOP_VENC_REQ_FULL_SCENE = 0,           /* 对整张YUV进行编码 */
    DHOP_VENC_REQ_CROP_REGION,              /* 对YUV局部区域进行编码 */
} DHOP_VENC_REQ_Type;

typedef enum
{
    DHOP_VENC_OVERLAY_TEXT = 0,            /* 文本 */
    DHOP_VENC_OVERLAY_RECT = 1,            /* 矩形框 */
    DHOP_VENC_OVERLAY_BMP  = 2,            /* 位图 暂不支持 */
}DHOP_VENC_OverlayType;

/**
 *    osd description
 *    pColorMap Find the corresponding color by 0 1 2 index value and fill in the color
 *
 *    00020000
 *    00212000
 *    00212000
 *    00020000
 *
*/

/*******************************************************************************/

/* 字体颜色, 使用ARGB1555颜色空间*/
typedef struct
{
    DH_Uint8                a;              // 透明分量, a为0透明, a为1不透明, 填入大于1按照1处理
    DH_Uint8                r;              // Red分量, 范围0到31
    DH_Uint8                g;              // Green分量, 范围0到31
    DH_Uint8                b;              // Blue分量, 范围0到31
} DH_Color;

typedef DH_Int32 (*DHOP_VENC_Callback)(DH_Uint32 size, DH_Uint8 *pData);

/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)               // 32位系统下结构体定义

/* 编码能力, 调用者无需填写 */
typedef struct
{
    DH_Uint16               maxWidth;       /* 设备支持的最大编码宽度 */
    DH_Uint16               maxHeight;      /* 设备支持的最大编码高度 */
    DH_Uint16               minWidth;       /* 设备支持的最小编码宽度 */
    DH_Uint16               minHeight;      /* 设备支持的最小编码高度 */
    DH_Uint16               alignWidth;     /* 编码宽度对齐要求 */
    DH_Uint16               alignHeight;    /* 编码高度对齐要求 */
    DH_Uint16               maxFps;         /* 最大编码帧率 */
    DH_Uint16               yuvFmtMask;     /* 支持编码的YUV格式掩码, DHOP_YUV_Format */
    DH_Uint32               reverse[16];    /* 保留字段 */
} DHOP_VENC_CapsInfo;

/* 编码器创建参数 */
typedef struct
{
    DH_Uint16               cbSize;         /* 当前结构体大小，sizeof(DHOP_VENC_CreateParam),调用者必填 */
    DH_Uint8                type;           /* 编码类型,参考DHOP_VENC_Type,调用者必填 */
    DH_Uint8                format;         /* 编码YUV格式,参考DHOP_YUV_Format,调用者必填 */
    DH_Uint16               max_width;      /* 待编码的最大宽度,不超过能力支持范围,调用者必填 */
    DH_Uint16               max_height;     /* 待编码的最大高度  ,不超过能力支持范围,调用者必填*/
    DH_Uint32               reserved[6];    /* 保留字段 */
} DHOP_VENC_CreateParam;

/* 编码结果 */
typedef struct
{
    DH_Uint16               cbSize;         /* 当前结构体大小，sizeof(DHOP_VENC_Response),调用者必填 */
    DH_Uint16               type;           /* 编码数据类型,参考DHOP_VENC_TYPE, 调用者无需填写,由接口内部赋值 */

    DH_Uint32               size;           /* 编码后数据的长度,单位:字节,调用者无需填写,由接口内部赋值 */

    DH_Uint64               pts;            /* 系统时间戳，来自DHOP_VENC_ReqInfo2.data.pts,调用者无需填写,由接口内部赋值 */

    DH_Uint8               *virAddr;        /* 编码后数据的虚拟地址,调用者无需填写,由接口内部赋值 */
    DH_Uint8               *phyAddr;        /* 编码后数据的物理地址,调用者无需填写,由接口内部赋值 */

    DH_Int32                timeout;        /* 请求超时时间  < 0 : 阻塞       ; = 0 : 非阻塞; >0 : 超时时间(ms)
                                               用于DHOP_VENC_request2失效,用于DHOP_VENC_getResult接口中有效 */

    DH_Uint32               reserved[15];   /* 保留字段 */
} DHOP_VENC_Result;

/* 编码osd文字 */
typedef struct
{
    DH_Uint32               type;           /* 固定值 DHOP_VENC_OVERLAY_TEXT,调用者必填*/
    DH_Uint32               left;           /* 叠加在画面中左上角的x坐标,调用者必填 */
    DH_Uint32               top;            /* 叠加在画面中左上角的y坐标,调用者必填 */
    DH_Int32                width;          /* 点阵的宽度,调用者必填 */
    DH_Int32                height;         /* 点阵的高度,调用者必填 */
    DH_Uint8               *pAddr;          /* 点阵转换后的颜色索引地址 */
    DH_Color               *pColorMap;      /* 点阵颜色索引值  索引范围 [0,osdMaxColorIndex),调用者必填 */
    DH_Uint32                colorMapNum;   /* 颜色个数,调用者必填 */
    DH_Uint32               reserved[15];   /* 保留字段,调用者必填 */
} DHOP_VENC_OverlayText;

/* 编码osd 线框  */
typedef struct
{
    DH_Uint32               type;           /* 固定值 DHOP_VENC_OVERLAY_RECT,调用者必填 */
    DH_Point32              beginPoint;     /* 矩形框在画面中左上角的坐标,调用者必填 */
    DH_Point32              endPoint;       /* 矩形框在画面中右下角的坐标,调用者必填 */
    DH_Color                color;          /* 矩形框颜色,调用者必填 */
    DH_Int32                pixcelWidth;    /* 线框宽度 [2,8], 2像素对齐,调用者必填 */
    DH_Uint32               reserved[16];   /* 保留字段 */
} DHOP_VENC_OverlayRect;

typedef union
{
    DHOP_VENC_OverlayText  *text;           /* OSD叠加文本,调用者选填 */
    DHOP_VENC_OverlayRect  *rect;           /* OSD叠加线框,调用者选填 */
} DHOP_VENC_OverlayElement;

/* 编码请求信息 */
typedef struct
{
    DH_Uint16               cbSize;         /* 当前结构体大小，sizeof(DHOP_VENC_ReqInfo2),调用者必填 */
    DH_Uint16               quality;        /* 编码质量,参考DHOP_VENC_JPEG_Quality,调用者必填 */

    DH_Uint8                resByte[4];     /* 保留字段 */

    DH_Rect16               region;         /* 编码区域,调用者必填 */
    DHOP_YUV_FrameData2    *data;           /* 待编码的YUV数据,
											   DHOP_YUV_FrameData2结构体中的privData不为空表明YUV数据为DHOP_YUV_getFrame输出,
											   DHOP_YUV_FrameData2结构体中的privData为空表明为用户提供的YUV数据,调用者必填 */
    DH_Int32                timeout;        /* 请求超时时间:       <0 : 阻塞  ; =0 : 非阻塞; >0 : 超时时间(ms) */

    DHOP_VENC_OverlayElement*elements;      /* element数组指针:要叠加的OSD信息,当elemNum大于0时不为NULL */
    DH_Uint16                elemNum;        /* element数组元素个数,调用者必填，=0:elements字段无效, >0:elements字段生效 */
    DH_Uint16                res16;

    DH_Uint32               reserved[10];   /* 保留字段 */
} DHOP_VENC_ReqInfo2;

#endif

#if (__SIZEOF_POINTER__ == 8)               // 64位系统下结构体定义

/* 编码能力, 调用者无需填写 */
typedef struct
{
    DH_Uint16               maxWidth;       /* 设备支持的最大编码宽度 */
    DH_Uint16               maxHeight;      /* 设备支持的最大编码高度 */
    DH_Uint16               minWidth;       /* 设备支持的最小编码宽度 */
    DH_Uint16               minHeight;      /* 设备支持的最小编码高度 */
    DH_Uint16               alignWidth;     /* 编码宽度对齐要求 */
    DH_Uint16               alignHeight;    /* 编码高度对齐要求 */
    DH_Uint16               maxFps;         /* 最大编码帧率 */
    DH_Uint16               yuvFmtMask;     /* 支持编码的YUV格式掩码 */
    DH_Uint64               reverse[8];     /* 保留字段 */
} DHOP_VENC_CapsInfo;

/* 编码器创建参数 */
typedef struct
{
    DH_Uint16               cbSize;         /* 当前结构体大小，sizeof(DHOP_VENC_CreateParam),调用者必填 */
    DH_Uint8                type;           /* 编码类型,参考DHOP_VENC_Type,调用者必填 */
    DH_Uint8                format;         /* 编码YUV格式,参考DHOP_YUV_Format,调用者必填 */
    DH_Uint16               max_width;      /* 待编码的最大宽度,不超过能力范围,调用者必填 */
    DH_Uint16               max_height;     /* 待编码的最大高度  ,不超过能力范围,调用者必填 */
    DH_Uint32               reserved[6];    /* 保留字段 */
} DHOP_VENC_CreateParam;

/* 编码结果 */
typedef struct
{
    DH_Uint16               cbSize;         /* 当前结构体大小，sizeof(DHOP_VENC_Response),调用者必填 */
    DH_Uint16               type;           /* 编码数据类型,参考DHOP_VENC_TYPE,调用者无需填写,由接口内部赋值 */

    DH_Uint32               size;           /* 编码后数据的长度,单位:字节,调用者无需填写,由接口内部赋值 */

    DH_Uint64               pts;            /* 系统时间戳，来自DHOP_VENC_ReqInfo2.data.pts,调用者无需填写,由接口内部赋值 */

    DH_Uint8               *virAddr;        /* 编码后数据的虚拟地址,调用者无需填写,由接口内部赋值 */
    DH_Uint8               *phyAddr;        /* 编码后数据的物理地址,调用者无需填写,由接口内部赋值 */

    DH_Int32                timeout;        /* 请求超时时间  <0 : 阻塞  =0 : 非阻塞 >0 : 超时时间(ms),异步获取结果有效 */

    DH_Uint32               reserved[15];   /* 保留字段 */
} DHOP_VENC_Result;

/* 编码osd文字 */
typedef struct
{
    DH_Uint32               type;           /* 固定值 DHOP_VENC_OVERLAY_TEXT,调用者必填 */    
    DH_Uint32               left;           /* 叠加在画面中左上角的x坐标,绝对坐标,调用者必填 */          
    DH_Uint32               top;            /* 叠加在画面中左上角的y坐标,绝对坐标,调用者必填 */
                                            /* OSD叠加坐标是绝对坐标系的坐标值 */
    DH_Int32                width;          /* 点阵的宽度,按2像素对齐,调用者必填 */
    DH_Int32                height;         /* 点阵的高度,按2像素对齐,调用者必填 */
    DH_Uint32                res32;
    DH_Uint8               *pAddr;          /* 点阵地址,调用者必填 */
    DH_Color               *pColorMap;      /* 点阵颜色索引值  索引范围 [0,osdMaxColorIndex),调用者必填*/
    DH_Uint32               colorMapNum;    /* 颜色个数,调用者必填 */
    DH_Uint32               reserved[14];   /* 保留字段 */
} DHOP_VENC_OverlayText;

/* 编码osd 线框  */
typedef struct
{
    DH_Uint32               type;           /* 固定值 DHOP_VENC_OVERLAY_RECT,调用者必填 */
    DH_Uint32                res32;
    DH_Point32              beginPoint;     /* 矩形框在画面中左上角的坐标,2像素对齐,坐标值为绝对坐标,调用者必填 */ 
    DH_Point32              endPoint;       /* 矩形框在画面中右下角的坐标,2像素对齐,坐标值为绝对坐标,调用者必填 */ 
    DH_Color                color;          /* 矩形框颜色,调用者必填 */
    DH_Int32                pixcelWidth;    /* 线框宽度 [2,8] 2像素对齐,调用者必填 */
    DH_Uint32               reserved[15];   /* 保留字段 */
} DHOP_VENC_OverlayRect;

typedef union
{
    DHOP_VENC_OverlayText  *text;           /* OSD叠加文本,调用者选填 */  
    DHOP_VENC_OverlayRect  *rect;           /* OSD叠加线框,调用者选填 */
} DHOP_VENC_OverlayElement;

/* 编码请求信息 */
typedef struct
{
    DH_Uint16               cbSize;         /* 当前结构体大小，sizeof(DHOP_VENC_ReqInfo2),调用者必填 */
    DH_Uint16               quality;        /* 编码质量,参考DHOP_VENC_JPEG_Quality,调用者必填 */

    DH_Uint8                resByte[4];     /* 保留字段 */

    DH_Rect16               region;         /* 编码区域,调用者必填 */
    DHOP_YUV_FrameData2    *data;           /* 待编码的YUV数据,privData字段不为空表明YUV数据为
                                               DHOP_YUV_getFrame输出,为空表明未用户提供的YUV数据,调用者必填 */
    DH_Int32                timeout;        /* 请求超时时间  <0 : 阻塞  =0 : 非阻塞 >0 : 超时时间(ms)*/

    DHOP_VENC_OverlayElement *elements;     /* element数组指针:要叠加的OSD信息,elemNum大于0时,字段有效 */
    DH_Uint16                elemNum;        /* element数组元素个数,调用者必填,=0:osd叠加无效, >0:需保证elements字段有效*/
    DH_Uint16                res16;

    DH_Uint32               reserved[9];    /* 保留字段 */
} DHOP_VENC_ReqInfo2;

#endif


/*******************************************************************************/

/***************************************************************
* function name : DHOP_VENC_getCaps
*
* description   : 获取编码能力
*
* input         : pCapInfo -- DHOP支持的编码能力
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VENC_getCaps(DHOP_VENC_CapsInfo *pCapInfo);


/***************************************************************
* function name : DHOP_VENC_create
*
* description   : 创建编码器
*
* input         : pParam   -- 创建参数
* output        : hEncoder -- 编码操作句柄指针
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. v1.2.0及以上版本支持
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VENC_create(DHOP_VENC_CreateParam *pParam, DH_Handle *hEncoder);


/***************************************************************
* function name : DHOP_VENC_destroy
*
* description   : 销毁编码器。销毁通过DHOP_VENC_create生成的句柄
*
* input         : hEncoder -- 编码操作句柄指针
* output        : None
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 句柄不安全
*                 4. 调用成功后,底层编码资源被释放
*                 5. V1.2.0及以上版本支持
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VENC_destroy(DH_Handle *hEncoder);

/***************************************************************
* function name : DHOP_VENC_request2
*
* description   : 发起一次编码请求
*
* input         : hEncoder -- 编码操作句柄
*                 pReq -- 编码请求
*                 pResult -- 编码结果
*
* output        : 无
*
* notice        : 1. 线程不安全
*                 2. 同步接口
*                 3. 句柄不安全
*                 4. V1.2.0及以上版本支持
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VENC_request2(DH_Handle hEncoder,
                            DHOP_VENC_ReqInfo2* pReq,
                            DHOP_VENC_Result*  pResult);


/***************************************************************
* function name : DHOP_VENC_sendRequest
*
* description   : 发送一次异步编码请求
*
* input         : hEncoder -- 编码操作句柄
*                 pReq -- 编码请求
* output        : None
*
* notice        : 1. 线程安全
*                 2. 异步接口
*                 3. 句柄安全
*                 4. V1.2.0以上版本支持
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VENC_sendRequest(DH_Handle hEncoder, DHOP_VENC_ReqInfo2 * pReq);


/***************************************************************
* function name : DHOP_VENC_getResult
*
* description   : 获取异步编码请求的结果，该接口为阻塞式调用
*
* input         : hEncoder -- 编码操作句柄
* output        : pResult  -- 编码结果
*
* notice        : 1. 线程安全
*                 2. 异步接口
*                 3. 句柄安全
*                 4. V1.2.0以上版本支持
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VENC_getResult(DH_Handle hEncoder, DHOP_VENC_Result * pResult);


/***************************************************************
* function name : DHOP_VENC_releaseResult
*
* description   : 释放已经获取到的编码结果
*
* input         : hEncoder -- 编码操作句柄
*                 pResult  -- 通过DHOP_VENC_getResult获取到的结果信息
*
* output        : None
*
* notice        : 1. 线程安全
*                 2. 异步接口
*                 3. 句柄安全
*                 4. V1.2.0以上版本支持
*
* return value  : DHOP_SUCCESS: 成功
*                 其它值:  失败 -- 参考dhop_errno.h中的错误码
***************************************************************/
DH_Int32 DHOP_VENC_releaseResult(DH_Handle hEncoder, DHOP_VENC_Result * pResult);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_VENC_H__


