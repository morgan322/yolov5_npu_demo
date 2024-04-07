
#include "config.h"
#include <stdio.h>
#include <stdlib.h>





/*work_conf = 25
person_conf = 35
rubbish_conf = 45
  int person_conf,rubbish_conf,work_conf;
    int upload_count,last_time;
upload_count = 300
last_time = 300
*/
int handler(void* location, const char* section, const char* url,
                   const char* value)
{
    configuration* pconfig = (configuration*)location;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(url, n) == 0
    if (MATCH("params", "poly_x1")) {
        pconfig->x1 = atoi(value);
    } else if (MATCH("params", "poly_y1")) {
        pconfig->y1 = atoi(value);
    }else if (MATCH("params", "poly_x2")) {
        pconfig->x2 = atoi(value);
    }else if (MATCH("params", "poly_y2")) {
        pconfig->y2 = atoi(value);
    }else if (MATCH("params", "poly_x3")) {
        pconfig->x3 = atoi(value);
    }else if (MATCH("params", "poly_y3")) {
        pconfig->y3 = atoi(value);
    }else if (MATCH("params", "poly_x4")) {
        pconfig->x4 = atoi(value);
    }else if (MATCH("params", "poly_y4")) {
        pconfig->y4 = atoi(value);
    }else if (MATCH("rubbish", "start_hour")) {
        pconfig->rsh = atoi(value);
    }else if (MATCH("rubbish", "start_min")) {
        pconfig->rsm = atoi(value);
    }else if (MATCH("rubbish", "end_hour")) {
        pconfig->reh = atoi(value);
    }else if (MATCH("rubbish", "end_min")) {
        pconfig->rem = atoi(value);
    }else if (MATCH("rubbish", "interval")) {
        pconfig->rin = atoi(value);
    }else  if (MATCH("params", "poly_person_x1")) {
        pconfig->px1 = atoi(value);
    } else if (MATCH("params", "poly_person_y1")) {
        pconfig->py1 = atoi(value);
    }else if (MATCH("params", "poly_person_x2")) {
        pconfig->px2 = atoi(value);
    }else if (MATCH("params", "poly_person_y2")) {
        pconfig->py2 = atoi(value);
    }else if (MATCH("params", "poly_person_x3")) {
        pconfig->px3 = atoi(value);
    }else if (MATCH("params", "poly_person_y3")) {
        pconfig->py3 = atoi(value);
    }else if (MATCH("params", "poly_person_x4")) {
        pconfig->px4 = atoi(value);
    }else if (MATCH("params", "poly_person_y4")) {
        pconfig->py4 = atoi(value);
    }else if (MATCH("person", "start_hour")) {
        pconfig->psh = atoi(value);
    }else if (MATCH("person", "start_min")) {
        pconfig->psm = atoi(value);
    }else if (MATCH("person", "end_hour")) {
        pconfig->peh = atoi(value);
    }else if (MATCH("person", "end_min")) {
        pconfig->pem = atoi(value);
    }else if (MATCH("person", "interval")) {
        pconfig->pin = atoi(value);
    }else  if (MATCH("params", "poly_podai_x1")) {
        pconfig->bx1 = atoi(value);
    } else if (MATCH("params", "poly_podai_y1")) {
        pconfig->by1 = atoi(value);
    }else if (MATCH("params", "poly_podai_x2")) {
        pconfig->bx2 = atoi(value);
    }else if (MATCH("params", "poly_podai_y2")) {
        pconfig->by2 = atoi(value);
    }else if (MATCH("params", "poly_podai_x3")) {
        pconfig->bx3 = atoi(value);
    }else if (MATCH("params", "poly_podai_y3")) {
        pconfig->by3 = atoi(value);
    }else if (MATCH("params", "poly_podai_x4")) {
        pconfig->bx4 = atoi(value);
    }else if (MATCH("params", "poly_podai_y4")) {
        pconfig->by4 = atoi(value);
    }else if (MATCH("params", "work_conf")) {
        pconfig->work_conf = atoi(value);
    }else if (MATCH("params", "person_conf")) {
        pconfig->person_conf = atoi(value);
    }else if (MATCH("params", "rubbish_conf")) {
        pconfig->rubbish_conf = atoi(value);
    }else if (MATCH("bag", "start_hour")) {
        pconfig->bsh = atoi(value);
    }else if (MATCH("bag", "start_min")) {
        pconfig->bsm = atoi(value);
    }else if (MATCH("bag", "end_hour")) {
        pconfig->beh = atoi(value);
    }else if (MATCH("bag", "end_min")) {
        pconfig->bem = atoi(value);
    }else if (MATCH("bag", "interval")) {
        pconfig->bin = atoi(value);
    }else if (MATCH("worker", "start_hour")) {
        pconfig->wsh = atoi(value);
    }else if (MATCH("worker", "start_min")) {
        pconfig->wsm = atoi(value);
    }else if (MATCH("worker", "end_hour")) {
        pconfig->weh = atoi(value);
    }else if (MATCH("worker", "end_min")) {
        pconfig->wem = atoi(value);
    }else if (MATCH("worker", "interval")) {
        pconfig->win = atoi(value);
    }else if (MATCH("overflow", "start_hour")) {
        pconfig->osh = atoi(value);
    }else if (MATCH("overflow", "start_min")) {
        pconfig->osm = atoi(value);
    }else if (MATCH("overflow", "end_hour")) {
        pconfig->oeh = atoi(value);
    } else if (MATCH("overflow", "end_min")) {
        pconfig->oem = atoi(value);
    } else if (MATCH("overflow", "interval")) {
        pconfig->oin = atoi(value);
    } else if (MATCH("params", "upload_count")) {
        pconfig->upload_count = atoi(value);
    } else if (MATCH("params", "last_time")) {
        pconfig->last_time = atoi(value);
    } else if (MATCH("location", "url")) {
        pconfig->url = strdup(value);
    } else if (MATCH("location", "savepath")) {
        pconfig->savepath = strdup(value);
    } else if (MATCH("location", "overtag")) {
        pconfig->overtag = strdup(value);
    } else if (MATCH("location", "persontag")) {
        pconfig->persontag = strdup(value);
    } else if (MATCH("location", "bagtag")) {
        pconfig->bagtag = strdup(value);
    } else if (MATCH("location", "rubbishtag")) {
        pconfig->rubbishtag = strdup(value);
    } else if (MATCH("location", "workertag")) {
        pconfig->workertag = strdup(value);
    } else if (MATCH("location", "ugurl")) {
        pconfig->ugurl = strdup(value);
    } else if (MATCH("location", "cgurl")) {
        pconfig->cgurl = strdup(value);
    } else if (MATCH("location", "overtip")) {
        pconfig->overtip = strdup(value);
    } else if (MATCH("location", "persontip")) {
        pconfig->persontip = strdup(value);
    } else if (MATCH("location", "bagtip")) {
        pconfig->bagtip = strdup(value);
    } else if (MATCH("location", "workertip")) {
        pconfig->workertip = strdup(value);
    } else if (MATCH("location", "rubbishtip")) {
        pconfig->rubbishtip = strdup(value);
    } else if (MATCH("location", "purl")) {
        pconfig->purl = strdup(value);
    } else if (MATCH("location", "dataurl")) {
        pconfig->dataurl = strdup(value);
    }else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

void info_write(char * info)  
{  
    //下面是写数据，将数字0~9写入到data.txt文件中  
    FILE * fpWrite  = fopen("../data/web.json","wb"); 
    int errNum = 0;
    if (fpWrite == NULL)
    {
            /*errNum = errno;
            printf("[saveFile] open fail errno = %d, reason = %s", errNum, strerror(errNum));*/
            return;
    }
    fprintf(fpWrite,"%s",info);  
    /*for(int i=1;i<num;i++)  {
        fprintf(fpWrite,"%d ",getptr(phead,i)->data);  
    }*/
    //fprintf(fpWrite,"%s:","\n");  
    fclose(fpWrite);  
}


static size_t config_httpCurlResCallback(char* buffer, size_t size, size_t nmemb, void* pUserArg)
{
    size_t len = 0;
    filesize += size * nmemb;
    printf("fsize=%d\r\n", filesize);
    strcat(pstr,buffer);
    printf("%s\n",pstr);
    len = size * nmemb;
    return len;
}


void  config_get(const char *url)
{
    CURL *pCurlHandle = curl_easy_init();
    curl_easy_setopt(pCurlHandle, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(pCurlHandle, CURLOPT_URL, url);
   
    //curl_easy_setopt(pCurlHandle, CURLOPT_WRITEDATA, para);
    curl_easy_setopt(pCurlHandle, CURLOPT_CONNECTTIMEOUT, 10);// 设置连接超时时间，单位s
	curl_easy_setopt(pCurlHandle, CURLOPT_TIMEOUT, 120);// 设置下载超时时间，单位s
	curl_easy_setopt(pCurlHandle, CURLOPT_NOSIGNAL, 1L);//接收数据时超时设置，如果10秒内数据未接收完，直接退出
    curl_easy_setopt(pCurlHandle, CURLOPT_MAXREDIRS, 1);//查找次数，防止查找太深
    curl_easy_setopt(pCurlHandle, CURLOPT_WRITEFUNCTION, config_httpCurlResCallback);
    CURLcode nRet = curl_easy_perform(pCurlHandle);
    curl_easy_cleanup(pCurlHandle);
}

void config_parse(configuration* config){

     //写入
    printf("%s\n",pstr);
    info_write((char *)pstr);

    cJSON *root0 = cJSON_Parse(pstr);
    cJSON *item = cJSON_GetObjectItem(root0, "data");
    cJSON *item1 = cJSON_GetObjectItem(item,"algorithmConfig");
    char *value= cJSON_GetStringValue(item1);
    cJSON * root = cJSON_Parse(value);
    int array_size = cJSON_GetArraySize(root);
    printf("%d\n",array_size);
    for (int i =0;i<array_size;i++){
        cJSON *item2 = cJSON_GetArrayItem(root, i);
        cJSON *item3  = cJSON_GetObjectItem(item2, "ruleName");
        cJSON *item5  = cJSON_GetObjectItem(item2, "poly");
        cJSON *item4 = cJSON_GetArrayItem(item5, 0);
        printf("%s\n",item3->valuestring);
        if (strcmp(item3->valuestring , "暴露垃圾")==0){//
            config->x1 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,0),"x")->valueint;
            config->y1 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,0),"y")->valueint;
            config->x2 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,1),"x")->valueint;
            config->y2 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,1),"y")->valueint;
            config->x3 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,2),"x")->valueint;
            config->y3 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,2),"y")->valueint;
            config->x4 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,3),"x")->valueint;
            config->y4 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,3),"y")->valueint;
        }else if (strcmp(item3->valuestring , "垃圾桶满溢")==0){//
            config->px1 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,0),"x")->valueint;
            config->py1 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,0),"y")->valueint;
            config->px2 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,1),"x")->valueint;
            config->py2 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,1),"y")->valueint;
            config->px3 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,2),"x")->valueint;
            config->py3 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,2),"y")->valueint;
            config->px4 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,3),"x")->valueint;
            config->py4 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,3),"y")->valueint;
        }else if (strcmp(item3->valuestring , "厨余未破袋")==0){
            config->bx1 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,0),"x")->valueint;
            config->by1 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,0),"y")->valueint;
            config->bx2 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,1),"x")->valueint;
            config->by2 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,1),"y")->valueint;
            config->bx3 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,2),"x")->valueint;
            config->by3 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,2),"y")->valueint;
            config->bx4 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,3),"x")->valueint;
            config->by4 =  cJSON_GetObjectItem(cJSON_GetArrayItem(item4,3),"y")->valueint;
        }
    }
    
    cJSON_Delete(root);
    cJSON_Delete(root0);

}

