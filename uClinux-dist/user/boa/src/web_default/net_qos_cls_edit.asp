<HTML>
<HEAD>
<TITLE><% multilang("Add QoS Classification Rules"); %></TITLE>
<meta http-equiv="Content-Type" content="text/html" charset="utf-8">

<style>
SELECT {width:200px;}
</style>

<SCRIPT language="javascript" src="common.js"></SCRIPT>
<script type="text/javascript" src="share.js"> </script>
<SCRIPT language="javascript" type="text/javascript">

var dscps = new it_nr("dscplst", 
 new it(0, ""),
 new it(1, "default(000000)"), 
 new it(57, "AF13(001110)"), 
 new it(49, "AF12(001100)"), 
 new it(41, "AF11(001010)"),
 new it(33, "CS1(001000)"),
 new it(89, "AF23(010110)"),
 new it(81, "AF22(010100)"),
 new it(73, "AF21(010010)"),
 new it(65, "CS2(010000)"),
 new it(121, "AF33(011110)"),
 new it(113, "AF32(011100)"),
 new it(105, "AF31(011010)"),
 new it(97, "CS3(011000)"),
 new it(153, "AF43(100110)"),
 new it(145, "AF42(100100)"),
 new it(137, "AF41(100010)"),
 new it(129, "CS4(100000)"),
 new it(185, "EF(101110)"),
 new it(161, "CS5(101000)"),
 new it(193, "CS6(110000)"),
 new it(225, "CS7(111000)"));

<!--var protos = new Array("", "ICMP", "TCP", "UDP", "TCP/UDP");-->
var protos = new Array("", "TCP", "UDP", "ICMP", "TCP/UDP");
var states = new Array("disable", "enable");
var md802ps = new Array("", "0", "1", "2", "3", "4", "5", "6", "7");
//var iffs = new Array("", "LAN_1", "LAN_2", "LAN_3", "LAN_4");
var iffs = new it_nr("lanitf");
var quekeys = new it_nr("queuekey");
var oifkeys = new it_nr("outifkey");

var sel1 = new Array("phypt", "proto", "dscp", "sip", "smsk", "spts", "spte", "dip", "dmsk", "dpts", "dpte", "smac", "dmac",
					 "sip6", "sip6PrefixLen", "dip6", "dip6PrefixLen");
var sel2 = new Array("vlan1p");
var sel3 = new Array("ethType");

var ipversions = new Array("<% multilang("Please select IP version"); %>", "IPv4", "IPv6");
//default
quekeys.add(new it("", ""));
<% initRulePriority(); %>

iffs.add(new it(0, ""));
<% initQosLanif(); %>
<!--oifkeys.add(new it("65535|255", ""));-->
//oifkeys.add(new it("65535", ""));
//<% initOutif(); %>

//var opts = new Array(new Array("prio", quekeys), new Array("outif", oifkeys), new Array("proto", protos),
var opts = new Array(new Array("prio", quekeys), new Array("proto", protos),
	new Array("mdscp", dscps), new Array("m1p", md802ps), new Array("phypt", iffs),
	new Array("dscp", dscps), new Array("vlan1p", md802ps), new Array("IpProtocolType", ipversions) );

var rule = new it_nr("rule_");
var paramrl = sji_queryparam("rule");
rule.dec(paramrl);

function checkstr(str)
{
	var ch="";
	if(typeof str != "string") return 0;
	for(var i =0;i< str.length; i++) {
		ch = str.charAt(i);
		if(!(ch =="_"||(ch<="9"&&ch>="0")||(ch<="z"&&ch>="a")||(ch<="Z"&&ch>="A"))) return 0;
	}
	return 1;
}

function onChange_proto()
{
	for(var n2 in sel2)
	{
		var oin = document.getElementById(sel2[n2]);
		if(typeof oin == "undefined")continue;
		if(oin.tagName == "SELECT")oin.selectedIndex = 0;
		else oin.value = "";
	}

	for(var n1 in sel3)
	{
		var oin = document.getElementById(sel3[n1]);
		if(typeof oin == "undefined")continue;
		if(oin.tagName == "SELECT")oin.selectedIndex = 0;
		else oin.value = "";
	}
	
	with ( document.forms[0] )
	{
		if (proto.value == 5) {
			spts.disabled = true;
			spte.disabled = true;
			dpts.disabled = true;
			dpte.disabled = true;
		} else {
			spts.disabled = false;
			spte.disabled = false;
			dpts.disabled = false;
			dpte.disabled = false;
		}
	}
}

function onchange_sel1()
{
	for(var n2 in sel2)
	{
		var oin = document.getElementById(sel2[n2]);
		if(typeof oin == "undefined")continue;
		if(oin.tagName == "SELECT")oin.selectedIndex = 0;
		else oin.value = "";
	}
	
	for(var n1 in sel3)
	{
		var oin = document.getElementById(sel3[n1]);
		if(typeof oin == "undefined")continue;
		if(oin.tagName == "SELECT")oin.selectedIndex = 0;
		else oin.value = "";
	}
}

function onchange_sel2()
{
/*
	for(var n1 in sel1)
	{
		var oin = document.getElementById(sel1[n1]);
		if(typeof oin == "undefined")continue;
		if(oin.tagName == "SELECT")oin.selectedIndex = 0;
		else oin.value = "";
	}
	
	for(var n2 in sel3)
	{
		var oin = document.getElementById(sel3[n2]);
		if(typeof oin == "undefined")continue;
		if(oin.tagName == "SELECT")oin.selectedIndex = 0;
		else oin.value = "";
	}
*/
}

