#ifdef PRECOMPILEDHEADERS
	#include "Editor All.h"
#else
	#include "builddefines.h"
#endif

#ifdef JA2EDITOR

#ifndef PRECOMPILEDHEADERS
	//sgp
	#include "Button System.h"
	#include "Font Control.h"
	#include "debug.h"
	//editor
	#include "EditorDefines.h"
	#include "Editor Callback Prototypes.h"
	#include "Editor Taskbar Utils.h"
	#include "EditorMercs.h"
	#include "EditorMapInfo.h"
	//tactical
	#include "Soldier Create.h"
	#include "overhead types.h"
#endif

//Category tabs of the editor buttons
void InitEditorTerrainToolbar();
void InitEditorBuildingsToolbar();
void InitEditorItemsToolbar();
void InitEditorMercsToolbar();
void InitEditorMapInfoToolbar();
void InitEditorOptionsToolbar();
void InitEditorItemStatsButtons();

void InitEditorItemStatsButtons()
{
	iEditorButton[ ITEMSTATS_PANEL ] =
		CreateTextButton( 0, 0, 0, 0, BUTTON_USE_DEFAULT, 480, 361, 160, 99, BUTTON_TOGGLE,
		MSYS_PRIORITY_NORMAL, BUTTON_NO_CALLBACK, BUTTON_NO_CALLBACK );
	SpecifyDisabledButtonStyle( iEditorButton[ ITEMSTATS_PANEL ], DISABLED_STYLE_NONE );
	DisableButton( iEditorButton[ ITEMSTATS_PANEL ] );
	iEditorButton[ ITEMSTATS_HIDDEN_BTN ] =
		CreateCheckBoxButton(	485, 365, "EDITOR\\SmCheckbox.sti", MSYS_PRIORITY_NORMAL, ItemStatsToggleHideCallback );
	iEditorButton[ ITEMSTATS_DELETE_BTN ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_DELETE], FONT10ARIAL, FONT_RED, FONT_BLACK, BUTTON_USE_DEFAULT,
		600, 441, 36, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL+1, DEFAULT_MOVE_CALLBACK, ItemStatsDeleteCallback );
}

void InitEditorMercsToolbar()
{
	INT16 TempString[50];
	INT16 *FaceDirs[8] = {gzEditorStrings[EDITOR_STR_NORTH],gzEditorStrings[EDITOR_STR_NORTHEAST],gzEditorStrings[EDITOR_STR_EAST],gzEditorStrings[EDITOR_STR_SOUTHEAST],gzEditorStrings[EDITOR_STR_SOUTH],gzEditorStrings[EDITOR_STR_SOUTHWEST],gzEditorStrings[EDITOR_STR_WEST],gzEditorStrings[EDITOR_STR_NORTHWEST]};
	INT32 x;

	iEditorButton[ MERCS_PLAYERTOGGLE ] =
		CreateCheckBoxButton(	4, 362, "EDITOR\\SmCheckbox.sti", MSYS_PRIORITY_NORMAL, MercsTogglePlayers );
	if( gfShowPlayers )
		ClickEditorButton( MERCS_PLAYERTOGGLE );
	SetButtonFastHelpText( iEditorButton[ MERCS_PLAYERTOGGLE ], gzEditorStrings[EDITOR_STR_TOGGLE_VIEW_PLAYERS]);
	DisableButton( iEditorButton[ MERCS_PLAYERTOGGLE ] );
	iEditorButton[ MERCS_ENEMYTOGGLE ] =
		CreateCheckBoxButton(	4, 382, "EDITOR\\SmCheckbox.sti", MSYS_PRIORITY_NORMAL, MercsToggleEnemies );
	if( gfShowEnemies )
		ClickEditorButton( MERCS_ENEMYTOGGLE );
	SetButtonFastHelpText( iEditorButton[ MERCS_ENEMYTOGGLE ], gzEditorStrings[EDITOR_STR_TOGGLE_VIEW_ENEMIES]);
	iEditorButton[ MERCS_CREATURETOGGLE ] =
		CreateCheckBoxButton(	4, 402, "EDITOR\\SmCheckbox.sti", MSYS_PRIORITY_NORMAL, MercsToggleCreatures );
	if( gfShowCreatures )
		ClickEditorButton( MERCS_CREATURETOGGLE );
	SetButtonFastHelpText( iEditorButton[ MERCS_CREATURETOGGLE ], gzEditorStrings[EDITOR_STR_TOGGLE_VIEW_CREATURES]);
//	iEditorButton[ MERCS_REBELTOGGLE ] =
//		CreateCheckBoxButton(	4, 422, "EDITOR\\SmCheckbox.sti", MSYS_PRIORITY_NORMAL, MercsToggleRebels );
//	if( gfShowRebels )
//		ClickEditorButton( MERCS_REBELTOGGLE );
//	SetButtonFastHelpText( iEditorButton[ MERCS_REBELTOGGLE ], L"Toggle viewing of rebels");
//	iEditorButton[ MERCS_CIVILIANTOGGLE ] =
//		CreateCheckBoxButton(	4, 442, "EDITOR\\SmCheckbox.sti", MSYS_PRIORITY_NORMAL, MercsToggleCivilians );
//	if( gfShowCivilians )
//		ClickEditorButton( MERCS_CIVILIANTOGGLE );
//	SetButtonFastHelpText( iEditorButton[ MERCS_CIVILIANTOGGLE ], L"Toggle viewing of civilians");
	iEditorButton[MERCS_PLAYER] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_PLAYER],(UINT16)BLOCKFONT, 165, FONT_BLACK, BUTTON_USE_DEFAULT,
		20, 362, 78, 19, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsPlayerTeamCallback );
	SpecifyButtonDownTextColors( iEditorButton[MERCS_PLAYER], FONT_YELLOW, FONT_BLACK );
	DisableButton( iEditorButton[MERCS_PLAYER] );
	iEditorButton[MERCS_ENEMY] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_ENEMY],(UINT16)BLOCKFONT, 165, FONT_BLACK, BUTTON_USE_DEFAULT,
		20, 382, 78, 19, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsEnemyTeamCallback );
	SpecifyButtonDownTextColors( iEditorButton[MERCS_ENEMY], FONT_YELLOW, FONT_BLACK );
	iEditorButton[MERCS_CREATURE] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_CREATURE],(UINT16)BLOCKFONT, 165, FONT_BLACK, BUTTON_USE_DEFAULT,
		20, 402, 78, 19, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsCreatureTeamCallback );
	SpecifyButtonDownTextColors( iEditorButton[MERCS_CREATURE], FONT_YELLOW, FONT_BLACK );
//	iEditorButton[MERCS_REBEL] =
//		CreateTextButton( L"Rebels",(UINT16)BLOCKFONT, 165, FONT_BLACK, BUTTON_USE_DEFAULT,
//		20, 422, 78, 19, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
//		MercsRebelTeamCallback );
//	SpecifyButtonDownTextColors( iEditorButton[MERCS_REBEL], FONT_YELLOW, FONT_BLACK );
//	iEditorButton[MERCS_CIVILIAN] =
//		CreateTextButton( L"Civilian",(UINT16)BLOCKFONT, 165, FONT_BLACK, BUTTON_USE_DEFAULT,
//		20, 442, 78, 19, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
//		MercsCivilianTeamCallback );
//	SpecifyButtonDownTextColors( iEditorButton[MERCS_CIVILIAN], FONT_YELLOW, FONT_BLACK );

	iEditorButton[ MERCS_1 ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_DETAILED_PLACEMENT_TEXT ], SMALLCOMPFONT, FONT_ORANGE, 60, BUTTON_USE_DEFAULT,
		100, 362, 68, 20, BUTTON_TOGGLE,
		MSYS_PRIORITY_NORMAL, BUTTON_NO_CALLBACK, BUTTON_NO_CALLBACK );
	DisableButton( iEditorButton[ MERCS_1 ] );
	SpecifyDisabledButtonStyle( iEditorButton[ MERCS_1 ], DISABLED_STYLE_NONE );
	SpecifyButtonTextOffsets( iEditorButton[ MERCS_1 ], 20, 4, FALSE );
	SpecifyButtonTextWrappedWidth( iEditorButton[ MERCS_1 ], 46 );
//	iEditorButton[ MERCS_DETAILEDCHECKBOX ] =
//		CreateCheckBoxButton(	103, 365, "EDITOR\\checkbox.sti", MSYS_PRIORITY_NORMAL, MercsDetailedPlacementCallback );

	iEditorButton[ MERCS_GENERAL ] =
		CreateEasyToggleButton( 100, 382, "EDITOR\\MercGeneral.sti", MercsGeneralModeCallback );
	SetButtonFastHelpText( iEditorButton[ MERCS_GENERAL ], gzEditorStrings[EDITOR_STR_GENERAL_INFO_MODE]);
