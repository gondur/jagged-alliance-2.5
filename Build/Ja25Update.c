#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
	#include "Ja25Update.h"
	#include "PreBattle Interface.h"
	#include "Strategic AI.h"
	#include "Ja25 Strategic Ai.h"
#endif


//** Defines *******************************************************************

//Starting money
#define JA2_5_STARTING_MONEY_EASY			40000
#define JA2_5_STARTING_MONEY_MEDIUM		35000
#define JA2_5_STARTING_MONEY_HARD			30000


#define	JA2SAVE_CONV_FILENAME		"..\\SavedGames\\Ja2.dts"

typedef struct
{
	INT8		bMercID;
	INT8		bPercentStatIncrease;
} STAT_CHANGE;

#define	NUM_MERCS_TO_USE_IN_PERCENT_STAT_INCREASE			6

#define	MAX_STAT_INCREASE															30

//******************************************************************************


//** GLOBAL VARIABLES ****************************************************************

STAT_CHANGE gJa2PlayerStatIncrease[NUM_MERCS_TO_USE_IN_PERCENT_STAT_INCREASE];
UINT8		gubTotalNumberMercsOnJa2PlayersTeam;
UINT32	guiTotalStatIncreaseFromMercsOnJa2PlayersTeam;


extern UINT32	guiJA2EncryptionSet;

extern	void GiveItemsToPC( UINT8 ubProfileId );

//******************************************************************************


//** Prototypes ****************************************************************

void		RemoveItemsFromMercAndAddItemsForJa25( MERCPROFILESTRUCT *pProfile );
//void ResetLaptopStatPages();
BOOLEAN LoadAndAddNewItemsToExistingSoldiers( MERCPROFILESTRUCT *pProfile, UINT8 ubMercID );
BOOLEAN LoadJa2ConvertedSaveAndReplaceProfiles();
UINT32	GetTotalStatIncreaseOfAllAimAndMercMercs();
UINT32	GetPercentImprovementForMerc( MERCPROFILESTRUCT *pNewMerc );

void		InsertNewPercentStatIncrease( INT8 bLevelPercentChange, INT8 bMercID );
void		CalculateDifficultyModifierForImportedGames();
UINT8		IncreaseEnemiesBasedOnJA2PlayerStatIncrease( UINT8 ubNumEnemies, INT8 bPercentStatIncrease );
INT8		CalculateAveragePercentStatIncreaseForTopMercs();
//ppp

//******************************************************************************




void RemoveItemsFromMercAndAddItemsForJa25( MERCPROFILESTRUCT *pProfile )
//void RemoveItemsFromMercAndAddItemsForJa25( SOLDIERTYPE *pSoldier, 	MERCPROFILESTRUCT *pProfile )
{
	UINT32 uiInvSlot;

	//loop through all the mercs pockets
	for( uiInvSlot=0; uiInvSlot<NUM_INV_SLOTS; uiInvSlot++)
	{
		//Get riD of the item
		pProfile->inv[ uiInvSlot ] = NONE;

//		DeleteObj( &pSoldier->inv[ uiInvSlot ] );
	}

	//Add code to get any "new" item from the new profile data
}

/*
void ResetLaptopStatPages()
{
	//Delete the existing list of emails
	ShutDownEmailList();

	//Remove the new email laptop sign
	fNewMailFlag = FALSE;

	// unlink history file
	FileClearAttributes( HISTORY_DATA_FILE );
	FileDelete( HISTORY_DATA_FILE );
	ClearHistoryList( );


	FileClearAttributes( FINANCES_DATA_FILE );
	FileDelete( FINANCES_DATA_FILE );
  ClearFinanceList( );
}
*/