/*void config_parse(){


}*/


void config_read(configuration* config){
     //configuration config;

    config->x1 = 0;  /* set defaults */
    config->y1 = 0;
    config->x2 = 0;
    config->y2 = 0;
    config->x3 = 0;
    config->y3 = 0;
    config->x4 = 0;
    config->y4 = 0;
    config->rsh = 0;
    config->rsm = 0;
    config->reh = 0;
    config->rem = 0;
    config->rin = 0;
    config->px1 = 0;  /* set defaults */
    config->py1 = 0;
    config->px2 = 0;
    config->py2 = 0;
    config->px3 = 0;
    config->py3 = 0;
    config->px4 = 0;
    config->py4 = 0;
    config->wsh = 0;
    config->wsm = 0;
    config->weh = 0;
    config->wem = 0;
    config->win = 0;
    config->bx1 = 0;  /* set defaults */
    config->by1 = 0;
    config->bx2 = 0;
    config->by2 = 0;
    config->bx3 = 0;
    config->by3 = 0;
    config->bx4 = 0;
    config->by4 = 0;
    config->bsh = 0;
    config->bsm = 0;
    config->beh = 0;
    config->bem = 0;
    config->bin = 0;
    config->osh = 0;
    config->osm = 0;
    config->oeh = 0;
    config->oem = 0;
    config->oin = 0;
    config->psh = 0;
    config->psm = 0;
    config->peh = 0;
    config->pem = 0;
    config->pin = 0;
    config->work_conf = 0;
    config->person_conf = 0;
    config->rubbish_conf = 0;
    config->last_time = 0;
    config->upload_count = 0;
    config->bagtag = NULL;
    config->overtag = NULL;
    config->overtip = NULL;
    config->rubbishtag = NULL;
    config->rubbishtip = NULL;
    config->persontag = NULL;
    config->persontip = NULL;
    config->workertag = NULL;
    config->workertip = NULL;
    config->bagtip = NULL;
    config->url = NULL;
    config->savepath = NULL;
    config->ugurl = NULL;
    config->cgurl = NULL;

    if (ini_parse("../data/alarm.ini", handler, config) < 0) {
        printf("Can't load 'alarm.ini'\n");
    }
}