//	iEditorButton[ MERCS_APPEARANCE ] =
//		CreateEasyToggleButton( 134, 382, "EDITOR\\MercAppearance.sti", MercsAppearanceModeCallback );
//	SetButtonFastHelpText( iEditorButton[ MERCS_APPEARANCE ], L"Physical appearance mode");
	iEditorButton[ MERCS_ATTRIBUTES ] =
		CreateEasyToggleButton( 134, 382, "EDITOR\\MercAttributes.sti", MercsAttributesModeCallback );
	SetButtonFastHelpText( iEditorButton[ MERCS_ATTRIBUTES ], gzEditorStrings[EDITOR_STR_ATTRIBUTES_MODE]);
	iEditorButton[ MERCS_INVENTORY ] =
		CreateEasyToggleButton( 100, 408, "EDITOR\\MercInventory.sti", MercsInventoryModeCallback );
	SetButtonFastHelpText( iEditorButton[ MERCS_INVENTORY ], gzEditorStrings[EDITOR_STR_INVENTORY_MODE]);
//	iEditorButton[ MERCS_PROFILE ] =
//		CreateEasyToggleButton( 100, 434, "EDITOR\\MercProfile.sti", MercsProfileModeCallback );
//	SetButtonFastHelpText( iEditorButton[ MERCS_PROFILE ], L"Profile ID mode");
//	iEditorButton[ MERCS_SCHEDULE ] =
//		CreateEasyToggleButton( 134, 434, "EDITOR\\MercSchedule.sti", MercsScheduleModeCallback );
//	SetButtonFastHelpText( iEditorButton[ MERCS_SCHEDULE ], L"Schedule mode");
	//Workaround for identical buttons.
//	MSYS_SetBtnUserData( iEditorButton[ MERCS_SCHEDULE ], 3, 0xffffffff );
	iEditorButton[ MERCS_GLOWSCHEDULE ] =
		CreateEasyToggleButton( 134, 434, "EDITOR\\MercGlowSchedule.sti", MercsScheduleModeCallback );
	SetButtonFastHelpText( iEditorButton[ MERCS_GLOWSCHEDULE ], gzEditorStrings[EDITOR_STR_SCHEDULE_MODE]);
	HideEditorButton( MERCS_GLOWSCHEDULE );

	iEditorButton[ MERCS_DELETE ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_DELETE], (UINT16)SMALLCOMPFONT, FONT_DKBLUE, FONT_BLACK, BUTTON_USE_DEFAULT,
		600, 362, 40, 20, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsDeleteCallback );
	SetButtonFastHelpText( iEditorButton[ MERCS_DELETE ], gzEditorStrings[EDITOR_STR_DELETE_SEL_MERC]);
	iEditorButton[ MERCS_NEXT ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_NEXT], (UINT16)SMALLCOMPFONT, FONT_DKBLUE, FONT_BLACK, BUTTON_USE_DEFAULT,
		600, 382, 40, 20, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsNextCallback );
	SetButtonFastHelpText( iEditorButton[ MERCS_NEXT ], gzEditorStrings[EDITOR_STR_FIND_NEXT_MERC]);

	//Priority Existance
	iEditorButton[ MERCS_PRIORITYEXISTANCE_CHECKBOX ] =
		CreateCheckBoxButton(	170, 365, "EDITOR\\checkbox.sti", MSYS_PRIORITY_NORMAL, MercsPriorityExistanceCallback );
	SetButtonFastHelpText( iEditorButton[ MERCS_PRIORITYEXISTANCE_CHECKBOX ], gzEditorStrings[EDITOR_STR_TOGGLE_PRIORITY_EXISTANCE] );

	//If merc has keys
//	iEditorButton[ MERCS_HASKEYS_CHECKBOX ] =
//		CreateCheckBoxButton(	170, 390, "EDITOR\\checkbox.sti", MSYS_PRIORITY_NORMAL, MercsHasKeysCallback );
//	SetButtonFastHelpText( iEditorButton[ MERCS_HASKEYS_CHECKBOX ], L"Toggle whether or not placement has/naccess to all doors." );

	//Orders
	iEditorButton[ MERCS_ORDERS_STATIONARY ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_STATIONARY], (UINT16)SMALLCOMPFONT, FONT_GRAY2, FONT_BLACK, BUTTON_USE_DEFAULT,
		200, 368, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetOrdersCallback );
	iEditorButton[ MERCS_ORDERS_ONGUARD] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_ON_GUARD], (UINT16)SMALLCOMPFONT, FONT_GRAY2, FONT_BLACK, BUTTON_USE_DEFAULT,
		200, 380, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetOrdersCallback );
	iEditorButton[ MERCS_ORDERS_ONCALL ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_ON_CALL], (UINT16)SMALLCOMPFONT, FONT_GRAY2, FONT_BLACK, BUTTON_USE_DEFAULT,
		200, 392, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetOrdersCallback );
	iEditorButton[ MERCS_ORDERS_SEEKENEMY ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_SEEK_ENEMY], (UINT16)SMALLCOMPFONT, FONT_GRAY2, FONT_BLACK, BUTTON_USE_DEFAULT,
		200, 404, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetOrdersCallback );
	iEditorButton[ MERCS_ORDERS_CLOSEPATROL ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_CLOSE_PATROL], (UINT16)SMALLCOMPFONT, FONT_GRAY2, FONT_BLACK, BUTTON_USE_DEFAULT,
		270, 368, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetOrdersCallback );
	iEditorButton[ MERCS_ORDERS_FARPATROL ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_FAR_PATROL], (UINT16)SMALLCOMPFONT, FONT_GRAY2, FONT_BLACK, BUTTON_USE_DEFAULT,
		270, 380, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetOrdersCallback );
	iEditorButton[ MERCS_ORDERS_POINTPATROL ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_POINT_PATROL], (UINT16)SMALLCOMPFONT, FONT_GRAY2, FONT_BLACK, BUTTON_USE_DEFAULT,
		270, 392, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetOrdersCallback );
	iEditorButton[ MERCS_ORDERS_RNDPTPATROL ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_RND_PT_PATROL], (UINT16)SMALLCOMPFONT, FONT_GRAY2, FONT_BLACK, BUTTON_USE_DEFAULT,
		270, 404, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetOrdersCallback );
	for ( x = 0; x < 8; x++ )
	{
		MSYS_SetBtnUserData( iEditorButton[ FIRST_MERCS_ORDERS_BUTTON + x ], 0, x);
	}

	//Attitudes
	iEditorButton[ MERCS_ATTITUDE_DEFENSIVE ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_DEFENSIVE], (UINT16)SMALLCOMPFONT, FONT_GRAY4, FONT_BLACK, BUTTON_USE_DEFAULT,
		200, 424, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetAttitudeCallback );
	iEditorButton[ MERCS_ATTITUDE_BRAVESOLO ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_BRAVE_SOLO], (UINT16)SMALLCOMPFONT, FONT_GRAY4, FONT_BLACK, BUTTON_USE_DEFAULT,
		200, 436, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetAttitudeCallback );
	iEditorButton[ MERCS_ATTITUDE_BRAVEAID ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_BRAVE_AID], (UINT16)SMALLCOMPFONT, FONT_GRAY4, FONT_BLACK, BUTTON_USE_DEFAULT,
		200, 448, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetAttitudeCallback );
	iEditorButton[ MERCS_ATTITUDE_AGGRESSIVE ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_AGGRESSIVE], (UINT16)SMALLCOMPFONT, FONT_GRAY4, FONT_BLACK, BUTTON_USE_DEFAULT,
		270, 424, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetAttitudeCallback );
	iEditorButton[ MERCS_ATTITUDE_CUNNINGSOLO ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_CUNNING_SOLO], (UINT16)SMALLCOMPFONT, FONT_GRAY4, FONT_BLACK, BUTTON_USE_DEFAULT,
		270, 436, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetAttitudeCallback );
	iEditorButton[ MERCS_ATTITUDE_CUNNINGAID ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_CUNNING_AID], (UINT16)SMALLCOMPFONT, FONT_GRAY4, FONT_BLACK, BUTTON_USE_DEFAULT,
		270, 448, 70, 12, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK,
		MercsSetAttitudeCallback );
	for ( x = 0; x < 6; x++ )
	{
		MSYS_SetBtnUserData( iEditorButton[ FIRST_MERCS_ATTITUDE_BUTTON + x ], 0, x);
	}

	iEditorButton[ MERCS_DIRECTION_W ] =
		CreateIconButton((INT16)giEditMercDirectionIcons[0], 7, BUTTON_USE_DEFAULT,
		360, 365, 30, 30, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL + 1, DEFAULT_MOVE_CALLBACK, MercsDirectionSetCallback );
	iEditorButton[ MERCS_DIRECTION_NW ] =
		CreateIconButton((INT16)giEditMercDirectionIcons[0], 0, BUTTON_USE_DEFAULT,
		390, 365, 30, 30, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL + 1, DEFAULT_MOVE_CALLBACK, MercsDirectionSetCallback );
	iEditorButton[ MERCS_DIRECTION_N ] =
		CreateIconButton((INT16)giEditMercDirectionIcons[0], 1, BUTTON_USE_DEFAULT,
		420, 365, 30, 30, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL + 1, DEFAULT_MOVE_CALLBACK, MercsDirectionSetCallback );
	iEditorButton[ MERCS_DIRECTION_NE] =
		CreateIconButton((INT16)giEditMercDirectionIcons[0], 2, BUTTON_USE_DEFAULT,
		420, 395, 30, 30, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL + 1, DEFAULT_MOVE_CALLBACK, MercsDirectionSetCallback );
	iEditorButton[ MERCS_DIRECTION_E ] =
		CreateIconButton((INT16)giEditMercDirectionIcons[0], 3, BUTTON_USE_DEFAULT,
		420, 425, 30, 30, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL + 1, DEFAULT_MOVE_CALLBACK, MercsDirectionSetCallback );
	iEditorButton[ MERCS_DIRECTION_SE ] =
		CreateIconButton((INT16)giEditMercDirectionIcons[0], 4, BUTTON_USE_DEFAULT,
		390, 425, 30, 30, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL + 1, DEFAULT_MOVE_CALLBACK, MercsDirectionSetCallback );
	iEditorButton[ MERCS_DIRECTION_S ] =
		CreateIconButton((INT16)giEditMercDirectionIcons[0], 5, BUTTON_USE_DEFAULT,
		360, 425, 30, 30, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL + 1, DEFAULT_MOVE_CALLBACK, MercsDirectionSetCallback );
	iEditorButton[ MERCS_DIRECTION_SW ] =
		CreateIconButton((INT16)giEditMercDirectionIcons[0], 6, BUTTON_USE_DEFAULT,
		360, 395, 30, 30, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL + 1, DEFAULT_MOVE_CALLBACK, MercsDirectionSetCallback );
	for ( x = 0; x < 8; x++ )
	{
		swprintf( TempString, gzEditorStrings[EDITOR_STR_SET_MERC_TO_FACE], FaceDirs[x] );
		SetButtonFastHelpText( iEditorButton[ FIRST_MERCS_DIRECTION_BUTTON + x ], TempString );
		MSYS_SetBtnUserData( iEditorButton[ FIRST_MERCS_DIRECTION_BUTTON + x ], 0, x);
	}

	iEditorButton[ MERCS_DIRECTION_FIND ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_FIND], (INT16)FONT12POINT1, FONT_MCOLOR_BLACK, FONT_BLACK, BUTTON_USE_DEFAULT,
		390, 395, 30, 30, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL + 1, DEFAULT_MOVE_CALLBACK, MercsFindSelectedMercCallback );
	SetButtonFastHelpText( iEditorButton[ MERCS_DIRECTION_FIND] , gzEditorStrings[EDITOR_STR_FIND_SEL_MERC] );

