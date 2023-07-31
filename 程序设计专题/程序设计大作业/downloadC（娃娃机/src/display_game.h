#ifndef _DISPLAY_GAME_H
#define _DISPLAY_GAME_H
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include "linkedlist.h"
#include <math.h>
#include "imgui.h"
#include <windows.h>
#pragma  comment (lib,"Winmm.lib") //ʹ�����ֲ��ſ�


/*
 * The following constants control the sizes of the
 * windows.
 */
#define WindowWidth 20.0
#define WindowHeight 14.0
#define timer_interval 1000
#define time_limit 45

/*
 * The followings are my functions
 */
void display6();//��Ϸ����
void drawMap();//������
void drawChess(double px, double py, int button, int event);//���Ӻ���
int rule(int pi, int pj);//�ж��߷��Ƿ����
void drawTimer();//����ʱģ��
void record(int Record);//����¼�����
void drawPiece();//������
void movechess(int px,int py,int nx,int ny);//���������ƶ���Ϣ
void retractit(int i,int j);//��¼��һ������
void doretract();//����
/*
 * The followings are imGUI functions
 */
void MouseEventProcess(int x, int y, int button, int event);// �û�������¼���Ӧ����
void TimerEventProcess(int timerID);// �û��ļ�ʱ��ʱ����Ӧ����
void KeyboardEventProcess(int key, int event);// �û��ļ����¼���Ӧ����
#endif
