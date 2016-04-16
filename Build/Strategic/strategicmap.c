#ifdef PRECOMPILEDHEADERS
	#include "Strategic All.h"
	#include "Loading Screen.h"
	#include "Enemy Soldier Save.h"
	#include "Ja25Update.h"
	#include "MapScreen Quotes.h"
	#include "Ja25_Tactical.h"
	#include "Ja25 Strategic Ai.h"
	#include "CustomMapHeader.h"
#else
	#include "strategicmap.h"
	#include "strategic.h"
	#include "Strategic Mines.h"
	#include "types.h"
	#include "memory.h"
	#include <stdio.h>
	#include <stdarg.h>
	#include <math.h>
	#include <time.h> 
	#include "jascreens.h"
	#include "worlddef.h"
	#include "Soldier Control.h"
	#include "overhead.h"
	#include "interface panels.h"
	#include "isometric utils.h"
	#include "Ambient Control.h"
	#include "worlddef.h"
	#include "worlddat.h"
	#include "text.h"
	#include "Soldier add.h"
	#include "soldier macros.h"
	#include "Strategic Pathing.h"
	#include "soldier create.h"
	#include "handle UI.h"
	#include "faces.h"
	#include "renderworld.h"
	#include "gamescreen.h"
	#include "game clock.h"
	#include "Soldier Init List.h"
	#include "strategic turns.h"
	#include "merc entering.h"
	#include "Map Information.h"
	#include "Assignments.h"
	#include "message.h"
	#include "Font Control.h"
	#include "environment.h"
	#include "Game Events.h"
	#include "quests.h"
	#include "FileMan.h"
	#include "animated progressbar.h"
	#include "music control.h"
	#include "fade screen.h"
	#include "Strategic Movement.h"
	#include "Campaign Types.h"
	#include "sys globals.h"
	#include "Exit Grids.h"
	#include "Tactical Save.h"
	#include "pathai.h"
	#include "animation control.h"
	#include "squads.h"
	#include "worldman.h"
	#include "Overhead.h"
	#include "Strategic Town Loyalty.h"
	#include "Queen Command.h"
	#include "cursor control.h"
	#include "PreBattle Interface.h"
	#include "Shade Table Util.h"
	#include "Scheduling.h"
	#include "gameloop.h"
	#include "Random.h"
	#include "ai.h"
	#include "opplist.h"
	#include "keys.h"
	#include "Tactical Placement GUI.h"
	#include "Map Screen Helicopter.h"
	#include "map edgepoints.h"
	#include "Player Command.h"
	#include "Event Pump.h"
	#include "meanwhile.h"
	#include "air raid.h"
	#include "Strategic Mines.h"
	#include "Creature Spreading.h"
	#include "SaveLoadMap.h"
	#include "Militia Control.h"
	#include "gamesettings.h"
	#include "dialogue control.h"
	#include "Town Militia.h"
	#include "sysutil.h"
	#include "sound control.h"
	#include "points.h"
	#include "JA2 Demo Ads.h"
	#include "render dirty.h"
#endif

#include "SaveLoadGame.h"

//Used by PickGridNoToWalkIn
#define MAX_ATTEMPTS	200

#define		QUEST_CHECK_EVENT_TIME							( 8 * 60 )
#define		BOBBYRAY_UPDATE_TIME							  ( 9 * 60 )
#define		INSURANCE_UPDATE_TIME								0
#define		EARLY_MORNING_TIME									( 4 * 60 )
#define   ENRICO_MAIL_TIME                    ( 7 * 60 ) 

enum
{
	ABOUT_TO_LOAD_NEW_MAP,
	ABOUT_TO_TRASH_WORLD,
};
BOOLEAN HandleDefiniteUnloadingOfWorld( UINT8 ubUnloadCode );

extern	INT16		gsRobotGridNo;
extern	BOOLEAN	gfUndergroundTacticalTraversal;
extern	INT8 gbExitingMapScreenToWhere;

extern	MINE_LOCATION_TYPE gMineLocation[MAX_NUMBER_OF_MINES];

extern void CalculateNonPersistantPBIInfo();

extern void MapScreenDefaultOkBoxCallback( UINT8 bExitValue );

BOOLEAN		gfGettingNameFromSaveLoadScreen;

INT16			gWorldSectorX = 0;
INT16			gWorldSectorY = 0;
INT8			gbWorldSectorZ = -1;

INT16			gsAdjacentSectorX, gsAdjacentSectorY;
INT8			gbAdjacentSectorZ;
GROUP			*gpAdjacentGroup = NULL;
UINT8			gubAdjacentJumpCode;
UINT32		guiAdjacentTraverseTime;
UINT8			gubTacticalDirection;
INT16			gsAdditionalData;
UINT16		gusDestExitGridNo;

BOOLEAN		fUsingEdgePointsForStrategicEntry = FALSE;
BOOLEAN		gfInvalidTraversal = FALSE;
BOOLEAN		gfLoneEPCAttemptingTraversal = FALSE;
BOOLEAN		gfRobotWithoutControllerAttemptingTraversal = FALSE;
BOOLEAN   gubLoneMercAttemptingToAbandonEPCs = 0;
INT8			gbPotentiallyAbandonedEPCSlotID = -1;

INT8 gbGreenToElitePromotions = 0;
INT8 gbGreenToRegPromotions = 0;
INT8 gbRegToElitePromotions = 0;
INT8 gbMilitiaPromotions = 0;


extern BOOLEAN gfUsePersistantPBI;

extern STRUCTURE * SwapStructureForPartnerForcingGraphicalChangeAndStoreChangeInMap( INT16 sGridNo, STRUCTURE * pStructure );

BOOLEAN		gfUseAlternateMap = FALSE;

/*
JA25: no orta
// whether or not we have found Orta yet
BOOLEAN fFoundOrta = FALSE;
*/

// have any of the sam sites been found
BOOLEAN fSamSiteFound[ NUMBER_OF_SAMS ]={
	FALSE,
	FALSE,
	FALSE,
	FALSE,
};

INT16 pSamList[ NUMBER_OF_SAMS ]={
	SECTOR( SAM_1_X, SAM_1_Y ),
	SECTOR( SAM_2_X, SAM_2_Y ),
	SECTOR( SAM_3_X, SAM_3_Y ),
	SECTOR( SAM_4_X, SAM_4_Y ),
};

INT16 pSamGridNoAList[ NUMBER_OF_SAMS ]={
	10196,
	11295,
	16080,
	11913,
};

INT16 pSamGridNoBList[ NUMBER_OF_SAMS ]={
	10195,
	11135,
	15920,
	11912, 
};

// ATE: Update this w/ graphic used 
// Use 3 if / orientation, 4 if \ orientation
INT8 gbSAMGraphicList[ NUMBER_OF_SAMS ]={
	4,
	3,
	3,
  3,
};

INT8 gbMercIsNewInThisSector[ MAX_NUM_SOLDIERS ];


// the amount of time that a soldier will wait to return to desired/old squad
#define DESIRE_SQUAD_RESET_DELAY 12 * 60



UINT8 ubSAMControlledSectors[ MAP_WORLD_Y ][ MAP_WORLD_X ] = {
//       1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,

    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// A
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// B
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// C
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// D
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// E
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// F
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// G
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// H
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// I
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// J
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// K
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// L
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// M
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// N
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// O
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,		// P

    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,
};

/*
ja25

UINT8 ubSAMControlledSectors[ MAP_WORLD_Y ][ MAP_WORLD_X ] = {
//       1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,

    0,   1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 2, 2, 2, 2, 2,   0,		// A
    0,   1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,   0,		// B
    0,   1, 1, 1, 1, 1, 1, 1, 3, 2, 2, 2, 2, 2, 2, 2, 2,   0,		// C
    0,   1,01, 1, 1, 1, 1, 1, 3, 3, 2, 2, 2, 2, 2,02, 2,   0,		// D
    0,   1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2,   0,		// E
    0,   1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2,   0,		// F
    0,   1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2,   0,		// G
    0,   1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,   0,		// H
    0,   1, 1, 3, 3, 3, 3, 3,03, 3, 3, 3, 3, 3, 2, 2, 2,   0,		// I
    0,   1, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,   0,		// J
    0,   4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,   0,		// K
    0,   4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,   0,		// L
    0,   4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 2, 2, 2,   0,		// M
    0,   4, 4, 4,04, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2,   0,		// N
    0,   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2,   0,		// O
    0,   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2,   0,		// P

    0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,
};

*/


INT16 DirXIncrementer[8] =
 {
  0,        //N
	1,        //NE
	1,        //E
	1,        //SE
	0,         //S
	-1,       //SW
	-1,       //W
	-1       //NW
 };

INT16 DirYIncrementer[8] =
 {
  -1,        //N
	-1,        //NE
	0,        //E
	1,        //SE
	1,         //S
	1,       //SW
	0,       //W
	-1       //NW
 };


STR8 pVertStrings[]={
"X",
"A",
"B",
"C",
"D",
"E",
"F",
"G",
"H",
"I",
"J",
"K",
"L",
"M",
"N",
"O",
"P",
"Q",
"R",
};

STR8 pHortStrings[]={
"X",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"10",
"11",
"12",
"13",
"14",
"15",
"16",
"17",
};

void DoneFadeOutAdjacentSector( void );
void DoneFadeOutExitGridSector( void );

INT16 PickGridNoNearestEdge( SOLDIERTYPE *pSoldier, UINT8 ubTacticalDirection );
INT16 PickGridNoToWalkIn( SOLDIERTYPE *pSoldier, UINT8 ubInsertionDirection, UINT32 *puiNumAttempts );

void HandleQuestCodeOnSectorExit( INT16 sOldSectorX, INT16 sOldSectorY, INT8 bOldSectorZ );
void HandlePotentialMoraleHitForSkimmingSectors( GROUP *pGroup );
void HandlePlayerTeamQuotesWhenEnteringSector( INT16 sSectorX, INT16 sSectorY, INT16 sSectorZ );
void ShouldNpcBeAddedToSector( INT16 sMapX, INT16 sMapY, INT8 bMapZ );
void HandlePlayerQuotesWhenEnteringFirstTunnelSector();
void AddExitGridForFanToPowerGenSector();
void HandleSectorSpecificUnLoadingOfMap( INT16 sMapX, INT16 sMapY, INT8 bMapZ );
void MakeAllTeamMembersCrouchedThenStand();
void HandleMovingTheEnemiesToBeNearPlayerWhenEnteringComplexMap();
void HandleFortifiedDoor();
void CreateAndAddMoneyObjectToGround( INT16 sGridNo, INT32 iEasyAmount, INT32 iNormalAmount, INT32 iHardAmount );
void HandleGoingUpOrDownStairsForLoadScreensPurposes( INT16 sCurrentlyInSectorZ, INT16 sGoingToSectorZ );
void HandleMovingEnemiesCloseToEntranceInFirstTunnelMap();
void HandleMovingEnemiesCloseToEntranceInSecondTunnelMap();
void HandleFirstPartOfTunnelFanSound();
void HandlePowerGenFanSoundModification();
BOOLEAN MoveEnemyFromGridNoToRoofGridNo( INT16 sSourceGridNo, INT16 sDestGridNo );
void		HandleMovingEnemiesOntoRoofs();

//ppp



extern void InitializeTacticalStatusAtBattleStart();

extern HVSURFACE ghFrameBuffer;
/*
Ja25 No Strategic ai
extern BOOLEAN gfOverrideSector;
*/

extern STR16 pBullseyeStrings[];

//Ja25:	extern void HandleRPCDescription( );


#ifdef CRIPPLED_VERSION
void CrippledVersionFailureToLoadMapCallBack( UINT8 bExitValue );
void CrippledVersionFailureToLoadMapCheck();
#endif


//temp timer stuff -- to measure the time it takes to load a map.
#ifdef JA2TESTVERSION
/*
Ja25 No Strategic ai
	extern INT16	 gsAINumAdmins;
	extern INT16	 gsAINumTroops;
	extern INT16	 gsAINumElites;
	extern INT16	 gsAINumCreatures;
*/
	//The wrapper time for EnterSector
	BOOLEAN fStartNewFile = TRUE;
	UINT32 uiEnterSectorStartTime;
	UINT32 uiEnterSectorEndTime;
	//The grand total time for loading a map
	UINT32 uiLoadWorldStartTime;
	UINT32 uiLoadWorldEndTime;
	//The time spent in FileRead
	UINT32 uiTotalFileReadTime;
	UINT32 uiTotalFileReadCalls;
	//LoadWorld and parts
	UINT32 uiLoadWorldTime;
	UINT32 uiTrashWorldTime;
	UINT32 uiLoadMapTilesetTime;
	UINT32 uiLoadMapLightsTime;
	UINT32 uiBuildShadeTableTime;
	UINT32 uiNumTablesSaved;
	UINT32 uiNumTablesLoaded;
	UINT32 uiNumImagesReloaded;
	#include "render dirty.h"
	#include "tiledat.h"
#endif

UINT32 UndergroundTacticalTraversalTime( INT8 bExitDirection )
{ //We are attempting to traverse in an underground environment.  We need to use a complete different
	//method.  When underground, all sectors are instantly adjacent.
	switch( bExitDirection )
	{
		case NORTH_STRATEGIC_MOVE:
			if( gMapInformation.sNorthGridNo != -1 )
				return 0;
			break;
		case EAST_STRATEGIC_MOVE:
			if( gMapInformation.sEastGridNo != -1 )
				return 0;
			break;
		case SOUTH_STRATEGIC_MOVE:
			if( gMapInformation.sSouthGridNo != -1 )
				return 0;
			break;
		case WEST_STRATEGIC_MOVE:
			if( gMapInformation.sWestGridNo != -1 )
				return 0;
			break;
	}
	return 0xffffffff;
}

#ifdef JA2DEMOADS
	extern void DoDemoIntroduction();
	extern BOOLEAN gfDemoIntro;
#endif

void BeginLoadScreen( )
{
	SGPRect SrcRect, DstRect;
	UINT32 uiStartTime, uiCurrTime;
	INT32 iPercentage, iFactor;
	UINT32 uiTimeRange;
	INT32 iLastShadePercentage;
	UINT8 ubLoadScreenID;

#ifdef JA2DEMOADS
	if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
	{
		DoDemoIntroduction();
	}
	else
	{
		gfDemoIntro = TRUE;
	}
#endif

	SetCurrentCursorFromDatabase( VIDEO_NO_CURSOR );

/*
Ja25: No meanwhiles
	if( guiCurrentScreen == MAP_SCREEN && !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME) && !AreInMeanwhile() )
*/
	if( guiCurrentScreen == MAP_SCREEN && !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME) )
	{
		DstRect.iLeft = 0;
		DstRect.iTop = 0;
		DstRect.iRight = SCREEN_BUFFER_WIDTH;
		DstRect.iBottom = SCREEN_BUFFER_HEIGHT;
		uiTimeRange = 2000;
		iPercentage = 0;
		iLastShadePercentage = 0;
		uiStartTime = GetJA2Clock();
		BlitBufferToBuffer( FRAME_BUFFER, guiSAVEBUFFER, 0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT );
		PlayJA2SampleFromFile( "SOUNDS\\Final Psionic Blast 01 (16-44).wav", RATE_11025, HIGHVOLUME, 1, MIDDLEPAN );
		while( iPercentage < 100  )
		{
			uiCurrTime = GetJA2Clock();
			iPercentage = (uiCurrTime-uiStartTime) * 100 / uiTimeRange;
			iPercentage = min( iPercentage, 100 );

			//Factor the percentage so that it is modified by a gravity falling acceleration effect.
			iFactor = (iPercentage - 50) * 2;
			if( iPercentage < 50 )
				iPercentage = (UINT32)(iPercentage + iPercentage * iFactor * 0.01 + 0.5);
			else
				iPercentage = (UINT32)(iPercentage + (100-iPercentage) * iFactor * 0.01 + 0.05);

			if( iPercentage > 50 )
			{
				//iFactor = (iPercentage - 50) * 2;
				//if( iFactor > iLastShadePercentage )
			//	{
					//Calculate the difference from last shade % to the new one.  Ex:  Going from
					//50% shade value to 60% shade value requires applying 20% to the 50% to achieve 60%.
					//if( iLastShadePercentage )
					//	iReqShadePercentage = 100 - (iFactor * 100 / iLastShadePercentage);
					//else
					//	iReqShadePercentage = iFactor;
					//Record the new final shade percentage.
					//iLastShadePercentage = iFactor;
					ShadowVideoSurfaceRectUsingLowPercentTable( guiSAVEBUFFER, 0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT );
			//	}
			}

			SrcRect.iLeft = 536 * iPercentage / 100;
			SrcRect.iRight = SCREEN_BUFFER_WIDTH - iPercentage / 20;
			SrcRect.iTop = 367 * iPercentage / 100;
			SrcRect.iBottom = SCREEN_BUFFER_HEIGHT - 39 * iPercentage / 100;
			BltStretchVideoSurface( FRAME_BUFFER, guiSAVEBUFFER, 0, 0, 0, &SrcRect, &DstRect );
			InvalidateScreen();
			RefreshScreen( NULL );
		}
	}
	ColorFillVideoSurfaceArea( FRAME_BUFFER, 0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT, Get16BPPColor( FROMRGB( 0, 0, 0 ) ) );
	InvalidateScreen( );
	RefreshScreen( NULL );

	//if we are going to the intro screen, return before putting up a loadscreen
	if( gbExitingMapScreenToWhere == MAP_EXIT_TO_INTRO_SCREEN )
	{
		SetPendingNewScreen( INTRO_SCREEN );
		return;
	}

	//If we are loading a saved game, use the Loading screen we saved into the SavedGameHeader file
	// ( which gets reloaded into gubLastLoadingScreenID )
	if( !gfGotoSectorTransition )
	{
		if( gTacticalStatus.uiFlags & LOADING_SAVED_GAME )
		{
			DisplayLoadScreenWithID( gubLastLoadingScreenID );
		}
		else
		{
			ubLoadScreenID = GetLoadScreenID( gWorldSectorX, gWorldSectorY, gbWorldSectorZ );
			DisplayLoadScreenWithID( ubLoadScreenID );
		}
	}

#ifdef JA2TESTVERSION
	uiEnterSectorStartTime = 0;
	uiEnterSectorEndTime = 0;
	//The grand total time for loading a map
	uiLoadWorldStartTime = 0;
	uiLoadWorldEndTime = 0;
	//The time spent in FileRead
	uiTotalFileReadTime = 0;
	uiTotalFileReadCalls = 0;
	//Sections of LoadWorld
	uiLoadWorldTime = 0;
	uiTrashWorldTime = 0;
	uiLoadMapTilesetTime = 0;
	uiLoadMapLightsTime = 0;
	uiBuildShadeTableTime = 0;
	uiEnterSectorStartTime = GetJA2Clock();
#endif

	//used when determing wether we are going up or down stairs
	gJa25SaveStruct.ubLoadScreenStairTraversal = LS__NOT_GOING_UP_STAIRS;
}

void EndLoadScreen( )
{
#ifdef JA2TESTVERSION
	//Report the time it took to load the map.  This is temporary until we are satisfied with the time
	//it takes to load the map.
	UINT16 str[60];
	FILE *fp;
	UINT32 uiSeconds;
	UINT32 uiHundreths;
	UINT32 uiUnaccounted;
	UINT32 uiPercentage;
	uiEnterSectorEndTime = GetJA2Clock();
	uiSeconds = (uiEnterSectorEndTime - uiEnterSectorStartTime) / 1000;
	uiHundreths = ((uiEnterSectorEndTime - uiEnterSectorStartTime) / 10) % 100;
	SetFont( FONT10ARIAL );
	SetFontForeground( FONT_YELLOW );
	SetFontBackground( FONT_NEARBLACK );
	if( !gbWorldSectorZ )
	{
		swprintf( str, L"%c%d ENTER SECTOR TIME:  %d.%02d seconds.", 
							'A' + gWorldSectorY - 1, gWorldSectorX, uiSeconds, uiHundreths );
	}
	else
	{
		swprintf( str, L"%c%d_b%d ENTER SECTOR TIME:  %d.%02d seconds.", 
							'A' + gWorldSectorY - 1, gWorldSectorX, gbWorldSectorZ, uiSeconds, uiHundreths );
	}
	ScreenMsg( FONT_YELLOW, MSG_TESTVERSION, str );
	if( fStartNewFile )
	{ //start new file
		fp = fopen( "TimeResults.txt", "w" );
		ScreenMsg( FONT_YELLOW, MSG_TESTVERSION, L"See JA2\\Data\\TimeResults.txt for more detailed timings." );
		fStartNewFile = FALSE;
	}
	else
	{ //append to end of file
		fp = fopen( "TimeResults.txt", "a" );

		if ( fp )
		{
			fprintf( fp, "\n\n--------------------------------------------------------------------\n\n" );
		}
	}
	if( fp )
	{
		//Record all of the timings.
		fprintf( fp, "%S\n", str );
		fprintf( fp, "EnterSector() supersets LoadWorld().  This includes other external sections.\n");
		//FileRead()
		fprintf( fp, "\n\nVARIOUS FUNCTION TIMINGS (exclusive of actual function timings in second heading)\n" );
		uiSeconds = uiTotalFileReadTime / 1000;
		uiHundreths = (uiTotalFileReadTime / 10) % 100; 
		fprintf( fp, "FileRead:  %d.%02d (called %d times)\n", uiSeconds, uiHundreths, uiTotalFileReadCalls );
		
		fprintf( fp, "\n\nSECTIONS OF LOADWORLD (all parts should add up to 100%)\n" );
		//TrashWorld()
		uiSeconds = uiTrashWorldTime / 1000;
		uiHundreths = (uiTrashWorldTime / 10) % 100; 
		fprintf( fp, "TrashWorld: %d.%02d\n", uiSeconds, uiHundreths );
		//LoadMapTilesets()
		uiSeconds = uiLoadMapTilesetTime / 1000;
		uiHundreths = (uiLoadMapTilesetTime / 10) % 100; 
		fprintf( fp, "LoadMapTileset: %d.%02d\n", uiSeconds, uiHundreths );
		//LoadMapLights()
		uiSeconds = uiLoadMapLightsTime / 1000;
		uiHundreths = (uiLoadMapLightsTime / 10) % 100; 
		fprintf( fp, "LoadMapLights: %d.%02d\n", uiSeconds, uiHundreths );
		uiSeconds = uiBuildShadeTableTime / 1000;
		uiHundreths = (uiBuildShadeTableTime / 10) % 100;
		fprintf( fp, "  1)  BuildShadeTables: %d.%02d\n", uiSeconds, uiHundreths );

		uiPercentage = uiNumImagesReloaded * 100 / NUMBEROFTILETYPES;
		fprintf( fp, "  2)  %d%% of the tileset images were actually reloaded.\n", uiPercentage );
		if ( ( uiNumTablesSaved+uiNumTablesLoaded ) != 0 )
		{
			uiPercentage = uiNumTablesSaved * 100 / (uiNumTablesSaved+uiNumTablesLoaded);
		}
		else
		{
			uiPercentage = 0;
		}
		fprintf( fp, "  3)  Of that, %d%% of the shade tables were generated (not loaded).\n", uiPercentage );
		if( gfForceBuildShadeTables )
			fprintf( fp, "  NOTE:  Force building of shadetables enabled on this local computer.\n" );


		//Unaccounted
		uiUnaccounted = uiLoadWorldTime - uiTrashWorldTime - uiLoadMapTilesetTime - uiLoadMapLightsTime;
		uiSeconds = uiUnaccounted / 1000;
		uiHundreths = (uiUnaccounted / 10) % 100; 
		fprintf( fp, "Unaccounted: %d.%02d\n", uiSeconds, uiHundreths ); 
		//LoadWorld()
		uiSeconds = uiLoadWorldTime / 1000;
		uiHundreths = (uiLoadWorldTime / 10) % 100; 
		fprintf( fp, "\nTotal: %d.%02d\n", uiSeconds, uiHundreths );
	
		fclose( fp );
	}
#endif
}


BOOLEAN InitStrategicEngine( )
{
	// this runs every time we start the application, so don't put anything in here that's only supposed to run when a new
	// *game* is started!  Those belong in InitStrategicLayer() instead.

	InitializeMapStructure();
	
	// set up town stuff
	BuildListOfTownSectors( );

	// town distances are pre-calculated and read in from a data file
	// since it takes quite a while to plot strategic paths between all pairs of town sectors...

//#define RECALC_TOWN_DISTANCES
#ifdef RECALC_TOWN_DISTANCES
	CalcDistancesBetweenTowns ( );
	WriteOutDistancesBetweenTowns( );
	DumpDistancesBetweenTowns( );
#endif
	
	ReadInDistancesBetweenTowns( );

	return( TRUE );
}


UINT8 GetTownIdForSector( INT16 sMapX, INT16 sMapY )
{
	// return the name value of the town in this sector

	return( StrategicMap[CALCULATE_STRATEGIC_INDEX( sMapX, sMapY )].bNameId );
}


// return number of sectors this town takes up
UINT8 GetTownSectorSize( INT8 bTownId )
{
	UINT8 ubSectorSize = 0;
	INT32 iCounterA =0, iCounterB = 0;

	for( iCounterA = 0; iCounterA < ( INT32 )( MAP_WORLD_X - 1 ); iCounterA++ )
	{
		for( iCounterB = 0; iCounterB < ( INT32 )( MAP_WORLD_Y - 1 ); iCounterB++ )
		{
			if(  StrategicMap[CALCULATE_STRATEGIC_INDEX( iCounterA, iCounterB )].bNameId == bTownId )
			{
				ubSectorSize++;
			}
		}
	}

	return( ubSectorSize );
}

UINT8 GetMilitiaCountAtLevelAnywhereInTown( UINT8 ubTownValue, UINT8 ubLevelValue )
{
	INT32 iCounter = 0;
	UINT8 ubCount =0;

	while( pTownNamesList[ iCounter ] != 0 )
	{
		if( StrategicMap[ pTownLocationsList[ iCounter ] ].bNameId == ubTownValue )
		{
			// match.  Add the number of civs at this level
			ubCount += SectorInfo[ STRATEGIC_INDEX_TO_SECTOR_INFO( pTownLocationsList[ iCounter ] ) ].ubNumberOfCivsAtLevel[ ubLevelValue ];
		}

		iCounter++;
	}
	return( ubCount );
}


// return number of sectors under player control for this town
UINT8 GetTownSectorsUnderControl( INT8 bTownId )
{
	INT8 ubSectorsControlled = 0;
	INT32 iCounterA =0, iCounterB = 0;
	UINT16 usSector = 0;

	for( iCounterA = 0; iCounterA < ( INT32 )( MAP_WORLD_X - 1 ); iCounterA++ )
	{
		for( iCounterB = 0; iCounterB < ( INT32 )( MAP_WORLD_Y - 1 ); iCounterB++ )
		{
			usSector = (UINT16)CALCULATE_STRATEGIC_INDEX( iCounterA, iCounterB );

			if( ( StrategicMap[ usSector ].bNameId == bTownId ) &&
					( StrategicMap[ usSector ].fEnemyControlled == FALSE ) &&
					( NumEnemiesInSector( ( INT16 )iCounterA, ( INT16 )iCounterB ) == 0 ) )
			{
				ubSectorsControlled++;
			}
		}
	}

	return( ubSectorsControlled );
}


void InitializeMapStructure()
{
	memset(StrategicMap, 0, sizeof(StrategicMap));

	InitializeStrategicMapSectorTownNames( );
}


void InitializeSAMSites( void )
{
	// move the landing zone over to Omerta
	gsMercArriveSectorX = JA2_5_START_SECTOR_X;
	gsMercArriveSectorY = JA2_5_START_SECTOR_Y;

	// all SAM sites start game in perfect working condition
	StrategicMap[(SAM_1_X)+(MAP_WORLD_X*(SAM_1_Y))].bSAMCondition = 100;
	StrategicMap[(SAM_2_X)+(MAP_WORLD_X*(SAM_2_Y))].bSAMCondition = 100;
	StrategicMap[(SAM_3_X)+(MAP_WORLD_X*(SAM_3_Y))].bSAMCondition = 100;
	StrategicMap[(SAM_4_X)+(MAP_WORLD_X*(SAM_4_Y))].bSAMCondition = 100;

	UpdateAirspaceControl( );
}


// get short sector name without town name
void GetShortSectorString( INT16 sMapX,INT16 sMapY, STR16 sString )
{
	// OK, build string id like J11
	swprintf( sString, L"%S%S",pVertStrings[ sMapY ], pHortStrings[ sMapX ] );

	return;
}


