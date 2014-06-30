#include "ufxlib.h"
#include "font.h"
#include "ctype.h"
#include "string.h"
#include "conio.h"
#include "defs.h"

#define SCR_WIDTH           240
#define SCR_HEIGHT          128

#define STACK_SIZE          99
#define BUFFER_SIZE         128
#define FONT_WIDTH          6
#define FONT_HEIGHT         8
#define EMPTY_TOKEN         "[]"

#define SYM_ABS             "abs"
#define SYM_SQRT            "sqrt"
#define SYM_NEG             "neg"

#define fz_StrEq(s1,s2)     (strcmp(s1,s2)==0)
#define fz_ExprSave()       {const char * p = pexpr;
#define fz_ExprRestore()    pexpr = p;}

enum {
    T_OPR = 1,T_NUM,T_VAR,T_END,T_ERR,T_STR
};

struct {
    char *  s;
    int     n;
}
FUNCS[] = {
    {"sin"      ,1},
    {"cos"      ,1},
    {"tan"      ,1},
    {"log"      ,1},
    {"expand"   ,1},
    {"factor"   ,1},
    {"equals"   ,2},
    {"sum"      ,4},
    {SYM_ABS    ,1},
    {SYM_SQRT   ,1},
    {""         ,-1},
};

const char *    expr   = NULL;
const char *    pexpr  = NULL;
char            token[BUFFER_SIZE];
int             toktype;
char            poexpr[BUFFER_SIZE];
char       *    ppoexpr;

void fz_GetNextSize (int *w,int *h);
int fz_GetNextTop   (int x,int y,int *rtop);

void fz_SetExpr (const char * e) {
    expr = pexpr = e;
}

int fz_Max (int a,int b) {
    return a > b ? a : b;
}

char * fz_GetToken () {
    char * t = token;
    *t = '\0';
    while (isspace(*pexpr))
        pexpr++;
    if (*pexpr == 0) {
        toktype = T_END;
        return token;
    }
    if (*pexpr == '+' || *pexpr == '-' ||
        *pexpr == '*' || *pexpr == '/' ||
        *pexpr == '^' || *pexpr == '(' || 
        *pexpr == ')' || *pexpr == '|' ||
        *pexpr == '#' || *pexpr == '=') {
        *t++ = *pexpr++;
        *t = '\0';
        toktype = T_OPR;
        return token;
    }
    else if (isdigit(*pexpr)) {
        toktype = T_NUM;
        while (isdigit(*pexpr)) {
            *t++ = *pexpr++;
        }
        if (*pexpr != '.') {
            *t = '\0';
            return token;
        }
        *t++ = *pexpr++;
        while (isdigit(*pexpr)) {
            *t++ = *pexpr++;
        }
        *t = '\0';
        
        return token;
    }
    else if (isalpha(*pexpr)) {
        toktype = T_VAR;
        while (isalnum(*pexpr)) {
            *t++ = *pexpr++;
        }
        *t = '\0';
        return token;
    }
    else if (*pexpr == '\\') {
        toktype = T_OPR;
        *t++ = *pexpr++;
        while (isalpha(*pexpr)) {
            *t++ = *pexpr++;
        }
        *t = '\0';
        return token;
    }
    else if (*pexpr == '\"') {
        do {
            *t++ = *pexpr++;
        } while (*pexpr != '\"' && *pexpr != '\0');
        *t++ = '\"'; *t = 0;
        toktype = T_STR;
        return token;
    }
    else {
        *t++ = *pexpr++;
        *t = '\0';
        toktype = T_ERR;
        return token;
    }
}

int fz_IsFuncName(const char * name) {
    int i;
    for (i = 0;FUNCS[i].n != -1; ++i) {
        if (fz_StrEq(name,FUNCS[i].s))
            return FUNCS[i].n;
    }
    return -1;
}

void fz_Print (int x,int y,const char * s,BOOL disp) {
    if (disp)
        font_Print(x,y,s,FALSE);
}

