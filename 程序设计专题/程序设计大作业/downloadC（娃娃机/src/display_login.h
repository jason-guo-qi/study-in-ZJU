#ifndef _DISPLAY_LOGIN_H
#define _DISPLAY_LOGIN_H
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

/*
 * The following constants control the sizes of the
 * windows.
 */
#define WindowWidth 20.0
#define WindowHeight 14.0
/*
 * The followings are my functions
 */
void display1();//��¼����
void WriteName(char name1[],char name2[]);//���û���д���ļ�
char* getname1();//����name1
char* getname1();//����name2
/*
 * The followings are imGUI functions
 */
void CharEventProcess(char ch);// �û����ַ��¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event);// �û�������¼���Ӧ����
#endif
