<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Yeepay.aspx.cs" Inherits="Bzw.Web.AgencyAdmin.pay.Yeepay.Yeepay" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
      <script type="text/javascript" src="/Public/Js/common.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
    <script src="/Public/Js/public.js" type="text/javascript"></script>
    <style type="text/css">
.cz{   text-align:center;clear:both;width:100%;margin:0 auto; }
.tab03{border-top:2px solid #0c71a0;  margin-left:200px; border:solid 1px #2C2C2C; width:900px;}
.tab03 th{ text-align:right; border:solid 1px #2C2C2C;}
.tab03 td{ text-align:left; border:solid 1px #2C2C2C;}
.cz tbody tr {border-bottom:1px solid #cccccc;height:30px;}
.cz tbody th {background-color:#f0f0f0;text-align:right;padding-left:10px;}
.cz tbody td {padding-left:10px;}
.yzm {background-color:#dddddd;width:42px;height:18px;text-align:center;margin-right:5px;}
.yzm01 {width:180px;}
.yzm02 {width:280px;}
.cz_btn {text-align:center;padding:30px 0 60px 0;}

bady{ font-size:12px;}
    </style>
</head>
<body>
   <form id="Form2" action="" class="democss" runat="server" onsubmit="return onFormSubmit(this)">
    <div>
      <div class="cz">
                    <h6 style=" text-align:left; padding-left:210px;">
                        您选择了<%=payType %>充值方式</h6>
                   
                    <asp:HiddenField ID="hidType" runat="server" />
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
                                <asp:TextBox ID="txtUserName" runat="server" MaxLength="20" CssClass="input"></asp:TextBox>
                                *
                            </td>
                        </tr>
                     
                        <%if (ConfigurationManager.AppSettings["IsPayToPoint"] == "1")
                          { %>
                        <tr style=" display:none">
                            <th height="30" align="right" scope="row">
                                充值类型：
                            </th>
                            <td valign="middle">
                                <asp:RadioButtonList ID="rblPayType" runat="server" RepeatDirection="Horizontal"
                                    onclick="ChangeType()">
                                    <asp:ListItem Text="龙币" Value="money" Selected="True"></asp:ListItem>
                                    <asp:ListItem Text="积分" Value="point"></asp:ListItem>
                                </asp:RadioButtonList>
                            </td>
                        </tr>
                        <tr style=" display:none">
                            <th height="30" align="right" scope="row">
                                请选择游戏：
                            </th>
                            <td valign="middle">
                                <asp:DropDownList ID="ddlGameList" runat="server" Enabled="false">
                                </asp:DropDownList>
                                &nbsp;充值<%=UiCommon.StringConfig.MoneyName %>不用选择游戏
                            </td>
                        </tr>
                        <%} %>
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
                            <th  height="35">
                                <span id="sp1">兑换成<%=ConfigurationManager.AppSettings["moneyName"].ToString()%></span><span
                                    id="sp2" style="display: none;">兑换成积分</span>：
                            </th>
                            <td align="left">
                                <input type="text" id="ExchangeMoney" readonly="readonly" value="0" class="input" />
                            </td>
                        </tr>
                        <tr id="Card" style="display: none">
                            <th class="td2" align="right">
                                点卡类型：
                            </th>
                            <td style="text-align: left; padding: 5px 5px;">
                                <asp:RadioButtonList ID="rtype" runat="server">
                                    <asp:ListItem Text="易宝一卡通充值" Value="YPCARD-NET"></asp:ListItem>
                                    <asp:ListItem Text="征途游戏卡充值" Value="ZHENGTU-NET"></asp:ListItem>
                                    <asp:ListItem Text="盛大游戏卡充值" Value="SNDACARD-NET"></asp:ListItem>
                                    <asp:ListItem Text="Q币支付充值" Value="QQCARD-NET"></asp:ListItem>
                                    <asp:ListItem Text="全国骏网一卡通充值" Value="JUNNET-NET"></asp:ListItem>
                                </asp:RadioButtonList>
                            </td>
                        </tr>
                        <tr id="Bank" style="display: none">
                            <th class="td2" align="right">
                                请选择银行：
                            </th>
                            <td>
                                <table width="100%" border="0" cellspacing="0" cellpadding="0" style="border-top: 0px;">
                                    <tr id="Tr2">
                                        <td style="width: 100%; text-align: left;">
                                            <asp:RadioButtonList ID="rtypeBank" runat="server" RepeatColumns="4" RepeatDirection="Horizontal">
                                                <asp:ListItem Text="工商银行" Value="ICBC-NET"></asp:ListItem>
                                                <asp:ListItem Text="农业银行" Value="ABC-NET"></asp:ListItem>
                                                <asp:ListItem Text="招商银行" Value="CMBCHINA-NET"></asp:ListItem>
                                                <asp:ListItem Text="建设银行" Value="CCB-NET"></asp:ListItem>
                                                <asp:ListItem Text="交通银行" Value="BOCO-NET"></asp:ListItem>
                                                <asp:ListItem Text="民生银行" Value="CMBC-NET"></asp:ListItem>
                                                <asp:ListItem Text="平安银行" Value="SDB-NET"></asp:ListItem>
                                                <asp:ListItem Text="中国银行" Value="BOC-NET"></asp:ListItem>
                                                <asp:ListItem Text="中信银行" Value="ECITIC-NET"></asp:ListItem>
                                                <asp:ListItem Text="兴业银行" Value="CIB-NET"></asp:ListItem>
                                                <asp:ListItem Text="浦发银行" Value="SPDB-NET"></asp:ListItem>
                                                <asp:ListItem Text="光大银行" Value="CEB-NET"></asp:ListItem>
                                                <asp:ListItem Text="北京银行" Value="BCCB-NET"></asp:ListItem>
                                                <asp:ListItem Text="渤海银行" Value="3001_1002"></asp:ListItem>
                                                <asp:ListItem Text="广东发展银行" Value="GDB-NET"></asp:ListItem>
                                                <asp:ListItem Text=" 广州市农信社" Value="GNXS-NET"></asp:ListItem>
                                                <asp:ListItem Text="广州市商业银行" Value="GZCB-NET"></asp:ListItem>
                                                <asp:ListItem Text="上海农商银行" Value="SHRCB-NET"></asp:ListItem>
                                                <asp:ListItem Text="顺德农信社" Value="SDE-NET"></asp:ListItem>
                                                <asp:ListItem Text="华夏银行" Value="HXB-NET"></asp:ListItem>
                                                <asp:ListItem Text="南京银行" Value="NJCB-NET"></asp:ListItem>
                                            </asp:RadioButtonList>
                                        </td>
                                    </tr>
                                </table>
                            </td>
                        </tr>
                        <tr>
                            <th height="65" scope="row" >
                                &nbsp;
                            </th>
                            <td style=" text-align:center;">
                                <input type="submit" name="imageField2" id="imageField2" class="but_01" value="充&nbsp;&nbsp;值"
                                    onserverclick="Button1_Click" runat="server" />
                                <input type="reset" name="imageField3" id="imageField3" class="but_02" value="重&nbsp;&nbsp;填"
                                    onclick="ClearInfo()" />
                            </td>
                        </tr>
                    </table>
                 
                    <div id="warning" style=" color:Red; text-align:left; padding-left:210px; padding-top:5px;">
                        请一定要正确的填写充值的代理帐号（用户名），如填错而造成的个人损失，请自己承担责任。</div>
                    <div class="clear">
                    </div>
                </div>
    <!--content End-->
    <!--footer-->
  
    <script type="text/javascript">
		var type=document.getElementById("hidType").value;
		 
		if(type=="Bank")
		{
		 $("#Bank").show();
       
		}
		if(type!="Bank" && type!="SZX-NET" && type!="UNICOM-NET")
		{
		  $("#Card").show();
        
		}
 
			function CalculationMoney() {
			KeyPressNum(this,$("#PayMoney").val());
				if(isNaN($("#PayMoney").val())){
					$("#ExchangeMoney").val("0");
					return false;
					
				}else{
				  if ($("#rblPayType").find("input[@checked]").val() == "point") {
					$("#ExchangeMoney").val($("#PayMoney").val()*<%= UiCommon.StringConfig.AddZeros(MoneyToPointRate) %>);
					}else
					{
						$("#ExchangeMoney").val($("#PayMoney").val()*<%= UiCommon.StringConfig.AddZeros(MoneyRate) %>);
				
					}
				}	
			}
			function ClearInfo() {
				document.getElementById('txtUserName').value = '';
				document.getElementById('txtUserName2').value = '';
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
			 function ChangeType() {
            CalculationMoney();
	        if ($("#rblPayType").find("input[@checked]").val() == "point") {
	           document.getElementById("sp1").style.display="none";
	            document.getElementById("sp2").style.display="";
    	      
	            document.getElementById("ddlGameList").disabled = false;
	        }
	        else {
	            document.getElementById("sp1").style.display="";
	            document.getElementById("sp2").style.display="none";
	            document.getElementById("ddlGameList").disabled = true;
	        }
	}
 
    </script>
    </div>
    </form>
</body>
</html>
