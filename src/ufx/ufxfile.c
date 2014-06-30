/*
    ufxfile.c : ufxlib�е��ļ�����

    Copyright (C) 2001-2012  Anderain Ryu (Hikari no Uihiaru)

    Anderain Ryu - anderain.develop@gmail.com

*/
#include "ufxlib.h"
#include "stdio.h"
#ifndef PLATFORM_FX9860
/*
 * PC API��ʹ��POSIX�ӿ�ʵ��
 */
/*!
 * @brief ��ֻ���ļ�
 * @param fileName �ļ���
 * @return ufxfile �ļ����
 */
ufxfile ufx_OpenReadOnlyFile (const char * fileName) {
    FILE * fp = fopen(fileName,"rb");
    return fp;
}
/*!
 * @brief ����ļ��Ƿ��ʧ��
 * @param fh �ļ����
 */
BOOL ufx_OpenFail (ufxfile fh) {
    return fh == NULL;
}
/*!
 * @brief ��ȡ�ļ�
 * @param fh �ļ����
 * @param buf ��ȡ����
 * @param pos ��ȡλ��
 * @param size ��ȡ��С
 */
void ufx_FileRead (ufxfile fh,void * buf,size_t size,size_t pos) {
    fseek(fh,pos,SEEK_SET);
    fread(buf,size,1,fh);
}
/*!
 * @brief �ر��ļ�
 * @param fh �ļ����
 */
void ufx_FileClose (ufxfile fh) {
    fclose(fh);
}
#else
/*
 * fx-9860 API��ʹ��fxlibʵ��
 */

#endif