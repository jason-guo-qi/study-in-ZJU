#ifndef _WRITEFILE_H
#define _WRITEFILE_H
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
void newfile();//�������ļ� 
void writenew(int px,int py,int nx,int ny);//д���²��� 
void close_fn(int isClose);//��Ϸ�����رռ�¼ 
#endif
