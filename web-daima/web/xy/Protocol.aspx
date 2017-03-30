<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Protocol.aspx.cs" Inherits="HN.Web.xy.Protocol" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html lang="zh-cn" class="no-js">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>深圳市红鸟网络,棋牌开发,棋牌游戏开发,棋牌游戏开发商,棋牌游戏程序,棋牌游戏源码,深圳市红鸟网络科技有限公司</title>
    <meta name="discription" content="深圳红鸟网络是国内最专业的棋牌游戏开发商,专业为投资创业者提供棋牌游戏源码、棋牌游戏平台定制开发，出售和定制扑克类、麻将类、休闲娱乐类、地方游戏等游戏，目前已拥有PC客户端棋牌、手机棋牌、网页棋牌等多种棋牌产品可供选择。" />
    <meta name="Keywords" content="棋牌开发,手机棋牌游戏,棋牌游戏开发,手机棋牌游戏开发,棋牌游戏开发商,棋牌游戏程序,棋牌游戏源码,红鸟网络,红鸟网络科技有限公司" />
    <meta name="viewport" content="initial-scale=1, maximum-scale=1, user-scalable=no" />
    <meta name="format-detection" content="telephone=no" />
    <meta name="format-detection" content="email=no" />
    <link href="css/layout.css" type="text/css" rel="stylesheet" />
    <style type="text/css">
        .nav ul li .nav4 { line-height: 35px; color: #000; border-bottom: #818181 3px solid; background: url("images/icon.png") no-repeat center bottom; }
        .cont_menu li .cont_menu_hover { border-top: #c96706 1px solid; border-bottom: #c96706 1px solid; background: #de8407; color: #fff; }
        .cont_ban{ line-height:180%; padding:5px; overflow:hidden;  text-align:left;}
    </style>
</head>
<body>
    <div class="top">
        <h2>
            <img src="images/logo.png" width="300" />
        </h2>
    </div>
    <div class="nav">
        <ul>
            <li class="home"><a href="#" class="nav1" style="font-size:14px;">用户协议</a></li>

        </ul>
    </div>
    <div class="cont_ban">
       <%=BLL.Config.GetContent(BLL.Config.ItemName_Accept).Replace("\r\n","<br/>") %>
        </div>
    
    
    <div style="height: 48px;">
    </div>
    
    
  
</body>
</html>
