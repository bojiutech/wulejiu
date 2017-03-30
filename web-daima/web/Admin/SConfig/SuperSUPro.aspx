<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="SuperSUPro.aspx.cs" Inherits="HN.Admin.Admin.SConfig.SuperSUPro" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script src="/Public/Js/jquery.js"></script>
    <script src="/Public/Js/public.js"></script>
    <style type="text/css">
        .div_main { padding: 0px; margin: 0px; margin: 0px auto; width: 1000px; }
        table.gridtable { width: 100%; font-family: verdana,arial,sans-serif; font-size: 11px; color: #333333; border-width: 1px; border-color: #666666; border-collapse: collapse; }
        table.gridtable th { text-align: left; padding-left: 60px; height: 35px; line-height: 35px; border-width: 1px; padding: 8px; border-style: solid; border-color: #666666; background-color: #dedede; }
        table.gridtable td { text-align: left; padding-left: 100px; height: 35px; line-height: 35px; border-width: 1px; padding-top: 5px; border-style: solid; border-color: #666666; background-color: #ffffff; }
        table.gridtable ul { width: 100%; height: 100%; list-style: none; }
        table.gridtable ul li { width: 168px; line-height: 25px; float: left; }
        #Button1 { width: 60px; }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div class="div_main">
        <table cellpadding="0" cellspacing="0" class="gridtable">
            <asp:Literal ID="lit_str" runat="server"></asp:Literal>
            <tr>
                <td style="text-align: center">
                    <asp:HiddenField ID="idList" runat="server" />
                    <asp:Button ID="BtnSubmit" runat="server" OnClick="BtnSubmit_Click" Text="保存" />
                </td>
            </tr>
        </table>
    </div>
    </form>
    <script type="text/javascript">
        $().ready(function () {
            $("input[name=chepr]").click(function () {
                if (subClassChecked(this)) {
                    $("input[name=chep" + $(this).attr("_val") + "]").attr("checked", "checked");
                }
                if (subClassUnChecked(this)) {
                    $("input[name=chep" + $(this).attr("_val") + "]").attr("checked", "");
                }
            });

            $("input[_val=]").click(function () {
                var subClasses = $("input[_val=" + $(this).val() + "]");
                for (var i = 0; i < subClasses.length; i++) {
                    if ($(this).attr("checked") == true) {
                        subClasses.eq(i).attr("checked", "checked");
                    }
                    else {
                        subClasses.eq(i).attr("checked", "");
                    }
                }
            });

            $("#form1").submit(function () {
                if (isChecked()) {
                    return true;
                }
                else {
                    return false;
                }
            });

            function subClassUnChecked(obj) {
                var subClasses = $(obj).parent().parent().find("input");
                var subChecked = 0;
                for (var i = 0; i < subClasses.length; i++) {
                    if (subClasses.eq(i).attr("checked") == "") {
                        subChecked++;
                    }
                }
                if (subChecked == subClasses.length) {
                    return true;
                }
                else {
                    return false;
                }
            }

            function subClassChecked(obj) {
                var subClasses = $(obj).parent().parent().find("input");
                var subChecked = 0;
                for (var i = 0; i < subClasses.length; i++) {
                    if (subClasses.eq(i).attr("checked") == "checked") {
                        subChecked++;
                    }
                }
                if (subChecked == 0) {
                    return true;
                }
                else {
                    return false;
                }
            }

            function isChecked() {
                var ID = "";
                $(".cheval").each(function () {
                    if ("checked" == $(this).attr("checked") || $(this).attr("checked")) {
                        ID += $(this).attr("value") + "_";
                    }
                });
                ID = ID.substring(0, ID.length - 1);
                $("#idList").val(ID);
                if (ID == "") {
                    return false;
                }
                else { return true; }
            }
        });
    </script>
</body>
</html>