function onchange_sel3()
{
	for(var n1 in sel1)
	{
		var oin = document.getElementById(sel1[n1]);
		if(typeof oin == "undefined")continue;
		if(oin.tagName == "SELECT")oin.selectedIndex = 0;
		else oin.value = "";
	}
	
	for(var n2 in sel2)
	{
		var oin = document.getElementById(sel2[n2]);
		if(typeof oin == "undefined")continue;
		if(oin.tagName == "SELECT")oin.selectedIndex = 0;
		else oin.value = "";
	}
}

/********************************************************************
**          on document load
********************************************************************/
function on_init()
{	

	for(var i in opts)
	{
		var slit = document.getElementById(opts[i][0]);
		if(typeof slit == "undefined")continue;
		for(var j in opts[i][1])
		{
			if(j == "name" || (typeof opts[i][1][j] != "string" && typeof opts[i][1][j] != "number"))continue;
			slit.options.add(new Option(opts[i][1][j], j));
		}
		slit.selectedIndex = 0;
	}
	
	for(var key in rule)
	{
		if((typeof rule[key] != "string" && typeof rule[key] != "number"))continue;
		if(typeof form[key] == "undefined")continue;
		form[key].value =  rule[key];
	}
	

	displayByType();

}

/********************************************************************
**          on document submit
********************************************************************/
function on_submit() 
{
	with ( document.forms[0] )	{
		var sbmtstr = "addrule";
		if(paramrl != null)
			sbmtstr = "editrule";
		sbmtstr = sbmtstr+"&index="+index.value;
		if(!checkstr(name.value)) {
			name.value="";
			name.focus();
			alert("Rule Name is invalid!");
			return;
		} else {
			sbmtstr = sbmtstr+"&name="+name.value;
		}
		//sbmtstr = sbmtstr+"&state="+state.value;

		if(prio.value == "") {
			prio.focus();
			alert("Please assign used Queue!");
			return;
		} else {
			sbmtstr = sbmtstr+"&prio="+prio.value;
		}

		var qostype_select_type=-1;
		var sizes = document.all.qos_rule_type;

		for (i=0; i < document.all.qos_rule_type.length; i++) {
			if (sizes[i].checked==true) {
				qostype_select_type = i; 
			}
		}
		sbmtstr = sbmtstr+"&qos_rule_type="+qostype_select_type;

		//condition check
		if (phypt.value==0 && proto.value==0 && dscp.value==0 && (sip.value=="" || 
					sip.value=="0.0.0.0") && (spts.value==0 || spts.value=="") && (dip.value=="" || 
						dip.value=="0.0.0.0") && (dpts.value==0 || dpts.value=="") && vlan1p.value==0 && 
				smac.value=="" && dmac.value=="" && sip6.value=="" && dip6.value=="" && ethType.value=="" && 
				vendorclass.value=="" && duid_hw_type.value=="" && duid_mac.value=="" && opt125_ent_num.value=="")
		{
			alert("Need to specify one parameter at least!");
			return;
		}



		sbmtstr = sbmtstr+"&outif="+outif.value;
		sbmtstr = sbmtstr+"&markdscp="+mdscp.value;

		var vid = parseInt(mvid.value);
		if(vid<=0 || vid>=4096)
		{
			alert("Incorrect vlan id, shoule be 1~4095");
			mvid.focus();
			return;
		}
		sbmtstr = sbmtstr+"&markvid="+mvid.value;
		sbmtstr = sbmtstr+"&mark1p="+m1p.value;
		sbmtstr = sbmtstr+"&phyport="+phypt.value;
		sbmtstr = sbmtstr+"&proto="+proto.value;
		sbmtstr = sbmtstr+"&matchdscp="+dscp.value;	
		if ( <% checkWrite("IPv6Show"); %> && qostype_select_type==2 ) {
			sbmtstr = sbmtstr+"&IPversion="+IpProtocolType.value;
			if((document.forms[0].IpProtocolType.value == 0 ) && (qostype_select_type!=1) ) {  //EtherType don'e need IPVersion
				alert("Please assign IP version!");
				return;
			}
		}


		if(qostype_select_type==1)
		{
			if(ethType.value!=0 &&(ethType.value.length < 4 || ethType.value.length > 4 || ethType.value < 0800)) {
				ethType.focus();
				alert("Invalid Ethernet Type!");
				return;
			}
			//for ether type
			sbmtstr = sbmtstr+"&ethType="+ethType.value;
		}
		else if(qostype_select_type ==2)
		{
			// for IP/prototocl base		

			if (proto.value==5) {//RTP
				if (dpts.value!=0 && dpts.value!="")
				{
					alert("Protocol is RTP, can not specify Dst port!");
					return;
				}
			}

			// If this is a IPv4 rule
			if(document.forms[0].IpProtocolType.value == 1) {
				if(sip.value!=""&&!sji_checkip(sip.value)) {
					sip.value = "";
					sip.focus();
					alert("Src IP is invalid!");
					return;
				} else {
					sbmtstr = sbmtstr+"&sip="+sip.value;
				}

				if(smsk.value!=""&&!sji_checkmask(smsk.value)) {
					smsk.value="";
					smsk.focus();
					alert("Src Mask is invalid!");
					return;
				} else {
					sbmtstr = sbmtstr+"&smask="+smsk.value;
				}

				if(dip.value!=""&&!sji_checkip(dip.value)) {
					dip.value = "";
					dip.focus();
					alert("Dst IP is invalid!");
					return;
				} else {
					sbmtstr = sbmtstr+"&dip="+dip.value;
				}


				if(smsk.value!=""&&!sji_checkmask(smsk.value)) {
					smsk.value="";
					smsk.focus();
					alert("Src Mask is invalid!");
					return;
				} else {
					sbmtstr = sbmtstr+"&smask="+smsk.value;
				}

				if(dmsk.value!=""&&!sji_checkmask(dmsk.value)) {
					dmsk.value="";
					dmsk.focus();
					alert("Dst Mask is invalid!");
					return;
				} else {
					sbmtstr = sbmtstr+"&dmask="+dmsk.value;
				}


			}
			else {
				//If this is IPv6 rule.
				if(document.forms[0].IpProtocolType.value == 2){				
					if(sip6.value != ""){
						if (! isGlobalIpv6Address(sip6.value) ){
							alert("Invalid Source IPv6 address!");					
							return;
						}
						if ( sip6PrefixLen.value != "" ) {
							var prefixlen= getDigit(sip6PrefixLen.value, 1);
							if (prefixlen > 128 || prefixlen <= 0) {
								alert("Invalid Source IPv6 prefix length!");							
								return;
							}
						}
					}

					if(dip6.value != ""){
						if (! isGlobalIpv6Address(dip6.value) ){
							alert("Invalid Destination IPv6 address!");					
							return;
						}
						if ( dip6PrefixLen.value != "" ) {
							var prefixlen= getDigit(dip6PrefixLen.value, 1);
							if (prefixlen > 128 || prefixlen <= 0) {
								alert("Invalid destination IPv6 prefix length!");							
								return;
							}
						}
					}
					sbmtstr = sbmtstr+"&sip6="+sip6.value;
					sbmtstr = sbmtstr+"&dip6="+dip6.value;
					sbmtstr = sbmtstr+"&sip6PrefixLen="+sip6PrefixLen.value;
					sbmtstr = sbmtstr+"&dip6PrefixLen="+dip6PrefixLen.value;					
				}
			}

			if((spts.value!="") && (spts.value<=0||spts.value>65536)) {
				spts.focus();
				alert("Invalid Src Start Port!");
				return;
			} else {		     
				if (spts.value!=0 && proto.value!=1 && proto.value!=2 && proto.value!=4 ) {//TCP/UDP			
					alert("Protocol is not TCP/UDP, can not specify port!");
					return;
				}		
				sbmtstr = sbmtstr+"&spts="+spts.value;
			}

			if((spte.value!="") && (spte.value<=0||spte.value>65536)) {
				spte.focus();
				alert("Invalid Src End Port!");
				return;
			} else {
				if (spte.value!=0 && proto.value!=1 && proto.value!=2 && proto.value!=4) {//TCP/UDP			
					alert("Protocol is not TCP/UDP, can not specify port!");
					return;
				}
				sbmtstr = sbmtstr+"&spte="+spte.value;
			}	

			if((dpts.value!="") && (dpts.value<=0||dpts.value>65536)) {
				dpts.focus();
				alert("Invalid Dst Start Port!");
				return;
			} else {
				if (dpts.value!=0 && proto.value!=1 && proto.value!=2 && proto.value!=4) {//TCP/UDP			
					alert("Protocol is not TCP/UDP, can not specify port!");
					return;
				}
				sbmtstr = sbmtstr+"&dpts="+dpts.value;
			}

			if((dpte.value!="") && (dpte.value<=0||dpte.value>65536)) {
				dpte.focus();
				alert("Invalid Dst End Port!");
				return;
			} else {
				if (dpte.value!=0  && proto.value!=1 && proto.value!=2 && proto.value!=4) {//TCP/UDP			
					alert("Protocol is not TCP/UDP, can not specify port!");
					return;
				}
				sbmtstr = sbmtstr+"&dpte="+dpte.value;			
			}
		}
		else if(qostype_select_type ==3)
		{
			//mac base
			if(smac.value!=""&&!sji_checkmac2(smac.value)) {
				smac.value = "";
				smac.focus();
				alert("Invalid Src MAC!");
				return;
			} else {
				sbmtstr = sbmtstr+"&smac="+smac.value;
			}

			if(dmac.value!=""&&!sji_checkmac2(dmac.value)) {
				dmac.value = "";
				dmac.focus();
				alert("Invalid Dst MAC!");
				return;
			} else {
				sbmtstr = sbmtstr+"&dmac="+dmac.value;
			}	

		}
		else if(qostype_select_type==4)
		{
			//for dhcp opt
			var select_dhcpopt_type=-1;
			var sizes = document.all.dhcpopt_type;

			for (i=0; i < document.all.dhcpopt_type.length; i++) {
				if (sizes[i].checked==true) {
					select_dhcpopt_type = i; 
				}
			}	
			sbmtstr = sbmtstr+"&dhcpopt_type="+select_dhcpopt_type;

			if(select_dhcpopt_type==0)
			{
				//option 60
				if(vendorclass.value=="")
				{
					alert("vendorclass should not be empty!");
					return;
				}

				if(!checkString(vendorclass.value)) {
					vendorclass.value="";
					vendorclass.focus();
					alert("vendorclass is invalid!");
					return;
				} else {
					sbmtstr = sbmtstr+"&vender_class="+vendorclass.value;
				}
			}
			else if(select_dhcpopt_type==1)
			{
				//option 61
				var select_duid_type=-1;
				var sizes = document.all.duid_type;

				for (i=0; i < document.all.duid_type.length; i++) {
					if (sizes[i].selected==true) {
						select_duid_type = i; 
					}
				}	

				sbmtstr = sbmtstr+"&dhcpopt_duid_type="+select_duid_type;

				if(opt61_iaid.value!=""&&!checkDigit(opt61_iaid.value)) {
					opt61_iaid.value="";
					opt61_iaid.focus();
					alert("opt61_iaid is invalid!");
					return;
				}

				if(select_duid_type ==0 )
				{	
					duid_ent_num.value = "";
					duid_ent_id.value = "";

					if(duid_hw_type.value!=""&&!checkDigit(duid_hw_type.value)) {
						duid_hw_type.value="";
						duid_hw_type.focus();
						alert("duid_hw_type is invalid!");
						return;
					}


					if(duid_time.value!=""&&!checkDigit(duid_time.value)) {
						duid_time.value="";
						duid_time.focus();
						alert("duid_time is invalid!");
						return;
					}

					if(duid_mac.value!=""&&!sji_checkmac2(duid_mac.value)) {
						duid_mac.value="";
						duid_mac.focus();
						alert("duid_mac is invalid!");
						return;
					}

					if(opt61_iaid.value==""||duid_hw_type.value==""||duid_time.value==""||duid_mac.value=="")
					{
						alert("Need to fill value!!");
						return;
					}

				}	
				else if(select_duid_type ==1 )
				{
					duid_hw_type.value="";
					duid_time.value = "";
					duid_mac.value = "";

					if(duid_ent_num.value!="" &&!checkDigit(duid_ent_num.value)) {
						duid_ent_num.value="";
						duid_ent_num.focus();
						alert("duid_ent_num is invalid!");
						return;
					}

					if(duid_ent_id.value!="" &&!checkString(duid_ent_id.value)) {
						duid_ent_id.value="";
						duid_ent_id.focus();
						alert("duid_ent_id is invalid!");
						return;
					}
					if(opt61_iaid.value==""||duid_ent_num.value==""||duid_ent_id.value=="")
					{
						alert("Need to fill value!!");
						return;
					}


				}
				else if(select_duid_type ==1 )
				{
					duid_ent_num.value = "";
					duid_ent_id.value = "";
					duid_time.value = "";

					if(duid_hw_type.value!="" &&!checkDigit(duid_hw_type.value)) {
						duid_hw_type.value="";
						duid_hw_type.focus();
						alert("duid_hw_type is invalid!");
						return;
					}

					if(duid_mac.value!="" &&!checkMac(duid_mac.value)) {
						duid_mac.value="";
						duid_mac.focus();
						alert("duid_mac is invalid!");
						return;
					}

					if(opt61_iaid.value==""||duid_hw_type.value==""||duid_mac.value=="")
					{
						alert("Need to fill value!!");
						return;
					}
				}	

				sbmtstr = sbmtstr+"&opt61_iaid="+opt61_iaid.value;

				sbmtstr = sbmtstr+"&duid_hw_type="+duid_hw_type.value;

				sbmtstr = sbmtstr+"&duid_time="+duid_time.value;

				sbmtstr = sbmtstr+"&duid_mac="+duid_mac.value;

				sbmtstr = sbmtstr+"&duid_ent_num="+duid_ent_num.value;

				sbmtstr = sbmtstr+"&duid_ent_id="+duid_ent_id.value;				

			}	
			else if(select_dhcpopt_type==2)
			{
				//option 125        
				if(!checkDigit(opt125_ent_num.value)) {
					opt125_ent_num.value="";
					opt125_ent_num.focus();
					alert("opt125_ent_num is invalid!");
					return;
				}	

				if(opt125_manufacturer.value!=""&&!checkString(opt125_manufacturer.value)) {
					opt125_manufacturer.value="";
					opt125_manufacturer.focus();
					alert("opt125_manufacturer is invalid!");
					return;
				}


				if(opt125_product_class.value!=""&&!checkString(opt125_product_class.value)) {
					opt125_product_class.value="";
					opt125_product_class.focus();
					alert("opt125_product_class is invalid!");
					return;
				}

				if(opt125_model.value!=""&&!checkString(opt125_model.value)) {
					opt125_model.value="";
					opt125_model.focus();
					alert("opt125_model is invalid!");
					return;
				}

				if(opt125_serial.value!=""&&!checkString(opt125_serial.value)) {
					opt125_serial.value="";
					opt125_serial.focus();
					alert("opt125_serial is invalid!");
					return;
				}

				if(opt125_ent_num.value=="" ||(opt125_manufacturer.value=="" &&opt125_product_class.value==""&&opt125_model.value==""&&opt125_serial.value==""))
				{
					alert("Should not be emplty");
					return;
				}

				sbmtstr = sbmtstr+"&opt125_ent_num="+opt125_ent_num.value;

				sbmtstr = sbmtstr+"&opt125_manufacturer="+opt125_manufacturer.value;

				sbmtstr = sbmtstr+"&opt125_product_class="+opt125_product_class.value;

				sbmtstr = sbmtstr+"&opt125_model="+opt125_model.value;

				sbmtstr = sbmtstr+"&opt125_serial="+opt125_serial.value;																		
			}

		}

		sbmtstr = sbmtstr+"&vlan1p="+vlan1p.value;	

		lst.value = sbmtstr;
		submit();
	}
}

