function kuistd(id1,id2)
{
	var kuistd_obj = document.getElementById(id1);
	if(kuistd_obj)
	{
		kuistd_text = "<ul id='"+id2+"' class='Na' style='display:none;'><li><a href='http://www.jj.cn/'>J J 首页</a></li><li><a href='http://www.jj.cn/download/download.html'>下载中心</a></li><li><a href='http://show.jj.cn/'>荣 誉 室</a></li><li><a href='http://shop.jj.cn/'>J J 商城</a></li><li><a href='http://www.jj.cn/rank/'>J J 排行</a></li><li><a href='http://club.jj.cn/'>J J 公社</a></li><li><a href='http://bbs.jj.cn/'>J J 论坛</a></li><li><a href='http://www.jj.cn/promote/'>推广赚金</a></li><li><a href='http://www.5599.com/'>网页游戏</a></li><li><a href='http://www.3399.com//?fr=10002-2'>小 游 戏</a></li><li class='Di'><dl><dt><a href='http://my.jj.cn/'>我的JJ首页</a></dt><dt><a href='http://club.jj.cn/interface.php'>我的公社</a></dt><dt><a href='http://my.jj.cn/account/honour.php'>我的荣誉室</a></dt></dl></li></ul>";
		kuistd_obj.innerHTML = kuistd_text;
	}
}
kuistd("kuistd","celerityNavNa");
kuistd("kuistd_bottom","celerityNavNaD");
