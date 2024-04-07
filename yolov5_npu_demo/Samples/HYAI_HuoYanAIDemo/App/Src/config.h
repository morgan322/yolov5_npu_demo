#include "dhop_sys.h"
#include "dhop_app.h"
#include "dhop_version.h"
#include "dhop_http.h"
#include "dhop_yuv.h"
#include "dhop_codec.h"
#include "dhop_mem.h"
#include "dhop_log.h"
#include "dhop_event_common.h"
#include "dhop_event_pushCustom.h"
#include "dhop_venc.h"
#include "dhop_osd.h"
#include "dhop_ai.h"
#include "yolo_object.h"
#include "dhop_errno.h"
#include "dhop_sys.h"
#include "dhop_storage.h"
#include "dhop_cfg_os.h"
#include "dhop_audout.h"
#include "dhop_stream.h"

#include<string.h>
#include "curl/curl.h"
#include "ini.h"
#include "List.h"
#include <curl/easy.h>
#include "cJSON.h"
#include "fun.h"

#include "openssl/aes.h"
#include "openssl/evp.h"
#include "openssl/bio.h"
#include "openssl/buffer.h"
#include "openssl/md5.h"

/*#ifndef _CONFIG_H_
#define _CONFIG_H_*/



// config
typedef struct
{
    int x1,x2,x3,x4;
    int y1,y2,y3,y4;
    int rsh,rsm,reh,rem,rin;
    int px1,px2,px3,px4;
    int py1,py2,py3,py4;
    int psh,psm,peh,pem,pin;
    int bx1,bx2,bx3,bx4;
    int by1,by2,by3,by4;
    int wsh,wsm,weh,wem,win;
    int osh,osm,oeh,oem,oin;
    int bsh,bsm,beh,bem,bin;
    int person_conf,rubbish_conf,work_conf;
    int upload_count,last_time;
    int vedio,upload,auth;


    const char *url;
    const char *cgurl;
    const char* ugurl;
    const char* dataurl;
    const char* savepath;
    const char* purl;

    const char* authcode;
    const char* overtag;
    const char* persontag;
    const char* bagtag;
    const char* rubbishtag;
    const char* workertag;
    const char* overtip;
    const char* persontip;
    const char* bagtip;
    const char* workertip;
    const char* rubbishtip;

} configuration;


struct app_config {
    struct {
        int     lt_x;
        int     lt_y;
        int     rb_x;
        int     rb_y;
    } detect_region;
    struct {
        int     lt_x;
        int     lt_y;
        int     rb_x;
        int     rb_y;
    } min_region;
    int         selected_objs[16];
    int         linkage_event;

    char        net_ip[16];
    int         net_port;

    int         log_level;

    int         mask;
};



struct paint_info_t {
    DHOP_OSD_Element            element[2];
    DHOP_OSD_Polygon            rect;
    DHOP_OSD_Point              points[4];
    DHOP_OSD_Text               text;
    DH_Char                     szText[24];
};


static size_t filesize = 0;
static char pstr[10240]="";
static char *nurl ="https://dev-api-cloud.eiotyun.com:83/jfq/api/video-surveillance/adm-event/pushEvent";
static int upload_type = 1;
static int auth = 0;


extern void config_read(configuration *config);
extern int handler(void* location, const char* section, const char* url, const char* value);
extern void  config_get(const char *url);
extern void config_parse(configuration *config);
extern void json_read(configuration* config);
extern void p_upload(const char* url, char* payload );
extern void encrypt_alg(configuration *config,char *serial);

//#endif
