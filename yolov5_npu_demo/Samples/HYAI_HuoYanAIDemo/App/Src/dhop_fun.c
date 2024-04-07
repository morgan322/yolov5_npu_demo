#include  "dhop_fun.h"




//dhop
void update_http(char * url)
{
    // 远程升级url, 支持http
    //char tmp[] = "https://huoyan-smoke.oss-cn-beijing.aliyuncs.com/hyboot/AIDemo_Rubbish_0.1.1_20221117.bin";

    // 升级参数
    DHOP_APP_UpdateParam info;
    memset(&info, 0, sizeof(DHOP_APP_UpdateParam));
    info.type = DHOP_APP_URL_TYPE_APPPKG; /// 升级的类型
    info.url = url; /// 升级的文件地址

    // 升级(异步接口, 调用成功只代表参数下发成功，不代表升级成功)
    int ret = DHOP_APP_updateByURL(&info);
    if (ret != 0)
    {
        printf("DHOP_APP_updateByURL failed %d \n", ret);
    }
	else
	{
		printf("DHOP_APP_updateByURL success \n");
	}
}

static pthread_mutex_t gMutex = PTHREAD_MUTEX_INITIALIZER;
static bool gSdCard = false;
static char gSdCardPath[DHOP_STORAGE_NAME_MAX_LEN] = {0,};

DH_Void exitFunc(DH_Void)
{
    return;
}

DH_Int32 statusCallback(const DHOP_STORAGE_NotifyState *pNotify)
{
    int ret = DHOP_FAILED;
    DHOP_STORAGE_DevInfo devInfo;

    //Only processing SD card status in this example.
    if(DHOP_STORAGE_SD_CARD == pNotify->mediaType)
    {
        if(DHOP_STORAGE_STATUS_LOAD == pNotify->statusType)
        {
            //The SD card is inserted and loaded by the device successfully, mount SD card to app.
            ret = DHOP_STORAGE_mount(pNotify->devName);
            if(DHOP_SUCCESS != ret)
            {
                printf("mount sd card %s fail with %#x\n", pNotify->devName, ret);
                return ret;
            }

            //The SD card is successfully mounted to the app, get the accessible mounting path in the app.
            ret = DHOP_STORAGE_getDevInfo(pNotify->devName, &devInfo);
            if(DHOP_SUCCESS != ret)
            {
                printf("get sd card %s info fail with %#x\n", pNotify->devName, ret);
                return ret;
            }

            //Update SD card status information in app.
            pthread_mutex_lock(&gMutex);
            gSdCard = true;
            memcpy(gSdCardPath, devInfo.partition[0].mountDir, strlen(devInfo.partition[0].mountDir));
            pthread_mutex_unlock(&gMutex);
        }

        if(DHOP_STORAGE_STATUS_UNLOAD == pNotify->statusType)
        {
            //SD card is pulled out, Update SD card status information in app.
            //After the SD card is pulled out, it will be automatically umount from app.
            pthread_mutex_lock(&gMutex);
            gSdCard = false;
            memset(gSdCardPath, 0, sizeof(gSdCardPath)/sizeof(gSdCardPath[0]));
            pthread_mutex_unlock(&gMutex);
        }
    }

    return 0;
}


static bool isSdCardOk(void)
{
    bool status;
    pthread_mutex_lock(&gMutex);
    status = gSdCard;
    pthread_mutex_unlock(&gMutex);
    return status;
}


static void storeLog2Sd(const char *pMountPath)
{
    DH_Char logPath[128] = {0,};
    DH_Char logInfo[128] = {0,};
    FILE *fp = NULL;
    time_t times;
    struct tm *pTime = NULL;

    snprintf(logPath, sizeof(logPath) - 1, "%s/test.log", pMountPath);
    fp = fopen((const char *)logPath, "a+");
    if(NULL == fp)
    {
        //printf("open %s fail with %d\n", logPath, errno);
        return;
    }
    
    fseek(fp, 0, SEEK_END);
    
    time(&times);
    pTime = gmtime(&times);
    snprintf(logInfo, sizeof(logInfo) - 1, "%d-%d-%d %d:%d:%d hello_world!!!\n",
            1900 + pTime->tm_year, 1 + pTime->tm_mon, pTime->tm_mday,
            pTime->tm_hour, pTime->tm_min, pTime->tm_sec);


    fwrite(logInfo, 1, strlen(logInfo), fp);
    fclose(fp);
    return;
}

int sdload(){
   int ret;
    DHOP_SYS_InitParam sysInit;
    DHOP_STORAGE_Dev storageDevList[8];
    DH_Uint32 devNum  = 0;
    DHOP_STORAGE_DevInfo storageDevInfo;
    storageDevInfo.cbSize = sizeof(storageDevInfo);
  

    /*
    memset(&sysInit, 0, sizeof(sysInit));
    sysInit.version = DHOP_SDK_VERSION;
    sysInit.onExitCallback = exitFunc;*/

    /*ret = DHOP_SYS_init(&sysInit);
    if(DHOP_SUCCESS != ret)
    {
        printf("DHOP_SYS_init fail with %#x\n", ret);
        return ret;
    }*/

    //1.Get the list of external storage devices that are ready at this time.
    devNum = sizeof(storageDevList)/sizeof(storageDevList[0]);
    for(int i=0;i<devNum;i++)
    {
        storageDevList[i].cbSize=sizeof(DHOP_STORAGE_Dev);
    }
    ret = DHOP_STORAGE_getDevList(DHOP_STORAGE_EXTDEV, storageDevList, &devNum);
    if(DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("DHOP_STORAGE_getDevList fail with %#x\n", ret);
        return ret;
    }
	DHOP_LOG_INFO("DHOP_STORAGE_getDevList success\n");
	
    //2.Query the ready external storage device information in turn.
    for(int i = 0; i < devNum; i++)
    {
        ret = DHOP_STORAGE_getDevInfo(storageDevList[i].devName, &storageDevInfo);
        if(DHOP_SUCCESS != ret)
        {
            DHOP_LOG_ERROR("get storage device %s information fail with %#x\n", storageDevList[i].devName, ret);
            continue;
        }

        if(DHOP_STORAGE_SD_CARD == storageDevInfo.mediaType)
        {
            //The SD card has been loaded successfully on device, mount it to make it available within the app.
            ret = DHOP_STORAGE_mount(storageDevInfo.devName);
            if(DHOP_SUCCESS != ret)
            {
                DHOP_LOG_ERROR("mount sd card %s fail with %#x\n", storageDevInfo.devName, ret);
                continue;
            }

            //Mount to app successfully, get the accessible mount path.
            ret = DHOP_STORAGE_getDevInfo(storageDevList[i].devName, &storageDevInfo);
            if(DHOP_SUCCESS != ret)
            {
                DHOP_LOG_ERROR("get storage device %s information fail with %#x\n", storageDevInfo.devName, ret);
                continue;
            }

            //Update SD card status information in app.
            memcpy(gSdCardPath, storageDevInfo.partition[0].mountDir, strlen(storageDevInfo.partition[0].mountDir));
            gSdCard = true;
            break;
        }
    }
	DHOP_LOG_INFO("DHOP_STORAGE_getDevInfo success\n");
	
    //3.Start listen SD card status, and register event callback function.
    ret = DHOP_STORAGE_startListenStatus(DHOP_STORAGE_SD_CARD, statusCallback);
    if(DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("DHOP_STORAGE_startListenStatus fail with %#x\n", ret);
        return ret;
    }
	DHOP_LOG_INFO("DHOP_STORAGE_startListenStatus\n");

    return 0;
}



