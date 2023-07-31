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

int SearchFlag = 0;  //0��Ҫ���������Ϣ��1�����������������-1û�в��ҵ��������
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

double winwidth, winheight;   // ���ڳߴ�
int status = 0;   //��¼ϵͳ״̬  

int ReserveFlag = 0;//0���������Ʒ��Ž��棬1��ʾԤ���ɹ����棬2��ʾ�Ѿ�Ԥ������Ʒ��-1�����Ҳ�����Ʒ����
char ReserveNum[10] = "";

int UnsubFlag = 0;//0���������Ʒ��Ž��棬1��ʾ�˶��ɹ����棬2��ʾδԤ�����ò�Ʒ��-1�����Ҳ�����Ʒ����
char UnsubNum[10] = "";

int OrderWay;//1��ʾ���۸�����2��ʾ����������
int OrderFlag = 0;

int NewAddFlag = 0;//0���������Ʒ��Ž��棬1���ڳɹ����棬-1���ڲ�Ʒ����ظ�����

int NewFeedFlag = 0;//0�������뷴�����棬1���ڳɹ����棬-1���ڲ�Ʒ����ظ�����
 
int DeleteFlag = 0;//0���������Ʒ��Ž��棬1����ɾ���ɹ����棬-1���ڲ�Ʒ��Ų����ڽ���
char  DeleteNum[10] = ""; 

int Returnflag = 0;//��¼�����Ǵ��û����ǹ���Ա��������������Ԥ����������棬0�����û����棬1���ع���Ա���� 

// ��ʱ������������provided in libgraphics
void startTimer(int id, int timeinterval);

// �û����ַ��¼���Ӧ����
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI��ȡ����
	display(); // ˢ����ʾ
}

// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); //GUI��ȡ���
	display(); // ˢ����ʾ
}

// ��ʼ�����ں�ͼ��ϵͳ
void InitWindow() 
{
	//���ڳߴ����� 
	SetWindowTitle("���β�Ʒ����ϵͳ");
	SetWindowSize(15, 10);
	InitGraphics();

	// ��ô��ڳߴ�
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	// ע��ʱ����Ӧ����
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	
	display();
}

//��˫������ṹ˳���ȡ��Ʒ��Ĳ�Ʒ����������ͷ�ڵ�					 
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



//����Ʒ��Ϣ��ʾ�ڽ����� 
void drawProduct(double fH, double x, double y, double w, double h, Product* p)
{
	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("���") - 1.2 * h, (y -= h * 1.2) + fH * 0.7, "���");
	textbox(GenUIID(0), x - 1.2 * h, y, w, h, p->Num, sizeof(p->Num));

	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("�ص�") - 1.2 * h, (y -= h * 1.2) + fH * 0.7, "�ص�");
	textbox(GenUIID(0), x - 1.2 * h, y, w, h, p->Location, sizeof(p->Location));
	
	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("�۸�") - 1.2 * h, (y -= h * 1.2) + fH * 0.7, "�۸�");
	textbox(GenUIID(0), x - 1.2 * h, y, w, h, p->Price, sizeof(p->Price));

	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("��������") - 1.2 * h, (y -= h * 1.2) + fH * 0.7, "��������");
	textbox(GenUIID(0), x - 1.2 * h, y, w, h, p->Date, sizeof(p->Date));
	
	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("��������") - 1.2 * h, (y -= h * 1.2) + fH * 0.7, "��������");
	textbox(GenUIID(0), x - 1.2 * h, y, w, h, p->Amount, sizeof(p->Amount));
	
	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("�������") - 1.2 * h, (y -= h * 1.2) + fH * 0.7, "�������");
	textbox(GenUIID(0), x - 1.2 * h, y, w, h, p->Information, sizeof(p->Information));

	SetPenColor("Gray");
}

//���ص�ǰ�ڵ����һ�ڵ� 
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
	if (status == 0) //���β�Ʒ����ϵͳ������ Main 
	{
		SetPointSize(2);
        DisplayClear();
        drawMainButtons();
        drawMainBox();
        RollingSlogan();
        DrawleftArc();
        DrawrightArc();
	} 
	if (status == 1) //�û������� User
	{
		
		DisplayClear();
		drawUserButtons();
		drawUserMenu();
		drawUserProduct(fH, x, y, w, h, Temp_Product);
	} 
	if (status == 2) //����Ա������ Administrater
	{
		DisplayClear();
		drawAdminButtons();
		drawAdminProduct();
		drawAdminBox();
		drawAdminMenu();
	}
	if (status == 3) //�ص��������� LocationSearch
	{
		DisplayClear();
		drawLocationSearchText();
		drawLocationSearchButtons();
		RollingSlogan(); 
	} 
	if (status == 4) //������������ DateSearch
	{
		DisplayClear();
		drawDateSearchText();
		drawDateSearchButtons();
		RollingSlogan(); 
	} 
	if (status == 5) //Ԥ������ Reserve
	{
		DisplayClear();
		drawReserveText();
		drawReserveButtons();
		RollingSlogan();
	} 
	if (status == 6) //�˶����� Unsubmit
	{
		DisplayClear();
		drawUnsubText();
		drawUnsubButtons();
		RollingSlogan();
	} 
	if (status == 7) //������� Sort
	{
		DisplayClear();
		drawSortText();
		drawSortButtons();
		RollingSlogan();
	} 
	if (status == 8) //������Ʒ���� Add
	{
		DisplayClear();
		drawAddButtons(); 
 		drawAddText();
 		RollingSlogan();
	}
	if (status == 9) //ɾ����Ʒ���� Delete
	{
		DisplayClear();
		drawDeleteText();
		drawDeleteButtons(); 
		RollingSlogan();
	} 	
	if (status == 10) //�û���������Feedback
	{
		DisplayClear();
		drawFeedText();
		drawFeedButtons();
		RollingSlogan();
	 } 
}

//��дtxt�ı����� 
void fprintProduct(Product* p)
{
	FILE* fp;
	Product* p1 = p;
	fp = fopen("Data.txt", "w");//����ļ���ֻд��
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

//�������������Ʒ��������������ߵĲ�Ʒ �����ڹ���Ա������ʾ������Ʒ 
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
 drawLabel(label_x, winheight - 1.20* GetFontHeight(), "ZGL�����绶ӭ��");
 SetPointSize(GetFontHeight()); 
}

void Judgestatus()
{
	if(Returnflag==0) status = 1;
	else if(Returnflag==1) status = 2;
	else status = 0;
}
