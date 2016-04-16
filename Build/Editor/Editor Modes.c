#ifdef PRECOMPILEDHEADERS
	#include "Editor All.h"
#else
	#include "builddefines.h"
#endif


#ifdef JA2EDITOR

#ifndef PRECOMPILEDHEADERS
	#include "types.h"
	#include "Editor Modes.h"
	#include "Editor Taskbar Utils.h"
	#include "EditorDefines.h"
	#include "EditorItems.h"
	#include "EditorBuildings.h"
	#include "EditorTerrain.h"
	#include "Cursor Modes.h"
	#include "Map Information.h"
	#include "editscreen.h"
	#include "selectwin.h"
	#include "environment.h"
	#include "worlddef.h"
	#include "Exit Grids.h"
	#include "Worldman.h"
#endif
	#include "strategic.h"
	#include "Loading Screen.h"

BOOLEAN gfShowExitGrids = FALSE;

INT8		gbInsertionCode = INSERTION_CODE_EAST;
INT16	gsInsertionGridNo = -1;

void DisplayInsertionInfo();
void DisplayLoadingScreenInfo( );

void SetEditorItemsTaskbarMode( UINT16 usNewMode )
{
	UnclickEditorButtons( ITEMS_WEAPONS, ITEMS_TRIGGERS );

	switch( usNewMode )
	{
		case ITEMS_WEAPONS:
			ClickEditorButton( ITEMS_WEAPONS );
			iEditorToolbarState = TBAR_MODE_ITEM_WEAPONS;
			break;
		case ITEMS_AMMO:
			ClickEditorButton( ITEMS_AMMO );
			iEditorToolbarState = TBAR_MODE_ITEM_AMMO;
			break;
		case ITEMS_ARMOUR:
			ClickEditorButton( ITEMS_ARMOUR );
			iEditorToolbarState = TBAR_MODE_ITEM_ARMOUR;
			break;
		case ITEMS_EXPLOSIVES:
			ClickEditorButton( ITEMS_EXPLOSIVES );
			iEditorToolbarState = TBAR_MODE_ITEM_EXPLOSIVES;
			break;
		case ITEMS_EQUIPMENT1:
			ClickEditorButton( ITEMS_EQUIPMENT1 );
			iEditorToolbarState = TBAR_MODE_ITEM_EQUIPMENT1;
			break;
		case ITEMS_EQUIPMENT2:
			ClickEditorButton( ITEMS_EQUIPMENT2 );
			iEditorToolbarState = TBAR_MODE_ITEM_EQUIPMENT2;
			break;
		case ITEMS_EQUIPMENT3:
			ClickEditorButton( ITEMS_EQUIPMENT3 );
			iEditorToolbarState = TBAR_MODE_ITEM_EQUIPMENT3;
			break;
		case ITEMS_TRIGGERS:
			ClickEditorButton( ITEMS_TRIGGERS );
			iEditorToolbarState = TBAR_MODE_ITEM_TRIGGERS;
			break;
//		case ITEMS_KEYS:
//			ClickEditorButton( ITEMS_KEYS );
//			iEditorToolbarState = TBAR_MODE_ITEM_KEYS;
//			break;
	}
}

#define NO_EFFECT			2

