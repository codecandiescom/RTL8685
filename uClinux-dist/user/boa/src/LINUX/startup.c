/* startup.c - kaohj */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/route.h>
#include <linux/atm.h>
#include <linux/atmdev.h>
#include <crypt.h>
#ifdef EMBED
#include <linux/config.h>
#else
#include "../../../../include/linux/autoconf.h"
#endif
#include "../defs.h"

#include "mibtbl.h"
#include "utility.h"
#ifdef WLAN_SUPPORT

#if defined(_LINUX_2_6_) || defined(_LINUX_3_4_)
#include "wireless.h"
#else
#include <linux/wireless.h>
#endif // 2.6

#endif

#include "debug.h"
// Mason Yu
#include "syslog.h"

#if defined(CONFIG_RTK_L34_ENABLE)
#if defined(CONFIG_GPON_FEATURE) || defined(CONFIG_EPON_FEATURE)
#include <rtk_rg_liteRomeDriver.h>
#endif
#else
#if defined(CONFIG_GPON_FEATURE)
#include "rtk/gpon.h"
#endif
#if defined(CONFIG_EPON_FEATURE)
#include "rtk/epon.h"
#endif
#endif

int startLANAutoSearch(const char *ipAddr, const char *subnet);
int isDuplicate(struct in_addr *ipAddr, const char *device);

#ifdef CONFIG_DEV_xDSL
//--------------------------------------------------------
// xDSL startup
// return value:
// 0  : not start by configuration
// 1  : successful
// -1 : failed
int startDsl()
{
	unsigned char init_line;
	unsigned short dsl_mode;
	int adslmode;
	int ret;

#ifdef CONFIG_VDSL
	//enable/disable dsl log
	system("/bin/adslctrl debug 9");
#endif /*CONFIG_VDSL*/


	ret = 1;
	if (mib_get(MIB_INIT_LINE, (void *)&init_line) != 0) {
		if (init_line == 1) {
			// start adsl
		  #ifdef CONFIG_VDSL
			adslmode=0;
		  #else
			mib_get(MIB_ADSL_MODE, (void *)&dsl_mode);
			adslmode=(int)(dsl_mode & (ADSL_MODE_GLITE|ADSL_MODE_T1413|ADSL_MODE_GDMT));	// T1.413 & G.dmt
		  #endif /*CONFIG_VDSL*/
			adsl_drv_get(RLCM_PHY_START_MODEM, (void *)&adslmode, 4);
			ret = setupDsl();
		}
		else
			ret = 0;
	}
	else
		ret = -1;
	return ret;
}
#endif


//--------------------------------------------------------
// Find the minimun WLAN-side link MRU
// It is used to set the LAN-side MTU(MRU) for the
// path-mtu problem.
// RETURN: 0: if failed
//	 : others: the minimum MRU for the WLAN link
static int get_min_wan_mru()
{
	int vcTotal, i, pmtu;
	MIB_CE_ATM_VC_T Entry;

	vcTotal = mib_chain_total(MIB_ATM_VC_TBL);
	pmtu = 1500;

	for (i = 0; i < vcTotal; i++)
	{
		/* get the specified chain record */
		if (!mib_chain_get(MIB_ATM_VC_TBL, i, (void *)&Entry))
			return 0;

		if (Entry.enable == 0)
			continue;

		if (Entry.mtu < pmtu)
			pmtu = Entry.mtu;
	}

	return pmtu;
}

//--------------------------------------------------------
// Ethernet LAN startup
// return value:
// 1  : successful
// -1 : failed
#define ConfigWlanLock "/var/run/configWlanLock"

#if defined(CONFIG_LUNA) && defined(CONFIG_RTK_RG_INIT)
#include "rtusr_rg_api.h"
#endif

