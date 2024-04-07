/*******************************************************************************
 * dhop_yuv.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义YUV模块的数据结构与API。
 *
 *******************************************************************************/

#ifndef __DHOP_YUV_H__
#define __DHOP_YUV_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"
#include "dhop_version.h"
#include "dhop_sys.h"

/*******************************************************************************/


/* DHOP使用的YUV格式 */
typedef enum
{
    DHOP_YUV_FMT_ONLY_Y = 0,            /* GREY */
    DHOP_YUV_FMT_420P_I420,             /* I420: [Y][U][V], [yAddr][uAddr][vAddr] */
    DHOP_YUV_FMT_420P_YV12,             /* YV12: [Y][V][U], [yAddr][vAddr][uAddr] */
    DHOP_YUV_FMT_420SP_UV,              /* NV12: [Y][UV], [yAddr][uAddr] */
    DHOP_YUV_FMT_420SP_VU,              /* NV21: [Y][VU], [yAddr][uAddr] */

    DHOP_YUV_FMT_BUTT
} DHOP_YUV_Format;


/* YUV扩展数据信息类型 */
typedef enum
{
    DHOP_YUV_EXT_TYPE_FLASHLIGHT = 0,   /* 闪光灯信息，主要用于交通产品 */
    DHOP_YUV_EXT_TYPE_SNAP       = 1,   /* 抓拍信息，主要用于交通产品 */
    DHOP_YUV_EXT_TYPE_BUTT
} DHOP_YUV_ExtInfoType;


/* YUV格式参数掩码类型 */
typedef enum
{
    DHOP_YUV_FMT_MSK_ONLY_Y     = (1 << DHOP_YUV_FMT_ONLY_Y),
    DHOP_YUV_FMT_MSK_420P_I420  = (1 << DHOP_YUV_FMT_420P_I420),
    DHOP_YUV_FMT_MSK_420P_YV12  = (1 << DHOP_YUV_FMT_420P_YV12),
    DHOP_YUV_FMT_MSK_420SP_UV   = (1 << DHOP_YUV_FMT_420SP_UV),
    DHOP_YUV_FMT_MSK_420SP_VU   = (1 << DHOP_YUV_FMT_420SP_VU)
} DHOP_YUV_FormatMskType;

/* DHOP YUV可选配置类型 */
typedef enum
{
    DHOP_YUV_OPT_DEPTH = 0,             /* YUV队列深度 */

    DHOP_YUV_OPT_BUTT,
} DHOP_YUV_OptionType;

/*******************************************************************************/

/* YUV数据地址 */
typedef union
{
    /* Only Y */
    DH_Uint8            *y;

    struct
    {
        DH_Uint8        *y;
        DH_Uint8        *vu;
    } nv21; // NV21

    struct
    {
        DH_Uint8        *y;
        DH_Uint8        *uv;
    } nv12; // NV12

    struct
    {
        DH_Uint8        *y;
        DH_Uint8        *u;
        DH_Uint8        *v;
    } i420;

    struct
    {
        DH_Uint8        *y;
        DH_Uint8        *v;
        DH_Uint8        *u;
    } yv12;
} DHOP_YUV_PixelAddr;

#if (__SIZEOF_POINTER__ == 4)           // 32位系统下结构体定义

/* YUV像素数据 */
typedef struct
{
    DH_Uint16           format;         /* YUV格式,参考DHOP_YUV_Format*/
    DH_Uint16           width;          /* YUV宽度 */
    DH_Uint16           height;         /* YUV高度 */
    DH_Uint16           stride[3];      /* YUV跨距，各分量数据跨距 */
    DHOP_YUV_PixelAddr  virAddr;        /* YUV数据虚拟地址 */
    DHOP_YUV_PixelAddr  phyAddr;        /* YUV数据物理地址 */
} DHOP_YUV_PixelData;