void SetEditorBuildingTaskbarMode( UINT16 usNewMode )
{
	BOOLEAN fNewGroup = FALSE;
	BOOLEAN fNewRoofs, fNewWalls, fNewRoomInfo;
	if( usNewMode == usCurrentMode )
	{
		ClickEditorButton( usNewMode );
		return;
	}
	usCurrentMode = usNewMode;
	//Unclick all of the building section buttons first -- except the view modes.
	UnclickEditorButton( BUILDING_PLACE_WALLS );
	UnclickEditorButton( BUILDING_PLACE_DOORS );
	UnclickEditorButton( BUILDING_PLACE_WINDOWS );
	UnclickEditorButton( BUILDING_PLACE_ROOFS );
	UnclickEditorButton( BUILDING_PLACE_BROKEN_WALLS );
	UnclickEditorButton( BUILDING_PLACE_FURNITURE );
	UnclickEditorButton( BUILDING_PLACE_DECALS );
	UnclickEditorButton( BUILDING_PLACE_FLOORS );
	UnclickEditorButton( BUILDING_PLACE_TOILETS );
	UnclickEditorButton( BUILDING_SMART_WALLS );
	UnclickEditorButton( BUILDING_SMART_DOORS );
	UnclickEditorButton( BUILDING_SMART_WINDOWS );
	UnclickEditorButton( BUILDING_SMART_BROKEN_WALLS );
//	UnclickEditorButton( BUILDING_DOORKEY );
	UnclickEditorButton( BUILDING_NEW_ROOM );
	UnclickEditorButton( BUILDING_NEW_ROOF );
	UnclickEditorButton( BUILDING_CAVE_DRAWING );
	UnclickEditorButton( BUILDING_SAW_ROOM );
	UnclickEditorButton( BUILDING_KILL_BUILDING );
	UnclickEditorButton( BUILDING_COPY_BUILDING );
	UnclickEditorButton( BUILDING_MOVE_BUILDING );
	UnclickEditorButton( BUILDING_DRAW_ROOMNUM );
	UnclickEditorButton( BUILDING_TOGGLE_ERASEMODE );
	UnclickEditorButton( BUILDING_ERASE_ROOMNUM );

	ClickEditorButton( usNewMode );

	gfRenderDrawingMode = TRUE;

	//Clicking on certain buttons will automatically activate/deactive certain views.
	switch( usNewMode )
	{
		case BUILDING_KILL_BUILDING://Show everything
			fNewWalls = TRUE;
			fNewRoofs = TRUE;
			fNewRoomInfo = TRUE;
			break;
		case BUILDING_NEW_ROOF:
		case BUILDING_PLACE_ROOFS:
			fNewWalls = TRUE;
			fNewRoofs = TRUE;
			fNewRoomInfo = FALSE;
			break;
		case BUILDING_DRAW_ROOMNUM: //Show room info
		case BUILDING_ERASE_ROOMNUM: //Show room info
			fNewWalls = NO_EFFECT;
			fNewRoofs = gfBasement ? TRUE : FALSE;
			fNewRoomInfo = TRUE;
			break;
		case BUILDING_PLACE_DOORS:
		case BUILDING_PLACE_WINDOWS:
		case BUILDING_PLACE_WALLS:
		case BUILDING_PLACE_BROKEN_WALLS:
		case BUILDING_PLACE_FLOORS:
		case BUILDING_PLACE_TOILETS:
		case BUILDING_PLACE_FURNITURE:
		case BUILDING_PLACE_DECALS:
		case BUILDING_SMART_WALLS:
		case BUILDING_SMART_DOORS:
		case BUILDING_SMART_WINDOWS:
		case BUILDING_SMART_BROKEN_WALLS:
//		case BUILDING_DOORKEY:
		case BUILDING_SAW_ROOM:
		case BUILDING_NEW_ROOM:
		case BUILDING_COPY_BUILDING:
		case BUILDING_MOVE_BUILDING:
		case BUILDING_CAVE_DRAWING:
			fNewRoofs = gfBasement ? TRUE : FALSE;
			fNewWalls =	TRUE;
			fNewRoomInfo = FALSE;
			if( usNewMode == BUILDING_PLACE_FLOORS )
				gusSelectionType = gusSavedSelectionType;
			break;
		default:
			return;
	}
	UnclickEditorButton( BUILDING_TOGGLE_INFO_VIEW );
	if( fNewWalls != NO_EFFECT && fNewWalls != fBuildingShowWalls )
	{
		if( fNewWalls )
			ClickEditorButton( BUILDING_TOGGLE_WALL_VIEW );
		else
			UnclickEditorButton( BUILDING_TOGGLE_WALL_VIEW );
		fBuildingShowWalls = fNewWalls;
		UpdateWallsView();
	}
	if( fNewRoofs != NO_EFFECT && fNewRoofs != fBuildingShowRoofs )
	{
		if( fNewRoofs )
			ClickEditorButton( BUILDING_TOGGLE_ROOF_VIEW );
		else
			UnclickEditorButton( BUILDING_TOGGLE_ROOF_VIEW );
		fBuildingShowRoofs = fNewRoofs;
		UpdateRoofsView();
	}
	if( fNewRoomInfo != NO_EFFECT && fNewRoomInfo != fBuildingShowRoomInfo )
	{
		if( fNewRoomInfo )
			ClickEditorButton( BUILDING_TOGGLE_INFO_VIEW );
		else
			UnclickEditorButton( BUILDING_TOGGLE_INFO_VIEW );
		fBuildingShowRoomInfo = fNewRoomInfo;
		gfRenderWorld = TRUE;
	}
}

