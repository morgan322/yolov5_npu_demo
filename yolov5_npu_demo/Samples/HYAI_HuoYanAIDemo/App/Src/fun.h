#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/stat.h>


#define DATA_SIZE 30
#define _CRT_SECURE_NO_WARNINGS 1
typedef struct
{
    int    x;  /**< x-axis position */
    int    y;  /**< y-axis position */ 
} Point;

typedef struct
{   
    Point   ul; /**< upper-left corner point */
    Point   lr; /**< lower-right corner point */     
} Rect;

char* itoa(int val);
char* litoa(int val);
char* fitoa(float val);
time_t timeStamp();
char *join(const char *str1, const char *str2);
char** split(char *str, char *delimiter);
int my_copy();
int dou_post(char **str_ptr);
double dou_point(char **str_ptr);
double str_to_dou(char *str_ptr);
int RectInRect( Rect out,  Rect in);
//void MyWrite(char* value);
int isPointInRect(int x, int y,int x1,int x2,int x3,int x4,int y1, int y2,int y3,int y4);
 int isTimeScale(int startTimeHour, int startTimeMin, int endTimeHour, int endTimeMin,int nowhour, int nowmin);
 
