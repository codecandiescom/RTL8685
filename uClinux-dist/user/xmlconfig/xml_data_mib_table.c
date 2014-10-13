#include <stdio.h>
#include "xml_config_define.h"
#include "xml_config.h"

MIB_T _config;
HW_MIB_T _hw_config;

MIB_Tp config = &_config;
HW_MIB_Tp hw_config = &_hw_config;

/* MIB HW SETTING TABLE	*/
XML_DIR_SINGLE("HW_MIB_TABLE", hw_config, root, 0);
XML_ENTRY_STRING2("SUPER_NAME", superName, hw_config,  hw_config->superName, MIB_SUPER_NAME);	//STRING_T
XML_ENTRY_STRING2("SUPER_PASSWORD", superPassword, hw_config, hw_config->superPassword, MIB_SUPER_PASSWORD);	//STRING_T
XML_ENTRY_BYTE6("ELAN_MAC_ADDR", elanMacAddr, hw_config, hw_config->elanMacAddr, MIB_ELAN_MAC_ADDR);	//BYTE6_T
XML_ENTRY_BYTE6("WLAN_MAC_ADDR", wlanMacAddr, hw_config, hw_config->wlanMacAddr, MIB_WLAN_MAC_ADDR);	//BYTE6_T
XML_ENTRY_PRIMITIVE2("WAN_PHY_PORT", wanPhyPort, hw_config, "%u", hw_config->wanPhyPort, MIB_WAN_PHY_PORT);	//INTEGER_T
//#if WLAN_SUPPORT
XML_ENTRY_PRIMITIVE2("HW_RF_TYPE", rfType, hw_config, "%hhu", hw_config->rfType, MIB_HW_RF_TYPE);	//BYTE_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_CCK_A", pwrlevelCCK_A, hw_config, hw_config->pwrlevelCCK_A, MIB_HW_TX_POWER_CCK_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_CCK_B", pwrlevelCCK_B, hw_config, hw_config->pwrlevelCCK_B, MIB_HW_TX_POWER_CCK_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_HT40_1S_A", pwrlevelHT40_1S_A, hw_config, hw_config->pwrlevelHT40_1S_A, MIB_HW_TX_POWER_HT40_1S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_HT40_1S_B", pwrlevelHT40_1S_B, hw_config, hw_config->pwrlevelHT40_1S_B, MIB_HW_TX_POWER_HT40_1S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_HT40_2S", pwrdiffHT40_2S, hw_config, hw_config->pwrdiffHT40_2S, MIB_HW_TX_POWER_HT40_2S);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_HT20", pwrdiffHT20, hw_config, hw_config->pwrdiffHT20, MIB_HW_TX_POWER_HT20);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_OFDM", pwrdiffOFDM, hw_config, hw_config->pwrdiffOFDM, MIB_HW_TX_POWER_DIFF_OFDM);	//BYTE_ARRAY_T
XML_ENTRY_PRIMITIVE2("HW_WLAN0_11N_TSSI1", TSSI1, hw_config, "%hhu", hw_config->TSSI1, MIB_HW_11N_TSSI1);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN0_11N_TSSI2", TSSI2, hw_config, "%hhu", hw_config->TSSI2, MIB_HW_11N_TSSI2);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN0_11N_THER", Ther, hw_config, "%hhu", hw_config->Ther, MIB_HW_11N_THER);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN0_11N_THER_2", Ther2, hw_config, "%hhu", hw_config->Ther2, MIB_HW_11N_THER2);   //BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN0_11N_PA_TYPE", PA_type, hw_config, "%hhu", hw_config->PA_type, MIB_HW_11N_PA_TYPE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN0_REG_DOMAIN", regDomain, hw_config, "%hhu", hw_config->regDomain, MIB_HW_REG_DOMAIN);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN0_11N_TRSWITCH", trswitch, hw_config, "%hhu", hw_config->trswitch, MIB_HW_11N_TRSWITCH);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN0_11N_TRSWPAPE_C9", trswpape_c9, hw_config, "%hhu", hw_config->trswpape_c9, MIB_HW_11N_TRSWPAPE_C9);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN0_11N_TRSWPAPE_CC", trswpape_cc, hw_config, "%hhu", hw_config->trswpape_cc, MIB_HW_11N_TRSWPAPE_CC);	//BYTE_T

#ifdef WLAN_DUALBAND_CONCURRENT
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_CCK_A", pwrlevelCCK_A_w1, hw_config, hw_config->pwrlevelCCK_A_w1, MIB_HW_WLAN1_TX_POWER_CCK_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_CCK_B", pwrlevelCCK_B_w1, hw_config, hw_config->pwrlevelCCK_B_w1, MIB_HW_WLAN1_TX_POWER_CCK_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_HT40_1S_A", pwrlevelHT40_1S_A_w1, hw_config, hw_config->pwrlevelHT40_1S_A_w1, MIB_HW_WLAN1_TX_POWER_HT40_1S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_HT40_1S_B", pwrlevelHT40_1S_B_w1, hw_config, hw_config->pwrlevelHT40_1S_B_w1, MIB_HW_WLAN1_TX_POWER_HT40_1S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_HT40_2S", pwrdiffHT40_2S_w1, hw_config, hw_config->pwrdiffHT40_2S_w1, MIB_HW_WLAN1_TX_POWER_HT40_2S);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_HT20", pwrdiffHT20_w1, hw_config, hw_config->pwrdiffHT20_w1, MIB_HW_WLAN1_TX_POWER_HT20);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_OFDM", pwrdiffOFDM_w1, hw_config, hw_config->pwrdiffOFDM_w1, MIB_HW_WLAN1_TX_POWER_DIFF_OFDM);	//BYTE_ARRAY_T
XML_ENTRY_PRIMITIVE2("HW_WLAN1_11N_TSSI1", TSSI1_w1, hw_config, "%hhu", hw_config->TSSI1_w1, MIB_HW_WLAN1_11N_TSSI1);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN1_11N_TSSI2", TSSI2_w1, hw_config, "%hhu", hw_config->TSSI2_w1, MIB_HW_WLAN1_11N_TSSI2);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN1_11N_THER", Ther_w1, hw_config, "%hhu", hw_config->Ther_w1, MIB_HW_WLAN1_11N_THER);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN1_11N_THER_2", Ther2_w1, hw_config, "%hhu", hw_config->Ther2_w1, MIB_HW_WLAN1_11N_THER2);       //BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN1_11N_PA_TYPE", PA_type_w1, hw_config, "%hhu", hw_config->PA_type_w1, MIB_HW_WLAN1_11N_PA_TYPE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN1_REG_DOMAIN", regDomain_w1, hw_config, "%hhu", hw_config->regDomain_w1, MIB_HW_WLAN1_REG_DOMAIN);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN1_11N_TRSWITCH", trswitch_w1, hw_config, "%hhu", hw_config->trswitch_w1, MIB_HW_WLAN1_11N_TRSWITCH);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN1_11N_TRSWPAPE_C9", trswpape_c9_w1, hw_config, "%hhu", hw_config->trswpape_c9_w1, MIB_HW_WLAN1_11N_TRSWPAPE_C9);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN1_11N_TRSWPAPE_CC", trswpape_cc_w1, hw_config, "%hhu", hw_config->trswpape_cc_w1, MIB_HW_WLAN1_11N_TRSWPAPE_CC);	//BYTE_T
#endif

XML_ENTRY_PRIMITIVE2("HW_ANT_DIVERSITY", antDiversity, hw_config, "%hhu", hw_config->antDiversity, MIB_HW_ANT_DIVERSITY);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_TX_ANT", txAnt, hw_config, "%hhu", hw_config->txAnt, MIB_HW_TX_ANT);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_CS_THRESHOLD", csThreshold, hw_config, "%hhu", hw_config->csThreshold, MIB_HW_CS_THRESHOLD);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_CCA_MODE", ccaMode, hw_config, "%hhu", hw_config->ccaMode, MIB_HW_CCA_MODE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_PHY_TYPE", phyType, hw_config, "%hhu", hw_config->phyType, MIB_HW_PHY_TYPE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN_LED_TYPE", ledType, hw_config, "%hhu", hw_config->ledType, MIB_HW_LED_TYPE);	//BYTE_T

#if defined(WLAN0_5G_SUPPORT) || defined(CONFIG_RTL_92D_SUPPORT)
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_5G_HT40_1S_A", pwrlevel5GHT40_1S_A, hw_config, hw_config->pwrlevel5GHT40_1S_A, MIB_HW_TX_POWER_5G_HT40_1S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_5G_HT40_1S_B", pwrlevel5GHT40_1S_B, hw_config, hw_config->pwrlevel5GHT40_1S_B, MIB_HW_TX_POWER_5G_HT40_1S_B);	//BYTE_ARRAY_T
#ifdef CONFIG_RTL_92D_SUPPORT
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_HT40_2S", pwrdiff5GHT40_2S, hw_config, hw_config->pwrdiff5GHT40_2S, MIB_HW_TX_POWER_DIFF_5G_HT40_2S);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_HT20", pwrdiff5GHT20, hw_config, hw_config->pwrdiff5GHT20, MIB_HW_TX_POWER_DIFF_5G_HT20);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_OFDM", pwrdiff5GOFDM, hw_config, hw_config->pwrdiff5GOFDM, MIB_HW_TX_POWER_DIFF_5G_OFDM);	//BYTE_ARRAY_T
#endif
#endif
#if defined(WLAN1_5G_SUPPORT) || defined(CONFIG_RTL_92D_SUPPORT)
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_5G_HT40_1S_A", pwrlevel5GHT40_1S_A, hw_config, hw_config->pwrlevel5GHT40_1S_A, MIB_HW_TX_POWER_5G_HT40_1S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_5G_HT40_1S_B", pwrlevel5GHT40_1S_B, hw_config, hw_config->pwrlevel5GHT40_1S_B, MIB_HW_TX_POWER_5G_HT40_1S_B);	//BYTE_ARRAY_T
#ifdef CONFIG_RTL_92D_SUPPORT
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_HT40_2S", pwrdiff5GHT40_2S, hw_config, hw_config->pwrdiff5GHT40_2S, MIB_HW_TX_POWER_DIFF_5G_HT40_2S);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_HT20", pwrdiff5GHT20, hw_config, hw_config->pwrdiff5GHT20, MIB_HW_TX_POWER_DIFF_5G_HT20);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_OFDM", pwrdiff5GOFDM, hw_config, hw_config->pwrdiff5GOFDM, MIB_HW_TX_POWER_DIFF_5G_OFDM);	//BYTE_ARRAY_T
#endif
#endif

#if defined(WLAN0_5G_SUPPORT)
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_20BW1S_OFDM1T_A", pwrdiff_20BW1S_OFDM1T_A, hw_config, hw_config->pwrdiff_20BW1S_OFDM1T_A, MIB_HW_TX_POWER_DIFF_20BW1S_OFDM1T_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_40BW2S_20BW2S_A", pwrdiff_40BW2S_20BW2S_A, hw_config, hw_config->pwrdiff_40BW2S_20BW2S_A, MIB_HW_TX_POWER_DIFF_40BW2S_20BW2S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_OFDM2T_CCK2T_A", pwrdiff_OFDM2T_CCK2T_A, hw_config, hw_config->pwrdiff_OFDM2T_CCK2T_A, MIB_HW_TX_POWER_DIFF_OFDM2T_CCK2T_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_40BW3S_20BW3S_A", pwrdiff_40BW3S_20BW3S_A, hw_config, hw_config->pwrdiff_40BW3S_20BW3S_A, MIB_HW_TX_POWER_DIFF_40BW3S_20BW3S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_OFDM3T_CCK3T_A", pwrdiff_4OFDM3T_CCK3T_A, hw_config, hw_config->pwrdiff_4OFDM3T_CCK3T_A, MIB_HW_TX_POWER_DIFF_OFDM3T_CCK3T_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_40BW4S_20BW4S_A", pwrdiff_40BW4S_20BW4S_A, hw_config, hw_config->pwrdiff_40BW4S_20BW4S_A, MIB_HW_TX_POWER_DIFF_40BW4S_20BW4S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_OFDM4T_CCK4T_A", pwrdiff_OFDM4T_CCK4T_A, hw_config, hw_config->pwrdiff_OFDM4T_CCK4T_A, MIB_HW_TX_POWER_DIFF_OFDM4T_CCK4T_A);	//BYTE_ARRAY_T

XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_20BW1S_OFDM1T_A", pwrdiff_5G_20BW1S_OFDM1T_A, hw_config, hw_config->pwrdiff_5G_20BW1S_OFDM1T_A, MIB_HW_TX_POWER_DIFF_5G_20BW1S_OFDM1T_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_40BW2S_20BW2S_A", pwrdiff_5G_40BW2S_20BW2S_A, hw_config, hw_config->pwrdiff_5G_40BW2S_20BW2S_A, MIB_HW_TX_POWER_DIFF_5G_40BW2S_20BW2S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_40BW3S_20BW3S_A", pwrdiff_5G_40BW3S_20BW3S_A, hw_config, hw_config->pwrdiff_5G_40BW3S_20BW3S_A, MIB_HW_TX_POWER_DIFF_5G_40BW3S_20BW3S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_40BW4S_20BW4S_A", pwrdiff_5G_40BW4S_20BW4S_A, hw_config, hw_config->pwrdiff_5G_40BW4S_20BW4S_A, MIB_HW_TX_POWER_DIFF_5G_40BW4S_20BW4S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_RSVD_OFDM4T_A", pwrdiff_5G_RSVD_OFDM4T_A, hw_config, hw_config->pwrdiff_5G_RSVD_OFDM4T_A, MIB_HW_TX_POWER_DIFF_5G_RSVD_OFDM4T_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_80BW1S_160BW1S_A", pwrdiff_5G_80BW1S_160BW1S_A, hw_config, hw_config->pwrdiff_5G_80BW1S_160BW1S_A, MIB_HW_TX_POWER_DIFF_5G_80BW1S_160BW1S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_80BW2S_160BW2S_A", pwrdiff_5G_80BW2S_160BW2S_A, hw_config, hw_config->pwrdiff_5G_80BW2S_160BW2S_A, MIB_HW_TX_POWER_DIFF_5G_80BW2S_160BW2S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_80BW3S_160BW3S_A", pwrdiff_5G_80BW3S_160BW3S_A, hw_config, hw_config->pwrdiff_5G_80BW3S_160BW3S_A, MIB_HW_TX_POWER_DIFF_5G_80BW3S_160BW3S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_80BW4S_160BW4S_A", pwrdiff_5G_80BW4S_160BW4S_A, hw_config, hw_config->pwrdiff_5G_80BW4S_160BW4S_A, MIB_HW_TX_POWER_DIFF_5G_80BW4S_160BW4S_A);	//BYTE_ARRAY_T

XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_20BW1S_OFDM1T_B", pwrdiff_20BW1S_OFDM1T_B, hw_config, hw_config->pwrdiff_20BW1S_OFDM1T_B, MIB_HW_TX_POWER_DIFF_20BW1S_OFDM1T_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_40BW2S_20BW2S_B", pwrdiff_40BW2S_20BW2S_B, hw_config, hw_config->pwrdiff_40BW2S_20BW2S_B, MIB_HW_TX_POWER_DIFF_40BW2S_20BW2S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_OFDM2T_CCK2T_B", pwrdiff_OFDM2T_CCK2T_B, hw_config, hw_config->pwrdiff_OFDM2T_CCK2T_B, MIB_HW_TX_POWER_DIFF_OFDM2T_CCK2T_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_40BW3S_20BW3S_B", pwrdiff_40BW3S_20BW3S_B, hw_config, hw_config->pwrdiff_40BW3S_20BW3S_B, MIB_HW_TX_POWER_DIFF_40BW3S_20BW3S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_OFDM3T_CCK3T_B", pwrdiff_OFDM3T_CCK3T_B, hw_config, hw_config->pwrdiff_OFDM3T_CCK3T_B, MIB_HW_TX_POWER_DIFF_OFDM3T_CCK3T_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_40BW4S_20BW4S_B", pwrdiff_40BW4S_20BW4S_B, hw_config, hw_config->pwrdiff_40BW4S_20BW4S_B, MIB_HW_TX_POWER_DIFF_40BW4S_20BW4S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_OFDM4T_CCK4T_B", pwrdiff_OFDM4T_CCK4T_B, hw_config, hw_config->pwrdiff_OFDM4T_CCK4T_B, MIB_HW_TX_POWER_DIFF_OFDM4T_CCK4T_B);	//BYTE_ARRAY_T

XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_20BW1S_OFDM1T_B", pwrdiff_5G_20BW1S_OFDM1T_B, hw_config, hw_config->pwrdiff_5G_20BW1S_OFDM1T_B, MIB_HW_TX_POWER_DIFF_5G_20BW1S_OFDM1T_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_40BW2S_20BW2S_B", pwrdiff_5G_40BW2S_20BW2S_B, hw_config, hw_config->pwrdiff_5G_40BW2S_20BW2S_B, MIB_HW_TX_POWER_DIFF_5G_40BW2S_20BW2S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_40BW3S_20BW3S_B", pwrdiff_5G_40BW3S_20BW3S_B, hw_config, hw_config->pwrdiff_5G_40BW3S_20BW3S_B, MIB_HW_TX_POWER_DIFF_5G_40BW3S_20BW3S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_40BW4S_20BW4S_B", pwrdiff_5G_40BW4S_20BW4S_B, hw_config, hw_config->pwrdiff_5G_40BW4S_20BW4S_B, MIB_HW_TX_POWER_DIFF_5G_40BW4S_20BW4S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_RSVD_OFDM4T_B", pwrdiff_5G_RSVD_OFDM4T_B, hw_config, hw_config->pwrdiff_5G_RSVD_OFDM4T_B, MIB_HW_TX_POWER_DIFF_5G_RSVD_OFDM4T_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_80BW1S_160BW1S_B", pwrdiff_5G_80BW1S_160BW1S_B, hw_config, hw_config->pwrdiff_5G_80BW1S_160BW1S_B, MIB_HW_TX_POWER_DIFF_5G_80BW1S_160BW1S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_80BW2S_160BW2S_B", pwrdiff_5G_80BW2S_160BW2S_B, hw_config, hw_config->pwrdiff_5G_80BW2S_160BW2S_B, MIB_HW_TX_POWER_DIFF_5G_80BW2S_160BW2S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_80BW3S_160BW3S_B", pwrdiff_5G_80BW3S_160BW3S_B, hw_config, hw_config->pwrdiff_5G_80BW3S_160BW3S_B, MIB_HW_TX_POWER_DIFF_5G_80BW3S_160BW3S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN0_TX_POWER_DIFF_5G_80BW4S_160BW4S_B", pwrdiff_5G_80BW4S_160BW4S_B, hw_config, hw_config->pwrdiff_5G_80BW4S_160BW4S_B, MIB_HW_TX_POWER_DIFF_5G_80BW4S_160BW4S_B);	//BYTE_ARRAY_T
#endif

#if defined(WLAN1_5G_SUPPORT)
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_20BW1S_OFDM1T_A", pwrdiff_20BW1S_OFDM1T_A, hw_config, hw_config->pwrdiff_20BW1S_OFDM1T_A, MIB_HW_TX_POWER_DIFF_20BW1S_OFDM1T_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_40BW2S_20BW2S_A", pwrdiff_40BW2S_20BW2S_A, hw_config, hw_config->pwrdiff_40BW2S_20BW2S_A, MIB_HW_TX_POWER_DIFF_40BW2S_20BW2S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_OFDM2T_CCK2T_A", pwrdiff_OFDM2T_CCK2T_A, hw_config, hw_config->pwrdiff_OFDM2T_CCK2T_A, MIB_HW_TX_POWER_DIFF_OFDM2T_CCK2T_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_40BW3S_20BW3S_A", pwrdiff_40BW3S_20BW3S_A, hw_config, hw_config->pwrdiff_40BW3S_20BW3S_A, MIB_HW_TX_POWER_DIFF_40BW3S_20BW3S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_OFDM3T_CCK3T_A", pwrdiff_4OFDM3T_CCK3T_A, hw_config, hw_config->pwrdiff_4OFDM3T_CCK3T_A, MIB_HW_TX_POWER_DIFF_OFDM3T_CCK3T_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_40BW4S_20BW4S_A", pwrdiff_40BW4S_20BW4S_A, hw_config, hw_config->pwrdiff_40BW4S_20BW4S_A, MIB_HW_TX_POWER_DIFF_40BW4S_20BW4S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_OFDM4T_CCK4T_A", pwrdiff_OFDM4T_CCK4T_A, hw_config, hw_config->pwrdiff_OFDM4T_CCK4T_A, MIB_HW_TX_POWER_DIFF_OFDM4T_CCK4T_A);	//BYTE_ARRAY_T

XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_20BW1S_OFDM1T_A", pwrdiff_5G_20BW1S_OFDM1T_A, hw_config, hw_config->pwrdiff_5G_20BW1S_OFDM1T_A, MIB_HW_TX_POWER_DIFF_5G_20BW1S_OFDM1T_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_40BW2S_20BW2S_A", pwrdiff_5G_40BW2S_20BW2S_A, hw_config, hw_config->pwrdiff_5G_40BW2S_20BW2S_A, MIB_HW_TX_POWER_DIFF_5G_40BW2S_20BW2S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_40BW3S_20BW3S_A", pwrdiff_5G_40BW3S_20BW3S_A, hw_config, hw_config->pwrdiff_5G_40BW3S_20BW3S_A, MIB_HW_TX_POWER_DIFF_5G_40BW3S_20BW3S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_40BW4S_20BW4S_A", pwrdiff_5G_40BW4S_20BW4S_A, hw_config, hw_config->pwrdiff_5G_40BW4S_20BW4S_A, MIB_HW_TX_POWER_DIFF_5G_40BW4S_20BW4S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_RSVD_OFDM4T_A", pwrdiff_5G_RSVD_OFDM4T_A, hw_config, hw_config->pwrdiff_5G_RSVD_OFDM4T_A, MIB_HW_TX_POWER_DIFF_5G_RSVD_OFDM4T_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_80BW1S_160BW1S_A", pwrdiff_5G_80BW1S_160BW1S_A, hw_config, hw_config->pwrdiff_5G_80BW1S_160BW1S_A, MIB_HW_TX_POWER_DIFF_5G_80BW1S_160BW1S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_80BW2S_160BW2S_A", pwrdiff_5G_80BW2S_160BW2S_A, hw_config, hw_config->pwrdiff_5G_80BW2S_160BW2S_A, MIB_HW_TX_POWER_DIFF_5G_80BW2S_160BW2S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_80BW3S_160BW3S_A", pwrdiff_5G_80BW3S_160BW3S_A, hw_config, hw_config->pwrdiff_5G_80BW3S_160BW3S_A, MIB_HW_TX_POWER_DIFF_5G_80BW3S_160BW3S_A);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_80BW4S_160BW4S_A", pwrdiff_5G_80BW4S_160BW4S_A, hw_config, hw_config->pwrdiff_5G_80BW4S_160BW4S_A, MIB_HW_TX_POWER_DIFF_5G_80BW4S_160BW4S_A);	//BYTE_ARRAY_T

XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_20BW1S_OFDM1T_B", pwrdiff_20BW1S_OFDM1T_B, hw_config, hw_config->pwrdiff_20BW1S_OFDM1T_B, MIB_HW_TX_POWER_DIFF_20BW1S_OFDM1T_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_40BW2S_20BW2S_B", pwrdiff_40BW2S_20BW2S_B, hw_config, hw_config->pwrdiff_40BW2S_20BW2S_B, MIB_HW_TX_POWER_DIFF_40BW2S_20BW2S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_OFDM2T_CCK2T_B", pwrdiff_OFDM2T_CCK2T_B, hw_config, hw_config->pwrdiff_OFDM2T_CCK2T_B, MIB_HW_TX_POWER_DIFF_OFDM2T_CCK2T_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_40BW3S_20BW3S_B", pwrdiff_40BW3S_20BW3S_B, hw_config, hw_config->pwrdiff_40BW3S_20BW3S_B, MIB_HW_TX_POWER_DIFF_40BW3S_20BW3S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_OFDM3T_CCK3T_B", pwrdiff_OFDM3T_CCK3T_B, hw_config, hw_config->pwrdiff_OFDM3T_CCK3T_B, MIB_HW_TX_POWER_DIFF_OFDM3T_CCK3T_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_40BW4S_20BW4S_B", pwrdiff_40BW4S_20BW4S_B, hw_config, hw_config->pwrdiff_40BW4S_20BW4S_B, MIB_HW_TX_POWER_DIFF_40BW4S_20BW4S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_OFDM4T_CCK4T_B", pwrdiff_OFDM4T_CCK4T_B, hw_config, hw_config->pwrdiff_OFDM4T_CCK4T_B, MIB_HW_TX_POWER_DIFF_OFDM4T_CCK4T_B);	//BYTE_ARRAY_T

XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_20BW1S_OFDM1T_B", pwrdiff_5G_20BW1S_OFDM1T_B, hw_config, hw_config->pwrdiff_5G_20BW1S_OFDM1T_B, MIB_HW_TX_POWER_DIFF_5G_20BW1S_OFDM1T_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_40BW2S_20BW2S_B", pwrdiff_5G_40BW2S_20BW2S_B, hw_config, hw_config->pwrdiff_5G_40BW2S_20BW2S_B, MIB_HW_TX_POWER_DIFF_5G_40BW2S_20BW2S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_40BW3S_20BW3S_B", pwrdiff_5G_40BW3S_20BW3S_B, hw_config, hw_config->pwrdiff_5G_40BW3S_20BW3S_B, MIB_HW_TX_POWER_DIFF_5G_40BW3S_20BW3S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_40BW4S_20BW4S_B", pwrdiff_5G_40BW4S_20BW4S_B, hw_config, hw_config->pwrdiff_5G_40BW4S_20BW4S_B, MIB_HW_TX_POWER_DIFF_5G_40BW4S_20BW4S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_RSVD_OFDM4T_B", pwrdiff_5G_RSVD_OFDM4T_B, hw_config, hw_config->pwrdiff_5G_RSVD_OFDM4T_B, MIB_HW_TX_POWER_DIFF_5G_RSVD_OFDM4T_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_80BW1S_160BW1S_B", pwrdiff_5G_80BW1S_160BW1S_B, hw_config, hw_config->pwrdiff_5G_80BW1S_160BW1S_B, MIB_HW_TX_POWER_DIFF_5G_80BW1S_160BW1S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_80BW2S_160BW2S_B", pwrdiff_5G_80BW2S_160BW2S_B, hw_config, hw_config->pwrdiff_5G_80BW2S_160BW2S_B, MIB_HW_TX_POWER_DIFF_5G_80BW2S_160BW2S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_80BW3S_160BW3S_B", pwrdiff_5G_80BW3S_160BW3S_B, hw_config, hw_config->pwrdiff_5G_80BW3S_160BW3S_B, MIB_HW_TX_POWER_DIFF_5G_80BW3S_160BW3S_B);	//BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("HW_WLAN1_TX_POWER_DIFF_5G_80BW4S_160BW4S_B", pwrdiff_5G_80BW4S_160BW4S_B, hw_config, hw_config->pwrdiff_5G_80BW4S_160BW4S_B, MIB_HW_TX_POWER_DIFF_5G_80BW4S_160BW4S_B);	//BYTE_ARRAY_T
#endif

XML_ENTRY_PRIMITIVE2("BYTE", byte_test, hw_config, "%hhu", hw_config->byte_test, MIB_BYTE_TEST);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WORD", word_test, hw_config, "%hu", hw_config->word_test, MIB_WORD_TEST);	//WORD_T
XML_ENTRY_PRIMITIVE2("DWORD", dword_test, hw_config, "%u", hw_config->dword_test, MIB_DWORD_TEST);	//DWORD_T
XML_ENTRY_PRIMITIVE2("INT1", int_test1, hw_config, "%d", hw_config->int_test1, MIB_INTERGER_TEST1);	//INTEGER_T
XML_ENTRY_PRIMITIVE2("INT2", int_test2, hw_config, "%d", hw_config->int_test2, MIB_INTERGER_TEST2);	//INTEGER_T
XML_ENTRY_PRIMITIVE2("WIFI_SUPPORT", wifi_support, hw_config, "%hhu", hw_config->wifi_support, MIB_WIFI_SUPPORT);	//BYTE_T
XML_ENTRY_STRING2("HW_SERIAL_NO", serialNumber, hw_config, hw_config->serialNumber, MIB_HW_SERIAL_NUMBER);	//STRING_T
XML_ENTRY_BYTE_ARRAY("HW_FON_KEYWORD", fon_keyword, hw_config, hw_config->fon_keyword, MIB_HW_FON_KEYWORD); //BYTE_ARRAY_T

XML_ENTRY_PRIMITIVE2("HW_WLAN0_11N_XCAP", rf_xCap, hw_config, "%hhu", hw_config->rf_xCap, MIB_HW_RF_XCAP);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN0_11N_XCAP_2", rf_xCap2, hw_config, "%hhu", hw_config->rf_xCap2, MIB_HW_RF_XCAP2);      //BYTE_T
#ifdef WLAN_DUALBAND_CONCURRENT
XML_ENTRY_PRIMITIVE2("HW_WLAN1_11N_XCAP", rf_xCap_w1, hw_config, "%hhu", hw_config->rf_xCap_w1, MIB_HW_WLAN1_RF_XCAP);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HW_WLAN1_11N_XCAP_2", rf_xCap2_w1, hw_config, "%hhu", hw_config->rf_xCap2_w1, MIB_HW_WLAN1_RF_XCAP2);  //BYTE_T
#endif

/* MIB HW SETTING TABLE	END*/

