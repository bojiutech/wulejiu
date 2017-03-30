//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved



#import "HNLocationAdapter_IMPL.h"
#import "platform/ios/common/JSONKit/JSONKit.h"
#import "platform/ios/HNMarket.h"
#import "platform/external/json/json.h"
#import "platform/ios/oc-marco.h"

#import<CoreLocation/CoreLocation.h>
@interface HNLocationAdapter_IMPL ()<CLLocationManagerDelegate>

@property (nonatomic,strong) CLLocationManager* locationManager;
@property (nonatomic,assign) CLLocationCoordinate2D  coor;
@end

@interface HNLocationAdapter_IMPL()
{
   
}
@end

@implementation HNLocationAdapter_IMPL
- (void)dealloc
{
    [super dealloc];
}

-(id)init
{
    if (self = [super init]) {
        
        // 初始化定位管理
        self.locationManager=[[CLLocationManager alloc]init];
        
        // 设置代理
        self.locationManager.delegate=self;
        
        // 设置定位的精准度
        self.locationManager.desiredAccuracy=kCLLocationAccuracyBest;
        
        // 设置设备移动更新位置信息的最小距离，单位是米
        self.locationManager.distanceFilter=kCLDistanceFilterNone;
        
        // 请求授权
        if ([[[UIDevice currentDevice] systemVersion] floatValue]>=8.0) {
            // 请求总是允许使用定位功能
            [self.locationManager requestAlwaysAuthorization];
            
            // 请求应用使用时才允许使用定位功能
//            [self.locationManager requestWhenInUseAuthorization];
        }
    }
    return self;
}

-  (void)locationAddress : (CALLBACK_PRAGMA*) callback
{
    _callback = *callback;
    
    if ([CLLocationManager locationServicesEnabled] &&
        ([CLLocationManager authorizationStatus] == kCLAuthorizationStatusAuthorizedAlways
         || [CLLocationManager authorizationStatus] == kCLAuthorizationStatusAuthorizedWhenInUse)) {
            
            // 开始定位
            [self.locationManager startUpdatingLocation];
            
        }else if ([CLLocationManager authorizationStatus] == kCLAuthorizationStatusDenied){
            
            UIAlertView *al=[[UIAlertView alloc]initWithTitle:@"提示" message:@"定位失败，请在[设置]中打开定位服务或者检查网络!" delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil];
            [al show];
        }
    else
    {
        NSLog(@"定位失败");
        
        std::string resp = "{\"success\":false,\"}";
        
        HN::Market::sharedMarket()->responseChannel(&_callback, resp);
    }
}

-  (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations
{
    CLLocation *locationXY=[locations lastObject];
    self.coor =locationXY.coordinate;
    NSString   *latitude   =  [NSString stringWithFormat:@"%f",self.coor.latitude];
    NSString   *longitude = [NSString stringWithFormat:@"%f",self.coor.longitude];
    NSLog(@"定位获取坐标:%@,%@",latitude,longitude);
    
    std::string weidu = [latitude UTF8String];
    std::string jingdu = [longitude UTF8String];
    
    std::string resp = "{\"success\":true,\"latitude\":\""+ weidu + "\"," +
    "\"lontitude\":\"" + jingdu + "\"}";

    HN::Market::sharedMarket()->responseChannel(&_callback, resp);
    // 停止定位
    [self.locationManager stopUpdatingLocation];
    
}

-  (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
    NSLog(@"定位失败");
    
    std::string resp = "{\"success\":false,\"}";
    
    HN::Market::sharedMarket()->responseChannel(&_callback, resp);
}

@end
