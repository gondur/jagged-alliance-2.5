#ifndef _INTRO__C_
#define _INTRO__C_



UINT32	IntroScreenShutdown( void );
UINT32	IntroScreenHandle( void );
UINT32	IntroScreenInit( void );


//enums used for when the intro screen can come up, used with 'gbIntroScreenMode'
enum
{
//Ja25: no intro video	INTRO_BEGINING,			//set when viewing the intro at the begining of the game
	INTRO_HELI_CRASH,
	INTRO_ENDING,				//set when viewing the end game video.

	INTRO_SPLASH,
};


extern	UINT32	guiSmackerSurface;


void SetIntroType( INT8 bIntroType );

#endif