void GetMapFileName(INT16 sMapX,INT16 sMapY, INT8 bSectorZ, STR8 bString, BOOLEAN fUsePlaceholder, BOOLEAN fAddAlternateMapLetter )
{
	//if the player is using the custom maps
#ifdef	ENABLE_CUSTOM_MAP_INTERFACE
	if( gJa25SaveStruct.fInCustomMap )
	{
		// This is the string to return, but...
		sprintf( bString, "%s", gSelectedCustomScenario.pMap[ gSelectedCustomScenario.iCurrentMap ].pFileNameArray );
	}

	else
#endif
	{
		CHAR8	 bTestString[ 150 ];
		CHAR8	 bExtensionString[ 15 ];

		if ( bSectorZ != 0 )
		{
			sprintf( bExtensionString, "_b%d", bSectorZ );
		}
		else
		{
			strcpy( bExtensionString, "" );
		}

		// the gfUseAlternateMap flag is set in the loading saved games.  When starting a new game the underground sector
		//info has not been initialized, so we need the flag to load an alternate sector.
		if( gfUseAlternateMap | GetSectorFlagStatus( sMapX, sMapY, bSectorZ, SF_USE_ALTERNATE_MAP ) )
		{
			gfUseAlternateMap = FALSE;

			//if we ARE to use the a map, or if we are saving AND the save game version is before 80, add the a
			if( fAddAlternateMapLetter )
			{
				strcat( bExtensionString, "_a" );
			}
		}

	/*
	Ja25: No meanwhiles
		// If we are in a meanwhile...
		if ( AreInMeanwhile( ) && sMapX == 3 && sMapY == 16 && !bSectorZ )//GetMeanwhileID() != INTERROGATION )
		{
			if( fAddAlternateMapLetter )
			{
				strcat( bExtensionString, "_m" );
			}
		}
	*/

		// This is the string to return, but...
		sprintf( bString, "%S%s%s%s.DAT", JA25_EXP_MAP_NAME_PREFIX, pVertStrings[sMapY], pHortStrings[sMapX], bExtensionString );

		// We will test against this string

		sprintf( bTestString, "%s\\%s", GetMapsDirectory( ), bString );

		//if( fUsePlaceholder && !FileExists( bTestString ) )
		//{
			// Debug str
		//	DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Map does not exist for %s, using default.", bTestString ) );
			// Set to a string we know!
		//	sprintf(bString, "H10.DAT",pVertStrings[sMapY],pHortStrings[sMapX]);
		//	ScreenMsg( FONT_YELLOW, MSG_DEBUG, L"Using PLACEHOLDER map!");
		//}
		return;
	}
}

void GetCurrentWorldSector( INT16 *psMapX, INT16 *psMapY )
{
	*psMapX = gWorldSectorX;
	*psMapY = gWorldSectorY;
}

//not in overhead.h!
extern UINT8 NumEnemyInSector();

/*
Ja25 No sector descriptions
void HandleRPCDescriptionOfSector( INT16 sSectorX, INT16 sSectorY, INT16 sSectorZ )
{
	UINT32	cnt;
	UINT8		ubSectorDescription[33][3] =
	{
		 // row (letter), column, quote #
		 { 2, 13,  0 },	// b13	Drassen
		 { 3, 13,  1 },	// c13	Drassen
		 { 4, 13,  2 },	// d13	Drassen
		 { 8, 13,  3 },	// h13	Alma
		 { 8, 14,  4 },	// h14	Alma
		 { 9, 13,  5 },	// i13	Alma * (extra quote 6 if Sci-fi ) *
		 { 9, 14,  7 },	// i14	Alma
		 { 6,  8,  8 },	// f8	Cambria
		 { 6,  9,  9 }, 	// f9	Cambria   
		 { 7,  8, 10 },	// g8	Cambria

		 { 7,  9, 11 },	// g9	Cambria
		 { 3,  6, 12 },	// c6	San Mona
		 { 3,  5, 13 },	// c5	San Mona
		 { 4,  5, 14 },	// d5	San Mona
		 { 2,  2, 15 },	// b2	Chitzena
		 { 1,  2, 16 },	// a2	Chitzena
		 { 7,  1, 17 },	// g1	Grumm
		 { 8,  1, 18 },	// h1	Grumm
		 { 7,  2, 19 },	// g2 	Grumm
		 { 8,  2, 20 },	// h2	Grumm

		 { 9,  6, 21 },	// i6	Estoni
		 {11,	 4, 22 },	// k4	Orta
		 {12,	 11, 23 },	// l11	Balime
		 {12,	 12, 24 },	// l12	Balime
		 {15,  3, 25 },	// o3	Meduna
		 {16,  3, 26 },	// p3	Meduna
		 {14,  4, 27 },	// n4	Meduna
		 {14,  3, 28 },	// n3	Meduna
		 {15,  4, 30 },	// o4	Meduna
		 {10,  9, 31 },	// j9	Tixa

		 {4,	15, 32 },	// d15	NE SAM
		 {4,  2, 33 },	// d2	NW SAM
		 {9,  8, 34 }	// i8	CENTRAL SAM
	};

  // Default to false
	gTacticalStatus.fCountingDownForGuideDescription = FALSE;


	// OK, if the first time in...
	if ( GetSectorFlagStatus( sSectorX, sSectorY, ( UINT8 )sSectorZ, SF_HAVE_USED_GUIDE_QUOTE ) != TRUE )
	{
		if ( sSectorZ != 0 )
		{
			return;
		}

		// OK, check if we are in a good sector....
		for ( cnt = 0; cnt < 33; cnt++ )
		{
			if ( sSectorX == ubSectorDescription[ cnt ][ 1 ] && sSectorY == ubSectorDescription[ cnt ][ 0 ] )
			{
				// If we're not scifi, skip some
				if ( !gGameOptions.fSciFi && cnt == 3 )
				{
					continue;
				}

				SetSectorFlag( sSectorX, sSectorY, ( UINT8 )sSectorZ, SF_HAVE_USED_GUIDE_QUOTE );

				gTacticalStatus.fCountingDownForGuideDescription = TRUE;
				gTacticalStatus.bGuideDescriptionCountDown			 = (INT8)( 4 + Random( 5 ) ); // 4 to 8 tactical turns...
				gTacticalStatus.ubGuideDescriptionToUse					 = ubSectorDescription[ cnt ][ 2 ];
				gTacticalStatus.bGuideDescriptionSectorX				 =  (INT8)sSectorX;
				gTacticalStatus.bGuideDescriptionSectorY				 =  (INT8)sSectorY;
			}
		}
	}

  // Handle guide description ( will be needed if a SAM one )
	HandleRPCDescription( );

}
*/

