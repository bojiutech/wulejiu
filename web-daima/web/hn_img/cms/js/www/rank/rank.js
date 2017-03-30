function form1_onsubmit(){
	nickname1 = $.trim($("#nickname").val());
	cdate =$("#cdate").val();
	cyclenum =$("#cyclenum").val();
	rlbid =$("#rlbid").val();
	rlbtype =$("#rlbtype").val();
	if(nickname1 == ""){
		alert("昵称不能为空！");
		return false;
	}else{	
		var goUrl ='http://www.jj.cn/rank/ajax.php?nickname='+encodeURI(nickname1)+'&rlbid='+rlbid+'&cdate='+cdate+'&cyclenum='+cyclenum+'&rlbtype='+rlbtype;			
		$.ajax({
		    type:'GET',									    
			url:goUrl,
		    success:function(data)
		    {
				if(data == -2){
					alert("用户昵称不存在！");
					return false;
				}else if(data == -1){
					alert("此用户不存在此排行榜！");
					return false;
				}else{					
					$("#userrank").html(data);
					$("#userrank").css("display","");
					return false;
				}
		    }
		});			
	}
	return false;
}
var list_id = 0;
var date_id = 0;
function get_date_more(){
    $("#listyy").empty();
	var d = new Date();
	var this_year = parseInt(d.getFullYear());
	var this_mon = d.getMonth() + 1;
	var str="";
	for (var j = 2013; j < this_year+1; j++) {				   
	   	if(j == this_year){
	   		str +="<option value='"+j+"' selected='selected'>" + j + "年</option>";
	   	}else{
	   		str +="<option value='"+j+"'>" + j + "年</option>";
	   	}	               
	 }
    $("#listyy").append(str);
    $("#listmm").empty();
   	str = "";
   	for (var i = 1; i <= 12; i++) {				   
   		if (i < 10) {
   			i = "0" + i;
   		}
		if(this_mon == parseInt(i)){
		 	str +="<option value='"+i+"' selected='selected'>" + i + "月</option>"
		}else{
		 	str +="<option value='"+i+"'>" + i + "月</option>";
		}	                        
	 }
   	$("#listmm").append(str);
	week();	
};

function close_more(){
	$("#set_my").empty();
	$("#pro_date").css("display","none");
	var week_val=$("#dropweek").val();
	var date_id=$("#listyy").val()+"-"+$("#listmm").val()+"-"+week_val.substring(0,2);		
	var d = new Date();
	var vYear = d.getFullYear();
	var vMon = d.getMonth() + 1;
	var vDay = d.getDate();
	var this_date=vYear+"-"+(vMon<10 ? "0" + vMon : vMon)+"-"+(vDay<10 ? "0"+ vDay : vDay);
	if(parseInt(date_id.replace(/-/gm,'')) - parseInt(this_date.replace(/-/gm,'')) > 8 ){
		alert("您查询的日期暂无统计数据！");
		return false;
	}else{
		var set_html=$("#listyy").val()+"年"+$("#listmm").val()+"月"+week_val.substring(week_val.lastIndexOf('||')+2);
		$("#wq_more").html("<em>"+set_html+"</em>");
		list_id=$(".active").attr('vkey');
		goPage('http://www.jj.cn/rank/rank.php?page_no=1',list_id,date_id);	
	}
			
};

$("#listyy").change(function(){
	week();
});
$("#listmm").change(function(){
	week();
});

function week() {
	var listy = $("#listyy").val();
	var listm = $("#listmm").val();
	var ymd = listy + "-" + listm + "-1";
	var week = new Date(Date.parse(ymd.replace(/\-/g, "/")));
	var d = new Date();
	var this_day = d.getDate();
	var w = week.toString().substring(0, 3);
	var yymm = new Date(listy, listm, 0);
	var day = yymm.getDate();
	var dd = 1;
	switch (w) {
		case "Mon": dd = 0; break;
		case "Tue": dd = 1; break;
		case "Wed": dd = 2; break;
		case "Thu": dd = 3; break;
		case "Fri": dd = 4; break;
		case "Sat": dd = 5; break;
		case "Sun": dd = 6; break;
	}
	
	var aw = 5;
	if (day == 28 && dd == 0) {
		aw = 4;
	}

	var i = 1;
	$("#dropweek").empty();
	var str = "";
	for (var i = 0; i < aw; i++) {
		var start = i * 7 + 1 - dd;
		var end = i * 7 + 7 - dd;
		if (start < 1) {
			start = 1;
		}
		if (end > day) {
			end = day;
		}
		if (start < 10) {
			start = "0" + start;
		}
		if (end < 10) {
			end = "0" + end;
		}
		var week = i+1>10 ? i+1 : '0'+(i+1);
		if(end - this_day < 7 && end - this_day > 0){
			str +="<option value='"+end+"||第" + week + "周' selected='selected'>第" + week + "周</option>";
		}else{
			str +="<option value='"+end+"||第" + week + "周'>第" + week + "周</option>"
		}               
	}
	$("#dropweek").append(str);  
	var itme = $("#dropweek").find("option:selected").text();
	$("#txtweek:text").val(itme.toString());
}	
$(".sec_li").click(function(){ 
	list_id=$(this).attr('vkey');
	is_zong=$(this).attr('vtype');
	if(is_zong == "zb" && is_zong != undefined){
		date_id = 7;
	}
	goPage('http://www.jj.cn/rank/rank.php?page_no=1',list_id,date_id);
})
$("#data a").click(function(){ 
	list_id=$(".active").attr('vkey');
	date_id=$(this).attr('vkey');
	goPage('http://www.jj.cn/rank/rank.php?page_no=1',list_id,date_id);	
})
function goPage(go_url,list_id,date_id){
	if(date_id == undefined){
		date_id = 0;
	}
	var goUrl = go_url+'&game='+$.trim($("#game").attr("vkey"))+'&listid='+list_id+'&dateid='+date_id;
	location.href = goUrl;	
}