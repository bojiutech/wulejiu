var domain = {user:'http:\/\/my.65.com\/',platform:'http:\/\/www.65.com\/',api:'http:\/\/api.65.com\/',pic:'http:\/\/hnlogin\/platform\/'};
var timeout = null;
var referer =getUrlParam("referer");//百度
$(function(){
	head.init.log_status();
	$('.t-moregames').mouseover(function(){head.init.load_game_start(this);}).mouseout(function(){head.init.load_game_stop(".t-moregames");});	
	$('.pop-g-box').mouseover(function(){clearTimeout(timeout);$(".t-moregames").addClass('t-moregames-focus');$('.pop-g-box').show();}).mouseout(function(){head.init.load_game_stop(".t-moregames");});
	$('#sethome').click(function(){head.init.SetHome(this,window.location);})
	$('#bookmark').click(function(){head.init.AddFavorite(window.location,document.title);})
	
	$('#loginBtn').bind("click",function(){head.user_info.login();});
	$('#tj-top-log').bind("click",function(){head.tool.top_login()});
	$('#tj-top-reg').bind("click",function(){head.tool.top_register()});
	
	document.onkeydown=function(event){ 
		e = event ? event :(window.event ? window.event : null); 
		if(e.keyCode==13&&$("#s-login-wrap").is(":visible")&&$("#s-user-login2").is(":visible")){ 
			show_login();
			return false;
		} 
		else if(e.keyCode==13&&$("#s-login-wrap").is(":visible")&&$("#s-user-register2").is(":visible")){
			$("#zc_submit_btn").click();
			return false;
			}
		else if(e.keyCode==13&&$(".w_login_fot").is(":visible")){ 
			head.user_info.login();
			return false;
		}
	} 
	
	
	$("#quicklogin").click(function() {fast_login();});
	$("#quickregister").click(function() {fast_reg();});
	
	$('.w_keep_password').click(function(){
	  if($(this).hasClass('w_keep_pasw_check')){$(this).removeClass('w_keep_pasw_check')}
	  else{$(this).addClass('w_keep_pasw_check');}
     })
	
})

