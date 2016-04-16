#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
	#include "CustomMap.h"
	#include "CustomMapMercChoosing.h"
	#include "CustomMapHeader.h"
#else
	#include "Screens.h"
#endif



#ifdef ENABLE_CUSTOM_MAP_INTERFACE

//** Defines *******************************************************************



//** Global Variables  *********************************************************
UINT8				gubCMMercChoosingExitScreen=CUSTOM_MAP_MERC_CHOOSING_SCREEN;
BOOLEAN			gfCMMercChoosingExit=FALSE;
BOOLEAN			gfCMMercChoosingEntry=TRUE;
BOOLEAN			gfRenderCMMercChoosing=TRUE;




//** Prototypes ****************************************************************

BOOLEAN			EnterCMMercChoosing();
void				GetCMMercChoosingUserInput();
void				ExitCMMercChoosing();
void				SetCMMercChoosingExitScreen( UINT32 uiNewScreen );
BOOLEAN			RenderCMMercChoosing();
void				HandleCMMercChoosing();
void				TestChooseMercsAndEnterGame();

//ppp




//** Functions  ****************************************************************




UINT32	CMMercChoosingInit( void )
{
	return( 1 );
}



UINT32	CMMercChoosingHandle( void )
{
	StartFrameBufferRender();

	if( gfCMMercChoosingEntry )
	{
		gubCMMercChoosingExitScreen=CUSTOM_MAP_MERC_CHOOSING_SCREEN;
		EnterCMMercChoosing();
		gfCMMercChoosingEntry = FALSE;
		gfCMMercChoosingExit = FALSE;
	}

	//Get any keyboard events
	GetCMMercChoosingUserInput();
	

	HandleCMMercChoosing();

	// render buttons marked dirty	
	MarkButtonsDirty( );
	RenderButtons( ); 

	ExecuteBaseDirtyRectQueue();
	EndFrameBufferRender();

	if ( HandleFadeOutCallback( ) )
	{
		ClearMainMenu();
		return( gubCMMercChoosingExitScreen );
	}


	if( gfCMMercChoosingExit )
	{
		ExitCMMercChoosing();
		gfCMMercChoosingEntry = TRUE;
	}


	return( gubCMMercChoosingExitScreen );
}


UINT32	CMMercChoosingShutdown( void )
{
	return( 1 );
}





BOOLEAN EnterCMMercChoosing()
{
	ClearMainMenu();

	gfRenderCMMercChoosing = TRUE;
	return( TRUE );
}


void ExitCMMercChoosing()
{

}

void HandleCMMercChoosing()
{
	//if we are to render the interface
	if( gfRenderCMMercChoosing )
	{
		RenderCMMercChoosing();

		gfRenderCMMercChoosing = FALSE;
	}
}

BOOLEAN RenderCMMercChoosing()
{
	//Display Title
	DrawTextToScreen( L"Choose Mercs", 0, 30, SCREEN_BUFFER_WIDTH, FONT14ARIAL, FONT_GREEN, FONT_MCOLOR_BLACK, FALSE, CENTER_JUSTIFIED	);

	InvalidateRegion( 0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT );

	return( TRUE );
}

void GetCMMercChoosingUserInput()
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
					gfRenderCMMercChoosing = TRUE;
					break;

				//TEST:  use current settings and enter game
				case '1':
					TestChooseMercsAndEnterGame();
					break;
#endif
				case ESC:
					//Cancel back to the briefing
					SetCMMercChoosingExitScreen( CUSTOM_MAP_BRIEFING_SCREEN );
					break;
			}
		}
	}
}


void SetCMMercChoosingExitScreen( UINT32 uiNewScreen )
{
	gubCMMercChoosingExitScreen = uiNewScreen;

	gfCMMercChoosingExit= TRUE;
}

void TestChooseMercsAndEnterGame()
{
	INT8	bReturnCode;
	MERC_HIRE_STRUCT HireMercStruct;
	UINT8		ubCurrentSoldier = 11;

//	gfFirstTimeInGameHeliCrash = FALSE;
//	gTacticalStatus.fDidGameJustStart = FALSE;


	HireMercStruct.ubProfileID = ubCurrentSoldier;

	//DEF: temp
	HireMercStruct.sSectorX = gsMercArriveSectorX;
	HireMercStruct.sSectorY = gsMercArriveSectorY;
	HireMercStruct.bSectorZ = 0;
	HireMercStruct.fUseLandingZoneForArrival = TRUE;
	HireMercStruct.ubInsertionCode	= INSERTION_CODE_CENTER;

	HireMercStruct.fCopyProfileItemsOver = TRUE;
	gMercProfiles[ ubCurrentSoldier ].ubMiscFlags |= PROFILE_MISC_FLAG_ALREADY_USED_ITEMS;



	HireMercStruct.iTotalContractLength = 14;

	//specify when the merc should arrive
	HireMercStruct.uiTimeTillMercArrives = GetMercArrivalTimeOfDay( );// + ubCurrentSoldier;

	SetFlagToForceHireMerc( TRUE );
	bReturnCode = HireMerc( &HireMercStruct );
	SetFlagToForceHireMerc( FALSE );

	

	SetCMMercChoosingExitScreen( MAP_SCREEN );

	//Specify the starting sector
	gsMercArriveSectorX = gSelectedCustomScenario.pMap[ 0 ].sSectorX;
	gsMercArriveSectorY = gSelectedCustomScenario.pMap[ 0 ].sSectorY;
}



#endif