<%@ Control Language="C#" AutoEventWireup="true" CodeBehind="HotGame.ascx.cs" Inherits="Bzw.Web.Public.HotGame" %>


<asp:Repeater runat="server" ID="rep_hotgame">
<ItemTemplate>
 <li class="png"><i class="png"></i><span>
 <%#Container.ItemIndex+1%>
 
 </span>
                            <div class="info">
                                
                                <%#Eval("game_name")%>
                                 <a class="apply png" href='/GameNew.aspx?id= <%#Eval("Game_id")%>'
                                    ><b class="png" style="left: -1px;"></b></a>
                            </div>
                        </li>
</ItemTemplate>
</asp:Repeater>

              