var head = {
	'init':{
		'log_status':function(){
			$('.w_login_late').css('display','none');
			$('.w_login_fot').css('display','none');
			$.getJSON(domain.api+'65user/login_status.php?callback=?',function(res){
				if(res.code=='-1'){
					if(referer=='65_bd'){
						fast_reg();//百度
					}
					$("#nav dd:eq(5)").find("a").attr("href","http://my.65.com/login.html");
					$(".w-tc3,.w-tc4").attr("href","http://my.65.com/login.html");
					if(location.href.indexOf("www.65.com/service")>=0){
						$(".nav_wrap a:eq(1)").attr("href","http://my.65.com/login.html");
						$("#hz_serc a:eq(1)").attr("href","http://my.65.com/login.html");
					    $("#hz_serc a:eq(2)").attr("href","http://my.65.com/login.html");
					}
					if(location.href.indexOf("my.65.com")>=0){
						window.location.href = "http:\/\/my.65.com\/login.html?url="+location.href;
					}
					if(location.href.indexOf("gift.html")>=0){
						$("#search_jg li:eq(2)").hide();//隐藏积分商城“我能兑换”
					}
					$('.t-loged').css('display','none');
					$('.t-log').css('display','inline-block');
					$('.w_login_late').css('display','none');
					$('.w_login_fot').css('display','block');
				}else{
					if(location.href.indexOf("www.65.com/service")>=0){
						$(".nav_wrap a:eq(1)").attr("href","http://my.65.com/userprotect.html");
						$("#hz_serc a:eq(1)").attr("href","http://my.65.com/userprotect.html?action=phone");
					    $("#hz_serc a:eq(2)").attr("href","http://my.65.com/userprotect.html");
					}
					head.user_info.head(res.data);
					head.user_info.info();
					if(location.href.indexOf("gift.html")>=0){
						$("#search_jg li:eq(2)").show();//显示积分商城“我能兑换”
					}
				}
			});
		},
		'load_game_start':function(obj){
			$(obj).addClass('t-moregames-focus');
			clearTimeout(timeout);
		
		$.getScript(domain.api+"65api/get_game.php");
			$('.pop-g-box').fadeIn();
		},
		'load_game_stop':function(obj){
			$(obj).removeClass('t-moregames-focus');
			timeout = setTimeout(function(){ $('.pop-g-box').hide(); },200);
		},
		'AddFavorite':function(sURL, sTitle){
			try{
				window.external.addFavorite(sURL, sTitle);
			}catch (e){
				try{
					window.sidebar.addPanel(sTitle, sURL, "");
				}
				catch (e){
					alert("加入收藏失败，请使用Ctrl+D进行添加");
				}
			}
		},
		'SetHome':function(obj,vrl){
			try{
                obj.style.behavior='url(#default#homepage)';obj.setHomePage(vrl);
			}
			catch(e){
				if(window.netscape) {
					try {
						netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");
					}catch (e) {
						alert("此操作被浏览器拒绝！\n请在浏览器地址栏输入“about:config”并回车\n然后将 [signed.applets.codebase_principal_support]的值设置为'true',双击即可。");
					}
						var prefs = Components.classes['@mozilla.org/preferences-service;1'].getService(Components.interfaces.nsIPrefBranch);
						prefs.setCharPref('browser.startup.homepage',vrl);
				}
			}
		}
	},
	
	'content_callback_header':function(data){	
		var game_list = '<div class="pop-g-url pop-1" id="pop-1">';
		var status = '';
		for(var i=0; i<data.length; i++){
			if(data[i].head_pic_info=='new_pic'){
				status = '<span class="corner corner-new-g"></span>';
			}else if(data[i].head_pic_info=='hot_pic'){
				status = '<span class="corner corner-new-o"></span>';
			}else{ status = ''; }
			
			game_list+= '<a href="'+data[i].game_url.home+'" class="lnk apic" target="_blank">'+data[i].game_name+status+'</a>';
			if(i==9 && i!=data.length) game_list+= '</div><div class="pop-g-url pop-2" id="pop-2">';
			if(i==19 && i!=data.length) game_list+= '</div><div class="pop-g-url pop-3" id="pop-3">';
			if(i==data.length && i!=29) game_list+= '</div>';
			if(i==29) game_list+= '<span class="pop-g-cate"><a target="_blank" href="'+domain.platform+'game/hall/" style="color:#f06834;">\u66f4\u591a\u6e38\u620f</a></span></div>';
		}
		$('.pop-g').html(game_list);		
	},
	'user_info':{
		'head':function(uinfo){
			$("#nav dd:eq(5)").find("a").attr("href","http://my.65.com/");
			$(".w-tc3,.w-tc4").attr("href","http://my.65.com/userprotect.html");
			head.user_info.left(uinfo);
			$('.t-loged-id b').attr('title',uinfo.UNAME).html(uinfo.UNAME);
			if(uinfo.MSG!=0) $('.ico-img').fadeIn();
			$('.t-loged').css('display','inline-block');
			$('.t-log').css('display','none');
		},
		'left':function(uinfo){
			$(".w_login").removeClass("w_login2");
			$('.w-lp1').html('<a href="'+domain.user+'"><img width="50" height="50" src="http:\/\/uservefany.65.com\/uc_server\/avatar.php?uid='+uinfo.UID+'&size=small" /></a>');
			$('.w-lp2 span').html(uinfo.UNAME);
			$('.user_message_list2').html(uinfo.MSG);
			$('.w-loga2:eq(0)').html(uinfo.POINT);
			head.user_info.game_record(uinfo.HISTORY_GAME_SERVER);
			$('.w_login_late').css('display','block');
			$('.w_login_fot').css('display','none');
			$('.user-exit,.t-log-out').live("click",function(){head.user_info.log_out();})
		},
		'info':function(){
			  $.getJSON(domain.api+'65user/uservip.php?callback=?',function(da){
					if(da.code==1){
						 $("#vip,#vip2").attr("class","vip vip"+da.data.vip);
						 $("#vip3").attr("class","t-loged-vip t-loged-vip"+da.data.vip);
						 $(".vip_fs").html('<span id="vip_jyz">'+da.data.exp+'</span>/<span id="vip_bjyz">'+da.data.endexp+'</span>')	
						 $("#day_raking").html(da.data.enddaynum);	
						 $(".w-loga3").html(da.data.coin);
						 var ranking=da.data.ranking; 
						 if(ranking>=0){$("#ranking").removeClass("ranking2");$("#ranking span").html(da.data.ranking);}
						 else{$("#ranking").addClass("ranking2");$("#ranking span").html(-da.data.ranking);}
						 var jdtwidht=150*($("#vip_jyz").html()/$("#vip_bjyz").html());
						 $("#vipwidth,#vipwidth2").width(jdtwidht);
					}
				});
			},
		'game_record':function(log){
			var glog = '';
			if(log!=null && log.length > 0){
				for(var i=0; i<log.length; i++){
					if(i>1) break;
					glog+='<a href="'+log[i].SERVER_URL+'" title="'+log[i].GAME_NAME+'" target="_blank"><img src="'+domain.pic+'Uploads/images/'+log[i].GAME_PIC+'" />';
					glog+='<span class="user_yellow">'+log[i].GAME_NAME+'</span><span class="user_black">'+log[i].SERVER_NAME+'</span>';
					glog+='<span class="user_beijing">\u8fdb\u5165\u6e38\u620f</span></a>';
				}
			}else{
			}
			$('.w-log-l3').html(glog);
		},
		'log_out':function(){
			head.user_info.app_logout();
			/*
			$.getJSON(domain.platform+'account/loginout?callback=?',function(data){
				if(data.res==1) head.user_info.app_logout();
			});
			*/
		},
		'app_logout':function(){
			$.getJSON(domain.api+'65user/login_out.php?callback=?',function(d){
				if(d.code==1){
					$("#nav dd:eq(5)").find("a").attr("href","http://my.65.com/login.html");
					$(".w-tc3,.w-tc4").attr("href","http://my.65.com/login.html");
					if(location.href.indexOf("www.65.com/service")>=0){
						$(".nav_wrap a:eq(1)").attr("href","http://my.65.com/login.html");
						$("#hz_serc a:eq(1)").attr("href","http://my.65.com/login.html");
					    $("#hz_serc a:eq(2)").attr("href","http://my.65.com/login.html");
					}
					$('body').append('<div style="display:none;">'+d.synlogout+'</div>');
					$(".w_login").removeClass("w_login2");
				    $('.w_login_fot p:eq(2)').hide();
					$('.w-pwd-wrap2').hide();
					$('#show-login_msg').html('');
					var url = location.pathname.toLowerCase();
					//alert(domain.user);
					//if(window.location.host==domain.user){
					if(window.location.host=='my.65.com'){
						window.location.href='http://my.65.com/login.html?url='+window.location;
					}else if(url.indexOf("pay.shtml") >= 0){
						window.location.href = domain.platform+'pay.html';
					}else{
						$("#search_jg li:eq(2)").hide();//隐藏积分商城“我能兑换”
						$('.w_login_fot').css('display','block');
						$('.w_login_late').css('display','none');
						$('.t-loged').css('display','none');
						$('.t-log').css('display','inline-block');
					}
				}
			});
		},
		'login':function(obj){
			var uname = $('.w_log_name').val();
			var upwd  = encryptedString(key,$('.w_log_paw').val());
			var ucode = $('.w_log_code').val();
			head.app_login(uname, upwd, ucode);
			return false;
		}
	},
	'app_login':function(uname, upwd, ucode){
		$.getJSON(domain.api+'65user/ajax_login.php?callback=?',{u:uname,p:upwd,code:ucode},function(d){
			if(d.loginnum>=5){
				$(".w_login").addClass("w_login2");
				if($(".w_login_fot p:eq(2)").is(":visible")){
						$('.login-error-tipwrap span').html(d.msg);
						$('.log-tip-cover,.login-error-tipwrap').show();
						$('.closetip').live("click",function(){$('.log-tip-cover,.login-error-tipwrap').hide();});
						setTimeout(function(){
							$('.log-tip-cover,.login-error-tipwrap').hide();
						},2000)
					}
				else{
					$(".w_login_fot p:eq(2)").show();
					$(".w_log_code").val('').focus();
					//cgetcode();
					return false;
					}			
			}
			if(d.res==1){
				$('.log-tip-cover,.login-error-tipwrap').hide();
				head.init.log_status();
				$('body').append('<div style="display:none;">'+d.synlogin+'</div>');
			}
			else if(d.res==-1||d.res==-2||d.res==-3){
				$('.login-error-tipwrap span').html("用户名或密码错误");
				$('.log-tip-cover,.login-error-tipwrap').show();
				$('.closetip').live("click",function(){$('.log-tip-cover,.login-error-tipwrap').hide();});
				setTimeout(function(){
					$('.log-tip-cover,.login-error-tipwrap').hide();
				},2000)
			}
			else{
				$('.login-error-tipwrap span').html(d.msg);
				$('.log-tip-cover,.login-error-tipwrap').show();
				$('.closetip').live("click",function(){$('.log-tip-cover,.login-error-tipwrap').hide();});
				setTimeout(function(){
					$('.log-tip-cover,.login-error-tipwrap').hide();
				},2000)
			}
		});
	}
}