void SetEditorTerrainTaskbarMode( UINT16 usNewMode )
{
	UnclickEditorButton( TERRAIN_FGROUND_TEXTURES );
	UnclickEditorButton( TERRAIN_BGROUND_TEXTURES );
	UnclickEditorButton( TERRAIN_PLACE_CLIFFS );
	UnclickEditorButton( TERRAIN_PLACE_DEBRIS );
	UnclickEditorButton( TERRAIN_PLACE_TREES );
	UnclickEditorButton( TERRAIN_PLACE_ROCKS );
	UnclickEditorButton( TERRAIN_PLACE_MISC );
	UnclickEditorButton( TERRAIN_FILL_AREA );
	UnclickEditorButton( TERRAIN_PLACE_ROADS );
	TerrainTileDrawMode=0;

	gfRenderDrawingMode = TRUE;

	switch( usNewMode )
	{
		case TERRAIN_FGROUND_TEXTURES:
			TerrainTileDrawMode = TERRAIN_TILES_FOREGROUND;
			ClickEditorButton( TERRAIN_FGROUND_TEXTURES );
			iDrawMode = DRAW_MODE_GROUND;
			gusSelectionType = gusSavedSelectionType;
			gfRenderTaskbar = TRUE;
			break;
		case TERRAIN_BGROUND_TEXTURES:
			TerrainTileDrawMode = TERRAIN_TILES_BACKGROUND;
			ClickEditorButton( TERRAIN_BGROUND_TEXTURES );
			iDrawMode = DRAW_MODE_NEW_GROUND;
			break;
		case TERRAIN_PLACE_CLIFFS:
			ClickEditorButton( TERRAIN_PLACE_CLIFFS );
			iDrawMode = DRAW_MODE_BANKS;
			break;
		case TERRAIN_PLACE_ROADS:
			ClickEditorButton( TERRAIN_PLACE_ROADS );
			iDrawMode = DRAW_MODE_ROADS;
			break;
		case TERRAIN_PLACE_DEBRIS:
			ClickEditorButton( TERRAIN_PLACE_DEBRIS );
			iDrawMode = DRAW_MODE_DEBRIS;
			gusSelectionType = gusSavedSelectionType;
			gfRenderTaskbar = TRUE;
			break;
		case TERRAIN_PLACE_TREES:
			ClickEditorButton( TERRAIN_PLACE_TREES );
			iDrawMode = DRAW_MODE_OSTRUCTS;
			gusSelectionType = gusSavedSelectionType;
			gfRenderTaskbar = TRUE;
			break;
		case TERRAIN_PLACE_ROCKS:
			ClickEditorButton( TERRAIN_PLACE_ROCKS );
			iDrawMode = DRAW_MODE_OSTRUCTS1;
			gusSelectionType = gusSavedSelectionType;
			gfRenderTaskbar = TRUE;
			break;
		case TERRAIN_PLACE_MISC:
			ClickEditorButton( TERRAIN_PLACE_MISC );
			iDrawMode = DRAW_MODE_OSTRUCTS2;
			gusSelectionType = gusSavedSelectionType;
			gfRenderTaskbar = TRUE;
			break;
		case TERRAIN_FILL_AREA:
			ClickEditorButton( TERRAIN_FILL_AREA );
			iDrawMode = DRAW_MODE_FILL_AREA + DRAW_MODE_GROUND;
			TerrainTileDrawMode=1;
			break;
	}
}

void ShowExitGrids()
{
	UINT16 i;
	LEVELNODE *pLevelNode;
	if( gfShowExitGrids )
		return;
	gfShowExitGrids = TRUE;
	for( i = 0; i < WORLD_MAX; i++ )
	{
		if( GetExitGridLevelNode( i, &pLevelNode ) )
		{
			AddTopmostToTail( i, FIRSTPOINTERS8 );
		}
	}
}

