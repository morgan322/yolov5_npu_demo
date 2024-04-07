/*******************************************************************************
 * dhop_ai_img.h
 *
 * Copyright (C) 2015-2020 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: define the image data types and APIs for intelligent algorithm.
 *
 *******************************************************************************/

#ifndef __DHOP_AI_IMG_H__
#define __DHOP_AI_IMG_H__

#include "dhop_ai_com.h"

#ifdef __cplusplus
extern "C"{
#endif

// element types for the image.
#define DHOP_AI_IMG_8U   0          ///<  8-bit unsigned integer
#define DHOP_AI_IMG_8S   1          ///<  8-bit signed integer
#define DHOP_AI_IMG_16U  2          ///< 16-bit unsigned integer
#define DHOP_AI_IMG_16S  3          ///< 16-bit signed integer
#define DHOP_AI_IMG_32S  4          ///< 32-bit signed integer
#define DHOP_AI_IMG_32F  5          ///< 32-bit single precision float
#define DHOP_AI_IMG_64F  6          ///< 64-bit double precision float
#define DHOP_AI_IMG_16F  7          ///< 16-bit half precision float

/** image handle for intelligent algorithm */
typedef DH_Handle DHOP_AI_IMG_Handle;

// colorspace enumerates.
typedef enum                      
{                     
    DHOP_AI_IMG_CS_YUV420= 0,       /**< YUV420(I420), stored as YYYY...YYYY, U...U, V...V, where U and V is sub-sampled in both directions. */
    DHOP_AI_IMG_CS_Y,               /**< Gray image, only Y component stored as YYYY...YYYY. */
    DHOP_AI_IMG_CS_YUV420SP,        /**< YUV420(NV12), stored as YYYY...YYYY, UV...UV, where UV is sub-sampled in both direction. */
    DHOP_AI_IMG_CS_YUV420SP_VU,     /**< YUV420_VU(NV21), stored as YYYY...YYYY, VU...VU, where VU is sub-sampled in both direction. */
    DHOP_AI_IMG_CS_RGB,             /**< RGB24bit, stored as RGB...RGB. Each pixel is made of 3 bytes for 8U data. */
    DHOP_AI_IMG_CS_RGBP,            /**< RGB24bit-PLANAR mode, stored as RRRRRR GGGGGG BBBBBB. Every plane has the same size. */
    DHOP_AI_IMG_CS_BGR,             /**< RGB24bit, stored as BGR...BGR. Each pixel is make of 3 bytes for 8U data. */
    DHOP_AI_IMG_CS_BGRP,            /**< RGB24bit-PLANAR mode, stored as BBBBBBB GGGGGG RRRRRR. Every plane has the same size. */
    DHOP_AI_IMG_CS_NR,              /**< have no color space */

    DHOP_AI_IMG_CS_EXT_START = 100, /**< Color space extension Start. */
    DHOP_AI_IMG_CS_ARGB,            /**< packed A-RGB, stored as ARGB...ARGB. Each pixel is made of 4 bytes for 8U data. */
    DHOP_AI_IMG_CS_RGBA,            /**< packed RGB-A, stored as RGBA...RGBA. Each pixel is made of 4 bytes for 8U data. */
    DHOP_AI_IMG_CS_ABGR,            /**< packed A-BGR, stored as ABGR...ABGR. Each pixel is made of 4 bytes for 8U data. */
    DHOP_AI_IMG_CS_BGRA,            /**< packed BGR-A, stored as BGRA...BGRA. Each pixel is made of 4 bytes for 8U data. */
    DHOP_AI_IMG_CS_RGB565,          /**< packed RGB 5:6:5, 16bpp. (msb)    5R 6G 5B (lsb), 8U only. */
    DHOP_AI_IMG_CS_BGR565,          /**< packed BGR 5:6:5, 16bpp. (msb)    5B 6G 5R (lsb), 8U only. */
    DHOP_AI_IMG_CS_RGB555,          /**< packed RGB 5:5:5, 16bpp. (msb) 1A 5R 5G 5B (lsb), 8U only. */
    DHOP_AI_IMG_CS_BGR555,          /**< packed BGR 5:5:5, 16bpp. (msb) 1A 5B 5G 5R (lsb), 8U only. */
    DHOP_AI_IMG_CS_RGB444,          /**< packed RGB 4:4:4, 16bpp. (msb) 4A 4R 4G 4B (lsb), 8U only. */ 
    DHOP_AI_IMG_CS_BGR444,          /**< packed BGR 4:4:4, 16bpp. (msb) 4A 4B 4G 4R (lsb), 8U only. */
	DHOP_AI_IMG_CS_YUYV422,     	/**< packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr  */
    DHOP_AI_IMG_CS_YUV444P,         /**< planar YUV 4:4:4, 24bpp, (1 Cr & Cb sample per 1x1 Y samples) */
    DHOP_AI_IMG_CS_YUV422P,         /**< planar YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples) */
    DHOP_AI_IMG_CS_YUV440P,         /**< planar YUV 4:4:0, 16bpp, (1 Cr & Cb sample per 1x2 Y samples) */
    DHOP_AI_IMG_CS_YUV411P,         /**< planar YUV 4:1:1, 12bpp, (1 Cr & Cb sample per 4x1 Y samples) */
    DHOP_AI_IMG_CS_GBRP,            /**< planar GBR 4:4:4 24bpp */
    DHOP_AI_IMG_CS_GBRAP,           /**< planar GBRA 4:4:4:4 32bpp */
    DHOP_AI_IMG_CS_EXT_END
}DHOP_AI_IMG_ColorSpace;

/**
 * @brief create the image handle.
 *
 * @param [out] image       store the image handle when creation is successful.
 * @param [in]  width       the width of the image
 * @param [in]  height      the height of the image
 * @param [in]  cs          the colorspace of the image
 * @param [in]  type        data type of the image, i.e., @ref DHOP_AI_IMG_8U.
 * @param [in]  ptrs        external memory addresses for CPU/software/host access, one for each plane. 
 *                          Set to DH_NULL if no external memory is supplied. 
 * @param [in]  ptrs_HW     external memory addresses for GPU/hardware/device access, one for each plane.
 *                          Set to DH_NULL if no external memory is supplied.
 * @param [in]  strides     strides of the planes, measured in bytes, one for each plane.
 *                          Set to DH_NULL means the continuous mode.
 * @param [in]  planes      specify the number of planes used by the image. It must be a valid value with the colorspace.
 *                          Set to 0 if the default value for the specified colorspace is used.
 *
 * @return                  DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_IMG_create(DHOP_AI_IMG_Handle * image, DH_Int32 width, DH_Int32 height, 
        DHOP_AI_IMG_ColorSpace cs, DH_Int32 type, DH_Ptr * ptrs, DH_Ptr * ptrs_HW, DH_Int32 * strides, DH_Int32 planes);

/**
 * @brief destroy the image handle and all allocated resources.
 *
 * @param [in]  image       the image handle
 *
 * @return                  DHOP_SUCCESS for success, otherwise failed.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_IMG_destroy(DHOP_AI_IMG_Handle image);

/**
 * @brief check whether the image handle is valid or not.
 *
 * @param [in]  image       the image handle
 *
 * @return                  DH_TRUE if it is a valid image handle; 
 *                          DH_FALSE if it is not a valid image handle.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_IMG_isValid(DHOP_AI_IMG_Handle image);

/**
 * @brief get the data type of the image.
 *
 * @param [in]  image       the image handle.
 *
 * @return                  the data type of the image, i.e. @ref DHOP_AI_IMG_8U, < 0 means a failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_type(DHOP_AI_IMG_Handle image);

/**
 * @brief get the size of the data element of the image.
 *
 * @param [in]  image       the image handle.
 *
 * @return                  the element size, measured in bytes. < 0 means a failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_elementSize(DHOP_AI_IMG_Handle image);

/**
 * @brief get the width of the image.
 *
 * @param [in]  image       the image handle
 *
 * @return                  the width of the image. < 0 means a failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_width(DHOP_AI_IMG_Handle image);

/**
 * @brief get the height of the image.
 *
 * @param [in]  image       the image handle.
 *
 * @return                  the height of the image. < 0 means a failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_height(DHOP_AI_IMG_Handle image);

/**
 * @brief get the colorspace of the image.
 *
 * @param [in]  image       the image handle
 *
 * @return                  the colorspace of the image, see @ref DHOP_AI_IMG_ColorSpace. < 0 means a failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_colorSpace(DHOP_AI_IMG_Handle image);

/**
 * @brief get the number of planes in the image.
 *
 * @param [in]  image       the image handle
 *
 * @return                  number of planes in the image. < 0 means a failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_planeNumber(DHOP_AI_IMG_Handle image);

/**
 * @brief get the information of the planes in the image.
 *
 * @param [in]  image       the image handle
 * @param [out] ptrs        pointers for CPU/software/host access, one for each plane. 
 *                          Set to DH_NULL if these addresses are not required.
 * @param [out] ptrs_HW     pointers for GPU/hardware/device access, one for each plane.
 *                          Set to DH_NULL if these addresses are not required.
 * @param [out] strides     strides measured in bytes, one for each plane.
 *                          Set to DH_NULL if the stride information is not required.
 *
 * @return                  DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_IMG_planeInfo(DHOP_AI_IMG_Handle image, DH_Ptr * ptrs, DH_Ptr * ptrs_HW, DH_Int32 * strides);

/**
 * @brief make a declaration of read operation in the image from CPU/software/host.
 *
 * @param [in]  image       the image handle
 *
 * @return                  DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_read(DHOP_AI_IMG_Handle image);

/**
 * @brief make a declaration of write operation in the image from CPU/software/host.
 *
 * @param [in]  image       the image handle.
 *
 * @return                  DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_write(DHOP_AI_IMG_Handle image);

/**
 * @brief make a declaration of read and/or write operation in the image from CPU/software/host.
 *
 * @param [in]  image       the image handle
 *
 * @return                  DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_readWrite(DHOP_AI_IMG_Handle image);

/**
 * @brief make a declaration of read operation in the image from GPU/hardware/device
 *
 * @param [in]  image       the image handle
 *
 * @return                  DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_readHW(DHOP_AI_IMG_Handle image);

/**
 * @brief make a declaration of write operation in the image from GPU/hardware/device
 *
 * @param [in]  image       the image handle
 *
 * @return                  DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_writeHW(DHOP_AI_IMG_Handle image);

/**
 * @brief make a declaration of read and/or write operation in the image from GPU/hardware/device
 * 
 * @param [in]  image       the image handle
 *
 * @return                  DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_readWriteHW(DHOP_AI_IMG_Handle image);

/**
 * @brief set the ROI(region of interest) for the image.
 *
 * @param [in]  image       the image handle
 * @param [in]  rect        rectangle information of the ROI.
 *
 * @return                  DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_setROI(DHOP_AI_IMG_Handle image, DHOP_AI_Rect * rect);

/**
 * @brief get the ROI(region of interest) from the image.
 *
 * @param [in]  image       the image handle
 * @param [out] rect        rectangle information of the ROI. It is invalid on failure.
 *
 * @return                  DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_getROI(DHOP_AI_IMG_Handle image, DHOP_AI_Rect * rect);

/**
 * @brief set the user-defined data for the image.
 *
 * @param [in] image         the image handle
 * @param [in] user_data     the user-defined data.
 *
 * @return                   DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_setUserData(DHOP_AI_IMG_Handle image, DH_Ptr user_data);

/**
 * @brief get the user-defined data from the image.
 *
 * @param [in] image         the image handle
 * 
 * @return                   the user-defined data. DH_NULL is returned if there is no user-defined data or failure has occurred.
 */
DHOP_AI_API
DH_Ptr DHOP_AI_IMG_getUserData(DHOP_AI_IMG_Handle image);

/**
 * @brief get the user-defined data from the image.
 *
 * @param [in] image         the image handle
 * 
 * @return                   the user-defined data. DH_NULL is returned if there is no user-defined data or failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_IMG_matrixNumber(DHOP_AI_IMG_Handle image);

/**
 * @brief Get the Matrix number of the Image
 *
 * @param [in] image         the image handle
 *
 * @return                   DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DHOP_AI_IMG_Handle DHOP_AI_IMG_getMatrix(DHOP_AI_IMG_Handle image, DH_Int32 index);



#ifdef __cplusplus
}
#endif

#endif