BOOLEAN LoadAndAddNewItemsToExistingSoldiers( MERCPROFILESTRUCT *pProfile, UINT8 ubMercID )
{
	HWFILE hFile;
	UINT32 uiDistToMove;
	MERCPROFILESTRUCT DummyProfile;
	UINT32 uiInvSlot;
	UINT32 uiNumBytesRead;

	//open the file
	hFile = FileOpen( JA25_PROF_DAT, FILE_ACCESS_READ, FALSE );
	if( !hFile )
	{
		DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String("FAILED to LoadAndAddNewItemsToExistingSoldiers for merc: %s", pProfile->zName ) );
		return(FALSE);
	}

	//if the merc is the IMP merc
	if( ubMercID > BUBBA && ubMercID < GASTON )
	{
		//set the merc to get the equipment from the first pgc profile
//		ubMercID = 51;
	}

	//seek to the proper spot in the file
	uiDistToMove = sizeof( MERCPROFILESTRUCT ) * ubMercID;
	if( FileSeek( hFile, uiDistToMove, FILE_SEEK_FROM_START ) != 1 )
	{
		DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String("FAILED to seek to Merc ID: %d inLoadAndAddNewItemsToExistingSoldiers for merc: %s", ubMercID, pProfile->zName ) );
		FileClose( hFile );
		return(FALSE);
	}

	//Read in the mercs data
	if( JA2EncryptedFileRead( hFile, &DummyProfile, sizeof( MERCPROFILESTRUCT ), &uiNumBytesRead )  != 1)
	{
		DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "FAILED to Read Merc Profiles from File %d %s",ubMercID, pProfile->zName ) );
		FileClose( hFile );
		return(FALSE);
	}

	//copy over the mercs inventory
	for( uiInvSlot=0; uiInvSlot<NUM_INV_SLOTS; uiInvSlot++)
	{
		//Get the item from the dummy profile
		pProfile->inv[ uiInvSlot ] = DummyProfile.inv[ uiInvSlot ];
		pProfile->bInvStatus[ uiInvSlot ] = DummyProfile.bInvStatus[ uiInvSlot ];
		pProfile->bInvNumber[ uiInvSlot ] = DummyProfile.bInvNumber[ uiInvSlot ];

		if( pProfile->inv[ uiInvSlot ] != NONE )
		{
			//Create the item
//			CreateItems( pProfile->inv[ uiInvSlot ], pProfile->bInvStatus[ uiInvSlot ], pProfile->bInvNumber[ uiInvSlot ], &Obj );

			//add the item to the soldier
//			AutoPlaceObject( pSoldier, &Obj, TRUE );
		}
	}

	//if the merc is the IMP merc
	if( ubMercID > BUBBA && ubMercID < FIRST_RPC )
	{
		//They get their equipment another way
		//Call the Function that distrubutes the item when the IMP is first created
		GiveItemsToPC( ubMercID );
	}

	FileClose( hFile );
	return( TRUE );
}

