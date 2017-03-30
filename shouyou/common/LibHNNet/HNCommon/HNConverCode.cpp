﻿/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "HNConverCode.h"
#include "HNSingleAutoPtr.h"
#include "cocos2d.h"
#include <errno.h>
#include <assert.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "win32-specific/icon/include/iconv.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../../../../cocos2d/libiconv/include/iconv.h"
#else
#include "iconv.h"
#endif

namespace HN 
{

	int code_convert(const char *from_charset, const char *to_charset,
					const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
	{
		memset(outbuf, 0, outlen);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		 const char *_inbuf = (char*)inbuf;
#else
		char *_inbuf = const_cast<char*>(inbuf);
#endif
   
		size_t outbytes = outlen;
    
		size_t ret = -1;
		iconv_t ic = NULL;
		ic = iconv_open (to_charset, from_charset);
		if (ic == (iconv_t *) - 1)
		{
			CCLOG ("iconv_open failed: from: %s, to: %s: %s", from_charset, to_charset, strerror(errno));
			return -1;
		}

		while (inlen > 0)
		{
			ret = iconv (ic, &_inbuf, &inlen, &outbuf, &outbytes);
		
			if (ret == -1)
			{
				CCLOG ("iconv failed: from: %s, to: %s: %s", from_charset, to_charset, strerror(errno));
				return -1;
			}
		}

		ret = iconv_close (ic);
		if (ret == -1)
		{
			CCLOG ("iconv_close failed: from: %s, to: %s: %s", from_charset, to_charset, strerror(errno));
			return -1;
		}
		return 0;
	}

	//UTF8->GBK
	std::string HNConverCode::Utf8_2_GBK(const std::string& utf8)
	{
		if (utf8.empty()) return "";

		size_t inlen = utf8.size();
		size_t outlen = inlen * 2 + 2;

		HNPointerArray<char> outbuf(new char[outlen]);
		std::string strRet("");
		if (code_convert("utf-8", "gbk", utf8.c_str(), inlen, outbuf, outlen) == 0)
		{
			strRet = outbuf;
		}
		return strRet;
	}

	//gbk->UTF8
	std::string HNConverCode::GBK_2_Utf8(const std::string& gbk)
	{
		if (gbk.empty()) return "";

		size_t inlen = gbk.size();

		size_t outlen = inlen * 2 + 2;
		HNPointerArray<char> outbuf(new char[outlen]);

		std::string strRet(gbk);
		if (code_convert("gbk", "utf-8", gbk.c_str(), inlen, outbuf, outlen) == 0)
		{
			strRet = outbuf;
		}
		return strRet;
	}
	
	/* Converts a hex character to its integer value */  
	char from_hex(char ch) {  
		return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;  
	}  

	/* Converts an integer value to its hex character*/  
	char to_hex(char code) {  
		static char hex[] = "0123456789abcdef";  
		return hex[code & 15];  
	}  

	/* Returns a url-encoded version of str */  
	/* IMPORTANT: be sure to free() the returned string after use */  
	char *url_encode(char *str) {  
		char *pstr = str, *buf = (char*)malloc(strlen(str) * 3 + 1), *pbuf = buf;  
		while (*pstr) {
			if (((*pstr >= -1 && *pstr <= 255) && isalnum(*pstr)) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~')
				*pbuf++ = *pstr;  
			else if (*pstr == ' ')   
				*pbuf++ = '+';  
			else   
				*pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);  
			pstr++;  
		}  
		*pbuf = '\0';  
		return buf;  
	}  

	/* Returns a url-decoded version of str */  
	/* IMPORTANT: be sure to free() the returned string after use */  
	char *url_decode(char *str) {  
		char *pstr = str, *buf = (char*)malloc(strlen(str) + 1), *pbuf = buf;  
		while (*pstr) {  
			if (*pstr == '%') {  
				if (pstr[1] && pstr[2]) {  
					*pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);  
					pstr += 2;  
				}  
			} else if (*pstr == '+') {   
				*pbuf++ = ' ';  
			} else {  
				*pbuf++ = *pstr;  
			}  
			pstr++;  
		}  
		*pbuf = '\0';  
		return buf;  
	}
	
	std::string HNConverCode::HNURLEncode(const std::string& url)
	{
		return url_encode((char*)url.c_str());
	}


	std::string HNConverCode::HNURLDeCode(const std::string& decodedUrl)
	{
		return url_decode((char*)decodedUrl.c_str());
	}
}