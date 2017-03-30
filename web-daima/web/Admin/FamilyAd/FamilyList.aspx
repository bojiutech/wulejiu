<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="FamilyList.aspx.cs" Inherits="HN.Admin.Admin.FamilyAd.FamilyList" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
         <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
<!--
body {

	margin-top: 0px;
}
        .style1
        {
            height: 24px;
        }
-->
</style>
</head>
<body>
    <form id="form1" runat="server">
     <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td class="title_03" colspan="11">
                    <strong>家族管理设置</strong>
                    </td>
            </tr>
             <tr>
                <td class="title_03" colspan="11">
                  <a href="FamilyAdd.aspx">添加</a>
                    </td>
            </tr>
            <tr>
                <td>
                    序号</td>
                <td>
                   标题</td>
                <td>
                    内容</td>
                 <td>图片</td>
                <td>
                    操作</td>
            </tr>
            <asp:Repeater ID="GetFamilyList" runat="server">
                <ItemTemplate>
                    <tr>
                        <td>
                           <%=TableID=TableID+1 %>
                        </td>
                        <td>
                            <%#Eval("Title") %>
                          
                            </td>
                        <td>
                            <%#Eval("CONTENT")%>
                          </td>
                            <td> 
                               <img  src='<%#Eval("ImgAddress")%>' width="26" height="26"/>
                            </td>
                        <td>
                            <a href='FamilyEdit.aspx?id=<%#Eval("ID")%>'>修改</a>&nbsp;&nbsp; <a href='FamilyDel.aspx?imgurl=<%#Eval("ImgAddress")%>&id=<%#Eval("ID")%>' onclick="return confirm('确定删除？');">
                                删除</a></td>
                    </tr>
                </ItemTemplate>
            </asp:Repeater>
        </table>
    </form>
</body>
</html>
