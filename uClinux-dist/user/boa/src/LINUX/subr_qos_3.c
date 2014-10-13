/*
 *      System routines for IP QoS
 *
 */

#include "debug.h"
#include "utility.h"
#include <signal.h>
#include <string.h>
#include <netdb.h>

#define QOS_SETUP_DEBUG   1// for qos debug
#define MAX_PORT(val1, val2) (val1>val2?val1:val2)
#define MIN_PORT(val1, val2) (val1<val2?val1:val2)
const char QOS_IP_CHAIN[] =  "qos_ip_rules";
const char QOS_EB_CHAIN[] =  "qos_eb_rules";
const char QOS_RTP_CHAIN[] =  "qos_rtp_rules";
const char CAR_FILTER_CHAIN[] =  "car_filter";
const char CAR_TRAFFIC_CHAIN[] =  "car_traffic_qos";
static unsigned int qos_setup_debug = 3;


#ifdef QOS_SETUP_DEBUG
#define QOS_SETUP_PRINT_FUNCTION                    \
    do{if(qos_setup_debug&0x1) fprintf(stderr,"%s: %s  %d\n", __FILE__, __FUNCTION__,__LINE__);}while(0);

#define QOS_SETUP_PRINT(fmt, args...)        \
    do{if(qos_setup_debug&0x2) fprintf(stderr,fmt, ##args);}while(0)
#else
#define QOS_SETUP_PRINT_FUNCTION do{}while(0);
#define QOS_SETUP_PRINT(fmt, args...) do{}while(0)
#endif

#define RTP_RULE_NUM_MAX     256

#define QOS_WAN_ENABLE		0x01
#define QOS_WAN_VLAN_ENABLE	0x02
#define QOS_WAN_BRIDGE		0x04
#define QOS_WAN_TR069		0x08

#define QOS_MARK_MASK		0xFFF1FFFF
#define QOS_8021P_MASK		0x7
#define QOS_APP_NONE		0
#define QOS_APP_VOIP		1
#define QOS_APP_TR069		2


#ifdef QOS_SUPPORT_RTP
#define RTP_PORT_FILE	"/proc/net/ip_qos_rtp"
#endif

static char* proto2str[] = {
    [0]" ",
    [1]"-p TCP",
    [2]"-p UDP",
	[3]"-p ICMP",
};

static char* proto2str2layer[] = {
    [0]" ",
    [1]"--ip-proto 6",
    [2]"--ip-proto 17",
	[3]"--ip-proto 1",
};

#ifdef CONFIG_IPV6
static char* proto2str_v6[] = {
    [0]" ",
    [1]"-p TCP",
    [2]"-p UDP",
	[3]"-p ICMPV6",
};

static char* proto2str2layer_v6[] = {
    [0]" ",
    [1]"--ip6-proto 6",
    [2]"--ip6-proto 17",
	[3]"--ip6-proto 58",
};
#endif

static unsigned int current_uprate;

#ifdef CONFIG_HWNAT
#include "hwnat_ioctl.h"

static int fill_ip_family_common_rule(struct rtl867x_hwnat_qos_rule *qos_rule, MIB_CE_IP_QOS_Tp qEntry){
	//printf("qEntry->sip %x\n", *((struct in_addr *)qEntry->sip));
	//printf("qEntry->dip %x\n", *((struct in_addr *)qEntry->dip));
	qos_rule->Format_IP_SIP = (((struct in_addr *)qEntry->sip)->s_addr);
	if(qEntry->smaskbit != 0)
		qos_rule->Format_IP_SIP_M = ~((1<<(32-qEntry->smaskbit)) - 1);
	qos_rule->Format_IP_DIP = (((struct in_addr *)qEntry->dip)->s_addr);
	if(qEntry->dmaskbit != 0)
		qos_rule->Format_IP_DIP_M = ~((1<<(32-qEntry->dmaskbit)) - 1);
	return 0;
}

static int fill_ip_rule(struct rtl867x_hwnat_qos_rule *qos_rule, MIB_CE_IP_QOS_Tp qEntry){
	fill_ip_family_common_rule(qos_rule, qEntry);
	// protocol
	if (qEntry->protoType != PROTO_NONE) {//not none
		if((qEntry->flags&EXC_PROTOCOL) != EXC_PROTOCOL){//EXC_PROTOCOL didn't set, we don't support
			qos_rule->Format_IP_Proto_M = 0xff;
			if (qEntry->protoType == PROTO_TCP)
				qos_rule->Format_IP_Proto = 6;
			else if (qEntry->protoType == PROTO_UDP)
				qos_rule->Format_IP_Proto = 17;
			else if (qEntry->protoType == PROTO_ICMP)
				qos_rule->Format_IP_Proto = 1;
			else
				qos_rule->Format_IP_Proto_M = 0x0;
		}
	}
	return 0;
}

static int fill_tcp_rule(struct rtl867x_hwnat_qos_rule *qos_rule, MIB_CE_IP_QOS_Tp qEntry){
	fill_ip_family_common_rule(qos_rule, qEntry);
	qos_rule->Format_TCP_SPORT_Sta = qEntry->sPort;
	qos_rule->Format_TCP_SPORT_End = qEntry->sPortRangeMax;
	qos_rule->Format_TCP_DPORT_Sta = qEntry->dPort;
	qos_rule->Format_TCP_DPORT_End = qEntry->dPortRangeMax;
	return 0;
}

static int fill_udp_rule(struct rtl867x_hwnat_qos_rule *qos_rule, MIB_CE_IP_QOS_Tp qEntry){
	fill_ip_family_common_rule(qos_rule, qEntry);
	qos_rule->Format_UDP_SPORT_Sta = qEntry->sPort;
	qos_rule->Format_UDP_SPORT_End = qEntry->sPortRangeMax;
	qos_rule->Format_UDP_DPORT_Sta = qEntry->dPort;
	qos_rule->Format_UDP_DPORT_End = qEntry->dPortRangeMax;
	return 0;
}

static int hwnat_qos_translate_rule(MIB_CE_IP_QOS_Tp qEntry){
	hwnat_ioctl_cmd hifr;
	struct hwnat_ioctl_qos_cmd hiqc;
	struct rtl867x_hwnat_qos_rule *qos_rule;
	MIB_CE_ATM_VC_T pvcEntry;

	if ( qEntry->outif != DUMMY_IFINDEX ) {
		if( (MEDIA_INDEX(qEntry->outif) != MEDIA_ETH)
		  #ifdef CONFIG_PTMWAN
		   && (MEDIA_INDEX(qEntry->outif) != MEDIA_PTM)
		  #endif /*CONFIG_PTMWAN*/
		   )
			return -1;
	}
	memset(&hiqc, 0, sizeof(hiqc));
	hifr.type = HWNAT_IOCTL_QOS_TYPE;
	hifr.data = &hiqc;
	hiqc.type = QOSRULE_CMD;
	qos_rule = &(hiqc.u.qos_rule.qos_rule_pattern);
	//type decide
	//Warning! now we don't support exclude....
	//and we only try IP TYPE now...
	qos_rule->rule_type = RTL867x_IPQos_Format_IP;//default
	
	switch(qEntry->ipqos_rule_type)
	{
		case IPQOS_PORT_BASE:
			strncpy(qos_rule->Format_SRCPort_NETIFNAME, ELANVIF[qEntry->phyPort-1], strlen(ELANVIF[qEntry->phyPort-1]));
			//printf("qos_rule->Format_SRCPort_NETIFNAME=%s, ALIASNAME_ELAN0=%s\n", qos_rule->Format_SRCPort_NETIFNAME, ALIASNAME_ELAN0);
			qos_rule->rule_type = RTL867x_IPQos_Format_srcPort;
			break;
		case IPQOS_MAC_BASE:
		case IPQOS_ETHERTYPE_BASE:
			qos_rule->rule_type = RTL867x_IPQos_Format_Ethernet;
			break;
		case IPQOS_IP_PROTO_BASE:
			if (qEntry->protoType == PROTO_TCP)
				qos_rule->rule_type = RTL867x_IPQos_Format_TCP;
			else if (qEntry->protoType == PROTO_UDP)
				qos_rule->rule_type = RTL867x_IPQos_Format_UDP;
			else //if (qEntry->protoType == PROTO_ICMP)
				qos_rule->rule_type = RTL867x_IPQos_Format_IP;
			break;
		case IPQOS_8021P_BASE:
			qos_rule->rule_type = RTL867x_IPQos_Format_8021p;
			break;
		default:
			printf("Error! No HW QoS rule type matched, should not go here!\n");
			break;
	}

RULE_TYPE_OK:

	//remark dscp
/*DSCP modify Boyce 2014-06-06*/
#if defined(CONFIG_RTL_FTTDP_SUPPORT)
                hiqc.u.qos_rule.qos_rule_remark_dscp= qEntry->m_dscp -1;
#else
#ifdef QOS_DSCP
	if(qEntry->dscp==0) {
#endif
		// Kaohj -- use DSCP target to set IP-preced
		if (qEntry->m_ipprio) {
			hiqc.u.qos_rule.qos_rule_remark_dscp = (qEntry->m_ipprio-1) << 3;
		}
		if (qEntry->m_iptos != 0xff) {
			//seems we need to shift left 2 bits to fit DSCP's format?
			hiqc.u.qos_rule.qos_rule_remark_dscp |= ((qEntry->m_iptos)>>2);
		}
#ifdef QOS_DSCP
	}
	else if (qEntry->dscp == 1) {
		if (qEntry->m_ipprio != 0 || qEntry->m_iptos != 0) {
			hiqc.u.qos_rule.qos_rule_remark_dscp = qEntry->m_ipprio << 3;
			hiqc.u.qos_rule.qos_rule_remark_dscp |= qEntry->m_iptos << 1;
		}
	}
#endif
        
#endif

	//802.1p remark
	if(qEntry->m_1p != 0){
		hiqc.u.qos_rule.qos_rule_remark_8021p = (qEntry->m_1p-1);	// 802.1p
	}

	//vid remark
	if(qEntry->m_vid !=0){
		hiqc.u.qos_rule.qos_rule_vid = qEntry->m_vid;	// VLAN ID
	}
	//q_index
	hiqc.u.qos_rule.qos_rule_queue_index = qEntry->prior-1;  //(0, 1, 2, 3)
	//fill the rule
	switch(qos_rule->rule_type){
		case RTL867x_IPQos_Format_srcPort:
			break;
		case RTL867x_IPQos_Format_Ethernet:			
			{
				uint8 maskMac[MAC_ADDR_LEN]={0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
				memcpy(qos_rule->Format_Ethernet_SMAC.octet, qEntry->smac, MAC_ADDR_LEN);
				memcpy(qos_rule->Format_Ethernet_DMAC.octet, qEntry->dmac, MAC_ADDR_LEN);
				if (memcmp(qEntry->smac, EMPTY_MAC, MAC_ADDR_LEN))
					memcpy(qos_rule->Format_Ethernet_SMAC_M.octet, maskMac, MAC_ADDR_LEN);
				if (memcmp(qEntry->dmac, EMPTY_MAC, MAC_ADDR_LEN))
					memcpy(qos_rule->Format_Ethernet_DMAC_M.octet, maskMac, MAC_ADDR_LEN);

                                if(0 != qEntry->ethType) {
					qos_rule->Format_Ethernet_TYPE = qEntry->ethType;
                                        qos_rule->Format_Ethernet_TYPE_M = 0xffff;
			
			}
           }
			break;
                        
		case RTL867x_IPQos_Format_IP:
			fill_ip_rule(qos_rule, qEntry);
                        /*DSCP modify Boyce 2014-06-06
                        qEntry->qosDscp  
                        b'0=0 don't care dscp rule 
                        b'0=1 also compare dscp value  
                        */
                        #if defined(CONFIG_RTL_FTTDP_SUPPORT)
                                if(qEntry->qosDscp & 0x1)
                                {
                                        qos_rule->Format_IP_TOS =qEntry->qosDscp-1;
                                        qos_rule->Format_IP_TOS_M= 0xfC;  //only mask dscpField
                                }else
                                {
                                        qos_rule->Format_IP_TOS_M= 0x0;
                                }
                        #endif                        
			break;

		case RTL867x_IPQos_Format_TCP:
			fill_tcp_rule(qos_rule, qEntry);
                        /*DSCP modify Boyce 2014-06-06
                        qEntry->qosDscp  
                        b'0=0 don't care dscp rule
                        b'0=1 also compare dscp value  
                        */
                        #if defined(CONFIG_RTL_FTTDP_SUPPORT)
                                if(qEntry->qosDscp & 0x1)
                                {
                                        qos_rule->Format_IP_TOS =qEntry->qosDscp-1;
                                        qos_rule->Format_IP_TOS_M= 0xfC;  //only mask dscpField
                                }else
                                {
                                        qos_rule->Format_IP_TOS_M= 0x0;
                                }
                        #endif
			break;

		case RTL867x_IPQos_Format_UDP:
			fill_udp_rule(qos_rule, qEntry);
                        /*DSCP modify Boyce 2014-06-06
                        qEntry->qosDscp  
                        b'0=0 don't care dscp rule 
                        b'0=1 also compare dscp value  
                        */
                        #if defined(CONFIG_RTL_FTTDP_SUPPORT)
                                if(qEntry->qosDscp & 0x1)
                                {
                                        qos_rule->Format_IP_TOS =qEntry->qosDscp-1;
                                        qos_rule->Format_IP_TOS_M= 0xfC;  //only mask dscpField
                                }else
                                {
                                        qos_rule->Format_IP_TOS_M= 0x0;
                                }
                        #endif
			break;
                        
		// Added by Mason Yu. for 802.1p match
		case RTL867x_IPQos_Format_8021p:
			//printf("***** set hwnat rule for 801.1p match(%d)\n", (qEntry->vlan1p-1));
			qos_rule->Format_8021P_PRIORITY = qEntry->vlan1p-1;
			qos_rule->Format_8021P_PRIORITY_M = 0x07;
			break;
		default:
			break;
	}
	send_to_hwnat(hifr);
	return 0;
}

static int hwnat_qos_queue_setup(void){
	hwnat_ioctl_cmd hifr;
	struct hwnat_ioctl_qos_cmd hiqc;
	struct rtl867x_hwnat_qos_queue *qos_queue;

	memset(&hiqc, 0, sizeof(hiqc));
	hifr.type = HWNAT_IOCTL_QOS_TYPE;
	hifr.data = &hiqc;
	hiqc.type = OUTPUTQ_CMD;
	qos_queue = &(hiqc.u.qos_queue);
	qos_queue->action = QDISC_ENABLE;
	qos_queue->sp_num = 4;
	//qos_queue->bandwidth = -1;
	qos_queue->default_queue = 2;
	send_to_hwnat(hifr);
	return 0;
}

static int hwnat_qos_bandwidth_setup(int total_tandwidth){
	hwnat_ioctl_cmd hifr;
	struct hwnat_ioctl_qos_cmd hiqc;

	memset(&hiqc, 0, sizeof(hiqc));
	hifr.type = HWNAT_IOCTL_QOS_TYPE;
	hifr.data = &hiqc;
	hiqc.type = OUTPUTQ_BWCTL_CMD;
	hiqc.qos_total_bandwidth = total_tandwidth;
	send_to_hwnat(hifr);
	return 0;
}

static int hwnat_qos_queue_stop(void){
	hwnat_ioctl_cmd hifr;
	struct hwnat_ioctl_qos_cmd hiqc;
	struct rtl867x_hwnat_qos_queue *qos_queue;

	memset(&hiqc, 0, sizeof(hiqc));
	hifr.type = HWNAT_IOCTL_QOS_TYPE;
	hifr.data = &hiqc;
	hiqc.type = OUTPUTQ_CMD;
	qos_queue = &(hiqc.u.qos_queue);
	qos_queue->action = QDISC_DISABLE;
	send_to_hwnat(hifr);
	return 0;
}

#else
static int hwnat_qos_default_rule(void){}
static int hwnat_qos_translate_rule(MIB_CE_IP_QOS_Tp qEntry){}
static int hwnat_qos_queue_setup(void){}
static int hwnat_qos_queue_stop(void){}
static int hwnat_qos_bandwidth_setup(int total_tandwidth){}
#endif

int findQueueMinWeigh()
{
	int nBytes=0;
	MIB_CE_IP_QOS_QUEUE_T qEntry;
	int qEntryNum, i;

	if((qEntryNum=mib_chain_total(MIB_IP_QOS_QUEUE_TBL)) <=0)
		return nBytes;
	for(i=0;i<qEntryNum; i++)
	{
		if(!mib_chain_get(MIB_IP_QOS_QUEUE_TBL, i, (void*)&qEntry))
			continue;
		if ( !qEntry.enable)
			continue;

		if(nBytes==0)
			nBytes = qEntry.weight;

		if(qEntry.weight < nBytes)
			nBytes = qEntry.weight;
	}
	return nBytes;
}

int ifSumWeighIs100()
{
	int sum=0;
	MIB_CE_IP_QOS_QUEUE_T qEntry;
	int qEntryNum, i;

	if((qEntryNum=mib_chain_total(MIB_IP_QOS_QUEUE_TBL)) <=0)
		return 0;
	for(i=0;i<qEntryNum; i++)
	{
		if(!mib_chain_get(MIB_IP_QOS_QUEUE_TBL, i, (void*)&qEntry))
			continue;
		if ( !qEntry.enable)
			continue;
		sum += qEntry.weight;
	}

	if (sum == 100)
		return 1;
	else
		return 0;
}

int isQueneEnableForRule(unsigned char prior)
{
	MIB_CE_IP_QOS_QUEUE_T qEntry;
	int qEntryNum, j;

	if((qEntryNum=mib_chain_total(MIB_IP_QOS_QUEUE_TBL)) <=0)
		return 0;
	for(j=0;j<qEntryNum; j++)
	{
		if(!mib_chain_get(MIB_IP_QOS_QUEUE_TBL, j, (void*)&qEntry))
			continue;
		if (j == (prior-1))
		{
			if (qEntry.enable)
				return 1;
			break;
		}
	}
	return 0;
}

int set_wrr_class_qdisc()
{
	MIB_CE_IP_QOS_QUEUE_T qEntry;
	int qEntryNum, minWeigh, j;
	char *devname="imq0";
	char s_classid[16], s_handle[16], s_qlen[16];

	if((qEntryNum=mib_chain_total(MIB_IP_QOS_QUEUE_TBL)) <=0)
		return 0;
	for(j=0;j<qEntryNum; j++)
	{
		if(!mib_chain_get(MIB_IP_QOS_QUEUE_TBL, j, (void*)&qEntry))
			continue;
		if ( !qEntry.enable)
			continue;

		snprintf(s_classid, 16, "1:%d00", j+1);
		snprintf(s_handle, 16, "%d00:", j+1);
		minWeigh = findQueueMinWeigh();
		snprintf(s_qlen, 16, "%d", 30*qEntry.weight/100);
		//printf("set_wrr_class_qdisc: s_qlen=%s\n", s_qlen);

		va_cmd(TC, 11, 1, "qdisc", (char *)ARG_ADD, "dev", devname,
		"parent", s_classid, "handle", s_handle, "pfifo", "limit", s_qlen);

	}
	return 1;
}

//get state about qos from pvc interface, 0: false, 1: true
#ifdef BR_ROUTE_ONEPVC
static unsigned int get_pvc_qos_state(unsigned int ifIndex, unsigned char cmode)
#else
static unsigned int get_pvc_qos_state(unsigned int ifIndex)
#endif
{
	MIB_CE_ATM_VC_T entry;
	int i, entryNum = 0;
	unsigned int ret = 0;

	// Mason Yu.
	if ( ifIndex == DUMMY_IFINDEX )
		return QOS_WAN_VLAN_ENABLE;

	entryNum = mib_chain_total(MIB_ATM_VC_TBL);
	for(i = 0; i< entryNum; i++)
	{
		if(!mib_chain_get(MIB_ATM_VC_TBL, i, &entry))
			continue;

#ifdef BR_ROUTE_ONEPVC
		if (entry.cmode != cmode)
			continue;
#endif
		if(entry.ifIndex == ifIndex)
		{
			if(entry.enableIpQos)
				ret |= QOS_WAN_ENABLE;
			if(entry.vlan)
				ret |= QOS_WAN_VLAN_ENABLE;
#ifndef BR_ROUTE_ONEPVC
			if (entry.cmode == ADSL_BR1483)
				ret |= QOS_WAN_BRIDGE;
#endif
			// Mason Yu.
#if 0
			/*ql:20080825 START: for tr069 pvc, just set priority according to wanport*/
			if (entry.applicationtype&X_CT_SRV_TR069)
			//if (entry.applicationtype == APPTYPE_TR069)//tr069
				ret |= QOS_WAN_TR069;
			/*ql:20080825 END*/
#endif
			break;
		}
	}

	return ret;
}

static unsigned int getUpLinkRate()
{
	unsigned int total_bandwidth = 1024;//default to be 1Mbps

	//  Because we can not distinguish total bandwidth. It is for total bandwidth limit. Let user to input total bandwidth.
	if(mib_get(MIB_TOTAL_BANDWIDTH, &total_bandwidth))
	{
		return total_bandwidth;
	}
	else
		return 1024;
}

// QoS Enable
int getQosEnable()
{
	unsigned char qosEnable;

	mib_get(MIB_QOS_ENABLE_QOS, (void*)&qosEnable);
	return (int)qosEnable;
}

int getQosRuleNum()
{
	MIB_CE_IP_QOS_T entry;
	int i, ruleNum;
	int sum=0;

	ruleNum = mib_chain_total(MIB_IP_QOS_TBL);
	if (0 == ruleNum)
		return 0;

	for (i=0; i<ruleNum; i++)
	{
		if (!mib_chain_get(MIB_IP_QOS_TBL, i, (void *)&entry) || !entry.enable)
			continue;

		sum++;
	}

	return(sum);
}

static int isQosMacRule(MIB_CE_IP_QOS_Tp pEntry)
{
	if (pEntry->protoType || pEntry->sip || pEntry->dip || pEntry->sPort ||
		pEntry->dPort || pEntry->qosDscp)
		return 0;
	return 1;
}

static int mac_hex2string(unsigned char *hex, char *str)
{
	snprintf(str, 18, "%02x:%02x:%02x:%02x:%02x:%02x",
		hex[0], hex[1],	hex[2], hex[3],	hex[4], hex[5]);
	return 0;
}

static int setupCarChain(unsigned int enable)
{
	QOS_SETUP_PRINT_FUNCTION

	if (enable)
	{
		va_cmd(IPTABLES, 2, 1, "-N", CAR_FILTER_CHAIN);
		va_cmd(IPTABLES, 5, 1, "-I", "FORWARD", "1", "-j", CAR_FILTER_CHAIN);

		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-N", CAR_TRAFFIC_CHAIN);
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-A", "POSTROUTING", "-j", CAR_TRAFFIC_CHAIN);

		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-N", "pvc_mark");
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-A", "POSTROUTING", "-j", "pvc_mark");

		#ifdef CONFIG_IPV6
		va_cmd(IP6TABLES, 2, 1, "-N", CAR_FILTER_CHAIN);
		va_cmd(IP6TABLES, 5, 1, "-I", "FORWARD", "1", "-j", CAR_FILTER_CHAIN);

		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-N", CAR_TRAFFIC_CHAIN);
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-A", "POSTROUTING", "-j", CAR_TRAFFIC_CHAIN);

		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-N", "pvc_mark");
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-A", "POSTROUTING", "-j", "pvc_mark");
		#endif
	} else {
		va_cmd(IPTABLES, 2, 1, "-F", CAR_FILTER_CHAIN);
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-F", "pvc_mark");
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-F", CAR_TRAFFIC_CHAIN);

		va_cmd(IPTABLES, 4, 1, "-D", "FORWARD", "-j", CAR_FILTER_CHAIN);
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-D", "POSTROUTING", "-j", "pvc_mark");
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-D", "POSTROUTING", "-j", CAR_TRAFFIC_CHAIN);

		va_cmd(IPTABLES, 2, 1, "-X", CAR_FILTER_CHAIN);
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-X", "pvc_mark");
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-X", CAR_TRAFFIC_CHAIN);

		#ifdef CONFIG_IPV6
		va_cmd(IP6TABLES, 2, 1, "-F", CAR_FILTER_CHAIN);
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-F", "pvc_mark");
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-F", CAR_TRAFFIC_CHAIN);

		va_cmd(IP6TABLES, 4, 1, "-D", "FORWARD", "-j", CAR_FILTER_CHAIN);
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-D", "POSTROUTING", "-j", "pvc_mark");
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-D", "POSTROUTING", "-j", CAR_TRAFFIC_CHAIN);

		va_cmd(IP6TABLES, 2, 1, "-X", CAR_FILTER_CHAIN);
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-X", "pvc_mark");
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-X", CAR_TRAFFIC_CHAIN);
		#endif
	}

	return 1;
}

/*
 *                              HTB(root qdisc, handle 10:)
 *                               |
 *                              HTB(root class, classid 10:1)
 *            ___________________|_____________________
 *            |         |        |          |          |
 *           HTB       HTB      HTB        HTB        HTB
 *(subclass id 10:10 rate Xkbit)........       (sub class id 10:N0 rate Ykbit)
 */
static int setupCarQdisc(unsigned int enable)
{
	MIB_CE_ATM_VC_T vcEntry;
	int i, vcEntryNum;
	char ifname[IFNAMSIZ];
	char s_rate[16], s_ceil[16];
	unsigned char totalBandWidthEn;
	unsigned int bandwidth;
	unsigned int rate, ceil;

	QOS_SETUP_PRINT_FUNCTION;

	mib_get(MIB_TOTAL_BANDWIDTH_LIMIT_EN, (void *)&totalBandWidthEn);

	if (totalBandWidthEn) {
		mib_get(MIB_TOTAL_BANDWIDTH, &bandwidth);
	}
	else
		bandwidth = getUpLinkRate();

	vcEntryNum = mib_chain_total(MIB_ATM_VC_TBL);
	for(i=0;i<vcEntryNum; i++)
	{
		if(!mib_chain_get(MIB_ATM_VC_TBL, i, (void*)&vcEntry)||!vcEntry.enableIpQos)
			continue;

		ifGetName(vcEntry.ifIndex, ifname, sizeof(ifname));

		if (!enable) {
			va_cmd(TC, 5, 1, "qdisc", (char *)ARG_DEL, "dev", ifname, "root");
			continue;
		}
#ifdef BR_ROUTE_ONEPVC
		if (vcEntry.br_route_flag)
		{
			if (vcEntry.cmode == ADSL_BR1483)
			{//check if route itf has enabled qos
				if (isPvcQosEnable(&vcEntry))
					continue;
			}
		}
#endif
		//patch: actual bandwidth maybe a little greater than configured limit value, so I minish 7% of the configured limit value ahead.
		if (totalBandWidthEn)
			//ceil = bandwidth/100 * 93;
			ceil = bandwidth*93/100;
		else
			ceil = bandwidth;

		//tc qdisc add dev $DEV root handle 1: htb default 2 r2q 1		
		va_cmd(TC, 12, 1, "qdisc", (char *)ARG_ADD, "dev", ifname,
			"root", "handle", "1:", "htb", "default", "2", "r2q", "1");

		// root class
		snprintf(s_rate, 16, "%dKbit", ceil);
		//tc class add dev $DEV parent 1: classid 1:1 htb rate $RATE ceil $CEIL
		va_cmd(TC, 17, 1, "class", (char *)ARG_ADD, "dev", ifname,
			"parent", "1:", "classid", "1:1", "htb", "rate", s_rate, "ceil", s_rate,
			"mpu", "64", "overhead", "4");

		//patch with above
		rate = (ceil>10)?10:ceil;

		// default class
		snprintf(s_rate, 16, "%dKbit", rate);
		snprintf(s_ceil, 16, "%dKbit", ceil);
		//tc class add dev $DEV parent 1:1 classid 1:2 htb rate $RATE ceil $CEIL
		va_cmd(TC, 17, 1, "class", (char *)ARG_ADD, "dev", ifname,
			"parent", "1:1", "classid", "1:2", "htb", "rate",
			s_rate, "ceil", s_ceil, "mpu", "64", "overhead", "4");

		va_cmd(TC, 11, 1, "qdisc", (char *)ARG_ADD, "dev", ifname,
			"parent", "1:2", "handle", "2:", "pfifo", "limit", "10");
	}

	return 0;
}

static int setupCarRule_one(MIB_CE_IP_TC_Tp entry)
{
	char ifname[IFNAMSIZ]={0};
	char* tc_act = NULL, *fw_act=NULL;
	char* proto1 = NULL, *proto2 = NULL;
	char wanPort[16]={0};
	char  saddr[55], daddr[55], sport[16], dport[16];
	char tmpstr[48];
	int upLinkRate=0, childRate=0;
	int mark;
	char *iptables_cmd=NULL, *tc_protocol=NULL;
	DOCMDINIT;

	QOS_SETUP_PRINT_FUNCTION;

	tc_act = (char*)ARG_ADD;
	fw_act = (char*)FW_ADD;

	if(NULL == entry) {
		printf("Null traffic contolling rule!\n");
		return 1;
	}

	ifGetName(entry->ifIndex, ifname, sizeof(ifname));
	//wan interface
	if (ifname[0] != '\0')
		snprintf(wanPort, 16, "-o %s", ifname);

#ifdef CONFIG_IPV6
	// This is a IPv4 rule
	if ( entry->IpProtocol == 0x1 ) {
		//source address and netmask
		snprintf(tmpstr, 16, "%s", inet_ntoa(*((struct in_addr *)entry->srcip)));
		if (strcmp(tmpstr, ARG_0x4)) {
			if(0 != entry->smaskbits) {
				snprintf(saddr, 24, "-s %s/%d", tmpstr, entry->smaskbits);
			} else {
				snprintf(saddr, 24, "-s %s", tmpstr);
			}
		}
		else {//if not specify the source ip
			saddr[0] = '\0';
		}
	}
	// This is a IPv6 rule
	else if ( entry->IpProtocol == 0x2 ) {
		//source address and netmask
		inet_ntop(PF_INET6, (struct in6_addr *)entry->sip6, tmpstr, sizeof(tmpstr));
		if (strcmp(tmpstr, "::")) {
			if(0 != entry->sip6PrefixLen) {
				snprintf(saddr, 55, "-s %s/%d", tmpstr, entry->sip6PrefixLen);
			} else {
				snprintf(saddr, 55, "-s %s", tmpstr);
			}
		}
		else {//if not specify the source ip
			saddr[0] = '\0';
		}
	}
#else
	//source address and netmask
	snprintf(tmpstr, 16, "%s", inet_ntoa(*((struct in_addr *)entry->srcip)));
	if (strcmp(tmpstr, ARG_0x4)) {
		if(0 != entry->smaskbits) {
			snprintf(saddr, 24, "-s %s/%d", tmpstr, entry->smaskbits);
		} else {
			snprintf(saddr, 24, "-s %s", tmpstr);
		}
	}
	else {//if not specify the source ip
		saddr[0] = '\0';
	}
#endif

#ifdef CONFIG_IPV6
	// This is a IPv4 rule
	if ( entry->IpProtocol == 0x1 ) {
		//destination address and netmask
		snprintf(tmpstr, 16, "%s", inet_ntoa(*((struct in_addr *)entry->dstip)));
		if (strcmp(tmpstr, ARG_0x4)) {
			if(0 != entry->dmaskbits) {
				snprintf(daddr, 24, "-d %s/%d", tmpstr, entry->dmaskbits);
			} else {
				snprintf(daddr, 24, "-d %s", tmpstr);
			}
		} else {//if not specify the dest ip
			daddr[0] = '\0';
		}
	}
	// This is a IPv6 rule
	else if ( entry->IpProtocol == 0x2 ) {
		//destination address and netmask
		inet_ntop(PF_INET6, (struct in6_addr *)entry->dip6, tmpstr, sizeof(tmpstr));
		if (strcmp(tmpstr, "::")) {
			if(0 != entry->dip6PrefixLen) {
				snprintf(daddr, 55, "-d %s/%d", tmpstr, entry->dip6PrefixLen);
			} else {
				snprintf(daddr, 55, "-d %s", tmpstr);
			}
		} else {//if not specify the dest ip
			daddr[0] = '\0';
		}
	}
#else
	//destination address and netmask
	snprintf(tmpstr, 16, "%s", inet_ntoa(*((struct in_addr *)entry->dstip)));
	if (strcmp(tmpstr, ARG_0x4)) {
		if(0 != entry->dmaskbits) {
			snprintf(daddr, 24, "-d %s/%d", tmpstr, entry->dmaskbits);
		} else {
			snprintf(daddr, 24, "-d %s", tmpstr);
		}
	} else {//if not specify the dest ip
		daddr[0] = '\0';
	}
#endif

	//source port
	if(0 != entry->sport) {
		snprintf(sport, 16, "--sport %d", entry->sport);
	} else {
		sport[0] = '\0';
	}

	//destination port
	if(0 != entry->dport) {
		snprintf(dport, 16, "--dport %d", entry->dport);
	} else {
		dport[0] = '\0';
	}

	//protocol
	//if (((0 != entry->sport) || (0 != entry->dport)) &&
	//	(entry->protoType < 2))
	//	entry->protoType = 4;

	if(entry->protoType>4)//wrong protocol index
	{
		printf("Wrong protocol\n");
		return 1;
	} else {
		switch(entry->protoType)
		{
			case PROTO_NONE://NONE
				proto1 = " ";
				break;
			case PROTO_ICMP://ICMP
				#ifdef CONFIG_IPV6
				// This is a IPv4 rule
				if ( entry->IpProtocol == 0x1 )
					proto1 = "-p ICMP";
				// This is a IPv6 rule
				else if ( entry->IpProtocol == 0x2 )
					proto1 = "-p ICMPV6";
				#else
				proto1 = "-p ICMP";
				#endif
				break;
			case PROTO_TCP://TCP
				proto1 = "-p TCP";
				break;
			case PROTO_UDP://UDP
				proto1 = "-p UDP";
				break;
			case PROTO_UDPTCP://TCP/UDP
				proto1 = "-p TCP";
				proto2 = "-p UDP";
				break;
		}
	}

#ifdef CONFIG_IPV6
		// This is a IPv4 rule
		if ( entry->IpProtocol == 0x1 ) {
			iptables_cmd = "/bin/iptables";
			tc_protocol = "protocol ip";
		}
		// This is a IPv6 rule
		else {
			iptables_cmd = "/bin/ip6tables";
			tc_protocol = "protocol ipv6";
		}
#else
		// This is a IPv4 rule
		iptables_cmd = "/bin/iptables";
		tc_protocol = "protocol ip";
#endif

	upLinkRate = entry->limitSpeed;
	if(0 != upLinkRate)
	{
		//get mark
		mark = (entry->entryid<<12);

		//patch: true bandwidth will be a little greater than limit value, so I minish 7% of set limit value ahead.
		int ceil;
		//ceil = upLinkRate/100 * 93;
		ceil = upLinkRate*93/100;

		childRate = (10>ceil)?ceil:10;
		//childRate = ceil;

		DOCMDARGVS(TC, DOWAIT, "class %s dev %s parent 1:1 classid 1:%d0 htb rate %dkbit ceil %dkbit mpu 64 overhead 4",
			tc_act, ifname, entry->entryid, childRate, ceil);

		DOCMDARGVS(TC, DOWAIT, "qdisc %s dev %s parent 1:%d0 handle %d1: pfifo limit 10",
			tc_act, ifname, entry->entryid, entry->entryid);

		//DOCMDARGVS(TC, DOWAIT, "filter %s dev %s parent 1: protocol ip prio 0 handle 0x%x fw flowid 1:%d0",
		//	tc_act, ifname, mark, entry->entryid);
		DOCMDARGVS(TC, DOWAIT, "filter %s dev %s parent 1: %s prio 0 handle 0x%x fw flowid 1:%d0",
			tc_act, ifname, tc_protocol, mark, entry->entryid);

		DOCMDARGVS(iptables_cmd, DOWAIT,  "-t mangle %s %s %s %s %s %s %s %s -j MARK --set-mark 0x%x",
			fw_act, CAR_TRAFFIC_CHAIN, wanPort, proto1, saddr, daddr, sport, dport, mark);

		/*TCP/UDP?*/
		if(proto2)//setup the other protocol
		{
			DOCMDARGVS(iptables_cmd, DOWAIT, "-t mangle %s %s %s %s %s %s %s %s -j MARK --set-mark 0x%x",
				fw_act, CAR_TRAFFIC_CHAIN, wanPort, proto2, saddr, daddr, sport, dport, mark);
		}
	}
	else
	{//if uprate=0, forbid traffic matching the rules
		DOCMDARGVS(iptables_cmd, DOWAIT, "-t filter %s %s %s %s %s %s %s %s -j DROP",
			fw_act, CAR_FILTER_CHAIN, wanPort, proto1, saddr, daddr, sport, dport);

		/*TCP/UDP again*/
		if(proto2)
		{
			DOCMDARGVS(iptables_cmd, DOWAIT, "-t filter %s %s %s %s %s %s %s %s -j DROP",
				fw_act, CAR_FILTER_CHAIN, wanPort, proto2, saddr, daddr, sport, dport);
		}
	}

	return 0;
}

static int setupCarRule()
{
	int entry_num, i;
	MIB_CE_IP_TC_T  entry;

	entry_num = mib_chain_total(MIB_IP_QOS_TC_TBL);

	for(i=0; i<entry_num; i++)
	{
		if(!mib_chain_get(MIB_IP_QOS_TC_TBL, i, (void*)&entry))
			continue;

		if (setupCarRule_one(&entry))
			return 1;
	}

	return 0;
}

/*********************************************************************
 * NAME:    setup_qos_rules
 * DESC:    Using iptables to setup rules for queue, including packet
 *          marking(dscp, 802.1p). This function doesn't affect traffic
 *          controlling, just for priority and weighted round robin
 *          queue. Suppose that the mib setting is well-formated and right.
 * ARGS:    none
 * RETURN:  0 success, others fail
 *********************************************************************/
static int setup_qos_rules(unsigned char policy)
{
	MIB_CE_IP_QOS_T entry;
	MIB_CE_ATM_VC_T vcEntry;
	int i, j, EntryNum = 0, vcEntryNum = 0;
	unsigned char enableDscpMark=1;
#ifdef QOS_SUPPORT_RTP
	FILE *fp;
	char buff[100];
	unsigned int rtp_dip;
	unsigned int rtp_dpt;
	unsigned int rtpCnt=0, rtpRuleCnt=0;
	struct rtp_struct {
		unsigned int dip;
		unsigned int dport;
	} __PACK__;
	struct rtp_rule_st {
		char daddr[48];
		char dport[48];
	} __PACK__;

	struct rtp_struct rtp_entry[RTP_RULE_NUM_MAX];
	struct rtp_rule_st rtp_rule_entry[RTP_RULE_NUM_MAX];
#endif

	DOCMDINIT

	QOS_SETUP_PRINT_FUNCTION

	if(PLY_WRR==policy)//weighted round robin
	{
		if (!ifSumWeighIs100())
			return 1;
	}

	//get current RTP stream info
#ifdef QOS_SUPPORT_RTP
	if (!(fp=fopen(RTP_PORT_FILE, "r"))) {
		printf("no RTP connection!\n");
	} else {
		while ( fgets(buff, sizeof(buff), fp) != NULL ) {
			if(sscanf(buff, "dip=%d dport=%d", &rtp_dip, &rtp_dpt)!=2) {
				printf("Unsuported rtp format\n");
				break;
			}
			else {
				rtpCnt++;
				rtp_entry[rtpCnt-1].dip = rtp_dip;
				rtp_entry[rtpCnt-1].dport = rtp_dpt;
			}
		}
		fclose(fp);
	}
#endif
	//mib_get(MIB_QOS_ENABLE_DSCP_MARK, (void *)&enableDscpMark);

	EntryNum = mib_chain_total(MIB_IP_QOS_TBL);
	for(i=0; i<EntryNum; i++)
	{
		char ifname[IFNAMSIZ], phyPort[16]={0};
		char phyPort1[16]={0};
		char wanPort[16]={0};
		char sport[48]={0}, dport[48]={0}, saddr[75]={0}, daddr[75]={0}, strmark[48]={0}, strEthType[48]={0};
		char tmpstr[48];
		char *proto1=NULL, *proto2 = NULL, *eth_proto = NULL;
		char *iptables_cmd=NULL, *tc_protocol=NULL;
		char dscp[24] = {0};
		unsigned int mark=0;
		char smac[48]={0}, dmac[48]={0};
		//ql
		unsigned int wan_qos_state = 0;
		unsigned int wan_vlan_enable = 0;
		/*ql:20080825 START: for tr069 pvc, just set priority according to wanport*/
		unsigned int wan_tr069=0;
		/*ql:20080825 END*/
		unsigned int ebtable=0;
		unsigned short vid=0;
		char dhcpopt_cmd[80]={0};

		if(!mib_chain_get(MIB_IP_QOS_TBL, i, (void*)&entry)||!entry.enable)
		    continue;

		if(!isQueneEnableForRule(entry.prior))
			continue;

#ifdef BR_ROUTE_ONEPVC
		wan_qos_state = get_pvc_qos_state(entry.outif, entry.cmode);
#else
		wan_qos_state = get_pvc_qos_state(entry.outif);
#endif
		wan_vlan_enable = wan_qos_state&QOS_WAN_VLAN_ENABLE;
		/*ql:20080825 START: for tr069 pvc, just set priority according to wanport*/
		wan_tr069 = wan_qos_state&QOS_WAN_TR069;
		/*ql:20080825 END*/
#ifdef BR_ROUTE_ONEPVC
		if ((entry.outif != DUMMY_IFINDEX) && (entry.cmode == ADSL_BR1483))
			ebtable = 1;
#else
		ebtable = wan_qos_state&QOS_WAN_BRIDGE;
#endif
		// If this rule is for All WAN interface(DUMMY_IFINDEX), use ebtables to set rule.
	    if ( entry.outif == DUMMY_IFINDEX ) {
			ebtable = 1;
		}

		//interface
		if ( entry.outif != DUMMY_IFINDEX ) {
			ifGetName(entry.outif, ifname, sizeof(ifname));

			//wan port
			snprintf(wanPort, 16, "-o %s", ifname);
		}

		if (memcmp(entry.smac, EMPTY_MAC, MAC_ADDR_LEN)) {
			mac_hex2string(entry.smac, tmpstr);
			snprintf(smac, 48, "-s %s", tmpstr);
		}
		else
			smac[0] = '\0';

		if (memcmp(entry.dmac, EMPTY_MAC, MAC_ADDR_LEN)) {
			mac_hex2string(entry.dmac, tmpstr);
			snprintf(dmac, 48, "-d %s", tmpstr);
		}
		else
			dmac[0] = '\0';

		if ((smac[0] != '\0') || (dmac[0] != '\0'))
			ebtable = 1;

		//phy port, 0: none, range:1-4
		if (entry.phyPort>=1 && entry.phyPort<=SW_LAN_PORT_NUM)
			snprintf(phyPort, 16, "-i %s", SW_LAN_PORT_IF[entry.phyPort-1]);
		else {
			if (ebtable)
				phyPort[0] = '\0';
			else
#ifdef CONFIG_PPPOE_PROXY_IF_NAME
				/*ql:20080805 START: qos enable for ppp proxy*/
				snprintf(phyPort, 16, "-i br+");
				/*ql: 20080805 END*/
#else
				snprintf(phyPort, 16, "-i br0");
#endif
		}

		//dscp match
		if(0 != entry.qosDscp)
		{
			#ifdef CONFIG_IPV6
			if (ebtable) {
				// This is a IPv4 rule
				if ( entry.IpProtocol == 0x1 )
					snprintf(dscp, 24, "--ip-tos 0x%x", (entry.qosDscp-1)&0xFF);
				// This is a IPv6 rule
				else if ( entry.IpProtocol == 0x2 )
					snprintf(dscp, 24, "--ip6-tclass 0x%x", (entry.qosDscp-1)&0xFF);
			}
			#else
			if (ebtable)
				snprintf(dscp, 24, "--ip-tos 0x%x", (entry.qosDscp-1)&0xFF);
			#endif
			else
				snprintf(dscp, 24, "-m dscp --dscp 0x%x", (entry.qosDscp-1)>>2);
		}else{
		    dscp[0]='\0';
		}

		//protocol
#ifdef QOS_SUPPORT_RTP
		if(entry.protoType>5)//invalid protocol index
			return 1;
#else
		if(entry.protoType>4)//invalid protocol index
			return 1;
#endif

		//source port (range)
		if(0 == entry.protoType||1 == entry.protoType||0 == entry.sPort)
		{//if protocol is icmp or none or port not set, ignore the port
		    sport[0] = '\0';
		}
		else
		{
			#ifdef CONFIG_IPV6
			// This is a IPv4 rule
			if ( entry.IpProtocol == 0x1 && ebtable) {
					if(0 != entry.sPortRangeMax)
						snprintf(sport, 48, "--ip-source-port %d:%d", MIN_PORT(entry.sPort, entry.sPortRangeMax),
							MAX_PORT(entry.sPort, entry.sPortRangeMax));
					else
						snprintf(sport, 48, "--ip-source-port %d", entry.sPort);
			}
			// This is a IPv6 rule
			else if ( entry.IpProtocol == 0x2 && ebtable) {
					if(0 != entry.sPortRangeMax)
						snprintf(sport, 48, "--ip6-source-port %d:%d", MIN_PORT(entry.sPort, entry.sPortRangeMax),
							MAX_PORT(entry.sPort, entry.sPortRangeMax));
					else
						snprintf(sport, 48, "--ip6-source-port %d", entry.sPort);
			}
			#else
			if (ebtable) {
				if(0 != entry.sPortRangeMax)
					snprintf(sport, 48, "--ip-source-port %d:%d", MIN_PORT(entry.sPort, entry.sPortRangeMax),
						MAX_PORT(entry.sPort, entry.sPortRangeMax));
				else
					snprintf(sport, 48, "--ip-source-port %d", entry.sPort);
			}
			#endif
			else {
				if(0 != entry.sPortRangeMax)
					snprintf(sport, 48, "--sport %d:%d", MIN_PORT(entry.sPort, entry.sPortRangeMax),
						MAX_PORT(entry.sPort, entry.sPortRangeMax));
				else
					snprintf(sport, 48, "--sport %d", entry.sPort);
			}
		}

#ifdef CONFIG_IPV6
		// This is a IPv4 rule
		if ( entry.IpProtocol == 0x1 ) {
			//source address
			snprintf(tmpstr, 16, "%s", inet_ntoa(*((struct in_addr *)entry.sip)));
			if (strcmp(tmpstr, ARG_0x4)) {
				if (ebtable) {
					if(0 != entry.smaskbit)
						snprintf(saddr, 48, "--ip-source %s/%d",
							tmpstr, entry.smaskbit );
					else
						snprintf(saddr, 48, "--ip-source %s", tmpstr);
				}
				else {
					if(0 != entry.smaskbit)
						snprintf(saddr, 48, "-s %s/%d",
							tmpstr, entry.smaskbit );
					else
						snprintf(saddr, 48, "-s %s", tmpstr);
				}
			}
			else
				saddr[0]='\0';
		}
		// This is a IPv6 rule
		else if ( entry.IpProtocol == 0x2 ) {
			//source address
			inet_ntop(PF_INET6, (struct in6_addr *)entry.sip6, tmpstr, sizeof(tmpstr));
			if (strcmp(tmpstr, "::")) {
				if (ebtable) {
					if(0 != entry.sip6PrefixLen)
						snprintf(saddr, 75, "--ip6-source %s/%d",
							tmpstr, entry.sip6PrefixLen );
					else
						snprintf(saddr, 75, "--ip6-source %s", tmpstr);
				}
				else {
					if(0 != entry.sip6PrefixLen)
						snprintf(saddr, 75, "-s %s/%d",
							tmpstr, entry.sip6PrefixLen );
					else
						snprintf(saddr, 75, "-s %s", tmpstr);
				}
			}
			else
				saddr[0]='\0';
		}
#else
		//source address
		snprintf(tmpstr, 16, "%s", inet_ntoa(*((struct in_addr *)entry.sip)));
		if (strcmp(tmpstr, ARG_0x4)) {
			if (ebtable) {
				if(0 != entry.smaskbit)
					snprintf(saddr, 48, "--ip-source %s/%d",
						tmpstr, entry.smaskbit );
				else
					snprintf(saddr, 48, "--ip-source %s", tmpstr);
			}
			else {
				if(0 != entry.smaskbit)
					snprintf(saddr, 48, "-s %s/%d",
						tmpstr, entry.smaskbit );
				else
					snprintf(saddr, 48, "-s %s", tmpstr);
			}
		}
		else
			saddr[0]='\0';
#endif

#ifdef QOS_SUPPORT_RTP
		if (entry.protoType == 5)//RTP
		{
			if (0 == rtpCnt)//no rtp stream found
				continue;

			if (ebtable)
				continue;//don't process such rule
			else
				proto1 = "-p UDP";

			rtpRuleCnt = 0;
/*star:20090407 START only parse rtp src port*/
			snprintf(tmpstr, 16, "%s", inet_ntoa(*((struct in_addr *)entry.dip)));
			if (strcmp(tmpstr, ARG_0x4)) {
				for (j=0; j<rtpCnt; j++) {
					rtpRuleCnt++;

					if(0 != entry.dmaskbit)
						snprintf(rtp_rule_entry[rtpRuleCnt-1].daddr, 26, "-d %s/%d",
							tmpstr, entry.dmaskbit );
					else
						snprintf(rtp_rule_entry[rtpRuleCnt-1].daddr, 26, "-d %s", tmpstr);

					snprintf(rtp_rule_entry[rtpRuleCnt-1].dport, 24, "--sport %d", rtp_entry[j].dport);
				}
				if (rtpRuleCnt==0)//not found .
					continue;
			} else {
				for (j=0; j<rtpCnt; j++) {
					rtpRuleCnt++;
					//snprintf(rtp_rule_entry[rtpRuleCnt-1].daddr, 26, "-d %s", inet_ntoa(*((struct in_addr*)(&rtp_entry[j].dip))));
					rtp_rule_entry[rtpRuleCnt-1].daddr[0]=0;
					snprintf(rtp_rule_entry[rtpRuleCnt-1].dport, 24, "--sport %d", rtp_entry[j].dport);
				}
			}
		}
		else
		{
#endif
			if(entry.protoType == 4)//add by penggenyao, support two protos at the same time
			{
				#ifdef CONFIG_IPV6
				if (ebtable) {
					// This is a IPv4 rule
					if ( entry.IpProtocol == 0x1 ) {
						proto1 = "--ip-proto 6";
						proto2 = "--ip-proto 17";
					}
					// This is a IPv6 rule
					else if ( entry.IpProtocol == 0x2 ) {
						proto1 = "--ip6-proto 6";
						proto2 = "--ip6-proto 17";
					}
				}
				#else
				if (ebtable) {
					proto1 = "--ip-proto 6";
					proto2 = "--ip-proto 17";
				}
				#endif
				else {
				    proto1 = "-p TCP";
				    proto2 = "-p UDP";
				}
			}
			else {
				#ifdef CONFIG_IPV6
				if (ebtable) {
					// This is a IPv4 rule
					if ( entry.IpProtocol == 0x1 )
						proto1 = proto2str2layer[entry.protoType];
					// This is a IPv6 rule
					else if ( entry.IpProtocol == 0x2 )
						proto1 = proto2str2layer_v6[entry.protoType];
				}
				else {
					// This is a IPv4 rule
					if ( entry.IpProtocol == 0x1 )
						proto1 = proto2str[entry.protoType];
					// This is a IPv6 rule
					else if ( entry.IpProtocol == 0x2 )
						proto1 = proto2str_v6[entry.protoType];
				}
				#else
				if (ebtable)
					proto1 = proto2str2layer[entry.protoType];
				else
					proto1 = proto2str[entry.protoType];
				#endif

			}

			//dest port (range)
			if(0 == entry.protoType||1 == entry.protoType||0 == entry.dPort)
			{//if protocol is icmp or none or port not set, ignore the port
			    dport[0] = '\0';
			}
			else
			{
				#ifdef CONFIG_IPV6
				// This is a IPv4 rule
				if ( entry.IpProtocol == 0x1 && ebtable) {
						if(0 != entry.dPortRangeMax)
							snprintf(dport, 48, "--ip-destination-port %d:%d", MIN_PORT(entry.dPort, entry.dPortRangeMax),
								MAX_PORT(entry.dPort, entry.dPortRangeMax));
						else
							snprintf(dport, 48, "--ip-destination-port %d", entry.dPort);
				}
				// This is a IPv6 rule
				else if ( entry.IpProtocol == 0x2 && ebtable) {
						if(0 != entry.dPortRangeMax)
							snprintf(dport, 48, "--ip6-destination-port %d:%d", MIN_PORT(entry.dPort, entry.dPortRangeMax),
								MAX_PORT(entry.dPort, entry.dPortRangeMax));
						else
							snprintf(dport, 48, "--ip6-destination-port %d", entry.dPort);
				}
				#else
				if (ebtable) {
					if(0 != entry.dPortRangeMax)
						snprintf(dport, 48, "--ip-destination-port %d:%d", MIN_PORT(entry.dPort, entry.dPortRangeMax),
							MAX_PORT(entry.dPort, entry.dPortRangeMax));
					else
						snprintf(dport, 48, "--ip-destination-port %d", entry.dPort);
				}
				#endif
				else {
				    if(0 != entry.dPortRangeMax)
						snprintf(dport, 48, "--dport %d:%d", MIN_PORT(entry.dPort, entry.dPortRangeMax),
							MAX_PORT(entry.dPort, entry.dPortRangeMax));
				    else
						snprintf(dport, 48, "--dport %d", entry.dPort);
				}
			}

#ifdef CONFIG_IPV6
			// This is a IPv4 rule
			if ( entry.IpProtocol == 0x1 ) {
				//dest address
				snprintf(tmpstr, 16, "%s", inet_ntoa(*((struct in_addr *)entry.dip)));
				if (strcmp(tmpstr, ARG_0x4)) {
					if (ebtable) {
						if(0 != entry.dmaskbit)
							snprintf(daddr, 48, "--ip-destination %s/%d",
								tmpstr, entry.dmaskbit );
						else
							snprintf(daddr, 48, "--ip-destination %s", tmpstr);
					} else {
						if(0 != entry.dmaskbit)
							snprintf(daddr, 48, "-d %s/%d",
								tmpstr, entry.dmaskbit );
						else
							snprintf(daddr, 48, "-d %s", tmpstr);
					}
				}
				else
					daddr[0]='\0';
			}
			// This is a IPv6 rule
			else if ( entry.IpProtocol == 0x2 ){
				//dest address
				inet_ntop(PF_INET6, (struct in6_addr *)entry.dip6, tmpstr, sizeof(tmpstr));
				if (strcmp(tmpstr, "::")) {
					if (ebtable) {
						if(0 != entry.dip6PrefixLen)
							snprintf(daddr, 75, "--ip6-destination %s/%d",
								tmpstr, entry.dip6PrefixLen );
						else
							snprintf(daddr, 75, "--ip6-destination %s", tmpstr);
					}
					else {
						if(0 != entry.dip6PrefixLen)
							snprintf(daddr, 75, "-d %s/%d",
								tmpstr, entry.dip6PrefixLen );
						else
							snprintf(daddr, 75, "-d %s", tmpstr);
					}
				}
				else {
					daddr[0]='\0';
				}
			}
#else
			//dest address
			snprintf(tmpstr, 16, "%s", inet_ntoa(*((struct in_addr *)entry.dip)));
			if (strcmp(tmpstr, ARG_0x4)) {
				if (ebtable) {
					if(0 != entry.dmaskbit)
						snprintf(daddr, 48, "--ip-destination %s/%d",
							tmpstr, entry.dmaskbit );
					else
						snprintf(daddr, 48, "--ip-destination %s", tmpstr);
				} else {
					if(0 != entry.dmaskbit)
						snprintf(daddr, 48, "-d %s/%d",
							tmpstr, entry.dmaskbit );
					else
						snprintf(daddr, 48, "-d %s", tmpstr);
				}
			}
			else
				daddr[0]='\0';
#endif

#ifdef QOS_SUPPORT_RTP
		}
#endif

		//lan 802.1p mark, 0-2 bit(match)
		if(0 != entry.vlan1p) {
			// Mason Yu
			ebtable=1;
			phyPort[0] = '\0';						
			snprintf(strmark, 48, "--vlan-prio %d", (entry.vlan1p-1)&0xff);
		} else
			strmark[0] = '\0';

		if (ebtable) {
			if(strmark[0] != '\0')//vlan 802.1p priority, use 802.1Q ethernet protocol
			{
				eth_proto = "-p 0x8100";
			}
			else {//use ipv4 for ethernet protocol
#ifdef CONFIG_IPV6
		if(entry.ipqos_rule_type==IPQOS_IP_PROTO_BASE)
		{
				// This is a IPv4 rule
				if ( entry.IpProtocol == 0x1 )
					eth_proto = "-p 0x0800";
				// This is a IPv6 rule
				else if ( entry.IpProtocol == 0x2 )
					eth_proto = "-p 0x86dd";
		}
		else  if(entry.ipqos_rule_type==IPQOS_DHCPOPT_BASE)
			eth_proto = "-p 0x0800";
				else
					eth_proto = " ";
#else
				if (!isQosMacRule(&entry))
					eth_proto = "-p 0x0800";
				else
					eth_proto = " ";
#endif
			}
		}
		
		// Match Ethernet Type		
		if(0 != entry.ethType) {			
			ebtable=1;									
			snprintf(strEthType, 48, "-p 0x%x", entry.ethType);
			eth_proto = strEthType;
		} else
			strEthType[0] = '\0';

#ifdef CONFIG_BRIDGE_EBT_DHCP_OPT
		if(entry.ipqos_rule_type==IPQOS_DHCPOPT_BASE)
		{
			char duid_mac[20]={0};
			// duid mac
			snprintf(duid_mac, 18, "%02x:%02x:%02x:%02x:%02x:%02x",
					entry.duid_mac[0], entry.duid_mac[1],
					entry.duid_mac[2], entry.duid_mac[3],
					entry.duid_mac[4], entry.duid_mac[5]);
			switch(entry.dhcpopt_type)
			{
				case IPQOS_DHCPOPT_60:
					//EX:ebtables -A FORWARD --dhcp-opt60 ABC -j DROP
					sprintf(dhcpopt_cmd,"--dhcp-opt60 \"%s\"",entry.opt60_vendorclass);
					break;
				case IPQOS_DHCPOPT_61:
					switch(entry.opt61_duid_type)
					{
						case 0:  //llt , EX: ebtables -A FORWARD --dhcp-opt61 1234/llt/1/1234/00:12:34:56:12:13 -j DROP
							sprintf(dhcpopt_cmd,"--dhcp-opt61 %d/llt/%d/%d/%s",entry.opt61_iaid,entry.duid_hw_type,entry.duid_time,duid_mac);
							break;
						case 1:  //en , EX: ebtables -A FORWARD --dhcp-opt61 1234/en/1234/ABCDE -j DROP
							sprintf(dhcpopt_cmd,"--dhcp-opt61 %d/en/%d/%s",entry.opt61_iaid,entry.duid_ent_num,entry.duid_ent_id);
							break;
						case 2:  //ll, EX: ebtables -A FORWARD --dhcp-opt61 1234/ll/1/00:12:34:56:12:13 -j DROP
							sprintf(dhcpopt_cmd,"--dhcp-opt61 %d/ll/%d/%s",entry.opt61_iaid,entry.duid_hw_type,duid_mac);
							break;
					}
					break;
				case IPQOS_DHCPOPT_125:
					//EX: ebtables -A FORWARD --dhcp-opt125 1234//DEF// -j DROP
					sprintf(dhcpopt_cmd,"--dhcp-opt125 %d/%s/%s/%s/%s",
							entry.opt125_ent_num,
							entry.opt125_manufacturer,
							entry.opt125_product_class,
							entry.opt125_model,
							entry.opt125_serial);
					break;
				default:
					break;
			}
			eth_proto = "-p 0x0800";
		}
		printf("dhcpopt_cmd:[%s]\n",dhcpopt_cmd);
#endif // CONFIG_BRIDGE_EBT_DHCP_OPT

		//wan 802.1p mark 0-2 bit: 802.1p, 8-15 bit: entry id
		// We can not use 0 to as tc handle. So we use (i+1).

		//======================================================================
		//
		// For port based/protocol based/Source IP based ....etc VLAN function.
		//
		// Using Mark to let driver know how to insert 802.1Q header.
		// The rule is as following desgin. And please be reminded that current
		// port mapping function is using bit [31:24] so port mapping and this
		// 802.1Q VLAN function could not exist at the same time.
		//
		// VLAN ID  [31:20](12 bits): value should be 1~4095
		// DNS Bind [19:17]( 3 bits): For DNS Binding
		// Qos Enable  [16]( 1 bit) : Qos Enable Indicator
		// Qos Entry [15:8]( 8 bits): Qos Enctry ID
		// VLAN Enable  [7]( 1 bit) : VLAN ID Enable Indicator
		// 802.1p     [2:0]( 3 bits): 802.1p value. (0~7)
		//
		//        28      24      20      16      12      8       4       0   
		// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		// |    VLAN ID[31:20]     |DNSb |Q|  Qos Entry ID |V|       | p   |
		// |       (12bits)        |3bits|1| [15:8] (8bits)|1|       |[2:0]|
		// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		//
		//======================================================================

		//vid, if VLAN ID is configured(value>0), 
		//     then set it into bit [31:20] and turn on bit 7(VLAN enable)
		if(entry.m_vid>0)
		{
			vid= entry.m_vid;
			mark |= (vid) <<20 | (1<<7);
		}
		
		if((0 != entry.m_1p)) {
		    mark |= (entry.m_1p-1)&0x7;
				//ql 20090106 START: set bit 16 of nfmark when tag 802.1p
				mark |= (((i+1)<<8) | (1<<16));
			}
			else {
				mark |= ((i+1)<<8);
			}

#ifdef CONFIG_IPV6
		// This is a IPv6 rule
		if ( entry.IpProtocol == IPv6 ){
			iptables_cmd = "/bin/ip6tables";
			tc_protocol = "protocol all";
		}
		else  {  // This is a IPv4 rule or no specify protocol. (EX: LAN Port)
			iptables_cmd = "/bin/iptables";
			tc_protocol = "protocol all";
		}

#else
		// This is a IPv4 rule
		iptables_cmd = "/bin/iptables";
		tc_protocol = "protocol all";
#endif

		//2004/03/04 should add rule to set dscp value first, since rules to set mark , the target changed to ACCEPT.

		//set dscp
		if( enableDscpMark && (0 != entry.m_dscp))
		{
#ifdef QOS_SUPPORT_RTP
			if (entry.protoType != 5)//RTP
			{
#endif
				if (!ebtable) {
						//forward chain
						DOCMDARGVS(iptables_cmd, DOWAIT, "-t mangle -A %s %s %s %s %s %s %s %s %s %s -j DSCP --set-dscp 0x%x",
							QOS_IP_CHAIN, phyPort, wanPort, (proto1==NULL)?"":proto1, saddr, sport, daddr, dport, dscp, strmark, (entry.m_dscp-1)>>2);
						//output chain
						if (!entry.phyPort && !saddr[0] && !strmark[0] && !dscp[0] && (daddr[0] || dport[0])) {
							DOCMDARGVS(iptables_cmd, DOWAIT, "-t mangle -A qos_rule_output %s %s %s %s %s -j DSCP --set-dscp 0x%x",
								wanPort, (proto1==NULL)?"":proto1, sport, daddr, dport, (entry.m_dscp-1)>>2);
						}

						if(proto2)/* TCP/UDP, bored, why not set twice, any other wise idea? */
						{
							//forward chain
							DOCMDARGVS(iptables_cmd, DOWAIT, "-t mangle -A %s %s %s %s %s %s %s %s %s %s -j DSCP --set-dscp 0x%x",
								QOS_IP_CHAIN, phyPort, wanPort, proto2, saddr, sport, daddr, dport, dscp, strmark, (entry.m_dscp-1)>>2);
							//output chain
							if (!entry.phyPort && !saddr[0] && !strmark[0] && !dscp[0] && (daddr[0] || dport[0])) {
								DOCMDARGVS(iptables_cmd, DOWAIT, "-t mangle -A qos_rule_output %s %s %s %s %s -j DSCP --set-dscp 0x%x",
									wanPort, proto2, sport, daddr, dport, (entry.m_dscp-1)>>2);
							}
						}
				} else {
					// 2014/3/4 Because DHCP Option 60 may contain space, and original way DOCMDARGVS 
					//	        will seperate argument by space, it's not workable. So, change this way 
					//	        by using system function call.

					char cmd_buf[200]={0};
					sprintf(cmd_buf,"%s -t %s -A %s %s %s %s %s %s %s %s %s %s %s %s %s -j ftos --set-ftos 0x%x", 
							EBTABLES, "broute", QOS_EB_CHAIN, phyPort, eth_proto, (proto1==NULL)?" ":proto1, smac, dmac, saddr, sport, daddr, dport, dscp, strmark, dhcpopt_cmd, (entry.m_dscp-1)&0xFF);
					system(cmd_buf);
						if(proto2)
						{
						sprintf(cmd_buf,"%s -t %s -A %s %s %s %s %s %s %s %s %s %s %s %s %s -j ftos --set-ftos 0x%x", 
								EBTABLES, "broute", QOS_EB_CHAIN, phyPort, eth_proto, proto2, smac, dmac, saddr, sport, daddr, dport, dscp, strmark, dhcpopt_cmd, (entry.m_dscp-1)&0xFF);
						system(cmd_buf);
						}
				}
#ifdef QOS_SUPPORT_RTP
			} else {
				if (!ebtable) {
					for (j=0; j<rtpRuleCnt; j++) {
						DOCMDARGVS(iptables_cmd, DOWAIT, "-t mangle -A %s %s %s %s %s %s %s %s %s %s -j DSCP --set-dscp 0x%x",
							QOS_RTP_CHAIN, phyPort, wanPort, (proto1==NULL)?"":proto1, saddr, sport, rtp_rule_entry[j].daddr, rtp_rule_entry[j].dport, dscp, strmark, (entry.m_dscp-1)>>2);
					}
				}
			}
#endif
		}

//set the mark
#ifdef QOS_SUPPORT_RTP
		if (entry.protoType != 5)//RTP
		{
		
#endif
			if (!ebtable) {
				/*ql:20080825 START: for tr069 pvc, just set priority according to wanport*/
				if (wan_tr069)
				{
					DOCMDARGVS(iptables_cmd, DOWAIT, "-t mangle -A qos_rule_output %s -j MARK --set-mark 0x%x/0x%x",
						wanPort, mark, QOS_MARK_MASK);
				} else {
				/*ql:20080825 END*/
					//forward chain
					DOCMDARGVS(iptables_cmd, DOWAIT, "-t mangle -A %s %s %s %s %s %s %s %s %s %s -j MARK --set-mark 0x%x/0x%x",
						QOS_IP_CHAIN, phyPort, wanPort, (proto1==NULL)?"":proto1, saddr, sport, daddr, dport, dscp, strmark, mark, QOS_MARK_MASK);
					//output chain
					if (!entry.phyPort && !saddr[0] && !strmark[0] && !dscp[0] && (daddr[0] || dport[0])) {
						DOCMDARGVS(iptables_cmd, DOWAIT, "-t mangle -A qos_rule_output %s %s %s %s %s -j MARK --set-mark 0x%x/0x%x",
							wanPort, (proto1==NULL)?"":proto1, sport, daddr, dport, mark, QOS_MARK_MASK);
					}

					if(proto2) /*OK, Here it comes again. TCP/UDP*/
					{
						//forward chain
						DOCMDARGVS(iptables_cmd, DOWAIT, "-t mangle -A %s %s %s %s %s %s %s %s %s %s -j MARK --set-mark 0x%x/0x%x",
							QOS_IP_CHAIN, phyPort, wanPort, proto2, saddr, sport, daddr, dport, dscp, strmark, mark, QOS_MARK_MASK);
						//output chain
						if (!entry.phyPort && !saddr[0] && !strmark[0] && !dscp[0] && (daddr[0] || dport[0])) {
							DOCMDARGVS(iptables_cmd, DOWAIT, "-t mangle -A qos_rule_output %s %s %s %s %s -j MARK --set-mark 0x%x/0x%x",
								wanPort, proto2, sport, daddr, dport, mark, QOS_MARK_MASK);
						}
					}
				/*ql:20080825 START: for tr069 pvc, just set priority according to wanport*/
				}
				/*ql:20080825 END*/
			} else {
				// Mason Yu. match IN interface error
				//if (phyPort[0]) {
				//
					if(entry.ipqos_rule_type==IPQOS_ETHERTYPE_BASE)
					{
						DOCMDARGVS(EBTABLES, DOWAIT, "-t %s -A %s %s -j mark --mark-or 0x%x --mark-target ACCEPT", "broute",
								QOS_EB_CHAIN, eth_proto, mark);
					
					}
					else
					{
						// 2014/3/4 Because DHCP Option 60 may contain space, and original way DOCMDARGVS 
						//	        will seperate argument by space, it's not workable. So, change this way 
						//	        by using system function call.
						// 2014/3/4 --mark-target ACCEPT, if match, ACCEPT it, not use default CONTINUE, because the rule may
						//          match for multiple rules, and the mark value may not be correct.        

						char cmd_buf[200]={0};
						sprintf(cmd_buf,"%s -t %s -A %s %s %s %s %s %s %s %s %s %s %s %s %s -j mark --mark-or 0x%x --mark-target ACCEPT", 
								EBTABLES, "broute", QOS_EB_CHAIN, phyPort, eth_proto, (proto1==NULL)?" ":proto1, smac, dmac, saddr, sport, daddr, dport, dscp, strmark, dhcpopt_cmd, mark);
						system(cmd_buf);
					if(proto2)
					{
							sprintf(cmd_buf,"%s -t %s -A %s %s %s %s %s %s %s %s %s %s %s %s %s -j mark --mark-or 0x%x --mark-target ACCEPT", 
									EBTABLES, "broute", QOS_EB_CHAIN, phyPort, eth_proto, proto2, smac, dmac, saddr, sport, daddr, dport, dscp, strmark, dhcpopt_cmd, mark);
							system(cmd_buf);
					}
				}
			}
#ifdef QOS_SUPPORT_RTP
		} else {
			if (!ebtable) {
				for (j=0; j<rtpRuleCnt; j++) {
					DOCMDARGVS(iptables_cmd, DOWAIT, "-t mangle -A %s %s %s %s %s %s %s %s %s %s -j MARK --set-mark 0x%x/0x%x",
						QOS_RTP_CHAIN, phyPort, wanPort, (proto1==NULL)?"":proto1, saddr, sport, rtp_rule_entry[j].daddr, rtp_rule_entry[j].dport, dscp, strmark, mark, QOS_MARK_MASK);
				}
			}
		}
#endif

		vcEntryNum = mib_chain_total(MIB_ATM_VC_TBL);

#ifndef QOS_SETUP_IMQ
		if(PLY_PRIO==policy)//priority queue
		{
			//DOCMDARGVS(TC, DOWAIT, "filter add dev %s parent 1: prio %d protocol ip handle 0x%x/0x%x fw flowid 1:%d",
			//	ifname, entry.prior, mark, QOS_MARK_MASK, entry.prior);
			for(j=0; j<vcEntryNum; j++)
			{
				if(!mib_chain_get(MIB_ATM_VC_TBL, j, &vcEntry))
					continue;

				ifGetName(vcEntry.ifIndex, ifname, sizeof(ifname));
				DOCMDARGVS(TC, DOWAIT, "filter add dev %s parent 1: prio %d %s handle 0x%x/0x%x fw flowid 1:%d",
					ifname, entry.prior, tc_protocol, mark, QOS_MARK_MASK, entry.prior);
			}
		}
		else if(PLY_WRR==policy)//weighted round robin
		{
			for(j=0; j<vcEntryNum; j++)
			{
				if(!mib_chain_get(MIB_ATM_VC_TBL, j, &vcEntry))
					continue;

				ifGetName(vcEntry.ifIndex, ifname, sizeof(ifname));

				DOCMDARGVS(TC, DOWAIT, "filter add dev %s parent 1: prio 1 %s handle 0x%x/0x%x fw flowid 1:%d00",
					ifname, tc_protocol, mark, QOS_MARK_MASK, entry.prior);
			}
		}
#else
		if(PLY_PRIO==policy)//priority queue
		{

			ifGetName(vcEntry.ifIndex, ifname, sizeof(ifname));
			DOCMDARGVS(TC, DOWAIT, "filter add dev imq0 parent 2: prio %d %s handle 0x%x/0x%x fw flowid 2:%d",
					entry.prior, tc_protocol, mark, QOS_MARK_MASK, entry.prior);

			//if in bridge mode, need redirect packet to imq0 by tc filter rule
			if (ebtable) {
			for(j=0; j<vcEntryNum; j++)
			{
				if(!mib_chain_get(MIB_ATM_VC_TBL, j, &vcEntry))
					continue;

				ifGetName(vcEntry.ifIndex, ifname, sizeof(ifname));
					DOCMDARGVS(TC, DOWAIT, "filter add dev %s parent 1: prio %d %s handle 0x%x/0x%x fw flowid 2:%d action mirred egress redirect dev imq0",
					ifname, entry.prior, tc_protocol, mark, QOS_MARK_MASK, entry.prior);
			}
		}
		}
		else if(PLY_WRR==policy)//weighted round robin
		{
			DOCMDARGVS(TC, DOWAIT, "filter add dev imq0 parent 1: prio 1 %s handle 0x%x/0x%x fw flowid 1:%d00",
				tc_protocol, mark, QOS_MARK_MASK, entry.prior);

			// Mason Yu.
			// If the vc is bridge mode , set tc action mirred and redirect to img0
			if (ebtable) {				
				for(j=0; j<vcEntryNum; j++)
				{
					if(!mib_chain_get(MIB_ATM_VC_TBL, j, &vcEntry))
						continue;

					ifGetName(vcEntry.ifIndex, ifname, sizeof(ifname));					
					DOCMDARGVS(TC, DOWAIT, "filter add dev %s parent 1: prio 1 %s handle 0x%x/0x%x fw flowid 1:1 action mirred egress redirect dev imq0",
						ifname, tc_protocol, mark, QOS_MARK_MASK);					
				}
			}
		}
#endif
		//if ( (wan_qos_state&QOS_WAN_BRIDGE) != QOS_WAN_BRIDGE) {
			// hwnat qos
			hwnat_qos_translate_rule(&entry);
		//}
#ifdef CONFIG_RTK_RG_INIT
		RTK_RG_QoS_Rule_Set(&entry);
#endif
	}

    return 0;
}

static int setupQosRuleChain(unsigned int enable)
{
	QOS_SETUP_PRINT_FUNCTION;

	if (enable)
	{
		va_cmd(EBTABLES, 4, 1, "-t", "broute", "-N", QOS_EB_CHAIN);
		va_cmd(EBTABLES, 5, 1, "-t", "broute", "-P", QOS_EB_CHAIN, "RETURN");
		va_cmd(EBTABLES, 6, 1, "-t", "broute", "-A", "BROUTING", "-j", QOS_EB_CHAIN);

		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-N", QOS_IP_CHAIN);
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-A", "FORWARD", "-j", QOS_IP_CHAIN);

		//for rtp qos
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-N", QOS_RTP_CHAIN);
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-A", "FORWARD", "-j", QOS_RTP_CHAIN);

		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-N", "pvc_mark");
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-A", "FORWARD", "-j", "pvc_mark");

		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-N", "qos_rule_output");
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-A", "OUTPUT", "-j", "qos_rule_output");

		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-N", "pvc_mark_output");
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-A", "OUTPUT", "-j", "pvc_mark_output");

#ifdef CONFIG_IPV6
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-N", QOS_IP_CHAIN);
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-A", "FORWARD", "-j", QOS_IP_CHAIN);

		//for rtp qos
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-N", QOS_RTP_CHAIN);
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-A", "FORWARD", "-j", QOS_RTP_CHAIN);

		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-N", "pvc_mark");
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-A", "FORWARD", "-j", "pvc_mark");

		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-N", "qos_rule_output");
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-A", "OUTPUT", "-j", "qos_rule_output");

		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-N", "pvc_mark_output");
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-A", "OUTPUT", "-j", "pvc_mark_output");
#endif
	} else {
		va_cmd(EBTABLES, 4, 1, "-t", "broute", "-F", QOS_EB_CHAIN);
		va_cmd(EBTABLES, 6, 1, "-t", "broute", "-D", "BROUTING", "-j", QOS_EB_CHAIN);
		va_cmd(EBTABLES, 4, 1, "-t", "broute", "-X", QOS_EB_CHAIN);

		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-F", "pvc_mark");
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-F", QOS_IP_CHAIN);
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-F", QOS_RTP_CHAIN);	//for rtp qos
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-F", "pvc_mark_output");
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-F", "qos_rule_output");

		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-D", "FORWARD", "-j", "pvc_mark");
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-D", "FORWARD", "-j", QOS_IP_CHAIN);
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-D", "FORWARD", "-j", QOS_RTP_CHAIN);
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-D", "OUTPUT", "-j", "pvc_mark_output");
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-D", "OUTPUT", "-j", "qos_rule_output");

		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-X", "pvc_mark");
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-X", QOS_IP_CHAIN);
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-X", QOS_RTP_CHAIN);
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-X", "pvc_mark_output");
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-X", "qos_rule_output");

#ifdef CONFIG_IPV6
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-F", "pvc_mark");
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-F", QOS_IP_CHAIN);
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-F", QOS_RTP_CHAIN);	//for rtp qos
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-F", "pvc_mark_output");
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-F", "qos_rule_output");

		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-D", "FORWARD", "-j", "pvc_mark");
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-D", "FORWARD", "-j", QOS_IP_CHAIN);
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-D", "FORWARD", "-j", QOS_RTP_CHAIN);
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-D", "OUTPUT", "-j", "pvc_mark_output");
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-D", "OUTPUT", "-j", "qos_rule_output");

		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-X", "pvc_mark");
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-X", QOS_IP_CHAIN);
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-X", QOS_RTP_CHAIN);
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-X", "pvc_mark_output");
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-X", "qos_rule_output");
#endif
	}

	return 1;
}

static int setup_prio_queue(int enable)
{
	// Mason Yu. Use device name not imq0
	char *imq0_devname="imq0";
	//char devname[IFNAMSIZ];
	MIB_CE_ATM_VC_T vcEntry;
	int i, vcEntryNum;
	char s_rate[16], s_ceil[16];
	char tc_cmd[100];
	unsigned int total_bandwidth = 0;

	QOS_SETUP_PRINT_FUNCTION;

	if(!enable){
		va_cmd(TC, 5, 1, "qdisc", (char *)ARG_DEL, "dev", imq0_devname, "root");
		hwnat_qos_bandwidth_setup(0);
	}

	//tc qdisc add dev $DEV root handle 1: htb default 400
	va_cmd(TC, 10, 1, "qdisc", (char *)ARG_ADD, "dev", imq0_devname,
		"root", "handle", "1:", "htb", "default", "100");
	
	//set total_bandwidth limit in imq0, and let packet be mirred to imq0 by tc filter or iptables rule	
	total_bandwidth = getUpLinkRate();
	hwnat_qos_bandwidth_setup(total_bandwidth*1024);
	snprintf(s_rate, 16, "%dKbit", total_bandwidth);
	snprintf(s_ceil, 16, "%dKbit", total_bandwidth);
	va_cmd(TC, 13, 1, "class", "add", "dev", imq0_devname,
		"parent", "1:", "classid", "1:100", "htb", "rate", s_rate, "ceil", s_ceil);

	snprintf(tc_cmd, 100, "tc qdisc add dev %s parent 1:100 handle 2: prio bands 4 priomap %s", imq0_devname, "3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3");
	TRACE(STA_SCRIPT,"%s\n",tc_cmd);
	system(tc_cmd);
	va_cmd(TC, 11, 1, "qdisc", (char *)ARG_ADD, "dev", imq0_devname,
		"parent", "2:1", "handle", "3:", "pfifo", "limit", "10");
	va_cmd(TC, 11, 1, "qdisc", (char *)ARG_ADD, "dev", imq0_devname,
		"parent", "2:2", "handle", "4:", "pfifo", "limit", "10");
	va_cmd(TC, 11, 1, "qdisc", (char *)ARG_ADD, "dev", imq0_devname,
		"parent", "2:3", "handle", "5:", "pfifo", "limit", "10");
	va_cmd(TC, 11, 1, "qdisc", (char *)ARG_ADD, "dev", imq0_devname,
		"parent", "2:4", "handle", "6:", "pfifo", "limit", "10");
	
	vcEntryNum = mib_chain_total(MIB_ATM_VC_TBL);
	for(i=0;i<vcEntryNum; i++)
	{
		char devname[IFNAMSIZ];
		if(!mib_chain_get(MIB_ATM_VC_TBL, i, (void*)&vcEntry)||!vcEntry.enableIpQos)
			continue;

		ifGetName(vcEntry.ifIndex, devname, sizeof(devname));

		if (!enable) {
			va_cmd(TC, 5, 1, "qdisc", (char *)ARG_DEL, "dev", devname, "root");
			continue;
		}

		snprintf(tc_cmd, 100, "tc qdisc add dev %s root handle 1: prio bands 4 priomap %s", devname, "3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3");
		TRACE(STA_SCRIPT,"%s\n",tc_cmd);
		system(tc_cmd);
		va_cmd(TC, 11, 1, "qdisc", (char *)ARG_ADD, "dev", devname,
			"parent", "1:1", "handle", "2:", "pfifo", "limit", "10");
		va_cmd(TC, 11, 1, "qdisc", (char *)ARG_ADD, "dev", devname,
			"parent", "1:2", "handle", "3:", "pfifo", "limit", "10");
		va_cmd(TC, 11, 1, "qdisc", (char *)ARG_ADD, "dev", devname,
			"parent", "1:3", "handle", "4:", "pfifo", "limit", "10");
		va_cmd(TC, 11, 1, "qdisc", (char *)ARG_ADD, "dev", devname,
			"parent", "1:4", "handle", "5:", "pfifo", "limit", "10");
	}
	if (!enable) {
			// disable IPQoS
			__dev_setupIPQoS(0);
	}
	else {
		// enable IPQoS
		__dev_setupIPQoS(1);
	}
	return 0;
}

/*
 *	action:
 *	0: Add
 *	1: Change
 */
static int setup_htb_class(int action, unsigned int upRate)
{
	char *devname="imq0";
	char s_rate[16], s_ceil[16], s_classid[16], s_quantum[16];
	const char *pAction;
	int j;
	int rate, ceil, quantum;
	unsigned char enableForceWeight=0;
	MIB_CE_IP_QOS_QUEUE_T qEntry;
	int qEntryNum, minWeigh;

	if (action == 0)
		pAction = ARG_ADD;
	else
		pAction = ARG_CHANGE;
	snprintf(s_rate, 16, "%dKbit", upRate);
	snprintf(s_ceil, 16, "%dKbit", upRate);
	//tc class add dev $DEV parent 1: classid 1:1 htb rate $RATE ceil $CEIL
	va_cmd(TC, 13, 1, "class", pAction, "dev", devname,
		"parent", "1:", "classid", "1:1", "htb", "rate", s_rate, "ceil", s_ceil);

	//mib_get(MIB_QOS_ENABLE_FORCE_WEIGHT, (void *)&enableForceWeight);

	if((qEntryNum=mib_chain_total(MIB_IP_QOS_QUEUE_TBL)) <=0)
		return 0;
	for(j=0;j<qEntryNum; j++)
	{
		if(!mib_chain_get(MIB_IP_QOS_QUEUE_TBL, j, (void*)&qEntry))
			continue;
		if ( !qEntry.enable)
			continue;

		snprintf(s_classid, 16, "1:%d00", j+1);
		minWeigh = findQueueMinWeigh();
		// Quantum should be bigger then MTU (1500) so you can send the maximum packet in 1 turn and smaller then 60000
		quantum = (1500*qEntry.weight)/minWeigh;
		if (quantum > 60000)
			quantum = 60000;
		snprintf(s_quantum, 16, "%d", quantum);
		//printf("s_quantum=%s\n", s_quantum);
		rate = qEntry.weight;
		//if enableForceWeight, then send rate should not larger than wrr proportion
		ceil = enableForceWeight?(upRate*qEntry.weight/100):upRate;
		snprintf(s_ceil, 16, "%dKbit", ceil);
		if (rate > ceil)
		{
			if (enableForceWeight) rate = ceil;
			else rate = ceil*qEntry.weight/100;
		}
		snprintf(s_rate, 16, "%dKbit", rate);

		//tc class add dev $DEV parent 10:1 classid 10:$SUBID htb rate $RATE ceil $RATE prio $PRIO
		va_cmd(TC, 15, 1, "class", pAction, "dev", devname,
			"parent", "1:1", "classid", s_classid, "htb", "rate",
			s_rate, "ceil", s_ceil, "quantum", s_quantum);
	}

}

static int setup_wrr_queue(enable)
{
	int j;
	char *devname="imq0";
	char s_rate[16], s_ceil[16], s_classid[16], s_quantum[16];
	unsigned int total_bandwidth = 0;

	MIB_CE_ATM_VC_T vcEntry;
	int i, vcEntryNum;
	char tc_cmd[100];
	char devname2[IFNAMSIZ];

	QOS_SETUP_PRINT_FUNCTION;

	if (!enable) {
		va_cmd(TC, 5, 1, "qdisc", (char *)ARG_DEL, "dev", devname, "root");
		//return 0;
		goto SETVCQDISC;
	}

	if (!ifSumWeighIs100())
		return 0;

	total_bandwidth = getUpLinkRate();
	current_uprate = total_bandwidth;

	snprintf(s_rate, 16, "%dKbit", total_bandwidth);
	snprintf(s_ceil, 16, "%dKbit", total_bandwidth);
	//tc qdisc add dev $DEV root handle 1: htb default 400
	va_cmd(TC, 10, 1, "qdisc", (char *)ARG_ADD, "dev", devname,
		"root", "handle", "1:", "htb", "default", "400");

	setup_htb_class(0, total_bandwidth);
	//set queue len
	set_wrr_class_qdisc();

SETVCQDISC:
	// Mason Yu.
	// If the vc is bridge mode , set root qdisc for tc action mirred
	vcEntryNum = mib_chain_total(MIB_ATM_VC_TBL);
	for(i=0;i<vcEntryNum; i++)
	{
		if(!mib_chain_get(MIB_ATM_VC_TBL, i, (void*)&vcEntry)||!vcEntry.enableIpQos)
			continue;

		if (vcEntry.cmode != ADSL_BR1483)
			continue;

		ifGetName(vcEntry.ifIndex, devname2, sizeof(devname2));

		if (!enable) {
			va_cmd(TC, 5, 1, "qdisc", (char *)ARG_DEL, "dev", devname2, "root");
			continue;
		}

		snprintf(tc_cmd, 100, "tc qdisc add dev %s root handle 1: prio bands 4 priomap %s", devname2, "3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3");
		TRACE(STA_SCRIPT,"%s\n",tc_cmd);
		system(tc_cmd);
	}
	return 0;
}

static int setupQdisc(int enable)
{
	unsigned char policy;

	QOS_SETUP_PRINT_FUNCTION;
	mib_get(MIB_QOS_POLICY, (void*)&policy);

	if (policy == PLY_PRIO)
		setup_prio_queue(enable);
	else
		setup_wrr_queue(enable);
	return 0;
}

static int setupQRule()
{
	unsigned char policy;

	QOS_SETUP_PRINT_FUNCTION;
	mib_get(MIB_QOS_POLICY, (void*)&policy);
	setup_qos_rules(policy);
	return 0;
}

int enableIMQ(int enable)
{
	MIB_CE_ATM_VC_T vcEntry;
	int i, entryNum;
	char ifname[IFNAMSIZ];

	QOS_SETUP_PRINT_FUNCTION;

	if (!enable) {
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-F", "IMQ_CHAIN");
		va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-D", "POSTROUTING", "-j", "IMQ_CHAIN");
		va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-X", "IMQ_CHAIN");
#ifdef CONFIG_IPV6
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-F", "IMQ_CHAIN");
		va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-D", "POSTROUTING", "-j", "IMQ_CHAIN");
		va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-X", "IMQ_CHAIN");
#endif
		va_cmd(IFCONFIG, 2, 1, "imq0", "down");
		return 0;
	}

	va_cmd(IFCONFIG, 3, 1, "imq0", "txqueuelen", "100");
	va_cmd(IFCONFIG, 2, 1, "imq0", "up");

	va_cmd(IPTABLES, 4, 1, "-t", "mangle", "-N", "IMQ_CHAIN");
	va_cmd(IPTABLES, 6, 1, "-t", "mangle", "-A", "POSTROUTING", "-j", "IMQ_CHAIN");
#ifdef CONFIG_IPV6
	va_cmd(IP6TABLES, 4, 1, "-t", "mangle", "-N", "IMQ_CHAIN");
	va_cmd(IP6TABLES, 6, 1, "-t", "mangle", "-A", "POSTROUTING", "-j", "IMQ_CHAIN");
#endif

	entryNum = mib_chain_total(MIB_ATM_VC_TBL);

	for(i=0; i<entryNum; i++)
	{
		if(!mib_chain_get(MIB_ATM_VC_TBL, i, (void*)&vcEntry))
			continue;

		if (vcEntry.cmode == ADSL_BR1483)
			continue;

		ifGetName(vcEntry.ifIndex, ifname, sizeof(ifname));
		va_cmd(IPTABLES, 10, 1, "-t", "mangle", "-A", "IMQ_CHAIN",
			"-o", ifname, "-j", "IMQ", "--todev", "0");
#ifdef CONFIG_IPV6
		va_cmd(IP6TABLES, 10, 1, "-t", "mangle", "-A", "IMQ_CHAIN",
			"-o", ifname, "-j", "IMQ", "--todev", "0");
#endif
	}

	return 0;
}

/*
 * Make sure we have 4 QoS Queues.
 */
static void checkQosQueue()
{
	MIB_CE_IP_QOS_QUEUE_T qEntry;
	int qEntryNum, i;

	if((qEntryNum=mib_chain_total(MIB_IP_QOS_QUEUE_TBL)) >= 4)
		return;

	// Flush table
	for (i=0; i<qEntryNum; i++) {
		mib_chain_delete(MIB_IP_QOS_QUEUE_TBL, 0);
	}

	// Add MAX_QOS_QUEUE_NUM of default Qos Queues
	for (i=0; i<4; i++) {
		qEntry.enable = 0;
		qEntry.weight = 10*(4-i);
		qEntry.QueueInstNum = i+1;
		mib_chain_add(MIB_IP_QOS_QUEUE_TBL, &qEntry);
	}
	mib_update(CURRENT_SETTING, CONFIG_MIB_ALL);
}


int setupIPQ(void)
{
	unsigned int qosEnable;
	unsigned int qosRuleNum, carRuleNum;
	unsigned char totalBandWidthEn;

	QOS_SETUP_PRINT_FUNCTION;
	checkQosQueue();
	UpdateIpFastpathStatus(); // need to disable upstream IPQoS for IPQoS

	qosEnable = getQosEnable();
	qosRuleNum = getQosRuleNum();
	mib_get(MIB_TOTAL_BANDWIDTH_LIMIT_EN, (void *)&totalBandWidthEn);
	carRuleNum = mib_chain_total(MIB_IP_QOS_TC_TBL);

	printf("[%s %d]qosEnable=%d, totalBandWidthEn=%d, qosRuleNum=%d, carRuleNum=%d\n", __func__, __LINE__, qosEnable, totalBandWidthEn, qosRuleNum, carRuleNum);

	// hwnat qos
	hwnat_qos_queue_setup();
	hwnat_wanif_rule();
	if (qosEnable && qosRuleNum) { // ip qos
		setupQosRuleChain(1);
#ifdef CONFIG_RTK_RG_INIT
		FlushRTK_RG_QoS_Rules();
		RTK_RG_QoS_Queue_Set();
#endif
		setupQdisc(1);
		setupQRule();
		enableIMQ(1);
	}
	else if (totalBandWidthEn || carRuleNum) { // traffic shapping
		setupCarChain(1);
		setupCarQdisc(1);
		setupCarRule();
	}

	//setupUserIPQoSRule(1);
}

int stopIPQ(void)
{
	setupQosRuleChain(0);
	setupQdisc(0);
	enableIMQ(0);

	setupCarChain(0);
	setupCarQdisc(0);
	// hwnat qos
	hwnat_qos_queue_stop();
	hwnat_qos_bandwidth_setup(0);
	return 0;
}

void take_qos_effect_v3(void)
{
	stopIPQ();
	setupIPQ();
}

