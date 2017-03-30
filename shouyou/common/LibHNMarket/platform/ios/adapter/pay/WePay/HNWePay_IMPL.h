//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved

#import <Foundation/Foundation.h>
#import "../HNPayDelegate.h"
#import "SDKExport/WXApiObject.h"
#import "SDKExport/WXApi.h"
//生成预支付订单地址
#define NOTIFY_URL @"http://yc.kl78.com/Manage/Pay/WePay/WxPay_Mobile.aspx"

@interface NSString (MD5)
//创建md5加密的签名
-(NSString *) createMd5Sign : (NSMutableDictionary *) dict;
@end

@interface HNWePay_IMPL : NSObject<WXApiDelegate>
- (id)initWithAppID:(NSString *)appID
              mchID:(NSString *)mchID
              spKey:(NSString *)spKey
              Delegate:(HNPayDelegate *)delegate;

- (void)pay:(NSString  *)orderID Price:(NSString *)price Description:(NSString  *)description;
- (bool)handleURL:(NSURL *)url;


//商户关键信息
@property (nonatomic, strong) NSString *appId, *mchId, *spKey;
//预支付网关地址
@property (nonatomic, strong) NSString* payUrl;

@property (nonatomic, strong) NSString* prepay;
//返回的错误信息
@property (nonatomic, strong) NSMutableString *debugInfo;
@property (nonatomic, assign) NSInteger lastErrCode;//错误码

//获取package带参数的签名包
-(NSString *) genPackage:(NSMutableDictionary *)packageParams;
//提交预支付订单
-(NSString *) sendPrePay:(NSMutableDictionary *) preParams;

//支付回调更新
-(void) NoticePayResult:(bool)resCodeStatus;

+ (instancetype)sharedManager;

@end