/* 设备YUV通道能力 */
typedef struct
{
    DH_Uint16           maxWidth;       /* 通道支持获取YUV的最大宽度 */
    DH_Uint16           maxHeight;      /* 通道支持获取YUV的最大高度 */
    DH_Uint16           minWidth;       /* 通道支持获取YUV的最小宽度 */
    DH_Uint16           minHeight;      /* 通道支持获取YUV的最小高度 */
    DH_Uint16           alignWidth;     /* 通道YUV宽度对齐要求 */
    DH_Uint16           alignHeight;    /* 通道YUV高度对齐要求 */
    DH_Uint16           maxFps;         /* 通道支持获取YUV的最大帧率 */
    DH_Uint16           fmtMask;        /* 通道支持YUV格式掩码,每一位代表一种格式,
                                            YUV格式可参考DHOP_YUV_Format */
    DH_Uint16           maxDepth;       /* 通道可设置的最大深度 */
    DH_Uint16           res16;          /* 保留字段 */
    DH_Uint32           reserve[4];     /* 保留字段 */
} DHOP_YUV_CapInfo;

/* 设备YUV服务启动参数 */
typedef struct
{
    DH_Int8             channel;        /* 通道ID，取值范围[0,n)，最大值n为DHOP_YUV_getChannelNum接口返回的值,调用者必填 */
    /*
        表示即将打开的handle要每次要获取几种不同格式的YUV(即同一次获取的YUV是同源(序号),不同分辨率的)
        0或1表示只同时只获取1种格式的。最大值不超过DHOP_YUV_getChnMulCaps返回的有效个数
        如果fmtNum大于1，需要使用DHOP_YUV_getMulFrame/DHOP_YUV_releaseMulFrame接口
    */
    DH_Int8             fmtNum;
    DH_Int8             resByte[2];     /* 保留字段 */
    DH_Uint32           reserve[31];    /* 保留字段 */
}DHOP_YUV_OpenParam;


/* YUV设置参数 */
typedef struct
{
    DH_Uint16           fps;            /* YUV帧率,不超过DHOP_YUV_CapInfo中的maxFps */
    DH_Uint16           width;          /* YUV宽度,如果不满足对齐要求,内部向下对齐 */
    DH_Uint16           height;         /* YUV高度,如果不满足对齐要求,内部向下对齐*/
    DH_Uint16           format;         /* YUV格式,参考DHOP_YUV_Format */
    DH_Uint8            index;          /* 本次format生效的YUV索引值，索引值为[0,fmtNum)(其中fmtNum为DHOP_YUV_OpenParam中指定的值)*/
    DH_Uint8            rsv0;           /* 保留字段 */
    DH_Uint16           res[7];         /* 保留字段 */
} DHOP_YUV_FormatParam;


/* YUV扩展信息 */
typedef struct
{
    DH_Uint16           cbSize;         /* 结构体大小 */
    DH_Uint8            type;           /* 信息类型，定义参见DHOP_YUV_ExtInfoType */
    DH_Uint8            res[5];         /* 保留字段 */
    union
    {
        /* YUV携带的闪光灯信息，当前帧是在触发闪光灯后生成的图像 */
        struct
        {
            DH_Uint8    res[3];         /* 保留字段 */
            DH_Uint8    usrDataNum;     /* pUsrData数组元素个数 */

            /*
            用户数据数组，个数由usrDataNum指定，该数据由用户调用DHOP_DEVICE模块触
            发闪光灯时配置DHOP_FLASHLIGHT_CmdArgs 结构体中usrData 字段填入的数据；用于映射当成帧与用户的触发关系。
            对应的Device头文件参考dhop_flashlight.h
            */
            DH_Uint16*  pUsrData;
        } flashlight;

        struct
        {
            DH_Uint64        pts;         /* 抓拍帧PTS */
            DH_Uint64        sysJiffies;  /* 抓拍帧系统jiffies时间 */
            DHOP_SYS_UtcTime utcTime;     /* 抓拍帧UTC时间 */
            DH_Uint8         flag;        /* 抓拍帧标记 1为抓拍帧 0为非抓拍帧*/
            DH_Uint8         mark;        /* 抓拍帧计数 1-255 */
            DH_Uint8         res[2];
        } snap;

        DH_Uint32       szUnion[16];    /* 联合体大小 */
    } detail;
} DHOP_YUV_ExtInfo;


