#include "search_mode.h"
extern int mode;//ģʽ��¼

static int isChosen=0;//�Ƿ�ѡ��ģʽ

void display7() {
	DisplayClear();
//	������
	SetPenColor("Black");
	SetPointSize(25);
	drawLabel(WindowWidth/2-TextStringWidth("ģ  ʽ  ѡ  ��")/2,9*WindowHeight/10,"ģ  ʽ  ѡ  ��");
//	ѡ��ģʽ
	SetPointSize(30);
	setButtonColors("Brown","White","Gray","White",1);
	if(button(GenUIID(0),4,5,4,5,"�� �� ģ ʽ")) {
		record(0);
		isChosen=1;
	}
	if(button(GenUIID(0),12,5,4,5,"¼ �� ģ ʽ")) {
		record(1);
		isChosen=1;
	}
//	�ύ����ʼ��Ϸ
	SetPointSize(20);
	while(button(GenUIID(0),8,2.5,4,1,"��ʼ��Ϸ")) {
		if(isChosen) {
			mode=6;
		}
	}
//	���ذ�ť
	SetPenColor("Black");
	SetPointSize(15);
	setButtonColors("Brown","Brown","Gray","Gray",0);
	if(button(GenUIID(0),17,1,3,1,"����")) {
		mode=1;
	}
}
