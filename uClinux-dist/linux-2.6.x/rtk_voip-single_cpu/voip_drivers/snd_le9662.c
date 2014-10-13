#include "rtk_voip.h"
#include "voip_init.h"

#include "con_register.h"
//#include "con_defer_init.h"
#include "snd_pin_cs.h"
//#include "snd_help_ipc.h"
#include "snd_zarlink_ioc_op.h"

#include "zarlink_int.h"
#include "zarlink_api.h"

#include "gpio.h"
#include "spi.h"
static voip_snd_t			snd_zarlink_le9662[2*CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR];
static rtl_spi_dev_t		spi_dev_le9662[CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR];
/*
** Realtek memory space that API-2 requires 
** for the Device/Line contexts and objects
*/
static RTKDevObj	  	  	DevObj_le9662[CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR]; //
static RTKLineObj	  	  	LineObj_le9662[2*CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR]; //2FXS

/*
** Application memory space that API-2 requires 
** for the Device/Line contexts and objects
*/
static Vp886DeviceObjectType  VpDevObj_le9662[CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR];
static Vp886LineObjectType    VpLineObj_le9662[2*CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR];

static VpDevCtxType           VpDevCtx_le9662[CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR];

static VpLineCtxType          VpLineCtx_le9662[2*CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR];

#if 1
static const uint32 * const pin_cs_le9662 = 
		&snd_pin_cs[ CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_PIN_CS - 1 ];
#else
static uint32 pin_cs_le9662[] = {
#if !defined( CONFIG_RTK_VOIP_DRIVERS_SLIC_LE89116 ) && !defined( CONFIG_RTK_VOIP_DRIVERS_SLIC_LE89316 )
	PIN_CS1,
	PIN_CS2,
#endif
	PIN_CS3,
	PIN_CS4,
};

#define NUM_OF_PIN_CS_LE9662		( sizeof( pin_cs_le9662 ) / sizeof( pin_cs_le9662[ 0 ] ) )

CT_ASSERT( NUM_OF_PIN_CS_LE9662 >= CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR );
#endif

static int SLIC_init_le9662(int pcm_mode, int initonly)
{
	int i;
	RTKDevObj *pDev;
	int PcnType;
   	int rtn;
   	//int ch;



	PRINT_MSG("================================================\n");
	PRINT_MSG("Zarlink API-II Lite Version %d.%d.%d\n", 
				VP_API_VERSION_MAJOR_NUM, 
				VP_API_VERSION_MINOR_NUM, 
				VP_API_VERSION_MINI_NUM);
			
	if( initonly )
		goto label_do_init_only;

	/* ******************* */
	/* Init Realtek obj    */
	/* ******************* */
	// setup GPIO for SPI 
	for( i = 0; i < CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR; i ++ ) {
		//PRINT_MSG( "le9662[%d] CS=%08X\n", i, 0 );
		//_init_rtl_spi_dev_type_hw( &spi_dev_le9662[ i ], 0);
		#ifdef CONFIG_RTK_VOIP_8676_SHARED_SPI
		PRINT_MSG( "le9662[%d] CS=%08X\n", i, CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_PIN_CS + i);
		init_spi_pins( &spi_dev_le9662[ i ], CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_PIN_CS + i, PIN_CLK, PIN_DO, PIN_DI);
		#else
		PRINT_MSG( "le9662[%d] CS=%08X\n", i, pin_cs_le9662[ i ] );
		init_spi_pins( &spi_dev_le9662[ i ], pin_cs_le9662[ i ], PIN_CLK, PIN_DO, PIN_DI);
		#endif
	}
	// Create Dev & Line Object 
	for( i = 0; i < CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR; i ++ ) {
		Ve886CreateDevObj( 
			DEV_FXSFXS, 0, 
			&DevObj_le9662[ i ], &LineObj_le9662[ i * 2 ],
			&spi_dev_le9662[ i ], VP_DEV_886_SERIES,
			&VpDevObj_le9662[ i ], &VpDevCtx_le9662[ i ],
			&VpLineObj_le9662[ i * 2 ], &VpLineCtx_le9662[ i * 2 ]);

		/* FXS */
		Ve886CreateLineObj( rtkGetNewChID(),   0, LINE_FXS, DevObj_le9662[ i ].pLine[0], 
							pcm_mode, snd_zarlink_le9662[ i * 2 ].TS1 );
							//pcm_mode, snd_zarlink_le9662[ i ].TS1 );
		/* FXS */
		Ve886CreateLineObj( rtkGetNewChID(), 1, LINE_FXS, DevObj_le9662[ i ].pLine[1], 
							pcm_mode, snd_zarlink_le9662[ i * 2 + 1 ].TS1 );
	}
	
label_do_init_only:

	/* ******************* */
	/* Init Zarlink API-II */
	/* ******************* */
	for( i = 0; i < CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR; i ++ ) 
	{
		/* deviceId imply spi device id */
		pDev = &DevObj_le9662[ i ];
		PcnType = Ve886GetRev( pDev );

		if ( PcnType == FAILED ) {
			PRINT_R("Error (%d:x) %s Read version fail\n", i, __FUNCTION__);
			return FAILED;
		}

		/* Initialize API-2 device settings */
		rtn = zarlinkInitDevice( pDev );
		if ( rtn == FAILED ) {
			PRINT_R("Error (%d:x) %s\n", i, __FUNCTION__);
			return FAILED;
		}	
	}

	
	return SUCCESS;
}