int startELan()
{
	unsigned char value[6];
	int vInt;
	char macaddr[13];
	char ipaddr[16];
	char subnet[16];
	char timeOut[6];
	int status=0;
	int i;
#ifdef WLAN_MBSSID
	char para2[20];
#endif
#ifdef WLAN_SUPPORT
	FILE *f;
#endif

#ifdef CONFIG_RTL8672NIC
#ifdef WIFI_TEST
	//for wifi test
	mib_get(MIB_WLAN_BAND, (void *)value);
	if(value[0]==4 || value[0]==5){//wifi
		status|=va_cmd("/bin/ethctl",2,1,"wifi","1");
	}
	else
#endif
	{
#ifdef WLAN_SUPPORT
	// to support WIFI logo test mode.....
	mib_get(MIB_WIFI_SUPPORT, (void*)value);
	if(value[0]==1)
	{
		mib_get(MIB_WLAN_BAND, (void *)value);
		if(value[0]==2 || value[0]==3)
			status|=va_cmd("/bin/ethctl",2,1,"wifi","1");
		else
			status|=va_cmd("/bin/ethctl",2,1,"wifi","0");
	}
	else
		status|=va_cmd("/bin/ethctl",2,1,"wifi","0");
#endif
	}
#endif

	if (mib_get(MIB_ELAN_MAC_ADDR, (void *)value) != 0)
	{
#ifdef WLAN_SUPPORT
		if((f = fopen(ConfigWlanLock, "w")) == NULL)
			return;
		fclose(f);
#endif
		snprintf(macaddr, 13, "%02x%02x%02x%02x%02x%02x",
			value[0], value[1], value[2], value[3], value[4], value[5]);
		for(i=0;i<ELANVIF_NUM;i++){
			status|=va_cmd(IFCONFIG, 4, 1, ELANVIF[i], "hw", "ether", macaddr);
		}
#if defined(CONFIG_RTL8681_PTM)
		status|=va_cmd(IFCONFIG, 4, 1, PTMIF, "hw", "ether", macaddr);
#endif
#ifdef CONFIG_USB_ETH
		status|=va_cmd(IFCONFIG, 4, 1, USBETHIF, "hw", "ether", macaddr);
#endif //CONFIG_USB_ETH
#ifdef WLAN_SUPPORT
		status|=va_cmd(IFCONFIG, 4, 1, WLANIF[0], "hw", "ether", macaddr);

#ifdef WLAN_MBSSID
		// Set macaddr for VAP
		for (i=1; i<=WLAN_MBSSID_NUM; i++) {
			value[5] = value[5] + 1;

			snprintf(macaddr, 13, "%02x%02x%02x%02x%02x%02x",
				value[0], value[1], value[2], value[3], value[4], value[5]);

			sprintf(para2, "wlan0-vap%d", i-1);

			status|=va_cmd(IFCONFIG, 4, 1, para2, "hw", "ether", macaddr);
		}
#endif
#if defined(CONFIG_RTL_92D_DMDP) || (defined(WLAN_DUALBAND_CONCURRENT) && !defined(CONFIG_LUNA_DUAL_LINUX))
		value[5] = value[5] + 1;
		snprintf(macaddr, 13, "%02x%02x%02x%02x%02x%02x",
			value[0], value[1], value[2], value[3], value[4], value[5]);
		status|=va_cmd(IFCONFIG, 4, 1, WLANIF[1], "hw", "ether", macaddr);

#ifdef WLAN_MBSSID
		// Set macaddr for VAP
		for (i=1; i<=WLAN_MBSSID_NUM; i++) {
			value[5] = value[5] + 1;

			snprintf(macaddr, 13, "%02x%02x%02x%02x%02x%02x",
				value[0], value[1], value[2], value[3], value[4], value[5]);

			sprintf(para2, "wlan1-vap%d", i-1);

			status|=va_cmd(IFCONFIG, 4, 1, para2, "hw", "ether", macaddr);
		}
#endif
#endif //CONFIG_RTL_92D_DMDP
#endif // WLAN_SUPPORT
	}

	// ifconfig eth0 up
	//va_cmd(IFCONFIG, 2, 1, "eth0", "up");

	// brctl addbr br0
	status|=va_cmd(BRCTL, 2, 1, "addbr", (char*)BRIF);

	// ifconfig br0 hw ether
	if (mib_get(MIB_ELAN_MAC_ADDR, (void *)value) != 0)
	{
		snprintf(macaddr, 13, "%02x%02x%02x%02x%02x%02x",
		value[0], value[1], value[2], value[3], value[4], value[5]);
		va_cmd(IFCONFIG, 4, 1, BRIF, "hw", "ether", macaddr);
	}

#if !defined(CONFIG_LUNA) && !defined(CONFIG_DSL_VTUO)
	//setup WAN to WAN blocking
	system("/bin/echo 1 > /proc/br_wanblocking");
#endif

	if (mib_get(MIB_BRCTL_STP, (void *)value) != 0)
	{
		vInt = (int)(*(unsigned char *)value);
		if (vInt == 0)	// stp off
		{
			// brctl stp br0 off
			status|=va_cmd(BRCTL, 3, 1, "stp", (char *)BRIF, "off");

			// brctl setfd br0 1
			//if forwarding_delay=0, fdb_get may fail in serveral seconds after booting
			status|=va_cmd(BRCTL, 3, 1, "setfd", (char *)BRIF, "1");
		}
		else		// stp on
		{
			// brctl stp br0 on
			status|=va_cmd(BRCTL, 3, 1, "stp", (char *)BRIF, "on");
		}
	}

	// brctl setageing br0 ageingtime
	if (mib_get(MIB_BRCTL_AGEINGTIME, (void *)value) != 0)
	{
		vInt = (int)(*(unsigned short *)value);
		snprintf(timeOut, 6, "%u", vInt);
		status|=va_cmd(BRCTL, 3, 1, "setageing", (char *)BRIF, timeOut);
	}
	for(i=0;i<ELANVIF_NUM;i++){
		status|=va_cmd(BRCTL, 3, 1, "addif", (char *)BRIF, ELANVIF[i]);
#ifdef CONFIG_IPV6
		// Disable ipv6 for bridge interface
		setup_disable_ipv6(ELANVIF[i], 1);
#endif
	}

#if defined(CONFIG_RTL8681_PTM)
	status|=va_cmd(BRCTL, 3, 1, "addif", (char *)BRIF, PTMIF);
#endif
#ifdef CONFIG_USB_ETH
	status|=va_cmd(BRCTL, 3, 1, "addif", (char *)BRIF, USBETHIF);
#ifdef CONFIG_IPV6
	// Disable ipv6 for bridge interface
	setup_disable_ipv6(USBETHIF, 1);
#endif
#endif //CONFIG_USB_ETH

	/* Mason Yu. 2011/04/12
	 * In order to wait if the ALL LAN bridge ports is ready or not. Set dad probes amount to 4 for br0.
	 */
    /*
     * 2012/8/15
     * Since the eth0.2~5 up timing is tuned to must more later, so 4 is not enough, the first 5 NS
     * could not be send out until eth0.2~5 are up.
     */
	unsigned char val[64];
	snprintf(val, 64, "/bin/echo 8 > /proc/sys/net/ipv6/conf/%s/dad_transmits", (char*)BRIF);
	system(val);

	// ifconfig LANIF LAN_IP netmask LAN_SUBNET
	if (mib_get(MIB_ADSL_LAN_IP, (void *)value) != 0)
	{
		strncpy(ipaddr, inet_ntoa(*((struct in_addr *)value)), 16);
		ipaddr[15] = '\0';
	}
	if (mib_get(MIB_ADSL_LAN_SUBNET, (void *)value) != 0)
	{
		strncpy(subnet, inet_ntoa(*((struct in_addr *)value)), 16);
		subnet[15] = '\0';
	}

#if defined(CONFIG_LUNA) && defined(CONFIG_RTK_RG_INIT)
	{
//		status|=va_cmd(IFCONFIG, 3, 1, (char*)LANIF,"up", ipaddr);
		Init_rg_api();
		Init_RG_ELan(TagCPort, BridgeWan);
	}
#endif

	// get the minumum MRU for all WLAN-side link
	/* marked by Jenny
	vInt = get_min_wan_mru();
	if (vInt==0) */
		vInt = 1500;
	snprintf(value, 6, "%d", vInt);
	// set LAN-side MRU
	status|=va_cmd(IFCONFIG, 6, 1, (char*)LANIF, ipaddr, "netmask", subnet, "mtu", value);

#ifdef SECONDARY_IP
	mib_get(MIB_ADSL_LAN_ENABLE_IP2, (void *)value);
	if (value[0] == 1) {
		// ifconfig LANIF LAN_IP netmask LAN_SUBNET
		if (mib_get(MIB_ADSL_LAN_IP2, (void *)value) != 0)
		{
			strncpy(ipaddr, inet_ntoa(*((struct in_addr *)value)), 16);
			ipaddr[15] = '\0';
		}
		if (mib_get(MIB_ADSL_LAN_SUBNET2, (void *)value) != 0)
		{
			strncpy(subnet, inet_ntoa(*((struct in_addr *)value)), 16);
			subnet[15] = '\0';
		}
		snprintf(value, 6, "%d", vInt);
		// set LAN-side MRU
		status|=va_cmd(IFCONFIG, 6, 1, (char*)"br0:0", ipaddr, "netmask", subnet, "mtu", value);
	}
#endif


#ifdef CONFIG_USER_DHCP_SERVER
	if (mib_get(MIB_ADSL_LAN_AUTOSEARCH, (void *)value) != 0)
	{
		if (value[0] == 1)	// enable LAN ip autosearch
		{
			// check if dhcp server on ? per TR-068, I-190
			// Modified by Mason Yu for dhcpmode
			// if (mib_get(MIB_ADSL_LAN_DHCP, (void *)value) != 0)
			if (mib_get(MIB_DHCP_MODE, (void *)value) != 0)
			{
				if (value[0] != 2)	// dhcp server is disabled
				{
					usleep(2000000); // wait 2 sec for br0 ready
					startLANAutoSearch(ipaddr, subnet);
				}
			}
		}
	}
#endif

	if (status)  //start fail
	    return -1;

	//start success
    return 1;
}

#if 0
int check_for_rip()
{
	unsigned int num;
	unsigned char uChar;
	MIB_CE_ATM_VC_Tp pEntry;

	// --- Check LAN side
	if (mib_get(MIB_ADSL_LAN_DHCP, (void *)&uChar) != 0)
	{
		if (uChar != 0)
			return 0;	// dhcp server not disabled
	}

	// --- Check WAN side
	if (mib_chain_total(MIB_ATM_VC_TBL) != 1)
		return 0;
	pEntry = (MIB_CE_ATM_VC_Tp) mib_chain_get(MIB_ATM_VC_TBL,0);
	if(!pEntry)
		return 0;
	if (pEntry->cmode != ADSL_RT1483 && pEntry->cmode != ADSL_MER1483)
		return 0;
	if(pEntry->napt != 0)
		return 0;	// napt not disabled
	if(pEntry->ipDhcp != 0)
		return 0;	// not fixed ip

	return 1;
}
#endif