//MIB TABLE
XML_DIR_SINGLE("MIB_TABLE", config_setting, root, 0);
XML_ENTRY_PRIMITIVE2("WAN_MODE", wanmode, config_setting, "%hhu", config->wanmode, MIB_WAN_MODE);	//BYTE_T
XML_ENTRY_ADDR("LAN_IP_ADDR", ipAddr, config_setting, config->ipAddr, MIB_ADSL_LAN_IP);	//IA_T
XML_ENTRY_ADDR("LAN_SUBNET", subnetMask, config_setting, config->subnetMask, MIB_ADSL_LAN_SUBNET);	//IA_T
XML_ENTRY_PRIMITIVE2("LAN_ENABLE_IP2", enable_ip2, config_setting, "%hhu", config->enable_ip2, MIB_ADSL_LAN_ENABLE_IP2);	//BYTE_T
XML_ENTRY_ADDR("LAN_IP_ADDR2", ipAddr2, config_setting, config->ipAddr2, MIB_ADSL_LAN_IP2);	//IA_T
XML_ENTRY_ADDR("LAN_SUBNET2", subnetMask2, config_setting, config->subnetMask2, MIB_ADSL_LAN_SUBNET2);	//IA_T
#ifdef CONFIG_USER_DHCP_SERVER
XML_ENTRY_PRIMITIVE2("LAN_DHCP", dhcp, config_setting, "%hhu", config->dhcp, MIB_ADSL_LAN_DHCP);	//BYTE_T
XML_ENTRY_PRIMITIVE2("LAN_DHCP_POOLUSE", dhcp_pooluse, config_setting, "%hhu", config->dhcp_pooluse, MIB_ADSL_LAN_DHCP_POOLUSE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("LAN_DHCP_START", dhcpClientStart, config_setting, "%hhu", config->dhcpClientStart, MIB_ADSL_LAN_CLIENT_START);	//BYTE_T
XML_ENTRY_PRIMITIVE2("LAN_DHCP_END", dhcpClientEnd, config_setting, "%hhu", config->dhcpClientEnd, MIB_ADSL_LAN_CLIENT_END);	//BYTE_T
XML_ENTRY_ADDR("LAN_DHCP_POOL_START", ipDhcpStart, config_setting, config->ipDhcpStart, MIB_DHCP_POOL_START);	//IA_T
XML_ENTRY_ADDR("LAN_DHCP_POOL_END", ipDhcpEnd, config_setting, config->ipDhcpEnd, MIB_DHCP_POOL_END);	//IA_T
XML_ENTRY_PRIMITIVE2("LAN_DHCP_DNS_OPT", dhcps_dns_opt, config_setting, "%hhu", config->dhcps_dns_opt, MIB_DHCP_DNS_OPTION);	//BYTE_T
XML_ENTRY_ADDR("DHCPS_DNS1", dhcps_dns1, config_setting, config->dhcps_dns1, MIB_DHCPS_DNS1);	//IA_T
XML_ENTRY_ADDR("DHCPS_DNS2", dhcps_dns2, config_setting, config->dhcps_dns2, MIB_DHCPS_DNS2);	//IA_T
XML_ENTRY_ADDR("DHCPS_DNS3", dhcps_dns3, config_setting, config->dhcps_dns3, MIB_DHCPS_DNS3);	//IA_T
XML_ENTRY_PRIMITIVE2("LAN_DHCP_LEASE", dhcpLTime, config_setting, "%u", config->dhcpLTime, MIB_ADSL_LAN_DHCP_LEASE);	//INTEGER_T
XML_ENTRY_STRING2("LAN_DHCP_DOMAIN", dhcpDomain, config_setting, config->dhcpDomain, MIB_ADSL_LAN_DHCP_DOMAIN);	//STRING_T
#endif
XML_ENTRY_PRIMITIVE2("LAN_RIP", rip, config_setting, "%hhu", config->rip, MIB_ADSL_LAN_RIP);	//BYTE_T
XML_ENTRY_PRIMITIVE2("LAN_AUTOSEARCH", lanAutoSearch, config_setting, "%hhu", config->lanAutoSearch, MIB_ADSL_LAN_AUTOSEARCH);	//BYTE_T
#ifdef DEFAULT_GATEWAY_V2
XML_ENTRY_ADDR("DGW_IP", defaultGateway, config_setting, config->defaultGateway, MIB_ADSL_WAN_DGW_IP);	//IA_T
XML_ENTRY_PRIMITIVE2("DGW_ITF", dgwItf, config_setting, "%u", config->dgwItf, MIB_ADSL_WAN_DGW_ITF);	//INTEGER_T
#endif	//DEFAULT_GATEWAY_V2
XML_ENTRY_PRIMITIVE2("DNS_MODE", dnsMode, config_setting, "%hhu", config->dnsMode, MIB_ADSL_WAN_DNS_MODE);	//BYTE_T
XML_ENTRY_ADDR("DNS1", dns1, config_setting, config->dns1, MIB_ADSL_WAN_DNS1);	//IA_T
XML_ENTRY_ADDR("DNS2", dns2, config_setting, config->dns2, MIB_ADSL_WAN_DNS2);	//IA_T
XML_ENTRY_ADDR("DNS3", dns3, config_setting, config->dns3, MIB_ADSL_WAN_DNS3);	//IA_T
#ifdef CONFIG_USER_DHCP_SERVER
XML_ENTRY_ADDR("DHCPS", dhcps, config_setting, config->dhcps, MIB_ADSL_WAN_DHCPS);	//IA_T
XML_ENTRY_PRIMITIVE2("DHCP_MODE", dhcpMode, config_setting, "%hhu", config->dhcpMode, MIB_DHCP_MODE);	//BYTE_T
#endif
XML_ENTRY_PRIMITIVE2("ADSL_MODE", adslMode, config_setting, "%hu", config->adslMode, MIB_ADSL_MODE);	//WORD_T
XML_ENTRY_PRIMITIVE2("ADSL_OLR", adslOlr, config_setting, "%hhu", config->adslOlr, MIB_ADSL_OLR);	//BYTE_T
#ifdef FIELD_TRY_SAFE_MODE
XML_ENTRY_PRIMITIVE2("ADSL_FIELDTRYSAFEMODE", adslFtMode, config_setting, "%hhu", config->adslFtMode, MIB_ADSL_FIELDTRYSAFEMODE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("ADSL_FIELDTRYTESTPSDTIMES", adslFtTestPSDTimes, config_setting, "%u", config->adslFtTestPSDTimes, MIB_ADSL_FIELDTRYTESTPSDTIMES);	//INTEGER_T
XML_ENTRY_PRIMITIVE2("ADSL_FIELDTRYCTRLIN", adslFtCtrlIn, config_setting, "%u", config->adslFtCtrlIn, MIB_ADSL_FIELDTRYCTRLIN);	//INTEGER_T
#endif	//FIELD_TRY_SAFE_MODE
#ifdef CONFIG_USER_ROUTED_ROUTED
XML_ENTRY_PRIMITIVE2("RIP_ENABLE", ripEnabled, config_setting, "%hhu", config->ripEnabled, MIB_RIP_ENABLE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("RIP_VERSION", ripVer, config_setting, "%hhu", config->ripVer, MIB_RIP_VERSION);	//BYTE_T
#endif	//CONFIG_USER_ROUTED_ROUTED
#ifdef CONFIG_USER_ZEBRA_OSPFD_OSPFD
XML_ENTRY_PRIMITIVE2("OSPF_ENABLE", ospfEnabled, config_setting, "%hhu", config->ospfEnabled, MIB_OSPF_ENABLE);	//BYTE_T
#endif	//CONFIG_USER_ZEBRA_OSPFD_OSPFD
#ifdef CONFIG_IGMP_FORBID
XML_ENTRY_PRIMITIVE2("IGMP_FORBID_ENABLE", igmpforbidEnable, config_setting, "%hhu", config->igmpforbidEnable, MIB_IGMP_FORBID_ENABLE);	//BYTE_T
#endif	//CONFIG_IGMP_FORBID
XML_ENTRY_PRIMITIVE2("IPF_OUT_ACTION", ipfOutAction, config_setting, "%hhu", config->ipfOutAction, MIB_IPF_OUT_ACTION);	//BYTE_T
XML_ENTRY_PRIMITIVE2("IPF_IN_ACTION", ipfInAction, config_setting, "%hhu", config->ipfInAction, MIB_IPF_IN_ACTION);	//BYTE_T
XML_ENTRY_PRIMITIVE2("MACF_OUT_ACTION", macfOutAction, config_setting, "%hhu", config->macfOutAction, MIB_MACF_OUT_ACTION);	//BYTE_T
XML_ENTRY_PRIMITIVE2("MACF_IN_ACTION", macfInAction, config_setting, "%hhu", config->macfInAction, MIB_MACF_IN_ACTION);	//BYTE_T
XML_ENTRY_PRIMITIVE2("PORT_FW_ENABLE", portFwEnabled, config_setting, "%hhu", config->portFwEnabled, MIB_PORT_FW_ENABLE);	//BYTE_T
#ifdef NATIP_FORWARDING
XML_ENTRY_PRIMITIVE2("IP_FW_ENABLE", ipFwEnabled, config_setting, "%hhu", config->ipFwEnabled, MIB_IP_FW_ENABLE);	//BYTE_T
#endif	//NATIP_FORWARDING
XML_ENTRY_PRIMITIVE2("DMZ_ENABLE", dmzEnabled, config_setting, "%hhu", config->dmzEnabled, MIB_DMZ_ENABLE);	//BYTE_T
XML_ENTRY_ADDR("DMZ_IP", dmzHost, config_setting, config->dmzHost, MIB_DMZ_IP);	//IA_T
XML_ENTRY_STRING2("USER_NAME", userName, config_setting, config->userName, MIB_USER_NAME);	//STRING_T
XML_ENTRY_STRING2("USER_PASSWORD", userPassword, config_setting, config->userPassword, MIB_USER_PASSWORD);	//STRING_T

XML_ENTRY_PRIMITIVE2("DEVICE_TYPE", deviceType, config_setting, "%hhu", config->deviceType, MIB_DEVICE_TYPE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("INIT_LINE", initLine, config_setting, "%hhu", config->initLine, MIB_INIT_LINE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("INIT_SCRIPT", initScript, config_setting, "%hhu", config->initScript, MIB_INIT_SCRIPT);	//BYTE_T

#if defined(CONFIG_USER_SNMPD_SNMPD_V2CTRAP) || defined(_CWMP_MIB_)
XML_ENTRY_STRING2("SNMP_SYS_DESCR", snmpSysDescr, config_setting, config->snmpSysDescr, MIB_SNMP_SYS_DESCR);	//STRING_T
#endif //defined(CONFIG_USER_SNMPD_SNMPD_V2CTRAP) || defined(_CWMP_MIB_)
#ifdef CONFIG_USER_SNMPD_SNMPD_V2CTRAP
XML_ENTRY_STRING2("SNMP_SYS_OID", snmpSysObjectID, config_setting, config->snmpSysObjectID, MIB_SNMP_SYS_OID);	//STRING_T
XML_ENTRY_STRING2("SNMP_SYS_CONTACT", snmpSysContact, config_setting, config->snmpSysContact, MIB_SNMP_SYS_CONTACT);	//STRING_T
XML_ENTRY_STRING2("SNMP_SYS_LOCATION", snmpSysLocation, config_setting, config->snmpSysLocation, MIB_SNMP_SYS_LOCATION);	//STRING_T
XML_ENTRY_ADDR("SNMP_TRAP_IP", snmpTrapIpAddr, config_setting, config->snmpTrapIpAddr, MIB_SNMP_TRAP_IP);	//IA_T
XML_ENTRY_STRING2("SNMP_COMM_RO", snmpCommunityRO, config_setting, config->snmpCommunityRO, MIB_SNMP_COMM_RO);	//STRING_T
XML_ENTRY_STRING2("SNMP_COMM_RW", snmpCommunityRW, config_setting, config->snmpCommunityRW, MIB_SNMP_COMM_RW);	//STRING_T
#endif	//CONFIG_USER_SNMPD_SNMPD_V2CTRAP
XML_ENTRY_STRING2("SNMP_SYS_NAME", snmpSysName, config_setting, config->snmpSysName, MIB_SNMP_SYS_NAME);	//STRING_T
XML_ENTRY_PRIMITIVE2("VC_AUTOSEARCH", atmVcAutoSearch, config_setting, "%hhu", config->atmVcAutoSearch, MIB_ATM_VC_AUTOSEARCH);	//BYTE_T
XML_ENTRY_PRIMITIVE2("BR_AGEING_TIME", brctlAgeingTime, config_setting, "%hu", config->brctlAgeingTime, MIB_BRCTL_AGEINGTIME);	//WORD_T
XML_ENTRY_PRIMITIVE2("BR_STP_ENABLED", brctlStp, config_setting, "%hhu", config->brctlStp, MIB_BRCTL_STP);	//BYTE_T
XML_ENTRY_PRIMITIVE2("MP_MODE", mpMode, config_setting, "%hhu", config->mpMode, MIB_MPMODE);	//BYTE_T

#ifdef IP_QOS
XML_ENTRY_PRIMITIVE2("QOS_DEFAULT_QUEUE", qosDefaultQueue, config_setting, "%u", config->qosDefaultQueue, MIB_QOS_DEFAULT_QUEUE);	//INTEGER_T
XML_ENTRY_PRIMITIVE2("QOS_DOMAIN", qosDomain, config_setting, "%hhu", config->qosDomain, MIB_QOS_DOMAIN);	//BYTE_T
#endif	//IP_QOS
#ifdef QOS_DIFFSERV
XML_ENTRY_PRIMITIVE2("QOS_DIFFSERV", qosDiffServ, config_setting, "%hhu", config->qosDiffServ, MIB_QOS_DIFFSERV);	//BYTE_T
XML_ENTRY_PRIMITIVE2("DIFFSERV_PHBCLASS", phbClass, config_setting, "%hhu", config->phbClass, MIB_DIFFSERV_PHBCLASS);	//BYTE_T
#endif	//QOS_DIFFSERV
#ifdef CONFIG_USER_IP_QOS
XML_ENTRY_PRIMITIVE2("QOS_UPRATE", qosUprate, config_setting, "%u", config->qosUprate, MIB_QOS_UPRATE);	//INTEGER_T
XML_ENTRY_PRIMITIVE2("QOS_POLICY", qosPolicy, config_setting, "%hhu", config->qosPolicy, MIB_QOS_POLICY);	//BYTE_T
XML_ENTRY_PRIMITIVE2("TOTAL_BANDWIDTH", TotalBandWidth, config_setting, "%u", config->TotalBandWidth, MIB_TOTAL_BANDWIDTH);	//WORD_T
XML_ENTRY_PRIMITIVE2("TOTAL_BANDWIDTH_LIMIT", TotalBandWidthEn, config_setting, "%hhu", config->TotalBandWidthEn, MIB_TOTAL_BANDWIDTH_LIMIT_EN);	//BYTE_T
XML_ENTRY_PRIMITIVE2("QOS_MODE", qosmode, config_setting, "%hhu", config->qosmode, MIB_QOS_MODE);	//BYTE_T
#endif	//NEW_IP_QOS_SUPPORT
#ifdef CONFIG_USER_IGMPPROXY
XML_ENTRY_PRIMITIVE2("IGMP_PROXY", igmpProxy, config_setting, "%hhu", config->igmpProxy, MIB_IGMP_PROXY);	//BYTE_T
XML_ENTRY_PRIMITIVE2("IGMP_PROXY_ITF", igmpProxyItf, config_setting, "%u", config->igmpProxyItf, MIB_IGMP_PROXY_ITF);	//INTEGER_T
#endif	//CONFIG_USER_IGMPPROXY
#ifdef CONFIG_USER_PPTP_CLIENT_PPTP
XML_ENTRY_PRIMITIVE2("PPTP_ENABLE", pptpenable, config_setting, "%u", config->pptpenable, MIB_PPTP_ENABLE); //INTEGER_T
#endif //end of CONFIG_USER_PPTP_CLIENT_PPTP
#ifdef CONFIG_USER_L2TPD_L2TPD
XML_ENTRY_PRIMITIVE2("L2TP_ENABLE", l2tpenable, config_setting, "%u", config->l2tpenable, MIB_L2TP_ENABLE); //INTEGER_T
#endif //endof CONFIG_USER_L2TPD_L2TPD
#ifdef CONFIG_NET_IPIP
XML_ENTRY_PRIMITIVE2("PPTP_ENABLE", ipipenable, config_setting, "%u", config->ipipenable, MIB_IPIP_ENABLE); //INTEGER_T
#endif //end of CONFIG_NET_IPIP

#ifdef IP_PASSTHROUGH
XML_ENTRY_PRIMITIVE2("IPPT_ITF", ipptItf, config_setting, "%u", config->ipptItf, MIB_IPPT_ITF);	//INTEGER_T
XML_ENTRY_PRIMITIVE2("IPPT_LEASE", ipptLTime, config_setting, "%u", config->ipptLTime, MIB_IPPT_LEASE);	//INTEGER_T
XML_ENTRY_PRIMITIVE2("IPPT_LANACC", ipptLanacc, config_setting, "%hhu", config->ipptLanacc, MIB_IPPT_LANACC);	//BYTE_T
#endif	//IP_PASSTHROUGH
XML_ENTRY_PRIMITIVE2("SPC_ENABLED", spcEnable, config_setting, "%hhu", config->spcEnable, MIB_SPC_ENABLE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("SPC_IPTYPE", spcIPType, config_setting, "%hhu", config->spcIPType, MIB_SPC_IPTYPE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("ACL_CAPABILITY", aclcapability, config_setting, "%hhu", config->aclcapability, MIB_ACL_CAPABILITY);	//BYTE_T
#ifdef NAT_CONN_LIMIT
XML_ENTRY_PRIMITIVE2("CONN_LIMIT", connlimit, config_setting, "%hhu", config->connlimit, MIB_NAT_CONN_LIMIT);	//BYTE_T
#endif	//NAT_CONN_LIMIT
#ifdef URL_BLOCKING_SUPPORT
XML_ENTRY_PRIMITIVE2("URL_CAPABILITY", urlcapability, config_setting, "%hhu", config->urlcapability, MIB_URL_CAPABILITY);	//BYTE_T
#endif	//URL_BLOCKING_SUPPORT
#ifdef TIME_ZONE
XML_ENTRY_PRIMITIVE2("NTP_ENABLED", ntpEnabled, config_setting, "%hhu", config->ntpEnabled, MIB_NTP_ENABLED);	//BYTE_T
XML_ENTRY_PRIMITIVE2("NTP_TIMEZONE_DB_INDEX", ntpTimeZoneDBIndex, config_setting, "%u", config->ntpTimeZoneDBIndex, MIB_NTP_TIMEZONE_DB_INDEX);	//DWORD_T
XML_ENTRY_PRIMITIVE2("DST_ENABLED", dstEnabled, config_setting, "%hhu", config->dstEnabled, MIB_DST_ENABLED);	//BYTE_T
XML_ENTRY_PRIMITIVE2("NTP_SERVER_ID", ntpServerId, config_setting, "%hhu", config->ntpServerId, MIB_NTP_SERVER_ID);	//BYTE_T
XML_ENTRY_STRING2("NTP_SERVER_HOST1", ntpServerHost1, config_setting, config->ntpServerHost1, MIB_NTP_SERVER_HOST1);	//STRING_T
XML_ENTRY_STRING2("NTP_SERVER_HOST2", ntpServerHost2, config_setting, config->ntpServerHost2, MIB_NTP_SERVER_HOST2);	//STRING_T
#endif	// defined(TIME_ZONE)
XML_ENTRY_PRIMITIVE2("UPNP", upnp, config_setting, "%hhu", config->upnp, MIB_UPNP_DAEMON);	//BYTE_T
XML_ENTRY_PRIMITIVE2("UPNP_EXT_ITF", upnpExtItf, config_setting, "%u", config->upnpExtItf, MIB_UPNP_EXT_ITF);	//INTEGER_T
#ifdef DOMAIN_BLOCKING_SUPPORT
XML_ENTRY_PRIMITIVE2("DOMAINBLK_CAPABILITY", domainblkcap, config_setting, "%hhu", config->domainblkcap, MIB_DOMAINBLK_CAPABILITY);	//BYTE_T
#endif	//DOMAIN_BLOCKING_SUPPORT

#ifdef CONFIG_USER_MINIDLNA
XML_ENTRY_PRIMITIVE2("dms_ENABLE", dmsenable, config_setting, "%u", config->dmsenable, MIB_DMS_ENABLE);	//INTEGER_T
#endif

#ifdef CONFIG_USER_IP_QOS_3
XML_ENTRY_PRIMITIVE2("ENABLE_QOS", qosEnableQos, config_setting, "%hhu", config->qosEnableQos, MIB_QOS_ENABLE_QOS);	//BYTE_T
#endif

#ifdef CONFIG_USER_FON
XML_ENTRY_PRIMITIVE2("FON_ONOFF", fon_onoffline, config_setting, "%hhu", config->fon_onoffline, MIB_FON_ONOFF); //BYTE_T
#endif

#ifdef WLAN_SUPPORT
XML_ENTRY_STRING2("SSID", ssid, config_setting, config->ssid, MIB_WLAN_SSID);	//STRING_T
XML_ENTRY_PRIMITIVE2("AUTO_CHANNEL", auto_channel, config_setting, "%hhu", config->auto_channel, MIB_WLAN_AUTO_CHAN_ENABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("CHANNEL", channel, config_setting, "%hhu", config->channel, MIB_WLAN_CHAN_NUM);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WEP", wep, config_setting, "%hhu", config->wep, MIB_WLAN_WEP);	//BYTE_T
XML_ENTRY_BYTE5("WEP64_KEY1", wep64Key1, config_setting, config->wep64Key1, MIB_WLAN_WEP64_KEY1);	//BYTE5_T
XML_ENTRY_BYTE5("WEP64_KEY2", wep64Key2, config_setting, config->wep64Key2, MIB_WLAN_WEP64_KEY2);	//BYTE5_T
XML_ENTRY_BYTE5("WEP64_KEY3", wep64Key3, config_setting, config->wep64Key3, MIB_WLAN_WEP64_KEY3);	//BYTE5_T
XML_ENTRY_BYTE5("WEP64_KEY4", wep64Key4, config_setting, config->wep64Key4, MIB_WLAN_WEP64_KEY4);	//BYTE5_T
XML_ENTRY_BYTE13("WEP128_KEY1", wep128Key1, config_setting, config->wep128Key1, MIB_WLAN_WEP128_KEY1);	//BYTE13_T
XML_ENTRY_BYTE13("WEP128_KEY2", wep128Key2, config_setting, config->wep128Key2, MIB_WLAN_WEP128_KEY2);	//BYTE13_T
XML_ENTRY_BYTE13("WEP128_KEY3", wep128Key3, config_setting, config->wep128Key3, MIB_WLAN_WEP128_KEY3);	//BYTE13_T
XML_ENTRY_BYTE13("WEP128_KEY4", wep128Key4, config_setting, config->wep128Key4, MIB_WLAN_WEP128_KEY4);	//BYTE13_T
XML_ENTRY_PRIMITIVE2("WEP_DEFAULT_KEY", wepDefaultKey, config_setting, "%hhu", config->wepDefaultKey, MIB_WLAN_WEP_DEFAULT_KEY);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WEP_KEY_TYPE", wepKeyType, config_setting, "%hhu",config->wepKeyType, MIB_WLAN_WEP_KEY_TYPE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("FRAG_THRESHOLD", fragThreshold, config_setting, "%hu", config->fragThreshold, MIB_WLAN_FRAG_THRESHOLD);	//WORD_T
XML_ENTRY_PRIMITIVE2("SUPPORTED_RATES", supportedRates, config_setting, "%hu", config->supportedRates, MIB_WLAN_SUPPORTED_RATE);	//WORD_T
XML_ENTRY_PRIMITIVE2("BEACON_INTERVAL", beaconInterval, config_setting, "%hu", config->beaconInterval, MIB_WLAN_BEACON_INTERVAL);	//WORD_T
XML_ENTRY_PRIMITIVE2("PREAMBLE_TYPE", preambleType, config_setting, "%hhu", config->preambleType, MIB_WLAN_PREAMBLE_TYPE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("BASIC_RATES", basicRates, config_setting, "%hu", config->basicRates, MIB_WLAN_BASIC_RATE);	//WORD_T
XML_ENTRY_PRIMITIVE2("RTS_THRESHOLD", rtsThreshold, config_setting, "%hu", config->rtsThreshold, MIB_WLAN_RTS_THRESHOLD);	//WORD_T
XML_ENTRY_PRIMITIVE2("AUTH_TYPE", authType, config_setting, "%hhu", config->authType, MIB_WLAN_AUTH_TYPE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("HIDDEN_SSID", hiddenSSID, config_setting, "%hhu", config->hiddenSSID, MIB_WLAN_HIDDEN_SSID);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_DISABLED", wlanDisabled, config_setting, "%hhu", config->wlanDisabled, MIB_WLAN_DISABLED);	//BYTE_T
// Added by Mason Yu for TxPower
//modified by xl_yue
XML_ENTRY_PRIMITIVE2("WLAN_RFPOWER_SCALE", txPower, config_setting, "%hhu", config->txPower, MIB_TX_POWER);	//BYTE_T
XML_ENTRY_PRIMITIVE2("INACTIVITY_TIME", inactivityTime, config_setting, "%ld", config->inactivityTime, MIB_WLAN_INACTIVITY_TIME);	//DWORD_T
XML_ENTRY_PRIMITIVE2("RATE_ADAPTIVE_ENABLED", rateAdaptiveEnabled, config_setting, "%hhu", config->rateAdaptiveEnabled, MIB_WLAN_RATE_ADAPTIVE_ENABLED);	//BYTE_T
XML_ENTRY_PRIMITIVE2("DTIM_PERIOD", dtimPeriod, config_setting, "%hhu", config->dtimPeriod, MIB_WLAN_DTIM_PERIOD);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_MODE", wlanMode, config_setting, "%hhu", config->wlanMode, MIB_WLAN_MODE);	//BYTE_T
XML_ENTRY_PRIMITIVE2("NETWORK_TYPE", networkType, config_setting, "%hhu", config->networkType, MIB_WLAN_NETWORK_TYPE);	//BYTE_T
#ifdef WLAN_WDS
XML_ENTRY_PRIMITIVE2("WLAN_WDS_ENABLED", wdsEnabled, config_setting, "%hhu", config->wdsEnabled, MIB_WLAN_WDS_ENABLED);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_WDS_NUM", wdsNum, config_setting, "%hhu", config->wdsNum, MIB_WLAN_WDS_NUM);	//BYTE_T
//XML_ENTRY_PRIMITIVE_ARRAY2("WLAN_WDS", wdsArray, config_setting, "%hhu", config->wdsArray);	//WDS_ARRAY_T (it is a dir)
XML_ENTRY_PRIMITIVE2("WLAN_WDS_ENCRYPT", wdsEncrypt, config_setting, "%hhu", config->wdsEncrypt, MIB_WLAN_WDS_ENCRYPT);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_WDS_WEP_FORMAT", wdsWepFormat, config_setting, "%hhu", config->wdsWepFormat, MIB_WLAN_WDS_WEP_FORMAT); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_WDS_WEP_KEY", wdsWepKey, config_setting, "%hhu", config->wdsWepKey, MIB_WLAN_WDS_WEP_KEY); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_WDS_PSK_FORMAT", wdsPskFormat, config_setting, "%hhu", config->wdsPskFormat, MIB_WLAN_WDS_PSK_FORMAT); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_WDS_PSK", wdsPsk, config_setting, "%hhu", config->wdsPsk, MIB_WLAN_WDS_PSK); //BYTE_T
#if 0
XML_ENTRY_BYTE5("WDS_WEP64_KEY1", wdsWep64Key1, config_setting, config->wdsWep64Key1, MIB_WLAN_WDS_WEP64_KEY1);	//BYTE5_T
XML_ENTRY_BYTE5("WDS_WEP64_KEY2", wdsWep64Key2, config_setting, config->wdsWep64Key2, MIB_WLAN_WDS_WEP64_KEY2);	//BYTE5_T
XML_ENTRY_BYTE5("WDS_WEP64_KEY3", wdsWep64Key3, config_setting, config->wdsWep64Key3, MIB_WLAN_WDS_WEP64_KEY3);	//BYTE5_T
XML_ENTRY_BYTE5("WDS_WEP64_KEY4", wdsWep64Key4, config_setting, config->wdsWep64Key4, MIB_WLAN_WDS_WEP64_KEY4);	//BYTE5_T
XML_ENTRY_BYTE13("WDS_WEP128_KEY1", wdsWep128Key1, config_setting, config->wdsWep128Key1, MIB_WLAN_WDS_WEP128_KEY1);	//BYTE13_T
XML_ENTRY_BYTE13("WDS_WEP128_KEY2", wdsWep128Key2, config_setting, config->wdsWep128Key2, MIB_WLAN_WDS_WEP128_KEY2);	//BYTE13_T
XML_ENTRY_BYTE13("WDS_WEP128_KEY3", wdsWep128Key3, config_setting, config->wdsWep128Key3, MIB_WLAN_WDS_WEP128_KEY3);	//BYTE13_T
XML_ENTRY_BYTE13("WDS_WEP128_KEY4", wdsWep128Key4, config_setting, config->wdsWep128Key4, MIB_WLAN_WDS_WEP128_KEY4);	//BYTE13_T
XML_ENTRY_PRIMITIVE2("WDS_WEP_DEFAULT_KEY", wdsWepDefaultKey, config_setting, "%hhu", config->wdsWepDefaultKey, MIB_WLAN_WDS_WEP_DEFAULT_KEY);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WDS_WEP_KEY_TYPE", wdsWepKeyType, config_setting, "%hhu", config->wdsWepKeyType, MIB_WLAN_WDS_WEP_KEY_TYPE);	//BYTE_T
#endif
#endif	//WLAN_WDS

#ifdef WLAN_WPA
XML_ENTRY_PRIMITIVE2("WLAN_ENCRYPT", encrypt, config_setting, "%hhu", config->encrypt, MIB_WLAN_ENCRYPT);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_ENABLE_SUPP_NONWPA", enableSuppNonWpa, config_setting, "%hhu", config->enableSuppNonWpa, MIB_WLAN_ENABLE_SUPP_NONWPA);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_SUPP_NONWPA", suppNonWpa, config_setting, "%hhu", config->suppNonWpa, MIB_WLAN_SUPP_NONWPA);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_WPA_AUTH", wpaAuth, config_setting, "%hhu", config->wpaAuth, MIB_WLAN_WPA_AUTH);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_WPA_CIPHER_SUITE", wpaCipher, config_setting, "%hhu", config->wpaCipher, MIB_WLAN_WPA_CIPHER_SUITE);	//BYTE_T
XML_ENTRY_STRING2("WLAN_WPA_PSK", wpaPSK, config_setting, config->wpaPSK, MIB_WLAN_WPA_PSK);	//STRING_T
XML_ENTRY_PRIMITIVE2("WLAN_WPA_GROUP_REKEY_TIME", wpaGroupRekeyTime, config_setting, "%ld", config->wpaGroupRekeyTime, MIB_WLAN_WPA_GROUP_REKEY_TIME);	//DWORD_T
XML_ENTRY_PRIMITIVE2("MAC_AUTH_ENABLED", macAuthEnabled, config_setting, "%hhu", config->macAuthEnabled, MIB_WLAN_ENABLE_MAC_AUTH);	//BYTE_T
#ifdef WLAN_1x
XML_ENTRY_ADDR("RS_IP", rsIpAddr, config_setting, config->rsIpAddr, MIB_WLAN_RS_IP);	//IA_T
XML_ENTRY_PRIMITIVE2("RS_PORT", rsPort, config_setting, "%hu", config->rsPort, MIB_WLAN_RS_PORT);	//WORD_T
XML_ENTRY_STRING2("RS_PASSWORD", rsPassword, config_setting, config->rsPassword, MIB_WLAN_RS_PASSWORD);	//STRING_T
XML_ENTRY_PRIMITIVE2("RS_MAXRETRY", rsMaxRetry, config_setting, "%hhu", config->rsMaxRetry, MIB_WLAN_RS_RETRY);	//BYTE_T
XML_ENTRY_PRIMITIVE2("RS_INTERVAL_TIME", rsIntervalTime, config_setting, "%hu", config->rsIntervalTime, MIB_WLAN_RS_INTERVAL_TIME);	//WORD_T
XML_ENTRY_PRIMITIVE2("ACCOUNT_RS_ENABLED", accountRsEnabled, config_setting, "%hhu", config->accountRsEnabled, MIB_WLAN_ACCOUNT_RS_ENABLED);	//BYTE_T
XML_ENTRY_ADDR("ACCOUNT_RS_IP", accountRsIpAddr, config_setting, config->accountRsIpAddr, MIB_WLAN_ACCOUNT_RS_IP);	//IA_T
XML_ENTRY_PRIMITIVE2("ACCOUNT_RS_PORT", accountRsPort, config_setting, "%hu", config->accountRsPort, MIB_WLAN_ACCOUNT_RS_PORT);	//WORD_T
XML_ENTRY_STRING2("ACCOUNT_RS_PASSWORD", accountRsPassword, config_setting, config->accountRsPassword, MIB_WLAN_ACCOUNT_RS_PASSWORD);	//STRING_T
XML_ENTRY_PRIMITIVE2("ACCOUNT_RS_UPDATE_ENABLED", accountRsUpdateEnabled, config_setting, "%hhu", config->accountRsUpdateEnabled, MIB_WLAN_ACCOUNT_UPDATE_ENABLED);	//BYTE_T
XML_ENTRY_PRIMITIVE2("ACCOUNT_RS_UPDATE_DELAY", accountRsUpdateDelay, config_setting, "%hu", config->accountRsUpdateDelay, MIB_WLAN_ACCOUNT_UPDATE_DELAY);	//WORD_T
XML_ENTRY_PRIMITIVE2("ACCOUNT_RS_MAXRETRY", accountRsMaxRetry, config_setting, "%hhu", config->accountRsMaxRetry, MIB_WLAN_ACCOUNT_RS_RETRY);	//BYTE_T
XML_ENTRY_PRIMITIVE2("ACCOUNT_RS_INTERVAL_TIME", accountRsIntervalTime, config_setting, "%hu", config->accountRsIntervalTime, MIB_WLAN_ACCOUNT_RS_INTERVAL_TIME);	//WORD_T
XML_ENTRY_PRIMITIVE2("WLAN_ENABLE_1X", enable1X, config_setting, "%hhu", config->enable1X, MIB_WLAN_ENABLE_1X);	//BYTE_T
#endif	//WLAN_1x
XML_ENTRY_PRIMITIVE2("WLAN_PSK_FORMAT", wpaPSKFormat, config_setting, "%hhu", config->wpaPSKFormat, MIB_WLAN_WPA_PSK_FORMAT);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WPA2_CIPHER_SUITE", wpa2Cipher, config_setting, "%hhu", config->wpa2Cipher, MIB_WLAN_WPA2_CIPHER_SUITE);	//BYTE_T
#ifdef WLAN_11W
XML_ENTRY_PRIMITIVE2("WLAN_DOTIEEE80211W", dotIEEE80211W, config_setting, "%hhu", config->dotIEEE80211W, MIB_WLAN_DOTIEEE80211W);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_SHA256", sha256, config_setting, "%hhu", config->sha256, MIB_WLAN_SHA256);	//BYTE_T
#endif //WLAN_11W
#endif	//WLAN_WPA

#ifdef WLAN_ACL
XML_ENTRY_PRIMITIVE2("WLAN_MACAC_ENABLED", acEnabled, config_setting, "%hhu", config->acEnabled, MIB_WLAN_AC_ENABLED);	//BYTE_T
#endif	//WLAN_ACL

XML_ENTRY_PRIMITIVE2("WLAN_BLOCK_RELAY", blockRelay, config_setting, "%hhu", config->blockRelay, MIB_WLAN_BLOCK_RELAY);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_BLOCK_ETH2WIR", BlockEth2Wir, config_setting, "%hhu", config->BlockEth2Wir, MIB_WLAN_BLOCK_ETH2WIR);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_ITF_GROUP", itfGroup, config_setting, "%hhu", config->itfGroup, MIB_WLAN_ITF_GROUP);	//BYTE_T

#ifdef WLAN_MBSSID
XML_ENTRY_PRIMITIVE2("WLAN_BLOCK_MBSSID", BlockMbssid, config_setting, "%hhu", config->BlockMbssid, MIB_WLAN_BLOCK_MBSSID);	//BYTE_T
#endif	//WLAN_MBSSID

XML_ENTRY_PRIMITIVE2("WLAN_BAND", wlanBand, config_setting, "%hhu", config->wlanBand, MIB_WLAN_BAND);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_FIX_RATE", fixedTxRate, config_setting, "%u", config->fixedTxRate, MIB_WLAN_FIX_RATE);	//DWORD_T
#ifdef CONFIG_USB_RTL8187SU_SOFTAP
XML_ENTRY_PRIMITIVE2("WLAN_MLCSTRATE", mlcstRate, config_setting, "%hu", config->mlcstRate, MIB_WLAN_MLCSTRATE);   //WORD_T
#endif	//CONFIG_USB_RTL8187SU_SOFTAP

#ifdef WLAN_WEB_REDIRECT  //jiunming,web_redirect
XML_ENTRY_STRING2("WLAN_WEB_REDIR_URL", WlanWebRedirURL, config_setting, config->WlanWebRedirURL, MIB_WLAN_WEB_REDIR_URL);	//STRING_T
#endif	//WLAN_WEB_REDIRECT
#ifdef WLAN_QoS
XML_ENTRY_PRIMITIVE2("WLAN_QoS", wlanqos, config_setting, "%hhu", config->wlanqos, MIB_WLAN_QoS); //BYTE_T
#endif	//WLAN_QoS
XML_ENTRY_PRIMITIVE2("WLAN_BEACON_ADVERTISEMENT", wlanBcnAdvtisement, config_setting, "%hhu", config->wlanBcnAdvtisement, MIB_WLAN_BEACON_ADVERTISEMENT); //BYTE_T
XML_ENTRY_PRIMITIVE2("WIFI_TEST", wifitest, config_setting, "%hhu", config->wifitest, MIB_WIFI_TEST); //BYTE_T
XML_ENTRY_PRIMITIVE2("WIFI_REGDOMAIN_DEMO", wifiregdemo, config_setting, "%hhu", config->wifiregdemo, MIB_WIFI_REGDOMAIN_DEMO); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_PROTECTON", wlanProtectionDisabled, config_setting, "%hhu", config->wlanProtectionDisabled, MIB_WLAN_PROTECTION_DISABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_AGGREGATION", wlanAggregation, config_setting, "%hhu", config->wlanAggregation, MIB_WLAN_AGGREGATION); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_SHORTGI", wlanShortGIEnabled, config_setting, "%hhu", config->wlanShortGIEnabled, MIB_WLAN_SHORTGI_ENABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_CONTROLBAND", wlanContrlBand, config_setting, "%hhu", config->wlanContrlBand, MIB_WLAN_CONTROL_BAND); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_CHANNELWIDTH", wlanChannelWidth, config_setting, "%hhu", config->wlanChannelWidth, MIB_WLAN_CHANNEL_WIDTH); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_11NCOEXIST", wlan11nCoexist, config_setting, "%hhu", config->wlan11nCoexist, MIB_WLAN_11N_COEXIST); //BYTE_T
#ifdef CONFIG_RTL_WAPI_SUPPORT
XML_ENTRY_STRING2("WAPI_PSK", wapiPsk, config_setting, config->wapiPsk, MIB_WLAN_WAPI_PSK);	//STRING_T
XML_ENTRY_PRIMITIVE2("WAPI_PSKLEN", wapiPskLen, config_setting, "%hhu", config->wapiPskLen, MIB_WLAN_WAPI_PSKLEN); //BYTE_T
XML_ENTRY_PRIMITIVE2("WAPI_PSKFORMAT", wapiPskFormat, config_setting, "%hhu", config->wapiPskFormat, MIB_WLAN_WAPI_PSK_FORMAT); //BYTE_T
XML_ENTRY_PRIMITIVE2("WAPI_AUTH", wapiAuth, config_setting, "%hhu", config->wapiAuth, MIB_WLAN_WAPI_AUTH); //BYTE_T
XML_ENTRY_ADDR("WAPI_ASIPADDR", wapiAsIpAddr, config_setting, config->wapiAsIpAddr, MIB_WLAN_WAPI_ASIPADDR); //IA_T
XML_ENTRY_STRING2("WAPI_SEARCHINFO", wapiSearchCertInfo, config_setting, config->wapiSearchCertInfo, MIB_WLAN_WAPI_SEARCH_CERTINFO); //STRING_T
XML_ENTRY_PRIMITIVE2("WAPI_SEARCHINDEX", wapiSearchIndex, config_setting, "%hhu", config->wapiSearchIndex, MIB_WLAN_WAPI_SEARCH_CERTINDEX); //BYTE_T
XML_ENTRY_PRIMITIVE2("WAPI_MCASTREKEY", wapiMcastkey, config_setting, "%hhu", config->wapiPskLen, MIB_WLAN_WAPI_MCAST_REKEYTYPE); //BYTE_T
XML_ENTRY_PRIMITIVE2("WAPI_MCAST_TIME", wapiMcastRekeyTime, config_setting, "%ld", config->wapiMcastRekeyTime, MIB_WLAN_WAPI_MCAST_TIME); //DWORD_T
XML_ENTRY_PRIMITIVE2("WAPI_MCAST_PACKETS", wapiMcastRekeyPackets, config_setting, "%ld", config->wapiMcastRekeyPackets, MIB_WLAN_WAPI_MCAST_PACKETS); //DWORD_T
XML_ENTRY_PRIMITIVE2("WAPI_UCASTREKEY", wapiUcastkey, config_setting, "%hhu", config->wapiUcastkey, MIB_WLAN_WAPI_UCAST_REKETTYPE); //BYTE_T
XML_ENTRY_PRIMITIVE2("WAPI_UCAST_TIME", wapiUcastRekeyTime, config_setting, "%ld", config->wapiUcastRekeyTime, MIB_WLAN_WAPI_UCAST_TIME); //DWORD_T
XML_ENTRY_PRIMITIVE2("WAPI_UCAST_PACKETS", wapiUcastRekeyPackets, config_setting, "%ld", config->wapiUcastRekeyPackets, MIB_WLAN_WAPI_UCAST_PACKETS); //DWORD_T
XML_ENTRY_PRIMITIVE2("WAPI_CA_INIT", wapiCAInit, config_setting, "%hhu", config->wapiCAInit, MIB_WLAN_WAPI_CA_INIT); //BYTE_T
#endif	//CONFIG_RTL_WAPI_SUPPORT

#ifdef WLAN_UNIVERSAL_REPEATER
XML_ENTRY_PRIMITIVE2("REPEATER_ENABLED1", repeaterEnabled1, config_setting, "%hhu", config->repeaterEnabled1, MIB_REPEATER_ENABLED1); //BYTE_T
XML_ENTRY_STRING2("REPEATER_SSID1", repeaterSSID1, config_setting, config->repeaterSSID1, MIB_REPEATER_SSID1); //STRING_T
XML_ENTRY_PRIMITIVE2("REPEATER_ENABLED2", repeaterEnabled2, config_setting, "%hhu", config->repeaterEnabled2, MIB_REPEATER_ENABLED2); //BYTE_T
XML_ENTRY_STRING2("REPEATER_SSID2", repeaterSSID2, config_setting, config->repeaterSSID2, MIB_REPEATER_SSID2); //STRING_T
#endif	//WLAN_UNIVERSAL_REPEATER

XML_ENTRY_PRIMITIVE2("WLAN_PHY_BAND_SELECT", phyBandSelect, config_setting, "%hhu", config->phyBandSelect, MIB_WLAN_PHY_BAND_SELECT); //BYTE_T
#if defined(CONFIG_RTL_92D_SUPPORT)
XML_ENTRY_PRIMITIVE2("WLAN_BAND2G5G_SELECT", wlanBand2G5GSelect, config_setting, "%hhu", config->wlanBand2G5GSelect, MIB_WLAN_BAND2G5G_SELECT); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_MAC_PHY_MODE", macPhyMode, config_setting, "%hhu", config->macPhyMode, MIB_WLAN_MAC_PHY_MODE); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_BAND2G5G_SINGLE_SELECT", wlanBand2G5GSelect_single, config_setting, "%hhu", config->wlanBand2G5GSelect_single, MIB_WLAN_BAND2G5G_SINGLE_SELECT); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_MAC_PHY_MODE", wlan1_macPhyMode, config_setting, "%hhu", config->wlan1_macPhyMode, MIB_WLAN1_MAC_PHY_MODE); //BYTE_T
#endif
#if defined(CONFIG_RTL_92D_SUPPORT) || defined(WLAN1_5G_SUPPORT) || defined(WLAN_DUALBAND_CONCURRENT)
XML_ENTRY_PRIMITIVE2("WLAN1_PHY_BAND_SELECT", wlan1_phyBandSelect, config_setting, "%hhu", config->wlan1_phyBandSelect, MIB_WLAN1_PHY_BAND_SELECT); //BYTE_T
#endif

#if defined(CONFIG_RTL_92D_SUPPORT) || defined(WLAN_DUALBAND_CONCURRENT)
XML_ENTRY_STRING2("WLAN1_SSID", wlan1_ssid, config_setting, config->wlan1_ssid, MIB_WLAN1_SSID); //STRING_T
XML_ENTRY_PRIMITIVE2("WLAN1_AUTO_CHANNEL", wlan1_auto_channel, config_setting, "%hhu", config->wlan1_auto_channel, MIB_WLAN1_AUTO_CHAN_ENABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_CHANNEL", wlan1_channel, config_setting, "%hhu", config->wlan1_channel, MIB_WLAN1_CHAN_NUM); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WEP", wlan1_wep, config_setting, "%hhu", config->wlan1_wep, MIB_WLAN1_WEP); //BYTE_T
XML_ENTRY_BYTE5("WLAN1_WEP64_KEY1", wlan1_wep64Key1, config_setting, config->wlan1_wep64Key1, MIB_WLAN1_WEP64_KEY1);	//BYTE5_T
XML_ENTRY_BYTE5("WLAN1_WEP64_KEY2", wlan1_wep64Key2, config_setting, config->wlan1_wep64Key2, MIB_WLAN1_WEP64_KEY2);	//BYTE5_T
XML_ENTRY_BYTE5("WLAN1_WEP64_KEY3", wlan1_wep64Key3, config_setting, config->wlan1_wep64Key3, MIB_WLAN1_WEP64_KEY3);	//BYTE5_T
XML_ENTRY_BYTE5("WLAN1_WEP64_KEY4", wlan1_wep64Key4, config_setting, config->wlan1_wep64Key4, MIB_WLAN1_WEP64_KEY4);	//BYTE5_T
XML_ENTRY_BYTE13("WLAN1_WEP128_KEY1", wlan1_wep128Key1, config_setting, config->wlan1_wep128Key1, MIB_WLAN1_WEP128_KEY1);	//BYTE13_T
XML_ENTRY_BYTE13("WLAN1_WEP128_KEY2", wlan1_wep128Key2, config_setting, config->wlan1_wep128Key2, MIB_WLAN1_WEP128_KEY2);	//BYTE13_T
XML_ENTRY_BYTE13("WLAN1_WEP128_KEY3", wlan1_wep128Key3, config_setting, config->wlan1_wep128Key3, MIB_WLAN1_WEP128_KEY3);	//BYTE13_T
XML_ENTRY_BYTE13("WLAN1_WEP128_KEY4", wlan1_wep128Key4, config_setting, config->wlan1_wep128Key4, MIB_WLAN1_WEP128_KEY4);	//BYTE13_T
XML_ENTRY_PRIMITIVE2("WLAN1_WEP_DEFAULT_KEY", wlan1_wepDefaultKey, config_setting, "%hhu", config->wlan1_wepDefaultKey, MIB_WLAN1_WEP_DEFAULT_KEY); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WEP_KEY_TYPE", wlan1_wepKeyType, config_setting, "%hhu", config->wlan1_wepKeyType, MIB_WLAN1_WEP_KEY_TYPE); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_FRAG_THRESHOLD", wlan1_fragThreshold, config_setting, "%hu", config->wlan1_fragThreshold, MIB_WLAN1_FRAG_THRESHOLD); //WORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_RTS_THRESHOLD", wlan1_rtsThreshold, config_setting, "%hu", config->wlan1_rtsThreshold, MIB_WLAN1_RTS_THRESHOLD); //WORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_SUPPORTED_RATES", wlan1_supportedRates, config_setting, "%hu", config->wlan1_supportedRates, MIB_WLAN1_SUPPORTED_RATE); //WORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_BASIC_RATES", wlan1_basicRates, config_setting, "%hu", config->wlan1_basicRates, MIB_WLAN1_BASIC_RATE); //WORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_BEACON_INTERVAL", wlan1_beaconInterval, config_setting, "%hu", config->wlan1_beaconInterval, MIB_WLAN1_BEACON_INTERVAL); //WORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_PREAMBLE_TYPE", wlan1_preambleType, config_setting, "%hhu", config->wlan1_preambleType, MIB_WLAN1_PREAMBLE_TYPE); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_AUTH_TYPE", wlan1_authType, config_setting, "%hhu", config->wlan1_authType, MIB_WLAN1_AUTH_TYPE); //BYTE_T
#ifdef WLAN_ACL
XML_ENTRY_PRIMITIVE2("WLAN1_MACAC_ENABLED", wlan1_acEnabled, config_setting, "%hhu", config->wlan1_acEnabled, MIB_WLAN1_AC_ENABLED); //BYTE_T
#endif	//WLAN_ACL
XML_ENTRY_PRIMITIVE2("WLAN1_HIDDEN_SSID", wlan1_hiddenSSID, config_setting, "%hhu", config->wlan1_hiddenSSID, MIB_WLAN1_HIDDEN_SSID); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_DISABLED", wlan1_wlanDisabled, config_setting, "%hhu", config->wlan1_wlanDisabled, MIB_WLAN1_DISABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_RFPOWER_SCALE", wlan1_txPower, config_setting, "%hhu", config->wlan1_txPower, MIB_WLAN1_TX_POWER); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_INACTIVITY_TIME", wlan1_inactivityTime, config_setting, "%ld", config->wlan1_inactivityTime, MIB_WLAN1_INACTIVITY_TIME); //DWORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_RATE_ADAPTIVE_ENABLED", wlan1_rateAdaptiveEnabled, config_setting, "%hhu", config->wlan1_rateAdaptiveEnabled, MIB_WLAN1_RATE_ADAPTIVE_ENABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_DTIM_PERIOD", wlan1_dtimPeriod, config_setting, "%hhu", config->wlan1_dtimPeriod, MIB_WLAN1_DTIM_PERIOD); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WLAN_MODE", wlan1_wlanMode, config_setting, "%hhu", config->wlan1_wlanMode, MIB_WLAN1_MODE); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_NETWORK_TYPE", wlan1_networkType, config_setting, "%hhu", config->wlan1_networkType, MIB_WLAN1_NETWORK_TYPE); //BYTE_T

