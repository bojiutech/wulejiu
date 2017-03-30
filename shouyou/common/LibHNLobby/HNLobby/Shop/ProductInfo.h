#ifndef __ProductInfo_H__
#define __ProductInfo_H__

#include "HNNetExport.h"
#include <string>

namespace HN {

	//{
	//	"identifier": "11111111111111111111",
	//	"number": 10000,
	//	"price": 2
	//}

#define PRODUCT_PAY_TYPE_NONE		-1	//������
#define PRODUCT_PAY_TYPE_WEIXIN		0	//΢��֧��
#define PRODUCT_PAY_TYPE_ZHIFUBAO	1	//֧����֧��
#define PRODUCT_PAY_TYPE_PPQIANBAO	2	//PPǮ��֧��
#define PRODUCT_PAY_TYPE_ZHIFU   	3	//�Ǹ�
#define PRODUCT_PAY_TYPE_IAP   		4	//ƻ���ڹ�

    // ��Ʒ�ṹ
    struct PRODUCT_INFO
    {
    public:
		PRODUCT_INFO()
			: number(0)
			, price(0.0)
			, payType(PRODUCT_PAY_TYPE_NONE)
			, orderID("")
			, SerialNumber(-1)
			, stype(1)
		{

		}

        PRODUCT_INFO(LLONG number, DOUBLE price, const std::string& identifier)
			: number(number)
            , price(price)
            , identifier(identifier)
			, payType(PRODUCT_PAY_TYPE_NONE)
			, SerialNumber(-1)
			, stype(1)
        {
            
        }

		// ���л�
		std::string serialize();

		// �����л�
		void deserialize(std::string data);

    public:
        // ��������
        LLONG					number;
        // ��Ʒ�۸�
        DOUBLE					price;
        // ��ƷID
        std::string             identifier;
		// ֧����ʽ(sdk���)
		INT						payType;
		// xmlFile(sdkʹ��)
		std::string				xmlFile;
		// ������
		std::string             orderID;

		// ��Ʒ���
		LLONG                SerialNumber;
		//1��� 2��ʯ
		INT                       stype;
    };
}

#endif