<%@ Control Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Public.Public_WebLogBannister"%>
 <div  id="record" class="rank_manu"> 
	<a id="g1" href="/Manage/Pay/PointCardLog.aspx" >�㿨��ֵ��¼</a>&nbsp;&nbsp;
	|&nbsp;&nbsp;<a id="g2" href="/Manage/Pay/PayMoneyLog.aspx" >������ֵ��¼</a>&nbsp;&nbsp;
	|&nbsp;&nbsp;<a id="g3" href="/Manage/BankMoneyOperaLog.aspx" >��ȡ��¼</a>&nbsp;&nbsp;
	|&nbsp;&nbsp;<a id="g4" href="/Manage/BankTransLog.aspx?type=1" >ת�˼�¼</a>&nbsp;&nbsp;
<%--	|&nbsp;&nbsp;<a id="g5" href="/Manage/BuyPropLog.aspx" >������߼�¼</a>&nbsp;&nbsp;
	|&nbsp;&nbsp;<a id="g6" href="/Manage/BuyVipLog.aspx" >����VIP��¼</a>&nbsp;&nbsp;
	|&nbsp;&nbsp;<a id="g7" href="/Manage/PrizeLog.aspx" >��Ʒ�һ���¼</a>
	|&nbsp;&nbsp;<a id="g8" href="/Manage/GetVipLog.aspx" >����VIP��¼</a>
	<br />|&nbsp;&nbsp;<a id="g9" href="/Manage/FasciExchangeLog.aspx" >����ֵ�һ���¼</a>--%>
	 
</div>

<script type="text/javascript">
<!--
    function SetLogNav(n){
        var ulnav = document.getElementById('record');
        var els = ulnav.getElementsByTagName('a');
        for(var i=0;i<els.length;i++){
            //alert(els[i].id);
            els[i].className='';
        }
        
        document.getElementById('g'+n).className='rank_manubg';
    }
//-->
</script>
