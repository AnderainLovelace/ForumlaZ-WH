#ifndef _FONT_H_
#define _FONT_H_

void font_Init      ();
void font_Quit      ();
void font_Print     (int x,int y,const char * str,int rev);
void font_PrintChar (int x,int y,char c,int rev);

#endif