static void SLIC_reset_le9662( voip_snd_t *this, int codec_law )
{
	extern int law;	// FIXME: chmap 
	
	SLIC_init_le9662( law, 1 /* init only */ );
}

static void SLIC_show_ID_le9662( voip_snd_t *this )
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	RTKDevObj * const pDev = pLine ->pDev;
	
	Ve886GetRev( pDev );
}

// --------------------------------------------------------
// channel mapping architecture 
// --------------------------------------------------------
__attribute__ ((section(".snd_desc_data")))
static snd_ops_fxs_t snd_le9662_fxs_ops;

static void __init fill_le9662_register_info( 
	voip_snd_t snd_zarlink_le9662[],
	int n_fxs, int m_daa, uint16 TS_base,
	RTKLineObj LineObj_le9662[] 
	)
{
	// once call this function:
	//  - one control interface 
	//  - n fxs
	//  - m daa 
	int sch;
	int daa = 0;
	
	for( sch = 0; sch < n_fxs + m_daa; sch ++ ) {
	
		if( sch == n_fxs )
			daa = 1;

		snd_zarlink_le9662[ sch ].sch = sch;
		snd_zarlink_le9662[ sch ].name = "le9662";
		snd_zarlink_le9662[ sch ].snd_type = SND_TYPE_FXS;
		snd_zarlink_le9662[ sch ].bus_type_sup = BUS_TYPE_PCM;
		snd_zarlink_le9662[ sch ].TS1 = TS_base + sch * 2;
#ifdef CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_WIDEBAND
		snd_zarlink_le9662[ sch ].TS2 = ( daa || TS_base + sch * 2 >= 16 ? 0 : TS_base + ( sch + 8 ) * 2 );
		snd_zarlink_le9662[ sch ].band_mode_sup = ( daa ? BAND_MODE_8K : BAND_MODE_8K | BAND_MODE_16K );
#else
		snd_zarlink_le9662[ sch ].TS2 = 0;
		snd_zarlink_le9662[ sch ].band_mode_sup = BAND_MODE_8K;
#endif
	//	snd_zarlink_le9662[ 0 ].TS1 = 4;
	//	snd_zarlink_le9662[ 1 ].TS1 = 2;
		snd_zarlink_le9662[ sch ].snd_ops = ( const snd_ops_t * )&snd_le9662_fxs_ops;
		snd_zarlink_le9662[ sch ].priv = &LineObj_le9662[ sch ];
		
		// DAA port  
		if( daa ) {
			snd_zarlink_le9662[ sch ].snd_type = SND_TYPE_DAA;
#if 0
			snd_zarlink_le9662[ sch ].snd_ops = ( const snd_ops_t * )&snd_zarlink_daa_ops;
#else
			printk( "No snd_ops for DAA!!\n" );
#endif
		}		
	}
}

static int __init voip_snd_zarlink_init_le9662( void )
{
	extern int law;	// FIXME: chmap 
	extern const snd_ops_fxs_t snd_zarlink_fxs_ops;
	int i;//, sch, daa;
	int TS_base, TS_cur;
	int rtn;
#ifdef CONFIG_RTK_VOIP_DEFER_SNDDEV_INIT
	static defer_init_t le9662_defer;
#endif
	
	// le9662 override proslic base ops 
	snd_le9662_fxs_ops = snd_zarlink_fxs_ops;

	snd_le9662_fxs_ops.SLIC_reset = SLIC_reset_le9662;
	snd_le9662_fxs_ops.SLIC_show_ID = SLIC_show_ID_le9662;
	
	// get TS base 
	TS_base = get_snd_free_timeslot();
	if( TS_base < 0 )
		TS_base = 0;
	
	TS_cur = TS_base;
	// common port definition 
	for( i = 0; i < CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR; i ++ ) {
		
		fill_le9662_register_info( &snd_zarlink_le9662[ i * 2 ], 
				2 /* fxs */, 0 /* daa */, (uint16)TS_cur,
				&LineObj_le9662[ i * 2 ] );
#ifdef CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_OWNER_ALL_DSP
		if( fill_ipc_dsp_cpuid( &snd_zarlink_le9662[ i ], 
				1 /* fxs */, 0 /* daa */, 
				i, 
				SND_PER_DSPCPU( CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR, 
								CONFIG_RTK_VOIP_DSP_DEVICE_NR ) ) )
		{
			TS_cur = TS_base;
		} else
#endif
		{
			TS_cur += 2;
		}
		
		//TS_base += 4;
	}
	
	// SLIC init use ops 
#ifdef CONFIG_RTK_VOIP_DEFER_SNDDEV_INIT
	le9662_defer.fn_defer_func = ( fn_defer_func_t )SLIC_init_le9662;
	le9662_defer.p0 = law;
	le9662_defer.p1 = 0;
	
	add_defer_initialization( &le9662_defer );
	rtn = 0; //success
#else
	rtn = SLIC_init_le9662( law, 0 /* allocate */ );
#endif
	
	if ( rtn == FAILED ) /* init Device fail */
		return -1;

	for( i = 0; i < CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR; i ++ ) 
		register_voip_snd( &snd_zarlink_le9662[ i * 2 ], 2 );	

	return 0;
}

voip_initcall_snd( voip_snd_zarlink_init_le9662 );

// --------------------------------------------------------
// IOC support 
// --------------------------------------------------------
#ifdef CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_IO
#define LE9662_IO_NUM		2

static voip_ioc_t le9662_ioc[ CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR * 2 ][ LE9662_IO_NUM ];
static zarlink_ioc_priv_t le9662_ioc_priv[ CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR * 2 ][ LE9662_IO_NUM ];

static int __init voip_ioc_zarlink_init_le9662( void )
{
	int i, j;
	
	for( i = 0; i < CONFIG_RTK_VOIP_DRIVERS_SLIC_LE9662_NR * 2; i ++ ) {
		for( j = 0; j < LE9662_IO_NUM; j ++ ) {
			
			voip_ioc_t * const p_ioc = &le9662_ioc[ i ][ j ];
			zarlink_ioc_priv_t * const p_ioc_priv = &le9662_ioc_priv[ i ][ j ];
			voip_snd_t * const p_snd = &snd_zarlink_le9662[ i ];
			
			p_ioc ->ioch = ( i << 8 ) | j;
			p_ioc ->name = "le9662";
			p_ioc ->ioc_type = ( j == 1 ? IOC_TYPE_RELAY : IOC_TYPE_LED );
			p_ioc ->pre_assigned_snd_ptr = ( j < 3 ? p_snd : NULL );
			p_ioc ->ioc_ops = ( p_ioc ->ioc_type == IOC_TYPE_RELAY ? &ioc_relay_ops_zarlink : &ioc_led_ops_zarlink );
			p_ioc ->priv = p_ioc_priv;
			
			p_ioc ->state_var = ( p_ioc ->ioc_type == IOC_TYPE_RELAY ? IOC_STATE_RELAY_CLOSE : IOC_STATE_LED_OFF );
			
			// NOTE: one 9662 has two lines, and our definition is:  
			//       First line uses IO1 and IO2, and 
			//       second line uses IO3 and IO4. 
			p_ioc_priv ->IO = zarlink_VPIO_list[ ( i & 0x01 ? 2 + j : j ) ];
			p_ioc_priv ->snd_priv = p_snd ->priv;
			
			InitializeZarlinkIO( p_ioc );
		}
		
		register_voip_ioc( &le9662_ioc[ i ][ 0 ], LE9662_IO_NUM );
	}
	
	return 0;
}

voip_initcall_ioc( voip_ioc_zarlink_init_le9662 );
#endif