/*-
	iEditorButton[ MERCS_EQUIPMENT_BAD ] =
		CreateTextButton( L"BAD", (INT16)SMALLCOMPFONT, FONT_GRAY1, FONT_BLACK, BUTTON_USE_DEFAULT,
		480, 385, 40, 15, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsSetRelativeEquipmentCallback );
	SpecifyButtonDownTextColors( iEditorButton[ MERCS_EQUIPMENT_BAD ], FONT_LTRED, FONT_BLACK );
	iEditorButton[ MERCS_EQUIPMENT_POOR ] =
		CreateTextButton( L"POOR", (INT16)SMALLCOMPFONT, FONT_GRAY1, FONT_BLACK, BUTTON_USE_DEFAULT,
		480, 400, 40, 15, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsSetRelativeEquipmentCallback );
	SpecifyButtonDownTextColors( iEditorButton[ MERCS_EQUIPMENT_POOR ], FONT_ORANGE, FONT_BLACK );
	iEditorButton[ MERCS_EQUIPMENT_AVERAGE ] =
		CreateTextButton( L"AVERAGE", (INT16)SMALLCOMPFONT, FONT_GRAY1, FONT_BLACK, BUTTON_USE_DEFAULT,
		480, 415, 40, 15, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsSetRelativeEquipmentCallback );
	SpecifyButtonDownTextColors( iEditorButton[ MERCS_EQUIPMENT_AVERAGE ], FONT_YELLOW, FONT_BLACK );
	iEditorButton[ MERCS_EQUIPMENT_GOOD ] =
		CreateTextButton( L"GOOD", (INT16)SMALLCOMPFONT, FONT_GRAY1, FONT_BLACK, BUTTON_USE_DEFAULT,
		480, 430, 40, 15, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsSetRelativeEquipmentCallback );
	SpecifyButtonDownTextColors( iEditorButton[ MERCS_EQUIPMENT_GOOD ], FONT_LTGREEN, FONT_BLACK );
	iEditorButton[ MERCS_EQUIPMENT_GREAT ] =
		CreateTextButton( L"GREAT", (INT16)SMALLCOMPFONT, FONT_GRAY1, FONT_BLACK, BUTTON_USE_DEFAULT,
		480, 445, 40, 15, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsSetRelativeEquipmentCallback );
	SpecifyButtonDownTextColors( iEditorButton[ MERCS_EQUIPMENT_GREAT ], FONT_LTBLUE, FONT_BLACK );
	for ( x = 0; x < 5; x++ )
	{
		MSYS_SetBtnUserData( iEditorButton[ FIRST_MERCS_REL_EQUIPMENT_BUTTON + x ], 0, x);
	}

	iEditorButton[ MERCS_ATTRIBUTES_BAD ] =
		CreateTextButton( L"BAD", (INT16)SMALLCOMPFONT, FONT_GRAY1, FONT_BLACK, BUTTON_USE_DEFAULT,
		530, 385, 40, 15, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsSetRelativeAttributesCallback );
	SpecifyButtonDownTextColors( iEditorButton[ MERCS_ATTRIBUTES_BAD ], FONT_LTRED, FONT_BLACK );
	iEditorButton[ MERCS_ATTRIBUTES_POOR ] =
		CreateTextButton( L"POOR", (INT16)SMALLCOMPFONT, FONT_GRAY1, FONT_BLACK, BUTTON_USE_DEFAULT,
		530, 400, 40, 15, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsSetRelativeAttributesCallback );
	SpecifyButtonDownTextColors( iEditorButton[ MERCS_ATTRIBUTES_POOR ], FONT_ORANGE, FONT_BLACK );
	iEditorButton[ MERCS_ATTRIBUTES_AVERAGE ] =
		CreateTextButton( L"AVERAGE", (INT16)SMALLCOMPFONT, FONT_GRAY1, FONT_BLACK, BUTTON_USE_DEFAULT,
		530, 415, 40, 15, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsSetRelativeAttributesCallback );
	SpecifyButtonDownTextColors( iEditorButton[ MERCS_ATTRIBUTES_AVERAGE ], FONT_YELLOW, FONT_BLACK );
	iEditorButton[ MERCS_ATTRIBUTES_GOOD ] =
		CreateTextButton( L"GOOD", (INT16)SMALLCOMPFONT, FONT_GRAY1, FONT_BLACK, BUTTON_USE_DEFAULT,
		530, 430, 40, 15, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsSetRelativeAttributesCallback );
	SpecifyButtonDownTextColors( iEditorButton[ MERCS_ATTRIBUTES_GOOD ], FONT_LTGREEN, FONT_BLACK );
	iEditorButton[ MERCS_ATTRIBUTES_GREAT ] =
		CreateTextButton( L"GREAT", (INT16)SMALLCOMPFONT, FONT_GRAY1, FONT_BLACK, BUTTON_USE_DEFAULT,
		530, 445, 40, 15, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsSetRelativeAttributesCallback );
	SpecifyButtonDownTextColors( iEditorButton[ MERCS_ATTRIBUTES_GREAT ], FONT_LTBLUE, FONT_BLACK );
	for( x = 0; x < 5; x++ )
		MSYS_SetBtnUserData( iEditorButton[ FIRST_MERCS_REL_ATTRIBUTE_BUTTON + x ], 0, x);
-*/

	iEditorButton[ MERCS_ARMY_CODE ] =
		CreateCheckBoxButton(	555, 429, "EDITOR\\radiobutton.sti", MSYS_PRIORITY_NORMAL, MercsSetEnemyColorCodeCallback );
	MSYS_SetBtnUserData( iEditorButton[ MERCS_ARMY_CODE ], 0, SOLDIER_CLASS_ARMY );
	iEditorButton[ MERCS_ADMIN_CODE ] =
		CreateCheckBoxButton(	555, 415, "EDITOR\\radiobutton.sti", MSYS_PRIORITY_NORMAL, MercsSetEnemyColorCodeCallback );
	MSYS_SetBtnUserData( iEditorButton[ MERCS_ADMIN_CODE ], 0, SOLDIER_CLASS_ADMINISTRATOR );
	iEditorButton[ MERCS_ELITE_CODE ] =
		CreateCheckBoxButton(	555, 443, "EDITOR\\radiobutton.sti", MSYS_PRIORITY_NORMAL, MercsSetEnemyColorCodeCallback );
	MSYS_SetBtnUserData( iEditorButton[ MERCS_ELITE_CODE ], 0, SOLDIER_CLASS_ELITE );

	iEditorButton[ MERCS_CIVILIAN_GROUP ] =
		CreateTextButton( gszCivGroupNames[0], (INT16)SMALLCOMPFONT, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		574, 410, 60, 25, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsCivilianGroupCallback );

	iEditorButton[ MERCS_TOGGLECOLOR_BUTTON ] =
		CreateCheckBoxButton(	180, 364, "EDITOR\\checkbox.sti", MSYS_PRIORITY_NORMAL, MercsToggleColorModeCallback );
	iEditorButton[MERCS_HAIRCOLOR_DOWN] =
		CreateEasyNoToggleButton( 200,364,"EDITOR\\leftarrow.sti", MercsSetColorsCallback );
	iEditorButton[MERCS_HAIRCOLOR_UP] =
		CreateEasyNoToggleButton( 360,364,"EDITOR\\rightarrow.sti", MercsSetColorsCallback );
	iEditorButton[MERCS_SKINCOLOR_DOWN] =
		CreateEasyNoToggleButton( 200,388,"EDITOR\\leftarrow.sti", MercsSetColorsCallback );
	iEditorButton[MERCS_SKINCOLOR_UP] =
		CreateEasyNoToggleButton( 360,388,"EDITOR\\rightarrow.sti", MercsSetColorsCallback );
	iEditorButton[MERCS_VESTCOLOR_DOWN] =
		CreateEasyNoToggleButton( 200,412,"EDITOR\\leftarrow.sti", MercsSetColorsCallback );
	iEditorButton[MERCS_VESTCOLOR_UP] =
		CreateEasyNoToggleButton( 360,412,"EDITOR\\rightarrow.sti", MercsSetColorsCallback );
	iEditorButton[MERCS_PANTCOLOR_DOWN] =
		CreateEasyNoToggleButton( 200,436,"EDITOR\\leftarrow.sti", MercsSetColorsCallback );
	iEditorButton[MERCS_PANTCOLOR_UP] =
		CreateEasyNoToggleButton( 360,436,"EDITOR\\rightarrow.sti", MercsSetColorsCallback );
	for ( x = FIRST_MERCS_COLOR_BUTTON; x < LAST_MERCS_COLOR_BUTTON; x+=2 )
	{
		SetButtonFastHelpText( iEditorButton[x], gzEditorStrings[EDITOR_STR_PREVIOUS_COL_SET] );
		SetButtonFastHelpText( iEditorButton[x + 1], gzEditorStrings[EDITOR_STR_NEXT_COL_SET] );
		DisableButton( iEditorButton[ x ] );
		DisableButton( iEditorButton[ x + 1 ] );
	}

