
 $(function () {
	 
	    //***首页广告切换***//	
		var $con = $('#w_banner'), $box = $con.find('#w_banner_img'), $btns = $con.find('#w_banner_num'), i = 0
		var autoChange = function () {
			i += 1;
			if (i === 5) { i = 0; }
			$btns.find('a:eq(' + i + ')').addClass('focus').siblings().removeClass('focus');
			var curr = $box.find('a:eq(' + i + ')'), prev = curr.siblings();
			prev.stop(true, true).fadeOut(0);
			curr.stop(true, true).fadeIn(500);

		}, loop = setInterval(autoChange, 4000);
		$con.hover(function () {
			clearInterval(loop);
		}, function () {
			loop = setInterval(autoChange, 4000);
		});
		$btns.find('a').mouseover(function () {
				i = $(this).index() - 1;
			    autoChange();	
		});
		//***首页左部广告切换***//	
		var aSlidePagew = $('.slide-nav-box');
		var aSlideCon = $('.slide-box a');
		var iSize = aSlideCon.size();
		var iNow = 0;
		var timer = null;
		aSlideCon.eq(0).show();
		for (var i = 1; i <= iSize; i++) {
		if (i == 1) {aSlidePagew.append('<a href="javascript:void(0)" class="active"></a>');}
		else {aSlidePagew.append('<a href="javascript:void(0)"></a>');}
		}
		if(iSize==1){
			aSlidePagew.html('');
			}
		
		var aSlidePage = $('.slide-nav-box a');
		aSlidePage.each(function(index){
			$(this).mouseover(function(){
				iNow = index;
				slideRun()
			})
		})
		function slideRun(){
			aSlidePage.removeClass('active');
			aSlidePage.eq(iNow).addClass('active');
			aSlideCon.stop();
			aSlideCon.eq(iNow).siblings().fadeOut(500);
			aSlideCon.eq(iNow).css({opacity:1}).fadeIn(1000);
		}
		autoRun();
		function autoRun(){
			timer = setInterval(function(){
				iNow++;
				if(iNow>iSize-1) iNow=0;
				slideRun();
			},4000)
		};
		$('#w_l_banner').hover(function(){
			clearInterval(timer);
		},function(){
			autoRun();
		})
	
	//全部游戏	
	$('#all_game').hover(function() {
		$('#allgame_wrap').show();
	},function(){
		$('#allgame_wrap').hide();
	});	
	
	$('#w_ziwul>li>a').mouseover(function(){
	 var title = $(this);
	 $(this).addClass('current').parent().siblings().find('a').removeClass('current');				
	 $("#w_games_list").find("ul").hide();
	 $("#w_games_list").find("#" + title.attr("data")).show();
	 
	 });
	 
	 //开服列表
	 $('#w_slw_t>li>a').mouseover(function(){
	 var title = $(this);
	 $(this).addClass('current').parent().siblings().find('a').removeClass('current');				
	 $("#w_swrap_c").find("div").hide();
	 $("#w_swrap_c").find("#" + title.attr("data")).show();
	 
	 });
	 
	  $('#w_swrap_c div>table>tbody>tr').live({
		 'mouseover':function(){$(this).addClass('w_trhover');},
	 	'mouseout':function(){$(this).removeClass('w_trhover');}
	 })
	
	//推荐游戏
	 $('.w_game div.w_game_img ,.w_behalf_img').hover(function(){
		 var _animatep=$(this).find("p");
			   _animatep.stop().animate({
				   bottom:0+'px',
				   opacity:1
				   },300) 
	 },function(){
		  var _animatep=$(this).find("p");
			   _animatep.stop().animate({
				   bottom:-26+'px',
				   opacity:0
				   },300)
		 });
		 
	//热门网页游戏
	 $('.w_hotgame_list div.w_hotgame' ).hover(function(){
		 $(this).addClass("w_hotgameborder");
	 },function(){
		  $(this).removeClass("w_hotgameborder");
		 });
		 
	//全部游戏
	 $('.w-allg-show ul li').hover(function(){
		 $(this).addClass("shadowborder");
	 },function(){
		  $(this).removeClass("shadowborder");
		 });
	//注册页面切换 
	$('#yhm-register').click(function(){
		 var title = $(this);
		 $(this).addClass('yhm-register2').parent().siblings().find('a').removeClass('phone-register2');				
		 $("#hz-reg-right").find("div.yhm-reg-content").fadeOut(0);
		 $("#hz-reg-right").find("div#register-fs1").fadeIn(500); 
	 });
	 $('#phone-register').click(function(){
		 var title = $(this);
		 $(this).addClass('phone-register2').parent().siblings().find('a').removeClass('yhm-register2');				
		 $("#hz-reg-right").find("div.yhm-reg-content").fadeOut(0);
		 $("#hz-reg-right").find("#register-fs12").fadeIn(500); 
	 });

 //***被盗中心 提交申请的判断***/
	    var msg = "";
        var reg = /[^\u4e00-\u9fa5]/;//验证中文的正则表达式
		var num = /^[1]+[3,5,8]+\d{9}$/;//验证手机的正则表达式
		var emal = /^\w+((-\w+)|(\.\w+))*\@[A-Za-z0-9]+((\.|-)[A-Za-z0-9]+)*\.[A-Za-z0-9]+$/; //验证邮箱的正则表达式
		var gamezh = /[^\w]/;//验证游戏账号
		$("input.hz_txt,textarea.textarea_txt,select").blur(function(){
			var $parent = $(this).parent();

			var rig_img = "<span class='addHtmlCode2' style='float:left; margin-top:4px;'><img src='/Public/new/images/hz_error_dui.jpg' width='16' height='16' /></span>";
            $parent.find(".addHtmlCode,.addHtmlCode2").remove();
			if ($(this).is("#w-pdname")){  //真实姓名

					if($(this).val() == "" || reg.test($(this).val())){
				    msg = "请输入真实姓名";
                    	$parent.append("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
					}else{
						$parent.append(rig_img);
					}
				}
				
				
			if ($(this).is("#w-pddhnum")){  //手机号码
					if($(this).val() == "" || !num.test($(this).val())){
						msg = "请输入正确联系手机";
                    	$parent.append("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
					}else{
						$parent.append(rig_img);
					}
				}
				
				
			if ($(this).is("#w-pdemail")){  //联系邮箱 
					if($(this).val() == "" || !emal.test($(this).val())){
						msg = "请输入正确的邮箱地址";
						$parent.append("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
					}else{
						$parent.append(rig_img);
					}
				}
				
			if ($(this).is("#w-pdzsname")){  //游戏账号 
					if($(this).val() == "" || gamezh.test($(this).val())){
						msg = "请输入真实帐号";
						$parent.append("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
					} else if($(this).val().length < 4 || $(this).val().length > 16){
						 msg = "账号只能是4到16位非中文字符";
						 $parent.append("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
					}else{
						$parent.append(rig_img);
					}
				}
			
			if ($(this).is("#w-pdgameId")){  //游戏 
				if($(this).val() == ""){
					msg = "请选择游戏 ";
					$parent.append("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
				}else{
					$parent.append(rig_img);
				}
			}
			
			if ($(this).is("#w-pdsevId")){  //游戏服务器 
				if($(this).val() == ""){
					msg = "请选择游戏服务器 ";
					$parent.append("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
				}else{
					$parent.append(rig_img);
				}
			}
				
			if ($(this).is("#w-pdjsname")){  //角色名 
					if($(this).val() == ""){
						msg = "请输入角色名";
						$parent.append("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
					}else{
						$parent.append(rig_img);
					}
				}
				
			if ($(this).is("#log_city_1")){  // 常用登录地点1
				if($(this).val() == "" ){
					msg = "请选择帐号常登录地点";
					$(this).after("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
				}else{
					$parent.append(rig_img);
				}
			}
			
			if ($(this).is("#appeal_regdate")){  // 注册时间
				if($(this).val() == "" ){
					msg = "请选择账号注册时间";
					$(this).after("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
				}else{
					$parent.append(rig_img);
				}
			}
			
			if ($(this).is("#reg_city")){  // 注册地点
				if($(this).val() == "" ){
					msg = "请选择帐号注册地点";
					$(this).after("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
				}else{
					$parent.append(rig_img);
				}
			}
				
			if ($(this).is("#w-csms")){  // 帐号遇到的情况 
					if($(this).val() == "" ){
						msg = "请描述帐号遇到的情况";
						$parent.append("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
					}else{
						$parent.append(rig_img);
					}
				}
				
		    if ($(this).is("#w-yzm")){  // 验证码 
					if($(this).val() == "" ){
						msg = "请输入验证码";
						$(this).after("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
					}
					/*else{
						$parent.after("<span class='addHtmlCode2' style='float:left; margin-top:4px;'><img src='images/hz_error_dui.jpg' width='16' height='16' /></span>");
						}*/
				}
	
			if ($(this).is("#w-servernum")){  // 服务编号 
					if($(this).val() == "" ){
						msg = "请输入服务编号";
						$(this).after("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
					}else{
						$parent.append(rig_img);
					}
				}
				
			if ($(this).is("#w-serpaw")){  // 查询密码 
					if($(this).val() == "" ){
						msg = "请输入查询密码";
						$(this).after("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
						}
					/*else{
						$parent.after("<span class='addHtmlCode2' style='float:left; margin-top:4px;'><img src='images/hz_error_dui.jpg' width='16' height='16' /></span>");
						}*/
				}
			if($(this).is("#w-ctype")){//投诉类型
				if($(this).val() == "" ){
					msg = "请选择投诉类型";
					$(this).after("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
				}else{
					$parent.append(rig_img);
				}
			}
			if ($(this).is("#w-bgjy")){  // 宝贵建议 
					if($(this).val() == "" ){
						msg = "请输入您的内容";
						$parent.append("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
					}else{
						$parent.append(rig_img);
					}
				}
			
			}).keyup(function() {
                    $(this).triggerHandler("blur");
			}).focus(function() {
					$(this).triggerHandler("blur");
				    });	

		$("#w-sumbit").click(function() {
			$("input.hz_txt,textarea,select").trigger("blur");  //提交前再触发 blur 事

			if($("#hz_tongyi").is(":checked"))              //判断是否选中
			{
				$(".hz_p1").find(".addHtmlCode").remove();
			}else{
				msg = "请勾选65游戏平台保证书协议";
				$(".hz_p1").find(".addHtmlCode").remove();
				$(".hz_p1").append("<span class='addHtmlCode' style='color: #FC0303;'>" + msg + "</span>");
				
				}
			var errorNum = $("span[class='addHtmlCode']").length;
			if (errorNum > 0) {
				return false;
			}
		});
			
});
/*---------更多推荐游戏滚动----*/
function DY_scroll(wraper, prev, next, img, speed, or) {
            var wraper = $(wraper);
            var prev = $(prev);
            var next = $(next);
            var img = $(img).find('ul');
            var w = img.find('li').outerWidth(true);
            var s = speed;
            next.click(function() {
                if (!img.is(":animated")) {
                    img.animate({ 'margin-left': -w }, function() {
                        img.find('li').eq(0).appendTo(img);
                        img.css({ 'margin-left': 0 });
                    });
                }
            });
            prev.click(function() {
                if (!img.is(":animated")) {
                    img.find('li:last').prependTo(img);
                    img.css({ 'margin-left': -w });
                    img.animate({ 'margin-left': 0 });

                }

            });
            if (or == true) {
                ad = setInterval(function() { next.click(); }, s * 1000);
                wraper.hover(function() { clearInterval(ad); }, function() { ad = setInterval(function() { next.click(); }, s * 1000); });

            }
 }
 
/*---------login登录input判断placeholder----*/
$(function(){
	if(!placeholderSupport()){  
		$('.w_logininput').focus(function() {
			var input = $(this);
			if (input.val() == input.attr('placeholder')) {
				input.val('').css({color:'#333'});
				input.removeClass('placeholder');
			}
		}).blur(function() {
			var input = $(this);
			if (input.val() == '' || input.val() == input.attr('placeholder')) {
				input.addClass('placeholder').css({color:'#a9a9a9'});
				input.val(input.attr('placeholder'));
			}
		}).blur();
	};
	})
	function placeholderSupport() {
		return 'placeholder' in document.createElement('input');
}


jQuery.fn.center = function () {
	this.css("top", ( $(window).height() - this.height() ) / 2+$(window).scrollTop() + "px");
	this.css("left", ( $(window).width() - this.width() ) / 2+$(window).scrollLeft() + "px");
}	//弹出层
function $popup(arg1, arg2) {
	var $arg1 = arg1;
	var $arg2 = arg2;
	var $pLeft = ($(window).width() - $($arg1).width()) / 2 + $(window).scrollLeft();
	var $pTop = ($(window).height() - $($arg1).height()) / 2 + $(window).scrollTop();
	$pTop = $pTop > 0 ? $pTop : 40;
	if($.browser.msie && parseInt($.browser.version) == 6) {
		$("html,body").css("overflow", "hidden");
	}
	if ($("body").hasClass("gray")) {}
	else{
		$("<div class='gray'></div>").appendTo($("body")).height($(document).height()).fadeTo("fast", 0.4);
		}
	
	$($arg1).css({
		display : 'block',
		position : 'absolute',
		left : $pLeft,
		top : $pTop,
		zIndex : 10000
	});

	$($arg2 + ',' + ".gray").click(function() {
		$($arg1).hide();
		if($.browser.msie && parseInt($.browser.version) == 6) {
			$("html,body").css("overflow", "")
		};
		$(".gray").fadeOut(500, cb);
		function cb() {
			$(this).remove();
		}

		return false;
	});
	//窗口大小变化时调用
	$(window).bind('scroll resize', function(event) {
		var $pLeft = ($(window).width() - $($arg1).width()) / 2 + $(window).scrollLeft();
		var $pTop = ($(window).height() - $($arg1).height()) / 2 + $(window).scrollTop();
		$($arg1).animate({
			left : $pLeft,
			top : $pTop
		}, {
			duration : 500,
			queue : false
		})
	})
}

$(function() {
    if ($("#bill_index").length > 0) {
        var speed = 500;
		var margintop=($(window).height()/2-135)+"px";
        var menuYloc = $("#bill_index").offset().top;
		$('#bill_index').css("top",margintop);
        $(window).scroll(function() {  //当页面滚动时执行
            var offsetTop = menuYloc + $(window).scrollTop() + "px";
            $("#bill_index").animate({ top: offsetTop }, { duration: speed, queue: false });

        });
        $(window).scroll();
    }
});



$(function(){
	//返回顶部
	 if ($("#goTopBtn").length > 0){
	   $(window).scroll(function(){
				if($(window).scrollTop()>122){
					$("#goTopBtn").show();
	
				}else{
					$("#goTopBtn").hide();
				}
			});
		$("#goTopBtn").click(function(){
			$("body,html").animate({scrollTop:0},300);
			return false;
		});
		}
	
    $('.sq-cwechat-corner a.sq-cwechat-corner-wechat').click(function(){
		$popup('#weixin-wrap', '#close-weixin');
	});
});




$('#q_rem,.q_rem').click(function(){
	$('#q_rem').toggleClass('w_keep_pasw_check');
})
$('#r_rem,.r_rem').click(function(){
	$('#r_rem').toggleClass('w_keep_pasw_check');
})
/*$(document).ready(function() {
	$("#quicklogin").click(function() {
		$popup('#s-login-wrap', '#close-ql');
		$("#s-user-login").click();
	});
	$("#quickregister").click(function() {
		$popup('#s-login-wrap', '#close-ql');
		$("#s-user-register").click();
	});
	
	$('#s-user-login').click(function(){
		 $(this).addClass('current').parent().siblings().find('a').removeClass('current');				
		 $("#s-login-content").find("#s-user-register2").hide();
		 $("#s-login-content").find("#s-user-login2").fadeIn(300);
		 $("#s-login-wrap").center(); 
		 
		 });
	$('#s-user-register').click(function(){
		 $(this).addClass('current').parent().siblings().find('a').removeClass('current');				
		 $("#s-login-content").find("#s-user-login2").hide();
		 $("#s-login-content").find("#s-user-register2").fadeIn(300);
		 $("#s-login-wrap").center();
		 });
	
});*/

//新页游开服表
$(function(){
    $('.new_game ul li').hover(function(){
	    $(this).addClass('current');
	},function(){
	    $(this).removeClass('current');
	});
	
	$('.new_game ul li:last .ngl_line').addClass('ngl_no');
	$('.new_game ul li:last').css("border","none");
	
})

 
 
var pagesize=7,pagecount=1,pageLen
    var obj,j
	$(function(){
	    obj = $('.new_game ul li');
		j = obj.length;
		var pageno = $('#pageno');
		var page= $('#page');
		pageLen=Math.ceil(j/pagesize);
		var pagel = j%7;
		pageno.html(pageLen);
		page.html(pagecount);
		N(0);
	})
	
	function resetStyle(){
	    for (var i=0;i<j;i++){
		    obj[i].style.display="none";
		    if((i+1)%7==0){
			    obj[i].className="lihidden";
			}
		    $('.lihidden .ngl_line').addClass('ngl_no');
		    $('.lihidden').css("border","none");
		}
	}
	
	function N(k){
	    if (k>=0 && pagecount>=pageLen ||k<0 && pagecount<=1)return
        pagecount+=k;
        resetStyle();
	    page.innerHTML=pagecount;
        for (var i=(pagecount-1)*pagesize;i<=pagecount*pagesize-1;i++){
		    if (obj[i]){
		        obj[i].style.display="";
		    }
		}
	}


