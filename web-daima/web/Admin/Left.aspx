<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Left.aspx.cs" Inherits="Bzw.Admin2.Admin.Left" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title></title>
    <link href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/css/admin.css"
        type="text/css" rel="stylesheet" />
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
    <style type="text/css">
        .menuParent { float: left; text-align: left; display: block; width: 120px; height: 20px; line-height: 20px; overflow: hidden; }
        .menuChild { clear: both; float: left; text-align: left; margin: 0px; padding: 2px 0px; }
    </style>
</head>
<body style="background-image: url(images/menu_bg.jpg); background-repeat: repeat-y;">
    <form id="form1" runat="server">
    <input id="menus" type="hidden" runat="server" />
    <div>
        <table cellspacing="0" cellpadding="0" width="170" style="width: 100%;" border="0">
            <tr>
                <td valign="top" align="middle">
                    <table cellspacing="0" cellpadding="0" width="100%" border="0">
                        <tr>
                            <td height="10">
                            </td>
                        </tr>
                    </table>
                    <table cellspacing="0" cellpadding="0" width="150" border="0">
                        <tr height="22" runat="server" id="tr_xtrz" visible="false">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(1)" href="javascript:void(0);">系统设置</a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child1" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr runat="server" id="menu_a1">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/UserAdmin/Add_AdminUser.aspx"
                                    target="main">管理员管理</a>
                            </td>
                        </tr>
                        <tr runat="server" id="menu_a2">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="menu1" onclick="changeMenu(1)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/UserAdmin/UpdateLoginName.aspx"
                                    target="main">修改默认登录名</a>
                            </td>
                        </tr>
                        <tr runat="server" id="menu_a3">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="menu2" onclick="changeMenu(2)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/UserAnaly/Add_AnalyUser.aspx"
                                    target="main">运营系统用户管理</a>
                            </td>
                        </tr>
                        <%--<tr runat="server" id="menu_a4">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <div style="color: Blue; width: 140; height: 20px; z-index: 1000; display: none;
                                    position: absolute; top: 14%; left: 9%; background-color: #e3effb; border: solid 1px yellow"
                                    id="div_send">
                                </div>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/UserAdmin/ConfigEncryption.aspx" target="main">加密/解密数据库链接</a>
                            </td>
                        </tr>--%>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <div style="color: Blue; width: 140; height: 20px; z-index: 1000; display: none;
                                    position: absolute; top: 14%; left: 9%; background-color: #e3effb; border: solid 1px yellow"
                                    id="div1">
                                </div>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/AdminModifyLog.aspx "
                                    target="main">系统日志</a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td colspan="2">
                            </td>
                        </tr>
                    </table>
                    <table cellspacing="0" cellpadding="0" width="150" border="0">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(2)" href="javascript:void(0);">网站信息管理 </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child2" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr id="menu_01" style="display: none">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="menu8" onclick="changeMenu(8)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/FlashAd/FlashList.aspx"
                                    target="main">首页Flash管理 </a>
                            </td>
                        </tr>
                        <tr id="menu_02" style="display: none">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="menu9" onclick="changeMenu(9)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Books/Book.aspx"
                                    target="main">玩家留言管理</a>
                            </td>
                        </tr>
                        <tr id="menu_03" style="display: none">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="menu10" onclick="changeMenu(10)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/systems.aspx"
                                    target="main">网站参数设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/Accept.aspx"
                                    target="main">服务条款设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/ServiceContent.aspx"
                                    target="main">客服中心内容设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/GameAdSetting.aspx"
                                    target="main">游戏广告位管理 </a>
                            </td>
                        </tr>
                        <tr runat="server" id="menu_18" style="display: none" visible="false">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/AdminMsgList.aspx"
                                    target="main">系统信息发送管理 </a>
                            </td>
                        </tr>
                        <tr id="menu_10" style="display: none">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/News/News.aspx"
                                    target="main">新闻管理 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/news/AppAdList.aspx"
                                    target="main">APP公告</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/serverinfo.aspx"
                                    target="main">服务器信息</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/ClearList.aspx"
                                    target="main">清理表数据 </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td colspan="2">
                            </td>
                        </tr>
                    </table>
                    <table cellspacing="0" cellpadding="0" width="150" border="0" runat="server" id="menu_04"
                        style="display: none">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(3)" href="javascript:void(0);">用户管理中心 </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child3" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr id="menu_14" style="display: none">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/FineryID/FineryID.aspx"
                                    target="main">靓号管理 </a>
                            </td>
                        </tr>
                        <tr height="20">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/CreateUser.aspx"
                                    target="main">新增用户</a>
                            </td>
                        </tr>
                        <tr height="20">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/Users_Seach.aspx"
                                    target="main">搜索站内会员</a>
                            </td>
                        </tr>
                        <tr height="20">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/UserPointList.aspx"
                                    target="main">用户积分管理</a>
                            </td>
                        </tr>
                        <tr height="20">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/User_List.aspx?id=1"
                                    target="main">今日注册用户</a>
                            </td>
                        </tr>
                        <tr height="20">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/UserIp_Seach.aspx"
                                    target="main">注册IP查询</a>
                            </td>
                        </tr>
                        <%--      <tr height="20">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/UserIP_top.aspx" target="main">注册IP(Top100)</a>
                            </td>
                        </tr>--%>
                        <tr height="20">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/UserLoginSearch.aspx"
                                    target="main">游戏登录记录查询</a>
                            </td>
                        </tr>
                        <%--      <tr height="20">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/Pictures.aspx" target="main">用户照片审核</a>
                            </td>
                        </tr>--%>
                        <tr height="20">
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/ClearLoginInfo.aspx"
                                    target="main">解除用户登录限制</a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td colspan="2">
                            </td>
                        </tr>
                    </table>
                    <table cellspacing="0" cellpadding="0" width="150" border="0" runat="server" id="menu_05"
                        style="display: none">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(4)" href="javascript:void(0);">充值管理中心</a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child4" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="menu14" onclick="changeMenu(14)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Pay/Rate.aspx"
                                    target="main">金币兑换比例设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="menu14" onclick="changeMenu(14)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Pay/PhoneExAdd.aspx"
                                    target="main">手游商品兑换设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="menu14" onclick="changeMenu(14)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Pay/PhoneExchange.aspx"
                                    target="main">手游商品兑换列表 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="menu63" onclick="changeMenu(63)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Pay/Pay.aspx?pay=1"
                                    target="main">点卡充值管理 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Pay/PayBank.aspx"
                                    target="main">网上支付充值记录</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Pay/PayToPoint.aspx"
                                    target="main">充值积分记录 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Pay/MobilePayGameType.aspx"
                                    target="main">手游充值类别管理 </a>
                            </td>
                        </tr>
                        <%--   <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Pay/MobilePayDiamond.aspx"
                                    target="main">手游充值钻石管理 </a>
                            </td>
                        </tr> --%>
                        <%--   <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Pay/FreeCardCount.aspx" target="main">赠送免费卡数量设置
                                </a>
                            </td>
                        </tr>--%>
                        <tr height="4">
                            <td colspan="2">
                            </td>
                        </tr>
                    </table>
                    <table cellspacing="0" cellpadding="0" width="150" border="0" runat="server" id="menu_06"
                        style="display: none">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(5)" href="javascript:void(0);">游戏管理中心</a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child5" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/GameTypesAdd.aspx"
                                    target="main">添加游戏类别</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/GameTypes.aspx"
                                    target="main">游戏类别管理</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/GameNamesAdd.aspx"
                                    target="main">添加游戏信息</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="A3" onclick="changeMenu(41)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/AppList.aspx"
                                    target="main">手机游戏管理</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="menu41" onclick="changeMenu(41)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/GameNames.aspx"
                                    target="main">游戏信息管理</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/GameRoomsAdd.aspx"
                                    target="main">游戏房间添加</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/GameRooms.aspx"
                                    target="main">游戏房间管理</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/VipDeskToCount.aspx"
                                    target="main">购买桌位局数设置</a>
                            </td>
                        </tr>
                        <%-- <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/GameBattleRoomsWrite.aspx" target="main">添加混战房间</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/GameBattleRooms.aspx" target="main">混战房间管理</a>
                            </td>
                        </tr>--%>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/GameContestRoomsWrite.aspx"
                                    target="main">添加比赛房间</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/GameContestRooms.aspx"
                                    target="main">比赛房间管理</a>
                            </td>
                        </tr>
                        <%--                        <tr>
                            <td align="middle" width="32">
                                <img alt="" height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Games/ApplyRoomList.aspx"
                                    target="main">租赁房间列表 </a>
                            </td>
                        </tr>--%>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/GameInfo/GameBigTing.aspx"
                                    target="main">游戏大厅信息管理</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/GameInfo/GameMain_Add.aspx"
                                    target="main">添加游戏规则</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/GameInfo/GameMain.aspx"
                                    target="main">游戏规则管理</a>
                            </td>
                        </tr>
                        <%--        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/FilterGameName.aspx" target="main">累积游戏时长设置</a>
                            </td>
                        </tr>--%>
                        <tr height="4">
                            <td colspan="2">
                            </td>
                        </tr>
                    </table>
                    <table cellspacing="0" cellpadding="0" width="150" border="0" runat="server" id="menu_19"
                        style="display: none">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(6)" href="javascript:void(0);">比赛管理中心</a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child6" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/MatchSendType.aspx"
                                    target="main">奖励方案名设置</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/MatchSendLotteries.aspx"
                                    target="main">赠送奖券设置 </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td colspan="2">
                            </td>
                        </tr>
                    </table>
                    <table cellspacing="0" cellpadding="0" width="150" border="0" runat="server" id="menu_17">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(120)" href="javascript:void(0);">代理商帐号管理 </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td colspan="2">
                            </td>
                        </tr>
                    </table>
                    <table id="child120" style="display: none" cellspacing="0" cellpadding="0" width="155"
                        border="0">
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Agency/AgencyView.aspx"
                                    target="main">代理商帐号管理 </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td colspan="2">
                            </td>
                        </tr>
                    </table>
                    <table cellspacing="0" cellpadding="0" width="150" border="0" id="menu_08" style="display: none">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(0)" href="javascript:void(0);">转账管理中心 </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child0" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/Transfers.aspx"
                                    target="main">转账参数设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Trans/TransSeach.aspx"
                                    target="main">转账记录搜索</a>
                            </td>
                        </tr>
                    </table>
                    <table cellspacing="0" cellpadding="0" width="150" border="0" runat="server" id="menu_09"
                        style="display: none">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(1120)" href="javascript:void(0);">记录查询中心</a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child1120" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/UserGameSeach.aspx"
                                    target="main">游戏记录查询 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/UserRoomSeach.aspx"
                                    target="main">房间记录查询 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/ClearGameRecord.aspx"
                                    target="main">清理游戏记录 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/MoneyStatiEveryday.aspx"
                                    target="main">每天金币统计 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/TaxStatiEveryday.aspx"
                                    target="main">游戏门票统计 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/SystemStat.aspx"
                                    target="main">系统信息统计 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/UsersMoneyChangeLogNew.aspx"
                                    target="main">金币变化日志-新 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/UserReceiveMoneyList.aspx"
                                    target="main">领取金币日志</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/UserSendMoneyLog.aspx"
                                    target="main">时长,局数金币日志</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/UserGameMoneyLog.aspx"
                                    target="main">玩家游戏输赢统计</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Users/UserLoterriesLog.aspx"
                                    target="main">用户奖券变化日志</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/BankAccessLog.aspx"
                                    target="main">用户存取记录管理</a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table cellspacing="0" cellpadding="0" width="150" border="0" runat="server" id="menu_15"
                        style="display: none">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(11213)" href="javascript:void(0);">道具管理中心
                                </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child11213" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/JpPrices.aspx"
                                    target="main">道具价格设置</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/DaoJuLog.aspx"
                                    target="main">道具购买记录</a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="menu52" onclick="changeMenu(52)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/PropStatistic.aspx"
                                    target="main">道具每日消耗统计 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="menu53" onclick="changeMenu(53)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/Prices.aspx"
                                    target="main">VIP购买价格设置 </a>
                            </td>
                        </tr>
                        <%-- <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="A1" onclick="changeMenu(53)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/PFPrices.aspx"
                                    target="main">魅力值清零道具设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="A2" onclick="changeMenu(53)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/DaoJuFasciLog.aspx"
                                    target="main">魅力值清零道具记录 </a>
                            </td>
                        </tr>--%>
                        <%--      <tr >
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="A3" onclick="changeMenu(53)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Cloth/ClothesList.aspx"
                                    target="main"> 服装列表  </a>
                            </td>
                        </tr>
                            <tr >
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a id="A4" onclick="changeMenu(53)" class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Cloth/BuyClothLog.aspx"
                                    target="main"> 服装购买记录   </a>
                            </td>
                        </tr>--%>
                    </table>
                    <%--  <table cellspacing="0" cellpadding="0" width="150" border="0" runat="server" id="menu_16"
                        style="display: none">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(1121)" href="javascript:void(0);">魅力兑换管理中心
                                </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child1121" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/FasciExchange/FasciPropAdd.aspx" target="main">添加魅力兑换金币道具
                                </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/FasciExchange/FasciExchange.aspx" target="main">魅力兑换管理
                                </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/FasciExchange/FasciExchangeLog.aspx" target="main">
                                    魅力兑换记录 </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td colspan="2">
                            </td>
                        </tr>
                    </table>--%>
                    <table cellspacing="0" cellpadding="0" width="150" border="0" runat="server" id="menu_11"
                        style="display: none">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(22123)" href="javascript:void(0);">奖品管理中心
                                </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child22123" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Prizes/PrizeClassAdd.aspx"
                                    target="main">添加奖品类别 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Prizes/PrizeClass.aspx"
                                    target="main">奖品类别管理 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Prizes/PrizesAdd.aspx"
                                    target="main">添加奖品 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Prizes/Prizes.aspx"
                                    target="main">奖品管理 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Prizes/PrizesH.aspx"
                                    target="main">兑奖记录管理 </a>
                            </td>
                        </tr>
                    </table>
                    <table cellspacing="0" cellpadding="0" width="150" border="0" runat="server" id="menu_12"
                        style="display: none">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(22124)" href="javascript:void(0);">系统配置中心
                                </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child22124" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/Filtering.aspx"
                                    target="main">注册过滤设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/ReceiveMoneyConfig.aspx"
                                    target="main">添加设置领取金币参数 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/ReceiveMoneySettings.aspx"
                                    target="main">领取金币设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/Prices.aspx"
                                    target="main">注册送金币设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/LastLoginGameCount.aspx"
                                    target="main">平台显示最近登录游戏个数 </a>
                            </td>
                        </tr>
                        <%-- <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/CreateRanking.aspx" target="main">排行榜静态页设置
                                </a>
                            </td>
                        </tr>--%>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/GMAwardTypeSet.aspx"
                                    target="main">GM奖励方案设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/LinkAdd.aspx"
                                    target="main">友情链接设置 </a>
                            </td>
                        </tr>
                        <%--<tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/AwardSet.aspx"
                                    target="main">分享邀请参数设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/RewardRankSet.aspx"
                                    target="main">分享邀请等级奖励设置 </a>
                            </td>
                        </tr>--%>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/SConfig/AuditConfig.aspx"
                                    target="main">手游功能开关配置 </a>
                            </td>
                        </tr>
                        <%if (ConfigurationManager.AppSettings["Falimy"] == "1")
                          { %>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/FamilyAd/FamilyList.aspx"
                                    target="main">家族管理 </a>
                            </td>
                        </tr>
                        <%} %>
                    </table>
                    <% if (Convert.ToInt32(ConfigurationManager.AppSettings["IsCheckHeadPic"] ?? "0") == 1)
                       { %>
                    <table cellspacing="0" cellpadding="0" width="150" border="0">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(14)" href="javascript:void(0);">手游头像审核 </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child14" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Mobile/MobileHeadPic.aspx"
                                    target="main">手游头像审核 </a>
                            </td>
                        </tr>
                    </table>
                    <%} %>
                    <table cellspacing="0" cellpadding="0" width="150" border="0" runat="server" id="menu_13"
                        style="display: none">
                        <tr height="22">
                            <td style="padding-left: 30px" background="images/menu_bt.jpg">
                                <a class="menuParent" onclick="expand(22125)" href="javascript:void(0);">推广系统管理
                                </a>
                            </td>
                        </tr>
                        <tr height="4">
                            <td>
                            </td>
                        </tr>
                    </table>
                    <table id="child22125" style="display: none" cellspacing="0" cellpadding="0" width="150"
                        border="0">
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Promotion/PrCs.aspx"
                                    target="main">推广相关参数设置 </a>
                            </td>
                        </tr>
                        <tr>
                            <td align="middle" width="30">
                                <img height="9" src="images/menu_icon.gif" width="9">
                            </td>
                            <td>
                                <a class="menuChild" href="/<%=ConfigurationManager.AppSettings["ManageDirectory"]%>/Promotion/PrList.aspx"
                                    target="main">推广管理 </a>
                            </td>
                        </tr>
                    </table>
                </td>
                <td width="1" bgcolor="#d1e6f7">
                </td>
            </tr>
        </table>
    </div>
    <script type="text/javascript" language="javascript">

        $().ready(function () {
            var menus = $('#menus').val();
            if (menus != null && menus.length > 0) {

                var array = menus.split("-");
                var obj = null;
                if (array != null && array.length > 0) {
                    for (var i = 0; i < array.length; i++) {
                        if ($("#menu_" + array[i]) != null) {
                            $("#menu_" + array[i]).show();
                        }
                    }
                }

            }

        });
        function expand(el) {
            childObj = document.getElementById("child" + el);

            if (childObj.style.display == 'none') {
                childObj.style.display = 'block';
            }
            else {
                childObj.style.display = 'none';
            }

            return;
        }

        $(function () {
            $(".menuChild").click(

      function () {

          $(".menuChild").each(function () {
              $(this).css('color', "#000000");

          });

          $(this).css('color', "#FF0000");
      }
            );
        });
        function changeMenu(ID) {

        }
    </script>
    </form>
</body>
</html>