//	iEditorButton[MERCS_BODYTYPE_DOWN] =
//		CreateEasyNoToggleButton( 460,364,"EDITOR\\leftarrow.sti", MercsSetBodyTypeCallback );
//	SetButtonFastHelpText( iEditorButton[ MERCS_BODYTYPE_DOWN ], L"Previous body type");
//	iEditorButton[MERCS_BODYTYPE_UP] =
//		CreateEasyNoToggleButton( 560,364,"EDITOR\\rightarrow.sti", MercsSetBodyTypeCallback );
//	SetButtonFastHelpText( iEditorButton[ MERCS_BODYTYPE_UP ], L"Next body type");

	iEditorButton[ MERCS_SCHEDULE_VARIANCE1 ] =
		CreateCheckBoxButton(	309, 375, "EDITOR\\SmCheckBox.sti", MSYS_PRIORITY_NORMAL, MercsScheduleToggleVariance1Callback );
	SetButtonFastHelpText( iEditorButton[ MERCS_SCHEDULE_VARIANCE1 ], gzEditorStrings[EDITOR_STR_TOGGLE_TIME_VAR]);
	iEditorButton[ MERCS_SCHEDULE_VARIANCE2 ] =
		CreateCheckBoxButton(	309, 396, "EDITOR\\SmCheckBox.sti", MSYS_PRIORITY_NORMAL, MercsScheduleToggleVariance2Callback );
	SetButtonFastHelpText( iEditorButton[ MERCS_SCHEDULE_VARIANCE2 ], gzEditorStrings[EDITOR_STR_TOGGLE_TIME_VAR]);
	iEditorButton[ MERCS_SCHEDULE_VARIANCE3 ] =
		CreateCheckBoxButton(	309, 417, "EDITOR\\SmCheckBox.sti", MSYS_PRIORITY_NORMAL, MercsScheduleToggleVariance3Callback );
	SetButtonFastHelpText( iEditorButton[ MERCS_SCHEDULE_VARIANCE3 ], gzEditorStrings[EDITOR_STR_TOGGLE_TIME_VAR]);
	iEditorButton[ MERCS_SCHEDULE_VARIANCE4 ] =
		CreateCheckBoxButton(	309, 438, "EDITOR\\SmCheckBox.sti", MSYS_PRIORITY_NORMAL, MercsScheduleToggleVariance4Callback );
	SetButtonFastHelpText( iEditorButton[ MERCS_SCHEDULE_VARIANCE4 ], gzEditorStrings[EDITOR_STR_TOGGLE_TIME_VAR]);

	iEditorButton[ MERCS_SCHEDULE_ACTION1 ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_NO_ACTION], FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		186, 373, 77, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleAction1Callback );
	iEditorButton[ MERCS_SCHEDULE_ACTION2 ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_NO_ACTION], FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		186, 394, 77, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleAction2Callback );
	iEditorButton[ MERCS_SCHEDULE_ACTION3 ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_NO_ACTION], FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		186, 415, 77, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleAction3Callback );
	iEditorButton[ MERCS_SCHEDULE_ACTION4 ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_NO_ACTION], FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		186, 436, 77, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleAction4Callback );

	iEditorButton[ MERCS_SCHEDULE_DATA1A ] =
		CreateTextButton( L"", FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		331, 373, 40, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleData1ACallback );
	iEditorButton[ MERCS_SCHEDULE_DATA1B ] =
		CreateTextButton( L"", FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		381, 373, 40, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleData1BCallback );
	iEditorButton[ MERCS_SCHEDULE_DATA2A ] =
		CreateTextButton( L"", FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		331, 394, 40, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleData2ACallback );
	iEditorButton[ MERCS_SCHEDULE_DATA2B ] =
		CreateTextButton( L"", FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		381, 394, 40, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleData2BCallback );
	iEditorButton[ MERCS_SCHEDULE_DATA3A ] =
		CreateTextButton( L"", FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		331, 415, 40, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleData3ACallback );
	iEditorButton[ MERCS_SCHEDULE_DATA3B ] =
		CreateTextButton( L"", FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		381, 415, 40, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleData3BCallback );
	iEditorButton[ MERCS_SCHEDULE_DATA4A ] =
		CreateTextButton( L"", FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		331, 436, 40, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleData4ACallback );
	iEditorButton[ MERCS_SCHEDULE_DATA4B ] =
		CreateTextButton( L"", FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		381, 436, 40, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleData4BCallback );
	iEditorButton[ MERCS_SCHEDULE_CLEAR ] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_CLEAR_SCHED], FONT10ARIAL, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		516, 362, 77, 16, BUTTON_NO_TOGGLE, MSYS_PRIORITY_NORMAL, DEFAULT_MOVE_CALLBACK, MercsScheduleClearCallback );
	HideEditorButtons( MERCS_SCHEDULE_DATA1A, MERCS_SCHEDULE_DATA4B );

	iEditorButton[ MERCS_HEAD_SLOT ] =
		CreateCheckBoxButton(	MERCPANEL_X+61, MERCPANEL_Y+0, "EDITOR\\smCheckbox.sti", MSYS_PRIORITY_NORMAL+1, MercsInventorySlotCallback );
	MSYS_SetBtnUserData( iEditorButton[ MERCS_HEAD_SLOT ], 0, HELMETPOS );
	iEditorButton[ MERCS_BODY_SLOT ] =
		CreateCheckBoxButton(	MERCPANEL_X+61, MERCPANEL_Y+22, "EDITOR\\smCheckbox.sti", MSYS_PRIORITY_NORMAL+1, MercsInventorySlotCallback );
	MSYS_SetBtnUserData( iEditorButton[ MERCS_BODY_SLOT ], 0, VESTPOS );
	iEditorButton[ MERCS_LEGS_SLOT ] =
		CreateCheckBoxButton(	MERCPANEL_X+62, MERCPANEL_Y+73, "EDITOR\\smCheckbox.sti", MSYS_PRIORITY_NORMAL+1, MercsInventorySlotCallback );
	MSYS_SetBtnUserData( iEditorButton[ MERCS_LEGS_SLOT ], 0, LEGPOS );
	iEditorButton[ MERCS_LEFTHAND_SLOT ] =
		CreateCheckBoxButton(	MERCPANEL_X+12, MERCPANEL_Y+43, "EDITOR\\smCheckbox.sti", MSYS_PRIORITY_NORMAL+1, MercsInventorySlotCallback );
	MSYS_SetBtnUserData( iEditorButton[ MERCS_LEFTHAND_SLOT ], 0, HANDPOS );
	iEditorButton[ MERCS_RIGHTHAND_SLOT ] =
		CreateCheckBoxButton(	MERCPANEL_X+90, MERCPANEL_Y+42, "EDITOR\\smCheckbox.sti", MSYS_PRIORITY_NORMAL+1, MercsInventorySlotCallback );
	MSYS_SetBtnUserData( iEditorButton[ MERCS_RIGHTHAND_SLOT ], 0, SECONDHANDPOS );
	iEditorButton[ MERCS_PACK1_SLOT ] =
		CreateCheckBoxButton(	MERCPANEL_X+166, MERCPANEL_Y+6, "EDITOR\\smCheckbox.sti", MSYS_PRIORITY_NORMAL+1, MercsInventorySlotCallback );
	MSYS_SetBtnUserData( iEditorButton[ MERCS_PACK1_SLOT ], 0, BIGPOCK1POS );
	iEditorButton[ MERCS_PACK2_SLOT ] =
		CreateCheckBoxButton(	MERCPANEL_X+166, MERCPANEL_Y+29, "EDITOR\\smCheckbox.sti", MSYS_PRIORITY_NORMAL+1, MercsInventorySlotCallback );
	MSYS_SetBtnUserData( iEditorButton[ MERCS_PACK2_SLOT ], 0, BIGPOCK2POS );
	iEditorButton[ MERCS_PACK3_SLOT ] =
		CreateCheckBoxButton(	MERCPANEL_X+166, MERCPANEL_Y+52, "EDITOR\\smCheckbox.sti", MSYS_PRIORITY_NORMAL+1, MercsInventorySlotCallback );
	MSYS_SetBtnUserData( iEditorButton[ MERCS_PACK3_SLOT ], 0, BIGPOCK3POS );
	iEditorButton[ MERCS_PACK4_SLOT ] =
		CreateCheckBoxButton(	MERCPANEL_X+166, MERCPANEL_Y+75, "EDITOR\\smCheckbox.sti", MSYS_PRIORITY_NORMAL+1, MercsInventorySlotCallback );
	MSYS_SetBtnUserData( iEditorButton[ MERCS_PACK4_SLOT ], 0, BIGPOCK4POS );
}