// return value:
// 0  : not active
// 1  : successful
// -1 : startup failed
int setupService(void)
{
	MIB_CE_ACC_T Entry;
	char *argv[15];
	int status=0;

	if (!mib_chain_get(MIB_ACC_TBL, 0, (void *)&Entry))
		return 0;

	/* run as console web
	if (pEntry->web !=0) {
		// start webs
		va_cmd(WEBSERVER, 0, 0);
	}
	*/
	//if (pEntry->snmp !=0) {
		// start snmpd
		// Commented by Mason Yu
		// We use new version
		//va_cmd(SNMPD, 0, 0);
		// Add by Mason Yu for start SnmpV2Trap
#ifdef CONFIG_USER_SNMPD_SNMPD_V2CTRAP
	char vChar;
	mib_get(MIB_SNMPD_ENABLE, (void *)&vChar);
	if(vChar==1)
		status = startSnmp();
#endif
	//}
	return status;
}

//--------------------------------------------------------
// Daemon startup
// return value:
// 1  : successful
// -1 : failed
int startDaemon(void)
{
	int pppd_fifo_fd=-1;
	int mpoad_fifo_fd=-1;
	int status=0, tmp_status;
	int k;

#ifdef CONFIG_USER_XDSL_SLAVE
	if( startSlv()<0 )
		status=-1;
#endif /*CONFIG_USER_XDSL_SLAVE*/

	//#ifndef CONFIG_ETHWAN
	#ifdef CONFIG_RTL8672_SAR
	// start mpoad
	status|=va_cmd(MPOAD, 0, 0);

	// check if mpoad ready to serve
	//while ((mpoad_fifo_fd = open(MPOAD_FIFO, O_WRONLY)) == -1)
	for (k=0; k<=100; k++)
	{
		if ((mpoad_fifo_fd = open(MPOAD_FIFO, O_WRONLY))!=-1)
			break;
		usleep(30000);
	}

	if (mpoad_fifo_fd == -1)
	{
		printf("open mpoad fifo failed !\n");
		status = -1;
	}
	else
		close(mpoad_fifo_fd);
	#endif // CONFIG_RTL8672_SAR

// Mason Yu. for IPv6
// To start DNSv6Relay, it will refer /proc/net/if_inet6.
// After the IPv6 IP is set, we can start the DNSRelay.
// Remove the following process to main().
#if 0
	if (startDnsRelay() == -1)
	{
		printf("start DNS relay failed !\n");
		status=-1;
	}
#endif

	// Marked by Mason Yu. try123. If combine DHCP Server and relay, we should start DHCPD on startRest().
#ifdef CONFIG_USER_DHCP_SERVER
#ifndef COMBINE_DHCPD_DHCRELAY
	tmp_status=setupDhcpd();
	if (tmp_status == 1)
	{
		status|=va_cmd(DHCPD, 1, 0, DHCPD_CONF);
	} else if (tmp_status==-1)
	    status = -1;
#endif
#endif

    // 2012/8/22
    // Move start_dhcpv6 to here because need to set IPv6 Global address
    // faster to pass the IPv6 core ready logo test.

	// Mason Yu.
#ifdef CONFIG_IPV6
#ifdef CONFIG_USER_DHCPV6_ISC_DHCP411
	start_dhcpv6(1);
#endif
#endif

#ifdef CONFIG_PPP
	// start spppd
	status|=va_cmd(SPPPD, 0, 0);

	// check if spppd ready to serve
	//while ((pppd_fifo_fd = open(PPPD_FIFO, O_WRONLY)) == -1)
	for (k=0; k<=100; k++)
	{
		if ((pppd_fifo_fd = open(PPPD_FIFO, O_WRONLY))!=-1)
			break;
		usleep(30000);
	}

	if (pppd_fifo_fd == -1)
		status = -1;
	else
		close(pppd_fifo_fd);
#endif

#ifdef CONFIG_USER_WT_146
#define BFD_DAEMON "/bin/bfdmain"
#define BFD_SERVER_FIFO_NAME "/tmp/bfd_serv_fifo"
{
	int bfdmain_fifo_fd=-1;

	// start bfdmain
	status|=va_cmd(BFD_DAEMON, 0, 0);

	// check if bfdmain ready to serve
	//while ((bfdmain_fifo_fd = open(BFD_SERVER_FIFO_NAME, O_WRONLY)) == -1)
	for (k=0; k<=100; k++)
	{
		if ((bfdmain_fifo_fd = open(BFD_SERVER_FIFO_NAME, O_WRONLY))!=-1)
			break;
		usleep(30000);
	}

	if (bfdmain_fifo_fd == -1)
		status = -1;
	else
		close(bfdmain_fifo_fd);
}
#endif //CONFIG_USER_WT_146


#ifdef TIME_ZONE
	status|=startNTP();
#endif

	status|=setupService();
	// Kaohj -- move from startRest().
	// start webs
	status|=va_cmd(WEBSERVER, 0, 0);

	return status;
}

#ifdef ELAN_LINK_MODE_INTRENAL_PHY
// Added by Mason Yu
int setupLinkMode_internalPHY()
{
	restart_ethernet(1);
	return 1;

}
#endif

//--------------------------------------------------------
// LAN side IP autosearch using ARP
// Input: current IP address
// return value:
// 1  : successful
// -1 : failed
int startLANAutoSearch(const char *ipAddr, const char *subnet)
{
	unsigned char netip[4];
	struct in_addr *dst;
	int k, found;

	TRACE(STA_INFO, "Start LAN IP autosearch\n");
	dst = (struct in_addr *)netip;

	if (!inet_aton(ipAddr, dst)) {
		printf("invalid or unknown target %s", ipAddr);
		return -1;
	}

	if (isDuplicate(dst, LANIF)) {
		TRACE(STA_INFO, "Duplicate LAN IP found !\n");
		found = 0;
		inet_aton("192.168.1.254", dst);
		if (isDuplicate(dst, LANIF)) {
			netip[3] = 63;	// 192.168.1.63
			if (isDuplicate(dst, LANIF)) {
				// start from 192.168.1.253 and descending
				for (k=253; k>=1; k--) {
					netip[3] = k;
					if (!isDuplicate(dst, LANIF)) {
						// found it
						found = 1;
						TRACE(STA_INFO, "Change LAN ip to %s\n", inet_ntoa(*dst));
						break;
					}
				}
			}
			else {
				// found 192.168.1.63
				found = 1;
				TRACE(STA_INFO, "Change LAN ip to %s\n", inet_ntoa(*dst));
			}
		}
		else {
			// found 192.168.1.254
			found = 1;
			TRACE(STA_INFO, "Change LAN ip to %s\n", inet_ntoa(*dst));
		}

		if (!found) {
			printf("not available LAN IP !\n");
			return -1;
		}

		// ifconfig LANIF LAN_IP netmask LAN_SUBNET
		va_cmd(IFCONFIG, 4, 1, (char*)LANIF, inet_ntoa(*dst), "netmask", subnet);
	}

	return 1;
}