#ifdef WLAN_WPA
XML_ENTRY_PRIMITIVE2("WLAN1_ENCRYPT", wlan1_encrypt, config_setting, "%hhu", config->wlan1_encrypt, MIB_WLAN1_ENCRYPT); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_ENABLE_SUPP_NONWPA", wlan1_enableSuppNonWpa, config_setting, "%hhu", config->wlan1_enableSuppNonWpa, MIB_WLAN1_ENABLE_SUPP_NONWPA); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_SUPP_NONWPA", wlan1_suppNonWpa, config_setting, "%hhu", config->wlan1_suppNonWpa, MIB_WLAN1_SUPP_NONWPA); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WPA_AUTH", wlan1_wpaAuth, config_setting, "%hhu", config->wlan1_wpaAuth, MIB_WLAN1_WPA_AUTH); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WPA_CIPHER_SUITE", wlan1_wpaCipher, config_setting, "%hhu", config->wlan1_wpaCipher, MIB_WLAN1_WPA_CIPHER_SUITE); //BYTE_T
XML_ENTRY_STRING2("WLAN1_WPA_PSK", wlan1_wpaPSK, config_setting, config->wlan1_wpaPSK, MIB_WLAN1_WPA_PSK); //STRING_T
XML_ENTRY_PRIMITIVE2("WLAN1_WPA_GROUP_REKEY_TIME", wlan1_wpaGroupRekeyTime, config_setting, "%ld", config->wlan1_wpaGroupRekeyTime, MIB_WLAN1_WPA_GROUP_REKEY_TIME); //DWORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_MAC_AUTH_ENABLED", wlan1_macAuthEnabled, config_setting, "%hhu", config->wlan1_macAuthEnabled, MIB_WLAN1_ENABLE_MAC_AUTH); //BYTE_T
#ifdef WLAN_1x
XML_ENTRY_ADDR("WLAN1_RS_IP", wlan1_rsIpAddr, config_setting, config->wlan1_rsIpAddr, MIB_WLAN1_RS_IP); //IA_T
XML_ENTRY_PRIMITIVE2("WLAN1_RS_PORT", wlan1_rsPort, config_setting, "%hu", config->wlan1_rsPort, MIB_WLAN1_RS_PORT); //WORD_T
XML_ENTRY_STRING2("WLAN1_RS_PASSWORD", wlan1_rsPassword, config_setting, config->wlan1_rsPassword, MIB_WLAN1_RS_PASSWORD); //STRING_T
XML_ENTRY_PRIMITIVE2("WLAN1_RS_MAXRETRY", wlan1_rsMaxRetry, config_setting, "%hhu", config->wlan1_rsMaxRetry, MIB_WLAN1_RS_RETRY); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_RS_INTERVAL_TIME", wlan1_rsIntervalTime, config_setting, "%hu", config->wlan1_rsIntervalTime, MIB_WLAN1_RS_INTERVAL_TIME); //WORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_ACCOUNT_RS_ENABLED", wlan1_accountRsEnabled, config_setting, "%hhu", config->wlan1_accountRsEnabled, MIB_WLAN1_ACCOUNT_RS_ENABLED); //BYTE_T
XML_ENTRY_ADDR("WLAN1_ACCOUNT_RS_IP", wlan1_accountRsIpAddr, config_setting, config->wlan1_accountRsIpAddr, MIB_WLAN1_ACCOUNT_RS_IP); //IA_T
XML_ENTRY_PRIMITIVE2("WLAN1_ACCOUNT_RS_PORT", wlan1_accountRsPort, config_setting, "%hu", config->wlan1_accountRsPort, MIB_WLAN1_ACCOUNT_RS_PORT); //WORD_T
XML_ENTRY_STRING2("WLAN1_ACCOUNT_RS_PASSWORD", wlan1_accountRsPassword, config_setting, config->wlan1_accountRsPassword, MIB_WLAN1_ACCOUNT_RS_PASSWORD); //STRING_T
XML_ENTRY_PRIMITIVE2("WLAN1_ACCOUNT_RS_UPDATE_ENABLED", wlan1_accountRsUpdateEnabled, config_setting, "%hhu", config->wlan1_accountRsUpdateEnabled, MIB_WLAN1_ACCOUNT_UPDATE_ENABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_ACCOUNT_RS_UPDATE_DELAY", wlan1_accountRsUpdateDelay, config_setting, "%hu", config->wlan1_accountRsUpdateDelay, MIB_WLAN1_ACCOUNT_UPDATE_DELAY); //WORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_ACCOUNT_RS_MAXRETRY", wlan1_accountRsMaxRetry, config_setting, "%hhu", config->wlan1_accountRsMaxRetry, MIB_WLAN1_ACCOUNT_RS_RETRY); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_ACCOUNT_RS_INTERVAL_TIME", wlan1_accountRsIntervalTime, config_setting, "%hu", config->wlan1_accountRsIntervalTime, MIB_WLAN1_ACCOUNT_RS_INTERVAL_TIME); //WORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_ENABLE_1X", wlan1_enable1X, config_setting, "%hhu", config->wlan1_enable1X, MIB_WLAN1_ENABLE_1X); //BYTE_T
#endif	//WLAN_1x
XML_ENTRY_PRIMITIVE2("WLAN1_PSK_FORMAT", wlan1_wpaPSKFormat, config_setting, "%hhu", config->wlan1_wpaPSKFormat, MIB_WLAN1_WPA_PSK_FORMAT); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WPA2_CIPHER_SUITE", wlan1_wpa2Cipher, config_setting, "%hhu", config->wlan1_wpa2Cipher, MIB_WLAN1_WPA2_CIPHER_SUITE); //BYTE_T
#ifdef WLAN_11W
XML_ENTRY_PRIMITIVE2("WLAN1_DOTIEEE80211W", wlan1_dotIEEE80211W, config_setting, "%hhu", config->wlan1_dotIEEE80211W, MIB_WLAN1_DOTIEEE80211W);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_SHA256", wlan1_sha256, config_setting, "%hhu", config->wlan1_sha256, MIB_WLAN1_SHA256);	//BYTE_T
#endif //WLAN_11W
#endif	//WLAN_WPA
#ifdef WLAN_WDS
XML_ENTRY_PRIMITIVE2("WLAN1_WDS_ENABLED", wlan1_wdsEnabled, config_setting, "%hhu", config->wlan1_wdsEnabled, MIB_WLAN1_WDS_ENABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WDS_NUM", wlan1_wdsNum, config_setting, "%hhu", config->wlan1_wdsNum, MIB_WLAN1_WDS_NUM); //BYTE_T
//XML_DIR_ARRAY("WLAN1_WDS", wlan1_wdsArray, root, wlan1_wdsArray_Idx, MAX_WDS_NUM, MIB_WLAN1_WDS); //WDS_ARRAY_T
XML_ENTRY_PRIMITIVE2("WLAN1_WDS_ENCRYPT", wlan1_wdsEncrypt, config_setting, "%hhu", config->wlan1_wdsEncrypt, MIB_WLAN1_WDS_ENCRYPT);	//BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WDS_WEP_FORMAT", wlan1_wdsWepFormat, config_setting, "%hhu", config->wlan1_wdsWepFormat, MIB_WLAN1_WDS_WEP_FORMAT); //BYTE_T
XML_ENTRY_STRING2("WLAN1_WDS_WEP_KEY", wlan1_wdsWepKey, config_setting, config->wlan1_wdsWepKey, MIB_WLAN1_WDS_WEP_KEY);	//STRING_T
XML_ENTRY_PRIMITIVE2("WLAN1_WDS_PSK_FORMAT", wlan1_wdsPskFormat, config_setting, "%hhu", config->wlan1_wdsPskFormat, MIB_WLAN1_WDS_PSK_FORMAT); //BYTE_T
XML_ENTRY_STRING2("WLAN1_WDS_PSK", wlan1_wdsPsk, config_setting, config->wlan1_wdsPsk, MIB_WLAN1_WDS_PSK);	//STRING_T
#if 0
XML_ENTRY_PRIMITIVE2("WLAN1_WDS_WEP", wlan1_wdsWep, config_setting, "%hhu", config->wlan1_wdsWep, MIB_WLAN1_WDS_WEP); //BYTE_T
XML_ENTRY_BYTE5("WLAN1_WDS_WEP64_KEY1", wlan1_wdsWep64Key1, config_setting, config->wlan1_wdsWep64Key1, MIB_WLAN1_WDS_WEP64_KEY1);	//BYTE5_T
XML_ENTRY_BYTE5("WLAN1_WDS_WEP64_KEY2", wlan1_wdsWep64Key2, config_setting, config->wlan1_wdsWep64Key2, MIB_WLAN1_WDS_WEP64_KEY2);	//BYTE5_T
XML_ENTRY_BYTE5("WLAN1_WDS_WEP64_KEY3", wlan1_wdsWep64Key3, config_setting, config->wlan1_wdsWep64Key3, MIB_WLAN1_WDS_WEP64_KEY3);	//BYTE5_T
XML_ENTRY_BYTE5("WLAN1_WDS_WEP64_KEY4", wlan1_wdsWep64Key4, config_setting, config->wlan1_wdsWep64Key4, MIB_WLAN1_WDS_WEP64_KEY4);	//BYTE5_T
XML_ENTRY_BYTE13("WLAN1_WDS_WEP128_KEY1", wlan1_wdsWep128Key1, config_setting, config->wlan1_wdsWep128Key1, MIB_WLAN1_WDS_WEP128_KEY1);	//BYTE13_T
XML_ENTRY_BYTE13("WLAN1_WDS_WEP128_KEY2", wlan1_wdsWep128Key2, config_setting, config->wlan1_wdsWep128Key2, MIB_WLAN1_WDS_WEP128_KEY2);	//BYTE13_T
XML_ENTRY_BYTE13("WLAN1_WDS_WEP128_KEY3", wlan1_wdsWep128Key3, config_setting, config->wlan1_wdsWep128Key3, MIB_WLAN1_WDS_WEP128_KEY3);	//BYTE13_T
XML_ENTRY_BYTE13("WLAN1_WDS_WEP128_KEY4", wlan1_wdsWep128Key4, config_setting, config->wlan1_wdsWep128Key4, MIB_WLAN1_WDS_WEP128_KEY4);	//BYTE13_T
XML_ENTRY_PRIMITIVE2("WLAN1_WDS_WEP_DEFAULT_KEY", wlan1_wdsWepDefaultKey, config_setting, "%hhu", config->wlan1_wdsWepDefaultKey, MIB_WLAN1_WDS_WEP_DEFAULT_KEY); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WDS_WEP_KEY_TYPE", wlan1_wdsWepKeyType, config_setting, "%hhu", config->wlan1_wdsWepKeyType, MIB_WLAN1_WDS_WEP_KEY_TYPE); //BYTE_T
#endif
#endif	//WLAN_WDS
XML_ENTRY_PRIMITIVE2("WLAN1_BLOCK_RELAY", wlan1_blockRelay, config_setting, "%hhu", config->wlan1_blockRelay, MIB_WLAN1_BLOCK_RELAY); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_BLOCK_ETH2WIR", wlan1_BlockEth2Wir, config_setting, "%hhu", config->wlan1_BlockEth2Wir, MIB_WLAN1_BLOCK_ETH2WIR); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_ITF_GROUP", wlan1_itfGroup, config_setting, "%hhu", config->wlan1_itfGroup, MIB_WLAN1_ITF_GROUP); //BYTE_T
#ifdef WLAN_MBSSID
XML_ENTRY_PRIMITIVE2("WLAN1_BLOCK_MBSSID", wlan1_BlockMbssid, config_setting, "%hhu", config->wlan1_BlockMbssid, MIB_WLAN1_BLOCK_MBSSID); //BYTE_T
#endif	//WLAN_MBSSID

