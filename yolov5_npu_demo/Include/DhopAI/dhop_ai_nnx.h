/*******************************************************************************
 * dhop_ai_nnx.h
 *
 * Copyright (C) 2015-2020 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: define inference engine data types and APIs for intelligent algorithm.
 *
 *******************************************************************************/
#ifndef __DHOP_AI_NNX_H__
#define __DHOP_AI_NNX_H__

#include "dhop_ai_img.h"
#include "dhop_ai_mat.h"

#ifdef __cplusplus
extern "C"{
#endif

///< node parameter type
typedef enum
{
    DHOP_AI_NNX_PARAM_TYPE_STRING = 0,          ///< string
    DHOP_AI_NNX_PARAM_TYPE_FLOAT  = 1,          ///< float
    DHOP_AI_NNX_PARAM_TYPE_INT    = 2,          ///< int
    DHOP_AI_NNX_PARAM_TYPE_ARRAY_FLOAT  = 3,    ///< float array
    DHOP_AI_NNX_PARAM_TYPE_ARRAY_INT    = 4,    ///< int array
    DHOP_AI_NNX_PARAM_TYPE_ARRAY_STRING = 5,    ///< string array
    DHOP_AI_NNX_PARAM_TYPE_MAX                  ///< invalid type
}DHOP_AI_NNX_ParamType;

///< coordinate frame align mode
typedef enum 
{
    DHOP_AI_NNX_ALIGN_MODE_UPPERLEFT    = 0,    ///< x coordinate moves left and y coordinate moves up align
    DHOP_AI_NNX_ALIGN_MODE_LOWERRIGHT   = 1,    ///< x coordinate moves right and y coordinate moves down align
    DHOP_AI_NNX_ALIGN_MODE_INWARDS      = 2,    ///< inwards align
    DHOP_AI_NNX_ALIGN_MODE_OUTWARDS     = 3,    ///< outwards align
    DHOP_AI_NNX_ALIGN_MODE_INVALID
}DHOP_AI_NNX_AlignMode;

///< scale mode
typedef enum
{
    DHOP_AI_NNX_RESIZE_FULL_SCALE              = 0,  ///< full image scale */
    DHOP_AI_NNX_RESIZE_FIXED_SCALE_OF_CENTER   = 1,  ///< image keeps the original aspect ratio scale, align center, and the free part is filled with the color of fill_color */
    DHOP_AI_NNX_RESIZE_FIXED_SCALE_OF_BOTTOM   = 2,  ///< image keeps the original aspect ratio scale£¬align bottom, center left and right */
    DHOP_AI_NNX_RESIZE_FIXED_SCALE_OF_TOP      = 3,  ///< image keeps the original aspect ratio scale£¬align top, align left */
    DHOP_AI_NNX_RESIZE_SCALE_NR
}DHOP_AI_NNX_ScaleMode;

///< engine output type
typedef enum 
{
    DHOP_AI_NNX_RESULT_TYPE_INFER = 0,          ///< infer node output, W-dim data structure is the basic data type, eg:DH_Float32 DH_Int8
    DHOP_AI_NNX_RESULT_TYPE_YOLO  = 1,          ///< yolo postproc node output, W-dim data structure is DHOP_AI_NNX_ResultYolo
    DHOP_AI_NNX_RESULT_TYPE_TOPN  = 2,          ///< topN postproc node output, W-dim data structure is DHOP_AI_NNX_ResultTopN
    DHOP_AI_NNX_RESULT_TYPE_MAX
}DHOP_AI_NNX_ResultType;

///< node command 
typedef enum
{
    ///< only yolo postproc node is valid
    DHOP_AI_NNX_CMD_YOLO_SET_RECTIFY_PARAMS   = 0x0,        ///< set yolo detect frame rectify params, \ref DHOP_AI_NNX_YoloRectify_Params
    DHOP_AI_NNX_CMD_YOLO_GET_DET_PARAMS       = 0x1,        ///< get yolo detect param, \ref DHOP_AI_NNX_YoloDet_Params
    DHOP_AI_NNX_CMD_YOLO_UPDATE_THRESH        = 0x2,        ///< update class conf thresh, \ref DHOP_AI_NNX_Thresh_Params
    DHOP_AI_NNX_CMD_UPDATE_MAX_DET_NUM        = 0x3,        ///< update the max number of detect, it will affect the output matrix memory,need to get the output matrix again. \ref DH_Uint32
    
    ///< only preproc node is valid
    DHOP_AI_NNX_CMD_PREPROC_ALIGN_RECT        = 0x103,      ///< according to the needs of the network, align the region of interest ,\ref DHOP_AI_NNX_AlignRect_Params
    
    ///< only inference node is valid
    DHOP_AI_NNX_CMD_INFER_GET_NET_RESO        = 0x200,      ///< get network width and height, \ref DHOP_AI_NNX_Resolution
    DHOP_AI_NNX_CMD_INFER_GET_INPUT_CS        = 0x201,      ///< get network input color space, \ref DHOP_AI_IMG_ColorSpace
    DHOP_AI_NNX_CMD_INFER_GET_CUDA_STREAM     = 0x203,      ///< get the cuda stream being used, only applies to TensorRT , \ref DH_Ptr
    DHOP_AI_NNX_CMD_INFER_SET_CUDA_STREAM     = 0x204,      ///< set the cuda stream being used, only applies to TensorRT , \ref DH_Ptr

    ///< common order
    DHOP_AI_NNX_CMD_SET_NET_RESO                = 0xFFFF1001, ///< set network input width and height, \ref DHOP_AI_NNX_Resolution
    
    DHOP_AI_NNX_CMD_MAX_NUM
} DHOP_AI_NNX_Cmd;

///< version information
typedef struct
{
    DH_Int32            byte_size;
    DH_Int32            res;                    
    DH_Char           * version;                        ///< version string, memory is maintained internally */
    DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(version)
    DH_Int32    reserved[12];
}DHOP_AI_NNX_Version;

typedef struct
{
    DH_Uint16 width;
    DH_Uint16 height;
}DHOP_AI_NNX_Resolution;

///< align command parameter structure
typedef struct
{
    DH_Int32    num;                                ///< The number of areas that need to be aligned. corresponding image\pRectIn\pRectOutis array
    DHOP_AI_NNX_AlignMode   align_mode;             ///< align mode
    DHOP_AI_IMG_Handle*     image;                  ///< image source data of the roi area to be processed.
    DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(image)
    DHOP_AI_Rect*           pRectIn;                ///< roi area to be processed
    DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(pRectIn)
    DHOP_AI_Rect*           pRectOut;               ///< roi area after alignment£¬the pointer can be the same as pRectIn,but the content will be overwritten
    DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(pRectOut)
    DH_Uint32           reserved[8];
}DHOP_AI_NNX_AlignRect_Params;


///< yolo node detection frame rectify param
typedef struct
{
    DH_Uint32 imgNum;                               ///< if batch image size is different, then imgNum is the number of pictures, Otherwise imgNum equl 1 express all pictures have the same size
    DH_Uint32 fix_mode;                             ///< fixed scaling mode, \ref DHOP_AI_NNX_ScaleMode
    DHOP_AI_IMG_Handle *pImage;                     ///< input image , include image width height and ROI
    DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(pImage)
    DH_Uint32 reserved[12];
}DHOP_AI_NNX_YoloRectify_Params;

///< yolo node detection parameters
typedef struct
{
    DH_Uint32   layerNum;                           ///< CNN network detection layer number
    DH_Uint32   maxObjectNum;                       ///< max number of object
    DH_Uint32   coords;                             ///< number of coordinate
    DH_Uint32   classNum;                           ///< Number of class
    DH_Float32  *thresh;                            ///< confidence threshold of each class, dhop_nnx provid pointer memory, and the content pointer must not be modified externally
    DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(thresh)
    DH_Uint32   *numAnchors;                        ///< The number of anchors per layer. eg: 3-layer is 3,5,1; respectively, numAnchors[]={3,5,1}
    DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(numAnchors)
    DH_Float32  *anchors;                           ///< anchor value, fill in the order of layer, dhop_nnx provid pointer memory, and the content pointer must not be modified externally
	DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(anchors)
    DH_Uint32   reserved[6];
}DHOP_AI_NNX_YoloDet_Params;


///< yolo update class conf thresh structure
typedef struct
{
    DH_Uint32   classNum;                           ///< class number, must be the same as the actual number of class
    DH_Uint32   reserved1[1];
    DH_Float32  *thresh;                            ///< conf thresh for each class
    DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(thresh)
    DH_Uint32   reserved[4];
}DHOP_AI_NNX_Thresh_Params;

    
///< constant node inform structure
typedef struct
{
    DHOP_AI_NNX_ParamType type;             ///< Type of param
    DH_Int32    size;                       ///< number of values
    union{
        DH_Float32 f;                       ///< type: DHOP_AI_NNX_PARAM_TYPE_FLOAT
        DH_Int32   a;                       ///< type: DHOP_AI_NNX_PARAM_TYPE_INT
        DH_String  s;                       ///< type: DHOP_AI_NNX_PARAM_TYPE_STRING
        DH_Void*   array;                   ///< type: DHOP_AI_NNX_PARAM_TYPE_FLOAT/DHOP_AI_NNX_PARAM_TYPE_INT; array first address
        DH_String* array_str;               ///< type: DHOP_AI_NNX_PARAM_TYPE_ARRAY_STRING
        DH_Uint8   unused[8];
    }value; 
    DH_Int32 reserved[8];
}DHOP_AI_NNX_ConstantInfo;

///< yolo detection frame result
typedef struct
{
    DH_Float32 x, y;                        ///< Center point coord
    DH_Float32 w, h;                        ///< target width and height
    DH_Float32 prob;                        ///< conf
    DH_Int32 classIdx;
    DH_Int32 batchIdx;
    DH_Int32 layerId;
    DH_Int32 cellId;                        ///< equals to (w_stride * cell_y + cell_x).
    DH_Int32 anchorId;
    DH_Int32 reserved[9];
}DHOP_AI_NNX_ResultYolo;

///< topN result
typedef struct
{
    DH_Int32   batchIdx;                    ///< batch index value
    DH_Int32   splitIdx;                    ///< split index value
    DH_Int32   index;                       ///< Corresponding to the index value of topN output data
    DH_Float32   value;                     ///< Corresponding to the value of topN output data, arrange the same batch/spilitIdx item from high to low
    DH_Int32   reserved[12];
} DHOP_AI_NNX_ResultTopN;

typedef DH_Handle DHOP_AI_NNX_Handle;


/**
 * @brief get engine version
 *
 * @param [out]  pVersion    return version inform
 *
 * @return                  0:sucess  other:fail.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_NNX_getVersion(DHOP_AI_NNX_Version* pVersion);

/**
 * @brief create engine
 *
 * @param [out] hNNX        engine handle pointer
 * @param [in]  model_file  model file, suffix .nnx
 * @param [in]  en_key      encryp key, which is generated when the nnx generates
 *
 * @return                  0:sucess  other:fail.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_NNX_create(DHOP_AI_NNX_Handle* hNNX, const DH_String model_file, const DH_String en_key);


/**
 * @brief destory handle
 *
 * @param [in] hNNX         NNX handle
 *
 * @return                  0:sucess  other:fail.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_NNX_destroy(DHOP_AI_NNX_Handle hNNX);


/**
 * @brief get the max input batch
 *
 * @param [in] hNNX         NNX handle
 *
 * @return                  > 0:sucess  other:fail.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_NNX_getMaxBatchSize(DHOP_AI_NNX_Handle hNNX);


/**
 * @brief set input image
 *
 * @param [in] hNNX         NNX handle
 * @param [in] blob_name    input node blob name
 * @param [in] image        image handle array
 * @param [in] batch        image number
 
 * @return                  0:sucess  other:fail.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_NNX_setInputImg(DHOP_AI_NNX_Handle hNNX, const DH_String blob_name, DHOP_AI_IMG_Handle *image, DH_Int32 batch);


/**
 * @brief get input data pointer
 *
 * @param [in] hNNX         NNX handle
 * @param [in] blob_name    inference node input blob name
 * @param [out] pInput      store input mat handle
 
 * @return                  0:sucess  other:fail.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_NNX_getInput(DHOP_AI_NNX_Handle hNNX, const DH_String blob_name, DHOP_AI_MAT_Handle *pInput);

/**
 * @brief run engine
 *
 * @param [in] hNNX         NNX handle
 *
 * @return                  0:sucess  other:fail.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_NNX_run(DHOP_AI_NNX_Handle hNNX);


/**
 * @brief get result
 *
 * @param [in]  hNNX        NNX handle
 * @param [in]  blob_name   output blob name
 * @param [out] type        output type \ref DHOP_AI_NNX_ResultType
 * @param [out] mat         result pointer
 *
 * @return                  0:sucess  other:fail.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_NNX_getResult(DHOP_AI_NNX_Handle hNNX, const DH_String blob_name, DH_Uint32* type, DHOP_AI_MAT_Handle *mat);


/**
 * @brief get input blob number
 *
 * @param [in]  hNNX        NNX handle
 * @param [out] inputNames  array of pointers to store the name of the input blob, the size is num (the memory of the pointer array is provided by the caller); 
 *							if NULL,it means just get the actual num
 * @param [in&out] num      number of members of the pointer array when input, the output is the actual number of input blobs obtained
 *
 * @return                  0:sucess  other:fail.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_NNX_getInputBlobNames(DHOP_AI_NNX_Handle hNNX, DH_String inputNames[], DH_Uint32* num);


/**
 * @brief get output blob number
 *
 * @param [in]  hNNX        NNX handle
 * @param [out] inputNames  array of pointers to store the name of the output blob, the size is num (the memory of the pointer array is provided by the caller); 
 *							if NULL,it means just get the actual num
 * @param [in&out] num      number of members of the pointer array when input, the output is the actual number of input blobs obtained
 *
 * @return                  0:sucess  other:fail.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_NNX_getOutputBlobNames(DHOP_AI_NNX_Handle hNNX, DH_String outputNames[], DH_Uint32* num);


/**
 * @brief get constant node parameters
 *
 * @param [in]  hNNX        NNX handle
 * @param [in]  nodeName    node name
 * @param [in]  key         the path of the param¡£eg£º ¡°/test_yyy/0¡±, If it is an array£¬can use 0, 1, 2 to access. otherwise, it will return the array type
 * @param[inout] value      get the value
 *
 * @return                  0:sucess  other:fail.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_NNX_getNodeParam(DHOP_AI_NNX_Handle hNNX, const DH_String nodeName, const DH_String key, DHOP_AI_NNX_ConstantInfo* value);


/**
 * @brief get/set node operating parameters
 *
 * @param [in]  hNNX        NNX handle
 * @param [in]  node_name   node name
 * @param [in]  cmd         Command field, \ref DHOP_AI_NNX_Cmd
 * @param [in]  param       
 *
 * @return                  0:sucess  other:fail.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_NNX_control(DHOP_AI_NNX_Handle hNNX, const DH_String node_name, DH_Int32 cmd, DH_Void* param);

#ifdef __cplusplus
}
#endif

#endif