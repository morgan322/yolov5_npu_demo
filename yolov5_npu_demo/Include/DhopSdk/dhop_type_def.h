/*******************************************************************************
 * dhop_type_def.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: Definition of Base types and APIs of Dahua Open Platform.
 *
 *******************************************************************************/

#ifndef __DHOP_TYPE_DEF_H__
#define __DHOP_TYPE_DEF_H__
#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/
/* bool types definition */
#ifndef DEFINED_DH_Bool
#define DEFINED_DH_Bool
typedef unsigned char      DH_Bool;        /* 8-bit bool type */
typedef unsigned char      DH_Bool8;       /* 8-bit bool type */
#endif

#ifndef DEFINED_DH_Bool16
#define DEFINED_DH_Bool16
typedef unsigned short     DH_Bool16;      /* 16-bit bool type */
#endif

#ifndef DEFINED_DH_Bool32
#define DEFINED_DH_Bool32
typedef unsigned int       DH_Bool32;      /* 32-bit bool type */
#endif


/* signed integer types definition */
#ifndef DEFINED_DH_Int64
#define DEFINED_DH_Int64
typedef long long          DH_Int64;       /* 64-bit signed int type */
#endif

#ifndef DEFINED_DH_Int32
#define DEFINED_DH_Int32
typedef int                DH_Int32;       /* 32-bit signed int type */
#endif

#ifndef DEFINED_DH_Int16
#define DEFINED_DH_Int16
typedef short              DH_Int16;       /* 16-bit signed int type */
#endif

#ifndef DEFINED_DH_Int8
#define DEFINED_DH_Int8
typedef signed char        DH_Int8;        /* 8-bit signed int type */
#endif


/* unsigned integer types definition */
#ifndef DEFINED_DH_Uint64
#define DEFINED_DH_Uint64
typedef unsigned long long DH_Uint64;      /* 64-bit unsigned int type */
#endif

#ifndef DEFINED_DH_Uint32
#define DEFINED_DH_Uint32
typedef unsigned int       DH_Uint32;      /* 32-bit unsigned int type */
#endif

#ifndef DEFINED_DH_Uint16
#define DEFINED_DH_Uint16
typedef unsigned short     DH_Uint16;      /* 16-bit unsigned int type */
#endif

#ifndef DEFINED_DH_Uint8
#define DEFINED_DH_Uint8
typedef unsigned char      DH_Uint8;       /* 8-bit unsigned int type */
#endif


/* character types definition */
#ifndef DEFINED_DH_Char
#define DEFINED_DH_Char
typedef char               DH_Char;        /* char type */
#endif

#ifndef DEFINED_DH_Byte
#define DEFINED_DH_Byte
typedef char               DH_Byte;        /* Byte type */
#endif

#ifndef DEFINED_DH_String
#define DEFINED_DH_String
typedef char *             DH_String;      /* string type, end of '\0' */
#endif


/* float types definition */
#ifndef DEFINED_DH_Float32
#define DEFINED_DH_Float32
typedef float              DH_Float32;     /* 32-bit float type */
#endif

#ifndef DEFINED_DH_Float64
#define DEFINED_DH_Float64
typedef double             DH_Float64;     /* 64-bit float type */
#endif


/* handle type definition */
#ifndef DEFINED_DH_Handle
#define DEFINED_DH_Handle
typedef void *             DH_Handle;      /* handle type */
#endif


/* void type definition */
#ifndef DEFINED_DH_Void
#define DEFINED_DH_Void
#define DH_Void  void       /* void type */
#endif


/* void type definition */
#ifndef DEFINED_DH_Ptr
#define DEFINED_DH_Ptr
typedef void *             DH_Ptr;        /* pointer type */
#endif


/* definition of true or false values */
#ifndef DH_TRUE
#define DH_TRUE            1             /* true */
#endif


/* definition of true or false values */
#ifndef DH_FALSE
#define DH_FALSE           0             /* false */
#endif


/* definition of null value */
#ifndef DH_NULL
#define DH_NULL            NULL         /* null value */
#endif


/* definition of Point-16bit */
typedef struct
{
    DH_Int16               x;
    DH_Int16               y;
} DH_Point16;


/* definition of Point-32bit */
typedef struct
{
    DH_Int32               x;
    DH_Int32               y;
} DH_Point32;


/* definition of Rectangle-16bit */
typedef struct
{
    DH_Point16             lt;         /* left-top */
    DH_Point16             rb;         /* right-bottom */
} DH_Rect16;


/* definition of Rectangle-32bit */
typedef struct
{
    DH_Point32             lt;         /* left-top */
    DH_Point32             rb;         /* right-bottom */
} DH_Rect32;


/* definition of datetime */
typedef struct
{
    DH_Uint16              year;
    DH_Uint16              month : 6;  /* 取值范围[1~12] */
    DH_Uint16              day   : 5;  /* 取值范围[1~31] */
    DH_Uint16              hour  : 5;  /* 取值范围[0~23] */
    DH_Uint8               min;        /* 取值范围[0~59] */
    DH_Uint8               sec;        /* 取值范围[0~59] */
    DH_Uint16              msec;       /* 取值范围[0~999] */
} DH_DateTime;


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_TYPE_DEF_H__


