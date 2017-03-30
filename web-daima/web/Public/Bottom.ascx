<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="Bottom.ascx.cs" Inherits="HN.Web.Public.Bottom" %>
<div class="footer" style="margin: 0;">
    <div class="center">
        <div class="footMenu">
            <p>
         <%--备注用法：GetValue里边传参数名称，就获取到对应的参数值，参数名称列表在后台的“网站参数设置”里去查和修改--%>
                <a href="#" id="copyright">
                    <%=GetValue("copyright")%></a>&nbsp; &nbsp;|&nbsp; <a href="#" rel="nofollow" id="ProductCopyright">
                        <%=GetValue("ProductCopyright")%></a>&nbsp; &nbsp;|&nbsp; <a href="#" rel="nofollow">
                            <%=GetValue("copyright")%></a>&nbsp; &nbsp;|&nbsp; <a href="#" rel="nofollow">
                                <%=GetValue("copyright")%></a>&nbsp; &nbsp;|&nbsp; <a href="#" rel="nofollow">
                                    <%=GetValue("公司地址")%></a>&nbsp;
            </p>
            <p class="copyright">
                <a id="Title">
                    <%=GetValue("Title") %></a>&nbsp;&nbsp;&nbsp;<br>
                本平台游戏仅适合18岁以上人群&nbsp;&nbsp;&nbsp;ICP证：<a id="SiteICP" href="#" target="_blank"><%=GetValue("SiteICP")%></a>
            </p>
        </div>
    </div>
</div>
