window.onload = window.onresize = width_onload;
function width_onload(){
	var isMaxWidth = true;
	var isMinWidth = true;
	var iWinWidth = document.body.clientWidth || document.documentElement.clientWidth;
	var times = null;
	
    //width judge effect
	if(document.getElementById('wrap')){
		var oLinkCss = document.getElementById('wrap');
		var oBnnerImg = document.getElementById('banner').getElementsByTagName('img');
		var oMenu_more = document.getElementById('menu_more');
		var oMenu_w = document.getElementById('menu_w');
		var oPro_menu = document.getElementById('pro_menu');
		var tm =null;
			 
		oMenu_w.onmouseover = oMenu_more.onmouseover = function(){
			oMenu_more.className = "menu_more menu_moreed";
			 clearTimeout(tm);
			oPro_menu.style.display = "block";
		};
		oMenu_w.onmouseout = function(){
			oMenu_more.className = "menu_more"; 
			tm = setTimeout (function(){
					oPro_menu.style.display = "none";
				},200)
		};
		
		
		left_nav('nav_ul','de_list');  //left nav hover effect
		left_nav('pro_menu','de_list');  //left nav hover effect
		
		floatCodeFn('floating','qr_close');     //right bottom code propmt
		if(iWinWidth > 1200 && isMaxWidth){
			oLinkCss.className = 'wrap wrap_1200';
			isMinWidth = true;
			isMaxWidth = false;
			//index banner
			oBnnerImg[0].src = "http://hn_img/www/tv/img/banner01.jpg";
			
			//prev next
			slideNext({ 
				obj_ul:gtId('slide'),
				oPrev:gtId('prev'),
				oNext:gtId('next'),
				null_prev:gtId('preved'),
				null_next:gtId('nexted'),
				oNum:5 
			});
			slideNext({ 
				obj_ul:gtId('v_slide'),
				oPrev:gtId('v_prev'),
				oNext:gtId('v_next'),
				null_prev:gtId('v_preved'),
				null_next:gtId('v_nexted'),
				oNum:5 
			});
			
			//vedio hover effect
			hosVedio("v_slide");
		}
		if(iWinWidth < 1200 && isMinWidth){
			oLinkCss.className = 'wrap';
			isMaxWidth = true;
			isMinWidth = false;
			oBnnerImg[0].src = "http://hn_img/www/tv/img/banner_980_01.jpg";
			//prev next
			slideNext({ 
				obj_ul:gtId('slide'),
				oPrev:gtId('prev'),
				oNext:gtId('next'),
				null_prev:gtId('preved'),
				null_next:gtId('nexted'),
				oNum:4 
			});
			slideNext({ 
				obj_ul:gtId('v_slide'),
				oPrev:gtId('v_prev'),
				oNext:gtId('v_next'),
				null_prev:gtId('v_preved'),
				null_next:gtId('v_nexted'),
				oNum:4 
			});
			hosVedio("v_slide"); //vedio hover effect
		}
	}else if(document.getElementById('det_w')){
		var oLinkCss = document.getElementById('det_w'); 
		if(iWinWidth > 1200 && isMaxWidth){
			oLinkCss.className = 'det_w det1200';			
			ceiLing ('rt_com','rt_pos');   //xi ding effect
			hosVedio("v_slide");           //vedio hover effect
		}
		if(iWinWidth < 1200 && isMinWidth){
			oLinkCss.className = 'det_w';
			ceiLing ('rt_com','rt_pos');  //xi ding effect
			hosVedio("v_slide");          //vedio hover effect
		}
	}else if(document.getElementById('wrap_img')){ 
		var oLinkCss = document.getElementById('wrap_img');
		if(iWinWidth > 1200 && isMaxWidth){
			oLinkCss.className = 'det_w det1200';
		}
		if(iWinWidth < 1200 && isMinWidth){
			oLinkCss.className = 'det_w';
		}
		proImgFn();
	}else if(document.getElementById('wrap_vedio')){ 
		var oLinkCss = document.getElementById('wrap_vedio');
		if(iWinWidth > 1200 && isMaxWidth){
			oLinkCss.className = 'det_w det1200';
			hosVedio("v_slide");
		}
		if(iWinWidth < 1200 && isMinWidth){
			oLinkCss.className = 'det_w';
			hosVedio("v_slide");
		}
	 }else if(document.getElementById('det_player')){
		var oLinkCss = document.getElementById('det_player'); 
		if(iWinWidth > 1200 && isMaxWidth){
			oLinkCss.className = 'det_w det1200';
			slideNext({ 
				obj_ul:gtId('v_slide'),
				oPrev:gtId('v_prev'),
				oNext:gtId('v_next'),
				null_prev:gtId('v_preved'),
				null_next:gtId('v_nexted'),
				oNum:5 
			});
			hosVedio("v_slide");
		}
		if(iWinWidth < 1200 && isMinWidth){
			oLinkCss.className = 'det_w';
			slideNext({ 
				obj_ul:gtId('v_slide'),
				oPrev:gtId('v_prev'),
				oNext:gtId('v_next'),
				null_prev:gtId('v_preved'),
				null_next:gtId('v_nexted'),
				oNum:4 
			});
			hosVedio("v_slide");
		}
	 }
}


