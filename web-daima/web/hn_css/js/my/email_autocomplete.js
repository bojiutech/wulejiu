(function(){
	if($("#email").length < 1) return;
	var email_addr = ['@qq.com','@163.com','@126.com','@sina.com','@sina.cn','@sohu.com','@vip.qq.com','@vip.sina.com','@hotmail.com','@tom.com','@21cn.com','@gmail.com','@139.com','@189.com']
	$("#email").focus(function(){
		if(!$("#email_dl").length){
			$("#email").after("<dl id='email_dl'></dl>");
			$("#email_dl").click(function(event){
				$("#email").val(event.target.innerHTML);
				event.stopPropagation();
			});
			$("#email_dl").hide();
		}
	}).keyup(function(event){
		var keycode = event.which;
		if($.inArray(keycode,[13,38,40]) >= 0){
			var email_dl_len = $("#email_dl dt").length;
			switch(keycode){
			case 13:
				event.stopPropagation();
				$("#email").val($("#email_dl dt[class='hov']").html());
				$("#email_dl").hide();
				break;
			case 38:
				var hov_key = $("#email_dl dt[class='hov']").index() - 1;
				hov_key = hov_key < 0 ? 0 : hov_key;
				$("#email_dl dt").removeClass('hov');
				$("#email_dl dt").eq(hov_key).addClass('hov');
				break;
			case 40:
				var hov_key = $("#email_dl dt[class='hov']").index() + 1;
				hov_key = hov_key >= email_dl_len ? hov_key-1 : hov_key;
				$("#email_dl dt").removeClass('hov');
				$("#email_dl dt").eq(hov_key).addClass('hov');
				break;
			}
			return;
		}
		$("#email_dl").hide().find("dt").remove();
		var email_input = $("#email").val();
		var key = email_input.lastIndexOf("@");
		var _find = (key  < 0) ? '': email_input.substring(key);
		var email_top = email_input.substring(0,key);
		if(email_input != ''){
			for(var i in email_addr){
				if(_find != ''){
					if(email_addr[i].indexOf(_find) > -1){
						$("#email_dl").append("<dt>"+email_top+email_addr[i]+"</dt>");
					}
				}else{
					$("#email_dl").append("<dt>"+email_input+email_addr[i]+"</dt>");
				}
			}
			if($("#email_dl dt").length > 0) $("#email_dl").show();
		}
	}).blur(function(){setTimeout(function(){$("#email_dl").hide();},200)});
})();