#if 0
void addStaticRoute()
{
	unsigned int entryNum, i;
	MIB_CE_IP_ROUTE_T Entry;
	//struct rtentry rt;
	//struct sockaddr_in *inaddr;
	//char	ifname[17];

	/* Clean out the RTREQ structure. */
	//memset((char *) &rt, 0, sizeof(struct rtentry));
	entryNum = mib_chain_total(MIB_IP_ROUTE_TBL);

	for (i=0; i<entryNum; i++) {

		if (!mib_chain_get(MIB_IP_ROUTE_TBL, i, (void *)&Entry))
		{
			return;
		}
		route_cfg_modify(&Entry, 0);
	}
}
#endif
#if defined(CONFIG_RTL_IGMP_SNOOPING)
int setupIGMPSnoop()
{
	unsigned char mode;
	mib_get(MIB_MPMODE, (void *)&mode);
	if (mode&MP_IGMP_MASK){
		__dev_setupIGMPSnoop(1);
	}
	return 1;
}
#endif
#if defined(CONFIG_RTL_MLD_SNOOPING)
int setupMLDSnoop()
{
	unsigned char mode;
	mib_get(MIB_MPMODE, (void *)&mode);
	if (mode&MP_MLD_MASK){
		__dev_setupMLDSnoop(1);
	}
	return 1;
}
#endif
//--------------------------------------------------------
// Final startup
// return value:
// 1  : successful
// -1 : failed
int startRest(void)
{
	int vcTotal, i;
	unsigned char autosearch, mode;
	MIB_CE_ATM_VC_T Entry;
	int status=0;

#ifdef CONFIG_IPV6
	char ipv6Enable =-1;
#endif

	// Kaohj -- move to startDaemon().
	//	When ppp up, it will send command to boa message queue,
	//	so we needs boa msgq to be enabled earlier.
/*
	// start snmpd
	va_cmd(SNMPD, 0, 0);
*/

	// Add static routes
	// Mason Yu. Init hash table for all routes on RIP
	// Move to startWan()
	//addStaticRoute();

	// Mason Yu. If combine DHCP Server and relay, we should start DHCPD here not on startDaemon().
#ifdef CONFIG_USER_DHCP_SERVER
#ifdef COMBINE_DHCPD_DHCRELAY
	int tmp_status;
	tmp_status=setupDhcpd();
	if (tmp_status == 1)
	{
		status|=va_cmd(DHCPD, 2, 0, "-S", DHCPD_CONF);
	} else if (tmp_status==-1)
	    status = -1;
#endif

	//Added by Mason Yu for start DHCP relay
	// We only can choice DHCP Server or Relay one.
	if (-1==startDhcpRelay())
	    return -1;
#endif

#if defined(CONFIG_RTL_IGMP_SNOOPING)
	setupIGMPSnoop();
#endif
#if defined(CONFIG_RTL_MLD_SNOOPING)
	setupMLDSnoop();
#endif

#ifdef NEW_PORTMAPPING
	setupnewEth2pvc();
#endif


#ifdef IP_QOS
	mib_get(MIB_MPMODE, (void *)&mode);
#ifdef QOS_DIFFSERV
	unsigned char qosDomain;
	mib_get(MIB_QOS_DIFFSERV, (void *)&qosDomain);
	if (qosDomain == 1)
		setupDiffServ();
	else {
#endif
	if (mode&MP_IPQ_MASK)
		setupIPQ();
#ifdef QOS_DIFFSERV
	}
#endif
#elif defined(NEW_IP_QOS_SUPPORT)
	//ql 20081117 START for IP QoS
	setup_qos_setting();
#elif defined(CONFIG_USER_IP_QOS_3)
	setupIPQ();
#endif

#ifdef CONFIG_USER_IP_QOS
#ifdef CONFIG_HWNAT
	setWanIF1PMark();
#endif
#endif

#ifndef NEW_PORTMAPPING
// Mason Yu. combine_1p_4p_PortMapping
#if (defined( ITF_GROUP_1P) && defined(ITF_GROUP))
	if (mode&MP_PMAP_MASK)
		setupEth2pvc();
#endif
#endif //NEW_PORTMAPPING

	// ioctl for direct bridge mode, jiunming
	{
		unsigned char  drtbr_mode;
		if (mib_get(MIB_DIRECT_BRIDGE_MODE, (void *)&drtbr_mode) != 0)
		{
			__dev_setupDirectBridge( (int) drtbr_mode );
		}
	}

#ifdef DOS_SUPPORT
	// for DOS support
	setup_dos_protection();
#endif

     #ifdef CONFIG_IGMP_FORBID

       unsigned char igmpforbid_mode;

	 if (!mib_get( MIB_IGMP_FORBID_ENABLE,  (void *)&igmpforbid_mode)){
		printf("igmp forbid  parameter failed!\n");
	}
	 if(1==igmpforbid_mode){
             __dev_igmp_forbid(1);
	 }
     #endif

#ifdef CONFIG_USER_SAMBA
	startSamba();
#endif // CONFIG_USER_SAMBA

#ifdef CONFIG_IPV6
	mib_get(MIB_V6_IPV6_ENABLE, (void *)&ipv6Enable);
	// Added by Mason Yu. for ipv6
#ifdef CONFIG_USER_IPV6READYLOGO_ROUTER
	if(ipv6Enable==1)
		printf("Init System OK for IPV6\n");    // Added by Mason Yu for p2r_test
#endif

#ifdef CONFIG_USER_IPV6READYLOGO_HOST
	if(ipv6Enable==1)
		printf("Init System OK for IPV6\n");	  // Added by Mason Yu for p2r_test
#endif
#endif

#if defined (WLAN_SUPPORT)
	mode = 0;
	mib_get(MIB_WIFI_TEST, (void *)&mode);
	if (mode == 1)
		va_cmd("/bin/11N_UDPserver", 1, 0, "&");
	#ifdef CONFIG_USER_WIRELESS_MP_MODE
	va_cmd("/bin/11N_UDPserver", 1, 0, "&");
	#endif
#endif

	// Mason Yu. User do not need to modify the media directory.
#ifdef CONFIG_USER_MINIDLNA
	// Mason Yu. init minidlna
	startMiniDLNA();
#endif

	return 1;
}

extern unsigned char cs_valid;
extern unsigned char ds_valid;
extern unsigned char hs_valid;

#ifdef CONFIG_USER_SNMPD_SNMPD_V2CTRAP
// Added by Mason Yu
static int getSnmpConfig(void)
{

	//char *str1, *str2, *str3, *str4, *str5;
	unsigned char str[256];
	FILE *fp;

	fp=fopen("/tmp/snmp", "w+");


	mib_get(MIB_SNMP_SYS_DESCR, (void *)str);
	fprintf(fp, "%s\n", str);


	mib_get( MIB_SNMP_SYS_CONTACT,  (void *)str);
	fprintf(fp, "%s\n", str);


	mib_get( MIB_SNMP_SYS_NAME,  (void *)str);
	fprintf(fp, "%s\n", str);


	mib_get( MIB_SNMP_SYS_LOCATION,  (void *)str);
	fprintf(fp, "%s\n", str);


	mib_get( MIB_SNMP_SYS_OID,  (void *)str);
	fprintf(fp, "%s\n", str);


  	fclose(fp);
	return 0;
}
#endif


/*
 * system initialization, checking, setup, etc.
 */
