#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
	#include "ImportJa2SaveScreen.h"
	#include "Ja25Update.h"
	#include "_Ja25Englishtext.h"
	#include "Ja25 Strategic Ai.h"
#endif





//*******************************************************************
//
// Local Defines
//
//*******************************************************************

#define		IJS_TITLE_FONT													FONT14ARIAL
#define		IJS_HIGHLIGHT_COLOR											FONT_MCOLOR_LTYELLOW
#define		IJS_TITLE_SHADOW_COLOR									192

#define		IJS_SUBTITLE_FONT												FONT12ARIAL
#define		IJS_SUBTITLE_COLOR											FONT_MCOLOR_WHITE
#define		IJS_SUBTITLE_SHADOW											FONT_MCOLOR_BLACK

#define		IJS_DESC_FONT														FONT10ARIAL
#define		IJS_DESC_COLOR													FONT_MCOLOR_WHITE
#define		IJS_DESC_SHADOW													FONT_MCOLOR_BLACK


#define		IJS__TITLE_LOC_X												0
#define		IJS__TITLE_LOC_Y												18
#define		IJS__TITLE_LOC_WIDTH										SCREEN_BUFFER_WIDTH


#define		IJS__SUBSECTION_TITLE_X									50

#define		IJS__SUBSECTION_TITLE_OFFSET_Y					20
#define		IJS__DESC_OFFSET_X											15


#define		IJS__TITLE_DESC_Y												95
#define		IJS__SUBSECTION_BODY_X									IJS__SUBSECTION_TITLE_X
#define		IJS__SUBSECTION_BODY_WIDTH							( 554 - 2 * IJS__DESC_OFFSET_X ) 

#define		IJS__START_FRESH_TITLE_Y								145
#define		IJS__START_FRESH_BODY_Y									IJS__SUBSECTION_TITLE_OFFSET_Y + IJS__START_FRESH_TITLE_Y

#define		IJS__IMPORT_TITLE_Y											245
#define		IJS__IMPORT_BODY_Y_1										IJS__SUBSECTION_TITLE_OFFSET_Y + IJS__IMPORT_TITLE_Y


#define		IJS__BUTTON_WIDTH												119

#define		IJS__START_FRESH_BTN_LOC_X							94
#define		IJS__START_FRESH_BTN_LOC_Y							438

#define		IJS__IMPORT_BTN_LOC_X										IJS__START_FRESH_BTN_LOC_X + IJS__BUTTON_WIDTH + 46
#define		IJS__IMPORT_BTN_LOC_Y										IJS__START_FRESH_BTN_LOC_Y

#define		IJS__CANCEL_BTN_LOC_X										IJS__IMPORT_BTN_LOC_X + IJS__BUTTON_WIDTH + 46
#define		IJS__CANCEL_BTN_LOC_Y										IJS__START_FRESH_BTN_LOC_Y




//*******************************************************************
//
// Global Variables
//
//*******************************************************************

BOOLEAN		gfImportScreenEntry = TRUE;
BOOLEAN		gfImportScreenExit	= FALSE;

INT32			giImportMessageBox=0;
UINT8			gubImportExitScreen=IMPORT_SCREEN;


//Different states of the Import
enum
{
	IMPORT_NOTHING,
	IMPORT_FIRST_DIALOG,
	IMPORT_IMPORT_DIALOG,
	IMPORT_CONTINUE,
};

UINT8	gubImportState=IMPORT_NOTHING;

UINT32	guiJIS_BackGroundGraphics;

//Buttons
UINT32		guiJIS_ButtonStartFresh;
UINT32		guiJIS_ButtonImport;
UINT32		guiJIS_ButtonCancel;

//Button Graphics
INT32		giJIS_ButtonStartFreshImage;
INT32		giJIS_ButtonImportImage;
INT32		giJIS_ButtonCancelImage;




//ggg

//*******************************************************************
//
// Function Prototypes
//
//*******************************************************************


