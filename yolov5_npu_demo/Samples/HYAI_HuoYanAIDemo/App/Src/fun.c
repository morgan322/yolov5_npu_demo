#include "fun.h"
//#include "CfgFile.h"


//function
char* itoa(int val)
{
    static char result[sizeof(int)<<3+2];
    sprintf(result,"%d",val);
    return result;
}

char* litoa(int val)
{
    static char result[sizeof(long long int)<<3+2];
    sprintf(result,"%d",val);
    return result;
}


char* fitoa(float val)
{
    static char result[sizeof(float)<<3+2];
    sprintf(result,"%f",val);
    return result;
}
                                        
time_t timeStamp()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}


/*调用库函数*/
char *join(const char *str1, const char *str2)
{
	char *result = (char *)malloc(strlen(str1) + strlen(str2) + 1);
	
	if(result == NULL)
		return NULL;
	
	strcpy(result, str1);
	//printf("%s\n", result);
	strcat(result, str2);
	
	return result;
}

char** split(char *str, char *delimiter) {
	int len = strlen(str);
	char *strCopy = (char*)malloc((len + 1) * sizeof(char)); //额外分配多一个字符空间来存储'\0'
	strcpy(strCopy, str); //复制str字符串
	//将strCopy中的每个分隔符赋值为'\0'
	for (int i = 0; strCopy[i] != '\0'; i++) {
		for (int j = 0; delimiter[j] != '\0'; j++) {
			if (strCopy[i] == delimiter[j]) {
				strCopy[i] = '\0';
				break;
			}
		}
	}
	//为字符串数组分配空间,额外分配多一个字符串指针并赋值为NULL来作为字符串结束标志
	char** res = (char**)malloc((len + 2) * sizeof(char*)); 
	len++; //遍历到strCopy最后的'\0'才结束
	int resI = 0; //每一个分隔符和原字符串的'\0'标志依次作为数组中的字符串的结束标志
	for (int i = 0; i < len; i++) {
		res[resI++] = strCopy + i;
		while (strCopy[i] != '\0') {
			i++;
		}
	}
	res[resI] = NULL; //字符串数组中结束标志
 
 
	return res;
}

int my_copy()
{

        int fd_src,fd_dest;
        char buf[DATA_SIZE];
        int count = 0;
        /*if(argc != 3 ) {

                perror("input error");
                return -1;
        }*/
        fd_src = open("alarm.ini",O_RDONLY);
        if(fd_src == -1){
                perror("open failed");
                return -1;
        }

        fd_dest = open("../data/alarm.ini",O_WRONLY | O_CREAT | O_EXCL,0700);
        if(fd_dest == -1){
                close(fd_src);
                perror("open failed");
                return -1;
        }
        while(1){
                count = read(fd_src,buf,DATA_SIZE);
                if(count == -1 ) {
                        perror("read failed");
                        return -1;
                }
                if(count == 0) break;
                write(fd_dest,buf,count);
        }
        close(fd_src);
        close(fd_dest);
}


int dou_post(char **str_ptr)
{
        int post_num = 0;
        while((**str_ptr >='0')&&(**str_ptr <= '9')){
                post_num = post_num * 10;
                post_num += (**str_ptr - 48);
                (*str_ptr)++;
        }
        if(**str_ptr == '.') (*str_ptr)--;
        return post_num;
 
}
 
double dou_point(char **str_ptr)
{
        double point_num = 0;
        if((**str_ptr >='0')&&(**str_ptr <= '9')){
                point_num = **str_ptr - 48;
                (*str_ptr)++;
                if((**str_ptr >='0')&&(**str_ptr <= '9')){
                        point_num += dou_point(str_ptr);
                }
        }
        if(**str_ptr == '\0') (*str_ptr)--;
        return point_num / 10;
}
 
// 字符串转double
double str_to_dou(char *str_ptr)
{
        int post_num = 0;
        double point_num = 0;
        int point_flag = 0;
        while(*str_ptr != '\0')
        {
            if(*str_ptr == '.')
                    point_flag = 1;
            else if(point_flag == 0)
                    post_num =dou_post(&str_ptr);
            else if(point_flag == 1)
                    point_num =dou_point(&str_ptr);
            str_ptr++;
 
        }
        return (double)post_num + point_num;
}



int RectInRect( Rect out,  Rect in)
{
	int bRet = 1;
	int x1 = out.ul.x;
	int y1 = out.ul.y;
	int x2 = out.lr.x;
	int y2 = out.lr.y;

	int x3 = in.ul.x;
	int y3 = in.ul.y;
	int x4 = in.lr.x;
	int y4 = in.lr.y;

	bRet = (((x1 >= x3 && x1 < x4) || (x3 >= x1 && x3 <= x2)) &&
		((y1 >= y3 && y1 < y4) || (y3 >= y1 && y3 <= y2))) ? 1 : 0;
        //printf("bRet: %d\n", bRet);
	return bRet;
}


/*void MyWrite(char* value)
{
    //char key[128] = { 0 };
    //char value[128] = { 0 };
    //int valuelen = 0;
    int ret = 0;
   
   ret = WriteCfgFile(CfgFileName, "hydeviceCode", value);
    
    if (ret != 0)
    {
        printf("写入key:%s,value:%s,失败\n", "hydeviceCode",value);
        return ;
    }
    printf("写入key:%s,value:%s,成功\n", "hydeviceCode", value);
}*/



int isPointInRect(int x, int y,int x1,int x2,int x3,int x4,int y1, int y2,int y3,int y4)
{

    /*printf("Config loaded from 'test.ini': version=%d, name=%s, email=%s\n",
        config.version, config.name, config.email);*/
	int a, b, c,d;//分别存四个向量的计算结果;
	a = (x2 - x1)*(y - y1) - (y2 - y1)*(x - x1);  
        b = (x3 - x2)*(y - y2) - (y3 - y2)*(x - x2);  
        c = (x4 - x3)*(y - y3) - (y4 - y3)*(x - x3);  
        d = (x1 - x4)*(y - y4) - (y1 - y4)*(x - x4);  
        if((a > 0 && b > 0 && c > 0 && d > 0) || (a < 0 && b < 0 && c < 0 && d < 0)) 
   	 {  
                return 1;  
        }  
	else
	{
  		return 0;
 	}
 }

 int isTimeScale(int startTimeHour, int startTimeMin, int endTimeHour, int endTimeMin,int nowhour, int nowmin)
{
	
	int startMin = startTimeHour * 60 + startTimeMin;
	int endMin = endTimeHour * 60 + endTimeMin;
	int curMin = nowhour * 60 + nowmin;
	
	if (startMin < endMin)
	{
		if (startMin <= curMin && curMin <= endMin)
		{
			return 1;
		}
	}
	
	else if (startMin > endMin)
	{
		if (startMin <= curMin || curMin <= endMin)
		{
			return 1;
		}
	}
	return 0;
}

