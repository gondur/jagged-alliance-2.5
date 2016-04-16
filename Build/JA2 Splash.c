#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
#else
	//add includes here!
#endif

UINT32 guiSplashFrameFade = 10;
UINT32 guiSplashStartTime = 0;
extern HVSURFACE ghFrameBuffer;

//Simply create videosurface, load image, and draw it to the screen.
void InitJA2SplashScreen()
{
	UINT32 uiLogoID = 0;
	STRING512			CurrentDir;
	STRING512			DataDir;

	InitializeJA2Clock();
	//InitializeJA2TimerID();
	// Get Executable Directory
	GetExecutableDirectory( CurrentDir );

	// Adjust Current Dir
#ifdef JA2UB_PRESS_PREVIEW
	sprintf( DataDir, "%s\\PreviewData", CurrentDir );
#else
	sprintf( DataDir, "%s\\Data", CurrentDir );
#endif

	if ( !SetFileManCurrentDirectory( DataDir ) )
	{
		DebugMsg( TOPIC_JA2, DBG_LEVEL_3, "Could not find data directory, shutting down");
		return;
	}

	//Initialize the file database
	InitializeFileDatabase( gGameLibaries, NUMBER_OF_LIBRARIES );

	//#ifdef ENGLISH
		ClearMainMenu();
	//#else
	//	{
	//		HVSURFACE hVSurface;
	//		VSURFACE_DESC VSurfaceDesc;
//
	//		memset( &VSurfaceDesc, 0, sizeof( VSURFACE_DESC ) );
	//		VSurfaceDesc.fCreateFlags = VSURFACE_CREATE_FROMFILE | VSURFACE_SYSTEM_MEM_USAGE;
	//		GetMLGFilename( VSurfaceDesc.ImageFile, MLG_SPLASH );
	//		if( !AddVideoSurface( &VSurfaceDesc, &uiLogoID ) )
	//		{	
	//			AssertMsg( 0, String( "Failed to load %s", VSurfaceDesc.ImageFile ) );
	//			return;
	//		}

	//		GetVideoSurface( &hVSurface, uiLogoID );
	//		BltVideoSurfaceToVideoSurface( ghFrameBuffer, hVSurface, 0, 0, 0, 0, NULL );
	//		DeleteVideoSurfaceFromIndex( uiLogoID );
	//	}
//	#endif


	InvalidateScreen();
	RefreshScreen( NULL );

	guiSplashStartTime = GetJA2Clock();
}
