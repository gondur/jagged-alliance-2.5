#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
	#include "CustomMap.h"
	#include "CustomMapBriefingScreen.h"
	#include "CustomMapHeader.h"
#else
	#include "Screens.h"
#endif

#ifdef	ENABLE_CUSTOM_MAP_INTERFACE

//** Defines *******************************************************************



//** Global Variables  *********************************************************
UINT8				gubCMBriefingScreenExitScreen=CUSTOM_MAP_BRIEFING_SCREEN;
BOOLEAN			gfCMBriefingScreenExit=FALSE;
BOOLEAN			gfCMBriefingScreenEntry=TRUE;
BOOLEAN			gfRenderCMBriefingScreen=TRUE;




//** Prototypes ****************************************************************

BOOLEAN			EnterCMBriefingScreen();
void				GetCMBriefingScreenUserInput();
void				ExitCMBriefingScreen();
void				SetCMBriefingScreenExitScreen( UINT32 uiNewScreen );
BOOLEAN			RenderCMBriefingScreen();
void				HandleCMBriefingScreen();

//ppp




//** Functions  ****************************************************************




UINT32	CMBriefingScreenInit( void )
{
	return( 1 );
}



UINT32	CMBriefingScreenHandle( void )
{
	StartFrameBufferRender();

	if( gfCMBriefingScreenEntry )
	{
		gubCMBriefingScreenExitScreen=CUSTOM_MAP_BRIEFING_SCREEN;
		EnterCMBriefingScreen();
		gfCMBriefingScreenEntry = FALSE;
		gfCMBriefingScreenExit = FALSE;
	}

	//Get any keyboard events
	GetCMBriefingScreenUserInput();
	

	HandleCMBriefingScreen();

	// render buttons marked dirty	
	MarkButtonsDirty( );
	RenderButtons( ); 

	ExecuteBaseDirtyRectQueue();
	EndFrameBufferRender();

	if ( HandleFadeOutCallback( ) )
	{
		ClearMainMenu();
		return( gubCMBriefingScreenExitScreen );
	}


	if( gfCMBriefingScreenExit )
	{
		ExitCMBriefingScreen();
		gfCMBriefingScreenEntry = TRUE;
	}


	return( gubCMBriefingScreenExitScreen );
}


UINT32	CMBriefingScreenShutdown( void )
{
	return( 1 );
}





BOOLEAN EnterCMBriefingScreen()
{
	ClearMainMenu();

	gfRenderCMBriefingScreen = TRUE;
	return( TRUE );
}


void ExitCMBriefingScreen()
{

}

void HandleCMBriefingScreen()
{
	//if we are to render the interface
	if( gfRenderCMBriefingScreen )
	{
		RenderCMBriefingScreen();

		gfRenderCMBriefingScreen = FALSE;
	}
}

BOOLEAN RenderCMBriefingScreen()
{
	//Display Title
	DrawTextToScreen( L"Map Briefing", 0, 30, SCREEN_BUFFER_WIDTH, FONT14ARIAL, FONT_GREEN, FONT_MCOLOR_BLACK, FALSE, CENTER_JUSTIFIED	);

	InvalidateRegion( 0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT );

	return( TRUE );
}

void GetCMBriefingScreenUserInput()
{
	InputAtom  InputEvent;
	POINT  MousePos;

	GetCursorPos(&MousePos);

	// Check for esc 
	while (DequeueEvent(&InputEvent) == TRUE)
  {
		// HOOK INTO MOUSE HOOKS
		switch( InputEvent.usEvent)
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

    if( InputEvent.usEvent == KEY_UP )
		{
			switch( InputEvent.usParam )
			{
#ifdef JA2TESTVERSION
				case 'r':
					gfRenderCMBriefingScreen = TRUE;
					break;
				case 'm':
					//goto the merc choosing screen
					SetCMBriefingScreenExitScreen( CUSTOM_MAP_MERC_CHOOSING_SCREEN );
					break;
#endif
				case '1':
					break;
				case ESC:
					//Cancel back to the custom map choosing screen
					SetCMBriefingScreenExitScreen( CUSTOM_MAP_LOAD_SCREEN );
					break;
			}
		}
	}
}


void SetCMBriefingScreenExitScreen( UINT32 uiNewScreen )
{
	gubCMBriefingScreenExitScreen = uiNewScreen;

	gfCMBriefingScreenExit= TRUE;
}




#endif