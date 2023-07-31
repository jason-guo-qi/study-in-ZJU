#include "display_winner.h"
extern int mode;//ģʽ��¼

static int firstread=0;//�Ƿ��һ�ν����ҳ�� 
static int result[7];//�洢��ǰҳ����ʾ��ʤ����� 
static int i=0;//�������� 
static char name1[7][20]= {0},name2[7][20]= {0};//�û��� 
static int total;//��ǰҳ���ܹ�չʾ����� 
static int istailed=0;//�Ƿ��Ѿ�չʾ���һ������ 
static int page=1;//ҳ�� 
void display2() {
	DisplayClear();
	if(!firstread) {
		firstread=1;
		total=0;
		memset(result,0,7);
//	���ļ�
		FILE *fp,*fw;
		fp=fopen("winner.txt","r");
		for(i=0; i<(page-1)*7; i++) {
			fscanf(fp,"%s",name1[0]);
			fscanf(fp,"%s",name2[0]);
			fscanf(fp,"%d",&result[0]);
		}
		for(i=0; i<7&&!feof(fp); i++) {
			memset(name1[i],0,20);
			memset(name2[i],0,20);
			fscanf(fp,"%s",name1[i]);
			fscanf(fp,"%s",name2[i]);
			fscanf(fp,"%d",&result[i]);
			if(feof(fp))istailed=1;
		}
		total=i;
		fclose(fp);
	}
//	����ҳ��
	SetPenColor("black");
	SetPointSize(30);
	drawLabel(WindowWidth/2-TextStringWidth("��   ��   ��   ¼")/2,9*WindowHeight/10,"��   ��   ��   ¼");
	SetPointSize(15);
	drawLabel(WindowWidth/2,8.5*WindowHeight/10,"���չʾ�����Ծֽ��");
	SetPointSize(25);
	drawLabel(5,11,"Player1");
	drawLabel(9,11,"Player2");
	drawLabel(13,11,"Winner");
	SetPointSize(20);
	for(i=0; i<total; i++) {
		drawLabel(5,10.2-i,name1[i]);
		drawLabel(9,10.2-i,name2[i]);
		if(result[i]) {
			drawLabel(13,10.2-i,name2[i]);
		} else {
			drawLabel(13,10.2-i,name1[i]);
		}
	}
	setButtonColors("Brown","Brown","Gray","Gray",0);
	if(button(GenUIID(0),6,2,3,1,"��һҳ")) {
		if(page!=1)page--;
		if(istailed)istailed=0;
		firstread=0;
	}
	if(button(GenUIID(0),13,2,3,1,"��һҳ")) {
		if(!istailed)page++;
		firstread=0;
	}
//	���ذ�ť
	SetPointSize(15);
	setButtonColors("Brown","Brown","Gray","Gray",0);
	if(button(GenUIID(0),17,1,3,1,"����")) {
		mode=0;
		firstread=0;
		istailed=0;
		page=1;
	}
}
