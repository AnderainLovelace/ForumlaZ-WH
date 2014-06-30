#include "ufxlib.h"
#include "font.h"

#define FONT_WIDTH      6
#define FONT_HEIGHT     8

ufxfile fontFile;

void font_Init () {
    fontFile = ufx_OpenReadOnlyFile("data/font6x8.dat");
    if (ufx_OpenFail(fontFile)) {
        exit(0);
        return;
    }
}

void font_Quit () {
    ufx_FileClose(fontFile);
}

void font_Print (int x,int y,const char * str,int rev) {
    for (;*str;++str) {
        font_PrintChar(x,y,*str,rev);
        x += FONT_WIDTH;
    }
}

void font_PrintChar (int x,int y,char c,int rev) {
    unsigned char mat[8 * FONT_HEIGHT / 8];
    long offset = (long)c * sizeof(mat);
    ufx_FileRead(fontFile,mat,sizeof(mat),offset);
    ufx_WriteGraph(x,y,FONT_WIDTH,FONT_HEIGHT,mat,UFX_OVER,rev);
}