function protocolChange()
{	
	// If protocol is IPv4 only.
	if(document.forms[0].IpProtocolType.value == 1){			
		if (document.getElementById)  // DOM3 = IE5, NS6
		{
			document.getElementById('ip4tbl').style.display = 'block';
			document.getElementById('ip6tbl').style.display = 'none';						
		}
		else {
			if (document.layers == false) // IE4
			{
				document.all.ip4tbl.style.display = 'block';
				document.all.ip6tbl.style.display = 'none';						
			}
		}	
		
						if(sip.value=="0.0.0.0")
					sip.value = "";
				if(dip.value=="0.0.0.0")
					dip.value = "";		
	}
	// If protocol is IPv6 only.
	else if(document.forms[0].IpProtocolType.value == 2){			
		if (document.getElementById)  // DOM3 = IE5, NS6
		{
			document.getElementById('ip4tbl').style.display = 'none';
			document.getElementById('ip6tbl').style.display = 'block';			
		}
		else {
			if (document.layers == false) // IE4
			{
				document.all.ip4tbl.style.display = 'none';
				document.all.ip6tbl.style.display = 'block';						
			}
		}
						if(sip6.value=="::")
					sip6.value = "";
				if(dip6.value=="::")
					dip6.value = "";
					
					if(sip6PrefixLen.value==0)
						sip6PrefixLen.value="";
					if(dip6PrefixLen.value==0)
						dip6PrefixLen.value="";	
	}	
	
		        if(spts.value==0)
				spts.value="";
		        if(spte.value==0)
				spte.value="";				
		        if(dpts.value==0)
				dpts.value="";				
		        if(dpte.value==0)
				dpte.value="";		
}


