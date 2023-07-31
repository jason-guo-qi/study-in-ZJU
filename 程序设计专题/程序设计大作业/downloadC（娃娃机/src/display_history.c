#include "display_history.h"
extern int mode;//ģʽ��¼

struct save {
	int prex,prey,nowx,nowy;
	struct save *next;
};//��ʱ�洢�ò���仯 
struct save *p=NULL,*head=NULL,*tail=NULL;//����ָ�� 
static int i=1;//�������� 
static int first=1;//��һ�ν���ҳ��
static int firstdisplay=1;//�Ƿ��ȡ�ļ���� 
static int page=1;//ҳ�� 
static int istailed=0;//ҳ���Ƿ����һҳ 
static char name1[7][20]= {0},name2[7][20]= {0};//�洢˫���û��� 

void display5() {
	DisplayClear();
//	����ҳ��
	SetPenColor("black");
	SetPointSize(30);
	drawLabel(WindowWidth/2-TextStringWidth("��   ʷ   ��   ��")/2,9*WindowHeight/10,"��   ʷ   ��   ��");
	SetPointSize(25);
	drawLabel(6,11,"Player1");
	drawLabel(10,11,"Player2");
	if(firstdisplay){
		FILE *fp;
		fp=fopen("participant_list.txt","r");
		for(i=0;i<(page-1)*7;i++){
			fscanf(fp,"%s",name1[0]);
			fscanf(fp,"%s",name2[0]);
		}
		for(i=0; i<7; i++) {
			memset(name1[i],0,20);
			memset(name2[i],0,20);
			fscanf(fp,"%s",name1[i]);
			fscanf(fp,"%s",name2[i]);
		}
		fclose(fp);
		firstdisplay=0;
	}
	if(name1[0][0]) {
		SetPenColor("black");
		drawLabel(6,10.2,name1[0]);
		drawLabel(10,10.2,name2[0]);
		if(button(GenUIID(0),13,10,2,1,"�鿴")) {
			first=1;
			mode=9;
			i=1+(page-1)*7;
			readdata();
		}
	}else istailed=1;
	if(name1[1][0]) {
		SetPenColor("black");
		drawLabel(6,10.2-1,name1[1]);
		drawLabel(10,10.2-1,name2[1]);
		if(button(GenUIID(0),13,9,2,1,"�鿴")) {
			first=1;
			mode=9;
			i=2+(page-1)*7;
			readdata();
		}
	}else istailed=1;
	if(name1[2][0]) {
		SetPenColor("black");
		drawLabel(6,10.2-2,name1[2]);
		drawLabel(10,10.2-2,name2[2]);
		if(button(GenUIID(0),13,10-2,2,1,"�鿴")) {
			first=1;
			mode=9;
			i=3+(page-1)*7;
			readdata();
		}
	}else istailed=1;
	if(name1[3][0]) {
		SetPenColor("black");
		drawLabel(6,10.2-3,name1[3]);
		drawLabel(10,10.2-3,name2[3]);
		if(button(GenUIID(0),13,10-3,2,1,"�鿴")) {
			first=1;
			mode=9;
			i=4+(page-1)*7;
			readdata();
		}
	}else istailed=1;
	if(name1[4][0]) {
		SetPenColor("black");
		drawLabel(6,10.2-4,name1[4]);
		drawLabel(10,10.2-4,name2[4]);
		if(button(GenUIID(0),13,10-4,2,1,"�鿴")) {
			first=1;
			mode=9;
			i=5+(page-1)*7;
			readdata();
		}
	}else istailed=1;
	if(name1[5][0]) {
		SetPenColor("black");
		drawLabel(6,10.2-5,name1[5]);
		drawLabel(10,10.2-5,name2[5]);
		if(button(GenUIID(0),13,10-5,2,1,"�鿴")) {
			first=1;
			mode=9;
			i=6+(page-1)*7;
			readdata();
		}
	}else istailed=1;
	if(name1[6][0]) {
		SetPenColor("black");
		drawLabel(6,10.2-6,name1[6]);
		drawLabel(10,10.2-6,name2[6]);
		if(button(GenUIID(0),13,10-6,2,1,"�鿴")) {
			first=1;
			mode=9;
			i=7+(page-1)*7;
			readdata();
		}
	}else istailed=1;
	setButtonColors("Brown","Brown","Gray","Gray",0);
	if(button(GenUIID(0),6,2,3,1,"��һҳ")) {
		p=NULL;
		head=NULL;
		tail=NULL;
		firstdisplay=1;
		i=1;
		if(istailed)istailed=0;
		if(page!=1)page--;
		first=1;
	}
	if(button(GenUIID(0),13,2,3,1,"��һҳ")) {
		p=NULL;
		head=NULL;
		tail=NULL;
		firstdisplay=1;
		i=1;
		if(!istailed)page++;
		first=1;
	}
//	���ذ�ť
	SetPointSize(15);
	if(button(GenUIID(0),17,1,3,1,"����")) {
		mode=0;
		p=NULL;
		head=NULL;
		tail=NULL;
		i=1;
		first=1;
	}
}

void readdata() {
//	��ȡ����
	FILE *fp;
	char ch[5];
	sprintf(ch,"%d",i);
	fp=fopen(Concat(ch,".txt"),"r");
//	InitConsole();
	while(1) {
		p=(struct save*)malloc(sizeof(struct save));
		fscanf(fp,"%d %d %d %d\n",&p->prex,&p->prey,&p->nowx,&p->nowy);
//		printf("%d %d %d %d\n",p->prex,p->prey,p->nowx,p->nowy);
		p->next=NULL;
		if(head==NULL) {
			head=p;
		} else {
			tail->next=p;
		}
		tail=p;
		if(feof(fp))break;
	}
	tail->next=p;
	tail=p;
	p=(struct save*)malloc(sizeof(struct save));
	p->nowx=0;
	p->nowy=0;
	p->prex=0;
	p->prey=0;
	p->next=NULL;
//	printf("%d %d %d %d\n",p->prex,p->prey,p->nowx,p->nowy);
	p=head;
}

void openhistory() {
//	����ҳ��
	DisplayClear();
	if(first) {
		InitMap();
		first=0;
	}
	DisplayClear();
	drawMap();
	drawPiece();
//	������ť
	SetPointSize(20);
	if(button(GenUIID(0),0.5,8,2,1, "��һ��")) {
		if(!(p->nowx==0&&p->nowy==0&&p->prex==0&&p->prey==0)){
			movechess(p->prex,p->prey,p->nowx,p->nowy);
		}
		if(p->next) {
			p=p->next;
		}
		openhistory();
	}
//	���ذ�ť
	SetPenSize(1);
	SetPenColor("Black"); 
	SetPointSize(15);
	setButtonColors("Brown","Brown","Gray","Gray",0);
	if(button(GenUIID(0),0,0,3,1,"����")) {
		p=NULL;
		head=NULL;
		tail=NULL;
		i=1;
		page=1;
		first=1;
		mode=5;
		istailed=0;
		firstdisplay=1;
	}
}