void InitEditorBuildingsToolbar()
{
	iEditorButton[BUILDING_TOGGLE_ROOF_VIEW] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_ROOFS],(UINT16)SMALLCOMPFONT, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		110, 400, 50, 15, BUTTON_TOGGLE,MSYS_PRIORITY_NORMAL,BUTTON_NO_CALLBACK,
		BuildingToggleRoofViewCallback);
	iEditorButton[BUILDING_TOGGLE_WALL_VIEW] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_WALLS],(UINT16)SMALLCOMPFONT, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		110, 415, 50, 15, BUTTON_TOGGLE,MSYS_PRIORITY_NORMAL,BUTTON_NO_CALLBACK,
		BuildingToggleWallViewCallback);
	iEditorButton[BUILDING_TOGGLE_INFO_VIEW] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_ROOM_INFO],(UINT16)SMALLCOMPFONT, FONT_YELLOW, FONT_BLACK, BUTTON_USE_DEFAULT,
		110, 430, 50, 15, BUTTON_TOGGLE,MSYS_PRIORITY_NORMAL,BUTTON_NO_CALLBACK,
		BuildingToggleInfoViewCallback);
	//Selection method buttons
	iEditorButton[BUILDING_PLACE_WALLS] =
		CreateEasyToggleButton( 180,370,"EDITOR\\wall.sti", BuildingWallCallback);
	//SetButtonFastHelpText(iEditorButton[BUILDING_PLACE_WALLS],L"Place walls using selection method");


	SetButtonFastHelpText(iEditorButton[BUILDING_PLACE_WALLS],
		gzEditorStrings[EDITOR_STR_PLACE_WALLS]);


	iEditorButton[BUILDING_PLACE_DOORS] =
		CreateEasyToggleButton( 210,370,"EDITOR\\door.sti",	BuildingDoorCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_PLACE_DOORS],gzEditorStrings[EDITOR_STR_PLACE_DOORS]);
	iEditorButton[BUILDING_PLACE_ROOFS] =
		CreateEasyToggleButton( 240,370,"EDITOR\\roof.sti", BuildingRoofCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_PLACE_ROOFS],gzEditorStrings[EDITOR_STR_PLACE_ROOFS]);
	iEditorButton[BUILDING_PLACE_WINDOWS] =
		CreateEasyToggleButton( 180,400,"EDITOR\\window.sti", BuildingWindowCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_PLACE_WINDOWS],gzEditorStrings[EDITOR_STR_PLACE_WINDOWS]);
	iEditorButton[BUILDING_PLACE_BROKEN_WALLS] =
		CreateEasyToggleButton( 210,400,"EDITOR\\crackwall.sti", BuildingCrackWallCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_PLACE_BROKEN_WALLS],gzEditorStrings[EDITOR_STR_PLACE_DAMAGED_WALLS]);
	iEditorButton[BUILDING_PLACE_FURNITURE] =
		CreateEasyToggleButton( 240,400,"EDITOR\\decor.sti", BuildingFurnitureCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_PLACE_FURNITURE],gzEditorStrings[EDITOR_STR_PLACE_FURNITURE]);
	iEditorButton[BUILDING_PLACE_DECALS] =
		CreateEasyToggleButton( 180,430,"EDITOR\\decal.sti", BuildingDecalCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_PLACE_DECALS],gzEditorStrings[EDITOR_STR_PLACE_DECALS]);
	iEditorButton[BUILDING_PLACE_FLOORS] =
		CreateEasyToggleButton( 210,430,"EDITOR\\floor.sti", BuildingFloorCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_PLACE_FLOORS],gzEditorStrings[EDITOR_STR_PLACE_FLOORS]);
	iEditorButton[BUILDING_PLACE_TOILETS] =
		CreateEasyToggleButton( 240,430,"EDITOR\\toilet.sti", BuildingToiletCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_PLACE_TOILETS],gzEditorStrings[EDITOR_STR_PLACE_GEN_FURNITURE]);

	//Smart method buttons
	iEditorButton[BUILDING_SMART_WALLS] =
		CreateEasyToggleButton( 290,370,"EDITOR\\wall.sti", BuildingSmartWallCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_SMART_WALLS],gzEditorStrings[EDITOR_STR_SMART_WALLS]);
	iEditorButton[BUILDING_SMART_DOORS] =
		CreateEasyToggleButton( 320,370,"EDITOR\\door.sti", BuildingSmartDoorCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_SMART_DOORS],gzEditorStrings[EDITOR_STR_SMART_DOORS]);
	iEditorButton[BUILDING_SMART_WINDOWS] =
		CreateEasyToggleButton( 290,400,"EDITOR\\window.sti", BuildingSmartWindowCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_SMART_WINDOWS],gzEditorStrings[EDITOR_STR_SMART_WINDOWS]);
	iEditorButton[BUILDING_SMART_BROKEN_WALLS] =
		CreateEasyToggleButton( 320,400,"EDITOR\\crackwall.sti", BuildingSmartCrackWallCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_SMART_BROKEN_WALLS],gzEditorStrings[EDITOR_STR_SMART_DAMAGED_WALLS]);