BOOLEAN ImportOldProfilesAndProcessThem()
{
	UINT32 uiCnt;
	MERCPROFILESTRUCT *pProfile;
//	SOLDIERCREATE_STRUCT		MercCreateStruct;
//	UINT8	ubNewIndex;

	//Designate the new arrival point
	gsMercArriveSectorX = JA2_5_START_SECTOR_X;
	gsMercArriveSectorY = JA2_5_START_SECTOR_Y;

	//load in the converted save
	if( !LoadJa2ConvertedSaveAndReplaceProfiles() )
	{
		return( FALSE );
	}

	//loop through and adjust their inventorires
	for( uiCnt=0; uiCnt<GASTON; uiCnt++)
	{
		pProfile = &gMercProfiles[uiCnt];

		//Remove the old items
		RemoveItemsFromMercAndAddItemsForJa25( pProfile );

		//Add the proper items to the merc
		LoadAndAddNewItemsToExistingSoldiers( pProfile, (UINT8)uiCnt );

		//Ja25:  No optional gear cost in the exp		
		pProfile->usOptionalGearCost = 0;
		/*
		Ja25:  No optional gear cost in the exp		
				//Calculate the mercs optional gear cost
				CalculateMercsOptionalGearCost( pProfile );
		*/

		//reassign the total kills & assists from ja2 to to a new variable
		pProfile->usTotalKills = pProfile->usKills;
		pProfile->usTotalAssists = pProfile->usAssists;

		//Reset specific variables
		pProfile->usKills = 0;
		pProfile->usAssists = 0;
		pProfile->usTimesWounded = 0;
		pProfile->usBattlesFought = 0;
		pProfile->usShotsHit = 0;
		pProfile->usShotsFired = 0;

		//Reset the exp level gains ( so players wont immediatgely level when importing )
		//might want to scale stats as a percentage of jha2 values ( so player is always 80%  close to leveling )
		pProfile->sLifeGain = 0;
		pProfile->sLeadershipGain = 0;
		pProfile->sStrengthGain = 0;
		pProfile->sExpLevelGain = 0;
		pProfile->sLifeGain = 0;
		pProfile->sAgilityGain = 0;
		pProfile->sDexterityGain = 0;
		pProfile->sWisdomGain = 0;
		pProfile->sMarksmanshipGain = 0;
		pProfile->sMedicalGain = 0;
		pProfile->sMechanicGain = 0;
		pProfile->sExplosivesGain = 0;

		if ( pProfile->bLife > 0 )
		{
			pProfile->bLife = pProfile->bLifeMax;
		}

		//if the merc is an AIM merc or MERC merc
		if( uiCnt <= BUBBA )
		{
			//Make sure the merc is an aim or merc merc
			if( !IsProfileIdAnAimOrMERCMerc( (UINT8)uiCnt ) )
			{
				continue;
			}

			//if the merc is alive, and not on assignment elswhere
//			if( pProfile->bLife > 0 && pProfile->bMercStatus != MERC_WORKING_ELSEWHERE )
			if( pProfile->bLife > 0 && pProfile->bMercStatus >= MERC_HAS_NO_TEXT_FILE )
			{
				//Set the merc "ready"
				pProfile->uiDayBecomesAvailable = 0;
				pProfile->bMercStatus = MERC_OK;			

				//Reset the fact that we have bought the mercs inventory
				pProfile->ubMiscFlags &= ~PROFILE_MISC_FLAG_ALREADY_USED_ITEMS;
			}
			else
			{
				int i=0;
			}
			continue;
		}

		//if the merc is the IMP merc
		if( uiCnt > BUBBA && uiCnt < FIRST_RPC )
		{
			//if the merc is alive
			if( pProfile->bActive && pProfile->bLife > 0 && pProfile->bMercStatus >= MERC_HAS_NO_TEXT_FILE )
			{
				MERC_HIRE_STRUCT HireMercStruct;

				//Add the proper items to the merc
//				LoadAndAddNewItemsToExistingSoldiers( pProfile, uiCnt );

				pProfile->bMercStatus = MERC_OK;			

				memset(&HireMercStruct, 0, sizeof(MERC_HIRE_STRUCT));

				HireMercStruct.ubProfileID = uiCnt;

				HireMercStruct.sSectorX = gsMercArriveSectorX;
				HireMercStruct.sSectorY = gsMercArriveSectorY;
				HireMercStruct.bSectorZ = 0;
				HireMercStruct.fUseLandingZoneForArrival = TRUE;
				HireMercStruct.ubInsertionCode	= INSERTION_CODE_ARRIVING_GAME;

				HireMercStruct.fCopyProfileItemsOver = TRUE;

				HireMercStruct.uiTimeTillMercArrives = GetMercArrivalTimeOfDay( );// + ubCurrentSoldier;

				HireMerc( &HireMercStruct );
			}
		}
	}


	// Get the total Stat increase 
//	GetTotalStatIncreaseOfAllAimAndMercMercs();
	CalculateDifficultyModifierForImportedGames();

	//Modify the enemies to make them harder
	HandleDifficultyModifierForImportedGames();

	//Remeber that we are continuing from an imported save
	SetFactTrue( FACT_PLAYER_IMPORTED_SAVE );

	// initialize mercs' status
	StartSomeMercsOnAssignment( );

	return( TRUE );
}