void fz_DrawLine (int x1,int y1,int x2,int y2,BOOL disp) {
    if(disp)
        ufx_DrawLine(x1,y1,x2,y2,FALSE);
}

void fz_Render (int x,int y,BOOL disp,int * w,int * h,int * rtop) {
    int width = 0,height = 0;
    fz_GetToken();
    /* error , draw a empty token */
    if (toktype == T_END) {
        fz_Print(x,y,EMPTY_TOKEN,disp);
        /* width & height */
        width  = strlen(EMPTY_TOKEN) * FONT_WIDTH;
        height = FONT_HEIGHT;
    }
    /* linear binary operator */
    else if (*token == '+' || *token == '-' || *token == '*' || *token == '=') {
        char    tokbuf[BUFFER_SIZE];
        int     heightl,heightr,widthl,widthr,widthc;

LINEAR_OPR:

        strcpy(tokbuf,token);
        
        fz_GetNextSize(&widthl,&heightl);
        fz_Render(x,y,disp,NULL,NULL,rtop);

        widthc  = strlen(tokbuf) * FONT_WIDTH;
        fz_Print(x + widthl,y,tokbuf,disp);
        
        fz_GetNextSize(&widthr,&heightr);
        fz_Render(x + widthl + widthc,y,disp,NULL,NULL,rtop);

        /* width & height */
        width  = widthc + widthl + widthr;
        height = fz_Max(heightl,heightr);
    }
    /* div */
    else if (*token == '/') {
        int heighta,heightl,widtha,widthl,topa,topl;
        const int border = 4;
        y += 3;
        x += 1;

        fz_ExprSave();

        fz_GetNextTop(x,y,&topa);
        fz_Render(0,0,FALSE,&widtha,&heighta,NULL);

        fz_GetNextTop(x,y,&topl);
        fz_Render(0,0,FALSE,&widthl,&heightl,NULL);

        fz_ExprRestore();

        /* width & height ;*/

        width  = fz_Max(widtha,widthl) + border * 2;
        height = heightl + heighta + 2;

        fz_Render(x + (width - widtha) / 2 ,y - heighta + topa,disp,NULL,NULL,rtop);
        fz_Render(x + (width - widthl) / 2 ,y + 2 + topl,disp,NULL,NULL,rtop);

        fz_DrawLine(x + 1,y,x + width - 1,y,disp);

        //y -= heighta;
    }
    /* abs */
    else if (fz_StrEq(token,SYM_ABS)) {
        const int   border = 1;
        int         top;

        x++;

        fz_GetNextTop(x,y,&top);
        fz_Render(x + border,y,disp,&width,&height,rtop);

        width += border * 2 + 2;

        y -= top;
        

        height--;

        fz_DrawLine(x,y,x,y + height,disp);
        fz_DrawLine(x + width - 1,y,x + width - 1,y + height,disp);

        height++;
        width++;
    }
    /* abs */
    else if (fz_StrEq(token,SYM_SQRT)) {
        const int   border = 2;
        int         top;

        x += border * 2 + 1;

        fz_GetNextTop(x,y,&top);
        fz_Render(x + border,y,disp,&width,&height,rtop);
        
        x -= border;

        width += border * 2;

        y -= top + 2;
        
        x;

        fz_DrawLine(x,y,x,y + height,disp);
        fz_DrawLine(x,y,x + width + border * 2,y ,disp);
        fz_DrawLine(x,y + height,x - 3,y + height - 3,disp);

        width += border * 2 + 2;
        height += 2;
    }
    /* () */
    else if (*token == '(' || *token == ')') {
        const int   border = 3;
        const int   borderh = 2;
        int         top;

        x++;

        fz_GetNextTop(x,y,&top);
        fz_Render(x + border,y,disp,&width,&height,rtop);

        width += border * 2 + 1;

        y -= top;
        height--;
        // left
        {
            int rx = x,ry = y + borderh;
            fz_DrawLine(rx,ry,rx + borderh,ry - borderh,disp);
            fz_DrawLine(rx,ry,rx,ry + height - 2 * borderh,disp);
            ry += height - 2 * borderh;
            fz_DrawLine(rx,ry,rx + borderh,ry + borderh,disp);

        }
        // right
        {
            int rx = x + width - 1,ry = y + borderh;
            fz_DrawLine(rx,ry,rx - borderh,ry - borderh,disp);
            fz_DrawLine(rx,ry,rx,ry + height - 2 * borderh,disp);
            ry += height - 2 * borderh;
            fz_DrawLine(rx,ry,rx - borderh,ry + borderh,disp);
        }
        height++;
        width++;
    }
    /* power */
    else if (*token == '^') {
        int heightl,heightr,widthl,widthr,top,yo = y;

        fz_GetNextTop(x,y,&top);
        fz_GetNextSize(&widthl,&heightl);
        fz_Render(x,y,disp,NULL,NULL,rtop);

        fz_GetNextSize(&widthr,&heightr);

        y -= top + heightr / 2;

        if (heightl < heightr)
            height = heightl / 2 + heightr;
        else
            height = heightl + heightr / 2;

        fz_Render(x + widthl,y,disp,NULL,NULL,rtop);
        
        /* width & height */
        width  = widthl + widthr;

    }
    /* equals */ 
    else if (fz_StrEq(token,"equals")) {
        strcpy(token,"=");
        goto LINEAR_OPR;
    }
    /* negtive */
    else if (fz_StrEq(token,SYM_NEG)) {
        int             w;
        const char  *   neg = "-";

        fz_Print(x,y,neg,disp);

        width = strlen(neg) * FONT_WIDTH;
        x += width;

        fz_Render(x,y,disp,&w,&height,rtop);

        width += w;
    }
    /* sum */
    else if (fz_StrEq(token,"sum")) {
        int w1,h1,w2,h2,w3,h3,w4,h4;
    }
    /* variable or number */
    else {
        int n;
        /* function */
        n = fz_IsFuncName(token);
        if (n != -1) {
            const int   border = 3;
            const int   borderh = 2;
            int w = 0,h = 0,ox = x;

            fz_Print(x,y,token,disp);

            width  = strlen(token) * FONT_WIDTH;
            height = FONT_HEIGHT;
            x += width;

            {
                fz_Print(x,y,"(",disp);
                x += FONT_WIDTH;
                width += FONT_WIDTH;
            }

            while (n-- > 0) {
                fz_Render(x,y,disp,&w,&h,rtop);
    
                x += w ;
                width += w;
                if (n != 0) {
                    fz_Print(x,y,",",disp);
                    x += FONT_WIDTH;
                    width += FONT_WIDTH;
                }
                if (h > height)
                    height = h;
            }
            {
                fz_Print(x,y,")",disp);
                x += FONT_WIDTH;
                width += FONT_WIDTH;
            }
        }
        else {
            fz_Print(x,y,token,disp);
            /* width & height */
            width  = strlen(token) * FONT_WIDTH;
            height = FONT_HEIGHT;
        }
    }
    /* save border position*/
    if (rtop && y < *rtop) {
        *rtop = y;
    }
    if (w != NULL) {
        *w = width;
    }
    if (h != NULL) {
        *h = height;
    }
}

