function kuistd(id1,id2)
{
	var kuistd_obj = document.getElementById(id1);
	if(kuistd_obj)
	{
		kuistd_text = "<ul id='"+id2+"' class='Na' style='display:none;'><li><a href='http://www.jj.cn/'>J J ��ҳ</a></li><li><a href='http://www.jj.cn/download/download.html'>��������</a></li><li><a href='http://show.jj.cn/'>�� �� ��</a></li><li><a href='http://shop.jj.cn/'>J J �̳�</a></li><li><a href='http://www.jj.cn/rank/'>J J ����</a></li><li><a href='http://club.jj.cn/'>J J ����</a></li><li><a href='http://bbs.jj.cn/'>J J ��̳</a></li><li><a href='http://www.jj.cn/promote/'>�ƹ�׬��</a></li><li><a href='http://www.5599.com/'>��ҳ��Ϸ</a></li><li><a href='http://www.3399.com//?fr=10002-2'>С �� Ϸ</a></li><li class='Di'><dl><dt><a href='http://my.jj.cn/'>�ҵ�JJ��ҳ</a></dt><dt><a href='http://club.jj.cn/interface.php'>�ҵĹ���</a></dt><dt><a href='http://my.jj.cn/account/honour.php'>�ҵ�������</a></dt></dl></li></ul>";
		kuistd_obj.innerHTML = kuistd_text;
	}
}
kuistd("kuistd","celerityNavNa");
kuistd("kuistd_bottom","celerityNavNaD");
