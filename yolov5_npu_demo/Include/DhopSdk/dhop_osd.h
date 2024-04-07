/*******************************************************************************
 * dhop_osd.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 本模块中提供的功能，仅在大华产品体系中有效，在大华的解码产品体系中
 *              支持将叠加信息绘制显示。包含: web预览
 *
 *******************************************************************************/

#ifndef __DHOP_OSD_H__
#define __DHOP_OSD_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"


/*******************************************************************************/

/* max text length */
#define DHOP_OSD_TEXT_MAX_LENGTH       512

/* 绘制对象状态 */
typedef enum
{
    DHOP_OSD_PS_NEW = 0,                    // 创建: 对象创建, 新增对象ID
    DHOP_OSD_PS_HIDE,                       // 隐藏: 对象隐藏
    DHOP_OSD_PS_UPDATE,                     // 更新: 对象更新位置或其他信息
    DHOP_OSD_PS_DELETE,                     // 销毁: 对象销毁
} DHOP_OSD_PaintState;

/* 文本内容字符集 */
typedef enum
{
    DHOP_OSD_CS_UTF8 = 0,                   // UTF-8字符集
    DHOP_OSD_CS_GBK                         // GBK字符集
} DHOP_OSD_CharSet;

/* 元素类型 */
typedef enum
{
    DHOP_OSD_ET_PIE = 0,                    // 圆饼
    DHOP_OSD_ET_TEXT,                       // 文本
    DHOP_OSD_ET_POLYLINE,                   // 折线
    DHOP_OSD_ET_POLYGON,                    // 多边形
} DHOP_OSD_ElemType;

typedef enum
{
    DHOP_OSD_RS_NONE = 0x00,                // 无边框且不填充
    DHOP_OSD_RS_SOLID = 0x01,               // 实线边框但无填充
    DHOP_OSD_RS_DASHED = 0x02,              // 虚线边框但无填充
    DHOP_OSD_RS_FILLING = 0x10,             // 无边框但有填充
    DHOP_OSD_RS_SOLID_FILLING = 0x11,       // 实线边框且有填充
    DHOP_OSD_RS_DASHED_FILLING = 0x12,      // 虚线边框且有填充
} DHOP_OSD_RegionStyle;

typedef enum
{
    DHOP_OSD_LS_SOLID = 0x01,               // 实线
    DHOP_OSD_LS_DASHED,                     // 虚线
} DHOP_OSD_LineStyle;

/*******************************************************************************/

typedef struct
{
    DH_Uint16               x;              // x坐标，调用者必填
    DH_Uint16               y;              // y坐标，调用者必填
} DHOP_OSD_Point;

/* 字体颜色 */
typedef struct
{
    DH_Uint8                A;              // 透明分量，调用者必填
    DH_Uint8                R;              // Red分量，调用者必填
    DH_Uint8                G;              // Green分量，调用者必填
    DH_Uint8                B;              // Blue分量，调用者必填
} DHOP_OSD_COLOR;

typedef struct
{
    DH_Uint8                type;           // 固定值DHOP_OSD_ET_PIE，调用者必填
    DH_Uint8                borderWeight;   // 圆的边框线宽，表示基准1的倍数.基准1由解码端决定，调用者必填
    DH_Uint16               radius;         // 基于8192坐标系，调用者必填
    DH_Uint8                style;          // 样式，参见DHOP_OSD_RegionStyle，调用者必填
    DH_Uint8                res0[3];        //调用者无需填写
    DHOP_OSD_Point          center;         // 圆心坐标，调用者必填，根据《DHOP_OSD_Point》结构体注释填写
    DHOP_OSD_COLOR          clrBorder;      // 边框颜色，调用者必填，根据《DHOP_OSD_COLOR》结构体注释填写
    DHOP_OSD_COLOR          clrFiller;      // 填充颜色，调用者必填，根据《DHOP_OSD_COLOR》结构体注释填写
    DH_Uint8                res1[4];        //调用者无需填写
} DHOP_OSD_Pie;
 