//	iEditorButton[BUILDING_DOORKEY] =
//		CreateEasyToggleButton( 290, 430,"EDITOR\\key.sti", BuildingDoorKeyCallback);
//	SetButtonFastHelpText(iEditorButton[BUILDING_DOORKEY], L"Lock or trap existing doors" );

	iEditorButton[BUILDING_NEW_ROOM] =
		CreateEasyToggleButton( 370,370,"EDITOR\\newroom.sti", BuildingNewRoomCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_NEW_ROOM],gzEditorStrings[EDITOR_STR_ADD_ROOM]);
	iEditorButton[BUILDING_CAVE_DRAWING] =
		CreateEasyToggleButton( 370,370,"EDITOR\\caves.sti", BuildingCaveDrawingCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_CAVE_DRAWING],gzEditorStrings[EDITOR_STR_EDIT_CAVE]);
	iEditorButton[BUILDING_SAW_ROOM] =
		CreateEasyToggleButton( 370,400,"EDITOR\\sawroom.sti", BuildingSawRoomCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_SAW_ROOM],gzEditorStrings[EDITOR_STR_REMOVE_AREA]);
	iEditorButton[BUILDING_KILL_BUILDING] =
		CreateEasyToggleButton( 370,430,"EDITOR\\delroom.sti", BuildingKillBuildingCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_KILL_BUILDING],gzEditorStrings[EDITOR_STR_REMOVE_BUILDING]);
	iEditorButton[BUILDING_NEW_ROOF] =
		CreateEasyToggleButton( 400,430,"EDITOR\\newroof.sti", BuildingNewRoofCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_NEW_ROOF],gzEditorStrings[EDITOR_STR_REPLACE_ROOF]);
	iEditorButton[BUILDING_COPY_BUILDING] =
		CreateEasyToggleButton( 430,430,"EDITOR\\copyroom.sti", BuildingCopyBuildingCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_COPY_BUILDING],gzEditorStrings[EDITOR_STR_COPY_BUILDING]);
	iEditorButton[BUILDING_MOVE_BUILDING] =
		CreateEasyToggleButton( 460,430,"EDITOR\\moveroom.sti", BuildingMoveBuildingCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_MOVE_BUILDING],gzEditorStrings[EDITOR_STR_MOVE_BUILDING]);
	iEditorButton[BUILDING_DRAW_ROOMNUM] =
		CreateEasyToggleButton( 410,370,"EDITOR\\addTileRoom.sti", BuildingDrawRoomNumCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_DRAW_ROOMNUM],gzEditorStrings[EDITOR_STR_DRAW_ROOM_NUMBER]);
	iEditorButton[BUILDING_ERASE_ROOMNUM] =
		CreateEasyToggleButton( 440,370,"EDITOR\\killTileRoom.sti", BuildingEraseRoomNumCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_ERASE_ROOMNUM],gzEditorStrings[EDITOR_STR_ERASE_ROOM_NUMBER]);

	iEditorButton[BUILDING_TOGGLE_ERASEMODE] =
		CreateEasyToggleButton( 500,400,"EDITOR\\eraser.sti", BtnEraseCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_TOGGLE_ERASEMODE],gzEditorStrings[EDITOR_STR_TOGGLE_ERASE_MODE]);
	iEditorButton[BUILDING_UNDO] =
		CreateEasyNoToggleButton( 530,400,"EDITOR\\undo.sti", BtnUndoCallback);
	SetButtonFastHelpText(iEditorButton[BUILDING_UNDO],gzEditorStrings[EDITOR_STR_UNDO_LAST]);
	iEditorButton[BUILDING_CYCLE_BRUSHSIZE] =
		CreateEasyNoToggleButton( 500,430,"EDITOR\\paint.sti",BtnBrushCallback);
	SetButtonFastHelpText( iEditorButton[ BUILDING_CYCLE_BRUSHSIZE ], gzEditorStrings[EDITOR_STR_CYCLE_BRUSH_SIZE]);
}

void InitEditorItemsToolbar()
{
	SetFontForeground( FONT_MCOLOR_LTRED );
	iEditorButton[ITEMS_WEAPONS] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_WEAPONS],(UINT16)BLOCKFONT, FONT_MCOLOR_DKWHITE, FONT_BLACK, BUTTON_USE_DEFAULT,
		100, 440, 59, 20, BUTTON_TOGGLE,MSYS_PRIORITY_NORMAL,DEFAULT_MOVE_CALLBACK,
		ItemsWeaponsCallback);
	iEditorButton[ITEMS_AMMO] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_AMMO],(UINT16)BLOCKFONT, FONT_MCOLOR_DKWHITE, FONT_BLACK, BUTTON_USE_DEFAULT,
		159, 440, 40, 20, BUTTON_TOGGLE,MSYS_PRIORITY_NORMAL,DEFAULT_MOVE_CALLBACK,
		ItemsAmmoCallback);
	iEditorButton[ITEMS_ARMOUR] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_ARMOR],(UINT16)BLOCKFONT, FONT_MCOLOR_DKWHITE, FONT_BLACK, BUTTON_USE_DEFAULT,
		199, 440, 52, 20, BUTTON_TOGGLE,MSYS_PRIORITY_NORMAL,DEFAULT_MOVE_CALLBACK,
		ItemsArmourCallback);
	iEditorButton[ITEMS_EXPLOSIVES] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_EXPLOSIVES],(UINT16)BLOCKFONT, FONT_MCOLOR_DKWHITE, FONT_BLACK, BUTTON_USE_DEFAULT,
		251, 440, 69, 20, BUTTON_TOGGLE,MSYS_PRIORITY_NORMAL,DEFAULT_MOVE_CALLBACK,
		ItemsExplosivesCallback);
	iEditorButton[ITEMS_EQUIPMENT1] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_E1],(UINT16)BLOCKFONT, FONT_MCOLOR_DKWHITE, FONT_BLACK, BUTTON_USE_DEFAULT,
		320, 440, 21, 20, BUTTON_TOGGLE,MSYS_PRIORITY_NORMAL,DEFAULT_MOVE_CALLBACK,
		ItemsEquipment1Callback);
	iEditorButton[ITEMS_EQUIPMENT2] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_E2],(UINT16)BLOCKFONT, FONT_MCOLOR_DKWHITE, FONT_BLACK, BUTTON_USE_DEFAULT,
		341, 440, 21, 20, BUTTON_TOGGLE,MSYS_PRIORITY_NORMAL,DEFAULT_MOVE_CALLBACK,
		ItemsEquipment2Callback);
	iEditorButton[ITEMS_EQUIPMENT3] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_E3],(UINT16)BLOCKFONT, FONT_MCOLOR_DKWHITE, FONT_BLACK, BUTTON_USE_DEFAULT,
		362, 440, 21, 20, BUTTON_TOGGLE,MSYS_PRIORITY_NORMAL,DEFAULT_MOVE_CALLBACK,
		ItemsEquipment3Callback);
	iEditorButton[ITEMS_TRIGGERS] =
		CreateTextButton( gzEditorStrings[EDITOR_STR_TRIGGERS],(UINT16)BLOCKFONT, FONT_MCOLOR_DKWHITE, FONT_BLACK, BUTTON_USE_DEFAULT,
		383, 440, 59, 20, BUTTON_TOGGLE,MSYS_PRIORITY_NORMAL,DEFAULT_MOVE_CALLBACK,
		ItemsTriggersCallback );
//	iEditorButton[ITEMS_KEYS] =
//		CreateTextButton( L"Keys",(UINT16)BLOCKFONT, FONT_MCOLOR_DKWHITE, FONT_BLACK, BUTTON_USE_DEFAULT,
//		442, 440, 38, 20, BUTTON_TOGGLE,MSYS_PRIORITY_NORMAL,DEFAULT_MOVE_CALLBACK,
//		ItemsKeysCallback );

	iEditorButton[ITEMS_LEFTSCROLL] =
		CreateEasyNoToggleButton( 1,361,"EDITOR\\leftscroll.sti", ItemsLeftScrollCallback);
	iEditorButton[ITEMS_RIGHTSCROLL] =
		CreateEasyNoToggleButton( 50,361,"EDITOR\\rightscroll.sti", ItemsRightScrollCallback);

}