BOOLEAN LoadJa2ConvertedSaveAndReplaceProfiles()
{
	UINT16	cnt;
	UINT32	uiNumBytesRead=0;
	HWFILE	hFile;
	SAVED_GAME_HEADER SaveGameHeader;
	UINT8 ubQuest[MAX_QUESTS];
	UINT8 ubFact[NUM_FACTS];
	MERCPROFILESTRUCT DummyMercProfiles;
	BOOLEAN	fJohnKulbaWasAlive=FALSE;
	UINT32	uiWeeklySalary;

	hFile = FileOpen( JA2SAVE_CONV_FILENAME, FILE_ACCESS_READ | FILE_OPEN_EXISTING, FALSE );
	if( !hFile )
	{
		return(FALSE);
	}


	FileRead( hFile, &SaveGameHeader, sizeof( SAVED_GAME_HEADER ), &uiNumBytesRead );
	if( uiNumBytesRead != sizeof( SAVED_GAME_HEADER ) )
	{
		FileClose( hFile );
		return(FALSE);
	}


	//Calc the encryption key
	guiJA2EncryptionSet = CalcJA2EncryptionSet( &SaveGameHeader );



	//Loop through all the profiles to Load ( goes up to gaston cause that WAS the first RPC
	for( cnt=0; cnt<NUM_PROFILES; cnt++)
	{
		//Only overwrite the profiles up to the last MERC merc
		if( cnt< 57 )
		{
//			NewJA2EncryptedFileRead( hFile, &gMercProfiles[cnt], sizeof( MERCPROFILESTRUCT ), &uiNumBytesRead );
			NewJA2EncryptedFileRead( hFile, &DummyMercProfiles, sizeof( MERCPROFILESTRUCT ), &uiNumBytesRead );
			if( uiNumBytesRead != sizeof( MERCPROFILESTRUCT ) )
			{
				FileClose( hFile );
				return(FALSE);
			}

//			if ( gMercProfiles[ cnt ].uiProfileChecksum != ProfileChecksum( &(gMercProfiles[ cnt ]) ) )
			if ( DummyMercProfiles.uiProfileChecksum != ProfileChecksum( &(DummyMercProfiles) ) )
			{
				FileClose( hFile );
				return( FALSE );
			}

			//Remeber his salary
			uiWeeklySalary = gMercProfiles[cnt].uiWeeklySalary;

			//copy over the new data
			memcpy( &gMercProfiles[cnt], &DummyMercProfiles, sizeof( MERCPROFILESTRUCT ) );

			//replace the salary field
			gMercProfiles[cnt].uiWeeklySalary = uiWeeklySalary;
		}
		else
		{
			NewJA2EncryptedFileRead( hFile, &DummyMercProfiles, sizeof( MERCPROFILESTRUCT ), &uiNumBytesRead );
			if( uiNumBytesRead != sizeof( MERCPROFILESTRUCT ) )
			{
				FileClose( hFile );
				return(FALSE);
			}

			if ( DummyMercProfiles.uiProfileChecksum != ProfileChecksum( &(DummyMercProfiles) ) )
			{
				FileClose( hFile );
				return( FALSE );
			}

			//if this was profile was John Kulba
			if( cnt == 118 )
			{
				//if john was still alive
				if( DummyMercProfiles.bLife > 0 )
					fJohnKulbaWasAlive = TRUE;
				else
					fJohnKulbaWasAlive = FALSE;
			}

			//if this was profile was Mary Kulba
			if( cnt == 119 )
			{
				//if Mary was still alive
				if( DummyMercProfiles.bLife > 0 )
					SetFactFalse( FACT_IMPORTED_SAVE_AND_MARY_WAS_DEAD );
				else
					SetFactTrue( FACT_IMPORTED_SAVE_AND_MARY_WAS_DEAD );
			}

			//if this was profile was Miguel
			if( cnt == 57 )
			{
				//if Miguel was still alive
				if( DummyMercProfiles.bLife > 0 )
					SetFactFalse( FACT_PLAYER_IMPORTED_SAVE_MIGUEL_DEAD );
				else
					SetFactTrue( FACT_PLAYER_IMPORTED_SAVE_MIGUEL_DEAD );
			}

			//if this was profile was Fatima or Pacos
			if( cnt == 101 || cnt == 114 )
			{
				//if Fatima or Pacos was still alive
				if( DummyMercProfiles.bLife > 0 )
					SetFactFalse( FACT_PLAYER_IMPORTED_SAVE_FATIMA_OR_PACOS_DEAD );
				else
					SetFactTrue( FACT_PLAYER_IMPORTED_SAVE_FATIMA_OR_PACOS_DEAD );
			}

			//if this was profile was Carlos
			if( cnt == 58 )
			{
				//if Carlos was still alive
				if( DummyMercProfiles.bLife > 0 )
					SetFactFalse( FACT_PLAYER_IMPORTED_SAVE_CARLOS_DEAD );
				else
					SetFactTrue( FACT_PLAYER_IMPORTED_SAVE_CARLOS_DEAD );
			}

			//if this was profile was Ira
			if( cnt == 59 )
			{
				//if Ira was still alive
				if( DummyMercProfiles.bLife > 0 )
					SetFactFalse( FACT_PLAYER_IMPORTED_SAVE_IRA_DEAD );
				else
					SetFactTrue( FACT_PLAYER_IMPORTED_SAVE_IRA_DEAD );
			}

			//if this was profile was Dimitri
			if( cnt == 60 )
			{
				//if Dimitri was still alive
				if( DummyMercProfiles.bLife > 0 )
					SetFactFalse( FACT_PLAYER_IMPORTED_SAVE_DIMITRI_DEAD );
				else
					SetFactTrue( FACT_PLAYER_IMPORTED_SAVE_DIMITRI_DEAD );
			}

			//if this was profile was Biff
			if( cnt == 40 )
			{
				//if Biff was still alive
				if( DummyMercProfiles.bLife > 0  && DummyMercProfiles.bMercStatus >= MERC_HAS_NO_TEXT_FILE )
					gJa25SaveStruct.fBiffWasKilledWhenImportingSave = FALSE;
				else
					gJa25SaveStruct.fBiffWasKilledWhenImportingSave = TRUE;
			}


		}
	}

	//load the quest and facts from the converted save

	//load all the states if the Quests
	FileRead( hFile, ubQuest, MAX_QUESTS, &uiNumBytesRead );
	if( uiNumBytesRead != MAX_QUESTS )
	{
		FileClose( hFile );
		return(FALSE);
	}

	//load all the states for the facts
	FileRead( hFile, ubFact, NUM_FACTS, &uiNumBytesRead );
	if( uiNumBytesRead != NUM_FACTS )
	{
		FileClose( hFile );
		return(FALSE);
	}

	FileClose( hFile );


	//if the player succesfully escorted John Kulba & John was alive, then john will be available
	if( ubQuest[19] == QUESTDONE )
	{
		//John is available
		gJa25SaveStruct.fJohnKulbaIsInGame = TRUE;

		//Tex is not
		SetFactFalse( FACT_TEX_IS_IN_GAME_AND_ALIVE_IN_STORE );
	}
	else
	{
		//John is not available
		gJa25SaveStruct.fJohnKulbaIsInGame = FALSE;

		//Tex is 
		SetFactTrue( FACT_TEX_IS_IN_GAME_AND_ALIVE_IN_STORE );
	}


	return( TRUE );
}