function getUrlParam(name) 
{ 
 var reg = new RegExp("(^|&)" + name + "=([^&]*)(&|$)", "i");
 var r = window.location.search.substr(1).match(reg);
 if (r != null) return unescape(r[2]); return '';
}

var appendScriptList = new Array();
	var confCid          = getUrlParam('cid')!= null ? getUrlParam('cid') : null ;
    var confGid          = getUrlParam('gid')!= null ? getUrlParam('gid') : null ;
    var isBdReferer      = getUrlParam('referer')== '65_bd' ? true : false ;

var addLogScript     = function(url,keyurl) {
	if(appendScriptList.indexOf( keyurl ) == -1 ){
		var script = document.createElement('script');
		script.type = 'text/javascript';
		script.src  = url ;
		appendScriptList.push( keyurl );
		$.getJSON( url, function( data ) {
			console.log(data);
		});
		//document.body.appendChild(script);
		//document.getElementsByTagName('head')[0].appendChild(script);
		return true;
	}else{
		return false;
	}
};
var http_referer     = window.location.href ? encodeURIComponent(window.location.href) : '' ;
var url_from         = document.referrer ? document.referrer : '' ;
var show_log_url     = "http://log.65.com/index.php?m=log&a=adv_log";
var download_log_url = "http://log.65.com/index.php?m=log&a=download_log";
var click_log_url    = "http://log.65.com/index.php?m=log&a=click_log";
//var channelId        = ( config.cid && config.tid ) ? config.tid+config.cid: 0 ;
var channelId        = confCid ;
var publicQuery      = '&cid='+channelId
+'&game_id='+confGid
+'&server_id=0'
+'&mid=0&__rqTime='+new Date().getTime()
+'&http_referer='+http_referer
+"&url_from="+url_from;
var reg_log_url      = "http://log.65.com/index.php?m=log&a=reg_log"+publicQuery;
var appendScriptList = new Array;