BOOLEAN	SetCurrentWorldSector( INT16 sMapX, INT16 sMapY, INT8 bMapZ )
{
//	UNDERGROUND_SECTORINFO	*pUnderWorld=NULL;
	BOOLEAN									fChangeMusic = TRUE;
	BOOLEAN									fWorldWasLoaded=FALSE;
	INT16										sOldMapX, sOldMapY, sOldMapZ;

	sOldMapX=sOldMapY=sOldMapZ = 0;
	#ifdef CRIPPLED_VERSION
		if( sMapY >= 5 && sMapY != 16 )
		{
			CrippledVersionFailureToLoadMapCheck();
			return FALSE;	
		}
	#endif
	
	// ATE: Zero out accounting functions
	memset( gbMercIsNewInThisSector, 0, sizeof( gbMercIsNewInThisSector ) );

	SyncStrategicTurnTimes();
	
/*
Ja25 No Strategic ai
	#ifdef JA2BETAVERSION
	if( gfOverrideSector )
	{
		//skip the cancel, and force load the sector.  This is used by the AIViewer to "reset" a level with
		//different numbers of various types of enemies.
	}
	else
	#endif
*/

	// is the sector already loaded?
	if( ( gWorldSectorX == sMapX ) && ( sMapY == gWorldSectorY) && ( bMapZ == gbWorldSectorZ) )
	{
		//Inserts the enemies into the newly loaded map based on the strategic information.
		//Note, the flag will return TRUE only if enemies were added.  The game may wish to
		//do something else in a case where no enemies are present.

		SetPendingNewScreen(GAME_SCREEN);
		if( !NumEnemyInSector( ) )
		{
			PrepareEnemyForSectorBattle();
		}

/*
Ja25 no creatures
		if( gubNumCreaturesAttackingTown && !gbWorldSectorZ && 
				gubSectorIDOfCreatureAttack == SECTOR( gWorldSectorX, gWorldSectorY ) )
		{
			PrepareCreaturesForBattle();
		}
*/
		if( gfGotoSectorTransition )
		{
			BeginLoadScreen( );
			gfGotoSectorTransition = FALSE;
		}

		// Check for helicopter being on the ground in this sector...
		HandleHelicopterOnGroundGraphic( );

/*
Ja25 no militia
		ResetMilitia();
*/
		AllTeamsLookForAll( TRUE );
		return( TRUE );
	}

	if( gWorldSectorX && gWorldSectorY && gbWorldSectorZ != -1 )
	{
		//rememeber the old sector
		sOldMapX = gWorldSectorX;
		sOldMapY = gWorldSectorY;
		sOldMapZ = gbWorldSectorZ;

		HandleDefiniteUnloadingOfWorld( ABOUT_TO_LOAD_NEW_MAP );
		fWorldWasLoaded = TRUE;
	}

	// make this the currently loaded sector
	gWorldSectorX  = sMapX;
	gWorldSectorY  = sMapY;
	gbWorldSectorZ = bMapZ;

	if( fWorldWasLoaded )
	{
		HandleSectorSpecificUnLoadingOfMap( sOldMapX, sOldMapY, (UINT8)sOldMapZ );
	}

	// update currently selected map sector to match
	ChangeSelectedMapSector( sMapX, sMapY, bMapZ );


	//Check to see if the sector we are loading is the cave sector under Tixa.  If so
	//then we will set up the meanwhile scene to start the creature quest.
	if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
	{
    StopAnyCurrentlyTalkingSpeech( );

/*
Ja25 no creatures
		if( gWorldSectorX == 9 && gWorldSectorY == 10 && gbWorldSectorZ == 2 )
		{
			InitCreatureQuest(); //Ignored if already active.
		}
*/
	}

	//Stop playing any music -- will fade out.
	// SetMusicMode( MUSIC_NONE );

	// ATE: Determine if we should set the default music...

	// Are we already in 'tense' music...

	// ATE: Change music only if not loading....
	/*-
	if ( gubMusicMode == MUSIC_TACTICAL_ENEMYPRESENT  )
	{
		fChangeMusic = FALSE;
	}

	// Did we 'tactically traverse' over....
	if ( gfTacticalTraversal )
	{
		fChangeMusic = FALSE;
	}

	// If we have no music playing at all....
	if ( gubMusicMode == MUSIC_NONE  )
	{
		fChangeMusic = TRUE;
	}
	-*/
	
	if( (gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
	{
		fChangeMusic = TRUE;
	}
	else
	{
		fChangeMusic = FALSE;
	}


	if ( fChangeMusic )
	{
		SetMusicMode( MUSIC_MAIN_MENU );		
	}

	// ATE: Do this stuff earlier!
	if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
	{
		// Update the last time we were in tactical...
		gTacticalStatus.uiTimeSinceLastInTactical = GetWorldTotalMin( );

		// init some AI stuff
		InitializeTacticalStatusAtBattleStart();

		// CJC: delay this until after entering the sector!
		//InitAI();

	  // Check for helicopter being on the ground in this sector...
	  HandleHelicopterOnGroundSkyriderProfile( );

		//Check to see if we should add Manuel to this sector, if so add him
		ShouldNpcBeAddedToSector( gWorldSectorX, gWorldSectorY, bMapZ );
	}

	//Load and enter the new sector
	if( EnterSector( gWorldSectorX, gWorldSectorY, bMapZ ) )
	{
		// CJC: moved this here Feb 17
		if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
		{
			InitAI();
		}

		//If there are any people with schedules, now is the time to process them.
		//CJC: doesn't work here if we're going through the tactical placement GUI; moving
		// this call to PrepareLoadedSector()
		//PostSchedules();

		// ATE: OK, add code here to update the states of doors if they should 
		// be closed......
		if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
		{
			ExamineDoorsOnEnteringSector( );
		}

		// Update all the doors in the sector according to the temp file previously
		// loaded, and any changes made by the schedules
		UpdateDoorGraphicsFromStatus( TRUE, FALSE );

		//Set the fact we have visited the  sector
		SetSectorFlag( gWorldSectorX, gWorldSectorY, gbWorldSectorZ, SF_ALREADY_LOADED );

		// Check for helicopter being on the ground in this sector...
		HandleHelicopterOnGroundGraphic( );
	}
	else
		return( FALSE );

	if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
	{
		if( (gubMusicMode != MUSIC_TACTICAL_ENEMYPRESENT && gubMusicMode != MUSIC_TACTICAL_BATTLE) || 
				(!NumHostilesInSector( sMapX, sMapY, bMapZ ) && gubMusicMode == MUSIC_TACTICAL_ENEMYPRESENT) )
		{
			// ATE; Fade FA.T....
			SetMusicFadeSpeed( 5 );

			SetMusicMode( MUSIC_TACTICAL_NOTHING );
		}

		// ATE: Check what sector we are in, to show description if we have an RPC.....
//Ja25: no sector descriptions
//		HandleRPCDescriptionOfSector( sMapX, sMapY, bMapZ );


		// Say a quote from a merc who has new lines for the sector ( if any )
		HandlePlayerTeamQuotesWhenEnteringSector( sMapX, sMapY, bMapZ );    

		// ATE: Set Flag for being visited...
		SetSectorFlag( sMapX, sMapY, bMapZ, SF_HAS_ENTERED_TACTICAL );

		// If any emails should be sent from this sector
		HandleEmailBeingSentWhenEnteringSector( sMapX, sMapY, bMapZ, FALSE );


		// ATE; Reset some flags for creature sayings....
		gTacticalStatus.fSaidCreatureFlavourQuote = FALSE;
		gTacticalStatus.fHaveSeenCreature					= FALSE;
		gTacticalStatus.fBeenInCombatOnce					= FALSE;
		gTacticalStatus.fSaidCreatureSmellQuote		= FALSE;
		ResetMultiSelection( );

		// ATE: Decide if we can have crows here....
		gTacticalStatus.fGoodToAllowCrows					= FALSE;
    gTacticalStatus.fHasEnteredCombatModeSinceEntering = FALSE;
    gTacticalStatus.fDontAddNewCrows          = FALSE;

		//Call this function, if Jerry doesnt need to be added, it will return
		UpdateJerryMiloInInitialSector();


    // Adjust delay for tense quote
    gTacticalStatus.sCreatureTenseQuoteDelay = (INT16)( 10 + Random( 20 ) );

    {
//      INT16 sWarpWorldX;
//      INT16 sWarpWorldY;
//      INT8  bWarpWorldZ;
//      INT16 sWarpGridNo;

/*
Ja25 No creatures, therefore not in creature layer to get teleported out of
      if ( GetWarpOutOfMineCodes( &sWarpWorldX, &sWarpWorldY, &bWarpWorldZ, &sWarpGridNo ) && gbWorldSectorZ >= 2 )
      {
        gTacticalStatus.uiFlags |= IN_CREATURE_LAIR;
      }
      else
*/
      {
        gTacticalStatus.uiFlags &= ( ~IN_CREATURE_LAIR );
      }
    }

		// Every third turn
		//if ( Random( 3 ) == 0  )
		{
			gTacticalStatus.fGoodToAllowCrows				= TRUE;
			gTacticalStatus.ubNumCrowsPossible			= (UINT8)( 5 + Random( 5 ) );
		}

	}

	return( TRUE );
}



BOOLEAN MapExists( UINT8 *szFilename )
{
	UINT8 str[50];
	HWFILE fp;
#ifdef	ENABLE_CUSTOM_MAP_INTERFACE
	if( gJa25SaveStruct.fInCustomMap )
	{
		sprintf( str, "CUSTOMMAPS\\%s\\%s", gSelectedCustomScenario.zScenarioDirName, szFilename );
	}
	else
#endif
	{
		sprintf( str, "%s\\%s", GetMapsDirectory( ), szFilename );
	}
	fp = FileOpen( str, FILE_ACCESS_READ, FALSE );
	if( !fp )
		return FALSE;
	FileClose( fp );
	return TRUE;
}

void RemoveMercsInSector( )
{
	INT32					cnt;
	SOLDIERTYPE		*pSoldier;

	// IF IT'S THE SELECTED GUY, MAKE ANOTHER SELECTED!
	cnt = gTacticalStatus.Team[ gbPlayerNum ].bFirstID;
  for ( pSoldier = MercPtrs[ cnt ]; cnt <= gTacticalStatus.Team[ gbPlayerNum ].bLastID; cnt++, pSoldier++)
	{	
		if ( pSoldier->bActive  )
		{
			RemoveSoldierFromGridNo( pSoldier );
		}
	}

}

void PrepareLoadedSector()
{
//	INT32 iCounter = 0;
	BOOLEAN fEnemyPresenceInThisSector = FALSE;
//	BOOLEAN fUsingOverride = FALSE;
	BOOLEAN fAddCivs = TRUE;
	INT8 bMineIndex = -1;

//Ja25 No meanwhiles	if( AreInMeanwhile( ) == FALSE )
	{
		if( gbWorldSectorZ == 0 )
		{
//			MakePlayerPerceptionOfSectorControlCorrect( gWorldSectorX, gWorldSectorY, gbWorldSectorZ );
		}
		else
		{
			// we always think we control underground sectors once we've visited them
			SectorInfo[ SECTOR( gWorldSectorX, gWorldSectorY ) ].fPlayer[ gbWorldSectorZ ] = TRUE;
		}
	}

	if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
	{
		UpdateMercsInSector( gWorldSectorX, gWorldSectorY, gbWorldSectorZ );
	}

	// Reset ambients!
	HandleNewSectorAmbience( gTilesets[ giCurrentTilesetID ].ubAmbientID );

	//if we are loading a 'pristine' map ( ie, not loading a saved game )
	if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ))
	{
//Ja25 No meanwhiles
//		if ( !AreReloadingFromMeanwhile( ) )
		{
			SetPendingNewScreen(GAME_SCREEN);

      // Make interface the team panel always...
			SetCurrentInterfacePanel( (UINT8)TEAM_PANEL );
		}


		//Check to see if civilians should be added.  Always add civs to maps unless they are
		//in a mine that is shutdown.  
		if( gbWorldSectorZ )
		{
			bMineIndex = GetIdOfMineForSector( gWorldSectorX, gWorldSectorY, gbWorldSectorZ );
			if( bMineIndex != -1 )
			{
				if( !AreThereMinersInsideThisMine( (UINT8)bMineIndex ) )
				{
					fAddCivs = FALSE;
				}
			}
		}
		if( fAddCivs )
		{
			AddSoldierInitListTeamToWorld( CIV_TEAM, 255 );
		}

		AddSoldierInitListTeamToWorld( MILITIA_TEAM, 255 );
		AddSoldierInitListBloodcats();
		//Creatures are only added if there are actually some of them.  It has to go through some
		//additional checking.

/*
Ja25 No Strategic ai
		#ifdef JA2TESTVERSION 
		//Override the sector with the populations specified in the AIViewer
		if( gfOverrideSector )
		{
			if( gbWorldSectorZ > 0 )
			{
				UNDERGROUND_SECTORINFO *pSector;
				pSector = FindUnderGroundSector( gWorldSectorX, gWorldSectorY, gbWorldSectorZ );
				pSector->ubNumAdmins = (UINT8)( gsAINumAdmins > 0 ? gsAINumAdmins : 0 );
				pSector->ubNumTroops = (UINT8)( gsAINumTroops > 0 ? gsAINumTroops : 0 );
				pSector->ubNumElites = (UINT8)( gsAINumElites > 0 ? gsAINumElites : 0 );
				pSector->ubNumCreatures = (UINT8)( gsAINumCreatures > 0 ? gsAINumCreatures : 0 );
			}
			else if( !gbWorldSectorZ )
			{
				SECTORINFO *pSector;
				pSector = &SectorInfo[ SECTOR( gWorldSectorX, gWorldSectorY ) ];
				pSector->ubNumAdmins = (UINT8)( gsAINumAdmins > 0 ? gsAINumAdmins : 0 );
				pSector->ubNumTroops = (UINT8)( gsAINumTroops > 0 ? gsAINumTroops : 0 );
				pSector->ubNumElites = (UINT8)( gsAINumElites > 0 ? gsAINumElites : 0 );
				pSector->ubNumCreatures = (UINT8)( gsAINumCreatures > 0 ? gsAINumCreatures : 0 );
			}
		}
		#endif
*/

/*
Ja25 no creatures or militia
		PrepareCreaturesForBattle();

		PrepareMilitiaForTactical();
*/

		// OK, set varibles for entring this new sector...
		gTacticalStatus.fVirginSector = TRUE;

		//Inserts the enemies into the newly loaded map based on the strategic information.
		//Note, the flag will return TRUE only if enemies were added.  The game may wish to
		//do something else in a case where no enemies are present.
		if( !gfRestoringEnemySoldiersFromTempFile )
		{
			//AddSoldierInitListTeamToWorld( CIV_TEAM, 255 );
//			fEnemyPresenceInThisSector = PrepareEnemyForSectorBattle();
		}
		AddProfilesNotUsingProfileInsertionData();
		
//Ja25 No meanwhiles		if( !AreInMeanwhile() || GetMeanwhileID() == INTERROGATION )
		{
			fEnemyPresenceInThisSector = PrepareEnemyForSectorBattle();
		}


		//Regardless whether or not this was set, clear it now.
		gfRestoringEnemySoldiersFromTempFile = FALSE;

		//KM:  FEB 8, 99 -- This call is no longer required!  Done already when group arrives in sector.
		//if( ( gbWorldSectorZ == 0 ) && ( fEnemyPresenceInThisSector == FALSE ) )
		//{
		//	SetThisSectorAsPlayerControlled( gWorldSectorX, gWorldSectorY, 0 );
		//}

		if( gbWorldSectorZ > 0 )
		{
			// we always think we control underground sectors once we've visited them
			SectorInfo[ SECTOR( gWorldSectorX, gWorldSectorY ) ].fPlayer[ gbWorldSectorZ ] = TRUE;
		}

		//@@@Evaluate
		//Add profiles to world using strategic info, not editor placements.
		AddProfilesUsingProfileInsertionData();

		PostSchedules();
	}

	if( gubEnemyEncounterCode == ENEMY_AMBUSH_CODE || gubEnemyEncounterCode == BLOODCAT_AMBUSH_CODE )
	{
		if( gMapInformation.sCenterGridNo != -1 )
		{
			CallAvailableEnemiesTo( gMapInformation.sCenterGridNo );
		}
		else
		{
			#ifdef JA2BETAVERSION
				ScreenMsg( FONT_RED, MSG_ERROR, L"Ambush aborted in sector %c%d -- no center point in map.  LC:1", 
					gWorldSectorY + 'A' - 1, gWorldSectorX );
			#endif
		}
	}

	EndLoadScreen( );

	if( !( gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
	{
		// unpause game
		UnPauseGame( );
	}

	gpBattleGroup = NULL;

	if( gfTacticalTraversal )
	{
		CalculateNonPersistantPBIInfo();
	}

	ScreenMsg( FONT_YELLOW, MSG_DEBUG, L"Current Time is: %d", GetWorldTotalMin() );

	HandleSectorSpecificModificatioToMap( gWorldSectorX, gWorldSectorY, gbWorldSectorZ, FALSE );

	//If there needs to be modifications done to the enemy exp levels...
	HandleJa25EnemyExpLevelModifier( );

	AllTeamsLookForAll( TRUE );
	
}

#define RANDOM_HEAD_MINERS 4
void HandleQuestCodeOnSectorEntry( INT16 sNewSectorX, INT16 sNewSectorY, INT8 bNewSectorZ )
{
//	UINT8		ubRandomMiner[RANDOM_HEAD_MINERS] = { 106, 156, 157, 158 };
//	UINT8		ubMiner, ubMinersPlaced;
	UINT8		ubThisMine;
	UINT8		cnt;
	SOLDIERTYPE * pSoldier;

/*
Ja25:
	No terrorist, no carmen
	if ( CheckFact( FACT_ALL_TERRORISTS_KILLED, 0 ) )
	{
		// end terrorist quest
		EndQuest( QUEST_KILL_TERRORISTS, gMercProfiles[ CARMEN ].sSectorX, gMercProfiles[ CARMEN ].sSectorY );
		// remove Carmen
		gMercProfiles[ CARMEN ].sSectorX = 0;
		gMercProfiles[ CARMEN ].sSectorY = 0;
		gMercProfiles[ CARMEN ].bSectorZ = 0;
	}
*/

	// are we in a mine sector, on the surface?
	if ( IsThereAMineInThisSector( sNewSectorX, sNewSectorY ) && ( bNewSectorZ == 0 ))
	{
		if ( CheckFact( FACT_MINERS_PLACED, 0 ) == FALSE )
		{
			// SET HEAD MINER LOCATIONS

			ubThisMine = GetMineIndexForSector( sNewSectorX, sNewSectorY );

/*
Ja25:  only mine in exp. is abandoned
			if (ubThisMine != MINE_SAN_MONA) // San Mona is abandoned
			{
				ubMinersPlaced = 0;

				if (ubThisMine != MINE_ALMA)
				{
					// Fred Morris is always in the first mine sector we enter, unless that's Alma (then he's randomized, too)
					gMercProfiles[ 106 ].sSectorX = sNewSectorX;
					gMercProfiles[ 106 ].sSectorY = sNewSectorY;
					gMercProfiles[ 106 ].bSectorZ = 0;
					gMercProfiles[ 106 ].bTown = gMineLocation[ ubThisMine ].bAssociatedTown;

					// mark miner as placed
					ubRandomMiner[ 0 ] = 0;
					ubMinersPlaced++;
				}

				// assign the remaining (3) miners randomly
				for ( ubMine = 0; ubMine < MAX_NUMBER_OF_MINES; ubMine++ )
				{
					if ( ubMine == ubThisMine || ubMine == MINE_ALMA || ubMine == MINE_SAN_MONA )
					{
						// Alma always has Matt as a miner, and we have assigned Fred to the current mine
						// and San Mona is abandoned
						continue;
					}
					
					do
					{
						ubMiner = (UINT8) Random( RANDOM_HEAD_MINERS );
					}
					while( ubRandomMiner[ ubMiner ] == 0 );
					
					GetMineSector( ubMine, &(gMercProfiles[ ubRandomMiner[ ubMiner ] ].sSectorX),
																 &(gMercProfiles[ ubRandomMiner[ ubMiner ] ].sSectorY) );
					gMercProfiles[ ubRandomMiner[ ubMiner ] ].bSectorZ = 0;
					gMercProfiles[ ubRandomMiner[ ubMiner ] ].bTown = gMineLocation[ ubMine ].bAssociatedTown;

					// mark miner as placed
					ubRandomMiner[ ubMiner ] = 0;
					ubMinersPlaced++;

					if (ubMinersPlaced == RANDOM_HEAD_MINERS)
					{
						break;
					}
				}

				SetFactTrue( FACT_MINERS_PLACED );
			}
*/
		}
	}

	if ( CheckFact( FACT_ROBOT_RECRUITED_AND_MOVED, 0 ) == FALSE )
	{
		SOLDIERTYPE * pRobot;
		pRobot = FindSoldierByProfileID( ROBOT, TRUE );
		if (pRobot)
		{
			// robot is on our team and we have changed sectors, so we can
			// replace the robot-under-construction in Madlab's sector
			RemoveGraphicFromTempFile( gsRobotGridNo, SEVENTHISTRUCT1, gMercProfiles[MADLAB].sSectorX, gMercProfiles[MADLAB].sSectorY, gMercProfiles[MADLAB].bSectorZ );
			SetFactTrue( FACT_ROBOT_RECRUITED_AND_MOVED );
		}
	}

	// Check to see if any player merc has the Chalice; if so, 
	// note it as stolen
	cnt = gTacticalStatus.Team[ gbPlayerNum ].bFirstID;

	for ( pSoldier = MercPtrs[ cnt ]; cnt <= gTacticalStatus.Team[ gbPlayerNum ].bLastID; cnt++,pSoldier++)
	{
		if ( pSoldier->bActive )
		{
			if ( FindObj( pSoldier, CHALICE ) != ITEM_NOT_FOUND )
			{
				SetFactTrue( FACT_CHALICE_STOLEN );
			}
		}
	}

#ifdef JA2DEMO
	// special stuff to make NPCs talk as if the next day, after going down
	// into mines
	if (bNewSectorZ > 0)
	{
		if ( gMercProfiles[ GABBY ].ubLastDateSpokenTo != 0 )
		{
			gMercProfiles[ GABBY ].ubLastDateSpokenTo = 199;
		}
		if ( gMercProfiles[ JAKE ].ubLastDateSpokenTo != 0 )
		{
			gMercProfiles[ JAKE ].ubLastDateSpokenTo = 199;
		}
	}
#endif
/*
Ja25 no assassins and no kingin
	if ( (gubQuest[ QUEST_KINGPIN_MONEY ] == QUESTINPROGRESS) && CheckFact( FACT_KINGPIN_CAN_SEND_ASSASSINS, 0 ) && (GetTownIdForSector( sNewSectorX, sNewSectorY ) != BLANK_SECTOR) && Random( 10 + GetNumberOfMilitiaInSector( sNewSectorX, sNewSectorY, bNewSectorZ ) ) < 3 )
	{
		DecideOnAssassin();
	}
*/

/*
	if ( sNewSectorX == 5 && sNewSectorY == MAP_ROW_C )
	{
		// reset Madame Layla counters
		gMercProfiles[ MADAME ].bNPCData = 0;
		gMercProfiles[ MADAME ].bNPCData2 = 0;
	}
	*/

	if ( sNewSectorX == 6 && sNewSectorY == MAP_ROW_C && gubQuest[ QUEST_RESCUE_MARIA ] == QUESTDONE )
	{
		// make sure Maria and Angel are gone
		gMercProfiles[ MARIA ].sSectorX = 0;
		gMercProfiles[ ANGEL ].sSectorY = 0;
		gMercProfiles[ MARIA ].sSectorX = 0;
		gMercProfiles[ ANGEL ].sSectorY = 0;
	}

	if ( sNewSectorX == 5 && sNewSectorY == MAP_ROW_D )
	{
		gubBoxerID[ 0 ] = NOBODY;
		gubBoxerID[ 1 ] = NOBODY;
		gubBoxerID[ 2 ] = NOBODY;
	}

	if ( sNewSectorX == 3 && sNewSectorY == MAP_ROW_P )
	{
		// heal up Elliot if he's been hurt
		if ( gMercProfiles[ ELLIOT ].bLife < gMercProfiles[ ELLIOT ].bLifeMax )
		{
			gMercProfiles[ ELLIOT ].bLife = gMercProfiles[ ELLIOT ].bLifeMax;
		}
	}

	ResetOncePerConvoRecordsForAllNPCsInLoadedSector();
}

void HandleQuestCodeOnSectorExit( INT16 sOldSectorX, INT16 sOldSectorY, INT8 bOldSectorZ )
{
	SOLDIERTYPE *pSoldier=NULL;
/*
//Ja25 no kingpin
	if ( sOldSectorX == KINGPIN_MONEY_SECTOR_X && sOldSectorY == KINGPIN_MONEY_SECTOR_Y && bOldSectorZ == KINGPIN_MONEY_SECTOR_Z )
	{
		CheckForKingpinsMoneyMissing( TRUE );
	}
*/

	// ATE: if this is a custom map, return
	if ( bOldSectorZ == 0 )
	{
		if ( SectorInfo[ SECTOR( sOldSectorY, sOldSectorX ) ].fCustomSector )
		{
			return;
		}
	}


	if ( sOldSectorX == 13 && sOldSectorY == MAP_ROW_H && bOldSectorZ == 0 && CheckFact( FACT_CONRAD_SHOULD_GO, 0 ) )
	{
		// remove Conrad from the map
		gMercProfiles[ CONRAD ].sSectorX = 0;
		gMercProfiles[ CONRAD ].sSectorY = 0;
	}

	if( sOldSectorX == 7 && sOldSectorY == MAP_ROW_H && bOldSectorZ == 0 )
	{
		// remove Jerry from the map
		gMercProfiles[ JERRY ].sSectorX = 0;
		gMercProfiles[ JERRY ].sSectorY = 0;
	}

	//if the player is leaving a sector with  Tex in it
	if( sOldSectorX == gMercProfiles[ TEX ].sSectorX && sOldSectorY == gMercProfiles[ TEX ].sSectorY && bOldSectorZ == 0 && gMercProfiles[ TEX ].ubLastDateSpokenTo != 0 )
	{
		pSoldier = FindSoldierByProfileID( TEX, TRUE );

		//if the npc isnt on the players team AND the player has never spoken to them
		if( pSoldier == NULL && gMercProfiles[ TEX ].ubLastDateSpokenTo != 0 )
		{
			// remove Tex from the map
			gMercProfiles[ TEX ].sSectorX = 0;
			gMercProfiles[ TEX ].sSectorY = 0;
		}
	}

	//if the player is leaving a sector with  John kulba in it
	if( sOldSectorX == gMercProfiles[ JOHN_K ].sSectorX && sOldSectorY == gMercProfiles[ JOHN_K ].sSectorY && bOldSectorZ == 0 && gMercProfiles[ JOHN_K].ubLastDateSpokenTo != 0 )
	{
		pSoldier = FindSoldierByProfileID( JOHN_K, TRUE );

		//if the npc isnt on the players team AND the player has never spoken to them
		if( pSoldier == NULL && gMercProfiles[ JOHN_K ].ubLastDateSpokenTo != 0 )
		{
			// remove Tex from the map
			gMercProfiles[ JOHN_K ].sSectorX = 0;
			gMercProfiles[ JOHN_K ].sSectorY = 0;
		}
	}

	//if the player is leaving a sector with  Manuel in it
	if( sOldSectorX == gMercProfiles[ MANUEL ].sSectorX && sOldSectorY == gMercProfiles[ MANUEL ].sSectorY && bOldSectorZ == 0 )
	{
		pSoldier = FindSoldierByProfileID( MANUEL, TRUE );

		//if the npc isnt on the players team AND the player has never spoken to them
		if( pSoldier == NULL && gMercProfiles[ MANUEL ].ubLastDateSpokenTo != 0 )
		{
			// remove Manuel from the map
			gMercProfiles[ MANUEL ].sSectorX = 0;
			gMercProfiles[ MANUEL ].sSectorY = 0;
		}
	}


/*
Ja25 no cambria hospital
	if ( sOldSectorX == HOSPITAL_SECTOR_X && sOldSectorY == HOSPITAL_SECTOR_Y && bOldSectorZ == HOSPITAL_SECTOR_Z )
	{
		CheckForMissingHospitalSupplies();
	}
*/

	// reset the state of the museum alarm for Eldin's quotes
	SetFactFalse( FACT_MUSEUM_ALARM_WENT_OFF );
}

BOOLEAN EnterSector( INT16 sSectorX, INT16 sSectorY , INT8 bSectorZ )
{
	INT32 i;
	UNDERGROUND_SECTORINFO *pNode = NULL;
	CHAR8 bFilename[ 50 ];

	// pause game
	PauseGame( );

	// stop time for this frame
	InterruptTime( );

	//Setup the tactical existance of RPCs and CIVs in the last sector before moving on to a new sector.
	//@@@Evaluate
	if( gfWorldLoaded )
	{
		for( i = gTacticalStatus.Team[ CIV_TEAM ].bFirstID; i <= gTacticalStatus.Team[ CIV_TEAM ].bLastID; i++ )
		{
			if( MercPtrs[ i ]->bActive && MercPtrs[ i ]->bInSector )
			{
				SetupProfileInsertionDataForSoldier( MercPtrs[ i ] );
			}
		}
	}

	if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
	{
		// Handle NPC stuff related to changing sectors
		HandleQuestCodeOnSectorEntry( sSectorX, sSectorY, bSectorZ );
	}

	// Begin Load
	BeginLoadScreen( );

	// This has tobe done before loadworld, as it will remmove old gridnos if present
	RemoveMercsInSector( );
	
//Ja25 No meanwhiles	if( AreInMeanwhile() == FALSE )
	{
		SetSectorFlag( sSectorX, sSectorY, bSectorZ, SF_ALREADY_VISITED );
	}


	CreateLoadingScreenProgressBar();
	#ifdef JA2BETAVERSION
	//set the font
	SetProgressBarMsgAttributes( 0, FONT12ARIAL, FONT_MCOLOR_WHITE, 0 );

	//Set the tile so we don see the text come up
	SetProgressBarTextDisplayFlag( 0, TRUE, TRUE, TRUE );
	#endif

	//CreateProgressBar( 0, 160, 380, 480, 400 );
	//#ifdef JA2TESTVERSION
	//	//add more detailed progress bar
	//	DefineProgressBarPanel( 0, 65, 79, 94, 130, 350, 510, 430 );
	//	swprintf( str, L"Loading map:  %S", bFilename );
	//	SetProgressBarTitle( 0, str, FONT12POINT1, FONT_BLACK, FONT_BLACK );
	//#endif

	{
		BOOLEAN fOldMap = TRUE;

		if( !bSectorZ )
		{
			if ( SectorInfo[ ( SECTOR( sSectorX , sSectorY ) ) ].fCustomSector )
			{
				fOldMap = FALSE;
			}
		}
		else
		{
			// Find sector info and see if this is a custom map
			UNDERGROUND_SECTORINFO *pSector=NULL;

			pSector = FindUnderGroundSector( (INT16)sSectorX, (INT16)sSectorY, bSectorZ );

			if ( pSector )
			{
				if ( pSector->fCustomSector )
				{
					fOldMap = FALSE;
				}
			}
		}


		GetMapFileName( sSectorX, sSectorY, bSectorZ,  bFilename, TRUE, TRUE );

		if( !LoadWorld( bFilename, fOldMap, TRUE ) )
		{
			return( FALSE );
		}
	}

	// underground?
	if( bSectorZ )
	{
		pNode = FindUnderGroundSector( sSectorX, sSectorY, bSectorZ );
		
		// is there a sector?..if so set flag
		if( pNode )
		{
			pNode->fVisited = TRUE;
		}
	}

	// if we arent loading a saved game
	// ATE: Moved this form above, so that we can have the benefit of
	// changing the world BEFORE adding guys to it...
	if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
	{
		// Load the current sectors Information From the temporary files
		if( !LoadCurrentSectorsInformationFromTempItemsFile() )
		{ //The integrity of the temp files have been compromised.  Boot out of the game after warning message.
			InitExitGameDialogBecauseFileHackDetected();
			return TRUE;
		}
	}

	//if we need to modify the map in any way, put the code in here
//	HandleSectorSpecificModificatioToMap( sSectorX, sSectorY, bSectorZ );


	RemoveLoadingScreenProgressBar();
	//RemoveProgressBar( 0 );

	if( gfEnterTacticalPlacementGUI )
	{
		SetPendingNewScreen(GAME_SCREEN);
		InitTacticalPlacementGUI();
		HandleSectorSpecificModificatioToMap( sSectorX, sSectorY, bSectorZ, FALSE );
	}
	else
	{
		// in this case HandleSectorSpecific gets called inside PrepareLoadedSector()
		PrepareLoadedSector();
	}

	//if we need to modify the map in any way, put the code in here
	//HandleSectorSpecificModificatioToMap( sSectorX, sSectorY, bSectorZ, FALSE );

//	UnPauseGame( );

	// This function will either hide or display the tree tops, depending on the game setting
	SetTreeTopStateForMap();

	return TRUE; //because the map was loaded.
}


void UpdateMercsInSector( INT16 sSectorX, INT16 sSectorY, INT8 bSectorZ )
{
	INT32					cnt;
	SOLDIERTYPE		*pSoldier;
	BOOLEAN				fPOWSquadSet = FALSE;
	UINT8					ubPOWSquad=0;

	// Remove from interface slot
	RemoveAllPlayersFromSlot( );

	// Remove tactical interface stuff
	guiPendingOverrideEvent = I_CHANGE_TO_IDLE;

	//If we are in this function during the loading of a sector
	if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
	{
		//DONT set these values
		gusSelectedSoldier = NO_SOLDIER;	
		gfGameScreenLocateToSoldier = TRUE;
	}

	// Set all faces intactive
	SetAllAutoFacesInactive( );

	if ( fUsingEdgePointsForStrategicEntry )
	{
		BeginMapEdgepointSearch();
	}

	//if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
	{
		for ( cnt = 0, pSoldier = MercPtrs[ cnt ]; cnt < MAX_NUM_SOLDIERS; cnt++, pSoldier++)
		{	
			if ( gfRestoringEnemySoldiersFromTempFile && 
					cnt >= gTacticalStatus.Team[ ENEMY_TEAM ].bFirstID &&
					cnt <= gTacticalStatus.Team[ CREATURE_TEAM ].bLastID )
			{ //Don't update enemies/creatures (consec. teams) if they were
				//just restored via the temp map files...
				continue;
			}
			// Remove old merc, if exists
			RemoveMercSlot( pSoldier );

			pSoldier->bInSector = FALSE;

			if ( pSoldier->bActive  )
			{
				if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
				{
					if( gMapInformation.sCenterGridNo != -1 && gfBlitBattleSectorLocator && 
							(gubEnemyEncounterCode == ENEMY_AMBUSH_CODE || gubEnemyEncounterCode == BLOODCAT_AMBUSH_CODE) && pSoldier->bTeam != CIV_TEAM )
					{
						pSoldier->ubStrategicInsertionCode = INSERTION_CODE_GRIDNO;
						pSoldier->usStrategicInsertionData = gMapInformation.sCenterGridNo; 
					}
					else if( gfOverrideInsertionWithExitGrid )
					{
						pSoldier->ubStrategicInsertionCode = INSERTION_CODE_GRIDNO;
						pSoldier->usStrategicInsertionData = gExitGrid.usGridNo;
					}
				}

				if ( pSoldier->sSectorX == sSectorX && pSoldier->sSectorY == sSectorY && pSoldier->bSectorZ == bSectorZ && !pSoldier->fBetweenSectors )
				{
					gbMercIsNewInThisSector[ pSoldier->ubID ] = 1;

					UpdateMercInSector( pSoldier, sSectorX, sSectorY, bSectorZ );

					if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
					{
						if ( pSoldier->bAssignment == ASSIGNMENT_POW )
						{
							if ( !fPOWSquadSet )
							{
								fPOWSquadSet = TRUE;

								// ATE: If we are in i13 - pop up message!
								if ( sSectorY == MAP_ROW_I && sSectorX == 13 )
								{
									DoMessageBox( MSG_BOX_BASIC_STYLE, TacticalStr[ POW_MERCS_ARE_HERE ], GAME_SCREEN, ( UINT8 )MSG_BOX_FLAG_OK, NULL, NULL );	
								}
								else
								{
									AddCharacterToUniqueSquad( pSoldier );
									ubPOWSquad = pSoldier->bAssignment;								
									pSoldier->bNeutral		= FALSE;
								}
							}
							else
							{
								if ( sSectorY != MAP_ROW_I && sSectorX != 13 )
								{
									AddCharacterToSquad( pSoldier, ubPOWSquad );
								}
							}

							// ATE: Call actions based on what POW we are on...
							if ( gubQuest[ QUEST_HELD_IN_ALMA ] == QUESTINPROGRESS )
							{
								// Complete quest
								EndQuest( QUEST_HELD_IN_ALMA, sSectorX, sSectorY );

								// Do action
								HandleNPCDoAction( 0, NPC_ACTION_GRANT_EXPERIENCE_3, 0 );

							}

						}
					}
				}
				else
				{
					pSoldier->bInSector = FALSE;
				}
			}
		}
	}

	if ( fUsingEdgePointsForStrategicEntry )
	{
		EndMapEdgepointSearch();

		// Set to false
		fUsingEdgePointsForStrategicEntry = FALSE;
	}

}

void UpdateMercInSector( SOLDIERTYPE *pSoldier, INT16 sSectorX, INT16 sSectorY, INT8 bSectorZ )
{
	BOOLEAN fError = FALSE;
	if( pSoldier->uiStatusFlags & SOLDIER_IS_TACTICALLY_VALID)
	{
		pSoldier->ubStrategicInsertionCode = INSERTION_CODE_GRIDNO;
	}
	// OK, determine entrence direction and get sweetspot
	// Only if we are an OK guy to control....
	// SOME CHECKS HERE MUST BE FLESHED OUT......
	if ( pSoldier->bActive )		// This was in the if, removed by DEF:  pSoldier->bLife >= OKLIFE && 
	{
		// If we are not in transit...
		if ( pSoldier->bAssignment != IN_TRANSIT )
		{				
			// CHECK UBINSERTION CODE..
			if( pSoldier->ubStrategicInsertionCode == INSERTION_CODE_PRIMARY_EDGEINDEX || 
					pSoldier->ubStrategicInsertionCode == INSERTION_CODE_SECONDARY_EDGEINDEX )
			{
				if ( !fUsingEdgePointsForStrategicEntry )
				{
					// If we are not supposed to use this now, pick something better...
					pSoldier->ubStrategicInsertionCode = (UINT8)pSoldier->usStrategicInsertionData;
				}
			}

			MAPEDGEPOINT_SEARCH_FAILED:

			if ( pSoldier->ubProfile != NO_PROFILE && gMercProfiles[ pSoldier->ubProfile ].ubMiscFlags3 & PROFILE_MISC_FLAG3_PERMANENT_INSERTION_CODE )
			{
				// override orders
				pSoldier->bOrders = STATIONARY;
			}


			// Use insertion direction from loaded map!
			switch( pSoldier->ubStrategicInsertionCode )
			{
				case INSERTION_CODE_NORTH:
					pSoldier->sInsertionGridNo = gMapInformation.sNorthGridNo;
					if ( !gfEditMode && gMapInformation.sNorthGridNo == -1 )
						fError = TRUE;
					break;
				case INSERTION_CODE_SOUTH:
					pSoldier->sInsertionGridNo = gMapInformation.sSouthGridNo;
					if ( !gfEditMode && gMapInformation.sSouthGridNo == -1)
						fError = TRUE;
					break;
				case INSERTION_CODE_EAST:
					pSoldier->sInsertionGridNo = gMapInformation.sEastGridNo;
					if ( !gfEditMode && gMapInformation.sEastGridNo == -1)
						fError = TRUE;
					break;
				case INSERTION_CODE_WEST:
					pSoldier->sInsertionGridNo = gMapInformation.sWestGridNo;
					if ( !gfEditMode && gMapInformation.sWestGridNo == -1)
						fError = TRUE;
					break;
				case INSERTION_CODE_CENTER:
					pSoldier->sInsertionGridNo = gMapInformation.sCenterGridNo;
					if ( !gfEditMode && gMapInformation.sCenterGridNo == -1)
						fError = TRUE;
					break;
				case INSERTION_CODE_GRIDNO:
					pSoldier->sInsertionGridNo = pSoldier->usStrategicInsertionData;
					break;

				case INSERTION_CODE_PRIMARY_EDGEINDEX:
					pSoldier->sInsertionGridNo = SearchForClosestPrimaryMapEdgepoint( pSoldier->sPendingActionData2, (UINT8)pSoldier->usStrategicInsertionData );
					#ifdef JA2BETAVERSION
					{
						UINT8 str[256];
						sprintf( str, "%S's primary insertion gridno is %d using %d as initial search gridno and %d insertion code.", 
													pSoldier->name, pSoldier->sInsertionGridNo, pSoldier->sPendingActionData2, pSoldier->usStrategicInsertionData );
						DebugMsg( TOPIC_JA2, DBG_LEVEL_3, str );	
					}
					#endif
					if( pSoldier->sInsertionGridNo == NOWHERE )
					{
						ScreenMsg( FONT_RED, MSG_ERROR, L"Main edgepoint search failed for %s -- substituting entrypoint.", pSoldier->name );
						pSoldier->ubStrategicInsertionCode = (UINT8)pSoldier->usStrategicInsertionData;
						goto MAPEDGEPOINT_SEARCH_FAILED;
					}
					break;
				case INSERTION_CODE_SECONDARY_EDGEINDEX:
					pSoldier->sInsertionGridNo = SearchForClosestSecondaryMapEdgepoint( pSoldier->sPendingActionData2, (UINT8)pSoldier->usStrategicInsertionData );
					#ifdef JA2BETAVERSION
					{
						UINT8 str[256];
						sprintf( str, "%S's isolated insertion gridno is %d using %d as initial search gridno and %d insertion code.", 
													pSoldier->name, pSoldier->sInsertionGridNo, pSoldier->sPendingActionData2, pSoldier->usStrategicInsertionData );
						DebugMsg( TOPIC_JA2, DBG_LEVEL_3, str );	
					}
					#endif
					if( pSoldier->sInsertionGridNo == NOWHERE )
					{
						ScreenMsg( FONT_RED, MSG_ERROR, L"Isolated edgepont search failed for %s -- substituting entrypoint.", pSoldier->name );
						pSoldier->ubStrategicInsertionCode = (UINT8)pSoldier->usStrategicInsertionData;
						goto MAPEDGEPOINT_SEARCH_FAILED;
					}
					break;

				case INSERTION_CODE_ARRIVING_GAME:
					// Are we in Omerta!
					if ( sSectorX == gWorldSectorX && gWorldSectorX == 9 && sSectorY == gWorldSectorY && gWorldSectorY == 1 && bSectorZ == gbWorldSectorZ && gbWorldSectorZ == 0 )
					{
						// Try another location and walk into map
						pSoldier->sInsertionGridNo = 4379;
					}
					else
					{
						pSoldier->ubStrategicInsertionCode = INSERTION_CODE_NORTH;
						pSoldier->sInsertionGridNo				 = gMapInformation.sNorthGridNo;
					}
					break;
				case INSERTION_CODE_CHOPPER:
					// Try another location and walk into map
					// Add merc to chopper....
					//pSoldier->sInsertionGridNo = 4058;
					AddMercToHeli( pSoldier->ubID );
					return;
					break;
				default:
					pSoldier->sInsertionGridNo = 12880;
					DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Improper insertion code %d given to UpdateMercsInSector", pSoldier->ubStrategicInsertionCode ) );							
					break;
			}

			if( fError )
			{ //strategic insertion failed because it expected to find an entry point.  This is likely 
				//a missing part of the map or possible fault in strategic movement costs, traversal logic, etc.
				UINT16 szEntry[10];
				UINT16 szSector[10];
				INT16 sGridNo;
				GetLoadedSectorString( szSector );
				if( gMapInformation.sNorthGridNo != -1 )
				{
					swprintf( szEntry, L"north" );
					sGridNo = gMapInformation.sNorthGridNo;
				}
				else if( gMapInformation.sEastGridNo != -1 )
				{
					swprintf( szEntry, L"east" );
					sGridNo = gMapInformation.sEastGridNo;
				}
				else if( gMapInformation.sSouthGridNo != -1 )
				{
					swprintf( szEntry, L"south" );
					sGridNo = gMapInformation.sSouthGridNo;
				}
				else if( gMapInformation.sWestGridNo != -1 )
				{
					swprintf( szEntry, L"west" );
					sGridNo = gMapInformation.sWestGridNo;
				}
				else if( gMapInformation.sCenterGridNo != -1 )
				{
					swprintf( szEntry, L"center" );
					sGridNo = gMapInformation.sCenterGridNo;
				}
				else 
				{
					ScreenMsg( FONT_RED, MSG_BETAVERSION, L"Sector %s has NO entrypoints -- using precise center of map for %s.", szSector, pSoldier->name );
					pSoldier->sInsertionGridNo = 12880;
					AddSoldierToSector( pSoldier->ubID );
					return;
				}
				pSoldier->sInsertionGridNo = sGridNo;
				switch( pSoldier->ubStrategicInsertionCode )
				{
					case INSERTION_CODE_NORTH:
						ScreenMsg( FONT_RED, MSG_BETAVERSION, L"Sector %s doesn't have a north entrypoint -- substituting  %s entrypoint for %s.", szSector, szEntry, pSoldier->name );
						break;
					case INSERTION_CODE_EAST:
						ScreenMsg( FONT_RED, MSG_BETAVERSION, L"Sector %s doesn't have a east entrypoint -- substituting  %s entrypoint for %s.", szSector, szEntry, pSoldier->name );
						break;
					case INSERTION_CODE_SOUTH:
						ScreenMsg( FONT_RED, MSG_BETAVERSION, L"Sector %s doesn't have a south entrypoint -- substituting  %s entrypoint for %s.", szSector, szEntry, pSoldier->name );
						break;
					case INSERTION_CODE_WEST:
						ScreenMsg( FONT_RED, MSG_BETAVERSION, L"Sector %s doesn't have a west entrypoint -- substituting  %s entrypoint for %s.", szSector, szEntry, pSoldier->name );
						break;
					case INSERTION_CODE_CENTER:
						ScreenMsg( FONT_RED, MSG_BETAVERSION, L"Sector %s doesn't have a center entrypoint -- substituting  %s entrypoint for %s.", szSector, szEntry, pSoldier->name );
						break;
				}
			}
			// If no insertion direction exists, this is bad!
			if ( pSoldier->sInsertionGridNo == -1 )
			{
				DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Insertion gridno for direction %d not added to map sector %d %d", pSoldier->ubStrategicInsertionCode, sSectorX, sSectorY ) );							
				pSoldier->sInsertionGridNo = 12880;
			}

			AddSoldierToSector( pSoldier->ubID );
		}
	}
}


void InitializeStrategicMapSectorTownNames( void )
{
//Town Sectors

	//Guard Post
//	StrategicMap[CALCULATE_STRATEGIC_INDEX( 9, 8 ) ].bNameId = GUARD_POST;

	// Town
	StrategicMap[CALCULATE_STRATEGIC_INDEX( 10, 9 ) ].bNameId = TOWN_1;
	StrategicMap[CALCULATE_STRATEGIC_INDEX( 11, 9 )].bNameId = TOWN_1;
	StrategicMap[CALCULATE_STRATEGIC_INDEX( 11, 8 )].bNameId = TOWN_1;

	//Abondoned Mine
	StrategicMap[CALCULATE_STRATEGIC_INDEX( 13, 9 )].bNameId = ABANDONED_MINE_SECTOR;

	//Power Generator
//	StrategicMap[CALCULATE_STRATEGIC_INDEX( 13, 10 )].bNameId = POWER_GEN;

	//Complex
//	StrategicMap[CALCULATE_STRATEGIC_INDEX( 15, 11 )].bNameId = COMPLEX;

/*
Ja25 Removerd to add new towns

  StrategicMap[2+2*MAP_WORLD_X].bNameId= StrategicMap[2+1*MAP_WORLD_X].bNameId= CHITZENA;
	StrategicMap[5+3*MAP_WORLD_X].bNameId=StrategicMap[6+3*MAP_WORLD_X].bNameId=StrategicMap[5+4*MAP_WORLD_X].bNameId = StrategicMap[4+4*MAP_WORLD_X].bNameId =SAN_MONA;
	StrategicMap[9+1*MAP_WORLD_X].bNameId=StrategicMap[10+1*MAP_WORLD_X].bNameId=OMERTA;
  StrategicMap[13+2*MAP_WORLD_X].bNameId=StrategicMap[13+3*MAP_WORLD_X].bNameId=StrategicMap[13+4*MAP_WORLD_X].bNameId=DRASSEN;
	StrategicMap[1+7*MAP_WORLD_X].bNameId=StrategicMap[1+8*MAP_WORLD_X].bNameId=StrategicMap[2+7*MAP_WORLD_X].bNameId= StrategicMap[2+8*MAP_WORLD_X].bNameId = StrategicMap[3+8*MAP_WORLD_X].bNameId = GRUMM;
	StrategicMap[6+9*MAP_WORLD_X].bNameId=ESTONI;
  StrategicMap[9+10*MAP_WORLD_X].bNameId=TIXA;
	StrategicMap[8+6*MAP_WORLD_X].bNameId=StrategicMap[9+6*MAP_WORLD_X].bNameId=StrategicMap[8+7*MAP_WORLD_X].bNameId=StrategicMap[9+7*MAP_WORLD_X].bNameId= StrategicMap[8+8*MAP_WORLD_X].bNameId = CAMBRIA;
	StrategicMap[13+9*MAP_WORLD_X].bNameId=StrategicMap[14+9*MAP_WORLD_X].bNameId=StrategicMap[13+8*MAP_WORLD_X].bNameId=StrategicMap[14+8*MAP_WORLD_X].bNameId=ALMA;
	StrategicMap[4+11*MAP_WORLD_X].bNameId=ORTA;
	StrategicMap[11+12*MAP_WORLD_X].bNameId= 	StrategicMap[12+12*MAP_WORLD_X].bNameId = BALIME;
	StrategicMap[3+14*MAP_WORLD_X].bNameId=StrategicMap[4+14*MAP_WORLD_X].bNameId=StrategicMap[5+14*MAP_WORLD_X].bNameId=StrategicMap[3+15*MAP_WORLD_X].bNameId=StrategicMap[4+15*MAP_WORLD_X].bNameId= StrategicMap[3+16*MAP_WORLD_X].bNameId = MEDUNA;
	//StrategicMap[3+16*MAP_WORLD_X].bNameId=PALACE;
	return;
*/

}


// Get sector ID string makes a string like 'A9 - OMERTA', or just J11 if no town....
void GetSectorIDString( INT16 sSectorX, INT16 sSectorY, INT8 bSectorZ , CHAR16 *zString, BOOLEAN fDetailed )
{

#ifdef JA2DEMO

	swprintf( zString, L"Demoville" );

#else
	SECTORINFO *pSector = NULL;
	UNDERGROUND_SECTORINFO *pUnderground;
	INT8		bTownNameID; 	
	INT8		bMineIndex;
	UINT8 ubSectorID = 0;
	UINT8 ubLandType = 0;

	if( sSectorX <= 0 || sSectorY <= 0 || bSectorZ < 0 )
	{
		//swprintf( zString, L"%s", pErrorStrings[0] );
	}
	else if( bSectorZ != 0 )
	{
		pUnderground = FindUnderGroundSector( sSectorX, sSectorY, bSectorZ );

		if ( pUnderground )
		{
			// ATE: Check if this is a custom sector
			if ( pUnderground->fCustomSector )
			{
				// Use sector name...
				swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pUnderground->zCustomLevelName );			
				return;
			}
		}

		//Ja25:  DEF: Changed cause we dont need to know the underground status if we are loading a saved game
		// and the underground sector WILL NOT be loaded when we first load to the main menu
//		if( pUnderground && ( pUnderground->fVisited || gfGettingNameFromSaveLoadScreen ) )
		if( ( pUnderground && pUnderground->fVisited ) || gfGettingNameFromSaveLoadScreen )
		{
			bMineIndex = GetIdOfMineForSector( sSectorX, sSectorY, bSectorZ );
			if( bMineIndex != -1 )
			{
//Ja25				swprintf( zString, L"%c%d: %s %s", 'A' + sSectorY - 1, sSectorX, pTownNames[ GetTownAssociatedWithMine( bMineIndex ) ], pwMineStrings[ 0 ] );
				swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pTownNames[ GetTownAssociatedWithMine( bMineIndex ) ] );
			}
			else switch( SECTOR( sSectorX, sSectorY ) )
			{
/* 
Ja25:  Not in the game
				case SEC_A10:
					swprintf( zString, L"A10: %s", pLandTypeStrings[ REBEL_HIDEOUT ] );
					break;
				case SEC_J9:
					swprintf( zString, L"J9: %s", pLandTypeStrings[ TIXA_DUNGEON ] );
					break;
				case SEC_K4:
					swprintf( zString, L"K4: %s", pLandTypeStrings[ ORTA_BASEMENT ] );
					break;
				case SEC_O3:
					swprintf( zString, L"O3: %s", pLandTypeStrings[ TUNNEL ] );
					break;
				case SEC_P3:
					swprintf( zString, L"P3: %s", pLandTypeStrings[ SHELTER ] );
					break;
*/
				//caves under power genplant
				case SEC_J13:
					swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pTownNames[ 2 ] );
					break;

				// Final Complex
				case SEC_K15:
				case SEC_L15:
					swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ FINAL_COMPLEX ] );
					break;

				//Tunnels
				case SEC_J14:
				case SEC_K14:
					swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ TUNNEL ] );
					break;
				default:
					swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ CREATURE_LAIR ] );
					break;
			}
		}
		else
		{ //Display nothing
			wcscpy( zString, L"" );
		}
	}
	else
	{
		bTownNameID = StrategicMap[ CALCULATE_STRATEGIC_INDEX( sSectorX, sSectorY ) ].bNameId;
		ubSectorID = (UINT8)SECTOR( sSectorX, sSectorY );
		pSector = &SectorInfo[ ubSectorID ];
		ubLandType = pSector->ubTraversability[ 4 ];
		swprintf( zString, L"%c%d: ", 'A' + sSectorY - 1, sSectorX );

		// ATE: Use custom map name
		if ( SectorInfo[ ( SECTOR( sSectorX , sSectorY ) ) ].fCustomSector )
		{			
			swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, SectorInfo[ ( SECTOR( sSectorX , sSectorY ) ) ].zCustomLevelName );
			return;
		}


		if ( bTownNameID == BLANK_SECTOR )
		{
			// OK, build string id like J11
			// are we dealing with the unfound towns?
			switch( ubSectorID )
			{
/*
Ja25: None of these sectors are in the game
				case SEC_D2: //Chitzena SAM
					if( !fSamSiteFound[ SAM_SITE_ONE ] )
						wcscat( zString, pLandTypeStrings[ TROPICS ] );
					else if( fDetailed )
						wcscat( zString, pLandTypeStrings[ TROPICS_SAM_SITE ] );
					else 
						wcscat( zString, pLandTypeStrings[ SAM_SITE ] );
					break;
				case SEC_D15: //Drassen SAM
					if( !fSamSiteFound[ SAM_SITE_TWO ] )
						wcscat( zString, pLandTypeStrings[ SPARSE ] );
					else if( fDetailed )
						wcscat( zString, pLandTypeStrings[ SPARSE_SAM_SITE ] );
					else 
						wcscat( zString, pLandTypeStrings[ SAM_SITE ] );
					break;
				case SEC_I8: //Cambria SAM
					if( !fSamSiteFound[ SAM_SITE_THREE ] )
						wcscat( zString, pLandTypeStrings[ SAND ] );
					else if( fDetailed )
						wcscat( zString, pLandTypeStrings[ SAND_SAM_SITE ] );
					else 
						wcscat( zString, pLandTypeStrings[ SAM_SITE ] );
					break;
*/

				case SEC_H7:
//					if( pSector->fSurfaceWasEverPlayerControlled )
					if( GetSectorFlagStatus( 7, 8, 0, SF_ALREADY_VISITED ) == TRUE  || gfGettingNameFromSaveLoadScreen )
						swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ CRASH_SITE_TYPE ] );
					else
						swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ MOUNTAINS_TYPE ] );
					break;

				case SEC_H8:
						swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ MOUNTAINS_TYPE ] );
					break;

				//Guard Post
				case SEC_H9:
					if( GetSectorFlagStatus( 9, 8, 0, SF_ALREADY_VISITED ) == TRUE  || gfGettingNameFromSaveLoadScreen )
						swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ GUARD_POST_TYPE ] );
					else
						swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ MOUNTAINS_TYPE ] );
					break;

				case SEC_J13:
					if( GetSectorFlagStatus( 13, 10, 0, SF_ALREADY_VISITED ) == TRUE  || gfGettingNameFromSaveLoadScreen )
						swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ POWER_PLANT_TYPE ] );
					else
						swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ UNKNOWN_TYPE ] );
					break;

				//Complex
				case SEC_K15:
					if( GetSectorFlagStatus( 15, 11, 0, SF_ALREADY_VISITED ) == TRUE  || gfGettingNameFromSaveLoadScreen )
						swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ FINAL_COMPLEX ] );
					else
						swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ UNKNOWN_TYPE ] );
					break;

				case SEC_K16:
					swprintf( zString, L"%c%d: %s", 'A' + sSectorY - 1, sSectorX, pLandTypeStrings[ SPARSE ] );
					break;

				default:
					wcscat( zString, pLandTypeStrings[ ubLandType ] );
					break;
			}
		}
		else
		{
			switch( ubSectorID )
			{
/*
Ja25:  None of these sectors are in the game
				case SEC_B13:
					if( fDetailed )
						wcscat( zString, pLandTypeStrings[ DRASSEN_AIRPORT_SITE ] );
					else
						wcscat( zString, pTownNames[ DRASSEN ] );
					break;
				case SEC_F8:
					if( fDetailed )
						wcscat( zString, pLandTypeStrings[ CAMBRIA_HOSPITAL_SITE ] );
					else
						wcscat( zString, pTownNames[ CAMBRIA ] );
					break;
				case SEC_J9: //Tixa
			if( !fFoundTixa )
						wcscat( zString, pLandTypeStrings[ SAND ] );
					else
						wcscat( zString, pTownNames[ TIXA ] );
					break;
				case SEC_K4: //Orta
					if( !fFoundOrta )
						wcscat( zString, pLandTypeStrings[ SWAMP ] );
					else
						wcscat( zString, pTownNames[ ORTA ] );
					break;
				case SEC_N3: 
					if( fDetailed )
						wcscat( zString, pLandTypeStrings[ MEDUNA_AIRPORT_SITE ] );
					else
						wcscat( zString, pTownNames[ MEDUNA ] );
					break;
*/
				default:
/*
Ja25: No meduna
					if( ubSectorID == SEC_N4 && fSamSiteFound[ SAM_SITE_FOUR ] )
					{	//Meduna's SAM site
						if( fDetailed )
							wcscat( zString, pLandTypeStrings[ MEDUNA_SAM_SITE ] );
						else
							wcscat( zString, pLandTypeStrings[ SAM_SITE ] );
					}
					else 
*/
					{	//All other towns that are known since beginning of the game.
						wcscat( zString, pTownNames[ bTownNameID ] );
						if( fDetailed )
						{
							switch( ubSectorID )
							{ 
								//Append the word, "mine" for town sectors containing a mine.
/*
Ja25:  Only 1 mine
								case SEC_B2:
								case SEC_D4:
								case SEC_D13:
								case SEC_H3:
								case SEC_H8:
								case SEC_I14:

								case SEC_I13:
									wcscat( zString, L" " ); //space
									wcscat( zString, pwMineStrings[ 0 ] ); //then "Mine"
									break;
*/
							}
						}
					}
					break;
			}
		}
	}
