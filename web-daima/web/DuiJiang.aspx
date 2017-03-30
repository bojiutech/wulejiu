<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.DuiJiang" %>

<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title><%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络游戏世界___最专业的棋牌游戏平台</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <meta name="Description" content="<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏平台是中国最专业的网络棋牌游戏中心之一，是<%=ConfigurationManager.AppSettings["sitename"].ToString()%>网络旗下最主要的棋牌游戏平台，拥有各类棋牌游戏累计达100多种，包括人们熟知的斗地主、升级、麻将、围棋、四国军棋等。" />
    <meta name="Keywords" content="棋牌游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>游戏,<%=ConfigurationManager.AppSettings["sitename"].ToString()%>,棋牌,双扣,麻将,斗地主,牛牛,三扣一,连连看,四国军旗,象棋,棋牌比赛,休闲游戏,小游戏" />
    <link href="/css/reset.css" rel="stylesheet" type="text/css" />
    <link href="/css/base.css" rel="stylesheet" type="text/css" />
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
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
        
        .red
        {
            color: red;
            font-family: Arial, "宋体";
        }
        #r_content img
        {
            max-width: 500px;
        }
        /* for Firefox & IE7 */* html #r_content img
        {
            /* for IE6 */
            width: expression(this.width > 700 ? 500 : true);
        }
    </style>
</head>
<body>
    <form id="Form1" class="democss" runat="server" onsubmit="return onFormSubmit(this)">
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
                <div class="text">
                   奖品兑换
                </div>
            </div>
            <div class="totalBd">
                <table summary="" border="0" class=" tab05">
                   
                 
                        <tr>
                            <th scope="row">
                                奖品名称
                            </th>
                            <td>
                                <img src="/Images/cont_line02.jpg" alt="" />
                            </td>
                            <td class="font01 l10">
                                <%=AwardName %>
                            </td>

                            <td rowspan="4" >
                             <img src="<%= AwardPic%>" alt="" width="136" height="107"  />
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                所需<%=UiCommon.StringConfig.GoldName%>
                            </th>
                            <td>
                                <img src="/Images/cont_line02.jpg" alt="" />
                            </td>
                            <td class="font01 l10">
                                <%=UiCommon.StringConfig.AddZeros(AwardMoney)%><%=UiCommon.StringConfig.GoldName%>
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                所需时长
                            </th>
                            <td>
                                <img src="/Images/cont_line02.jpg" alt="" />
                            </td>
                            <td class="font01 l10">
                                <%=AwardTime %>小时（游戏时间）
                            </td>
                        </tr>
                        <tr>
                            <th scope="row">
                                剩余数量
                            </th>
                            <td>
                                <img src="/Images/cont_line02.jpg" alt="" />
                            </td>
                            <td class="font01 l10">
                                <%=AwardCount%>
                            </td>
                        </tr>
                   
                </table>
                <div class="dtjs" style="  padding-top:0px;width:100%;">
                    <h3 style="background-color:#bedff6;">
                        奖品详细说明</h3>
                    <br />
                    <div id="r_content" style="width: 100%; word-wrap: break-word;">
                        <%= Server.HtmlDecode(AwardInfo) %>
                    </div>
                    <br />
                    <strong>请认真填写您的姓名和联系方式以及详细收货地址，以便确保您所兑换的奖品准确送到您的手中!</strong>
                    <br />
                    <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                    <div class="cz">
                        <table width="100%" border="0" cellspacing="0" cellpadding="0">
                            <tr>
                                <td colspan="2">
                                    当前拥有的奖券数：<%=jq %>
                                </td>
                            </tr>
                            <tr>
                                <th width="20%" height="30" align="right" scope="row">
                                    <label for="id01">
                                        真实姓名：</label>
                                </th>
                                <td width="80%">
                                    <asp:TextBox ID="txtTrueName" runat="server" CssClass="in" MaxLength="20"></asp:TextBox>
                                </td>
                            </tr>
                            <tr>
                                <th height="30" align="right" scope="row">
                                    <label for="id01">
                                        联系电话：</label>
                                </th>
                                <td>
                                    <asp:TextBox ID="txtPhone" runat="server" CssClass="in" MaxLength="20"></asp:TextBox>
                                    <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtPhone"
                                        Display="Dynamic" ErrorMessage="电话号码不能空！"></asp:RequiredFieldValidator>
                                    <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" ControlToValidate="txtPhone"
                                        Display="Dynamic" ErrorMessage="请输入正确的电话号码！" ValidationExpression="^(\(\d{3,4}\)|\d{3,4}-|\d{3})\d{7,8}$"></asp:RegularExpressionValidator>
                                </td>
                            </tr>
                            <tr>
                                <th>
                                    &nbsp;
                                </th>
                                <td>
                                    注：固定电话的区号用()或- 隔开！
                                </td>
                            </tr>
                            <tr>
                                <th height="30" align="right" scope="row">
                                    <label for="id01">
                                        收货地址：</label>
                                </th>
                                <td>
                                    <asp:TextBox ID="txtAddress" runat="server" CssClass="in" MaxLength="100" Width="365px"></asp:TextBox>
                                </td>
                            </tr>
                            <tr>
                                <th height="30" align="right" scope="row">
                                    <label for="id01">
                                        备注信息：</label>
                                </th>
                                <td>
                                    <asp:TextBox ID="txtUserRemark" runat="server" Rows="2" TextMode="MultiLine" Width="365px"
                                        MaxLength="500"></asp:TextBox>
                                </td>
                            </tr>
                            <tr>
                                <th height="50" scope="row">
                                </th>
                                <td>
                                    <input type="submit" name="imageField2" id="imageField2" class="but_01" value="  "
                                        onserverclick="button5_ServerClick" runat="server" />
                                </td>
                            </tr>
                        </table>
                    </div>
                    <script type="text/javascript">
    <!--
                        function onFormSubmit(f) {

                            //            var pass  = document.getElementById("txtPassword");
                            //            if(!alertNull(pass,"请先输入您的密码！")){
                            //				return false;
                            //            }

                            //真实姓名-----------
                            var txtTrueName = document.getElementById('txtTrueName');
                            if (!alertNull(txtTrueName, '请输入真实姓名！')) {
                                return false;
                            }

                            //联系电话-----------
                            var txtPhone = document.getElementById('txtPhone');
                            if (!alertNull(txtPhone, '请输入联系电话！')) {
                                return false;
                            }

                            //联系地址-----------
                            var txtAddress = document.getElementById('txtAddress');
                            if (!alertNull(txtAddress, '请输入收货地址！')) {
                                return false;
                            }

                            var o = document.getElementById("txtUserRemark");
                            if (o.value.length > 500) {
                                alert('备注不能超过500个字符');
                                return false;
                            }

                            return true;
                        }
     //-->
                    </script>
                </div>
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
