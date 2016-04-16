#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
	#include "Intro.h"
	#include "Cinematics.h"
	#include "Cinematics Bink.h"
	#include "Ja25_Tactical.h"
	#include "end game.h"
#else
	#include "sgp.h"
	#include "sys globals.h"
	#include "sysutil.h"
	#include "vobject_blitters.h"
	#include "wcheck.h"
	#include "cursors.h"
	#include "font control.h"
	#include "cursor control.h"
	#include "render dirty.h"
	#include "GameScreen.h"
	#include	"Text.h"
	#include	"Utilities.h"
	#include	"WordWrap.h"
	#include "Font Control.h"
	#include "text.h"
	#include "Multi Language Graphic Utils.h"
	#include "Line.h"
	#include "Intro.h"
	#include "Cinematics.h"
#endif

extern STR16	gzIntroScreen[];
extern HVSURFACE ghFrameBuffer;

enum
{
	INTRO_TXT__CANT_FIND_INTRO,
};

//ddd


//ggg
BOOLEAN		gfIntroScreenEntry;
BOOLEAN		gfIntroScreenExit;

UINT32		guiIntroExitScreen = INTRO_SCREEN;


extern	BOOLEAN	gfDoneWithSplashScreen;

//SMKFLIC *gpSmackFlic = NULL;
BINKFLIC *gpBinkFlic = NULL;

#define		SMKINTRO_FIRST_VIDEO				255
#define		SMKINTRO_NO_VIDEO						-1

//enums for the various smacker files
enum
{
	SMKINTRO_REBEL_CRDT,
	SMKINTRO_OMERTA,
	SMKINTRO_PRAGUE_CRDT,
	SMKINTRO_PRAGUE,

	//there are no more videos shown for the begining


	SMKINTRO_END_END_SPEECH_MIGUEL,
	SMKINTRO_END_END_SPEECH_NO_MIGUEL,
	SMKINTRO_END_HELI_FLYBY,
	SMKINTRO_END_SKYRIDER_HELICOPTER,
	SMKINTRO_END_NOSKYRIDER_HELICOPTER,

	SMKINTRO_SPLASH_SCREEN,
	SMKINTRO_SPLASH_INTERPLAY,

	SMKINTRO_HELI_CRASH_SCENE_1,
//	SMKINTRO_HELI_CRASH_SCENE_2,

	//there are no more videos shown for the endgame
	SMKINTRO_LAST_END_GAME,
};

INT32	giCurrentIntroBeingPlayed = SMKINTRO_NO_VIDEO;

/*
CHAR		*gpzSmackerFileNames[] = 
{
	//begining of the game
	"INTRO\\Rebel_cr.smk",
	"INTRO\\Omerta.smk",
	"INTRO\\Prague_cr.smk",
	"INTRO\\Prague.smk",


	//endgame
	"INTRO\\Throne_Mig.smk",
	"INTRO\\Throne_NoMig.smk",
	"INTRO\\Heli_FlyBy.smk",
	"INTRO\\Heli_Sky.smk",
	"INTRO\\Heli_NoSky.smk",

	"INTRO\\SplashScreen.smk",
	"INTRO\\TalonSoftid_endhold.smk",

	"INTRO\\Heli_FlyBy.smk",
	"INTRO\\Heli_FlyBy2.smk",
};
*/

CHAR		*gpzBinkFileNames[] = 
{
	//begining of the game
	"INTRO\\Rebel_cr.smk",
	"INTRO\\Omerta.smk",
	"INTRO\\Prague_cr.smk",
	"INTRO\\Prague.smk",


	//endgame
	"INTRO\\Throne_Mig.smk",
	"INTRO\\Throne_NoMig.smk",
	"INTRO\\Heli_FlyBy.smk",
	"INTRO\\Heli_Sky.smk",
	"INTRO\\Heli_NoSky.smk",

	"INTRO\\SplashScreen.bik",
	"INTRO\\IPLYLogo.bik",

	//Ja25: New vidoes
	"INTRO\\Intro.bik",
//	"INTRO\\Fade.bik",

	"INTRO\\MissileEnding.bik"
};


//enums used for when the intro screen can come up, either begining game intro, or end game cinematic
INT8	gbIntroScreenMode=-1;


extern	void		CDromEjectionErrorMessageBoxCallBack( UINT8 bExitValue );

void	GetIntroScreenUserInput();
BOOLEAN	EnterIntroScreen();
void	RenderIntroScreen();
void	ExitIntroScreen();
void	HandleIntroScreen();
void	PrepareToExitIntroScreen();
INT32 GetNextIntroVideo( UINT32 uiCurrentVideo );
void	StartPlayingIntroFlic( INT32 iIndexOfFlicToPlay );
void	DisplaySirtechSplashScreen();


