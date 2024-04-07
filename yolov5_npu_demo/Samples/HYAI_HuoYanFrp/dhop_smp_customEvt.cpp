#include <stdio.h>
#include <string>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <map>
#include <vector>
#include <sys/time.h>
#include "dhop_sys.h"
#include "dhop_app.h"
#include "dhop_event.h"
#include "dhop_log.h"


unsigned char* g_jpgBuf = 0;
unsigned int g_jpgSize = 0;



static void __appExit()
{
	DHOP_LOG_INFO("oh! app will exit\n");
}

int main()
{

	/// init dhop
	DHOP_SYS_InitParam stInit = {0,};
	stInit.version = DHOP_SDK_VERSION;
	stInit.onExitCallback = &__appExit;
	if (DHOP_SYS_init(&stInit) != 0)
	{
		printf("DHOP_SYS_init failed\n");
		return -1;
	}
	DHOP_LOG_setLevel(DHOP_LOG_LEVEL_DEBUG, DHOP_LOG_DEST_WEB);
	DHOP_LOG_INFO("DHOP_SYS_init suscess!");
	
	while (1)
	{
	
		sleep(10);
	}
	return 0;
}