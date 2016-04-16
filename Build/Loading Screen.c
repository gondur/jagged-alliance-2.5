#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
	#include "Loading Screen.h"
	#include "Ja25 Strategic Ai.h"
#else
	//???
#endif

extern HVSURFACE ghFrameBuffer;

extern JA25_SECTOR_AI	*gJa25AiSectorStruct;

UINT8 ErrorLoadScreen( BOOLEAN fNight, UINT32 uiLineNumber );


UINT8 gubLastLoadingScreenID = LOADINGSCREEN_NOTHING;

//returns the UINT8 ID for the specified sector.
UINT8 GetLoadScreenID( INT16 sSectorX, INT16 sSectorY, INT8 bSectorZ )
{
	SECTORINFO *pSector;
	UINT8 ubSectorID;
	BOOLEAN fNight = FALSE;
	INT16		sJa25SaiSectorValue;

	ubSectorID = SECTOR( sSectorX, sSectorY );
	if( NightTime() ) //before 5AM or after 9PM
	{
		fNight = TRUE;
	}

	// OK, get JA25 AI information, this will tell us if we are a custom map
	sJa25SaiSectorValue = GetJA25SectorID( sSectorX, sSectorY, bSectorZ );
	
	if( sJa25SaiSectorValue != -1 && gJa25AiSectorStruct[ sJa25SaiSectorValue ].fCustomSector )
	{
		// OK, ID depends on day or night
		switch( gJa25AiSectorStruct[ sJa25SaiSectorValue ].ubLoadingScreenID )
		{
			case LOADINGSCREEN_DAY_SNOW:

				if ( fNight )
					return( LOADINGSCREEN_NIGHT_SNOW );
				return( LOADINGSCREEN_DAY_SNOW );
				break;

			case LOADINGSCREEN_GUARDPOST_DAY:

				if ( fNight )
					return( LOADINGSCREEN_GUARDPOST_NIGHT );
				return( LOADINGSCREEN_GUARDPOST_DAY );
				break;

			case LOADINGSCREEN_POWERPLANT_DAY:

				if ( fNight )
					return( LOADINGSCREEN_POWERPLANT_NIGHT );
				return( LOADINGSCREEN_POWERPLANT_DAY );
				break;

			case LOADINGSCREEN_DAYGENERIC:

				if ( fNight )
					return( LOADINGSCREEN_NIGHTGENERIC );
				return( LOADINGSCREEN_DAYGENERIC );
				break;

			case LOADINGSCREEN_DAYTOWN1:

				if ( fNight )
					return( LOADINGSCREEN_NIGHTTOWN1 );
				return( LOADINGSCREEN_DAYTOWN1 );
				break;

			case LOADINGSCREEN_DAYTOWN2:

				if ( fNight )
					return( LOADINGSCREEN_NIGHTTOWN2 );
				return( LOADINGSCREEN_DAYTOWN2 );
				break;

			case LOADINGSCREEN_DAYFOREST:

				if ( fNight )
					return( LOADINGSCREEN_NIGHTFOREST );
				return( LOADINGSCREEN_DAYFOREST );
				break;

			case LOADINGSCREEN_MINE:

				return( LOADINGSCREEN_MINE );
				break;

			case LOADINGSCREEN_CAVE:

				return( LOADINGSCREEN_CAVE );
				break;

			case LOADINGSCREEN_DAYPINE:

				if ( fNight )
					return( LOADINGSCREEN_NIGHTPINE );
				return( LOADINGSCREEN_DAYPINE );
				break;

			case LOADINGSCREEN_DAYMINE:

				if ( fNight )
					return( LOADINGSCREEN_NIGHTMINE );
				return( LOADINGSCREEN_DAYMINE );
				break;

			case LOADINGSCREEN_DAYWILD:

				if ( fNight )
					return( LOADINGSCREEN_NIGHTWILD );
				return( LOADINGSCREEN_DAYWILD );
				break;

			case LOADINGSCREEN_COMPLEX_BASEMENT_GENERIC:

				return( LOADINGSCREEN_COMPLEX_BASEMENT_GENERIC );
				break;
		}

		if ( fNight )
			return( LOADINGSCREEN_NIGHTGENERIC );
		return( LOADINGSCREEN_DAYGENERIC );

	}


	switch( bSectorZ )
	{
		case 0:
		{
			switch( ubSectorID )
			{
				case SEC_H7:
					{
//						if( DidGameJustStart() )
						//if the player has never gone to H8, then we can still view the heli crash
						if( !GetSectorFlagStatus( 8, 8, 0, SF_ALREADY_VISITED ) )
						{
							return LOADINGSCREEN_HELI_CRASH;
						}
						else
						{
							if( fNight )
								return LOADINGSCREEN_NIGHT_SNOW;
							return LOADINGSCREEN_DAY_SNOW;
						}
					}
					break;

				case SEC_H8:
					{
						if( fNight )
							return LOADINGSCREEN_NIGHT_SNOW;
						return LOADINGSCREEN_DAY_SNOW;
					}
					break;

				//guard post
				case SEC_H9:
					{
						if( fNight )
							return LOADINGSCREEN_GUARDPOST_NIGHT;
						return LOADINGSCREEN_GUARDPOST_DAY;
					}
					break;

				case SEC_H11:
					{
						if( fNight )
							return LOADINGSCREEN_NIGHTGENERIC;
						return LOADINGSCREEN_DAYGENERIC;
					}
					break;

				case SEC_K16:
				case SEC_H10:
				case SEC_I9:
					{
						if( fNight )
							return LOADINGSCREEN_NIGHTPINE;
						return LOADINGSCREEN_DAYPINE;
					}
					break;

				case SEC_I10:
				case SEC_I11:
					{
						pSector = &SectorInfo[ ubSectorID ];
						switch( pSector->ubTraversability[ 4 ] )
						{
							case TOWN:
							{
								if( fNight )
								{
									if( Random( 2 ) )
										return LOADINGSCREEN_NIGHTTOWN2;
									else
										return LOADINGSCREEN_NIGHTTOWN1;
								}
								if( Random( 2 ) )
									return LOADINGSCREEN_DAYTOWN2;
								else
									return LOADINGSCREEN_DAYTOWN1;
							}
						}
						return( LOADINGSCREEN_NOTHING );
					}
					break;

				case SEC_I12:
				case SEC_J11:
					{
						if( fNight )
							return LOADINGSCREEN_NIGHTWILD;
						return LOADINGSCREEN_DAYWILD;
					}
					break;

				case SEC_J12:
					{
						if( fNight )
							return LOADINGSCREEN_NIGHTFOREST;
						return LOADINGSCREEN_DAYFOREST;
					}
					break;

				case SEC_I13:
					{
						if( fNight )
							return LOADINGSCREEN_NIGHTMINE;
						return LOADINGSCREEN_DAYMINE;
					}
					break;

				//Power plant
				case SEC_J13:
					{
						if( fNight )
							return LOADINGSCREEN_POWERPLANT_NIGHT;
						return LOADINGSCREEN_POWERPLANT_DAY;
					}
					break;

				//Complex
				case SEC_K15:
					{
						if( fNight )
							return LOADINGSCREEN_COMPLEX_TOP_LEVEL_NIGHT;
						return LOADINGSCREEN_COMPLEX_TOP_LEVEL_DAY;
					}
					break;

				default:
					return( ErrorLoadScreen( fNight, __LINE__ ) );
			}
		}
		break;

		case 1:
		{
			switch( ubSectorID )
			{
				case SEC_I13:
				case SEC_J13:
				{
					if( fNight )
						return LOADINGSCREEN_MINE;
					return LOADINGSCREEN_MINE;
					break;
				}

				//tunnels
				case SEC_J14:
				case SEC_K14:
				{
					return LOADINGSCREEN_TUNNELS;
					break;
				}

				case SEC_K15:
				{
					if( gJa25SaveStruct.ubLoadScreenStairTraversal == LS__GOING_UP_STAIRS )
						return( LOADINGSCREEN_UP_STAIRS );
					else if( gJa25SaveStruct.ubLoadScreenStairTraversal == LS__GOING_DOWN_STAIRS )
						return( LOADINGSCREEN_DOWN_STAIRS );
					else
						return( LOADINGSCREEN_COMPLEX_BASEMENT_GENERIC );
					break;
				}
				default:
					return( ErrorLoadScreen( fNight, __LINE__ ) );
			}
		}
		case 2:
		{
			switch( ubSectorID )
			{
				case SEC_K15:
				{	
					//if we are going up stairs, else traversing at same level
					if( gJa25SaveStruct.ubLoadScreenStairTraversal == LS__GOING_UP_STAIRS )
						return( LOADINGSCREEN_UP_STAIRS );
					else if( gJa25SaveStruct.ubLoadScreenStairTraversal == LS__GOING_DOWN_STAIRS )
						return( LOADINGSCREEN_DOWN_STAIRS );
					else
						return( LOADINGSCREEN_COMPLEX_BASEMENT );
					break;
				}

				case SEC_L15:
				{
					//if we are going up stairs, else traversing at same level
					if( gJa25SaveStruct.ubLoadScreenStairTraversal == LS__GOING_UP_STAIRS )
						return( LOADINGSCREEN_UP_STAIRS );
					else
						return( LOADINGSCREEN_COMPLEX_BASEMENT );
					break;
				}

				default:
					return( ErrorLoadScreen( fNight, __LINE__ ) );
			}
		}
		case 3:
		{
			switch( ubSectorID )
			{
				case SEC_L15:
				{
					//if we are going up stairs, else traversing at same level
					if( gJa25SaveStruct.ubLoadScreenStairTraversal == LS__GOING_DOWN_STAIRS )
						return( LOADINGSCREEN_DOWN_STAIRS );
					else
						return( LOADINGSCREEN_COMPLEX_BASEMENT_GENERIC );
					break;
				}

				default:
					return( ErrorLoadScreen( fNight, __LINE__ ) );
			}
		}
		break;

		default:
			return( ErrorLoadScreen( fNight, __LINE__ ) );
	}
}

