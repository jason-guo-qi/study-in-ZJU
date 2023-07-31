#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "imgui.h"
#include "Main.h"
#include "Add.h"
#include "Administrater.h"
#include "DateSearch.h"
#include "Delete.h"
#include "Feedback.h"
#include "LocationSearch.h"
#include "Reserve.h"
#include "Sort.h"
#include "Unsubmit.h"
#include "User.h"
#include "FunctionLib.h"

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h> 
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <string.h>
#include <math.h>

double x;
double y;
double w;
double h;
double fH;

double label_x = 1.0;

int SearchFlag = 0;  //0需要输入查找信息；1将所查找内容输出；-1没有查找到相关内容
char input_of_search[15] = "";

Product* Head_Product = NULL;
Product* Search_Product = NULL;
Product* Temp_Product = NULL;
Product* Order_Product = NULL;
 
Product* Headd_Product = NULL;
Product* Tempp_Product = NULL;
Product* Orderr_Product = NULL;

Product* Head_FeedProduct = NULL;
Product* Search_FeedProduct = NULL;
Product* Temp_FeedProduct = NULL;
Product* Order_FeedProduct = NULL;

double winwidth, winheight;   // 窗口尺寸
int status = 0;   //记录系统状态  

int ReserveFlag = 0;//0处于输入产品编号界面，1表示预定成功界面，2表示已经预订过产品；-1处于找不到产品界面
char ReserveNum[10] = "";

int UnsubFlag = 0;//0处于输入产品编号界面，1表示退订成功界面，2表示未预订过该产品；-1处于找不到产品界面
char UnsubNum[10] = "";

int OrderWay;//1表示按价格排序，2表示按销量排序
int OrderFlag = 0;

int NewAddFlag = 0;//0处于输入产品编号界面，1处于成功界面，-1处于产品编号重复界面

int NewFeedFlag = 0;//0处于输入反馈界面，1处于成功界面，-1处于产品编号重复界面
 
int DeleteFlag = 0;//0处于输入产品编号界面，1处于删除成功界面，-1处于产品编号不存在界面
char  DeleteNum[10] = ""; 

int Returnflag = 0;//记录界面是从用户还是管理员界面进入的搜索、预订、排序界面，0返回用户界面，1返回管理员界面 

// 计时器启动函数，provided in libgraphics
void startTimer(int id, int timeinterval);

// 用户的字符事件响应函数
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI获取键盘
	display(); // 刷新显示
}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); //GUI获取鼠标
	display(); // 刷新显示
}

// 初始化窗口和图形系统
void InitWindow() 
{
	//窗口尺寸设置 
	SetWindowTitle("旅游产品管理系统");
	SetWindowSize(15, 10);
	InitGraphics();

	// 获得窗口尺寸
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	// 注册时间响应函数
	registerCharEvent(CharEventProcess);        // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	
	display();
}

//以双向链表结构顺序读取产品库的产品，返回链表头节点					 
Product* LoadProduct()
{
	int i, j;
	Product* head = NULL;
	Product* tail = NULL;
	Product* p = NULL;
	int size = sizeof(Product);
	p = (Product*)malloc(size);

	FILE* fp;
	fp = fopen("Data.txt", "r");
	if (fp == NULL) exit(-1);
	while (!feof(fp)) {
		fscanf(fp, "%s", p->Num);
		fscanf(fp, "%s", p->Location);
		fscanf(fp, "%s", p->Date);
		fscanf(fp, "%s", p->Price);
		fgetc(fp);
		fgets(p->Information, sizeof(p->Information), fp);
		fscanf(fp, "%s", p->Amount);
		fscanf(fp, "%s", p->SubFlag);
		p->Next = NULL;
		p->Last = NULL;
		if (head == NULL) {
			head = p;
		}
		else{
			tail->Next = p;
			tail->Next->Last = tail;
		}
		tail = p;
		head->Last = tail;
		p = (Product*)malloc(size);
	}
	tail->Next = NULL;
	fclose(fp);
	return head;
}