typedef struct
{
    DH_Uint8                type;           // 固定值DHOP_OSD_ET_TEX,调用者必填
    DH_Uint8                charset;        // text所采用的字符集，,调用者必填,参见DHOP_OSD_CharSet
    DH_Uint8                fontsize;       // 字体大小,调用者必填
    DH_Uint8                res;            // 保留字段,调用者必填
    DHOP_OSD_Point          position;       // 文字左上角坐标,调用者必填，根据《DHOP_OSD_Point》结构体注释填写
    DHOP_OSD_COLOR          color;          // 字体颜色,调用者必填，根据《DHOP_OSD_COLOR》结构体注释填写
    DH_Uint16               resshort;       // 保留字段，调用者无需填写
    DH_Uint16               length;         // 外部传入，文字内容占用多少字节,调用者如果调用text必须填写
    DH_Char                 *text;          // 文字内容,调用者根据需要选填
} DHOP_OSD_Text;

typedef struct
{
    DH_Uint8                type;           // 固定值DHOP_OSD_ET_POLYLINE，调用者必填
    DH_Uint8                pointNum;       // 当前折线端点的个数，调用者必填
    DH_Uint8                borderWeight;   // 线的宽度，表示基准1的倍数.基准1由解码端决定，调用者必填
    DH_Uint8                style;          // 样式，参见DHOP_OSD_LineStyle，调用者必填
    DHOP_OSD_COLOR          color;          // 线条颜色，调用者必填，根据《DHOP_OSD_COLOR》结构体注释填写
    DHOP_OSD_Point          *points;        // 点序列，调用者必填，根据《DHOP_OSD_Point》结构体注释填写
} DHOP_OSD_PolyLine;

#if (__SIZEOF_POINTER__ == 4)               // 32位系统下结构体定义
typedef struct
{
    DH_Int16                x;              // 框的左上角x坐标，8192坐标系，调用者必填
    DH_Int16                y;              // 框的左上角y坐标，8192坐标系，调用者必填
    DH_Int16                w;              // 框的宽度，8192坐标系，调用者必填
    DH_Int16                h;              // 框的高度，8192坐标系，调用者必填
    DH_Int32                reserved[6];    // 保留字段，调用者无需填写
} DHOP_OSD_Box;

typedef struct
{
    DH_Uint64               pts;            // 时间戳信息，暂填0，调用者必填
    DH_Uint32               nbrOfBox;       // box的个数，调用者必填
    DHOP_OSD_Box*           boxList;        // box列表，调用者必填
} DHOP_OSD_BoxInfo;

typedef struct
{
    DH_Uint8                type;           // 固定值DHOP_OSD_ET_POLYGON，调用者必填
    DH_Uint8                borderWeight;   // 圆的边框线宽，表示基准1的倍数.基准1由解码端决定，调用者必填
    DH_Uint8                style;          // 样式，参见DHOP_OSD_RegionStyle，调用者必填
    DH_Uint8                pointNum;       // 当前折线端点的个数，调用者必填
    DH_Uint8                res[4];
    DHOP_OSD_COLOR          clrBorder;      // 边框颜色，调用者必填，根据《DHOP_OSD_COLOR》结构体注释填写
    DHOP_OSD_COLOR          clrFiller;      // 填充颜色，调用者必填，根据《DHOP_OSD_COLOR》结构体注释填写
    DHOP_OSD_Point          *points;        // 点序列，调用者必填，根据《DHOP_OSD_Point》结构体注释填写
} DHOP_OSD_Polygon;

#endif
#if (__SIZEOF_POINTER__ == 8)               // 64位系统下结构体定义
typedef struct
{
    DH_Int16                x;              // 框的左上角x坐标，8192坐标系，调用者必填
    DH_Int16                y;              // 框的左上角y坐标，8192坐标系，调用者必填
    DH_Int16                w;              // 框的宽度，8192坐标系，调用者必填
    DH_Int16                h;              // 框的高度，8192坐标系，调用者必填
    DH_Int32                reserved[6];    // 保留字段，调用者无需填写
} DHOP_OSD_Box;

typedef struct
{
    DH_Uint64               pts;            // 时间戳信息，暂填0，调用者必填
    DH_Uint32               nbrOfBox;       // box的个数，调用者必填
    DH_Uint32               resByte;        // 保留字段，调用者无需填写
    DHOP_OSD_Box*           boxList;        // 调box列表，调用者必填
} DHOP_OSD_BoxInfo;