function displayByType() 
{
	var qostype_select_type=rule["ipqos_rule_type"];
	var sizes = document.all.qos_rule_type;

	document.all.port_base.style.display = "none";
	document.all.ip_proto_base.style.display = "none";
	document.all.mac_base.style.display = "none";
	document.all.ether_type_base.style.display = "none";
	document.all.dhcp_opt_base.style.display = "none";
	document.all.ipprotbl.style.display = 'none';						

	if(mvid.value=='0')
		mvid.value = '';

	if(rule["ipqos_rule_type"]== "")
	{
		qostype_select_type=0
	}    

	 displayEach(qostype_select_type);
}

function displayEach(qostype_select_type)
{
	document.all.port_base.style.display = "none";
	document.all.ip_proto_base.style.display = "none";
	document.all.mac_base.style.display = "none";
	document.all.ether_type_base.style.display = "none";
	document.all.dhcp_opt_base.style.display = "none";
	document.all.ipprotbl.style.display = 'none';						

	if(typeof document.all.qos_rule_type[qostype_select_type] !== 'undefined')
		document.all.qos_rule_type[qostype_select_type].checked=true;
		
	if(qostype_select_type==0)
	{  //Port based
		document.all.port_base.style.display = "block";
	}
	else if(qostype_select_type==1)
	{ //EtherType based
		document.all.ether_type_base.style.display = "block";
		if(ethType.value=="0000")
			ethType.value="";
	}
	else if(qostype_select_type==2)
	{ //IP,Protocol based
		document.all.ip_proto_base.style.display = "block";
		if ( <% checkWrite("IPv6Show"); %> )
		{
			if (document.getElementById)  // DOM3 = IE5, NS6
			{
				document.getElementById('ipprotbl').style.display = 'block';						
			}
			else {
				if (document.layers == false) // IE4
				{
					document.all.ipprotbl.style.display = 'block';						
				}
			}

			protocolChange();
		}
	
			
					
	}
	else if(qostype_select_type==3)
	{ //Mac address based
		document.all.mac_base.style.display = "block";
		if(smac.value=="00:00:00:00:00:00")
			smac.value="";
		if(dmac.value=="00:00:00:00:00:00")
			dmac.value="";	
	}
	else if(qostype_select_type==4)
	{ //DHCP option based
		document.all.dhcp_opt_base.style.display = "block";
		dhcpopt_display_by_type();
	}
}

