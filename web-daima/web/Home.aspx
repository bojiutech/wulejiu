<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Home.aspx.cs" Inherits="Bzw.Web.Home" %>
<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<%@ Register src="/Public/HotGame.ascx" tagname="HotGame" tagprefix="uc2" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title><%= SiteConfig.GetParaValue("Title")%>___最专业的棋牌游戏平台</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <meta name="Description" content="<%= SiteConfig.GetParaValue("Title")%>游戏平台是中国最专业的网络棋牌游戏中心之一，是<%= SiteConfig.GetParaValue("Title")%>网络旗下最主要的棋牌游戏平台，拥有各类棋牌游戏累计达100多种，包括人们熟知的斗地主、升级、麻将、围棋、四国军棋等。" />
    <meta name="Keywords" content="棋牌游戏,<%= SiteConfig.GetParaValue("Title")%>游戏,<%= SiteConfig.GetParaValue("Title")%>,棋牌,双扣,麻将,斗地主,牛牛,三扣一,连连看,四国军旗,象棋,棋牌比赛,休闲游戏,小游戏" />
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
</head>
<body>
    <form id="form1" runat="server">
    <div class="bgBox">
        <img src="/images/Bg2.jpg" alt="<%= SiteConfig.GetParaValue("Title")%>游戏世界" />
    </div>
    <div class="wrap">
        <div class="header">
            <div class="mainNav " id="mainNav">
                <uc1:NewMenu ID="NewMenu1" runat="server" />
            </div>
            <a href="/index.aspx">
                <div class="logo png" title="<%= SiteConfig.GetParaValue("Title")%>游戏世界">
                </div>
            </a>
        </div>
        <div class="content">
            <div class="indexLeft">
                <div class="nowDown" style=" padding-left:4px; padding-bottom:3px;">


                    <asp:Literal runat="server" ID="lit_link"> </asp:Literal>


                
                </div>
                <div class="pageNav">
                    <ul>
                        <li><a class="png" href="/Leaderboard.aspx"><i class="ico_44 i5 png"></i><span>玩家排行</span></a></li>
                        <li><a class="png" href="/manage/index.aspx"><i class="ico_44 i6 png"></i><span>会员中心</span></a></li>

                        <li><a class="png" href="/daoju.aspx" target="_blank"><i class="ico_44 i7 png">
                        </i><span>道具商城</span></a></li>
                        <li><a class="png" href="/Manage/Pay/Yeepay2/Default.aspx" target="_blank"><i class="ico_44 i8 png">
                        </i><span>在线充值</span></a></li>
                        <li class="popupBtntrigger"><a class="png" href="/Promoter.aspx">
                            <i class="ico_44 i9 png"></i><span>推广员</span></a></li>
                    </ul>
                </div>
                <div class="healthGames png">
                    <a href="/abc.html" target="_blank"></a>
                </div>
            </div>
            <div class="indexMiddle png">
                <div class="advertisement">
                    <div class="imgs">
                        <ul id="adPicsTrigger">
                            <%--轮换图片 437 * 220--%>
                            <asp:Repeater ID="repPic" runat="server">
                                <ItemTemplate>
                                    <li><a href="<%#Eval("LinkPic") %>" target="_blank">
                                        <img src='<%#Eval("PicUrl") %>'></a></li>
                                </ItemTemplate>
                            </asp:Repeater>
                            <%--轮换图片end--%>
                          
                        </ul>
                    </div>
                    <ul id="adBtnsTrigger" class="nums">
                        <li class="png cur"><a href="javascript:;"></a></li>
                        <li class="png "><a href="javascript:;"></a></li>
                        <li class="png "><a href="javascript:;"></a></li>
                        <li class="png "><a href="javascript:;"></a></li>
                        <li class="png "><a href="javascript:;"></a></li>
                    </ul>
                </div>
                <div class="newsList">
                    <div class="hd">
                        <a href="/NewList.aspx">更多+</a>资讯公告</div>
                    <div class="bd">
                        <ul>
                        <asp:Repeater runat="server"  ID="rep_new">
                        <ItemTemplate>
                         <li><span class="time"><%#DateTime.Parse(Eval("issue_time").ToString()).ToString("MM-dd")%></span><span>[<%#Eval("typeName")%>]<span><a  title='<%#Eval("title") %>' style='color: <%#Eval("TitleColor").ToString() == "black" ? "#555454" : Eval("TitleColor")%>;;' href='/NewsPage.aspx?Id=<%#Eval("news_id") %>'><%# MyTitle(Eval("title"),22)%></a></span></span></li>
                        </ItemTemplate>
                        </asp:Repeater>
                        </ul>
                    </div>
                </div>
            </div>
            <div class="indexRight png">
                <div class="mobileGames">
                    <div class="hd">
                        <a title="最新游戏" href="/GameList.aspx?type=new">更多+</a><i class="png"></i></div>
                    <div class="bd">
                        <ul>

                        <asp:Repeater ID="rep_newGame" runat="server">
                            <ItemTemplate>
                            <li><i class="png"></i><a title="<%#Eval("game_name") %>" class="for56ie6" href='/GameNew.aspx?id=<%#Eval("game_ID") %>'
                                target="_blank">
                                <img src="<%#Eval("Image_URL") %>"  alt="<%#Eval("game_name") %>" /></a></li>
                            
                            </ItemTemplate>
                        </asp:Repeater>
                          
                        </ul>
                    </div>
                </div>
                <div class="hotGames">
                    <div class="hd">
                        <a href="/GameList.aspx">更多+</a>热门游戏</div>
                    <div class="bd">
                        <ul>

                        <asp:Repeater runat="server" ID="rep_hotGame">
                        <ItemTemplate>
                        <li><i class="png"></i><a titl='<%#Eval("game_name") %>' class="for56ie6" href='/GameNew.aspx?id=<%#Eval("game_ID") %>'
                                target="_blank">
                              <img src="<%#Eval("Image_URL") %>"  alt="<%#Eval("game_name") %>" />
                              </a></li>
                        </ItemTemplate>
                        </asp:Repeater>
                         
                        </ul>
                    </div>
                </div>
                <div class="weibo png" style="  background-image:url(/images/kf.png); overflow:hidden; margin:0px;padding:0px;  background-position:center; background-repeat:no-repeat;  vertical-align:middle; text-align:center; clear:both; line-height:77px; ">
       <span style=" display:block;font-size:18px;font-weight:700; height:50px; width:90%; margin-top:18px;">
         <%= SiteConfig.GetParaValue("客服电话")%>
       </span>
       
                </div>
            </div>
            <div id="tvNav" class="tvNav scrollerTrigger png">
                <div class="arrowLeft leftBtnTrigger">
                    <a class="al png" href="javascript:;"></a>
                </div>
                <div class="TVstation">
                    <ul data-itemtype="li" class="scrollPanelTrigger">
                       
                        <uc2:HotGame ID="HotGame1" runat="server" />
                    </ul>
                </div>
                <div class="arrowRight rightBtnTrigger">
                    <a class="ar png" href="javascript:;"></a>
                </div>
            </div>
            <div class="gameInfo png">
                <ul>
                    <li>抵制不良游戏</li>
                    <li>拒绝盗版游戏</li>
                    <li>注意自我保护</li>
                    <li>谨防受骗上当</li>
                    <li>适度游戏益脑</li>
                    <li>沉迷游戏伤身</li>
                    <li>合理安排时间</li>
                    <li>享受健康生活</li>
                </ul>
            </div>
            <div class="footer png">
                <ul>
                    <li><i></i></li>
                    <li >
               
                        <p><%--| <a target="_blank" href="/Service.aspx">联系我们</a> | <a target="_blank" href="/NewsPage.aspx?type=1">关于我们</a>--%>
                        &nbsp;
                        </p>
                        <p> <a target="_blank" href="/yuewangwenimage.html" >  网络文化经营许可证:<%= SiteConfig.GetParaValue("文化经营许可证")%><%--京网文[2013]0298-064--%></a>   | 
                              <a target="_blank" href="http://www.miitbeian.gov.cn/" >   网站备案号:<%= SiteConfig.GetParaValue("SiteICP")%> </a>
                           <%-- | <a href="/images/ICP证1.jpg">TCP证书</a>--%>
                              
                       </p>
                        <p>地址： <%= SiteConfig.GetParaValue("公司地址")%> &nbsp;|
                            <%= SiteConfig.GetParaValue("Copyright")%> </p>

                                   <p>本游戏适合18岁以上的玩家进入丨禁止任何利用本平台游戏进行赌博的行为</p>

                    <p>  丨让我们共同净化游戏环境丨一旦发现有违反用户协议的行为丨我们将立即封杀账号！</p>
                    </li>
                </ul>
            </div>
        </div>

       
    </div>

  
    <script type="text/javascript" src="/js/jquery-1.7.2.min.js"></script>
    <script type="text/javascript" src="/js/scroll.js"></script>
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
