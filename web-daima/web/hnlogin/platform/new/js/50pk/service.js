/**
 * 客服中心
 */
$(function(){
	
	/*---------------------------------------------玩家中心-------------------------------------------------*/
/*---------------上传头像功能------------*/
$('.hz_tall_l dd .hz_p3>.hz_touxiang').click(function(e) {
    $('.hz_uploadbg,.hz_upload').show();
	$('.hz_uploadbg').fadeTo(0,0.4).height($(document).height());
});
$('.hz_upload>.hz_head>span').click(function(e) {
    $(this).parent().parent().hide();
	$('.hz_uploadbg').hide();
});

/*---------------------------------------------客服中心新手心看-------------------------------------------------*/
/*----------导航切换-----------*/
$('.hz_newcomer_all .hz_headin a').click(function(e) {
	var newal=$(this).index();
	$(this).addClass('current').siblings().removeClass('current');
	$('.hz_newcomer_all h3 span').eq(newal).addClass('hz_ss').siblings().removeClass('hz_ss');
	$('.hz_newall>.hz_new').eq(newal).addClass('hz_newshow').siblings().removeClass('hz_newshow');
});
/*----------内容伸缩切换-----------*/
$('.hz_newwt>.hz_p1').click(function(e) {
	
	if($(this).parent().children('.hz_p2').css("display")=='none'){
		//把当前的p2显示
		$(this).parent().children('.hz_p2').slideToggle("",function(){
			//给右边收缩按钮添加删除类
			$(this).children('.hz_pin_02').children().removeClass('hz_span01').addClass('hz_span02');
	 	});
	}else{
		//把当前的p2隐藏
		$(this).parent().children('.hz_p2').slideToggle("",function(){
			//给右边收缩按钮添加删除类
			$(this).children('.hz_pin_02').children().removeClass('hz_span02').addClass('hz_span01');
		});
		
	}
});
	
	
	var showimg = $('#showimg');
	$("#fileupload").wrap("<form style='border:0; background:none; padding:0;' id='myupload' action='/service/upload.html' method='post' enctype='multipart/form-data'></form>");
   
	$("#file_upload").click(function(){
    	if($('#showimg span').length>=3){
    		$("#file_msg").html("限制三张");
    		return false;
    	}
		$("#myupload").ajaxSubmit({
			dataType:  'json',
			beforeSend: function() {
        		$("#file_msg").html("上传中...");
    		},
    		uploadProgress: function(event, position, total, percentComplete) {
        		var percentVal = percentComplete + '%';
        		$("#file_msg").html(percentVal);
    		},
			success: function(data) {
				if(data.status==1){
					showimg.prepend("<span><img src='"+data.path+"'/><a href='javascript:void(0)' onClick='$(this).parent().remove();'>删除</a><input type='hidden' value='"+data.info+"' name='user_icard[]'/></span>");
					$("#file_msg").html("上传成功");
					$("#fileupload").val('');
				}else{
					$("#file_msg").html(data.info);
				}
			},
			error:function(xhr){
				$("#file_msg").html("上传失败");
				//alert(xhr.responseText);
				//files.html(xhr.responseText);
			}
		});
	});
	
	
	
	var showimg1 = $('#ques_showimg');
	$("#ques_fileupload").wrap("<form style='border:0; background:none; padding:0;' id='ques_myupload' action='/service/upload.html' method='post' enctype='multipart/form-data'></form>");
   
	$("#ques_file_upload").click(function(){

    	if($('#ques_showimg span').length>=3){
    		$("#ques_file_msg").html("限制三张");
    		return false;
    	}
		$("#ques_myupload").ajaxSubmit({
			dataType:  'json',
			beforeSend: function() {
        		$("#ques_file_msg").html("上传中...");
    		},
    		uploadProgress: function(event, position, total, percentComplete) {
        		var percentVal = percentComplete + '%';
        		$("#ques_file_msg").html(percentVal);
    		},
			success: function(data) {
				if(data.status==1){
					showimg1.prepend("<span><img src='"+data.path+"'/><a href='javascript:void(0)' onClick='$(this).parent().remove();'>删除</a><input type='hidden' value='"+data.info+"' name='ques_user_pic[]'/></span>");
					$("#ques_file_msg").html("上传成功");
					$("#ques_fileupload").val('');
				}else{
					$("#ques_file_msg").html(data.info);
				}
			},
			error:function(xhr){
				$("#ques_file_msg").html("上传失败");
				//alert(xhr.responseText);
				//files.html(xhr.responseText);
			}
		});
	});
	//被盗申诉结果提交
	var stolen_upload_show = $('#stolen_upload_show');
	$("#stolen_fileupload").wrap("<form style='border:0; background:none; padding:0;' id='ques_myupload' action='/service/upload.html' method='post' enctype='multipart/form-data'></form>");
   
	$("#stolen_upload").click(function(){

    	if($('#stolen_upload_show span').length>=3){
    		$("#stolen_upload_msg").html("限制三张");
    		return false;
    	}
		$("#ques_myupload").ajaxSubmit({
			dataType:  'json',
			beforeSend: function() {
        		$("#stolen_upload_msg").html("上传中...");
    		},
    		uploadProgress: function(event, position, total, percentComplete) {
        		var percentVal = percentComplete + '%';
        		$("#stolen_upload_msg").html(percentVal);
    		},
			success: function(data) {
				if(data.status==1){
					stolen_upload_show.prepend("<span><img src='"+data.path+"' style='width:200px;height:100px'/><a href='javascript:void(0)' onClick='$(this).parent().remove();'>删除</a><input type='hidden' value='"+data.info+"' name='ques_user_pic[]'/></span>");
					$("#stolen_upload_msg").html("上传成功");
					$("#stolen_fileupload").val('');
				}else{
					$("#stolen_upload_msg").html(data.info);
				}
			},
			error:function(xhr){
				$("#stolen_upload_msg").html("上传失败");
				//alert(xhr.responseText);
				//files.html(xhr.responseText);
			}
		});
	});
	
	//省份
	$.getJSON("/service/stolen_appeal.html?m=service&a=get_province&callback=?", function(data){
		var select_str = "";
		$.each(data.result,function(i,n){
			select_str += '<option value="'+n.region_name+'" region_id="'+n.region_id+'">'+n.region_name+'</option>';
		});
		
		$("#reg_province").append(select_str);
		$("#log_province_1").append(select_str);
		$("#log_province_2").append(select_str);
	}); 
	
	//城市
	$("#reg_province, #log_province_1, #log_province_2").change(function(){			
		var arr_select = new Array()
		arr_select['reg_province'] = "reg_city";
		arr_select['log_province_1'] = "log_city_1";
		arr_select['log_province_2'] = "log_city_2";

		var select_province_id = $(this).attr("id");			
		var province = $("#"+select_province_id+" option:selected").attr("region_id");
		
		if(typeof(province)=='undefined'){
			$("#"+arr_select[select_province_id]).html('<option value="">选择城市</value>');				
		}else{
			$.getJSON("/service/stolen_appeal.html?m=service&a=get_city&callback=?&province="+province, function(data){
				var select_str = "";
				$.each(data.result,function(i,n){
					select_str += '<option value="'+n.region_name+'" region_id="'+n.region_id+'">'+n.region_name+'</option>';
				});				
				$("#"+arr_select[select_province_id]).html(select_str);
			});
		}
	});
  
  //所在游戏
  $.getJSON("/game/getGame.html?callback=?", function(sData){
      var gameStr = '<option value="">请选择游戏</option>';
      var games = sData;
      for (var i in games) {
          gameStr += '<option value="'+games[i].game_id+'">'+games[i].game_name+'</option>';
      }
      $("#w-pdgameId").append(gameStr);
  });
  //服务器
  $('#w-pdgameId').change(function(){
      var selOpt = $("#w-pdsevId option");  
      selOpt.remove();
      var gameId = $("#w-pdgameId").val();
		
		if(gameId==''){
			var serverStr = '<option value="">请选择服务器</option>';
			$('#w-pdsevId').append(serverStr); 
		}else{
			$.getJSON("/game/getServers.html?callback=?&gid="+gameId, function(sData){
			var serverStr = '<option value="">请选择服务器</option>';            

          var servers = sData.servers;
          for (var i in servers) {
              serverStr += '<option value="'+servers[i].server_id+'">'+servers[i].server_name+'</option>';
          }     
			$('#w-pdsevId').append(serverStr);           
			});		
		}
  });
});
function show_tip(index,type,msg){
	if(type=='error'){
		$('.hz_span02:eq('+index+')').hide();
		$('.hz_span01:eq('+index+')').html(msg).show();
	}else{
		$('.hz_span01:eq('+index+')').hide();
		$('.hz_span02:eq('+index+')').show();
	}
}