// audio_play
void exitCbFunc(void)
{
    DHOP_LOG_ERROR("process-%d will exit\n", getpid());
    return;
}

int min(int a,int b)
{
	return a>b?b:a;
}

int audio_play(int volu,char* audiopath)
{
	int ret = -1;
	/*DHOP_SYS_InitParam initParam;

    initParam.onExitCallback = exitCbFunc;
	initParam.version = DHOP_SDK_VERSION;
	ret = DHOP_SYS_init(&initParam);*/


	/*if(0 != ret)
	{
		printf("DHOP_SYS_init fail\n");
		return -1;
	}
	*/
	DHOP_LOG_setLevel(DHOP_LOG_LEVEL_DEBUG, DHOP_LOG_DEST_WEB);
	DHOP_LOG_INFO("DHOP_SYS_init suscess!");

	/// 获取音频通道数
	DH_Uint32 num=0;
	ret= DHOP_AUDOUT_getChnNum(&num);
	if(0 != ret)
	{
		printf("DHOP_AUDOUT_getChnNum fail for %d\n",ret);
		return -1;
	}
	DHOP_LOG_INFO("DHOP_AUDOUT_getChnNum get audio num is %d\n",num);

	/// 获取通道能力
	DH_Uint32 arraySize=32;
	DHOP_AUDOUT_Capability caps[32];
	memset(&caps,0,sizeof(DHOP_AUDOUT_Capability) * 32);
	for(int i=0;i<32;i++)
	{
		caps[i].cbSize=sizeof(DHOP_AUDOUT_Capability);
	}
	ret=DHOP_AUDOUT_getChnCaps(0,caps,&arraySize);
	if(0 != ret)
	{
		printf("DHOP_AUDOUT_getChnCaps fail for %d\n",ret);
		return -1;
	}
	
	/// 检查能力是否满足自己的要求
	for(int i=0;i<arraySize;i++)
	{
		DHOP_LOG_INFO("--------------audio_play----------------------------------------------------\n");
		//DHOP_LOG_INFO("DHOP_AUDOUT_getChnCaps format is %d\n",caps[i].format);
		//DHOP_LOG_INFO("DHOP_AUDOUT_getChnCaps depth is %d\n",caps[i].depth);
		//DHOP_LOG_INFO("DHOP_AUDOUT_getChnCaps frequency is %d\n",caps[i].frequency);
		//DHOP_LOG_INFO("**********************************************************************\n");
	}
	
	/// 读取音频文件
	struct stat  fileInfo;
	memset(&fileInfo,0,sizeof(fileInfo));
	stat(audiopath,&fileInfo);
	
	DHOP_LOG_INFO("file size is %f\n",(float)fileInfo.st_size);
	
	int fd=open(audiopath,O_RDONLY);
	if(fd==-1)
	{
		DHOP_LOG_ERROR("open file failed\n");
		perror("open");
		return -1;
	}
	DHOP_LOG_INFO("open file success\n");
	char *readBuf=(char*)malloc(fileInfo.st_size);
	 ssize_t readSize = read(fd,readBuf,fileInfo.st_size);
	DHOP_LOG_INFO("read file size is %d\n",(int)readSize);
	
	if(readSize!=fileInfo.st_size)
	{
		DHOP_LOG_ERROR("readFile not finished\n");
		close(fd);
		free(readBuf);
		return -1;
	}
	close(fd);	

	/// 循环播放音频文件
	//while(1)
	//{
    /// 创建音频播放handler
    DHOP_AUDOUT_CreateParam creatParam;
    DH_Handle audioHandle;
    memset(&creatParam,0,sizeof(DHOP_AUDOUT_CreateParam));
    creatParam.cbSize = sizeof(DHOP_AUDOUT_CreateParam);
    /// 具体播放参数和实际音频文件保持一致
    creatParam.format=0;
    creatParam.depth=1;
    creatParam.frequency=8000;
    creatParam.channel=0;
    ret=DHOP_AUDOUT_create(&creatParam,&audioHandle);
    if(0 != ret)
    {
        DHOP_LOG_ERROR("DHOP_AUDOUT_CreateParam fail for %d\n",ret);
        free(readBuf);
        return -1;
    }
    //DHOP_LOG_INFO("DHOP_AUDOUT_CreateParam success\n");
    
    /// 设置音频播放音量
    DH_Uint32 volume=volu;
    ret=DHOP_AUDOUT_setVolume(audioHandle,volume);
    if(0 != ret)
    {
        DHOP_LOG_ERROR("DHOP_AUDOUT_setVolume fail for %d\n",ret);
        free(readBuf);
        DHOP_AUDOUT_destroy(audioHandle);
        return -1;
    }
    //DHOP_LOG_INFO("DHOP_AUDOUT_setVolume success\n");
    
    /// 分块送入待播放的音频数据
    int putPos = 0;
    while (putPos < readSize)
    {
        int piece = 8192;
        piece=min(readSize-putPos,8192);
        ret=DHOP_AUDOUT_putData(audioHandle,readBuf + putPos, piece);
        if(0 != ret)
        {
            DHOP_LOG_ERROR("DHOP_AUDOUT_putData fail for %d\n",ret);
            free(readBuf);
            DHOP_AUDOUT_destroy(audioHandle);
            return -1;
        }
        putPos += piece;
        DHOP_LOG_INFO("DHOP_AUDOUT_putData success\n");
    }

    /// 检查是否播放完成
    DH_Uint32 status =0;
    while(1)
    {
        ret =DHOP_AUDOUT_getStatus(audioHandle,&status);
        if(0 != ret)
        {
            DHOP_LOG_ERROR("DHOP_AUDOUT_getStatus fail for %d\n",ret);
            free(readBuf);
            DHOP_AUDOUT_destroy(audioHandle);
            return -1;
        }
        if(status == DHOP_AUDOUT_STATUS_END)
        {
            /// 播放完成
            break;
        }
        usleep(50000);
    }

    /// 播放完成,销毁播放句柄
    DHOP_AUDOUT_destroy(audioHandle);

    /// 5秒后重复播放
    //sleep(5);
    DHOP_LOG_ERROR("audio play end this time\n");
}
//}

void upload(const char* url, char* filename,const char* Id,const char* tag,const char* tip){

     CURL *curl = curl_easy_init();
     curl_easy_setopt(curl, CURLOPT_URL, url);

     // 添加配置表单
     curl_mime *multipart = curl_mime_init(curl);
     curl_mimepart *part = curl_mime_addpart(multipart);
     curl_mime_name(part, "deviceCode");
     curl_mime_data(part, Id, CURL_ZERO_TERMINATED);

     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "eventTag");
     curl_mime_data(part, tag, CURL_ZERO_TERMINATED);

     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "eventTip");
     curl_mime_data(part, tip, CURL_ZERO_TERMINATED);
     /*
     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "content");
     curl_mime_data(part, "{"check_address":"shenzhen","type":"xxx","number":"xxxx"}", CURL_ZERO_TERMINATED);*/
     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "bigImageFiles");
     curl_mime_filedata(part, filename);
     curl_easy_setopt(curl, CURLOPT_MIMEPOST, multipart);
     CURLcode rescode = curl_easy_perform(curl);
     curl_mime_free(multipart);
     curl_easy_cleanup(curl);

}