void json_read(configuration* config){

    FILE *fp = NULL;
    char *buf;

    if (NULL != (fp = fopen("../data/config.json", "rb")))    // 打开文件
    {
        fseek(fp, 0, SEEK_END);
        long len = ftell(fp);        // 文件长度
        fseek(fp, 0, SEEK_SET);
        if (len < 0)
        {
            printf("invalid path\n");
        }

        // 根据文件大小申请内存空间, 多申请1个字节存放'\0'
        buf = (char *)malloc(len + 1);
        if (buf == NULL)
        {
            printf("No enough memory.");
            exit(0);
        }
        // 读取文件内容至buf
        int nread = fread(buf, len, 1, fp);
        if (!nread)
        {
            printf("Failed to read the config file.");
        }
        // 关闭文件
        fclose(fp);

        // 字符串结尾
        buf[len] = '\0'; // end of string*/
        printf("len:%d\n", len);
        printf("buf:%s\n", buf);
        //json_parse(buf);
        cJSON *json;
        json = cJSON_Parse(buf); // 解析json结构
        if (json == NULL)
        {
            free(buf);
            printf("Failed to parse the json file\n");
            //continue;
        }
        free(buf);
        char *out = cJSON_Print(json);
        printf("read json:%s\n", out);   // 打印解析的json结构
        //rubbish
        cJSON * ritem = cJSON_GetObjectItem(json,"rubbish");
        printf("platform:%s\n", cJSON_GetObjectItem(ritem,"platform")->valuestring); 
        cJSON * ritem1 = cJSON_GetObjectItem(ritem,"exclusionZone");
        cJSON *ritem2 = cJSON_GetArrayItem(ritem1, 0);
        config->x1 =  cJSON_GetArrayItem(ritem2, 0)->valueint;
        config->y1 =  cJSON_GetArrayItem(ritem2, 1)->valueint;
        cJSON *ritem3 = cJSON_GetArrayItem(ritem1, 1);
        config->x2 =  cJSON_GetArrayItem(ritem3, 0)->valueint;
        config->y2 =  cJSON_GetArrayItem(ritem3, 1)->valueint;
        cJSON *ritem4 = cJSON_GetArrayItem(ritem1, 2);
        config->x3 =  cJSON_GetArrayItem(ritem4, 0)->valueint;
        config->y3 =  cJSON_GetArrayItem(ritem4, 1)->valueint;
        cJSON *ritem5 = cJSON_GetArrayItem(ritem1, 3);
        config->x4 =  cJSON_GetArrayItem(ritem5, 0)->valueint;
        config->y4 =  cJSON_GetArrayItem(ritem5, 1)->valueint;
        printf("x1:%d\n", config->x1);
        //over
        cJSON * oitem = cJSON_GetObjectItem(json,"person");
        printf("platform:%s\n", cJSON_GetObjectItem(oitem,"platform")->valuestring); 
        cJSON * oitem1 = cJSON_GetObjectItem(oitem,"exclusionZone");
        
        cJSON *oitem2 = cJSON_GetArrayItem(oitem1, 0);
        config->px1 =  cJSON_GetArrayItem(oitem2, 0)->valueint;
        config->py1 =  cJSON_GetArrayItem(oitem2, 1)->valueint;
        cJSON *oitem3 = cJSON_GetArrayItem(ritem1, 1);
        config->px2 =  cJSON_GetArrayItem(oitem3, 0)->valueint;
        config->py2 =  cJSON_GetArrayItem(oitem3, 1)->valueint;
        cJSON *oitem4 = cJSON_GetArrayItem(ritem1, 2);
        config->px3 =  cJSON_GetArrayItem(oitem4, 0)->valueint;
        config->py3 =  cJSON_GetArrayItem(oitem4, 1)->valueint;
        cJSON *oitem5 = cJSON_GetArrayItem(ritem1, 3);
        config->px4 =  cJSON_GetArrayItem(oitem5, 0)->valueint;
        config->py4 =  cJSON_GetArrayItem(oitem5, 1)->valueint;
        
        printf("x1:%d\n", config->px1);

        //bag
        cJSON * bitem = cJSON_GetObjectItem(json,"bag");
        printf("platform:%s\n", cJSON_GetObjectItem(bitem,"platform")->valuestring); 
        cJSON * bitem1 = cJSON_GetObjectItem(bitem,"exclusionZone");
        
        cJSON *bitem2 = cJSON_GetArrayItem(bitem1, 0);
        config->bx1 =  cJSON_GetArrayItem(bitem2, 0)->valueint;
        config->by1 =  cJSON_GetArrayItem(bitem2, 1)->valueint;
        cJSON *bitem3 = cJSON_GetArrayItem(ritem1, 1);
        config->bx2 =  cJSON_GetArrayItem(bitem3, 0)->valueint;
        config->by2 =  cJSON_GetArrayItem(bitem3, 1)->valueint;
        cJSON *bitem4 = cJSON_GetArrayItem(bitem1, 2);
        config->bx3 =  cJSON_GetArrayItem(bitem4, 0)->valueint;
        config->by3 =  cJSON_GetArrayItem(bitem4, 1)->valueint;
        cJSON *bitem5 = cJSON_GetArrayItem(ritem1, 3);
        config->bx4 =  cJSON_GetArrayItem(bitem5, 0)->valueint;
        config->by4 =  cJSON_GetArrayItem(bitem5, 1)->valueint;
        
        printf("bx1:%d\n", config->bx1);
        cJSON_Delete(json);

        
        // 进行后续处理
    }
}








