var www_jj_cn_pub = {
	gat_id: function(id){
		return document.getElementById(id);	
	},
	add_event: function addEvent(obj,s_ev,fn){
		if(obj.attachEvent){
			obj.attachEvent('on'+s_ev,fn);
		}else{
			obj.addEventListener(s_ev,fn,false);
		}
	 },
	get_by_class: function(oParent,sClass){
		var arr = [];
		var aEle = oParent.getElementsByTagName('*');
		var re = new RegExp('\\b'+sClass+'\\b');
		
		for(var i=0;i<aEle.length;i++){
			if( re.test(aEle[i].className) ){
				arr.push( aEle[i] );
			}
		}
		return arr;
	},
	but_wm2: function(id,wm){
		//var timer = null;
		id.onmouseover = function(){
			clearTimeout(id.timer);	
			clearTimeout(id.timer2);			
			id.timer2 = setTimeout(function (){
				wm.style.display = "block";
			}, 250);
		}
		id.onmouseout = function(){
			clearTimeout(id.timer);		
			clearTimeout(id.timer2);
			id.timer = setTimeout(function (){
				wm.style.display = "none";
			}, 50);
		}		
	},
	but_wm2_fn: function(){
		this.but_wm2(this.gat_id("but_wm2_and"),this.gat_id("wm2_and"));
		this.but_wm2(this.gat_id("but_wm2_iph"),this.gat_id("wm2_iph"));
		this.but_wm2(this.gat_id("but_wm2_ipad"),this.gat_id("wm2_ipad"));
	},
	setStyle3: function(obj, name, value){
		var aCss3=['transform', 'transition', 'borderRadius', 'boxShadow', 'textShadow'];
		if(aCss3.indexOf(name)!=-1){
			obj.style['Webkit'+name.charAt(0).toUpperCase()+name.substring(1)]=value;
			obj.style['Moz'+name.charAt(0).toUpperCase()+name.substring(1)]=value;
			obj.style['ms'+name.charAt(0).toUpperCase()+name.substring(1)]=value;
			obj.style['O'+name.charAt(0).toUpperCase()+name.substring(1)]=value;
			obj.style[name] = value;
		}else{
			obj.style[name]=value;
		}
	},
	is_max_width: true,
	is_min_width: true,
	page_max_width: 1200,		
	min_max_width: function (){
		if(document.getElementById('min_max_width')){
			var iWinWidth = document.body.clientWidth || document.documentElement.clientWidth;
			var iWinHeight =  document.documentElement.clientHeight || document.body.clientHeight;	
			var oBorWidth = document.getElementById('min_max_width');
			if((iWinWidth > 1200 || iWinHeight < 760) && this.is_max_width){
				oBorWidth.className = 'max_1200';
				this.is_min_width = true;
				this.is_max_width = false;
				this.page_max_width = 1200;
			}
			if((iWinWidth <= 1201 || iWinHeight <= 761) && this.is_min_width){
				oBorWidth.className = 'min_980';
				this.is_max_width = true;
				this.is_min_width = false;
				this.page_max_width = 980;
			}
		}
	}
	/*,//ÏÂÔØÖÐÐÄÓÃµÄ£¬Ö®ºóÒªÉ¾³ýÁË
	dow_get_gameicon: function(id){
		var box_id = document.getElementById(id);
			game_list = document.getElementsByTagName("li");
			len = game_list.length;
			_this = this;
		for(var i = 0; i < len; i++){
			game_list[i].onmouseover = function(){
				_this.get_by_class(this, "wm")[0].style.display = "block";
			}
			game_list[i].onmouseout = function(){
				_this.get_by_class(this, "wm")[0].style.display = "none";
			}
		}
	}*/
}
//±³¾°ÂÖ²¥
function www_jj_cn_pub_lenbo(){
	this.obj = null;
	this.timerr = null;
	this.now = 0;
	this.index = 1;
}
www_jj_cn_pub_lenbo.prototype = {
	init: function(nav, bjimg, jjnavhot){
		var _this = this;
		this.outImgUl = document.getElementById(nav);
		this.imgChildren = this.outImgUl.children;
		this.obj = document.getElementById(bjimg);
		this.jjnavhot = document.getElementById(jjnavhot);
		this.aImg = this.obj.children;
		this.len = this.aImg.length;
		for(var i=0; i < this.len; i++){
			var oLi = document.createElement('li');
			oLi.index = i;
			oLi.onclick = function(){
				_this.now = this.index;
				_this.tab_but();
			}
			this.outImgUl.appendChild(oLi);
		}
		this.imgChildren[this.now].className = "hov";
		this.aImg[this.now].style.zIndex = this.index;
		this.aImg[this.now].style.opacity = '1';	
		this.slider();
	},
	slider: function(){
		var _this = this;
		this.timerr = setInterval(function(){
			_this.now++;
			_this.tab();
		}, 6000);
		
		this.jjnavhot.onmouseover = function(){
			clearInterval(_this.timerr);
		}
		this.jjnavhot.onmouseout = function(){
			_this.timerr = setInterval(function(){
				_this.now++;
				_this.tab();
			}, 6000);
		}
	},
	tab: function(){
		++this.index		
		if(this.now == -1){
			this.now = this.len-1;
		};
		if(this.now == this.len){
			this.now = 0;
		};
		this.tab_but();
	},
	tab_but: function(){
		for(var i=0; i<this.len; i++){
			this.imgChildren[i].className = ""
			this.aImg[i].style.opacity = '0';
			this.aImg[i].style.zIndex = '0';
		}
		this.aImg[this.now].style.zIndex = this.index;		
		this.aImg[this.now].style.opacity = '1';	
		this.imgChildren[this.now].className = "hov"	
	}
}
//±³¾°ÂÖ²¥
//var top_bg_lenbo = new www_jj_cn_pub_lenbo();
//top_bg_lenbo.init("hot_img_nav", "jj_hot_img", "jj_nav_hot")
//±³¾°ÂÖ²¥end
www_jj_cn_pub.min_max_width();
www_jj_cn_pub.add_event(window,'resize',function(){
	www_jj_cn_pub.min_max_width();
});