void HideExitGrids()
{
	UINT16 i;
	LEVELNODE *pLevelNode;
	if( !gfShowExitGrids )
		return;
	gfShowExitGrids = FALSE;
	for( i = 0; i < WORLD_MAX; i++ )
	{
		if( GetExitGridLevelNode( i, &pLevelNode ) )
		{
			pLevelNode = gpWorldLevelData[ i ].pTopmostHead;
			while( pLevelNode )
			{
				if( pLevelNode->usIndex == FIRSTPOINTERS8 )
				{
					RemoveTopmost( i, pLevelNode->usIndex );
					break;
				}
				pLevelNode = pLevelNode->pNext;
			}
		}
	}
}

void SetEditorMapInfoTaskbarMode( UINT16 usNewMode )
{
	BOOLEAN fShowExitGrids = FALSE;
	UnclickEditorButton( MAPINFO_ADD_LIGHT1_SOURCE );
	UnclickEditorButton( MAPINFO_DRAW_EXITGRIDS );
	UnclickEditorButton( MAPINFO_NORTH_POINT );
	UnclickEditorButton( MAPINFO_WEST_POINT );
	UnclickEditorButton( MAPINFO_CENTER_POINT );
	UnclickEditorButton( MAPINFO_EAST_POINT );
	UnclickEditorButton( MAPINFO_SOUTH_POINT );
	UnclickEditorButton( MAPINFO_ISOLATED_POINT );
	ClickEditorButton( usNewMode );
	switch( usNewMode )
	{
		case MAPINFO_ADD_LIGHT1_SOURCE:
			iDrawMode = DRAW_MODE_LIGHT;
			break;
		case MAPINFO_DRAW_EXITGRIDS:
			iDrawMode = DRAW_MODE_EXITGRID;
			gusSelectionType = gusSavedSelectionType;
			fShowExitGrids = TRUE;
			gfRenderTaskbar = TRUE;
			break;
		case MAPINFO_NORTH_POINT:
			iDrawMode = DRAW_MODE_NORTHPOINT;
			break;
		case MAPINFO_WEST_POINT:
			iDrawMode = DRAW_MODE_WESTPOINT;
			break;
		case MAPINFO_EAST_POINT:
			iDrawMode = DRAW_MODE_EASTPOINT;
			break;
		case MAPINFO_SOUTH_POINT:
			iDrawMode = DRAW_MODE_SOUTHPOINT;
			break;
		case MAPINFO_CENTER_POINT:
			iDrawMode = DRAW_MODE_CENTERPOINT;
			break;
		case MAPINFO_ISOLATED_POINT:
			iDrawMode = DRAW_MODE_ISOLATEDPOINT;
			break;
		case MAPINFO_RADIO_NORMAL:
			SetEditorSmoothingMode( SMOOTHING_NORMAL );
			gfRenderTaskbar = TRUE;
			break;
		case MAPINFO_RADIO_BASEMENT:
			SetEditorSmoothingMode( SMOOTHING_BASEMENT );
			gfRenderTaskbar = TRUE;
			break;
		case MAPINFO_RADIO_CAVES:
			SetEditorSmoothingMode( SMOOTHING_CAVES );
			gfRenderTaskbar = TRUE;
			break;
	}
	if( fShowExitGrids )
	{
		ShowExitGrids();
	}
	else
	{
		HideExitGrids();
	}
}


void SetEditorSmoothingMode( UINT8 ubNewMode )
{
	UnclickEditorButtons( MAPINFO_RADIO_NORMAL, MAPINFO_RADIO_CAVES );
	if( iCurrentTaskbar == TASK_BUILDINGS )
		HideEditorButtons( BUILDING_NEW_ROOM, BUILDING_CAVE_DRAWING );
	gfBasement = FALSE;
	gfCaves = FALSE;
	gMapInformation.ubEditorSmoothingType = SMOOTHING_NORMAL;
	switch( ubNewMode )
	{
		case SMOOTHING_NORMAL:
			ClickEditorButton( MAPINFO_RADIO_NORMAL );
			if( iCurrentTaskbar == TASK_BUILDINGS )
				ShowEditorButtons( BUILDING_NEW_ROOM, BUILDING_MOVE_BUILDING );
			EnableEditorButtons( BUILDING_SMART_WALLS, BUILDING_SMART_BROKEN_WALLS );
			break;
		case SMOOTHING_BASEMENT:
			gfBasement = TRUE;
			ClickEditorButton( MAPINFO_RADIO_BASEMENT );
			if( iCurrentTaskbar == TASK_BUILDINGS )
				ShowEditorButtons( BUILDING_NEW_ROOM, BUILDING_KILL_BUILDING );
			EnableEditorButtons( BUILDING_SMART_WALLS, BUILDING_SMART_BROKEN_WALLS );
			break;
		case SMOOTHING_CAVES:
			gfCaves = TRUE;
			ClickEditorButton( MAPINFO_RADIO_CAVES );
			if( iCurrentTaskbar == TASK_BUILDINGS )
				ShowEditorButton( BUILDING_CAVE_DRAWING );
			DisableEditorButtons( BUILDING_SMART_WALLS, BUILDING_SMART_BROKEN_WALLS );
			break;
		default:
			AssertMsg( 0, "Attempting to set an illegal smoothing mode." );
			break;
	}
	gMapInformation.ubEditorSmoothingType = ubNewMode;
}