void			HandleImportScreen();
BOOLEAN		EnterImportScreen();
void			ExitImportScreen();
void			RenderImportScreen();
BOOLEAN		DoImportMessageBox( UINT8 ubStyle, INT16 *zString, UINT32 uiExitScreen, UINT16 usFlags, MSGBOX_CALLBACK ReturnCallback );
void			ConfirmStartFreshImportMessageBoxCallBack( UINT8 bExitValue );
void			ConfirmRunConverterMessageBoxCallBack( UINT8 bExitValue );
void			ConfirmAfterConvertContinueMessageBoxCallBack( UINT8 bExitValue );
void			ErrorAfterConvertMessageBoxCallBack( UINT8 bExitValue );
void			SetImportExitScreen( UINT32 uiNewScreen );
void			GetImportScreenUserInput();
void			BtnIJS_StartFreshCallback(GUI_BUTTON *btn,INT32 reason);
void			BtnIJS_ImportCallback(GUI_BUTTON *btn,INT32 reason);
void			BtnIJS_CancelCallback(GUI_BUTTON *btn,INT32 reason);
//ppp



//*******************************************************************
//
// Functions
//
//*******************************************************************


UINT32	ImportJa2SaveScreenInit( void )
{
	return( 1 );
}



UINT32	ImportJa2SaveScreenHandle( void )
{
	StartFrameBufferRender();

	if( gfImportScreenEntry )
	{
//		PauseGame();

		EnterImportScreen();
		gfImportScreenEntry = FALSE;
		gfImportScreenExit = FALSE;
		RenderImportScreen();
		InvalidateRegion( 0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT );
	}

	GetImportScreenUserInput();
	

	HandleImportScreen();

	// render buttons marked dirty	
	MarkButtonsDirty( );
	RenderButtons( ); 

	ExecuteBaseDirtyRectQueue();
	EndFrameBufferRender();

	if ( HandleFadeOutCallback( ) )
	{
		ClearMainMenu();
		return( gubImportExitScreen );
	}


	if( gfImportScreenExit )
	{
		ExitImportScreen();
		gfImportScreenEntry = TRUE;
	}


	return( gubImportExitScreen );
}


UINT32	ImportJa2SaveScreenShutdown( void )
{
	return( 1 );
}




void HandleImportScreen()
{
	switch( gubImportState )
	{
		case IMPORT_NOTHING:
			break;
		case IMPORT_FIRST_DIALOG:
//			DoImportMessageBox( MSG_BOX_BASIC_STYLE, zNewButtonText[ NEW_BTN_TXT__IMPORT_QUESTION ], IMPORT_SCREEN, MSG_BOX_FLAG_IMPORT_CHARACTERS, ConfirmStartFreshImportMessageBoxCallBack );
			gubImportState=IMPORT_NOTHING;
			break;
		case IMPORT_IMPORT_DIALOG:
			DoImportMessageBox( MSG_BOX_BASIC_STYLE, zNewButtonText[ NEW_BTN_TXT__RUN_CONVERTER ], IMPORT_SCREEN, MSG_BOX_FLAG_YESNO, ConfirmRunConverterMessageBoxCallBack );
			gubImportState=IMPORT_NOTHING;
			break;
		case IMPORT_CONTINUE:
			//
			// if there is a problem opening the file created by the external utility, report an error
			//
			
			if( DoesJa25ImportSaveExistAndSeemValid() )
			{
				DoImportMessageBox( MSG_BOX_BASIC_STYLE, zNewButtonText[ NEW_BTN_TXT__CONTINUE ], IMPORT_SCREEN, MSG_BOX_FLAG_YESNO, ConfirmAfterConvertContinueMessageBoxCallBack );
				gubImportState=IMPORT_NOTHING;
			}
			else
			{
				//an error occured
				DoImportMessageBox( MSG_BOX_BASIC_STYLE, zNewButtonText[ NEW_BTN_TXT__ERROR ], IMPORT_SCREEN, MSG_BOX_FLAG_OK, ErrorAfterConvertMessageBoxCallBack );
				gubImportState=IMPORT_NOTHING;
			}

			break;
		default:
			Assert( 0 );
	}
}



