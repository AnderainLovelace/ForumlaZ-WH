#include <stdio.h>

char    buf[1024];
char *  pbuf;

void lineclear () {
    pbuf = buf;
}

void lineend() {
    *pbuf = '\0';
}

const char * lineread() {
    return buf;
}

void printchar(int c)
{
    putchar(c);
    *pbuf++ = c ;
}

void printstr(const char * s)
{
    while (!*s) {
        printchar(*s++);
    }
}