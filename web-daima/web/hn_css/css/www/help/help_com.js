window.onload = window.onresize = left_nav;
function left_nav(){
	if(document.getElementById('help_left')){
		var oLeft = document.getElementById('help_left');
		var aLi = oLeft.getElementsByTagName('li');
		for(var i=0;i<aLi.length;i++){
			aLi[i].onmouseover = function(){
				this.className == ''? this.className = 'line':this.className;
			}
			aLi[i].onmouseout = function(){
				this.className == 'line'? this.className = '':this.className;
			}
		}
		
	}	
	var oL = document.getElementById('left');
	var oRight = document.getElementById('help_right');
	if(oL.offsetHeight < oRight.offsetHeight){
		oL.style.height = oRight.offsetHeight + 'px';
	}
}
function left_tow_nav(ih3,ili){
	var oL = document.getElementById('tow_left');
	var aH = oL.getElementsByTagName('h3');
	var aUl = oL.getElementsByTagName('ul');
	aH[ih3].className = 'up';
	aUl[ih3].style.display = 'block';
	aUl[ih3].getElementsByTagName('li')[ili].className = 'active';
	for(var j = 0; j<aH.length; j++){
		aH[j].index = j;
		aH[j].onclick = function(){
			for (i=0;i<aH.length;i++){
			if(i != this.index)	{
				aH[i].className = 'down';
				aUl[i].style.display = 'none';
			}
			}
			if(this.className == 'down'){
				this.className = 'up';
				aUl[this.index].style.display = 'block'
			}else{
				this.className = 'down';
				aUl[this.index].style.display = 'none'
			}
		}
	}
}