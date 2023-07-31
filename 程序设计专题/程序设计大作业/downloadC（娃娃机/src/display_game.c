#include "display_game.h"
extern int mode;//ģʽ��¼

//��������
static int Chess_Color=0;//�ж�ִ�巽���ڷ�Ϊ1
static int gaming=1;//�ж��Ƿ���Ϸ��ʼ����ʼΪ0
static int isRecord=0;//�ж��Ƿ�¼�ƣ�¼��Ϊ1
static int isGaming=0;//�ж���Ϸ���У�����ʱ������������Ϊ1
static int mytimer=time_limit;//��ʱ��
static int lose_r,lose_b;//�췽���ڷ�ʧ�Ӹ���
static int loser[2][16];//��¼���Ե�������
static int isRetract=0;//�Ƿ�����
static int selecting=0;//��ǰ�Ƿ������ӱ�ѡ��
static int selectx=999,selecty=999;//ѡ�����ӵ�����
static const double Round=0.6;//���Ӱ뾶
const double width=12/9.0;//���̸��ӱ߳�
typedef struct {
	int id;//��Ӫ
	int isSelect;//�Ƿ�ѡ��
	int type;//��������
	int isOn;//�Ƿ��ڳ�
	double cx,cy;//����
} Chess; //���̸��Ӱ�
static Chess map[10][9];//�����ͼ
static int retract[2][5];//��һ�����ƶ�����λ�õ�id,type,isOn,i,j
const string kind[2][7]= {"˧","��","��","��","܇","��","��","��","ʿ","��","�R","܇","�h","��"};//�洢����

void record(int Record) {
	isRecord=Record;
}

void KeyboardEventProcess(int key, int event) {
	uiGetKeyboard(key,event); // GUI��ȡ����
	switch(event) {
		case KEY_DOWN:
			switch(key) {
				case VK_F1:
					isGaming=0;
					break;
				case VK_F2:
					isGaming=1;
					break;
				case VK_F3:
					gaming=1;
					break;
				case VK_F4:
					doretract();
					break;
				case VK_ESCAPE:
					mode=7;
					isGaming=1;
					break;
				default:
					break;
			}
		default:
			break;
	}
}

void TimerEventProcess(int timerID) {
	if(timerID==1&&isGaming) {
		mytimer--;//������
		if(!mytimer) {
			gaming=1;
			isGaming=0;
			Gameover(1-Chess_Color);
			mode=-1;
		} else {
			drawTimer();
		}
	}
	if(!timerID) {
		switch(mode) {
			case 0:
				display0();
				break;//��ʼ����
			case 1:
				display1();
				break;//��¼
			case 2:
				display2();
				break;//�Ծּ�¼
			case 3:
				display3();
				break;//����
			case 4:
				display4();
				break;//����
			case 5:
				display5();
				break;//��ʷ�Ծ�������
			case 7:
				display7();
				break;//ģʽѡ�����
			case 9:
				openhistory();
				break;
			case -1:
				Gameover(color());
				break;//��Ϸ��������
		}
	}
}

void drawTimer() {
	SetPenColor("White");
	drawRectangle(0.1,12.2,2.8,2,1);
	SetPenSize(1);
	SetPenColor("black");
	drawRectangle(0.05,11.95,3,3,0);
	SetPointSize(20);
	drawLabel(0.1,13.5,"����ʱ");
	char ch[10];
	sprintf(ch,"%d",mytimer);
	SetPointSize(25);
	drawLabel(0.1,12.2,ch);
}

void drawMap() {
	double i;
	SetPenColor("black");
//	����
	for(i=1; i<=13; i=i+width) {
		MovePen(6,i);
		DrawLine(width*8,0);
	}
//	����
	MovePen(6,1);
	DrawLine(0,width*9);
	for(i=6+width; i<19-width; i=i+width) {
		MovePen(i,1);
		DrawLine(0,width*4);
		MovePen(i,1+width*5);
		DrawLine(0,width*4);
	}
	MovePen(18-width,1);
	DrawLine(0,width*9);
//	б��
	MovePen(6+width*3,1);
	DrawLine(width*2,width*2);
	MovePen(6+width*5,1);
	DrawLine(-width*2,width*2);
	MovePen(6+width*3,1+width*7);
	DrawLine(width*2,width*2);
	MovePen(6+width*5,1+width*7);
	DrawLine(-width*2,width*2);
//	����
	SetPointSize(25);
	drawLabel(6.3+width,1.3+width*4,"��   ��");
	drawLabel(6.3+width*5,1.3+width*4,"�h   ��");
}

