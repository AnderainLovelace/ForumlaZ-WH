#ifndef _UFXLIB_H_
#define _UFXLIB_H_

#if !(defined(__GNUC__) || defined(_MSC_VER))
#   define PLATFORM_FX9860
#endif

#ifdef PLATFORM_FX9860
#   include "fxlib.h"
#else
#   include "SDL.h"
#   define UFX_SCR_ZOOM     2
#endif

typedef unsigned char   uchar;
typedef unsigned int    uint;
typedef int             BOOL;

#ifndef TRUE
#   define TRUE 1
#endif
#ifndef FALSE
#   define FALSE 0
#endif

/*
 * UFXLIB GRAPH
 */

#define UFX_OVER    1
#define UFX_AND     2
#define UFX_OR      3

void ufx_GraphInit      (int,int,const char *);
void ufx_GraphQuit      ();
void ufx_Clear          () ;
void ufx_ClearPixel     (int x,int y);
void ufx_SetPixel       (int x,int y);
BOOL ufx_GetPixel       (int x,int y);
void ufx_WriteGraph     (int x,int y,int w,int h,const uchar* pimage,int mode,BOOL rev);
void ufx_WriteGraphAuto (int x,int y,int w,int h,const uchar* pimage,BOOL flip);
void ufx_DrawLine       (int x1,int y1,int x2,int y2,BOOL rev);
void ufx_Flip           ();
void ufx_FillRect       (int x,int y,int w,int h,BOOL clear);

/*
 * UFXLIB FILE
 */
#ifdef PLATFORM_FX9860
    typedef int     ufxfile;
#else
    typedef FILE*   ufxfile;
#endif
 
ufxfile ufx_OpenReadOnlyFile    (const char * fileName);
BOOL    ufx_OpenFail            (ufxfile fh);
void    ufx_FileRead            (ufxfile fh,void * buf,size_t size,size_t pos);
void    ufx_FileClose           (ufxfile fh);

/*
 * UFXLIB KEY
 */
#ifndef PLATFORM_FX9860
#   include "ufxkeycode.h"
#endif

uint ufx_GetKey ();

/*
 * UFXLIB CHINESE
 */
typedef struct
{
	char			author[16]		;
	unsigned int	cwidth			;
	unsigned int	awidth,height	;
	unsigned int	asc_offset		;
	unsigned int	chs_offset		;
	ufxfile			file_handle		;
	int				cfont_size		;
	int				afont_size		;
}
ufxfont;

ufxfont *   ufx_ChsOpenFont     (const char * fileName);
void        ufx_ChsCloseFont    (ufxfont * ff);
void        ufx_ChsSelectFont   (ufxfont * font);
void        ufx_ChsPrintChar    (int x,int y,int sel,unsigned char c1,unsigned char c2);
void        ufx_ChsPrintCharA   (int x,int y,int sel,unsigned char c);
void        ufx_ChsPrint        (int x,int y,int sel,const unsigned char * str);

#endif