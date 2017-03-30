// libXXTea.cpp : 定义 DLL 应用程序的导出函数。
//

#include "xxtea.h"

#ifdef LIBXXTEA_EXPORTS
#define LIBXXTEA_API _declspec(dllexport)
#else
#define LIBXXTEA_API _declspec(dllimport)
#endif // LIBXXTEA_EXPORTS

extern "C"
{
	LIBXXTEA_API unsigned char * encrypt(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length);
	LIBXXTEA_API unsigned char * decrypt(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length);
}

class LIBXXTEA_API HNEncrypt
{
public:
	HNEncrypt();
	~HNEncrypt();

public:
	unsigned char * encrypt(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length);
	unsigned char * decrypt(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length);
};