void GivePlayerStartingJa25Money()
{
	INT32	iStartingCash=0;

	switch( gGameOptions.ubDifficultyLevel )
	{
		case DIF_LEVEL_EASY:
			iStartingCash	= JA2_5_STARTING_MONEY_EASY;
			break;

		case DIF_LEVEL_MEDIUM:
			iStartingCash	= JA2_5_STARTING_MONEY_MEDIUM;
			break;

		case DIF_LEVEL_HARD:
			iStartingCash	= JA2_5_STARTING_MONEY_HARD;
			break;

		default:
			Assert(0);
	}


	//add the players starting money
	AddTransactionToPlayersBook( ANONYMOUS_DEPOSIT, 0, GetWorldTotalMin(), iStartingCash );
}


UINT32 GetTotalStatIncreaseOfAllAimAndMercMercs()
{
	UINT32 uiCnt;
	MERCPROFILESTRUCT *pProfile;
//	MERCPROFILESTRUCT *pOldProfile;


	UINT32 uiTotalStatIncreaseNeverHired=0;
	UINT32 uiTotalStatIncrease=0;

	UINT32 uiTotalMarksmanship=0;
	UINT32 uiTotalAgility=0;
	UINT32 uiTotalDexterity=0;
	UINT32 uiTotalStrength=0;//
	UINT32 uiTotalWisdom=0;
	UINT32 uiTotalLeadership=0;//
	UINT32 uiTotalMedical=0;
	UINT32 uiTotalMechanical=0;
	UINT32 uiTotalExplosives=0;
	UINT32 uiTotalLife=0;	//
	UINT32 uiTotalExpGain=0;

	//loop through and adjust their inventorires
	for( uiCnt=0; uiCnt<BUBBA; uiCnt++)
	{
		pProfile = &gMercProfiles[uiCnt];

		uiTotalExpGain = pProfile->sExpLevelGain;
		uiTotalMarksmanship += pProfile->sMarksmanshipGain;
/*
		
		uiTotalLife					+= pProfile->sLifeGain;
		uiTotalAgility			+= pProfile->sAgilityGain;
		uiTotalDexterity		+= pProfile->sDexterityGain;
		uiTotalWisdom				+= pProfile->sWisdomGain;
		uiTotalMarksmanship += pProfile->sMarksmanshipGain;
		uiTotalMedical			+= pProfile->sMedicalGain;
		uiTotalMechanical		+= pProfile->sMechanicGain;
		uiTotalExplosives		+= pProfile->sExplosivesGain;
		uiTotalStrength			+= pProfile->sStrengthGain;
		uiTotalLeadership		+= pProfile->sLeadershipGain;
*/
		if( pProfile->usTotalDaysServed == 0 )
		{
//			uiTotalStatIncreaseNeverHired += pProfile->sLifeGain + pProfile->sAgilityGain + pProfile->sDexterityGain + pProfile->sWisdomGain + pProfile->sMarksmanshipGain + pProfile->sMedicalGain + pProfile->sMechanicGain + pProfile->sExplosivesGain;
			uiTotalStatIncreaseNeverHired += pProfile->sMarksmanshipGain + ( pProfile->sExpLevelGain * 10 );
		}
		else
		{
			INT32 i =0;
		}
	}

	uiTotalStatIncrease = uiTotalMarksmanship + 
												uiTotalAgility +
												uiTotalDexterity +
												uiTotalStrength +
												uiTotalWisdom +
												uiTotalLeadership +
												uiTotalMedical +
												uiTotalMechanical +
												uiTotalExplosives +
												uiTotalLife;

	return( uiTotalStatIncrease );
}

