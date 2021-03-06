<html>
<! Copyright (c) Realtek Semiconductor Corp., 2003. All Rights Reserved. ->
<head>
<META HTTP-EQUIV=Refresh CONTENT="30; URL=ddns.asp">
<meta http-equiv="Content-Type" content="text/html" charset="utf-8">
<title><% multilang("Dynamic"); %> DNS <% multilang("Configuration"); %></title>
<script type="text/javascript" src="share.js">
</script>
<SCRIPT>
selected=0;

function deSelected()
{
	/*
	if (document.ddns.select) {
		var len = document.ddns.select.length;
		if (len == undefined)
			document.ddns.select.checked = false;
		else {
			for (var i=0; i < len; i++)
				document.ddns.select[i].checked = false;
		}
	}
	*/
}

function addClick()
{
	if (document.ddns.hostname.value=="") {
		alert("Please enter hostname for this account!");
		document.ddns.hostname.focus();
		deSelected();
		return false;
	}
	if (includeSpace(document.ddns.hostname.value)) {
		alert('Invalid host name.');
		document.ddns.hostname.focus();
		return false;
	}
	if (checkString(document.ddns.hostname.value) == 0) {
		alert('Invalid host name.');
		document.ddns.hostname.focus();
		return false;
	}

	if (document.ddns.ddnsProv.value=="0") {
		if (document.ddns.username.value=="") {
			alert("Please enter username for this account!");
			document.ddns.username.focus();
			deSelected();
			return false;
		}
		if (includeSpace(document.ddns.username.value)) {
			alert('Invalid user name.');
			document.ddns.username.focus();
			return false;
		}
		if (checkString(document.ddns.username.value) == 0) {
			alert('Invalid user name.');
			document.ddns.username.focus();
			return false;
		}

		if (document.ddns.password.value=="") {
			alert("Please enter password for this account!");
			document.ddns.password.focus();
			deSelected();
			return false;
		}
	  	if ( includeSpace(document.ddns.password.value)) {
			alert('Invalid password.');
			document.ddns.password.focus();
			return false;
 		}
		if (checkString(document.ddns.password.value) == 0) {
			alert('Invalid password.');
			document.ddns.password.focus();
			return false;
		}
	}

	if (document.ddns.ddnsProv.value=="1") {
		if (document.ddns.email.value=="") {
			alert("Please enter email for this account!");
			document.ddns.email.focus();
			deSelected();
			return false;
		}
		if (includeSpace(document.ddns.email.value)) {
			alert('Invalid email.');
			document.ddns.email.focus();
			return false;
		}
		if (checkString(document.ddns.email.value) == 0) {
			alert('Invalid email.');
			document.ddns.email.focus();
			return false;
		}

		if (document.ddns.key.value=="") {
			alert("Please enter key for this account!");
			document.ddns.key.focus();
			deSelected();
		        return false;
	        }
		if (includeSpace(document.ddns.key.value)) {
			alert('Invalid key.');
			document.ddns.key.focus();
			return false;
		}
		if (checkString(document.ddns.key.value) == 0) {
			alert('Invalid key.');
			document.ddns.key.focus();
			return false;
		}
	}

	return true;
}

function modifyClick()
{
	if (!selected) {
		alert("Please select an entry to modify !");
		return false;
	}
	return addClick();
}

function removeClick()
{
	if (!selected) {
		alert("Please select an entry to delete!");
		return false;
	}
	return true;
}

function updateState()
{
  if (document.ddns.ddnsProv.value=="0") {
 	enableTextField(document.ddns.username);
 	enableTextField(document.ddns.password);
 	disableTextField(document.ddns.email)
 	disableTextField(document.ddns.key)
  }
  else {
  	enableTextField(document.ddns.email);
  	enableTextField(document.ddns.key);
 	disableTextField(document.ddns.username);
 	disableTextField(document.ddns.password);
  }
}

function postEntry(enabled, pvd, host, user, passwd, intf)
{
	if (enabled)
		document.ddns.enable.checked = true;
	else
		document.ddns.enable.checked = false;
	document.ddns.hostname.value = host;
	if (pvd == 'dyndns') {
		document.ddns.ddnsProv.value = 0;
		document.ddns.username.value = user;
		document.ddns.password.value = passwd;
		document.ddns.email.value = '';
		document.ddns.key.value = '';
		document.ddns.interface.value = intf;
	}
	else {
		document.ddns.ddnsProv.value = 1;
		document.ddns.username.value = '';
		document.ddns.password.value = '';
		document.ddns.email.value = user;
		document.ddns.key.value = passwd;
		document.ddns.interface.value = intf;
	}
	updateState();
	selected = 1;
}