void nupload(char *hydeviceCode,int alarmtype,int sec,char *usec,char *daytime,char *filename,char *mfilename){

     CURL *curl = curl_easy_init();
     curl_easy_setopt(curl, CURLOPT_URL, nurl);
     curl_easy_setopt(curl, CURLOPT_POST,1 );
     curl_easy_setopt(curl, CURLOPT_HTTPGET, 0);
     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); 
     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    
     // 添加配置表单
     curl_mime *multipart = curl_mime_init(curl);

     curl_mimepart *part = curl_mime_addpart(multipart);
     curl_mime_name(part, "serialNo");
     curl_mime_data(part, hydeviceCode, CURL_ZERO_TERMINATED);

     part = curl_mime_addpart(multipart);
     char *eventCode=join("HY",itoa(sec));
     curl_mime_name(part, "eventCode");
     curl_mime_data(part, eventCode, CURL_ZERO_TERMINATED);

     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "eventedAt");
     curl_mime_data(part, usec, CURL_ZERO_TERMINATED);//毫秒

     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "typeCode");
     curl_mime_data(part,itoa(alarmtype), CURL_ZERO_TERMINATED);

    char *pi = join("http://event.huoyanzn.com:8004/bigImage/",daytime);
    char *pi1 = join(pi,"/");
    char *pic = join(pi1,filename);

    printf("%s; buffer = %s\n", __FILE__, pic);

     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "imageFile");
     curl_mime_data(part, pic,CURL_ZERO_TERMINATED);

    char *vi = join("http://event.huoyanzn.com:8004/video/",daytime);
    char *vi1 = join(vi,"/");
    char *vie = join(vi1,mfilename);
    printf("%s; buffer = %s\n", __FILE__, vie);
     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "videoFile");
     curl_mime_data(part, vie, CURL_ZERO_TERMINATED);
     curl_easy_setopt(curl, CURLOPT_MIMEPOST, multipart);

     CURLcode rescode = curl_easy_perform(curl);
     curl_mime_free(multipart);
     curl_easy_cleanup(curl);

}

void c_upload(char *hydeviceCode,int alarmtype,int sec,char *usec,char *filename,char *mfilename){

     CURL *curl = curl_easy_init();
     curl_easy_setopt(curl, CURLOPT_URL, nurl);
     curl_easy_setopt(curl, CURLOPT_POST,1 );
     curl_easy_setopt(curl, CURLOPT_HTTPGET, 0);
     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); 
     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    
     // 添加配置表单
     curl_mime *multipart = curl_mime_init(curl);

     curl_mimepart *part = curl_mime_addpart(multipart);
     curl_mime_name(part, "serialNo");
     curl_mime_data(part, hydeviceCode, CURL_ZERO_TERMINATED);

     part = curl_mime_addpart(multipart);
     char *eventCode=join("HY",itoa(sec));
     curl_mime_name(part, "eventCode");
     curl_mime_data(part, eventCode, CURL_ZERO_TERMINATED);

     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "eventedAt");
     curl_mime_data(part, usec, CURL_ZERO_TERMINATED);//毫秒

     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "typeCode");
     curl_mime_data(part,itoa(alarmtype), CURL_ZERO_TERMINATED);

     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "imageFile");
     curl_mime_filedata(part, filename);

     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "videoFile");
     curl_mime_filedata(part, mfilename);

     curl_easy_setopt(curl, CURLOPT_MIMEPOST, multipart);
     CURLcode rescode = curl_easy_perform(curl);
     curl_mime_free(multipart);
     curl_easy_cleanup(curl);

}


//检测的结果发送
void coupload(const char* url, char* filename, char * mfilename,const char* Id,const char* tag,const char* tip){

     CURL *curl = curl_easy_init();
     curl_easy_setopt(curl, CURLOPT_URL, url);

     // 添加配置表单
     curl_mime *multipart = curl_mime_init(curl);
     curl_mimepart *part = curl_mime_addpart(multipart);
     curl_mime_name(part, "deviceCode");
     curl_mime_data(part, Id, CURL_ZERO_TERMINATED);
     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "eventTag");
     curl_mime_data(part, tag, CURL_ZERO_TERMINATED);
     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "eventTip");
     curl_mime_data(part, tip, CURL_ZERO_TERMINATED);
     /*
     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "content");
     curl_mime_data(part, "{"check_address":"深圳","type":"xxx","number":"xxxx"}", CURL_ZERO_TERMINATED);*/
     part = curl_mime_addpart(multipart);
     curl_mime_name(part, "bigImageFiles");
     curl_mime_filedata(part, filename);
     //curl_mime_type(part, "image/jpeg");
    part = curl_mime_addpart(multipart);
     curl_mime_name(part, "videoFile");
     curl_mime_filedata(part, mfilename);
     //curl_mime_type(part, "video/mp4");
 
     curl_easy_setopt(curl, CURLOPT_MIMEPOST, multipart);
     CURLcode rescode = curl_easy_perform(curl);
     curl_mime_free(multipart);
     curl_easy_cleanup(curl);

}


int getNalu(FILE *pFile, unsigned char *pNalu)
{
    unsigned char c;
    int pos = 0;
    int len;

    if(!pFile)
        return -1;

    if((len = fread(pNalu, 1, 4, pFile)) <= 0)
        return -1;

    if(pNalu[0] != 0 || pNalu[1] != 0 || pNalu[2] != 0 || pNalu[3] != 1)
        return -1;

    pos = 4;

    while(1)
    {
        if(feof(pFile))
            break;

        pNalu[pos] = fgetc(pFile);
        
        if(pNalu[pos-3] == 0 && pNalu[pos-2] == 0 && pNalu[pos-1] == 0 && pNalu[pos] == 1)
        {
            fseek(pFile, -4, SEEK_CUR);
            pos -= 4;
            break;
        }
        pos++;
    }
    len = pos+1;
    return len;
}



