/*
    ufxfile.c : ufxlib中的文件部分

    Copyright (C) 2001-2012  Anderain Ryu (Hikari no Uihiaru)

    Anderain Ryu - anderain.develop@gmail.com

*/
#include "ufxlib.h"
#include "stdio.h"
#ifndef PLATFORM_FX9860
/*
 * PC API，使用POSIX接口实现
 */
/*!
 * @brief 打开只读文件
 * @param fileName 文件名
 * @return ufxfile 文件句柄
 */
ufxfile ufx_OpenReadOnlyFile (const char * fileName) {
    FILE * fp = fopen(fileName,"rb");
    return fp;
}
/*!
 * @brief 检测文件是否打开失败
 * @param fh 文件句柄
 */
BOOL ufx_OpenFail (ufxfile fh) {
    return fh == NULL;
}
/*!
 * @brief 读取文件
 * @param fh 文件句柄
 * @param buf 读取缓冲
 * @param pos 读取位置
 * @param size 读取大小
 */
void ufx_FileRead (ufxfile fh,void * buf,size_t size,size_t pos) {
    fseek(fh,pos,SEEK_SET);
    fread(buf,size,1,fh);
}
/*!
 * @brief 关闭文件
 * @param fh 文件句柄
 */
void ufx_FileClose (ufxfile fh) {
    fclose(fh);
}
#else
/*
 * fx-9860 API，使用fxlib实现
 */

#endif