function gtId(el){return document.getElementById(el)}

//left nav hover effect
function left_nav(obj_ul,sClass){
	var aNav_li = getByClass(gtId(obj_ul),"a");
	var aDe_list = getByClass(gtId(obj_ul),sClass);
	var len = aNav_li.length;
	var timer_01 = null,timer_2 = null
	for(var i = 0;i < len;i ++){
		(function(index){ 
			aNav_li[index].onmouseover = function(){
				clearTimeout(aNav_li[index].timer_01);
				aNav_li[index].timer_2 = setTimeout(function(){ 	
					aNav_li[index].className += " active";
					aDe_list[index].style.display = "block";
					if(gtId(obj_ul).id == "nav_ul"){
						switch(index){ 
							case 3:
								aDe_list[index].style.top = "-2px";
								break;
							case 4:
								aDe_list[index].style.top = "-49px";
								break;
							case 5:
								aDe_list[index].style.top = "-96px";
								break;
							case 6:
								aDe_list[index].style.top = "-143px";
								break;
							case 7:
								aDe_list[index].style.top = "-190px";
								break;				
						} 
					}
					if(gtId(obj_ul).id == "pro_menu"){
						switch(index){ 
							case 0:
								aDe_list[index].style.top = "-284px";
								break;
							case 1:
								aDe_list[index].style.top = "-331px";
								break;
							case 2:
								aDe_list[index].style.top = "-378px";
								break;			
						} 
					}
					
				},300);
			};
			
			aNav_li[index].onmouseout = function(){
				clearTimeout(aNav_li[index].timer_2);
				aNav_li[index].timer_01 = setTimeout(function(){ 
					aNav_li[index].className = aNav_li[index].className.replace(/active/,'');
					aDe_list[index].style.display = "none";
				},300);	
			};
			
			aDe_list[index].onmouseover= function(){
				clearTimeout(aNav_li[index].timer_01);
					aNav_li[index].className = 'a active';
					aDe_list[index].style.display = "block";
			};	
			aDe_list[index].onmouseout = function(){
				aNav_li[index].timer_01 = setTimeout(function(){ 
					aNav_li[index].className = aNav_li[index].className.replace(/active/,'');
					aDe_list[index].style.display = "none";
				},300);	
			};
		})(i)				
	}
}	

