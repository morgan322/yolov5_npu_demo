#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <string>

#include "dhop_sys.h"
#include "dhop_version.h"
#include "dhop_log.h"
#include "web.h"



int dataCallback(DHOP_WEB_Point* pointArray, int n)
{
    for (int i = 0; i < n; i++)
    {
        DHOP_LOG_INFO("DHOP_WEB_Point index:%d is [%d,%d]\n", i, pointArray[i].x, pointArray[i].y);
    }
}

DH_Void TestHttpOnExit()
{
    DHOP_LOG_INFO("process-%d will exit\n", getpid());
}

int main(void)
{
    DH_Int32 ret = -1;
    DHOP_SYS_InitParam initParam;

    memset(&initParam, 0, sizeof(initParam));
    initParam.onExitCallback = TestHttpOnExit;
    initParam.version = DHOP_SDK_VERSION;
    ret = DHOP_SYS_init(&initParam);
    if (0 != ret)
    {
        DHOP_LOG_INFO("DHOP_SYS_init fail with %#x\n", ret);
        return -1;
    }

    DHOP_LOG_setLevel(DHOP_LOG_LEVEL_DEBUG, DHOP_LOG_DEST_WEB);
    DHOP_LOG_INFO("DHOP_SYS_init suscess!");


    DHOP_WEB_init(dataCallback);

    while (1)
    {
        sleep(1);
    }
    return -1;
}