void SetupTextInputForOptions()
{
	UINT16 str[10];

	InitTextInputModeWithScheme( DEFAULT_SCHEME );

	AddUserInputField( NULL );  //just so we can use short cut keys while not typing.

	swprintf( str, L"%d", gMapInformation.ubNumAdminsE );
	AddTextInputField( 330, 385, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gMapInformation.ubNumTroopsE );
	AddTextInputField( 330, 400, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gMapInformation.ubNumElitesE );
	AddTextInputField( 330, 415, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gMapInformation.ubNumBloodcatsE );
	AddTextInputField( 330, 430, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );


	swprintf( str, L"%d", gMapInformation.ubNumAdminsN );
	AddTextInputField( 370, 385, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gMapInformation.ubNumTroopsN );
	AddTextInputField( 370, 400, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gMapInformation.ubNumElitesN );
	AddTextInputField( 370, 415, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gMapInformation.ubNumBloodcatsN );
	AddTextInputField( 370, 430, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );


	swprintf( str, L"%d", gMapInformation.ubNumAdminsD );
	AddTextInputField( 410, 385, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gMapInformation.ubNumTroopsD );
	AddTextInputField( 410, 400, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gMapInformation.ubNumElitesD );
	AddTextInputField( 410, 415, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gMapInformation.ubNumBloodcatsD );
	AddTextInputField( 410, 430, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );


	swprintf( str, L"%d", gMapInformation.ubBaseNumEnemies );
	AddTextInputField( 460, 385, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gMapInformation.ubAttackProbabilityRate );
	AddTextInputField( 555, 385, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gMapInformation.ubGracePeriod );
	AddTextInputField( 460, 410, 30, 15, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gsInsertionGridNo );
	AddTextInputField( 555, 440, 30, 15, MSYS_PRIORITY_NORMAL, str, 5, INPUTTYPE_NUMERICSTRICT | INPUTTYPE_FIRSTPOSMINUS );

	AddTextInputField( 5, 375, 110, 15, MSYS_PRIORITY_NORMAL, gMapInformation.zLevelName, 16, INPUTTYPE_ASCII );

}



void UpdateOptions()
{
	SetFont( FONT10ARIAL );
	SetFontShadow( FONT_NEARBLACK );

	SetFontForeground( FONT_YELLOW );
	mprintf( 340, 364, gzEditorStrings[EDITOR_STR_STARTING_POPULATION]);

	mprintf( 335, 375, gzEditorStrings[EDITOR_STR_EASY]);

	mprintf( 370, 375, gzEditorStrings[EDITOR_STR_NORMAL]);

	mprintf( 415, 375, gzEditorStrings[EDITOR_STR_DIFF]);

	mprintf( 283, 388, gzEditorStrings[EDITOR_STR_ADMINS]);

	mprintf( 283, 403, gzEditorStrings[EDITOR_STR_TROOPS]);

	mprintf( 283, 418, gzEditorStrings[EDITOR_STR_ELITES]);

	mprintf( 283, 433, gzEditorStrings[EDITOR_STR_BLOODCATS]);


	mprintf( 500, 364, gzEditorStrings[EDITOR_STR_INVASION_DATA]);

	mprintf( 450, 375, gzEditorStrings[EDITOR_STR_MIN_ENEMIES]);

	mprintf( 520, 375, gzEditorStrings[EDITOR_STR_ATTACK_PROB_RATE]);

	mprintf( 450, 400, gzEditorStrings[EDITOR_STR_GRACE_PERIOD]);

	mprintf( 520, 430, gzEditorStrings[EDITOR_STR_INSERTION_GRIDNO]);

	mprintf(   5, 365, gzEditorStrings[EDITOR_STR_LEVEL_NAME]);

	mprintf(   5, 443, gzEditorStrings[EDITOR_STR_CAMPAIGN], GetCurrentCampaign( ) );



	DisplayInsertionInfo( );

	DisplayLoadingScreenInfo( );

}


