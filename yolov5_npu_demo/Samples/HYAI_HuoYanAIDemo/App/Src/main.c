#include "dhop_fun.h"
#include "web.h"

static struct app_global_t      g_app_global;
static struct app_config        g_app_config;
static configuration config;
static int audio_flag=0;

// Initialization of YUV
DH_Int32 app_yuv_init(struct app_global_t * g_app_global)
{
    DH_Int32                ret = -1;
    DHOP_YUV_Option         yuvOption;
    DHOP_YUV_CapInfo        yuvCap;
    DHOP_YUV_OpenParam      yuvOpenPrm;
    DHOP_YUV_FormatParam    yuvFmtPrm;
    DH_Int32                yuvChn = 0;

    memset(&yuvCap, 0, sizeof(DHOP_YUV_CapInfo));
    memset(&yuvOpenPrm, 0, sizeof(yuvOpenPrm));
    // 1.Get YUV channel capability
    ret = DHOP_YUV_getChnCaps(yuvChn, &yuvCap);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("DHOP_YUV_getChnCaps fail with %#x\n", ret);
        return ret;
    }

    yuvOpenPrm.channel = 0;
    // 2.Open YUV channel
    ret = DHOP_YUV_open(&yuvOpenPrm, &(g_app_global->hYuv));
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("DHOP_YUV_open fail with %#x\n", ret);
        return ret;
    }

    memset(&yuvFmtPrm, 0, sizeof(yuvFmtPrm));
    yuvFmtPrm.format = DHOP_YUV_FMT_420SP_VU;
    yuvFmtPrm.fps    = 5;
    yuvFmtPrm.width  = yuvCap.maxWidth;
    yuvFmtPrm.height = yuvCap.maxHeight;
    // 3.Set YUV channel format parameters
    ret = DHOP_YUV_setFormat(g_app_global->hYuv, &yuvFmtPrm);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("DHOP_YUV_setFormat fail with %#x\n", ret);
        DHOP_YUV_close(&g_app_global->hYuv);
        return ret;
    }

    memset(&yuvOption, 0, sizeof(yuvOption));
    yuvOption.cbSize = sizeof(yuvOption);
    yuvOption.type = DHOP_YUV_OPT_DEPTH;
    yuvOption.option.depth = 1;
    // 4.Set YUV optional configuration
    ret = DHOP_YUV_setOption(g_app_global->hYuv, &yuvOption);
    if(DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("DHOP_YUV_setOption fail with %#x\n", ret);
        DHOP_YUV_close(&g_app_global->hYuv);
        return ret;
    }
    DHOP_LOG_INFO("DHOP_AI_init success\n");
}


int app_enc_init(struct app_global_t * g_app_global) {
    DH_Int32                ret;
    DHOP_YUV_CapInfo        yuvCap;
    DHOP_VENC_CapsInfo      encCap;
    DHOP_VENC_CreateParam   createParam;

    ret = DHOP_YUV_getChnCaps(0, &yuvCap);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("DHOP_YUV_getChnCaps fail with %#x\n", ret);
        return ret;
    }

    memset(&createParam, 0, sizeof(createParam));
    createParam.cbSize = sizeof(createParam);
    createParam.type = DHOP_VENC_YUV_TO_JPEG;
    createParam.max_width = yuvCap.maxWidth;
    createParam.max_height = yuvCap.maxHeight;
    createParam.format = DHOP_YUV_FMT_420SP_VU;

    ret = DHOP_VENC_getCaps(&encCap);


    g_app_global->encAlignW = encCap.alignWidth;
    g_app_global->encAlignH = encCap.alignHeight;

    // Create encoder
    ret = DHOP_VENC_create(&createParam, &(g_app_global->hVenc));
    if (ret != DHOP_SUCCESS) {
        DHOP_LOG_ERROR("DHOP_VENC_create fail with %#x\n", ret);
        return ret;
    }

    return 0;
}



void * audio_bag(void *){
    while (1)
    {
        if (audio_flag==1){
             printf("audio_flag:%d",audio_flag);
            int ret = audio_play(100,"./bag.pcm");
            audio_flag=0;
            printf("audio_flag:%d",audio_flag);
        }
    }
}

