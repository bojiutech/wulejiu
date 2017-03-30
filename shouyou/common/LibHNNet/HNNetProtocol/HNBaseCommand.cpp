#include "HNBaseCommand.h"
#include "HNSocket/HNSocket.h"

// ���ϵ�ַ
static const std::string PLATFORM_SERVER_ADDRESS("118.178.190.206");// ��Ϸ��������ַ		118.178.190.206		192.168.1.32	app.bojiutech.cn	�� 192.168.1.141
//static const std::string PLATFORM_SERVER_ADDRESS("192.168.31.200");
//static const std::string PLATFORM_SERVER_ADDRESS("36.110.72.62");
static const std::string API_SERVER_URL("app.bojiutech.cn");    // Web�ӿڵ�ַ


// app����ר�õ�ַ��iOS��ҪSSL֤�飩
static const std::string WEB_SERVER_URL("app.bojiutech.cn");

LLONG getSecrectKey()
{
	return 20161215;
}

std::string getPlatformServerAddress()
{
	std::string address(PLATFORM_SERVER_ADDRESS);
	if(HN::HNSocket::isValidIP(address))
	{
		return address;
	}
	else
	{
		std::vector<std::string> ips = HN::HNSocket::getIpAddress(address.c_str());
		return ips.empty() ? "" : ips.at(0);
	}
}

INT getPlatformServerPort()
{
	return 3015;
}

std::string getWebServerUrl()
{
	return WEB_SERVER_URL;
}

std::string getAPIServerUrl()
{
	return API_SERVER_URL;
}

std::string getXXTEA_KEY()
{
	// ��ֹ���뾲̬�ڴ�����
	char key[] = { 'G', '9', 'w', '0', 'B', 'A', 'Q', 'E', 'F', 'A', 'A', 'S', 'C', 'A', 'l', '8', 'w', 'g', 'g' };
	return std::string(key);
}