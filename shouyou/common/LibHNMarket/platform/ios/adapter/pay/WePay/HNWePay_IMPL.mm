//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved

#import "HNWePay_IMPL.h"
#include <UIKit/UIKit.h>
#import "Util/DataSigner.h"
#import  <Foundation/Foundation.h>
#import <CommonCrypto/CommonCrypto.h>
#include "../../../HNMarket.h"
#import "HNWePayModule.h"
#import <tinyxml2.h>

@interface HNWePay_IMPL()
{
    NSString *_appID;
    NSString *_privateKey;
    NSString *_handleUrl;
    NSString *_noncestr;
    HNPayDelegate *_delegate;
}

@end

@implementation HNWePay_IMPL
+(instancetype)sharedManager {
    static dispatch_once_t onceToken;
    static HNWePay_IMPL *instance;
    dispatch_once(&onceToken, ^{
        instance = [[HNWePay_IMPL alloc] init];
    });
    return instance;
}
- (void)dealloc
{
    [super dealloc];
    [_appID release];
    [_privateKey release];
    [_handleUrl release];
    [_noncestr release];
    _delegate = nil;
    _appID = nil;
    _privateKey = nil;
    _handleUrl = nil;
    _noncestr = nil;
}

- (id)initWithAppID:(NSString *)appID mchID:(NSString *)mchID spKey:(NSString *)spKey Delegate:(HNPayDelegate *)delegate{
    self = [super init];
    if (self)
    {
        //初始化私有的参数（主要是商户信息）
        self.payUrl = @"https://api.mch.weixin.qq.com/pay/unifiedorder";
        if (self.debugInfo == nil) {
            self.debugInfo = [NSMutableString string];
        }
        [self.debugInfo setString:@""];
        self.appId = appID;
        self.mchId = mchID;
        self.spKey = spKey;
        _delegate = delegate;
        
    }
    return self;
}

- (void)pay:(NSString *)orderID
      Price:(NSString *)price
Description:(NSString *)description
{
    //订单号
    NSString *orderNo = orderID;
    //设备号(现用订单号代替)
    //NSString *orderDevice = orderID;
    //金额
    int orderPrice = (int)([price floatValue]*100) ;
    
    //描述
    NSString *orderDescription = description;
    //支付类型
    NSString *orderType = @"APP";
    //发起支付的ip
    NSString *orderIP = @"192.168.1.1";
    //随机字符串
    srand((unsigned)time(0));
    _noncestr = [NSString stringWithFormat:@"%d", rand()];
    
    
    //设置预支付订单参数
    NSMutableDictionary *packageParams = [NSMutableDictionary dictionary];
    [packageParams setObject:self.appId forKey:@"appid"];//appid
    [packageParams setObject:orderDescription forKey:@"body"];//描述
    [packageParams setObject:self.mchId forKey:@"mch_id"];//商户id
    [packageParams setObject:_noncestr forKey:@"nonce_str"];//随机串
    [packageParams setObject:NOTIFY_URL forKey:@"notify_url"];//支付结果异步通知地址
    [packageParams setObject:orderNo forKey:@"out_trade_no"];//订单号
    [packageParams setObject:orderIP forKey:@"spbill_create_ip"];//发起支付的ip
    [packageParams setObject:[NSString stringWithFormat:@"%d",orderPrice] forKey:@"total_fee"];//订单金额
    [packageParams setObject:orderType forKey:@"trade_type"];//支付类型
    //[packageParams setObject:orderDevice forKey:@"device_info"];//设备号
    
    //生成签名
    //NSString *presign = [self createMd5Sign:packageParams];
    //添加签名到组装的字符串中
    //[packageParams setObject:presign forKey:@"sign"];//签名
    
    //获取预支付订单
    NSString *prePayid;
    prePayid = [self sendPrePay:packageParams];
    
    if (prePayid == nil)
    {
        [self.debugInfo appendFormat:@"获取prepayid失败！"];
        return ;
    }
    //获取到预支付订单后再组装调起微信支付的参数
    NSString *package, *time_stamp, *nonce_str;
    //设置支付参数
    time_t now;
    time(&now);
    time_stamp = [NSString stringWithFormat:@"%ld", now];
    //nonce_str = [self createMd5Sign:@{@"time_stamp":time_stamp}];//生成随机字符串
    //组装参数
    package = @"Sign=WXPay";
    NSMutableDictionary *signParams = [NSMutableDictionary dictionary];
    [signParams setObject:self.appId forKey:@"appid"];//appid
    [signParams setObject:self.mchId forKey:@"partnerid"];//商户id
    [signParams setObject:_noncestr forKey:@"noncestr"];//随机串
    [signParams setObject:package forKey:@"package"];//扩展字段
    [signParams setObject:time_stamp forKey:@"timestamp"];//时间戳
    [signParams setObject:prePayid forKey:@"prepayid"];//预支付订单
    
    //生成签名
    NSString *sign = [self createMd5Sign:signParams];
    
    //添加签名到组装的字符串中
    [signParams setObject:sign forKey:@"sign"];
    [self.debugInfo appendFormat:@"再次组装字符串成功！sign = %@", sign];
    
   //调起微信支付
    PayReq* req = [[[PayReq alloc] init]autorelease];
    req.partnerId = [signParams objectForKey:@"partnerid"];
    req.prepayId = [signParams objectForKey:@"prepayid"];
    req.nonceStr = [signParams objectForKey:@"noncestr"];
    req.timeStamp = time_stamp.intValue;
    req.package = [signParams objectForKey:@"package"];
    req.sign = [signParams objectForKey:@"sign"];
    
    [WXApi sendReq:req];
    
}