void * app_ai_task(void *)
//void app_ai_task()
{
    DH_Int32                i, ret = -1;
    DH_Int32                tryCnt = 0;
    DHOP_YUV_FrameData2     yuvFrame;


    float pconf = (float)config.person_conf/100;
    float rconf = (float)config.rubbish_conf/100;
    float wconf = (float)config.work_conf/100;

     //init
    LTNode* ruinfolist = ListInit();
    LTNode* rulist = ListInit();
    LTNode* blist = ListInit();
    LTNode* prlist = ListInit();
    LTNode* rtlist = ListInit();
    LTNode* otlist = ListInit();
    LTNode* dblist = ListInit();


    int m = 3; 
    int framen = 16;
    int maxnum = 5;
    int overcount = 0;//1
    int rubbishcount = 0;//5
    int framecount = 0;

    for (int i =0 ;i<maxnum*4;i++){
         ListPushBack(ruinfolist, i);
    }
    //ListPrint(ruinfolist);

    for (int i =0 ;i<maxnum*4;i++){
         ListPushBack(rulist, i);
    }
    //ListPrint(rulist);

    for (int i =1;i<framen*2-1;i++){
        ListPushBack(blist, 0);
    }
     for (int i =1;i<framen*2-1;i++){
        ListPushBack(dblist, 0);
    }
    //ListPrint(blist);

    for (int i =1;i<m;i++){
        ListPushBack(prlist, 0);
    }

    for (int i =1;i<m;i++){
        ListPushBack(rtlist, 0);
    }

    for (int i =1;i<m;i++){
        ListPushBack(otlist, 0);
    }
    DHOP_SYS_DevInfo pDevInfo;
    ret=DHOP_SYS_getDevInfo(&pDevInfo);
    printf("s/n: %s\n", pDevInfo.serial);

    char *hydeviceCode = (char*)pDevInfo.serial;

    
    while(1)
    {
        //printf("s/n: %s\n",  hydeviceCode);
        
        //time
        DHOP_SYS_LocalTime pLocalTime;
        ret = DHOP_SYS_getLocalTime(&pLocalTime);
        //printf("time of frame %d\n", pLocalTime.min);
        DHOP_SYS_UtcTime pUtcTime;
        ret = DHOP_SYS_getUtcTime(&pUtcTime);
        int sec = pUtcTime.sec;
        //g_app_global.usec = 1000*pUtcTime.sec +pUtcTime.msec;
        char *usec = join(litoa(pUtcTime.sec),itoa(199));
        //printf("microsec %s\n",g_app_global.usec);

        int hmiao0 = pUtcTime.sec*1000 + pUtcTime.msec;
        int   y,m,d,h,n,s;
        y   =   pLocalTime.year;     //年
        m   =   pLocalTime.mon;             //月
        d   =   pLocalTime.mday;               //日
        h   =   pLocalTime.hour;               //时
        n   =   pLocalTime.min;                 //分
        s   =   pLocalTime.sec;                 //秒
        int totals = h*24*60 + n*60 + s;

        char *nian;char *yue;char *ri;char *shi;char *fen;char *miao;
        nian =itoa(y);
        printf("time = %d\\%d\\%d\\%d\\%d\\%d \n", y,m,d,h,n,s);

        char *b="0";
        char *t0 = join(nian,"_");
        
        if (m>9){
            yue = itoa(m);
        }else{
            yue = join(b,itoa(m));
        }
        char *t1= join(t0,yue);
        char *t2=join(t1,"_");

        if(d>9){
            ri = itoa(d);
        }else{
            ri=join(b,itoa(d));
        }
        char *t3=join(t2,ri);
        //printf("wst = %s \n", wstr);
        char *daytime=t3;

          // 获取YUV数据，对参数进行清理
        memset(&yuvFrame, 0, sizeof(yuvFrame));
        // 结构体必要的字段进行填写
        yuvFrame.cbSize = sizeof(yuvFrame);
        //depth
        DHOP_YUV_Option yuvOption;
        memset(&yuvOption, 0, sizeof(yuvOption));
        yuvOption.cbSize = sizeof(yuvOption);
        yuvOption.type = DHOP_YUV_OPT_DEPTH;
        yuvOption.option.depth = 1;
        ret = DHOP_YUV_setOption(g_app_global.hYuv, &yuvOption);
        if(DHOP_SUCCESS != ret)
        {
            printf("DHOP_YUV_setOption fail with %#x\n", ret);
        }
        // Get YUV channel data
        // 获取一帧YUV数据，超时实际为2秒
        ret = DHOP_YUV_getFrame2(g_app_global.hYuv, &yuvFrame, 2000);
        if (DHOP_SUCCESS != ret)
        {
            DHOP_LOG_ERROR("Get YUV frame data fail with %#x\n", ret);
            // If the frame data cannot be obtained, pause for 100ms and try again
            usleep(100000);

            // If the number of consecutive times is less than 100, continue to try, otherwise end the task
            if (tryCnt < 100) {
                tryCnt++;
                continue;
            }
           // return;
        }
        tryCnt = 0;

        // AI detection
        // 将YUV送给AI模块进行处理，结果会填充到g_app_global中
        ret = app_ai_process(g_app_global.hNNX, &yuvFrame,&g_app_global);
        if(ret != DHOP_SUCCESS)
        {
            DHOP_LOG_ERROR("get result is failure\n");
        }

       
        printf("秒：%d\n",s);
        json_read(&config);
        

        //app_result_ztdraw(&config);
        // Draw OSD
        // 将结果在当前设备的视频预览界面中显示出来。
        printf("rubbish:%d; %d; %d; %d; %d; %d;%d; %d;\n ",config.x1,config.x2,config.x3,config.x4,config.y1,config.y2,config.y3,config.y4);
        printf("overflow:%d; %d; %d; %d; %d; %d;%d; %d;\n ",config.bx1,config.bx2,config.bx3,config.bx4,config.by1,config.by2,config.by3,config.by4);
        printf("overflow:%d; %d; %d; %d; %d; %d;%d; %d;\n ",config.px1,config.px2,config.px3,config.px4,config.py1,config.py2,config.py3,config.py4);
        app_result_draw(&config,&g_app_global);
        if (g_app_global.resultNum>0){
           
            for(int a = 0;a < g_app_global.resultNum ;a++) {
                 if (g_app_global.aiResult[a].rect.lt.x>g_app_global.aiResult[a].rect.rb.x){
                    int a0 = g_app_global.aiResult[a].rect.lt.x;
                    g_app_global.aiResult[a].rect.lt.x = g_app_global.aiResult[a].rect.rb.x;
                    g_app_global.aiResult[a].rect.rb.x = a0;
                }
                if (g_app_global.aiResult[a].rect.lt.y>g_app_global.aiResult[a].rect.rb.y){
                    int a1 = g_app_global.aiResult[a].rect.lt.y;
                    g_app_global.aiResult[a].rect.lt.y = g_app_global.aiResult[a].rect.rb.y;
                    g_app_global.aiResult[a].rect.rb.y = a1;
                } 

                printf("class:%d\t", g_app_global.aiResult[a].classId);
                printf("confidence:%f\n", g_app_global.aiResult[a].conf);
                printf("x1:%d\t ",g_app_global.aiResult[a].rect.lt.x);
                printf("y1:%d\t ",g_app_global.aiResult[a].rect.lt.y);
                printf("x2:%d \t",g_app_global.aiResult[a].rect.rb.x);
                printf("y2:%d\n",g_app_global.aiResult[a].rect.rb.y);
            }
        }

         //update
        /*if ((h==1)&&(n==1)){
            //printf("updateurl: %s\n", config.ugurl);
            char *updateurl = join(config.ugurl,config.hydeviceCode);
            http_uget(updateurl);
            sleep(20);
        }*/

        //printf("code: %s\n", config.hydeviceCode);
        //printf("wconf %f\n",wconf);
        //printf("%s\n",config.hydeviceCode);
        //printf("%d\n",config.rucout);

        //alarm 抓图
        printf("---------------------rubbish----------------------\n");
        //2 :rub 1 :over 4 :person 3 :bag 5 :worker
        //area of bag
        int overnum = 0;
        int rbagnum = 0;
        //LTNode* palist = ListInit();
        char ostr[1024]="";
        char rstr[1024]="";
        for (int i=0;i<g_app_global.resultNum;i++){
            if(g_app_global.aiResult[i].classId == 2){
                int bw = g_app_global.aiResult[i].rect.rb.x-g_app_global.aiResult[i].rect.lt.x;
                int bh = g_app_global.aiResult[i].rect.rb.y-g_app_global.aiResult[i].rect.lt.y;
                //ListPushBack(palist, bw*bh);
                //ListPushBack(palist, bw*bh);
                //log_write(m,"area",palist);
                //printf("area: %d\n", bw*bh);//4980000
                if((bw*bh>4980000)&&(g_app_global.aiResult[i].conf>pconf)){
                    overnum++;
                    char buffer[100];
                    char *b = "_";
                    char *a0 = itoa(g_app_global.aiResult[i].rect.lt.x);
                    sprintf(buffer, "%s%s", a0, b);
                    strcat(ostr,buffer);
                    char *a1 = itoa(g_app_global.aiResult[i].rect.lt.y);
                    sprintf(buffer, "%s%s", a1, b);
                    strcat(ostr,buffer);
                    char *a2 = itoa(g_app_global.aiResult[i].rect.rb.x);
                    sprintf(buffer, "%s%s", a2, b);
                    strcat(ostr,buffer);
                    char *a3 = itoa(g_app_global.aiResult[i].rect.rb.y);
                    sprintf(buffer, "%s%s", a3, b);
                    strcat(ostr,buffer);
                    char *a4 = fitoa(g_app_global.aiResult[i].conf);
                    sprintf(buffer, "%s%s", a4, b);
                    strcat(ostr,buffer);
                    printf("%s\n",ostr);
                }
            }
        }

       // rubbish
        int curnum = 0;
        LTNode* newrublist = ListInit();
        //if((s == 10)||(s==40)){ ||(g_app_global.aiResult[i].classId == 2)
        int timeflag = isTimeScale(config.rsh,config.rsm,config.reh,config.rem,h,m);
        //printf("timeflag: %d\n", timeflag);
        // num of rubbish
        if(timeflag==1){
            for (int i = 0; i < g_app_global.resultNum; i++) 
            {//&&g_app_global.aiResult[i].conf>0.4
                int rx = (g_app_global.aiResult[i].rect.lt.x+g_app_global.aiResult[i].rect.rb.x)/2;
                int ry = (g_app_global.aiResult[i].rect.lt.y+g_app_global.aiResult[i].rect.rb.y)/2;
                int rectflag = isPointInRect(rx*1920/8191,ry*1080/8191,config.x1,config.x2,config.x3,config.x4,config.y1,config.y2,config.y3,config.y4);
                //rectflag =1;
                printf("rectflag: %d\n", rectflag);
                printf("rucenter: (%d,%d)\n", rx,ry);
                printf("conf: %f \n", g_app_global.aiResult[i].conf);

                if (((g_app_global.aiResult[i].classId == 1)||(g_app_global.aiResult[i].classId == 2)||(g_app_global.aiResult[i].classId == 3)||(g_app_global.aiResult[i].classId == 5)||(g_app_global.aiResult[i].classId == 6)||(g_app_global.aiResult[i].classId == 7))&&(rectflag==1)&&(g_app_global.aiResult[i].conf>rconf))
                {
                    int excusive;
                    int pickplag;
                    for (int j = 0; j< g_app_global.resultNum; j++) {
                        if (g_app_global.aiResult[j].classId == 13){
                            excusive++;
                            int iou =IoU (g_app_global.aiResult[i].rect.lt.x,g_app_global.aiResult[i].rect.lt.y,g_app_global.aiResult[i].rect.rb.x, g_app_global.aiResult[i].rect.rb.y,g_app_global.aiResult[j].rect.lt.x,g_app_global.aiResult[j].rect.lt.y,g_app_global.aiResult[j].rect.rb.x, g_app_global.aiResult[j].rect.rb.y);
                            printf("IoU1: %d\n",iou);
                            if(iou>0){
                                pickplag++;
                            }
                        }else if (g_app_global.aiResult[j].classId == 11){
                            excusive++;
                            int iou =IoU (g_app_global.aiResult[i].rect.lt.x,g_app_global.aiResult[i].rect.lt.y,g_app_global.aiResult[i].rect.rb.x, g_app_global.aiResult[i].rect.rb.y,g_app_global.aiResult[j].rect.lt.x,g_app_global.aiResult[j].rect.lt.y,g_app_global.aiResult[j].rect.rb.x, g_app_global.aiResult[j].rect.rb.y);
                            printf("IoU2: %d\n",iou);
                            if(iou>0){
                                pickplag++;
                            }
                        }
                     }
                    if ((excusive==0)||((excusive>0)&&(pickplag==0))){
                        curnum++;
                     }
                }
            }
        }
        //printf("rubnum:%d\n", curnum);
        int brubnum = curnum+rbagnum;
        printf("rubnum:%d\n", brubnum);
        if (brubnum>0){
            rubbishcount++;
        }else{
            rubbishcount--;
        }
        printf("rubbishcount:%d\n", rubbishcount);
        if(rubbishcount<0){
            rubbishcount = 0;
        }else if(rubbishcount>30){
            rubbishcount = 30;
            printf("rubbishcount:%d\n", rubbishcount);
         }
        // match
        if((rubbishcount>20)&&(brubnum>0)){
            for (int i = 0; i < g_app_global.resultNum; i++) 
            {//&&g_app_global.aiResult[i].conf>0.4
                int rx = (g_app_global.aiResult[i].rect.lt.x+g_app_global.aiResult[i].rect.rb.x)/2;
                int ry = (g_app_global.aiResult[i].rect.lt.y+g_app_global.aiResult[i].rect.rb.y)/2;
                int rectflag = isPointInRect(rx*1920/8191,ry*1080/8191,config.x1,config.x2,config.x3,config.x4,config.y1,config.y2,config.y3,config.y4);
              //  printf("rectflag: %d\n", rectflag);
                //printf("rucenter: (%d,%d)\n", rx,ry);
                //printf("conf: %f \n", g_app_global.aiResult[i].conf);
                if (((g_app_global.aiResult[i].classId == 1)||(g_app_global.aiResult[i].classId == 2)||(g_app_global.aiResult[i].classId == 3)||(g_app_global.aiResult[i].classId == 5)||(g_app_global.aiResult[i].classId == 6)||(g_app_global.aiResult[i].classId == 7))&&(rectflag==1)&&(g_app_global.aiResult[i].conf>rconf))
                {
                    //info of obj
                    char buffer[100];
                    char *b = "_";
                    char *a0 = itoa(g_app_global.aiResult[i].rect.lt.x);
                    sprintf(buffer, "%s%s", a0, b);
                    strcat(rstr,buffer);
                    char *a1 = itoa(g_app_global.aiResult[i].rect.lt.y);
                    sprintf(buffer, "%s%s", a1, b);
                    strcat(rstr,buffer);
                    char *a2 = itoa(g_app_global.aiResult[i].rect.rb.x);
                    sprintf(buffer, "%s%s", a2, b);
                    strcat(rstr,buffer);
                    char *a3 = itoa(g_app_global.aiResult[i].rect.rb.y);
                    sprintf(buffer, "%s%s", a3, b);
                    strcat(rstr,buffer);
                    char *a4 = fitoa(g_app_global.aiResult[i].conf);
                    sprintf(buffer, "%s%s", a4, b);
                    strcat(rstr,buffer);
                    printf("%s\n",rstr);
                    //list of rub
                    ListPopFront(rulist);
                    ListPopFront(rulist);
                    ListPopFront(rulist);
                    ListPopFront(rulist);
                    ListPushBack(rulist, g_app_global.aiResult[i].rect.lt.x);
                   // printf("x1: %d\n", g_app_global.aiResult[i].rect.lt.x);
                    ListPushBack(rulist, g_app_global.aiResult[i].rect.lt.y);
                    ListPushBack(rulist, g_app_global.aiResult[i].rect.rb.x);
                    ListPushBack(rulist, g_app_global.aiResult[i].rect.rb.y);
                }
            }
            ListPrint(rulist);
            newrublist = ruinfomatch(rulist,maxnum-brubnum,brubnum,50);
            ListPrint(newrublist);
            int run =0;
            assert(newrublist);
            LTNode* curb = newrublist->next;
           // printf("%d\n", curb->data);
            while (curb != newrublist)
            {
                run++;
                curb = curb->next;
            } 
            //match of time
            ListPopFront(rtlist);
            ListPushBack(rtlist, totals);
            if (run>0){
                if(getptr(rtlist,2)->data-getptr(rtlist,1)->data > 20)
                {
                    ret = audio_play(100,"./voice/rub.pcm");
                     //文件名
                    int alarmtype = 1;
                    char *result4 = join("0_0", rstr);
                    char *result5 = join(result4, itoa(sec));
                    char *result6 = join(itoa(alarmtype), result5);
                    char *cfilename = join(result6, ".jpeg");
                    char *cmfile = join(itoa(sec), ".mp4");
                    //路径
                    char *filename = join(config.savepath, cfilename);
                    char *result0 =join(config.savepath,"1_");
                    char *result2 =join(result0,itoa(sec));
                    char *hfilename = join(result2, ".h264");
                    char *mfilename = join(result2, ".mp4");
        
                    app_coresult_snap(&g_app_global, &yuvFrame , filename,rstr);
                    DHOP_SMP_RealStreamModDemo(3,hfilename,mfilename);
                    coupload(config.url,filename,mfilename,hydeviceCode,config.rubbishtag,config.rubbishtip);
                    if (upload_type==1){
                        c_upload(hydeviceCode,alarmtype,sec,usec,filename,mfilename);
                    }
                    //log_write(m,"rubbish",rtlist);
                }
            }
        }

          //(m % config.oin == 0 )&& &&((s=39)||(s=40)||(s=41))

        int overtimeflag = isTimeScale(config.osh,config.osm,config.oeh,config.oem,h,m);
        //char ostr[100]="";
        printf("------------------------overflow----------------------------------------------\n");
        if (overtimeflag == 1){
            //overflow
            for (i = 0; i < g_app_global.resultNum; i++) {
                int bx = (g_app_global.aiResult[i].rect.lt.x+g_app_global.aiResult[i].rect.rb.x)/2;
                int by = (g_app_global.aiResult[i].rect.lt.y+g_app_global.aiResult[i].rect.rb.y)/2;
                int bagrectflag = isPointInRect(bx*1920/8191,by*1080/8191,config.px1,config.px2,config.px3,config.px4,config.py1,config.py2,config.py3,config.py4);
                //printf("bukeflag %d\n", bagrectflag);
                //printf("bukeflag %d\n", config.bx1);
                if (((g_app_global.aiResult[i].classId == 1)||(g_app_global.aiResult[i].classId == 2)||(g_app_global.aiResult[i].classId == 7)||(g_app_global.aiResult[i].classId == 3)||(g_app_global.aiResult[i].classId == 5)||(g_app_global.aiResult[i].classId == 6))&& (bagrectflag == 1)&&(g_app_global.aiResult[i].conf>pconf))

               // if ((g_app_global.aiResult[i].classId == 0)&&(g_app_global.aiResult[i].conf>pconf))
                {
                    overnum++;
                    char buffer[100];
                    char *b = "_";

                    char *a0 = itoa(g_app_global.aiResult[i].rect.lt.x);
                    sprintf(buffer, "%s%s", a0, b);
                    strcat(ostr,buffer);
                    char *a1 = itoa(g_app_global.aiResult[i].rect.lt.y);
                    sprintf(buffer, "%s%s", a1, b);
                    strcat(ostr,buffer);
                    char *a2 = itoa(g_app_global.aiResult[i].rect.rb.x);
                    sprintf(buffer, "%s%s", a2, b);
                    strcat(ostr,buffer);
                    char *a3 = itoa(g_app_global.aiResult[i].rect.rb.y);
                    sprintf(buffer, "%s%s", a3, b);
                    strcat(ostr,buffer);
                    char *a4 = fitoa(g_app_global.aiResult[i].conf);
                    sprintf(buffer, "%s%s", a4, b);
                    strcat(ostr,buffer);
                    printf("%s\n",ostr);
                }
            }
            int bukeflag = 5;
            for (i = 0; i < g_app_global.resultNum; i++) {
                if (g_app_global.aiResult[i].classId == 4){
                    bukeflag++;
                }
            }
            printf("overflag %d\n", overnum);
            printf("bukeflag %d\n", bukeflag);

            printf("-----------------------overflow----------------------------------------\n");
            if((overnum>0)&&(bukeflag>0)){
                overcount++;
            }else{
                overcount--;
            }
            printf("overcount %d\n", overcount);
            
            if(overcount>15){
                overcount=15;
            }else if(overcount<0){
                overcount=0;
            }

            if((overcount >10)&&(overnum>0)&&(bukeflag>0)){
                ListPopFront(otlist);
                ListPushBack(otlist, totals);
                ListPrint(otlist);
                printf("overcount %d\n", getptr(otlist,2)->data-getptr(otlist,1)->data);
                if(getptr(otlist,2)->data-getptr(otlist,1)->data > 15){
                    ret = audio_play(100,"./voice/over.pcm");
                     //文件名
                    int alarmtype = 2;
                    char *result4 = join("0_0", rstr);
                    char *result5 = join(result4, itoa(sec));
                    char *result6 = join(itoa(alarmtype), result5);
                    char *cfilename = join(result6, ".jpeg");
                    char *cmfile = join(itoa(sec), ".mp4");
                    //路径
                    char *filename = join(config.savepath, cfilename);
                    char *result0 =join(config.savepath,"2_");
                    char *result2 =join(result0,itoa(sec));
                    char *hfilename = join(result2, ".h264");
                    char *mfilename = join(result2, ".mp4");
                
                    app_coresult_snap(&g_app_global, &yuvFrame , filename,rstr);
                    DHOP_SMP_RealStreamModDemo(3,hfilename,mfilename);
                    coupload(config.url,filename,mfilename,hydeviceCode,config.overtag,config.overtip);
                    if (upload_type==1){
                        c_upload(hydeviceCode,alarmtype,sec,usec,filename,mfilename);
                    }
                }
            }
        }
                                                                                                                                                           
        printf("------------------worker----------\n");
        //worker
      int workflag = 0;
        for (i = 0; i < g_app_global.resultNum; i++) {
            if (((g_app_global.aiResult[i].classId == 8)||(g_app_global.aiResult[i].classId == 9))&&(g_app_global.aiResult[i].conf>wconf))
            {
                workflag++;
            }
        }
         /* int worktimeflag = isTimeScale(config.wsh,config.wsm,config.weh,config.wem,h,m);
        printf("miao: %d\n", s);
        //printf("worktimeflag %d\n", worktimeflag);
        if (worktimeflag==1){
        
        }*/
         
         if((n % config.win == 0 )&&(s==30)){
            if (workflag == 0){
                    //DHOP_SMP_RealStreamModDemo(&config, 5);
                //app_result_snap("worker_", &yuvFrame , &config,0);
                //DHOP_SMP_RealStreamdemon(&config, 5);
                printf("work");
                //app_coresult_snap("worker_", &yuvFrame , &config,5);
            }
        }
        //printf("workflag %d\n", workflag);
        printf("overflow:%d; %d; %d; %d; %d; %d;%d; %d;\n ",config.x1,config.x2,config.x3,config.x4,config.y1,config.y2,config.y3,config.y4);
        printf("overflow:%d; %d; %d; %d; %d; %d;%d; %d;\n ",config.px1,config.px2,config.px3,config.px4,config.py1,config.py2,config.py3,config.py4);
        printf("--------------------------person------------------------\n");
        //person
        LTNode* slist = ListInit();
        LTNode* newrulist = ListInit();
        char pstr[1000]="";
        //printf("px1 %d\n", config.px1);
        //list of person
        int personnum = 0;
        for (i = 0; i < g_app_global.resultNum; i++) {
            int px = (g_app_global.aiResult[i].rect.lt.x+g_app_global.aiResult[i].rect.rb.x)/2;
            int py = (g_app_global.aiResult[i].rect.lt.y+g_app_global.aiResult[i].rect.rb.y)/2;
            int perectflag = isPointInRect(px*1920/8191,py*1080/8191,config.x1,config.x2,config.x3,config.x4,config.y1,config.y2,config.y3,config.y4);
            printf("perectflag %d\n", perectflag);
            if ((g_app_global.aiResult[i].classId == 11)&&(perectflag==1)){
                //printf("center: (%d,%d)\n", px,py);
                personnum++;
                ListPushBack(slist, g_app_global.aiResult[i].rect.lt.x);
                //printf("x1: %d\n", g_app_global.aiResult[i].rect.lt.x);
                ListPushBack(slist, g_app_global.aiResult[i].rect.lt.y);
                ListPushBack(slist, g_app_global.aiResult[i].rect.rb.x);
                ListPushBack(slist, g_app_global.aiResult[i].rect.rb.y);
            }
        }
        ListPrint(slist);
        printf("personnum: %d\n",personnum);
        printf("overflow:%d; %d; %d; %d; %d; %d;%d; %d;\n ",config.bx1,config.bx2,config.bx3,config.bx4,config.by1,config.by2,config.by3,config.by4);
        //list of rubbish
        int rubnum = 0;
        int pertimeflag = isTimeScale(config.psh,config.psm,config.peh,config.pem,h,m);
        for (i = 0; i < g_app_global.resultNum; i++) {
            int prx = (g_app_global.aiResult[i].rect.lt.x+g_app_global.aiResult[i].rect.rb.x)/2;
            int pry = (g_app_global.aiResult[i].rect.lt.y+g_app_global.aiResult[i].rect.rb.y)/2;
            int prrectflag = isPointInRect(prx*1920/8191,pry*1080/8191,config.x1,config.x2,config.x3,config.x4,config.y1,config.y2,config.y3,config.y4);
             //DHOP_LOG_ERROR("prrectflag %d\n", prrectflag);
            int bx = (g_app_global.aiResult[i].rect.lt.x+g_app_global.aiResult[i].rect.rb.x)/2;
             int by = (g_app_global.aiResult[i].rect.lt.y+g_app_global.aiResult[i].rect.rb.y)/2;
             int bagrectflag = isPointInRect(bx*1920/8191,by*1080/8191,config.bx1,config.bx2,config.bx3,config.bx4,config.by1,config.by2,config.by3,config.by4);
            if (((g_app_global.aiResult[i].classId == 1)||(g_app_global.aiResult[i].classId == 2)||(g_app_global.aiResult[i].classId == 3)||(g_app_global.aiResult[i].classId == 5)||(g_app_global.aiResult[i].classId == 7)||(g_app_global.aiResult[i].classId == 6))&&(prrectflag==1)){
                //printf("center: (%d,%d)\n", prx,pry);
                rubnum++;
                ListPopFront(ruinfolist);
                ListPopFront(ruinfolist);
                ListPopFront(ruinfolist);
                ListPopFront(ruinfolist);
                ListPushBack(ruinfolist, g_app_global.aiResult[i].rect.lt.x);
                //printf("x1: %d\n", g_app_global.aiResult[i].rect.lt.x);
                ListPushBack(ruinfolist, g_app_global.aiResult[i].rect.lt.y);
                ListPushBack(ruinfolist, g_app_global.aiResult[i].rect.rb.x);
                ListPushBack(ruinfolist, g_app_global.aiResult[i].rect.rb.y);
            }
        }
    
        int run =0;
        if (rubnum>0){
            ListPrint(ruinfolist);
            newrulist = ruinfomatch(ruinfolist,maxnum - rubnum,rubnum,50);
            ListPrint(newrulist);
            assert(newrulist);
            LTNode* curb = newrulist->next;
            //printf("%d\n", curb->data);
            while (curb != newrulist)
            {
                run++;
                curb = curb->next;
            }
        }

        int nrubnum = run/4;
        printf("nrubnum: %d\n",nrubnum);
        int personcross = 0;
        if ((nrubnum>0)&&(personnum>0)){
            //ret = audio_play(100,"./person.pcm");
            for(int i = 0;i<4*nrubnum;i+=4){
                Point rul;
                rul.x= getptr(newrulist,i+1)->data;
                //printf("x1: %d\n", rul.x);
                rul.y= getptr(newrulist,i+2)->data;
                //printf("y1: %d\n", rul.y);
                Point rur;
                rur.x= getptr(newrulist,i+3)->data;
                rur.y= getptr(newrulist,i+4)->data;
                Rect rr;
                rr.lr=rur;
                rr.ul=rul;
                //printf("y1: %d\n", rr.ul.y);
                printf("personnum: %d\n",personnum);
                for(int j = 0;j<4*personnum;j+=4){
                    //printf("personnum: %d\n",personnum);
                    Point pel;
                    pel.x=getptr(slist,j+1)->data;
                    //printf("x1: %d\n", pel.x);
                    pel.y=getptr(slist,j+2)->data;
                    Point per;
                    per.x=getptr(slist,j+3)->data;
                    per.y=getptr(slist,j+4)->data;
                    Rect pr;
                    pr.ul=pel;
                    pr.lr=per;
                    int crossflag = RectInRect(pr,rr);
                    if (crossflag == 1){
                       // ret = audio_play(100,"./person.pcm");
                        char buffer[100];
                        char *b = "_";

                        char *a0 = itoa(rr.ul.x);
                        sprintf(buffer, "%s%s", a0, b);
                        strcat(pstr,buffer);
                        char *a1 = itoa(rr.ul.y);
                        sprintf(buffer, "%s%s", a1, b);
                        strcat(pstr,buffer);
                        char *a2 = itoa(rr.lr.x);
                        sprintf(buffer, "%s%s", a2, b);
                        strcat(pstr,buffer);
                        char *a3 = itoa(rr.lr.y);
                        sprintf(buffer, "%s%s", a3, b);
                        strcat(pstr,buffer);
                        char *a4 = fitoa(0.565865);
                        sprintf(buffer, "%s%s", a4, b);
                        strcat(pstr,buffer);
                        printf("%s\n",pstr);
                        char *a5 = itoa(pr.ul.x);
                        sprintf(buffer, "%s%s", a5, b);
                        strcat(pstr,buffer);
                        char *a6 = itoa(pr.ul.y);
                        sprintf(buffer, "%s%s", a6, b);
                        strcat(pstr,buffer);
                        char *a7 = itoa(pr.lr.x);
                        sprintf(buffer, "%s%s", a7, b);
                        strcat(pstr,buffer);
                        char *a8 = itoa(pr.lr.y);
                        sprintf(buffer, "%s%s", a8, b);
                        strcat(pstr,buffer);
                        char *a9 = fitoa(0.565865);
                        sprintf(buffer, "%s%s", a9, b);
                        strcat(pstr,buffer);
                        printf("%s\n",pstr);

                        ListPopFront(prlist);
                        ListPushBack(prlist, totals);
                        ListPrint(prlist);
                        //printf("frame time: %d\n",getptr(prlist,2)->data-getptr(prlist,1)->data);
                        //printf("two frame time: %d\n",getptr(prlist,2)->data);
                        //printf("one frame time: %d\n",getptr(prlist,1)->data);
                        if(getptr(prlist,2)->data-getptr(prlist,1)->data >10){
                            ret = audio_play(100,"./person.pcm");
                            //app_result_snap(pstr, &yuvFrame , &config,4);
                            //app_coresult_snap(pstr, &yuvFrame , &config,4);
                            //DHOP_SMP_RealStreamModDemo(&config, 4);
                           // log_write(m,"person",prlist);
                           printf("person");
                        }
                    }
                }
            }
        }
        ListDestory(slist);
        slist = NULL;  //需要我们手动改变plist
        ListDestory(newrulist);
        newrulist = NULL;  //需要我们手动改变plist
      
        printf("------------------------------------bag----------------------------------------\n");
        //bag
        char bstr[1024]="";
        int bagtimeflag = isTimeScale(config.bsh,config.bsm,config.beh,config.bem,h,m);
        int allpersonnum = 0;
        for (i = 0; i < g_app_global.resultNum; i++) {
            if ((g_app_global.aiResult[i].classId == 11)||(g_app_global.aiResult[i].classId == 4)){
                allpersonnum++;
            }
        }
        int bagnum=0;
        int armnum = 0;
        if((allpersonnum>0)&&(bagtimeflag==1)){
            for (i = 0; i < g_app_global.resultNum; i++) {
                int bx = (g_app_global.aiResult[i].rect.lt.x+g_app_global.aiResult[i].rect.rb.x)/2;
                int by = (g_app_global.aiResult[i].rect.lt.y+g_app_global.aiResult[i].rect.rb.y)/2;
                int bagrectflag = isPointInRect(bx*1920/8191,by*1080/8191,config.bx1,config.bx2,config.bx3,config.bx4,config.by1,config.by2,config.by3,config.by4);
                if((bagrectflag==1)&&(g_app_global.aiResult[i].classId==2)){
                     bagnum++;
                     ListPopFront(blist);
                    ListPushBack(blist, totals);
                    ListPopFront(blist);
                    ListPushBack(blist, 2);
                   
                }else if ((bagrectflag==1)&&(g_app_global.aiResult[i].classId==13))
                {
                    armnum++;
                    ListPopFront(blist);
                    ListPushBack(blist, totals);
                    ListPopFront(blist);
                    ListPushBack(blist, 3);
                } else{
                    armnum++;
                    ListPopFront(blist);
                    ListPushBack(blist, 0);
                    ListPopFront(blist);
                    ListPushBack(blist, 1);
                }
            }
        }
        if (bagnum>0){
            audio_flag = 1;
            //ret = audio_play(100,"./voice/bag.pcm");
            //文件名
            int alarmtype = 4;
            char *result4 = join("0_0", rstr);
            char *result5 = join(result4, itoa(sec));
            char *result6 = join(itoa(alarmtype), result5);
            char *cfilename = join(result6, ".jpeg");
            char *cmfile = join(itoa(sec), ".mp4");
            //路径
            char *filename = join(config.savepath, cfilename);
            char *result0 =join(config.savepath,"4_");
            char *result2 =join(result0,itoa(sec));
            char *hfilename = join(result2, ".h264");
            char *mfilename = join(result2, ".mp4");

            app_result_snap(&g_app_global, &yuvFrame , filename);
            DHOP_SMP_RealStreamModDemo(5,hfilename,mfilename);
            coupload(config.url,filename,mfilename,hydeviceCode,config.bagtag,config.bagtip);
            if (upload_type==1){
                c_upload(hydeviceCode,alarmtype,sec,usec,filename,mfilename);
            }
        }

        printf("-------------------------------------bag----------------------------------\n");
        ListPrint(blist);
        int framenum = 0;
        int armframenum = 0;
        int s1 = getptr(blist,framen*2-1-1)->data;
        int s2 = getptr(blist,framen*2-1-3)->data;
        int s3 = getptr(blist,framen*2-1-5)->data;
        int r1 = getptr(blist,2)->data;
        int r2 = getptr(blist,4)->data;
        int r3 = getptr(blist,6)->data;

        printf("timeframe:%d; %d; %d; %d; %d; %d;\n ",s1,s2,s3,r1,r2,r3);

        /*if((s1== 1)&&(s2 == 1)&&(r1 == 1)&&(r2 == 1)&&(r3 == 1)){
            if(Max(blist) == 1 ){
                printf("%s\n","nobag");
            }else{
                for (int i  = 1;i< framen-2;i++){
                    if((getptr(blist,i)->data == Max(blist))||(getptr(blist,i)->data == Max(blist)-1)||(getptr(blist,i)->data == Max(blist)-2)){
                        framenum++;
                    }
                }
            }
        } */
        if((s1== 1)&&(s2 == 1)&&(r1 == 1)&&(r2 == 1)&&(r3 == 1)){

            if(Max(blist) == 1 ){
                printf("%s\n","nobag");
            }else{
                for (int i  = 1;i< framen;i++){
                    if((getptr(blist,i)->data == 2)&&(totals==getptr(blist,i-1)->data)){
                        framenum++;
                    }else if (getptr(blist,i)->data == 3)
                    {
                        armframenum++;
                    }
                }
            }
        } 

        printf("num of bag frame: %d//%d//%d//%d\n", framenum,totals,Max(blist),totals-Max(blist));

        

        //||(framenum==2)) &&(bagnum>0)||(framenum==2)||(framenum==3)&&(s3 == 1)&&(r3 == 1)&&(s3 == 1)&&((totals-Max(blist))==0)
        if((framenum==1)&&(armframenum==0)){
            //log_write(framen,"bag",blist);
            //config.upload =1;
            printf("%s\n","bag");
            /*audio_flag = 1;
           // ret = audio_play(100,"./bag.pcm");
            app_result_snap(&g_app_global, &yuvFrame , &config,0,bstr);;//编解码图片不发送
            DHOP_SMP_RealStreamModDemo(&config, 4);//编解码视频并发送
            //DHOP_SMP_RealStreamdemon(&config, 3); */
        }

         printf("-------------------------------------doublebag----------------------------------\n");
        
        //person:1 bag :2 over:3
        if((allpersonnum>0)&&(bagtimeflag==1)){
            for (i = 0; i < g_app_global.resultNum; i++) {
                int bx = (g_app_global.aiResult[i].rect.lt.x+g_app_global.aiResult[i].rect.rb.x)/2;
                int by = (g_app_global.aiResult[i].rect.lt.y+g_app_global.aiResult[i].rect.rb.y)/2;
                int bagrectflag = isPointInRect(bx*1920/8191,by*1080/8191,config.bx1,config.bx2,config.bx3,config.bx4,config.by1,config.by2,config.by3,config.by4);
                int obrectflag = isPointInRect(bx*1920/8191,by*1080/8191,config.px1,config.px2,config.px3,config.px4,config.py1,config.py2,config.py3,config.py4);

                if((bagrectflag==1)&&((g_app_global.aiResult[i].classId==2)||(g_app_global.aiResult[i].classId==13)||(g_app_global.aiResult[i].classId==1)||(g_app_global.aiResult[i].classId==3)||(g_app_global.aiResult[i].classId==5)||(g_app_global.aiResult[i].classId==6)||(g_app_global.aiResult[i].classId==7))){
                    ListPopFront(dblist);
                    ListPushBack(dblist, totals);
                    ListPopFront(dblist);
                    ListPushBack(dblist, 2);

                } else if ((obrectflag==1)&&((g_app_global.aiResult[i].classId==2)||(g_app_global.aiResult[i].classId==13)||(g_app_global.aiResult[i].classId==1)||(g_app_global.aiResult[i].classId==3)||(g_app_global.aiResult[i].classId==5)||(g_app_global.aiResult[i].classId==6)||(g_app_global.aiResult[i].classId==7))){
                     ListPopFront(dblist);
                     ListPushBack(dblist, totals);
                     ListPopFront(dblist);
                     ListPushBack(dblist, 3);
                }else{
                    ListPopFront(dblist);
                    ListPushBack(dblist, 0);
                    ListPopFront(dblist);
                    ListPushBack(dblist, 1);
                }
            }
        }
        ListPrint(dblist);

        int bagframenum = 0;
        int overframenum = 0;
        int s10 = getptr(dblist,framen*2-1-1)->data;
        int s20= getptr(dblist,framen*2-1-3)->data;
        int s30 = getptr(dblist,framen*2-1-5)->data;
        int r10 = getptr(dblist,2)->data;
        int r20 = getptr(dblist,4)->data;
        int r30 = getptr(dblist,6)->data;

        printf("timeframe:%d; %d; %d; %d; %d; %d;\n ",s10,s20,s30,r10,r20,r30);
        if((s10== 1)&&(s20 == 1)&&(r10 == 1)&&(r20 == 1)&&(r30 == 1)){
             if(Max(dblist) == 1 ){
                printf("%s\n","nobag");
            }else{
                for (int i  = 1;i< framen;i++){
                    if((getptr(blist,i)->data == 2)&&(totals-getptr(blist,i-1)->data<3)){
                        bagframenum++;
                    }else if ((getptr(blist,i)->data == 3)&&(totals-getptr(blist,i-1)->data<3))
                    {
                        overframenum++;
                    }
                }
            }
        }
        
        ret = DHOP_YUV_releaseFrame2(g_app_global.hYuv, &yuvFrame);
        if(DHOP_SUCCESS != ret) {
            DHOP_LOG_ERROR("Release YUV frame data fail with %#x\n", ret);
        }
        /*DHOP_SYS_UtcTime pUtcTime0;
        ret = DHOP_SYS_getUtcTime(&pUtcTime0);
        g_app_global.sec = pUtcTime0.sec;
        int hmiao1 = pUtcTime0.sec*1000+pUtcTime0.msec;
        printf("time of one frame %d\n", hmiao1-hmiao0);*/

    }
    //return DHOP_SUCCESS;
}

