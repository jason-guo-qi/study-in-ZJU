#include "display_help.h"
extern int mode;//ģʽ��¼

void display3() {
	DisplayClear();
//	˵������
	SetPenColor("Black");
	SetPointSize(25);
	drawLabel(WindowWidth/2-TextStringWidth("��   Ϸ   ˵   ��")/2,9*WindowHeight/10,"��   Ϸ   ˵   ��");
	SetPointSize(15);
	drawLabel(WindowWidth/10,8*WindowHeight/10,"1.�������˺����뿪ʼ�����Ϸ");
	drawLabel(WindowWidth/10,7*WindowHeight/10,"2.�ж���ģʽ��¼��ģʽ�ɹ�ѡ��");
	drawLabel(WindowWidth/10,6*WindowHeight/10,"3.��¼��ģʽ��Ҳ���¼˫��ս��");
	drawLabel(WindowWidth/10,5*WindowHeight/10,"4.���ڿ�ʼ����ط���¼�Ƶ����ݼ��鿴¼�������");
	drawLabel(WindowWidth/10,4*WindowHeight/10,"5.ʹ�������������ƶ�����");
	drawLabel(WindowWidth/10,3*WindowHeight/10,"6.��Ϸ�����ݼ���F1--��ͣ��Ϸ F2--������Ϸ F3--���¿�ʼ F4--���� ESC--����");
	drawLabel(WindowWidth/10,2*WindowHeight/10,"7.��ͨ���鿴�Ծ�ʤ����鿴��ʷ�Ծ�ʤ�����");
	drawLabel(WindowWidth/10,WindowHeight/10,"8.ÿ�ֽ���һ�λ������");
//	���ذ�ť
	SetPointSize(15);
	setButtonColors("Brown","Brown","Gray","Gray",0);
	if(button(GenUIID(0),17,1,3,1,"����")) {
		mode=0;
	}
}

void display4() {
	DisplayClear();
//	��������
	SetPenColor("Black");
	SetPointSize(25);
	drawLabel(WindowWidth/2-TextStringWidth("��   ��   ��   ��")/2,9*WindowHeight/10,"��   ��   ��   ��");
	SetPointSize(15);
	drawLabel(WindowWidth/10,8*WindowHeight/10,"�����ߣ���ΰ��");
	drawLabel(WindowWidth/10,7*WindowHeight/10,"��л��������ʦ�Ա������ָ��֧��");
	drawLabel(WindowWidth/10,6*WindowHeight/10,"����ͼ�ο⣺Libgraphics&&simpleGUI");
	drawLabel(WindowWidth/10,4*WindowHeight/10,"���һ�α༭ʱ�䣺2022/5/31");
	drawLabel(WindowWidth/10,3*WindowHeight/10,"��Ϸ�����й�����      �汾�ţ�1.2.2");
//	���ذ�ť
	SetPointSize(15);
	setButtonColors("Brown","Brown","Gray","Gray",0);
	if(button(GenUIID(0),17,1,3,1,"����")) {
		mode=0;
	}
}
