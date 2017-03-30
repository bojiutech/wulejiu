<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="WebQQ.ascx.cs" Inherits="Bzw.Web.Public.WebQQ" %>

<div id="qq" style="z-index:3333;">
    <div class="fl" id="qqfl"  >
        <h2 style="background: url('/Images/qq/pop_tit01.png') no-repeat; width: 130px; height: 46px;">
            <span id="qqcls" style="width: 25px; height: 25px; top: 0; cursor: pointer; float: right;">
            </span>
        </h2>
        <div class="qq01" style="background-color: #065a7a; border-left: 1px solid #0b9dbf;
            border-right: 1px solid #0b9dbf">
            <ul>
                <%=contactStr %>
            </ul>
        </div>
        <p id="qq_btn">
            <img src="/Images/qq/pop_img01.png" alt="" /></p>
    </div>
    <p id="qqfr" style="display: none;">
        <img src="/Images/pop_tit02.gif" alt="" /></p>
</div>



<script   type="text/javascript" language="javascript">
    function QQHit(qq) {
        //window.open('http://crm2.qq.com/page/portalpage/wpa.php?uin=4006600669&cref=http://b.qq.com/eim/home.html&ref=&pt=%E4%BC%81%E4%B8%9AQQ%E5%8A%9E%E5%85%AC%E7%89%88_%E4%BC%81%E4%B8%9Aqq&f=1&ty=1&ap=&as=&aty=0&a=&dm=qq.com&sv=4&sp=');
        window.open('http://wpa.qq.com/msgrd?v=3&uin=' + qq + '&site=qq&menu=yes', '_blank', 'height=544, width=644,toolbar=no,scrollbars=no,menubar=no,status=no');
    }

    //在线展开与收起
    $(function() {
        $('#qqfr').click(function() {   //展开

            $('#qqfl').show();
            $('#qqfl').css("left","0");
            $('#qqfr').hide();
           

        });

        $('#qqcls').click(function() {   //关闭
            $('#qqfl').hide();
            $('#qq').css("left","-167px" );
           
            $('#qqfr').show();
         
        });

    })
 
    var IE6 = $.browser.msie && $.browser.version < 7 && !window.XMLHttpRequest;

    if (IE6) {

        $(window).scroll(function() {
            var bodyTop = 0;
            if (typeof window.pageYOffset != 'undefined') {
                bodyTop = window.pageYOffset
            } else if (typeof document.compatMode != 'undefined' && document.compatMode != 'BackCompat') {
                bodyTop = document.documentElement.scrollTop
            } else if (typeof document.body != 'undefined') {
                bodyTop = document.body.scrollTop
            }
            $('#qq').css('top', 220 + bodyTop);

        });
        document.getElementById("qq").style.position = "absolute";
    }
   
</script>
 