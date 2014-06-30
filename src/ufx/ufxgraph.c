/*
    ufxgraph.c : ufxlib中的图像部分

    Copyright (C) 2001-2012  Anderain Ryu (Hikari no Uihiaru)

    Anderain Ryu - anderain.develop@gmail.com

*/
#include "ufxlib.h"
#include "string.h"
#include "math.h"
#ifndef PLATFORM_FX9860
/*
 * PC API，使用SDL实现
 */
#define SCR_WIDTH       320 
#define SCR_HEIGHT      240
#define SCR_BBP         8
#define CRGB(r,g,b)     (SDL_MapRGB(screen->format,r,g,b))
/*
 * 屏幕surface
 */
SDL_Surface * screen;
/* 
 * 默认的黑白颜色
 */
Uint32 COLOR_WHITE;
Uint32 COLOR_BLACK;
/*
 * 屏幕缓冲区
 */
uchar scrbuf[SCR_WIDTH * SCR_HEIGHT / 8];
/*!
 * @brief 初始化ufxlib、创建窗口
 */
void ufx_GraphInit (int w,int h,const char * title) {
	SDL_Init(SDL_INIT_VIDEO);
    SDL_ShowCursor(FALSE);
    SDL_WM_SetCaption(title,NULL);
    screen = SDL_SetVideoMode(w * UFX_SCR_ZOOM, h * UFX_SCR_ZOOM,SCR_BBP, SDL_SWSURFACE);
 
    COLOR_WHITE = CRGB(255,255,255);
    COLOR_BLACK = CRGB(0,0,0);

    ufx_Clear();
}
/*!
 * @brief 退出ufx、释放资源
 */
void ufx_GraphQuit () {
    SDL_Quit();
}
/*!
 * @brief 清除屏幕内容
 */
void ufx_Clear () {
    memset(scrbuf,0,sizeof(scrbuf));
}
/*!
 * @brief 清除屏幕上一个像素
 * @param x x坐标
 * @param y y坐标
 */
void ufx_ClearPixel (int x,int y) {
    uchar *     p;
    int         t = 1;

    if (x < 0 || y < 0 || x >= SCR_WIDTH || y >= SCR_HEIGHT)
        return;
    
    p =   scrbuf + y * SCR_WIDTH / 8 + x / 8;
    t <<= 7 - x % 8;
    t =   ~t;

    *p &= t;
}
/*!
 * @brief 绘制屏幕上一个像素
 * @param x x坐标
 * @param y y坐标
 */
void ufx_SetPixel (int x,int y) {
    uchar *     p;
    int         t = 1;

    if (x < 0 || y < 0 || x >= SCR_WIDTH || y >= SCR_HEIGHT)
        return;
    
    p =   scrbuf + y * SCR_WIDTH / 8 + x / 8;
    t <<= 7 - x % 8;

    *p |= t;
}
/*!
 * @brief 获取屏幕上一个像素
 * @param x x坐标
 * @param y y坐标
 * @return BOOL
 * @retval TRUE  该像素不为空
 * @retval FALSE 该像素为空
 */
BOOL ufx_GetPixel (int x,int y) {
    uchar *     p;
    int         t = 1;

    if (x < 0 || y < 0 || x >= SCR_WIDTH || y >= SCR_HEIGHT)
        return FALSE;
    
    p = scrbuf + y * SCR_WIDTH / 8 + x / 8;

    return ((*p >> (7 - x % 8)) & 1);
}
/*!
 * @brief 绘制屏幕上一个像素
 * @param x x坐标
 * @param y y坐标
 * @param color 颜色TRUE为黑色FALSE白色
 * @note 内部实现，不需要被外部调用
 */
void ufx_SDL_SetPixel(int x, int y,BOOL color) {
    Uint32    pixel = color ? COLOR_BLACK : COLOR_WHITE;
    SDL_Rect  r;
    r.x = x * UFX_SCR_ZOOM;
    r.y = y * UFX_SCR_ZOOM;
    r.w = UFX_SCR_ZOOM;
    r.h = UFX_SCR_ZOOM;
    SDL_FillRect(screen,&r,pixel);
}
/*!
 * @brief 绘制屏幕上单色位图
 * @param x x坐标
 * @param y y坐标
 * @param w 宽度
 * @param h 高度
 * @param pimage 位图
 * @param mode 绘制模式
 * @note 内部实现，不需要被外部调用
 */
static void ufx_SDL_WriteGraph (int x,int y,int w,int h,const uchar* pimage) {
    uchar   p;
    int     i;
    int     j;
    int     k;
    int     pixel;
    int     rx = 0,ry = 0;
    int     iwidth = w/8 + (w % 8 ? 1:0);

    for (i = 0;i < h; ++i, pimage += iwidth) {
        ry = y + i;
        if (ry >= SCR_HEIGHT)
            return;
        for (j = 0;j < iwidth; ++j) {
            p = pimage[j];
            for (k = 0;k < 8; ++k) {
                rx = x + (7 - k) + (j << 3); /* j * 8 */
                pixel = p & 1;
                p >>= 1;
                if (pixel) {
                    ufx_SDL_SetPixel(rx,ry,TRUE);
                }
                else {
                    ufx_SDL_SetPixel(rx,ry,FALSE);
                }
            }
        }
    }
}
/*!
 * @brief 绘制屏幕上单色位图
 * @param x x坐标
 * @param y y坐标
 * @param w 宽度
 * @param h 高度
 * @param pimage 位图
 * @param mode 绘制模式
 */