//enter:
BOOLEAN EnterImportScreen()
{
  VOBJECT_DESC    VObjectDesc;

	//clear the screen;
	ClearMainMenu();


	//The first thing that is to be done is ask the user what he wants to do next
//	gubImportState = IMPORT_FIRST_DIALOG;


	// load Load Screen Add ons graphic and add it
	VObjectDesc.fCreateFlags=VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\ja25Updatebase.sti", VObjectDesc.ImageFile);
	CHECKF(AddVideoObject(&VObjectDesc, &guiJIS_BackGroundGraphics ));



	//Start Fresh button
	giJIS_ButtonStartFreshImage = LoadButtonImage("INTERFACE\\OptionScreenAddons.sti", -1,2,-1,3,-1 );
	guiJIS_ButtonStartFresh = CreateIconAndTextButton( giJIS_ButtonStartFreshImage, gzImportJa2ScreenText[IJS__START_FRESH_BTN], OPT_BUTTON_FONT, 
													 OPT_BUTTON_ON_COLOR, DEFAULT_SHADOW, 
													 OPT_BUTTON_OFF_COLOR, DEFAULT_SHADOW, 
													 TEXT_CJUSTIFIED, 
													 IJS__START_FRESH_BTN_LOC_X, IJS__START_FRESH_BTN_LOC_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGH,
													 DEFAULT_MOVE_CALLBACK, BtnIJS_StartFreshCallback);
	SpecifyDisabledButtonStyle( guiJIS_ButtonStartFresh, DISABLED_STYLE_HATCHED );


	//Import button
	giJIS_ButtonImportImage = UseLoadedButtonImage( giJIS_ButtonStartFreshImage, -1,2,-1,3,-1 );
	guiJIS_ButtonImport = CreateIconAndTextButton( giJIS_ButtonImportImage, gzImportJa2ScreenText[IJS__IMPORT_BTN], OPT_BUTTON_FONT, 
													 OPT_BUTTON_ON_COLOR, DEFAULT_SHADOW, 
													 OPT_BUTTON_OFF_COLOR, DEFAULT_SHADOW, 
													 TEXT_CJUSTIFIED, 
													 IJS__IMPORT_BTN_LOC_X, IJS__IMPORT_BTN_LOC_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGH,
													 DEFAULT_MOVE_CALLBACK, BtnIJS_ImportCallback);
	SpecifyDisabledButtonStyle( guiJIS_ButtonImport, DISABLED_STYLE_SHADED );

	//Cancel button
	giJIS_ButtonCancelImage = UseLoadedButtonImage( giJIS_ButtonStartFreshImage, -1,2,-1,3,-1 );
	guiJIS_ButtonCancel = CreateIconAndTextButton( giJIS_ButtonCancelImage, gzImportJa2ScreenText[IJS__CANCEL_BTN], OPT_BUTTON_FONT, 
													 OPT_BUTTON_ON_COLOR, DEFAULT_SHADOW, 
													 OPT_BUTTON_OFF_COLOR, DEFAULT_SHADOW, 
													 TEXT_CJUSTIFIED, 
													 IJS__CANCEL_BTN_LOC_X, IJS__CANCEL_BTN_LOC_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGH,
													 DEFAULT_MOVE_CALLBACK, BtnIJS_CancelCallback);
	SpecifyDisabledButtonStyle( guiJIS_ButtonCancel, DISABLED_STYLE_SHADED );


	gubImportExitScreen = IMPORT_SCREEN;

	return( TRUE );
}

void ExitImportScreen()
{
	DeleteVideoObjectFromIndex( guiJIS_BackGroundGraphics );


	//Removes buttons
	RemoveButton( guiJIS_ButtonStartFresh );
	RemoveButton( guiJIS_ButtonImport );
	RemoveButton( guiJIS_ButtonCancel );

	//Remove Buttons images
	UnloadButtonImage( giJIS_ButtonStartFreshImage );
	UnloadButtonImage( giJIS_ButtonImportImage );
	UnloadButtonImage( giJIS_ButtonCancelImage );
}

