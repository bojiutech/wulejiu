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
		unknow,	//δ֪
		string,//�ַ���
		expression//����
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

		// ��֤�Ƿ��������ַ
		static bool verifyEmailAddress(const std::string& email);

		// ��֤�Ƿ����ֻ���
		static bool verifyPhone(const std::string& phone);

		// ��֤�Ƿ�������
		static bool verifyChinese(const std::string& word);

		// ��֤�Ƿ�ֻ������
		static bool verifyNumber(const std::string& word);

		// ��֤�Ƿ�ֻ�����ֺ�Ӣ��
		static bool verifyNumberAndEnglish(const std::string& word);

		// url����
		static std::string base64urlencode(const std::string &str);
		
		// ip��ַת���ַ���
		static std::string parseIPAdddress(unsigned int address);

		// ������������
		static std::stack<BUBBLE_ITEM> parseChatMsg(const std::string &msg);
		
		// ����emoji����
		static std::wstring filterEmoji(const std::wstring& source);
		static bool isEmojiCharacter(wchar_t codePoint);
		static bool containsEmojiCharacter(const std::wstring& source);
		
	};
}


#endif // __Tools_h__