//ppp


UINT32	IntroScreenInit( void )
{
	//Set so next time we come in, we can set up
	gfIntroScreenEntry = TRUE;

	return( 1 );
}


UINT32	IntroScreenShutdown( void )
{
	return( 1 );
}


UINT32	IntroScreenHandle( void )
{
	if( gfIntroScreenEntry )
	{
		gfIntroScreenEntry = FALSE;
		gfIntroScreenExit = FALSE;

		EnterIntroScreen();

		InvalidateRegion( 0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT );
	}

	RestoreBackgroundRects();


	GetIntroScreenUserInput();

	HandleIntroScreen();

	SetCurrentCursorFromDatabase( VIDEO_NO_CURSOR );

	ExecuteBaseDirtyRectQueue();
	EndFrameBufferRender();


	if( gfIntroScreenExit )
	{
		ExitIntroScreen();
		gfIntroScreenExit = FALSE;
		gfIntroScreenEntry = TRUE;
	}

	return( guiIntroExitScreen );
}


BOOLEAN EnterIntroScreen()
{
	INT32 iFirstVideoID = -1;

	// CLEAR THE FRAME BUFFER
	ClearMainMenu();

	//Clear out all the saved background rects
	EmptyBackgroundRects( );


	SetCurrentCursorFromDatabase( VIDEO_NO_CURSOR );

	// Don't play music....
	SetMusicMode( MUSIC_NONE );

//#ifdef JA2BETAVERSION
	if( FileExists( "..\\NoIntro.txt" ) )
	{
		PrepareToExitIntroScreen();
		return( TRUE );
	}
//#endif

	//if the library doesnt exist, exit
	if( !IsLibraryOpened( LIBRARY_INTRO ) )
	{
		PrepareToExitIntroScreen();
		return( TRUE );
	}

	//initialize smacker
//	SmkInitialize( ghWindow, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT);
	BinkInitialize(  ghWindow, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT );


	//get the index opf the first video to watch
	iFirstVideoID = GetNextIntroVideo( SMKINTRO_FIRST_VIDEO );

	if( iFirstVideoID != -1 )
	{
		StartPlayingIntroFlic( iFirstVideoID );

		guiIntroExitScreen = INTRO_SCREEN;
	}

	//Got no intro video, exit
	else
	{
		PrepareToExitIntroScreen();
	}
	

	return( TRUE );
}

void RenderIntroScreen()
{
}

void ExitIntroScreen()
{

	//shutdown smaker
//	SmkShutdown();

	BinkShutdownVideo( );
}

void HandleIntroScreen()
{
	BOOLEAN	fFlicStillPlaying = FALSE;

	//if we are exiting this screen, this frame, dont update the screen
	if( gfIntroScreenExit )
		return;


	//handle smaker each frame
//	fFlicStillPlaying = SmkPollFlics();
	fFlicStillPlaying = BinkPollFlics();

	//if the flic is not playing
	if( !fFlicStillPlaying )
	{
		INT32 iNextVideoToPlay = -1;

		iNextVideoToPlay = GetNextIntroVideo( giCurrentIntroBeingPlayed );

		if( iNextVideoToPlay != -1 )
		{
			StartPlayingIntroFlic( iNextVideoToPlay );
		}
		else
		{
			PrepareToExitIntroScreen();
			giCurrentIntroBeingPlayed = -1;
		}
	}

	InvalidateScreen();
}



void		GetIntroScreenUserInput()
{
	InputAtom Event;
	POINT  MousePos;

	static BOOLEAN gfOldMouseState = FALSE;

	GetCursorPos(&MousePos);

	while( DequeueEvent( &Event ) )
	{
		// HOOK INTO MOUSE HOOKS
		switch( Event.usEvent)
	  {
			case LEFT_BUTTON_DOWN:
				MouseSystemHook(LEFT_BUTTON_DOWN, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);
				break;
			case LEFT_BUTTON_UP:
				MouseSystemHook(LEFT_BUTTON_UP, (INT16)MousePos.x, (INT16)MousePos.y ,_LeftButtonDown, _RightButtonDown);			
				break;
			case RIGHT_BUTTON_DOWN:
				MouseSystemHook(RIGHT_BUTTON_DOWN, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);
				break;
			case RIGHT_BUTTON_UP: 
				MouseSystemHook(RIGHT_BUTTON_UP, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);	
				break;
			case RIGHT_BUTTON_REPEAT: 
				MouseSystemHook(RIGHT_BUTTON_REPEAT, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);			
				break;
			case LEFT_BUTTON_REPEAT: 
				MouseSystemHook(LEFT_BUTTON_REPEAT, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);				
				break;
		}

//		if( Event.usEvent == LEFT_BUTTON_DOWN || Event.usEvent == RIGHT_BUTTON_DOWN )
//{
//			BinkCloseFlic( gpBinkFlic );
//		}
 
		if( Event.usEvent == KEY_UP )
		{
			switch( Event.usParam )
			{
				case ESC:

					// ATE: if in splash, don't exit all!
					BinkCloseFlic( gpBinkFlic );
					if ( gbIntroScreenMode != INTRO_SPLASH )
					{
						PrepareToExitIntroScreen();
					}
					break;
				case SPACE:
//					SmkCloseFlic( gpSmackFlic );
					BinkCloseFlic( gpBinkFlic );
					break;

#ifdef JA2TESTVERSION

				case 'r':
					break;

				case 'i':
					InvalidateRegion( 0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT );
					break;

#endif
			}
		}
	}

	// if the user presses either mouse button
	if( !gfLeftButtonState && !gfRightButtonState  && gfOldMouseState )
	{
		//advance to the next flic
		BinkCloseFlic( gpBinkFlic );

		gfOldMouseState = FALSE;
	}

	if ( gfLeftButtonState || gfRightButtonState )
	{
		gfOldMouseState = TRUE;
	}
}


