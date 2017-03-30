#pragma once

#include "StdAfx.h"

#ifndef AFC_MD5_H
#define AFC_MD5_H

//MD5 ������
class EXT_CLASS MD5_CTX 
{
	//��������
private:
	unsigned long int				state[4];
	unsigned long					int count[2];
	unsigned char					buffer[64];  
	unsigned char					PADDING[64];

	//��������
public:
	//���캯��
	MD5_CTX();
	//��������
	virtual ~MD5_CTX();
	void MD5Update ( unsigned char *input, unsigned int inputLen);
	void MD5Final (unsigned char digest[16]);

	//˽�к���
private:
	void MD5Init();
	void MD5Transform (unsigned long int state[4], unsigned char block[64]);
	void MD5_memcpy (unsigned char* output, unsigned char* input,unsigned int len);
	void Encode (unsigned char *output, unsigned long int *input,unsigned int len);
	void Decode (unsigned long int *output, unsigned char *input, unsigned int len);
	void MD5_memset (unsigned char* output,int value,unsigned int len);
};

#endif