function ruleType_click() 
{
	var qostype_select_type=-1;
	var sizes = document.all.qos_rule_type;

	for (i=0; i < document.all.qos_rule_type.length; i++) {
		if (sizes[i].checked==true) {
			qostype_select_type = i; 
		}
	}

	 displayEach(qostype_select_type);
}

function dhcpopt_display_by_type()
{
	var select_type=rule["dhcpopt_type_select"];
	var sizes = document.all.qos_rule_type;

	document.all.dhcp_opt_base_opt60.style.display = "none";
	document.all.dhcp_opt_base_opt61.style.display = "none";
	document.all.dhcp_opt_base_opt125.style.display = "none";
	
	if(typeof select_type == "undefined" ||(rule["dhcpopt_type_select"]== ""))
	{
		select_type=0;
	}
	document.qosrule.dhcpopt_type[select_type].checked=true;
	dhcpopt_displayEach(select_type);
}

function dhcpopt_click()
{
	var select_type=-1;
	var sizes = document.all.dhcpopt_type;

	for (i=0; i < document.all.dhcpopt_type.length; i++) {
		if (sizes[i].checked==true) {
			select_type = i; 
		}
	}

	dhcpopt_displayEach(select_type);
}

function dhcpopt_displayEach(select_type)
{
	document.all.dhcp_opt_base_opt60.style.display = "none";
	document.all.dhcp_opt_base_opt61.style.display = "none";
	document.all.dhcp_opt_base_opt125.style.display = "none";

	if(select_type==0)
	{ 
		document.all.dhcp_opt_base_opt60.style.display = "block";
	}
	else if(select_type==1)
	{ 
		
		document.all.dhcp_opt_base_opt61.style.display = "block";
		//document.qosrule.duid_type.selectedIndex == 0;	
	}
	else if(select_type==2)
	{ 
		document.all.dhcp_opt_base_opt125.style.display = "block";
		if(document.all.opt125_ent_num.value=="0")
			document.all.opt125_ent_num.value="";

	}
	
	update_ui();
}