UINT32 GetPercentImprovementForMerc( MERCPROFILESTRUCT *pNewMerc )
{
	UINT32 uiPercentImprovement=0;
	UINT32 uiMarksmanshipPercentChange=0;
	UINT32 uiLevelPercentChange=0;


	//Marksmanship
	uiMarksmanshipPercentChange = pNewMerc->bMarksmanshipDelta;

	//Level
	uiLevelPercentChange = pNewMerc->bExpLevelDelta * 10;

	uiPercentImprovement = ( uiMarksmanshipPercentChange + uiLevelPercentChange ) / 2;

	return( uiPercentImprovement);
}

void CalculateDifficultyModifierForImportedGames()
{
	UINT8 ubMercID;
	UINT32 uiLevelPercentChange;
	MERCPROFILESTRUCT *pProfile=NULL;
	UINT8	ubNumber=0;
	UINT32 uiTotalStatIncrease=0;

	//Reset
	memset( gJa2PlayerStatIncrease, -1, sizeof( STAT_CHANGE ) * NUM_MERCS_TO_USE_IN_PERCENT_STAT_INCREASE );

	gubTotalNumberMercsOnJa2PlayersTeam = 0;
	guiTotalStatIncreaseFromMercsOnJa2PlayersTeam = 0;

	for( ubMercID=0; ubMercID<GASTON; ubMercID++ )
	{
		pProfile = &gMercProfiles[ubMercID];

		//if the merc is the IMP merc
		if( !( ( ubMercID <= BUBBA ) || ( ubMercID > BUBBA && ubMercID < GASTON && pProfile->usTotalDaysServed > 0 ) ) )
		{
			continue;
		}

		//if this merc shouldnt be included
		if( pProfile->usTotalDaysServed < 10 )
		{
			continue;
		}

		uiLevelPercentChange = GetPercentImprovementForMerc( &gMercProfiles[ ubMercID ] );

		InsertNewPercentStatIncrease( (INT8) uiLevelPercentChange, ubMercID );

		//IF A MERC improved in the required stats
		if( uiLevelPercentChange > 0 )
		{
			gubTotalNumberMercsOnJa2PlayersTeam++;
			guiTotalStatIncreaseFromMercsOnJa2PlayersTeam += uiLevelPercentChange;
		}
	}
}

