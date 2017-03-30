#ifndef __Tools_h__
#define __Tools_h__

#include <string>
#include <stack>

namespace HN
{
	// Get individual number
#define FIRST_IPADDRESS(x)  (((x) >> 24) & 0xff)
#define SECOND_IPADDRESS(x) (((x) >> 16) & 0xff)
#define THIRD_IPADDRESS(x)  (((x) >> 8) & 0xff)
#define FOURTH_IPADDRESS(x) ((x) & 0xff)

	enum class BUBBLE_ITEM_TYPE
	{
		unknow,	//未知
		string,//字符串
		expression//表情
	};

	typedef struct _BUBBLE_ITEM
	{
		BUBBLE_ITEM_TYPE t;
		std::string name;

		_BUBBLE_ITEM() : t(BUBBLE_ITEM_TYPE::unknow) {}
	} BUBBLE_ITEM;

	class Tools
	{		
	public:

		// 验证是否是邮箱地址
		static bool verifyEmailAddress(const std::string& email);

		// 验证是否是手机号
		static bool verifyPhone(const std::string& phone);

		// 验证是否是中文
		static bool verifyChinese(const std::string& word);

		// 验证是否只有数字
		static bool verifyNumber(const std::string& word);

		// 验证是否只有数字和英文
		static bool verifyNumberAndEnglish(const std::string& word);

		// url编码
		static std::string base64urlencode(const std::string &str);
		
		// ip地址转成字符串
		static std::string parseIPAdddress(unsigned int address);

		// 解析聊天内容
		static std::stack<BUBBLE_ITEM> parseChatMsg(const std::string &msg);
		
		// 过滤emoji表情
		static std::wstring filterEmoji(const std::wstring& source);
		static bool isEmojiCharacter(wchar_t codePoint);
		static bool containsEmojiCharacter(const std::wstring& source);
		
	};
}


#endif // __Tools_h__