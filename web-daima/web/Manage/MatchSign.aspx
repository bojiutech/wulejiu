<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MatchSign.aspx.cs" Inherits="Bzw.Web.Manage.MatchSign" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <meta http-equiv="Pragma" content="no-cache" />
    <meta http-equiv="Cache-Control" content="no-cache" />
    <meta http-equiv="Expires" content="0" />
    <link href="/style/css2.css" rel="stylesheet" type="text/css" />
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
    <script language="javascript" type="text/javascript">
        var timer1 = null;
        $().ready(function () {
            // 锁鼠标右键和键盘CONTEXTMENU键
            function click(e) {
                if (document.all) {
                    if (event.button == 2 || event.button == 3) {
                        oncontextmenu = 'return false';
                    }
                }
            }
            document.onmousedown = click;
            document.oncontextmenu = new Function("return false;");
            if ($("#imageField2").val() == 1) {
                $("#div_ts").show();
                $("#div_cs").hide();
                $("#imageField2").val("")
                $("#lblMsg").html("已报名！");
            }
            $("#div_cs").mouseover(function () {
                $("#div_cs").attr("src", "/images/cs_02.png");
            });

            $("#div_cs").mouseout(function () {

                $("#div_cs").attr("src", "/images/cs_01.png");
            });


            $("#div_ts").mouseover(function () {
                $("#div_ts").attr("src", "/images/ts_02.png");

            });

            $("#div_ts").mouseout(function () {

                $("#div_ts").attr("src", "/images/ts_01.png");
            });


            //报名
            $("#div_cs").click(
                     function () {

                         MyApply('matchapply');
                     }
                    );
            //退赛
            $("#div_ts").click(
                     function () {
                         MyApply('matchexit');
                     }
                    );
            GetApplyNum();
            timer1 = setInterval(GetApplyNum, 2000);
            if ("参数传递错误" == $("#lblMsg").text()) {
                clearInterval(timer1);
                $("#btnExit").hide();
                $("#imageField2").hide();
            }
        });
        //报名与退赛
        function MyApply(type) {
            $.getJSON("/Public/XmlHttpUser.aspx?rd=" + Math.random(), { type: type, gameID: $("#txtgameID").val(), RoomID: $("#txtroomID").val(), uid: $("#txtuid").val(), ContestID: $("#ContestID").val() }, function (data) {
                if (data != null) {

                    if (data.rs == -1) {

                        clearInterval(timer1);
                        $("#div_ts").hide();
                        $("#div_cs").hide();

                    }
                    if (data.rs == 1) {
                        $("#div_ts").show();
                        $("#div_cs").hide();

                        $("#span_score").html("<strong>当前" + $("#txt_MoneyName").val() + "数：</strong>" + data.WalletMoney + "</span>");
                        window.document.title = "1_" + $("#txtuid").val() + "_" + $("#txtgameID").val() + "_" + $("#txtroomID").val();
                        //GetApplyNum();
                    }
                    if (data.rs == 2) {

                        $("#span_score").html("<strong>当前" + $("#txt_MoneyName").val() + "数：</strong>" + data.WalletMoney + "</span>");
                        $("#div_ts").hide();
                        $("#div_cs").show();
                        window.document.title = "2_" + $("#txtuid").val() + "_" + $("#txtgameID").val() + "_" + $("#txtroomID").val();
                        GetApplyNum();
                    }
                    if (data.rs == 4 || data.rs == 7 || data.rs == 8)//报名失败
                    {
                        window.document.title = "3_" + $("#txtuid").val() + "_" + $("#txtgameID").val() + "_" + $("#txtroomID").val();
                    }
                    $("#lblMsg").html(data.msg);
                }

            });
            // matchapply 
            //matchexit
        }
        //获取当前已报名人数
        function GetApplyNum() {

            $.getJSON("/Public/XmlHttpUser.aspx?rd=" + Math.random(), { ContestID: $("#ContestID").val(), type: "GetApplyNum", gameID: $("#txtgameID").val(), RoomID: $("#txtroomID").val() }, function (data) {
                if (data != null && "0" == data.rs) {

                    $("#span_ybm").html(data.ynum);
                    $("#span_hbm").html(data.snum);
                    if (data.isOK == 1) {
                        clearInterval(timer1);
                        $("#lblMsg").html("比赛开始...");
                        $("#div_ts").hide();
                        $("#div_cs").hide();
                        window.document.title = "4_" + $("#txtuid").val() + "_" + $("#txtgameID").val() + "_" + $("#txtroomID").val();
                    }
                }
            });
        }
    </script>
    <title>1</title>
          <style type="text/css">
            .contentbm1 ul{   list-style-type:none; margin:0px; padding:0px;}
            .contentbm1 ul  li{   color:fff;}
             .contentbm1 ul  li span{color: #edfa39;}
        </style>
</head>
<body style="background-color: #506f9d; -moz-user-select: none; -webkit-user-select: none;
    user-select: none; cursor: default" oncontextmenu="return false" onselectstart="return false"
    ondragstart="return false" onbeforecopy="return false" oncopy="document.selection.empty()"
    onselect="document.selection.empty()">
    
    <form id="form1" runat="server">
    <div class="Ma-Box" style="display: none">
        <div class="Ma-Time">
        </div>
        <div class="ma-Content">
            &nbsp;
        </div>
    </div>
    <div style="height: 20px;">
        &nbsp;</div>
    <div class="main">
        <div class="content">
            <div class="Ma-Intr">
                <ul>
                 
                    <li><span runat="server" id="span_dg"><strong>夺冠次数：</strong>1</span> <span runat="server"
                        id="span_zjmc"><strong>最佳名次：</strong>1</span></li>
                    <li><span runat="server" id="span_cscs"><strong>参赛次数：</strong>0</span> </li>
                   <li><span runat="server" style="width: 180px;" id="span_score"><strong>当前金币数：</strong>1000</span>
                    </li>
                    <%-- <li><span style="font-size: 14px; color: #edfa39;"><strong style="font-size: 14px;
                        color: #fff;">配桌方式：</strong>比赛开始后系统将为您自动分配位置</span> </li>--%>
                </ul>
            </div>

        </div>
  
       <div class="contentbm1" style=" padding-top:0px;">
    <ul>
     <li>
      <span runat="server" id="span4">奖励方案
        </span>
    </li>

    <li>
     第一名： <span runat="server" id="span_nummoney1">0
        </span>
    </li>
        <li>
     第二名： <span runat="server" id="span_nummoney2">0
        </span>
    </li>

        <li>
     第三名： <span runat="server" id="span_nummoney3">0
        </span>
    </li>
          <li>
     报名费： <span runat="server" id="span_PayMoney">0
        </span>
    </li>
    </ul>
      
     <br/>
        
       

       </div>


       <div style=" clear:both"></div>
        <div class="contentbm">
            <input id="txtroomID" value="0" runat="server" type="hidden" />
            <input id="txtgameID" value="0" runat="server" type="hidden" />
            <input id="ContestID" value="0" runat="server" type="hidden" />
            <input id="txtuid" value="0" runat="server" type="hidden" />
             <input id="txt_MoneyName"  runat="server" type="hidden" value="" />
            <input id="imageField2" value="0" runat="server" type="hidden" />
            <div class="div_title">
                <div style="clear: both; text-align: right; padding-right: 30px;">
                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;已有&nbsp;<span id="span_ybm" class="s_num">0</span>&nbsp;名用户报名<br />
                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;还需&nbsp;<span class="s_num" id="span_hbm">0</span>&nbsp;名用户报名
                    <div style="clear: both; width: 300px; height: 71px; overflow: hidden; margin: 0px;
                        text-align: right; padding: 0px; padding-top: 20px;">
                        &nbsp;<asp:Label ID="lblMsg" runat="server" CssClass="msg" Text=""></asp:Label>
                    </div>
                </div>
            </div>
            <div class="div_titleb">
                <div style="width: 172px; padding: 0px; float: left; height: 101px; overflow: hidden;
                    cursor: pointer; margin: 0px; border: 0px; margin-top: 10px;">
                    <img src="/images/cs_01.png" id="div_cs" alt="参赛"  />
                    <img src="/images/ts_01.png" id="div_ts" alt="退赛"  />
                </div>
            </div>
        </div>
    </div>
    </form>
    <script language="javascript" type="text/javascript">
        // 修复 IE 下 PNG 图片不能透明显示的问题
        function fixPNG(myImage) 
        {
            
        }
    </script>
</body>
</html>
