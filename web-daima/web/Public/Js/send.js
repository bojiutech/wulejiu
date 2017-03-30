
var username;
var i = 301;

function getValidCode() {
     if (i == 301) {
    username = document.getElementById("txtAccount").value;
    var urlData = '/Public/XmlHttpUser.aspx?type=phonevalid&username=' + escape(username);

    var strReturn = AjaxCall(urlData);
    
    //用户名存在,并手机验证
    if (strReturn != "0") {

   
            document.getElementById("validcode").style.display = "none";
            document.getElementById("btnGetCode").style.display = "";

            document.getElementById("lbMsg").innerText = "验证码已发送到您的手机上，若未收到请重新获取！";
            SendCode();
     
    } else {
        if (username != "") {
            document.getElementById("lbMsg").innerText = "";
            document.getElementById("btnGetCode").style.display = "none";
            document.getElementById("validcode").style.display = "inline";
            document.getElementById("lbMsg").innerText = "";
        }

    }
}   }



//重新发送验证码
function send() {
    i--;
    if (i == -1) {
        document.getElementById("btnGetCode").disabled = false;
        document.getElementById("btnGetCode").value = "重新获取";
        clearTimeout(set_id);

    } else {
        document.getElementById("btnGetCode").value = "重新获取(" + i + ")";

        set_id = setTimeout("send();", 1000);
    }
}
function SendCode() {
    username = document.getElementById("txtAccount").value;

    var url = '/Public/GetPhonecode.aspx?x=' + Math.random() + "&name=" + username;

    var data = AjaxCall(url);
    
    if (data == "-99") {
        document.getElementById("lbMsg").innerText = "用户名不存在！";
        return;
    }
    else if (data > 0) {
        i = 301;

        document.getElementById("btnGetCode").value = "重新获取（300）";
        document.getElementById("btnGetCode").disabled = true;
        send();

    } else {
    i--;
  //  i = 61;
   // getValidCode();
    }

}

 