int packet2Mp4(const char *inputFile, const char *outputFiles)
{
    FILE *pIn = NULL;
    unsigned char *pBuf = (unsigned char*) malloc(1024*1024);
    unsigned char *pNalu = NULL;
    unsigned char naluType;
    int len;
    int num = 0;
    MP4FileHandle pHandle = NULL;
    MP4TrackId videoId;
	int width = 1920;
	int height = 1080;
	int frameRate = 25;
	int timeScale = 90000;
    int addStream = 1;

    pIn = fopen(inputFile, "rb");
    if(!pIn)
        return -1;

    pHandle = MP4Create(outputFiles, 0);
    if(pHandle == MP4_INVALID_FILE_HANDLE)
    {
		printf("ERROR:Create mp4 handle fialed.\n");
		return -1;
    }

    MP4SetTimeScale(pHandle, timeScale);

    while(1)
    {
        len = getNalu(pIn, pBuf);
        if (len <= 0)
            break;

        if (pBuf[0] != 0 || pBuf[1] != 0 || pBuf[2] != 0 || pBuf[3] != 1)
            continue;

        len -= 4;
        pNalu = pBuf+4;
        naluType = pNalu[0]&0x1F;

        switch (naluType)
        {
            case 0x07: // SPS
                printf("------------------------------------\n");
                //printf("sps(%d)\n", len);
                if (addStream)
                {
                    videoId = MP4AddH264VideoTrack
                            (pHandle, 
                            timeScale,              // 一秒钟多少timescale
                            timeScale/frameRate,    // 每个帧有多少个timescale
                            width,                  // width
                            height,                 // height
                            pNalu[1],               // sps[1] AVCProfileIndication
                            pNalu[2],               // sps[2] profile_compat
                            pNalu[3],               // sps[3] AVCLevelIndication
                            3);                     // 4 bytes length before each NAL unit
                    if (videoId == MP4_INVALID_TRACK_ID)
                    {
                        printf("Error:Can't add track.\n");
                        return -1;
                    }
                    
                    MP4SetVideoProfileLevel(pHandle, 0x7F);

                    addStream = 0;
                }

                MP4AddH264SequenceParameterSet(pHandle, videoId, pNalu, len);
                break;
            
            case 0x08: // PPS
                //printf("pps(%d)\n", len);
                MP4AddH264PictureParameterSet(pHandle, videoId, pNalu, len);
                break;

            default:
                //printf("slice(%d)\n", len);
                pBuf[0] = (len>>24)&0xFF;
                pBuf[1] = (len>>16)&0xFF;
                pBuf[2] = (len>>8)&0xFF;
                pBuf[3] = (len>>0)&0xFF;

                MP4WriteSample(pHandle, videoId, pBuf, len+4, MP4_INVALID_DURATION, 0, 1);

                break;
        }
    }

    free(pBuf);
    fclose(pIn);
    MP4Close(pHandle, 0);

    return 0;
}
/* //upload to huoyan
        //0 :rub 1 :over 4 :person3 :bag 5 :worker
    if(upload_type==1){
        nupload(config,alarmtype);
    }
    printf("mfilename:%s",config->url);
    printf("mfilename:%s",config->hydeviceCode);
    DHOP_SYS_DevInfo pDevInfo;
    ret=DHOP_SYS_getDevInfo(&pDevInfo);
    printf("s/n: %s\n", pDevInfo.serial);
    config->hydeviceCode = (char*)pDevInfo.serial;

    if(alarmtype == 1){
        coupload(config->url,config->cofilename,config->mfilename,config->hydeviceCode,config->rubbishtag,config->rubbishtip);
       
    }else if (alarmtype == 2)
    {
        coupload(config->url,config->cofilename,config->mfilename,config->hydeviceCode,config->overtag,config->overtip);
       
    }else if (alarmtype == 5)
    {
        coupload(config->url,config->cofilename,config->mfilename,config->hydeviceCode,config->persontag,config->persontip);
    } else if (alarmtype == 4)
    {
        coupload(config->url,config->cofilename,config->mfilename,config->hydeviceCode,config->bagtag,config->bagtip);
       
    } else if (alarmtype == 3)
    {
        coupload(config->url,config->cofilename,config->mfilename,config->hydeviceCode,config->workertag,config->workertip);
    }*/


DH_Int32 DHOP_SMP_RealStreamModDemo(int pretime,char *hfilename,char *mfilename)
{

    DH_Int32 ret = -1;
    DH_Uint32 channel = 0,streamNum = 0;

    ret =DHOP_STREAM_getChannelNum(0,&channel);
    if(ret != 0)
    {
        DHOP_LOG_ERROR("DHOP_STREAM_getChannelNum failed %x\n",ret);
        return -1;
    }

    ret = DHOP_STREAM_getChnStreamNum(0,channel-1,&streamNum);
    if(ret != 0)
    {
        DHOP_LOG_ERROR("DHOP_STREAM_getChnStreamNum failed %x\n",ret);
        return -1;
    }

    
    DHOP_STREAM_Handle      handle;
    DHOP_STREAM_OpenParam   param;
    DHOP_STREAM_Option      option;

    memset(&param,0,sizeof(DHOP_STREAM_OpenParam));

    param.chnl = 0;
    param.strm = DHOP_STREAM_STREAM_MAIN;
    param.mediaType = DHOP_STREAM_MEDIA_TYPE_AUTO;
    option.preRecord = pretime;
    option.timeoutMs = 1000;
    param.option = &option;

    ret = DHOP_STREAM_open(&param, &handle);
    if(ret != 0)
    {
        DHOP_LOG_ERROR("DHOP_STREAM_open failed %x \n",ret);
        return -1;
    }
    sleep(pretime);
    //char filePath[64] = "../data/realStream.h264"; 

    /*char *result0 =join(config->savepath,itoa(config->sec));
    char *hfilename = join(result0, ".h264");
    char *mfilename = join(result0, ".mp4");
    char *cmfile = join(itoa(config->sec), ".mp4");*/
    printf("filename:%s",hfilename);
    printf("filename:%s",mfilename);

    FILE *fd = fopen(hfilename,"wb");
    if( fd == NULL )
    {
        DHOP_LOG_ERROR("file open failed %d,%s\n",errno,strerror(errno));
        DHOP_STREAM_close(&handle);
        return -1;
    }

    DHOP_STREAM_Packet  packet;
    for(int i = 0; i < 150;i++)
    {
        DHOP_SYS_LocalTime localtime;
        memset(&localtime,0,sizeof(DHOP_SYS_LocalTime));
        DHOP_SYS_getLocalTime(&localtime);
        printf("%d//%d//%d//%d//%d//%d\n",localtime.year,localtime.mon,localtime.mday,localtime.hour,localtime.min,localtime.sec);
        printf("%d//%d//%d//%d//%d//%d\n",packet.time.year,packet.time.month,packet.time.day,packet.time.hour,packet.time.min,packet.time.sec);
        ret = DHOP_STREAM_getPacket(handle,&packet);
        if(ret != 0)
        {
            DHOP_LOG_ERROR("DHOP_STREAM_getPacket failed %x\n",ret);
            break;
        }
        //DHOP_LOG_INFO("channel = %d,streamNum = %d\n",1,4);
        fwrite(packet.packetData,1,packet.packetSize,fd);
        fflush(fd);

        ret = DHOP_STREAM_releasePacket(handle,&packet);
        if(ret != 0)
        {
            DHOP_LOG_ERROR("DHOP_STREAM_releasePacket failed %x \n",ret);   
            break;
        }
    }
    fclose(fd);
    DHOP_STREAM_close(&handle);

    if (packet2Mp4(hfilename, mfilename))
    {
        printf("Error:Packet to Mp4 fail.\n");
    }

    return 0;
}






// dhop project
// Convert AI detection coordinates

