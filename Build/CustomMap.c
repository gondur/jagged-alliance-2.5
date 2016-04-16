#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
	#include "CustomMap.h"
	#include "CustomMapHeader.h"
	#include "Ja25 Strategic Ai.h"
#else
	#include "Screens.h"
#endif

#include "_Ja25EnglishText.h"

CHAR8		gzCurrentCampaign[200];
CHAR8		gzMapsDirectory[512];
CHAR8		gzDefaultMapsDirectory[] = { "Campaigns\\Unfinished Business" };


extern void	FailedLoadingGameCallBack( UINT8 bExitValue );


// ATE: Function to get maps directory

BOOLEAN LoadCampaignString( )
{
	CHAR8 zCampaignName[500], zExeDir[500], zIniFile[500];

	GetExecutableDirectory( zExeDir );

	sprintf( zIniFile, "%s\\Campaign.ini", zExeDir );

	GetPrivateProfileString( "Campaigns", "Current Campaign", "Unfinished Business", zCampaignName, sizeof( zCampaignName ), zIniFile );
	
	return( SetCampaignString( zCampaignName , FALSE ) );
}



BOOLEAN SetCampaignString( CHAR8 *pzString, BOOLEAN fFromSaveScreen )
{
	CHAR8 zExeDir[500], zTempDir[500];
	CHAR8	zOldCurrentCampaign[100], zOldMapsDir[500];

	// ATE;make backups
	strcpy( zOldCurrentCampaign, gzCurrentCampaign );
	strcpy( zOldMapsDir, gzMapsDirectory );

	GetExecutableDirectory( zExeDir );

	strcpy( gzCurrentCampaign, pzString );

	sprintf( gzMapsDirectory, "Campaigns\\%s", gzCurrentCampaign );

	// ATE: Validate name length
	if ( strlen( gzCurrentCampaign ) > 30 )
	{
		// ATE; restore backups
		strcpy( gzCurrentCampaign, zOldCurrentCampaign );
		strcpy( gzMapsDirectory, zOldMapsDir );

		if ( !fFromSaveScreen )
		{
			// end with error
			CHAR8	zErrorMessage[256];
			sprintf( zErrorMessage, "%S", zNewTacticalMessages[ TCTL_MSG__CAMPAIGN_NAME_TOO_LARGE ] );

			// Pop up message boc and get answer....
			if ( MessageBox( NULL, zErrorMessage, "Jagged Alliance 2:UB", MB_OK ) == IDOK )
			{
				return( FALSE );
			}
		}
		else
		{
			CHAR16	zErrorMessage[256];
			swprintf( zErrorMessage, L"%s", zNewTacticalMessages[ TCTL_MSG__CAMPAIGN_NAME_TOO_LARGE ] );

			DoSaveLoadMessageBox( MSG_BOX_BASIC_STYLE, zErrorMessage, SAVE_LOAD_SCREEN, MSG_BOX_FLAG_OK, FailedLoadingGameCallBack );

			return( FALSE );
		}	
	}


	// ATE: If the standard campaign, make directories
	if ( InDefaultCampaign( ) )
	{
		sprintf( zTempDir, "%s\\Data\\Campaigns", zExeDir );
		CreateDirectory( zTempDir, NULL );

		sprintf( zTempDir, "%s\\Data\\Campaigns\\Unfinished Business", zExeDir );
		CreateDirectory( zTempDir, NULL );
	}


	sprintf( zTempDir, "%s\\Data\\%s", zExeDir, gzMapsDirectory );

	// Check if the directory exists!
	if( !DirectoryExists( zTempDir ) || strlen( pzString ) == 0 )
	{
		// ATE; restore backups
		strcpy( gzCurrentCampaign, zOldCurrentCampaign );
		strcpy( gzMapsDirectory, zOldMapsDir );

		if ( !fFromSaveScreen )
		{
			// end with error
			CHAR8	zErrorMessage[256];
			sprintf( zErrorMessage, "%S", zNewTacticalMessages[ TCTL_MSG__CAMPAIGN_DOESN_T_EXIST ] );

			// Pop up message boc and get answer....
			if ( MessageBox( NULL, zErrorMessage, "Jagged Alliance 2:UB", MB_OK ) == IDOK )
			{
				return( FALSE );
			}	
		}
		else
		{
			// end with error
			CHAR16	zErrorMessage[256];
			swprintf( zErrorMessage, L"%s", zNewTacticalMessages[ TCTL_MSG__CAMPAIGN_DOESN_T_EXIST ] );

			DoSaveLoadMessageBox( MSG_BOX_BASIC_STYLE, zErrorMessage, SAVE_LOAD_SCREEN, MSG_BOX_FLAG_OK, FailedLoadingGameCallBack );

			return( FALSE );
		}
	}

	// ATE: Now check, if we are going into the editor, and we have the default campaign, spew message
	if ( gfIntendOnEnteringEditor && InDefaultCampaign( ) )
	{
		// Pop up message boc and get answer....
		CHAR8	zErrorMessage[256];
		sprintf( zErrorMessage, "%S", zNewTacticalMessages[ TCTL_MSG__CANT_EDIT_DEFAULT ] );
		if ( MessageBox( NULL, zErrorMessage, "Jagged Alliance 2:UB", MB_OK ) == IDOK )
		{
			return( FALSE );
		}	
	}

	return( TRUE );
}


