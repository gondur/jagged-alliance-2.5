#ifndef _CUSTOM_MAP_CHOOSE_MAP__H_
#define _CUSTOM_MAP_CHOOSE_MAP__H_


//#define	ENABLE_CUSTOM_MAP_INTERFACE


BOOLEAN LoadCampaignString( );

CHAR8 *GetMapsDirectory( );

CHAR8 *GetCurrentCampaign( );

BOOLEAN SetCampaignString( CHAR8 *pzString, BOOLEAN fFromSaveScreen );

BOOLEAN InDefaultCampaign( );

CHAR8 *GetDefaultMapsDirectory( );

	#ifdef	ENABLE_CUSTOM_MAP_INTERFACE

		extern	UINT32	CustomMapInit( void );
		extern	UINT32	CustomMapHandle( void );
		extern	UINT32	CustomMapShutdown( void );

	#endif

#endif