int isEffect(double x,double y,double a, double b) {
	if((x-a)*(x-a)+(y-b)*(y-b)<=Round) {
		return 1;
	} else {
		return 0;
	}
}

void InitMap() {
//	init ����
	int i,j;
	for(i=0; i<10; i++) {
		for(j=0; j<9; j++) {
			map[i][j].cx=6+width*j;
			map[i][j].cy=1+width*i;
			map[i][j].id=0;
			map[i][j].isOn=0;
			map[i][j].isSelect=0;
			map[i][j].type=0;
		}
	}
//	init ������һ��
	for(j=0; j<9; j++) {
		map[0][j].id=0;//�췽idΪ0
		map[9][j].id=1;//��1
		map[0][j].isSelect=0;
		map[9][j].isSelect=0;
		map[0][j].isOn=1;
		map[9][j].isOn=1;
	}
	map[0][0].type=4;
	map[9][0].type=4;
	map[0][1].type=3;
	map[9][1].type=3;
	map[0][2].type=2;
	map[9][2].type=2;
	map[0][3].type=1;
	map[9][3].type=1;
	map[0][4].type=0;
	map[9][4].type=0;
	map[0][5].type=1;
	map[9][5].type=1;
	map[0][6].type=2;
	map[9][6].type=2;
	map[0][7].type=3;
	map[9][7].type=3;
	map[0][8].type=4;
	map[9][8].type=4;
//	init ��
	for(j=0; j<9; j=j+2) {
		map[3][j].id=0;
		map[6][j].id=1;
		map[3][j].isSelect=0;
		map[6][j].isSelect=0;
		map[3][j].isOn=1;
		map[6][j].isOn=1;
		map[3][j].type=6;
		map[6][j].type=6;
	}
//	init �h
	map[2][1].id=0;
	map[2][7].id=0;
	map[7][1].id=1;
	map[7][7].id=1;
	map[2][1].isSelect=0;
	map[2][7].isSelect=0;
	map[7][1].isSelect=0;
	map[7][7].isSelect=0;
	map[2][1].isOn=1;
	map[2][7].isOn=1;
	map[7][1].isOn=1;
	map[7][7].isOn=1;
	map[2][1].type=5;
	map[2][7].type=5;
	map[7][1].type=5;
	map[7][7].type=5;
}