//encrypt
static size_t p_httpCurlResCallback(char* buffer, size_t size, size_t nmemb, void* pUserArg)
{
    size_t len = 0;
    printf("%s; buffer = %s\n", __FILE__, buffer);

    cJSON *root = cJSON_Parse(buffer);
    cJSON *child = cJSON_GetObjectItem(root, "code");
	auth = child->valueint;
    printf("auth:%d\n",child->valueint);
	//g_app_global.auth=child->valueint;
    cJSON_Delete(root);
    len = size * nmemb;
    return len;
}


void p_upload(const char* url, char* payload ){

     CURL *curl = curl_easy_init();
     curl_easy_setopt(curl, CURLOPT_URL, url);
	 curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, p_httpCurlResCallback);

     // 添加配置表单
     curl_mime *multipart = curl_mime_init(curl);
     curl_mimepart *part = curl_mime_addpart(multipart);
     curl_mime_name(part, "payload");
     curl_mime_data(part, payload, CURL_ZERO_TERMINATED);
    
     curl_easy_setopt(curl, CURLOPT_MIMEPOST, multipart);

     CURLcode rescode = curl_easy_perform(curl);
     curl_mime_free(multipart);
     curl_easy_cleanup(curl);

}

/*************************************************
  Function:    		base64Encode
  Description:		base64 编码
  Input:
  	1.input			需编码的数据字符串
  	2.length		实际长度（不可使用strlen求取，字符串中可能含有结束符等）
  	3.newLine
  Output:			
  Return:			转化后的字符串指针
  Others:			
*************************************************/
char * base64Encode(const char *buffer, int length, int newLine)
{
    BIO *bmem = NULL;
    BIO *b64 = NULL;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    if (!newLine) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, buffer, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    BIO_set_close(b64, BIO_NOCLOSE);

    char *buff = (char *)malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;
    BIO_free_all(b64);

    return buff;
}