void RenderImportScreen()
{
  HVOBJECT hPixHandle;
	UINT32	uiNumPixels;

	//Blit the background
	GetVideoObject(&hPixHandle, guiJIS_BackGroundGraphics);
  BltVideoObject(FRAME_BUFFER, hPixHandle, 0, 0, 0, VO_BLT_SRCTRANSPARENCY,NULL);


	//Display the title
	DisplayWrappedString( IJS__TITLE_LOC_X, IJS__TITLE_LOC_Y, IJS__TITLE_LOC_WIDTH, 2, IJS_TITLE_FONT, IJS_HIGHLIGHT_COLOR, gzImportJa2ScreenText[ IJS__TITLE ], IJS_TITLE_SHADOW_COLOR, FALSE, CENTER_JUSTIFIED );


	//Display the desc of the page
	DisplayWrappedString( IJS__SUBSECTION_BODY_X, IJS__TITLE_DESC_Y, IJS__SUBSECTION_BODY_WIDTH, 2, IJS_SUBTITLE_FONT, IJS_DESC_COLOR, gzImportJa2ScreenText[ IJS__TITLE_DESC ], IJS_DESC_SHADOW, FALSE, LEFT_JUSTIFIED );


	//Display the title of the start fresh
	DisplayWrappedString( IJS__SUBSECTION_BODY_X, IJS__START_FRESH_TITLE_Y, IJS__SUBSECTION_BODY_WIDTH, 2, IJS_SUBTITLE_FONT, IJS_SUBTITLE_COLOR, gzImportJa2ScreenText[ IJS__START_FRESH ], IJS_SUBTITLE_SHADOW, FALSE, LEFT_JUSTIFIED );

	//Display the desc of the start fresh section
	DisplayWrappedString( IJS__SUBSECTION_BODY_X+IJS__DESC_OFFSET_X, IJS__START_FRESH_BODY_Y, IJS__SUBSECTION_BODY_WIDTH, 2, IJS_DESC_FONT, IJS_DESC_COLOR, gzImportJa2ScreenText[ IJS__START_FRESH_DESC ], IJS_DESC_SHADOW, FALSE, LEFT_JUSTIFIED );


	//Display the desc of the Import Title
	DisplayWrappedString( IJS__SUBSECTION_BODY_X, IJS__IMPORT_TITLE_Y, IJS__SUBSECTION_BODY_WIDTH, 2, IJS_SUBTITLE_FONT, IJS_SUBTITLE_COLOR, gzImportJa2ScreenText[ IJS__IMPORT ], IJS_SUBTITLE_SHADOW, FALSE, LEFT_JUSTIFIED );

	//Display the desc of the Import section 1
	uiNumPixels = DisplayWrappedString( IJS__SUBSECTION_BODY_X+IJS__DESC_OFFSET_X, IJS__IMPORT_BODY_Y_1, IJS__SUBSECTION_BODY_WIDTH, 2, IJS_DESC_FONT, IJS_DESC_COLOR, gzImportJa2ScreenText[ IJS__IMPORT_DESC_1 ], IJS_DESC_SHADOW, FALSE, LEFT_JUSTIFIED );

	//increment down a line
	uiNumPixels += GetFontHeight( IJS_DESC_FONT );

	//Display the desc of the Import section 2
	DisplayWrappedString( IJS__SUBSECTION_BODY_X+IJS__DESC_OFFSET_X, (UINT16)(IJS__IMPORT_BODY_Y_1+uiNumPixels), IJS__SUBSECTION_BODY_WIDTH, 2, IJS_DESC_FONT, IJS_DESC_COLOR, gzImportJa2ScreenText[ IJS__IMPORT_DESC_2 ], IJS_DESC_SHADOW, FALSE, LEFT_JUSTIFIED );
}