/*
// APP作为客户端，联上PC上的服务端程序，对应本示例的ResultShow.exe程序
int app_net_init() {
    DH_Int32                ret;
    struct sockaddr_in      sever_addr;
    struct timeval          timeout = {2, 0};
    socklen_t               len = sizeof(timeout);

    g_app_global.hNet = socket(AF_INET, SOCK_STREAM, 0);
    if (g_app_global.hNet < 0)
    {;
        perror("socket failed");
        g_app_global.hNet = -1;
        return -1;
    }
    DHOP_LOG_INFO("create socket %d\n", g_app_global.hNet);

    // 设置一下超时（2秒），防止connect失败后一直卡住
    setsockopt(g_app_global.hNet, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);

    memset(&sever_addr, 0, sizeof(sever_addr));
    sever_addr.sin_family       = AF_INET;
    sever_addr.sin_port         = htons(g_app_config.net_port);
    sever_addr.sin_addr.s_addr  = inet_addr(g_app_config.net_ip);

    ret = connect(g_app_global.hNet, (struct sockaddr *)&sever_addr, sizeof(sever_addr));
    if (ret != 0)
    {
        perror("connect failed");

        close(g_app_global.hNet);
        g_app_global.hNet = -1;
    }
    else {
        DHOP_LOG_INFO("connect success: %d\n", g_app_global.hNet);
    }

    return ret;
}*/


/*int app_net_deinit() {
    if (g_app_global.hNet > 0) {
        close(g_app_global.hNet);
        g_app_global.hNet = -1;
    }
    return 0;
}



int app_net_reinit() {
    app_net_deinit();
    return app_net_init();
}*/



/*int app_enc_deinit() {
    DHOP_VENC_destroy(&(g_app_global.hVenc));
    return 0;
}*/



// Close YUV
/*DH_Int32 app_yuv_deinit()
{
    DHOP_YUV_close(&(g_app_global.hYuv));
    return DHOP_SUCCESS;
}*/

//调用AI模型
int app_ai_init(struct app_global_t * g_app_global) {

    DH_Int32                ret = -1;
    DHOP_AI_NNX_Version     ver;
    char modelkeystr[] = "gGQaZICol8tv2BqcbQ0UZG9kXmRvZBnsPWQDZMRkkmSg/G8xkNtvZG5k5a1vZG/81a00yXIgcMpvDpFkOmRMYg==";

    ver.byte_size = sizeof(DHOP_AI_NNX_Version);
    // Get engine version number
    ret = DHOP_AI_NNX_getVersion(&ver);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("DHOP_AI_NNX_getVersion %#x\n", ret);
        return DHOP_FAILED;
    }
    DHOP_LOG_INFO("version:%s\n", ver.version);

    // AI initialization
    ret = DHOP_AI_init();
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("dhop ai init fail %#x\n", ret);
        return DHOP_FAILED;
    }
    DHOP_LOG_INFO("DHOP_AI_init success\n");

    // Create engine
    ret = DHOP_AI_NNX_create(&(g_app_global->hNNX), g_modelfile, modelkeystr);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("dhop ai nnx create fail#x\n", ret);
        return DHOP_FAILED;
    }

    return 0;
}

/*int app_ai_deinit() {
    // Destroy algorithm model handle
    DHOP_AI_NNX_destroy(g_app_global.hNNX);
    // AI unInitialization
    DHOP_AI_unInit();

    return 0;
}*/


//模型推理
DH_Int32 app_ai_process(DHOP_AI_NNX_Handle hNNX, DHOP_YUV_FrameData2 * frame,struct app_global_t * g_app_global)
{
    DH_Int32                ret = -1, i, k;
    DH_Ptr                  ptrs[2];
    DH_Ptr                  ptrs_HW[2];
    DH_Int32                strides[2];
    DHOP_AI_IMG_Handle      hImg;
    DH_Uint32               type = DHOP_AI_NNX_RESULT_TYPE_MAX;
    DHOP_AI_MAT_Handle      yoloMat;
    DH_Int32                h,start;
    DHOP_AI_NNX_ResultYolo *yolo_result;

    g_app_global->resultNum = 0;

    ptrs[0]     = frame->data.virAddr.nv21.y;
    ptrs[1]     = frame->data.virAddr.nv21.vu;
    ptrs_HW[0]  = frame->data.phyAddr.nv12.y;
    ptrs_HW[1]  = frame->data.phyAddr.nv21.vu;
    strides[0]  = frame->data.stride[0];
    strides[1]  = frame->data.width;

    // AI to initialize and create Dhop_ AI_ IMG_ Handle, Dhop required_ AI_ IMG_ Destroy() to free img memory
    ret = DHOP_AI_IMG_create(&hImg,
                             frame->data.width,
                             frame->data.height,
                             DHOP_AI_IMG_CS_YUV420SP_VU,
                             DHOP_AI_IMG_8U,
                             ptrs,
                             ptrs_HW,
                             strides,
                             2);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("creat DHOP_AI_IMG_Handle fail\n");
        goto err0;
    }

    // Set picture input
    ret = DHOP_AI_NNX_setInputImg(hNNX, (const DH_String)"image", &hImg, 1);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("dhop ai set input img fail");
        goto err1;
    }

    // Run AI
    ret = DHOP_AI_NNX_run(hNNX);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("dhop ai run fail");
        goto err1;
    }

    // Obtain AI test results
    type = DHOP_AI_NNX_RESULT_TYPE_MAX;
    ret = DHOP_AI_NNX_getResult(hNNX, (const DH_String)"result", &type, &yoloMat);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("dhop ai get result fail");
        goto err1;
    }
    if (type != DHOP_AI_NNX_RESULT_TYPE_YOLO)
    {
        DHOP_LOG_ERROR("nnx result type is not yolo\n");
        goto err1;
    }

    // Gets the active range of the matrix on the specified dimension.
    ret = DHOP_AI_MAT_getActiveRange(yoloMat, 0, &start, &h);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("get rect num fail\n");
        goto err1;
    }

    yolo_result = (DHOP_AI_NNX_ResultYolo *)DHOP_AI_MAT_ptr2(yoloMat, NULL);
    if (NULL == yolo_result) {
        goto err1;
    }

    for (i = start, k = 0; i < start+h; i++)
    {
        // Filter confidence minima
        if ( yolo_result[i].prob > 0.1 )
        {
            if (k < APP_MAX_AI_RESULT_NUM) {
                // The output of the algorithm is 0 ~ 1 floating-point data, which should be converted into 8192 coordinates
                g_app_global->aiResult[k].rect.lt.x = app_size_limit((yolo_result[i].x - yolo_result[i].w/2) * 8192, 8192);
                g_app_global->aiResult[k].rect.lt.y = app_size_limit((yolo_result[i].y - yolo_result[i].h/2) * 8192, 8192);
                g_app_global->aiResult[k].rect.rb.x = app_size_limit((yolo_result[i].x + yolo_result[i].w/2) * 8192, 8192);
                g_app_global->aiResult[k].rect.rb.y = app_size_limit((yolo_result[i].y + yolo_result[i].h/2) * 8192, 8192);
                g_app_global->aiResult[k].classId   = yolo_result[i].classIdx;
                g_app_global->aiResult[k].conf = yolo_result[i].prob;

                // The output of the algorithm is 0 ~ 1 floating-point data, which should be converted into the width and height coordinates of YUV frame
                g_app_global->aiResult[k].actual.lt.x = app_size_limit((yolo_result[i].x - yolo_result[i].w/2) * frame->data.width, frame->data.width);
                g_app_global->aiResult[k].actual.lt.y = app_size_limit((yolo_result[i].y - yolo_result[i].h/2) * frame->data.height, frame->data.height);
                g_app_global->aiResult[k].actual.rb.x = app_size_limit((yolo_result[i].x + yolo_result[i].w/2) * frame->data.width, frame->data.width);
                g_app_global->aiResult[k].actual.rb.y = app_size_limit((yolo_result[i].y + yolo_result[i].h/2) * frame->data.height, frame->data.height);

                k++;
            }
            else {
                break;
            }
        }
    }
    g_app_global->resultNum = k;

