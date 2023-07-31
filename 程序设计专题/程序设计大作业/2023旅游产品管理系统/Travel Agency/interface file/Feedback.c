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

//������Ʒ��Ϣ����         
char FeedLocation[100];    
char FeedDate[20];         
char FeedInformation[1000];             
char FeedPrice[10];        
char FeedSubFlag[5];      

//����������Ʒ�����ı� 
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
		drawLabel(x + 2.05 * h, y + h, "����д���ķ�����Ϣ");
		SetPointSize(fH);
		
		SetPenColor("Brown");
		drawLabel(x - fH / 2 - TextStringWidth("�ص�"), (y -= h * 1.3), "�ص�");
		if (textbox(GenUIID(0), x, y - 0.3 * h, w, h, FeedLocation, sizeof(FeedLocation)))	sprintf(results, FeedLocation);
		
		SetPenColor("Brown");
		drawLabel(x - fH / 2 - TextStringWidth("��������"), (y -= h * 1.3), "��������");
		if (textbox(GenUIID(0), x, y - 0.3 * h, w, h, FeedDate, sizeof(FeedDate)))	sprintf(results, FeedDate);
		
		SetPenColor("Brown");
		drawLabel(x - fH / 2 - TextStringWidth("�����۸�"), (y -= h * 1.3), "�����۸�");
		if (textbox(GenUIID(0), x, y - 0.3 * h, w, h, FeedPrice, sizeof(FeedPrice)))	sprintf(results, FeedPrice);
		
		SetPenColor("Brown");
		drawLabel(x - fH / 2 - TextStringWidth("��Ʒ����"), (y -= h * 1.3), "��Ʒ����");
		if (textbox(GenUIID(0), x, y - 0.3 * h, w, h, FeedInformation, sizeof(FeedInformation)))	sprintf(results, FeedInformation);

		
		
	
	}
	else if (NewFeedFlag == 1)
	{
		y = winheight / 1.5 - h;
		SetPenColor("Brown");
		drawLabel(x * 1.325 - TextStringWidth("��л���ķ�����") / 2, (y -= h * 1.2) + fH * 0.7, "��л���ķ�����");
	}
	else if (NewFeedFlag == -1)
	{
		y = winheight / 1.5 - h;
		SetPenColor("Brown");
		drawLabel(x * 1.325 - TextStringWidth("�����Ĳ�Ʒ�Ѵ��ڣ�") / 2, (y -= h * 1.2) + fH * 0.7, "�����Ĳ�Ʒ�Ѵ��ڣ�");
	}
	SetPenColor("Gray");

}


//������Ʒ��ť���� 
void drawFeedButtons() 
{
	 h = fH * 2;  
	 x = winwidth / 2.5;
	 y = winheight / 2 - 6 * h;
	 w = winwidth / 5; 

	if (NewFeedFlag == 0)
	{
		if (button(GenUIID(0), x, y - 1.5 * h, w, h, "����"))
		{
			FeedProduct(FeedLocation, FeedDate, FeedPrice,FeedInformation);
		}
		if (button(GenUIID(0), x, y - 3 * h, w, h, "����"))
		{
			NewFeedFlag = 0;
			status = 1; 
		}
		
	
	}
	else if (NewFeedFlag == 1)
	{
		y = winheight / 2 - 2 * h;
		if (button(GenUIID(0), x, y - 3 * h, w, h, "����"))
		{
			NewFeedFlag = 0;
			status = 1; 
		}
	}
	else if (NewFeedFlag == -1)
	{
		y = winheight / 2 - 2 * h;
		if (button(GenUIID(0), x, y - 1.5 * h, w, h, "���·���"))
		{
			NewFeedFlag = 0;
		}
		if (button(GenUIID(0), x, y - 3 * h, w, h, "����"))
		{
			NewAddFlag = 0;
			status = 1; 
		}
	}
}

//������Ʒ����������д�� 
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
