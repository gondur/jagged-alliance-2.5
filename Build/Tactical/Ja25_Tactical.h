#ifndef _JA25_TACTICAL__H_
#define _JA25_TACTICAL__H_

#include "MapScreen Quotes.h"

#define		PGF__FAN_EXIT_GRID_GRIDNO																	10979

#define		NUM_MERCS_WITH_NEW_QUOTES												7


#define		DQ__NORMAL_DELAYED_QUOTE														0xff00
#define		DQ__JERRY_BROKE_TRANSMITTER													0xffff
#define		DQ__MORRIS_NOTE_NEW_MERC_DELAY											0xfffe
#define		DQ__MORRIS_NOTE_DISPLAY_NOTE_1											0xfffd
#define		DQ__MORRIS_NOTE_DISPLAY_NOTE_2											0xfffc
#define		DQ__SHOW_RADIO_LOCATOR															0xfffb
#define		DQ__NEW_MERC_SAY_NOTE_QUOTES												0xfffa
#define		DQ__START_EVERYONE_TALKING_AT_END_OF_GAME						0xfff0
#define		DQ__FADE_OUT_TO_END_GAME_CINEMATIC									0xfff9

enum
{
	JM_SE__HEADING_TO_TRACONA =MILO_QUOTE__HEADED_TO_TRACONA_QUOTE,
	JM_SE__SHOW_RADIO_LOCATOR = MILO_NO_QUOTE-10,
};

/*
// things that need to be saved in the exp in tactical
typedef struct
{

} JA25_TACTICAL_SAVE_STRUCT;

*/


INT8		RandomProfileIdFromNewMercsOnPlayerTeam();
INT8		RandomSoldierIdFromNewMercsOnPlayerTeam();
INT8		GetNumSoldierIdAndProfileIdOfTheNewMercsOnPlayerTeam( UINT8 *pSoldierIdArray, UINT8 *pProfileIdArray );
BOOLEAN	IsSoldierQualifiedMerc( SOLDIERTYPE *pSoldier );
BOOLEAN	IsSoldierQualifiedInitialHireMerc( SOLDIERTYPE *pSoldier );
BOOLEAN	IsSoldierQualifiedMercForSeeingPowerGenFan( SOLDIERTYPE *pSoldier );

BOOLEAN SayQuoteFromAllNewHiredMercButDoGastonLast( UINT8 ubProfile, UINT32 uiQuoteNum );

//Pass in an array of size NUM_MERCS_WITH_NEW_QUOTES, array will be filled with
//random soldier IDs of the qualified mercs
INT8 RandomArrayOfQualifiedMercs( UINT8 *pRandomSoldierIdArray );


INT8 Get3RandomQualifiedMercs( UINT8 *pSoldierId1, UINT8 *pSoldierId2, UINT8 *pSoldierId3 );

void HandleWhenCertainPercentageOfEnemiesDie();

void StartFanBackUpAgain();

void AddExitGridForFanToPowerGenSector();

void HandleAddingPowerGenFanSound();
void HandleRemovingPowerGenFanSound();

void HandleStartingFanBackUp();

void HandlePowerGenAlarm();


BOOLEAN HandlePlayerSayingQuoteWhenFailingToOpenGateInTunnel( SOLDIERTYPE *pSoldier, BOOLEAN fSayQuoteOnlyOnce );

void HandleHowPlayerGotThroughFan();

void RevealAllDroppedEnemyItems();

void HandlePlayingQuoteWhenHiringNpc( UINT8 ubProfile );


BOOLEAN LoadJa25TacticalInfoFromSavedGame( HWFILE hFile );
BOOLEAN SaveJa25TacticalInfoToSaveGame( HWFILE hFile );

BOOLEAN HandleNewGunComment( SOLDIERTYPE *pSoldier, INT32 iItemIndex, BOOLEAN fFromGround );
void HandleDeathInPowerGenSector( SOLDIERTYPE *pSoldier );

void		HandleJa25EnemyExpLevelModifier( );

INT8		RandomSoldierIdForAnyMercInSector();

void		HandleFanStartingAtEndOfCombat();

void		HandleInitialEventsInHeliCrash();

void		HandleCommanderMorrisNewMercWantsNoteDelayedSpeech();

void		DisplayCommanderMorrisNote( SOLDIERTYPE *pSoldier );

void		HandleShowingRadioLocatorsInMorrisArea();

void		HandleNewMercSayingContentsOfMorrisNote( SOLDIERTYPE *pSoldier );

void		HandlePlayerHittingSwitchToLaunchMissles();

void		HandleStartingEveryoneTalkingAtEndOfGame();

void		HandleFadingOutToEndGameCinematics();

void		HandleOpenControlPanelToRevealSwitchInMorrisArea();

void		InitNewGunArray();

#endif