BOOLEAN DoImportMessageBox( UINT8 ubStyle, INT16 *zString, UINT32 uiExitScreen, UINT16 usFlags, MSGBOX_CALLBACK ReturnCallback )
{
  SGPRect CenteringRect= {0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT };
  
	// reset exit mode
//	gfExitGioDueToMessageBox = TRUE;

	// do message box and return
  giImportMessageBox = DoMessageBox(  ubStyle,  zString,  uiExitScreen, ( UINT16 ) ( usFlags| MSG_BOX_FLAG_USE_CENTERING_RECT ),  ReturnCallback,  &CenteringRect );

	// send back return state
	return( ( giImportMessageBox != -1 ) );
}


void			ConfirmStartFreshImportMessageBoxCallBack( UINT8 bExitValue )
{
	switch( bExitValue )
	{
		case MSG_BOX_RETURN_IMPORT:
			gubImportState=IMPORT_IMPORT_DIALOG;

			break;

		case MSG_BOX_RETURN_START_FRESH:
			SetImportExitScreen( GAME_INIT_OPTIONS_SCREEN );
			break;

		case MSG_BOX_RETURN_NO:
			SetImportExitScreen( MAINMENU_SCREEN );
			break;

		default:
			Assert( 0 );
	}
}

void			ConfirmRunConverterMessageBoxCallBack( UINT8 bExitValue )
{
	UINT32 uiRetVal=0;
	STRING512 zOriginalDir;

	if( bExitValue == MSG_BOX_RETURN_YES )
	{
		//minimize JA2
//		ShowWindow( ghWindow, SW_MINIMIZE ); 
		ShowWindow( ghWindow, SW_SHOWMINIMIZED ); 
//		ShowWindow( ghWindow, SW_HIDE ); 

		GetFileManCurrentDirectory( zOriginalDir );

		SetFileManCurrentDirectory( ".." );

		//Run the converter
		uiRetVal = WinExec( "Ja2UBSaveConverter.exe", SW_SHOWNORMAL );

		gubImportState = IMPORT_CONTINUE;

		SetFileManCurrentDirectory( zOriginalDir );
	}

	gubImportState = IMPORT_CONTINUE;
}


void			ConfirmAfterConvertContinueMessageBoxCallBack( UINT8 bExitValue )
{
	UINT32 uiRetVal=0;

	if( bExitValue == MSG_BOX_RETURN_YES )
	{
		//go the initial game options screen
		SetImportExitScreen( GAME_INIT_OPTIONS_SCREEN );

		//Remeber that we are continuing from an imported save
		gJa25SaveStruct.fImportCharactersFromOldJa2Save = TRUE;
	}
	else
	{
		SetImportExitScreen( MAINMENU_SCREEN );
	}
}


void	ErrorAfterConvertMessageBoxCallBack( UINT8 bExitValue )
{
	UINT32 uiRetVal=0;

	//Remeber that we are NOT continuing from an imported save
	gJa25SaveStruct.fImportCharactersFromOldJa2Save = FALSE;

	SetImportExitScreen( MAINMENU_SCREEN );
}


void SetImportExitScreen( UINT32 uiNewScreen )
{
	gubImportExitScreen = uiNewScreen;

	gfImportScreenExit = TRUE;
}



void		GetImportScreenUserInput()
{
	InputAtom Event;
	POINT  MousePos;

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

		if( Event.usEvent == KEY_UP )
		{
			switch( Event.usParam )
			{
				case ESC:
					SetImportExitScreen( MAINMENU_SCREEN );
					break;
			}
		}
	}
}



void BtnIJS_StartFreshCallback(GUI_BUTTON *btn,INT32 reason)
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		SetImportExitScreen( GAME_INIT_OPTIONS_SCREEN );

		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE)
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
} 



void BtnIJS_ImportCallback(GUI_BUTTON *btn,INT32 reason)
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		gubImportState = IMPORT_IMPORT_DIALOG;

		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE)
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
} 



void BtnIJS_CancelCallback(GUI_BUTTON *btn,INT32 reason)
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		SetImportExitScreen( MAINMENU_SCREEN );

		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE)
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
} 