err1:
    /// Destroy Dhop_ AI_ IMG_ Handle handle
    ret = DHOP_AI_IMG_destroy(hImg);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_ERROR("DHOP_AI_IMG_destroy fail\n");
    }
 
err0:
    return ret;
}





/*
// Send the detection results to the server
int app_result_send(DHOP_VENC_Result* image, obj_info_t * result) {
    DH_Int32                ret = -1;
    struct {
        int                 cbsize;
        int                 pic_size;
        short               lt_x;
        short               lt_y;
        short               rb_x;
        short               rb_y;
        unsigned int        magic_code; // 0x12345678
        char                name[48];
    } img_info;

    if (g_app_global.hNet > 0) {

        memset(&img_info, 0, sizeof(img_info));
        img_info.cbsize     = sizeof(img_info);
        img_info.pic_size   = image->size;
        img_info.lt_x       = result->actual.lt.x;
        img_info.lt_y       = result->actual.lt.y;
        img_info.rb_x       = result->actual.rb.x;
        img_info.rb_y       = result->actual.rb.y;
        img_info.magic_code = 0x12345678;

        if (result->classId >= 0 && result->classId < 80) {
            strcpy(img_info.name, g_yolo_object_list[result->classId]);
        }
        else {
            return -1;
        }
        ret = send(g_app_global.hNet, &img_info, sizeof(img_info), 0);
        if (ret < 0) {
            perror("send head failed:");
            app_net_reinit();
            return -2;
        }

        ret = send(g_app_global.hNet, image->virAddr, image->size, 0);
        if (ret < 0) {
            perror("send image failed:");
            app_net_reinit();
            return -3;
        }

        return 0;
    }

    return -1;
}*/

// Encode the data detected by the algorithm
//void app_result_snap(obj_info_t * result, DHOP_YUV_FrameData2* frame) 
void app_coresult_snap(struct app_global_t * g_app_global,DHOP_YUV_FrameData2* frame, char *filename,char  *objinfo) {
    DH_Int32                ret = -1;
    DHOP_VENC_ReqInfo2      encReq;
    DHOP_VENC_Result        encResult;

    // coordinates
    DHOP_VENC_OverlayElement elements[128] = {0,};
    DHOP_VENC_OverlayRect rect[128] ={0,};

    char **res = split(objinfo,"_");
    int n = 0;
    for (int j = 0; res[j] != NULL; j++) {
      	if (strlen(res[j])>0){
            n++;
        }
    }
    printf("n/5:%d ",n/5);
     
    for (int i =0;i<n;i+=5){

   // for (int i =0;i<g_app_global.resultNum;i++){
       // if (g_app_global.aiResult[i].conf>0.4){
        rect[i/5].pixcelWidth = 2;
        rect[i/5].type = DHOP_VENC_OVERLAY_RECT;
        int ex1 = atoi(res[i]) *1920/8192;
        if(ex1%2==0){
            rect[i/5].beginPoint.x = ex1;
        }else{
            rect[i/5].beginPoint.x = ex1-1;
        }
        if (ex1 <= 0){
            ex1 = 2;
        }
        int ey1 = atoi(res[i+1]) *1080/8192;
        if(ey1%2==0){
            rect[i/5].beginPoint.y = ey1;
        }else{
            rect[i/5].beginPoint.y = ey1 -1;
        }
        if (ey1 <= 0){
            ey1 = 2;
        }
        int ex2 = atoi(res[i +2])*1920/8192;
        if(ex2%2==0){
            rect[i/5].endPoint.x = ex2;
        }else{
            rect[i/5].endPoint.x = ex2 -1;
        }
        if (ex2 <= 0){
            ex2 = 2;
        }
        int ey2 =atoi(res[i+3])*1080/8192;
        if(ey2%2==0){
            rect[i/5].endPoint.y = ey2;
        }else{
            rect[i/5].endPoint.y = ey2 -1;
        }
        if (ey2 <= 0){
            ey2 = 2;
        }
        printf("x1:%d ",rect[i/5].beginPoint.x);
        printf("y1:%d ",rect[i/5].beginPoint.y);
        printf("x2:%d ",rect[i/5].endPoint.x);
        printf("y2:%d\n",rect[i/5].endPoint.y);
        rect[i/5].color.a = 1;
        rect[i/5].color.r = 30;//0~31
        rect[i/5].color.g = 0;
        rect[i/5].color.b = 0;
        elements[i/5].rect = &rect[i/5];
        //elements[i].text = NULL;
       // }
    }
    //Encode
    memset(&encReq, 0, sizeof(encReq));
    encReq.cbSize       = sizeof(encReq);
    encReq.quality      = DHOP_VENC_JPEG_QUALITY_DEFAULT;
    //encReq.region.lt.x  = FLOOR(result->actual.lt.x, g_app_global.encAlignW);
   // encReq.region.lt.y  = FLOOR(result->actual.lt.y, g_app_global.encAlignH);
  //  encReq.region.rb.x  = FLOOR(result->actual.rb.x, g_app_global.encAlignW);
  //  encReq.region.rb.y  = FLOOR(result->actual.rb.y, g_app_global.encAlignH);
    encReq.region.lt.x  = 0;
    encReq.region.lt.y  = 0;
    encReq.region.rb.x  = frame->data.width;
    encReq.region.rb.y  = frame->data.height;
     encReq.elements = elements;
    encReq.elemNum = n/5;
    encReq.data         = frame;
    encReq.timeout      = 2000;

    ret = DHOP_VENC_sendRequest(g_app_global->hVenc, &encReq);
    if (ret != DHOP_SUCCESS) {
        DHOP_LOG_WARN("Send enc reqeust failed!\n");
        printf("enc fail with %d\n", ret);
    }
    else {
        memset(&encResult, 0, sizeof(encResult));
        encResult.cbSize  = sizeof(encResult);
        encResult.pts     = encReq.data->pts;
        encResult.timeout = 200;
        ret = DHOP_VENC_getResult(g_app_global->hVenc, &encResult);
        if (ret != DHOP_SUCCESS) {
            DHOP_LOG_WARN("Get enc result failed!\n");
            printf("enc fail with %d\n", ret);
        }
        //write
        printf("filename:%s\n", filename);
        FILE *fp = NULL;
        DH_Uint32	 fileSize = 0;
        fp = fopen(filename, "w+");
        if(NULL == fp)
        {  
            printf("open file %s fail\n", filename);
        //return -1;
        }
        fileSize = fwrite(encResult.virAddr, 1, encResult.size, fp);
        if(fileSize != encResult.size)
        {
            printf("process %d-write file %s fail\n", getpid(), filename);
            fclose(fp);
        //return -1;
        }
        //app_result_send(&encResult, result);
        ret = DHOP_VENC_releaseResult(g_app_global->hVenc, &encResult);
        if (ret != DHOP_SUCCESS) {
            DHOP_LOG_WARN("Release enc result failed!\n");
        }
    }
}