//将产品信息显示在界面上 
void drawProduct(double fH, double x, double y, double w, double h, Product* p)
{
	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("编号") - 1.2 * h, (y -= h * 1.2) + fH * 0.7, "编号");
	textbox(GenUIID(0), x - 1.2 * h, y, w, h, p->Num, sizeof(p->Num));

	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("地点") - 1.2 * h, (y -= h * 1.2) + fH * 0.7, "地点");
	textbox(GenUIID(0), x - 1.2 * h, y, w, h, p->Location, sizeof(p->Location));
	
	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("价格") - 1.2 * h, (y -= h * 1.2) + fH * 0.7, "价格");
	textbox(GenUIID(0), x - 1.2 * h, y, w, h, p->Price, sizeof(p->Price));

	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("出行日期") - 1.2 * h, (y -= h * 1.2) + fH * 0.7, "出行日期");
	textbox(GenUIID(0), x - 1.2 * h, y, w, h, p->Date, sizeof(p->Date));
	
	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("已售数量") - 1.2 * h, (y -= h * 1.2) + fH * 0.7, "已售数量");
	textbox(GenUIID(0), x - 1.2 * h, y, w, h, p->Amount, sizeof(p->Amount));
	
	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("详情介绍") - 1.2 * h, (y -= h * 1.2) + fH * 0.7, "详情介绍");
	textbox(GenUIID(0), x - 1.2 * h, y, w, h, p->Information, sizeof(p->Information));

	SetPenColor("Gray");
}

//返回当前节点的上一节点 
Product* PreProduct(Product* p1, Product* p2)
{
	Product* m;
	m = p2;
	while (m) {
		if (m->Next == p1) 
		break;
		m = m->Next;
	}
	if(m != NULL) return m; 
	else return NULL;
}

void display()
{ 	
	if (status == 0) //旅游产品管理系统主界面 Main 
	{
		SetPointSize(2);
        DisplayClear();
        drawMainButtons();
        drawMainBox();
        RollingSlogan();
        DrawleftArc();
        DrawrightArc();
	} 
	if (status == 1) //用户主界面 User
	{
		
		DisplayClear();
		drawUserButtons();
		drawUserMenu();
		drawUserProduct(fH, x, y, w, h, Temp_Product);
	} 
	if (status == 2) //管理员主界面 Administrater
	{
		DisplayClear();
		drawAdminButtons();
		drawAdminProduct();
		drawAdminBox();
		drawAdminMenu();
	}
	if (status == 3) //地点搜索界面 LocationSearch
	{
		DisplayClear();
		drawLocationSearchText();
		drawLocationSearchButtons();
		RollingSlogan(); 
	} 
	if (status == 4) //日期搜索界面 DateSearch
	{
		DisplayClear();
		drawDateSearchText();
		drawDateSearchButtons();
		RollingSlogan(); 
	} 
	if (status == 5) //预订界面 Reserve
	{
		DisplayClear();
		drawReserveText();
		drawReserveButtons();
		RollingSlogan();
	} 
	if (status == 6) //退订界面 Unsubmit
	{
		DisplayClear();
		drawUnsubText();
		drawUnsubButtons();
		RollingSlogan();
	} 
	if (status == 7) //排序界面 Sort
	{
		DisplayClear();
		drawSortText();
		drawSortButtons();
		RollingSlogan();
	} 
	if (status == 8) //新增产品界面 Add
	{
		DisplayClear();
		drawAddButtons(); 
 		drawAddText();
 		RollingSlogan();
	}
	if (status == 9) //删除产品界面 Delete
	{
		DisplayClear();
		drawDeleteText();
		drawDeleteButtons(); 
		RollingSlogan();
	} 	
	if (status == 10) //用户反馈界面Feedback
	{
		DisplayClear();
		drawFeedText();
		drawFeedButtons();
		RollingSlogan();
	 } 
}

