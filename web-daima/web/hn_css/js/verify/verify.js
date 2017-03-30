function check_client_answer(successFunName,failFunName) {
	var str = $("#verifyVal").val();
	var vtr = $("#verifyImg").attr("name");
	var bol = false;
	$.ajax({
		url: "http://jj.cn/verify_code/c.php?vtr="+vtr+"&t="+Math.random()+"&callback=?&str="+str,
		type: "get",
		dataType: "jsonp",
		jsonp: "callback",
		cache: false,
		success: function(data) {
			if(data.msg == 1) {	
				$("#verifyTextAstr").val(str);
				eval(successFunName);
			} else {
				eval(failFunName);
			}
		},
		error:function(data){
			eval(failFunName);
		}
	});
}

function get_verify_code() {
	$("#verifyImg").attr({src:"http://hn_img/images/newIndex/201008/loadingN.gif"});
	url = "http://jj.cn/verify_code/v1.php";
	s = 10;
	z = "l";
	y = "l00";
	//q = "t="+Math.random()+"&s=1l&z=011&callback=?";
	q = "t="+Math.random()+"&s="+s+"&z="+z+"&y="+y+"&callback=?";
	url = url+"?"+q;
	//url = "http://jj.cn/verify_code/v1.php?t="+Math.random()+"&s="+s+"&z="+z+"&callback=?";
	//ur1 = "http://jj.cn/verify_code/v1.php?t="+Math.random()+"&s=10&z=l&y=l&callback=?";
	$.ajax({
		url: "http://jj.cn/verify_code/v1.php?t="+Math.random()+"&s=10&z=l&y=10&callback=?",
		type: "get",
		dataType: "jsonp",
		jsonp: "callback",
		cache: false,
		success: function(data) {
			$("#verifyImg").attr({src:"http://jj.cn/verify_code/i.php?id="+data.vid,name:data.vas});
			$("#verifyTextVid").val(data.vid);
			$("#verifyTextViq").val(data.viq);			
		},
		error:function(data){
		}
	});
}