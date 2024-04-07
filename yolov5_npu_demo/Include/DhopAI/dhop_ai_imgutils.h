/*******************************************************************************
 * dhop_ai_img.h
 *
 * Copyright (C) 2015-2020 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: Auxiliary operation functions for the image and matrix of the test demo
 *
 *******************************************************************************/

#ifndef __DHOP_AI_IMGUTILS_H__
#define __DHOP_AI_IMGUTILS_H__

#include "dhop_ai_img.h"

#ifdef __cplusplus
extern "C"{
#endif

/**< picture file type */
typedef enum
{
    DHOP_AI_IMGUTILS_FILE_TYPE_RAW,        /**< yuv/rgb raw data*/
    DHOP_AI_IMGUTILS_FILE_TYPE_JPG,        /**< jpg format picture */
    DHOP_AI_IMGUTILS_FILE_TYPE_NUM
}DHOP_AI_IMGUTILS_FileType;

/**
 * @brief create image from file.
 *
 * @param [out] image       image handle, need to use DHOP_AI_ImageUtils_Destroy to destroy after creation.
 * @param [in] filename     file name used to read the image.
 * @param [in] cs           color space.
 *
 * @return 0:sucess  other:fail.
 */  
DHOP_AI_API 
DH_Int32 DHOP_AI_IMGUTILS_createFromFile(DHOP_AI_IMG_Handle * image, const DH_Char * filename, DHOP_AI_IMG_ColorSpace cs);

/**
 * @brief save image to file
 *
 * @param [in] image     image handle
 * @param [in] prefix    filename prefix, the complete filename will be determined by the filename prefix and file type.
 * @param [in] filetype  file type¦‚ \ref DHOP_AI_IMGUTILS_FileType.
 *
 * @return 0:sucess  other:fail.
 */  
DHOP_AI_API 
DH_Int32 DHOP_AI_IMGUTILS_save(DHOP_AI_IMG_Handle image, const DH_Char * prefix, DH_Int32 filetype);

/**
 * @brief destory image
 *
 * @param [in] image     image handle
 *
 * @return 0:sucess  other:fail.
 */  
DHOP_AI_API 
DH_Int32 DHOP_AI_IMGUTILS_destroy(DHOP_AI_IMG_Handle image);

#ifdef __cplusplus
}
#endif

#endif