const char PW_HOME_DIR[] = "/tmp";
extern char DNSV4_SNAT[];
static int sys_setup()
{
	key_t key;
	int qid, vInt, activePVC, ret;
	int i;
	MIB_CE_ATM_VC_T Entry;
	unsigned char value[32];
	FILE *fp;
	char userName[MAX_NAME_LEN], userPass[MAX_NAME_LEN];
	char *xpass;
#ifdef ACCOUNT_CONFIG
	MIB_CE_ACCOUNT_CONFIG_T entry;
	unsigned int totalEntry;
#endif

	ret = 0;
	//----------------- check if configd is ready -----------------------
	key = ftok("/bin/init", 'k');
	for (i=0; i<=100; i++) {
		if (i==100) {
			printf("Error: configd not started !!\n");
			return 0;
		}
		if ((qid = msgget( key, 0660 )) == -1)
			usleep(30000);
		else
			break;
	}

	// Kaohj -- check consistency between MIB chain definition and descriptor.
	// startup process would be ceased if checking failed, programmer must review
	// all MIB chain descriptors in problem.
	if (mib_check_desc()==-1) {
		printf("Please check MIB chain descriptors !!\n");
		return -1;
	}
#ifdef CONFIG_USER_RTK_RECOVER_SETTING
	// Delay before writing to flash for system stability
	sleep(1);
	//va_cmd("/bin/LoadxmlConfig", 1, 1, "flash");
	fp = fopen(FLASH_CHECK_FAIL, "r"); //only when current setting check is fail, sys restore to oldconfig
	if (fp) {
		fclose(fp);
		unlink(FLASH_CHECK_FAIL);
		va_cmd("/bin/loadconfig", 2, 1, "-f", OLD_SETTING_FILE);
#ifdef COMMIT_IMMEDIATELY
		Commit();
#endif
		unlink(OLD_SETTING_FILE);
//ccwei_flatfsd
#ifdef CONFIG_USER_FLATFSD_XXX
		va_cmd("/bin/flatfsd", 1, 1, "-s");
#endif
	}
#endif

	// Mason Yu. flash all atm_vc_tbl for AutoHunt.
	unsigned char autosearch;
	if (mib_get(MIB_ATM_VC_AUTOSEARCH, (void *)&autosearch) != 0)
	{
		if (autosearch == 1) {
			//printf("***** clear MIB_ATM_VC_TBL chain record\n");
			mib_chain_clear(MIB_ATM_VC_TBL); /* clear chain record */
		}
	}

	//----------------
	// Mason Yu
#ifdef CONFIG_USER_SNMPD_SNMPD_V2CTRAP
	getSnmpConfig();
#endif
	// ftpd: /etc/passwd & /tmp (as home dir)
	fp = fopen("/var/passwd", "w+");
#ifdef ACCOUNT_CONFIG
	totalEntry = mib_chain_total(MIB_ACCOUNT_CONFIG_TBL); /* get chain record size */
	for (i=0; i<totalEntry; i++) {
		if (!mib_chain_get(MIB_ACCOUNT_CONFIG_TBL, i, (void *)&entry)) {
			printf("ERROR: Get account configuration information from MIB database failed.\n");
			return;
		}
		strcpy(userName, entry.userName);
		strcpy(userPass, entry.userPassword);
		xpass = crypt(userPass, "$1$");
		if (xpass) {
			if (entry.privilege == (unsigned char)PRIV_ROOT)
				fprintf(fp, "%s:%s:0:0::%s:%s\n", userName, xpass, PW_HOME_DIR, PW_CMD_SHELL);
			else
				fprintf(fp, "%s:%s:1:0::%s:%s\n", userName, xpass, PW_HOME_DIR, PW_CMD_SHELL);
		}
	}
#endif
	mib_get( MIB_SUSER_NAME, (void *)userName );
	mib_get( MIB_SUSER_PASSWORD, (void *)userPass );
	xpass = crypt(userPass, "$1$");
	if (xpass)
		fprintf(fp, "%s:%s:0:0::%s:%s\n", userName, xpass, PW_HOME_DIR, PW_CMD_SHELL);

	// Added by Mason Yu for others user
	mib_get( MIB_SUPER_NAME, (void *)userName );
	mib_get( MIB_SUPER_PASSWORD, (void *)userPass );
	xpass = crypt(userPass, "$1$");
	if (xpass)
		fprintf(fp, "%s:%s:0:0::%s:%s\n", userName, xpass, PW_HOME_DIR, PW_CMD_SHELL);

#if 0 // anonymous ftp
	// added for anonymous ftp
	fprintf(fp, "%s:%s:10:10::/tmp:/dev/null\n", "ftp", "x");
#endif
	mib_get( MIB_USER_NAME, (void *)userName );
	if (userName[0]) {
		mib_get( MIB_USER_PASSWORD, (void *)userPass );
		xpass = crypt(userPass, "$1$");
		if (xpass)
			fprintf(fp, "%s:%s:1:0::%s:%s\n", userName, xpass, PW_HOME_DIR, PW_CMD_SHELL);
	}

	fclose(fp);
	chmod(PW_HOME_DIR, 0x1fd);	// let owner and group have write access
	// Kaohj --- force kernel(linux-2.6) igmp version to 2
#ifdef _LINUX_2_6_
#ifdef FORCE_IGMP_V2
	fp = fopen((const char *)PROC_FORCE_IGMP_VERSION,"w");
	if(fp)
	{
		fprintf(fp, "%d", 2);
		fclose(fp);
	}
#endif
#endif
#ifdef POLICY_ROUTING_DNSV4RELAY	
	//iptables -t nat -N dnsv4_snat
	//iptables -t nat -A POSTROUTING -j dnsv4_snat
	va_cmd(IPTABLES, 4, 1, "-t", "nat", "-N", DNSV4_SNAT);
	va_cmd(IPTABLES, 6, 1, "-t", "nat", "-A", "POSTROUTING", "-j", DNSV4_SNAT);
#endif
	return ret;
}

#ifdef CONFIG_USER_XDSL_SLAVE
int startSlv(void)
{
	int  sysret, ret=0;
	char sysbuf[128];

	sprintf( sysbuf, "/bin/ucrelay" );
	printf( "system(): %s\n", sysbuf );
	sysret=system( sysbuf );
	if( WEXITSTATUS(sysret)!=0 )
	{
		printf( "exec ucrelay failed!\n" );
		ret=-1;
	}

	if(ret==0)
	{
#if 1
		int i=3;
		while(i--)
		{
			sprintf( sysbuf, "/bin/ucstartslv" );
			printf( "system(): %s\n", sysbuf );
			sysret=system( sysbuf );
			if( WEXITSTATUS(sysret)!=0 )
			{
				printf( "call /bin/ucstartslv to init slave firmware failed!\n" );
				ret=-1;
			}else{
				ret=0;
				break;
			}
		}
#endif
	}
	return ret;
}
#endif /*CONFIG_USER_XDSL_SLAVE*/

#ifdef CONFIG_KEEP_BOOTCODE_CONFIG
#define BOOTCONF_START 0xbfc07f80
#define BOOTCONF_SIZE  0x40
#define BOOTCONF_MAGIC (('b'<<24) | ('t'<<16) | ('c'<<8) | ('f')) //0x62746366
#define BOOTCONF_PROCNAME	"/proc/bootconf"
struct bootconf
{
	unsigned long	magic;
	unsigned char	mac[6];
	unsigned short	flag;
	unsigned long	ip;
	unsigned long	ipmask;
	unsigned long	serverip;
	unsigned char	filename[24];
	unsigned char	res[16];
};
typedef struct bootconf bootconf_t, *bootconf_p;