//index l_judge list
function sliderBanner(obj_parent,obj_circle,obj_ul){
	if(obj_parent){
		var oPlay=document.getElementById(obj_circle);
		var aBtn=oPlay.getElementsByTagName('span');
		var oList_in=document.getElementById(obj_ul);
		var aLi=oList_in.children;
		var now=0;
		var last=0;
		var liWidth=getStyle(aLi[0],'width');
			 oList_in.style.width=liWidth*2+'px';
		for(var i=0;i<aBtn.length;i++){
			aBtn[i].index=i;
			aBtn[i].onclick=function(){
				 now=this.index;
				 tab(); 
			};
		}
		
		function tab(){
			if(now==last)return;
			for(var i=0;i<aBtn.length;i++){
				aBtn[i].className='';	 
			}	      
			aBtn[now].className='active';
			 
			for(var i=0;i<aLi.length;i++){
				 aLi[i].style.display='none'; 
			}
			aLi[last].style.display='block';   
			aLi[now].style.display='block'; 	  
					   
			if(last<now){
				oList_in.style.left=0;
				setMove(oList_in,{left:-liWidth});
			}else{
				oList_in.style.left=-liWidth+'px';    
				setMove(oList_in,{left:0});               
			};
				last=now;                            
		};
				  
		function prev(){
		  now--;
		  if(now==-1)now=aBtn.length-1;
		  tab();
		};
		
		function next(){
		   now++;
		   if(now==aBtn.length)now=0;
		   tab();
		};
		clearInterval(oPlay.timer_007);
		oPlay.timer_007=setInterval(next,3000);
		obj_parent.onmouseover=function(){ 
			clearInterval(oPlay.timer_007);
		};
		obj_parent.onmouseout=function(){ 
			oPlay.timer_007=setInterval(next,3000);
		};
	}
}
//prev next
function slideNext(options){
	//obj_ul,oPrev,oNext,null_prev,null_next
	var obj_ul = options.obj_ul;
	var oPrev = options.oPrev;
	var oNext = options.oNext;
	var null_prev = options.null_prev;
	var null_next = options.null_next;
	var oNum = options.oNum;
	var aimg_li = obj_ul.getElementsByTagName('li');
	var each_li = parseInt(aimg_li[0].offsetWidth);
	var li_len = aimg_li.length;
	var nows = 0;
	obj_ul.style.width = each_li * li_len + 'px';
	obj_ul.style.left = 0;
	
	oNext.onclick = function(){ 
		nows++
			
		oPrev.style.display = 'block';
		null_prev.style.display = 'none';
		
		if(nows >=(li_len*10/oNum-10)/10){
				nows = (li_len*10/oNum-10)/10;
			}
		setMove(obj_ul,{left: -each_li * (oNum*nows)},function(){ 
			if(nows >= li_len/oNum - 1){ 
				oNext.style.display = 'none';
				null_next.style.display = 'block';
			}
		});
	};
	
	oPrev.onclick = function(){
		nows --;
		oNext.style.display = 'block';
		null_next.style.display = 'none';
		if(nows <= 0){
			nows = 0;
		}
		setMove(obj_ul,{left: -each_li * (oNum*nows)},function(){ 
			if(nows <= 0){ 
				oPrev.style.display = 'none';
				null_prev.style.display = 'block';
			}
		});
	};
}
//vedio hover effect
function hosVedio(obj_ul){
	if(gtId(obj_ul)){
		var aimg_li = gtId(obj_ul).getElementsByTagName('li');
		var li_len = aimg_li.length;
		var  sPalyer = getByClass(document,'palyer');
		
			for(var k=0;k< li_len;k++){ 
				(function(index){
					
					aimg_li[index].onmouseover = function(){
						sPalyer[index].style.display = "block";
					};
					aimg_li[index].onmouseout = function(){
						sPalyer[index].style.display = "none";
					};
				})(k)
			}
	}
}
//xi ding effect
function  ceiLing (obj,obj_null){
	var oTop = document.getElementById(obj);
	var oTopNull = document.getElementById(obj_null);
	
	var p = getPos(oTop);
	var timer = null;
	var t = 422;
	
	addEvent(window,'scroll',topTop);
	
	function topTop(){
		var scrollTop = document.documentElement.scrollTop || document.body.scrollTop;
		if(scrollTop > t){
			if(window.navigator.userAgent.indexOf('MSIE 6.0') != -1){
				oTop.style.position = 'absolute';			
				oTop.style.top = scrollTop-422 + 'px';
				oTopNull.style.display = 'block';	
			}else{
				oTop.style.position = 'fixed';
				oTopNull.style.display = 'block';		
			}
		}
		else{
			oTop.style.position = '';
			oTopNull.style.display = 'none';	
		}
	}
	function getPos(obj){
		var l = 0;
		var t = 0;
		
		while(obj){
			l += obj.offsetLeft;
			t += obj.offsetTop;
			obj = obj.offsetParent;
		}
		return {left: l, top: t};
	}
};

//right bottom code propmt
function floatCodeFn(obj_Float,obj_cl){ 
	var oFloat = document.getElementById(obj_Float);
	var oClose = document.getElementById(obj_cl);
	var t = document.documentElement.clientHeight || document.body.clientHeight;
	
	bind(window, 'scroll', oWin1200);
	function oWin1200(){
		var oW = document.documentElement.clientWidth || document.body.clientWidth;
		var scrollTop=document.documentElement.scrollTop||document.body.scrollTop;
		if(window.navigator.userAgent.indexOf('MSIE 6.0') != -1){
			oFloat.style.position = 'absolute';
			oFloat.style.top = scrollTop +550 + 'px';
		};
		if( oW < 1200 ){
			oFloat.className = 'qr_code qr_ewm'
		}else{
			oFloat.className = 'qr_code'
		}
	}
	
	oClose.onclick = function(){
		oFloat.style.display = "none";
	}
	function bind(obj, evname, fn){
		if (obj.addEventListener) {
			obj.addEventListener(evname, fn, false);
		} else {
			obj.attachEvent('on' + evname, function() {
				fn.call(obj);
			});
		}
	}
}