int rule(int pi, int pj) {
	int i,j;
	switch(map[selectx][selecty].type) {
		case 0: {//��
			if(!map[pi][pj].type&&selecty==pj&&map[pi][pj].isOn) {
				int k,cntt=0;
				for(k=selectx+1; k<pj; k++)if(map[k][pj].isOn)cntt++;
				for(k=pj+1; k<selectx; k++)if(map[k][pj].isOn)cntt++;
				if(!cntt)return 1;
			}//�ɽ�
			if(map[selectx][selecty].id) return (pi<=9&&pi>=7&&pj>=3&&pj<=5)&&((pi-1==selectx&&pj==selecty)||(pi+1==selectx&&pj==selecty)||(pi==selectx&&pj-1==selecty)||(pi==selectx&&pj+1==selecty));
			else return (pi<=2&&pi>=0&&pj>=3&&pj<=5)&&((pi-1==selectx&&pj==selecty)||(pi+1==selectx&&pj==selecty)||(pi==selectx&&pj-1==selecty)||(pi==selectx&&pj+1==selecty));
		}
		case 1: {//��
			if(map[selectx][selecty].id) return (pi<=9&&pi>=7&&pj>=3&&pj<=5)&&((pi-1==selectx&&pj-1==selecty)||(pi+1==selectx&&pj+1==selecty)||(pi+1==selectx&&pj-1==selecty)||(pi-1==selectx&&pj+1==selecty));
			else return (pi<=2&&pi>=0&&pj>=3&&pj<=5)&&((pi-1==selectx&&pj-1==selecty)||(pi+1==selectx&&pj+1==selecty)||(pi+1==selectx&&pj-1==selecty)||(pi-1==selectx&&pj+1==selecty));
		}
		case 2: {//��
			if(map[selectx][selecty].id) return (pi<=9&&pi>=5&&pj>=0&&pj<=8)&&((pi-2==selectx&&pj-2==selecty)||(pi+2==selectx&&pj+2==selecty)||(pi+2==selectx&&pj-2==selecty)||(pi-2==selectx&&pj+2==selecty))&&(!map[(selectx+pi)/2][(selecty+pj)/2].isOn);
			else return (pi<=4&&pi>=0&&pj>=0&&pj<=8)&&((pi-2==selectx&&pj-2==selecty)||(pi+2==selectx&&pj+2==selecty)||(pi+2==selectx&&pj-2==selecty)||(pi-2==selectx&&pj+2==selecty))&&(!map[(selectx+pi)/2][(selecty+pj)/2].isOn);
		}
		case 3: {//��
			if((pj-selecty==1&&pi-selectx==2)||(pj-selecty==-1&&pi-selectx==2)) {
				if(map[selectx+1][selecty].isOn) {
					return 0;
				} else {
					return 1;
				}
			} else if((pj-selecty==1&&pi-selectx==-2)||(pj-selecty==-1&&pi-selectx==-2)) {
				if(map[selectx-1][selecty].isOn) {
					return 0;
				} else {
					return 1;
				}
			} else if((pi-selectx==1&&pj-selecty==2)||(pi-selectx==-1&&pj-selecty==2)) {
				if(map[selectx][selecty+1].isOn) {
					return 0;
				} else {
					return 1;
				}
			} else if((pi-selectx==1&&pj-selecty==-2)||(pi-selectx==-1&&pj-selecty==-2)) {
				if(map[selectx][selecty-1].isOn) {
					return 0;
				} else {
					return 1;
				}
			} else {
				return 0;
			}
		}
		case 4: {//��
			int cnt=0;//��·���м�������
			if(selectx==pi) {
				if(selecty<pj) {
					for(j=selecty+1; j<pj; j++) {
						if(map[pi][j].isOn)cnt++;
					}
				} else {
					for(j=pj+1; j<selecty; j++) {
						if(map[pi][j].isOn)cnt++;
					}
				}
				if(!cnt)return 1;
				return 0;
			} else if(selecty==pj) {
				if(selectx<pi) {
					for(i=selectx+1; i<pi; i++) {
						if(map[i][pj].isOn)cnt++;
					}
				} else {
					for(i=pi+1; i<selectx; i++) {
						if(map[i][pj].isOn)cnt++;
					}
				}
				if(!cnt)return 1;
				return 0;
			} else return 0;
		}
		case 5: {//��
			int cnt=0;
			if(selectx==pi) {
				if(selecty<pj) {
					for(j=selecty+1; j<pj; j++) {
						if(map[pi][j].isOn)cnt++;
					}
					if(!cnt&&!map[pi][pj].isOn)return 1;
					return cnt==1&&map[pi][pj].isOn;
				} else {
					for(j=selecty-1; j>pj; j--) {
						if(map[pi][j].isOn)cnt++;
					}
					if(!cnt&&!map[pi][pj].isOn)return 1;
					return cnt==1&&map[pi][pj].isOn;
				}
				return 0;
			} else if(selecty==pj) {
				if(selectx<pi) {
					for(i=selectx+1; i<pi; i++) {
						if(map[i][pj].isOn)cnt++;
					}
					if(!cnt&&!map[pi][pj].isOn)return 1;
					return cnt==1&&map[pi][pj].isOn;
				} else {
					for(i=selectx-1; i>pi; i--) {
						if(map[i][pj].isOn)cnt++;
					}
					if(!cnt&&!map[pi][pj].isOn)return 1;
					return cnt==1&&map[pi][pj].isOn;
				}
				return 0;
			} else return 0;
		}
		case 6: {//��
			if(map[selectx][selecty].id) {
				if(selectx>4)return pi==selectx-1&&pj==selecty;
				else return (pi==selectx-1&&pj==selecty)||(pi==selectx&&pj+1==selecty)||(pi==selectx&&pj-1==selecty);
			} else {
				if(selectx<5)return pi==selectx+1&&pj==selecty;
				else return (pi==selectx+1&&pj==selecty)||(pi==selectx&&pj+1==selecty)||(pi==selectx&&pj-1==selecty);
			}
		}
	}
	return 0;
}