CHAR8 *GetMapsDirectory( )
{
	return( gzMapsDirectory );
}

CHAR8 *GetDefaultMapsDirectory( )
{
	return( gzDefaultMapsDirectory );
}

CHAR8 *GetCurrentCampaign( )
{
	return( gzCurrentCampaign );
}

BOOLEAN InDefaultCampaign( )
{
	if ( stricmp( gzCurrentCampaign, "Unfinished Business" ) == 0 )
	{
		return( TRUE );
	}
	else
	{
		return( FALSE );
	}
}	

#ifdef	ENABLE_CUSTOM_MAP_INTERFACE




//** Defines *******************************************************************

//enums for strings that can be in the ini file
enum
{
	CM_INI__NUM_MAPS,
	CM_INI__GET_SECTOR_X_Y_Z,
	CM_INI__MAP_NAME,
	CM_INI__INDIVIDUAL_MAP_INFO,
	CM_INI__NUM_ELITES,
	CM_INI__NUM_REGULAR,
	CM_INI__NUM_ADMINS,
	CM_INI__NUM_BLOODCATS,
};

#define		CM_INI__SECTION_NAME__GENERAL		"General"
#define		CM_INI__SECTION_MAP_NAME				"MAP"


//** Global Variables  *********************************************************

//extern	BOOLEAN sBadSectorsList[ WORLD_MAP_X ][ WORLD_MAP_X ];

UINT8				gubCustomMapExitScreen=CUSTOM_MAP_LOAD_SCREEN;
BOOLEAN			gfCustomMapExit=FALSE;
BOOLEAN			gfCustomMapEntry=TRUE;
BOOLEAN			gfRenderCustomMap=TRUE;

CUSTOM_MAP_HEADER_STRUCT		gSelectedCustomScenario;


//** Prototypes ****************************************************************

BOOLEAN			EnterCustomMap();
void				GetCustomMapUserInput();
void				ExitCustomMap();
void				SetCustumMapExitScreen( UINT32 uiNewScreen );
BOOLEAN			RenderCustomMap();
void				HandleCustomMap();
BOOLEAN			TempSelectMap();
BOOLEAN			AllocateMapNameForCustomMap( CHAR8 **ppFileName, UINT32 uiSizeOfString );
void				DeAllocateMapNameForCustomMap( CHAR8 **ppFileName );
BOOLEAN			GetStringForCustomMapIniFile( UINT32 uiTypeOfString, CHAR8 *pString, UINT32 *pData1, UINT32 *pData2, UINT32 *pData3 );
BOOLEAN			GetAllMapInfoFromIniFile( UINT32 uiNumMaps );
void				SetUpCustomMapScreenBadSectorList();
BOOLEAN			GetSectorsEnemyValues( UINT32 uiMapNum );
//ppp




