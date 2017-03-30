function TabSwitch(id,ev,num){
	var oTab = document.getElementById(id);
	var oNav = getByClass(oTab,id)[0];
	var oLi = oNav.getElementsByTagName('li');
	var oUl = getByClass(oTab,'rank_ul');
	var i=0;
	var len = oLi.length;
	oLi[num].className+=' active';
	oUl[num].style.display='block';
	for(i=0;i<len;i++)
	{
		oLi[i].index=i;
		oLi[i][ev]=function ()
		{
			for(j=0;j<len;j++)
			{
				oLi[j].className=this.className.replace('active','');
				oUl[j].style.display='none';
			}
			this.className+=' active';
			oUl[this.index].style.display='block';
		};
	}
}