void ufx_WriteGraph (int x,int y,int w,int h,const uchar* pimage,int mode,BOOL rev) {
    uchar   p;
    int     i;
    int     j;
    int     k;
    int     pixel;
    int     rx = 0,ry = 0;
    int     iwidth = w/8 + (w % 8 ? 1:0);
    void    (*fnSet)(int,int);
    void    (*fnClear)(int,int);

    if (rev) {
        fnSet = ufx_ClearPixel;
        fnClear = ufx_SetPixel;
    }
    else {
        fnSet = ufx_SetPixel;
        fnClear = ufx_ClearPixel;
    }

    for (i = 0;i < h; ++i, pimage += iwidth) {
        ry = y + i;
        if (ry >= SCR_HEIGHT)
            return;
        for (j = 0;j < iwidth; ++j) {
            p = pimage[j];
            for (k = 0;k < 8; ++k) {
                rx = x + (7 - k) + (j << 3); /* j * 8 */
                pixel = p & 1;
                p >>= 1;
                if (rx >= w + x)
                    continue;
                if (pixel) {
                    fnSet(rx,ry);
                }
                else {
                    switch (mode) {
                    case UFX_OVER:
                        fnClear(rx,ry);
                        break;
                    case UFX_OR:
                        if (!ufx_GetPixel(rx,ry))
                            fnClear(rx,ry);
                        break;
                    case UFX_AND:
                    default:
                        break;
                    }
                }
            }
        }
    }
}
/*!
 * @brief 绘制直线
 * @param x1 点1x坐标
 * @param y1 点1y坐标
 * @param x2 点2x坐标
 * @param y2 点2y坐标
 */
void ufx_DrawLine (int x1,int y1,int x2,int y2,BOOL rev) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int ux = ((dx > 0) << 1) - 1;
    int uy = ((dy > 0) << 1) - 1;
    int x = x1, y = y1, eps = 0;

    void    (*fnSet)(int,int);

    fnSet = rev ? ufx_ClearPixel : ufx_SetPixel;

    dx = abs(dx);
    dy = abs(dy);
    if (dx > dy) {
        for (x = x1; x!= x2; x+= ux) {
            fnSet(x,y);
            eps += dy;
            if ((eps << 1) >= dx) {
                y += uy;
                eps -= dx;
            }
        }
    }
    else {
        for (y = y1; y != y2; y+= uy) {
            fnSet(x,y);
            eps += dx;
            if ((eps << 1) >= dy) {
                x += ux;
                eps -= dy;
            }
        }
    }
}
/*!
 * @brief 绘制屏幕上单色位图
 *        自动忽略边缘的空白
 * @param x x坐标
 * @param y y坐标
 * @param w 宽度
 * @param h 高度
 * @param pimage 位图
 * @param mode 绘制模式
 * @note 内部实现，不需要被外部调用
 */
void ufx_WriteGraphAuto (int x,int y,int w,int h,const uchar* pimage,BOOL flip) {
    uchar   p;
    int     i;
    int     j;
    int     k;
    int     pixel;
    int     rx = 0,ry = 0;
    int     iwidth = w/8 + (w % 8 ? 1:0);
    
    int     whiteStart;
    int     whiteLength;

    for (i = 0,ry = y;i < h; ++i, pimage += iwidth,++ry) {
        rx = x;
        whiteStart = -1;
        whiteLength = 0;
        for (j = 0;j < iwidth; ++j) {
            p = pimage[j];
            for (k = 0;k < 8; ++k,++rx) {
                /* 获取像素 */
                pixel = p >> (7 - k) & 1;
                /* 像素为黑色 */
                if (pixel) {
                    ufx_SetPixel(flip ? w - 1 - rx : rx,ry);
                    if (whiteStart != -1) {
                        int i;
                        for (i = 0; i < whiteLength; ++i) {
                            int x = whiteStart + i;
                            ufx_ClearPixel(flip ? w - 1 - x : x,ry);
                        }
                        whiteLength = 0;
                    }
                    whiteStart = rx + 1;
                }
                /* 像素为白色 */
                else {
                    if (whiteStart != -1)
                        whiteLength++;
                }
            }
        }
    }
}
/*!
 * @brief 填充空白
 * @param x x坐标
 * @param y y坐标
 * @param w 宽度
 * @param h 高度
 */
void ufx_FillRect (int x,int y,int w,int h,BOOL clear) {
    void (*draw)(int,int) = clear ? ufx_ClearPixel : ufx_SetPixel;
    int i,j;

    for (j = 0;j < h; ++j)
        for (i = 0;i < w; ++i)
            draw(i + x,j + y);
}
/*!
 * @brief 刷新屏幕内容
 */
void ufx_Flip () {
    ufx_SDL_WriteGraph(0,0,SCR_WIDTH,SCR_HEIGHT,scrbuf);
    SDL_Flip(screen);
}

#else
/*
 * fx-9860 API，使用fxlib实现
 */

#endif