//** Functions  ****************************************************************




UINT32	CustomMapInit( void )
{
	memset( &gSelectedCustomScenario, 0, sizeof( CUSTOM_MAP_STRUCT ) );
	gSelectedCustomScenario.iCurrentMap = -1;

	return( 1 );
}



UINT32	CustomMapHandle( void )
{
	StartFrameBufferRender();

	if( gfCustomMapEntry )
	{
		gubCustomMapExitScreen=CUSTOM_MAP_LOAD_SCREEN;
		EnterCustomMap();
		gfCustomMapEntry = FALSE;
		gfCustomMapExit = FALSE;
		InvalidateRegion( 0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT );
	}

	//Get any keyboard events
	GetCustomMapUserInput();
	

	HandleCustomMap();

	// render buttons marked dirty	
	MarkButtonsDirty( );
	RenderButtons( ); 

	ExecuteBaseDirtyRectQueue();
	EndFrameBufferRender();

	if ( HandleFadeOutCallback( ) )
	{
		ClearMainMenu();
		return( gubCustomMapExitScreen );
	}


	if( gfCustomMapExit )
	{
		ExitCustomMap();
		gfCustomMapEntry = TRUE;
	}


	return( gubCustomMapExitScreen );
}


UINT32	CustomMapShutdown( void )
{
	return( 1 );
}





BOOLEAN EnterCustomMap()
{
	ClearMainMenu();

	gfRenderCustomMap = TRUE;

	//Remember that the player is using custom maps
	gJa25SaveStruct.fInCustomMap = TRUE;
	return( TRUE );
}


void ExitCustomMap()
{
}

void HandleCustomMap()
{
	//if we are to render the interface
	if( gfRenderCustomMap )
	{
		RenderCustomMap();

		gfRenderCustomMap = FALSE;
	}
}

BOOLEAN RenderCustomMap()
{
	//Display Title
	DrawTextToScreen( L"Choose Custom Scenario", 0, 30, SCREEN_BUFFER_WIDTH, FONT14ARIAL, FONT_GREEN, FONT_MCOLOR_BLACK, FALSE, CENTER_JUSTIFIED	);

	InvalidateRegion( 0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT );

	return( TRUE );
}

void GetCustomMapUserInput()
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
					gfRenderCustomMap = TRUE;
					break;
				case 'b':
					SetCustumMapExitScreen( CUSTOM_MAP_BRIEFING_SCREEN );
					break;
				case '1':
					TempSelectMap();
					break;
#endif

				case ESC:
					//Cancel back to the Mainmenu
					SetCustumMapExitScreen( MAINMENU_SCREEN );
					break;
			}
		}
	}
}


void SetCustumMapExitScreen( UINT32 uiNewScreen )
{
	gubCustomMapExitScreen = uiNewScreen;

	gfCustomMapExit= TRUE;

	//if the player is cancelling back to the main menu
	if( uiNewScreen == MAINMENU_SCREEN )
	{
		//clear the flag satying we are in a custom map
		gJa25SaveStruct.fInCustomMap = FALSE;
	}
}






BOOLEAN	BuildListOfCustomScenarios()
{
	//loop through the dir and determine all the legit custom maps


	return( TRUE );
}