/*
int dataCallback(DHOP_WEB_Point* pointArray, int n)
{
    for (int i = 0; i < n; i++)
    {
        DHOP_LOG_INFO("DHOP_WEB_Point index:%d is [%d,%d]\n", i, pointArray[i].x, pointArray[i].y);
    }
}*/

int dataCallback(char *buffer)
{
     printf("s: %s\n", buffer);
     //wstr=buffer;


}
// APP退出（web界面上可以点击停止按钮时）
DH_Void app_exit_callback()
{
    // 逐个模块进行注销
    DHOP_LOG_INFO("app-%d will exit\n", getpid());

    /*DHOP_HTTP_offline();

    app_net_deinit();

    app_enc_deinit();

    app_yuv_deinit();

    app_ai_deinit();

    object_ot_deinit();*/

    // 最后调用DHOP_SYS_deInit
    DHOP_SYS_deInit();
}

void app_init(){

    int ret = sdload();//sd
    ret = my_copy();
    config_read(&config);//默认参数

    printf("rub:%d; %d; %d; %d; %d; %d;%d; %d;\n ",config.x1,config.x2,config.x3,config.x4,config.y1,config.y2,config.y3,config.y4);
    printf("overflow:%d; %d; %d; %d; %d; %d;%d; %d;\n ",config.bx1,config.bx2,config.bx3,config.bx4,config.by1,config.by2,config.by3,config.by4);
    printf("bag:%d; %d; %d; %d; %d; %d;%d; %d;\n ",config.px1,config.px1,config.px3,config.px4,config.py1,config.py2,config.py3,config.py4);
    DHOP_SYS_DevInfo pDevInfo;
    ret=DHOP_SYS_getDevInfo(&pDevInfo);
    printf("s/n: %s\n", pDevInfo.serial);

    char *hydeviceCode = (char*)pDevInfo.serial;

    //算法配置
    /*printf("url: %s\n",config.cgurl);
    char *url =  join(config.cgurl,hydeviceCode);
    printf("url: %s\n",url);
    
    config_get(url);
    config_parse(&config);
    printf("rub:%d; %d; %d; %d; %d; %d;%d; %d;\n ",config.x1,config.x2,config.x3,config.x4,config.y1,config.y2,config.y3,config.y4);
    printf("overflow:%d; %d; %d; %d; %d; %d;%d; %d;\n ",config.bx1,config.bx2,config.bx3,config.bx4,config.by1,config.by2,config.by3,config.by4);
    printf("bag:%d; %d; %d; %d; %d; %d;%d; %d;\n ",config.px1,config.px1,config.px3,config.px4,config.py1,config.py2,config.py3,config.py4);
    printf("s/n: %s\n",hydeviceCode);*/

    DHOP_APP_ConfigParam configPrm;
    memset(&configPrm, 0, sizeof(configPrm));
    configPrm.watchdog = 1; /// enable watchdog
    configPrm.weburl = "index.html";
    configPrm.urllen = strlen("index.html");
    configPrm. previewUrl = "previewIndex.html";
    DHOP_APP_setConfig (&configPrm);

    
   
}