void InsertNewPercentStatIncrease( INT8 bLevelPercentChange, INT8 bMercID )
{
	UINT8 ubCnt;
	INT8	iTempStat_1;
	INT8	iTempID_1;

	INT8	iTempStat_2;
	INT8	iTempID_2;


	//if the new stat is greater then the lowest recorded stat
	if( bLevelPercentChange > gJa2PlayerStatIncrease[ NUM_MERCS_TO_USE_IN_PERCENT_STAT_INCREASE -1 ].bPercentStatIncrease )
	{
		iTempStat_1 = gJa2PlayerStatIncrease[0].bPercentStatIncrease;
		iTempID_1 = gJa2PlayerStatIncrease[0].bMercID;

		for( ubCnt=0; ubCnt<NUM_MERCS_TO_USE_IN_PERCENT_STAT_INCREASE; ubCnt++ )
		{
			iTempStat_2 = gJa2PlayerStatIncrease[ubCnt].bPercentStatIncrease;
			iTempID_2 = gJa2PlayerStatIncrease[ubCnt].bMercID;

			if( bLevelPercentChange > gJa2PlayerStatIncrease[ubCnt].bPercentStatIncrease )
			{
				gJa2PlayerStatIncrease[ubCnt].bPercentStatIncrease = bLevelPercentChange;
				gJa2PlayerStatIncrease[ubCnt].bMercID = bMercID;

				//so we dont use it again
				bLevelPercentChange=-1;
			}
			else if( bLevelPercentChange != -1 )
			{
				iTempStat_1 = iTempStat_2;
				iTempID_1 = iTempID_2;
			}
			else
			{
				gJa2PlayerStatIncrease[ubCnt].bPercentStatIncrease = iTempStat_1;
				gJa2PlayerStatIncrease[ubCnt].bMercID = iTempID_1;
			}

			iTempStat_1 = iTempStat_2;
			iTempID_1 = iTempID_2;
		}
	}
}


UINT32 HandleDifficultyModifierForImportedGames()
{
	INT16	iSectorCnt;
	INT8 bAverageStatIncrease=0;
	UINT32 uiTotalNumAdditionalEnemies=0;
	UINT8		ubNumberElites=0;
	UINT8		ubNumberRegular=0;
	UINT8		ubNumberAdmins=0;
	SECTORINFO *pSector;
	INT32		iTotalNum=0;

	bAverageStatIncrease = CalculateAveragePercentStatIncreaseForTopMercs();

//	if( gubTotalNumberMercsOnJa2PlayersTeam > 0 )
//		bAverageStatIncrease = (INT8)(guiTotalStatIncreaseFromMercsOnJa2PlayersTeam / gubTotalNumberMercsOnJa2PlayersTeam );


	//loop through all the sector and see if there has been 
	for( iSectorCnt=0; iSectorCnt<256 ; iSectorCnt++ )
	{
		ubNumberElites=0;
		ubNumberRegular=0;
		ubNumberAdmins=0;

		//
		//if there are any enemies, increase them...
		//

		pSector = &SectorInfo[ iSectorCnt ];

		//if there are no enemies in this sector
		if( pSector->ubNumAdmins == 0 && pSector->ubNumTroops == 0 && pSector->ubNumElites == 0 )
		{
			continue;
		}


		if( pSector->ubNumAdmins )
		{
			ubNumberAdmins = IncreaseEnemiesBasedOnJA2PlayerStatIncrease( pSector->ubNumAdmins, bAverageStatIncrease );
		}


		if( pSector->ubNumTroops )
		{
			ubNumberRegular = IncreaseEnemiesBasedOnJA2PlayerStatIncrease( pSector->ubNumTroops, bAverageStatIncrease );
		}

		if( pSector->ubNumElites )
		{
			ubNumberElites = IncreaseEnemiesBasedOnJA2PlayerStatIncrease( pSector->ubNumElites, bAverageStatIncrease );
		}

		//add up all the enemies that can be in the sector
		iTotalNum = pSector->ubNumElites + ubNumberElites + 
								pSector->ubNumTroops + ubNumberRegular + 
								pSector->ubNumAdmins + ubNumberAdmins;

		//if there will be more then 32
		if( iTotalNum > 32 )
		{
			INT32 iNumOver = iTotalNum - 32; 

			//
			// We must reduce the amount of enemies to be no more then 32
			//

			//if there are admins, reduce them
			if( pSector->ubNumAdmins )
			{
				//admins
				if( iNumOver > ubNumberAdmins )
				{
					iNumOver -= ubNumberAdmins;
					ubNumberAdmins=0;
				}
				else
				{
					ubNumberAdmins -= iNumOver;
					iNumOver = 0;
				}
			}

			//if there are admins, reduce them
			if( pSector->ubNumTroops )
			{
				//regulare
				if( iNumOver > ubNumberRegular )
				{
					iNumOver -= ubNumberRegular;
					ubNumberRegular=0;
				}
				else
				{
					ubNumberRegular -= iNumOver;
					iNumOver = 0;
				}
			}

			//if there are elites, reduce them
			if( pSector->ubNumElites )
			{
				//elites
				if( iNumOver > ubNumberElites )
				{
					iNumOver -= ubNumberElites;
					ubNumberElites=0;
				}
				else
				{
					ubNumberElites -= iNumOver;
					iNumOver = 0;
				}
			}
		}

		pSector->ubNumElites += ubNumberElites;
		pSector->ubNumTroops += ubNumberRegular;
		pSector->ubNumAdmins += ubNumberAdmins;

		uiTotalNumAdditionalEnemies = ubNumberRegular + ubNumberRegular + ubNumberAdmins ;
	}
	return( uiTotalNumAdditionalEnemies );
}

