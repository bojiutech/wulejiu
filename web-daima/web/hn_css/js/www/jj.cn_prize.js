// �ҽ������ļ� //��2015��5��
var jj_cn_prizw = {
	//��껬��
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
				if(browser == "Microsoft Internet Explorer" && (trim_Version == "MSIE6.0" || trim_Version == "MSIE7.0")){ //ieͼƬ���ܵ�
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
				
				_this.add_on_scrill_on = false;  //ע����ajax�������ݵĺ����� on = true;
				if({}.toString.call( fn ) === "[object Function]"){
					fn();					
				}
			}
		};
		www_jj_cn_pub.add_event(window, 'scroll', function(){
			on_scrill();
		});
	},
	get_param: function(name){ //�õ���ҳ����
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
	on_scrill_ajax: function (){ // ����ҳ��ajax��ֻ�ڶ���ҳ����
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
							new_html += '<li class="jp_li'+ one_css +'"><a target="_blank" href="http://www.jj.cn/prize_center/prize_detail.html?compose_id='+ item.ResComposeID +'">' + h_n_z + '<span class="im"><img title="'+ item.ComposeName2 +'" src="http://img1.jj.cn'+item.ComposeImageSmall+'"/></span><span class="ma" title="'+item.ComposeName2+'">'+item.ComposeName2+'</span><span class="qc">�����￨��'+ item.NeedSrcResNum +'</span></a></li>'
						});
						$("#inner_hot_img").append(new_html);
						document.title = json.list.ComposeTypeName + document.title;
						new_data = false;
					}
					
					if(!date){
						_this.add_on_scrill_on = false;
						$('.inner_Load_more span').css({'display':'block'}).html("����û����");
						on_scrill_ajaxfn = function(){};
						return false;
					}
					$.each(date, function(i, item){
						var h_n_z = "";
						if( parseInt(item.ComposeResMark)){
							h_n_z = '<img class="hd_new_hot" src="http://hn_img/www/prize/' + item.ComposeResMark + '.gif"/>'
						}
						html += '<li class="jp_li"><a target="_blank" href="http://www.jj.cn/prize_center/prize_detail.html?compose_id='+ item.ResComposeID +'">' + h_n_z + '<span class="im"><img title="'+ item.ComposeName2 +'" src="http://img1.jj.cn'+item.ComposeImageSmall+'"/></span><span class="ma" title="'+ item.ComposeName2 +'">'+item.ComposeName2+'</span><span class="qc">�����￨��'+ item.NeedSrcResNum +'</span></a></li>'
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
	detail_ajax: function(){ //��ҳ����Ϣ ֻ����ҳ��
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
					tit = json.ComposeName.split("�￨�ϳ�")[1],
					html = '';
				$('.inner_top_nav').html($('.inner_top_nav').html() + tit)
				document.title = tit + document.title;
				$("#inner_thr_top").html('<div class="le"><img src="http://img1.jj.cn'+json.img_data[0].ImageUrl+'"/></div><div class="ri"><h1>'+ tit +'</h1><div class="qc"><span class="q">�����￨��'+json.NeedSrcResNum+'��</span><a class="wh" href="http://www.jj.cn/news/320/20111213133600020502.shtml" target="_blank">ʲô���￨?</a></div><div class="js">��ƷͼƬ�����ο�������ʵ��Ϊ׼������˾ӵ�����ս���Ȩ��</div><div class="lc"><img src="http://hn_img/www/prize/three_1.gif"/>�뵽<a href="javascript:;"><img src="http://hn_img/www/prize/three_2.gif"/>JJ������Ʒ��ҽ�����</a>����<a href="javascript:;"><img src="http://hn_img/www/prize/three_3.gif"/>�ֻ��˶ҽ�����</a>�һ����Ľ�Ʒ��</div></div>');
				if(json.imgnum == 1){
					$(".inner_thr_box").addClass("inner_thr_boxtow");
				}
				$.each(img_data, function(i, item){
					html += '<img src="http://img1.jj.cn'+item.ImageUrl+'"/>'
				});
				$("#prize_detail").append(html);
				
				if({}.toString.call( inner_win_three ) === "[object Function]"){ //�������� inner_win_three();����д����ҳ���
					inner_win_three();					
				}
				www_jj_cn_pub.add_event(window, 'scroll', function(){ //go top but��ֻ����ҳ�õ�
					_this.go_top_but();	
				});
			},error:function(msg){
				
			}
		});
	},
	user_prize_fn: function (id){ //��ҳ24Сʱ��Ӯ�Ҷ���
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
$(function(){ //��ѡ�е���
	$(".jj_nav_info .nav li").eq(3).addClass("hov");	
})