void InitEditorMapInfoToolbar()
{
	iEditorButton[MAPINFO_ADD_LIGHT1_SOURCE] =
		CreateEasyToggleButton( 10, 362, "EDITOR\\light.sti", BtnDrawLightsCallback );
	SetButtonFastHelpText(iEditorButton[MAPINFO_ADD_LIGHT1_SOURCE],gzEditorStrings[EDITOR_STR_ADD_LIGHT_SOURCE]);

	iEditorButton[ MAPINFO_LIGHT_PANEL ] =
		CreateTextButton( 0, 0, 0, 0, BUTTON_USE_DEFAULT, 45, 362, 60, 50, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, BUTTON_NO_CALLBACK, BUTTON_NO_CALLBACK );
	SpecifyDisabledButtonStyle( iEditorButton[ MAPINFO_LIGHT_PANEL ], DISABLED_STYLE_NONE );
	DisableButton( iEditorButton[ MAPINFO_LIGHT_PANEL ] );
	iEditorButton[ MAPINFO_PRIMETIME_LIGHT ] =
		CreateCheckBoxButton(	48, 365, "EDITOR\\radiobutton.sti", MSYS_PRIORITY_NORMAL, MapInfoPrimeTimeRadioCallback );
	iEditorButton[ MAPINFO_NIGHTTIME_LIGHT ] =
		CreateCheckBoxButton(	48, 380, "EDITOR\\radiobutton.sti", MSYS_PRIORITY_NORMAL, MapInfoNightTimeRadioCallback );
	iEditorButton[ MAPINFO_24HOUR_LIGHT ] =
		CreateCheckBoxButton(	48, 395, "EDITOR\\radiobutton.sti", MSYS_PRIORITY_NORMAL, MapInfo24HourTimeRadioCallback );
	ClickEditorButton( gbDefaultLightType + MAPINFO_PRIMETIME_LIGHT );

	iEditorButton[MAPINFO_TOGGLE_FAKE_LIGHTS] =
		CreateEasyToggleButton( 120, 362, "EDITOR\\fakelight.sti", BtnFakeLightCallback );
	SetButtonFastHelpText(iEditorButton[MAPINFO_TOGGLE_FAKE_LIGHTS], gzEditorStrings[EDITOR_STR_TOGGLE_FAKE_LIGHTS]);

	iEditorButton[ MAPINFO_RADIO_PANEL ] =
		CreateTextButton( 0, 0, 0, 0, BUTTON_USE_DEFAULT, 207, 362, 70, 50, BUTTON_TOGGLE, MSYS_PRIORITY_NORMAL, BUTTON_NO_CALLBACK, BUTTON_NO_CALLBACK );
	SpecifyDisabledButtonStyle( iEditorButton[ MAPINFO_RADIO_PANEL ], DISABLED_STYLE_NONE );
	DisableButton( iEditorButton[ MAPINFO_RADIO_PANEL ] );
	iEditorButton[ MAPINFO_RADIO_NORMAL ] =
		CreateCheckBoxButton(	210, 365, "EDITOR\\radiobutton.sti", MSYS_PRIORITY_NORMAL, MapInfoNormalRadioCallback );
	iEditorButton[ MAPINFO_RADIO_BASEMENT ] =
		CreateCheckBoxButton(	210, 380, "EDITOR\\radiobutton.sti", MSYS_PRIORITY_NORMAL, MapInfoBasementRadioCallback );
	iEditorButton[ MAPINFO_RADIO_CAVES ] =
		CreateCheckBoxButton(	210, 395, "EDITOR\\radiobutton.sti", MSYS_PRIORITY_NORMAL, MapInfoCavesRadioCallback );

	iEditorButton[MAPINFO_DRAW_EXITGRIDS] =
		CreateEasyToggleButton( 305, 372, "EDITOR\\exitgridbut.sti", MapInfoDrawExitGridCallback );
	SetButtonFastHelpText(iEditorButton[MAPINFO_DRAW_EXITGRIDS],gzEditorStrings[EDITOR_STR_ADD_EXIT_GRIDS]);
	iEditorButton[MAPINFO_CYCLE_BRUSHSIZE] =
		CreateEasyNoToggleButton( 310, 430, "EDITOR\\paint.sti", BtnBrushCallback );
	SetButtonFastHelpText(iEditorButton[MAPINFO_CYCLE_BRUSHSIZE],gzEditorStrings[EDITOR_STR_CYCLE_BRUSH_SIZE]);
	iEditorButton[MAPINFO_UNDO] =
		CreateEasyNoToggleButton( 560, 430, "EDITOR\\undo.sti", BtnUndoCallback );
	SetButtonFastHelpText(iEditorButton[MAPINFO_UNDO],gzEditorStrings[EDITOR_STR_UNDO_LAST]);
	iEditorButton[MAPINFO_TOGGLE_ERASEMODE] =
		CreateEasyToggleButton( 590, 430, "EDITOR\\eraser.sti", BtnEraseCallback);
	SetButtonFastHelpText(iEditorButton[MAPINFO_TOGGLE_ERASEMODE],gzEditorStrings[EDITOR_STR_TOGGLE_ERASE_MODE]);

	iEditorButton[ MAPINFO_NORTH_POINT ] =
		CreateEasyToggleButton( 540, 365, "EDITOR\\north.sti", MapInfoEntryPointsCallback);
	SetButtonFastHelpText( iEditorButton[ MAPINFO_NORTH_POINT ], gzEditorStrings[EDITOR_STR_SPECIFY_NORTH_POINT]);

	iEditorButton[ MAPINFO_WEST_POINT ] =
		CreateEasyToggleButton( 525, 386, "EDITOR\\west.sti", MapInfoEntryPointsCallback);
	SetButtonFastHelpText( iEditorButton[ MAPINFO_WEST_POINT ], gzEditorStrings[EDITOR_STR_SPECIFY_WEST_POINT]);

	iEditorButton[ MAPINFO_EAST_POINT ] =
		CreateEasyToggleButton( 555, 386, "EDITOR\\east.sti", MapInfoEntryPointsCallback);
	SetButtonFastHelpText( iEditorButton[ MAPINFO_EAST_POINT ], gzEditorStrings[EDITOR_STR_SPECIFY_EAST_POINT]);

	iEditorButton[ MAPINFO_SOUTH_POINT ] =
		CreateEasyToggleButton( 540, 407, "EDITOR\\south.sti", MapInfoEntryPointsCallback);
	SetButtonFastHelpText( iEditorButton[ MAPINFO_SOUTH_POINT ], gzEditorStrings[EDITOR_STR_SPECIFY_SOUTH_POINT]);

	iEditorButton[ MAPINFO_CENTER_POINT ] =
		CreateEasyToggleButton( 590, 375, "EDITOR\\center.sti", MapInfoEntryPointsCallback);
	SetButtonFastHelpText( iEditorButton[ MAPINFO_CENTER_POINT ], gzEditorStrings[EDITOR_STR_SPECIFY_CENTER_POINT]);

	iEditorButton[ MAPINFO_ISOLATED_POINT ] =
		CreateEasyToggleButton( 590, 396, "EDITOR\\isolated.sti", MapInfoEntryPointsCallback);
	SetButtonFastHelpText( iEditorButton[ MAPINFO_ISOLATED_POINT ], gzEditorStrings[EDITOR_STR_SPECIFY_ISOLATED_POINT]);
}

void InitEditorOptionsToolbar()
{
	iEditorButton[OPTIONS_NEW_MAP] =
		CreateEasyNoToggleButton( 71,401,"EDITOR\\new.sti",  BtnNewMapCallback);
	SetButtonFastHelpText(iEditorButton[OPTIONS_NEW_MAP],gzEditorStrings[EDITOR_STR_NEW_MAP]);

	iEditorButton[OPTIONS_NEW_BASEMENT] =
		CreateEasyNoToggleButton( 101,401,"EDITOR\\new.sti",  BtnNewBasementCallback);
	SetButtonFastHelpText(iEditorButton[OPTIONS_NEW_BASEMENT],gzEditorStrings[EDITOR_STR_NEW_BASEMENT]);

	iEditorButton[OPTIONS_NEW_CAVES] =
		CreateEasyNoToggleButton( 131,401,"EDITOR\\new.sti", BtnNewCavesCallback);
	SetButtonFastHelpText(iEditorButton[OPTIONS_NEW_CAVES],gzEditorStrings[EDITOR_STR_NEW_CAVE]);

	iEditorButton[OPTIONS_SAVE_MAP] =
		CreateEasyNoToggleButton( 161,401,"EDITOR\\save.sti",  BtnSaveCallback);
	SetButtonFastHelpText(iEditorButton[OPTIONS_SAVE_MAP],gzEditorStrings[EDITOR_STR_SAVE_MAP]);

	iEditorButton[OPTIONS_LOAD_MAP] =
		CreateEasyNoToggleButton( 191,401,"EDITOR\\load.sti",  BtnLoadCallback);
	SetButtonFastHelpText(iEditorButton[OPTIONS_LOAD_MAP],gzEditorStrings[EDITOR_STR_LOAD_MAP]);

	iEditorButton[OPTIONS_CHANGE_TILESET] =
		CreateEasyNoToggleButton( 221,401,"EDITOR\\tileset.sti", BtnChangeTilesetCallback);
	SetButtonFastHelpText(iEditorButton[OPTIONS_CHANGE_TILESET],gzEditorStrings[EDITOR_STR_SELECT_TILESET]);

	iEditorButton[OPTIONS_LEAVE_EDITOR] =
		CreateEasyNoToggleButton( 251,401,"EDITOR\\cancel.sti", BtnCancelCallback);
	SetButtonFastHelpText(iEditorButton[OPTIONS_LEAVE_EDITOR],gzEditorStrings[EDITOR_STR_LEAVE_EDITOR]);

//	iEditorButton[OPTIONS_QUIT_GAME] =
//		CreateEasyNoToggleButton( 281,401,"EDITOR\\cancel.sti", BtnQuitCallback);
//	SetButtonFastHelpText(iEditorButton[OPTIONS_QUIT_GAME],L"Exit game.");

	iEditorButton[OPTIONS_DIRECTION_DOWN] =
		CreateEasyNoToggleButton( 510,410,"EDITOR\\leftarrow.sti", OptionsDirectionDown );
	SetButtonFastHelpText( iEditorButton[ OPTIONS_DIRECTION_DOWN ], gzEditorStrings[EDITOR_STR_PREV_DIR]);
	iEditorButton[OPTIONS_DIRECTION_UP] =
		CreateEasyNoToggleButton( 600,410,"EDITOR\\rightarrow.sti", OptionsDirectionUp );
	SetButtonFastHelpText( iEditorButton[ OPTIONS_DIRECTION_UP ], gzEditorStrings[EDITOR_STR_NEXT_DIR]);

	iEditorButton[OPTIONS_LOADSCREEN_DOWN] =
		CreateEasyNoToggleButton( 120,372,"EDITOR\\leftarrow.sti", OptionsLoadscreenDown );
	SetButtonFastHelpText( iEditorButton[ OPTIONS_LOADSCREEN_DOWN ], gzEditorStrings[EDITOR_STR_PREV_LOADSCREEN]);
	iEditorButton[OPTIONS_LOADSCREEN_UP] =
		CreateEasyNoToggleButton( 230,372,"EDITOR\\rightarrow.sti", OptionsLoadscreenUp );
	SetButtonFastHelpText( iEditorButton[ OPTIONS_LOADSCREEN_UP ], gzEditorStrings[EDITOR_STR_NEXT_LOADSCREEN]);

}

