#ifdef PRECOMPILEDHEADERS
	#include "Editor All.h"
	#include "Ja25Update.h"
#else
	#include "builddefines.h"
#endif

#ifdef JA2EDITOR

#ifndef PRECOMPILEDHEADERS
	#include <windows.h>
	#include "tiledef.h"
	#include "edit_sys.h"
	#include "vsurface.h"
	#include "vobject.h"
	#include "mousesystem.h"
	#include "Button System.h"
	#include "wcheck.h"
	#include "vsurface.h"
	#include "line.h"
	#include "input.h"
	#include "sysutil.h"
	#include "font.h"
	#include "Font Control.h"
	#include "editscreen.h"
	#include "selectwin.h"
	#include "video.h"
	#include "vobject_blitters.h"
	#include "interface panels.h"
	#include "interface items.h"
	#include "utilities.h"
	#include "World Items.h"
	#include "worldman.h"
	#include "overhead.h"	//GetSoldier
	#include "renderworld.h"
	#include "Animation Data.h"
	#include "Animation Control.h"
	#include "lighting.h"
	#include "EditorDefines.h"
	#include "EditorMercs.h"
	#include "EditorTerrain.h" //for access to TerrainTileDrawMode
	#include "Soldier Create.h" //The stuff that connects the editor generated information
	#include "Soldier Init List.h"
	#include "strategicmap.h"
	#include "Soldier Add.h"
	#include "Soldier Control.h"
	#include "Soldier Profile Type.h"
	#include "Soldier Profile.h"
	#include "Text Input.h"
	#include "Random.h"
	#include "wordwrap.h"
	#include "EditorItems.h"
	#include "Editor Taskbar Utils.h"
	#include "Exit Grids.h"
	#include "Editor Undo.h"
	#include "Item Statistics.h"
	#include "Map Information.h"
	#include "EditorMapInfo.h"
	#include "environment.h"
	#include "Simple Render Utils.h"
#endif

INT8 gbDefaultLightType = PRIMETIME_LIGHT;

SGPPaletteEntry	gEditorLightColor;

BOOLEAN gfEditorForceShadeTableRebuild = FALSE;

void SetupTextInputForMapInfo()
{
	UINT16 str[10];

	InitTextInputModeWithScheme( DEFAULT_SCHEME );

	AddUserInputField( NULL );  //just so we can use short cut keys while not typing.

	//light rgb fields
	swprintf( str, L"%d", gEditorLightColor.peRed );
	AddTextInputField( 10, 394, 25, 18, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );
	swprintf( str, L"%d", gEditorLightColor.peGreen );
	AddTextInputField( 10, 414, 25, 18, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );
	swprintf( str, L"%d", gEditorLightColor.peBlue );
	AddTextInputField( 10, 434, 25, 18, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );

	swprintf( str, L"%d", gsLightRadius );
	AddTextInputField( 120, 394, 25, 18, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_NUMERICSTRICT );
	swprintf( str, L"%d", gusLightLevel );
	AddTextInputField( 120, 414, 25, 18, MSYS_PRIORITY_NORMAL, str, 2, INPUTTYPE_NUMERICSTRICT );

	//Scroll restriction ID
	if( !gMapInformation.ubRestrictedScrollID )
		swprintf( str, L"" );
	else
		swprintf( str, L"%d", gMapInformation.ubRestrictedScrollID );
	AddTextInputField( 0, 420, 1, 421, MSYS_PRIORITY_NORMAL, str, 2, INPUTTYPE_NUMERICSTRICT );

	//exit grid input fields
	swprintf( str, L"%c%d", gExitGrid.ubGotoSectorY + 'A' - 1, gExitGrid.ubGotoSectorX );
	AddTextInputField( 338, 363, 30, 18, MSYS_PRIORITY_NORMAL, str, 3, INPUTTYPE_EXCLUSIVE_COORDINATE );
	swprintf( str, L"%d", gExitGrid.ubGotoSectorZ );
	AddTextInputField( 338, 383, 30, 18, MSYS_PRIORITY_NORMAL, str, 1, INPUTTYPE_NUMERICSTRICT );
	swprintf( str, L"%d", gExitGrid.usGridNo );
	AddTextInputField( 338, 403, 40, 18, MSYS_PRIORITY_NORMAL, str, 5, INPUTTYPE_NUMERICSTRICT );

	ClickEditorButton( MAPINFO_PRIMETIME_LIGHT + gbDefaultLightType );

}

