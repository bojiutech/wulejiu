//获取当前元素的class
function getByClass(oParent,sClass){
	var aEle = oParent.getElementsByTagName('*');
	var aResult = [];
	var re=new RegExp('\\b'+sClass+'\\b', 'i');
	
	for(var i=0; i<aEle.length;i++){
		if(aEle[i].className.search(re)!=-1){
			aResult.push(aEle[i]);
		}
	}
	return aResult;
}

//'获取'当前元素的样式
function getStyle(obj,name) {
	var values=obj.currentStyle?obj.currentStyle[name]:getComputedStyle(obj,false)[name];
	if(name=='opacity') {
		return Math.round(parseFloat(values)*100);  
	}else {
		return parseInt((values)); 
	}   
}

//'设置'当前元素的样式   
function setStyle(obj,name,value) {
   if(name=='opacity') {
	  obj.style.filter='alpha(opacity:'+value+')';
	  obj.style.opacity=value/100;
    }
    obj.style[name]=value+'px';  
}

//CSS3运动框架
Array.prototype.indexOf=function (n){
	for(var i=0;i<this.length;i++){
		if(this[i]==n)return i;
	}
	return -1;
};

function setStyle3(obj, name, value){
	//transform、transition、borderRadius、boxShadow、textShadow
	var aCss3=['transform', 'transition', 'borderRadius', 'boxShadow', 'textShadow'];
	
	if(aCss3.indexOf(name)!=-1){
		obj.style['Webkit'+name.charAt(0).toUpperCase()+name.substring(1)]=value;
		obj.style['Moz'+name.charAt(0).toUpperCase()+name.substring(1)]=value;
		obj.style['ms'+name.charAt(0).toUpperCase()+name.substring(1)]=value;
		obj.style['O'+name.charAt(0).toUpperCase()+name.substring(1)]=value;
		obj.style[name]=value;
	}else{
		obj.style[name]=value;
	 }
}

//css3运动框架
function startMove3(obj, json, fnEnd){
	function fnInnerEnd(){
		if(fnEnd)fnEnd();
		obj.removeEventListener('webkitTransitionEnd', fnInnerEnd, false);
		obj.removeEventListener('mozTransitionEnd', fnInnerEnd, false);
		obj.removeEventListener('msTransitionEnd', fnInnerEnd, false);
		obj.removeEventListener('oTransitionEnd', fnInnerEnd, false);
		obj.removeEventListener('transitionend', fnInnerEnd, false);
	}
	
	for(var i in json){
		setStyle3(obj, i, json[i]);
	}
	
	obj.addEventListener('webkitTransitionEnd', fnInnerEnd, false);
	obj.addEventListener('mozTransitionEnd', fnInnerEnd, false);
	obj.addEventListener('msTransitionEnd', fnInnerEnd, false);
	obj.addEventListener('oTransitionEnd', fnInnerEnd, false);
	obj.addEventListener('transitionend', fnInnerEnd, false);
}

//js运动框架万能版
function startMove2(options)
{
	//obj, cur_json, target_json, fnSet, fnEnd, type
	
	var obj=options.obj;
	var cur_json=options.cur;
	var target_json=options.target;
	var fnSet=options.fnSet;
	var fnEnd=options.fnEnd;
	var type=options.type;
	
	if(!type)type='buffer';
	
	var speed_json={};
	
	for(var i in cur_json){
		speed_json[i]=(target_json[i]-cur_json[i])/100;
	}
	
	clearInterval(obj.timer);
	obj.timer=setInterval(function (){
		var bStop=false;
		
		for(var i in target_json)
		{
			var cur=cur_json[i];
			
			if(type=='buffer')
			{
				var speed=(target_json[i]-cur)/6;
				speed=speed>0?Math.ceil(speed):Math.floor(speed);
			}
			else if(type=='linear')	
			{
				var speed=speed_json[i];
			}
			
			cur_json[i]+=speed;
			
			if(cur_json[i]!=target_json[i]){
				bStop=true;
			}
		}
		
		fnSet(obj, cur_json);
		
		if(bStop==false){
			clearInterval(obj.timer);
			fnEnd && fnEnd();
		}
	}, 30);
}

//'获取'当前元素的样式运动版
function getStyle2(obj,name) {
	if(obj.currentStyle){
		return  obj.currentStyle[name];
	}
	else {
		return getComputedStyle(obj,false)[name];
	 } 
}

//js运动框架易用版
function setMove(obj,json,fnEnd){
   clearInterval(obj.timer);
   obj.timer=setInterval(function(){ 
   
	   //if all reach is true
	   var isReach=true;
	   
		for(var name in json){ 
			   if(name=='opacity'){
					var cur=Math.round(parseFloat(getStyle2(obj,name))*100);
			   }
			   else {      
					  var cur=parseInt(getStyle2(obj,name));
			   }
			 var iSpeed=(json[name]-cur)/8;
				  iSpeed=iSpeed>0?Math.ceil(iSpeed):Math.floor(iSpeed);
					 
			  if(cur!=json[name]){  //if not to reach

				  isReach=false;   //is false 
			  }
		  
			  if(name=='opacity'){
				  obj.style.filter='alpha(opacity:'+(cur+iSpeed)+')';
				  obj.style.opacity=(cur+iSpeed)/100;
			  }else{
				  obj.style[name]=(cur+iSpeed)+'px';
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





