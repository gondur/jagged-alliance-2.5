#ifndef _GAME_VERSION_H_
#define _GAME_VERSION_H_


#ifdef __cplusplus
extern "C" {
#endif



#define			JA2_EXP_FIRST_SAVE_GAME_VERSION		1001


//
//	Keeps track of the game version
//

extern	INT16		zVersionLabel[16];
extern	INT8		czVersionNumber[16];
extern	INT16		zTrackingNumber[16];





//
//		Keeps track of the saved game version.  Increment the saved game version whenever 
//	you will invalidate the saved game file
//

const extern	UINT32	guiSavedGameVersion;

#ifdef __cplusplus
}
#endif


#endif