struct {
    char * s;
    int    p;
}
OPRPRIORITY [] = {
    {"+"    ,10},
    {"-"    ,10},
    {"*"    ,12},
    {"/"    ,12},
    {"^"    ,13},
    {"neg"  ,11},
    {""     ,-1},
};

int fz_GetPriority(const char * name) {
    int i;
    for (i = 0;OPRPRIORITY[i].p != -1; ++i) {
        if (fz_StrEq(name,OPRPRIORITY[i].s))
            return OPRPRIORITY[i].p;
    }
    return -1;
}

void fz_ExprToPreorderPop (char ** ostack,char ** nstack,int *osize,int *nsize) {
    char * T_OPR = ostack[--(*osize)];
    char * l = NULL,* r = NULL;
    char buf[BUFFER_SIZE];

    if (fz_StrEq(T_OPR,SYM_NEG)) {
        l = nstack[--(*nsize)];

        sprintf(buf,"%s %s",T_OPR,l);
    }
    else{
        l = nstack[--(*nsize)];
        r = nstack[--(*nsize)];

        sprintf(buf,"%s %s %s",T_OPR,r,l);
    }
    nstack[(*nsize)++] = strdup(buf);

    free(l);
    free(T_OPR);
    if (r != NULL)
        free(r);
}

void fz_ExprToPreorder(const char * e,char * p) {
    char *  ostack[STACK_SIZE];
    char *  nstack[STACK_SIZE];
    int     osize = 0,nsize = 0;
    int     bcount = 0;
    BOOL    pre_check = TRUE;

    if (e != NULL)
        fz_SetExpr(e);

    while (TRUE) {
        fz_GetToken();
       
        if (toktype == T_END || toktype == T_ERR)
            break;
        if (*token == '(') {
            ostack[osize++] = strdup(token);
            bcount++;
        }
        else if (*token == ')') {
            if (bcount <= 0) {
                break;
            }
            bcount--;
            while (osize > 0) {
                if (*ostack[osize-1] == '(') {
                    char buf2[BUFFER_SIZE];
                    sprintf(buf2,"( %s",nstack[nsize-1]);
                    free(nstack[--nsize]);
                    nstack[nsize++] = strdup(buf2);
                    osize--;
                    break;
                }
                fz_ExprToPreorderPop(ostack,nstack,&osize,&nsize);
            }
        }
        else if (toktype == T_OPR) {
            if (pre_check && *token == '-') {
                ostack[osize++] = strdup(SYM_NEG);
            }
            else {
                while (osize > 0 && fz_GetPriority(token) <= fz_GetPriority(ostack[osize-1])) {
                    fz_ExprToPreorderPop(ostack,nstack,&osize,&nsize);
                }
                ostack[osize++] = strdup(token);
            }
        }
        else {
            int n = fz_IsFuncName(token);
            if (n != -1) {
                char    bufexpr[BUFFER_SIZE];
                char    buf2[BUFFER_SIZE];
                int     i;

                sprintf(bufexpr,"%s ",token);

                fz_GetToken(); /* skip '(' */

                for(i = 0; i < n; ++i) {    
                    fz_ExprToPreorder(NULL,buf2);
                    nstack[nsize++] = strdup(buf2);
                }

                for (i = 0; i < n ; ++i) {
                    sprintf(strchr(bufexpr,0),"%s ",nstack[nsize-1]);
                    free(nstack[--nsize]);
                }

                nstack[nsize++] = strdup(bufexpr);
            }
            else{
                nstack[nsize++] = strdup(token);
            }
        }
        /* pre check */
        if (*token == '(')
            pre_check = TRUE;
        else
            pre_check = FALSE;
    }
    while (osize > 0) {
        fz_ExprToPreorderPop(ostack,nstack,&osize,&nsize);
    }
    strcpy(p,nstack[0]);
    free(nstack[0]);
}

