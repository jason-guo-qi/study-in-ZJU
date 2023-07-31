#include"Init.h"
#include "display_help.h"
#include "display_login.h"
#include "aftergame.h"
#include "display_game.h"
#include "display_history.h"
#include "search_mode.h"
#include "display_winner.h"
#include "writefile.h"
int mode;//ģʽ��¼


void MouseEventProcess(int x, int y, int button, int event) {
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	double px=ScaleXInches(x);
	double py=ScaleYInches(y);
//	ˢ����ʾ
	switch(mode) {
		case 6:
			display6();
			drawChess(px,py,button,event);
			break;//��Ϸ����
	}
}

void Main() {
	SetWindowTitle("Chinese Chess");
	SetWindowSize(WindowWidth, WindowHeight);
	InitGraphics();
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	registerTimerEvent(TimerEventProcess);      // ��ʱ��
	startTimer(0,timer_interval/1000);
	display0();
}
