#include "display_login.h"
extern int mode;//ģʽ��¼

//	��������
static char name1[20]= {0},name2[20]= {0}; // ��¼�û��������������

void CharEventProcess(char ch) {
	uiGetChar(ch); // GUI�ַ�����
	if(mode==1)
		display1();
}

char* getname1() {
	return name1;
}

char* getname2() {
	return name2;
}

void display1() {
	DisplayClear();
//	������
	SetPenColor("Black");
	SetPointSize(25);
	drawLabel(WindowWidth/2-TextStringWidth("��   Ϸ   ��   ¼")/2,9*WindowHeight/10,"��   Ϸ   ��   ¼");
//	�ռ���Ϣ
	SetPointSize(20);
	SetPenColor("Brown");
	drawLabel(8-TextStringWidth("user1 ID:"),8.5, "user1 ID:");
	drawLabel(8-TextStringWidth("user2 ID:"),6.5, "user2 ID:");
	usePredefinedTexBoxColors(3);
	textbox(GenUIID(0),10,8,4,1,name1,sizeof(name1[0])*20);
	textbox(GenUIID(0),10,6,4,1,name2,sizeof(name2[0])*20);
//	���ذ�ť
	SetPointSize(15);
	setButtonColors("Brown","Brown","Gray","Gray",0);
	if(button(GenUIID(0),17,1,3,1,"����")) {
		mode=0;
	}
//	�ύ�û���
	SetPointSize(20);
	setButtonColors("Brown","Brown","Gray","Gray",0);
	while(button(GenUIID(0),10,4,4,1,"�ύ")) {
		if(name1[0]!=0&&name2[0]!=0) {
			mode=7;
		}
	}
}
