<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="NewFooter.ascx.cs" Inherits="HN.Web.Public.NewFooter" %>
<div class="footer clear">
    <div class="wrap footcoop">
       <%-- <a target="_blank" href="#" rel="nofollow">关于我们</a> <a target="_blank" href="#">商务合作</a>
        <a target="_blank" href="#" rel="nofollow">加入我们</a>--%> <a target="_blank" href="/Service.aspx"
            rel="nofollow">客服中心</a> <a target="_blank" href="/abc.html">家长监护</a> <%--<a target="_blank"
                href="/Service.aspx">问题反馈</a>--%>
    </div>
    <div class="wrap clear link">
        <p class="fl link_l">
            <strong class="fr fl_txt">友情链接：</strong></p>
        <p class="fl link_r">
            <asp:Repeater runat="server" ID="rptLink">
                <ItemTemplate>
                    <a target="_blank" href="<%#Eval("Link") %>" title="<%#Eval("LinkDes") %>">
                        <%#Eval("LinkDes") %></a></ItemTemplate>
            </asp:Repeater>
        </p>
    </div>
    <div class="wrap clear footer_info">
        <p class="fl">
            <a target="_blank" href="#">
                <img alt="游戏平台" src="../hnfooter/static/images/f_logo.jpg" class="fl"></a></p>
        <p class="fl f_p">
            健康游戏忠告：抵制不良游戏 拒绝盗版游戏 注意自我保护 谨防受骗上当 适度游戏益脑 沉迷游戏伤身 合理安排 时间享受健康生活<br />
            <a rel="nofollow" href="#" target="_blank"><%= SiteConfig.GetParaValue("文化经营许可证")%></a> <a rel="nofollow"
                href="http://www.miibeian.gov.cn/" target="_blank"><%= SiteConfig.GetParaValue("SiteICP")%></a> <a rel="nofollow"
                    href="#" target="_blank">地址：<%= SiteConfig.GetParaValue("公司地址")%></a><br />
            <%= SiteConfig.GetParaValue("Title")%> Copyright &copy; <%= SiteConfig.GetParaValue("copyright")%> 版权所有 未经授权禁止转载、摘编、复制或建立镜像
        </p>
    </div>
	<div style="width:300px;margin:0 auto; padding:20px 0;">
		 		<a target="_blank" href="http://www.beian.gov.cn/portal/registerSystemInfo?recordcode=34170202000252" style="display:inline-block;text-decoration:none;height:20px;line-height:20px;"><img src="../hnfooter/static/images/beian.png" style="float:left;"/><p style="float:left;height:20px;line-height:20px;margin: 0px 0px 0px 5px; color:#939393;">皖公网安备 34170202000252号</p></a>
		 	</div>
</div>
