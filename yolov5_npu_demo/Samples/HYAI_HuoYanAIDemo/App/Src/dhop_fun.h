#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#include "config.h"
#include "mp4v2/mp4v2.h"

#define ALIGN(value, align)   ((( (value) + ( (align) - 1 ) ) \
            / (align) ) * (align) )
#define FLOOR(value, align)   (( (value) / (align) ) * (align) )

#define APP_MAX_AI_RESULT_NUM   (32)

struct app_global_t {
    int                         hNet;
    DH_Handle                   hYuv;
    DH_Handle                   hVenc;
    DHOP_AI_NNX_Handle          hNNX;

    DH_Int32                    resultNum;
    DH_Int32                    encAlignW;
    DH_Int32                    encAlignH;
    obj_info_t                  aiResult[APP_MAX_AI_RESULT_NUM];


};

//DH_Int32 app_yuv_init(struct app_global_t * g_app_global);
int app_ai_init(struct app_global_t * g_app_global);
DH_Int32 app_ai_process(DHOP_AI_NNX_Handle hNNX, DHOP_YUV_FrameData2 * frame,struct app_global_t * g_app_global);
//int app_enc_init(struct app_global_t * g_app_global);
DH_Int32 app_result_draw(configuration *config,struct app_global_t * g_app_global);
void app_coresult_snap(struct app_global_t * g_app_global,DHOP_YUV_FrameData2* frame, char *filename,char  *objinfo);
void app_result_snap(struct app_global_t * g_app_global,DHOP_YUV_FrameData2* frame, char *filename);
void update_http(char * url);
int sdload();
int audio_play(int volu,char* audiopath);
DH_Int32 DHOP_SMP_RealStreamModDemo(int pretime,char *hfilename,char *mfilename);
void coupload(const char* url, char* filename, char * mfilename,const char* Id,const char* tag,const char* tip);
void c_upload(char *hydeviceCode,int alarmtype,int sec,char *usec,char *filename,char *mfilename);
DH_Int32 app_size_limit(DH_Int32 pix, DH_Int32 max);
int IoU(int x1, int y1, int x2, int y2, int u1, int v1, int u2, int v2);