function fast_login(){
     $popup('#s-login-wrap', '#close-ql');
     show_qlogin();
}
function fast_reg(){
	 show_qreg();
	 if(isBdReferer == true){
		//发送日志才打开窗口
		$.getJSON( show_log_url+publicQuery, function( data ) {
			$popup('#s-login-wrap', '#close-ql');
		});
	 }else{
		$popup('#s-login-wrap', '#close-ql');
	}
 //addLogScript();
}

function show_qlogin(){
	 $("#s-user-login").addClass('current').parent().siblings().find('a').removeClass('current');				
	 $("#s-login-content").find("#s-user-register2").hide();
	 $("#s-login-content").find("#s-user-login2").fadeIn(300);
	 $("#s-login-wrap").center(); 
}
function show_qreg(){
	$("#s-user-register").addClass('current').parent().siblings().find('a').removeClass('current');			
	$("#s-login-content").find("#s-user-login2").hide();
	$("#s-login-content").find("#s-user-register2").fadeIn(300);
	$("#s-login-wrap").center();	
}

var addLogScript = function(url,keyurl) {
		if(appendScriptList.indexOf( keyurl ) == -1 ){
			var script = document.createElement('script');
			script.type = 'text/javascript';
			script.src  = url ;
			appendScriptList.push( keyurl );
			//document.body.appendChild(script);
			console.log( script );
			//document.getElementsByTagName('head')[0].appendChild(script);
			return true;
		}else{
			return false;
		}
	};