void fz_GetNextSize (int *w,int *h) {

    fz_ExprSave();
    fz_Render(0,0,FALSE,w,h,NULL);
    fz_ExprRestore();
}

int fz_GetNextTop (int x,int y,int * rtop) {
    *rtop = y;

    fz_ExprSave();
    fz_Render(x,y,FALSE,NULL,NULL,rtop);
    fz_ExprRestore();

    return (*rtop = y - *rtop);
}

void fz_GetRenderedSize (const char * e,int *w,int *h) {
    fz_SetExpr(e);
    fz_GetNextSize(w,h);
}

void fz_Display (int x,int y,const char * e) {
    int top = 0;

    fz_ExprToPreorder(e,poexpr);
    fz_SetExpr(poexpr);
    fz_GetNextTop(x,y,&top);
    fz_Render(x,y + top,TRUE,NULL,NULL,NULL);
}

void fz_DisplayPreorder (int x,int y,const char * e) {
    int top = 0;

    fz_SetExpr(e);
    fz_GetNextTop(x,y,&top);
    fz_Render(x,y + top,TRUE,NULL,NULL,NULL);
}

void get_line (char * s) {
    const int       height = 11;
    unsigned int    c;
    int             len = strlen(s);
    const int       x = 0,y = SCR_HEIGHT - height;
    const int       cwidth = SCR_WIDTH / FONT_WIDTH - 2;

    ufx_DrawLine(x,y - 1,x + SCR_WIDTH,y - 1,FALSE);

    while (TRUE) {

        ufx_FillRect(x,y,SCR_WIDTH,height,TRUE);
        font_Print(x,y+2,":",FALSE);
        font_Print(x+FONT_WIDTH,y+2,len <= cwidth ? s : s + (len - cwidth),FALSE);
        font_Print(len <= cwidth ? (len+1)*FONT_WIDTH : SCR_WIDTH - FONT_WIDTH,y+2,"_",FALSE);
        c = ufx_GetKey();
        if (c == '\n') {
            return;
        }
        else if (c == '\b') {
            if (len > 0) {
                s[--len] = 0;
            }
        }
        else if (c != 0){
            s[len] = c;
            s[++len] = 0;
        }
    }
}
/* history */
char * historyi[STACK_SIZE];
char * historyo[STACK_SIZE];
int    history_size = 0;

