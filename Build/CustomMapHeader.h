#ifndef _CUSTOM_MAP_HEADER__H_
#define _CUSTOM_MAP_HEADER__H_

#ifdef	ENABLE_CUSTOM_MAP_INTERFACE



#define				CM__CUSTOM_MAP_DIR_NAME				"CustomMaps"



#define				CMS__PART_OF_CAMPAIGN								1<<0			//Map is part of a campaign
#define				CMS__HAS_BRIEFING_TEXT_FILE					1<<1			//Also has the briefing text file
#define				CMS__HAS_CAMPAIGN_DATA_FILE					1<<2			//Also has the Campaign Data file


#define				CMS_SIZE_OF_STRING									256

typedef struct
{
	CHAR8			*pFileNameArray;						// An array of all the map names in the campaign
	INT32			iCurrentMap;								// Current map
	INT32			iNumberOfMaps;							// # of maps in included
	UINT32		uiFlags;										// Can be any of the above flags

	INT16			sSectorX;						
	INT16			sSectorY;						
	INT16			sSectorZ;						

} CUSTOM_MAP_STRUCT;


typedef struct
{
	INT32								iCurrentMap;								// Current map
	INT32								iNumberOfMaps;							// # of maps in included
	UINT32							uiFlags;										// Can be any of the above flags
	CUSTOM_MAP_STRUCT		*pMap;											// An array of map structs
	CHAR8								zScenarioDirName[CMS_SIZE_OF_STRING];					//The name of the directory where the scenario is

} CUSTOM_MAP_HEADER_STRUCT;



extern	CUSTOM_MAP_HEADER_STRUCT		gSelectedCustomScenario;

#endif



#endif