#endif
}


UINT8 SetInsertionDataFromAdjacentMoveDirection( SOLDIERTYPE *pSoldier, UINT8 ubTacticalDirection, INT16 sAdditionalData  )
{
	UINT8				ubDirection;
	EXITGRID		ExitGrid;


	// Set insertion code
	switch( ubTacticalDirection )
	{
		// OK, we are using an exit grid - set insertion values...

		case 255:
			if ( !GetExitGrid( sAdditionalData, &ExitGrid ) )
			{
				AssertMsg( 0, String( "No valid Exit grid can be found when one was expected: SetInsertionDataFromAdjacentMoveDirection." ) );
			}
			ubDirection = 255;
			pSoldier->ubStrategicInsertionCode = INSERTION_CODE_GRIDNO;
			pSoldier->usStrategicInsertionData = ExitGrid.usGridNo;
			pSoldier->bUseExitGridForReentryDirection = TRUE;
			break;		

		case NORTH:
			ubDirection = NORTH_STRATEGIC_MOVE;
			pSoldier->ubStrategicInsertionCode = INSERTION_CODE_SOUTH;
			break;
		case SOUTH:
			ubDirection = SOUTH_STRATEGIC_MOVE;
			pSoldier->ubStrategicInsertionCode = INSERTION_CODE_NORTH;
			break;
		case EAST:
			ubDirection = EAST_STRATEGIC_MOVE;
			pSoldier->ubStrategicInsertionCode = INSERTION_CODE_WEST;
			break;
		case WEST:
			ubDirection = WEST_STRATEGIC_MOVE;
			pSoldier->ubStrategicInsertionCode = INSERTION_CODE_EAST;
			break;
		default:
			// Wrong direction given!
			#ifdef JA2BETAVERSION
				DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Improper insertion direction %d given to SetInsertionDataFromAdjacentMoveDirection", ubTacticalDirection ) );							
				ScreenMsg( FONT_RED, MSG_ERROR, L"Improper insertion direction %d given to SetInsertionDataFromAdjacentMoveDirection", ubTacticalDirection );
			#endif
			ubDirection = EAST_STRATEGIC_MOVE;
			pSoldier->ubStrategicInsertionCode = INSERTION_CODE_WEST;
	}

	return( ubDirection );

}

UINT8 GetInsertionDataFromAdjacentMoveDirection( UINT8 ubTacticalDirection, INT16 sAdditionalData  )
{
	UINT8				ubDirection;


	// Set insertion code
	switch( ubTacticalDirection )
	{
		// OK, we are using an exit grid - set insertion values...

		case 255:

			ubDirection = 255;
			break;		

		case NORTH:
			ubDirection = NORTH_STRATEGIC_MOVE;
			break;
		case SOUTH:
			ubDirection = SOUTH_STRATEGIC_MOVE;
			break;
		case EAST:
			ubDirection = EAST_STRATEGIC_MOVE;
			break;
		case WEST:
			ubDirection = WEST_STRATEGIC_MOVE;
			break;
		default:
			// Wrong direction given!
			#ifdef JA2BETAVERSION
				DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Improper insertion direction %d given to GetInsertionDataFromAdjacentMoveDirection", ubTacticalDirection ) );							
				ScreenMsg( FONT_RED, MSG_ERROR, L"Improper insertion direction %d given to GetInsertionDataFromAdjacentMoveDirection", ubTacticalDirection );
			#endif
			ubDirection = EAST_STRATEGIC_MOVE;
	}

	return( ubDirection );

}

UINT8 GetStrategicInsertionDataFromAdjacentMoveDirection( UINT8 ubTacticalDirection, INT16 sAdditionalData  )
{
	UINT8				ubDirection;


	// Set insertion code
	switch( ubTacticalDirection )
	{
		// OK, we are using an exit grid - set insertion values...

		case 255:

			ubDirection = 255;
			break;		

		case NORTH:
			ubDirection = INSERTION_CODE_SOUTH;
			break;
		case SOUTH:
			ubDirection = INSERTION_CODE_NORTH;
			break;
		case EAST:
			ubDirection = INSERTION_CODE_WEST;
			break;
		case WEST:
			ubDirection = INSERTION_CODE_EAST;
			break;
		default:
			// Wrong direction given!
			#ifdef JA2BETAVERSION
				DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Improper insertion direction %d given to SetInsertionDataFromAdjacentMoveDirection", ubTacticalDirection ) );							
				ScreenMsg( FONT_RED, MSG_ERROR, L"Improper insertion direction %d given to GetStrategicInsertionDataFromAdjacentMoveDirection", ubTacticalDirection );
			#endif
			ubDirection = EAST_STRATEGIC_MOVE;
	}

	return( ubDirection );

}


void JumpIntoAdjacentSector( UINT8 ubTacticalDirection, UINT8 ubJumpCode, INT16 sAdditionalData )
{
	INT32 cnt;
	SOLDIERTYPE		*pSoldier;
	SOLDIERTYPE *pValidSoldier = NULL;
	GROUP *pGroup;
	UINT32 uiTraverseTime=0;
	UINT8 ubDirection=0;
	EXITGRID ExitGrid;
	INT8 bPrevAssignment;
	UINT8 ubPrevGroupID;
	
	// Set initial selected
	// ATE: moved this towards top...
	gubPreferredInitialSelectedGuy = (UINT8)gusSelectedSoldier;

	if ( ubJumpCode == JUMP_ALL_LOAD_NEW || ubJumpCode == JUMP_ALL_NO_LOAD )
	{
		// TODO: Check flags to see if we can jump!
		// Move controllable mercs!
		cnt = gTacticalStatus.Team[ gbPlayerNum ].bFirstID;

		// look for all mercs on the same team, 
		for ( pSoldier = MercPtrs[ cnt ]; cnt <= gTacticalStatus.Team[ gbPlayerNum ].bLastID; cnt++,pSoldier++)
		{	
			// If we are controllable 
			if ( OK_CONTROLLABLE_MERC( pSoldier) && pSoldier->bAssignment == CurrentSquad( )  )
			{
				pValidSoldier = pSoldier;
				//This now gets handled by strategic movement.  It is possible that the
				//group won't move instantaneously.
				//pSoldier->sSectorX = sNewX;
				//pSoldier->sSectorY = sNewY;

				ubDirection = GetInsertionDataFromAdjacentMoveDirection( ubTacticalDirection, sAdditionalData );
				break;
			}
		}
	}
	else if ( ( ubJumpCode == JUMP_SINGLE_LOAD_NEW || ubJumpCode == JUMP_SINGLE_NO_LOAD ) )
	{
		// Use selected soldier...
		// This guy should always be 1 ) selected and 2 ) close enough to exit sector to leave
		if ( gusSelectedSoldier != NOBODY )
		{
			pValidSoldier = MercPtrs[ gusSelectedSoldier ];
			ubDirection = GetInsertionDataFromAdjacentMoveDirection( ubTacticalDirection, sAdditionalData );
		}

		// save info for desired squad and and time for all single mercs leaving their squad.
		bPrevAssignment = pValidSoldier->bAssignment;
		ubPrevGroupID = pValidSoldier->ubGroupID;

		if( ubJumpCode == JUMP_SINGLE_NO_LOAD )
		{ // handle soldier moving by themselves
			HandleSoldierLeavingSectorByThemSelf( pValidSoldier );
		}
		else
		{ // now add char to a squad all their own
			AddCharacterToUniqueSquad( pValidSoldier );
		}
		if( !pValidSoldier->ubNumTraversalsAllowedToMerge && bPrevAssignment < ON_DUTY )
		{
			PLAYERGROUP *pPlayer;
			pValidSoldier->ubDesiredSquadAssignment = bPrevAssignment;
			pValidSoldier->ubNumTraversalsAllowedToMerge = 2;
			pGroup = GetGroup( ubPrevGroupID );
			Assert( pGroup );
			Assert( pGroup->fPlayer );
			//Assert( pGroup->ubGroupSize );
			pPlayer = pGroup->pPlayerList;
			while( pPlayer )
			{
				if( pPlayer->pSoldier != pValidSoldier )
				{
					pPlayer->pSoldier->ubNumTraversalsAllowedToMerge = 100;
					pPlayer->pSoldier->ubDesiredSquadAssignment = NO_ASSIGNMENT;
				}
				pPlayer = pPlayer->next;
			}
		}
	}
	else
	{
		// OK, no jump code here given...
		DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Improper jump code %d given to JumpIntoAdjacentSector", ubJumpCode ) );							
	}

	Assert( pValidSoldier );


	//Now, determine the traversal time.
	pGroup = GetGroup( pValidSoldier->ubGroupID );
	AssertMsg( pGroup, String( "%S is not in a valid group (pSoldier->ubGroupID is %d)",pValidSoldier->name, pValidSoldier->ubGroupID) );

	// If we are going through an exit grid, don't get traversal direction!
	if ( ubTacticalDirection != 255 )
	{
		if( !gbWorldSectorZ )
		{
			uiTraverseTime = GetSectorMvtTimeForGroup( (UINT8)SECTOR( pGroup->ubSectorX, pGroup->ubSectorY ), ubDirection, pGroup );
		}
		else if( gbWorldSectorZ > 0 )
		{ //We are attempting to traverse in an underground environment.  We need to use a complete different
			//method.  When underground, all sectors are instantly adjacent.
			uiTraverseTime = UndergroundTacticalTraversalTime( ubDirection );
		}
		if( uiTraverseTime == 0xffffffff )
			AssertMsg( 0, "Attempting to tactically traverse to adjacent sector, despite being unable to do so.");
	}

	// Alrighty, we want to do whatever our omnipotent player asked us to do
	// this is what the ubJumpCode is for.
	// Regardless of that we were asked to do, we MUST walk OFF ( Ian loves this... )
	// So..... let's setup our people to walk off...
	// We deal with a pGroup here... if an all move or a group...

	// Setup some globals so our callback that deals when guys go off screen is handled....
	// Look in the handler function AllMercsHaveWalkedOffSector() below...
	gpAdjacentGroup				= pGroup;
	gubAdjacentJumpCode		= ubJumpCode;
	guiAdjacentTraverseTime	= uiTraverseTime;
	gubTacticalDirection  = ubTacticalDirection;
	gsAdditionalData			= sAdditionalData;

	// If normal direction, use it!
	if ( ubTacticalDirection != 255 )
	{
		gsAdjacentSectorX				= (INT16)(gWorldSectorX + DirXIncrementer[ ubTacticalDirection ]);
		gsAdjacentSectorY				= (INT16)(gWorldSectorY + DirYIncrementer[ ubTacticalDirection ]);
		gbAdjacentSectorZ				= pValidSoldier->bSectorZ;
	}
	else
	{
		// Take directions from exit grid info!
		if ( !GetExitGrid( sAdditionalData, &ExitGrid ) )
		{
			AssertMsg( 0, String( "Told to use exit grid at %d but one does not exist", sAdditionalData ) );
		}

		gsAdjacentSectorX				= ExitGrid.ubGotoSectorX;
		gsAdjacentSectorY				= ExitGrid.ubGotoSectorY;
		gbAdjacentSectorZ				= ExitGrid.ubGotoSectorZ;
		gusDestExitGridNo				= ExitGrid.usGridNo;
	}

	// Give guy(s) orders to walk off sector...
	if( pGroup->fPlayer )
	{	//For player groups, update the soldier information
		PLAYERGROUP *curr;
		INT16				sGridNo;
		UINT8				ubNum = 0;

		curr = pGroup->pPlayerList;
		while( curr )
		{	
			if ( OK_CONTROLLABLE_MERC( curr->pSoldier) )
			{
				if ( ubTacticalDirection != 255 )
				{
					sGridNo = PickGridNoNearestEdge( curr->pSoldier, ubTacticalDirection );

					curr->pSoldier->sPreTraversalGridNo = curr->pSoldier->sGridNo;

					if ( sGridNo != NOWHERE )
					{
						// Save wait code - this will make buddy walk off screen into oblivion
						curr->pSoldier->ubWaitActionToDo = 2;
						// This will set the direction so we know now to move into oblivion
						curr->pSoldier->uiPendingActionData1		 = ubTacticalDirection;
					}
					else
					{
						AssertMsg( 0, String( "Failed to get good exit location for adjacentmove" ) );
					}

					EVENT_GetNewSoldierPath( curr->pSoldier, sGridNo, WALKING );

				}
				else
				{
						// Here, get closest location for exit grid....
						sGridNo = FindGridNoFromSweetSpotCloseToExitGrid( curr->pSoldier, sAdditionalData, 10, &ubDirection );

						//curr->pSoldier->
						if ( sGridNo != NOWHERE )
						{
							// Save wait code - this will make buddy walk off screen into oblivion
						//	curr->pSoldier->ubWaitActionToDo = 2;
						}
						else
						{
							AssertMsg( 0, String( "Failed to get good exit location for adjacentmove" ) );
						}

						// Don't worry about walk off screen, just stay at gridno...
						curr->pSoldier->ubWaitActionToDo = 1;

						// Set buddy go!
						gfPlotPathToExitGrid = TRUE;
						EVENT_GetNewSoldierPath( curr->pSoldier, sGridNo, WALKING );
						gfPlotPathToExitGrid = FALSE;

				}
				ubNum++;
			}
			else
			{
				// We will remove them later....
			}
			curr = curr->next;
		}

		// ATE: Do another round, removing guys from group that can't go on...
BEGINNING_LOOP:

		curr = pGroup->pPlayerList;
		while( curr )
		{	
			if ( !OK_CONTROLLABLE_MERC( curr->pSoldier ) )
			{
				RemoveCharacterFromSquads( curr->pSoldier );
				goto BEGINNING_LOOP;
			}
			curr = curr->next;
		}


		// OK, setup TacticalOverhead polling system that will notify us once everybody
		// has made it to our destination.
		if ( ubTacticalDirection != 255 )
		{
			SetActionToDoOnceMercsGetToLocation( WAIT_FOR_MERCS_TO_WALKOFF_SCREEN, ubNum, ubJumpCode, 0, 0 );
		}
		else
		{
			// Add new wait action here...
			SetActionToDoOnceMercsGetToLocation( WAIT_FOR_MERCS_TO_WALK_TO_GRIDNO, ubNum, ubJumpCode, 0, 0 );
		}

		// Lock UI!
		guiPendingOverrideEvent = LU_BEGINUILOCK;
		HandleTacticalUI( );
	}
}


void HandleSoldierLeavingSectorByThemSelf( SOLDIERTYPE *pSoldier )
{
	// soldier leaving thier squad behind, will rejoin later
	// if soldier in a squad, set the fact they want to return here
	UINT8 ubGroupId;

	if( pSoldier->bAssignment < ON_DUTY )
	{
			RemoveCharacterFromSquads( pSoldier );

		// are they in a group?..remove from group
		if( pSoldier->ubGroupID != 0 )
		{
			// remove from group
			RemovePlayerFromGroup(  pSoldier->ubGroupID, pSoldier );
			pSoldier->ubGroupID = 0;
		}
	}
	else
	{
		// otherwise, they are on thier own, not in a squad, simply remove mvt group
		if( pSoldier->ubGroupID && pSoldier->bAssignment != VEHICLE )
		{ //Can only remove groups if they aren't persistant (not in a squad or vehicle)
			// delete group
			RemoveGroup( pSoldier->ubGroupID );
			pSoldier->ubGroupID = 0;
		}
	}

	// set to guard
	AddCharacterToUniqueSquad( pSoldier );

	if( pSoldier->ubGroupID == 0 )
	{
	  // create independant group
	  ubGroupId = CreateNewPlayerGroupDepartingFromSector( ( UINT8 )pSoldier->sSectorX, ( UINT8 )pSoldier->sSectorY );
	  AddPlayerToGroup( ubGroupId , pSoldier );
	}

	return;
}

void AllMercsWalkedToExitGrid()
{
	PLAYERGROUP *pPlayer;
	BOOLEAN fDone;

  HandlePotentialMoraleHitForSkimmingSectors( gpAdjacentGroup );

	if( gubAdjacentJumpCode == JUMP_ALL_NO_LOAD || gubAdjacentJumpCode == JUMP_SINGLE_NO_LOAD )
	{
		Assert( gpAdjacentGroup );
		pPlayer = gpAdjacentGroup->pPlayerList;
		pPlayer = gpAdjacentGroup->pPlayerList;
		while( pPlayer )
		{
			SetInsertionDataFromAdjacentMoveDirection( pPlayer->pSoldier, gubTacticalDirection, gsAdditionalData );

			RemoveSoldierFromTacticalSector( pPlayer->pSoldier, TRUE );

			pPlayer = pPlayer->next;
		}

		SetGroupSectorValue( (UINT8)gsAdjacentSectorX, (UINT8)gsAdjacentSectorY, gbAdjacentSectorZ, gpAdjacentGroup->ubGroupID );
		AttemptToMergeSeparatedGroups( gpAdjacentGroup, FALSE );

		SetDefaultSquadOnSectorEntry( TRUE );

	}
	else
	{
		//Because we are actually loading the new map, and we are physically traversing, we don't want
		//to bring up the prebattle interface when we arrive if there are enemies there.  This flag
		//ignores the initialization of the prebattle interface and clears the flag.
		gfTacticalTraversal = TRUE;
		gpTacticalTraversalGroup = gpAdjacentGroup;

		//Check for any unconcious and/or dead merc and remove them from the current squad, so that they
		//don't get moved to the new sector.
		fDone = FALSE;
		while( !fDone )
		{
			fDone = FALSE;
			pPlayer = gpAdjacentGroup->pPlayerList;
			while( pPlayer )
			{
				if( pPlayer->pSoldier->bLife < OKLIFE )
				{
					AddCharacterToUniqueSquad( pPlayer->pSoldier );
					break;
				}
				pPlayer = pPlayer->next;
			}
			if( !pPlayer )
			{
				fDone = TRUE;
			}
		}

		// OK, Set insertion direction for all these guys....
		Assert( gpAdjacentGroup );
		pPlayer = gpAdjacentGroup->pPlayerList;
		while( pPlayer )
		{
			SetInsertionDataFromAdjacentMoveDirection( pPlayer->pSoldier, gubTacticalDirection, gsAdditionalData );

			pPlayer = pPlayer->next;
		}

		//if the X & Y values are the same
		if( gsAdjacentSectorX == gpAdjacentGroup->ubSectorX && gsAdjacentSectorY == gpAdjacentGroup->ubSectorY )
		{
			HandleGoingUpOrDownStairsForLoadScreensPurposes( gpAdjacentGroup->ubSectorZ, gbAdjacentSectorZ );
		}


		SetGroupSectorValue( gsAdjacentSectorX, gsAdjacentSectorY, gbAdjacentSectorZ, gpAdjacentGroup->ubGroupID );
		AttemptToMergeSeparatedGroups( gpAdjacentGroup, FALSE );

		gFadeOutDoneCallback = DoneFadeOutExitGridSector;
		FadeOutGameScreen( );
	}
	if( !PlayerMercsInSector( (UINT8)gsAdjacentSectorX, (UINT8)gsAdjacentSectorY, (UINT8)gbAdjacentSectorZ ) )
	{
/*
Ja25 no loyalty
		HandleLoyaltyImplicationsOfMercRetreat( RETREAT_TACTICAL_TRAVERSAL, gsAdjacentSectorX, gsAdjacentSectorY, gbAdjacentSectorZ );
*/
	}
	if( gubAdjacentJumpCode == JUMP_ALL_NO_LOAD || gubAdjacentJumpCode == JUMP_SINGLE_NO_LOAD )
	{
		gfTacticalTraversal = FALSE;
		gpTacticalTraversalGroup = NULL;
		gpTacticalTraversalChosenSoldier = NULL;
	}
}