void redraw_history () {
    int             i;
    int             y = 0;
    const int       height = 10;
    const char *    title = "FormulaZ Renderer";

    ufx_Clear();

    y = SCR_HEIGHT - height - 2;

    for (i = history_size - 1; i >= 0; --i) {
        const char  *ei = historyi[i],*eo = historyo[i];
        int          wl,hl,wr,hr;

        fz_GetRenderedSize(ei,&wl,&hl);
        fz_GetRenderedSize(eo,&wr,&hr);

        if (wr + wl < SCR_WIDTH) {
            int h;
            y -= h = fz_Max(hr,hl);

            fz_DisplayPreorder(0,y + (h - hl) / 2,ei);
            fz_DisplayPreorder(SCR_WIDTH - wr,y + (h - hr) / 2,eo);
        }
        else {
            y -= hr+hl;
            fz_DisplayPreorder(0,y,ei);
            fz_DisplayPreorder(SCR_WIDTH - wr,y + hl,eo);
        }
        y -= 2;
        ufx_DrawLine(0,y,SCR_WIDTH,y,FALSE);
        if (y <= 0)
            break;
    }
    /* title */
    y = 0;
    if (SCR_HEIGHT > 64) {
        ufx_FillRect(0,0,SCR_WIDTH,height,FALSE);
        ufx_DrawLine(0,y + height,SCR_WIDTH,y + height,FALSE);
        font_Print((SCR_WIDTH - strlen(title)*FONT_WIDTH)/2,1,title,TRUE);
    }
}

int main (int argc,char * argv[]) {
    char expr[BUFFER_SIZE] = "";

    ufx_GraphInit(SCR_WIDTH,SCR_HEIGHT,"ForumlaZ Renderer");
    font_Init();
    
    history_size = 0;

    while (TRUE) {
        redraw_history ();

        get_line(expr);
        
        if (fz_StrEq(expr,"quit")) {
            break;
        }
        run(expr);
        {
            char ei[BUFFER_SIZE],eo[BUFFER_SIZE];

            fz_ExprToPreorder(expr,ei);
            historyi[history_size] = strdup(ei);
            
        
            if (fz_StrEq(lineread(),"")) {
                historyo[history_size] = strdup("\"Done\"");
            }
            else {
                fz_ExprToPreorder(lineread(),eo);
                historyo[history_size] = strdup(eo);
            }
            history_size++;
        }
    }
    fz_DisplayPreorder(0,0,expr);
    ufx_GetKey();
    font_Quit();
    ufx_GraphQuit();
    return 0;
}