/* YUV帧数据 */
typedef struct
{
    DH_Uint32           cbSize;         /* 结构体大小 */
    DH_Uint32           frmSeq;         /* 帧序号 */
    DH_Uint64           pts;            /* 系统时间戳 */
    DH_Uint64           yuvStamp;       /* YUV的原始时间戳,能给编码后的视频帧匹配 */

    DHOP_YUV_PixelData  data;           /* 图像数据内容 */
    DHOP_YUV_ExtInfo    *pExtInfo;      /* YUV扩展信息,由DHOP分配内存,用户根据该指针是否为空及cbSize判断是否有扩展信息 */
    DH_Void             *privData;      /* DHOP使用的私有数据,不要修改 */
} DHOP_YUV_FrameData2;


/* YUV数据拷贝请求 */
typedef struct
{
    DH_Uint16           cbSize;         /* 结构体大小,调用者必填 */
    DH_Uint16           reserved;       /* 保留字段 */

    /******************************************************************************/
    /*                                                                            */
    /*   +----------------------------------------------------+                   */
    /*   |                                                    |                   */
    /*   |   +------------------+                             |                   */
    /*   |   |                  |                             |                   */
    /*   |   |      region      |                             |                   */
    /*   |   +--------||--------+                             |                   */
    /*   |            \\                                      |                   */
    /*   |             \\                                     |                   */
    /*   |              \\          source canvas             |                   */
    /*   +---------------++-----------------------------------+                   */
    /*                   ||                                                       */
    /*   +---------------++------------------------------+                        */
    /*   |              \||/                             |                        */
    /*   |      (x,y)o---\/-------------+                |                        */
    /*   |           |                  |                |                        */
    /*   |           |                  |                |                        */
    /*   +           +------------------+                |                        */
    /*   |                                               |                        */
    /*   |                      dest canvas              |                        */
    /*   +-----------------------------------------------+                        */
    /*                                                                            */
    /******************************************************************************/
    DHOP_YUV_PixelData  source;         /* YUV源数据,调用者必填 */
    DHOP_YUV_PixelData  dest;           /* YUV目标存放的数据,调用者必填 */

    /*
    拷贝子区域，子区域必须处于源图区域访问内，比如满足如下条件:
    1) region.x > 0;
    2) region.y > 0;
    3) (region.x + region.width) < source.width;
    4) (region.y + region.height) < source.height;
    5) (position.x + region.width) < dest.width;
    6) (position.y + region.height) < dest.height;
    */
    DH_Rect16           region;         /* 源数据中的区域 */
    DH_Point16          position;       /* 目标图像中的区域 */
} DHOP_YUV_CopyReq2;


/* YUV数据裁剪，裁剪区域支持缩放 */
typedef struct
{
    DH_Uint16           cbSize;         /* 结构体大小,调用者必填 */
    DH_Uint16           res[3];         /* 保留字段,调用者必填 */

    /******************************************************************************/
    /*                                                                            */
    /*   +----------------------------------------------------+                   */
    /*   |                                                    |                   */
    /*   |   +------------------+                             |                   */
    /*   |   |   from.region    |                             |                   */
    /*   |   |                  |                             |                   */
    /*   |   +--------||--------+                             |                   */
    /*   |            ||                                      |                   */
    /*   |           //                                       |                   */
    /*   |          ||          source canvas                 |                   */
    /*   +----------++----------------------------------------+                   */
    /*              ||                                                            */
    /*   +---------\++/----------------------------------+                        */
    /*   |     +----\/-----+                             |                        */
    /*   |     | to.region |                             |                        */
    /*   +     +-----------+                             |                        */
    /*   |                                               |                        */
    /*   |                      dest canvas              |                        */
    /*   +-----------------------------------------------+                        */
    /*                                                                            */
    /******************************************************************************/
    DHOP_YUV_PixelData  source;         /* YUV源数据,调用者必填 */
    DHOP_YUV_PixelData  dest;           /* YUV目标存放的数据,调用者必填 */

    DH_Rect16           from;           /* 源数据中的区域,调用者必填 */
    DH_Rect16           to;             /* 目标图像中的区域,调用者必填 */
} DHOP_YUV_ResizeReq;


