/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef _HN_ConverCode_h__
#define _HN_ConverCode_h__

#include "cocos2d.h"
#include <string>

USING_NS_CC;

namespace HN 
{
	#define UTF8(x) unicode_to_utf8( L##x ).c_str()
	
	inline int _unicode_to_utf8(const wchar_t *in, std::string& out, int *poutsize)
	{
		int outsize = 0;
		int charscount = 0;
		char *result = NULL;
		char *tmp = NULL;

		charscount = wcslen(in);
		result = (char *)new char[charscount * 3 + 1];
		memset(result, 0, charscount * 3 + 1);
		tmp = result;

		for (int i = 0; i < charscount; i++)
		{
			wchar_t unicode = in[i];
			unsigned int i_unicode = (unsigned int)unicode;
			if (/*i_unicode >= 0x0000 && */i_unicode <= 0x007f)
			{
				*tmp = (char)unicode;
				tmp += 1;
				outsize += 1;
			}
			else if (i_unicode >= 0x0080 && i_unicode <= 0x07ff)
			{
				*tmp = 0xc0 | (unicode >> 6);
				tmp += 1;
				*tmp = 0x80 | (unicode & (0xff >> 2));
				tmp += 1;
				outsize += 2;
			}
			else if (i_unicode >= 0x0800 && i_unicode <= 0xffff)
			{
				*tmp = 0xe0 | (unicode >> 12);
				tmp += 1;
				*tmp = 0x80 | (unicode >> 6 & 0x003f);
				tmp += 1;
				*tmp = 0x80 | (unicode & (0xff >> 2));
				tmp += 1;
				outsize += 3;
			}
		}

		*tmp = '\0';
		out = result;
		*poutsize = outsize;
		delete[] result;
		return 1;
	}

	inline int _utf8_to_unicode(const char *in, wchar_t **out, int *outsize)
	{
		unsigned char *p = (unsigned char*)in;
		wchar_t *result = NULL;
		int resultsize = 0;
		unsigned char *tmp = NULL;

		result = (wchar_t *)new wchar_t[strlen(in) + 1];
		*out = result;
		memset(result, 0, strlen(in) * sizeof(wchar_t) + sizeof(wchar_t));
		tmp = (unsigned char *)result;

		while (*p)
		{
			unsigned int i_p = (unsigned int)*p;
			if (/*i_p >= 0x00 && */i_p <= 0x7f)
			{
				*tmp = *p;
				tmp++;
				*tmp = '\0';
				tmp++;
				resultsize += 2;
				if (sizeof(wchar_t) == 4)
				{
					*tmp = '\0';
					tmp++;
					*tmp = '\0';
					tmp++;
					resultsize += 2;
				}
			}
			else if ((i_p & (0xff << 5)) == 0xc0)
			{
				unsigned char t1 = 0;
				unsigned char t2 = 0;

				t1 = *p & (0xff >> 3);
				p++;
				if (((*p) & 0x80) != 0x80)
					return 0;
				t2 = *p & (0xff >> 2);

				*tmp = t2 | ((t1 & (0xff >> 6)) << 6);//t1 >> 2;
				tmp++;

				*tmp = t1 >> 2;//t2 | ((t1 & (0xff >> 6)) << 6);
				tmp++;

				resultsize += 2;
				if (sizeof(wchar_t) == 4)
				{
					*tmp = '\0';
					tmp++;
					*tmp = '\0';
					tmp++;
					resultsize += 2;
				}
			}
			else if ((*p & (0xff << 4)) == 0xe0)
			{
				unsigned char t1 = 0;
				unsigned char t2 = 0;
				unsigned char t3 = 0;

				t1 = *p & (0xff >> 3);
				p++;
				if (((*p) & 0x80) != 0x80)
					return 0;
				t2 = *p & (0xff >> 2);
				p++;
				if (((*p) & 0x80) != 0x80)
				{
					if ((*p) == 13)
					{
						p++;
						if ((*p) == 10)
						{
							p++;
							if ((*p) == 32)
								p++;
						}
					}
					else
						return 0;
				}
				t3 = *p & (0xff >> 2);

				//Little Endian
				*tmp = ((t2 & (0xff >> 6)) << 6) | t3;//(t1 << 4) | (t2 >> 2);
				tmp++;

				*tmp = (t1 << 4) | (t2 >> 2);//((t2 & (0xff >> 6)) << 6) | t3;
				tmp++;
				resultsize += 2;
				if (sizeof(wchar_t) == 4)
				{
					*tmp = '\0';
					tmp++;
					*tmp = '\0';
					tmp++;
					resultsize += 2;
				}
			}

			p++;
		}

		*tmp = '\0';
		tmp++;
		*tmp = '\0';
		tmp++;
		resultsize += 2;
		if (sizeof(wchar_t) == 4)
		{
			*tmp = '\0';
			tmp++;
			*tmp = '\0';
			tmp++;
			resultsize += 2;
		}

		*outsize = resultsize;
		return 1;
	}
	std::wstring inline utf8_to_unicode(const char *in)
	{
		wchar_t *str;
		int size;
		if (!_utf8_to_unicode(in, &str, &size))
		{
			delete[] str;
			return L"";
		}
		std::wstring s = str;
		delete[] str;
		return s;
	}

	std::string inline unicode_to_utf8(const wchar_t *in)
	{
		std::string s;
		int outsize;
		_unicode_to_utf8(in, s, &outsize);
		return s;
	}

	std::string inline utf8_to_url_string(const char *in)
	{
		std::string str = in;
		std::string str2;
		char buf[64];
		for (std::string::size_type i = 0; i < str.size(); i++)
		{
			if (str[i] < 0)
			{
				sprintf(buf, "%x", (int)str[i]);
				str2 += std::string("%") + buf[6] + buf[7];
			}
			else str2 += str[i];
		}
		return str2;
	}

	class HNConverCode
	{
	public:
		static std::string GBK_2_Utf8(const std::string& gbk);

		static std::string Utf8_2_GBK(const std::string& utf8);
		
		// URL编码
		static std::string HNURLEncode(const std::string& url);

		// URL解码
		static std::string HNURLDeCode(const std::string& decodedUrl);
	};
}

#define Utf8ToGBK(object) HNConverCode::Utf8_2_GBK(object).c_str()

#define GBKToUtf8(object) HNConverCode::GBK_2_Utf8(object).c_str()

#define Utf8ToGB(object) HNConverCode::Utf8_2_GBK(object).c_str()

// URL编码
#define URLEncode(object) HNConverCode::HNURLEncode(object).c_str()

// URL解码
#define URLDecode(object) HNConverCode::HNURLDeCode(object).c_str()


#endif // _HN_ConverCode_h__
