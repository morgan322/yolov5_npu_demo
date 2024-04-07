#ifndef __DHOP_WEB_H__
#define __DHOP_WEB_H__

#ifdef __cplusplus
extern "C"{
#endif

    typedef struct 
    {
        int x;
        int y;
    }DHOP_WEB_Point;

    typedef int (*webCallback)(DHOP_WEB_Point* , int);

    int DHOP_WEB_init(webCallback cb);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // 
