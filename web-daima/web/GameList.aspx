<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GameList.aspx.cs" Inherits="Bzw.Web.GameList" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register Src="Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<title><%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络游戏世界___最专业的棋牌游戏平台</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
<meta name="Description" content="<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏平台是中国最专业的网络棋牌游戏中心之一，是<%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络旗下最主要的棋牌游戏平台，拥有各类棋牌游戏累计达100多种，包括人们熟知的斗地主、升级、麻将、围棋、四国军棋等。" />
<meta name="Keywords" content="棋牌游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>,棋牌,双扣,麻将,斗地主,牛牛,三扣一,连连看,四国军旗,象棋,棋牌比赛,休闲游戏,小游戏" />
<link href="/css/reset.css" rel="stylesheet" type="text/css" />
<link href="/css/base.css" rel="stylesheet" type="text/css" />
<style type="text/css">
    html
    {
        overflow-x: hidden;
        overflow-y: auto;
    }
    .plus
    {
        margin-left: 220px;
        margin-top: -140px;
        width: 415px;
        _margin-left: 110px;
        _margin-top: -215px;
    }
    .plus a
    {
        display: inline-block;
        text-align: center;
        width: 95px;
        color: #0073cc;
        font-size: 11px;
        -webkit-text-size-adjust: none;
    }
    .plus a:hover
    {
        color: #000000;
    }
</style>
<body>
    <form id="form1" runat="server">
    <div class="bgBox">
        <img src="/images/Bg2.jpg" />
    </div>
    <div class="wrap">
        <div class="header">
            <div class="mainNav " id="mainNav">
                <uc1:NewMenu ID="NewMenu1" runat="server" />
            </div>
            <a href="/index.aspx">
                <div class="logo png">
                </div>
            </a>
        </div>
        <div class="totalContent">
            <div class="totalHd png" style="background-image: none; background-color: #bedff6;
                overflow: hidden; height: 62px;">
                <i class="ico_67 i1 newsNotice png"></i>
                <div id='noticetime' class="time">
                    <span></span>
                </div>
                <div class="text" style="text-align:left">
                   <a style="color:#3f3f3f;" href="/Down2.aspx">游戏大厅 </a>&nbsp;| &nbsp;  <a style="color: #3f3f3f;" href="/Gamelist.aspx">游戏列表 </a> 
                </div>
            </div>
            <div class="totalBd">
               	 <ul class="gamelist">
                    <asp:Repeater ID="rpGameList" runat="server">
									<ItemTemplate>
								 
										<li>
											<a  href="/GameNew.aspx?id=<%#Eval("Game_id") %>" title="<%# Eval("Game_Name") %>">
												<img src="<%#Eval("Image_URL") %>" width="68" height="51" alt="<%# Eval("Game_Name") %>"/>
											</a>
											<p  class="ac t03"><a  style="color:#fff;" href="/GameNew.aspx?id=<%#Eval("Game_id") %>" title="<%# Eval("Game_Name") %>"><%# Eval("Game_Name") %></a></p>
										</li>
									</ItemTemplate>
					</asp:Repeater>
              </ul>
            </div>

            <div style=" width:100%; height:100%; text-align:center; margin:0 auto; margin-top:20px;">
            	<webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True"
				CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
				FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
				ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go" PageSize="24"
				TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="10" CurrentPageButtonClass="current" ShowPrevNext="False">
			</webdiyer:AspNetPager>
            </div>
        </div>
    </div>
    <div class="mask" style="display: none;" id="mask">
    </div>
    <div class="serviceIbox popup png" style="display: none;" id="servicePopup">
        <div class="service">
            <div class="iboxClose">
                <a class="popupCloseTrigger png" href="javascript:;"></a>
            </div>
            <div class="serviceQQ">
               &nbsp;
            </div>
        </div>
        <div class="serviceBottom">
        </div>
    </div>
    <div class="rechargeIbox popup png" style="display: none;" id="rechargePopup">
    </div>
    <script src="/js/jquery-1.7.2.min.js" type="text/javascript"></script>
    <script src="/js/scroll.js" type="text/javascript"></script>
    <!--[if IE 6]>
    <script src="/js/DD_belatedPNG.js"></script>
    <script>
        fixPng();
        function fixPng()
        {
            DD_belatedPNG.fix('.png');
	        $(function(){
		        $('a.for56ie6 img,a.for68ie6 img,a.for32ie6 img').each(function(){
			        var $i = $('<i>');
			        $(this).replaceWith($i);
			        $i.attr('style', 'cursor:pointer;filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(sizingMethod="scale",src="'+ $(this).attr('src') +'");background-image:none;');
		        });
	        });
        }
    </script>
    <![endif]-->
    </form>
</body>
</html>
