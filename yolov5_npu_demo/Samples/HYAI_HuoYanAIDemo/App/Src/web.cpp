#include <string>
#include <vector>
#include "web.h"



#ifdef __cplusplus
extern "C"{
#endif

    static webCallback callback;
    
    DHOP_WEB_Point point_array[20];

    static DH_Int32 doGet(const DHOP_HTTP_Request *request, const DHOP_HTTP_Response *response)
    {
        // 如果请求是获取配置，则返回配置
        // GET /DHOP_API/DhopSmpAI/getConfig?session=53dd8010c0916902fa346977b9418e78
        // if (strncmp(request->header->url, "/DHOP_API/DhopSmpAI/getConfig", 29) == 0)
        // {
        char *buffer = NULL;
        const char* ackBuf = NULL;
        int length = 0;
        FILE *fp = fopen("../data/config.json", "rb");
        if (fp != NULL)
        {
            // 获取文件长度
            fseek(fp, 0, SEEK_END);
            length = ftell(fp);
            fseek(fp, 0, SEEK_SET);

            // 申请内存
            buffer = (char *)malloc(length);
            if (buffer != NULL)
            {
                // 将内容读到内存中
                fread(buffer, sizeof(char), length, fp);
            }
            fclose(fp);
            ackBuf = buffer;
        }
        else
        {
            // 打开文件失败，返回一个固定的默认值
            ackBuf = "{"
                    "\"snap\":true,"
                    "\"box\":true,"
                    "\"direction\":\"A2B\","
                    "\"objects\":\"Vehicle\","
                    "\"detectRegion\":[[1675, 1716],[6444, 6799]],"
                    "\"alarmLine\":[[5060, 615],[4314, 7641]]"
                    "}";
            length = strlen(ackBuf);
        }
        if (ackBuf != NULL)
        {
            // 告诉Web浏览器，这个是一个JSON数据格式
            response->addHeader(request->token, "Content-Type", "application/json");
            response->setContentLength(request->token, length);
            response->writeContent(request->token, ackBuf, length);
            response->writeEnd(request->token);
        }

        // 内容是通过打开文件的形式，内容是申请出来的内存，所以要释放
        if (buffer)
        {
            free(buffer);
        }
        // }
        return 0;
    }

    static DH_Int32 doPost(const DHOP_HTTP_Request *request, const DHOP_HTTP_Response *response)
    {
        int i = 0;
        int n = 0;
        int m = 0;
        int ret =0;
        int contentLength = 4096;
        char *buffer = NULL;
        char ackBuf[32];

        // 从HTTP请求头中，获取Content-Length，表示数据的长度
        n = request->header->numOfHeader;
        for (i = 0; i < n; i++)
        {
            if (!strcmp(request->header->headers[i].key, "Content-Length"))
            {
                contentLength = atoi(request->header->headers[i].value);
                DHOP_LOG_INFO("contentLength=%d\n", contentLength);
                DHOP_LOG_INFO("url is %s\n", request->header->url);
                DHOP_LOG_INFO("http version is %d\n", request->header->version);
                DHOP_LOG_INFO("method is %d\n", request->header->method);
                break;
            }
        }
        if (contentLength > 0 && contentLength < 4096)
        {
            buffer = (char *)malloc(contentLength + 1);
            //DHOP_LOG_INFO("buffer = %p\n", buffer);
        }

    
        if (buffer != NULL)
        {
            // 读取请求的内容
            n = 0;
            m = contentLength;
            while (n < contentLength)
            {
                ret = request->readContent(request->token, buffer, (DH_Uint32 *)&m);
                if (ret != 0)
                {
                    break;
                }
                n += m;
            }
            buffer[n] = 0;
            DHOP_LOG_INFO("buffer = %s\n", buffer);
            std::string data(buffer);

            webstr= (char *)data.c_str();

            printf("webstr = %s \n", webstr);
            //std::string temstr = data.substr(data.find_first_of('[')+1);

           /* int pos= -1;
            int index = 0;
            while (pos = temstr.find(']'))
            {
                if (pos == -1) 
                {
                    break;
                }
                std::string tr = temstr.substr(temstr.find_first_of('['), temstr.find_first_of(']')+1);
                point_array[index].x = atoi(tr.substr(temstr.find_first_of('[') + 1, temstr.find_first_of(',')).c_str());
                point_array[index].y = atoi(tr.substr(temstr.find_first_of(',') + 1, temstr.find_first_of(']')).c_str());
                index++;
                temstr = temstr.substr(pos + 2);
            }
            //std::string data(buffer);*/
            callback(webstr);
            
            //写入
            FILE *fp = fopen("../data/config.json", "wb");
            if (fp != NULL)
            {
                int n=fwrite(buffer, strlen(buffer) , 1, fp );
                fclose(fp);    
            }
            // 释放内存
            free(buffer);
            buffer = NULL;

            // 按照HTTP规范，回复成功，使用"200 OK"
            response->setCode(request->token, DHOP_HTTP_StatusCode_200_OK);

            n = sprintf(ackBuf, "{\"status\":\"OK\"}");
            ackBuf[n] = 0;
        }
        else
        {
            // 按照HTTP规范，回复失败，使用"400 Bad Request"
            response->setCode(request->token, DHOP_HTTP_StatusCode_400_Bad_Request);
            n = sprintf(ackBuf, "{\"status\":\"Error\"}");
            ackBuf[n] = 0;
        }
        // 告诉Web浏览器，这个是一个JSON数据格式
        response->addHeader(request->token, "Content-Type", "application/json");
        response->setContentLength(request->token, n);
        response->writeContent(request->token, ackBuf, n);
        response->writeEnd(request->token);
        return 0;
    }

    static DH_Int32 ServletRequest(const DHOP_HTTP_Request *request, const DHOP_HTTP_Response *response)
    {
        if (!request->token)
        {
            DHOP_LOG_ERROR("ServletRequest token is null\n");
            return -1;
        }

        // 打印一下请求的信息
        if (request->header->method == DHOP_HTTP_METHOD_GET)
        {
            DHOP_LOG_INFO("GET %s\n", request->header->url);
            return doGet(request, response);
        }

        if (request->header->method == DHOP_HTTP_METHOD_POST)
        {
            DHOP_LOG_INFO("POST %s\n", request->header->url);
            return doPost(request, response);
        }

        // 只支持GET/POST，其它方式是不支持
        response->setContentLength(request->token, 0);
        response->setCode(request->token, DHOP_HTTP_StatusCode_501_Not_Implemented);
        return 0;
    }


    int DHOP_WEB_init(webCallback cb)
    {
        DH_Int32 ret = -1;
        DHOP_APP_ConfigParam appCfg;
        DH_Char webUrl[32] = "index.html";
        memset(&appCfg, 0, sizeof(appCfg));
        appCfg.weburl = webUrl;
        appCfg.urllen = strlen(webUrl);
        DHOP_APP_setConfig(&appCfg);
     
        callback = cb;

        DHOP_HTTP_AppDefinition stDef = {
            0,
        };
        stDef.cbSize = sizeof(stDef);
        stDef.timeout = 1 * 1000;
        stDef.servlet = &ServletRequest;
        ret = DHOP_HTTP_online(&stDef);
        if (ret != 0)
        {
            DHOP_LOG_ERROR("DHOP_HTTP_online fail:%d\n", ret);
            return -1;
        }
        DHOP_LOG_INFO("DHOP_HTTP_online suscess ");
        
        return -1;
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */

