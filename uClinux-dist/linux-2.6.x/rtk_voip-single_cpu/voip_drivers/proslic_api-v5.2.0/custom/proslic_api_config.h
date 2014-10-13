/*
** Copyright ? 2007 by Silicon Laboratories
**
** $Id: proslic_api_config.h,v 1.1 2012/08/21 09:43:18 krammer Exp $
**
**
** Author(s): 
** laj
**
** Distributed by: 
** Silicon Laboratories, Inc
**
** This file contains proprietary information.	 
** No dissemination allowed without prior written permission from
** Silicon Laboratories, Inc.
**
**
*/



#define DISABLE_DTMF_SETUP 
/*#define DISABLE_FSK_SETUP  */
/*#define DISABLE_TONE_SETUP  */
/*#define DISABLE_RING_SETUP  */
/*#define DISABLE_AUDIOGAIN_SETUP  */
/*#define DISABLE_DCFEED_SETUP  */
/*#define DISABLE_GPIO_SETUP  */
/*#define DISABLE_PCM_SETUP  */
#define ENABLE_DEBUG 
/*#define DISABLE_CI_SETUP  */
/*#define DISABLE_ZSYNTH_SETUP  */
#define DISABLE_MALLOC //[THLin change]
/*#define GCI_MODE  */

//#include "stdio.h" //[THLin change]
/*#if (PRINT_TO_STRING) */
/*extern char outputBuffer[]; */
/*#define LOGPRINT(...) sprintf(&(outputBuffer[strlen(outputBuffer)]),__VA_ARGS__) */
/*#else */
#include <linux/kernel.h>	// required by printk()
#define LOGPRINT printk //[THLin change]
/*#endif */

#ifndef PROSLIC_API_CFG
#define PROSLIC_API_CFG



#endif