BOOLEAN TempSelectMap()
{
//	char zTemp[128];

	strcpy( gSelectedCustomScenario.zScenarioDirName, "Test" );

/*
	if( gSelectedCustomScenario.zScenarioDirName != NULL )
	{
		DeAllocateMapNameForCustomMap( &gSelectedCustomScenario.zScenarioDirName );
	}

	AllocateMapNameForCustomMap( &gSelectedCustomScenario.zScenarioDirName, gSelectedCustomScenario.iNumberOfMaps );
*/

//	sprintf( &gSelectedCustomScenario, "%s\\%s\\", CM__CUSTOM_MAP_DIR_NAME, "Test.dat" );
	gSelectedCustomScenario.iCurrentMap = 0;
	gSelectedCustomScenario.uiFlags	= 0;


	//Get the number of maps
	if( !GetStringForCustomMapIniFile( CM_INI__NUM_MAPS, NULL, &gSelectedCustomScenario.iNumberOfMaps, NULL, NULL ) )
	{
		return( FALSE );
	}

	//Get all the informaiton from the scenario's INI file
	if( !GetAllMapInfoFromIniFile( gSelectedCustomScenario.iNumberOfMaps ) )
	{
		return( FALSE );
	}

	//Set up the bad sector list ( used in mapscreen ) for all the maps
	SetUpCustomMapScreenBadSectorList();

	return( TRUE );
}

void GetCustomMapName( UINT32 uiSectorX, UINT32 uiSectorY, UINT32 uiSectorZ )
{

	// This is the string to return, but...
//	sprintf( bString, "%S%s%s%s.DAT", JA25_EXP_MAP_NAME_PREFIX, pVertStrings[uiSectorY], pHortStrings[uiSectorX], bExtensionString );

}

BOOLEAN	AllocateMapNameForCustomMap( CHAR8 **ppFileName, UINT32 uiSizeOfString )
{
//	if( ppFileName == NULL )
//		return( FALSE );

	*ppFileName = ( CHAR8 *) MemAlloc( uiSizeOfString );
	if( *ppFileName == NULL )
	{
		return( FALSE );
	}

//	memset( ppFileName, 0, uiSizeOfString );

	return( TRUE );
}

void DeAllocateMapNameForCustomMap( CHAR8 **ppFileName )
{
	MemFree( *ppFileName );
	*ppFileName = NULL;
}