function show_login(){
	check_name('#u_name','用户名或密码错误',2);
	check_pwd('#p_word','用户名或密码错误',2);
	
	var uflg = $('#u_name').attr('status');
	var pflg = $('#p_word').attr('status');
	if(uflg=='y'&&pflg=='y'){
		var uname = $('#u_name').val();
		var upwd  = $('#p_word').val();
		var ucode  = $('#u_code').val();
		$("#show-login_msg").html("正在登录中...");
		$.getJSON('http://api.65.com/65user/ajax_login.php?callback=?',{u:uname,p:encryptedString(key,upwd),code:ucode},function(data){
			if(data.loginnum>=5){
					if($(".w-pwd-wrap2").is(":visible")){
						$('#show-login_msg').html(data.msg).fadeIn();
						}
					else{
						$('#show-login_msg').html("请输入验证码！");
						$('.w-pwd-wrap2').show();
						$("#u_code").val('').focus();
						//cgetcode();
					    return false;
						}
					}	
			if(data.res==1){
				 $('body').append('<div style="display:none;">'+data.synlogin+'</div>');
				 $(".w_login").removeClass("w_login2");
				 $('.w_login_fot p:eq(2)').hide();
				 head.init.log_status();
		         $("#close-ql").click();
				}
			else{
				$('#show-login_msg').html(data.msg).fadeIn();
				}
		});
	}else{
		return false;
	}
}
function check_name(obj,msg,status){
	if(status==2){
		$(obj).parent().next('span').eq(0).removeClass();
	}
	if($.trim($(obj).val())==''||$(obj).val().length<6||$(obj).val().length>22){
		$(obj).attr('status','n');
		if(status==1){
			$('#show_msg').css('display','block').find('span').html(msg).fadeIn();
			setTimeout(function(){
				$('#show_msg').css('display','none').fadeOut();
			},3000);
		}else{
			$(obj).parent().next('span').eq(0).removeClass();
			$(obj).parent().next('span').eq(0).addClass('w-login-error');
			$('#show-login_msg').html(msg).fadeIn();
		}
	}else{
		$(obj).attr('status','y');
	}
}
function check_pwd(obj,msg,status){
	if(status==2){
		$(obj).parent().next('span').eq(0).removeClass();
	}
	if($.trim($(obj).val())==''){
		$(obj).attr('status','n');
		if(status==1){
			$('#show_msg').css('display','block').find('span').html(msg).fadeIn();
			setTimeout(function(){
				$('#show_msg').css('display','none').fadeOut();
			},3000);
		}else{
			$(obj).parent().next('span').eq(0).removeClass();
			$(obj).parent().next('span').eq(0).addClass('w-login-error');
			$('#show-login_msg').html(msg).fadeIn();
		}	
	}else{
		$(obj).attr('status','y');
	}
}