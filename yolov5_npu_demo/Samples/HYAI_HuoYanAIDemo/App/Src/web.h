#ifndef __DHOP_WEB_H__
#define __DHOP_WEB_H__
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>


#include "dhop_sys.h"
#include "dhop_app.h"
#include "dhop_version.h"
#include "dhop_http.h"
#include "dhop_yuv.h"
#include "dhop_codec.h"
#include "dhop_log.h"

#ifdef __cplusplus
extern "C"{
#endif

    typedef struct 
    {
        int x;
        int y;
    }DHOP_WEB_Point;
   
    static char *webstr;

    typedef int (*webCallback)(char *buffer);

    int DHOP_WEB_init(webCallback cb);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // 
