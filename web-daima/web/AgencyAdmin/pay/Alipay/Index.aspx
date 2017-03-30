<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Index.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.pay.Alipay.Index" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title></title>
 
    <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
    <script src="/Public/Js/public.js" type="text/javascript"></script>
    <style type="text/css">
        .cz
        {
            text-align: center;
            clear: both;
            width: 100%;
            margin: 0 auto;
        }
        .tab03
        {
            border-top: 2px solid #0c71a0;
            margin-left: 200px;
            border: solid 1px #2C2C2C;
            width: 900px;
        }
        .tab03 th
        {
            text-align: right;
            border: solid 1px #2C2C2C;
        }
        .tab03 td
        {
            text-align: left;
            border: solid 1px #2C2C2C;
        }
        .cz tbody tr
        {
            border-bottom: 1px solid #cccccc;
            height: 30px;
        }
        .cz tbody th
        {
            background-color: #f0f0f0;
            text-align: right;
            padding-left: 10px;
        }
        .cz tbody td
        {
            padding-left: 10px;
        }
        .yzm
        {
            background-color: #dddddd;
            width: 42px;
            height: 18px;
            text-align: center;
            margin-right: 5px;
        }
        .yzm01
        {
            width: 180px;
        }
        .yzm02
        {
            width: 280px;
        }
        .cz_btn
        {
            text-align: center;
            padding: 30px 0 60px 0;
        }
        
        bady
        {
            font-size: 12px;
        }
    </style>
</head>
<body>
    <form id="Form2" action="" class="democss" runat="server" onsubmit="return onFormSubmit(this)">
    <div>
        <div class="cz">
            <div id="sub_nr" style="margin-top: 10px; ">
                <h3 style="text-align:left; padding-left:210px;">
                    您选择了支付宝充值方式</h3>
          
                <table border="0" cellpadding="2" cellspacing="0" class="tab03">
                    <tr>
                        <td colspan="2">
                            &nbsp;
                        </td>
                    </tr>
                    <tr>
                        <th align="right" height="35">
                            当前充值帐号(用户名)：
                        </th>
                        <td align="left">
                            <asp:TextBox ID="txtUserName" runat="server" MaxLength="20" CssClass="input" ReadOnly="true"></asp:TextBox>
                            *
                        </td>
                    </tr>
           
                    <tr>
                        <th align="right" height="35">
                            金额：
                        </th>
                        <td align="left">
                            <asp:TextBox ID="PayMoney" runat="server" MaxLength="9" CssClass="input" onkeypress="return KeyPressNum(this,event);"
                                onkeyup="CalculationMoney()"></asp:TextBox>
                            * 金额请输入大于零的整数
                        </td>
                    </tr>
                    <tr>
                        <th align="right" height="35">
                            兑换成<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>：
                        </th>
                        <td>
                            <input id="ExchangeMoney" readonly="readonly" value="0" />
                        </td>
                    </tr>
                    <tr>
                        <th height="65" scope="row" height="35">
                            &nbsp;
                        </th>
                        <td>
                            <input type="submit" name="imageField2" id="imageField2" class="but_01" value="提&nbsp;&nbsp;交"
                                onserverclick="Button1_Click" runat="server" />
                            <input type="reset" name="imageField3" id="imageField3" class="but_02" value="重&nbsp;&nbsp;填"
                                onclick="ClearInfo()" />
                        </td>
                    </tr>
                </table>
                
                <div id="warning"  style=" color:Red; padding:5px; text-align:left; padding-left:210px;">
                    请一定要正确的填写充值的游戏帐号（用户名），如填错而造成的个人损失，玩家自己承担责任。</div>
            </div>
        </div>
        <!--content End-->
        <!--footer-->
    </div>
    </form>
    <script type="text/javascript">
<!--
			function CalculationMoney() {
				KeyPressNum(this,$("#PayMoney").val());
				if(isNaN($("#PayMoney").val())){
					$("#ExchangeMoney").val("0");
					return false;
					
				}else{
					$("#ExchangeMoney").val($("#PayMoney").val()*<%= UiCommon.StringConfig.AddZeros(MoneyRate) %>);
				}	
			}
			function ClearInfo() {
				document.getElementById('txtUserName').value = '';
			}

			function onFormSubmit(f) {
				var pmsg = '金额请输入大于零的整数！';
				var PayMoney = document.getElementById('PayMoney');
				if (!alertNonNegativeNumber(PayMoney, pmsg)) {
					return false;
				} else if (parseInt(PayMoney.value.trim()) <= 0) {
					alert(pmsg);
					PayMoney.focus();
					return false;
				}

				return true;
			}
 //-->
    </script>
</body>
</html>