</SCRIPT>
</head>

<body>
<blockquote>
<h2><font color="#0000FF"><% multilang("Dynamic"); %> DNS <% multilang("Configuration"); %></font></h2>

<form action=/boaform/admin/formDDNS method=POST name="ddns">
<table border=0 width="500" cellspacing=4 cellpadding=0>
  <tr><td><font size=2>
    <% multilang("This page is used to configure the Dynamic DNS address from DynDNS.org or TZO. Here you can Add/Remove to configure Dynamic DNS."); %>
  </font></td></tr>
  <tr><td><hr size=1 noshade align=top></td></tr>
</table>
<table border=0 width="500" cellspacing=4 cellpadding=0>
  <tr>
      <td width="30%"><font size=2><b><% multilang("Enable"); %>:</b></td>
      <td width="70%"><input type="checkbox" name="enable" value="1" checked></td>
  </tr>

  <tr>
      <td width="30%"><font size=2><b>DDNS <% multilang("Provider"); %>:</b></td>
      <td width="70%">
      <select size="1" name="ddnsProv" onChange='updateState()'>
      <option selected value="0">DynDNS.org</option>
      <option value="1">TZO</option>
      </select>
      </td>
  </tr>

  <tr>
      <td width="30%"><font size=2><b><% multilang("Hostname"); %>:</b></td>
      <td width="70%"><input type="text" name="hostname" size="35" maxlength="35"></td>
  </tr>  
  
  <tr><td width="30%"><font size=2><b><% multilang("Interface"); %></b></td>
  <td width="35%">
  	<select name="interface" >
      <%  if_wan_list("rt");
      %>
      <!--<option value=100>LAN/br0</option>-->
  	</select>
  </td></tr>
  
</table>

<table border=0 width="500" cellspacing=4 cellpadding=0>
  <tr><td><hr size=1 noshade align=top></td></tr>
  <tr><font size=2><b>DynDns <% multilang("Settings"); %>:</b></font></tr>
  <tr>
      <td width="30%"><font size=2><b><% multilang("User"); %><% multilang(" Name"); %>:</b></td>
      <td width="70%"><input type="text" name="username" size="35" maxlength="35"></td>
  </tr>

  <tr>
      <td width="30%"><font size=2><b><% multilang("Password"); %>:</b></td>
      <td width="70%"><input type="password" name="password" size="35" maxlength="35"></td>
  </tr>
</table>

<table border=0 width="500" cellspacing=4 cellpadding=0>
  <tr><td><hr size=1 noshade align=top></td></tr>
  <tr><font size=2><b>TZO <% multilang("Settings"); %>:</b></font></tr>
  <tr>
      <td width="30%"><font size=2><b><% multilang("Email"); %>:</b></td>
      <td width="70%"><input type="text" name="email" size="35" maxlength="35"></td>
  </tr>

  <tr>
      <td width="30%"><font size=2><b><% multilang("Key"); %>:</b></td>
      <td width="70%"><input type="password" name="key" size="35" maxlength="35"></td>
  </tr>
</table>

  <br><br>
  <!--<input type="hidden" name="interface" value="all">-->
  <input type="submit" value="<% multilang("Add"); %>" name="addacc" onClick="return addClick()">
  <input type="submit" value="<% multilang("Modify"); %>" name="modify" onClick="return modifyClick()">
  <input type="submit" value="<% multilang("Remove"); %>" name="delacc" onClick="return removeClick()">
  </tr>

  <br><br>

<table border=0 width="800" cellspacing=4 cellpadding=0>
  <tr><font size=2><b><% multilang("Dynamic"); %> DNS <% multilang("Table"); %>:</b></font></tr>
  <% showDNSTable(); %>
</table>
  <br>
      <input type="hidden" value="/ddns.asp" name="submit-url">

  <script>
	updateState();
	deSelected();
  </script>
</form>
</blockquote>
</body>

</html>