static int bootconf_get_from_procfile(bootconf_t *p)
{
	FILE *f;
	int ret=-1;

	if(p==NULL) return ret;
	f=fopen( BOOTCONF_PROCNAME, "r" );
	if(f)
	{
		if( fread(p, 1, BOOTCONF_SIZE, f)==BOOTCONF_SIZE )
		{
			if(p->magic==BOOTCONF_MAGIC)
				ret=0;
			else
				printf( "%s: magic not match %08x\n", __FUNCTION__, p->magic );
		}else{
			printf( "%s: fread errno=%d\n", __FUNCTION__, errno );
		}
		fclose(f);
	}else{
		printf( "%s: can't open %s\n", __FUNCTION__, BOOTCONF_PROCNAME );
	}

	return ret;
}
static void bootconf_updatemib(void)
{
	bootconf_t bc;
	if( bootconf_get_from_procfile(&bc)==0 )
	{
		mib_set( MIB_ELAN_MAC_ADDR, bc.mac );
		mib_set( MIB_ADSL_LAN_IP, &bc.ip );
		mib_set( MIB_ADSL_LAN_SUBNET, &bc.ipmask );
	}else
		printf( "%s: call bootconf_getdata() failed!\n", __FUNCTION__);

	return;
}
#endif /*CONFIG_KEEP_BOOTCODE_CONFIG*/


#ifdef CONFIG_RTL8685_PTM_MII
const char PTMCTL[]="/bin/ptmctl";
int startPTM(void)
{
	int ret=-1;
	if (WAN_MODE & MODE_BOND){
		printf("PTM Bonding Mode!\n");
		if( va_cmd(PTMCTL, 1, 1, "set_sys") )
			goto ptmfail;
		if( va_cmd(PTMCTL, 3, 1, "set_hw", "bonding", "2") )
			goto ptmfail;
	} else {
		printf("PTM Non-Bonding Mode!\n");
		if( va_cmd(PTMCTL, 1, 1, "set_hw") )
			goto ptmfail;
	}

	//default fast path
	if( va_cmd(PTMCTL, 3, 1, "set_qmap", "7", "44444444") )
		goto ptmfail;

	ret=0;
ptmfail:
	return ret;
}
#endif /*CONFIG_RTL8685_PTM_MII*/


#if defined(CONFIG_GPON_FEATURE)
int startGPON(void)
{
	char tmpBuf[25];

	//Since OMCI has already active this, so need to deactive
	printf("GPON deActivate.\n");
#if defined(CONFIG_RTK_L34_ENABLE)
	rtk_rg_gpon_deActivate();
#else
	rtk_gpon_deActivate();
#endif

	if(!mib_get(MIB_GPON_PASSWD,  (void *)tmpBuf))
	{
		printf("Error!!! %s: get GPON LOID Error",__func__);
		goto handleError;
	}
	else
	{
		rtk_gpon_password_t gpon_password;

		memset(&gpon_password,0,sizeof(gpon_password));
		memcpy(gpon_password.password, tmpBuf, 10);
#if defined(CONFIG_RTK_L34_ENABLE)		
		rtk_rg_gpon_password_set(&gpon_password);
#else
		rtk_gpon_password_set(&gpon_password);
#endif
	}

	if(!mib_get(MIB_GPON_SN,  (void *)tmpBuf))
	{
		printf("Error!!! %s: get GPON LOID Error",__func__);
		goto handleError;
	}
	else
	{
		rtk_gpon_serialNumber_t SN;
		char specific_str[9] = {0};
		unsigned int  specific =0;

		memset(&SN, 0 ,sizeof(SN));
		memcpy(SN.vendor,tmpBuf,4);
		memcpy(specific_str,&tmpBuf[4],8);

		specific = (unsigned int) strtoll(specific_str,NULL,16);

		SN.specific[0] = ( specific >>24 ) &0xFF;
		SN.specific[1] = ( specific >>16 ) &0xFF;
		SN.specific[2] = ( specific >>8 ) &0xFF;
		SN.specific[3] = ( specific ) &0xFF;
#if defined(CONFIG_RTK_L34_ENABLE)
		rtk_rg_gpon_serialNumber_set(&SN);
#else
		rtk_gpon_serialNumber_set(&SN);
#endif
	}

	//Active GPON again
	printf("GPON Activate again.\n");
#if defined(CONFIG_RTK_L34_ENABLE)
	rtk_rg_gpon_activate(RTK_GPONMAC_INIT_STATE_O1);
#else
	rtk_gpon_activate(RTK_GPONMAC_INIT_STATE_O1);
#endif
	return 0;

handleError:
	return -1;
}
#endif

#if defined(CONFIG_EPON_FEATURE)
int startEPON(void)
{
	int entryNum=4;
	unsigned int totalEntry;
	int index;
	int retVal;
	MIB_CE_MIB_EPON_LLID_T mib_llidEntry;
	rtk_epon_llid_entry_t llid_entry;
	char loid[100]={0};	
	char passwd[100]={0};
	char oamcli_cmd[128]={0};
	
#if defined(CONFIG_RTK_L34_ENABLE)
	rtk_rg_epon_llidEntryNum_get(&entryNum);
#else
	rtk_epon_llidEntryNum_get(&entryNum);
#endif


	if(!mib_get(MIB_EPON_LOID,	(void *)loid))		
	{			
		printf("Get EPON LOID Failed\n");	
	}		
	
	if(!mib_get(MIB_EPON_PASSWD,  (void *)passwd))
	{
		printf("Get EPON Password Failed\n");
	}

	
	for(index=0;index<entryNum;index++)
	{
		sprintf(oamcli_cmd, "/bin/oamcli set ctc loid %d %s %s", index, loid,passwd);
		system(oamcli_cmd);
	}


	totalEntry = mib_chain_total(MIB_EPON_LLID_TBL); /* get chain record size */
	if(totalEntry == 0)
	{
		//First time to boot, the mib chain of LLID MAC table is empty.
		//need to create entry according to the LLID numbers chip supported.
		unsigned char mac[MAC_ADDR_LEN]={0x00,0x11,0x22,0x33,0x44,0x55};

		printf("First time to create EPON LLID MIB Table, now create %d entries.\n",entryNum);

		for(index=0;index<entryNum;index++)
		{
			int i;

			memset(&mib_llidEntry,0,sizeof(mib_llidEntry));

			//Add new EPON_LLID_ENTRY into mib chain
			memcpy(mib_llidEntry.macAddr,mac, MAC_ADDR_LEN);
			retVal = mib_chain_add(MIB_EPON_LLID_TBL, (unsigned char*)&mib_llidEntry);
			if (retVal == 0) {
				printf("Error!!!!!! %s:%s\n",__func__,Tadd_chain_error);
				return -1;
			}
			else if (retVal == -1) {
				printf("Error!!!!!! %s:%s\n",__func__,strTableFull);
				return -1;
			}
			printf("Add EPON LLID default entry into MIB Table with mac %2x:%2x:%2x:%2x:%2x:%2x Success!\n",
					mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);

			//Now set into driver.
			memset(&llid_entry,0,sizeof(llid_entry));
			llid_entry.llidIdx = index;
#if defined(CONFIG_RTK_L34_ENABLE)			
			rtk_rg_epon_llid_entry_get(&llid_entry);
#else
			rtk_epon_llid_entry_get(&llid_entry);
#endif
			for(i=0;i<MAC_ADDR_LEN;i++)
				llid_entry.mac.octet[i] = (unsigned char) mac[i];
#if defined(CONFIG_RTK_L34_ENABLE)			
			rtk_rg_epon_llid_entry_set(&llid_entry);
#else
			rtk_epon_llid_entry_set(&llid_entry);
#endif
			mac[5]++;
		}

#ifdef COMMIT_IMMEDIATELY
		Commit();
#endif

	}
	else
	{
		if(totalEntry!= entryNum)
		{
			printf("Error! %s: Chip support LLID entry %d is not the same ad MIB entries nubmer %d\n",
				__func__,entryNum, totalEntry);
			return -1;
		}

		//EPON_LLID MIB Table is not empty, read from it and set to driver
		for(index=0;index<totalEntry;index++)
		{
			int i;
			if (mib_chain_get(MIB_EPON_LLID_TBL, index, (void *)&mib_llidEntry))
			{
				memset(&llid_entry,0,sizeof(llid_entry));
				llid_entry.llidIdx = index;
#if defined(CONFIG_RTK_L34_ENABLE)				
				rtk_rg_epon_llid_entry_get(&llid_entry);
#else
				rtk_epon_llid_entry_get(&llid_entry);
#endif
				for(i=0;i<MAC_ADDR_LEN;i++)
					llid_entry.mac.octet[i] = (unsigned char) mib_llidEntry.macAddr[i];
#if defined(CONFIG_RTK_L34_ENABLE)
				rtk_rg_epon_llid_entry_set(&llid_entry);
#else
				rtk_epon_llid_entry_set(&llid_entry);
#endif
			}
			else
			{
				printf("Error: %s mib chain get error for index %d\n",__func__,index);
			}
		}
	}
	
	return 0;

}
#endif

