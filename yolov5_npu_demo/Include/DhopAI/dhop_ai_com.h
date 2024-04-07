/*******************************************************************************
 * dhop_ai_mat.h
 *
 * Copyright (C) 2015-2020 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: common defines and APIs for intelligent algorithm.
 *
 *******************************************************************************/

#ifndef __DHOP_AI_COM_H__
#define __DHOP_AI_COM_H__

#include<pthread.h>
#include "dhop_type_def.h"
#include "dhop_errno.h"

// API attributes.
#if __GNUC__ >= 4
#  define DHOP_AI_API __attribute__ ((visibility("default"))) 
#else
#  define DHOP_AI_API
#endif


#ifdef __cplusplus
extern "C"{
#endif


///<  Ensure the pointer variable lengths of 32-bit and 64-bit platforms are the same, 
///<  and prevent the 32-bit platform header file adding pointers to cause the size of the structure(64-bit) to change
///<  Usage: after the pointer variable, use this macro, N fill in any value, and the same structure body does not have the same name.
#ifndef DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8
#if defined(_WIN64) || (defined(__WORDSIZE) && __WORDSIZE==64)
#define DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(N)
#elif defined(_WIN32) || (defined(__WORDSIZE) && __WORDSIZE==32)
#define DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(N) DH_Uint32 unused##N;
#elif defined(__GNUC__)
#define DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(N) DH_Uint8 unused##N[8-sizeof(void*)];
#elif defined(CCS)
#define DHOP_AI_UNUSED_FORCE_POINTER_ALIGN8(N) DH_Uint32 unused##N;
#else
#error "Can't find macro `__WORDSIZE' definition, please specify this macro 32 or 64 base on your platform!"
#endif
#endif //UNUSED_FORCE_POINTER_ALIGN8

/** point data structure. */
typedef struct
{
    DH_Int32    x;  /**< x-axis position */
    DH_Int32    y;  /**< y-axis position */ 
} DHOP_AI_Point;

/** rectangle data structure. */
typedef struct
{   
    DHOP_AI_Point   ul; /**< upper-left corner point */
    DHOP_AI_Point   lr; /**< lower-right corner point */     
} DHOP_AI_Rect;

/**
 * @brief 		Get signal
 * @return     	0: normal	1:abnormal
 */
DHOP_AI_API
DH_Int32 DHOP_AI_getSignalFlag(void);

/**
 * @brief get lib version
 * 
 * @param [out]	version		memory pointer to store alg version (provided by the user),
 *							it is recommended to apply for 128 bytes, eg char ver[128];
 *
 * @param [in]	len			the longest string length that pointer can store (including'\0')
 * 
 * @return                  0:sucess  other:fail
 */
DHOP_AI_API
DH_Int32 DHOP_AI_getVersion(char* version, int len);
	
/**
 * @brief 		alg system init
 * @return      0:sucess  other:fail
 */
DHOP_AI_API
DH_Int32 DHOP_AI_init(void);

/**
 * @brief		alg system uninit
 * @return      0:sucess  other:fail
 */
DHOP_AI_API
DH_Int32 DHOP_AI_unInit(void);

#ifdef __cplusplus
}
#endif

#endif