void UpdateOptionsFields()
{
	UINT16 str[10];

	//Update the text fields to reflect the validated values.
	//light rgb fields
	swprintf( str, L"%d", gMapInformation.ubNumAdminsE );
	SetInputFieldStringWith16BitString( 1, str );
	swprintf( str, L"%d", gMapInformation.ubNumTroopsE );
	SetInputFieldStringWith16BitString( 2, str );
	swprintf( str, L"%d", gMapInformation.ubNumElitesE );
	SetInputFieldStringWith16BitString( 3, str );
	swprintf( str, L"%d", gMapInformation.ubNumBloodcatsE );
	SetInputFieldStringWith16BitString( 4, str );


	swprintf( str, L"%d", gMapInformation.ubNumAdminsN );
	SetInputFieldStringWith16BitString( 5, str );
	swprintf( str, L"%d", gMapInformation.ubNumTroopsN );
	SetInputFieldStringWith16BitString( 6, str );
	swprintf( str, L"%d", gMapInformation.ubNumElitesN );
	SetInputFieldStringWith16BitString( 7, str );
	swprintf( str, L"%d", gMapInformation.ubNumBloodcatsN );
	SetInputFieldStringWith16BitString( 8, str );


	swprintf( str, L"%d", gMapInformation.ubNumAdminsD );
	SetInputFieldStringWith16BitString( 9, str );
	swprintf( str, L"%d", gMapInformation.ubNumTroopsD );
	SetInputFieldStringWith16BitString( 10, str );
	swprintf( str, L"%d", gMapInformation.ubNumElitesD );
	SetInputFieldStringWith16BitString( 11, str );
	swprintf( str, L"%d", gMapInformation.ubNumBloodcatsD );
	SetInputFieldStringWith16BitString( 12, str );


	swprintf( str, L"%d", gMapInformation.ubBaseNumEnemies );
	SetInputFieldStringWith16BitString( 13, str );

	swprintf( str, L"%d", gMapInformation.ubAttackProbabilityRate );
	SetInputFieldStringWith16BitString( 14, str );

	swprintf( str, L"%d", gMapInformation.ubGracePeriod );
	SetInputFieldStringWith16BitString( 15, str );

	swprintf( str, L"%d", gsInsertionGridNo );
	SetInputFieldStringWith16BitString( 16, str );

	SetInputFieldStringWith16BitString( 17, gMapInformation.zLevelName );
}