#if defined(CONFIG_GPON_FEATURE) || defined(CONFIG_EPON_FEATURE)
int startPON(void)
{
	unsigned int pon_mode;

	if (mib_get(MIB_PON_MODE, (void *)&pon_mode) != 0)
	{
		if (pon_mode == EPON_MODE)
		{
#if defined(CONFIG_EPON_FEATURE)
			printf("set config for EPON\n");
			return startEPON();
#endif
		}
	}
}
#endif


#if defined(CONFIG_USER_JAMVM) && defined (CONFIG_APACHE_FELIX_FRAMEWORK) 
int startOsgi(void)
{
	FILE *fp_blist = NULL;
	FILE *fp_cnt = NULL;
	MIB_CE_OSGI_BUNDLE_T entry;
	int entry_cnt;
	int bundle_cnt;
	int idx, i , ignore;
	char osgi_cmd[512];
	char *ignore_bundle[] = 
	{
		"System Bundle",
		"RealtekTCPSocketListener",
		"Apache Felix Bundle Repository",
		"Apache Felix Gogo Command",
		"Apache Felix Gogo Runtime",
		"Apache Felix Gogo Shell",
		"osgi.cmpn",
		"Apache Felix Declarative Services",
		"Apache Felix Http Jetty"
	};

	snprintf(osgi_cmd,512, "ls /usr/local/class/felix/bundle/*.jar | wc -l > /tmp/bundle_cnt\n");
	system(osgi_cmd);

	
	if (!(fp_cnt=fopen("/tmp/bundle_cnt", "r")))
	{
		return 0;
	}

	fscanf(fp_cnt, "%d\n", &bundle_cnt);
	
	if (!(fp_blist=fopen("/tmp/OSGI_STARTUP", "w")))
	{
		return 0;
	}

	entry_cnt = mib_chain_total(MIB_OSGI_BUNDLE_TBL);

	for(idx = 0 ; idx < entry_cnt; idx++)
	{
		if (!mib_chain_get(MIB_OSGI_BUNDLE_TBL, idx, (void *)&entry))
		{
			fclose(fp_blist);
			return 0;
		}
		for(i = 0 ; i < sizeof(ignore_bundle) / sizeof(ignore_bundle[0]); i++)
		{
			if(strcmp(ignore_bundle[i] , entry.bundle_name) == 0 )
			{
				ignore = 1;
				break;
			}
		}
		if(ignore == 1)
		{
			ignore = 0;
			continue;
		}
		else // write file
		{
			fprintf(fp_blist, "/var/config_osgi/%s,%d,%d\n", entry.bundle_file, entry.bundle_action,++bundle_cnt);
		}
	}

	unlink("/tmp/bundle_cnt");
	fclose(fp_blist);
	fclose(fp_cnt);

	return 1;
}
#endif