BOOLEAN	GetStringForCustomMapIniFile( UINT32 uiTypeOfString, CHAR8 *pString, UINT32 *pData1, UINT32 *pData2, UINT32 *pData3 )
{
	CHAR8	zSectionName[128];
	CHAR8	zKeyName[128];
	CHAR	zReturnedString[CMS_SIZE_OF_STRING];
	CHAR	zFileName[512];
	UINT32	uiData1, uiData2, uiData3;
	UINT32 uiRetVal=0;

	sprintf( zFileName, "%s\\%s\\%s.ini", CM__CUSTOM_MAP_DIR_NAME, gSelectedCustomScenario.zScenarioDirName, gSelectedCustomScenario.zScenarioDirName );

	switch( uiTypeOfString )
	{
		case CM_INI__GET_SECTOR_X_Y_Z:
			if( pData1 == NULL || pData2 == NULL || pData3 == NULL )
			{
				return( FALSE );
			}

			sprintf( zSectionName, "%s", CM_INI__SECTION_NAME__GENERAL );
			sprintf( zKeyName, "%s", "SectorXYZ" );
			break;

		case CM_INI__NUM_MAPS:
			if( pData1 == NULL )
			{
				return( FALSE );
			}

			sprintf( zSectionName, "%s", CM_INI__SECTION_NAME__GENERAL );
			sprintf( zKeyName, "%s", "NumMaps" );
			break;

		case CM_INI__INDIVIDUAL_MAP_INFO:
			if( pData1 == NULL || pData2 == NULL || pData3 == NULL )
			{
				return( FALSE );
			}

			sprintf( zSectionName, "MAP_%d", *pData1 );
			sprintf( zKeyName, "%s", "SectorXYZ" );
			break;

		case CM_INI__MAP_NAME:
			if( pData1 == NULL || pString == NULL )
			{
				return( FALSE );
			}

			sprintf( zSectionName, "MAP_%d", *pData1 );
			sprintf( zKeyName, "%s", "name" );
			break;

		case CM_INI__NUM_ELITES:
			if( pData1 == NULL )
			{
				return( FALSE );
			}

			sprintf( zSectionName, "MAP_%d", *pData1 );
			sprintf( zKeyName, "%s", "Elites" );
			break;

		case CM_INI__NUM_REGULAR:
			if( pData1 == NULL )
			{
				return( FALSE );
			}

			sprintf( zSectionName, "MAP_%d", *pData1 );
			sprintf( zKeyName, "%s", "Regular" );
			break;

		case CM_INI__NUM_ADMINS:
			if( pData1 == NULL )
			{
				return( FALSE );
			}

			sprintf( zSectionName, "MAP_%d", *pData1 );
			sprintf( zKeyName, "%s", "Admins" );
			break;

		case CM_INI__NUM_BLOODCATS:
			if( pData1 == NULL )
			{
				return( FALSE );
			}

			sprintf( zSectionName, "MAP_%d", *pData1 );
			sprintf( zKeyName, "%s", "BloodCats" );
			break;


		//Not in switch
		default:
			Assert( 0 );
			return( FALSE );
	}

	uiRetVal = GetPrivateProfileString( zSectionName, zKeyName, "", zReturnedString, CMS_SIZE_OF_STRING, zFileName );
	if( uiRetVal == 0 )
	{
		UINT32 uiLastError = GetLastError();
		char zString[1024];
		FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, 0, uiLastError, 0, zString, 1024, NULL);
		return( FALSE );
	}


	//Act on the string returned
	switch( uiTypeOfString )
	{
		case CM_INI__INDIVIDUAL_MAP_INFO:
		case CM_INI__GET_SECTOR_X_Y_Z:
			sscanf( zReturnedString, "%d %d %d", &uiData1, &uiData2, &uiData3 );
			*pData1 = uiData1;
			*pData2 = uiData2;
			*pData3 = uiData3;
			break;

		case CM_INI__NUM_MAPS:
			sscanf( zReturnedString, "%d", &uiData1 );
			*pData1 = uiData1;
			break;

		case CM_INI__MAP_NAME:
			strcpy( pString, zReturnedString );
			break;

		case CM_INI__NUM_ELITES:
		case CM_INI__NUM_REGULAR:
		case CM_INI__NUM_ADMINS:
		case CM_INI__NUM_BLOODCATS:
			sscanf( zReturnedString, "%d", &uiData1 );
			*pData1 = uiData1;
			break;

		//Not in switch
		default:
			Assert( 0 );
			return( FALSE );
	}

	return( TRUE );
}


BOOLEAN	GetAllMapInfoFromIniFile( UINT32 uiNumMaps )
{
	UINT32 uiCnt;
	CHAR8	zMapNum[256];
	CHAR8	zMapName[256];
	UINT32	uiMapNum=0;
	UINT32	uiTemp1, uiTemp2, uiTemp3;

	//
	// Allocate memory for all the maps
	//
	gSelectedCustomScenario.pMap = MemAlloc( sizeof ( CUSTOM_MAP_STRUCT ) * uiNumMaps );
	if( gSelectedCustomScenario.pMap == NULL )
	{
		return( FALSE );
	}
	memset( gSelectedCustomScenario.pMap, 0, sizeof ( CUSTOM_MAP_STRUCT ) * uiNumMaps );

	
	//
	// loop through all the maps and fill out the info
	//
	for( uiCnt=0,uiMapNum=1; uiCnt<uiNumMaps; uiCnt++, uiMapNum++ )
	{
		//
		// Get the map name
		//
		sprintf( zMapNum, "%s_%d", CM_INI__SECTION_MAP_NAME, uiMapNum );
		if( !GetStringForCustomMapIniFile( CM_INI__MAP_NAME, zMapName, &uiMapNum, NULL, NULL ) )
		{
			return( FALSE );
		}

		if( !AllocateMapNameForCustomMap( &gSelectedCustomScenario.pMap[ uiCnt ].pFileNameArray, strlen( zMapName + 1 ) ) )
		{
			return( FALSE );
		}
		strcpy( gSelectedCustomScenario.pMap[ uiCnt ].pFileNameArray, zMapName );


		//
		// Get this particular sectors X, Y and Z value
		//
		uiTemp1 = uiMapNum;
		if( !GetStringForCustomMapIniFile( CM_INI__INDIVIDUAL_MAP_INFO, NULL, 
											&uiTemp1, &uiTemp2, &uiTemp3 ) )
		{
			return( FALSE );
		}

		//Assign the map values
		gSelectedCustomScenario.pMap[ uiCnt ].sSectorX = uiTemp1; 
		gSelectedCustomScenario.pMap[ uiCnt ].sSectorY = uiTemp2;
		gSelectedCustomScenario.pMap[ uiCnt ].sSectorZ = uiTemp3;


		//
		// Get this particular sectors enemy values
		//
		if( !GetSectorsEnemyValues( uiMapNum ) )
		{
			return( FALSE );
		}
	}


	return( TRUE );
}