//重写txt文本内容 
void fprintProduct(Product* p)
{
	FILE* fp;
	Product* p1 = p;
	fp = fopen("Data.txt", "w");//清空文件，只写打开
	while (p1)
	{
		if(p1->Next != NULL)
		{
			fputs(p1->Num, fp); fputc('\n', fp);                  
			fputs(p1->Location, fp); fputc('\n', fp);                     
			fputs(p1->Date, fp); fputc('\n', fp);                 
			fputs(p1->Price, fp); fputc('\n', fp);                
			fputs(p1->Information, fp);               
			fputs(p1->Amount, fp); fputc('\n', fp); 
			fputs(p1->SubFlag, fp);fputc('\n', fp);
		}
		else
		{
			fputs(p1->Num, fp); fputc('\n', fp);                  
			fputs(p1->Location, fp); fputc('\n', fp);                     
			fputs(p1->Date, fp); fputc('\n', fp);                 
			fputs(p1->Price, fp); fputc('\n', fp);                
			fputs(p1->Information, fp);               
			fputs(p1->Amount, fp); fputc('\n', fp); 
			fputs(p1->SubFlag, fp);
		}
		p1 = p1->Next;
	}
	fclose(fp);
}

//按照销量排序产品，并返回销量最高的产品 ，用于管理员界面显示热销产品 
Product* ProductMountOrder()
{
	Orderr_Product = (Product*)malloc(sizeof(Product));
	Headd_Product = LoadProduct();

	Product* p1 = NULL;
	Product* p2 = NULL;
	
	char tempNum[10];         
	char tempLocation[15];    
	char tempDate[10];         
	char tempInformation[80];
	char tempAmount[10];            
	char tempPrice[10];         
	char tempSubFlag[5];    
	
	int sign = 0;       
	
	for (p1 = Headd_Product; p1; p1 = p1->Next)
	{
		for (p2 = Headd_Product; p2->Next; p2 = p2->Next)
		{
			if(strlen(p2->Amount) < strlen(p2->Next->Amount)||strcmp(p2->Amount,p2->Next->Amount) < 0) sign = 1;
			else sign = 0;
				
			if (sign)
			{
				strcpy(tempNum, p2->Num);
				strcpy(p2->Num, p2->Next->Num);
				strcpy(p2->Next->Num, tempNum);
					
				strcpy(tempLocation, p2->Location);
				strcpy(p2->Location, p2->Next->Location);
				strcpy(p2->Next->Location, tempLocation);
					
				strcpy(tempDate, p2->Date);
				strcpy(p2->Date, p2->Next->Date);
				strcpy(p2->Next->Date, tempDate);
					
				strcpy(tempInformation, p2->Information);
				strcpy(p2->Information, p2->Next->Information);
				strcpy(p2->Next->Information, tempInformation);
					
				strcpy(tempPrice, p2->Price);
				strcpy(p2->Price, p2->Next->Price);
				strcpy(p2->Next->Price, tempPrice);
					
				strcpy(tempAmount, p2->Amount);
				strcpy(p2->Amount, p2->Next->Amount);
				strcpy(p2->Next->Amount, tempAmount);	
				 
				strcpy(tempSubFlag, p2->SubFlag);
				strcpy(p2->SubFlag, p2->Next->SubFlag);
				strcpy(p2->Next->SubFlag, tempSubFlag);	
			} 
	    }
	}
	Orderr_Product = Headd_Product;
	Tempp_Product = Orderr_Product;
	return Tempp_Product;
}

void mytimer(int  timerID)
{
	label_x += 0.5;
	if (label_x > 12.0) 
		label_x = 1.0;
	display();
}

void RollingSlogan()
{ registerTimerEvent(mytimer);
 startTimer(LabelTimer, 200);
 SetPenColor("Blue");
 drawRectangle(0, winheight - 10* GetFontHeight(), winwidth, 10 * GetFontHeight(), 1);
 SetPointSize(80);
 SetPenColor("Green");
 drawLabel(label_x, winheight - 1.20* GetFontHeight(), "ZGL旅行社欢迎您");
 SetPointSize(GetFontHeight()); 
}

void Judgestatus()
{
	if(Returnflag==0) status = 1;
	else if(Returnflag==1) status = 2;
	else status = 0;
}