- (NSString *)generateTradeNO
{
    NSDateFormatter *formatter = [[[NSDateFormatter alloc] init] autorelease];
    [formatter setDateFormat:@"MMddHHmmss"];
    //时间戳
    NSString *sourceStr = [formatter stringFromDate:[NSDate date]];
    //15位订单号
    NSString *result = [NSString stringWithFormat:@"%@%d",sourceStr,rand() + 10000];
    
    return result;
}

- (bool)handleURL:(NSURL *)url
{
//    if ([url.host isEqualToString:@"safepay"]) {
//        //支付结果url，传入后由SDK解析，统一在支付时的pay方法的callback中回调
//        [[AlipaySDK defaultService] processOrderWithPaymentResult:url standbyCallback:^(NSDictionary *resultDic) {}];
//        return true;
//    }
    return false;
}

//创建md5加密的签名
-(NSString *) createMd5Sign : (NSMutableDictionary *) dict
{
    NSMutableString * contentString = [NSMutableString string];
    NSArray* keys = [dict allKeys];
    //按字母顺序排序
    NSArray *sortedArray = [keys sortedArrayUsingComparator:^NSComparisonResult(id obj1, id obj2){
        return [obj1 compare:obj2 options:NSNumericSearch];
    }];
    
    //拼接字符串
    for(NSString *categoryId in sortedArray)
    {
        if (![[dict objectForKey:categoryId] isEqualToString:@""]
            && ![categoryId isEqualToString: @"sign"]
            && ![categoryId isEqualToString: @"key"]
            )
        {
            [contentString appendFormat:@"%@=%@&", categoryId, [dict objectForKey:categoryId]];
        }
    }
    //添加key
    [contentString appendFormat:@"key=%@", self.spKey];
    NSLog(@"%@",contentString);
    
    
    //md5加密
    const char *value = [contentString UTF8String];
    unsigned char outputBuffer[32];
    CC_MD5(value, (CC_LONG)strlen(value), outputBuffer);
    
    NSMutableString *md5Sign = [[NSMutableString alloc] init];
    for (int i=0; i<16; i++) {
        [md5Sign appendFormat:@"%02x", outputBuffer[i]];
    }

    //小写转大写
    NSString *newMD5Sign = [md5Sign uppercaseString];
    
    //将加密后的签名打印出来
    [self.debugInfo appendFormat:@"MD5签名字符串:%@", newMD5Sign];
    
    
    return newMD5Sign;
}