void UpdateMapInfo()
{
	SetFont( FONT10ARIAL );
	SetFontShadow( FONT_NEARBLACK );

	SetFontForeground( FONT_RED );
	mprintf( 38, 399, gzEditorStrings[EDITOR_STR_RED_IND]);
	SetFontForeground( FONT_GREEN );
	mprintf( 38, 419, gzEditorStrings[EDITOR_STR_GREEN_IND]);
	SetFontForeground( FONT_DKBLUE );
	mprintf( 38, 439, gzEditorStrings[EDITOR_STR_BLUE_IND]);

	SetFontForeground( FONT_YELLOW );
	mprintf( 65, 369, gzEditorStrings[EDITOR_STR_PRIME] );
	mprintf( 65, 382, gzEditorStrings[EDITOR_STR_NIGHT] );
	mprintf( 65, 397, gzEditorStrings[EDITOR_STR_24HR] );

	SetFontForeground( FONT_YELLOW );
	mprintf( 148, 399, gzEditorStrings[EDITOR_STR_RADIUS]);

	if( !gfBasement && !gfCaves )
		SetFontForeground( FONT_DKYELLOW );
	mprintf( 148, 414, gzEditorStrings[EDITOR_STR_UNDERGROUND] );
	mprintf( 148, 423, gzEditorStrings[EDITOR_STR_LIGHT_LEVEL] );

	SetFontForeground( FONT_YELLOW );
	mprintf( 230, 369, gzEditorStrings[EDITOR_STR_OUTDOORS] );
	mprintf( 230, 384, gzEditorStrings[EDITOR_STR_BASEMENT] );
	mprintf( 230, 399, gzEditorStrings[EDITOR_STR_CAVES] );

	SetFontForeground( FONT_ORANGE );
	//mprintf( 250, 420, L"Restricted" );
	//mprintf( 250, 430, L"Scroll ID" );

	SetFontForeground( FONT_YELLOW );
	mprintf( 368, 363, gzEditorStrings[EDITOR_STR_DESTINATION]);
	mprintf( 368, 372, gzEditorStrings[EDITOR_STR_SECTOR] );
	mprintf( 368, 383, gzEditorStrings[EDITOR_STR_DESTINATION]);
	mprintf( 368, 392, gzEditorStrings[EDITOR_STR_BASEMENT_LEVEL] );
	mprintf( 378, 403, gzEditorStrings[EDITOR_STR_DEST_ABBREV] );
	mprintf( 378, 412, gzEditorStrings[EDITOR_STR_GRIDNO] );

	SetFontForeground( FONT_RED );
}

void UpdateMapInfoFields()
{
	UINT16 str[10];
	//Update the text fields to reflect the validated values.
	//light rgb fields
	swprintf( str, L"%d", gEditorLightColor.peRed );
	SetInputFieldStringWith16BitString( 1, str );
	swprintf( str, L"%d", gEditorLightColor.peGreen );
	SetInputFieldStringWith16BitString( 2, str );
	swprintf( str, L"%d", gEditorLightColor.peBlue );
	SetInputFieldStringWith16BitString( 3, str );

	swprintf( str, L"%d", gsLightRadius );
	SetInputFieldStringWith16BitString( 4, str );
	swprintf( str, L"%d", gusLightLevel );
	SetInputFieldStringWith16BitString( 5, str );

	if( !gMapInformation.ubRestrictedScrollID )
		swprintf( str, L"" );
	else
		swprintf( str, L"%d", gMapInformation.ubRestrictedScrollID );
	SetInputFieldStringWith16BitString( 6, str );


	ApplyNewExitGridValuesToTextFields();
}

