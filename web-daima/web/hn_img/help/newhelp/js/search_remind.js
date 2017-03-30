$("#searchcontent").keyup(function (e){
	if (e.keyCode != 40 && e.keyCode != 38)
	{
         pinyinOption();
	 }
}
).focus(function ()
{
 	this.select(); 
}
);
function pinyinOption(){
 	var t = setTimeout(function()
	{
	 	var $currentTxt=$("#searchcontent").val();
		$.get('http://www.jj.cn/help/helpsearch.php',{'searchcontent':$currentTxt,'warn':"1"},function(data)
		{
			if(data == "")
			{
				$('search_auto').html('');
			}else
			{
				pinyinCallback(data,$currentTxt);
			}
		});
	  },500);
}
function pinyinCallback(data,$currentTxt)
{
	$con = data.split("@");
	$layer = "";
	for($index=0;$index<$con.length-1;$index++)
	{
		$layer += "<li class='line'>"+$con[$index]+"</li>";
	}
	$('#search_auto').html($layer).css('display','block');
	$('.line').hover(function()
	{
		$(this).addClass("hover"); 
		$('#searchcontent').val($(this).text());
	},function(){
		 $(this).removeClass("hover");
	});
	$('#search_auto').blur(function()
	{
		$('#search_auto').css('display','none');
	});
	
	$('.line').click(function()
	{
		 $('#searchcontent').focus();
		 $('#searchcontent').val($(this).text());
		 $('#search_auto').css('display','none');
	});
	
	var kindex=-1;
	document.documentElement.onkeydown=function(e)
	{
		e = window.event || e;
		if(e.keyCode == 40)
		{
			if(++kindex == $("#search_auto li").length){
				$("#searchcontent").val($currentTxt);
				$("#search_auto li").removeClass("hover");
				kindex=-1;
			}else
			{
				$('#searchcontent').val($($("#search_auto li")[kindex]).text());
				$($("#search_auto li")[kindex]).siblings().removeClass("hover").end().addClass("hover");
			}
		}
		if(e.keyCode == 38){
			if(--kindex == -1)
			{
				$("#searchcontent").val($currentTxt);
				$("#search_auto li").removeClass("hover");
			}
			else if(kindex == -2)
			{
				kindex=$("#search_auto li").length -1;
				$('#searchcontent').val($($("#search_auto li")[kindex]).text());
				$($("#search_auto li")[kindex]).siblings().removeClass("hover").end().addClass("hover");
			}else
			{
				$('#searchcontent').val($($("#search_auto li")[kindex]).text());
				$($("#search_auto li")[kindex]).siblings().removeClass("hover").end().addClass("hover");
			}
		}
		
	}				
}