void retractit(int i,int j) {
	retract[0][0]=map[selectx][selecty].id;
	retract[0][1]=map[selectx][selecty].type;
	retract[0][2]=map[selectx][selecty].isOn;
	retract[0][3]=selectx;
	retract[0][4]=selecty;
	retract[1][0]=map[i][j].id;
	retract[1][1]=map[i][j].type;
	retract[1][2]=map[i][j].isOn;
	retract[1][3]=i;
	retract[1][4]=j;
}

void drawChess(double px, double py, int button, int event) {
	int i,j;
//	�ж�ѡ�м�ȡ��ѡ�С��ƶ�����
	for(i=0; i<10; i++) {
		for(j=0; j<9; j++) {
//			ѡ������
			if(event==BUTTON_DOWN&&isEffect(px,py,map[i][j].cx,map[i][j].cy)&&map[i][j].isOn&&map[i][j].id==Chess_Color) {
				if(selecting) {
					map[selectx][selecty].isSelect=0;
					map[i][j].isSelect=1;
					selecting=1;
					selectx=i;
					selecty=j;
				} else {
					map[i][j].isSelect=1;
					selecting=1;
					selectx=i;
					selecty=j;
				}
				if(!isGaming) {
					startTimer(1,timer_interval);
					isGaming=1;//��һ��ѡ�����ӵ��ڿ�ʼ��Ϸ
				}
			}
//			�ƶ�����
			else if(event==BUTTON_DOWN&&isEffect(px,py,map[i][j].cx,map[i][j].cy)&&!map[i][j].isOn&&selecting&&rule(i,j)) {
				writenew(selectx,selecty,i,j);
				retractit(i,j);
				if(Chess_Color) {
					Chess_Color=0;
				} else {
					Chess_Color=1;
				}
				map[i][j].isOn=1;
				map[selectx][selecty].isOn=0;
				map[i][j].id=map[selectx][selecty].id;
				map[i][j].isSelect=0;
				map[i][j].type=map[selectx][selecty].type;
				mytimer=time_limit;
				selecting=0;
				selectx=999;
				selecty=999;
			}
//			ȡ��ѡ��
			else if(event==BUTTON_DOWN&&isEffect(px,py,map[i][j].cx,map[i][j].cy)&&map[i][j].isOn&&map[i][j].isSelect&&selecting) {
				selectx=999;
				selecty=999;
				selecting=0;
				map[i][j].isSelect=0;
			}
//			������
			else if(event==BUTTON_DOWN&&isEffect(px,py,map[i][j].cx,map[i][j].cy)&&map[i][j].isOn&&!map[i][j].isSelect&&map[i][j].id!=Chess_Color&&selecting&&rule(i,j)) {
				writenew(selectx,selecty,i,j);
				retractit(i,j);
				if(!map[i][j].type) {
					gaming=1;
					isGaming=0;
					Gameover(Chess_Color);
					mode=-1;
					return;
				}
				if(Chess_Color) {
					Chess_Color=0;
					loser[0][lose_r]=map[i][j].type;
					lose_r++;
				} else {
					Chess_Color=1;
					loser[1][lose_b]=map[i][j].type;
					lose_b++;
				}
				map[i][j].id=map[selectx][selecty].id;
				map[i][j].type=map[selectx][selecty].type;
				map[selectx][selecty].isOn=0;
				map[selectx][selecty].isSelect=0;

				mytimer=time_limit;
				selectx=999;
				selecty=999;
				selecting=0;
			}
		}
	}
//	������
	drawPiece();
}

void movechess(int prex,int prey,int nowx,int nowy) {
	map[prex][prey].isOn=0;
	map[nowx][nowy].isOn=1;
	map[nowx][nowy].id=map[prex][prey].id;
	map[nowx][nowy].isSelect=map[prex][prey].isSelect;
	map[nowx][nowy].type=map[prex][prey].type;
}