void InitEditorTerrainToolbar()
{
	iEditorButton[TERRAIN_FGROUND_TEXTURES] =
		CreateEasyToggleButton( 100,400,"EDITOR\\downgrid.sti", BtnFgGrndCallback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_FGROUND_TEXTURES],gzEditorStrings[EDITOR_STR_DRAW_GROUND]);

	iEditorButton[TERRAIN_BGROUND_TEXTURES] =
		CreateEasyToggleButton( 130,400,"EDITOR\\upgrid.sti", BtnBkGrndCallback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_BGROUND_TEXTURES],gzEditorStrings[EDITOR_STR_SET_GROUND]);

	iEditorButton[TERRAIN_PLACE_CLIFFS] =
		CreateEasyToggleButton( 160,400,"EDITOR\\banks.sti", BtnBanksCallback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_PLACE_CLIFFS],gzEditorStrings[EDITOR_STR_PLACE_CLIFFS]);

	iEditorButton[TERRAIN_PLACE_ROADS] =
		CreateEasyToggleButton( 190,400,"EDITOR\\road.sti", BtnRoadsCallback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_PLACE_ROADS],gzEditorStrings[EDITOR_STR_DRAW_ROADS]);

	iEditorButton[TERRAIN_PLACE_DEBRIS] =
		CreateEasyToggleButton( 220,400,"EDITOR\\debris.sti", BtnDebrisCallback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_PLACE_DEBRIS],gzEditorStrings[EDITOR_STR_DRAW_DEBRIS]);

	iEditorButton[TERRAIN_PLACE_TREES] =
		CreateEasyToggleButton( 250,400,"EDITOR\\tree.sti", BtnObjectCallback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_PLACE_TREES],gzEditorStrings[EDITOR_STR_PLACE_TREES]);

	iEditorButton[TERRAIN_PLACE_ROCKS] =
		CreateEasyToggleButton( 280,400,"EDITOR\\num1.sti", BtnObject1Callback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_PLACE_ROCKS],gzEditorStrings[EDITOR_STR_PLACE_ROCKS]);

	iEditorButton[TERRAIN_PLACE_MISC] =
		CreateEasyToggleButton( 310,400,"EDITOR\\num2.sti", BtnObject2Callback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_PLACE_MISC],gzEditorStrings[EDITOR_STR_PLACE_JUNK]);

	iEditorButton[TERRAIN_FILL_AREA] =
		CreateEasyToggleButton( 100,430,"EDITOR\\fill.sti", BtnFillCallback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_FILL_AREA],gzEditorStrings[EDITOR_STR_FILL_AREA]);

	iEditorButton[TERRAIN_UNDO] =
		CreateEasyNoToggleButton( 130,430,"EDITOR\\undo.sti", BtnUndoCallback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_UNDO],gzEditorStrings[EDITOR_STR_UNDO_LAST]);

	iEditorButton[TERRAIN_TOGGLE_ERASEMODE] =
		CreateEasyToggleButton( 160,430,"EDITOR\\eraser.sti", BtnEraseCallback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_TOGGLE_ERASEMODE],gzEditorStrings[EDITOR_STR_TOGGLE_ERASE_MODE]);

	iEditorButton[TERRAIN_CYCLE_BRUSHSIZE] =
		CreateEasyNoToggleButton( 190,430,"EDITOR\\paint.sti", BtnBrushCallback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_CYCLE_BRUSHSIZE],gzEditorStrings[EDITOR_STR_CYCLE_BRUSH_SIZE]);

	iEditorButton[TERRAIN_RAISE_DENSITY] =
		CreateEasyNoToggleButton( 280,430,"EDITOR\\uparrow.sti", BtnIncBrushDensityCallback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_RAISE_DENSITY],gzEditorStrings[EDITOR_STR_RAISE_BRUSH_DENSITY]);

	iEditorButton[TERRAIN_LOWER_DENSITY] =
		CreateEasyNoToggleButton( 350,430,"EDITOR\\downarrow.sti", BtnDecBrushDensityCallback);
	SetButtonFastHelpText(iEditorButton[TERRAIN_LOWER_DENSITY],gzEditorStrings[EDITOR_STR_LOWER_BRUSH_DENSITY]);
}

void CreateEditorTaskbarInternal()
{
	//Create the tabs for the editor taskbar
	iEditorButton[ TAB_TERRAIN ] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_TERRAIN], (UINT16)SMALLFONT1, FONT_LTKHAKI, FONT_DKKHAKI, BUTTON_USE_DEFAULT,
		100, 460, 90, 20, BUTTON_TOGGLE,MSYS_PRIORITY_HIGH,BUTTON_NO_CALLBACK,
		TaskTerrainCallback);
	SpecifyButtonDownTextColors( iEditorButton[TAB_TERRAIN], FONT_YELLOW, FONT_ORANGE );
	iEditorButton[ TAB_BUILDINGS ] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_BUILDINGS], (UINT16)SMALLFONT1, FONT_LTKHAKI, FONT_DKKHAKI, BUTTON_USE_DEFAULT,
		190, 460, 90, 20, BUTTON_TOGGLE,MSYS_PRIORITY_HIGH,BUTTON_NO_CALLBACK,
		TaskBuildingCallback);
	SpecifyButtonDownTextColors( iEditorButton[TAB_BUILDINGS], FONT_YELLOW, FONT_ORANGE );
	iEditorButton[ TAB_ITEMS ] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_ITEMS], (UINT16)SMALLFONT1, FONT_LTKHAKI, FONT_DKKHAKI, BUTTON_USE_DEFAULT,
		280, 460, 90, 20, BUTTON_TOGGLE,MSYS_PRIORITY_HIGH,BUTTON_NO_CALLBACK,
		TaskItemsCallback);
	SpecifyButtonDownTextColors( iEditorButton[TAB_ITEMS], FONT_YELLOW, FONT_ORANGE );
	iEditorButton[ TAB_MERCS ] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_MERCS], (UINT16)SMALLFONT1, FONT_LTKHAKI, FONT_DKKHAKI, BUTTON_USE_DEFAULT,
		370, 460, 90, 20, BUTTON_TOGGLE,MSYS_PRIORITY_HIGH,BUTTON_NO_CALLBACK,
		TaskMercsCallback);
	SpecifyButtonDownTextColors( iEditorButton[TAB_MERCS], FONT_YELLOW, FONT_ORANGE );
	iEditorButton[ TAB_MAPINFO ] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_MAP_INFO], (UINT16)SMALLFONT1, FONT_LTKHAKI, FONT_DKKHAKI, BUTTON_USE_DEFAULT,
		460, 460, 90, 20, BUTTON_TOGGLE,MSYS_PRIORITY_HIGH,BUTTON_NO_CALLBACK,
		TaskMapInfoCallback);
	SpecifyButtonDownTextColors( iEditorButton[TAB_MAPINFO], FONT_YELLOW, FONT_ORANGE );
	iEditorButton[ TAB_OPTIONS ] =
		CreateTextButton(gzEditorStrings[EDITOR_STR_MISC], (UINT16)SMALLFONT1, FONT_LTKHAKI, FONT_DKKHAKI, BUTTON_USE_DEFAULT,
		550, 460, 90, 20, BUTTON_TOGGLE,MSYS_PRIORITY_HIGH,BUTTON_NO_CALLBACK,
		TaskOptionsCallback);
	SpecifyButtonDownTextColors( iEditorButton[TAB_OPTIONS], FONT_YELLOW, FONT_ORANGE );

	//Create the buttons within each tab.
	InitEditorTerrainToolbar();
	InitEditorBuildingsToolbar();
	InitEditorItemsToolbar();
	InitEditorMercsToolbar();
	InitEditorMapInfoToolbar();
	InitEditorOptionsToolbar();
	InitEditorItemStatsButtons();
}


#endif
