// libXXTea.cpp : 定义 DLL 应用程序的导出函数。
//

#include "libXXTea.h"

unsigned char *encrypt(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length)
{
	return xxtea_encrypt(data, data_len, key, key_len, ret_length);
}

unsigned char *decrypt(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length)
{
	return xxtea_decrypt(data, data_len, key, key_len, ret_length);
}


HNEncrypt::HNEncrypt()
{

}

HNEncrypt::~HNEncrypt()
{

}

unsigned char * HNEncrypt::encrypt(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length)
{
	return ::encrypt(data, data_len, key, key_len, ret_length);
}

unsigned char * HNEncrypt::decrypt(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length)
{
	return ::decrypt(data, data_len, key, key_len, ret_length);
}