/* BACKUP VERSION -- Before KM rewrote it
	 The flaw with this version is that traversing multiple squads to an adjacent sector doesn't properly setup
	 tactical traversal information for the first squads to traverse, only the last.  The new version supports this
	 feature.
void AllMercsHaveWalkedOffSector( )
{
	PLAYERGROUP *pPlayer;
	SOLDIERTYPE *pSoldier;

	HandleLoyaltyImplicationsOfMercRetreat( RETREAT_TACTICAL_TRAVERSAL, gWorldSectorX, gWorldSectorY, gbWorldSectorZ );

	// ATE: Added here: donot load another screen if we were told not to....
	if( ( gubAdjacentJumpCode == JUMP_ALL_NO_LOAD || gubAdjacentJumpCode == JUMP_SINGLE_NO_LOAD ) )
	{ 
		//Case 1:
		//Move the group the conventionally strategic method

		// clear their strategic movement (mercpaths and waypoints)
		ClearMercPathsAndWaypointsForAllInGroup( gpAdjacentGroup );

		AddWaypointToPGroup( gpAdjacentGroup, (UINT8)gsAdjacentSectorX, (UINT8)gsAdjacentSectorY );

		pPlayer = gpAdjacentGroup->pPlayerList;
		while( pPlayer ) 
		{
			// NOTE: This line is different from case 2 and 3...
			RemoveSoldierFromTacticalSector( pPlayer->pSoldier, TRUE );

			// pass flag that this is a tactical traversal, the path built MUST go in the traversed direction even if longer!
			PlotPathForCharacter( pPlayer->pSoldier, gsAdjacentSectorX, gsAdjacentSectorY, TRUE );
			pPlayer = pPlayer->next;
		}

		SetDefaultSquadOnSectorEntry( TRUE );
	}
	else
	{
		// OK, Set insertion direction for all these guys....
		Assert( gpAdjacentGroup );
		pPlayer = gpAdjacentGroup->pPlayerList;
		while( pPlayer )
		{
			SetInsertionDataFromAdjacentMoveDirection( pPlayer->pSoldier, gubTacticalDirection, gsAdditionalData );

			pPlayer = pPlayer->next;
		}
		// OK, here we want to leave the screen
		// Two things can happen
		// 1 ) We are near a sector were there is a finite amount of time to traverse, so
		// we bring up mapscreen
		// 2 ) We can move right away so do it!
		if( guiAdjacentTraverseTime <= 5 )
		{ 
			INT16 sScreenX, sScreenY, sNewGridNo;
			UINT32	 sWorldX, sWorldY;

			//Case 2:
			//Because tactical travel time between town sectors is inconsequential, just warp the group and
			//the time by 5 minutes.

			// Loop through each guy and:
			// Determine 'mirror' gridno to place him
			// set that gridno in data
			// change insertion code to use edgepoints....
			pPlayer = gpAdjacentGroup->pPlayerList;
			while( pPlayer )
			{
				pSoldier = pPlayer->pSoldier;

				// Determine 'mirror' gridno...
				// Convert to absolute xy
				GetWorldXYAbsoluteScreenXY( (INT16)(pSoldier->sX / CELL_X_SIZE ), (INT16)(pSoldier->sY / CELL_Y_SIZE ), &sScreenX, &sScreenY ); 
				
				// Get 'mirror', depending on what direction...
				switch( gubTacticalDirection )
				{
					case NORTH:			sScreenY = 1520;				break;
					case SOUTH:			sScreenY = 0;						break;
					case EAST:			sScreenX = 0;						break;
					case WEST:			sScreenX = 3160;				break;
				}
				
				// Convert into a gridno again.....
				GetFromAbsoluteScreenXYWorldXY( &sWorldX, &sWorldY, sScreenX, sScreenY );
				sNewGridNo = (INT16)GETWORLDINDEXFROMWORLDCOORDS( sWorldY, sWorldX );
				
				// Save this gridNo....
				pSoldier->sPendingActionData2				= sNewGridNo;
				// Copy CODe computed earlier into data
				pSoldier->usStrategicInsertionData  = pSoldier->ubStrategicInsertionCode;
				// Now use NEW code....

				pSoldier->ubStrategicInsertionCode = CalcMapEdgepointClassInsertionCode( pSoldier->sPreTraversalGridNo );

				fUsingEdgePointsForStrategicEntry = TRUE;

				pPlayer = pPlayer->next;
			}

			gfTacticalTraversal = TRUE;
			gpTacticalTraversalGroup = gpAdjacentGroup;
			
			if( gbAdjacentSectorZ > 0 )
			{	//Nasty strategic movement logic doesn't like underground sectors!
				gfUndergroundTacticalTraversal = TRUE;
			}

			// clear their strategic movement (mercpaths and waypoints)
			ClearMercPathsAndWaypointsForAllInGroup( gpAdjacentGroup );

			AddWaypointToPGroup( gpAdjacentGroup, (UINT8)gsAdjacentSectorX, (UINT8)gsAdjacentSectorY );

			pPlayer = gpAdjacentGroup->pPlayerList;
			while( pPlayer )
			{
				// pass flag that this is a tactical traversal, the path built MUST go in the traversed direction even if longer!
				PlotPathForCharacter( pPlayer->pSoldier, gsAdjacentSectorX, gsAdjacentSectorY, TRUE );
				pPlayer = pPlayer->next;
			}

			if( gbAdjacentSectorZ > 0 )
			{	//Nasty strategic movement logic doesn't like underground sectors!
				gfUndergroundTacticalTraversal = FALSE;
			}

			//Warp the clock by 5 minutes, but ignore events until that 5 minutes is up.
			//...BUT only if we are above ground (if underground, traversal is always 1 minute.
			if( !gbAdjacentSectorZ )
			{
				UINT32 uiWarpTime;
				uiWarpTime = (GetWorldTotalMin() + 5) * 60 - GetWorldTotalSeconds();
				WarpGameTime( uiWarpTime, WARPTIME_PROCESS_TARGET_TIME_FIRST );
				//WarpGameTime( 300, WARPTIME_NO_PROCESSING_OF_EVENTS );
				//WarpGameTime( 1, WARPTIME_PROCESS_EVENTS_NORMALLY );
			}
			else if( gbAdjacentSectorZ > 0 )
			{
				UINT32 uiWarpTime;
				uiWarpTime = (GetWorldTotalMin() + 1) * 60 - GetWorldTotalSeconds();
				WarpGameTime( uiWarpTime, WARPTIME_PROCESS_TARGET_TIME_FIRST );
				//WarpGameTime( 60, WARPTIME_NO_PROCESSING_OF_EVENTS );
				//WarpGameTime( 1, WARPTIME_PROCESS_EVENTS_NORMALLY );
			}

			//Because we are actually loading the new map, and we are physically traversing, we don't want
			//to bring up the prebattle interface when we arrive if there are enemies there.  This flag
			//ignores the initialization of the prebattle interface and clears the flag.
			gFadeOutDoneCallback = DoneFadeOutAdjacentSector;
			FadeOutGameScreen( );
		}
		else
		{ //Case 3:
			BOOLEAN fWarpTime = FALSE;

			if( !gbAdjacentSectorZ && NumEnemiesInSector( gWorldSectorX, gWorldSectorY ) )
			{ //We are retreating from a sector with enemies in it and there are no mercs left  so 
				//warp the game time by 5 minutes to simulate the actual retreat.  This restricts the 
				//player from immediately coming back to the same sector they left to perhaps take advantage
				//of the tactical placement gui to get into better position.  Additionally, if there are any 
				//enemies in this sector that are part of a movement group, reset that movement group so that they 
				//are "in" the sector rather than 75% of the way to the next sector if that is the case.
				fWarpTime = TRUE;
				ResetMovementForEnemyGroupsInLocation( (UINT8)gWorldSectorX, (UINT8)gWorldSectorY );
			}
			
			//Lock game into mapscreen mode, but after the fade is done.
			gfEnteringMapScreen = TRUE;

			// ATE; Fade FAST....
			SetMusicFadeSpeed( 5 );
			SetMusicMode( MUSIC_TACTICAL_NOTHING );
			// clear their strategic movement (mercpaths and waypoints)
			ClearMercPathsAndWaypointsForAllInGroup( gpAdjacentGroup );

			AddWaypointToPGroup( gpAdjacentGroup, (UINT8)gsAdjacentSectorX, (UINT8)gsAdjacentSectorY );

			pPlayer = gpAdjacentGroup->pPlayerList;
			while( pPlayer )
			{
				// pass flag that this is a tactical traversal, the path built MUST go in the traversed direction even if longer!
				PlotPathForCharacter( pPlayer->pSoldier, gsAdjacentSectorX, gsAdjacentSectorY, TRUE );
				pPlayer = pPlayer->next;
			}
			if( fWarpTime )
			{
				WarpGameTime( 300, WARPTIME_NO_PROCESSING_OF_EVENTS );
			}
		}
	}
}
*/

void SetupTacticalTraversalInformation()
{
	SOLDIERTYPE *pSoldier;
	PLAYERGROUP *pPlayer;
	UINT32 sWorldX, sWorldY;
	INT16 sScreenX, sScreenY, sNewGridNo;

	Assert( gpAdjacentGroup );
	pPlayer = gpAdjacentGroup->pPlayerList;
	while( pPlayer )
	{
		pSoldier = pPlayer->pSoldier;

		SetInsertionDataFromAdjacentMoveDirection( pSoldier, gubTacticalDirection, gsAdditionalData );

		// pass flag that this is a tactical traversal, the path built MUST go in the traversed direction even if longer!
		PlotPathForCharacter( pSoldier, gsAdjacentSectorX, gsAdjacentSectorY, TRUE );
		
		if( guiAdjacentTraverseTime <= 5 )
		{
			// Determine 'mirror' gridno...
			// Convert to absolute xy
			GetWorldXYAbsoluteScreenXY( (INT16)(pSoldier->sX / CELL_X_SIZE ), (INT16)(pSoldier->sY / CELL_Y_SIZE ), &sScreenX, &sScreenY ); 
			
			// Get 'mirror', depending on what direction...
			switch( gubTacticalDirection )
			{
				case NORTH:			sScreenY = 1520;				break;
				case SOUTH:			sScreenY = 0;						break;
				case EAST:			sScreenX = 0;						break;
				case WEST:			sScreenX = 3160;				break;
			}
			
			// Convert into a gridno again.....
			GetFromAbsoluteScreenXYWorldXY( &sWorldX, &sWorldY, sScreenX, sScreenY );
			sNewGridNo = (INT16)GETWORLDINDEXFROMWORLDCOORDS( sWorldY, sWorldX );
			
			// Save this gridNo....
			pSoldier->sPendingActionData2				= sNewGridNo;
			// Copy CODe computed earlier into data
			pSoldier->usStrategicInsertionData  = pSoldier->ubStrategicInsertionCode;
			// Now use NEW code....

			pSoldier->ubStrategicInsertionCode = CalcMapEdgepointClassInsertionCode( pSoldier->sPreTraversalGridNo );

			if( gubAdjacentJumpCode == JUMP_SINGLE_LOAD_NEW || gubAdjacentJumpCode == JUMP_ALL_LOAD_NEW )
			{
				fUsingEdgePointsForStrategicEntry = TRUE;
			}
		}

		pPlayer = pPlayer->next;
	}
	if( gubAdjacentJumpCode == JUMP_ALL_NO_LOAD || gubAdjacentJumpCode == JUMP_SINGLE_NO_LOAD )
	{
		gfTacticalTraversal = FALSE;
		gpTacticalTraversalGroup = NULL;
		gpTacticalTraversalChosenSoldier = NULL;
	}
}

void AllMercsHaveWalkedOffSector( )
{
	PLAYERGROUP *pPlayer;
	BOOLEAN fEnemiesInLoadedSector = FALSE;

	if( NumEnemiesInAnySector( gWorldSectorX, gWorldSectorY, gbWorldSectorZ ) )
	{
		fEnemiesInLoadedSector = TRUE;		
	}

/*
Ja25 no loyalty
	HandleLoyaltyImplicationsOfMercRetreat( RETREAT_TACTICAL_TRAVERSAL, gWorldSectorX, gWorldSectorY, gbWorldSectorZ );
*/

	//Setup strategic traversal information
	if( guiAdjacentTraverseTime <= 5 )
	{
		gfTacticalTraversal = TRUE;
		gpTacticalTraversalGroup = gpAdjacentGroup;

		if( gbAdjacentSectorZ > 0 && guiAdjacentTraverseTime <= 5 )
		{	//Nasty strategic movement logic doesn't like underground sectors!
			gfUndergroundTacticalTraversal = TRUE;
		}
	}
	ClearMercPathsAndWaypointsForAllInGroup( gpAdjacentGroup );
	AddWaypointToPGroup( gpAdjacentGroup, (UINT8)gsAdjacentSectorX, (UINT8)gsAdjacentSectorY );
	if( gbAdjacentSectorZ > 0 && guiAdjacentTraverseTime <= 5 )
	{	//Nasty strategic movement logic doesn't like underground sectors!
		gfUndergroundTacticalTraversal = TRUE;
	}

	SetupTacticalTraversalInformation();

	// ATE: Added here: donot load another screen if we were told not to....
	if( ( gubAdjacentJumpCode == JUMP_ALL_NO_LOAD || gubAdjacentJumpCode == JUMP_SINGLE_NO_LOAD ) )
	{ //Case 1:  Group is leaving sector, but there are other mercs in sector and player wants to stay, or 
		//         there are other mercs in sector while a battle is in progress.
		pPlayer = gpAdjacentGroup->pPlayerList;
		while( pPlayer ) 
		{
			RemoveSoldierFromTacticalSector( pPlayer->pSoldier, TRUE );
			pPlayer = pPlayer->next;
		}
		SetDefaultSquadOnSectorEntry( TRUE );
	}
	else
	{
		if( fEnemiesInLoadedSector )
		{ //We are retreating from a sector with enemies in it and there are no mercs left  so 
			//warp the game time by 5 minutes to simulate the actual retreat.  This restricts the 
			//player from immediately coming back to the same sector they left to perhaps take advantage
			//of the tactical placement gui to get into better position.  Additionally, if there are any 
			//enemies in this sector that are part of a movement group, reset that movement group so that they 
			//are "in" the sector rather than 75% of the way to the next sector if that is the case.
			ResetMovementForEnemyGroupsInLocation( (UINT8)gWorldSectorX, (UINT8)gWorldSectorY );

			if( guiAdjacentTraverseTime > 5 )
			{
				//Because this final group is retreating, simulate extra time to retreat, so they can't immediately come back.
				WarpGameTime( 300, WARPTIME_NO_PROCESSING_OF_EVENTS );
			}
		}
		if( guiAdjacentTraverseTime <= 5 )
		{
			//Case 2:  Immediatly loading the next sector
			if( !gbAdjacentSectorZ )
			{
				UINT32 uiWarpTime;
				uiWarpTime = (GetWorldTotalMin() + 5) * 60 - GetWorldTotalSeconds();
				WarpGameTime( uiWarpTime, WARPTIME_PROCESS_TARGET_TIME_FIRST );
			}
			else if( gbAdjacentSectorZ > 0 )
			{
				UINT32 uiWarpTime;
				uiWarpTime = (GetWorldTotalMin() + 1) * 60 - GetWorldTotalSeconds();
				WarpGameTime( uiWarpTime, WARPTIME_PROCESS_TARGET_TIME_FIRST );
			}

			//Because we are actually loading the new map, and we are physically traversing, we don't want
			//to bring up the prebattle interface when we arrive if there are enemies there.  This flag
			//ignores the initialization of the prebattle interface and clears the flag.
			gFadeOutDoneCallback = DoneFadeOutAdjacentSector;
			FadeOutGameScreen( );
		}
		else
		{ //Case 3:  Going directly to mapscreen
		
			//Lock game into mapscreen mode, but after the fade is done.
			gfEnteringMapScreen = TRUE;

			// ATE; Fade FAST....
			SetMusicFadeSpeed( 5 );
			SetMusicMode( MUSIC_TACTICAL_NOTHING );
		}
	}
}

void DoneFadeOutExitGridSector( )
{
	SetCurrentWorldSector( gsAdjacentSectorX, gsAdjacentSectorY, gbAdjacentSectorZ );
	if( gfTacticalTraversal && gpTacticalTraversalGroup && gpTacticalTraversalChosenSoldier )
	{
		if( gTacticalStatus.fEnemyInSector )
		{
			TacticalCharacterDialogueWithSpecialEvent( gpTacticalTraversalChosenSoldier, QUOTE_ENEMY_PRESENCE, 0, 0, 0 );
		}
	}
	gfTacticalTraversal = FALSE;
	gpTacticalTraversalGroup = NULL;
	gpTacticalTraversalChosenSoldier = NULL;
	FadeInGameScreen( );
}

void DoneFadeOutAdjacentSector( )
{
	UINT8 ubDirection;
	SetCurrentWorldSector( gsAdjacentSectorX, gsAdjacentSectorY, gbAdjacentSectorZ );

	ubDirection = GetStrategicInsertionDataFromAdjacentMoveDirection( gubTacticalDirection, gsAdditionalData );
	if( gfTacticalTraversal && gpTacticalTraversalGroup && gpTacticalTraversalChosenSoldier )
	{
		if( gTacticalStatus.fEnemyInSector )
		{
			TacticalCharacterDialogueWithSpecialEvent( gpTacticalTraversalChosenSoldier, QUOTE_ENEMY_PRESENCE, 0, 0, 0 );
		}
	}
	gfTacticalTraversal = FALSE;
	gpTacticalTraversalGroup = NULL;
	gpTacticalTraversalChosenSoldier = NULL;

	if ( gfCaves )
	{
		// ATE; Set tactical status flag...
		gTacticalStatus.uiFlags |= IGNORE_ALL_OBSTACLES;
		// Set pathing flag to path through anything....
		gfPathAroundObstacles = FALSE;
	}
	
	// OK, give our guys new orders...
	if( gpAdjacentGroup->fPlayer )
	{	
		//For player groups, update the soldier information
		PLAYERGROUP *curr;
		UINT32 uiAttempts;
		INT16				sGridNo, sOldGridNo;
		UINT8				ubNum = 0;
		INT16 sWorldX, sWorldY;
		curr = gpAdjacentGroup->pPlayerList;
		while( curr )
		{	
			if( !(curr->pSoldier->uiStatusFlags & SOLDIER_IS_TACTICALLY_VALID) )
			{
				if( curr->pSoldier->sGridNo != NOWHERE )
				{
					sGridNo = PickGridNoToWalkIn( curr->pSoldier, ubDirection, &uiAttempts );

					//If the search algorithm failed due to too many attempts, simply reset the
					//the gridno as the destination is a reserved gridno and we will place the
					//merc there without walking into the sector.
					if( sGridNo == NOWHERE && uiAttempts == MAX_ATTEMPTS )
					{
						sGridNo = curr->pSoldier->sGridNo;
					}

					if( sGridNo != NOWHERE )
					{
						curr->pSoldier->ubWaitActionToDo = 1;
						// OK, here we have been given a position, a gridno has been given to use as well....
						sOldGridNo = curr->pSoldier->sGridNo;
						sWorldX = CenterX( sGridNo );
						sWorldY = CenterY( sGridNo );
						EVENT_SetSoldierPosition( curr->pSoldier, sWorldX, sWorldY );
						if( sGridNo != sOldGridNo )
						{
							EVENT_GetNewSoldierPath( curr->pSoldier, sOldGridNo, WALKING );
						}
						ubNum++;
					}
				}
				else
				{
					#ifdef JA2BETAVERSION
						UINT8 str[256];
						sprintf( str, "%S's gridno is NOWHERE, and is attempting to walk into sector.", curr->pSoldier->name );
						DebugMsg( TOPIC_JA2, DBG_LEVEL_3, str );	
					#endif
				}
			}
			curr = curr->next;
		}
		SetActionToDoOnceMercsGetToLocation( WAIT_FOR_MERCS_TO_WALKON_SCREEN, ubNum, 0, 0, 0 );
		guiPendingOverrideEvent = LU_BEGINUILOCK;
		HandleTacticalUI( );

		// Unset flag here.....
		gfPathAroundObstacles = TRUE;

	}
	FadeInGameScreen( );
}



BOOLEAN SoldierOKForSectorExit( SOLDIERTYPE * pSoldier, INT8 bExitDirection, UINT16 usAdditionalData )
{
	INT16 sXMapPos;
	INT16 sYMapPos;
	INT16 sWorldX;
	INT16 sWorldY;
	UINT8	ubDirection;
	INT16 sGridNo;
	INT16	sAPs;

	// if the soldiers gridno is not NOWHERE
	if( pSoldier->sGridNo == NOWHERE )
		return( FALSE );

	// OK, anyone on roofs cannot!
	if ( pSoldier->bLevel > 0 )
		return( FALSE );

	// get world absolute XY
	ConvertGridNoToXY( pSoldier->sGridNo, &sXMapPos, &sYMapPos );

	// Get screen coordinates for current position of soldier
	GetWorldXYAbsoluteScreenXY( sXMapPos, sYMapPos, &sWorldX, &sWorldY);

	// Check direction
	switch( bExitDirection )
	{	
		case EAST_STRATEGIC_MOVE:

			if ( sWorldX < ( ( gsTRX - gsTLX ) - CHECK_DIR_X_DELTA ) )
			{
				// NOT OK, return FALSE
				return( FALSE );
			}
			break;

		case WEST_STRATEGIC_MOVE:

			if ( sWorldX > CHECK_DIR_X_DELTA )
			{
				// NOT OK, return FALSE
				return( FALSE );
			}
			break;

		case SOUTH_STRATEGIC_MOVE:

			if ( sWorldY < ( ( gsBLY - gsTRY ) - CHECK_DIR_Y_DELTA ) )
			{
				// NOT OK, return FALSE
				return( FALSE );
			}
			break;

		case NORTH_STRATEGIC_MOVE:

			if ( sWorldY > CHECK_DIR_Y_DELTA )
			{
				// NOT OK, return FALSE
				return( FALSE );
			}
			break;

			// This case is for an exit grid....
			// check if we are close enough.....

		case -1:


			// FOR REALTIME - DO MOVEMENT BASED ON STANCE!
			if ( ( gTacticalStatus.uiFlags & REALTIME ) || !( gTacticalStatus.uiFlags & INCOMBAT ) )
			{
				pSoldier->usUIMovementMode =  GetMoveStateBasedOnStance( pSoldier, gAnimControl[ pSoldier->usAnimState ].ubEndHeight );
			}

			sGridNo = FindGridNoFromSweetSpotCloseToExitGrid( pSoldier, usAdditionalData, 10, &ubDirection );

			if ( sGridNo == NOWHERE )
			{
				return( FALSE );
			}

			// ATE: if we are in combat, get cost to move here....
			if ( gTacticalStatus.uiFlags & INCOMBAT )
			{
				// Turn off at end of function...
				sAPs = PlotPath( pSoldier, sGridNo, NO_COPYROUTE, NO_PLOT, TEMPORARY, (UINT16)pSoldier->usUIMovementMode, NOT_STEALTH, FORWARD, pSoldier->bActionPoints );

				if ( !EnoughPoints( pSoldier, sAPs, 0, FALSE ) )
				{
					return( FALSE );
				}
			}
			break;

	}
	return( TRUE );
}

//ATE: Returns FALSE if NOBODY is close enough, 1 if ONLY selected guy is and 2 if all on squad are...
BOOLEAN OKForSectorExit( INT8 bExitDirection, UINT16 usAdditionalData, UINT32 *puiTraverseTimeInMinutes )
{
	INT32 cnt;
	SOLDIERTYPE		*pSoldier;
	BOOLEAN		fAtLeastOneMercControllable = FALSE;
	BOOLEAN		fOnlySelectedGuy = FALSE;
	SOLDIERTYPE *pValidSoldier = NULL;
	UINT8			ubReturnVal = FALSE;
	UINT8			ubNumControllableMercs = 0;
	UINT8		  ubNumMercs = 0, ubNumEPCs = 0;
	UINT8     ubPlayerControllableMercsInSquad = 0;

	if( gusSelectedSoldier == NOBODY )
	{ //must have a selected soldier to be allowed to tactically traverse.
		return FALSE;
	}

	/*
	//Exception code for the two sectors in San Mona that are separated by a cliff.  We want to allow strategic
	//traversal, but NOT tactical traversal.  The only way to tactically go from D4 to D5 (or viceversa) is to enter
	//the cave entrance.
	if( gWorldSectorX == 4 && gWorldSectorY == 4 && !gbWorldSectorZ && bExitDirection == EAST_STRATEGIC_MOVE )
	{
		gfInvalidTraversal = TRUE;
		return FALSE;
	}
	if( gWorldSectorX == 5 && gWorldSectorY == 4 && !gbWorldSectorZ && bExitDirection == WEST_STRATEGIC_MOVE )
	{
		gfInvalidTraversal = TRUE;
		return FALSE;
	}
	*/

#ifdef JA2UB_PRESS_PREVIEW

	if( gWorldSectorX == 10 && gWorldSectorY == 9 && !gbWorldSectorZ && bExitDirection == EAST_STRATEGIC_MOVE )
	{
		gfInvalidTraversal = TRUE;
		return FALSE;
	}

#endif

	//
	// Check to see if we are in the I13 map were Biggens has explosives all around.  If we are, the player can
	// tactically traverse and bypass the explosives.  Not good.  We need to avoid that.
	//

	//if we are in I13, and we are wanting to exit through an exit grid, and it is the right gridno
	if( gWorldSectorX == 13 && gWorldSectorY == MAP_ROW_I && gbWorldSectorZ == 0 && 
			bExitDirection == -1 &&
			usAdditionalData == 12422 )
	{
		SOLDIERTYPE *pSoldier = NULL;

		//Get biggens soldier ptr
		pSoldier = FindSoldierByProfileID( BIGGENS, TRUE );

		//if biggens hasnt been recruited yet
		if( pSoldier == NULL )
		{
			//if the explosives are still there
			if( !gJa25SaveStruct.fBiggensUsedDetonator )
			{
				//we shouldnt allow the user to tactically traverse out of here
				return( FALSE );
			}
		}
	}

		
	gfInvalidTraversal = FALSE;
	gfLoneEPCAttemptingTraversal = FALSE;
	gubLoneMercAttemptingToAbandonEPCs = 0;
	gbPotentiallyAbandonedEPCSlotID = -1;

	// Look through all mercs and check if they are within range of east end....
	cnt = gTacticalStatus.Team[ gbPlayerNum ].bFirstID;

  // look for all mercs on the same team, 
  for ( pSoldier = MercPtrs[ cnt ]; cnt <= gTacticalStatus.Team[ gbPlayerNum ].bLastID; cnt++,pSoldier++)
	{	
		// If we are controllable 
		if ( OK_CONTROLLABLE_MERC( pSoldier) && pSoldier->bAssignment == CurrentSquad( ) )
		{
			//Need to keep a copy of a good soldier, so we can access it later, and
			//not more than once.
			pValidSoldier = pSoldier;

			ubNumControllableMercs++;

			//We need to keep track of the number of EPCs and mercs in this squad.  If we have
			//only one merc and one or more EPCs, then we can't allow the merc to tactically traverse,
			//if he is the only merc near enough to traverse.
			if( AM_AN_EPC( pSoldier ) )
			{
				ubNumEPCs++;
				//Also record the EPC's slot ID incase we later build a string using the EPC's name.
				gbPotentiallyAbandonedEPCSlotID = (INT8)cnt;
				if( AM_A_ROBOT( pSoldier ) && !CanRobotBeControlled( pSoldier ) )
				{
					gfRobotWithoutControllerAttemptingTraversal = TRUE;
					ubNumControllableMercs--;
					continue;
				}
			}
			else
			{
				ubNumMercs++;
			}

			if ( SoldierOKForSectorExit( pSoldier, bExitDirection, usAdditionalData ) )
			{
				fAtLeastOneMercControllable++;

				if ( cnt == gusSelectedSoldier )
				{
					fOnlySelectedGuy = TRUE;
				}
			}
			else
			{
				GROUP *pGroup;

				// ATE: Dont's assume exit grids here...
				if ( bExitDirection != -1 )
				{
					//Now, determine if this is a valid path.
					pGroup = GetGroup( pValidSoldier->ubGroupID );
					AssertMsg( pGroup, String( "%S is not in a valid group (pSoldier->ubGroupID is %d)",pValidSoldier->name, pValidSoldier->ubGroupID) );
					if( !gbWorldSectorZ )
					{
						*puiTraverseTimeInMinutes = GetSectorMvtTimeForGroup( (UINT8)SECTOR( pGroup->ubSectorX, pGroup->ubSectorY ), bExitDirection, pGroup );
					}
					else if( gbWorldSectorZ > 1 )
					{ //We are attempting to traverse in an underground environment.  We need to use a complete different
						//method.  When underground, all sectors are instantly adjacent.
						*puiTraverseTimeInMinutes = UndergroundTacticalTraversalTime( bExitDirection );
					}
					if( *puiTraverseTimeInMinutes == 0xffffffff )
					{
						gfInvalidTraversal = TRUE;
						return FALSE;
					}
				}
				else
				{
					*puiTraverseTimeInMinutes = 0; //exit grid travel is instantaneous
				}
			}
		}
	}

	// If we are here, at least one guy is controllable in this sector, at least he can go!
	if( fAtLeastOneMercControllable )
	{
		ubPlayerControllableMercsInSquad = (UINT8)NumberOfPlayerControllableMercsInSquad( MercPtrs[ gusSelectedSoldier ]->bAssignment );
		if( fAtLeastOneMercControllable <= ubPlayerControllableMercsInSquad )
		{ //if the selected merc is an EPC and we can only leave with that merc, then prevent it
			//as EPCs aren't allowed to leave by themselves.  Instead of restricting this in the 
			//exiting sector gui, we restrict it by explaining it with a message box.
			if ( AM_AN_EPC( MercPtrs[ gusSelectedSoldier ] ) )
			{
				if( AM_A_ROBOT( pSoldier ) && !CanRobotBeControlled( pSoldier ) )
				{
					//gfRobotWithoutControllerAttemptingTraversal = TRUE;
					return FALSE;
				}
				else if( fAtLeastOneMercControllable < ubPlayerControllableMercsInSquad || fAtLeastOneMercControllable == 1 )
				{
					gfLoneEPCAttemptingTraversal = TRUE;
					return FALSE;
				}
			}
			else
			{	//We previously counted the number of EPCs and mercs, and if the selected merc is not an EPC and there are no
				//other mercs in the squad able to escort the EPCs, we will prohibit this merc from tactically traversing.
				if( ubNumEPCs && ubNumMercs == 1 && fAtLeastOneMercControllable < ubPlayerControllableMercsInSquad )
				{
					gubLoneMercAttemptingToAbandonEPCs = ubNumEPCs;
					return FALSE;
				}
			}
		}
		if ( bExitDirection != -1 )
		{
			GROUP *pGroup;
			//Now, determine if this is a valid path.
			pGroup = GetGroup( pValidSoldier->ubGroupID );
			AssertMsg( pGroup, String( "%S is not in a valid group (pSoldier->ubGroupID is %d)",pValidSoldier->name, pValidSoldier->ubGroupID) );
			if( !gbWorldSectorZ )
			{
				*puiTraverseTimeInMinutes = GetSectorMvtTimeForGroup( (UINT8)SECTOR( pGroup->ubSectorX, pGroup->ubSectorY ), bExitDirection, pGroup );
			}
			else if( gbWorldSectorZ > 0 )
			{ //We are attempting to traverse in an underground environment.  We need to use a complete different
				//method.  When underground, all sectors are instantly adjacent.
				*puiTraverseTimeInMinutes = UndergroundTacticalTraversalTime( bExitDirection );
			}
			if( *puiTraverseTimeInMinutes == 0xffffffff )
			{
				gfInvalidTraversal = TRUE;
				ubReturnVal = FALSE;
			}
			else
			{
				ubReturnVal = TRUE;
			}
		}
		else
		{
			ubReturnVal = TRUE;
			*puiTraverseTimeInMinutes = 0; //exit grid travel is instantaneous
		}
	}

	if ( ubReturnVal )
	{
		// Default to FALSE again, until we see that we have
		ubReturnVal = FALSE;

		if ( fAtLeastOneMercControllable )
		{
			// Do we contain the selected guy?
			if ( fOnlySelectedGuy )
			{
				ubReturnVal = 1;
			}
			// Is the whole squad able to go here?
			if ( fAtLeastOneMercControllable == ubPlayerControllableMercsInSquad )
			{
				ubReturnVal = 2;
			}
		}
	}

	return( ubReturnVal );
}


