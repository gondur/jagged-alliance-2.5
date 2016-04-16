#ifndef _BUILDDEFINES_H
#define _BUILDDEFINES_H

#include "Language Defines.h"

// Beta version
// #define	JA2BETAVERSION

// Normal test version
// #define JA2TESTVERSION

// If we want to include the editor
#define JA2EDITOR

//#define JA2UB_PRESS_PREVIEW

// ATE: Disable editor if preview
#ifdef JA2UB_PRESS_PREVIEW
	#ifdef JA2EDITOR
		#undef JA2EDITOR
	#endif
#endif


// Allow the player to use the editor to make maps and place them in a new map, slot.  
// The game will allow the new sector to be traversed to.
#define	JA2UB__QUICK_USE_OF_EDITOR_MAPS



#ifdef _DEBUG
	#ifndef JA2TESTVERSION
		#define JA2TESTVERSION
	#endif
#endif

// Do combinations
#ifdef JA2TESTVERSION
	#define JA2BETAVERSION
	#define JA2EDITOR
#endif

#ifdef JA2BETAVERSION
	#define SGP_DEBUG
	#define	FORCE_ASSERTS_ON
	#define SGP_VIDEO_DEBUGGING
#endif

//#define CRIPPLED_VERSION

// Huge speed and memory hog, but thorough -- will work with release builds.
// #define EXTREME_MEMORY_DEBUGGING 

#endif