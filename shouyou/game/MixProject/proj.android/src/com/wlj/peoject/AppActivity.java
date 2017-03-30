/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/

package com.wlj.peoject;

import java.util.Date;
import java.util.HashMap;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHelper;

import com.umeng.social.CCUMSocialController;

import cn.paypalm.pppayment.PPInterface;
import cn.paypalm.pppayment.global.ResponseDataToMerchant;

import com.hn.market.core.HNPhotoModule;
import com.hn.market.core.HNVoiceModule;
import com.hn.market.core.HNLocationModule;
import com.hn.market.export.ChannelExport;
import com.hn.market.export.Constant;
import com.hn.market.export.GameChannel;
import com.hn.pay.base.PayResultCallBack;
import com.hn.pay.base.ProductInfo;
import com.hn.pay.sdk.AlipayManager;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.WindowManager;
import android.widget.Toast;


public class AppActivity extends Cocos2dxActivity {
	static {
		System.loadLibrary("c++_shared");
		}
	
	// 支付状�??
	private int status = 0;
	
	// 商品信息
	private ProductInfo product = new ProductInfo();
	static String strIdentifier;
	
	private Handler uiMessageHandler = new Handler(){

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			switch(msg.what){
			case Constant.COMMOAND_PAY:
				payRequest(msg);
				break;
			case Constant.COMMOAND_PAY_RESULT:
				payResponse(msg);
				break;
			case Constant.COMMAND_RESPONSECHANNEL:
				channelResonpse(msg);
				break;
			}
		}
	};
		
	// 支付请求
	public void payRequest(Message msg){
		String data = (String)msg.obj;
		product.deserialize(data);
		if(Constant.SDK_TYPE_WEIXIN == product.payType){
			int money = (int )(product.price*100);
			strIdentifier = product.identifier;
			PayActivity startPayActivity = new PayActivity();
			startPayActivity.onstart(AppActivity.this,String.format("%d",money),product.orderID);
		}
		else if(Constant.SDK_TYPE_ZHIFUBAO == product.payType){
			AlipayManager alipay = new AlipayManager(AppActivity.this);
			alipay.pay(String.format("%d筹码", product.number), 
					String.format("%.2f元购%d 筹码", product.price, product.number), product.orderID, 
					String.format("%.2f", product.price),
					new PayResultCallBack() {

						@Override
						public void onPayResult(PAY_SDK sdk, int status) {

							AppActivity.this.status = status;

							switch (sdk) {
							case ALIPAY:

								break;
							case WECHAT:

								break;
							case UNIONPAY:

								break;
							default:
								break;
							}

							if (1 == status) {
								Toast.makeText(AppActivity.this, "支付成功",
										Toast.LENGTH_SHORT).show();
							} else {
								Toast.makeText(AppActivity.this, "支付失败",
										Toast.LENGTH_SHORT).show();
							}
							updatePayResult();
						}

					});
		}
		else if(Constant.SDK_TYPE_PPQIANBAO == product.payType){
			String data1 = (String)msg.obj;
			product.deserialize(data1);
			Date d = new Date();
			long longtime = d.getTime();
			String order = "" + longtime;
			String userId = order;
			String productDesc = "金币";
			int goods = (int)product.price * 100;
			String goodsPrice = "" + goods;
			PPInterface.startPPPayment(AppActivity.this, order, "", "2015080615",
					userId, goodsPrice, "100001",
					"", "http://www.test.com", productDesc, new HashMap<String, String>(),
					"", (ResponseDataToMerchant)AppActivity.this);
			
			//String pointID = (String)msg.obj;
			//GameChannel.getInstance().notifyPay(pointID);
		}
		else if(Constant.SDK_TYPE_ZHIFU == product.payType){
			String data2 = (String)msg.obj;
			product.deserialize(data2);
			String xml = product.xmlFile;
			startPay(xml);
		}
	}
	
	// 支付返回
	public void payResponse(Message msg){
		final Intent intent = (Intent)msg.obj;
		Cocos2dxHelper.runOnGLThread(new Runnable() {

			@Override
			public void run() {
				GameChannel.getInstance().notifyPayCB(intent);
			}

		});
	}
	
	// 
	public void channelResonpse(Message msg){
		final Object obj = msg.obj;
		Cocos2dxHelper.runOnGLThread(new Runnable() {
				@Override
				public void run() {
					GameChannel.getInstance().notifyResponseChannel(obj);
				}

		});
	}

	// 支付回调更新
	public void updatePayResult() {
		Intent intent = new Intent();
		intent.putExtra("status", status);
		intent.putExtra("identifier", product.identifier);
		
		Message msg = new Message();
		msg.what = Constant.COMMOAND_PAY_RESULT;
		msg.obj = intent;
		uiMessageHandler.sendMessage(msg);	
	}
	
	// �?始支�?
	public void startPay(String xml){
		Intent intent = new Intent(this, MerchantPayResultActivity.class);
		intent.putExtra("xml", xml);
		//intent.putExtra("ActivityName", "com.JulyNet.MixProject.MerchantPayResultActivity");
		startActivity(intent);
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		// 安装完成后直接打�?黑屏问题
		if((getIntent().getFlags() & Intent.FLAG_ACTIVITY_BROUGHT_TO_FRONT) != 0){
			finish();
			return;
		}
		
		CCUMSocialController.initSocialSDK(this, "com.umeng.social.share");
		
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
				WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

		GameChannel.getInstance().start(this, uiMessageHandler);

		/*
		final String  fileProviderAuthority = getResources().getString(
                R.string.photo_file_provider_authority);
		HNPhotoModule photo = HNPhotoModule.getInstance();
		photo.start(this);
		photo.init(fileProviderAuthority);
		ChannelExport.getInstance().registerModule(photo.GetModuleName(), photo);
		*/
		
		//注册语音module
		HNVoiceModule voice = HNVoiceModule.getInstance();
		voice.start(this);
		ChannelExport.getInstance().registerModule(voice.GetModuleName(), voice);
		
		//注册定位module
		HNLocationModule location = HNLocationModule.getInstance();
		location.start(this);
		ChannelExport.getInstance().registerModule(location.GetModuleName(), location);
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		
		GameChannel.getInstance().onResume(this);
		
		if(MerchantPayResultActivity.isFromPay){
			MerchantPayResultActivity.isFromPay = false;
			
			Intent intent = new Intent();
			intent.putExtra("status", 1);
			intent.putExtra("identifier", product.identifier);
			
			//Log.i(TAG, product.identifier);
			
			Message msg = new Message();
			msg.what = Constant.COMMOAND_PAY_RESULT;
			msg.obj  = intent;
			uiMessageHandler.sendMessage(msg);
		}
	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		GameChannel.getInstance().onPause(this);
		super.onPause();
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		GameChannel.getInstance().onDestroy();
		super.onDestroy();
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		//super.onActivityResult(requestCode, resultCode, data);
		CCUMSocialController.onActivityResult(requestCode, resultCode, data);
		GameChannel.getInstance().onActivityResult(requestCode, resultCode, data);

		HNPhotoModule.getInstance().onActivityResult(requestCode, resultCode, data);	
		
		// 取支付数�?		
		if(data != null){
			boolean isFromPay = data.getBooleanExtra("isFromPay", false);
			if(isFromPay){
				Intent intent = new Intent();
				intent.putExtra("status", status);
				intent.putExtra("identifier", product.identifier);
				
				//Log.i(TAG, product.identifier);
				
				Message msg = new Message();
				msg.what = Constant.COMMOAND_PAY_RESULT;
				msg.obj  = intent;
				uiMessageHandler.sendMessage(msg);
			}
		}
	}
	
	// 微信支付回调更新
	public void NoticePayResult(int wstatus) {
		Intent intent = new Intent();
		intent.putExtra("status", wstatus);
		intent.putExtra("identifier", strIdentifier);
		
		Message msg = new Message();
		msg.what = Constant.COMMOAND_PAY_RESULT;
		msg.obj = intent;
		uiMessageHandler.sendMessage(msg);	
	}
}
