#include"Init.h"
extern int mode;//ģʽ��¼

void display0() {
	DisplayClear();
//	�����
	SetPointSize(50);
	SetPenColor("black");
	drawLabel(WindowWidth/2-TextStringWidth("�� �� �� ��")/2,11,"�� �� �� ��");
//	���˵�
	SetPointSize(25);
	setButtonColors("white","Brown","white","Gray",0);
	if(button(GenUIID(0),WindowWidth/2-1.3*TextStringWidth("��¼����ʼ��Ϸ")/2,8,1.3*TextStringWidth("��¼����ʼ��Ϸ"),1.5,"��¼����ʼ��Ϸ")) {
		mode=1;
	}
	if(button(GenUIID(0),WindowWidth/2-TextStringWidth("�Ծ�ʤ����")/2,6,TextStringWidth("�Ծ�ʤ����"),1.5,"�Ծ�ʤ����")) {
		mode=2;
	}
	if(button(GenUIID(0),WindowWidth/2-TextStringWidth("��ʷ�Ծ�������")/2,4,TextStringWidth("��ʷ�Ծ�������"),1.5,"��ʷ�Ծ�������")) {
		mode=5;
	}
//	��������
	SetPointSize(15);
	setButtonColors("white","Brown","white","Gray",0);
	if(button(GenUIID(0),14,1,3,1,"�˳����")) {
		exit(0);
	}
	if(button(GenUIID(0),17,1,1.5,1,"����")) {
		mode=3;
	}
	if(button(GenUIID(0),18.5,1,1.5,1,"����")) {
		mode=4;
	}
}