/*************************************************
  Function:    		base64Decode
  Description:		base64 解码
  Input:
  	1.input			需解码的数据字符串
  	2.length		实际长度（不可使用strlen求取，字符串中可能含有结束符等）
  	3.newLine
  Output:			
  Return:			转化后的字符串指针
  Others:			
*************************************************/
char * base64Decode(char *input, int length, int newLine)
{
    BIO *b64 = NULL;
    BIO *bmem = NULL;
    char *buffer = (char *)malloc(length);
    memset(buffer, 0, length);
    b64 = BIO_new(BIO_f_base64());
    if (!newLine) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    BIO_read(bmem, buffer, length);
    BIO_free_all(bmem);

    return buffer;
}

#define AES_DEBUG

/*************************************************
  Function:    		aes_ecb_pkcs5padding_encrypt
  Description:		AES加密
  Input:
  Output:			
  Return:			
  Others:			
*************************************************/
int aes_ecb_pkcs5padding_encrypt(const char *in, char *out, const unsigned char *key, const int keybits)
{
	AES_KEY aes;
	unsigned char *input_string;
	unsigned char *encrypt_string;
	unsigned int surplus_len;
	char b; 
	char *tmp_out;
	const char *tmp_in;
	int encrypt_quit = 0;
	
	if(in == NULL || out == NULL)
	{
		#ifdef AES_DEBUG
		printf("[%s] [%d] \"in\" or \"out\" point error!!\n", __FILE__, __LINE__);
		#endif
	}
	
	input_string = (unsigned char*)calloc(AES_BLOCK_SIZE, sizeof(unsigned char));
	if (input_string == NULL) 
	{
		#ifdef AES_DEBUG
		printf("[%s] [%d] input_string error!!\n", __FILE__, __LINE__);
		#endif
		fprintf(stderr, "Unable to allocate memory for input_string\n");
		exit(-1);
	}

	encrypt_string = (unsigned char*)calloc(AES_BLOCK_SIZE, sizeof(unsigned char));
	if (encrypt_string == NULL) 
	{
		#ifdef AES_DEBUG
		printf("[%s] [%d] encrypt_string error!!\n", __FILE__, __LINE__);
		#endif
		fprintf(stderr, "Unable to allocate memory for encrypt_string\n");
		return -1;
	}
	
	memset(encrypt_string, 0, AES_BLOCK_SIZE);
	// set encrypt key
	if (AES_set_encrypt_key(key, 128, &aes) < 0) 
	{
		#ifdef AES_DEBUG
		printf("[%s] [%d] AES_set_encrypt_key error!!\n", __FILE__, __LINE__);
		#endif
		fprintf(stderr, "Unable to set encryption key in AES\n");
		return -1;
	}
	
	tmp_in = in;
	tmp_out = out;
	while(!encrypt_quit)
	{
		if(strlen(tmp_in) == 0)
		{
			#ifdef AES_DEBUG
			//printf("[%s] [%d] (strlen(tmp_in) == 0) \n", __FILE__, __LINE__);
			#endif
			surplus_len = AES_BLOCK_SIZE;
			b = '\0'+surplus_len;
			memset(input_string, b, AES_BLOCK_SIZE);
			encrypt_quit = 1;
		}
		else if(strlen(tmp_in)/AES_BLOCK_SIZE > 0)
		{
			#ifdef AES_DEBUG
			//printf("[%s] [%d] (strlen(tmp_in)/AES_BLOCK_SIZE > 0) \n", __FILE__, __LINE__);
			#endif
			memcpy(input_string, tmp_in, AES_BLOCK_SIZE);
		}
		else
		{
			// daisy 加密数据应为16字节的整数倍，若不是则需填充。
			//填充方式为:surplus_len = AES_BLOCK_SIZE - (strlen(tmp_in)%AES_BLOCK_SIZE)
			//(即以所需不齐的数值作为填充值，填充剩余空缺)
			#ifdef AES_DEBUG
			printf("[%s] [%d] else \n", __FILE__, __LINE__);
			#endif
			surplus_len = AES_BLOCK_SIZE - (strlen(tmp_in)%AES_BLOCK_SIZE);
			b = '\0'+surplus_len;
			memset(input_string, b, AES_BLOCK_SIZE);
			memcpy(input_string, tmp_in, strlen(tmp_in));
			encrypt_quit = 1;
		}
		
		#ifdef AES_DEBUG
		//printf("input_string: %s\n", input_string);
		#endif
		memset(encrypt_string, 0, AES_BLOCK_SIZE);
		AES_ecb_encrypt(input_string, encrypt_string, &aes, AES_ENCRYPT);
		#ifdef AES_DEBUG
		//printf("encrypt_string: %s\n", encrypt_string);
		#endif
		memcpy(tmp_out, encrypt_string, AES_BLOCK_SIZE);
		tmp_out += AES_BLOCK_SIZE;
		tmp_in += AES_BLOCK_SIZE;
	}
	
	free(input_string);
	free(encrypt_string);
	return 0;
}