int main(void)
{
	unsigned char value[32];
	int vInt;
#ifdef CONFIG_USER_SNMPD_SNMPD_V2CTRAP
	int snmpd_pid;
#endif
	int i;
	// set debug mode
	DEBUGMODE(STA_INFO|STA_SCRIPT|STA_WARNING|STA_ERR);

#ifdef CONFIG_KEEP_BOOTCODE_CONFIG
	bootconf_updatemib();
#endif /*CONFIG_KEEP_BOOTCODE_CONFIG*/

#if defined(CONFIG_DSL_ON_SLAVE)
	system("/bin/adslctrl InitSAR 1");
	printf("/bin/adslctrl InitSAR 1\n");
	sleep(1);
	system("/bin/adslctrl InitPTM 1");
	printf("/bin/adslctrl InitPTM 1\n");
	sleep(1);
#endif

	if (sys_setup() == -1)
		goto startup_fail;

#ifdef CONFIG_INIT_SCRIPTS
	printf("========== Initiating Starting Script =============\n");
	system("sh /var/config/start_script");
	printf("========== End Initiating Starting Script =============\n");
#endif

#if defined(CONFIG_LUNA) && defined(CONFIG_RTK_RG_INIT)
//	Init_RTK_RG_Device();
#endif

	if (-1==startELan())
		printf("startELan fail, plz check!\n");
#if defined(CONFIG_LUNA) && !defined(CONFIG_RTK_RG_INIT)
#if defined(CONFIG_RTL_MULTI_LAN_DEV) && defined(CONFIG_RTL8686) && !defined(CONFIG_RTK_L34_ENABLE)
	//without RG, default let switch forward packet.
	system("/bin/echo normal > /proc/rtl8686gmac/switch_mode");
#endif
#endif

	// check INIT_SCRIPT
	if (mib_get(MIB_INIT_SCRIPT, (void *)value) != 0)
	{
		vInt = (int)(*(unsigned char *)value);
	}
	else
		vInt = 1;

	if (vInt == 0)
	{
		 for(i=0;i<ELANVIF_NUM;i++){
			va_cmd(IFCONFIG, 2, 1, ELANVIF[i], "up");
		}
#if defined(CONFIG_RTL8681_PTM)
		va_cmd(IFCONFIG, 2, 1, PTMIF, "up");
#endif
#ifdef CONFIG_USB_ETH
		va_cmd(IFCONFIG, 2, 1, USBETHIF, "up");
#endif //CONFIG_USB_ETH
		va_cmd(WEBSERVER, 0, 0);
		return 0;	// stop here
	}

#ifndef CONFIG_USER_XMLCONFIG
	// Kaohj --- generate the XML file
	//va_cmd("/bin/CreatexmlConfig", 0, 1);

	//Save the configuration file for backup.
	va_cmd("/bin/saveconfig", 0, 1);
#endif	/*CONFIG_USER_XMLCONFIG*/

#ifdef XOR_ENCRYPT
	cmd_xml2file(CONFIG_XMLFILE, CONFIG_XMLENC);
#endif

	if (-1==startDaemon())
		goto startup_fail;

	//root interface should be up first
#ifndef CONFIG_RTL_MULTI_LAN_DEV
	if (va_cmd(IFCONFIG, 2, 1, ELANIF, "up"))
		goto startup_fail;
#endif

#ifdef CONFIG_RTL8685_PTM_MII
	if( startPTM()<0 )
		goto startup_fail;
#endif /*CONFIG_RTL8685_PTM_MII*/


#if defined(CONFIG_GPON_FEATURE) || defined(CONFIG_EPON_FEATURE)
	if( startPON()<0 )
		goto startup_fail;
#endif

	// start WAN interface ...
#if defined(CONFIG_LUNA) && defined(CONFIG_RTK_RG_INIT)
	Init_RG_ELan(UntagCPort, RoutingWan);
#endif
	if (-1==startWan(CONFIGALL, NULL))
		goto startup_fail;

	for(i=0;i<ELANVIF_NUM;i++){
		if(va_cmd(IFCONFIG, 2, 1, ELANVIF[i], "up")){
			goto startup_fail;
		}
	}

    /*
     * 2012/8/15
     * Since now eth0.2~5 are up, change NS number to default number 1.
     */
	unsigned char val[64];
	snprintf(val, 64, "/bin/echo 1 > /proc/sys/net/ipv6/conf/%s/dad_transmits", (char*)BRIF);
	system(val);

#if defined(CONFIG_RTL8681_PTM)
	if (va_cmd(IFCONFIG, 2, 1, PTMIF, "up"))
		goto startup_fail;
#endif
#ifdef CONFIG_USB_ETH
	if (va_cmd(IFCONFIG, 2, 1, USBETHIF, "up"))
		goto startup_fail;
#endif //CONFIG_USB_ETH

#ifdef CONFIG_USER_RTK_SYSLOG
	if(-1==startLog())
		goto startup_fail;
#endif
//#ifndef CONFIG_ETHWAN
#ifdef CONFIG_DEV_xDSL
	if (-1==startDsl())
		goto startup_fail;
#endif

#ifdef ELAN_LINK_MODE_INTRENAL_PHY
	setupLinkMode_internalPHY();
#endif

#if	defined(CONFIG_LUNA_DUAL_LINUX)
	setup_vwlan();
#endif


#ifdef WLAN_SUPPORT
	//if (-1==startWLan())
	//	goto startup_fail;
	startWLan();
#endif


#if (defined(CONFIG_RTL867X_NETLOG)  && defined (CONFIG_USER_NETLOGGER_SUPPORT))
//#ifndef CONFIG_8M_SDRAM
#ifndef CONFIG_8M_SDRAM
        va_cmd(NETLOGGER,0,1);
#endif
#endif

#ifdef _CWMP_MIB_ /*jiunming, mib for cwmp-tr069*/
	if (-1==startCWMP())
		goto startup_fail;
#endif
#ifdef _PRMT_TR143_
	struct TR143_UDPEchoConfig echoconfig;
	UDPEchoConfigSave( &echoconfig );
	UDPEchoConfigStart( &echoconfig );
#endif //_PRMT_TR143_

	//ql 20081117 START init MIB_QOS_UPRATE before startup IP QoS
#ifdef NEW_IP_QOS_SUPPORT
	unsigned int up_rate=0;
	mib_set(MIB_QOS_UPRATE, (void *)&up_rate);
#endif

	if (-1==startRest())
		goto startup_fail;

#ifdef CONFIG_USER_WATCHDOG_WDG
    //start watchdog & kick every 5 seconds silently
	//va_cmd_no_echo("/bin/wdg", 2, 1, "timeout", "10");
	//va_cmd_no_echo("/bin/wdg", 2, 1, "start", "5");
#endif
#if 0
#ifdef CONFIG_USER_PPPOE_PROXY
       va_cmd("/bin/pppoe-server",0,1);
#endif
#endif
	//take effect
#ifdef CONFIG_XFRM
	ipsec_take_effect();
#endif
#ifdef CONFIG_USER_PPTP_CLIENT_PPTP
	pptp_take_effect();
#ifdef CONFIG_USER_PPTPD_PPTPD
	pptpd_take_effect();
#endif
#endif
#ifdef CONFIG_USER_L2TPD_L2TPD
	l2tp_take_effect();
#endif
#ifdef CONFIG_USER_L2TPD_LNS
	l2tpd_take_effect();
#endif

//star add: for ZTE LED request
// Kaohj --- TR068 Power LED
	FILE *fp;
	unsigned char power_flag;
	fp = fopen("/proc/power_flag","w");
	if(fp)
	{
		power_flag = '0';
		fwrite(&power_flag,1,1,fp);
		fclose(fp);
	}

//#ifdef _CWMP_MIB_ /*jiunming, mib for cwmp-tr069*/
	/*when those processes created by startup are killed,
	  they will be zombie processes,jiunming*/
	signal(SIGCHLD, SIG_IGN);//add by star
//#endif

#if 1
#ifdef CONFIG_USER_SNMPD_SNMPD_V2CTRAP
	// Mason Yu. System init status
	snmpd_pid = read_pid("/var/run/snmpd.pid");
	if (snmpd_pid > 0) {
		printf("Send signal to snmpd.\n");
		kill(snmpd_pid, SIGUSR1);
	}
#endif
#endif

	/*ql: 20081117 START startup qos here*/
#ifdef NEW_IP_QOS_SUPPORT
#ifdef CONFIG_DEV_xDSL
	printf("start monitor QoS!\n");
	while(1)
	{
		signal(SIGCHLD, SIG_DFL);
		monitor_qos_setting();
		signal(SIGCHLD, SIG_IGN);
		usleep(5000000); // wait 5 sec
	}
#endif
#endif
	/*ql 20081117 END*/
	// Mason Yu. for IPv6
	// remove from startDaemon()
#if defined(CONFIG_USER_DNSMASQ_DNSMASQ) || defined(CONFIG_USER_DNSMASQ_DNSMASQ245)
	if (startDnsRelay() == -1)
	{
		printf("start DNS relay failed !\n");
	}
#endif
#ifdef CONFIG_USER_FON
	system("mkdir -p /var/spool/cron/crontabs");
	createChilliCronAdmin("/var/spool/cron/crontabs/admin");
	createChilliconf("/var/chilli.conf");
	createFonWhitelist("/tmp/whitelist.dnsmasq");
	startFonsmcd();
	startFonSpot();
#endif
#ifdef CONFIG_INIT_SCRIPTS
	printf("========== Initiating Ending Script =============\n");
	system("sh /var/config/end_script");
	printf("========== End Initiating Ending Script =============\n");
#endif


#if defined(CONFIG_USER_JAMVM) && defined (CONFIG_APACHE_FELIX_FRAMEWORK) 
	if(startOsgi() == 0)
		printf("OSGi Start Error!!!\n");
#endif


	// Mason Yu. To make sure that system startup is finished
	FILE *fp2;
	fp2 = fopen("/var/init_ok","w");
	if(fp)
	{
		fclose(fp);
	}
	return 0;

startup_fail:
	va_cmd("/bin/boa",0,1);
	printf("System startup failed !\n");
	return -1;
}