//YUV可选配置
typedef struct
{
    DH_Uint32           cbSize;         /* 结构体大小,sizeof(DHOP_YUV_option),调用者必填 */
    DH_Uint32           type;           /* 可选配置类型,参考DHOP_YUV_OptionType,调用者必填 */
    union
    {
        DH_Uint16       depth;          /* 队列深度,有效范围为[1,maxDepth],调用者选填 */
        DH_Uint32       unSize[8];
    } option;
} DHOP_YUV_Option;
#endif

#if (__SIZEOF_POINTER__ == 8)           // 64位系统下结构体定义

/* YUV数据 */
typedef struct
{
    DH_Uint16           format;         /* YUV格式,参考DHOP_YUV_Format*/
    DH_Uint16           width;          /* YUV宽度 */
    DH_Uint16           height;         /* YUV高度 */
    DH_Uint16           stride[3];      /* YUV跨距，各分量数据跨距 */
    DH_Uint32           reserved;       /* 保留字段，对齐作用 */
    DHOP_YUV_PixelAddr  virAddr;        /* YUV数据虚拟地址 */
    DHOP_YUV_PixelAddr  phyAddr;        /* YUV数据物理地址 */
} DHOP_YUV_PixelData;

/* 设备YUV通道能力,调用者无需填写 */
typedef struct
{
    DH_Uint16           maxWidth;       /* 设备支持获取YUV的最大宽度 */
    DH_Uint16           maxHeight;      /* 设备支持获取YUV的最大高度 */
    DH_Uint16           minWidth;       /* 设备支持获取YUV的最小宽度 */
    DH_Uint16           minHeight;      /* 设备支持获取YUV的最小高度 */
    DH_Uint16           alignWidth;     /* YUV宽度对齐要求 */
    DH_Uint16           alignHeight;    /* YUV高度对齐要求 */
    DH_Uint16           maxFps;         /* 设备支持获取YUV的最大帧率 */
    DH_Uint16           fmtMask;        /* 设备支持YUV格式掩码,每一位代表一种格式,
                                            YUV格式可参考DHOP_YUV_Format */
    DH_Uint16           maxDepth;       /* 设备底层可以为当前通道缓存的YUV个数 */
    DH_Uint16           res16[3];       /* 保留字段 */
    DH_Uint64           reserve[3];     /* 保留字段 */
} DHOP_YUV_CapInfo;

/* YUV模块服务启动参数 */
typedef struct
{
    DH_Int8             channel;        /* 通道ID，取值范围[0,n)，最大值n为DHOP_YUV_getChannelNum接口返回的值,调用者必填 */
    /*
        表示即将打开的handle要每次要获取几种不同格式的YUV(即同一次获取的YUV是同源(序号),不同分辨率的)
        0或1表示只同时只获取1种格式的。最大值不超过DHOP_YUV_getChnMulCaps返回的有效个数
        如果fmtNum大于1，需要使用DHOP_YUV_getMulFrame/DHOP_YUV_releaseMulFrame接口
    */
    DH_Int8             fmtNum;
    DH_Int8             resByte[2];     /* 保留字段 */
    DH_Uint32           reserved[31];   /* 保留字段 */
}DHOP_YUV_OpenParam;