function hide_by_class(str_class)
{
	var elements = document.getElementsByClassName(str_class);

	for (var i = 0 ; i < elements.length ; i++)
		elements[i].style.display = 'none';
}

function clear_inputs(clear_select)
{
	with(document.qosrule)
	{
		opt60_enable.checked = false;
		vendorclass.value = "";
		opt61_enable.checked = false;
		opt61_iaid.value = "";
		duid_type.selectedIndex = 0;
		duid_hw_type.value= "";
		duid_time.value= "";
		duid_mac.value = "";
		duid_ent_num.value = "";
		duid_ent_id.value = "";
		opt125_enable.checked = false;
		opt125_ent_num.value = "";
		opt125_manufacturer.value = "";
		opt125_product_class.value = "";
		opt125_model.value = "";
		opt125_serial.value = "";
	}
	update_ui();
}

function show_by_class(str_class)
{
	var elements = document.getElementsByClassName(str_class);

	for (var i = 0 ; i < elements.length ; i++)
	    elements[i].style.display = '';
}

function update_ui()
{
	var select_type=-1;
	var sizes = document.all.dhcpopt_type;

	for (i=0; i < document.all.dhcpopt_type.length; i++) {
		if (sizes[i].checked==true) {
			select_type = i; 
		}
	}
	if(select_type==1)
	{
	
		show_by_class('dhcp_opt_61');

		if(document.qosrule.duid_type.selectedIndex == 0)
		{
			//type 1: DUID-LLT
			hide_by_class('duid_ll');
			hide_by_class('duid_en');
			show_by_class('duid_llt');
		}
		else if(document.qosrule.duid_type.selectedIndex == 1)
		{
			//type 2: DUID-EN
			hide_by_class('duid_ll');
			hide_by_class('duid_llt');
			show_by_class('duid_en');
		}
		else if(document.qosrule.duid_type.selectedIndex == 2)
		{
			//type 3: DUID-LL
			hide_by_class('duid_llt');
			hide_by_class('duid_en');
			show_by_class('duid_ll');
		}
		else
		{
			//default
			document.qosrule.duid_type.selectedIndex == 0;
			hide_by_class('duid_ll');
			hide_by_class('duid_en');
			show_by_class('duid_llt');
		}
	}
	else
		hide_by_class('dhcp_opt_61');


}

</SCRIPT>
</HEAD>