void ExtractAndUpdateMapInfo()
{
	UINT16 str[10];
	INT32 temp;
	BOOLEAN fUpdateLight1 = FALSE;
	//extract light1 colors
	temp = min( GetNumericStrictValueFromField( 1 ), 255 );
	if( temp != -1 && temp != gEditorLightColor.peRed )
	{
		fUpdateLight1 = TRUE;
		gEditorLightColor.peRed = (UINT8)temp;
	}
	temp = min( GetNumericStrictValueFromField( 2 ), 255 );
	if( temp != -1 && temp != gEditorLightColor.peGreen )
	{
		fUpdateLight1 = TRUE;
		gEditorLightColor.peGreen = (UINT8)temp;
	}
	temp = min( GetNumericStrictValueFromField( 3 ), 255 );
	if( temp != -1 && temp != gEditorLightColor.peBlue )
	{
		fUpdateLight1 = TRUE;
		gEditorLightColor.peBlue = (UINT8)temp;
	}
	if( fUpdateLight1 )
	{
		gfEditorForceShadeTableRebuild = TRUE;
		LightSetColors(	&gEditorLightColor, 1 );
		gfEditorForceShadeTableRebuild = FALSE;
	}

	//extract radius
	temp = max( min( GetNumericStrictValueFromField( 4 ), 8 ), 1 );
	if( temp != -1 )
		gsLightRadius = (INT16)temp;
	temp = max( min( GetNumericStrictValueFromField( 5 ), 15 ), 1 );
	if( temp != -1 && temp != gusLightLevel )
	{
		gusLightLevel = (UINT16)temp;
		gfRenderWorld = TRUE;
		ubAmbientLightLevel = (UINT8)(EDITOR_LIGHT_MAX - gusLightLevel);
		LightSetBaseLevel( ubAmbientLightLevel );
		LightSpriteRenderAll();
	}

	temp = (INT8)GetNumericStrictValueFromField( 6 );
	if( temp == -1 )
		gMapInformation.ubRestrictedScrollID = 0;
	else
		gMapInformation.ubRestrictedScrollID = (UINT8)temp;

	//set up fields for exitgrid information
	Get16BitStringFromField( 7, str );
	if( str[0] >= 'a' && str[0] <= 'z' )
		str[0] -= 32; //uppercase it!
	if( str[0] >= 'A' && str[0] <= 'Z' &&
		  str[1] >= '0' && str[1] <= '9' )
	{ //only update, if coordinate is valid.
		gExitGrid.ubGotoSectorY = (UINT8)(str[0] - 'A' + 1);
		gExitGrid.ubGotoSectorX = (UINT8)(str[1] - '0');
		if( str[2] >= '0' && str[2] <= '9' )
			gExitGrid.ubGotoSectorX = (UINT8)(gExitGrid.ubGotoSectorX * 10 + str[2] - '0' );
		gExitGrid.ubGotoSectorX = (UINT8)max( min( gExitGrid.ubGotoSectorX, 16 ), 1 );
		gExitGrid.ubGotoSectorY = (UINT8)max( min( gExitGrid.ubGotoSectorY, 16 ), 1 );
	}
	gExitGrid.ubGotoSectorZ    = (UINT8)max( min( GetNumericStrictValueFromField( 8 ), 3 ), 0 );
	gExitGrid.usGridNo					 = (UINT16)max( min( GetNumericStrictValueFromField( 9 ), 25600 ), 0 );

	UpdateMapInfoFields();
}

BOOLEAN ApplyNewExitGridValuesToTextFields()
{
	UINT16 str[10];
	//exit grid input fields
	if( iCurrentTaskbar != TASK_MAPINFO )
		return FALSE;
	swprintf( str, L"%c%d", gExitGrid.ubGotoSectorY + 'A' - 1, gExitGrid.ubGotoSectorX );
	SetInputFieldStringWith16BitString( 7, str );
	swprintf( str, L"%d", gExitGrid.ubGotoSectorZ );
	SetInputFieldStringWith16BitString( 8, str );
	swprintf( str, L"%d", gExitGrid.usGridNo );
	SetInputFieldStringWith16BitString( 9, str );
	SetActiveField( 0 );
	return TRUE;
}

UINT16 usCurrentExitGridNo = 0;
void LocateNextExitGrid()
{
	EXITGRID ExitGrid;
	UINT16 i;
	for( i = usCurrentExitGridNo + 1; i < WORLD_MAX; i++ )
	{
		if( GetExitGrid( i, &ExitGrid ) )
		{
			usCurrentExitGridNo = i;
			CenterScreenAtMapIndex( i );
			return;
		}
	}
	for( i = 0; i < usCurrentExitGridNo; i++ )
	{
		if( GetExitGrid( i, &ExitGrid ) )
		{
			usCurrentExitGridNo = i;
			CenterScreenAtMapIndex( i );
			return;
		}
	}
}

void ChangeLightDefault( INT8 bLightType )
{
	UnclickEditorButton( MAPINFO_PRIMETIME_LIGHT + gbDefaultLightType );
	gbDefaultLightType = bLightType;
	ClickEditorButton( MAPINFO_PRIMETIME_LIGHT + gbDefaultLightType );
}

#endif
