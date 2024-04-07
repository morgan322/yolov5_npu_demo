/*******************************************************************************
 * dhop_ai_mat.h
 *
 * Copyright (C) 2015-2020 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: define the matrix data types and APIs for intelligent algorithm.
 *
 *******************************************************************************/

#ifndef __DHOP_AI_MAT_H__
#define __DHOP_AI_MAT_H__

#include "dhop_ai_com.h"

#ifdef __cplusplus
extern "C"{
#endif

// element base types for the matrix.
#define DHOP_AI_MAT_8U   0          ///<  8-bit unsigned integer
#define DHOP_AI_MAT_8S   1          ///<  8-bit signed integer
#define DHOP_AI_MAT_16U  2          ///< 16-bit unsigned integer
#define DHOP_AI_MAT_16S  3          ///< 16-bit signed integer
#define DHOP_AI_MAT_32S  4          ///< 32-bit signed integer
#define DHOP_AI_MAT_32F  5          ///< 32-bit single precision float
#define DHOP_AI_MAT_64F  6          ///< 64-bit double precision float
#define DHOP_AI_MAT_16F  7          ///< 16-bit half precision float

#define DHOP_AI_MAT_TYPE_BASE_BITS    (4)
#define DHOP_AI_MAT_TYPE_CN_BITS      (8)   // channel number, 1 to 256, unsigned char + 1.
#define DHOP_AI_MAT_TYPE_QVAL_BITS    (8)   // -128 to 127, signed char, for integer data type.

#define DHOP_AI_MAT_TYPE_MASK         ((1 << DHOP_AI_MAT_TYPE_BASE_BITS) - 1)
#define DHOP_AI_MAT_TYPE_CN_MASK      ((1 << DHOP_AI_MAT_TYPE_CN_BITS) - 1)
#define DHOP_AI_MAT_TYPE_QVAL_MASK    ((1 << DHOP_AI_MAT_TYPE_QVAL_BITS) - 1)

#define DHOP_AI_MAT_CN_SHIFT          (DHOP_AI_MAT_TYPE_BASE_BITS)
#define DHOP_AI_MAT_QVAL_SHIFT        ((DHOP_AI_MAT_TYPE_BASE_BITS) + (DHOP_AI_MAT_TYPE_CN_BITS))
#define DHOP_AI_MAT_MAKETYPE(t, cn)   (((t)&DHOP_AI_MAT_TYPE_MASK) + (((cn) - 1) << DHOP_AI_MAT_CN_SHIFT))
/**
 * @brief get the combined data type with a quantized value. 
 * @param [in] t    data type without quantized value, including base type and channel number.
 * @param [in] q    quantized value(right shift number), number of bits of the fractional part.
 * @return          the combined data type
 */
#define DHOP_AI_MAT_QUANT_TYPE(t, q)  ((t) + (((q) & (DHOP_AI_MAT_TYPE_QVAL_MASK)) << (DHOP_AI_MAT_QVAL_SHIFT)))

/**
 * @brief get the base data type from the combined data type.
 * @param [in] t    the combined data type
 * @return          the base data type
 */
#define DHOP_AI_MAT_TYPE_BASE(t)      ((t) & (DHOP_AI_MAT_TYPE_MASK))
/**
 * @brief get the channel number from the combined data type.
 * @param [in] t    the combined data type
 * @return          channel number from the data type, from 1 to 256.
 */
#define DHOP_AI_MAT_TYPE_CHANNEL(t)   ((((t) >> (DHOP_AI_MAT_CN_SHIFT)) & (DHOP_AI_MAT_TYPE_CN_MASK)) + 1)
/**
 * @brief get the quantized value from the combined data type.
 * @param [in] t    the combined data type
 * @return          quantized value from the data type, from -128 to 127.
 */
#define DHOP_AI_MAT_TYPE_QVAL(t)      ((signed char)(((t) >> (DHOP_AI_MAT_QVAL_SHIFT)) & (DHOP_AI_MAT_TYPE_QVAL_MASK)))

#define DHOP_AI_MAT_8UC1       DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_8U, 1)  ///< single-channel 8-bit unsigned integer data type
#define DHOP_AI_MAT_8UC2       DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_8U, 2)  ///< double-channel 8-bit unsigned integer data type
#define DHOP_AI_MAT_8UC3       DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_8U, 3)  ///< triple-channel 8-bit unsigned integer data type
#define DHOP_AI_MAT_8UC4       DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_8U, 4)  ///< quadruple-channel 8-bit unsigned integer data type
#define DHOP_AI_MAT_8UC(n)     DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_8U, n)  ///< multi-channel, 8-bit unsigned integer data type   

#define DHOP_AI_MAT_8SC1       DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_8S, 1)  ///< single-channel 8-bit signed integer data type
#define DHOP_AI_MAT_8SC2       DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_8S, 2)  ///< double-channel 8-bit signed integer data type
#define DHOP_AI_MAT_8SC3       DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_8S, 3)  ///< triple-channel 8-bit signed integer data type
#define DHOP_AI_MAT_8SC4       DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_8S, 4)  ///< quadruple-channel 8-bit signed integer data type
#define DHOP_AI_MAT_8SC(n)     DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_8S, n)  ///< multi-channel, 8-bit signed integer data type   

#define DHOP_AI_MAT_16UC1      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16U, 1)  ///< single-channel 16-bit unsigned integer data type
#define DHOP_AI_MAT_16UC2      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16U, 2)  ///< double-channel 16-bit unsigned integer data type
#define DHOP_AI_MAT_16UC3      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16U, 3)  ///< triple-channel 16-bit unsigned integer data type
#define DHOP_AI_MAT_16UC4      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16U, 4)  ///< quadruple-channel 16-bit unsigned integer data type
#define DHOP_AI_MAT_16UC(n)    DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16U, n)  ///< multi-channel, 16-bit unsigned integer data type   

#define DHOP_AI_MAT_16SC1      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16S, 1)  ///< single-channel 16-bit signed integer data type
#define DHOP_AI_MAT_16SC2      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16S, 2)  ///< double-channel 16-bit signed integer data type
#define DHOP_AI_MAT_16SC3      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16S, 3)  ///< triple-channel 16-bit signed integer data type
#define DHOP_AI_MAT_16SC4      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16S, 4)  ///< quadruple-channel 16-bit signed integer data type
#define DHOP_AI_MAT_16SC(n)    DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16S, n)  ///< multi-channel, 16-bit signed integer data type   

#define DHOP_AI_MAT_32SC1      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_32S, 1)  ///< single-channel 32-bit signed integer data type
#define DHOP_AI_MAT_32SC2      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_32S, 2)  ///< double-channel 32-bit signed integer data type
#define DHOP_AI_MAT_32SC3      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_32S, 3)  ///< triple-channel 32-bit signed integer data type
#define DHOP_AI_MAT_32SC4      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_32S, 4)  ///< quadruple-channel 32-bit signed integer data type
#define DHOP_AI_MAT_32SC(n)    DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_32S, n)  ///< multi-channel, 32-bit signed integer data type   

#define DHOP_AI_MAT_32FC1      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_32F, 1)  ///< single-channel 32-bit float data type
#define DHOP_AI_MAT_32FC2      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_32F, 2)  ///< double-channel 32-bit float data type
#define DHOP_AI_MAT_32FC3      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_32F, 3)  ///< triple-channel 32-bit float data type
#define DHOP_AI_MAT_32FC4      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_32F, 4)  ///< quadruple-channel 32-bit float data type
#define DHOP_AI_MAT_32FC(n)    DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_32F, n)  ///< multi-channel, 32-bit float data type   

#define DHOP_AI_MAT_64FC1      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_64F, 1)  ///< single-channel 64-bit float data type
#define DHOP_AI_MAT_64FC2      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_64F, 2)  ///< double-channel 64-bit float data type
#define DHOP_AI_MAT_64FC3      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_64F, 3)  ///< triple-channel 64-bit float data type
#define DHOP_AI_MAT_64FC4      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_64F, 4)  ///< quadruple-channel 64-bit float data type
#define DHOP_AI_MAT_64FC(n)    DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_64F, n)  ///< multi-channel, 64-bit float data type   

#define DHOP_AI_MAT_16FC1      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16F, 1)  ///< single-channel 16-bit float data type
#define DHOP_AI_MAT_16FC2      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16F, 2)  ///< double-channel 16-bit float data type
#define DHOP_AI_MAT_16FC3      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16F, 3)  ///< triple-channel 16-bit float data type
#define DHOP_AI_MAT_16FC4      DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16F, 4)  ///< quadruple-channel 16-bit float data type
#define DHOP_AI_MAT_16FC(n)    DHOP_AI_MAT_MAKETYPE(DHOP_AI_MAT_16F, n)  ///< multi-channel, 16-bit float data type   

/// 32-bit signed integer data type, 12 bits quantized, for Hisi NNIE etc.
#define DHOP_AI_MAT_32S_Q12    DHOP_AI_MAT_QUANT_TYPE(DHOP_AI_MAT_32S, 12)      

/** matrix handle for intelligent algorithm */
typedef DH_Handle DHOP_AI_MAT_Handle;

/**
 * @brief create matrix handle for two-dimensional array.
 *
 * @param [out] matrix      store the matrix handle when creation is successful.
 * @param [in]  rows        rows of the matrix.
 * @param [in]  cols        columns of the matrix.
 * @param [in]  step        row stride of the matrix, measured in bytes. 0 means default(continuous storage)
 * @param [in]  type        data type of the matrix, i.e. @ref DHOP_AI_MAT_8U.
 * @param [in]  ptr         external memory address for CPU//SW/host access, set DH_NULL if not supplied.
 * @param [in]  ptr_HW      external memory address pointer for GPU/HW/device access, set DH_NULL if not supplied.
 *
 * @return                  DHOP_SUCCESS for success, otherwise failed.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_MAT_create(DHOP_AI_MAT_Handle * matrix, DH_Int32 rows, DH_Int32 cols, DH_Int32 step, DH_Int32 type, DH_Ptr ptr, DH_Ptr ptr_HW);

/**
 * @brief create matrix handle for n-dimensional array. 
 *
 * @param [out] matrix      store the matrix handle when creation is successful.
 * @param [in]  ndims       dimension of the matrix.
 * @param [in]  sizes       size of the matrix in each dimension(major first, minor last).
 * @param [in]  steps       stride of the matrix in each dimensional(major first, minor last), measured in bytes. Set to DH_NULL means continuous storage.
 * @param [in]  type        data type of the matrix, i.e. @ref DHOP_AI_MAT_8U.
 * @param [in]  ptr         external memory address for CPU/SW/host access, set DH_NULL if not supplied.
 * @param [in]  ptr_HW      external memory address pointer for GPU/HW/device access, set DH_NULL if not supplied.
 *
 * @return                  DHOP_SUCCESS for success, otherwise failed.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_MAT_create2(DHOP_AI_MAT_Handle * matrix, DH_Int32 ndims, const DH_Int32 * sizes, const DH_Int32 * steps, DH_Int32 type, DH_Ptr ptr, DH_Ptr ptr_HW);

/**
 * @brief create matrix handle with smart decision for two-dimensional matrix.
 *
 * If the matrix points to a valid matrix handle, it will reuse this handle.
 * The parameters and return value are almost same as the function @ref DHOP_AI_MAT_create.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_MAT_smartCreate(DHOP_AI_MAT_Handle * matrix, DH_Int32 rows, DH_Int32 cols, DH_Int32 step, DH_Int32 type, DH_Ptr ptr, DH_Ptr ptr_HW);

/**
 * @brief create matrix handle with smart decision for two-dimensional matrix.
 *
 * If the matrix points to a valid matrix handle, it will reuse this handle.
 * The parameters and return value are almost same as the function @ref DHOP_AI_MAT_create2.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_MAT_smartCreate2(DHOP_AI_MAT_Handle * matrix, DH_Int32 ndims, const DH_Int32 * sizes, const DH_Int32 * steps, DH_Int32 type, DH_Ptr ptr, DH_Ptr ptr_HW);

/**
 * @brief destroy the matrix handle and all allocated resources.
 *
 * @param [in]  matrix       the matrix handle to destroy.
 *
 * @return                   DHOP_SUCCESS for success, otherwise failed.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_MAT_destroy(DHOP_AI_MAT_Handle matrix);

/**
 * @brief check whether the matrix handle is valid or not.
 *
 * @param [in]  matrix       the matrix handle.
 *
 * @return                   DH_TRUE if it is a valid matrix handle; 
 *                           DH_FALSE if it is not a valid matrix handle.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_MAT_isValid(DHOP_AI_MAT_Handle matrix);

/**
 * @brief get the data type of the matrix.
 *
 * @param [in]  matrix       the matrix handle
 *
 * @return                   the data type of the matrix, i.e. @ref DHOP_AI_MAT_8U, < 0 means a failure has occurred.
 */
DHOP_AI_API 
DH_Int32 DHOP_AI_MAT_type(DHOP_AI_MAT_Handle matrix);

/**
 * @brief get the size of the data element of the matrix.
 *
 * @param [in]  matrix       the matrix handle
 *
 * @return                   the element size, measured in bytes. < 0 means a failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_elementSize(DHOP_AI_MAT_Handle matrix);

/**
 * @brief get the row number of the two-dimensional matrix.
 *
 * @param [in]  matrix       the matrix handle
 *
 * @return                   if the matrix is two-dimensional, it returns the row number. Otherwise, it returns negative value.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_rows(DHOP_AI_MAT_Handle matrix);

/**
 * @brief get the column number of the two-dimensional matrix.
 *
 * @param [in]  matrix       the matrix handle
 *
 * @return                   if the matrix is two-dimensional, it returns the column number. Otherwise, it returns a negative value.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_cols(DHOP_AI_MAT_Handle matrix);

/**
 * @brief get the row stride of the two-dimensional matrix.
 *
 * @param [in]  matrix       the matrix handle
 *
 * @return                   if the matrix is two-dimensional, it returns the row stride measured in bytes. Otherwise, it returns a negative value.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_step(DHOP_AI_MAT_Handle matrix);

/**
 * @brief get the number of dimensions of the matrix. 
 *
 * @param [in]  matrix       the matrix handle
 *
 * @return                   the number of dimensions of the matrix on success. <0 means a failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_ndims(DHOP_AI_MAT_Handle matrix);

/**
 * @brief get the size information of the matrix.
 *
 * @param [in]  matrix       the matrix handle
 *
 * @return                   a pointer to read-only array where the dimension sizes are stored. DH_NULL means a failure has occurred.
 */
DHOP_AI_API
const DH_Int32 * DHOP_AI_MAT_sizes(DHOP_AI_MAT_Handle matrix);


/**
 * @brief get the size of the matrix at a specified dimension.
 *
 * @param [in]  matrix       the matrix handle
 * @param [in]  index        the index of the specified dimension.
 *
 * @return                   the size of the matrix at dimension `index'. <0 means a failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_size(DHOP_AI_MAT_Handle matrix, DH_Int32 index);

/**
 * @brief get the stride information of the matrix.
 *
 * @param [in]  matrix       the matrix handle
 *
 * @return                   a pointer to read-only array where the strides are stored. DH_NULL means a failure has occurred.
 *                           The strides are measured in bytes.
 */
DHOP_AI_API
const DH_Int32 * DHOP_AI_MAT_steps(DHOP_AI_MAT_Handle matrix);

/**
 * @brief get the stride of the matrix at a specified dimension. 
 *
 * @param [in]  matrix       the matrix handle
 * @param [in]  index        the index of the specified dimension.
 *
 * @return                   the stride of the matrix at dimension `index'. <0 means a failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_stepi(DHOP_AI_MAT_Handle matrix, DH_Int32 index);

/**
 * @brief set the active range at a specified dimension for the matrix.
 *
 * @param [in]  matrix       the matrix handle
 * @param [in]  index        the index of the specified dimension.
 * @param [in]  start        the start position of the active range.
 * @param [in]  length       the length of the active range, it can be zero.
 *
 * @return                   DHOP_SUCCESS on success, otherwise failed.
 *
 * @note The data outside the active range are not valid.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_setActiveRange(DHOP_AI_MAT_Handle matrix, DH_Int32 index, DH_Int32 start, DH_Int32 length);

/**
 * @brief get the active range of the matrix at a specified dimension. 
 *
 * @param [in]  matrix       the matrix handle
 * @param [in]  index        the index of the specified dimension.
 * @param [out] start        the start position of the active range.
 * @param [out] length       the length of the active range.
 *
 * @return                   DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_getActiveRange(DHOP_AI_MAT_Handle matrix, DH_Int32 index, DH_Int32 * start, DH_Int32 * length);

/**
 * @brief set the user-defined data for the matrix.
 *
 * @param [in] matrix        the matrix handle
 * @param [in] user_data     a pointer to the user-defined data.
 *
 * @return                   DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_setUserData(DHOP_AI_MAT_Handle matrix, DH_Ptr user_data);

/**
 * @brief get the user-defined data for the matrix.
 *
 * @param [in] matrix        the matrix handle
 * 
 * @return                   the pointer to the user-defined data. 
 *                           DH_NULL means there is no user-defined data or a failure has occurred.
 */
DHOP_AI_API
DH_Ptr DHOP_AI_MAT_getUserData(DHOP_AI_MAT_Handle matrix);


/**
 * @brief discard the current data in the matrix.
 * 
 * @param [in]  matrix       the matrix handle
 *
 * @return                   DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_discard(DHOP_AI_MAT_Handle matrix);

/**
 * @brief check whether the matrix has a valid CPU/software/host address or not.
 *
 * @param [in]  matrix      the matrix handle
 *
 * @return                  DH_TRUE if condition is satisfied. 
 *                          DH_FALSE if condition is not satisfied, or a failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_hasPtr(DHOP_AI_MAT_Handle matrix);

/**
 * @brief check whether the matrix has a valid GPU/hardware/device address or not.
 *
 * @param [in]  matrix      the matrix handle
 *
 * @return                  DH_TRUE if condition is satisfied. 
 *                          DH_FALSE if condition is not satisfied, or a failure has occurred.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_hasPtrHW(DHOP_AI_MAT_Handle matrix);

/**
 * @brief get the CPU/software/host address from the two-dimensional matrix for an indexed element.
 *
 * @param [in]  matrix       the matrix handle
 * @param [in]  row          the row index of the element
 * @param [in]  col          the column index of the element
 *
 * @return                   the CPU/software/host address of the indexed element. 
 *                           DH_NULL means the matrix is not valid or not two-dimensional.
 */
DHOP_AI_API
DH_Ptr DHOP_AI_MAT_ptr(DHOP_AI_MAT_Handle matrix, DH_Int32 row, DH_Int32 col);

/**
 * @brief get the CPU/software/host address from the n-dimensional matrix for an indexed element.
 *
 * @param [in]  matrix       the matrix handle
 * @param [in]  pos          pointer to the element indexes at each dimension.
 *                           Set to DH_NULL will return the address of the first element.
 *
 * @return                   the CPU/software/host address of the indexed element. 
 *                           DH_NULL means the matrix is not valid or an error has occurred.
 */
DHOP_AI_API
DH_Ptr DHOP_AI_MAT_ptr2(DHOP_AI_MAT_Handle matrix, DH_Int32 * pos);

/**
 * @brief get the GPU/hardware/device address from the two-dimensional matrix for an indexed element.
 *
 * @param [in]  matrix       the matrix handle
 * @param [in]  row          the row index of the element
 * @param [in]  col          the column index of the element
 *
 * @return                   the GPU/hardware/device address of the indexed element. 
 *                           DH_NULL means the matrix is not valid or not two-dimensional.
 */
DHOP_AI_API
DH_Ptr DHOP_AI_MAT_ptrHW(DHOP_AI_MAT_Handle matrix, DH_Int32 row, DH_Int32 col);

/**
 * @brief get the GPU/hardware/device address from the n-dimensional matrix for an indexed element.
 *
 * @param [in]  matrix       the matrix handle
 * @param [in]  pos          pointer to the element indexes at each dimension.
 *                           Set to DH_NULL will return the address of the first element.
 *
 * @return                   the GPU/hardware/device address of the indexed element. 
 *                           DH_NULL means the matrix is not valid or an error has occurred.
 */
DHOP_AI_API
DH_Ptr DHOP_AI_MAT_ptr2HW(DHOP_AI_MAT_Handle matrix, DH_Int32 * pos);

/**
 * @brief make a declaration of read operation in the matrix from CPU/software/host.
 *
 * @param [in]  matrix       the matrix handle
 *
 * @return                   DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_read(DHOP_AI_MAT_Handle matrix);

/**
 * @brief make a declaration of write operation in the matrix from CPU/software/host.
 *
 * @param [in]  matrix       the matrix handle.
 *
 * @return                   DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_write(DHOP_AI_MAT_Handle matrix);

/**
 * @brief make a declaration of read and/or write operation in the matrix from CPU/software/host.
 *
 * @param [in]  matrix       the matrix handle
 *
 * @return                   DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_readWrite(DHOP_AI_MAT_Handle matrix);

/**
 * @brief make a declaration of read operation in the matrix from GPU/hardware/device
 *
 * @param [in]  matrix       the matrix handle
 *
 * @return                   DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_readHW(DHOP_AI_MAT_Handle matrix);

/**
 * @brief make a declaration of write operation in the matrix from GPU/hardware/device
 *
 * @param [in]  matrix       the matrix handle
 *
 * @return                   DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_writeHW(DHOP_AI_MAT_Handle matrix);

/**
 * @brief make a declaration of read and/or write operation in the matrix from GPU/hardware/device
 * 
 * @param [in]  matrix       the matrix handle
 *
 * @return                   DHOP_SUCCESS on success, otherwise failed.
 */
DHOP_AI_API
DH_Int32 DHOP_AI_MAT_readWriteHW(DHOP_AI_MAT_Handle matrix);

#ifdef __cplusplus
}
#endif

#endif