/* YUV设置参数 */
typedef struct
{
    DH_Uint16           fps;            /* YUV帧率,不超过DHOP_YUV_CapInfo中的maxFps,调用者必填 */
    DH_Uint16           width;          /* YUV宽度,如果不满足对齐要求,内部向下对齐,调用者必填 */
    DH_Uint16           height;         /* YUV高度,如果不满足对齐要求,内部向下对齐,调用者必填 */
    DH_Uint16           format;         /* YUV格式,参考DHOP_YUV_Format,调用者必填 */
    DH_Uint8            index;          /* 本次format生效的YUV索引值，索引值为[0,fmtNum)(其中fmtNum为DHOP_YUV_OpenParam中指定的值)*/
    DH_Uint8            rsv[15];        /* 保留字段 */
} DHOP_YUV_FormatParam;


/* YUV扩展信息 */
typedef struct
{
    DH_Uint16           cbSize;         /* 结构体大小 */
    DH_Uint8            type;           /* 信息类型，定义参见DHOP_YUV_ExtInfoType */
    DH_Uint8            res[5];         /* 保留字段 */
    union
    {
        /* YUV携带的闪光灯信息 */
        struct
        {
            DH_Uint8    res[7];         /* 保留字段 */
            DH_Uint8    usrDataNum;     /* pUsrData数组元素个数 */

            /*
            用户数据数组，个数由usrDataNum指定，该数据由用户调用DHOP_DEVICE模块触
            发闪光灯时配置DHOP_FLASHLIGHT_CmdArgs 结构体中usrData 字段填入的数据；用于映射当成帧与用户的触发关系。
            对应的Device头文件参考dhop_flashlight.h
            */
            DH_Uint16*  pUsrData;
        } flashlight;

        struct
        {
            DH_Uint64        pts;         /* 抓拍帧PTS */
            DH_Uint64        sysJiffies;  /* 抓拍帧系统jiffies时间 */
            DHOP_SYS_UtcTime utcTime;     /* 抓拍帧UTC时间 */
            DH_Uint8         flag;        /* 抓拍帧标记 1为抓拍帧 0为非抓拍帧*/
            DH_Uint8         mark;        /* 抓拍帧计数 1-255 */
            DH_Uint8         res[6];
        } snap;

        DH_Uint64       szUnion[16];    /* 联合体大小 */
    } detail;
} DHOP_YUV_ExtInfo;


/* YUV帧数据 */
typedef struct
{
    DH_Uint32           cbSize;         /* 结构体大小,调用者必填 */
    DH_Uint32           frmSeq;         /* 帧序号 */
    DH_Uint64           pts;            /* 系统时间戳 */
    DH_Uint64           yuvStamp;       /* YUV的原始时间戳,能给编码后的视频帧匹配 */

    DHOP_YUV_PixelData  data;           /* 图像数据内容 */
    DHOP_YUV_ExtInfo    *pExtInfo;      /* YUV扩展信息,由DHOP分配内存,用户根据该指针是否为空及cbSize判断是否有扩展信息 */
    DH_Void             *privData;      /* DHOP使用的私有数据,不要修改 */
} DHOP_YUV_FrameData2;


/* YUV数据拷贝请求 */
typedef struct
{
    DH_Uint16           cbSize;         /* 结构体大小,调用者必填 */
    DH_Uint16           res[3];         /* 保留字段,调用者必填 */

    /******************************************************************************/
    /*                                                                            */
    /*   +----------------------------------------------------+                   */
    /*   |                                                    |                   */
    /*   |   +------------------+                             |                   */
    /*   |   |                  |                             |                   */
    /*   |   |      region      |                             |                   */
    /*   |   +--------||--------+                             |                   */
    /*   |            \\                                      |                   */
    /*   |             \\                                     |                   */
    /*   |              \\          source canvas             |                   */
    /*   +---------------++-----------------------------------+                   */
    /*                   ||                                                       */
    /*   +---------------++------------------------------+                        */
    /*   |              \||/                             |                        */
    /*   |      (x,y)o---\/-------------+                |                        */
    /*   |           |                  |                |                        */
    /*   |           |                  |                |                        */
    /*   +           +------------------+                |                        */
    /*   |                                               |                        */
    /*   |                      dest canvas              |                        */
    /*   +-----------------------------------------------+                        */
    /*                                                                            */
    /******************************************************************************/
    DHOP_YUV_PixelData  source;         /* YUV源数据,调用者必填 */
    DHOP_YUV_PixelData  dest;           /* YUV目标存放的数据,调用者必填 */

    DH_Rect16           region;         /* 源数据中的区域,调用者必填 */
    DH_Point16          position;       /* 目地内存位置,调用者必填 */
    DH_Uint32           reserved;       /* 保留字段 */
} DHOP_YUV_CopyReq2;