void PrepareToExitIntroScreen()
{
/*
Ja25: no begining intro
	//if its the intro at the begining of the game
	if( gbIntroScreenMode == INTRO_BEGINING )
	{
		//go to the init screen
		guiIntroExitScreen = INIT_SCREEN;
	}
*/
	//if its the heli crash intro 
	if( gbIntroScreenMode == INTRO_HELI_CRASH )
	{
		//go to the init screen
//Ja25: no longer going to initscreen ( cause this is now AFTER mapscreen )
//		guiIntroExitScreen = INIT_SCREEN;

		guiIntroExitScreen = GAME_SCREEN;
		SetCurrentWorldSector( sSelMapX, sSelMapY, ( UINT8 )iCurrentMapSectorZ );
	}

	else if( gbIntroScreenMode == INTRO_SPLASH )
	{
		//display a logo when exiting
		DisplaySirtechSplashScreen();

		gfDoneWithSplashScreen = TRUE;
		guiIntroExitScreen = INIT_SCREEN;
	}
	else if( gbIntroScreenMode == INTRO_ENDING )
	{
		guiIntroExitScreen = GAME_SCREEN;
		SetCurrentWorldSector( 16, 11, 0 );

		EnterTacticalInFinalSector();

		//Dont leave tactical
		gfEnteringMapScreen = FALSE;
	}
	else
	{
		//We want to reinitialize the game
		ReStartingGame();

//		guiIntroExitScreen = MAINMENU_SCREEN;
		guiIntroExitScreen = CREDIT_SCREEN;
	}

	gfIntroScreenExit = TRUE;
}


INT32 GetNextIntroVideo( UINT32 uiCurrentVideo )
{
	INT32 iStringToUse = -1;

	//switch on whether it is the beginging or the end game video
	switch( gbIntroScreenMode )
	{
/*
Ja25: no begining intro
		//the video at the begining of the game
		case INTRO_BEGINING:
		{
			switch( uiCurrentVideo )
			{
				case SMKINTRO_FIRST_VIDEO:
					iStringToUse = SMKINTRO_REBEL_CRDT;
					break;
				case SMKINTRO_REBEL_CRDT:
					iStringToUse = SMKINTRO_OMERTA;
					break;
				case SMKINTRO_OMERTA:
					iStringToUse = SMKINTRO_PRAGUE_CRDT;
					break;
				case SMKINTRO_PRAGUE_CRDT:
					iStringToUse = SMKINTRO_PRAGUE;
					break;
				case SMKINTRO_PRAGUE:
					iStringToUse = -1;
					break;
//				case SMKINTRO_LAST_INTRO:
//					iStringToUse = -1;
//					break;
			}
		}
		break;
*/
		case INTRO_HELI_CRASH:
			switch( uiCurrentVideo )
			{
				case SMKINTRO_FIRST_VIDEO:
					iStringToUse = SMKINTRO_HELI_CRASH_SCENE_1;
					break;
			}
			break;

		//end game
		case INTRO_ENDING:
		{
			switch( uiCurrentVideo )
			{
				case SMKINTRO_FIRST_VIDEO:
					iStringToUse = SMKINTRO_LAST_END_GAME;
					break;
			}

/*
				case SMKINTRO_FIRST_VIDEO:
					//if Miguel is dead, play the flic with out him in it
//Ja25: No miguel
//					if( gMercProfiles[ MIGUEL ].bMercStatus == MERC_IS_DEAD )
//						iStringToUse = SMKINTRO_END_END_SPEECH_NO_MIGUEL;
//					else
						iStringToUse = SMKINTRO_END_END_SPEECH_MIGUEL;
					break;

				case SMKINTRO_END_END_SPEECH_MIGUEL:
				case SMKINTRO_END_END_SPEECH_NO_MIGUEL:
					iStringToUse = SMKINTRO_END_HELI_FLYBY;
					break;

				//if SkyRider is dead, play the flic without him
				case SMKINTRO_END_HELI_FLYBY:
					if( gMercProfiles[ SKYRIDER ].bMercStatus == MERC_IS_DEAD )
						iStringToUse = SMKINTRO_END_NOSKYRIDER_HELICOPTER;
					else
						iStringToUse = SMKINTRO_END_SKYRIDER_HELICOPTER;
					break;
			}
*/
		}
		break;

		case INTRO_SPLASH:

//#ifdef JA2TESTVERSION
//	return( -1 );
//#endif

			// CJC Nov 18 2002: disabled Interplay screen

			/*
			switch( uiCurrentVideo )
			{
				case SMKINTRO_FIRST_VIDEO:

#ifdef AUSSIE
					iStringToUse = SMKINTRO_SPLASH_SCREEN;
#else
					iStringToUse = SMKINTRO_SPLASH_INTERPLAY;
#endif
					break;
				case SMKINTRO_SPLASH_INTERPLAY:
					iStringToUse = SMKINTRO_SPLASH_SCREEN;
					break;
			}
			*/

		break;
	}

	return( iStringToUse );
}


