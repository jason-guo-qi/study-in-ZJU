#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "imgui.h"
#include "Main.h"
#include "FunctionLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h> 
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <string.h>
 
//绘制主界面按钮
void drawMainButtons() 
{
	
	fH = GetFontHeight();
	h = fH * 4;  
	x = winwidth / 2.5;
	y = winheight / 2 - h;
	w = winwidth / 5; 

	setButtonColors("Blue", "Green", "Red", "white", 1);
	if (button(GenUIID(0), x - 0.6 * w , y - 2 * h, w, h,"用户登录"))
	{
		status = 1;
		display();
	} 
		
	if (button(GenUIID(1), x - 0.6 * w , y - 3.5 * h, w, h,"管理员登陆"))
	{
		status = 2;
		display();
	}
	
	if (button(GenUIID(0), x + w * 0.6, y - 2 * h, w, h, "帮助"))
	{
		system("Help.txt");
	}
	
	if (button(GenUIID(1), x + w * 0.6, y - 3.5 * h, w, h, "退出"))
	{
		exit(-1); 
	}		
} 

//绘制主界面中心标语与滚动标语 
void drawMainBox()
{
	x = winwidth / 4; 
	y = winheight / 2; 
	w = winwidth / 2; 
	h = GetFontHeight() * 8;
	SetPointSize(50); 
	SetPenColor("Black");
	drawBox(x, y, w, h, 0, "旅游产品管理系统", 'C', "Orange");
	SetPointSize(GetFontHeight()); 
}
//绘制边界圆弧

void DrawleftArc() 
{ 

 SetPenColor("Orange");
 SetPenSize(2) ;                             
 MovePen(2,0);
 DrawArc(2,0,90);
   SetPointSize(30);
 drawBox(0, 0, 2, 2, 0, "欢迎", 'L', "Red");
 
 MovePen(2.828,0);
 SetPenColor("Yellow");
  DrawArc(2.828,0,90);
  drawBox(0, 0, 2.828, 2.828, 0, "  ", 'L', "White");
}

void DrawrightArc() 
{   SetPenSize(2) ;
SetPenColor("Orange");
 MovePen(winwidth*1.0-2.0,0.0);
 DrawArc(2,180,-90);
  MovePen(winwidth*1.0-2.828,0.0);
   SetPenColor("Yellow");
 DrawArc(2.828,180,-90);
  SetPointSize(30);
  SetPenColor("Orange");
drawBox(winwidth*1.0-2.0,0.0, 2, 2, 0, "登录", 'R', "Red");
SetPenColor("Yellow");
  drawBox(winwidth*1.0-2.828, 0, 2.828, 2.828, 0, "  ", 'R', "White");
  
}