/* YUV数据缩放请求 */
typedef struct
{
    DH_Uint16           cbSize;         /* 结构体大小,调用者必填 */
    DH_Uint16           res[3];         /* 保留字段 */

    /******************************************************************************/
    /*                                                                            */
    /*   +----------------------------------------------------+                   */
    /*   |                                                    |                   */
    /*   |   +------------------+                             |                   */
    /*   |   |   from.region    |                             |                   */
    /*   |   |                  |                             |                   */
    /*   |   +--------||--------+                             |                   */
    /*   |            ||                                      |                   */
    /*   |           //                                       |                   */
    /*   |          ||          source canvas                 |                   */
    /*   +----------++----------------------------------------+                   */
    /*              ||                                                            */
    /*   +---------\++/----------------------------------+                        */
    /*   |     +----\/-----+                             |                        */
    /*   |     | to.region |                             |                        */
    /*   +     +-----------+                             |                        */
    /*   |                                               |                        */
    /*   |                      dest canvas              |                        */
    /*   +-----------------------------------------------+                        */
    /*                                                                            */
    /******************************************************************************/
    DHOP_YUV_PixelData  source;         /* YUV源数据,调用者必填 */
    DHOP_YUV_PixelData  dest;           /* YUV目标存放的数据,调用者必填 */

    DH_Rect16           from;           /* 源数据中的区域,调用者必填 */
    DH_Rect16           to;             /* 目标图像中的区域,调用者必填 */
} DHOP_YUV_ResizeReq;


//YUV可选配置
typedef struct
{
    DH_Uint32           cbSize;         /* 结构体大小,sizeof(DHOP_YUV_option),调用者必填 */
    DH_Uint32           type;           /* 可选配置类型,调用者必填 */
    union
    {
        DH_Uint16       depth;          /* 队列深度,有效范围为[1,maxDepth],调用者必填 */
        DH_Uint32       unSize[8];
    } option;
} DHOP_YUV_Option;
#endif

/*******************************************************************************/

/***************************************************************
* function name : DHOP_YUV_getCaps
*
* description   : 获取0通道的YUV能力，如果要获取其它通道的能力，可
*                 采用DHOP_YUV_getChnCaps方式获取。
*
* input         : 无
*
* output        : pCapInfo  -- 能力集
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_getCaps(DHOP_YUV_CapInfo *pCapInfo);

/***************************************************************
* function name : DHOP_YUV_getChannelNum
*
* description   : 获取当前设备支持的通道数
*
* input         : 无
*
* output        : 无
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : 小于0表示失败，其它值为有效通道数
***************************************************************/
DH_Int32 DHOP_YUV_getChannelNum(DH_Void);