/*Ja25: New sectors
	switch( bSectorZ )
	{
		case 0:
			switch( ubSectorID )
			{
				case SEC_A2:
				case SEC_B2:
					if( fNight )
						return LOADINGSCREEN_NIGHTCHITZENA;
					return LOADINGSCREEN_DAYCHITZENA;
				case SEC_A9:
					if( !DidGameJustStart() )
					{
						if( fNight )
							return LOADINGSCREEN_NIGHTOMERTA;
						return LOADINGSCREEN_DAYOMERTA;
					}
					return LOADINGSCREEN_HELI;
				case SEC_A10:
					if( fNight )
						return LOADINGSCREEN_NIGHTOMERTA;
					return LOADINGSCREEN_DAYOMERTA;
				case SEC_P3:
					if( fNight )
						return LOADINGSCREEN_NIGHTPALACE;
					return LOADINGSCREEN_DAYPALACE;
				case SEC_H13:
				case SEC_H14: //military installations
				case SEC_I13:
				case SEC_N7:
					if( fNight )
						return LOADINGSCREEN_NIGHTMILITARY;
					return LOADINGSCREEN_DAYMILITARY;
				case SEC_K4: 
					if( fNight )
						return LOADINGSCREEN_NIGHTLAB;
					return LOADINGSCREEN_DAYLAB;
				case SEC_J9:
					if( fNight )
						return LOADINGSCREEN_NIGHTPRISON;
					return LOADINGSCREEN_DAYPRISON;
				case SEC_D2:
				case SEC_D15:
				case SEC_I8:
				case SEC_N4:
					if( fNight )
						return LOADINGSCREEN_NIGHTSAM;
					return LOADINGSCREEN_DAYSAM;
				case SEC_F8:
					if( fNight )
						return LOADINGSCREEN_NIGHTHOSPITAL;
					return LOADINGSCREEN_DAYHOSPITAL;
				case SEC_B13:
				case SEC_N3:
					if( fNight )
						return LOADINGSCREEN_NIGHTAIRPORT;
					return LOADINGSCREEN_DAYAIRPORT;
				case SEC_L11:
				case SEC_L12:
					if( fNight )
						return LOADINGSCREEN_NIGHTBALIME;
					return LOADINGSCREEN_DAYBALIME;
				case SEC_H3:
				case SEC_H8:
				case SEC_D4:
					if( fNight )
						return LOADINGSCREEN_NIGHTMINE;
					return LOADINGSCREEN_DAYMINE;
			}
			pSector = &SectorInfo[ ubSectorID ];
			switch( pSector->ubTraversability[ 4 ] )
			{
				case TOWN:
					if( fNight )
					{
						if( Random( 2 ) )
						{
							return LOADINGSCREEN_NIGHTTOWN2;
						}
						return LOADINGSCREEN_NIGHTTOWN1;
					}
					if( Random( 2 ) )
					{
						return LOADINGSCREEN_DAYTOWN2;
					}
					return LOADINGSCREEN_DAYTOWN1;
				case SAND:	
				case SAND_ROAD:
					if( fNight )
					{
						return LOADINGSCREEN_NIGHTDESERT;
					}
					return LOADINGSCREEN_DAYDESERT;
				case FARMLAND:
				case FARMLAND_ROAD:
				case ROAD:					
					if( fNight )
					{
						return LOADINGSCREEN_NIGHTGENERIC;
					}
					return LOADINGSCREEN_DAYGENERIC;
				case PLAINS:
				case SPARSE:
				case HILLS:
				case PLAINS_ROAD:
				case SPARSE_ROAD:
				case HILLS_ROAD:
					if( fNight )
					{
						return LOADINGSCREEN_NIGHTWILD;
					}
					return LOADINGSCREEN_DAYWILD;
				case DENSE:
				case SWAMP:
				case SWAMP_ROAD:
				case DENSE_ROAD:
					if( fNight )
					{
						return LOADINGSCREEN_NIGHTFOREST;
					}
					return LOADINGSCREEN_DAYFOREST;
				case TROPICS:
				case TROPICS_ROAD:
				case WATER:
				case NS_RIVER:
				case EW_RIVER:
				case COASTAL:
				case COASTAL_ROAD:
					if( fNight )
					{
						return LOADINGSCREEN_NIGHTTROPICAL;
					}
					return LOADINGSCREEN_DAYTROPICAL;
				default:
					Assert( 0 );
					if( fNight )
					{
						return LOADINGSCREEN_NIGHTGENERIC;
					}
					return LOADINGSCREEN_DAYGENERIC;
			}
			break;
		case 1:
			switch( ubSectorID )
			{
				case SEC_A10: //Miguel's basement
				case SEC_I13:	//Alma prison dungeon
				case SEC_J9:	//Tixa prison dungeon
				case SEC_K4:	//Orta weapons plant
				case SEC_O3:  //Meduna 
				case SEC_P3:  //Meduna 
					return LOADINGSCREEN_BASEMENT;
				default:			//rest are mines
					return LOADINGSCREEN_MINE;
			}
			break;
		case 2:	
		case 3:
			//all level 2 and 3 maps are caves!
			return LOADINGSCREEN_CAVE;
		default:
			// shouldn't ever happen
			Assert( FALSE );

			if( fNight )
			{
				return LOADINGSCREEN_NIGHTGENERIC;
			}
			return LOADINGSCREEN_DAYGENERIC;
	}
}
*/