int main(void)
{
    DH_Int32                    ret = -1;
    DH_Char                     webUrl[32] = "index.html";
    DHOP_SYS_InitParam          initParam;
    DHOP_APP_ConfigParam        appCfg;
    DHOP_HTTP_AppDefinition     webApp;
  
    /*
    APP起来，如果要调用DHOP-SDK的API，那么必须先执行DHOP_SYS_init接口，这里会注册APP退出时需要执行的callback。
    */
    memset(&initParam, 0, sizeof(initParam));
    initParam.onExitCallback = app_exit_callback;
    initParam.version = DHOP_SDK_VERSION;
    ret = DHOP_SYS_init(&initParam);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("DHOP_SYS_init fail with %#x\n", ret);
        return DHOP_FAILED;
    }
    /*
    打印输出初始化成功
    */
    DHOP_LOG_INFO("DHOP_SYS_init suscess!\n");
    /*
    注册SIGPIPE信号，这个信号主要是socket在send接口中，如果网络断开，操作系统会发出SIGPIPE，导致进程退出。
    这里将这个信号忽略掉。
    */
    signal(SIGPIPE, SIG_IGN);
 
    // 设置LOG输出等级
    DHOP_LOG_setLevel((DHOP_LOG_Level)g_app_config.log_level, DHOP_LOG_DEST_WEB);
    DHOP_LOG_setLevel((DHOP_LOG_Level)g_app_config.log_level, DHOP_LOG_DEST_TTY);
    DHOP_LOG_setLevel((DHOP_LOG_Level)g_app_config.log_level, DHOP_LOG_DEST_FILE);
    DHOP_LOG_setLevel(DHOP_LOG_LEVEL_DEBUG, DHOP_LOG_DEST_WEB);

    // AI算法初始化
    ret = app_ai_init(&g_app_global);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("app_ai_init fail with %#x\n", ret);
        goto err1;
    }

    // YUV模块初始化，打开需要的YUV通道
    ret = app_yuv_init(&g_app_global);

    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("app_yuv_init fail with %#x\n", ret);
       // goto err2;
    }
    
    // 编码模块初始化，创建号编码(YUV->JPEG)
    ret = app_enc_init(&g_app_global);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("app_enc_init fail with %#x\n", ret);
        //goto err3;
    }
    //读取配置信息
    app_init();
    ret = DHOP_WEB_init(dataCallback);//web

    // 开始允许AI处理任务
    //encrypt_alg();
    //app_ai_task();
    pthread_mutex_t mutex;
    pthread_cond_t empty ,full;
    pthread_t pro,con;

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&full,NULL);
    pthread_cond_init(&empty , NULL);
    pthread_create(&pro,NULL,app_ai_task,NULL);
    pthread_create(&con,NULL,audio_bag,NULL);//音视频分两个线程进行处理
    pthread_join(pro,NULL);
    pthread_join(con,NULL);

    /*if (g_app_global.auth==0){
        app_ai_task();
    }*/
    return 0;

/*err6:
    DHOP_HTTP_offline();
err5:
    app_net_deinit();
err4:
    app_enc_deinit();
err3:
    app_yuv_deinit();
err2:
    app_ai_deinit();*/
err1:
    //object_ot_deinit();
    DHOP_SYS_deInit();

    return -1;
}
