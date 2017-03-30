package com.hn.pay.base;

import org.json.JSONException;
import org.json.JSONObject;


public class ProductInfo {
	// 购买数量
	public long				number = 0;
	// 商品价格
	public double			price = 0;
	// 商品ID
	public String           identifier = null;
	// 支付类型 sdk
	public int				payType = -1;
	
	public String           xmlFile = null;
	
	// 订单号
    public String           orderID = null;
	
	public ProductInfo()
    {    
    }
	
    public ProductInfo(long number, double price, String identifier, int payType, String orderID)
    {
    	// 购买数量
    	this.number = number;
    	// 商品价格
    	this.price = price;
    	// 商品ID
    	this.identifier = identifier;       
    	// 支付类型 sdk
    	this.payType = payType;
    	// 订单号
    	this.orderID = orderID;
    }

    public String serialize()
    {
    	return "";
    }
    
    public void deserialize(String data)
    {
    	try {
			JSONObject json = new JSONObject(data);
			this.number = json.getInt("number");
			this.price = json.getDouble("price");
			this.identifier = json.getString("identifier");
			this.payType = json.getInt("payType");
			this.xmlFile = json.getString("xmlFile");
			this.orderID = json.getString("orderID");
		} catch (JSONException e) {
			e.printStackTrace();
		}
    }
}
