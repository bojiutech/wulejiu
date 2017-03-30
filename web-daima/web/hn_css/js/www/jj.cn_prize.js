// 兑奖公用文件 //易2015年5月
var jj_cn_prizw = {
	//鼠标滑过
	index_li_hov_fn: function(){
		var hov_li = www_jj_cn_pub.get_by_class(document, "jp_li") // www_jj_cn_pub.get_by_class_http://hn_css/js/www/www.jj.cn_pub_15.js
		for(var i = 0; i < hov_li.length; i++){
			hov_li[i].on_off = true;
			hov_li[i].css_name = hov_li[i].className;
			hov_li[i].onmouseover = function(){
				var browser = navigator.appName
				var b_version = navigator.appVersion
				var version = b_version.split(";");
				var trim_Version = ""
				if(version[1]){
					trim_Version = version[1].replace(/[ ]/g,"");
				}
				if(browser == "Microsoft Internet Explorer" && (trim_Version == "MSIE6.0" || trim_Version == "MSIE7.0")){ //ie图片不能点
					this.getElementsByTagName("img")[0].onclick = function(){
						var href = this.parentNode.parentNode.href;
						window.location.href = href;
					} 
				}  			
				hov_li_css = this.className;
				if(this.on_off){
					this.className +=  " jp_li_hov";
				}
				this.on_off = false;		
			};
			hov_li[i].onmouseout = function(){
				this.className =  this.css_name;			
				this.on_off = true;		
			};
		}
	},
	get_left_top_right: function (obj){
		var t = 0;
		while(obj){
			t += obj.offsetTop;
			obj = obj.offsetParent;
		}
		return t;
	},
	cei_ling: function (obj_id){
		var _this = this,
			o_top = document.getElementById(obj_id),
			t = _this.get_left_top_right( o_top );
		www_jj_cn_pub.add_event(window, 'scroll', top_top);
		function top_top(){
			var scroll_top = document.documentElement.scrollTop || document.body.scrollTop,
				client_width = document.documentElement.clientWidth || document.body.clientWidth;
			if( scroll_top > t){
				if(!(window.navigator.userAgent.indexOf('MSIE 6.0') != -1)){	
					o_top.style.position = 'fixed';
					o_top.style.right = (client_width - www_jj_cn_pub.page_max_width)/2 + 'px';				
				}
			}else{
				o_top.style.position = "";
				o_top.style.right = "";
			}
		};
	},
	add_on_scrill_on: true,
	add_on_scrill: function(id, fn){
		var _this = this;
			add_on = document.getElementById(id),
			o_top = this.get_left_top_right(add_on),
			on = true;
		function on_scrill(){
			var scro_top = document.documentElement.scrollTop || document.body.scrollTop,
				client_top =document.documentElement.clientHeight || document.body.clientHeight;
			if (((add_on.offsetHeight + o_top + 100) < (scro_top + client_top)) && _this.add_on_scrill_on) {
				
				_this.add_on_scrill_on = false;  //注：在ajax加载数据的后面让 on = true;
				if({}.toString.call( fn ) === "[object Function]"){
					fn();					
				}
			}
		};
		www_jj_cn_pub.add_event(window, 'scroll', function(){
			on_scrill();
		});
	},
	get_param: function(name){ //得到网页参数
		var search = document.location.search;
		var pattern = new RegExp("[?&]"+name+"\=([^&]+)", "g");
		var matcher = pattern.exec(search);
		var items = null;
		if(null != matcher){
			try{
				items = decodeURIComponent(decodeURIComponent(matcher[1]));
			}catch(e){
				try{
					items = decodeURIComponent(matcher[1]);
				}catch(e){
					items = matcher[1];
				}
			}
		}
		return items;
	},
	go_top_but_on_off: true,
	go_top_but: function(){
		var _this = this,
			scroll_top = document.body.scrollTop || document.documentElement.scrollTop,
			pop_win_prize = document.getElementById("return_top") || {};
		if(scroll_top > 400 && _this.go_top_but_on_off){
			pop_win_prize.className = "return_top return_top_on"
			_this.go_top_but_on_off = false;
		}
		if(scroll_top < 400 && !_this.go_top_but_on_off){
			pop_win_prize.className = "return_top"
			_this.go_top_but_on_off = true;
		}
	},
	on_scrill_ajax: function (){ // 二级页的ajax，只在二级页调用
		var n = 1,
			new_data = true,
			subtype = parseInt(jj_cn_prizw.get_param("subtype")),
			_this = this;
		switch(subtype){
			case 22:
				$("#inner_tow_right li").eq(0).addClass("hov")
				break;
			case 21:
				$("#inner_tow_right li").eq(1).addClass("hov")
				break;
			case 51:
				$("#inner_tow_right li").eq(2).addClass("hov")
				break;
			case 18:
				$("#inner_tow_right li").eq(3).addClass("hov")
				break;
			case 20:
				$("#inner_tow_right li").eq(4).addClass("hov")
				break;
			default:
		}
		
		var ajax_data = function(){
			$.ajax({
				url: "http://my.jj.cn/ajax/prize_list.php?",
				type: "get",
				data: "subtype="+subtype+"&page="+n+"&action=ajax_get_prize",
				dataType: "jsonp",
				jsonp: "callback",
				cache: false,
				success: function(json){
					var html = ""
					var new_html = ""
					var right_nav_html = ""
					var date = json.list.DATA;
					var new_date = json.new_list;
					if(new_data){
						$.each(json.banner, function(i, item){
							var co_mun = "",
								css_name = "",
								con_id = parseInt(item.ComposeTypeID);
							switch(con_id){
								case 22:
									co_mun = "co1";
									break;
								case 21:
									co_mun = "co2";
									break;
								case 51:
									co_mun = "co3";
									break;
								case 18:
									co_mun = "co4";
									break;
								case 20:
									co_mun = "co5";
									break;
								default:
									co_mun = "co6";
							}
							if(subtype == con_id){
								css_name = 'class="hov"'
							}
							right_nav_html += '<li '+ css_name +'><a href="http://www.jj.cn/prize_center/prize_list.html?subtype='+ item.ComposeTypeID +'"><span class="co '+ co_mun +'"></span>'+ item.ComposeTypeName +'</a></li>'
						});
						$(".inner_tow_right_nav").html(right_nav_html);
						$.each(new_date, function(i, item){
							var h_n_z = "";
							var one_css = ""
							if( parseInt(item.ComposeResMark)){
								h_n_z = '<img class="hd_new_hot" src="http://hn_img/www/prize/' + item.ComposeResMark + '.gif"/>'
							}
							if(i == 0){
								one_css = " inner_li1"
							}
							new_html += '<li class="jp_li'+ one_css +'"><a target="_blank" href="http://www.jj.cn/prize_center/prize_detail.html?compose_id='+ item.ResComposeID +'">' + h_n_z + '<span class="im"><img title="'+ item.ComposeName2 +'" src="http://img1.jj.cn'+item.ComposeImageSmall+'"/></span><span class="ma" title="'+item.ComposeName2+'">'+item.ComposeName2+'</span><span class="qc">所需秋卡：'+ item.NeedSrcResNum +'</span></a></li>'
						});
						$("#inner_hot_img").append(new_html);
						document.title = json.list.ComposeTypeName + document.title;
						new_data = false;
					}
					
					if(!date){
						_this.add_on_scrill_on = false;
						$('.inner_Load_more span').css({'display':'block'}).html("下面没有了");
						on_scrill_ajaxfn = function(){};
						return false;
					}
					$.each(date, function(i, item){
						var h_n_z = "";
						if( parseInt(item.ComposeResMark)){
							h_n_z = '<img class="hd_new_hot" src="http://hn_img/www/prize/' + item.ComposeResMark + '.gif"/>'
						}
						html += '<li class="jp_li"><a target="_blank" href="http://www.jj.cn/prize_center/prize_detail.html?compose_id='+ item.ResComposeID +'">' + h_n_z + '<span class="im"><img title="'+ item.ComposeName2 +'" src="http://img1.jj.cn'+item.ComposeImageSmall+'"/></span><span class="ma" title="'+ item.ComposeName2 +'">'+item.ComposeName2+'</span><span class="qc">所需秋卡：'+ item.NeedSrcResNum +'</span></a></li>'
					});
					$("#innert_prize_list").append(html);
					jj_cn_prizw.index_li_hov_fn();
					n++;
				},error:function(msg){
				}
			});
			setTimeout(function(){
				_this.add_on_scrill_on = true;
			},200);
		}
		ajax_data();
		return ajax_data;
	},
	detail_ajax: function(){ //内页读信息 只在内页用
		var compose_id = parseInt(jj_cn_prizw.get_param("compose_id")),
			_this = this;
		$.ajax({
			url: "http://my.jj.cn/ajax/prize_list.php?",
			type: "get",
			data: "action=view&compose_id="+compose_id,
			dataType: "jsonp",
			jsonp: "callback",
			cache: false,
			success: function(json){
				var img_data = json.img_data,
					tit = json.ComposeName.split("秋卡合成")[1],
					html = '';
				$('.inner_top_nav').html($('.inner_top_nav').html() + tit)
				document.title = tit + document.title;
				$("#inner_thr_top").html('<div class="le"><img src="http://img1.jj.cn'+json.img_data[0].ImageUrl+'"/></div><div class="ri"><h1>'+ tit +'</h1><div class="qc"><span class="q">所需秋卡：'+json.NeedSrcResNum+'张</span><a class="wh" href="http://www.jj.cn/news/320/20111213133600020502.shtml" target="_blank">什么是秋卡?</a></div><div class="js">物品图片仅供参考，请以实物为准，本公司拥有最终解释权！</div><div class="lc"><img src="http://hn_img/www/prize/three_1.gif"/>请到<a href="javascript:;"><img src="http://hn_img/www/prize/three_2.gif"/>JJ大厅物品箱兑奖中心</a>或者<a href="javascript:;"><img src="http://hn_img/www/prize/three_3.gif"/>手机端兑奖中心</a>兑换您的奖品！</div></div>');
				if(json.imgnum == 1){
					$(".inner_thr_box").addClass("inner_thr_boxtow");
				}
				$.each(img_data, function(i, item){
					html += '<img src="http://img1.jj.cn'+item.ImageUrl+'"/>'
				});
				$("#prize_detail").append(html);
				
				if({}.toString.call( inner_win_three ) === "[object Function]"){ //弹出窗口 inner_win_three();方法写在了页面里。
					inner_win_three();					
				}
				www_jj_cn_pub.add_event(window, 'scroll', function(){ //go top but现只有内页用到
					_this.go_top_but();	
				});
			},error:function(msg){
				
			}
		});
	},
	user_prize_fn: function (id){ //首页24小时大赢家动画
		var priz_id = document.getElementById(id);
		var ul = user_prize_list.getElementsByTagName("ul")[0];
		var li = null;
		function fn(){
			li = user_prize_list.getElementsByTagName("li")[0];
			li.style.height = '0';
		}
		setInterval(function(){
			fn();
			setTimeout(function(){
				li.style.height = '';
				ul.appendChild(li);
			},800);
		},3000);	
	}
}
$(function(){ //定选中导航
	$(".jj_nav_info .nav li").eq(3).addClass("hov");	
})