//img prompt effect
function proImgFn(){ 
	var oPro_img = document.getElementById('pro_img').getElementsByTagName("a");
	var oId_iframe = document.getElementById('id_iframe');	
	var oPropt_w = document.getElementById('propt_w');
	var oNext = document.getElementById('next');
	var oPrev = document.getElementById('prev');
	var oProShut = document.getElementById('pro_shut');
	var oPrev_no = document.getElementById('prev_no');
	var oNext_no = document.getElementById('next_no');
	var arr_BigImg = [];
	var now_n = 0;
	
	function get(url) {
		var ret = {};
		if (url.indexOf('?') !== -1) {
			var str = url.split('?')[1];
			var arr = str.split('&');
			var tmp = [];
			console.log(arr);
			for (var i = 0, len = arr.length; i < len; i++) {
			  tmp = arr[i].split('=');
			  ret[tmp[0]] = tmp[1];
			}
		}
		  return ret;
	}
		
	for(var k = 0;k<oPro_img.length;k++){ 
		(function(index){ 
			arr_BigImg[index] = oPro_img[index].href;
			oPro_img[index].onclick = function(){
				now_n = index;
				oPropt_w.style.display = "block"; 
				showNow();
			};
		})(k)
	}
	
	oNext.onclick = function(){ 
		now_n++;
		if(now_n == oPro_img.length){
			now_n = oPro_img.length -1;
			oNext_no.style.display = "block";
			setTimeout(function(){ 
				oNext_no.style.display = "none";
			},2000);
			return;
		}
		showNow();
		window.location.href = window.location.href.split("tv_img/")[0]+arr_BigImg[now_n].split('/tv/')[1];
	};
	oPrev.onclick = function(){ 
		now_n--;
		if(now_n == -1){
			now_n = 0;
			oPrev_no.style.display = "block";
			setTimeout(function(){ 
				oPrev_no.style.display = "none";
			},2000);
		}
		oNext.style.display = "block";
		showNow();
		window.location.href = window.location.href.split("tv_img/")[0]+arr_BigImg[now_n].split('/tv/')[1];
	};
	
	oProShut.onclick = function(){ 
		oPropt_w.style.display = "none"; 
	};
	function showNow(){
		oId_iframe.src = "http://www.jj.cn" + '/tv/'+arr_BigImg[now_n].split('/tv/')[1];	
	}
	get(window.location.href);
			
	function showUil2(){
		if(get(window.location.href).ulr){
			for(var i = 0; i<arr_BigImg.length; i++){
				if('/tv/'+arr_BigImg[i].split('/tv/')[1] == get(window.location.href).ulr){
					now_n = i;
				}
			}
			oPropt_w.style.display = "block";
			oId_iframe.src = "http://www.jj.cn" + get(window.location.href).ulr;
		}
	}
	showUil2();
}

//bind effect
function addEvent(obj,sEv,fn){
	if(obj.attachEvent){
		 obj.attachEvent('on'+sEv,fn);
	 }else{
		  obj.addEventListener(sEv,fn,false);
	 }
 };
//obj_ul,oPrev,oNext,null_prev,null_next	
//slideNext(gtId('slide'),gtId('prev'),gtId('next'),gtId('preved'),gtId('nexted'));

function getByClass(oParent,sClass){
	var aEle = oParent.getElementsByTagName('*');
	var aResult = [];
	var re = new RegExp('\\b'+sClass+'\\b', 'i');
	
	for(var i = 0; i<aEle.length;i++){
		if(aEle[i].className.search(re) != -1){
			aResult.push(aEle[i]);
		}
	}
	return aResult;
}

function getStyle(obj, name){
	var value=obj.currentStyle?obj.currentStyle[name]:getComputedStyle(obj, false)[name];

	if(name=='opacity'){
		return Math.round(parseFloat(value)*100);
	}
	else{
		return parseInt(value);
	}
}

function setStyle(obj, name, value){
	if(name=='opacity'){
		obj.style.filter='alpha(opacity:'+value+')';
		obj.style.opacity=value/100;
	}
	else{
		obj.style[name]=value+'px';
	}
}
//js move
function setMove(obj,json,fnEnd){
   clearInterval(obj.timer);
   obj.timer=setInterval(function(){ 
	   var isReach=true;
		for(var name in json){ 
			   if(name=='opacity'){
					var cur=Math.round(parseFloat(getStyle(obj,name))*100);
			   }
			   else {      
					  var cur=parseInt(getStyle(obj,name));
			   }
			 var iSpeed=(json[name]-cur)/8;
				  iSpeed=iSpeed>0?Math.ceil(iSpeed):Math.floor(iSpeed);
					 
			  if(cur!=json[name]){
				  isReach=false;
			  }
		  
			  if(name=='opacity'){
				  obj.style.filter='alpha(opacity:'+(cur+iSpeed)+')';
				  obj.style.opacity=(cur+iSpeed)/100;
			  }else{
				  obj.style[name]=parseInt(cur+iSpeed)+'px';
			   }
		 }
		 
		 if(isReach){
			isReach=true;
			 clearInterval(obj.timer);
			 if(fnEnd){
				 fnEnd(); 
			 }
		 }
   },30); 
}
