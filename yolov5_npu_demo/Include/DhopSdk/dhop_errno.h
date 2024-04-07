/*******************************************************************************
 * dhop_errno.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义DHOP中涉及到的错误码
 *
 *******************************************************************************/

#ifndef __DHOP_ERRNO_H__
#define __DHOP_ERRNO_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"


/*******************************************************************************/

/* definition of common return values of function */
#define DHOP_SUCCESS        ( 0)
#define DHOP_FAILED         (-1)


/*******************************************************************************/

/*
0x80系列错误码 -- Fatal Error
0x81系列错误码 -- Common Error
*/
typedef enum
{
    /* 通用错误码 */
    DHOP_ERR_UNSUPPORT              = 0x80000000,   /* 功能不支持 */
    DHOP_ERR_ILLEGAL_INPUT,                         /* 函数存在非法输入 */
    DHOP_ERR_PARAM_IS_NULL,                         /* 输入参数为NULL */
    DHOP_ERR_RESOURCE_BUSY,                         /* 资源正在使用中 */
    DHOP_ERR_INVALID_PARMETER,                      /* 无效的参数 */
    DHOP_ERR_OUT_OF_RANGE,                          /* 超出有效范围 */
    DHOP_ERR_TIMEOUT,                               /* 处理过程超时 */
    DHOP_ERR_FIFO_INVALID,                          /* 通信资源不可用 */
    DHOP_ERR_INVALID_HANDLE,                        /* 无效的操作句柄 */
    DHOP_ERR_LINK_INVALID,                          /* 通信链路不可用 */
    DHOP_ERR_SYS_INIT_REPEATED,                     /* 系统重复初始化 */
    DHOP_ERR_SYS_NOT_INIT,                          /* 系统未初始化 */
    DHOP_ERR_RESOURCE_INVALID,                      /* 资源不可用 */
    DHOP_ERR_OPERATE_NOT_PERMIT,                    /* 操作不允许 */
    DHOP_ERR_BUFFER_NOT_ENOUGH,                     /* 提供的buffer不足 */
    DHOP_ERR_STRUCT_SIZE_INVALID,                   /* 参数的结构体中cbSize字段填写不正确 */

    /* 调用Posix API失败系列 */
    DHOP_ERR_POSIX_API_FAIL1        = 0x80000100,   /* 调用Posix API-1失败 */
    DHOP_ERR_POSIX_API_FAIL2,                       /* 调用Posix API-2失败 */
    DHOP_ERR_POSIX_API_FAIL3,                       /* 调用Posix API-3失败 */
    DHOP_ERR_POSIX_API_FAIL4,                       /* 调用Posix API-4失败 */
    DHOP_ERR_POSIX_API_FAIL5,                       /* 调用Posix API-5失败 */
    DHOP_ERR_POSIX_API_FAIL6,                       /* 调用Posix API-6失败 */
    DHOP_ERR_POSIX_API_FAIL7,                       /* 调用Posix API-7失败 */
    DHOP_ERR_POSIX_API_FAIL8,                       /* 调用Posix API-8失败 */
    DHOP_ERR_POSIX_API_FAIL9,                       /* 调用Posix API-9失败 */
    DHOP_ERR_POSIX_API_FAIL10,                      /* 调用Posix API-10失败 */
    DHOP_ERR_POSIX_API_FAIL11,                      /* 调用Posix API-11失败 */
    DHOP_ERR_POSIX_API_FAIL12,                      /* 调用Posix API-12失败 */
    DHOP_ERR_POSIX_API_FAIL13,                      /* 调用Posix API-13失败 */
    DHOP_ERR_POSIX_API_FAIL14,                      /* 调用Posix API-14失败 */
    DHOP_ERR_POSIX_API_FAIL15,                      /* 调用Posix API-15失败 */

    /* 调用厂商 API失败系列 */
    DHOP_ERR_VENDOR_API_FAIL1        = 0x80000200,  /* 调用厂商 API-1失败 */
    DHOP_ERR_VENDOR_API_FAIL2,                      /* 调用厂商 API-2失败 */
    DHOP_ERR_VENDOR_API_FAIL3,                      /* 调用厂商 API-3失败 */
    DHOP_ERR_VENDOR_API_FAIL4,                      /* 调用厂商 API-4失败 */
    DHOP_ERR_VENDOR_API_FAIL5,                      /* 调用厂商 API-5失败 */
    DHOP_ERR_VENDOR_API_FAIL6,                      /* 调用厂商 API-6失败 */
    DHOP_ERR_VENDOR_API_FAIL7,                      /* 调用厂商 API-7失败 */
    DHOP_ERR_VENDOR_API_FAIL8,                      /* 调用厂商 API-8失败 */
    DHOP_ERR_VENDOR_API_FAIL9,                      /* 调用厂商 API-9失败 */
    DHOP_ERR_VENDOR_API_FAIL10,                     /* 调用厂商 API-10失败 */
    DHOP_ERR_VENDOR_API_FAIL11,                     /* 调用厂商 API-11失败 */
    DHOP_ERR_VENDOR_API_FAIL12,                     /* 调用厂商 API-12失败 */
    DHOP_ERR_VENDOR_API_FAIL13,                     /* 调用厂商 API-13失败 */
    DHOP_ERR_VENDOR_API_FAIL14,                     /* 调用厂商 API-14失败 */
    DHOP_ERR_VENDOR_API_FAIL15,                     /* 调用厂商 API-15失败 */
    DHOP_ERR_VENDOR_API_FAIL16,                     /* 调用厂商 API-16失败 */
    DHOP_ERR_VENDOR_API_FAIL17,                     /* 调用厂商 API-17失败 */
    DHOP_ERR_VENDOR_API_FAIL18,                     /* 调用厂商 API-18失败 */
    DHOP_ERR_VENDOR_API_FAIL19,                     /* 调用厂商 API-19失败 */
    DHOP_ERR_VENDOR_API_FAIL20,                     /* 调用厂商 API-20失败 */

    DHOP_ERR_SYS_xxx                = 0x80010000,
    DHOP_ERR_SYS_IS_NOT_READY,                      /* 未初始化DHOP系统 */
    DHOP_ERR_SYS_USERNAME_MODIFY_UNSUPPORT,         /* 用户名不支持修改 */
    DHOP_ERR_SYS_ACCOUNT_USER_EXIST,                /* 用户已经存在 */
    DHOP_ERR_SYS_ACCOUNT_USER_NOTEXIST,             /* 用户不存在 */
    DHOP_ERR_SYS_ACCOUNT_PWD_INVALID,               /* 密码不可用 */
    DHOP_ERR_SYS_ACCOUNT_PWD_ERROR,                 /* 密码校验错误 */
    DHOP_ERR_SYS_ACCOUNT_PWD_ENCERROR,              /* 密码加密失败 */
    DHOP_ERR_SYS_ACCOUNT_AUTH_INVALID,              /* 权限错误 */
    DHOP_ERR_SYS_ACCOUNT_SYS_ERROR,                 /* 系统操作失败 */
    DHOP_ERR_SYS_ACCOUNT_GRP_CHKERR,                /* 用户组检查错误 */

    DHOP_ERR_LOG_INIT_FAIL          = 0x80020000,
    DHOP_ERR_LOG_IS_NOT_READY,                      /* 日志模块未初始化 */

    DHOP_ERR_APP_xxx                = 0x80030000,
    DHOP_ERR_APP_SUDO_GET_WORK_PATH_FAIL,          /* 获取工作路径失败 */
    DHOP_ERR_APP_SUDO_ALG_LIC_NOT_FOUND,           /* 未找到算法证书 */
    DHOP_ERR_APP_SUDO_ALG_LIC_DST_DIR_UNEXIST,     /* 算法证书目标目录不存在 */
    DHOP_ERR_APP_SUDO_ALG_LIC_DST_DIR_READY_ONLY,  /* 算法证书目标目录不可写入 */
    DHOP_ERR_APP_SUDO_ALG_LIC_LOAD_FAIL,           /* 算法证书载入失败 */
    DHOP_ERR_APP_SUDO_ALG_LIC_RELOAD_FAIL,         /* 算法证书重载失败 */
    DHOP_ERR_APP_SUDO_CHMOD_INVALID_PATH,          /* 修改目录权限:无效的路径 */
    DHOP_ERR_APP_SUDO_CHMOD_INVALID_MODE,          /* 修改目录权限:无效的权限 */
    DHOP_ERR_APP_SUDO_MODULE_NOT_FOUND,            /* 未找到模块文件 */
    DHOP_ERR_APP_SUDO_MODULE_REPEAT_INSTALL,       /* 重复安装模块 */
    DHOP_ERR_APP_SUDO_MODULE_NOT_INSTALL,          /* 未安装模块 */
    DHOP_ERR_APP_SUDO_MODULE_INSTALL_FAIL,         /* 模块安装失败 */

    DHOP_ERR_MEM_PARAM_FAIL         = 0x80040000,   /*输入参数有误*/
    DHOP_ERR_MEM_NOMEM,                             /*内存申请失败*/
    DHOP_ERR_MEM_ADDR_UNEXIST,                      /*内存地址不存在*/
    DHOP_ERR_MEM_NOT_PERMIT,                        /*操作不允许*/


    DHOP_ERR_YUV_GET_PLAT_INFO_FAIL = 0x80050000,   /* 获取平台信息失败 */
    DHOP_ERR_YUV_NULL_PTR,                          /* 输入参数中有空指针 */
    DHOP_ERR_YUV_INVALID_HANDLE,                    /* 使用无效的操作句柄 */
    DHOP_ERR_YUV_INVALID_FMT,                       /* 使用无效的YUV格式    */
    DHOP_ERR_YUV_INVALID_SIZE,                      /* 使用无效的YUV尺寸 */
    DHOP_ERR_YUV_INVALID_FPS,                       /* 使用无效的YUV帧率 */
    DHOP_ERR_YUV_CREATE_COMM_FAIL,                  /* YUV模块创建通信失败 */
    DHOP_ERR_YUV_DESTROY_COMM_FAIL,                 /* YUV模块销毁通信失败 */
    DHOP_ERR_YUV_INVALID_CHN,                       /* 无效的YUV通道号 */
    DHOP_ERR_YUV_REPEAT_OPEN,                       /* YUV通道重复开启 */
    DHOP_ERR_YUV_INIT_LINK_FAIL,                    /* 初始化链接失败 */
    DHOP_ERR_YUV_DEINIT_LINK_FAIL,                  /* 去初始化链接失败 */
    DHOP_ERR_YUV_CHN_NOT_EXIST,                     /* YUV通道不存在 */
    DHOP_ERR_YUV_INVALID_RECT,                      /* 无效区域 */
    DHOP_ERR_YUV_INVALID_ZOOM_FACTOR,               /* 无效的缩放倍数 */
    DHOP_ERR_YUV_INVALID_STRIDE,                    /* 无效的跨距 */
    DHOP_ERR_YUV_INVALID_DATA_ADDR,                 /* 无效的数据地址 */
    DHOP_ERR_YUV_GET_HANDLE_FAIL,                   /* 申请YUV操作句柄失败 */
    DHOP_ERR_YUV_RELEASE_HANDLE_FAIL,               /* 释放YUV操作句柄失败 */
    DHOP_ERR_YUV_INVALID_LINK,                      /* 无效的通信链接 */
    DHOP_ERR_YUV_RESOURCE_NOT_EXIST,                /* YUV资源不存在 */
    DHOP_ERR_YUV_NOT_READY,                         /* 未初始化 */
    DHOP_ERR_YUV_INVALID_DEPTH,                     /* 无效的YUV队列深度 */
    DHOP_ERR_YUV_INTERNAL_COMM_FAIL,                /* YUV模块内部通信失败 */
    DHOP_ERR_YUV_BUFF_IS_FULL,                      /* YUV数据内存已满 */
    DHOP_ERR_YUV_BUFF_IS_EMPTY,                     /* 无YUV数据产生 */
    DHOP_ERR_YUV_CHANNEL_IS_BUSY,                   /* YUV通道忙 */
    DHOP_ERR_YUV_INVALID_POSITION,                  /* 无效的位置 */
    DHOP_ERR_YUV_INVALID_OPT_TYPE,                  /* 无效的可选配置类型 */
    DHOP_ERR_YUV_INVALID_YUV_FRAME,                 /* 无效的YUV帧 */

    DHOP_ERR_STREAM_END_OF_RECORD     = 0x80060000,  /* 表示回放的录像文件已读完 */
    DHOP_ERR_STREAM_INIT_LINK_FAIL,                  /* 初始化链接失败 */
    DHOP_ERR_STREAM_LINK_COMM_FAIL,                  /* 链接通信失败 */
    DHOP_ERR_STREAM_DEINIT_LINK_FAIL,                /* 去初始化链接失败 */
    DHOP_ERR_STREAM_CREATE_REPEATED,                 /* STREAMID重复创建*/
    DHOP_ERR_STREAM_STREAMID_IS_DISABLE,             /* STREAMID未使能*/
    DHOP_ERR_STREAM_STREAMID_NO_SUPPORT,             /* STREAMID不支持*/
    DHOP_ERR_STREAM_STREAMID_IS_ClOSING,             /* STREAM已退出，先释放所有数据*/
    DHOP_ERR_STREAM_RELEASE_OUT_OF_ORDER,            /* 数据不按顺序释放*/
    DHOP_ERR_STREAM_RELEASE_PACKET_UNEXIST,          /* 数据包非法 */
    DHOP_ERR_STREAM_STREAMID_CLOSE_IS_BUSY,          /* 当前STREAMID有数据未释放,先释放当前数据*/
    DHOP_ERR_STREAM_RECORD_OPEN_FAILED,              /* 录像文件打开失败*/
    DHOP_ERR_STREAM_GET_PACKET_TIMEOUT,              /* 获取码流数据超时 */
    DHOP_ERR_STREAM_NO_VALID_DATA,                   /* 无有效的码流数据 */

    DHOP_ERR_VENC_GET_PLAT_INFO_FAIL  = 0x80070000, /* 获取平台信息失败 */
    DHOP_ERR_VENC_NULL_PTR,                         /* 输入参数中有空指针 */
    DHOP_ERR_VENC_INVALID_HANDLE,                   /* 无效的编码操作句柄 */
    DHOP_ERR_VENC_INVALID_TYPE,                     /* 无效的编码类型   */
    DHOP_ERR_VENC_INVALID_SIZE,                     /* 无效的编码尺寸 */
    DHOP_ERR_VENC_INVALID_STRIDE,                   /* 无效的编码跨距 */
    DHOP_ERR_VENC_INVALID_FMT,                      /* 无效的YUV格式 */
    DHOP_ERR_VENC_INVALIDE_REGION,                  /* 无效的编码区域 */
    DHOP_ERR_VENC_BUFF_EMPTY,                       /* 编码帧队列为空 */
    DHOP_ERR_VENC_REPEATED_OPEN,                    /* 重复开启 */
    DHOP_ERR_VENC_REQUEST_RESRC_FAIL1,              /* 申请资源1失败 */
    DHOP_ERR_VENC_REQUEST_RESRC_FAIL2,              /* 申请资源2失败 */
    DHOP_ERR_VENC_RELEASE_RESRC_FAIL1,              /* 释放资源1失败 */
    DHOP_ERR_VENC_RELEASE_RESRC_FAIL2,              /* 释放资源2失败 */
    DHOP_ERR_VENC_INIT_LINK_FAIL,                   /* 初始化链接失败 */
    DHOP_ERR_VENC_DEINIT_LINK_FAIL,                 /* 去初始化链接失败 */
    DHOP_ERR_VENC_INVALID_QUALTIY,                  /* 无效的编码质量 */
    DHOP_ERR_VENC_INVALID_MODE,                     /* 无效的编码模式 */
    DHOP_ERR_VENC_INTERNAL_COMM_FAIL,               /* 内部通信失败 */
    DHOP_ERR_VENC_NOT_READY,                        /* VENC模块未就绪 */
    DHOP_ERR_VENC_RESOURCE_NOT_EXIST,               /* 编码资源不存在 */
    DHOP_ERR_VENC_NO_RESOURCE_AVAILABLE,            /* 无可用的编码资源 */
    DHOP_ERR_VENC_CLOSING_IS_BUSY,                  /* 编码数据仍有未释放*/
    DHOP_ERR_VENC_BUFF_FULL,                        /* 编码帧队列满*/
    DHOP_ERR_VENC_RELEASE_RESULT_UNEXIST,           /* 资源不存在*/
    DHOP_ERR_VENC_OSD_OUT_OF_RANGE,                 /* 文本或矩形框超出有效编码范围*/
    DHOP_ERR_VENC_OSD_OUT_OF_NUM,                   /* 文本或者框超出最大个数*/
    DHOP_ERR_VENC_OSD_RECT_NOT_ALIGN,               /* 矩形框像素未按要求对齐*/
    DHOP_ERR_VENC_OSD_TEXT_NOT_ALIGN,               /* 文本框像素未按要求对齐*/
    DHOP_ERR_VENC_OSD_NOT_SUPPORT_TYPE,             /* 叠加OSD类型无效*/
    DHOP_ERR_VENC_OSD_INVALID_INPUT,                /* 无效的OSD信息*/

    DHOP_ERR_VDEC_GET_PLAT_INFO_FAIL  = 0x80080000, /* 获取平台解码信息失败 */
    DHOP_ERR_VDEC_NULL_PTR,                         /* 输入参数中有空指针 */
    DHOP_ERR_VDEC_INVALID_HANDLE,                   /* 无效的解码操作句柄 */
    DHOP_ERR_VDEC_INVALID_TYPE,                     /* 无效的解码类型 */
    DHOP_ERR_VDEC_INVALID_SIZE,                     /* 无效的解码尺寸 */
    DHOP_ERR_VDEC_INVALID_RESULT_FMT,               /* 无效的解码结果格式 */
    DHOP_ERR_VDEC_INVALID_FILE_PATH,                /* 无效的文件路径 */
    DHOP_ERR_VDEC_READ_FILE_FAIL,                   /* 读取文件失败 */
    DHOP_ERR_VDEC_PARSE_DATA_FAIL,                  /* 数据解析失败 */
    DHOP_ERR_VDEC_INVALID_DATA_BITWIDTH,            /* 无效的数据位宽 */
    DHOP_ERR_VDEC_BUFF_NOT_ENOUGH,                  /* 解码底层内存不足 */
    DHOP_ERR_VDEC_SIZE_NOT_MATCH,                   /* 实际输入与请求尺寸不符 */
    DHOP_ERR_VDEC_INIT_LINK_FAIL,                   /* 初始化链接失败 */
    DHOP_ERR_VDEC_DEINIT_LINK_FAIL,                 /* 去初始化链接失败 */
    DHOP_ERR_VDEC_LINK_COMM_FAIL,                   /* 链接通信失败 */
    DHOP_ERR_VDEC_RESOURCE_NOT_ENOUGH,              /* 解码资源不足 */
    DHOP_ERR_VDEC_GET_RESOURCE_FAIL,                /* 获取底层解码资源失败 */
    DHOP_ERR_VDEC_INIT_RESOURCE_FAIL,               /* 初始化底层解码资源失败 */
    DHOP_ERR_VDEC_INVALID_TIMEOUT,                  /* 无效的超时参数 */
    DHOP_ERR_VDEC_STREAM_BUF_FULL,                  /* 解码缓存已满 */
    DHOP_ERR_VDEC_FRAME_BUF_EMPTY,                  /* 帧缓存已空 */
    DHOP_ERR_VDEC_INVALID_FPS,                      /* 无效的解码帧率 */

    DHOP_ERR_MODULE_RESERVED        = 0x80090000,   /* 预留错误码 */

    DHOP_ERR_OSD_xxx                = 0x800A0000,

    DHOP_ERR_PTZ_xxx                = 0x800B0000,

    DHOP_ERR_MISC_xxx               = 0x800C0000,

    DHOP_ERR_ISP_INVALID_CHNN_ID    = 0x800D0000,    /* 无效通道ID */
    DHOP_ERR_ISP_GET_PLAT_INFO_FAIL,                 /* 获取平台信息失败 */
    DHOP_ERR_ISP_REQUEST_RESRC_FAIL1,                /* 申请资源1失败 */
    DHOP_ERR_ISP_REQUEST_RESRC_FAIL2,                /* 申请资源2失败 */
    DHOP_ERR_ISP_REQUEST_RESRC_FAIL3,                /* 申请资源3失败 */
    DHOP_ERR_ISP_RELEASE_RESRC_FAIL1,                /* 释放资源1失败 */
    DHOP_ERR_ISP_RELEASE_RESRC_FAIL2,                /* 释放资源2失败 */
    DHOP_ERR_ISP_RELEASE_RESRC_FAIL3,                /* 释放资源3失败 */
    DHOP_ERR_ISP_EXCEED_CHN_CAPS,                    /* 超出通道能力 */
    DHOP_ERR_ISP_NULL_PTR,                           /* 输入参数中有空指针 */
    DHOP_ERR_ISP_INVALID_HANDLE,                     /* 无效的算法操作句柄 */
    DHOP_ERR_ISP_OPEN_COMM_FAIL,                     /* 开启通信失败 */
    DHOP_ERR_ISP_CLOSE_COMM_FAIL,                    /* 关闭通信失败 */
    DHOP_ERR_ISP_INIT_RESOURCE_FAIL,                 /* 初始化资源失败 */
    DHOP_ERR_ISP_QUERY_RESOURCE_FAIL,                /* 查询资源失败 */
    DHOP_ERR_ISP_DEINIT_RESOURCE_FAIL,               /* 注销资源失败 */
    DHOP_ERR_ISP_INNER_COMM_FAIL,                    /* 内部通信失败 */
    DHOP_ERR_ISP_MODULE_NOT_ENABLE,                  /* 模块未使能 */
    DHOP_ERR_ISP_MODULE_IS_BUSY,                     /* 模块资源忙 */
    DHOP_ERR_ISP_NO_ROI_RECT,                        /* 无感兴趣区域 */
    DHOP_ERR_ISP_INVALID_ROI_RECT,                   /* 无效感兴趣区域 */
    DHOP_ERR_ISP_NO_ROI_YUV,                         /* 无感兴趣区域YUV */
    DHOP_ERR_ISP_INVALID_ROI_YUV,                    /* 无效的感兴趣区域YUV */
    DHOP_ERR_ISP_INVALID_ROI_EXP_PARAM,              /* 无效的感兴趣区域曝光参数 */
    DHOP_ERR_ISP_INVALID_CONFIG_FILE_TYPE,           /* 无效的配置文件类型 */
    DHOP_ERR_ISP_INVALID_BRIGHTNESS,                 /* 无效的图像亮度值 */
    DHOP_ERR_ISP_INVALID_3DNR_VALUE,                 /* 无效的3D降噪值 */
    DHOP_ERR_ISP_INVALID_WDR_VALUE,                  /* 无效的宽动态值 */
    DHOP_ERR_ISP_GET_PARAM_FAIL,                     /* 参数获取失败 */
    DHOP_ERR_ISP_PARSE_PARAM_FAIL,                   /* 参数解析失败 */
    DHOP_ERR_ISP_SET_PARAM_FAIL,                     /* 参数设置失败 */
    DHOP_ERR_ISP_NOT_READY,                          /* 未初始化 */
    DHOP_ERR_ISP_GET_HANDLE_FAIL,                    /* 获取句柄失败 */
    DHOP_ERR_ISP_ROIEXP_RESOURCE_BUSY,               /* 感兴趣区域曝光资源忙 */
    DHOP_ERR_ISP_ROIEXP_ALREADY_OPEN,                /* 感兴趣区域曝光已开启 */
    DHOP_ERR_ISP_ROIEXP_ALREADY_CLOSE,               /* 感兴趣区域曝光已关闭 */
    DHOP_ERR_ISP_ROIEXP_INVALID_OPERATION,           /* 无效的感兴趣区域曝光功能操作 */

    DHOP_ERR_CFGOS_INVALID_CFG_TYPE = 0x800E0000,   /* 不可用的配置类型 */
    DHOP_ERR_CFGOS_INVALID_CFG_FMT,                 /* 不可用的配置格式 */
    DHOP_ERR_CFGOS_UNSUPPORT_CFG_TYPE,              /* 不支持的配置规则 */
    DHOP_ERR_CFGOS_INVALID_CFG_FIELD,               /* 不可用的配置字段 */
    DHOP_ERR_CFGOS_APPLY_CFG_ERROR,                 /* 应用配置失败 */
    DHOP_ERR_CFGOS_APPLY_CFG_TIMEOUT,               /* 应用配置超时 */
    DHOP_ERR_CFGOS_LENGTH_ERR,                      /* 数据长度错误*/

    DHOP_ERR_VIDEO_NULL_PTR = 0x800F0000,           /* 输入参数中有空指针 */
    DHOP_ERR_VIDEO_INVALID_HANDLE,                  /* 无效的操作句柄 */
    DHOP_ERR_VIDEO_GET_PLAT_CAP_FAIL,               /* 获取平台能力失败 */
    DHOP_ERR_VIDEO_INVALID_CHN,                     /* 无效通道ID */
    DHOP_ERR_VIDEO_INVALID_STREAM,                  /* 无效码流ID */
    DHOP_ERR_VIDEO_INVALID_RESOLUTION,              /* 无效的分辨率 */
    DHOP_ERR_VIDEO_INVALID_FPS,                     /* 无效的帧率 */
    DHOP_ERR_VIDEO_INVALID_GOP,                     /* 无效的I帧间隔 */
    DHOP_ERR_VIDEO_INVALID_BITRATE,                 /* 无效的码率 */
    DHOP_ERR_VIDEO_GET_PARAM_FAIL,                  /* 参数获取失败 */
    DHOP_ERR_VIDEO_PARSE_PARAM_FAIL,                /* 参数解析失败 */
    DHOP_ERR_VIDEO_SET_PARAM_FAIL,                  /* 参数设置失败 */

    DHOP_ERR_EQUIPMENT_NOT_EXIST = 0x80100000,      /* 设备不存在 */
    DHOP_ERR_EQUIPMENT_ALREADY_EXIST,               /* 设备已经存在 */

    DHOP_ERR_AUDIO_HANDLE_INVALID = 0x80110000,     /* 句柄非法 */
    DHOP_ERR_AUDIO_HANDLE_TYPEERR,                  /* 句柄类型非法 */
    DHOP_ERR_AUDIO_ENC_INVALID,                     /* 音频编码器不可用 */
    DHOP_ERR_AUDIO_DEC_INVALID,                     /* 音频解码器不可用 */
    DHOP_ERR_AUDIO_PKT_INVALID,                     /* 音频数据包不可用 */
    DHOP_ERR_AUDIO_MEM_INIT_FAILED,                 /* 内存初始化失败 */
    DHOP_ERR_AUDIO_MEM_ALLOC_FAILED,                /* 音频数据内存申请失败 */
    DHOP_ERR_AUDIO_MEM_NOT_RELEASE,                 /* 音频数据内存未被释放(则句柄无法关闭) */
    DHOP_ERR_AUDIO_CFG_GET_FAILED,                  /* 音频配置获取失败 */
    DHOP_ERR_AUDIO_CFG_SET_FAILED,                  /* 音频配置设置失败 */
    DHOP_ERR_AUDIO_VOL_SET_FAILED,                  /* 音量设置失败 */
    DHOP_ERR_AUDIO_MEM_RLS_FAILED,                  /* 内存释放失败 */

    DHOP_ERR_HTTP_TOKEN_INVALID = 0x80120000,       /* Token 非法 */
    DHOP_ERR_HTTP_CODE_INVALID,                     /* 状态码非法 */
    DHOP_ERR_HTTP_NOT_ONLINE,                       /* 服务未上线 */
    DHOP_ERR_HTTP_BUFFER_OUT,                       /* 缓冲区不足 */
    DHOP_ERR_HTTP_SERVICE_ERR,                      /* 响应失败 */
    DHOP_ERR_HTTP_LENGTH_ERR,                       /* 数据长度错误 */
    DHOP_ERR_HTTP_HEADER_LATER,                     /* 添加Header在Content之后 */
    DHOP_ERR_HTTP_DATA_EMPTY,                       /* 数据为空 */
    DHOP_ERR_HTTP_RESP_ERROR,                       /* 回复发送失败 */
    DHOP_ERR_HTTP_ALLOC_ERROR,                      /* 内部申请buffer失败 */
    DHOP_ERR_HTTP_HANDLE_CLOSED,                    /* 句柄已经关闭 */

    DHOP_ERR_UTILS_UNZIP_FMT_ERR = 0x80130000,      /* 压缩包格式错误 */
    DHOP_ERR_UTILS_UNZIP_INIT_ERR,                  /* 解压缩初始化失败 */
    DHOP_ERR_UTILS_UNZIP_HANDLER_INVALID,           /* 解压缩句柄非法 */
    DHOP_ERR_UTILS_UNZIP_HANDLER_BUSY,              /* 正在解压缩 */
    DHOP_ERR_UTILS_UNZIP_HANDLER_ERROR,             /* 解压缩失败 */

    DHOP_ERR_STORAGE_DEVICE_NOT_FOUND = 0x80140000, /* 设备没找到 */
    DHOP_ERR_STORAGE_DEVICE_UMOUNT,                 /* 设备未挂载 */
    DHOP_ERR_STORAGE_DEVICE_MOUNTED,                /* 设备已挂载 */
    DHOP_ERR_STORAGE_INVALID_FILE_SYSTEM_TYPE,      /* 无效的文件系统类型 */
    DHOP_ERR_STORAGE_GET_INFO_FAILED,               /* 存储设备信息获取失败 */
    DHOP_ERR_STORAGE_MOUNT_FAILED,                  /* 设备挂载失败 */
    DHOP_ERR_STORAGE_UMOUNT_FAILED,                 /* 设备卸载失败 */
    DHOP_ERR_STORAGE_FORMAT_FAILED,                 /* 设备格式化失败 */
    DHOP_ERR_STORAGE_INVALID_DEV_TYPE,              /* 无效的设备类型 */
    DHOP_ERR_STORAGE_INVALID_MEDIA_TYPE,            /* 无效的设备介质类型 */

    DHOP_ERR_EVENT_INVALID_TYPE = 0x80150000,       /* 事件类型不可用 */
    DHOP_ERR_EVENT_INVALID_SUBER,                   /* 订阅者非法 */
    DHOP_ERR_EVENT_ALLOC_FAILED,                    /* 内存资源申请失败 */
    DHOP_ERR_EVENT_LENGTH_ERR,                      /* 数据长度错误 */

    DHOP_ERR_FRAME_HANDLER_ERR = 0x80160000,        /* 处理句柄错误 */
    DHOP_ERR_FRAME_LENGTH_ERR,                      /* 数据长度错误 */
    DHOP_ERR_FRAME_ALLOC_ERR,                       /* 资源申请失败 */
    DHOP_ERR_FRAME_DATA_INVALID,                    /* 数据格式非法 */
    DHOP_ERR_FRAME_OBJ_LIMIT,                       /* 对象大小不符合限制 */
    DHOP_ERR_FRAME_ELE_LIMIT,                       /* 元素个数不符合限制 */
    DHOP_ERR_FRAME_LINE_LIMIT,                      /* 折线点不符合限制 */
    DHOP_ERR_FRAME_GON_LIMIT,                       /* 多边形点不符合限制 */
    DHOP_ERR_FRAME_TEXT_LIMIT,                      /* 文本个数不符合限制 */

    DHOP_ERR_DEVICE_LENGTH_ERR = 0x80170000,        /* 数据长度错误 */



} DHOP_ErrorCode;




#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_ERRNO_H__