extern BOOLEAN gfSchedulesHosed;

//sets up the loadscreen with specified ID, and draws it to the FRAME_BUFFER, 
//and refreshing the screen with it.
void DisplayLoadScreenWithID( UINT8 ubLoadScreenID )
{
	VSURFACE_DESC		vs_desc;
	HVSURFACE hVSurface;
	UINT32 uiLoadScreen;

	vs_desc.fCreateFlags = VSURFACE_CREATE_FROMFILE | VSURFACE_SYSTEM_MEM_USAGE;

	switch( ubLoadScreenID )
	{
		//Place holder
		case LOADINGSCREEN_NOTHING:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Heli.sti");
			break;

		//New load screens
		case LOADINGSCREEN_HELI_CRASH:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_HeliCrash.sti");
			break;

		case LOADINGSCREEN_DAY_SNOW:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Snow_day1.sti" );
			break;
		case LOADINGSCREEN_NIGHT_SNOW:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Snow_Night1.sti" );
			break;

		case LOADINGSCREEN_GUARDPOST_DAY:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Guardpostday.sti");
			break;

		case LOADINGSCREEN_GUARDPOST_NIGHT:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Guardpostnight.sti");
			break;

		case LOADINGSCREEN_POWERPLANT_DAY:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_PowerPlantDay.sti");
			break;

		case LOADINGSCREEN_POWERPLANT_NIGHT:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_PowerPlantNight.sti");
			break;

		//old loadscreens still being used
		case LOADINGSCREEN_DAYGENERIC:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayGeneric.sti");
			break;
		case LOADINGSCREEN_NIGHTGENERIC:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightGeneric.sti");
			break;

		case LOADINGSCREEN_DAYTOWN1:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayTown1.sti");
			break;
		case LOADINGSCREEN_DAYTOWN2:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayTown2.sti");
			break;

		case LOADINGSCREEN_NIGHTTOWN1:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightTown1.sti");
			break;
		case LOADINGSCREEN_NIGHTTOWN2:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightTown2.sti");
			break;

		case LOADINGSCREEN_DAYFOREST:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayForest.sti");
			break;
		case LOADINGSCREEN_NIGHTFOREST:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightForest.sti");
			break;

		case LOADINGSCREEN_DAYWILD:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayWild.sti");
			break;
		case LOADINGSCREEN_NIGHTWILD:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightWild.sti");
			break;

		case LOADINGSCREEN_MINE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Mine.sti");
			break;
		case LOADINGSCREEN_CAVE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Cave.sti");
			break;

		case LOADINGSCREEN_DAYPINE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayPine.sti");
			break;
		case LOADINGSCREEN_NIGHTPINE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightPine.sti");
			break;

		case LOADINGSCREEN_DAYMINE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_MineDay.sti" );
			break;
		case LOADINGSCREEN_NIGHTMINE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_MineNight.sti" );
			break;

		case 	LOADINGSCREEN_DOWN_STAIRS:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Basement.sti");
			break;

		case 	LOADINGSCREEN_UP_STAIRS:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_UpStairs.sti");
			break;

		case 	LOADINGSCREEN_COMPLEX_BASEMENT:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\ls_Complexbsmnt.sti");
			break;
		case 	LOADINGSCREEN_COMPLEX_BASEMENT_GENERIC:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Basement_Generic.sti");
			break;
		case 	LOADINGSCREEN_TUNNELS:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\ls_tunnels.sti");
			break;

		case 	LOADINGSCREEN_COMPLEX_TOP_LEVEL_DAY:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_MissleDay.sti");
			break;
		case 	LOADINGSCREEN_COMPLEX_TOP_LEVEL_NIGHT:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_MissleNight.sti");
			break;

		default:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Heli.sti");
			break;
	}
/*
		case LOADINGSCREEN_NOTHING:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Heli.sti");
			break;
		case LOADINGSCREEN_DAYGENERIC:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayGeneric.sti");
			break;
		case LOADINGSCREEN_DAYTOWN1:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayTown1.sti");
			break;
		case LOADINGSCREEN_DAYTOWN2:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayTown2.sti");
			break;
		case LOADINGSCREEN_DAYWILD:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayWild.sti");
			break;
		case LOADINGSCREEN_DAYTROPICAL:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayTropical.sti");
			break;
		case LOADINGSCREEN_DAYFOREST:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayForest.sti");
			break;
		case LOADINGSCREEN_DAYDESERT:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayDesert.sti");
			break;
		case LOADINGSCREEN_DAYPALACE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayPalace.sti");
			break;
		case LOADINGSCREEN_NIGHTGENERIC:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightGeneric.sti");
			break;
		case LOADINGSCREEN_NIGHTWILD:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightWild.sti");
			break;
		case LOADINGSCREEN_NIGHTTOWN1:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightTown1.sti");
			break;
		case LOADINGSCREEN_NIGHTTOWN2:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightTown2.sti");
			break;
		case LOADINGSCREEN_NIGHTFOREST:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightForest.sti");
			break;
		case LOADINGSCREEN_NIGHTTROPICAL:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightTropical.sti");
			break;
		case LOADINGSCREEN_NIGHTDESERT:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightDesert.sti");
			break;
		case LOADINGSCREEN_NIGHTPALACE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightPalace.sti");
			break;
		case LOADINGSCREEN_HELI:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Heli.sti");
			break;
		case LOADINGSCREEN_BASEMENT:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Basement.sti");
			break;
		case LOADINGSCREEN_MINE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Mine.sti");
			break;
		case LOADINGSCREEN_CAVE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Cave.sti");
			break;
		case LOADINGSCREEN_DAYPINE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayPine.sti");
			break;
		case LOADINGSCREEN_NIGHTPINE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightPine.sti");
			break;
		case LOADINGSCREEN_DAYMILITARY:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayMilitary.sti");
			break;
		case LOADINGSCREEN_NIGHTMILITARY:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightMilitary.sti");
			break;
		case LOADINGSCREEN_DAYSAM:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DaySAM.sti");
			break;
		case LOADINGSCREEN_NIGHTSAM:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightSAM.sti");
			break;
		case LOADINGSCREEN_DAYPRISON:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayPrison.sti");
			break;
		case LOADINGSCREEN_NIGHTPRISON:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightPrison.sti");
			break;
		case LOADINGSCREEN_DAYHOSPITAL:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayHospital.sti");
			break;
		case LOADINGSCREEN_NIGHTHOSPITAL:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightHospital.sti");
			break;
		case LOADINGSCREEN_DAYAIRPORT:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayAirport.sti");
			break;
		case LOADINGSCREEN_NIGHTAIRPORT:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightAirport.sti");
			break;
		case LOADINGSCREEN_DAYLAB:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayLab.sti");
			break;
		case LOADINGSCREEN_NIGHTLAB:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightLab.sti");
			break;
		case LOADINGSCREEN_DAYOMERTA:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayOmerta.sti");
			break;
		case LOADINGSCREEN_NIGHTOMERTA:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightOmerta.sti");
			break;
		case LOADINGSCREEN_DAYCHITZENA:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayChitzena.sti");
			break;
		case LOADINGSCREEN_NIGHTCHITZENA:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightChitzena.sti");
			break;
		case LOADINGSCREEN_DAYMINE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayMine.sti" );
			break;
		case LOADINGSCREEN_NIGHTMINE:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightMine.sti" );
			break;
		case LOADINGSCREEN_DAYBALIME:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_DayBalime.sti" );
			break;
		case LOADINGSCREEN_NIGHTBALIME:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_NightBalime.sti" );
			break;

		default:
			strcpy(vs_desc.ImageFile, "LOADSCREENS\\LS_Heli.sti");
			break;
	}
*/

	if( gfSchedulesHosed )
	{
		SetFont( FONT10ARIAL );
		SetFontForeground( FONT_YELLOW );
		SetFontShadow( FONT_NEARBLACK );
		ColorFillVideoSurfaceArea( FRAME_BUFFER, 0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT, 0 );
		mprintf( 5, 5, L"Error loading save, attempting to patch save to version 1.02...", vs_desc.ImageFile );
	}
	else if( AddVideoSurface( &vs_desc, &uiLoadScreen ) )
	{ //Blit the background image
		GetVideoSurface( &hVSurface, uiLoadScreen );
		BltVideoSurfaceToVideoSurface( ghFrameBuffer, hVSurface, 0, 0, 0, 0, NULL );
		DeleteVideoSurfaceFromIndex( uiLoadScreen );
	}
	else
	{ //Failed to load the file, so use a black screen and print out message.
		SetFont( FONT10ARIAL );
		SetFontForeground( FONT_YELLOW );
		SetFontShadow( FONT_NEARBLACK );
		ColorFillVideoSurfaceArea( FRAME_BUFFER, 0, 0, SCREEN_BUFFER_WIDTH, SCREEN_BUFFER_HEIGHT, 0 );
		mprintf( 5, 5, L"%S loadscreen data file not found...", vs_desc.ImageFile );
	}

	gubLastLoadingScreenID = ubLoadScreenID;
	InvalidateScreen( );
	ExecuteBaseDirtyRectQueue();
	EndFrameBufferRender();
	RefreshScreen( NULL );
}

UINT8 ErrorLoadScreen( BOOLEAN fNight, UINT32 uiLineNumber )
{
	CHAR zString[128];

	sprintf( zString, "Error in LoadScreen.c, actual line #%d", uiLineNumber );

//#ifndef JA2UB__QUICK_USE_OF_EDITOR_MAPS
	// shouldn't ever happen
//	AssertMsg( FALSE, zString );
//#endif

	if( fNight )
	{
		return LOADINGSCREEN_NIGHTGENERIC;
	}
	return LOADINGSCREEN_DAYGENERIC;
}