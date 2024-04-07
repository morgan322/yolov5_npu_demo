#define _CRT_SECURE_NO_WARNINGS 1
#include "List.h"

//初始化双链表
LTNode* ListInit()
{
	//创建哨兵位头结点
	LTNode* guard = (LTNode*)malloc(sizeof(struct ListNode));
	if (guard == NULL)
	{
		perror("malloc fail");
		return NULL;
	}

	//让双链表具有双向循环结构
	guard->prev = guard;
	guard->next = guard;
	return guard;
}

//开辟新节点
LTNode* BuyLTNode(LTDataType x)
{
	LTNode* newnode = (LTNode*)malloc(sizeof(struct ListNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		return NULL;
	}
	newnode->data = x;
	newnode->prev = NULL;
	newnode->next = NULL;
	return newnode;
}

//打印链表数据
void ListPrint(LTNode* phead)
{
	assert(phead);  //因为链表是带头的，所以phead不可能为空
	LTNode* cur = phead->next;  //从第一个有效元素开始打印
	printf("head<=>");
	while (cur != phead)  //当cur回到头结点时循环结束
	{
		printf("%d<=>", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

//销毁链表
void ListDestory(LTNode* phead)
{
	assert(phead);  //链表带头
	LTNode* cur = phead->next;

	//释放掉除头结点以外的其他节点
	while (cur != phead)
	{
		LTNode* next = cur->next;
		free(cur);
		cur = next;
	}

	//释放头结点 (这里需要调用者在函数外部手动把phead置为NULL（要改变phead需要用二级指针或者函数返回值）
	free(phead);
}

//在头部插入数据
void ListPushFront(LTNode* phead, LTDataType x)
{
	assert(phead);
	ListInsert(phead->next, x);  //相当于第一个节点前面插入元素

	//assert(phead);  //因为链表是带头的，所以phead不可能为空
	//LTNode* newnode = BuyLTNode(x);
	//LTNode* first = phead->next;  //记录第一个节点

	//改变链接关系（当链表中没有节点，即只有一个头时，下面逻辑也正常）
	//phead->next = newnode;
	//newnode->prev = phead;
	//newnode->next = first;
	//first->prev = newnode;
}

//在尾部插入数据
void ListPushBack(LTNode* phead, LTDataType x)
{
	assert(phead);
	ListInsert(phead, x);  //相当于头结点前面插入元素

	//assert(phead);
	//LTNode* newnode = BuyLTNode(x);

	//找尾：头结点的prev指向链表的尾
	//LTNode* tail = phead->prev;

	//修改链接关系(当链表中没有节点时逻辑也成立）
	//phead->prev = newnode;
	//newnode->next = phead;
	//newnode->prev = tail;
	//tail->next = newnode;
}

//查找数据
LTNode* ListFind(LTNode* phead, LTDataType x)
{
	assert(phead);
	LTNode* cur = phead->next;
	//遍历链表，找到返回数据所在节点的地址
	while (cur != phead)
	{
		if (cur->data == x){
            return cur;
        }
			
		cur = cur->next;
	}
	//找不到就返回NULL
	return NULL;
}
/*
int eleFind(LTNode* phead,LTDataType x)
{
	assert(phead);
	LTNode* cur = phead->next;
	
	//遍历链表，找到返回数据所在节点的地址
	while (cur != phead)
	{
		if (cur->data == x){
            return 1;
        }
			
		cur = cur->next;
	}
	//找不到就返回NULL
	return 0;
}*/

//在pos位置之前插入数据
void ListInsert(LTNode* pos, LTDataType x)
{
	assert(pos);
	LTNode* newnode = BuyLTNode(x);

	//找pos的前一个节点
	LTNode* prev = pos->prev;

	//修改链接关系（当pos为第一个节点/最后一个节点时逻辑也成立）
	//ps：头插和尾插可以通过直接调用此函数来完成
	prev->next = newnode;
	newnode->prev = prev;
	newnode->next = pos;
	pos->prev = newnode;
}

//判断链表是否为空
bool IsEmpty(LTNode* phead)
{
	assert(phead);
	return phead == phead->next;  //当链表中只剩下头结点时链表为空，返回true
}

//在头部删除数据
void ListPopFront(LTNode* phead)
{
	assert(phead);
	assert(!IsEmpty(phead));  //删空时继续删除报错
	ListErase(phead->next->next);  //相当于删除第二个节点前的数据

	//assert(phead);
	//assert(!IsEmpty(phead));  //删空时继续删除报错
	//记录第一个节点的下一个节点
	//LTNode* second = phead->next->next;

	//释放第一个节点
	//free(phead->next);

	//修改链接关系
	//phead->next = second;
	//second->prev = phead;
}

//在尾部删除数据
void ListPopBack(LTNode* phead)
{
	assert(phead);
	assert(!IsEmpty(phead));  //删空时继续删除报错
	ListErase(phead);  //相当于删除头结点前的数据

	//assert(phead);
	//assert(!IsEmpty(phead));  //删空时继续删除报错
	//记录尾结点的上一个节点
	//LTNode* prev = phead->prev->prev;

	//释放尾结点
	//free(phead->prev);

	//修改链接关系
	//phead->prev = prev;
	//prev->next = phead;
}

//在pos位置之前删除数据
void ListErase(LTNode* pos)
{
	//这里有一个问题：pos不能是第一个节点的地址，因为我们不可能把哨兵位头结点给删除了，需要函数调用者自己注意
	assert(pos);
	//记录pos的前一个节点的前一个节点
	LTNode* prev = pos->prev->prev;

	//free pos前的节点
	free(pos->prev);

	//修改链接关系（当pos为第二个节点/头结点节点时逻辑也成立）
	//ps：头删和尾删可以通过直接调用此函数来完成
	prev->next = pos;
	pos->prev = prev;
}

//计算链表长度
size_t ListSize(LTNode* phead)
{
	assert(phead);
	size_t size = 0;
	LTNode* cur = phead->next;  //链表长度不包含头结点，因为头结点不存储有效数据
	while (cur != phead)
	{
		size++;
		cur = cur->next;
	}
	return size;
}

//修改链表数据
void ListModify(LTNode* pos, LTDataType x)
{
	assert(pos);
	pos->data = x;
}


//fun
LTNode* getptr(LTNode* head, int pos)
{
	LTNode *p = head;
	if (p == NULL || pos == 0)
	{
		return head;
	}
	for (int i = 0; p && i < pos; i++)
	{
		p = p->next;
	}
	return p;
}


LTNode* ruinfomatch(LTNode* head, int mp,int nc,int thod){
    
    LTNode* newinfolist = ListInit();
    for(int i = 0;i<4*nc;i+=4){
        int distnum = 0;
        for(int j = 0;j<4*mp;j+=4){
            
            //pre
            int x1 = (getptr(head,j + 3)->data + getptr(head,j + 1)->data)/2;
           // printf("x1:%d\n", x1);
            int y1 = (getptr(head,j + 4)->data + getptr(head,j + 2)->data)/2;
            //cur
            int x2 = (getptr(head,4*mp + i + 3 )->data + getptr(head,4*mp+ i +1 )->data)/2;
            //printf("x2:%d\n", x2);
            int y2 =(getptr(head,4*mp  + i + 4 )->data + getptr(head,4*mp+ i +2 )->data)/2;
            //printf("sqrt:%d\n", (x1-x2)*(x1-x2) );
            int dist = sqrt((x1-x2)*(x1-x2) +(y1-y2)*(y1-y2));
            //printf("dist:%d\n", dist);
            if (dist<thod){
                distnum++;
            }
        }
        //printf("distnum:%d\n", distnum);
        if (distnum==0){
            ListPushBack(newinfolist,  getptr(head,4*mp+ i +1 )->data);
            //printf("x1:%d\n",  getptr(head,4*mp+ i +1 )->data);
            ListPushBack(newinfolist,  getptr(head,4*mp+ i +2 )->data);
            ListPushBack(newinfolist,  getptr(head,4*mp+ i +3 )->data);
            ListPushBack(newinfolist,  getptr(head,4*mp+ i +4 )->data);
        }
    }
    return newinfolist;
}


int twoframematch(LTNode* head, int mp,int nc,int thod){

    int num1,num2;
    num1 = mp;
    num2 = nc;
    int **array = (int **)calloc(num1,sizeof(int *));//开辟空间，num1个一维int*型指针
    for(int i=0;i<num1;i++)
    {
        array[i] = (int *)calloc(num2,sizeof(int));     //给每个int *型指针分配内存
    }
    int pos;
    for(int i = 2;i<2*mp+2;i++){
        if (getptr(head,i)->data == 0){
            pos = i;
        }
    }

    //printf("%dpos\t",pos);
    
    for(int i=0; i< 2 * num1;i+=2)
    {
        //int px = 2i +1;
        for(int j=0;j<2 * num2;j+=2)

        {
            if (i<pos-2){
            // printf("%d\t",i+1);
                int x1 = getptr(head,i + 2)->data;
                printf("%d\n",x1);
                int y1 = getptr(head,i + 3)->data;
                int x2 = getptr(head,2 + 2 * num1 + j + 2)->data;
                int y2 = getptr(head,2 + 2 * num1 + j + 3)->data;
                array[i/2][j/2] = sqrt((x1-x2)*(x1-x2) +(y1-y2)*(y1-y2));
                printf("%d\t",array[i/2][j/2]);
             }else{
                int x1 = getptr(head,i+3)->data;
                printf("%d\n",x1);
                int y1 = getptr(head,i+4)->data;
                int x2 = getptr(head,2 + 2 * num1 + j + 2)->data;
                int y2 = getptr(head,2 + 2 * num1 + j + 3)->data;
                array[i/2][j/2] = sqrt((x1-x2)*(x1-x2) +(y1-y2)*(y1-y2));
                printf("%d\t",array[i/2][j/2]);

            }
            printf("\n");
        }
    }

    int nu1 = 1;
    int nu2 = nc;
    int *curflag=(int*)calloc(nu2,sizeof(int));

    for (int i=0; i<nc;i++){
        curflag[i] = -1;
    }
    
     int n1 = 1;
     int n2 = mp;
     int *preflag=(int*)calloc(n2,sizeof(int));
     /*int **preflag = (int **)calloc(n1,sizeof(int *));//开辟空间，num1个一维int*型指针
     for(int i=0;i<num1;i++)
    {
        curflag[i] = (int *)calloc(n2,sizeof(int));     //给每个int *型指针分配内存
    }*/

    for (int i=0; i<mp;i++){
        preflag[i] = -1;
        printf("%d\t",preflag[i]);
    }
    //printf("\n");

    for (int p = 0; p < nc; p++) {
		int k = 0;
		for (int q = 0; q < mp; q++) {
            printf("%d\t",array[p][q]);
			if (array[k][p] > array[q][p]) {  //min
				k = q;
			}
		}
		/*cout << k << endl;
		cout << p << endl;*/
        printf("%d\t",array[k][p]);
		if (array[k][p] < thod) {
            
			if (preflag[k] == -1) { //	
				//preflag[k] = p;
				curflag[p] = k;
				/*cout << p << endl;
				cout << k << endl;*/
                printf("%d\t",k);
			}
		}
        //printf("\n");
	}
    printf("\n");

    int matchnum = 0;

    for(int i=0 ; i < nc;i++){
        if (curflag[i]==-1){
            matchnum++;
        }
    }

    if(matchnum>0){
        return 1;
    }else{
        return 0;
    }

    for(int i=0;i<num1;i++)
    {
        free(array[i]);     // 释放第二维的内存
    }
    free(array);   
    free(curflag); 
    free(preflag);         // 释放第一维的内存
}


int Max(LTNode* phead)
{
	assert(phead);
	LTNode* cur = phead->next;
	int max = 0;
	//遍历链表，找到返回max数据所在节点的地址
	while (cur != phead)
	{
		if (cur->data >= max){
            max = cur->data ;
        }
			
		cur = cur->next;
	}
	//返回max
	return max;
}

void log_write(int num,char * type,LTNode* phead)  
{  
    //下面是写数据，将数字0~9写入到data.txt文件中  
    FILE * fpWrite  = fopen("../data/log.txt","a"); 
    int errNum = 0;
    if (fpWrite == NULL)
    {
            errNum = errno;
            //printf("[saveYuvFile] open fail errno = %d, reason = %s", errNum, strerror(errNum));
            return;
    }
    fprintf(fpWrite,"%s:",type);  
    for(int i=1;i<num;i++)  {
        fprintf(fpWrite,"%d ",getptr(phead,i)->data);  
    }
    fprintf(fpWrite,"%s:","\n");  
    fclose(fpWrite);  
} 