<body onLoad="on_init();">
	<blockquote>
		<DIV align="left" style="padding-left:20px; padding-top:5px;">
			<form id="form" action="/boaform/admin/formQosRuleEdit" method="post"  name="qosrule">
				<h2><font color="#0000FF"><% multilang("Add QoS Classification Rules"); %></font></h2>				
				<div class="tip" style="width:90% ">
					&nbsp;&nbsp;<% multilang("This page is used to add a IP QoS classification rule."); %><br>
				</div>
				<br>				
				<hr class="sep" size="1" width="100%">
				<br>				
				
				
				<table cellSpacing="1" cellPadding="0" border="0">				
				        <tr><td width="260px"><font size=2><b><% multilang("Rule"); %><% multilang(" Name"); %>:</b></td><td><input type="text" id="name" size="22" style="width:200px "></td></tr>					
					
					<tr><td colspan="2">&nbsp; </td></tr>
					<tr><td colspan="2"><b><% multilang("Assign"); %> IP Precedence/DSCP/802.1p</b></td></tr>					
					<tr><td colspan="2">&nbsp; </td></tr>
					<tr><td width="160px"><font size=2><b>Precedence:</b></td><td><select id="prio" size="1"></select></td></tr>
					<tr><td width="160px"><font size=2><b><% multilang("Vlan ID"); %> (1~4095): </b></td><td><input type="text" id="mvid" size="15" maxlength="4"></td></tr>					
					<tr><td width="160px"><font size=2><b>DSCP:</b></td><td><select id="mdscp" size="1"></select></td></tr>
					<tr><td width="160px"><font size=2><b>802.1p:</b></td><td><select id="m1p" size="1"></select></td></tr>
					
					<tr><td colspan="2">&nbsp; </td></tr>
					<tr><td colspan="2"><b><% multilang("Specify Traffic Classification Rule"); %></b></td></tr>
					<tr><td colspan="2">&nbsp; </td></tr>
				

					<table cellSpacing="1" cellPadding="0" border="0">
					<tr>
						<td><b>IP QoS Rule by type:</b></td>
						<td><font size=2><input type="radio"  name=qos_rule_type value=0 onClick=ruleType_click();><% multilang("Port"); %></td>	
						<td><font size=2><input type="radio"  name=qos_rule_type value=1 onClick=ruleType_click();><% multilang("Ethery Type"); %></td>	
						<td><font size=2><input type="radio"  name=qos_rule_type value=2 onClick=ruleType_click();><% multilang("IP/Protocol"); %></td>	
						<td><font size=2><input type="radio"  name=qos_rule_type value=3 onClick=ruleType_click();><% multilang("MAC address"); %></td>	
						<% ipqos_dhcpopt(); %>
					</tr>
					</table>
					
					<tr><td width="260px" colspan="2"><font size=2><b><% multilang("WAN"); %>:</b></td><td><select id="outif" size="1" onChange="onchange_sel1();"><% if_wan_list("queueITF"); %></select></td></tr>

	
					<div id="port_base" style="display:none;">
				       <table cellSpacing="1" cellPadding="0" border="0">
				        <tr><td colSpan="1">&nbsp; </td></tr>
					<tr><td width="260px" colspan="2"><font size=2><b><% multilang("Physical Port"); %>:</b></td><td><select id="phypt" size="1" onChange="onchange_sel1();"></select></td></tr>
				       </table>
				</div>

				<div id='ipprotbl' style="display:none">
				<table cellSpacing="1" cellPadding="0" border="0">								
					<tr><td width="260px"><font size=2><b>IP <% multilang("Version"); %>:</b></td>
						<td><select id="IpProtocolType" size="1" onChange="protocolChange()" name="IpProtocolType">
							</select>
						</td>
					</tr>					
				</table>
				</div>

				<div id="ip_proto_base" style="display:none;">

					<table cellSpacing="1" cellPadding="0" border="0">
					<tr><td colSpan="1">&nbsp; </td></tr>
					<tr><td width="260px"><font size=2><b><% multilang("Protocol"); %>:</b></td><td><select id="proto" size="1" onChange="onChange_proto();"></select></td></tr>
					<tr><td width="260px"><font size=2><b>DSCP:</b></td><td><select id="dscp" size="1" onChange="onchange_sel1();"></select></td></tr>
					</table>
					<div id='ip4tbl' style="display:none;">
					<table cellSpacing="1" cellPadding="0" border="0">
						<tr><td width="260px"><font size=2><b><% multilang("Source"); %> IP: </b></td><td><input type="text" id="sip" size="15" maxlength="15" style="width:200px " onChange="onchange_sel1();"></td></tr>
						<tr><td width="160px"><font size=2><b><% multilang("Source Mask"); %>: </b></td><td><input type="text" id="smsk" size="15" maxlength="15" style="width:200px " onChange="onchange_sel1();"></td></tr>					
						<tr><td width="160px"><font size=2><b><% multilang("Destination"); %> IP: </b></td><td><input type="text" id="dip" size="15" maxlength="15" style="width:200px " onChange="onchange_sel1();"></td></tr>
						<tr><td width="160px"><font size=2><b><% multilang("Destination Mask"); %>: </b></td><td><input type="text" id="dmsk" size="15" maxlength="15" style="width:200px " onChange="onchange_sel1();"></td></tr>					
					</table>				
					</div>
				
					<div id='ip6tbl' style="display:none">
					<table cellSpacing="1" cellPadding="0" border="0">
						<tr><td width="260px"><font size=2><b><% multilang("Source"); %> IP: </b></td><td><input type="text" id="sip6" size="36" maxlength="39" style="width:200px " onChange="onchange_sel1();"></td></tr>
						<tr><td width="160px"><font size=2><b><% multilang("Source Prefix Length"); %>: </b></td><td><input type="text" id="sip6PrefixLen" size="15" maxlength="15" style="width:200px " onChange="onchange_sel1();"></td></tr>					
						<tr><td width="160px"><font size=2><b><% multilang("Destination"); %> IP: </b></td><td><input type="text" id="dip6" size="36" maxlength="39" style="width:200px " onChange="onchange_sel1();"></td></tr>
						<tr><td width="160px"><font size=2><b><% multilang("Destination Prefix Length"); %>: </b></td><td><input type="text" id="dip6PrefixLen" size="15" maxlength="15" style="width:200px " onChange="onchange_sel1();"></td></tr>					
					</table>
					 </div>
					<table cellSpacing="1" cellPadding="0" border="0">
					<tr><td width="260px"><font size=2><b><% multilang("Source Port"); %>: </b></td><td><input type="text" id="spts" size="5" maxlength="5" style="width:97px" onChange="onchange_sel1();">:<input type="text" id="spte" size="5" maxlength="5" style="width:97px" onChange="onchange_sel1();"></td></tr>
					<tr><td width="160px"><font size=2><b><% multilang("Destination Port"); %>: </b></td><td><input type="text" id="dpts" size="5" maxlength="5" style="width:97px" onChange="onchange_sel1();">:<input type="text" id="dpte" size="5" maxlength="5" style="width:97px" onChange="onchange_sel1();"></td></tr>
					
					</table>
				</div>

				<div id="mac_base" style="display:none;">
					<table cellSpacing="1" cellPadding="0" border="0">
					<tr><td colSpan="1">&nbsp; </td></tr>
					<tr><td width="160px"><font size=2><b><% multilang("Source"); %> MAC:</b></td><td><input type="text" id="smac" size="17" maxlength="17" style="width:200px " onChange="onchange_sel1();"></td></tr>
					<tr><td width="160px"><font size=2><b><% multilang("Destination"); %> MAC:</b></td><td><input type="text" id="dmac" size="17" maxlength="17" style="width:200px " onChange="onchange_sel1();"></td></tr>
					</table>
				</div>	

			

				<div id="ether_type_base" style="display:none;">
					<table cellSpacing="1" cellPadding="0" border="0">
					<tr><td colSpan="1">&nbsp; </td></tr>
					<tr><td width="260px"><font size=2><b>Ethernet Type:</b></td><td><b>0x</b><input type="text" id="ethType" size="5" maxlength="5" style="width:97px" onChange="onchange_sel3();"></td></tr>
					</table>
				</div>


				<div id="dhcp_opt_base" style="display:none;">
				<table cellSpacing="1" cellPadding="0" border="0">
                                    	<tr><td colSpan="1"><font size=2><b><% multilang("DHCP Options"); %>:</b></font> </td>
                               
						<td width="160px"><font size=2><input type="radio"  name=dhcpopt_type value=0 onClick=dhcpopt_click();><% multilang("Option 60"); %></td>	
						<td width="160px"><font size=2><input type="radio"  name=dhcpopt_type value=1 onClick=dhcpopt_click();><% multilang("Option 61"); %></td>
						<td width="160px"><font size=2><input type="radio"  name=dhcpopt_type value=2 onClick=dhcpopt_click();><% multilang("Option 125"); %></td>	
					
                                        </tr>
					</table>
