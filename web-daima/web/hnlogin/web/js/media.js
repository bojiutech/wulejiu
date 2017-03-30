var getHost = function(url) {
	var host = "null";
	if (typeof url == "undefined"
			|| null == url)
		url = window.location.href;
	var regex = /.*\:\/\/([^\/|:]*).*/;
	var match = url.match(regex);
	if (typeof match != "undefined"
			&& null != match) {
		host = match[1];
	}
	if (typeof host != "undefined"
			&& null != host) {
		var strAry = host.split(".");
		if (strAry.length > 1) {
			host = strAry[strAry.length - 2] + "." + strAry[strAry.length - 1];
		}
	}
	return host;
}
var game_id = '';
if((document.referrer!='' && getHost(document.referrer)!='65.com') || decodeURIComponent(window.location.search)!=''){
	if(document.referrer!='' && getHost(document.referrer)!='65.com'){
		document.cookie = "media_from="+document.referrer+";path=/;domain=65.com;";
		var referer = document.referrer;
	}
	if(decodeURIComponent(window.location.search)!=''){
		document.cookie = "media_from="+decodeURIComponent(window.location.search).replace(/\?/,'')+";path=/;domain=65.com;";
		var referer = decodeURIComponent(window.location.search).replace(/\?/,'');
	}
	
	var domain = document.domain;
	var arr = domain.split(".");
	var arr_1 = location.href.split('/');
	var game_code = (arr[0]=='www' ? arr_1[3]:arr[0]);
	$.getJSON('http://www.65.com/game/getGame/?callback=?',function(data){	
		var result = eval(data);
		var length = data.length;
		for(var i=0; i<length; i++){
			if(game_code==result[i]['game_code']) game_id=result[i]['game_id'];
		}
		
		document.cookie = "media_reg_game="+game_id+";path=/;domain=65.com;";
		$.get('http://log.65.com/index.php?m=log&a=adv_log&game_id='+game_id+'&server_id=&cid=&mid=&subsite_id=&is_media=1&url_from='+referer);
	});
}