/* if (alarmtype == -1){
            filename="/var/tmp/0.jpeg";
        }else{
            char *result0 = join(config->savepath, itoa(alarmtype));
            char *result1 = join(result0, "_");
            char *result2 = join(result1, objinfo);
            char *result3 = join(result2, itoa(sec));
            filename = join(result3, ".jpeg");
        }
        var->cofilename = filename;*/



void app_result_snap(struct app_global_t * g_app_global,DHOP_YUV_FrameData2* frame, char *filename){
    DH_Int32                ret = -1;
    DHOP_VENC_ReqInfo2      encReq;
    DHOP_VENC_Result        encResult;


    //Encode
    memset(&encReq, 0, sizeof(encReq));
    encReq.cbSize       = sizeof(encReq);
    encReq.quality      = DHOP_VENC_JPEG_QUALITY_DEFAULT;
    encReq.region.lt.x  = 0;
    encReq.region.lt.y  = 0;
    encReq.region.rb.x  = frame->data.width;
    encReq.region.rb.y  = frame->data.height;
    encReq.data         = frame;
    encReq.timeout      = 2000;

    ret = DHOP_VENC_sendRequest(g_app_global->hVenc, &encReq);
    if (ret != DHOP_SUCCESS) {
        printf("Send enc reqeust failed!\n");
        printf("enc fail with %d\n", ret);
    }
    else {
        memset(&encResult, 0, sizeof(encResult));
        encResult.cbSize  = sizeof(encResult);
        encResult.pts     = encReq.data->pts;
        encResult.timeout = 200;
        ret = DHOP_VENC_getResult(g_app_global->hVenc, &encResult);
        if (ret != DHOP_SUCCESS) {
            printf("Get enc result failed!\n");
            printf("enc fail with %d\n", ret);
        }
        //write
        printf("filename:%s\n", filename);
        FILE *fp = NULL;
        DH_Uint32	 fileSize = 0;
        fp = fopen(filename, "w+");
        if(NULL == fp)
        {  

            printf("open file %s fail\n", filename);
        //return -1;
        }
        fileSize = fwrite(encResult.virAddr, 1, encResult.size, fp);
        if(fileSize != encResult.size)
        {
            printf("process %d-write file %s fail\n", getpid(), filename);
            fclose(fp);
        //return -1;
        }

        //upload to huoyan
        //2:rub 1 over 4:person3 :bag 5 :worker
        /*if(alarmtype == 1){
            upload(config->url,filename,config->hydeviceCode,config->rubbishtag,config->rubbishtip);
        }else if (alarmtype == 2)
        {
            upload(config->url,filename,config->hydeviceCode,config->overtag,config->overtip);
        }else if (alarmtype == 5)
        {
             upload(config->url,filename,config->hydeviceCode,config->persontag,config->persontip);
        } else if (alarmtype == 4)
        {
             upload(config->url,filename,config->hydeviceCode,config->bagtag,config->bagtip);
        } else if (alarmtype == 3)
        {
             upload(config->url,filename,config->hydeviceCode,config->workertag,config->workertip);
        }
        //app_result_send(&encResult, result);*/
        ret = DHOP_VENC_releaseResult(g_app_global->hVenc, &encResult);
        if (ret != DHOP_SUCCESS) {
            DHOP_LOG_WARN("Release enc result failed!\n");
        }
    }
}