/*************************************************
  Function:    		aes_ecb_pkcs5padding_decrypt
  Description:		AES解密
  Input:
  Output:			
  Return:			
  Others:			
*************************************************/
int aes_ecb_pkcs5padding_decrypt(char* in, char* key, char* out)
{
    if(!in || !key || !out) return 0;
    AES_KEY aes;
    if(AES_set_decrypt_key((unsigned char*)key, 128, &aes) < 0)
    {
        return 0;
    }
    int len=strlen(in), en_len=0;
    while(en_len<len)
    {
    	AES_decrypt((unsigned char*)in, (unsigned char*)out, &aes);
    	in+=AES_BLOCK_SIZE;
    	out+=AES_BLOCK_SIZE;
    	en_len+=AES_BLOCK_SIZE;
    }
    return 1;
}

void encrypt_alg(configuration *config,char *serial){
    /*time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	printf("%d\\%d\\%d ",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday);
	printf("%d:%d:%d\n",p->tm_hour+8,p->tm_min,p->tm_sec);*/
	char *nian;char *yue;char *ri;char *shi;char *fen;char *miao;

	//nian = itoa(1900+p->tm_year);

    DHOP_SYS_LocalTime pLocalTime;
    int ret = DHOP_SYS_getLocalTime(&pLocalTime);
    
    int         y,m,d,h,n,s;
    y   =   pLocalTime.year;     //年
    m   =   pLocalTime.mon;             //月
    d   =   pLocalTime.mday;               //日
    h   =   pLocalTime.hour;               //时
    n   =   pLocalTime.min;                 //分
    s   =   pLocalTime.sec;                 //秒
    //int totals = h*24*60 + n*60 + s;
    nian =itoa(y);
    //printf("time = %d\\%d\\%d\\%d\\%d\\%d \n", y,m,d,h,n,s);
    
    char *b="0";
    char *s0 = join(nian,"-");

	//printf("nian = %s \n", nian);
	if (m>9){
		yue = itoa(m);
	}else{
		yue = join(b,itoa(m));
	}
    char *s1= join(s0,yue);
	char *s2=join(s1,"-");

	if(d>9){
		ri = itoa(d);
	}else{
		ri=join(b,itoa(d));
	}
    char *s3=join(s2,ri);
	char *s4=join(s3," ");

	if(h>9){
		shi = itoa(h);
	}else{
		shi = join(b,itoa(h));
	}
    char *s5=join(s4,shi);
	char *s6=join(s5,":");

	if(n>9){
		fen = itoa(n);
	}else{
		fen=join(b,itoa(n));
	}
    char *s7 =join(s6,fen);
	char *s8=join(s7,":");

	if(s>9){
		miao=itoa(s);
	}else{
		miao=join(b,itoa(s));
	}
	//printf("time = %s%s%s%s%s%s \n", nian,yue,ri,shi,fen,miao);
	char *s9 =join(s8,miao);
	printf("time = %s \n", s9);
	char *r0=join(serial,",");
	char *r1=join(r0,config->authcode);
	char *r2=join(r1,",");
	char *r3=join(r2,s9);
	const char *data =r3;
	int num = 0;
	char aes_encrypt_out[256];
	char aes_decrypt_out[256];
	memset(aes_encrypt_out, 0, sizeof(aes_encrypt_out));
	memset(aes_decrypt_out, 0, sizeof(aes_decrypt_out));
	printf("data = %s \n", data);
	aes_ecb_pkcs5padding_encrypt(data, aes_encrypt_out,(const unsigned char *) "BFMl72cVHNwSe@Kv", strlen("BFMl72cVHNwSe@Kv")*8);
	//printf("aes_encrypt_out = %s  \n", aes_encrypt_out);
	// daisy 实际长度（不可使用strlen求取，字符串中可能含有结束符等）
	// 简单粗暴的方法。判断从当前指针指向的字符开始，往后3位均为空，则判定当前到达字符串末尾
	while(!((*(aes_encrypt_out + num) == NULL) && (*(aes_encrypt_out + num + 1) == NULL) \
		&& (*(aes_encrypt_out + num + 2) == NULL) && (*(aes_encrypt_out + num + 3) == NULL)))
	{
//		printf("*(aes_encrypt_out + %d) = %c \n", num, *(aes_encrypt_out + num));
		num++;
	}
	//printf("num = %d \n", num);

	char * encode = base64Encode(aes_encrypt_out, num, 0);
	//printf("after base64Encode:%s\n", encode);

	const char* url =config->purl;
	p_upload(url,encode);

}






