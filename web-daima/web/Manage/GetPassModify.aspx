<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_GetPassModify" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>
<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<%@ Register Src="/Public/NewMenu.ascx" TagName="NewMenu" TagPrefix="uc1" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title></title>
    <link href="../../hn_css/css/www/hn_pub_15.css" rel="stylesheet" type="text/css" />
    <link href="../../hn_css/css/www/hn_prize_20150504.css" rel="stylesheet" type="text/css" />
    <link rel="stylesheet" type="text/css" href="../hnlogin/www/css/comm.css" />
    <link rel="stylesheet" type="text/css" href="../hnlogin/www/css/style.css" />
    <script src="../../hn_css/js/jquery.js" type="text/javascript"></script>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <style type="text/css">
        input
        {
            border: 1px solid #cfcece;
        }
  #content001 {
  width: 733px;
  background-color: #ffffff;
  overflow: hidden;
  margin:0 auto;
}
    </style>
</head>
<body>
    <div id="min_max_width">
        <uc1:NewMenu ID="NewMenu1" runat="server" />
        <div class="min_max_adap">
            <div class="wrap">
                <div class="totalContent">
                                <div class="totalHd png" style="background-image: none;
                        overflow: hidden; height: 62px;">
                        <i class="ico_67 i1 newsNotice png"></i>
                        <div id='noticetime' class="time">
                            <span></span>
                        </div>
                        <div class="text">
                          
                        </div>
                    </div>
                    <div class="totalBd">
                        <div id="content001">
                            <div id="title01">
                                <h3 class="fl">
                                    重置密码</h3>
                                <p class="dqwz">
                                    当前位置：首页 > 找回密码
                                </p>
                            </div>
                            <div id="sub_nr" style=" margin:0 auto;">
                                <div class="cz">
                                    <form id="form1" runat="server" onsubmit="return onFormSubmit(this)">
                                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab03">
                                        <tr>
                                            <th colspan="2" style="height: 40px; font-size: 14px;">
                                                第三步：设置新的密码
                                            </th>
                                        </tr>
                                        <tr>
                                            <th width="40%" height="30" align="right" scope="row">
                                                输入新密码：
                                            </th>
                                            <td width="60%" valign="middle">
                                                <asp:TextBox ID="txtPass" CssClass="pro_input" runat="server" TextMode="password"
                                                    MaxLength="20"></asp:TextBox>
                                                由6-20个英文字母或数字组成
                                            </td>
                                        </tr>
                                        <tr>
                                            <th align="right" height="30" scope="row" width="40%">
                                                确认新密码：
                                            </th>
                                            <td valign="middle" width="60%">
                                                <asp:TextBox ID="txtPass2" CssClass="pro_input" runat="server" TextMode="password"
                                                    MaxLength="20"></asp:TextBox>
                                                请再输入您上面输入的密码
                                            </td>
                                        </tr>
                                        <tr>
                                            <td height="65" scope="row">
                                                &nbsp;
                                            </td>
                                            <td>
                                                <input class="but_011" type="submit" name="button5" id="button5" value="更新密码" onserverclick="button5_ServerClick"
                                                    runat="server" />
                                                <input class="but_022" type="reset" name="button5" id="Submit1" value="重置" />
                                            </td>
                                        </tr>
                                        <tr>
                                            <td colspan="2" align="center" valign="middle">
                                                <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                                            </td>
                                        </tr>
                                    </table>
                                    </form>
                                    <script type="text/javascript">
    <!--

                                        function onFormSubmit(f) {

                                            var txtPass = document.getElementById('txtPass');
                                            if (!alertNull(txtPass, '请输入密码')) {
                                                return false;
                                            }

                                            if (!/^[0-9a-zA-Z]{6,20}$/.test(txtPass.value)) {
                                                alert('密码由6-20个英文字母或数字组成');
                                                txtPass.focus();
                                                return false;
                                            }

                                            var txtPass2 = document.getElementById('txtPass2');
                                            if (txtPass.value.trim() != txtPass2.value.trim()) {
                                                alert('两次输入密码不一致，请重新输入。');
                                                txtPass2.focus();
                                                return false;
                                            }

                                            return true;
                                        }
     //-->
                                    </script>
                                </div>
                                <div class="clear">
                                </div>
                            </div>
                            <!--right End-->
                            <p>
                                &nbsp;</p>
                        </div>
                    </div>
                </div>
            </div>
            <!--content End-->
            <!--footer-->
        </div>
    </div>
    <div class="wrap clear footer_info" style="margin: 0 auto; display:none;">
        <p class="fl">
            <a target="_blank" href="/index.aspx">
                <img alt="65游戏平台" src="../hnfooter/static/images/f_logo.jpg" class="fl"></a></p>
        <p class=" f_p">
            健康游戏忠告：抵制不良游戏 拒绝盗版游戏 注意自我保护 谨防受骗上当 适度游戏益脑 沉迷游戏伤身 合理安排 时间享受健康生活<br />
            <a rel="nofollow" href="../hnlogin/images/65wangwen.jpg" target="_blank">粤网文：[2013]0808-208号</a>
            <a rel="nofollow" href="http://www.miibeian.gov.cn/" target="_blank">粤ICP备16800008号</a>
            <a rel="nofollow" href="../hnlogin/images/65icp.jpg" target="_blank">增值电信业务经营许可证：粤B2-20130776</a><br />
            广东计算机系统股份有限公司 Copyright &copy; 2013-2015 版权所有 未经授权禁止转载、摘编、复制或建立镜像
        </p>
    </div>
    <script type="text/javascript" src="../../hn_css/js/www/www.jj.cn_pub_15.js"></script>
</body>
</html>