typedef struct
{
    DH_Uint8                type;           // 固定值DHOP_OSD_ET_POLYGON，调用者必填
    DH_Uint8                borderWeight;   // 圆的边框线宽，表示基准1的倍数.基准1由解码端决定，调用者必填
    DH_Uint8                style;          // 样式，参见DHOP_OSD_RegionStyle，调用者必填
    DH_Uint8                pointNum;       // 当前折线端点的个数,调用者必填
    DH_Uint8                res[4];
    DHOP_OSD_COLOR          clrBorder;      // 边框颜色，调用者必填，调用者必填，根据《DHOP_OSD_COLOR》结构体注释填写
    DHOP_OSD_COLOR          clrFiller;      // 填充颜色，调用者必填，调用者必填，根据《DHOP_OSD_COLOR》结构体注释填写
    DHOP_OSD_Point          *points;        // 点序列，调用者必填，根据《DHOP_OSD_Point》结构体注释填写
} DHOP_OSD_Polygon;

#endif

/* 该联合体是可以32/64共用 */
typedef union
{
    DHOP_OSD_Pie            *pie;           // 圆饼
    DHOP_OSD_Text           *text;          // 文本
    DHOP_OSD_PolyLine       *line;          // 折线
    DHOP_OSD_Polygon        *region;        // 多边形
} DHOP_OSD_Element;

/* 该联合体是可以32/64共用 */
typedef struct
{
    DH_Uint32               chn;            // 通道号，调用者必填
    DH_Uint32               id;             // 绘制的对象ID，调用者必填

    /*
    如果是根据YUV进行检测分析的结果，可以填写YUV的DHOP_YUV_FrameData的yuvStamp，
    OSD会尽量插入到YUV对应的视频帧附近.如果填0，收到会立即发出
    */
    DH_Uint64               pts;            

    DH_Uint16               coustomerField; // 用户自定义字段标识，short类型的
    DH_Uint8                state;          // DHOP_OSD_PaintState，调用者必填
    DH_Uint8                numOfElem;      // 对象的组成元素个数，调用者必填
    DH_Uint32               resv;           // 调用者无需填写
    DHOP_OSD_Element        *elems;         // 对象的组成原始列表（数组）,调用者必填，根据《DHOP_OSD_Element》填写
} DHOP_OSD_PaintWork;

/*******************************************************************************/

/*******************************************************************************
* function name : DHOP_OSD_drawBox
*
* description   : 在大华码流中插入OSD矩形框信息，在大华的产品体系中，设备端的web能够在
*                 预览画面中显示OSD矩形框信息，在后端产品的画面中也能够显示OSD矩形框信息
*                 , 该OSD为后处理显示，并非在编码前将信息混入图像后再进行图像编码。
*                 OSD的坐标系为8192x8192归一化的坐标系
*
* input         : pBoxInfo     -- 矩形框信息
*
* output        : None
* notice        : 1. 接口线程安全. 2. 不建议使用. 绘制效果较简单，只能绘制矩形
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_OSD_drawBox(DHOP_OSD_BoxInfo *pBoxInfo);


/*******************************************************************************
* function name : DHOP_OSD_richPaint
*
* description   : 在大华码流中插入绘制描述信息，解码时会根据信息进行绘制显示。
*                 信息为大华私有帧协议，需要配合大华提供的解码库或控件才有效。
*                 显示端最多维护256个对象ID。
*                 OSD的坐标系为8192x8192归一化的坐标系。
*
*                 典型场景：
*                   1) 人体检测，检测到人体后绘制矩形框并在框附近有文字描述（如：身高）
*                   2）人体检测，检测到人体后对人体轮廓进行绘制，内部为半透明填充
*                   3）骨架检测，通过关节点和线条，绘制出目标物体的骨架
*
* input         : pObjs     -- 描述对象列表
* input         : num       -- 描述对象个数
*
* output        : None
* notice        : 1. 接口线程安全.
*
* return value  : DHOP_SUCCESS - 成功
*               : DHOP_FAILED  - 失败
*               : 其它         - 参考DHOP_ErrorCode
*******************************************************************************/
DH_Int32 DHOP_OSD_richPaint(DHOP_OSD_PaintWork *pObjs, DH_Uint32 num);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_OSD_H__