XML_ENTRY_PRIMITIVE2("WLAN1_PROTECTON", wlan1_wlanProtectionDisabled, config_setting, "%hhu", config->wlan1_wlanProtectionDisabled, MIB_WLAN1_PROTECTION_DISABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_AGGREGATION", wlan1_wlanAggregation, config_setting, "%hhu", config->wlan1_wlanAggregation, MIB_WLAN1_AGGREGATION); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_SHORTGI", wlan1_wlanShortGIEnabled, config_setting, "%hhu", config->wlan1_wlanShortGIEnabled, MIB_WLAN1_SHORTGI_ENABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_CONTROLBAND", wlan1_wlanContrlBand, config_setting, "%hhu", config->wlan1_wlanContrlBand, MIB_WLAN1_CONTROL_BAND); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_CHANNELWIDTH", wlan1_wlanChannelWidth, config_setting, "%hhu", config->wlan1_wlanChannelWidth, MIB_WLAN1_CHANNEL_WIDTH); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_11NCOEXIST", wlan1_wlan11nCoexist, config_setting, "%hhu", config->wlan1_wlan11nCoexist, MIB_WLAN1_11N_COEXIST); //BYTE_T

#ifdef CONFIG_RTL_WAPI_SUPPORT
XML_ENTRY_STRING2("WLAN1_WAPI_PSK", wlan1_wapiPsk, config_setting, config->wlan1_wapiPsk, MIB_WLAN1_WAPI_PSK);	//STRING_T
XML_ENTRY_PRIMITIVE2("WLAN1_WAPI_PSKLEN", wlan1_wapiPskLen, config_setting, "%hhu", config->wlan1_wapiPskLen, MIB_WLAN1_WAPI_PSKLEN); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WAPI_PSKFORMAT", wlan1_wapiPskFormat, config_setting, "%hhu", config->wlan1_wapiPskFormat, MIB_WLAN1_WAPI_PSK_FORMAT); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WAPI_AUTH", wlan1_wapiAuth, config_setting, "%hhu", config->wlan1_wapiAuth, MIB_WLAN1_WAPI_AUTH); //BYTE_T
XML_ENTRY_ADDR("WLAN1_WAPI_ASIPADDR", wlan1_wapiAsIpAddr, config_setting, config->wlan1_wapiAsIpAddr, MIB_WLAN1_WAPI_ASIPADDR);	//IA_T
XML_ENTRY_STRING2("WLAN1_WAPI_SEARCHINFO", wlan1_wapiSearchCertInfo, config_setting, config->wlan1_wapiSearchCertInfo, MIB_WLAN1_WAPI_SEARCH_CERTINFO,z);	//STRING_T
XML_ENTRY_PRIMITIVE2("WLAN1_WAPI_SEARCHINDEX", wlan1_wapiSearchIndex, config_setting, "%hhu", config->wlan1_wapiSearchIndex, MIB_WLAN1_WAPI_SEARCH_CERTINDEX); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WAPI_MCASTREKEY", wlan1_wapiMcastkey, config_setting, "%hhu", config->wlan1_wapiMcastkey, MIB_WLAN1_WAPI_MCAST_REKEYTYPE); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WAPI_MCAST_TIME", wlan1_wapiMcastRekeyTime, config_setting, "%ld", config->wlan1_wapiMcastRekeyTime, MIB_WLAN1_WAPI_MCAST_TIME); //DWORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_WAPI_MCAST_PACKETS", wlan1_wapiMcastRekeyPackets, config_setting, "%ld", config->wlan1_wapiMcastRekeyPackets, MIB_WLAN1_WAPI_MCAST_PACKETS); //DWORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_WAPI_UCASTREKEY", wlan1_wapiUcastkey, config_setting, "%hhu", config->wlan1_wapiUcastkey, MIB_WLAN1_WAPI_UCAST_REKETTYPE); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WAPI_UCAST_TIME", wlan1_wapiUcastRekeyTime, config_setting, "%ld", config->wlan1_wapiUcastRekeyTime, MIB_WLAN1_WAPI_UCAST_TIME); //DWORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_WAPI_UCAST_PACKETS", wlan1_wapiUcastRekeyPackets, config_setting, "%ld", config->wlan1_wapiUcastRekeyPackets, MIB_WLAN1_WAPI_UCAST_PACKETS); //DWORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_WAPI_CA_INIT", wlan1_wapiCAInit, config_setting, "%hhu", config->wlan1_wapiCAInit, MIB_WLAN1_WAPI_CA_INIT); //BYTE_T
#endif	//CONFIG_RTL_WAPI_SUPPORT

#ifdef WLAN_WEB_REDIRECT  //jiunming,web_redirect
XML_ENTRY_STRING2("WLAN1_WEB_REDIR_URL", wlan1_WlanWebRedirURL, config_setting, config->wlan1_WlanWebRedirURL, MIB_WLAN1_WEB_REDIR_URL);	//STRING_T
#endif	//WLAN_WEB_REDIRECT

XML_ENTRY_PRIMITIVE2("WLAN1_BAND", wlan1_wlanBand, config_setting, "%hhu", config->wlan1_wlanBand, MIB_WLAN1_BAND); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_FIX_RATE", wlan1_fixedTxRate, config_setting, "%u", config->wlan1_fixedTxRate, MIB_WLAN1_FIX_RATE); //DWORD_T
XML_ENTRY_PRIMITIVE2("WLAN1_BEACON_ADVERTISEMENT", wlan1_wlanBcnAdvtisement, config_setting, "%hhu", config->wlan1_wlanBcnAdvtisement, MIB_WLAN1_BEACON_ADVERTISEMENT); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_MAC_CTRL", wlan1_wlan_mac_ctrl, config_setting, "%hhu", config->wlan1_wlan_mac_ctrl, MIB_WLAN1_MAC_CTRL); //BYTE_T
#ifdef CONFIG_WIFI_SIMPLE_CONFIG //WPS
XML_ENTRY_PRIMITIVE2("WLAN1_WSC_DISABLE", wlan1_wscDisable, config_setting, "%hhu", config->wlan1_wscDisable, MIB_WLAN1_WSC_DISABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WSC_METHOD", wlan1_wscMethod, config_setting, "%hhu", config->wlan1_wscMethod, MIB_WLAN1_WSC_METHOD); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WSC_AUTH", wlan1_wscAuth, config_setting, "%hhu", config->wlan1_wscAuth, MIB_WLAN1_WSC_AUTH); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WSC_ENC", wlan1_wscEnc, config_setting, "%hhu", config->wlan1_wscEnc, MIB_WLAN1_WSC_ENC); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WSC_MANUAL_ENABLED", wlan1_wscManualEnabled, config_setting, "%hhu", config->wlan1_wscManualEnabled, MIB_WLAN1_WSC_MANUAL_ENABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WSC_UPNP_ENABLED", wlan1_wscUpnpEnabled, config_setting, "%hhu", config->wlan1_wscUpnpEnabled, MIB_WLAN1_WSC_UPNP_ENABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_WSC_REGISTRAR_ENABLED", wlan1_wscRegistrarEnabled, config_setting, "%hhu", config->wlan1_wscRegistrarEnabled, MIB_WLAN1_WSC_REGISTRAR_ENABLED); //BYTE_T
XML_ENTRY_STRING2("WLAN1_WSC_PSK", wlan1_wscPsk, config_setting, config->wlan1_wscPsk, MIB_WLAN1_WSC_PSK);	//STRING_T
XML_ENTRY_STRING2("WLAN1_WSC_SSID", wlan1_wscSsid, config_setting, config->wlan1_wscSsid, MIB_WLAN1_WSC_SSID);	//STRING_T
XML_ENTRY_PRIMITIVE2("WLAN1_WSC_CONFIGBYEXTREG", wlan1_wscConfigByExtReg, config_setting, "%hhu", config->wlan1_wscConfigByExtReg, MIB_WLAN1_WSC_CONFIG_BY_EXT_REG); //BYTE_T
#endif	//CONFIG_WIFI_SIMPLE_CONFIG
#ifdef WLAN_MBSSID
XML_ENTRY_PRIMITIVE2("WLAN1_VAP0_ITF_GROUP", wlan1_itfGroupVap0, config_setting, "%hhu", config->wlan1_itfGroupVap0, MIB_WLAN1_VAP0_ITF_GROUP); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_VAP1_ITF_GROUP", wlan1_itfGroupVap1, config_setting, "%hhu", config->wlan1_itfGroupVap1, MIB_WLAN1_VAP1_ITF_GROUP); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_VAP2_ITF_GROUP", wlan1_itfGroupVap2, config_setting, "%hhu", config->wlan1_itfGroupVap2, MIB_WLAN1_VAP2_ITF_GROUP); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_VAP3_ITF_GROUP", wlan1_itfGroupVap3, config_setting, "%hhu", config->wlan1_itfGroupVap3, MIB_WLAN1_VAP3_ITF_GROUP); //BYTE_T
#endif	//WLAN_MBSSID
#ifdef WLAN_QoS
XML_ENTRY_PRIMITIVE2("WLAN1_QoS", wlan1_wlanqos, config_setting, "%hhu", config->wlan1_wlanqos, MIB_WLAN1_QoS); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN1_APSD_ENABLE", wlan1_wlanqos_apsd, config_setting, "%hhu", config->wlan1_wlanqos_apsd, MIB_WLAN1_APSD_ENABLE); //BYTE_T
#endif	//WLAN_QoS
#endif //CONFIG_RTL_92D_SUPPORT
#endif // of WLAN_SUPPORT

// Jenny, system log
XML_ENTRY_PRIMITIVE2("SYSLOG_LOG_LEVEL", syslogslevel, config_setting, "%hhu", config->syslogslevel, MIB_SYSLOG_LOG_LEVEL); //BYTE_T
XML_ENTRY_PRIMITIVE2("SYSLOG_DISPLAY_LEVEL", syslogdlevel, config_setting, "%hhu", config->syslogdlevel, MIB_SYSLOG_DISPLAY_LEVEL); //BYTE_T
#ifdef SYSLOG_REMOTE_LOG
XML_ENTRY_PRIMITIVE2("SYSLOG_MODE", syslogmode, config_setting, "%hhu", config->syslogmode, MIB_SYSLOG_MODE); //BYTE_T
XML_ENTRY_ADDR("SYSLOG_SERVER_IP", syslogServerIpAddr, config_setting, config->syslogServerIpAddr, MIB_SYSLOG_SERVER_IP);    //IA_T
XML_ENTRY_PRIMITIVE2("SYSLOG_SERVER_PORT", syslogServerPort, config_setting, "%hu", config->syslogServerPort, MIB_SYSLOG_SERVER_PORT); //WORD_T
#endif	//SYSLOG_REMOTE_LOG
// Added by Mason Yu for write superUser into Current Setting
XML_ENTRY_STRING2("SUSER_NAME", suserName, config_setting, config->suserName, MIB_SUSER_NAME);    //STRING_T
XML_ENTRY_STRING2("SUSER_PASSWORD", suserPassword, config_setting, config->suserPassword, MIB_SUSER_PASSWORD);    //STRING_T
// Added by Mason Yu for correct Tone Mib Type
XML_ENTRY_BYTE_ARRAY("ADSL_TONE", adslTone, config_setting, config->adslTone, MIB_ADSL_TONE); //BYTE_ARRAY_T
// ioctl for direct bridge mode, jiunming
XML_ENTRY_PRIMITIVE2("DIRECT_BRIDGE_MODE", DirectBridgeMode, config_setting, "%hhu", config->DirectBridgeMode, MIB_DIRECT_BRIDGE_MODE); //BYTE_T
XML_ENTRY_PRIMITIVE2("ADSL_HIGH_INP", adslHighInp, config_setting, "%hhu", config->adslHighInp, MIB_ADSL_HIGH_INP); //BYTE_T

#ifdef _CWMP_MIB_ /*jiunming, mib for cwmp-tr069*/
XML_ENTRY_STRING2("CWMP_PROVISIONINGCODE", cwmp_ProvisioningCode, config_setting, config->cwmp_ProvisioningCode, CWMP_PROVISIONINGCODE);    //STRING_T
XML_ENTRY_STRING2("CWMP_ACS_URL", cwmp_ACSURL, config_setting, config->cwmp_ACSURL, CWMP_ACS_URL);    //STRING_T
XML_ENTRY_STRING2("CWMP_ACS_URL_OLD", cwmp_ACSURL_OLD, config_setting, config->cwmp_ACSURL_OLD, CWMP_ACS_URL_OLD);    //STRING_T
XML_ENTRY_STRING2("CWMP_ACS_USERNAME", cwmp_ACSUserName, config_setting, config->cwmp_ACSUserName, CWMP_ACS_USERNAME);    //STRING_T
XML_ENTRY_STRING2("CWMP_ACS_PASSWORD", cwmp_ACSPassword, config_setting, config->cwmp_ACSPassword, CWMP_ACS_PASSWORD);    //STRING_T
XML_ENTRY_PRIMITIVE2("CWMP_INFORM_ENABLE", cwmp_InformEnable, config_setting, "%hhu", config->cwmp_InformEnable, CWMP_INFORM_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_INFORM_INTERVAL", cwmp_InformInterval, config_setting, "%u", config->cwmp_InformInterval, CWMP_INFORM_INTERVAL); //INTEGER_T
XML_ENTRY_PRIMITIVE2("CWMP_INFORM_TIME", cwmp_InformTime, config_setting, "%u", config->cwmp_InformTime, CWMP_INFORM_TIME); //INTEGER_T
XML_ENTRY_STRING2("CWMP_CONREQ_USERNAME", cwmp_ConnReqUserName, config_setting, config->cwmp_ConnReqUserName, CWMP_CONREQ_USERNAME);    //STRING_T
XML_ENTRY_STRING2("CWMP_CONREQ_PASSWORD", cwmp_ConnReqPassword, config_setting, config->cwmp_ConnReqPassword, CWMP_CONREQ_PASSWORD);    //STRING_T
XML_ENTRY_PRIMITIVE2("CWMP_ACS_UPGRADESMANAGED", cwmp_UpgradesManaged, config_setting, "%hhu", config->cwmp_UpgradesManaged, CWMP_ACS_UPGRADESMANAGED); //BYTE_T
XML_ENTRY_STRING2("CWMP_LAN_CONFIGPASSWD", cwmp_LANConfPassword, config_setting, config->cwmp_LANConfPassword, CWMP_LAN_CONFIGPASSWD);    //STRING_T
XML_ENTRY_STRING2("CWMP_SERIALNUMBER", cwmp_SerialNumber, config_setting, config->cwmp_SerialNumber, CWMP_SERIALNUMBER);    //STRING_T
XML_ENTRY_PRIMITIVE2("CWMP_DHCP_SERVERCONF", cwmp_DHCP_ServerConf, config_setting, "%hhu", config->cwmp_DHCP_ServerConf, CWMP_DHCP_SERVERCONF); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_LAN_IPIFENABLE", cwmp_LAN_IPIFEnable, config_setting, "%hhu", config->cwmp_LAN_IPIFEnable, CWMP_LAN_IPIFENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_LAN_ETHIFENABLE", cwmp_LAN_EthIFEnable, config_setting, "%hhu", config->cwmp_LAN_EthIFEnable, CWMP_LAN_ETHIFENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_WLAN_BASICENCRY", cwmp_WLAN_BasicEncry, config_setting, "%hhu", config->cwmp_WLAN_BasicEncry, CWMP_WLAN_BASICENCRY); //BYTE_T
XML_ENTRY_STRING2("CWMP_DL_COMMANDKEY", cwmp_DL_CommandKey, config_setting, config->cwmp_DL_CommandKey, CWMP_DL_COMMANDKEY);    //STRING_T
XML_ENTRY_PRIMITIVE2("CWMP_DL_STARTTIME", cwmp_DL_StartTime, config_setting, "%u", config->cwmp_DL_StartTime, CWMP_DL_STARTTIME); //INTEGER_T
XML_ENTRY_PRIMITIVE2("CWMP_DL_COMPLETETIME", cwmp_DL_CompleteTime, config_setting, "%u", config->cwmp_DL_CompleteTime, CWMP_DL_COMPLETETIME); //INTEGER_T
XML_ENTRY_PRIMITIVE2("CWMP_DL_FAULTCODE", cwmp_DL_FaultCode, config_setting, "%u", config->cwmp_DL_FaultCode, CWMP_DL_FAULTCODE); //INTEGER_T
XML_ENTRY_PRIMITIVE2("CWMP_INFORM_EVENTCODE", cwmp_Inform_EventCode, config_setting, "%u", config->cwmp_Inform_EventCode, CWMP_INFORM_EVENTCODE); //INTEGER_T
XML_ENTRY_STRING2("CWMP_RB_COMMANDKEY", cwmp_RB_CommandKey, config_setting, config->cwmp_RB_CommandKey, CWMP_RB_COMMANDKEY);    //STRING_T
XML_ENTRY_STRING2("CWMP_ACS_PARAMETERKEY", cwmp_ACS_ParameterKey, config_setting, config->cwmp_ACS_ParameterKey, CWMP_ACS_PARAMETERKEY);    //STRING_T
XML_ENTRY_STRING2("CWMP_CERT_PASSWORD", cwmp_CERT_Password, config_setting, config->cwmp_CERT_Password, CWMP_CERT_PASSWORD);    //STRING_T
XML_ENTRY_PRIMITIVE2("CWMP_FLAG", cwmp_Flag, config_setting, "%hhu", config->cwmp_Flag, CWMP_FLAG); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_FLAG2", cwmp_Flag2, config_setting, "%hhu", config->cwmp_Flag2, CWMP_FLAG2); //BYTE_T
/*star:20091228 START add for store parameterkey*/
XML_ENTRY_STRING2("CWMP_PARAMETERKEY", cwmp_Parameterkey, config_setting, config->cwmp_Parameterkey, CWMP_PARAMETERKEY);    //STRING_T
/*star:20091228 END*/
XML_ENTRY_STRING2("CWMP_SI_COMMANDKEY", cwmp_SI_CommandKey, config_setting, config->cwmp_SI_CommandKey, CWMP_SI_COMMANDKEY);    //STRING_T
#ifdef _PRMT_USERINTERFACE_
XML_ENTRY_PRIMITIVE2("UIF_PW_REQUIRED", UIF_PW_Required, config_setting, "%hhu", config->UIF_PW_Required, UIF_PW_REQUIRED); //BYTE_T
XML_ENTRY_PRIMITIVE2("UIF_PW_USER_SEL", UIF_PW_User_Sel, config_setting, "%hhu", config->UIF_PW_User_Sel, UIF_PW_USER_SEL); //BYTE_T
XML_ENTRY_PRIMITIVE2("UIF_UPGRADE", UIF_Upgrade, config_setting, "%hhu", config->UIF_Upgrade, UIF_UPGRADE); //BYTE_T
XML_ENTRY_PRIMITIVE2("UIF_WARRANTYDATE", UIF_WarrantyDate, config_setting, "%u", config->UIF_WarrantyDate, UIF_WARRANTYDATE); //INTEGER_T
XML_ENTRY_STRING2("UIF_AUTOUPDATESERVER", UIF_AutoUpdateServer, config_setting, config->UIF_AutoUpdateServer, UIF_AUTOUPDATESERVER);    //STRING_T
XML_ENTRY_STRING2("UIF_USERUPDATESERVER", UIF_UserUpdateServer, config_setting, config->UIF_UserUpdateServer, UIF_USERUPDATESERVER);    //STRING_T
#endif //#ifdef _PRMT_USERINTERFACE_
#ifdef  _PRMT_X_CT_COM_IPTV_
XML_ENTRY_PRIMITIVE2("CWMP_CT_IPTV_IGMPENABLE", cwmp_CT_IPTV_IGMPEnable, config_setting, "%hhu", config->cwmp_CT_IPTV_IGMPEnable, CWMP_CT_IPTV_IGMPENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_IPTV_STBNUMBER", cwmp_CT_IPTV_STBNumber, config_setting, "%u", config->cwmp_CT_IPTV_STBNumber, CWMP_CT_IPTV_STBNUMBER); //INTEGER_T
#endif //#ifdef  _PRMT_X_CT_COM_IPTV_
#ifdef  _PRMT_X_CT_COM_RECON_
XML_ENTRY_PRIMITIVE2("CWMP_CT_RECON_ENABLE", cwmp_CT_ReCon_Enable, config_setting, "%hhu", config->cwmp_CT_ReCon_Enable, CWMP_CT_RECON_ENABLE); //BYTE_T
#endif //_PRMT_X_CT_COM_RECON_

#ifdef  _PRMT_X_CT_COM_MWBAND_
XML_ENTRY_PRIMITIVE2("CWMP_CT_MWBAND_MODE", cwmp_CT_MWBAND_Mode, config_setting, "%u", config->cwmp_CT_MWBAND_Mode, CWMP_CT_MWBAND_MODE); //INTEGER_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_MWBAND_STB_ENABLE", cwmp_CT_MWBAND_STB_Enable, config_setting, "%hhu", config->cwmp_CT_MWBAND_STB_Enable, CWMP_CT_MWBAND_STB_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_MWBAND_CMR_ENABLE", cwmp_CT_MWBAND_CMR_Enable, config_setting, "%hhu", config->cwmp_CT_MWBAND_CMR_Enable, CWMP_CT_MWBAND_CMR_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_MWBAND_PC_ENABLE", cwmp_CT_MWBAND_PC_Enable, config_setting, "%hhu", config->cwmp_CT_MWBAND_PC_Enable, CWMP_CT_MWBAND_PC_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_MWBAND_PHN_ENABLE", cwmp_CT_MWBAND_PHN_Enable, config_setting, "%hhu", config->cwmp_CT_MWBAND_PHN_Enable, CWMP_CT_MWBAND_PHN_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_MWBAND_NUMBER", cwmp_CT_MWBAND_Number, config_setting, "%u", config->cwmp_CT_MWBAND_Number, CWMP_CT_MWBAND_NUMBER); //INTEGER_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_MWBAND_STB_NUM", cwmp_CT_MWBAND_STB_Num, config_setting, "%u", config->cwmp_CT_MWBAND_STB_Num, CWMP_CT_MWBAND_STB_NUM); //INTEGER_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_MWBAND_CMR_NUM", cwmp_CT_MWBAND_CMR_Num, config_setting, "%u", config->cwmp_CT_MWBAND_CMR_Num, CWMP_CT_MWBAND_CMR_NUM); //INTEGER_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_MWBAND_PC_NUM", cwmp_CT_MWBAND_PC_Num, config_setting, "%u", config->cwmp_CT_MWBAND_PC_Num, CWMP_CT_MWBAND_PC_NUM); //INTEGER_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_MWBAND_PHN_NUM", cwmp_CT_MWBAND_PHN_Num, config_setting, "%u", config->cwmp_CT_MWBAND_PHN_Num, CWMP_CT_MWBAND_PHN_NUM); //INTEGER_T
#endif //#ifdef  _PRMT_X_CT_COM_MWBAND_
#ifdef _PRMT_X_CT_COM_PORTALMNT_
XML_ENTRY_PRIMITIVE2("CWMP_CT_PM_ENABLE", cwmp_CT_PM_Enable, config_setting, "%hhu", config->cwmp_CT_PM_Enable, CWMP_CT_PM_ENABLE); //BYTE_T
XML_ENTRY_STRING2("CWMP_CT_PM_URL4PC", cwmp_CT_PM_URL4PC, config_setting, config->cwmp_CT_PM_URL4PC, CWMP_CT_PM_URL4PC);    //STRING_T
XML_ENTRY_STRING2("CWMP_CT_PM_URL4STB", cwmp_CT_PM_URL4STB, config_setting, config->cwmp_CT_PM_URL4STB, CWMP_CT_PM_URL4STB);    //STRING_T
XML_ENTRY_STRING2("CWMP_CT_PM_URL4MOBILE", cwmp_CT_PM_URL4MOBILE, config_setting, config->cwmp_CT_PM_URL4MOBILE, CWMP_CT_PM_URL4MOBILE);    //STRING_T
#endif //_PRMT_X_CT_COM_PORTALMNT_

#if defined( _PRMT_X_CT_COM_DHCP_)||defined(IP_BASED_CLIENT_TYPE)
#if 1
XML_ENTRY_ADDR("CWMP_CT_PC_MINADDR", cwmp_CT_PC_MinAddr, config_setting, config->cwmp_CT_PC_MinAddr, CWMP_CT_PC_MINADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_PC_MAXADDR", cwmp_CT_PC_MaxAddr, config_setting, config->cwmp_CT_PC_MaxAddr, CWMP_CT_PC_MAXADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_CMR_MINADDR", cwmp_CT_CMR_MinAddr, config_setting, config->cwmp_CT_CMR_MinAddr, CWMP_CT_CMR_MINADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_CMR_MAXADDR", cwmp_CT_CMR_MaxAddr, config_setting, config->cwmp_CT_CMR_MaxAddr, CWMP_CT_CMR_MAXADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_STB_MINADDR", cwmp_CT_STB_MinAddr, config_setting, config->cwmp_CT_STB_MinAddr, CWMP_CT_STB_MINADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_STB_MAXADDR", cwmp_CT_STB_MaxAddr, config_setting, config->cwmp_CT_STB_MaxAddr, CWMP_CT_STB_MAXADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_PHN_MINADDR", cwmp_CT_PHN_MinAddr, config_setting, config->cwmp_CT_PHN_MinAddr, CWMP_CT_PHN_MINADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_PHN_MAXADDR", cwmp_CT_PHN_MaxAddr, config_setting, config->cwmp_CT_PHN_MaxAddr, CWMP_CT_PHN_MAXADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_HGW_MINADDR", cwmp_CT_HGW_MinAddr, config_setting, config->cwmp_CT_HGW_MinAddr, CWMP_CT_HGW_MINADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_HGW_MAXADDR", cwmp_CT_HGW_MaxAddr, config_setting, config->cwmp_CT_HGW_MaxAddr, CWMP_CT_HGW_MAXADDR);    //IA_T
#else
XML_ENTRY_PRIMITIVE2("CWMP_CT_PC_MINADDR", cwmp_CT_PC_MinAddr, config_setting, "%hhu", config->cwmp_CT_PC_MinAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_PC_MAXADDR", cwmp_CT_PC_MaxAddr, config_setting, "%hhu", config->cwmp_CT_PC_MaxAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_CMR_MINADDR", cwmp_CT_CMR_MinAddr, config_setting, "%hhu", config->cwmp_CT_CMR_MinAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_CMR_MAXADDR", cwmp_CT_CMR_MaxAddr, config_setting, "%hhu", config->cwmp_CT_CMR_MaxAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_STB_MINADDR", cwmp_CT_STB_MinAddr, config_setting, "%hhu", config->cwmp_CT_STB_MinAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_STB_MAXADDR", cwmp_CT_STB_MaxAddr, config_setting, "%hhu", config->cwmp_CT_STB_MaxAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_PHN_MINADDR", cwmp_CT_PHN_MinAddr, config_setting, "%hhu", config->cwmp_CT_PHN_MinAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_PHN_MAXADDR", cwmp_CT_PHN_MaxAddr, config_setting, "%hhu", config->cwmp_CT_PHN_MaxAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_HGW_MINADDR", cwmp_CT_HGW_MinAddr, config_setting, "%hhu", config->cwmp_CT_HGW_MinAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_HGW_MAXADDR", cwmp_CT_HGW_MaxAddr, config_setting, "%hhu", config->cwmp_CT_HGW_MaxAddr); //BYTE_T
#endif
#endif //_PRMT_X_CT_COM_DHCP_
XML_ENTRY_STRING2("CWMP_ACS_KICKURL", cwmp_ACS_KickURL, config_setting, config->cwmp_ACS_KickURL, CWMP_ACS_KICKURL);    //STRING_T
XML_ENTRY_STRING2("CWMP_ACS_DOWNLOADURL", cwmp_ACS_DownloadURL, config_setting, config->cwmp_ACS_DownloadURL, CWMP_ACS_DOWNLOADURL);    //STRING_T
XML_ENTRY_PRIMITIVE2("CWMP_CONREQ_PORT", cwmp_ConnReqPort, config_setting, "%u", config->cwmp_ConnReqPort, CWMP_CONREQ_PORT); //INTEGER_T
XML_ENTRY_STRING2("CWMP_CONREQ_PATH", cwmp_ConnReqPath, config_setting, config->cwmp_ConnReqPath, CWMP_CONREQ_PATH);    //STRING_T
#ifdef _PRMT_TR143_
XML_ENTRY_PRIMITIVE2("TR143_UDPECHO_ENABLE", tr143_udpecho_enable, config_setting, "%hhu", config->tr143_udpecho_enable, TR143_UDPECHO_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("TR143_UDPECHO_ITFTYPE", tr143_udpecho_itftype, config_setting, "%hhu", config->tr143_udpecho_itftype, TR143_UDPECHO_ITFTYPE); //BYTE_T
XML_ENTRY_ADDR("TR143_UDPECHO_SRCIP", tr143_udpecho_srcip, config_setting, config->tr143_udpecho_srcip, TR143_UDPECHO_SRCIP); //IA_T
XML_ENTRY_PRIMITIVE2("TR143_UDPECHO_PORT", tr143_udpecho_port, config_setting, "%hu", config->tr143_udpecho_port, TR143_UDPECHO_PORT); //WORD_T
XML_ENTRY_PRIMITIVE2("TR143_UDPECHO_PLUS", tr143_udpecho_plus, config_setting, "%hhu", config->tr143_udpecho_plus, TR143_UDPECHO_PLUS); //BYTE_T
#endif //_PRMT_TR143_
XML_ENTRY_STRING2("CWMP_PERSISTENT_DATA", cwmp_Persistent_Data, config_setting, config->cwmp_Persistent_Data, CWMP_PERSISTENT_DATA);    //STRING_T
XML_ENTRY_PRIMITIVE2("CWMP_WAN_INTERFACE", cwmp_wan_interface, config_setting, "%u", config->cwmp_wan_interface, CWMP_WAN_INTERFACE); //INTEGER_T
#else/*_CWMP_MIB_*/
#if defined( _PRMT_X_CT_COM_DHCP_)||defined(IP_BASED_CLIENT_TYPE)
#if 1
XML_ENTRY_ADDR("CWMP_CT_PC_MINADDR", cwmp_CT_PC_MinAddr, config_setting, config->cwmp_CT_PC_MinAddr, CWMP_CT_PC_MINADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_PC_MAXADDR", cwmp_CT_PC_MaxAddr, config_setting, config->cwmp_CT_PC_MaxAddr, CWMP_CT_PC_MAXADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_CMR_MINADDR", cwmp_CT_CMR_MinAddr, config_setting, config->cwmp_CT_CMR_MinAddr, CWMP_CT_CMR_MINADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_CMR_MAXADDR", cwmp_CT_CMR_MaxAddr, config_setting, config->cwmp_CT_CMR_MaxAddr, CWMP_CT_CMR_MAXADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_STB_MINADDR", cwmp_CT_STB_MinAddr, config_setting, config->cwmp_CT_STB_MinAddr, CWMP_CT_STB_MINADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_STB_MAXADDR", cwmp_CT_STB_MaxAddr, config_setting, config->cwmp_CT_STB_MaxAddr, CWMP_CT_STB_MAXADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_PHN_MINADDR", cwmp_CT_PHN_MinAddr, config_setting, config->cwmp_CT_PHN_MinAddr, CWMP_CT_PHN_MINADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_PHN_MAXADDR", cwmp_CT_PHN_MaxAddr, config_setting, config->cwmp_CT_PHN_MaxAddr, CWMP_CT_PHN_MAXADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_HGW_MINADDR", cwmp_CT_HGW_MinAddr, config_setting, config->cwmp_CT_HGW_MinAddr, CWMP_CT_HGW_MINADDR);    //IA_T
XML_ENTRY_ADDR("CWMP_CT_HGW_MAXADDR", cwmp_CT_HGW_MaxAddr, config_setting, config->cwmp_CT_HGW_MaxAddr, CWMP_CT_HGW_MAXADDR);    //IA_T
#else
XML_ENTRY_PRIMITIVE2("CWMP_CT_PC_MINADDR", cwmp_CT_PC_MinAddr, config_setting, "%hhu", config->cwmp_CT_PC_MinAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_PC_MAXADDR", cwmp_CT_PC_MaxAddr, config_setting, "%hhu", config->cwmp_CT_PC_MaxAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_CMR_MINADDR", cwmp_CT_CMR_MinAddr, config_setting, "%hhu", config->cwmp_CT_CMR_MinAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_CMR_MAXADDR", cwmp_CT_CMR_MaxAddr, config_setting, "%hhu", config->cwmp_CT_CMR_MaxAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_STB_MINADDR", cwmp_CT_STB_MinAddr, config_setting, "%hhu", config->cwmp_CT_STB_MinAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_STB_MAXADDR", cwmp_CT_STB_MaxAddr, config_setting, "%hhu", config->cwmp_CT_STB_MaxAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_PHN_MINADDR", cwmp_CT_PHN_MinAddr, config_setting, "%hhu", config->cwmp_CT_PHN_MinAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_PHN_MAXADDR", cwmp_CT_PHN_MaxAddr, config_setting, "%hhu", config->cwmp_CT_PHN_MaxAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_HGW_MINADDR", cwmp_CT_HGW_MinAddr, config_setting, "%hhu", config->cwmp_CT_HGW_MinAddr); //BYTE_T
XML_ENTRY_PRIMITIVE2("CWMP_CT_HGW_MAXADDR", cwmp_CT_HGW_MaxAddr, config_setting, "%hhu", config->cwmp_CT_HGW_MaxAddr); //BYTE_T
#endif
#endif //_PRMT_X_CT_COM_DHCP_
#endif	/*_CWMP_MIB_*/

//for log
XML_ENTRY_PRIMITIVE2("SYSLOG", syslog, config_setting, "%hhu", config->syslog, MIB_SYSLOG); //BYTE_T
XML_ENTRY_PRIMITIVE2("MAXLOGLEN", maxmsglen, config_setting, "%u", config->maxmsglen, MIB_MAXLOGLEN); //INTEGER_T
XML_ENTRY_PRIMITIVE2("ADSLDBG", adsldbg, config_setting, "%hhu", config->adsldbg, MIB_ADSL_DEBUG); //BYTE_T
XML_ENTRY_PRIMITIVE2("MIB_ETH_MAC_CTRL", eth_mac_ctrl, config_setting, "%hhu", config->eth_mac_ctrl, MIB_ETH_MAC_CTRL); //BYTE_T
XML_ENTRY_PRIMITIVE2("MIB_WLAN_MAC_CTRL", wlan_mac_ctrl, config_setting, "%hhu", config->wlan_mac_ctrl, MIB_WLAN_MAC_CTRL); //BYTE_T

#ifdef DOS_SUPPORT
XML_ENTRY_PRIMITIVE2("DOS_ENABLED", dos_enable, config_setting, "%u", config->dos_enable, MIB_DOS_ENABLED); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DOS_SYSSYN_FLOOD", dos_syssyn_flood, config_setting, "%u", config->dos_syssyn_flood, MIB_DOS_SYSSYN_FLOOD); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DOS_SYSFIN_FLOOD", dos_sysfin_flood, config_setting, "%u", config->dos_sysfin_flood, MIB_DOS_SYSFIN_FLOOD); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DOS_SYSUDP_FLOOD", dos_sysudp_flood, config_setting, "%u", config->dos_sysudp_flood, MIB_DOS_SYSUDP_FLOOD); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DOS_SYSICMP_FLOOD", dos_sysicmp_flood, config_setting, "%u", config->dos_sysicmp_flood, MIB_DOS_SYSICMP_FLOOD); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DOS_PIPSYN_FLOOD", dos_pipsyn_flood, config_setting, "%u", config->dos_pipsyn_flood, MIB_DOS_PIPSYN_FLOOD); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DOS_PIPFIN_FLOOD", dos_pipfin_flood, config_setting, "%u", config->dos_pipfin_flood, MIB_DOS_PIPFIN_FLOOD); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DOS_PIPUDP_FLOOD", dos_pipudp_flood, config_setting, "%u", config->dos_pipudp_flood, MIB_DOS_PIPUDP_FLOOD); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DOS_PIPICMP_FLOOD", dos_pipicmp_flood, config_setting, "%u", config->dos_pipicmp_flood, MIB_DOS_PIPICMP_FLOOD); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DOS_BLOCK_TIME", dos_block_time, config_setting, "%u", config->dos_block_time, MIB_DOS_BLOCK_TIME); //INTEGER_T
#endif	//DOS_SUPPORT

#ifdef CONFIG_WIFI_SIMPLE_CONFIG //WPS
XML_ENTRY_PRIMITIVE2("WSC_DISABLE", wscDisable, config_setting, "%hhu", config->wscDisable, MIB_WSC_DISABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("WSC_METHOD", wscMethod, config_setting, "%hhu", config->wscMethod, MIB_WSC_METHOD); //BYTE_T
XML_ENTRY_PRIMITIVE2("WSC_CONFIGURED", wscConfigured, config_setting, "%hhu", config->wscConfigured, MIB_WSC_CONFIGURED); //BYTE_T
XML_ENTRY_STRING2("WSC_PIN", wscPin, config_setting, config->wscPin, MIB_WSC_PIN); //STRING_T
XML_ENTRY_PRIMITIVE2("WSC_AUTH", wscAuth, config_setting, "%hhu", config->wscAuth, MIB_WSC_AUTH); //BYTE_T
XML_ENTRY_PRIMITIVE2("WSC_ENC", wscEnc, config_setting, "%hhu", config->wscEnc, MIB_WSC_ENC); //BYTE_T
XML_ENTRY_PRIMITIVE2("WSC_MANUAL_ENABLED", wscManualEnabled, config_setting, "%hhu", config->wscManualEnabled, MIB_WSC_MANUAL_ENABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WSC_UPNP_ENABLED", wscUpnpEnabled, config_setting, "%hhu", config->wscUpnpEnabled, MIB_WSC_UPNP_ENABLED); //BYTE_T
XML_ENTRY_PRIMITIVE2("WSC_REGISTRAR_ENABLED", wscRegistrarEnabled, config_setting, "%hhu", config->wscRegistrarEnabled, MIB_WSC_REGISTRAR_ENABLED); //BYTE_T
XML_ENTRY_STRING2("WSC_PSK", wscPsk, config_setting, config->wscPsk, MIB_WSC_PSK); //STRING_T
XML_ENTRY_STRING2("WSC_SSID", wscSsid, config_setting, config->wscSsid, MIB_WSC_SSID); //STRING_T
XML_ENTRY_PRIMITIVE2("WSC_CONFIGBYEXTREG", wscConfigByExtReg, config_setting, "%hhu", config->wscConfigByExtReg, MIB_WSC_CONFIG_BY_EXT_REG); //BYTE_T
XML_ENTRY_PRIMITIVE2("WSC_VERSION", wscVersion, config_setting, "%hhu", config->wscVersion, MIB_WSC_VERSION); //BYTE_T
#endif	// CONFIG_WIFI_SIMPLE_CONFIG

#ifdef CONFIG_USER_DHCP_SERVER
XML_ENTRY_ADDR("LAN_DHCP_GATEWAY", dhcp_GatewayAddr, config_setting, config->dhcp_GatewayAddr, MIB_ADSL_LAN_DHCP_GATEWAY); //IA_T
#endif
#ifdef WLAN_MBSSID
XML_ENTRY_PRIMITIVE2("WLAN_VAP0_ITF_GROUP", itfGroupVap0, config_setting, "%hhu", config->itfGroupVap0, MIB_WLAN_VAP0_ITF_GROUP); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_VAP1_ITF_GROUP", itfGroupVap1, config_setting, "%hhu", config->itfGroupVap1, MIB_WLAN_VAP1_ITF_GROUP); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_VAP2_ITF_GROUP", itfGroupVap2, config_setting, "%hhu", config->itfGroupVap2, MIB_WLAN_VAP2_ITF_GROUP); //BYTE_T
XML_ENTRY_PRIMITIVE2("WLAN_VAP3_ITF_GROUP", itfGroupVap3, config_setting, "%hhu", config->itfGroupVap3, MIB_WLAN_VAP3_ITF_GROUP); //BYTE_T
#endif	// WLAN_MBSSID
#ifdef IP_QOS
XML_ENTRY_BYTE_ARRAY("8021P_PRIO", set8021p_prio, config_setting, config->set8021p_prio, MIB_8021P_PRIO); //BYTE_ARRAY_T
XML_ENTRY_BYTE_ARRAY("PRED_PRIO", setpred_prio, config_setting, config->setpred_prio, MIB_PRED_PRIO); //BYTE_ARRAY_T
#endif	// IP_QOS

//add by ramen for the ALG on-off
#ifdef CONFIG_IP_NF_ALG_ONOFF
#ifdef CONFIG_NF_CONNTRACK_FTP
XML_ENTRY_PRIMITIVE2("MIB_IP_ALG_FTP", ipAlgFTP, config_setting, "%hhu", config->ipAlgFTP, MIB_IP_ALG_FTP); //BYTE_T
#endif
#ifdef CONFIG_NF_CONNTRACK_H323
XML_ENTRY_PRIMITIVE2("MIB_IP_ALG_H323", ipAlgH323, config_setting, "%hhu", config->ipAlgH323, MIB_IP_ALG_H323); //BYTE_T
#endif
#ifdef CONFIG_NF_CONNTRACK_IRC
XML_ENTRY_PRIMITIVE2("MIB_IP_ALG_IRC", ipAlgIRC, config_setting, "%hhu", config->ipAlgIRC, MIB_IP_ALG_IRC); //BYTE_T
#endif
// Mason Yu. todo
//#ifdef CONFIG_NF_CONNTRACK_RTSP
#if 1
XML_ENTRY_PRIMITIVE2("MIB_IP_ALG_RTSP", ipAlgRTSP, config_setting, "%hhu", config->ipAlgRTSP, MIB_IP_ALG_RTSP); //BYTE_T
#endif
#ifdef CONFIG_NF_CONNTRACK_QUAKE3
XML_ENTRY_PRIMITIVE2("MIB_IP_ALG_QUAKE3", ipAlgQUAKE3, config_setting, "%hhu", config->ipAlgQUAKE3, MIB_IP_ALG_QUAKE3); //BYTE_T
#endif
#ifdef CONFIG_NF_CONNTRACK_CUSEEME
XML_ENTRY_PRIMITIVE2("MIB_IP_ALG_CUSEEME", ipAlgCUSEEME, config_setting, "%hhu", config->ipAlgCUSEEME, MIB_IP_ALG_CUSEEME); //BYTE_T
#endif
// Mason Yu. todo
//#ifdef CONFIG_NF_CONNTRACK_L2TP
#if 1
XML_ENTRY_PRIMITIVE2("MIB_IP_ALG_L2TP", ipAlgL2TP, config_setting, "%hhu", config->ipAlgL2TP, MIB_IP_ALG_L2TP); //BYTE_T
#endif
#ifdef CONFIG_NF_CONNTRACK_IPSEC
XML_ENTRY_PRIMITIVE2("MIB_IP_ALG_IPSEC", ipAlgIPSEC, config_setting, "%hhu", config->ipAlgIPSEC, MIB_IP_ALG_IPSEC); //BYTE_T
#endif
#ifdef CONFIG_NF_CONNTRACK_SIP
XML_ENTRY_PRIMITIVE2("MIB_IP_ALG_SIP", ipAlgSIP, config_setting, "%hhu", config->ipAlgSIP, MIB_IP_ALG_SIP); //BYTE_T
#endif
#ifdef CONFIG_NF_CONNTRACK_PPTP
XML_ENTRY_PRIMITIVE2("MIB_IP_ALG_PPTP", ipAlgPPTP, config_setting, "%hhu", config->ipAlgPPTP, MIB_IP_ALG_PPTP); //BYTE_T
#endif
#endif

//add by ramen for DNS bind pvc
#ifdef DNS_BIND_PVC_SUPPORT
XML_ENTRY_PRIMITIVE2("MIB_DNS_BIND_ENABLE", dns1PvcEnable, config_setting, "%hhu", config->dns1PvcEnable, MIB_DNS_BIND_PVC_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("MIB_DNS_BIND_PVC1", dns1PvcIfIndex, config_setting, "%u", config->dns1PvcIfIndex, MIB_DNS_BIND_PVC1); //INTEGER_T
XML_ENTRY_PRIMITIVE2("MIB_DNS_BIND_PVC2", dns2PvcIfIndex, config_setting, "%u", config->dns2PvcIfIndex, MIB_DNS_BIND_PVC2); //INTEGER_T
XML_ENTRY_PRIMITIVE2("MIB_DNS_BIND_PVC3", dns3PvcIfIndex, config_setting, "%u", config->dns3PvcIfIndex, MIB_DNS_BIND_PVC3); //INTEGER_T
#endif

//alex for 802.1P
#ifdef QOS_SPEED_LIMIT_SUPPORT
XML_ENTRY_PRIMITIVE2("MIB_PVC_TOTAL_BANDWIDTH", upbandwidth, config_setting, "%u", config->upbandwidth, MIB_PVC_TOTAL_BANDWIDTH); //WORD_T
#endif	// QOS_SPEED_LIMIT_SUPPORT

#ifdef ADDRESS_MAPPING
#ifndef MULTI_ADDRESS_MAPPING
XML_ENTRY_PRIMITIVE2("ADDRESS_MAP_TYPE", addressMapType, config_setting, "%hhu", config->addressMapType, MIB_ADDRESS_MAP_TYPE); //WORD_T
XML_ENTRY_ADDR("LOCAL_START_IP", lsip, config_setting, config->lsip, MIB_LOCAL_START_IP); //IA_T
XML_ENTRY_ADDR("LOCAL_END_IP", leip, config_setting, config->leip, MIB_LOCAL_END_IP); //IA_T
XML_ENTRY_ADDR("GLOBAL_START_IP", gsip, config_setting, config->gsip, MIB_GLOBAL_START_IP); //IA_T
XML_ENTRY_ADDR("GLOBAL_END_IP", geip, config_setting, config->geip, MIB_GLOBAL_END_IP); //IA_T
#endif //end of !MULTI_ADDRESS_MAPPING
#endif	// ADDRESS_MAPPING

#ifdef CONFIG_USER_SAMBA
XML_ENTRY_PRIMITIVE2("MIB_SAMBA_ENABLE", samba_enable, config_setting, "%hhu", config->samba_enable, MIB_SAMBA_ENABLE); //BYTE_T
#ifdef CONFIG_USER_NMBD
XML_ENTRY_STRING2("MIB_SAMBA_NETBIOS_NAME", samba_netbios_name, config_setting, config->samba_netbios_name, MIB_SAMBA_NETBIOS_NAME); //STRING_T
#endif
XML_ENTRY_STRING2("WSCMIB_SAMBA_SERVER_STRING_PIN", samba_server_string, config_setting, config->samba_server_string, MIB_SAMBA_SERVER_STRING); //STRING_T
#endif

#ifdef ELAN_LINK_MODE_INTRENAL_PHY
XML_ENTRY_PRIMITIVE2("MIB_ETH_MODE", ethMode, config_setting, "%hhu", config->ethMode, MIB_ETH_MODE); //BYTE_T
#endif	// ELAN_LINK_MODE_INTRENAL_PHY

#ifdef SYSLOG_SUPPORT
#ifdef SEND_LOG
XML_ENTRY_ADDR("LOG_SERVER_IP", logServer, config_setting, config->logServer, MIB_LOG_SERVER_IP); //IA_T
XML_ENTRY_STRING2("LOG_SERVER_NAME", logNmae, config_setting, config->logNmae, MIB_LOG_SERVER_NAME); //STRING_T
XML_ENTRY_STRING2("SERVER_PASSWORD", logPassword, config_setting, config->logPassword, MIB_LOG_SERVER_PASSWORD); //STRING_T
#endif	// SEND_LOG
#endif	// SYSLOG_SUPPORT
//#ifdef QSETUP_WEB_REDIRECT
//XML_ENTRY_PRIMITIVE2("MIB_QSETUP_REDIRECT", startRedirect, config_setting, "%hhu", config->startRedirect); //BYTE_T
//#endif

#ifdef CONFIG_USER_SNMPD_SNMPD_V2CTRAP
XML_ENTRY_PRIMITIVE2("SNMPD_ENABLE", snmpdEnabled, config_setting, "%hhu", config->snmpdEnabled, MIB_SNMPD_ENABLE); //BYTE_T
#endif	// CONFIG_USER_SNMPD_SNMPD_V2CTRAP
#ifdef TCP_UDP_CONN_LIMIT
XML_ENTRY_PRIMITIVE2("CONNLIMIT_ENABLE", connlimitEn, config_setting, "%hhu", config->connlimitEn, MIB_CONNLIMIT_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("CONNLIMIT_UDP", connlimitUdp, config_setting, "%u", config->connlimitUdp, MIB_CONNLIMIT_UDP); //INTEGER_T
XML_ENTRY_PRIMITIVE2("CONNLIMIT_TCP", connlimitTcp, config_setting, "%u", config->connlimitTcp, MIB_CONNLIMIT_TCP); //INTEGER_T
#endif	// TCP_UDP_CONN_LIMIT

#ifdef WEB_REDIRECT_BY_MAC
XML_ENTRY_STRING2("WEB_REDIR_BY_MAC_URL", WebRedirByMACURL, config_setting, config->WebRedirByMACURL, MIB_WEB_REDIR_BY_MAC_URL); //STRING_T
XML_ENTRY_PRIMITIVE2("WEB_REDIR_BY_MAC_INTERVAL", landingPageTime, config_setting, "%u", config->landingPageTime, MIB_WEB_REDIR_BY_MAC_INTERVAL); //INTEGER_T
#endif	// WEB_REDIRECT_BY_MAC

#ifdef CONFIG_USB_ETH
XML_ENTRY_PRIMITIVE2("USBETH_ITF_GROUP", usbeth_itfgrp, config_setting, "%hhu", config->usbeth_itfgrp, MIB_USBETH_ITF_GROUP); //BYTE_T
#endif //CONFIG_USB_ETH
// Mason Yu. combine_1p_4p_PortMapping
#if (defined( ITF_GROUP_1P) && defined(ITF_GROUP))
XML_ENTRY_PRIMITIVE2("ETH_ITF_GROUP", ethitfGroup, config_setting, "%hhu", config->ethitfGroup, MIB_ETH_ITF_GROUP); //BYTE_T
#endif
#ifdef CONFIG_USER_DHCP_SERVER
XML_ENTRY_ADDR("DHCP_SUBNET_MASK", dhcpSubnetMask, config_setting, config->dhcpSubnetMask, MIB_DHCP_SUBNET_MASK); //IA_T
#endif

//ql 20090119 START: for imagenio service
#ifdef IMAGENIO_IPTV_SUPPORT
#if 0
XML_ENTRY_ADDR("OPCH_CH_ADDR", dhcpOpchAddr, config_setting, config->dhcpOpchAddr, MIB_OPCH_ADDRESS); //IA_T
XML_ENTRY_PRIMITIVE2("OPCH_CH_PORT", dhcpOpchPort, config_setting, "%hu", config->dhcpOpchPort, MIB_OPCH_PORT); //WORD_T
#endif
XML_ENTRY_ADDR("IMAGENIO_DNS1", imagenioDns1, config_setting, config->imagenioDns1, MIB_IMAGENIO_DNS1); //IA_T
XML_ENTRY_ADDR("IMAGENIO_DNS2", imagenioDns2, config_setting, config->imagenioDns2, MIB_IMAGENIO_DNS2); //IA_T
#endif	// IMAGENIO_IPTV_SUPPORT
//ql 20090119 END

#ifdef _SUPPORT_CAPTIVEPORTAL_PROFILE_
XML_ENTRY_PRIMITIVE2("CAPTIVEPORTAL_ENABLE", captivePortalEnable, config_setting, "%hhu", config->captivePortalEnable, MIB_CAPTIVEPORTAL_ENABLE); //BYTE_T
XML_ENTRY_STRING2("CAPTIVEPORTAL_URL", captivePortalURL, config_setting, config->captivePortalURL, MIB_CAPTIVEPORTAL_URL); //STRING_T
#endif	// _SUPPORT_CAPTIVEPORTAL_PROFILE_

#ifdef WLAN_QoS
XML_ENTRY_PRIMITIVE2("WLAN_APSD_ENABLE", wlanqos_apsd, config_setting, "%hhu", config->wlanqos_apsd, MIB_WLAN_APSD_ENABLE); //BYTE_T
#endif	// WLAN_QoS
#if defined(CONFIG_IPV6) && defined(CONFIG_USER_RADVD)
XML_ENTRY_STRING2("V6_MAXRTRADVINTERVAL", V6MaxRtrAdvInterval, config_setting, config->V6MaxRtrAdvInterval, MIB_V6_MAXRTRADVINTERVAL); //STRING_T
XML_ENTRY_STRING2("V6_MINRTRADVINTERVAL", V6MinRtrAdvInterval, config_setting, config->V6MinRtrAdvInterval, MIB_V6_MINRTRADVINTERVAL); //STRING_T
XML_ENTRY_STRING2("V6_ADVCURHOPLIMIT", V6AdvCurHopLimit, config_setting, config->V6AdvCurHopLimit, MIB_V6_ADVCURHOPLIMIT); //STRING_T
XML_ENTRY_STRING2("V6_ADVDEFAULTLIFETIME", V6AdvDefaultLifetime, config_setting, config->V6AdvDefaultLifetime, MIB_V6_ADVDEFAULTLIFETIME); //STRING_T
XML_ENTRY_STRING2("V6_ADVREACHABLETIME", V6AdvReachableTime, config_setting, config->V6AdvReachableTime, MIB_V6_ADVREACHABLETIME); //STRING_T
XML_ENTRY_STRING2("V6_ADVRETRANSTIMER", V6AdvRetransTimer, config_setting, config->V6AdvRetransTimer, MIB_V6_ADVRETRANSTIMER); //STRING_T
XML_ENTRY_STRING2("V6_ADVLINKMTU", V6AdvLinkMTU, config_setting, config->V6AdvLinkMTU, MIB_V6_ADVLINKMTU); //STRING_T
XML_ENTRY_STRING2("V6_PREFIX_IP", V6prefix_ip, config_setting, config->V6prefix_ip, MIB_V6_PREFIX_IP); //STRING_T
XML_ENTRY_STRING2("V6_PREFIX_LEN", V6prefix_len, config_setting, config->V6prefix_len, MIB_V6_PREFIX_LEN); //STRING_T
XML_ENTRY_STRING2("V6_VALIDLIFETIME", V6ValidLifetime, config_setting, config->V6ValidLifetime, MIB_V6_VALIDLIFETIME); //STRING_T
XML_ENTRY_STRING2("V6_PREFERREDLIFETIME", V6PreferredLifetime, config_setting, config->V6PreferredLifetime, MIB_V6_PREFERREDLIFETIME); //STRING_T
XML_ENTRY_PRIMITIVE2("V6_SENDADVERT", V6SendAdvert, config_setting, "%hhu", config->V6SendAdvert, MIB_V6_SENDADVERT); //BYTE_T
XML_ENTRY_PRIMITIVE2("V6_MANAGEDFLAG", V6ManagedFlag, config_setting, "%hhu", config->V6ManagedFlag, MIB_V6_MANAGEDFLAG); //BYTE_T
XML_ENTRY_PRIMITIVE2("V6_OTHERCONFIGFLAG", V6OtherConfigFlag, config_setting, "%hhu", config->V6OtherConfigFlag, MIB_V6_OTHERCONFIGFLAG); //BYTE_T
XML_ENTRY_PRIMITIVE2("V6_ONLINK", V6OnLink, config_setting, "%hhu", config->V6OnLink, MIB_V6_ONLINK); //BYTE_T
XML_ENTRY_PRIMITIVE2("V6_AUTONOMOUS", V6Autonomous, config_setting, "%hhu", config->V6Autonomous, MIB_V6_AUTONOMOUS); //BYTE_T
XML_ENTRY_PRIMITIVE2("V6_PREFIX_MODE", V6PrefixMode, config_setting, "%hhu", config->V6PrefixMode, MIB_V6_PREFIX_MODE); //BYTE_T
XML_ENTRY_PRIMITIVE2("V6_PREFIX_ENABLE", V6PrefixEnable, config_setting, "%hhu", config->V6PrefixEnable, MIB_V6_PREFIX_ENABLE); //BYTE_T
XML_ENTRY_STRING2("V6_RDNSS1", V6RDNSS1, config_setting, config->V6RDNSS1, MIB_V6_RDNSS1); //STRING_T
XML_ENTRY_STRING2("V6_RDNSS2", V6RDNSS2, config_setting, config->V6RDNSS2, MIB_V6_RDNSS2); //STRING_T
XML_ENTRY_PRIMITIVE2("V6_ULAPrefixEnable", V6ULAPrefixEnable, config_setting, "%hhu", config->V6ULAPrefixEnable, MIB_V6_ULAPREFIX_ENABLE); //BYTE_T
XML_ENTRY_STRING2("V6_ULAPREFIX", V6ULAPrefix, config_setting, config->V6ULAPrefix, MIB_V6_ULAPREFIX); //STRING_T
XML_ENTRY_STRING2("V6_ULAPREFIX_LEN", V6ULAPrefix_len, config_setting, config->V6ULAPrefix_len, MIB_V6_ULAPREFIX_LEN); //STRING_T
XML_ENTRY_STRING2("V6_ULAPREFIX_VALID_TIME", V6ULAPrefixValidLifetime, config_setting, config->V6ULAPrefixValidLifetime, MIB_V6_ULAPREFIX_VALID_TIME); //STRING_T
XML_ENTRY_STRING2("V6_ULAPREFIX_PREFER_TIME", V6ULAPrefixPreferredLifetime, config_setting, config->V6ULAPrefixPreferredLifetime, MIB_V6_ULAPREFIX_PREFER_TIME); //STRING_T
#endif	// defined(CONFIG_IPV6) && defined(CONFIG_USER_RADVD)

#ifdef CONFIG_IPV6
#ifdef CONFIG_USER_DHCPV6_ISC_DHCP411
XML_ENTRY_PRIMITIVE2("DHCPV6S_PREFIX_LENGTH", dhcpv6s_prefix_length, config_setting, "%hhu", config->dhcpv6s_prefix_length, MIB_DHCPV6S_PREFIX_LENGTH); //BYTE_T
XML_ENTRY_ADDR6("DHCPV6S_RANGE_START", dhcpv6s_range_start, config_setting, config->dhcpv6s_range_start, MIB_DHCPV6S_RANGE_START); //IA6_T
XML_ENTRY_ADDR6("DHCPV6S_RANGE_END", dhcpv6s_range_end, config_setting, config->dhcpv6s_range_end, MIB_DHCPV6S_RANGE_END); //IA6_T
XML_ENTRY_PRIMITIVE2("DHCPV6S_DEFAULT_LEASE", dhcpv6s_default_LTime, config_setting, "%u", config->dhcpv6s_default_LTime, MIB_DHCPV6S_DEFAULT_LEASE); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DHCPV6S_PREFERRED_LIFETIME", dhcpv6s_preferred_LTime, config_setting, "%u", config->dhcpv6s_preferred_LTime, MIB_DHCPV6S_PREFERRED_LIFETIME); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DHCPV6R_UPPER_IFINDEX", dhcpv6r_ifIndex, config_setting, "%u", config->dhcpv6r_ifIndex, MIB_DHCPV6R_UPPER_IFINDEX); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DHCPV6_MODE", dhcpv6_mode, config_setting, "%hhu", config->dhcpv6_mode, MIB_DHCPV6_MODE); //BYTE_T
XML_ENTRY_PRIMITIVE2("DHCPV6S_RENEW_TIME", dhcpv6s_renew_time, config_setting, "%u", config->dhcpv6s_renew_time, MIB_DHCPV6S_RENEW_TIME); //INTEGER_T
XML_ENTRY_PRIMITIVE2("DHCPV6S_REBIND_TIME", dhcpv6s_rebind_time, config_setting, "%u", config->dhcpv6s_rebind_time, MIB_DHCPV6S_REBIND_TIME); //INTEGER_T
XML_ENTRY_STRING2("DHCPV6S_CLIENT_DUID", dhcpv6s_clientID, config_setting, config->dhcpv6s_clientID, MIB_DHCPV6S_CLIENT_DUID); //STRING_T
#endif	// CONFIG_USER_DHCPV6_ISC_DHCP411

#ifdef CONFIG_USER_ECMH
XML_ENTRY_PRIMITIVE2("MLD_PROXY_DAEMON", mld_proxy_daemon, config_setting, "%hhu", config->mld_proxy_daemon, MIB_MLD_PROXY_DAEMON); //BYTE_T
XML_ENTRY_PRIMITIVE2("MLD_PROXY_EXT_ITF", mld_proxy_ext_itf, config_setting, "%u", config->mld_proxy_ext_itf, MIB_MLD_PROXY_EXT_ITF); //INTEGER_T
#endif

#ifdef DNSV6_BIND_PVC_SUPPORT
XML_ENTRY_PRIMITIVE2("MIB_DNSV6_BIND_ENABLE", dnsv6PvcEnable, config_setting, "%hhu", config->dnsv6PvcEnable, MIB_DNSV6_BIND_PVC_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("MIB_DNSV6_BIND_PVC1", dnsv61PvcIfIndex, config_setting, "%u", config->dnsv61PvcIfIndex, MIB_DNSV6_BIND_PVC1); //INTEGER_T
XML_ENTRY_PRIMITIVE2("MIB_DNSV6_BIND_PVC2", dnsv62PvcIfIndex, config_setting, "%u", config->dnsv62PvcIfIndex, MIB_DNSV6_BIND_PVC2); //INTEGER_T
XML_ENTRY_PRIMITIVE2("MIB_DNSV6_BIND_PVC3", dnsv63PvcIfIndex, config_setting, "%u", config->dnsv63PvcIfIndex, MIB_DNSV6_BIND_PVC3); //INTEGER_T
#endif
XML_ENTRY_PRIMITIVE2("DNSV6_MODE", dnsv6Mode, config_setting, "%hhu", config->dnsv6Mode, MIB_ADSL_WAN_DNSV6_MODE); //BYTE_T
XML_ENTRY_ADDR6("DNSV61", dnsv61, config_setting, config->dnsv61, MIB_ADSL_WAN_DNSV61); //IA6_T
XML_ENTRY_ADDR6("DNSV62", dnsv62, config_setting, config->dnsv62, MIB_ADSL_WAN_DNSV62); //IA6_T
XML_ENTRY_ADDR6("DNSV63", dnsv63, config_setting, config->dnsv63, MIB_ADSL_WAN_DNSV63); //IA6_T
XML_ENTRY_PRIMITIVE2("V6_IPF_OUT_ACTION", v6ipfOutAction, config_setting, "%hhu", config->v6ipfOutAction, MIB_V6_IPF_OUT_ACTION); //BYTE_T
XML_ENTRY_PRIMITIVE2("V6_IPF_IN_ACTION", v6ipfInAction, config_setting, "%hhu", config->v6ipfInAction, MIB_V6_IPF_IN_ACTION); //BYTE_T
XML_ENTRY_PRIMITIVE2("V6_IPV6_ENABLE", v6ipv6Enable, config_setting, "%hhu", config->v6ipv6Enable, MIB_V6_IPV6_ENABLE); //BYTE_T
#endif  // #ifdef CONFIG_IPV6

#ifdef CONFIG_TR_064
XML_ENTRY_PRIMITIVE2("TR064_ENABLED", tr064_enabled, config_setting, "%hhu", config->tr064_enabled, MIB_TR064_ENABLED); //BYTE_T
#endif

#ifdef CONFIG_LUNA
#if defined(CONFIG_GPON_FEATURE) || defined(CONFIG_EPON_FEATURE)
XML_ENTRY_PRIMITIVE2("PON_MODE", pon_mode, config_setting, "%u", config->pon_mode, MIB_PON_MODE);	//INTEGER_T
#endif

#ifdef CONFIG_RTK_RG_INIT
XML_ENTRY_PRIMITIVE2("MAC_BASED_TAG_DECISION", macBasedTagDecision, config_setting, "%hhu", config->macBasedTagDecision, MIB_MAC_BASED_TAG_DECISION); //BYTE_T
XML_ENTRY_PRIMITIVE2("LAN_VLAN_ID1", lan_vlan_id1, config_setting, "%u", config->lan_vlan_id1, MIB_LAN_VLAN_ID1); //INTEGER_T
XML_ENTRY_PRIMITIVE2("LAN_VLAN_ID2", lan_vlan_id2, config_setting, "%u", config->lan_vlan_id2, MIB_LAN_VLAN_ID2); //INTEGER_T
XML_ENTRY_PRIMITIVE2("LAN_PORT_MASK1", lan_port_mask1, config_setting, "%u", config->lan_port_mask1, MIB_LAN_PORT_MASK1); //INTEGER_T
XML_ENTRY_PRIMITIVE2("LAN_PORT_MASK2", lan_port_mask2, config_setting, "%u", config->lan_port_mask2, MIB_LAN_PORT_MASK2); //INTEGER_T
XML_ENTRY_PRIMITIVE2("LAN_IP_VERSION1", lan_ip_version1, config_setting, "%hhu", config->lan_ip_version1, MIB_LAN_IP_VERSION1); //BYTE_T
XML_ENTRY_PRIMITIVE2("LAN_IP_VERSION2", lan_ip_version2, config_setting, "%hhu", config->lan_ip_version2, MIB_LAN_IP_VERSION2); //BYTE_T
#ifdef CONFIG_IPV6
XML_ENTRY_PRIMITIVE2("LAN_IPV6_MODE1", lan_ipv6_mode1, config_setting, "%hhu", config->lan_ipv6_mode1, MIB_LAN_IPV6_MODE1); //BYTE_T
XML_ENTRY_PRIMITIVE2("LAN_IPV6_MODE2", lan_ipv6_mode2, config_setting, "%hhu", config->lan_ipv6_mode2, MIB_LAN_IPV6_MODE2); //BYTE_T
XML_ENTRY_ADDR6("LAN_IPV6_ADDR1", lan_ipv6_addr1, config_setting, config->lan_ipv6_addr1, MIB_LAN_IPV6_ADDR1); //IA6_T
XML_ENTRY_ADDR6("LAN_IPV6_ADDR2", lan_ipv6_addr2, config_setting, config->lan_ipv6_addr2, MIB_LAN_IPV6_ADDR2); //IA6_T
XML_ENTRY_PRIMITIVE2("LAN_IPV6_PREFIX_LEN1", lan_ipv6_prefix_len1, config_setting, "%hhu", config->lan_ipv6_prefix_len1, MIB_LAN_IPV6_PREFIX_LEN1); //BYTE_T
XML_ENTRY_PRIMITIVE2("LAN_IPV6_PREFIX_LEN2", lan_ipv6_prefix_len2, config_setting, "%hhu", config->lan_ipv6_prefix_len2, MIB_LAN_IPV6_PREFIX_LEN2); //BYTE_T
#endif
#endif

#if defined(CONFIG_EPON_FEATURE)
XML_ENTRY_STRING2("EPON_LOID", epon_loid, config_setting, config->epon_loid, MIB_EPON_LOID); //STRING_T
XML_ENTRY_STRING2("EPON_PASSWD",epon_loid_passwd, config_setting, config->epon_passwd, MIB_EPON_PASSWD); //STRING_T
#endif

#if defined(CONFIG_GPON_FEATURE)
XML_ENTRY_STRING2("GPON_PASSWD", gpon_passwd, config_setting, config->gpon_passwd, MIB_GPON_PASSWD);
XML_ENTRY_STRING2("GPON_SN", gpon_sn, config_setting, config->gpon_sn, MIB_GPON_SN);
XML_ENTRY_STRING2("GPON_LOID", gpon_loid, config_setting, config->gpon_loid, MIB_GPON_LOID); //STRING_T
XML_ENTRY_STRING2("GPON_LOID_PASSWD", gpon_loid_passwd, config_setting, config->gpon_loid_passwd, MIB_GPON_LOID_PASSWD);
#endif

XML_ENTRY_PRIMITIVE2("DHCP_PORT_FILTER", dhcpPortFilter, config_setting, "%hu", config->dhcpPortFilter, MIB_DHCP_PORT_FILTER); //WORD_T

#ifdef CONFIG_DSL_VTUO
/* channel profile */
XML_ENTRY_PRIMITIVE2("VTUO_CHAN_DS_NDR_MAX", ChanDSNDRMax, config_setting, "%u", config->ChanDSNDRMax, VTUO_CHAN_DS_NDR_MAX); //DWORD_T
XML_ENTRY_PRIMITIVE2("VTUO_CHAN_DS_NDR_MIN", ChanDSNDRMin, config_setting, "%u", config->ChanDSNDRMin,	VTUO_CHAN_DS_NDR_MIN); //DWORD_T
XML_ENTRY_PRIMITIVE2("VTUO_CHAN_DS_MAX_DELAY", ChanDSMaxDelay, config_setting, "%hhu", config->ChanDSMaxDelay, VTUO_CHAN_DS_MAX_DELAY); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_CHAN_DS_MIN_INP", ChanDSMinINP, config_setting, "%hhu", config->ChanDSMinINP,  VTUO_CHAN_DS_MIN_INP); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_CHAN_DS_MIN_INP8", ChanDSMinINP8, config_setting, "%hhu", config->ChanDSMinINP8, VTUO_CHAN_DS_MIN_INP8); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_CHAN_DS_SOS_MDR", ChanDSSosMDR, config_setting, "%u", config->ChanDSSosMDR, VTUO_CHAN_DS_SOS_MDR); //DWORD_T

XML_ENTRY_PRIMITIVE2("VTUO_CHAN_US_NDR_MAX", ChanUSNDRMax, config_setting, "%u", config->ChanUSNDRMax,	VTUO_CHAN_US_NDR_MAX); //DWORD_T
XML_ENTRY_PRIMITIVE2("VTUO_CHAN_US_NDR_MIN", ChanUSNDRMin, config_setting, "%u", config->ChanUSNDRMin, VTUO_CHAN_US_NDR_MIN); //DWORD_T
XML_ENTRY_PRIMITIVE2("VTUO_CHAN_US_MAX_DELAY", ChanUSMaxDelay, config_setting, "%u", config->ChanUSMaxDelay, VTUO_CHAN_US_MAX_DELAY); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_CHAN_US_MIN_INP", ChanUSMinINP, config_setting, "%hhu", config->ChanUSMinINP, VTUO_CHAN_US_MIN_INP); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_CHAN_US_MIN_INP8", ChanUSMinINP8, config_setting, "%hhu", config->ChanUSMinINP8, VTUO_CHAN_US_MIN_INP8); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_CHAN_US_SOS_MDR", ChanUSSosMDR, config_setting, "%u", config->ChanUSSosMDR, VTUO_CHAN_US_SOS_MDR); //DWORD_T

/*ginp setup*/
XML_ENTRY_PRIMITIVE2("VTUO_GINP_DS_MODE", GinpDSMode, config_setting, "%hhu", config->GinpDSMode, VTUO_GINP_DS_MODE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_DS_ET_MAX", GinpDSETMax, config_setting, "%u", config->GinpDSETMax, VTUO_GINP_DS_ET_MAX); //DWORD_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_DS_ET_MIN", GinpDSETMin, config_setting, "%u", config->GinpDSETMin,	VTUO_GINP_DS_ET_MIN); //); //
XML_ENTRY_PRIMITIVE2("VTUO_GINP_DS_NDR_MAX", GinpDSNDRMax, config_setting, "%u", config->GinpDSNDRMax, VTUO_GINP_DS_NDR_MAX); //DWORD_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_DS_SHINE_RATIO", GinpDSShineRatio, config_setting, "%hu", config->GinpDSShineRatio, VTUO_GINP_DS_SHINE_RATIO); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_DS_LEFTR_THRD", GinpDSLeftrThrd, config_setting, "%hhu", config->GinpDSLeftrThrd, VTUO_GINP_DS_LEFTR_THRD); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_DS_MAX_DELAY", GinpDSMaxDelay, config_setting, "%hhu", config->GinpDSMaxDelay, VTUO_GINP_DS_MAX_DELAY); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_DS_MIN_DELAY", GinpDSMinDelay, config_setting, "%hhu", config->GinpDSMinDelay, VTUO_GINP_DS_MIN_DELAY); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_DS_MIN_INP", GinpDSMinINP, config_setting, "%hhu", config->GinpDSMinINP, VTUO_GINP_DS_MIN_INP); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_DS_REIN_SYM", GinpDSReinSym, config_setting, "%hhu", config->GinpDSReinSym, VTUO_GINP_DS_REIN_SYM); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_DS_REIN_FREQ", GinpDSReinFreq, config_setting, "%hhu", config->GinpDSReinFreq, VTUO_GINP_DS_REIN_FREQ); //BYTE_T

XML_ENTRY_PRIMITIVE2("VTUO_GINP_US_MODE", GinpUSMode, config_setting, "%hhu", config->GinpUSMode, VTUO_GINP_US_MODE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_US_ET_MAX", GinpUSETMax, config_setting, "%u", config->GinpUSETMax, VTUO_GINP_US_ET_MAX); //DWORD_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_US_ET_MIN", GinpUSETMin, config_setting, "%u", config->GinpUSETMin,	VTUO_GINP_US_ET_MIN); //DWORD_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_US_NDR_MAX", GinpUSNDRMax,  config_setting,	"%u", config->GinpUSNDRMax, VTUO_GINP_US_NDR_MAX); //DWORD_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_US_SHINE_RATIO", GinpUSShineRatio, config_setting, "%hu", config->GinpUSShineRatio,	VTUO_GINP_US_SHINE_RATIO); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_US_LEFTR_THRD", GinpUSLeftrThrd, config_setting, "%hhu", config->GinpUSLeftrThrd, VTUO_GINP_US_LEFTR_THRD); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_US_MAX_DELAY", GinpUSMaxDelay, config_setting, "%hhu", config->GinpUSMaxDelay, VTUO_GINP_US_MAX_DELAY); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_US_MIN_DELAY", GinpUSMinDelay, config_setting, "%hhu", config->GinpUSMinDelay, VTUO_GINP_US_MIN_DELAY); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_US_MIN_INP", GinpUSMinINP, config_setting, "%hhu", config->GinpUSMinINP, VTUO_GINP_US_MIN_INP); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_US_REIN_SYM", GinpUSReinSym, config_setting, "%hhu", config->GinpUSReinSym, VTUO_GINP_US_REIN_SYM); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_GINP_US_REIN_FREQ", GinpUSReinFreq, config_setting, "%hhu", config->GinpUSReinFreq, VTUO_GINP_US_REIN_FREQ); //BYTE_T

/* line profile */
XML_ENTRY_PRIMITIVE2("VTUO_LINE_VDSL2_PROFILE", LineVd2Profile, config_setting, "%hu", config->LineVd2Profile, VTUO_LINE_VDSL2_PROFILE); //WORD_T
/*
XML_ENTRY_PRIMITIVE2("VTUO_LINE_TRANS_MODE", LineTransMode, config_setting, "%hhu", config->LineTransMode, VTUO_LINE_TRANS_MODE); //BYTE_T
*/
XML_ENTRY_PRIMITIVE2("VTUO_LINE_ADSL_PROTOCOL", LineAdProtocol, config_setting, "%u", config->LineAdProtocol, VTUO_LINE_ADSL_PROTOCOL); //DWORD_T
/*
XML_ENTRY_PRIMITIVE2("VTUO_LINE_CLASS_MASK", LineClasMask, config_setting, "%hhu", config->LineClasMask, VTUO_LINE_CLASS_MASK); //BYTE_T
*/
XML_ENTRY_PRIMITIVE2("VTUO_LINE_LIMIT_MASK", LineLimitMask, config_setting, "%hhu", config->LineLimitMask, VTUO_LINE_LIMIT_MASK); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_US0_MASK", LineUs0Mask, config_setting, "%hhu", config->LineUs0Mask, VTUO_LINE_US0_MASK); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_UPBO_ENABLE", LineUpboEnable, config_setting, "%hhu", config->LineUpboEnable, VTUO_LINE_UPBO_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_UPBOKL", LineUpboKl, config_setting, "%hu", config->LineUpboKl, VTUO_LINE_UPBOKL); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_UPBO_1A", LineUpbo1a, config_setting, "%hu", config->LineUpbo1a, VTUO_LINE_UPBO_1A); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_UPBO_2A", LineUpbo2a, config_setting, "%hu", config->LineUpbo2a, VTUO_LINE_UPBO_2A); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_UPBO_3A", LineUpbo3a, config_setting, "%hu", config->LineUpbo3a, VTUO_LINE_UPBO_3A); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_UPBO_4A", LineUpbo4a, config_setting, "%hu", config->LineUpbo4a, VTUO_LINE_UPBO_4A); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_UPBO_1B", LineUpbo1b, config_setting, "%hu", config->LineUpbo1b, VTUO_LINE_UPBO_1B); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_UPBO_2B", LineUpbo2b, config_setting, "%hu", config->LineUpbo2b, VTUO_LINE_UPBO_2B); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_UPBO_3B", LineUpbo3b, config_setting, "%hu", config->LineUpbo3b, VTUO_LINE_UPBO_3B); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_UPBO_4B", LineUpbo4b, config_setting, "%hu", config->LineUpbo4b, VTUO_LINE_UPBO_4B); //WORD_T
/*
XML_ENTRY_PRIMITIVE2("VTUO_LINE_RT_MODE", LineRtMode, config_setting, "%hhu", config->LineRtMode, VTUO_LINE_RT_MODE); //BYTE_T
*/
XML_ENTRY_PRIMITIVE2("VTUO_LINE_US0_ENABLE", LineUs0Enable, config_setting, "%hhu", config->LineUs0Enable, VTUO_LINE_US0_ENABLE); //BYTE_T
/*
XML_ENTRY_PRIMITIVE2("VTUO_LINE_DS_MAX_SNR_NOLMT", LineDSMaxSNRNoLmt, config_setting, "%hhu", config->LineDSMaxSNRNoLmt, VTUO_LINE_DS_MAX_SNR_NOLMT); //BYTE_T
*/
XML_ENTRY_PRIMITIVE2("VTUO_LINE_DS_MAX_SNR", LineDSMaxSNR, config_setting, "%hu", config->LineDSMaxSNR,	VTUO_LINE_DS_MAX_SNR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_DS_TARGET_SNR", LineDSTargetSNR, config_setting, "%hu", config->LineDSTargetSNR, VTUO_LINE_DS_TARGET_SNR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_DS_MIN_SNR", LineDSMinSNR, config_setting, "%hu", config->LineDSMinSNR,	VTUO_LINE_DS_MIN_SNR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_DS_BITSWAP", LineDSBitswap, config_setting, "%hhu", config->LineDSBitswap, VTUO_LINE_DS_BITSWAP); //BYTE_T
/*
XML_ENTRY_PRIMITIVE2("VTUO_LINE_DS_MAX_TXPWR", LineDSMaxTXPwr, config_setting, "%hu", config->LineDSMaxTXPwr, VTUO_LINE_DS_MAX_TXPWR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_DS_MIN_OH_RATE", LineDSMinOhRate, config_setting, "%hu", config->LineDSMinOhRate, VTUO_LINE_DS_MIN_OH_RATE); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_US_MAX_SNR_NOLMT", LineUSMaxSNRNoLmt, config_setting, "%hhu", config->LineUSMaxSNRNoLmt, VTUO_LINE_US_MAX_SNR_NOLMT); //BYTE_T
*/
XML_ENTRY_PRIMITIVE2("VTUO_LINE_US_MAX_SNR", LineUSMaxSNR, config_setting, "%hu", config->LineUSMaxSNR,	VTUO_LINE_US_MAX_SNR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_US_TARGET_SNR", LineUSTargetSNR, config_setting, "%hu", config->LineUSTargetSNR, VTUO_LINE_US_TARGET_SNR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_US_MIN_SNR", LineUSMinSNR, config_setting, "%hu", config->LineUSMinSNR, VTUO_LINE_US_MIN_SNR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_US_BITSWAP", LineUSBitswap, config_setting, "%hhu", config->LineUSBitswap, VTUO_LINE_US_BITSWAP); //BYTE_T
/*
XML_ENTRY_PRIMITIVE2("VTUO_LINE_US_MAX_RXPWR_NOLMT", LineUSMaxRxPwrNoLmt, config_setting, "%hhu", config->LineUSMaxRxPwrNoLmt, VTUO_LINE_US_MAX_RXPWR_NOLMT); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_US_MAX_RXPWR", LineUSMaxRXPwr, config_setting, "%hu", config->LineUSMaxRXPwr, VTUO_LINE_US_MAX_RXPWR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_US_MAX_TXPWR", LineUSMaxTXPwr, config_setting, "%hu", config->LineUSMaxTXPwr, VTUO_LINE_US_MAX_TXPWR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_LINE_US_MIN_OH_RATE", LineUSMinOhRate, config_setting, "%hu", config->LineUSMinOhRate, VTUO_LINE_US_MIN_OH_RATE); //WORD_T
*/
/* inm profile */
XML_ENTRY_PRIMITIVE2("VTUO_INM_NE_INP_EQ_MODE", InmNEInpEqMode, config_setting, "%hhu", config->InmNEInpEqMode, VTUO_INM_NE_INP_EQ_MODE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_INM_NE_INMCC", InmNEInmCc, config_setting, "%hhu", config->InmNEInmCc, VTUO_INM_NE_INMCC); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_INM_NE_IAT_OFFSET", InmNEIatOffset, config_setting, "%hhu", config->InmNEIatOffset, VTUO_INM_NE_IAT_OFFSET); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_INM_NE_IAT_SETUP", InmNEIatSetup, config_setting, "%hhu", config->InmNEIatSetup, VTUO_INM_NE_IAT_SETUP); //BYTE_T
/*
XML_ENTRY_PRIMITIVE2("VTUO_INM_NE_ISDD_SEN", InmNEIsddSen, config_setting, "%hu", config->InmNEIsddSen,	VTUO_INM_NE_ISDD_SEN); //WORD_T
*/
XML_ENTRY_PRIMITIVE2("VTUO_INM_FE_INP_EQ_MODE", InmFEInpEqMode, config_setting, "%hhu", config->InmFEInpEqMode, VTUO_INM_FE_INP_EQ_MODE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_INM_FE_INMCC", InmFEInmCc, config_setting,"%hhu", config->InmFEInmCc, VTUO_INM_FE_INMCC); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_INM_FE_IAT_OFFSET", InmFEIatOffset, config_setting, "%hhu", config->InmFEIatOffset, VTUO_INM_FE_IAT_OFFSET); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_INM_FE_IAT_SETUP", InmFEIatSetup, config_setting, "%hhu", config->InmFEIatSetup, VTUO_INM_FE_IAT_SETUP); //BYTE_T
/*
XML_ENTRY_PRIMITIVE2("VTUO_INM_FE_ISDD_SEN", InmFEIsddSen, config_setting, "%hu", config->InmFEIsddSen,	VTUO_INM_FE_ISDD_SEN); //WORD_T
*/
/* sra setup */
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_RA_MODE", SraDSRAMode, config_setting, "%hhu", config->SraDSRAMode, VTUO_SRA_DS_RA_MODE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_DYNAMIC_DEPTH", SraDSDynDepth, config_setting, "%hhu", config->SraDSDynDepth, VTUO_SRA_DS_DYNAMIC_DEPTH); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_USHIFT_SNR", SraDSUpSftSNR, config_setting, "%hu", config->SraDSUpSftSNR, VTUO_SRA_DS_USHIFT_SNR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_USHIFT_TIME", SraDSUpSftTime, config_setting, "%hu", config->SraDSUpSftTime, VTUO_SRA_DS_USHIFT_TIME); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_DSHIFT_SNR", SraDSDownSftSNR, config_setting, "%hu", config->SraDSDownSftSNR, VTUO_SRA_DS_DSHIFT_SNR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_DSHIFT_TIME",	SraDSDownSftTime, config_setting, "%hu", config->SraDSDownSftTime, VTUO_SRA_DS_DSHIFT_TIME); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_SOS_TIME", SraDSSosTime, config_setting, "%hu", config->SraDSSosTime,	VTUO_SRA_DS_SOS_TIME); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_SOS_CRC", SraDSSosCRC, config_setting, "%hu", config->SraDSSosCRC, VTUO_SRA_DS_SOS_CRC); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_SOS_NTONE", SraDSSosnTone, config_setting, "%hhu", config->SraDSSosnTone, VTUO_SRA_DS_SOS_NTONE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_SOS_MAX", SraDSSosMax, config_setting, "%hhu", config->SraDSSosMax, VTUO_SRA_DS_SOS_MAX); //BYTE_T
/*
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_SOS_MSTEP_TONE", SraDSSosMStepTone, config_setting, "%hhu", config->SraDSSosMStepTone, VTUO_SRA_DS_SOS_MSTEP_TONE); //BYTE_T
*/
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_ROC_ENABLE", SraDSRocEnable, config_setting, "%hhu", config->SraDSRocEnable, VTUO_SRA_DS_ROC_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_ROC_SNR", SraDSRocSNR, config_setting, "%hu", config->SraDSRocSNR, VTUO_SRA_DS_ROC_SNR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_DS_ROC_MIN_INP", SraDSRocMinInp, config_setting, "%hhu", config->SraDSRocMinInp, VTUO_SRA_DS_ROC_MIN_INP); //BYTE_T

XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_RA_MODE", SraUSRAMode, config_setting, "%hhu", config->SraUSRAMode, VTUO_SRA_US_RA_MODE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_DYNAMIC_DEPTH", SraUSDynDepth, config_setting, "%hhu", config->SraUSDynDepth, VTUO_SRA_US_DYNAMIC_DEPTH); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_USHIFT_SNR", SraUSUpSftSNR, config_setting, "%hu", config->SraUSUpSftSNR, VTUO_SRA_US_USHIFT_SNR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_USHIFT_TIME",	SraUSUpSftTime, config_setting, "%hu", config->SraUSUpSftTime, VTUO_SRA_US_USHIFT_TIME); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_DSHIFT_SNR", SraUSDownSftSNR, config_setting, "%hu", config->SraUSDownSftSNR, VTUO_SRA_US_DSHIFT_SNR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_DSHIFT_TIME", SraUSDownSftTime, config_setting, "%hu", config->SraUSDownSftTime, VTUO_SRA_US_DSHIFT_TIME); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_SOS_TIME", SraUSSosTime, config_setting, "%hu", config->SraUSSosTime,	VTUO_SRA_US_SOS_TIME); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_SOS_CRC", SraUSSosCRC, config_setting, "%hu", config->SraUSSosCRC, VTUO_SRA_US_SOS_CRC); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_SOS_NTONE", SraUSSosnTone, config_setting, "%hhu", config->SraUSSosnTone, VTUO_SRA_US_SOS_NTONE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_SOS_MAX", SraUSSosMax, config_setting, "%hhu", config->SraUSSosMax, VTUO_SRA_US_SOS_MAX); //BYTE_T
/*
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_SOS_MSTEP_TONE", SraUSSosMStepTone, config_setting, "%hhu", config->SraUSSosMStepTone, VTUO_SRA_US_SOS_MSTEP_TONE); //BYTE_T
*/
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_ROC_ENABLE", SraUSRocEnable, config_setting, "%hhu", config->SraUSRocEnable, VTUO_SRA_US_ROC_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_ROC_SNR", SraUSRocSNR, config_setting, "%hu", config->SraUSRocSNR, VTUO_SRA_US_ROC_SNR); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_SRA_US_ROC_MIN_INP", SraUSRocMinInp, config_setting,	 "%hhu", config->SraUSRocMinInp, VTUO_SRA_US_ROC_MIN_INP); //BYTE_T

