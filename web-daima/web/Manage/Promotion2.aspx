<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Promotion2.aspx.cs" Inherits="HN.Web.Manage.Promotion2" %>


<%@ Import Namespace="UiCommon" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title></title>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/public.js"></script>
    <script type="text/javascript" src="/Public/Js/password_check.js"></script>
    <script type="text/javascript" src="/Public/Js/District.js"></script>
        <script src="/Public/Js/public.js"></script>
    <style type="text/css">
        .star
        {
            color: Red;
            font-size: 17px;
            font-weight: bold;
            display: inline-block;
            margin-top: 8px;
            margin-left: 3px;
        }
        .tips
        {
            display: inline-block;
            margin-left: 20px;
        }
    </style>
</head>
<body style="background-image: none;overflow:auto">
  <form id="Form1" runat="server">
    <div id="content01" style="width: 703px; margin: 0px; padding: 0px; clear: both;
        text-align: left; float: left;">
         <div id="title01">
            <h3 class="fl">
                游戏推广员</h3>
            <p class="dqwz">
                当前位置：首页 > 会员中心 > 游戏推广员</p>
        </div>
        <div id="sub_nr" style="margin-top: 10px;">
            <div id="memText01">
                <h4 id="h3Add" runat="server">
                    <%--	<img src="/images/icon03.gif" width="30" height="29" />--%>您目前还不是游戏推广员，现在就申请吧！
                </h4>
                <h4 id="h3Edit" runat="server" visible="false">
                    <%--<img src="/images/icon03.gif" width="30" height="29" />--%>非常感谢您提交的推广员申请资料，我们会尽快进行审核，请耐心的等待<br />
                    如有任何疑问，请联系网站管理员！
                </h4>
                <h4 id="h3InCheck" runat="server" visible="false">
                    <%--<img src="/images/icon03.gif" width="30" height="29" />--%>非常感谢您提交的推广员申请资料，<span
                        style="color: Red">资料已经审核中</span>，请耐心的等待<br />
                    如有任何疑问，请联系网站管理员！
                </h4>
                <h4 id="h3Pass" runat="server" visible="false">
                    <%--<img src="/images/icon03.gif" width="30" height="29" />--%>您的推广员身份已审核通过！现在就开始推广赚钱吧！
                </h4>
                <h4 id="h3notPass" runat="server" visible="false">
                    <%--<img src="/images/icon03.gif" width="30" height="29" />--%>您的推广员身份资料审核不通过！请重新申请！
                    <p>
                        拒绝理由：<p style="color: Red">
                            <%= Remark %></p>
                    </p>
                </h4>
                <div class="cz">
                    <table id="dltgAddress" runat="server" visible="false" width="100%" border="0" cellpadding="0"
                        cellspacing="0" class="tab07">
                        <tr>
                            <th align="right" scope="row">
                                &nbsp;
                            </th>
                            <td valign="middle">
                                &nbsp;
                            </td>
                        </tr>
                        <tr>
                            <th width="29%" height="30" align="right" scope="row">
                                我的推广地址：
                            </th>
                            <td width="71%" valign="middle" align="left">
                             <a target="_blank" href="/Register.aspx?recommend=<%=UiCommon.UserLoginInfo.UserName %>" class="under_line"  >
                                    <%=UiCommon.StringConfig.WebSiteName %>/Register.aspx?recommend=<%=UiCommon.UserLoginInfo.UserName %>
                                </a>
                            </td>
                        </tr>
                        <tr>
                            <th width="29%" height="30" align="right" scope="row">
                                我推广的玩家：
                            </th>
                            <td width="71%" valign="middle" align="left">
                                <a id="aa" href="PromotionBalance.aspx">点击查看我的推广记录（玩家达到推广度100%时，请及时进行结算）</a>
                            </td>
                        </tr>
                        <tr>
                            <th width="29%" height="30" align="right" scope="row">
                                &nbsp;
                            </th>
                            <td width="71%" valign="middle">
                                <a href="PromotionDetail.aspx">点击查看我推广的玩家的充值记录</a>
                            </td>
                        </tr>
                        <tr>
                            <th width="29%" height="30" align="right" scope="row">
                                我要结账：
                            </th>
                            <td width="71%" valign="middle">
                                <a href="PromotionCheckout.aspx" class="under_line">点击转到我的推广收入页面</a>
                            </td>
                        </tr>
                    </table>
                </div>
                <div id="zx">
                    <table width="100%" id="DownPromotionSet" runat="server" border="0" cellpadding="0"
                        cellspacing="0" class="tab07">
                        <tr>
                            <th align="right" scope="row">
                                &nbsp;
                            </th>
                            <td valign="middle">
                                &nbsp;
                            </td>
                        </tr>
                    </table>
                </div>
              
                <asp:HiddenField ID="hfCheckState" runat="server" Value="" />
                <div class="cz">
                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab07">
                        <tr>
                            <th align="right" scope="row">
                                &nbsp;
                            </th>
                            <td valign="middle">
                                &nbsp;
                            </td>
                        </tr>
                        <tr>
                            <th width="29%" height="30" align="right" scope="row">
                                真实姓名：
                            </th>
                            <td width="71%" valign="middle">
                                <asp:TextBox ID="txtTrueName" runat="server" CssClass="pro_input" MaxLength="10"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <th width="29%" height="30" align="right" scope="row">
                                身份证号码：
                            </th>
                            <td width="71%" valign="middle">
                                <asp:TextBox ID="txtIDCardNo" runat="server" CssClass="pro_input" MaxLength="22"></asp:TextBox><span
                                    class="star">*</span>
                            </td>
                        </tr>
                        <tr>
                             <th width="29%" height="30" align="right" scope="row">
                                身份证正面图片:
                           </th>
                           <td width="71%" valign="middle">
                                <asp:PlaceHolder runat="server" ID="phImageIDCardMain">
                                    <asp:TextBox runat="server" ID="txtImageIDCardMain" CssClass="put"></asp:TextBox>&nbsp;
                                    <input type="button" value=" 查 看 " class="put" onclick="OpenUrlNotAll('<%=txtImageIDCardMain.Text.Trim() %>',0,0);" />&nbsp;
                                    <%--<input type="button" value=" 删 除 " class="put" onclick="LocationToMeParam('action=delimg');" />--%>
                                </asp:PlaceHolder>
                                <asp:PlaceHolder runat="server" ID="phFileUpload">
                                    <asp:FileUpload runat="server" ID="fuImageIDCardMain" filter="" />（300K以内，仅允许jpg,jpeg及gif格式）
                                </asp:PlaceHolder>
                                <%--<iframe src='../inc/upload.inc.aspx' frameborder='0' style='height: 25px; width: 90%;'
                        scrolling='no'></iframe>--%>
                            </td>
                        </tr>
                        <tr>
                             <th width="29%" height="30" align="right" scope="row">
                                身份证反面图片:
                            </th>
                            <td width="71%" valign="middle">
                                <asp:PlaceHolder runat="server" ID="phImageIDCardOther">
                                    <asp:TextBox runat="server" ID="txtImageIDCardOther" CssClass="put"></asp:TextBox>&nbsp;
                                    <input type="button" value=" 查 看 " class="put" onclick="OpenUrlNotAll('<%=txtImageIDCardOther.Text.Trim() %>',0,0);" />&nbsp;
                                    <%--<input type="button" value=" 删 除 " class="put" onclick="LocationToMeParam('action=delimg');" />--%>
                                </asp:PlaceHolder>
                                <asp:PlaceHolder runat="server" ID="phFileUpload1">
                                    <asp:FileUpload runat="server" ID="fuImageIDCardOther"   />（300K以内，仅允许jpg,jpeg及gif格式）
                                </asp:PlaceHolder>
                                <%--<iframe src='../inc/upload.inc.aspx' frameborder='0' style='height: 25px; width: 90%;'
                        scrolling='no'></iframe>--%>
                            </td>
                        </tr>
                        <tr>
                            <th height="30" align="right" scope="row">
                                联系电话：
                            </th>
                            <td valign="middle">
                                <asp:TextBox ID="txtPhone" runat="server" CssClass="pro_input" MaxLength="20"></asp:TextBox><span
                                    class="star">*</span>
                                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtPhone"
                                    Display="Dynamic" ErrorMessage="联系电话不能空！"></asp:RequiredFieldValidator>
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
                                联系地址：
                            </th>
                            <td valign="middle">
                                <asp:TextBox ID="txtAddress" runat="server" CssClass="pro_input" MaxLength="50"></asp:TextBox><span
                                    class="star">*</span>
                            </td>
                        </tr>
                        <tr>
                            <th height="30" align="right" scope="row">
                                开户行：
                            </th>
                            <td valign="middle">
                                <asp:TextBox ID="txtBankName" runat="server" CssClass="pro_input" MaxLength="50"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <th height="30" align="right" scope="row">
                                银行账号：
                            </th>
                            <td valign="middle">
                                <asp:TextBox ID="txtBankNo" runat="server" CssClass="pro_input" MaxLength="20"></asp:TextBox>
                            </td>
                        </tr>
                        <tr id="SumbitBtn" runat="server">
                            <th height="65" scope="row">
                                &nbsp;
                            </th>
                            <td>
                                <input runat="server" class="but_011" type="submit" name="button5" id="button5" value=""
                                    onserverclick="button5_ServerClick" />&nbsp;&nbsp;<input class="but_022" type="button"
                                        name="button5" id="Submit1" value="清空重写" onclick="ClearInfo()" runat="server" />
                            </td>
                        </tr>
                    </table>
                </div>
             
                <script type="text/javascript">

                    function aa() {
                    
            window.document.title = $("#fe_text").text();
        }

<!--

                    function ClearInfo() {
                        document.getElementById('txtTrueName').value = '';
                        document.getElementById('txtPhone').value = '';
                        document.getElementById('txtAddress').value = '';
                         document.getElementById('txtIDCardNo').value = '';
                          document.getElementById('txtBankName').value = '';
                           document.getElementById('txtBankNo').value = '';
                    }

                    function onFormSubmit(f) {

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
                        if (!alertNull(txtAddress, '请输入联系地址！')) {
                            return false;
                        }

                        return true;
                    }
						  

 //-->
                </script>
                <br />
                <br />
                <strong>推广员申请流程：</strong><br />
                1、注册成为会员
                <br />
                2、申请为推广员
                <br />
                3、审核通过，成为推广员
            </div>
            <div class="clear">
            </div>
        </div>
        <p>
            &nbsp;</p>
        <div class="clear">
        </div>
    </div>
       </form>
</body>
</html>

