/*******************************************************************************
 * dhop_mem.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 定义内存相关的数据结构与API
 *
 *******************************************************************************/

#ifndef __DHOP_MEM_H__
#define __DHOP_MEM_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"


/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)

typedef struct
{
    DH_Void     *phyAddr;     // 调用者使用DHOP_MEM_blockAlloc接口申请得来的物理地址
    DH_Void     *virAddr;     // 调用者使用DHOP_MEM_blockAlloc接口申请得来的虚拟地址
    DH_Uint32    size;        // 根据DHOP_MEM_blockAlloc接口申请的size填写，拷贝过程会取pSrc->size、pDst->size较小的一个作为拷贝的尺寸
    DH_Uint32    reserved[9]; // 保留字段
} DHOP_MEM_blockInfo;

#endif

#if (__SIZEOF_POINTER__ == 8)

typedef struct
{
    DH_Void     *phyAddr;     // 调用者使用DHOP_MEM_blockAlloc接口申请得来的物理地址
    DH_Void     *virAddr;     // 调用者使用DHOP_MEM_blockAlloc接口申请得来的虚拟地址
    DH_Uint32    size;        // 根据DHOP_MEM_blockAlloc接口申请的size填写，拷贝过程取pSrc->size、pDst->size较小的一个作为拷贝的尺寸
    DH_Uint32    resBytes;    // reserved
    DH_Uint64    reserved[4]; // 保留字段
} DHOP_MEM_blockInfo;

#endif


/*******************************************************************************/


/***************************************************************
* function name : DHOP_MEM_blockAlloc
*
* description   : alloc block memory
*
* input         : size -- size of memory
*                 phyAlign  -- physical address align bytes, phyAlign must be less than 256
*                 cacheable -- DH_FALSE:alloc memory without cache;
*                              DH_TRUE:alloc memory with cache
*
* output        : ppPhyAddr -- physical address
*                 ppVirAddr -- virtual address
*
*notice        : 1. 线程安全
*                2. 支持多线程调用
*
* return value  : DHOP_SUCCESS
*                 DHOP_FAILED
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_MEM_blockAlloc(DH_Uint32            size,
                             DH_Uint32            phyAlign,
                             DH_Bool              cacheable,
                             DH_Void            **ppPhyAddr,
                             DH_Void            **ppVirAddr);


/***************************************************************
* function name : DHOP_MEM_blockFree
*
* description   : free block memory
*
* input         : pPhyAddr -- physical address
*                 pVirAddr -- virtual address
*
* output        :
*
*notice        : 1. 线程安全
*                2. 支持多线程调用
*
* return value  : DHOP_SUCCESS
*                 DHOP_FAILED
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_MEM_blockFree(DH_Void* pPhyAddr, DH_Void* pVirAddr);

/***************************************************************
* function name : DHOP_MEM_blockCopy
*
* description   : copy block memory(hardware accelerate)
*
* input         : pSrc -- source
*                 pDst -- destination
*
* output        :
*
*notice        : 1. 线程安全
*                2. 支持多线程调用
*
* return value  : DHOP_SUCCESS
*                 DHOP_FAILED
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_MEM_blockCopy(DHOP_MEM_blockInfo *pSrc, DHOP_MEM_blockInfo *pDst);

/***************************************************************
* function name : DHOP_MEM_blockFlushCache
*
* description   : flush cache to memory
*                 (for cacheable memory allocated by DHOP_MEM_alloc)
*
* input         : pPhyAddr -- physical address
*                 pVirAddr -- virtual address
*                 dataSize -- data size
*
* output        : none
*
*notice        : 1. 线程安全
*                2. 支持多线程调用
*
* return value  : DHOP_SUCCESS
*                 DHOP_FAILED
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_MEM_blockFlushCache(DH_Void* pPhyAddr, DH_Void* pVirAddr, DH_Uint32 dataSize);



/***************************************************************
* function name : DHOP_MEM_blockMmap
*
* description   : mmap block memory
*
* input         : size      -- size of memory
*                 cacheable -- DH_FALSE:mmap memory without cache;
*                              DH_TRUE:mmap memory with cache
*                 pPhyAddr  -- physical address
*
* output        : ppVirAddr -- virtual address
*
*notice        : 1. 线程安全
*                2. 支持多线程调用
*                3. 同进程内不支持对同一物理地址多次调用
*
* return value  : DHOP_SUCCESS
*                 DHOP_FAILED
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_MEM_blockMmap(DH_Uint32            size,
                            DH_Bool              cacheable,
                            DH_Void             *pPhyAddr,
                            DH_Void            **ppVirAddr);


/***************************************************************
* function name : DHOP_MEM_blockMunmap
*
* description   : munmap block memory
*
* input         : size      -- size of memory
*                 pPhyAddr  -- physical address
*
* output        : none
*
*notice        : 1. 线程安全
*                2. 支持多线程调用
*                3. 同进程内不支持对同一物理地址多次调用
*
* return value  : DHOP_SUCCESS
*                 DHOP_FAILED
*                 other - ref DHOP_ErrorCode
***************************************************************/
DH_Int32 DHOP_MEM_blockMunmap(DH_Uint32            size,
                              DH_Void             *pVirAddr);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_MEM_H__


