#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "imgui.h"
#include "Feedback.h"
#include "FunctionLib.h"

#include <stdio.h>
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

//新增产品信息数据         
char FeedLocation[100];    
char FeedDate[20];         
char FeedInformation[1000];             
char FeedPrice[10];        
char FeedSubFlag[5];      

//绘制新增产品界面文本 
void drawFeedText() 
{
	static char results[80] = "";
	fH = GetFontHeight();
	h = fH * 2; 
	w = winwidth / 3; 
	x = winwidth / 2.65;
	y = winheight / 1.5;

	if (NewFeedFlag == 0)
	{
		x = winwidth / 3;
		
		SetPointSize(25); 
		SetPenColor("red");
		drawLabel(x + 2.05 * h, y + h, "请填写您的反馈信息");
		SetPointSize(fH);
		
		SetPenColor("Brown");
		drawLabel(x - fH / 2 - TextStringWidth("地点"), (y -= h * 1.3), "地点");
		if (textbox(GenUIID(0), x, y - 0.3 * h, w, h, FeedLocation, sizeof(FeedLocation)))	sprintf(results, FeedLocation);
		
		SetPenColor("Brown");
		drawLabel(x - fH / 2 - TextStringWidth("旅行日期"), (y -= h * 1.3), "旅行日期");
		if (textbox(GenUIID(0), x, y - 0.3 * h, w, h, FeedDate, sizeof(FeedDate)))	sprintf(results, FeedDate);
		
		SetPenColor("Brown");
		drawLabel(x - fH / 2 - TextStringWidth("期望价格"), (y -= h * 1.3), "期望价格");
		if (textbox(GenUIID(0), x, y - 0.3 * h, w, h, FeedPrice, sizeof(FeedPrice)))	sprintf(results, FeedPrice);
		
		SetPenColor("Brown");
		drawLabel(x - fH / 2 - TextStringWidth("产品描述"), (y -= h * 1.3), "产品描述");
		if (textbox(GenUIID(0), x, y - 0.3 * h, w, h, FeedInformation, sizeof(FeedInformation)))	sprintf(results, FeedInformation);

		
		
	
	}
	else if (NewFeedFlag == 1)
	{
		y = winheight / 1.5 - h;
		SetPenColor("Brown");
		drawLabel(x * 1.325 - TextStringWidth("感谢您的反馈！") / 2, (y -= h * 1.2) + fH * 0.7, "感谢您的反馈！");
	}
	else if (NewFeedFlag == -1)
	{
		y = winheight / 1.5 - h;
		SetPenColor("Brown");
		drawLabel(x * 1.325 - TextStringWidth("反馈的产品已存在！") / 2, (y -= h * 1.2) + fH * 0.7, "反馈的产品已存在！");
	}
	SetPenColor("Gray");

}


//反馈产品按钮绘制 
void drawFeedButtons() 
{
	 h = fH * 2;  
	 x = winwidth / 2.5;
	 y = winheight / 2 - 6 * h;
	 w = winwidth / 5; 

	if (NewFeedFlag == 0)
	{
		if (button(GenUIID(0), x, y - 1.5 * h, w, h, "反馈"))
		{
			FeedProduct(FeedLocation, FeedDate, FeedPrice,FeedInformation);
		}
		if (button(GenUIID(0), x, y - 3 * h, w, h, "返回"))
		{
			NewFeedFlag = 0;
			status = 1; 
		}
		
	
	}
	else if (NewFeedFlag == 1)
	{
		y = winheight / 2 - 2 * h;
		if (button(GenUIID(0), x, y - 3 * h, w, h, "返回"))
		{
			NewFeedFlag = 0;
			status = 1; 
		}
	}
	else if (NewFeedFlag == -1)
	{
		y = winheight / 2 - 2 * h;
		if (button(GenUIID(0), x, y - 1.5 * h, w, h, "重新反馈"))
		{
			NewFeedFlag = 0;
		}
		if (button(GenUIID(0), x, y - 3 * h, w, h, "返回"))
		{
			NewAddFlag = 0;
			status = 1; 
		}
	}
}

//新增产品反馈操作并写入 
void FeedProduct(char* Location, char* Date, char* Price, char* Information)
{
	Head_Product = LoadProduct();
	Product* m = Head_Product;
	while (m)
	{
		if (strcmp(m->Location, Location) == 0&&strcmp(m->Date, Date) == 0)
		{
			NewFeedFlag = -1;
			return;
		}
		m = m->Next;
	}

	FILE* fp;
	
	if (!(fp = fopen("Feedback.txt", "a+"))) {
		exit(-1); 
	}
	fputc('\n', fp);                 
	fputs(Location, fp); fputc('\n', fp);                     
	fputs(Date, fp); fputc('\n', fp);                 
	fputs(Price, fp); fputc('\n', fp);                
	fputs(Information, fp); fputc('\n', fp);                        
	fputs("End", fp);                  
	fclose(fp);

	NewFeedFlag = 1;
}