//获取package带参数的签名包
-(NSString *) genPackage:(NSMutableDictionary *)packageParams
{
    NSString *sign;
    NSMutableString *reqPars = [NSMutableString string];
    //生成签名
    sign = [self createMd5Sign:packageParams];
    //生成xml的package
    NSArray *keys =[packageParams allKeys];
    [reqPars appendString:@"<xml>"];
    for(NSString *categoryId in keys)
    {
        [reqPars appendFormat:@"<%@>%@</%@>", categoryId, [packageParams objectForKey:categoryId], categoryId];
    }
    
    [reqPars appendFormat:@"<sign>%@</sign></xml>", sign];
    
    return [NSString stringWithString:reqPars];
}

//提交预支付订单
-(NSString *) sendPrePay:(NSMutableDictionary *) prePayParams
{
    //预支付订单号
    NSString *prepayid = nil;
    //获取提交支付
    NSString *send = [self genPackage:prePayParams];
    //输出debug info
    [self.debugInfo appendFormat:@"API链接:%@", self.payUrl];
    [self.debugInfo appendFormat:@"发送的xml：%@", send];
    
    /////////发送请求post xml数据
    NSString *urlString = [NSString stringWithFormat:@"%@", self.payUrl];
    //创建url对象
    NSURL *url = [NSURL URLWithString:urlString];
    //创建请求
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url cachePolicy:NSURLRequestReloadIgnoringCacheData timeoutInterval:10];
    //创建参数字符串对象
    //NSString *parmStr = [NSString stringWithFormat:@"%@", prePayParams];
    //将字符串转换为NSData对象
    
    
    NSData *data = [send dataUsingEncoding:NSUTF8StringEncoding];
    [request setHTTPBody:data];
    [request setHTTPMethod:@"POST"];
    NSString *contentType = [NSString stringWithFormat:@"text/xml"];
    [request addValue:contentType forHTTPHeaderField: @"Content-Type"];

    //开始解析
    NSData *retData = [NSURLConnection sendSynchronousRequest:request returningResponse:nil error:nil];

    //xml 解析
    prepayid = [self kissXMLParseData:retData];
 
    return prepayid;
}



-(NSString *)kissXMLParseData:(NSData *)data
{
    NSString *prepayid = nil;
    //nsdata类型转换为nsstring
    NSString *dataStr = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    
    tinyxml2::XMLDocument pDoc;
    
    pDoc.Parse([dataStr UTF8String]);
    //获取跟节点
    tinyxml2::XMLElement *rootEle = pDoc.RootElement();

    //节点
    tinyxml2::XMLElement *element = rootEle->FirstChildElement();
    while (element) {
       //获取属性的名字
        const char *attName = element->Value();
        if (strcmp(attName, "prepay_id") == 0) {
           const char *attData = element->GetText();
            prepayid = [[NSString alloc] initWithUTF8String:attData];
            break;
        }
        element = element->NextSiblingElement();//移动到下一个节点
    }
    return prepayid;
}

#pragma mark - WXApiDelegate

- (void)onResp:(BaseResp *)resp {
    if([resp isKindOfClass:[PayResp class]]){
        //支付返回结果，实际支付结果需要去微信服务器端查询
        NSString *strMsg,*strTitle = [NSString stringWithFormat:@"支付结果"];
        bool status = false;
        switch (resp.errCode) {
            case WXSuccess:
                strMsg = @"支付结果：成功！";
                status = true;
                break;
            case -1:
                strMsg = @"支付结果：失败！";
                status = false;
                break;
            case -2:
                strMsg = @"用户已经退出支付！";
                status = false;
                break;
            default:
                strMsg = [NSString stringWithFormat:@"支付结果：失败！retcode = %d, retstr = %@", resp.errCode,resp.errStr];
                break;
        }
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:strTitle message:strMsg delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alert show];
        [alert release];
        _delegate->HandlePayResult(status, 2);
    }
}

//支付回调更新
//-(void) NoticePayResult:(bool)resCodeStatus
//{
//    _delegate->HandlePayResult(resCodeStatus, 2);
//}


@end