void drawPiece() {
	int i,j;
	for(i=0; i<10; i++) {
		for(j=0; j<9; j++) {
			if(map[i][j].isOn) {
				MovePen(map[i][j].cx+Round,map[i][j].cy);
				SetPenColor("Brown");
				StartFilledRegion(1);
				DrawArc(Round,0,360);
				EndFilledRegion();
				if(map[i][j].isSelect) {
					SetPenColor("Black");
					SetPenSize(5);
					MovePen(map[i][j].cx+Round,map[i][j].cy);
					DrawArc(Round,0,360);
					SetPenSize(1);
				}
				if(map[i][j].id) {
					SetPenColor("Black");
				} else {
					SetPenColor("Red");
				}
				SetPointSize(25);
				drawLabel(map[i][j].cx-TextStringWidth("��")/2,map[i][j].cy-TextStringWidth("��")/2,kind[map[i][j].id][map[i][j].type]);
			}
		}
	}
}

void doretract() {
	map[retract[0][3]][retract[0][4]].id=retract[0][0];
	map[retract[0][3]][retract[0][4]].type=retract[0][1];
	map[retract[0][3]][retract[0][4]].isOn=retract[0][2];
	map[retract[0][3]][retract[0][4]].isSelect=0;
	map[retract[1][3]][retract[1][4]].id=retract[1][0];
	map[retract[1][3]][retract[1][4]].type=retract[1][1];
	map[retract[1][3]][retract[1][4]].isOn=retract[1][2];
	map[retract[1][3]][retract[1][4]].isSelect=0;
	writenew(retract[1][3],retract[1][4],retract[0][3],retract[0][4]);
	if(retract[1][2]) {
		if(Chess_Color&&lose_b>0)lose_b--;
		else if(!Chess_Color&&lose_r>0)lose_r--;
	}
	Chess_Color=1-Chess_Color;
	mytimer=time_limit;
	display6();
}

void display6() {
	DisplayClear();
	if(gaming) {
		PlaySound("./GMRemix-�й�����.wav", NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);
		InitMap();
		gaming=0;
		Chess_Color=0;
		isGaming=0;
		mytimer=time_limit;
		lose_r=0;
		lose_b=0;
		isRetract=0;
		if(isRecord) {
			newfile();
		}
	}
//	����ִ�巽
	SetPointSize(25);
	SetPenSize(1);
	if(Chess_Color) {
		SetPenColor("Black");
		drawLabel(0.3,11,"�ڷ�ִ��");
	} else {
		SetPenColor("Red");
		drawLabel(0.3,11,"�췽ִ��");
	}
//	��Ϸ����
	SetPointSize(15);
	setButtonColors("Brown","Brown","Gray","Gray",0);
	if(button(GenUIID(0),0.5,9,2,1, "���¿�ʼ")) {
		gaming=1;
	}

	SetPenColor("brown");
	int k;
	drawLabel(0.5,8,"�췽ʧ��");
	char red[5];
	sprintf(red,"%d",lose_r);
	drawLabel(0.5+TextStringWidth("�췽ʧ�� "),8,red);
	MovePen(0.5,7.3);
	for(k=0; k<lose_r; k++) {
		DrawTextString(kind[0][loser[0][k]]);
	}

	drawLabel(0.5,6.5,"�ڷ�ʧ��");
	char black[5];
	sprintf(black,"%d",lose_b);
	drawLabel(0.5+TextStringWidth("�ڷ�ʧ�� "),6.5,black);
	MovePen(0.5,5.8);
	for(k=0; k<lose_b; k++) {
		DrawTextString(kind[1][loser[1][k]]);
	}
//	����
	if(button(GenUIID(0),0.5,4,2,1, "����")) {
		if(!isRetract) {
			doretract();
			isRetract=1;
		}
	}
//	����ʱ
	drawTimer();
//	��ͣ��������BGM���ư�ť
	setButtonColors("White","Brown","White","Gray",1);
	SetPointSize(10);
	if(button(GenUIID(0),0.5,2.5,0.5,0.5, "||")) {
		isGaming=0;
	}
	if(button(GenUIID(0),1.3,2.5,0.5,0.5, "��")) {
		isGaming=1;
	}
//	����
	drawMap();
//	���ذ�ť
	SetPenSize(1);
	SetPenColor("Black");
	SetPointSize(15);
	setButtonColors("Brown","Brown","Gray","Gray",0);
	if(button(GenUIID(0),0,0,3,1,"����")) {
		mode=7;
	}
//	������drawChess���������
}
