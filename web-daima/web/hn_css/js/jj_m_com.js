var isMaxWidth = true;
var isMinWidth = true;
function width_onload(){
	if(document.getElementById('m_jjcn_main_width')){
		var iWinWidth = document.body.clientWidth || document.documentElement.clientWidth;
		var oBorWidth = document.getElementById('m_jjcn_main_width');
		if(iWinWidth > 1200 && isMaxWidth){
			oBorWidth.className = 'max_1200'
			isMinWidth = true;
			isMaxWidth = false;
		}
		if(iWinWidth < 1200 && isMinWidth){
			oBorWidth.className = 'max_980'
			isMaxWidth = true;
			isMinWidth = false;
		}
	}
	gotop();
}

function game_list_hov(id,c_name){
	var oQp_game = document.getElementById(id);
	var aQp_li = oQp_game.getElementsByTagName('li')
	for( var i=0;i<aQp_li.length;i++){
		aQp_li[i].onmouseover = function(){
			this.className = c_name;
		}
		aQp_li[i].onmouseout = function(){
			this.className = '';
		}
	}
}

function location_href(){
	var locString = String(window.document.location.href);
	locString=locString.split('#');
	if(locString[1]){
		$('.right').find('.s2').html('').end().find('.'+locString[1]).find('.s2').html(locString[1]);
		$('.list_nav').find('li').removeClass('nav_hov').end().find('.'+locString[1]).addClass('nav_hov');
	}	
}
function gotop(){
	if(!document.getElementById('r_hidden')){
		$('.down_b').prepend('<div id="r_hidden" style="display:none"></div>');
	};	
	if(!document.getElementById('go_back')){
		$('body').append('<div class="go_back" id="go_back"><a href="http://www.jj.cn/m/" class="go_home" title="返回首页"></a> <a href="#" class="go_top" id="go_top" title="返回顶部"></a></div>');
	};
	
	
	var oBcak = document.getElementById('go_back');
	var oGotop = document.getElementById('go_top');
	var oS_top = document.getElementById('s_top');
	var oR_hidden = document.getElementById('r_hidden');
	window.onscroll = function(){
		var oScrolltop = document.documentElement.scrollTop || document.body.scrollTop;
		var oDown_top = document.documentElement.clientHeight || document.body.clientHeight;
		if(oS_top){
			var oH_top = oS_top.offsetHeight;
			var oW_top = oS_top.offsetWidth;
			oR_hidden.style.height = oH_top + 'px';
			if(oScrolltop > 141){
				oS_top.style.position = 'fixed';
				oS_top.style.top = '0';
				oR_hidden.style.display = 'block';
				if(window.navigator.userAgent.indexOf('MSIE 6.0')!=-1 || window.navigator.userAgent.indexOf('MSIE 7.0')!=-1)
				{
					oS_top.style.position = 'absolute';
					oS_top.style.top = oScrolltop - 141 + 'px';
					oS_top.style.left = 0 + 'px'
				};
			}else{
			oR_hidden.style.display = 'none';
			oS_top.style.position = '';
			}
		} 
		//oR_hidden.style.width = oW_top + 'px';
		
		if(oScrolltop == 0){
			oBcak.style.display = 'none';
			
		}else{
			oBcak.style.display = 'block';
		}
		
		if(window.navigator.userAgent.indexOf('MSIE 6.0')!=-1 || window.navigator.userAgent.indexOf('MSIE 7.0')!=-1)
		{
			oBcak.style.position = 'absolute';
			oBcak.style.top = oScrolltop + (oDown_top - oBcak.offsetHeight) - 10 + 'px';
		}; 
		
	}
	oGotop.onclick = function(){
		document.documentElement.scrollTop = document.body.scrollTop =0;
	}
}