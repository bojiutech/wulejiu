/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/

package com.umeng.social;

import android.app.Application;

import com.umeng.socialize.PlatformConfig;

/**
 * Created by wangfei on 15/11/9.
 */
public class CCApp extends Application{
    {
        // 微信
        PlatformConfig.setWeixin("wxc3e81c981f91be0d", "fece50d0c89c7560e7fd57ee0e2ec50f");
        
        // 豆瓣平台目前只能在服务器端配置
        // PlatformConfig.setDouban( );
       
        // 新浪微博
        PlatformConfig.setSinaWeibo("3921700954","04b48b094faeb16683c32669824ebdad");
       
        // 易信
        PlatformConfig.setYixin("yxc0614e80c9304c11b0391514d09f13bf");
        PlatformConfig.setLaiwang("laiwangd497e70d4", "d497e70d4c3e4efeab1381476bac4c5e");
        PlatformConfig.setQQZone("1105655910", "RaJIuub9BszetjB1");
        PlatformConfig.setTwitter("3aIN7fuF685MuZ7jtXkQxalyi", "MK6FEYG63eWcpDFgRYw4w9puJhzDl0tyuqWjZ3M7XJuuG7mMbO");
    }
}