UINT8 IncreaseEnemiesBasedOnJA2PlayerStatIncrease( UINT8 ubNumEnemies, INT8 bPercentStatIncrease )
{
	UINT8 ubIncrease=0;
	

	//Make sure the increase isnt to high
	if( bPercentStatIncrease > MAX_STAT_INCREASE )
	{
		bPercentStatIncrease = MAX_STAT_INCREASE;
	}

	switch( gGameOptions.ubDifficultyLevel )
	{
		case DIF_LEVEL_EASY:
			bPercentStatIncrease = bPercentStatIncrease / 2;
			break;
		case DIF_LEVEL_MEDIUM:
			//no change to stat
			break;
		case DIF_LEVEL_HARD:
			//increase the count by 10 percent
			bPercentStatIncrease += 10;
			break;
	}



	ubIncrease = (UINT8)( ubNumEnemies * ( bPercentStatIncrease / (FLOAT)100 ) );

	//make sure we dont go over the max
	if( ( ubNumEnemies + ubIncrease ) > 30 )
	{
		ubIncrease = 30 - ubNumEnemies;
	}

	return( ubIncrease );
}

INT8 CalculateAveragePercentStatIncreaseForTopMercs()
{
	UINT8 ubCnt;

	UINT8 ubTotal=0;
	UINT8	ubNumber=0;

	for( ubCnt=0; ubCnt<NUM_MERCS_TO_USE_IN_PERCENT_STAT_INCREASE; ubCnt++ )
	{
		if( gJa2PlayerStatIncrease[ubCnt].bPercentStatIncrease != -1 )
		{
			ubTotal += gJa2PlayerStatIncrease[ubCnt].bPercentStatIncrease;
			ubNumber++;
		}
	}

	if( ubNumber == 0 )
		return( 0 );
	else
		return( ubTotal / ubNumber );
}


BOOLEAN DoesJa25ImportSaveExistAndSeemValid()
{
	HWFILE	hFile=0;
	UINT32	uiFileSize=0;

	//make sure we can open the file
	hFile = FileOpen( JA2SAVE_CONV_FILENAME, FILE_ACCESS_READ | FILE_OPEN_EXISTING, FALSE );
	if( !hFile )
	{
		return(FALSE);
	}

	FileClose( hFile );

	//See if the file contains anything
	uiFileSize = FileSize( JA2SAVE_CONV_FILENAME );

	if( uiFileSize == 0 )
	{
		return( FALSE );
	}

	//
	// Everything 'seems' ok
	//
	return( TRUE );
}