/*DPBO*/
XML_ENTRY_PRIMITIVE2("VTUO_DPBO_ENABLE", DpboEnable, config_setting,  "%hhu", config->DpboEnable, VTUO_DPBO_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_DPBO_ESEL", DpboEsel, config_setting, "%hu", config->DpboEsel, VTUO_DPBO_ESEL); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_DPBO_ESCMA", DpboEscma, config_setting, "%d", config->DpboEscma,	VTUO_DPBO_ESCMA); //INTEGER_T
XML_ENTRY_PRIMITIVE2("VTUO_DPBO_ESCMB", DpboEscmb, config_setting, "%d", config->DpboEscmb,	VTUO_DPBO_ESCMB); //INTEGER_T
XML_ENTRY_PRIMITIVE2("VTUO_DPBO_ESCMC", DpboEscmc, config_setting, "%d", config->DpboEscmc,	VTUO_DPBO_ESCMC); //INTEGER_T
XML_ENTRY_PRIMITIVE2("VTUO_DPBO_MUS", DpboMus, config_setting, "%hu", config->DpboMus,	VTUO_DPBO_MUS); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_DPBO_FMIN", DpboFmin, config_setting, "%hu", config->DpboFmin, VTUO_DPBO_FMIN); //WORD_T
XML_ENTRY_PRIMITIVE2("VTUO_DPBO_FMAX", DpboFmax, config_setting, "%hu", config->DpboFmax, VTUO_DPBO_FMAX); //WORD_T

/*VN*/
/*
XML_ENTRY_PRIMITIVE2("VTUO_VN_DS_ENABLE", VnDSEnable, config_setting, "%hhu", config->VnDSEnable,  VTUO_VN_DS_ENABLE); //BYTE_T
XML_ENTRY_PRIMITIVE2("VTUO_VN_US_ENABLE", VnUSEnable, config_setting, "%hhu", config->VnUSEnable,  VTUO_VN_US_ENABLE); //BYTE_T
*/
#endif /*CONFIG_DSL_VTUO*/

#endif