void SetUpCustomMapScreenBadSectorList()
{
	INT32 iCnt;

	//Clear the list
//	memset( &sBadSectorsList, 1, sizeof( sBadSectorsList ) );

	//Loop through the list of sectors that are valid and mark them as such
	for( iCnt=0; iCnt<gSelectedCustomScenario.iNumberOfMaps; iCnt++ )
	{
//		sBadSectorsList[ gSelectedCustomScenario.pMap[ iCnt ].sSectorX ][ gSelectedCustomScenario.pMap[ iCnt ].sSectorY ] = FALSE;
	}
}

BOOLEAN GetSectorsEnemyValues( UINT32 uiMapNum )
{
	UINT32	uiTemp1;
	INT16		sSectorX,sSectorY,sSectorZ;
	UINT8		ubNumAdmins, ubNumRegulars, ubNumElites;

	//Get this sector XYZ values
	sSectorX = gSelectedCustomScenario.pMap[ uiMapNum - 1 ].sSectorX;
	sSectorY = gSelectedCustomScenario.pMap[ uiMapNum - 1 ].sSectorY;
	sSectorZ = gSelectedCustomScenario.pMap[ uiMapNum - 1 ].sSectorZ;

	//
	// Elites
	//
	uiTemp1 = uiMapNum;
	if( !GetStringForCustomMapIniFile( CM_INI__NUM_ELITES, NULL, &uiTemp1, NULL, NULL ) )
	{
		return( FALSE );
	}
	ubNumElites = (UINT8)uiTemp1;

	//
	// Regulars
	//
	uiTemp1 = uiMapNum;
	if( !GetStringForCustomMapIniFile( CM_INI__NUM_REGULAR, NULL, &uiTemp1, NULL, NULL ) )
	{
		return( FALSE );
	}
	ubNumRegulars = (UINT8)uiTemp1;

	//
	// Admins
	//
	uiTemp1 = uiMapNum;
	if( !GetStringForCustomMapIniFile( CM_INI__NUM_ADMINS, NULL, &uiTemp1, NULL, NULL ) )
	{
		return( FALSE );
	}
	ubNumAdmins = (UINT8)uiTemp1;

		
	SetNumberJa25EnemiesInSector( sSectorX, sSectorY, (INT8)sSectorZ, ubNumAdmins, ubNumRegulars, ubNumElites );

/*
	//
	// Bloodcats
	//
	uiTemp1 = uiMapNum;
	if( !GetStringForCustomMapIniFile( CM_INI__NUM_BLOODCATS, NULL, &uiTemp1, NULL, NULL ) )
	{
		return( FALSE );
	}
	SetNumberOfJa25BloodCatsInSector( INT32 iSectorID, INT8 bNumBloodCats, INT8 bBloodCatPlacements );
*/


	return( TRUE );
}


#endif