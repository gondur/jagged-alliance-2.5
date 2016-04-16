#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
#else
	#include "Types.h"
	#include "GameVersion.h"
#endif
 
    
//
//	Keeps track of the game version
//
 
#ifdef JA2BETAVERSION

//BETA/TEST BUILD VERSION

	INT16		zVersionLabel[16]		= { L"v.1.01" }; 

#else

	#ifdef GERMAN 

	//RELEASE BUILD VERSION 
	INT16		zVersionLabel[16]		= { L"Release v.1.01" }; 

	#else

		//RELEASE BUILD VERSION 
		INT16		zVersionLabel[16]		= { L"Release v.1.02" }; 

	#endif


#endif

INT8		czVersionNumber[16]	= { "Build 02.12.01" };
INT16		zTrackingNumber[16]	= { L"Y" };
	

//
//		Keeps track of the saved game version.  Increment the saved game version whenever 
//	you will invalidate the saved game file

// Ja25	
//#define			SAVE_GAME_VERSION					96

//Increment Save Game Version to a High Value so we know the save is for the expansion pack
#define			SAVE_GAME_VERSION					1017

const	UINT32	guiSavedGameVersion = SAVE_GAME_VERSION;
