#ifndef ShopManager_h__
#define ShopManager_h__

#include "HNLobby/Shop/ProductInfo.h"
#include "HNMarketExport.h"
#include "HNNetExport.h"
#include <vector>
#include <string>

namespace HN {

	// ֧������
	class ProductManger: public HNHttpDelegate
	{
	public:
		// ��ȡ����
		static ProductManger* getInstance();

		// ���ٵ���
		static void destroyInstance();

	public:
		ProductManger();
		~ProductManger();

	public:
		void addProducts(const std::string& nameId);

		const PRODUCT_INFO* getProducts(INT index);

		const PRODUCT_INFO* getProducts(std::string& productIdentifier);

		INT getProductTypeNum(INT type);//��ȡ��Ʒ���� 1��� 2 ��ʯ

		UINT getSize() const;

		bool startPay(PRODUCT_INFO* product, CALLBACK_PRAGMA* callback);

		//{

		//	"status": 1
		//}
		bool parsePayResult(const std::string& result);
		bool parsePayResult(const std::string& result, std::string& ext);

		virtual void onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData) override;

	private:
		std::vector<PRODUCT_INFO*> _products;
	};
}

#endif // ShopManager_h__