void SetupNewStrategicGame( )
{
	INT16 sSectorX, sSectorY;

	// Set all sectors as enemy controlled
	for ( sSectorX = 0; sSectorX < MAP_WORLD_X; sSectorX++ )
	{
		for ( sSectorY = 0; sSectorY < MAP_WORLD_Y; sSectorY++ )
		{
			StrategicMap[ CALCULATE_STRATEGIC_INDEX( sSectorX, sSectorY ) ].fEnemyControlled = TRUE;
		}
	}

	//Ja25
	// Make the initial sector free of enemies
	StrategicMap[ CALCULATE_STRATEGIC_INDEX( JA2_5_START_SECTOR_X, JA2_5_START_SECTOR_Y ) ].fEnemyControlled = FALSE;


	//Initialize the game time
	InitNewGameClock();
	//Remove all events
	DeleteAllStrategicEvents();

	//Set up all events that get processed daily...
	//.............................................
	BuildDayLightLevels();
	// Check for quests each morning
	AddEveryDayStrategicEvent( EVENT_CHECKFORQUESTS, QUEST_CHECK_EVENT_TIME, 0 );
	// Some things get updated in the very early morning
	AddEveryDayStrategicEvent( EVENT_DAILY_EARLY_MORNING_EVENTS, EARLY_MORNING_TIME, 0 );

	//Daily Update BobbyRay Inventory
	//Ja25:  BobbyRay stuff is NOT being called, only the arms dealer info, which just happens to be inthe same function
	AddEveryDayStrategicEvent( EVENT_DAILY_UPDATE_BOBBY_RAY_INVENTORY, BOBBYRAY_UPDATE_TIME, 0 );

	//Daily Update of the M.E.R.C. site.
	AddEveryDayStrategicEvent( EVENT_DAILY_UPDATE_OF_MERC_SITE, 0, 0 );

/*
Ja25:  No insurance for mercs
	//Daily update of insured mercs
	AddEveryDayStrategicEvent( EVENT_HANDLE_INSURED_MERCS, INSURANCE_UPDATE_TIME,	0 );
*/
	//Daily update of mercs
	AddEveryDayStrategicEvent( EVENT_MERC_DAILY_UPDATE, 0, 0 );

/*
JA25: There is no mines
	// Daily mine production processing events
	AddEveryDayStrategicEvent( EVENT_SETUP_MINE_INCOME, 0, 0 );
*/

/*
Ja25 no town opinions
	// Daily merc reputation processing events
	AddEveryDayStrategicEvent( EVENT_SETUP_TOWN_OPINION, 0, 0 );
*/

/*
Ja25:  No enrico mail
	// Daily checks for E-mail from Enrico
	AddEveryDayStrategicEvent( EVENT_ENRICO_MAIL, ENRICO_MAIL_TIME , 0 );
*/

	// Hourly update of all sorts of things
	AddPeriodStrategicEvent( EVENT_HOURLY_UPDATE, 60, 0 );
	AddPeriodStrategicEvent( EVENT_QUARTER_HOUR_UPDATE, 15, 0 );

	#ifdef JA2DEMO
		AddPeriodStrategicEventWithOffset( EVENT_MINUTE_UPDATE, 60, 475, 0 );
	#endif

	//Clear any possible battle locator
	gfBlitBattleSectorLocator = FALSE;




	StrategicTurnsNewGame( );
}


// a -1 will be returned upon failure
INT8 GetSAMIdFromSector( INT16 sSectorX, INT16 sSectorY, INT8 bSectorZ )
{
	INT8 bCounter = 0;
	INT16 sSectorValue = 0;
		
	// check if valid sector
	if( bSectorZ != 0 )
	{
		return( -1 );
	}

	// get the sector value
	sSectorValue = SECTOR( sSectorX, sSectorY );

	// run through list of sam sites
	for( bCounter = 0; bCounter < 4; bCounter++ )
	{
		if( pSamList[ bCounter ] == sSectorValue )
		{
			return( bCounter );
		}
	}


	return( -1 );
}


BOOLEAN CanGoToTacticalInSector( INT16 sX, INT16 sY, UINT8 ubZ )
{
	INT32 cnt;
	SOLDIERTYPE *pSoldier;

	// if not a valid sector
	if( ( sX < 1 ) || ( sX > 16 ) || ( sY < 1 ) || ( sY > 16 ) || ( ubZ > 3 ) )
	{
		return( FALSE );
	}


	cnt = gTacticalStatus.Team[ gbPlayerNum ].bFirstID;

  // look for all living, fighting mercs on player's team.  Robot and EPCs qualify!
  for ( pSoldier = MercPtrs[ cnt ]; cnt <= gTacticalStatus.Team[ gbPlayerNum ].bLastID; cnt++, pSoldier++)
	{
		// ARM: now allows loading of sector with all mercs below OKLIFE as long as they're alive
		if ( ( pSoldier->bActive && pSoldier->bLife ) && !( pSoldier->uiStatusFlags & SOLDIER_VEHICLE ) &&
				 ( pSoldier->bAssignment != IN_TRANSIT ) && ( pSoldier->bAssignment != ASSIGNMENT_POW ) &&
				 ( pSoldier->bAssignment != ASSIGNMENT_DEAD ) && !SoldierAboardAirborneHeli( pSoldier ) )
		{
			if ( !pSoldier->fBetweenSectors && pSoldier->sSectorX == sX && pSoldier->sSectorY == sY && pSoldier->bSectorZ == ubZ )
			{
				return( TRUE );
			}
		}
	}

	return( FALSE );
}


INT32 GetNumberOfSAMSitesUnderPlayerControl( void )
{
	INT32 iNumber = 0, iCounter = 0;

	// if the sam site is under player control, up the number
	for( iCounter = 0; iCounter < NUMBER_OF_SAMS; iCounter++ )
	{
		if( StrategicMap[ SECTOR_INFO_TO_STRATEGIC_INDEX( pSamList[ iCounter ] ) ].fEnemyControlled == FALSE )
		{
			iNumber++;
		}
	}

	return( iNumber );
}

INT32 SAMSitesUnderPlayerControl( INT16 sX, INT16 sY )
{
	BOOLEAN fSamSiteUnderControl = FALSE;


	// is this sector a SAM sector?
	if( IsThisSectorASAMSector( sX, sY, 0 ) == TRUE )
	{
		// is it under control by the player
		if( StrategicMap[ CALCULATE_STRATEGIC_INDEX( sX , sY ) ].fEnemyControlled == FALSE )
		{
			// yes
			fSamSiteUnderControl = TRUE;
		}
	}	
		
	return( fSamSiteUnderControl );
}


void UpdateAirspaceControl( void )
{
	INT32 iCounterA = 0, iCounterB = 0;
	UINT8 ubControllingSAM;
	StrategicMapElement *pSAMStrategicMap = NULL;
	BOOLEAN fEnemyControlsAir;


	for( iCounterA = 1; iCounterA < ( INT32 )( MAP_WORLD_X - 1 ); iCounterA++ )
	{
		for( iCounterB = 1; iCounterB < ( INT32 )( MAP_WORLD_Y - 1 ); iCounterB++ )
		{
			// IMPORTANT: B and A are reverse here, since the table is stored transposed
			ubControllingSAM = ubSAMControlledSectors[ iCounterB ][ iCounterA ];

			if ( ( ubControllingSAM >= 1 ) && ( ubControllingSAM <= NUMBER_OF_SAMS ) )
			{
				pSAMStrategicMap = &( StrategicMap[ SECTOR_INFO_TO_STRATEGIC_INDEX( pSamList[ ubControllingSAM - 1 ] ) ] );

				// if the enemies own the controlling SAM site, and it's in working condition
				if( ( pSAMStrategicMap->fEnemyControlled ) && ( pSAMStrategicMap->bSAMCondition >= MIN_CONDITION_FOR_SAM_SITE_TO_WORK ) )
				{
					fEnemyControlsAir = TRUE;
				}
				else
				{
					fEnemyControlsAir = FALSE;
				}
			}
			else
			{
				// no controlling SAM site
				fEnemyControlsAir = FALSE;
			}

			StrategicMap[ CALCULATE_STRATEGIC_INDEX( iCounterA, iCounterB ) ].fEnemyAirControlled = fEnemyControlsAir;
		}
	}


	// check if currently selected arrival sector still has secure airspace

	// if it's not enemy air controlled
	if ( StrategicMap[ CALCULATE_STRATEGIC_INDEX( gsMercArriveSectorX, gsMercArriveSectorY ) ].fEnemyAirControlled == TRUE )
	{
		// NOPE!
		CHAR16 sMsgString[ 256 ], sMsgSubString1[ 64 ], sMsgSubString2[ 64 ];

		// get the name of the old sector
		GetSectorIDString( gsMercArriveSectorX, gsMercArriveSectorY, 0, sMsgSubString1, FALSE );

		// move the landing zone over to Omerta
		gsMercArriveSectorX = JA2_5_START_SECTOR_X;
		gsMercArriveSectorY = JA2_5_START_SECTOR_Y;

		// get the name of the new sector
		GetSectorIDString( gsMercArriveSectorX, gsMercArriveSectorY, 0, sMsgSubString2, FALSE );

		// now build the string
		swprintf( sMsgString, pBullseyeStrings[ 4 ], sMsgSubString1, sMsgSubString2 );

		// confirm the change with overlay message
		DoScreenIndependantMessageBox( sMsgString, MSG_BOX_FLAG_OK, NULL );

		// update position of bullseye
		fMapPanelDirty = TRUE;

		// update destination column for any mercs in transit
		fTeamPanelDirty = TRUE;
	}


	// ARM: airspace control now affects refueling site availability, so update that too with every change!
	UpdateRefuelSiteAvailability( );
}


BOOLEAN IsThereAFunctionalSAMSiteInSector( INT16 sSectorX, INT16 sSectorY, INT8 bSectorZ )
{
	if( IsThisSectorASAMSector( sSectorX, sSectorY, bSectorZ ) == FALSE )
	{
		return( FALSE );
	}

	if( StrategicMap[ CALCULATE_STRATEGIC_INDEX( sSectorX, sSectorY ) ].bSAMCondition < MIN_CONDITION_FOR_SAM_SITE_TO_WORK )
	{
		return( FALSE );
	}

	return( TRUE );
}

BOOLEAN IsThisSectorASAMSector( INT16 sSectorX, INT16 sSectorY, INT8 bSectorZ )
{

	// is the sector above ground?
	if( bSectorZ != 0 )
	{
		return( FALSE );
	}

	if( ( SAM_1_X == sSectorX ) && ( SAM_1_Y == sSectorY ) )
	{
		return( TRUE );
	}
	else 	if( ( SAM_2_X == sSectorX ) && ( SAM_2_Y == sSectorY ) )
	{
		return( TRUE );
	}
	else 	if( ( SAM_3_X == sSectorX ) && ( SAM_3_Y == sSectorY ) )
	{
		return( TRUE );
	}
	else 	if( ( SAM_4_X == sSectorX ) && ( SAM_4_Y == sSectorY ) )
	{
		return( TRUE );
	}

	return ( FALSE );
}


// is this sector part of the town?
BOOLEAN SectorIsPartOfTown( INT8 bTownId, INT16 sSectorX, INT16 sSectorY ) 
{
	if( StrategicMap[CALCULATE_STRATEGIC_INDEX( sSectorX, sSectorY ) ].bNameId == bTownId )
	{
		// is in the town
		return ( TRUE );
	}

	// not in the town
	return ( FALSE );
}


BOOLEAN SaveStrategicInfoToSavedFile( HWFILE hFile )
{
	UINT32		uiNumBytesWritten=0;
	UINT32		uiSize = sizeof( StrategicMapElement ) * ( MAP_WORLD_X * MAP_WORLD_Y );

	
	// Save the strategic map information
	FileWrite( hFile, StrategicMap, uiSize, &uiNumBytesWritten );
	if( uiNumBytesWritten != uiSize)
	{
		return(FALSE);
	}

	// Save the Sector Info
	uiSize = sizeof( SECTORINFO ) * 256;
	FileWrite( hFile, SectorInfo, uiSize, &uiNumBytesWritten );
	if( uiNumBytesWritten != uiSize)
	{
		return(FALSE);
	}

	// Save the SAM Controlled Sector Information
	uiSize = MAP_WORLD_X * MAP_WORLD_Y;
/*
	FileWrite( hFile, ubSAMControlledSectors, uiSize, &uiNumBytesWritten );
	if( uiNumBytesWritten != uiSize)
	{
		return(FALSE);
	}
*/
	FileSeek( hFile, uiSize, FILE_SEEK_FROM_CURRENT );

/*
JA25: no orta
	// Save the fFoundOrta
	FileWrite( hFile, &fFoundOrta, sizeof( BOOLEAN ), &uiNumBytesWritten );
	if( uiNumBytesWritten != sizeof( BOOLEAN ) )
	{
		return(FALSE);
	}
*/


	return( TRUE );
}



BOOLEAN LoadStrategicInfoFromSavedFile( HWFILE hFile )
{
	UINT32		uiNumBytesRead=0;
	UINT32		uiSize = sizeof( StrategicMapElement ) * ( MAP_WORLD_X * MAP_WORLD_Y );

	
	// Load the strategic map information
	FileRead( hFile, StrategicMap, uiSize, &uiNumBytesRead );
	if( uiNumBytesRead != uiSize)
	{
		return(FALSE);
	}

	// Load the Sector Info
	uiSize = sizeof( SECTORINFO ) * 256;
	FileRead( hFile, SectorInfo, uiSize, &uiNumBytesRead );
	if( uiNumBytesRead != uiSize)
	{
		return(FALSE);
	}

	// Load the SAM Controlled Sector Information
	uiSize = MAP_WORLD_X * MAP_WORLD_Y;
/*
	FileRead( hFile, ubSAMControlledSectors, uiSize, &uiNumBytesRead );
	if( uiNumBytesRead != uiSize)
	{
		return(FALSE);
	}
*/
	FileSeek( hFile, uiSize, FILE_SEEK_FROM_CURRENT );

/*
JA25: no orta
	// Load the fFoundOrta
	FileRead( hFile, &fFoundOrta, sizeof( BOOLEAN ), &uiNumBytesRead );
	if( uiNumBytesRead != sizeof( BOOLEAN ) )
	{
		return(FALSE);
	}
*/

	return( TRUE );
}


INT16 PickGridNoNearestEdge( SOLDIERTYPE *pSoldier, UINT8 ubTacticalDirection )
{
	INT16			sGridNo, sStartGridNo, sOldGridNo;
	INT8			bOdd = 1, bOdd2 = 1;
	UINT8			bAdjustedDist = 0;
	UINT32		cnt;

	switch( ubTacticalDirection )
	{

		case EAST:

			sGridNo				 = pSoldier->sGridNo;
			sStartGridNo	 = pSoldier->sGridNo;
			sOldGridNo     = pSoldier->sGridNo;

			// Move directly to the right!
			while( GridNoOnVisibleWorldTile( sGridNo ) )
			{
				sOldGridNo = sGridNo;

				if ( bOdd )
				{
					sGridNo -= WORLD_COLS;
				}
				else
				{
					sGridNo++;
				}
				
				bOdd = (INT8)!bOdd;
			}

			sGridNo			 = sOldGridNo;
			sStartGridNo = sOldGridNo;

			do
			{
				// OK, here we go back one, check for OK destination...
				if ( NewOKDestination( pSoldier, sGridNo, TRUE, pSoldier->bLevel ) && FindBestPath( pSoldier, sGridNo, pSoldier->bLevel, WALKING, NO_COPYROUTE, PATH_THROUGH_PEOPLE ) )
				{
					return( sGridNo );
				}

				// If here, try another place!
				// ( alternate up/down )
				if ( bOdd2 ) 
				{
					bAdjustedDist++;		
					
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo - WORLD_COLS - 1);
					}
				}
				else
				{
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo + WORLD_COLS + 1);
					}
				}

				bOdd2 = (INT8)(!bOdd2);

			} while( TRUE );

			break;

		case WEST:

			sGridNo				 = pSoldier->sGridNo;
			sStartGridNo	 = pSoldier->sGridNo;
			sOldGridNo     = pSoldier->sGridNo;

			// Move directly to the left!
			while( GridNoOnVisibleWorldTile( sGridNo ) )
			{
				sOldGridNo = sGridNo;

				if ( bOdd )
				{
					sGridNo += WORLD_COLS;
				}
				else
				{
					sGridNo--;
				}
				
				bOdd = (INT8)!bOdd;
			}

			sGridNo			 = sOldGridNo;
			sStartGridNo = sOldGridNo;

			do
			{
				// OK, here we go back one, check for OK destination...
				if ( NewOKDestination( pSoldier, sGridNo, TRUE, pSoldier->bLevel ) && FindBestPath( pSoldier, sGridNo, pSoldier->bLevel, WALKING, NO_COPYROUTE, PATH_THROUGH_PEOPLE ) )
				{
					return( sGridNo );
				}

				// If here, try another place!
				// ( alternate up/down )
				if ( bOdd2 ) 
				{
					bAdjustedDist++;		
					
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo - WORLD_COLS - 1);
					}
				}
				else
				{
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo + WORLD_COLS + 1);
					}
				}

				bOdd2 = (INT8)(!bOdd2);

			} while( TRUE );

			break;

		case NORTH:

			sGridNo				 = pSoldier->sGridNo;
			sStartGridNo	 = pSoldier->sGridNo;
			sOldGridNo     = pSoldier->sGridNo;

			// Move directly to the left!
			while( GridNoOnVisibleWorldTile( sGridNo ) )
			{
				sOldGridNo = sGridNo;

				if ( bOdd )
				{
					sGridNo -= WORLD_COLS;
				}
				else
				{
					sGridNo--;
				}
				
				bOdd = (INT8)(!bOdd);
			}

			sGridNo			 = sOldGridNo;
			sStartGridNo = sOldGridNo;

			do
			{
				// OK, here we go back one, check for OK destination...
				if ( NewOKDestination( pSoldier, sGridNo, TRUE, pSoldier->bLevel ) && FindBestPath( pSoldier, sGridNo, pSoldier->bLevel, WALKING, NO_COPYROUTE, PATH_THROUGH_PEOPLE ) )
				{
					return( sGridNo );
				}

				// If here, try another place!
				// ( alternate left/right )
				if ( bOdd2 ) 
				{
					bAdjustedDist++;		
					
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo + WORLD_COLS - 1);
					}
				}
				else
				{
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo - WORLD_COLS + 1);
					}
				}

				bOdd2 = (INT8)(!bOdd2);

			} while( TRUE );

			break;

		case SOUTH:

			sGridNo				 = pSoldier->sGridNo;
			sStartGridNo	 = pSoldier->sGridNo;
			sOldGridNo     = pSoldier->sGridNo;

			// Move directly to the left!
			while( GridNoOnVisibleWorldTile( sGridNo ) )
			{
				sOldGridNo = sGridNo;

				if ( bOdd )
				{
					sGridNo += WORLD_COLS;
				}
				else
				{
					sGridNo++;
				}
				
				bOdd = (INT8)(!bOdd);
			}

			sGridNo			 = sOldGridNo;
			sStartGridNo = sOldGridNo;

			do
			{
				// OK, here we go back one, check for OK destination...
				if ( NewOKDestination( pSoldier, sGridNo, TRUE, pSoldier->bLevel ) && FindBestPath( pSoldier, sGridNo, pSoldier->bLevel, WALKING, NO_COPYROUTE, PATH_THROUGH_PEOPLE ) )
				{
					return( sGridNo );
				}

				// If here, try another place!
				// ( alternate left/right )
				if ( bOdd2 ) 
				{
					bAdjustedDist++;		
					
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo + WORLD_COLS - 1);
					}
				}
				else
				{
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo - WORLD_COLS + 1);
					}
				}

				bOdd2 = (INT8)(!bOdd2);

			} while( TRUE );

			break;

	}

	return( NOWHERE );
}


void AdjustSoldierPathToGoOffEdge( SOLDIERTYPE *pSoldier, INT16 sEndGridNo, UINT8 ubTacticalDirection )
{
	INT16 sNewGridNo, sTempGridNo;
	INT32	iLoop;

	// will this path segment actually take us to our desired destination in the first place?
	if (pSoldier->usPathDataSize + 2 > MAX_PATH_LIST_SIZE)
	{

		sTempGridNo = pSoldier->sGridNo;

		for (iLoop = 0; iLoop < pSoldier->usPathDataSize; iLoop++)
		{
			sTempGridNo += (INT16)DirectionInc( pSoldier->usPathingData[ iLoop ] );
		}

		if (sTempGridNo == sEndGridNo)
		{
			// we can make it, but there isn't enough path room for the two steps required.
			// truncate our path so there's guaranteed the merc will have to generate another
			// path later on...	
			pSoldier->usPathDataSize -= 4;
			return;
		}
		else
		{
			// can't even make it there with these 30 tiles of path, abort...
			return;
		}
	}

	switch( ubTacticalDirection )
	{
		case EAST:

			sNewGridNo = NewGridNo( (UINT16)sEndGridNo, (UINT16)DirectionInc( (UINT8)NORTHEAST ) );

			if ( OutOfBounds( sEndGridNo, sNewGridNo ) )
			{
				return;
			}

			pSoldier->usPathingData[ pSoldier->usPathDataSize ] = NORTHEAST;
			pSoldier->usPathDataSize++;
			pSoldier->sFinalDestination = sNewGridNo;
			pSoldier->usActionData = sNewGridNo;

			sTempGridNo = NewGridNo( (UINT16)sNewGridNo, (UINT16)DirectionInc( (UINT8)NORTHEAST ) );

			if ( OutOfBounds( sNewGridNo, sTempGridNo ) )
			{
				return;
			}
			sNewGridNo = sTempGridNo;

			pSoldier->usPathingData[ pSoldier->usPathDataSize ] = NORTHEAST;
			pSoldier->usPathDataSize++;
			pSoldier->sFinalDestination = sNewGridNo;
			pSoldier->usActionData = sNewGridNo;

			break;

		case WEST:

			sNewGridNo = NewGridNo( (UINT16)sEndGridNo, (UINT16)DirectionInc( (UINT8)SOUTHWEST ) );

			if ( OutOfBounds( sEndGridNo, sNewGridNo ) )
			{
				return;
			}

			pSoldier->usPathingData[ pSoldier->usPathDataSize ] = SOUTHWEST;
			pSoldier->usPathDataSize++;
			pSoldier->sFinalDestination = sNewGridNo;
			pSoldier->usActionData = sNewGridNo;

			sTempGridNo = NewGridNo( (UINT16)sNewGridNo, (UINT16)DirectionInc( (UINT8)SOUTHWEST ) );

			if ( OutOfBounds( sNewGridNo, sTempGridNo ) )
			{
				return;
			}
			sNewGridNo = sTempGridNo;

			pSoldier->usPathingData[ pSoldier->usPathDataSize ] = SOUTHWEST;
			pSoldier->usPathDataSize++;
			pSoldier->sFinalDestination = sNewGridNo;
			pSoldier->usActionData = sNewGridNo;
			break;

		case NORTH:

			sNewGridNo = NewGridNo( (UINT16)sEndGridNo, (UINT16)DirectionInc( (UINT8)NORTHWEST ) );

			if ( OutOfBounds( sEndGridNo, sNewGridNo ) )
			{
				return;
			}

			pSoldier->usPathingData[ pSoldier->usPathDataSize ] = NORTHWEST;
			pSoldier->usPathDataSize++;
			pSoldier->sFinalDestination = sNewGridNo;
			pSoldier->usActionData = sNewGridNo;

			sTempGridNo = NewGridNo( (UINT16)sNewGridNo, (UINT16)DirectionInc( (UINT8)NORTHWEST ) );

			if ( OutOfBounds( sNewGridNo, sTempGridNo ) )
			{
				return;
			}
			sNewGridNo = sTempGridNo;

			pSoldier->usPathingData[ pSoldier->usPathDataSize ] = NORTHWEST;
			pSoldier->usPathDataSize++;
			pSoldier->sFinalDestination = sNewGridNo;
			pSoldier->usActionData = sNewGridNo;

			break;

		case SOUTH:

			sNewGridNo = NewGridNo( (UINT16)sEndGridNo, (UINT16)DirectionInc( (UINT8)SOUTHEAST ) );

			if ( OutOfBounds( sEndGridNo, sNewGridNo ) )
			{
				return;
			}

			pSoldier->usPathingData[ pSoldier->usPathDataSize ] = SOUTHEAST;
			pSoldier->usPathDataSize++;
			pSoldier->sFinalDestination = sNewGridNo;
			pSoldier->usActionData = sNewGridNo;

			sTempGridNo = NewGridNo( (UINT16)sNewGridNo, (UINT16)DirectionInc( (UINT8)SOUTHEAST ) );

			if ( OutOfBounds( sNewGridNo, sTempGridNo ) )
			{
				return;
			}
			sNewGridNo = sTempGridNo;

			pSoldier->usPathingData[ pSoldier->usPathDataSize ] = SOUTHEAST;
			pSoldier->usPathDataSize++;
			pSoldier->sFinalDestination = sNewGridNo;
			pSoldier->usActionData = sNewGridNo;
			break;

	}
}

