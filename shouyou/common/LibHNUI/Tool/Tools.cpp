#include "Tools.h"
#include <regex>

namespace HN
{
	std::stack<BUBBLE_ITEM> Tools::parseChatMsg(const std::string &msg)
	{
		int length = msg.size();
		std::stack<char> tmp;
		std::stack<_BUBBLE_ITEM> stackMsg;
		while (1 < length--)
		{
			char c0 = msg[length];
			char c1 = msg[length - 1];
			if (c0 == ':' && c1 == '/')
			{
				length -= 1;

				//解析表情
				_BUBBLE_ITEM exp;
				if (tmp.size() > 0)
				{
					exp.t = BUBBLE_ITEM_TYPE::expression;
					for (size_t i = 0; i < 2; i++)
					{
						exp.name.push_back(tmp.top());
						tmp.pop();
					}
				}

				//解析字符串
				if (tmp.size() > 0)
				{
					_BUBBLE_ITEM str;
					str.t = BUBBLE_ITEM_TYPE::string;
					while (!tmp.empty())
					{
						str.name.push_back(tmp.top());
						tmp.pop();
					}

					if (!str.name.empty()) stackMsg.push(str);
				}
				if (!exp.name.empty()) stackMsg.push(exp);
			}
			else
			{
				tmp.push(c0);
			}
		}

		//处理第0个字符
		if (length == 0)
		{
			tmp.push(msg[length]);
		}

		//解析字符串
		if (tmp.size() > 0)
		{
			_BUBBLE_ITEM str;
			str.t = BUBBLE_ITEM_TYPE::string;
			while (!tmp.empty())
			{
				str.name.push_back(tmp.top());
				tmp.pop();
			}
			stackMsg.push(str);
		}

		return stackMsg;
	}

	bool Tools::verifyEmailAddress(const std::string& email)
	{
		std::regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
		return std::regex_match(email, pattern);
	}

	bool Tools::verifyPhone(const std::string& phone)
	{
		return true;
	}

	bool Tools::verifyChinese(const std::string& word)
	{
		std::regex pattern("^[\u4e00-\u9fa5]+$");
		return std::regex_match(word, pattern);
	}

	bool Tools::verifyNumber(const std::string& word)
	{
		std::regex pattern("^[0-9]*$");
		return std::regex_match(word, pattern);
	}

	bool Tools::verifyNumberAndEnglish(const std::string& word)
	{
		std::regex pattern("^[A-Za-z0-9]+$");
		return std::regex_match(word, pattern);
	}

	std::string Tools::base64urlencode(const std::string &str)
	{
		std::string encode = str;
		std::string::size_type pos(0);
		while(( pos = encode.find("+") ) != std::string::npos)
		{
			encode.replace(pos,1,"%2B");
		}
		pos = 0;
		while(( pos = encode.find("/") ) != std::string::npos)
		{
			encode.replace(pos,1,"%2F");
		}
		return encode;
	}

	std::string Tools::parseIPAdddress(unsigned int address)
	{
		char ipAddress[32];

		
		sprintf(ipAddress, "%d.%d.%d.%d", FOURTH_IPADDRESS(address), THIRD_IPADDRESS(address),
			SECOND_IPADDRESS(address), FIRST_IPADDRESS(address));

		return std::string(ipAddress);
	}

	bool Tools::isEmojiCharacter(wchar_t codePoint) {
		return (codePoint == 0x0) ||
			(codePoint == 0x9) ||
			(codePoint == 0xA) ||
			(codePoint == 0xD) ||
			//((codePoint >= 0x20) && (codePoint <= 0xD7FF)) || //这个区域包含了中文，注释了就好了
			((codePoint >= 0xE000) && (codePoint <= 0xFFFD)) ||
			((codePoint >= 0x10000) && (codePoint <= 0x10FFFF));
	}

	bool Tools::containsEmojiCharacter(const std::wstring& source)
	{
		int len = source.length();

		for (int i = 0; i < len; i++) {
			wchar_t codePoint = source[i];

			if (isEmojiCharacter(codePoint)) {
				return true;
			}
		}

		return false;
	}

	/**
	* 过滤emoji 或者 其他非文字类型的字符
	* @param source
	* @return
	*/
	std::wstring Tools::filterEmoji(const std::wstring& source) {

		if (!containsEmojiCharacter(source))
		{
			return source;
		}

		//到这里铁定包含emoji
		std::wstring buf;

		int len = source.length();

		for (int i = 0; i < len; i++) {
			wchar_t codePoint = source[i];

			if (!isEmojiCharacter(codePoint)) {
				buf.push_back(codePoint);
			}
		}

		return buf;
	}
}