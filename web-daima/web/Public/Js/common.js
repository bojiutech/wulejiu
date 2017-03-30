function menu_over(num, nowp) {

    for (i = 1; i < 10; i++) {
        if (document.getElementById('m' + i) != null) {
            document.getElementById('m' + i).src = "/Images/top_menu0" + i + "off.jpg";
        }
    }
    document.getElementById('m' + num).src = "/Images/top_menu0" + num + "on.jpg";
    if (nowp != 0) {
        document.getElementById('m' + nowp).src = "/Images/top_menu0" + nowp + "on.jpg";
    }


}

function menu_over1(num, nowp) {
    for (i = 1; i < 10; i++) {
        if (document.getElementById('l' + i) != null) {
            document.getElementById('l' + i).src = "/Images/sub01/left_btn0" + i + "off.jpg";
        }
    }

    document.getElementById('l' + num).src = "/Images/sub01/left_btn0" + num + "on.jpg";
    if (nowp != 0) {
        document.getElementById('m' + nowp).src = "/Images/top_menu0" + nowp + "on.jpg";
    }

}
function menu_out(now, nowp) {
    for (i = 1; i < 10; i++) {
        if (document.getElementById('m' + i) != null) {
            document.getElementById('m' + i).src = "/Images/top_menu0" + i + "off.jpg";
        }
    }
    if (nowp != 0) {
        document.getElementById('m' + nowp).src = "/Images/top_menu0" + nowp + "on.jpg";
    }
}

 
 