INT16 PickGridNoToWalkIn( SOLDIERTYPE *pSoldier, UINT8 ubInsertionDirection, UINT32 *puiNumAttempts )
{
	INT16			sGridNo, sStartGridNo, sOldGridNo;
	INT8			bOdd = 1, bOdd2 = 1;
	UINT8			bAdjustedDist = 0;
	UINT32		cnt;

	*puiNumAttempts = 0;

	switch( ubInsertionDirection )
	{
		// OK, we're given a direction on visible map, let's look for the first oone
		// we find that is just on the start of visible map...
		case INSERTION_CODE_WEST:

			sGridNo				 = (INT16)pSoldier->sGridNo;
			sStartGridNo	 = (INT16)pSoldier->sGridNo;
			sOldGridNo     = (INT16)pSoldier->sGridNo;

			// Move directly to the left!
			while( GridNoOnVisibleWorldTile( sGridNo ) )
			{
				sOldGridNo = sGridNo;

				if ( bOdd )
				{
					sGridNo += WORLD_COLS;
				}
				else
				{
					sGridNo--;
				}
				
				bOdd = (INT8)(!bOdd);
			}

			sGridNo			 = sOldGridNo;
			sStartGridNo = sOldGridNo;

			while( *puiNumAttempts < MAX_ATTEMPTS )
			{
				(*puiNumAttempts)++;
				// OK, here we go back one, check for OK destination...
				if ( ( gTacticalStatus.uiFlags & IGNORE_ALL_OBSTACLES ) || ( NewOKDestination( pSoldier, sGridNo, TRUE, pSoldier->bLevel ) && FindBestPath( pSoldier, sGridNo, pSoldier->bLevel, WALKING, NO_COPYROUTE, PATH_THROUGH_PEOPLE ) ) )
				{
					return( sGridNo );
				}

				// If here, try another place!
				// ( alternate up/down )
				if ( bOdd2 ) 
				{
					bAdjustedDist++;		
					
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo - WORLD_COLS - 1);
					}
				}
				else
				{
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo + WORLD_COLS + 1);
					}
				}

				bOdd2 = (INT8)(!bOdd2);

			}
			return NOWHERE;

		case INSERTION_CODE_EAST:

			sGridNo				 = (INT16)pSoldier->sGridNo;
			sStartGridNo	 = (INT16)pSoldier->sGridNo;
			sOldGridNo     = (INT16)pSoldier->sGridNo;

			// Move directly to the right!
			while( GridNoOnVisibleWorldTile( sGridNo ) )
			{
				sOldGridNo = sGridNo;

				if ( bOdd )
				{
					sGridNo -= WORLD_COLS;
				}
				else
				{
					sGridNo++;
				}
				
				bOdd = (INT8)(!bOdd);
			}

			sGridNo			 = sOldGridNo;
			sStartGridNo = sOldGridNo;

			while( *puiNumAttempts < MAX_ATTEMPTS )
			{
				(*puiNumAttempts)++;
				// OK, here we go back one, check for OK destination...
				if ( ( gTacticalStatus.uiFlags & IGNORE_ALL_OBSTACLES ) || ( NewOKDestination( pSoldier, sGridNo, TRUE, pSoldier->bLevel ) && FindBestPath( pSoldier, sGridNo, pSoldier->bLevel, WALKING, NO_COPYROUTE, PATH_THROUGH_PEOPLE ) ) )
				{
					return( sGridNo );
				}

				// If here, try another place!
				// ( alternate up/down )
				if ( bOdd2 ) 
				{
					bAdjustedDist++;		
					
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo - WORLD_COLS - 1);
					}
				}
				else
				{
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo + WORLD_COLS + 1);
					}
				}

				bOdd2 = (INT8)(!bOdd2);

			}
			return NOWHERE;

		case INSERTION_CODE_NORTH:

			sGridNo				 = (INT16)pSoldier->sGridNo;
			sStartGridNo	 = (INT16)pSoldier->sGridNo;
			sOldGridNo     = (INT16)pSoldier->sGridNo;

			// Move directly to the up!
			while( GridNoOnVisibleWorldTile( sGridNo ) )
			{
				sOldGridNo = sGridNo;

				if ( bOdd )
				{
					sGridNo -= WORLD_COLS;
				}
				else
				{
					sGridNo--;
				}
				
				bOdd = (INT8)(!bOdd);
			}

			sGridNo			 = sOldGridNo;
			sStartGridNo = sOldGridNo;

			while( *puiNumAttempts < MAX_ATTEMPTS )
			{
				(*puiNumAttempts)++;
				// OK, here we go back one, check for OK destination...
				if ( ( gTacticalStatus.uiFlags & IGNORE_ALL_OBSTACLES ) || ( NewOKDestination( pSoldier, sGridNo, TRUE, pSoldier->bLevel ) && FindBestPath( pSoldier, sGridNo, pSoldier->bLevel, WALKING, NO_COPYROUTE, PATH_THROUGH_PEOPLE ) ) )
				{
					return( sGridNo );
				}

				// If here, try another place!
				// ( alternate left/right )
				if ( bOdd2 ) 
				{
					bAdjustedDist++;		
					
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo - WORLD_COLS + 1);
					}
				}
				else
				{
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo + WORLD_COLS - 1);
					}
				}

				bOdd2 = (INT8)(!bOdd2);

			}
			return NOWHERE;

		case INSERTION_CODE_SOUTH:

			sGridNo				 = (INT16)pSoldier->sGridNo;
			sStartGridNo	 = (INT16)pSoldier->sGridNo;
			sOldGridNo     = (INT16)pSoldier->sGridNo;

			// Move directly to the down!
			while( GridNoOnVisibleWorldTile( sGridNo ) )
			{
				sOldGridNo = sGridNo;

				if ( bOdd )
				{
					sGridNo += WORLD_COLS;
				}
				else
				{
					sGridNo++;
				}
				
				bOdd = (INT8)(!bOdd);
			}

			sGridNo			 = sOldGridNo;
			sStartGridNo = sOldGridNo;

			while( *puiNumAttempts < MAX_ATTEMPTS )
			{
				(*puiNumAttempts)++;
				// OK, here we go back one, check for OK destination...
				if ( ( gTacticalStatus.uiFlags & IGNORE_ALL_OBSTACLES ) || ( NewOKDestination( pSoldier, sGridNo, TRUE, pSoldier->bLevel ) && FindBestPath( pSoldier, sGridNo, pSoldier->bLevel, WALKING, NO_COPYROUTE, PATH_THROUGH_PEOPLE ) ) )
				{
					return( sGridNo );
				}

				// If here, try another place!
				// ( alternate left/right )
				if ( bOdd2 ) 
				{
					bAdjustedDist++;		
					
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo - WORLD_COLS + 1);
					}
				}
				else
				{
					sGridNo = sStartGridNo;

					for ( cnt = 0; cnt < bAdjustedDist; cnt++ )
					{
						sGridNo = (INT16)(sGridNo + WORLD_COLS - 1);
					}
				}

				bOdd2 = (INT8)(!bOdd2);

			}
			return NOWHERE;

	}

	//Unhandled exit
	*puiNumAttempts = 0;

	return( NOWHERE );
}


void GetLoadedSectorString( UINT16 *pString )
{
	if( !gfWorldLoaded )
	{
		swprintf( pString, L"" );
		return;
	}
	if( gbWorldSectorZ )
	{
		swprintf( pString, L"%c%d_b%d", gWorldSectorY + 'A' - 1, gWorldSectorX, gbWorldSectorZ );
	}
	else if( !gbWorldSectorZ )
	{
		swprintf( pString, L"%c%d", gWorldSectorY + 'A' - 1, gWorldSectorX );
	}
}

/*
void HandleSlayDailyEvent( void )
{
	SOLDIERTYPE *pSoldier = NULL;

	// grab slay
	pSoldier = FindSoldierByProfileID( SLAY, TRUE );

	if( pSoldier == NULL )
	{
		return;
	}

	// valid soldier?
	if( ( pSoldier->bActive == FALSE ) || ( pSoldier->bLife == 0 ) || ( pSoldier->bAssignment == IN_TRANSIT ) ||( pSoldier->bAssignment == ASSIGNMENT_POW ) )
	{
		// no
		return;
	}

	// ATE: This function is used to check for the ultimate last day SLAY can stay for
	// he may decide to leave randomly while asleep...
	//if the user hasnt renewed yet, and is still leaving today
	if( ( pSoldier->iEndofContractTime /1440 ) <= (INT32)GetWorldDay( ) )
	{
		pSoldier->ubLeaveHistoryCode = HISTORY_SLAY_MYSTERIOUSLY_LEFT;
		TacticalCharacterDialogueWithSpecialEvent( pSoldier, 0, DIALOGUE_SPECIAL_EVENT_CONTRACT_ENDING_NO_ASK_EQUIP, 0, 0 );
	}
}

*/

BOOLEAN IsSectorDesert( INT16 sSectorX, INT16 sSectorY )
{
	if ( SectorInfo[ SECTOR(sSectorX, sSectorY) ].ubTraversability[ THROUGH_STRATEGIC_MOVE ] == SAND )
	{
		// desert
		return( TRUE );
	}
	else
	{
		return( FALSE );
	}
}



BOOLEAN HandleDefiniteUnloadingOfWorld( UINT8 ubUnloadCode )
{
	INT32 i;

	// clear tactical queue
	ClearEventQueue();	

	// ATE: End all bullets....
	DeleteAllBullets();	

	// End all physics objects...
	RemoveAllPhysicsObjects();	

	RemoveAllActiveTimedBombs(); 

	// handle any quest stuff here so world items can be affected
	HandleQuestCodeOnSectorExit( gWorldSectorX, gWorldSectorY, gbWorldSectorZ );	

	//if we arent loading a saved game
	if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
	{
		//Clear any potential battle flags.  They will be set if necessary.
		gTacticalStatus.fEnemyInSector = FALSE; 
		gTacticalStatus.uiFlags &= ~INCOMBAT;		
	}

	if ( ubUnloadCode == ABOUT_TO_LOAD_NEW_MAP )
	{	
		//if we arent loading a saved game
		if( !(gTacticalStatus.uiFlags & LOADING_SAVED_GAME ) )
		{

			// Save the current sectors Item list to a temporary file, if its not the first time in
			SaveCurrentSectorsInformationToTempItemFile();	

			// Update any mercs currently in sector, their profile info...
			UpdateSoldierPointerDataIntoProfile( FALSE );	
		}
	}
	else if( ubUnloadCode == ABOUT_TO_TRASH_WORLD )
	{
		//Save the current sectors open temp files to the disk
		if( !SaveCurrentSectorsInformationToTempItemFile() )
		{
			ScreenMsg( FONT_MCOLOR_WHITE, MSG_TESTVERSION, L"ERROR in SaveCurrentSectorsInformationToTempItemFile()");
			return FALSE;
		}

		//Setup the tactical existance of the current soldier.
		//@@@Evaluate
		for( i = gTacticalStatus.Team[ CIV_TEAM ].bFirstID; i <= gTacticalStatus.Team[ CIV_TEAM ].bLastID; i++ )
		{
			if( MercPtrs[ i ]->bActive && MercPtrs[ i ]->bInSector )
			{
				SetupProfileInsertionDataForSoldier( MercPtrs[ i ] );
			}
		}

		gfBlitBattleSectorLocator = FALSE;
	}

	//if the fan sound is going, remove it
	HandleRemovingPowerGenFanSound();

/*
Ja25 no militia
	//Handle cases for both types of unloading
	HandleMilitiaStatusInCurrentMapBeforeLoadingNewMap();	
*/
	return TRUE;
}

BOOLEAN HandlePotentialBringUpAutoresolveToFinishBattle( )
{
	INT32 i;

	//We don't have mercs in the sector.  Now, we check to see if there are BOTH enemies and militia.  If both 
	//co-exist in the sector, then make them fight for control of the sector via autoresolve.
	for( i = gTacticalStatus.Team[ ENEMY_TEAM ].bFirstID; i <= gTacticalStatus.Team[ CREATURE_TEAM ].bLastID; i++ )
	{
		if( MercPtrs[ i ]->bActive && MercPtrs[ i ]->bLife )
		{
			if( MercPtrs[ i ]->sSectorX == gWorldSectorX && 
					MercPtrs[ i ]->sSectorY == gWorldSectorY && 
					MercPtrs[ i ]->bSectorZ == gbWorldSectorZ )
			{ //We have enemies, now look for militia!
				for( i = gTacticalStatus.Team[ MILITIA_TEAM ].bFirstID; i <= gTacticalStatus.Team[ MILITIA_TEAM ].bLastID; i++ )
				{
					if( MercPtrs[ i ]->bActive && MercPtrs[ i ]->bLife && MercPtrs[ i ]->bSide == OUR_TEAM )
					{
						if( MercPtrs[ i ]->sSectorX == gWorldSectorX && 
								MercPtrs[ i ]->sSectorY == gWorldSectorY && 
								MercPtrs[ i ]->bSectorZ == gbWorldSectorZ )
						{ //We have militia and enemies and no mercs!  Let's finish this battle in autoresolve.
							gfEnteringMapScreen = TRUE;
							gfEnteringMapScreenToEnterPreBattleInterface = TRUE;
							gfAutomaticallyStartAutoResolve = TRUE;
							gfUsePersistantPBI = FALSE;
							gubPBSectorX = (UINT8)gWorldSectorX;
							gubPBSectorY = (UINT8)gWorldSectorY;
							gubPBSectorZ = (UINT8)gbWorldSectorZ;
							gfBlitBattleSectorLocator = TRUE;
							gfTransferTacticalOppositionToAutoResolve = TRUE;
							if( gubEnemyEncounterCode != CREATURE_ATTACK_CODE )
							{
								gubEnemyEncounterCode = ENEMY_INVASION_CODE; //has to be, if militia are here.
							}
							else
							{
								//DoScreenIndependantMessageBox( gzLateLocalizedString[ 39 ], MSG_BOX_FLAG_OK, MapScreenDefaultOkBoxCallback );
							}

              return( TRUE );
						}
					}
				}
			}
		}
  }

  return( FALSE );
}


BOOLEAN CheckAndHandleUnloadingOfCurrentWorld()
{
	INT32 i;
	INT16 sBattleSectorX, sBattleSectorY, sBattleSectorZ;

	//Don't bother checking this if we don't have a world loaded.
	if( !gfWorldLoaded )
	{
		return FALSE;
	}

	if( gTacticalStatus.fDidGameJustStart && gWorldSectorX == 9 && gWorldSectorY == 1 && !gbWorldSectorZ )
	{ 
		return FALSE;
	}

	GetCurrentBattleSectorXYZ( &sBattleSectorX, &sBattleSectorY, &sBattleSectorZ );

	if( guiCurrentScreen == AUTORESOLVE_SCREEN )
	{ //The user has decided to let the game autoresolve the current battle.
		if( gWorldSectorX == sBattleSectorX && gWorldSectorY == sBattleSectorY && gbWorldSectorZ == sBattleSectorZ )
		{
			for( i = gTacticalStatus.Team[ OUR_TEAM ].bFirstID; i <= gTacticalStatus.Team[ OUR_TEAM ].bLastID; i++ )
			{ //If we have a live and valid soldier
				if( MercPtrs[ i ]->bActive && MercPtrs[ i ]->bLife && !MercPtrs[ i ]->fBetweenSectors && !(MercPtrs[ i ]->uiStatusFlags & SOLDIER_VEHICLE ) && !AM_A_ROBOT( MercPtrs[ i ] ) && !AM_AN_EPC(  MercPtrs[ i ] ) )
				{
					if( MercPtrs[ i ]->sSectorX == gWorldSectorX && 
							MercPtrs[ i ]->sSectorY == gWorldSectorY && 
							MercPtrs[ i ]->bSectorZ == gbWorldSectorZ )
					{
						RemoveSoldierFromGridNo( MercPtrs[ i ] );
						InitSoldierOppList( MercPtrs[ i ] );
					}
				}
			}
		}
	}
	else
	{	//Check and see if we have any live mercs in the sector.  
		for( i = gTacticalStatus.Team[ OUR_TEAM ].bFirstID; i <= gTacticalStatus.Team[ OUR_TEAM ].bLastID; i++ )
		{ //If we have a live and valid soldier
			if( MercPtrs[ i ]->bActive && MercPtrs[ i ]->bLife && !MercPtrs[ i ]->fBetweenSectors && !(MercPtrs[ i ]->uiStatusFlags & SOLDIER_VEHICLE ) && !AM_A_ROBOT( MercPtrs[ i ] ) && !AM_AN_EPC(  MercPtrs[ i ] ))
			{
				if( MercPtrs[ i ]->sSectorX == gWorldSectorX && 
						MercPtrs[ i ]->sSectorY == gWorldSectorY && 
						MercPtrs[ i ]->bSectorZ == gbWorldSectorZ )
				{ 
					return FALSE;
				}
			}
		}
		//KM : August 6, 1999 Patch fix
		//     Added logic to prevent a crash when player mercs would retreat from a battle involving militia and enemies.
		//		 Without the return here, it would proceed to trash the world, and then when autoresolve would come up to 
		//     finish the tactical battle, it would fail to find the existing soldier information (because it was trashed).
    if( HandlePotentialBringUpAutoresolveToFinishBattle( ) )
		{
			return FALSE;
		}
		//end

		//HandlePotentialBringUpAutoresolveToFinishBattle( ); //prior patch logic
	}


	CheckForEndOfCombatMode( FALSE );
	EndTacticalBattleForEnemy();

	// ATE: Change cursor to wait cursor for duration of frame.....
	// save old cursor ID....
	SetCurrentCursorFromDatabase( CURSOR_WAIT_NODELAY );
	RefreshScreen( NULL );

	if( guiCurrentScreen == GAME_SCREEN )
	{
		if( !gfTacticalTraversal )
		{ //if we are in tactical and don't intend on going to another sector immediately, then 
			gfEnteringMapScreen = TRUE;
		}
		else 
		{ //The trashing of the world will be handled automatically.
			return FALSE;
		}
	}

	//We have passed all the checks and can Trash the world.
	if( !HandleDefiniteUnloadingOfWorld( ABOUT_TO_TRASH_WORLD ) )
	{
		return FALSE;
	}

	if( guiCurrentScreen == AUTORESOLVE_SCREEN )
	{ 
		if( gWorldSectorX == sBattleSectorX && gWorldSectorY == sBattleSectorY && gbWorldSectorZ == sBattleSectorZ )
		{	//Yes, this is and looks like a hack.  The conditions of this if statement doesn't work inside
			//TrashWorld() or more specifically, TacticalRemoveSoldier() from within TrashWorld().  Because
			//we are in the autoresolve screen, soldiers are internally created different (from pointers instead of
			//the MercPtrs[]).  It keys on the fact that we are in the autoresolve screen.  So, by switching the
			//screen, it'll delete the soldiers in the loaded world properly, then later on, once autoresolve is
			//complete, it'll delete the autoresolve soldiers properly.  As you can now see, the above if conditions
			//don't change throughout this whole process which makes it necessary to do it this way.
			guiCurrentScreen = MAP_SCREEN;
			TrashWorld();
			guiCurrentScreen = AUTORESOLVE_SCREEN;
		}
	}
	else
	{
		TrashWorld();
	}

	//Clear all combat related flags.
	gTacticalStatus.fEnemyInSector = FALSE;
	gTacticalStatus.uiFlags &= ~INCOMBAT;
  EndTopMessage( );


	//Clear the world sector values.
	gWorldSectorX = gWorldSectorY = 0;
	gbWorldSectorZ = -1;

	//Clear the flags regarding.
	gfCaves = FALSE;
	gfBasement = FALSE;

	return TRUE;
}



//This is called just before the world is unloaded to preserve location information for RPCs and NPCs either in
//the sector or strategically in the sector (such as firing an NPC in a sector that isn't yet loaded.)  When loading that
//sector, the RPC would be added.
//@@@Evaluate
void SetupProfileInsertionDataForSoldier( SOLDIERTYPE *pSoldier )
{
	if( !pSoldier || pSoldier->ubProfile == NO_PROFILE )
	{ //Doesn't have profile information.
		return;
	}

	if ( gMercProfiles[ pSoldier->ubProfile ].ubMiscFlags3 & PROFILE_MISC_FLAG3_PERMANENT_INSERTION_CODE )
	//if ( gMercProfiles[ pSoldier->ubProfile ].ubStrategicInsertionCode == INSERTION_CODE_PERMANENT_GRIDNO )
	{
		// can't be changed!
		return;
	}

	if ( gfWorldLoaded && pSoldier->bActive && pSoldier->bInSector )
	{ //This soldier is currently in the sector

					//@@@Evaluate -- insert code here
					//SAMPLE CODE:  There are multiple situations that I didn't code.  The gridno should be the final destination
					//or reset???			

		if ( pSoldier->ubQuoteRecord && pSoldier->ubQuoteActionID )
		{
			// if moving to traverse
			if ( pSoldier->ubQuoteActionID >= QUOTE_ACTION_ID_TRAVERSE_EAST && pSoldier->ubQuoteActionID <= QUOTE_ACTION_ID_TRAVERSE_NORTH )
			{
				// Handle traversal.  This NPC's sector will NOT already be set correctly, so we have to call for that too
				HandleNPCChangesForTacticalTraversal( pSoldier );
				gMercProfiles[ pSoldier->ubProfile ].fUseProfileInsertionInfo = FALSE;			
				if ( pSoldier->ubProfile != NO_PROFILE && NPCHasUnusedRecordWithGivenApproach( pSoldier->ubProfile, APPROACH_DONE_TRAVERSAL ) )
				{
					gMercProfiles[ pSoldier->ubProfile ].ubMiscFlags3 |= PROFILE_MISC_FLAG3_HANDLE_DONE_TRAVERSAL;
				}

			}
			else
			{
				if ( pSoldier->sFinalDestination == pSoldier->sGridNo )
				{
					gMercProfiles[ pSoldier->ubProfile ].usStrategicInsertionData = pSoldier->sGridNo;
				}
				else if ( pSoldier->sAbsoluteFinalDestination != NOWHERE )
				{
					gMercProfiles[ pSoldier->ubProfile ].usStrategicInsertionData = pSoldier->sAbsoluteFinalDestination;
				}
				else
				{
					gMercProfiles[ pSoldier->ubProfile ].usStrategicInsertionData = pSoldier->sFinalDestination;
				}			

				gMercProfiles[ pSoldier->ubProfile ].fUseProfileInsertionInfo = TRUE;
				gMercProfiles[ pSoldier->ubProfile ].ubStrategicInsertionCode = INSERTION_CODE_GRIDNO;
				gMercProfiles[ pSoldier->ubProfile ].ubQuoteActionID = pSoldier->ubQuoteActionID;
				gMercProfiles[ pSoldier->ubProfile ].ubQuoteRecord = pSoldier->ubQuoteActionID;
			}
		}
		else
		{
			gMercProfiles[ pSoldier->ubProfile ].fUseProfileInsertionInfo = FALSE;
		}

	}
	else
	{ //use strategic information

		//It appears to set the soldier's strategic insertion code everytime a group arrives in a new sector.  The insertion data
		//isn't needed for these cases as the code is a direction only.
		gMercProfiles[ pSoldier->ubProfile ].ubStrategicInsertionCode = pSoldier->ubStrategicInsertionCode;
		gMercProfiles[ pSoldier->ubProfile ].usStrategicInsertionData = 0;
		
		//Strategic system should now work.
		gMercProfiles[ pSoldier->ubProfile ].fUseProfileInsertionInfo = TRUE;
	}
}


void HandlePotentialMoraleHitForSkimmingSectors( GROUP *pGroup )
{
	PLAYERGROUP *pPlayer;

  if ( !gTacticalStatus.fHasEnteredCombatModeSinceEntering && gTacticalStatus.fEnemyInSector )
  {
		//Flag is set so if "wilderness" enemies are in the adjacent sector of this group, the group has
		//a 90% chance of ambush.  Because this typically doesn't happen very often, the chance is high.  
		//This reflects the enemies radioing ahead to other enemies of the group's arrival, so they have
		//time to setup a good ambush!
		pGroup->uiFlags |= GROUPFLAG_HIGH_POTENTIAL_FOR_AMBUSH;

	  pPlayer = pGroup->pPlayerList;

	  while( pPlayer )
	  {
      // Do morale hit...
      // CC look here!
      // pPlayer->pSoldier 

		  pPlayer = pPlayer->next;
	  }
  }
}



#ifdef CRIPPLED_VERSION
void CrippledVersionFailureToLoadMapCheck()
{
	CHAR16	zString[512];

	swprintf( zString, L"Error! Sorry, you must stay between sectors A and E in this limited press version." );

	DoScreenIndependantMessageBox( zString, MSG_BOX_FLAG_OK, CrippledVersionFailureToLoadMapCallBack );	
}

void CrippledVersionFailureToLoadMapCallBack( UINT8 bExitValue )
{
	//clean up the code
	ReStartingGame();

	//go to the main menu
	if( guiCurrentScreen == MAP_SCREEN )
	{
		SetPendingNewScreen(MAINMENU_SCREEN);
	}
	else
	{
		InternalLeaveTacticalScreen( MAINMENU_SCREEN );
	}
}
#endif

typedef struct
{
	INT16	sSectorID;
	INT8	bSectorZ;
	UINT8	ubQuoteNum;
} ENTER_SECTOR_PLAYER_QUOTE;

void HandlePlayerTeamQuotesWhenEnteringSector( INT16 sSectorX, INT16 sSectorY, INT16 sSectorZ )
{
	UINT32	uiCnt;
	INT8		bNumValidMercs=-1;
	INT32		iSectorID = SECTOR( sSectorX, sSectorY );
	UINT8		ubValidMercProfileIDArray[ NUM_MERCS_WITH_NEW_QUOTES ];
	SOLDIERTYPE *pSoldier=NULL;


	#define	NUM_VALID_SECTORS									6
	#define	DELAY_FOR_PLAYER_DESC_OF_SECTOR		2
	ENTER_SECTOR_PLAYER_QUOTE	PlayerSectorDescQuote[ NUM_VALID_SECTORS ] = 
	{
		{ SEC_H9,		0,	QUOTE_HATE_MERC_1_ON_TEAM },
		{ SEC_I9,		0,	QUOTE_LEARNED_TO_HATE_MERC_ON_TEAM },
		{ SEC_H10,	0,	QUOTE_LEARNED_TO_HATE_MERC_ON_TEAM },
		{ SEC_I10,	0,	QUOTE_HATE_MERC_2_ON_TEAM },
		{ SEC_J13,	0,	QUOTE_ENTER_SECTOR_WITH_FAN_1 },
		{ SEC_J14,	1,	0 },
	};

	//loop through all the sectors that have the quotes
	for( uiCnt=0; uiCnt<NUM_VALID_SECTORS; uiCnt++ )
	{
		//if this sector is the right x & y
		if( PlayerSectorDescQuote[ uiCnt ].sSectorID == iSectorID )
		{
			//if is the right level
			if( PlayerSectorDescQuote[ uiCnt ].bSectorZ == sSectorZ )
			{
				// ATE: If this sector is a custom sector, break out!
				if ( !SectorInfo[ iSectorID ].fCampaignSector )
				{
					return;
				}

				// If the player has never said the "enter sector" desc before
				if( GetSectorFlagStatus( sSectorX, sSectorY, ( UINT8 )sSectorZ, SF_HAVE_SAID_PLAYER_QUOTE_NEW_SECTOR ) != TRUE )
				{
					//Get # of valid mercs
					bNumValidMercs = GetNumSoldierIdAndProfileIdOfTheNewMercsOnPlayerTeam( NULL, ubValidMercProfileIDArray );

					//if there isnt any valid mercs
					if( bNumValidMercs == 0 )
					{
						//exit
						return;
					}

					//Switch on the town ID
					switch( iSectorID )
					{
						case SEC_I10:
							{
								UINT8	cnt;
	
								for( cnt=0; cnt<bNumValidMercs; cnt++ )
								{
									//Say the qoute in a couple of seconds
									DelayedMercQuote( ubValidMercProfileIDArray[ cnt ], PlayerSectorDescQuote[ uiCnt ].ubQuoteNum, GetWorldTotalSeconds() + DELAY_FOR_PLAYER_DESC_OF_SECTOR + cnt );
								}
							}
							break;

						case SEC_J13:
							if( PlayerSectorDescQuote[ uiCnt ].bSectorZ == 0 )
							{
								//See if Manuel is on the team
								pSoldier = FindSoldierByProfileID( MANUEL, TRUE );

								//if he is ON the team
								if( pSoldier != NULL )
								{
									//get manuel to say the quote
									DelayedMercQuote( MANUEL, PlayerSectorDescQuote[ uiCnt ].ubQuoteNum, GetWorldTotalSeconds() + DELAY_FOR_PLAYER_DESC_OF_SECTOR );

									//get manuel to say his additional quote
									DelayedMercQuote( MANUEL, QUOTE_ENTER_SECTOR_WITH_FAN_2, GetWorldTotalSeconds() + DELAY_FOR_PLAYER_DESC_OF_SECTOR );
								}
								else
								{
									//else if Biggens is not on the team, check for biggens
									pSoldier = FindSoldierByProfileID( BIGGENS, TRUE );

									//if he is ON the team
									if( pSoldier != NULL )
									{
										//get manuel to say the quote
										DelayedMercQuote( BIGGENS, PlayerSectorDescQuote[ uiCnt ].ubQuoteNum, GetWorldTotalSeconds() + DELAY_FOR_PLAYER_DESC_OF_SECTOR );

										//Remember he said
										SetJa25GeneralFlag( JA_GF__BIGGENS_SAID_QUOTE_117 );
									}
								}

								//Remeber the quote was said
								SetFactTrue( FACT_PLAYER_KNOWS_ABOUT_FAN_STOPPING );
							}
							break;
						case SEC_J14:
							{
								//first underground sector
								HandlePlayerQuotesWhenEnteringFirstTunnelSector();
							}
							break;
						default:
							{
								//Get a random merc from the list
								UINT8	ubMercToSayQuote = RandomProfileIdFromNewMercsOnPlayerTeam();

								//Say the qoute in a couple of seconds
								DelayedMercQuote( ubMercToSayQuote, PlayerSectorDescQuote[ uiCnt ].ubQuoteNum, GetWorldTotalSeconds() + DELAY_FOR_PLAYER_DESC_OF_SECTOR );
							}
							break;
					}

					//if this sector is one of the fields before the town, only say the quote once for both sectors
					if( ( iSectorID == SEC_I9 || iSectorID == SEC_H10 ) && sSectorZ == 0 )
					{
						//Remeber that we said the quote
						SetSectorFlag( 9, 9, 0, SF_HAVE_SAID_PLAYER_QUOTE_NEW_SECTOR );
						SetSectorFlag( 10, 8, 0, SF_HAVE_SAID_PLAYER_QUOTE_NEW_SECTOR );
					}

					//default
					else
					{
						//Remeber that we said the quote
						SetSectorFlag( sSectorX, sSectorY, ( UINT8 )sSectorZ, SF_HAVE_SAID_PLAYER_QUOTE_NEW_SECTOR );
					}
				}

				//we are done here, leave
				return;
			}
		}
	}
}

