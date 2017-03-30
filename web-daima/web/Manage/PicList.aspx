<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_PicList" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
    <link href="/Style/mainstyle.css" rel="stylesheet" type="text/css" />
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script src="/public/js/jquery.js"></script>

    <script src="/public/js/public.js"></script>

    <script src="/Public/Js/lightbox.js"></script>

    <link href="/css/lightbox.css" type="text/css" rel="stylesheet" />
    <style type="text/css">
        .photo_list li
        {
            width: 200px;
            float: left;
            text-align: center; /*margin-top:20px;*/
            height: 240px;
            overflow: hidden;
        }
        .photo_list li dl
        {
            border: 0px;
            width: 190px;
        }
        .photo_list li dl dt
        {
            font-weight: bold;
            float: none;
        }
        .photo_list li dl dt a
        {
            color: #072a90;
        }
        .photo_list li dl dd
        {
            color: #666666;
            float: none;
        }
        #nav li {
float: left;
background: url(/images/nav_line.jpg) no-repeat 30% 0%;
height: 37px;
line-height: 37px;
width: 89px;
margin-left: 0px;
padding-left: 0px;
}


 .h_topnav{ width:150px; overflow:hidden;}
 .h_call{ padding-left: 45px; margin:0px; background-image:none;}



    </style>
</head>

<body style="background-image: none;">
    <div id="content01" style="width: 703px; margin: 0px; padding: 0px; clear: both;
        overflow: hidden; text-align: left; float: left;">
            <div id="title01">
                <h3 class="fl">
                    相片管理</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 相片管理</p>
            </div>
            <div id="sub_nr" style="margin-top: 15px;">
                <div class="frie_pro">
                    <a href="Album.aspx" id="current">
                        <img src="/images/fhphoto.gif" width="12" height="12" />
                        返回相册列表</a> &nbsp;&nbsp;| &nbsp;&nbsp;<a href="PicListWrite.aspx" title="上传照片"><img
                            src="/images/scphoto.gif" width="12" height="12" />
                            上传照片</a><br />
                </div>
                <div class="modipoto">
                    <asp:Repeater ID="rptAlbumColumnList" runat="server">
                        <ItemTemplate>
                            <dl class="phoLib">
                                <dt>
                                    <%# "<a href='/Public/Thumbs.aspx?path=" + Server.UrlEncode( Eval( HN.Entities.VUsersAlbum._.PicPath.Name ).ToString() ) + "&width=547&height=404' title='" + Eval( HN.Entities.VUsersAlbum._.PicName.Name ) + "' rel='lightbox'>" +
								"<img src='/Public/Thumbs.aspx?path=" + Server.UrlEncode( Eval( HN.Entities.VUsersAlbum._.PicPath.Name ).ToString() ) + "&width=100&height=98' alt='" + Eval( HN.Entities.VUsersAlbum._.PicName.Name ) + "' title='" + Eval( HN.Entities.VUsersAlbum._.PicName.Name ) + "' onerror='this.src=\"/images/none.jpg\"' /></a>"%>
                                </dt>
                                <dd>
                                    <strong>
                                        <%#Eval( HN.Entities.VUsersAlbum._.PicName.Name )%>
                                    </strong>
                                </dd>
                                <dd class="pic_ms">
                                    <%# HN.Common.CommonManager.String.CutString( Eval( HN.Entities.VUsersAlbum._.PicDescription.Name ).ToString().Replace( "\r\n", "<br />" ), 14, "..." )%>
                                </dd>
                                <dd>
                                    上传于<%# Eval(HN.Entities.VUsersAlbum._.InputTime.Name,"{0:yyyy-MM-dd}") %></dd>
                                <dd>
                                    <a href="javascript:void(0);" onclick="SetToCover(<%#Eval( HN.Entities.VUsersAlbum._.ID.Name )%>);">
                                        设为封面</a> <a href="PicListWrite.aspx?params=<%#Eval( HN.Entities.VUsersAlbum._.ID.Name )%>"
                                            title="修改">修改</a> <a href="javascript:void(0);" onclick="DeletePic(<%#Eval( HN.Entities.VUsersAlbum._.ID.Name )%>)">
                                                删除</a></dd>
                            </dl>
                        </ItemTemplate>
                    </asp:Repeater>
                   
                    <div class="clear">
                    </div>
                    <!--pageNumber-->
                    <div class="sabrosus">
                        <webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                            FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
                            ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
                            TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5"
                            CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="8">
                        </webdiyer:AspNetPager>
                    </div>
                </div>
            </div>    <p>
                &nbsp;</p>
        </div>

    <script language="javascript" type="text/javascript">
        function DeletePic(id) {
            //删除
            if (id == null || id == "" || isNaN(id))
                return;
            if (!confirm("您确定要删除这张照片吗？\r\n注意：此操作不可恢复。"))
                return;
            OpenStateBar("正在删除，请稍候...");
            $.get(
				"/Manage/UsersForm.aspx?params=delpic&type=1&id=" + id + "&x=" + Math.random(),
				function (data) {
				    if (data == "success") {
				        RefreshMe();
				    }
				    else {
				        Msg(data, 200);
				    }
				}
			);
        }

        //设为封面
        function SetToCover(id) {
            if (id == null || id == "" || isNaN(id))
                return;
            OpenStateBar("正在设置，请稍候...");
            $.get(
				"/Manage/UsersForm.aspx?params=settocover&id=" + id + "&x=" + Math.random(),
				function (data) {
				    if (data == "success") {
				        LocationToMe();
				    }
				    else {
				        Msg(data, 200);
				    }
				}
			);
        }
    </script>

</body>
</html>