// Draw frame
DH_Int32 app_result_draw(configuration *config,struct app_global_t * g_app_global)
{
    int                     i;
    struct paint_info_t    *info;
    DHOP_OSD_PaintWork      work[APP_MAX_AI_RESULT_NUM];
    /*if (g_app_global.resultNum <= 0)
    {
        return DHOP_FAILED;
    }*/
    info = (struct paint_info_t*)malloc(APP_MAX_AI_RESULT_NUM * sizeof(struct paint_info_t));
    if (info == NULL) {
        return DHOP_FAILED;
    }
    memset(info, 0, APP_MAX_AI_RESULT_NUM * sizeof(struct paint_info_t));
    int num = 3;
    for (i = 0; i <num; i++)
    {
        //personrubbish
        if (i == 0){
            work[i].chn = 0;
            work[i].id  = i+1;
            work[i].pts = 0;
            work[i].coustomerField = 1;
            work[i].state = 0;
            work[i].numOfElem = 2;

            //draw text
            info[i].text.type           = DHOP_OSD_ET_TEXT;
            info[i].text.charset        = DHOP_OSD_CS_UTF8;
            info[i].text.fontsize       = 30;
            info[i].text.position.x     = config->x1 *8192/1920;
            info[i].text.position.y     = config->y1 *8192/1080;
            info[i].text.color.A        = 255;
            info[i].text.color.R        = 0;
            info[i].text.color.G        = 255;
            info[i].text.color.B        = 0;

            sprintf(info[i].szText, "%s",  "personarea");
            //printf("text:%s ",g_yolo_object_list[g_app_global.aiResult[i].classId]);
            //printf("text:%s ",g_yolo_object_list[0]);
        // printf("text:%s ",g_yolo_object_list[13]);

            info[i].text.length         = strlen(info[i].szText)+1;
            info[i].text.text           = info[i].szText;
            info[i].element[0].text     = &info[i].text;

            //draw coordinates

            info[i].rect.type           = DHOP_OSD_ET_POLYGON;
            info[i].rect.borderWeight   = 2;
            info[i].rect.style          = DHOP_OSD_RS_SOLID;
            info[i].rect.clrBorder.A    = 255;
            info[i].rect.clrBorder.R    = 255;
            info[i].rect.clrBorder.G    = 0;
            info[i].rect.clrBorder.B    = 0;
            info[i].rect.pointNum       = 4;

            info[i].points[0].x         = config->x1*8192/1920; //x1
            info[i].points[0].y         = config->y1 *8192/1080; //y1
            info[i].points[1].x         = config->x2 *8192/1920; //x2
            info[i].points[1].y         = config->y2 *8192/1080; //y2
            info[i].points[2].x         = config->x3 *8192/1920; //x3
            info[i].points[2].y         = config->y3 *8192/1080; //y3
            info[i].points[3].x         = config->x4 *8192/1920; // x4
            info[i].points[3].y         = config->y4 *8192/1080; //y4
            
            info[i].rect.points         = info[i].points;
            info[i].element[1].region   = &info[i].rect;

            work[i].elems = info[i].element;
        }else if (i==1)
        {
            work[i].chn = 0;
            work[i].id  = i+1;
            work[i].pts = 0;
            work[i].coustomerField = 1;
            work[i].state = 0;
            work[i].numOfElem = 2;

            //draw text
            info[i].text.type           = DHOP_OSD_ET_TEXT;
            info[i].text.charset        = DHOP_OSD_CS_UTF8;
            info[i].text.fontsize       = 30;
            info[i].text.position.x     = config->px1 *8192/1920;
            info[i].text.position.y     = config->py1 *8192/1080;
            info[i].text.color.A        = 255;
            info[i].text.color.R        = 0;
            info[i].text.color.G        = 255;
            info[i].text.color.B        = 0;

            sprintf(info[i].szText, "%s",  "overflowarea");
            //printf("text:%s ",g_yolo_object_list[g_app_global.aiResult[i].classId]);
            //printf("text:%s ",g_yolo_object_list[0]);
        // printf("text:%s ",g_yolo_object_list[13]);

            info[i].text.length         = strlen(info[i].szText)+1;
            info[i].text.text           = info[i].szText;
            info[i].element[0].text     = &info[i].text;

            //draw coordinates

            info[i].rect.type           = DHOP_OSD_ET_POLYGON;
            info[i].rect.borderWeight   = 2;
            info[i].rect.style          = DHOP_OSD_RS_SOLID;
            info[i].rect.clrBorder.A    = 255;
            info[i].rect.clrBorder.R    = 255;
            info[i].rect.clrBorder.G    = 0;
            info[i].rect.clrBorder.B    = 0;
            info[i].rect.pointNum       = 4;

            info[i].points[0].x         = config->px1*8192/1920; //x1
            info[i].points[0].y         = config->py1 *8192/1080; //y1
            info[i].points[1].x         = config->px2 *8192/1920; //x2
            info[i].points[1].y         = config->py2 *8192/1080; //y2
            info[i].points[2].x         = config->px3 *8192/1920; //x3
            info[i].points[2].y         = config->py3 *8192/1080; //y3
            info[i].points[3].x         = config->px4 *8192/1920; // x4
            info[i].points[3].y         = config->py4 *8192/1080; //y4
            
            info[i].rect.points         = info[i].points;
            info[i].element[1].region   = &info[i].rect;

            work[i].elems = info[i].element;
        }else if (i == 2)
        {
            work[i].chn = 0;
            work[i].id  = i+1;
            work[i].pts = 0;
            work[i].coustomerField = 1;
            work[i].state = 0;
            work[i].numOfElem = 2;
            //draw text
            info[i].text.type           = DHOP_OSD_ET_TEXT;
            info[i].text.charset        = DHOP_OSD_CS_UTF8;
            info[i].text.fontsize       = 30;
            info[i].text.position.x     = config->bx1 *8192/1920;
            info[i].text.position.y     = config->by1 *8192/1080;
            info[i].text.color.A        = 255;
            info[i].text.color.R        = 0;
            info[i].text.color.G        = 255;
            info[i].text.color.B        = 0;

            sprintf(info[i].szText, "%s",  "bagarea");
            //printf("text:%s ",g_yolo_object_list[g_app_global.aiResult[i].classId]);
            //printf("text:%s ",g_yolo_object_list[0]);
        // printf("text:%s ",g_yolo_object_list[13]);

            info[i].text.length         = strlen(info[i].szText)+1;
            info[i].text.text           = info[i].szText;
            info[i].element[0].text     = &info[i].text;

            //draw coordinates

            info[i].rect.type           = DHOP_OSD_ET_POLYGON;
            info[i].rect.borderWeight   = 2;
            info[i].rect.style          = DHOP_OSD_RS_SOLID;
            info[i].rect.clrBorder.A    = 255;
            info[i].rect.clrBorder.R    = 255;
            info[i].rect.clrBorder.G    = 0;
            info[i].rect.clrBorder.B    = 0;
            info[i].rect.pointNum       = 4;

            info[i].points[0].x         = config->bx1*8192/1920; //x1
            info[i].points[0].y         = config->by1 *8192/1080; //y1
            info[i].points[1].x         = config->bx2 *8192/1920; //x2
            info[i].points[1].y         = config->by2 *8192/1080; //y2
            info[i].points[2].x         = config->bx3 *8192/1920; //x3
            info[i].points[2].y         = config->by3 *8192/1080; //y3
            info[i].points[3].x         = config->bx4 *8192/1920; // x4
            info[i].points[3].y         = config->by4 *8192/1080; //y4
            
            info[i].rect.points         = info[i].points;
            info[i].element[1].region   = &info[i].rect;

            work[i].elems = info[i].element;
        }
    }
    for (i = num; i < g_app_global->resultNum + num; i++)
    {
        work[i].chn = 0;
        work[i].id  = i+1;
        work[i].pts = 0;
        work[i].coustomerField = 1;
        work[i].state = 0;
        work[i].numOfElem = 2;

        //draw text

        info[i].text.type           = DHOP_OSD_ET_TEXT;
        info[i].text.charset        = DHOP_OSD_CS_UTF8;
        info[i].text.fontsize       = 30;
        info[i].text.position.x     = g_app_global->aiResult[i].rect.lt.x;
        info[i].text.position.y     = g_app_global->aiResult[i].rect.lt.y;
        info[i].text.color.A        = 255;
        info[i].text.color.R        = 0;
        info[i].text.color.G        = 255;
        info[i].text.color.B        = 0;

        sprintf(info[i].szText, "%s",  g_yolo_object_list[g_app_global->aiResult[i].classId]);
        //printf("text:%s ",g_yolo_object_list[g_app_global.aiResult[i].classId]);
        //printf("text:%s ",g_yolo_object_list[0]);
       // printf("text:%s ",g_yolo_object_list[13]);

        info[i].text.length         = strlen(info[i].szText)+1;
        info[i].text.text           = info[i].szText;
        info[i].element[0].text     = &info[i].text;

        //draw coordinates

        info[i].rect.type           = DHOP_OSD_ET_POLYGON;
        info[i].rect.borderWeight   = 2;
        info[i].rect.style          = DHOP_OSD_RS_SOLID;
        info[i].rect.clrBorder.A    = 255;
        info[i].rect.clrBorder.R    = 255;
        info[i].rect.clrBorder.G    = 0;
        info[i].rect.clrBorder.B    = 0;
        info[i].rect.pointNum       = 4;

        info[i].points[0].x         = g_app_global->aiResult[i].rect.lt.x;
        info[i].points[0].y         = g_app_global->aiResult[i].rect.lt.y;
        info[i].points[1].x         = g_app_global->aiResult[i].rect.rb.x;
        info[i].points[1].y         = g_app_global->aiResult[i].rect.lt.y;
        info[i].points[2].x         = g_app_global->aiResult[i].rect.rb.x;
        info[i].points[2].y         = g_app_global->aiResult[i].rect.rb.y;
        info[i].points[3].x         = g_app_global->aiResult[i].rect.lt.x;
        info[i].points[3].y         = g_app_global->aiResult[i].rect.rb.y;
        info[i].rect.points         = info[i].points;
        info[i].element[1].region   = &info[i].rect;

        work[i].elems = info[i].element;
    }

    int ret = DHOP_OSD_richPaint(work, g_app_global->resultNum + num);
    if (DHOP_SUCCESS != ret)
    {
        DHOP_LOG_INFO("DHOP_OSD_richPaint fail with %#x\n", ret);
    }

    free(info);

    return ret;
}

DH_Int32 app_size_limit(DH_Int32 pix, DH_Int32 max)
{
    if (pix < 0)
    {
        return 0;
    }
    if(pix > max)
    {
        return max-1;
    }
    return pix;
}

int max(int x, int y)
{
    return x > y ? x : y;
}

int IoU(int x1, int y1, int x2, int y2, int u1, int v1, int u2, int v2){
	int inters = max(min(x2, u2) - max(x1, u1), 0.0) * max(min(y2, v2) - max(y1, v1), 0.0);
	int unions = min((x2 - x1)*(y2 - y1),(u2 - u1)*(v2 - v1));
    printf("(%d,%d)\n",inters,unions);
    int a = inters/10000;
    int b = unions/10000;
    int c = 100*a/b;
    //printf("%d\n",100*a/b);
	return c;

}