/***************************************************************
* function name : DHOP_YUV_getChnCaps
*
* description   : 对DHOP_YUV_getCaps接口的扩展补充，在视频多通道产品上
*                 允许获取指定通道的能力，比如：
*                 1) 双Sensor背靠背的摄像机产品，用户可以获取指定视频通道的能力信息
*                 2) NVR产品，接入多个IPC，在NVR上可以获取指定通道的数据
*
* input         : channelId -- 通道ID，取值范围[0,n)，最大值n为DHOP_YUV_getChannelNum接口返回的值
*
* output        : pCapInfo  -- 能力集
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 其它 - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_getChnCaps(DH_Uint32 channelId, DHOP_YUV_CapInfo  *pCapInfo);


/***************************************************************
* function name : DHOP_YUV_getChnMulCaps
*
* description   : 对于有些设备，可以一次获取多张不同格式的同源YUV，对应的能力也就有多个
*                 此时，可以通过该接口，获取设备提供的每一种YUV的能力范围
*
* input         : channelId -- 通道ID，取值范围[0,n)，最大值n为DHOP_YUV_getChannelNum接口返回的值
* input         : pCapInfos -- 调用者提供的能力集数组
* input         : pNum -- 调用者提供的能力集数组的个数
*
* output        : pCapInfos  -- 实际获取到的能力集
* output        : pNum       -- 实际获取到的能力集个数
*
* notice        : 1. 线程安全
*                 2. 同步接口
*
* return value  : DHOP_SUCCESS: success
*                 DHOP_FAILED:  fail
*                 其它 - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_getChnMulCaps(DH_Uint32 channelId, DHOP_YUV_CapInfo *pCapInfos, DH_Uint32 *pNum);

/***************************************************************
* function name : DHOP_YUV_open
*
* description   : 开启YUV服务
*
* input         : pOpenParam -- 启动参数.
*
* output        : hYuv -- YUV操作句柄
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. open成功后返回有效的YUV操作句柄,
*                    并且每个app只能open成功一次
*                 4. 获取到的操作句柄仅在同进程内有效,
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_open(DHOP_YUV_OpenParam * pOpenParam, DH_Handle *hYuv);


/***************************************************************
* function name : DHOP_YUV_setFormat
*
* description   : 设置YUV格式参数
*
* input         : pFmtParam -- YUV参数
*                 hYuv -- YUV操作句柄
*
* output        : None
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 需要有效的YUV操作句柄
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_setFormat(DH_Handle hYuv, DHOP_YUV_FormatParam *pFmtParam);


/***************************************************************
* function name : DHOP_YUV_getFrame2
*
* description   : 获取一帧YUV
*
* input         : hYuv -- YUV操作句柄
*                 pFrmData -- YUV帧数据
*                 timeout -- 超时时间
*                 <0 : 阻塞
*                 =0 : 非阻塞
*                 >0 : 超时时间(ms)
*
* notice        : 1. 目前仅IPC产品支持该接口
*                 2. 线程安全
*                 3. 同步接口
*                 4. 需要有效的YUV操作句柄
*                 5. 适用于DHOP V1.2.0及以上版本
*
* output        : none
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_getFrame2(DH_Handle hYuv, DHOP_YUV_FrameData2 *pFrmData, DH_Int32 timeout);


/***************************************************************
* function name : DHOP_YUV_releaseFrame2
*
* description   : 释放YUV，将逐步替代DHOP_YUV_releaseFrame
*
* input         : pYuvData -- YUV数据
*                 hYuv -- YUV操作句柄
*
* output        : None
*
* notice        : 1. 目前仅IPC产品支持该接口
*                 2. 线程安全
*                 3. 同步接口
*                 4. 需要有效的YUV操作句柄
*                 5. 重复释放同一帧YUV数据会返回相关错误码
*                 6. 适用于DHOP V1.2.0及以上版本
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_releaseFrame2(DH_Handle hYuv, const DHOP_YUV_FrameData2 *pYuvData);

/***************************************************************
* function name : DHOP_YUV_getMulFrame
*
* description   : 一次获取多帧yuv
*
* input         : hYuv -- YUV操作句柄
*                 pFrmDatas -- 调用者提供的存放YUV帧数据的数组
*                 yuvNum -- 调用者提供的pFrmDatas分配的个数
*                 timeout -- 超时时间
*                 <0 : 阻塞
*                 =0 : 非阻塞
*                 >0 : 超时时间(ms)
*
* output        : pFrmDatas -- 实际获取的YUV帧数据
* notice        : 1. 目前仅IPC产品支持该接口
*                 2. 线程安全
*                 3. 同步接口
*                 4. 需要有效的YUV操作句柄
*                 5. 适用于DHOP V1.2.4及以上版本
*
* output        : none
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_getMulFrame(DH_Handle hYuv, DHOP_YUV_FrameData2 *pFrmDatas, DH_Uint32 yuvNum, DH_Int32 timeout);

/***************************************************************
* function name : DHOP_YUV_releaseMulFrame
*
* description   : 一次释放多帧yuv
*
* input         : hYuv -- YUV操作句柄
*                 pYuvDatas -- 调用者提供的待释放的YUV数组
*                 yuvNum -- 调用者提供的待释放的YUV数组个数
*
* output        : None
*
* notice        : 1. 目前仅IPC产品支持该接口
*                 2. 线程安全
*                 3. 同步接口
*                 4. 需要有效的YUV操作句柄
*                 5. 重复释放同一帧YUV数据会返回相关错误码
*                 6. 适用于DHOP V1.2.4及以上版本
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_releaseMulFrame(DH_Handle hYuv, const DHOP_YUV_FrameData2 *pYuvDatas, DH_Uint32 yuvNum);

/***************************************************************
* function name : DHOP_YUV_close
*
* description   : 关闭YUV服务
*
* input         : hYuv -- YUV操作句柄
*
* output        : none
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 需要有效的YUV操作句柄
*                 4. 关闭成功后句柄失效
*                    app可再次调用open接口开启YUV服务
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_close(DH_Handle *hYuv);


/***************************************************************
* function name : DHOP_YUV_copy2
*
* description   : 拷贝YUV数据
*
* input         : hYuv -- 操作句柄
*                 pCopyReq -- 拷贝请求
*
* output        : none
*
* notice        : 1. 目前仅IPC产品支持该接口
*                 2. 线程安全
*                 3. 同步接口
*                 4. 接口支持两种句柄输入:
*                    a:open接口获取的YUV操作句柄
*                    b:DHOP_YUV_getAnonyHandle获取的匿名操作句柄
*                 5. 适用于DHOP V1.2.0及以上版本
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_copy2(DH_Handle hYuv, DHOP_YUV_CopyReq2 * pCopyReq);

/***************************************************************
* function name : DHOP_YUV_resize2
*
* description   : YUV数据缩放
*
* input         : hYuv -- 操作句柄
*                 pResizeReq -- 缩放请求
*
* output        : none
*
* notice        : 1. 线程安全
*                 2. 同步接口
*                 3. 接口支持两种句柄输入:
*                    a:open接口获取的YUV操作句柄
*                    b:DHOP_YUV_getAnonyHandle获取的匿名操作句柄
*                 4. 适用于DHOP V1.2.0及以上版本
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_resize2(DH_Handle hYuv, DHOP_YUV_ResizeReq * pResizeReq);


/***************************************************************
* function name : DHOP_YUV_setOption
*
* description   : 设置YUV可选配置
*
* input         : hYuv -- 操作句柄
*                 pOption -- 可选配置
*
* output        : none
*
* notice        : 1. 目前仅IPC产品支持该接口
*                 2. 线程安全
*                 3. 同步接口
*                 4. 需要有效的YUV操作句柄
*                 5. 适用于DHOP V1.2.0及以上版本
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_setOption(DH_Handle hYuv, DHOP_YUV_Option *pOption);


/***************************************************************
* function name : DHOP_YUV_getAnonyHandle
*
* description   : 获取匿名YUV操作句柄
*
* input         : none
*
* output        : hYuv -- 操作句柄
*
* notice        : 1. 目前仅IPC产品支持该接口
*                 2. 线程安全
*                 3. 同步接口
*                 4. 获取到的匿名句柄可用于拷贝和缩放操作
*                 5. 适用于DHOP V1.2.0及以上版本
*
* return value  : 0: success
*                 Non 0:  fail -- ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_YUV_getAnonyHandle(DH_Handle *hYuv);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_YUV_H__