void StartPlayingIntroFlic( INT32 iIndexOfFlicToPlay )
{
	UINT32 uiTop=0;

	if( uiTop )
	{
	}

	if( iIndexOfFlicToPlay != -1 )
	{
		//start playing a flic
//		gpSmackFlic = SmkPlayFlic( gpzSmackerFileNames[ iIndexOfFlicToPlay ], 0, 0, TRUE );
		gpBinkFlic = BinkPlayFlic( gpzBinkFileNames[ iIndexOfFlicToPlay ], 0, 0, BINK_FLIC_AUTOCLOSE | BINK_FLIC_CENTER_VERTICAL );

//		if( gpSmackFlic != NULL )
		if( gpBinkFlic != NULL )
		{
			giCurrentIntroBeingPlayed = iIndexOfFlicToPlay;
		}
		else
		{
			//do a check
#ifdef JA2BETAVERSION
			PrepareToExitIntroScreen();
#else

			DoScreenIndependantMessageBox( gzIntroScreen[INTRO_TXT__CANT_FIND_INTRO], MSG_BOX_FLAG_OK, CDromEjectionErrorMessageBoxCallBack );
#endif
		}
	}
}


void SetIntroType( INT8 bIntroType )
{
/*
Ja25: no intro videos
	if( bIntroType == INTRO_BEGINING )
	{
		gbIntroScreenMode = INTRO_BEGINING;
	}
*/
	if( bIntroType == INTRO_HELI_CRASH )
	{
		gbIntroScreenMode = INTRO_HELI_CRASH;
	}

	else if( bIntroType == INTRO_ENDING )
	{
		gbIntroScreenMode = INTRO_ENDING;
	}
	else if( bIntroType == INTRO_SPLASH )
	{
		gbIntroScreenMode = INTRO_SPLASH;
	}
}


void DisplaySirtechSplashScreen()
{
  HVOBJECT hPixHandle;
  VOBJECT_DESC    VObjectDesc;
	UINT32 uiLogoID;

	UINT32										 uiDestPitchBYTES;
	UINT8											 *pDestBuf;


	// CLEAR THE FRAME BUFFER
	pDestBuf = LockVideoSurface( FRAME_BUFFER, &uiDestPitchBYTES );
	memset(pDestBuf, 0, SCREEN_HEIGHT * uiDestPitchBYTES );
	UnLockVideoSurface( FRAME_BUFFER );


	memset( &VObjectDesc, 0, sizeof( VOBJECT_DESC ) );
	VObjectDesc.fCreateFlags=VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\SirtechSplash.sti", VObjectDesc.ImageFile);
//	FilenameForBPP("INTERFACE\\TShold.sti", VObjectDesc.ImageFile);
	if( !AddVideoObject(&VObjectDesc, &uiLogoID) )
	{	
		AssertMsg( 0, String( "Failed to load %s", VObjectDesc.ImageFile ) );
		return;
	}

	GetVideoObject(&hPixHandle, uiLogoID);
	BltVideoObject(FRAME_BUFFER, hPixHandle, 0,0, 0, VO_BLT_SRCTRANSPARENCY,NULL);
	DeleteVideoObjectFromIndex(uiLogoID);


	InvalidateScreen();
	RefreshScreen( NULL );
}