<div id="dhcp_opt_base_opt60" style="display:none;">    
	<table cellSpacing="1" cellPadding="0" border="0">                              
<tr>
    <font size=2><% multilang("DHCP Option 60"); %>:</td>
</tr>
<tr class="dhcp_opt_60">
    <td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("Value"); %>:</td>
 <td><input type="text" name="vendorclass" size="32" maxlength="100" value="<% ipqos_dhcpopt_getoption60(); %>"></td>  
    
</tr>
<tr>

</table>	
</div>

<div id="dhcp_opt_base_opt61" style="display:none;">                                  
	<table cellSpacing="1" cellPadding="0" border="0">
	<font size=2><% multilang("DHCP Option 61"); %>:</td>

<tr class="dhcp_opt_61">
	<td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("IAID"); %>:</td>
	<td><input type="text" name="opt61_iaid" size="20" maxlength="10"></td>
</tr>
<tr class="dhcp_opt_61">
	<td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("DUID Type"); %>:</td>
	<td><select size="1" name="duid_type" onChange="update_ui()">
		<option selected value=1><% multilang("DUID-LLT"); %></option>
		<option value=2><% multilang("DUID-EN"); %></option>
		<option value=3><% multilang("DUID-LL"); %></option>
	</td>
</tr>
<tr class="dhcp_opt_61 duid_llt duid_ll">
	<td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("Hardware Type"); %>:</td>
	<td><input type="text" name="duid_hw_type" size="20" maxlength="10"></td>
</tr>
<tr class="dhcp_opt_61 duid_llt">
	<td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("Time"); %>:</td>
	<td><input type="text" name="duid_time" size="20" maxlength="20"></td>
</tr>
<tr class="dhcp_opt_61 duid_llt duid_ll">
	<td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("Link-layer Address"); %>:</td>
	<td><input type="text" name="duid_mac" size="20" maxlength="20">(xx:xx:xx:xx:xx:xx)</td>
</tr>
<tr class="dhcp_opt_61 duid_en">
	<td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("Enterprise Number"); %>:</td>
	<td><input type="text" name="duid_ent_num" size="20" maxlength="10"></td>
</tr>
<tr class="dhcp_opt_61 duid_en">
	<td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("Identifier"); %>:</td>
    <td><input type="text" name="duid_ent_id" size="20" maxlength="32"></td>
</tr>
<tr>
</table>
</div>


<div id="dhcp_opt_base_opt125" style="display:none;">                                  
	<table cellSpacing="1" cellPadding="0" border="0">
    <font size=2><% multilang("DHCP Option 125"); %>:</td>
</tr>
<tr class="dhcp_opt_125">
    <td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("Enterprise Number"); %>:</td>
    <td><input type="text" name="opt125_ent_num" size="20" maxlength="10"></td>
</tr>
<tr class="dhcp_opt_125">
    <td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("Manufacturer OUI"); %>:</td>
    <td><input type="text" name="opt125_manufacturer" size="20" maxlength="32"></td>
</tr>
<tr class="dhcp_opt_125">
    <td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("Product Class"); %>:</td>
    <td><input type="text" name="opt125_product_class" size="20" maxlength="32"></td>
</tr>
<tr class="dhcp_opt_125">
    <td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("Model Name"); %>:</td>
    <td><input type="text" name="opt125_model" size="20" maxlength="32"></td>
</tr>
<tr class="dhcp_opt_125">
    <td><font size=2>&nbsp;&nbsp;&nbsp;&nbsp;<% multilang("Serial Number"); %>:</td>
    <td><input type="text" name="opt125_serial" size="20" maxlength="32"></td>
</tr>
</table>
</div>

</div>

<p>
				<div id="configuration_2" style="display:none;">
					<table cellSpacing="1" cellPadding="0" border="0">
					<tr><td colSpan="2">&nbsp; </td></tr>
					<tr><td colSpan="2"><font size=2><b><% multilang("Configuration"); %> - 2</b></td></tr>
					<tr><td width="260px"><font size=2><b>802.1p:</b></td><td><select id="vlan1p" size="1" onChange="onchange_sel2();"></select></td></tr>
					</table>
				</div>	
				</div>

				<hr class="sep" size="1" width="100%">
				<br>
				<input type="button" class="button" onClick="on_submit();" value="<% multilang("Apply Changes"); %>">
				<input type="hidden" name="submit-url" value="/net_qos_cls.asp">
				<input type="hidden" name="lst" value="">
				<input type="hidden" name="index" value="0">
				</table>
			</form>
		</DIV>
	</blockquote>
</body>
</html>
