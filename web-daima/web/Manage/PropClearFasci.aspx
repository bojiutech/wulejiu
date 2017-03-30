<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_PropClearFasci" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>
      
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

</head>
<body style="background-image: none;">
    <div id="content01" style="width: 703px; margin: 0px; padding: 0px; clear: both;
        overflow: hidden; text-align: left; float: left;">
            <div id="title01">
                <h3 class="fl">
                    ����ֵ����</h3>
                <p class="dqwz">
                    ��ǰλ�ã���ҳ > ��Ա���� > ����ֵ����</p>
            </div>
            <div id="sub_nr">
                <form id="form1" runat="server" onsubmit="return onFormSubmit(this)">
                <div  class="cz">
                    <table border="0" cellpadding="2" cellspacing="0" width="100%" >
                        <tr>
                            <td align="right">
                                ����ǰ������ֵ��
                            </td>
                            <td align="left">
                                <%=UserFasci %>
                            </td>
                        </tr>
                        <tr>
                            <td align="right">
                                ѡ�����ͣ�
                            </td>
                            <td align="left">
                                <asp:DropDownList ID="ddlType" runat="server" AutoPostBack="False">
                                </asp:DropDownList>
                                <br />
                            </td>
                        </tr>
                        <tr><td colspan="2" style=" text-align:center; height:40px; line-height:40px;"> <input class="but_011" type="submit" name="button5" id="button5" value="����ʹ��" onserverclick="button5_ServerClick"
                        runat="server" /></td></tr>
                    </table>
                </div>
                <div style="margin: 10px;">
                    <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                </div>
               
                <div style="text-align: left; margin-left: 8px; margin-top: 10px;">
                    <b>�����������˵����</b><br />
                    <table width="100%" border="0" align="center" cellpadding="3" cellspacing="0" class="memberTable">
                        <asp:Repeater ID="rptList" runat="server">
                            <ItemTemplate>
                                <tr align="center">
                                    <td align="left">
                                        <%# Eval("Description") %>
                                    </td>
                                    <td align="left">
                                        �۸�<%# UiCommon.StringConfig.AddZeros(Eval( "Price" ))%><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                                    </td>
                                </tr>
                            </ItemTemplate>
                        </asp:Repeater>
                    </table>
                </div>
                </form>

                <script type="text/javascript">
							<!--
                    function onFormSubmit(f) {

                        if (confirm('ȷ�Ϲ���ʹ����')) {
                            return true;
                        }
                        else {
                            return false;
                        }
                    }
							//-->
                </script>

            </div>
            <p>
                &nbsp;</p>
        </div>
</body>
</html>
