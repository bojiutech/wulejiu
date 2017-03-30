<%@ Page Language="C#" AutoEventWireup="true" Codebehind="Menu.aspx.cs" Inherits="DataAnaly.Analy.Menu" %>

<ul class="sf-menu">
	<li><a href="javascript:void(0);" title="������ҷ�������">������ҷ�������</a>
		<ul>
			<li><a href="/Analy/Online/OnlineUser_Date.aspx" title="��������ͳ��">��������ͳ��</a></li>
			<li><a href="/Analy/Online/OnlineUsers.aspx?type=0" title="��ǰ��������">��ǰ�������</a></li>
			<li><a href="/Analy/Online/OnlineUsers.aspx?type=1" title="���߻������б�">��ǰ���߻�����</a> </li>
		</ul>
	</li>
	<li><a href="javascript:void(0);" title="������������">����ҷ�������</a>
		<ul>
			<li><a href="/Analy/NewUser/DateReport.aspx" title="�����ÿ������ͳ��">ÿ������ͳ��</a></li>
			<li><a href="/Analy/Records/UserInfoList.aspx?type=0" title="ע����ϸ�б�">ע����ϸ�б�</a></li>
			<li><a href="/Analy/NewUser/UserLoginList.aspx" title="��¼��Ϸ�б�">��¼��Ϸ�б�</a></li>
			<li><a href="/Analy/NewUser/PayList.aspx" title="����ҳ�ֵ��¼">����ҳ�ֵ��¼</a></li>
		</ul>
	</li>
	<li><a href="javascript:void(0);" title="������������">��¼�б��������</a>
		<ul>
			<li><a href="/Analy/Records/UserLoginList.aspx" title="��½��Ϸ��¼">��½��Ϸ��¼</a></li>
			<li><a href="/Analy/Records/ActiveList.aspx" title="��Ծ��Ҽ�¼">��Ծ��Ҽ�¼</a></li>
			<li><a href="/Analy/Records/PayList.aspx" title="�û���ֵ��¼">��ҳ�ֵ��¼</a></li>
			<li><a href="/Analy/Records/GameRecord.aspx" title="�����Ϸ��¼">�����Ϸ��¼</a></li>
			<li><a href="/Analy/Records/UserInfoList.aspx?type=2" title="ע��24Сʱ���½��Ϸ���">ע��24Сʱ���½��Ϸ���</a></li>
			<li><a href="/Analy/Records/UserInfoList.aspx?type=1" title="ע��24Сʱ�ڵ�½����Ϸ���">ע��24Сʱ�ڵ�½����Ϸ���</a></li>
		</ul>
	</li>
	<li><a href="javascript:void(0);" title="����ͳ������">��Ӫ����ͳ������</a>
		<ul>
			<li><a href="/Analy/Report/LoopMoneyReport.aspx" title="�����ͨͳ��">�����ͨͳ��</a></li>
			<li><a href="/Analy/Report/DateReport.aspx" title="ÿ������ͳ��">ÿ������ͳ��</a></li>
			<li><a href="/Analy/Report/MonthReport2.aspx" title="ÿ������ͳ��">ÿ������ͳ��</a></li>
			<li><a href="/Analy/Report/AgencyRegReport.aspx" title="ÿ��ע��ͳ��">ÿ��ע��ͳ��</a></li>
			<li><a href="/Analy/Report/PayReport.aspx" title="ÿ�ճ�ֵͳ��">ÿ�ճ�ֵͳ��</a></li>
			<li><a href="/Analy/Report/GameTaxReport.aspx" title="ÿ�ճ�ˮͳ��">ÿ�ճ�ˮͳ��</a></li>
			<li><a href="/Analy/Report/GameCountReport.aspx" title="ÿ����Ϸ����ͳ��">ÿ����Ϸ����ͳ��</a></li>
			<li><a href="/Analy/Report/AgencyDateReport.aspx" title="������ÿ������ͳ��">������ÿ������ͳ��</a></li>
			<li><a href="/Analy/Report/GameCountAndTaxReport.aspx" title="��Ϸ��������ˮͳ��">��Ϸ��������ˮͳ��</a></li>
			<li><a href="/Analy/Report/AgencyUsers.aspx" title="������ֱ�����ע��ͳ��">������ֱ�����ע��ͳ��</a></li>
		</ul>
	</li>
	<li><a href="javascript:void(0);" title="ͼ�����ݷ�������">ͼ�����ݷ�������</a>
		<ul>
			<li><a href="/Analy/Chart/DateChart.aspx?type=0" title="ÿ�����ݷ���">ÿ�����ݷ���</a></li>
			<li><a href="/Analy/Chart/DateChart.aspx?type=1" title="�����ÿ�����ݷ���">�����ÿ�����ݷ���</a></li>
			<li><a href="/Analy/Chart/Chart.aspx?type=0" title="ÿ��ʱ������ݷ���">ÿ��ʱ������ݷ���</a></li>
			<li><a href="/Analy/Chart/Chart.aspx?type=1" title="�����ÿ��ʱ������ݷ���">�����ÿ��ʱ������ݷ���</a></li>
		</ul>
	</li>
	<li><a href="javascript:void(0);" title="ϵͳ����">ϵͳ����</a>
		<ul>
			<li><a href="/Analy/Config.aspx" title="��������">��������</a></li>
			<li><a href="javascript:void(0);" onclick="AdminEditMe();" title="�޸�����">�޸�����</a></li>
			<li><a href="/Analy/Default.aspx" title="ϵͳ��ҳ">ϵͳ��ҳ</a></li>
		</ul>
	</li>
</ul>