void ExtractAndUpdateOptions()
{
	INT32 temp;
	CHAR16 tempWideStr[ 50 ];
	CHAR8	 tempStr[ 50 ];

	temp = min( GetNumericStrictValueFromField( 1 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubNumAdminsE = (UINT8)temp;
	}

	temp = min( GetNumericStrictValueFromField( 2 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubNumTroopsE = (UINT8)temp;
	}

	temp = min( GetNumericStrictValueFromField( 3 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubNumElitesE = (UINT8)temp;
	}

	temp = min( GetNumericStrictValueFromField( 4 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubNumBloodcatsE = (UINT8)temp;
	}



	temp = min( GetNumericStrictValueFromField( 5 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubNumAdminsN = (UINT8)temp;
	}

	temp = min( GetNumericStrictValueFromField( 6 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubNumTroopsN = (UINT8)temp;
	}

	temp = min( GetNumericStrictValueFromField( 7 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubNumElitesN = (UINT8)temp;
	}

	temp = min( GetNumericStrictValueFromField( 8 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubNumBloodcatsN = (UINT8)temp;
	}



	temp = min( GetNumericStrictValueFromField( 9 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubNumAdminsD = (UINT8)temp;
	}

	temp = min( GetNumericStrictValueFromField( 10 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubNumTroopsD = (UINT8)temp;
	}

	temp = min( GetNumericStrictValueFromField( 11 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubNumElitesD = (UINT8)temp;
	}

	temp = min( GetNumericStrictValueFromField( 12 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubNumBloodcatsD = (UINT8)temp;
	}

	temp = min( GetNumericStrictValueFromField( 13 ), 32 );
	if( temp != -1 )
	{
		gMapInformation.ubBaseNumEnemies = (UINT8)temp;
	}

	temp = min( GetNumericStrictValueFromField( 14 ), 100 );
	if( temp != -1 )
	{
		gMapInformation.ubAttackProbabilityRate = (UINT8)temp;
	}

	temp = min( GetNumericStrictValueFromField( 15 ), 100 );
	if( temp != -1 )
	{
		gMapInformation.ubGracePeriod = (UINT8)temp;
	}


	Get16BitStringFromField( 16, tempWideStr );
	sprintf( tempStr, "%S", tempWideStr );
	temp = atoi( tempStr );
	gsInsertionGridNo = (INT16)temp;
	gMapInformation.sInsertionGridNo = gsInsertionGridNo;

	Get16BitStringFromField( 17, gMapInformation.zLevelName );

	if ( gbInsertionCode != INSERTION_AUTO )
	{
		gMapInformation.ubInsertionDirection = gbInsertionCode;
		gMapInformation.fAutoDirection = FALSE;
	}
	else
	{
		gMapInformation.fAutoDirection = TRUE;
	}


	UpdateOptionsFields();
}


void DisplayInsertionInfo()
{
	UINT16 str[20];

	SetFont( FONT10ARIAL );
	SetFontShadow( FONT_NEARBLACK );

	SetFontForeground( FONT_YELLOW );
	mprintf( 530, 400, gzEditorStrings[EDITOR_STR_INSERTION_DIRECTION]);

	switch( gbInsertionCode )
	{
		case INSERTION_CODE_NORTH:							swprintf( str, gzEditorStrings[EDITOR_STR_NORTH] );					break;
		case INSERTION_CODE_SOUTH:							swprintf( str, gzEditorStrings[EDITOR_STR_SOUTH] );					break;
		case INSERTION_CODE_EAST:								swprintf( str, gzEditorStrings[EDITOR_STR_EAST] );						break;
		case INSERTION_CODE_WEST:								swprintf( str, gzEditorStrings[EDITOR_STR_WEST] );						break;
		case INSERTION_AUTO:										swprintf( str, gzEditorStrings[EDITOR_STR_AUTO] );						break;
	}
	DrawEditorInfoBox( str, FONT10ARIAL, 540, 413, 60, 15 );
}


void OptionsDirectionDown(GUI_BUTTON *btn,INT32 reason)
{
	if( reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		if ( gbInsertionCode == INSERTION_CODE_EAST )
		{
			gbInsertionCode = INSERTION_CODE_SOUTH;
		}
		else if ( gbInsertionCode == INSERTION_CODE_SOUTH )
		{
			gbInsertionCode = INSERTION_CODE_NORTH;
		}
		else if ( gbInsertionCode == INSERTION_CODE_NORTH )
		{
			gbInsertionCode = INSERTION_AUTO;
		}
		else if ( gbInsertionCode == INSERTION_AUTO )
		{
			gbInsertionCode = INSERTION_CODE_WEST;
		}
		else if ( gbInsertionCode == INSERTION_CODE_WEST )
		{
			gbInsertionCode = INSERTION_CODE_EAST;
		}

		gfRenderTaskbar = TRUE;

	}
}

void OptionsDirectionUp(GUI_BUTTON *btn,INT32 reason)
{
	if( reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		if ( gbInsertionCode == INSERTION_CODE_EAST )
		{
			gbInsertionCode = INSERTION_CODE_WEST;
		}
		else if ( gbInsertionCode == INSERTION_CODE_WEST )
		{
			gbInsertionCode = INSERTION_AUTO;
		}
		else if ( gbInsertionCode == INSERTION_AUTO )
		{
			gbInsertionCode = INSERTION_CODE_NORTH;
		}
		else if ( gbInsertionCode == INSERTION_CODE_NORTH )
		{
			gbInsertionCode = INSERTION_CODE_SOUTH;
		}
		else if ( gbInsertionCode == INSERTION_CODE_SOUTH )
		{
			gbInsertionCode = INSERTION_CODE_EAST;
		}

		gfRenderTaskbar = TRUE;

	}
}


void DisplayLoadingScreenInfo( )
{
	UINT16 str[20];

	SetFont( FONT10ARIAL );
	SetFontShadow( FONT_NEARBLACK );

	SetFontForeground( FONT_YELLOW );
	mprintf( 160, 365, gzEditorStrings[EDITOR_STR_LOADING_SCREEN]);

	switch( gMapInformation.ubLoadingScreenID )
	{
		case LOADINGSCREEN_DAY_SNOW:										swprintf( str, gzEditorStrings[EDITOR_STR_SNOW] );								break;
		case LOADINGSCREEN_GUARDPOST_DAY:								swprintf( str, gzEditorStrings[EDITOR_STR_GUARD_POST] );					break;
		case LOADINGSCREEN_POWERPLANT_DAY:							swprintf( str, gzEditorStrings[EDITOR_STR_POWER_PLANT] );				break;
		case LOADINGSCREEN_DAYGENERIC:									swprintf( str, gzEditorStrings[EDITOR_STR_GENERIC] );						break;
		case LOADINGSCREEN_DAYTOWN1:										swprintf( str, gzEditorStrings[EDITOR_STR_TOWN1] );							break;
		case LOADINGSCREEN_DAYTOWN2:										swprintf( str, gzEditorStrings[EDITOR_STR_TOWN2] );							break;
		case LOADINGSCREEN_DAYFOREST:										swprintf( str, gzEditorStrings[EDITOR_STR_FOREST] );							break;
		case LOADINGSCREEN_MINE:												swprintf( str, gzEditorStrings[EDITOR_STR_MINE] );								break;
		case LOADINGSCREEN_CAVE:												swprintf( str, gzEditorStrings[EDITOR_STR_CAVE] );								break;
		case LOADINGSCREEN_DAYPINE:											swprintf( str, gzEditorStrings[EDITOR_STR_PINE] );								break;
		case LOADINGSCREEN_DAYMINE:											swprintf( str, gzEditorStrings[EDITOR_STR_MINE_ENTRANCE] );			break;
		case LOADINGSCREEN_DAYWILD:											swprintf( str, gzEditorStrings[EDITOR_STR_WILDERNESS] );					break;
		case LOADINGSCREEN_COMPLEX_BASEMENT_GENERIC:  	swprintf( str, gzEditorStrings[EDITOR_STR_GENERIC_BASEMENT] );		break;

	}
	DrawEditorInfoBox( str, FONT10ARIAL, 150, 375, 80, 15 );

}



void OptionsLoadscreenDown(GUI_BUTTON *btn,INT32 reason)
{
	if( reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAY_SNOW )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_GUARDPOST_DAY;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_GUARDPOST_DAY )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_POWERPLANT_DAY;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_POWERPLANT_DAY )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYGENERIC;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYGENERIC )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYTOWN1;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYTOWN1 )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYTOWN2;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYTOWN2 )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYFOREST;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYFOREST )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_MINE;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_MINE )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_CAVE;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_CAVE )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYPINE;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYPINE )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYMINE;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYMINE )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYWILD;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYWILD )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_COMPLEX_BASEMENT_GENERIC;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_COMPLEX_BASEMENT_GENERIC )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAY_SNOW;
		}


		gfRenderTaskbar = TRUE;

	}
}

void OptionsLoadscreenUp(GUI_BUTTON *btn,INT32 reason)
{
	if( reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAY_SNOW )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_COMPLEX_BASEMENT_GENERIC;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_COMPLEX_BASEMENT_GENERIC )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYWILD;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYWILD )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYMINE;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYMINE )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYPINE;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYPINE )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_CAVE;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_CAVE )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_MINE;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_MINE )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYFOREST;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYFOREST )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYTOWN2;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYTOWN2 )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYTOWN1;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYTOWN1 )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAYGENERIC;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_DAYGENERIC )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_POWERPLANT_DAY;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_POWERPLANT_DAY )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_GUARDPOST_DAY;
		}
		else if ( gMapInformation.ubLoadingScreenID == LOADINGSCREEN_GUARDPOST_DAY )
		{
			gMapInformation.ubLoadingScreenID = LOADINGSCREEN_DAY_SNOW;
		}

		gfRenderTaskbar = TRUE;
	}
}


#endif