void HandlePlayerQuotesWhenEnteringFirstTunnelSector()
{
	UINT8 ubID;

	//if the player got through using the timed method
	if( gJa25SaveStruct.ubHowPlayerGotThroughFan == PG__PLAYER_STOPPED_FAN_TO_GET_THROUGH )
	{
		UINT8 ubNumPlayersInSector = NumActiveAndConsciousTeamMembers( OUR_TEAM );
		UINT8 ubNumPlayersOnTeam = NumberOfMercsOnPlayerTeam();

		//Get a random qualified merc to say the quote
		ubID = RandomSoldierIdFromNewMercsOnPlayerTeam();

		//if there is no valid merc
		if( ubID == -1 )
			return;

		//if not all the players made it through
		if( ubNumPlayersInSector < ubNumPlayersOnTeam )
		{
//			TacticalCharacterDialogue( &Menptr[ ubID ], QUOTE_CONTRACTS_OVER );
			DelayedMercQuote( Menptr[ ubID ].ubProfile, QUOTE_CONTRACTS_OVER, GetWorldTotalSeconds() + DELAY_FOR_PLAYER_DESC_OF_SECTOR );
		}

		//if ALL mercs made it through
		else if( ubNumPlayersInSector == ubNumPlayersOnTeam )
		{
			DelayedMercQuote( Menptr[ ubID ].ubProfile, QUOTE_CONTRACT_ACCEPTANCE, GetWorldTotalSeconds() + DELAY_FOR_PLAYER_DESC_OF_SECTOR );
//			TacticalCharacterDialogue( &Menptr[ ubID ], QUOTE_CONTRACT_ACCEPTANCE );
		}
	}

	else if( gJa25SaveStruct.ubHowPlayerGotThroughFan == PG__PLAYER_BLEW_UP_FAN_TO_GET_THROUGH )
	{
/*
Chnaged to be played when fan blows up
		//Get a random qualified merc to say the quote
		ubID = RandomSoldierIdFromNewMercsOnPlayerTeam();

		DelayedMercQuote( Menptr[ ubID ].ubProfile, QUOTE_ACCEPT_CONTRACT_RENEWAL, GetWorldTotalSeconds() + DELAY_FOR_PLAYER_DESC_OF_SECTOR );
*/
	}

	else
	{
		Assert( 0 );
	}
}


void HandleEmailBeingSentWhenEnteringSector( INT16 sMapX, INT16 sMapY, INT8 bMapZ, BOOLEAN fLaptopJustGotFixed )
{
	SOLDIERTYPE *pSoldier=NULL;

	//
	// if this sector is a sector we are to send an email to the player from
	//

	//if the laptop transmiter is not working yet
	if( gubQuest[ QUEST_FIX_LAPTOP ] != QUESTDONE && !fLaptopJustGotFixed )
	{
		//we will send these emails later
		return;
	}

	//if miguel is alive
	if( gubFact[ FACT_PLAYER_IMPORTED_SAVE_MIGUEL_DEAD ] == FALSE )
	{
		//if its either J11 or I12 ( or we just got the email back up and we have been to the sector
		if( ( ( sMapY == 10 && sMapX == 11 ) || ( sMapY == 9 && sMapX == 12 ) && bMapZ == 0 ) ||
			fLaptopJustGotFixed && 
			( GetSectorFlagStatus( 11, 10, 0, SF_HAS_ENTERED_TACTICAL ) == TRUE || GetSectorFlagStatus( 12, 9, 0, SF_HAS_ENTERED_TACTICAL ) == TRUE ) )
		{
			//and we havent sent it before
			if( !( gJa25SaveStruct.ubEmailFromSectorFlag & SECTOR_EMAIL__J11_J12 ) )
			{
				pSoldier = FindSoldierByProfileID( MANUEL, TRUE );

				//if Manuel isnt on the team
				if( pSoldier == NULL || gMercProfiles[ MANUEL ].bMercStatus == MERC_IS_DEAD )
				{
					//email 8a
					AddEmail( EMAIL_MIGUELSORRY, EMAIL_MIGUELSORRY_LENGTH, MAIL_MIGUEL,  GetWorldTotalMin() );
				}
				else
				{
					//email 8b
					AddEmail( EMAIL_MIGUELMANUEL, EMAIL_MIGUELMANUEL_LENGTH, MAIL_MIGUEL,  GetWorldTotalMin() );
				}

				//Remeber we sent it
				gJa25SaveStruct.ubEmailFromSectorFlag |= SECTOR_EMAIL__J11_J12;
			}
		}

		//if its the power generator sector
		if( sMapY == 10 && sMapX == 13 && bMapZ == 0 ||
			fLaptopJustGotFixed && GetSectorFlagStatus( 13, 10, 0, SF_HAS_ENTERED_TACTICAL ) == TRUE )
		{
			//and we havent sent it before
			if( !( gJa25SaveStruct.ubEmailFromSectorFlag & SECTOR_EMAIL__POWER_GEN ) )
			{
				AddEmail( EMAIL_MIGUELSICK, EMAIL_MIGUELSICK_LENGTH, MAIL_MIGUEL,  GetWorldTotalMin() );

				//Remeber we sent it
				gJa25SaveStruct.ubEmailFromSectorFlag |= SECTOR_EMAIL__POWER_GEN;
			}
		}
	}


	//if its the tunnel sector
	if( sMapY == 10 && sMapX == 14 && bMapZ == 1 ||
		fLaptopJustGotFixed && GetSectorFlagStatus( 14, 10, 1, SF_HAS_ENTERED_TACTICAL ) == TRUE	)
	{
		//and we havent sent it before
		if( !( gJa25SaveStruct.ubEmailFromSectorFlag & SECTOR_EMAIL__TUNNEL ) )
		{
			//If Jerry isnt dead
			if( gMercProfiles[ JERRY ].bMercStatus != MERC_IS_DEAD )
			{
				AddEmail( EMAIL_PILOTFOUND, EMAIL_PILOTFOUND_LENGTH, MAIL_ENRICO,  GetWorldTotalMin() );
			}

			//Remeber we sent it
			gJa25SaveStruct.ubEmailFromSectorFlag |= SECTOR_EMAIL__TUNNEL;
		}
	}
}

void ShouldNpcBeAddedToSector( INT16 sMapX, INT16 sMapY, INT8 bMapZ )
{
	//if Manuel has never been added before
	if( !( gJa25SaveStruct.fNpcHasBeenAdded & SECTOR_ADDED_NPC__MANUEL) )
	{
		//if it is the right sector
		if( ( sMapY == MAP_ROW_H && sMapX == 10 && bMapZ == 0 ) ||
				( sMapY == MAP_ROW_I && sMapX == 9 && bMapZ == 0 ) )
		{
			//Change his sector values to 
			gMercProfiles[ MANUEL ].sSectorX = sMapX;
			gMercProfiles[ MANUEL ].sSectorY = sMapY;
			gMercProfiles[ MANUEL ].bSectorZ = bMapZ;

			//remember that we have added him
			gJa25SaveStruct.fNpcHasBeenAdded |= SECTOR_ADDED_NPC__MANUEL;
		}
	}

	//if Tex has never been added before 
	if( !( gJa25SaveStruct.fNpcHasBeenAdded & SECTOR_ADDED_NPC__TEX ) )
	{
		//and tex is TO be added
		if( gubFact[ FACT_TEX_IS_IN_GAME_AND_ALIVE_IN_STORE ] )
		{
			//if it is the right sector
			if( sMapY == MAP_ROW_I && sMapX == 10 && bMapZ == 0 )
			{
				//Change his sector values to 
				gMercProfiles[ TEX ].sSectorX = sMapX;
				gMercProfiles[ TEX ].sSectorY = sMapY;
				gMercProfiles[ TEX ].bSectorZ = bMapZ;

				//remember that we have added him
				gJa25SaveStruct.fNpcHasBeenAdded |= SECTOR_ADDED_NPC__TEX;
			}
		}
	}

	//if John has never been added before 
	if( !( gJa25SaveStruct.fNpcHasBeenAdded & SECTOR_ADDED_NPC__JOHN_K ) )
	{
		//and John is TO be added ( Tex not in game )
		if( !gubFact[ FACT_TEX_IS_IN_GAME_AND_ALIVE_IN_STORE ] )
		{
			//if it is the right sector
			if( sMapX == gJa25SaveStruct.ubJohnKulbaInitialSectorX && 
					sMapY == gJa25SaveStruct.ubJohnKulbaInitialSectorY && 
					bMapZ == 0 )
			{
				//Change his sector values to 
				gMercProfiles[ JOHN_K ].sSectorX = sMapX;
				gMercProfiles[ JOHN_K ].sSectorY = sMapY;
				gMercProfiles[ JOHN_K ].bSectorZ = bMapZ;

				//remember that we have added him
				gJa25SaveStruct.fNpcHasBeenAdded |= SECTOR_ADDED_NPC__JOHN_K;
			}
		}
	}
}

void HandleSectorSpecificUnLoadingOfMap( INT16 sMapX, INT16 sMapY, INT8 bMapZ )
{
	//if this is the power gen map
	if( sMapX == 13 && sMapY == MAP_ROW_J && bMapZ == 0 )
	{
		BOOLEAN fGoingToTunnelSector=FALSE;

		//if we are going to the first sector if the tunnel
		if( gWorldSectorX == 14 &&
				gWorldSectorY == MAP_ROW_J &&
				gbWorldSectorZ == 1 )
		{
			fGoingToTunnelSector = TRUE;
		}

		switch( gJa25SaveStruct.ubStateOfFanInPowerGenSector )
		{
			case PGF__RUNNING_NORMALLY:
				HandleRemovingPowerGenFanSound();
				break;
		}

		//Remeber how the player got through
		HandleHowPlayerGotThroughFan();
	}
	//else if this is the 1st level of tunne;l
	else	if( sMapX == 14 && sMapY == MAP_ROW_J && bMapZ == 1 )
	{
		switch( gJa25SaveStruct.ubStateOfFanInPowerGenSector )
		{
			case PGF__RUNNING_NORMALLY:
			case PGF__STOPPED:

				//remove the sound to the world
				HandleRemovingPowerGenFanSound();
				break;
		}
	}
}


void HandleSectorSpecificModificatioToMap( INT16 sMapX, INT16 sMapY, INT8 bMapZ, BOOLEAN fLoadingSavedGame )
{
//	SOLDIERTYPE *pSoldier=NULL;
//	INT32				iCash=0;

	//if we are loading a game, dont do this yet ( it will be done after everything is loaded
	if( gTacticalStatus.uiFlags & LOADING_SAVED_GAME )
	{
		return;
	}

	SetTileAnimCounter( TILE_ANIM__NORMAL_SPEED );

	//if we are being called from LoadSavedGame()
	if( fLoadingSavedGame )
	{
		//
		// only do certain modifications
		//

		//if this is the power gen map
		if( sMapX == 13 && sMapY == MAP_ROW_J && bMapZ == 0 )
		{
			HandlePowerGenFanSoundModification();
		}
		else	if( sMapX == 14 && sMapY == MAP_ROW_J && bMapZ == 1 )
		{
			HandleFirstPartOfTunnelFanSound();
		}

		//if this is the Final Sector of the complex
		else if( sMapX == 15 && sMapY == MAP_ROW_L && bMapZ == 3 )
		{
			HandleOpenControlPanelToRevealSwitchInMorrisArea();
		}
	}
	else
	{
		//if this is the first map
		if( sMapX == 7 && sMapY == MAP_ROW_H && bMapZ == 0 )
		{
		}

		//if this is the guardpost
		else if( sMapX == 9 && sMapY == MAP_ROW_H && bMapZ == 0 )
		{
			//if we havent added the money to the sector before
			if( !IsJa25GeneralFlagSet( JA_GF__PICKED_UP_MONEY_IN_GUARD_POST ) )
			{
				SetJa25GeneralFlag( JA_GF__PICKED_UP_MONEY_IN_GUARD_POST );

				// Add some money to the location
				CreateAndAddMoneyObjectToGround( 9026, 15000, 10000, 7000 );
			}
		}

		//if this is the First sector of the town
		else if( sMapX == 10 && sMapY == MAP_ROW_I && bMapZ == 0 )
		{
			//if we havent added the money to the sector before
			if( !IsJa25GeneralFlagSet( JA_GF__PICKED_UP_MONEY_IN_FIRST_TOWN ) )
			{
				SetJa25GeneralFlag( JA_GF__PICKED_UP_MONEY_IN_FIRST_TOWN );

				// Add some money to the location
				CreateAndAddMoneyObjectToGround( 11894, 8000, 4000, 3000 );
				CreateAndAddMoneyObjectToGround( 7906,  12000, 6000, 5000 );
			}
		}

		//if this is the power gen map
		else if( sMapX == 13 && sMapY == MAP_ROW_J && bMapZ == 0 )
		{
			HandlePowerGenFanSoundModification();
		}

		//else if this is the 1st part of tunnel
		else	if( sMapX == 14 && sMapY == MAP_ROW_J && bMapZ == 1 )
		{
			HandleFirstPartOfTunnelFanSound();

			if( IsJa25GeneralFlagSet( JA_GF__MOVE_ENEMIES_TO_EDGE_IN_TUNNEL_1 ) )
			{
				HandleMovingEnemiesCloseToEntranceInFirstTunnelMap();
			}
		}

		//else if this is the 2nd part of tunnel
		else	if( sMapX == 14 && sMapY == MAP_ROW_K && bMapZ == 1 )
		{
			if( IsJa25GeneralFlagSet( JA_GF__MOVE_ENEMIES_TO_EDGE_IN_TUNNEL_1 ) )
			{
				HandleMovingEnemiesCloseToEntranceInSecondTunnelMap();
			}
		}

		//else if this is the 1st level in the complex
		else	if( sMapX == 15 && sMapY == MAP_ROW_K && bMapZ == 1 )
		{
			//Make all the team members look like they dropped from a high place
			//		MakeAllTeamMembersCrouchedThenStand();

			//If the player made noise in the tunnel, enemies should be placed near them
			HandleMovingTheEnemiesToBeNearPlayerWhenEnteringComplexMap();

			//if the big door should be opened
			HandleFortifiedDoor();
		}

		//if this is the Final Sector of the complex
		else if( sMapX == 15 && sMapY == MAP_ROW_L && bMapZ == 3 )
		{
			HandleOpenControlPanelToRevealSwitchInMorrisArea();
		}

		
		
		
		//if the enemies should go and find the player mercs
		if( GetSectorEnemyIsToImmediatelySeekEnemyIn() != -1 )
		{
			//Make the enemies go find the player mercs
			SetEnemiesToFindThePlayerMercs();
		}

		//if this is a sector we feel can be made harder for players ( on hard difficulty levels ), then move some
		//enemies onto roofs.
		HandleMovingEnemiesOntoRoofs();		
	}
}

void MakeAllTeamMembersCrouchedThenStand()
{
	UINT8	cnt;
	SOLDIERTYPE *pSoldier=NULL;

	//Move some of the enemies to be 'near' them player when the enter the room
	cnt = gTacticalStatus.Team[ OUR_TEAM ].bFirstID;

	// Loop through the list and move some of the enemies
	for ( pSoldier = MercPtrs[ cnt ]; cnt <= gTacticalStatus.Team[ OUR_TEAM ].bLastID; cnt++, pSoldier++)
	{	
		//if the soldier is active,
		if( pSoldier->bActive && pSoldier->bInSector )
		{
			EVENT_InitNewSoldierAnim( pSoldier, CRAWLING, 1, TRUE );
			ChangeSoldierStance( pSoldier, PRONE );
		}
	}
}

void HandleMovingTheEnemiesToBeNearPlayerWhenEnteringComplexMap()
{
	SOLDIERTYPE *pSoldier=NULL;
	UINT8				ubNumEnemiesMoved=0;

	//if we are loading a saved game, or we have already moved the enemies, get out.
	if( gTacticalStatus.uiFlags & LOADING_SAVED_GAME || 
			gJa25SaveStruct.uiJa25GeneralFlags & JA_GF__ALREADY_MOVED_ENEMIES_IN_COMPLEX )
	{
		return;
	}

	//if the player made a 'noise' going through the gate at the end of the tunnel sector
	if( gJa25SaveStruct.uiJa25GeneralFlags & JA_GF__DID_PLAYER_MAKE_SOUND_GOING_THROUGH_TUNNEL_GATE )
	{
		UINT8	cnt;

		//
		//Move some of the enemies to be 'near' them player when the enter the room
		//

		// Loop through the list and move some of the enemies
		cnt = gTacticalStatus.Team[ ENEMY_TEAM ].bFirstID;
		for ( pSoldier = MercPtrs[ cnt ]; cnt <= gTacticalStatus.Team[ ENEMY_TEAM ].bLastID; cnt++, pSoldier++)
		{	
			//if the soldier is active,
			if ( pSoldier->bActive  )
			{
				//
				// move the soldier to the modified location
				//

				if( pSoldier->sGridNo	== 13959 )
				{
					SetSoldierGridNo( pSoldier, 15705, TRUE );
					ubNumEnemiesMoved++;
				}

				if( pSoldier->sGridNo	== 13983 )
				{
					SetSoldierGridNo( pSoldier, 15712, TRUE );
					ubNumEnemiesMoved++;
				}

				if( pSoldier->sGridNo	== 12543 )
				{
					SetSoldierGridNo( pSoldier, 15233, TRUE );
					ubNumEnemiesMoved++;
				}
			}
		}

		while( ubNumEnemiesMoved < 3 )
		{
			cnt = gTacticalStatus.Team[ ENEMY_TEAM ].bFirstID;
			for ( pSoldier = MercPtrs[ cnt ]; cnt <= gTacticalStatus.Team[ ENEMY_TEAM ].bLastID; cnt++, pSoldier++)
			{	
				//if the soldier is active,
				if ( pSoldier->bActive  && pSoldier->sGridNo != 15705 && pSoldier->sGridNo != 15712 && pSoldier->sGridNo != 15233 )
				{
					//
					// move the soldier to the modified location
					//

					if( ubNumEnemiesMoved == 0 )
					{
						SetSoldierGridNo( pSoldier, 15706, TRUE );
						ubNumEnemiesMoved++;
					}

					if( ubNumEnemiesMoved == 1 )
					{
						SetSoldierGridNo( pSoldier, 15713, TRUE );
						ubNumEnemiesMoved++;
					}

					if( ubNumEnemiesMoved == 2 )
					{
						SetSoldierGridNo( pSoldier, 15234, TRUE );
						ubNumEnemiesMoved++;
					}
				}
			}
		}

		//Remeber we have moved the enemies
		gJa25SaveStruct.uiJa25GeneralFlags |= JA_GF__ALREADY_MOVED_ENEMIES_IN_COMPLEX;
	}
}

void HandleFortifiedDoor()
{
	//if the fortified door should be open
	if( gJa25SaveStruct.ubStatusOfFortifiedDoor == FD__OPEN )
	{
		ModifyDoorStatus( 11419, TRUE, DONTSETDOORSTATUS );
	}
}

void CreateAndAddMoneyObjectToGround( INT16 sGridNo, INT32 iEasyAmount, INT32 iNormalAmount, INT32 iHardAmount )
{
	OBJECTTYPE	Object;
	INT32				iCash=0;
//	INT8				bAmountToAdd=0;

	switch( gGameOptions.ubDifficultyLevel )
	{
		case DIF_LEVEL_EASY:
			iCash = iEasyAmount;
			break;

		case DIF_LEVEL_MEDIUM:
			iCash = iNormalAmount;
			break;

		case DIF_LEVEL_HARD:
			iCash = iHardAmount;
			break;

		default:
			Assert(0);
	}

	CreateMoney( iCash, &Object );

	//add the item to the world
	AddItemToPool( sGridNo, &Object, FALSE, 0, 0, 0 );
}


void HandleGoingUpOrDownStairsForLoadScreensPurposes( INT16 sCurrentlyInSectorZ, INT16 sGoingToSectorZ )
{
	if( sCurrentlyInSectorZ == sGoingToSectorZ )
	{
		gJa25SaveStruct.ubLoadScreenStairTraversal = LS__NOT_GOING_UP_STAIRS;
	}
	else if( sCurrentlyInSectorZ < sGoingToSectorZ )
	{
		gJa25SaveStruct.ubLoadScreenStairTraversal = LS__GOING_DOWN_STAIRS;
	}
	else
	{
		gJa25SaveStruct.ubLoadScreenStairTraversal = LS__GOING_UP_STAIRS;
	}
}

void HandleMovingEnemiesCloseToEntranceInFirstTunnelMap()
{
	SOLDIERTYPE *pSoldier=NULL;
	UINT8	ubIndex=0;
	UINT32 cnt;
	BOOLEAN	fDone=FALSE;
	INT16							sXPos, sYPos;
	INT16 sGridNos[27]={ 18200, 18360, 18520,
											 18199, 18359, 18519,
											 18198, 18358, 18518,
											 18197, 18357, 18517,
											 18196, 18356, 18516,
											 18195, 18355, 18515,
											 18194, 18354, 18514,
											 18193, 18353, 18513,
											 18035, 18034, 18033,
	};


	//
	//Move some of the enemies to be 'near' them player when the enter the room
	//

	// Loop through the list and move some of the enemies
	cnt = gTacticalStatus.Team[ ENEMY_TEAM ].bFirstID;
	for ( pSoldier = MercPtrs[ cnt ]; cnt <= gTacticalStatus.Team[ ENEMY_TEAM ].bLastID; cnt++, pSoldier++)
	{	
		//if the soldier is active,
		if ( pSoldier->bActive  )
		{
			fDone = FALSE;
			while( !fDone )
			{
				//if there is no one in the gridno
				if( WhoIsThere2( sGridNos[ ubIndex ], 0 ) == NOBODY )
				{
					// move the soldier to the modified location
					ConvertGridNoToCenterCellXY( sGridNos[ ubIndex ], &sXPos, &sYPos );
					EVENT_SetSoldierPosition( pSoldier, sXPos, sYPos );
//					SetSoldierGridNo( pSoldier, sGridNos[ ubIndex ], TRUE );
					ubIndex++;
					fDone=TRUE;
				}
				else
				{
					ubIndex++;
				}

				if( ubIndex >= 27 )
				{
					Assert( 0 );
					return;
				}
			}
		}
	}
}

void HandleMovingEnemiesCloseToEntranceInSecondTunnelMap()
{
	SOLDIERTYPE *pSoldier=NULL;
	UINT8	ubIndex=0;
	BOOLEAN	fDone=FALSE;
	UINT32 cnt;
	INT16							sXPos, sYPos;
	INT16 sGridNos[30]={ 4900, 4901, 4902, 4903, 4904, 
											 5060, 5061, 5062, 5063, 5064,
											 5220, 5221, 5222, 5223, 5224,
											 5380, 5381, 5382, 5383, 5384,
											 5540, 5541, 5542, 5543, 5544,
											 5700, 5701, 5702, 5703, 5704 };



	//
	//Move some of the enemies to be 'near' them player when the enter the room
	//

	// Loop through the list and move some of the enemies
	cnt = gTacticalStatus.Team[ ENEMY_TEAM ].bFirstID;
	for ( pSoldier = MercPtrs[ cnt ]; cnt <= gTacticalStatus.Team[ ENEMY_TEAM ].bLastID; cnt++, pSoldier++)
	{	
		//if the soldier is active,
		if ( pSoldier->bActive  )
		{
			fDone = FALSE;
			while( !fDone )
			{
				//if there is no one in the gridno
				if( WhoIsThere2( sGridNos[ ubIndex ], 0 ) == NOBODY )
				{
					// move the soldier to the modified location
					ConvertGridNoToCenterCellXY( sGridNos[ ubIndex ], &sXPos, &sYPos );
					EVENT_SetSoldierPosition( pSoldier, sXPos, sYPos );
//					SetSoldierGridNo( pSoldier, sGridNos[ ubIndex ], TRUE );
					ubIndex++;
					fDone=TRUE;
				}
				else
				{
					ubIndex++;
				}

				if( ubIndex >= 26 )
				{
					Assert( 0 );
					return;
				}
			}
		}
	}
}

void HandlePowerGenFanSoundModification()
{
	SetTileAnimCounter( TILE_ANIM__FAST_SPEED );

	switch( gJa25SaveStruct.ubStateOfFanInPowerGenSector )
	{
		case PGF__RUNNING_NORMALLY:
			HandleAddingPowerGenFanSound();

			//MAKE SURE the fan does not have an exit grid
			RemoveExitGridFromWorld( PGF__FAN_EXIT_GRID_GRIDNO );
			break;
		
		case PGF__STOPPED:
			//Add an exit grid to the map
			AddExitGridForFanToPowerGenSector();
			break;
		
		case PGF__BLOWN_UP:
			break;

		default:
			Assert( 0 );
	}
}

void HandleFirstPartOfTunnelFanSound()
{
	switch( gJa25SaveStruct.ubStateOfFanInPowerGenSector )
	{
		case PGF__RUNNING_NORMALLY:
		case PGF__STOPPED:

			//add the sound to the world
			HandleAddingPowerGenFanSound();
			break;
	}
}

void HandleMovingEnemiesOntoRoofs()
{
	if( gWorldSectorX <= 0 || gWorldSectorY <= 0 || gbWorldSectorZ < 0 )
	{
		return;
	}

	//if this is the sector south of the town
	if( gWorldSectorX == 11 && gWorldSectorY == MAP_ROW_J && gbWorldSectorZ == 0 )
	{
		switch( gGameOptions.ubDifficultyLevel )
		{
			case DIF_LEVEL_EASY:
			case DIF_LEVEL_MEDIUM:
				break;
			case DIF_LEVEL_HARD:
				MoveEnemyFromGridNoToRoofGridNo( 15446, 13993 );
				MoveEnemyFromGridNoToRoofGridNo( 15436, 14006 );
				break;
		}
	}

	//else if this is the sector south of the town
	else if( gWorldSectorX == 11 && gWorldSectorY == MAP_ROW_H && gbWorldSectorZ == 0 )
	{
		switch( gGameOptions.ubDifficultyLevel )
		{
			case DIF_LEVEL_EASY:
			case DIF_LEVEL_MEDIUM:
				break;
			case DIF_LEVEL_HARD:
				MoveEnemyFromGridNoToRoofGridNo( 8711, 5521 );
				break;
		}
	}
}



BOOLEAN MoveEnemyFromGridNoToRoofGridNo( INT16 sSourceGridNo, INT16 sDestGridNo )
{
	SOLDIERTYPE *pSoldier=NULL;
	INT32				cnt;
	INT16				sXPos, sYPos;

	cnt = gTacticalStatus.Team[ ENEMY_TEAM ].bFirstID;
  for ( pSoldier = MercPtrs[ cnt ]; cnt <= gTacticalStatus.Team[ ENEMY_TEAM ].bLastID; cnt++, pSoldier++)
	{	
		if( pSoldier->bLife >= OKLIFE && pSoldier->bActive && pSoldier->bInSector &&
				pSoldier->sGridNo == sSourceGridNo )
		{
			SetSoldierHeight( pSoldier, 50.0 );

			// move soldier
			ConvertGridNoToCenterCellXY( sDestGridNo, &sXPos, &sYPos );
			EVENT_SetSoldierPosition( pSoldier, sXPos, sYPos );

			return( TRUE );
//			pSoldier->bOrders = SEEKENEMY;
		}
	}

	return( FALSE );
}

