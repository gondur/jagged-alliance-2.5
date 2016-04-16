#ifndef __MAP_INFORMATION_H
#define __MAP_INFORMATION_H

#include "types.h"

extern FLOAT gdMajorMapVersion;
extern UINT8 gubMinorMapVersion;

enum //for use with MAPCREATE_STRUCT.ubEditorSmoothingType
{
	SMOOTHING_NORMAL,
	SMOOTHING_BASEMENT,
	SMOOTHING_CAVES
};

#define		MAP_INFO_RANDOM_FILLER_SIZE	100
#define		MAP_LEVEL_NAME_SIZE					16


typedef struct
{
	//These are the mandatory entry points for a map.  If any of the values are -1, then that means that
	//the point has been specifically not used and that the map is not traversable to or from an adjacent 
	//sector in that direction.  The >0 value points must be validated before saving the map.  This is 
	//done by simply checking if those points are sittable by mercs, and that you can plot a path from 
	//these points to each other.  These values can only be set by the editor : mapinfo tab

	// ATE: JA25 - used to make sure our new maps can't be used with ja2
	UINT8	uiRandomFiller[ MAP_INFO_RANDOM_FILLER_SIZE ];

  INT16 sNorthGridNo;
	INT16 sEastGridNo;
	INT16 sSouthGridNo;
	INT16 sWestGridNo;
	//This contains the number of individuals in the map.
	//Individuals include NPCs, enemy placements, creatures, civilians, rebels, and animals.
	UINT8 ubNumIndividuals;
	UINT8 ubMapVersion;
	UINT8 ubRestrictedScrollID;
	UINT8 ubEditorSmoothingType;  //normal, basement, or caves
	INT16 sCenterGridNo;
	INT16 sIsolatedGridNo;

	UINT8	ubNumElitesE;
	UINT8	ubNumAdminsE;
	UINT8	ubNumTroopsE;
	UINT8 ubNumBloodcatsE;

	UINT8	ubNumElitesN;
	UINT8	ubNumAdminsN;
	UINT8	ubNumTroopsN;
	UINT8 ubNumBloodcatsN;

	UINT8	ubNumElitesD;
	UINT8	ubNumAdminsD;
	UINT8	ubNumTroopsD;
	UINT8 ubNumBloodcatsD;

	UINT8	ubBaseNumEnemies;
	UINT8	ubAttackProbabilityRate;
	UINT8	ubGracePeriod;
	UINT8	ubFiller;

	UINT16	zLevelName[ MAP_LEVEL_NAME_SIZE ];

	UINT8		ubInsertionDirection;
	BOOLEAN	fAutoDirection;
	INT16		sInsertionGridNo;
	UINT8		ubLoadingScreenID;

	INT8 bPadding[30];	//I'm sure lots of map info will be added
}MAPCREATE_STRUCT; //99 bytes

extern MAPCREATE_STRUCT gMapInformation;

void SaveMapInformation( HWFILE fp );
void LoadMapInformation( INT8 **hBuffer, BOOLEAN fOldMap );
void ValidateAndUpdateMapVersionIfNecessary();
BOOLEAN ValidateEntryPointGridNo( INT16 *sGridNo );

extern BOOLEAN gfWorldLoaded;

#endif