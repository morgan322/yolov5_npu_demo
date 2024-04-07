#pragma once  //防止头文件重复包含

//头文件的定义
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>


//结构和符号的定义
typedef int LTDataType;
typedef struct ListNode
{
	LTDataType data;          //用于存放数据
	struct ListNode* prev;    //用于存放下一个节点的地址
	struct ListNode* next;    //用于存放上一个节点的地址
}LTNode;

//函数的声明
//初始化双链表
LTNode* ListInit();
//开辟新节点
LTNode* BuyLTNode(LTDataType x);
//打印链表数据
void ListPrint(LTNode* phead);
//销毁链表
void ListDestory(LTNode* phead);
//在头部插入数据
void ListPushFront(LTNode* phead, LTDataType x);
//在尾部插入数据
void ListPushBack(LTNode* phead, LTDataType x);
//查找数据
LTNode* ListFind(LTNode* phead, LTDataType x);
//int eleFind(LTNode* phead,LTDataType x);
//在pos位置之前插入数据
void ListInsert(LTNode* pos, LTDataType x);
//判断链表是否为空
bool IsEmpty(LTNode* phead);
//在头部删除数据
void ListPopFront(LTNode* phead);
//在尾部删除数据
void ListPopBack(LTNode* phead);
//在pos位置之前删除数据
void ListErase(LTNode* pos);
//计算链表长度
size_t ListSize(LTNode* phead);
//修改链表数据
void ListModify(LTNode* pos, LTDataType x);

//fun
LTNode* getptr(LTNode* head, int pos);
LTNode* ruinfomatch(LTNode* head, int mp,int nc,int thod);
int twoframematch(LTNode* head, int mp,int nc,int thod);
int Max(LTNode* phead);
void log_write(int num,char * type,LTNode* phead)  ;