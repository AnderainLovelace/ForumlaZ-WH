/*
    ufxfile.c : ufxlib中的按键部分

    Copyright (C) 2001-2012  Anderain Ryu (Hikari no Uihiaru)

    Anderain Ryu - anderain.develop@gmail.com

*/
#include "ufxlib.h"
#include "stdio.h"

#ifndef PLATFORM_FX9860
/*
 * 按键映射表
 */
typedef struct {
    int fxk;
    int sdlk;
}UFXKEYMAP;

extern UFXKEYMAP KEYMAP[];

/*
 * PC API，使用SDL实现
 */

void ufx_UpdateEvent () {

}
uint ufx_GetKey () {
    ufx_Flip();

	while (TRUE) {
        SDL_Event event;
        SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) { 
            exit(0);
		}
		else if (event.type == SDL_KEYDOWN) {
            int i;
            if (KMOD_SHIFT & event.key.keysym.mod) {
                switch(event.key.keysym.sym) {
                    case SDLK_1:        return '!';
                    case SDLK_2:        return '@';
                    case SDLK_3:        return '#';
                    case SDLK_4:        return '$';
                    case SDLK_5:        return '%';
                    case SDLK_6:        return '^';
                    case SDLK_7:        return '&';
                    case SDLK_8:        return '*';
                    case SDLK_9:        return '(';
                    case SDLK_0:        return ')';
                    case SDLK_MINUS:    return '_';
                    case SDLK_EQUALS:   return '+';
                    default:            return 0;
                }
            }
            else {
                for (i = 0; KEYMAP[i].sdlk != -1 ; ++i) {
                    if (event.key.keysym.sym == KEYMAP[i].sdlk) {
                        return KEYMAP[i].fxk;
                    }
                }
            }
		}
    }

    return 0;
}

/*
 * 按键映射表定义
 */
UFXKEYMAP KEYMAP[] = {
    {'a',SDLK_a},
    {'b',SDLK_b},
    {'c',SDLK_c},
    {'d',SDLK_d},
    {'e',SDLK_e},
    {'f',SDLK_f},
    {'g',SDLK_g},
    {'h',SDLK_h},
    {'i',SDLK_i},
    {'j',SDLK_j},
    {'k',SDLK_k},
    {'l',SDLK_l},
    {'m',SDLK_m},
    {'n',SDLK_n},
    {'o',SDLK_o},
    {'p',SDLK_p},
    {'q',SDLK_q},
    {'r',SDLK_r},
    {'s',SDLK_s},
    {'t',SDLK_t},
    {'u',SDLK_u},
    {'v',SDLK_v},
    {'w',SDLK_w},
    {'x',SDLK_x},
    {'y',SDLK_y},
    {'z',SDLK_z},

    {'0',SDLK_0},
    {'1',SDLK_1},
    {'2',SDLK_2},
    {'3',SDLK_3},
    {'4',SDLK_4},
    {'5',SDLK_5},
    {'6',SDLK_6},
    {'7',SDLK_7},
    {'8',SDLK_8},
    {'9',SDLK_9},

    {'0',SDLK_KP0},
    {'1',SDLK_KP1},
    {'2',SDLK_KP2},
    {'3',SDLK_KP3},
    {'4',SDLK_KP4},
    {'5',SDLK_KP5},
    {'6',SDLK_KP6},
    {'7',SDLK_KP7},
    {'8',SDLK_KP8},
    {'9',SDLK_KP9},

    {'\n',SDLK_KP_ENTER},

    {'\n',SDLK_RETURN},
    {'\b',SDLK_BACKSPACE},

    {'+',SDLK_PLUS},
    {'-',SDLK_MINUS},
    {'=',SDLK_EQUALS},
    {'*',SDLK_PERIOD},
    {'/',SDLK_SLASH},
    {',',SDLK_COMMA},

    {'+',SDLK_KP_PLUS},
    {'-',SDLK_KP_MINUS},
    {'*',SDLK_KP_MULTIPLY},
    {'/',SDLK_KP_DIVIDE},
    {-1,-1}
};
#else
/*
 * fx-9860 API，使用fxlib实现
 */

#endif