#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
	#include "CustomMap.h"
	#include "ImportJa2SaveScreen.h"
	#include "CustomMapBriefingScreen.h"
	#include "CustomMapMercChoosing.h"
#else
	#include "Screens.h"
#endif


Screens GameScreens[MAX_SCREENS] =
{
  { EditScreenInit,							EditScreenHandle,							EditScreenShutdown					}, 
  { SavingScreenInitialize,     SavingScreenHandle,						SavingScreenShutdown				}, // Title Screen
  { LoadingScreenInitialize,    LoadingScreenHandle,					LoadingScreenShutdown				}, // Title Screen
  { ErrorScreenInitialize,      ErrorScreenHandle,						ErrorScreenShutdown					}, // Title Screen
  { InitScreenInitialize,       InitScreenHandle,							InitScreenShutdown					}, // Title Screen
  { MainGameScreenInit,					MainGameScreenHandle,					MainGameScreenShutdown			},
	{ AniEditScreenInit,					AniEditScreenHandle,					AniEditScreenShutdown				},
	{ PalEditScreenInit,					PalEditScreenHandle,					PalEditScreenShutdown				},
	{ DebugScreenInit,						DebugScreenHandle,						DebugScreenShutdown					},
	{ MapScreenInit,							MapScreenHandle,							MapScreenShutdown						},
	{ LaptopScreenInit,						LaptopScreenHandle,						LaptopScreenShutdown				},
	{ LoadSaveScreenInit,					LoadSaveScreenHandle,					LoadSaveScreenShutdown			},
	{ MapUtilScreenInit,					MapUtilScreenHandle,					MapUtilScreenShutdown				},
	{ FadeScreenInit,							FadeScreenHandle,							FadeScreenShutdown					},
	{ MessageBoxScreenInit,				MessageBoxScreenHandle,				MessageBoxScreenShutdown		},
	{ MainMenuScreenInit,					MainMenuScreenHandle,					MainMenuScreenShutdown			},
	{ AutoResolveScreenInit,			AutoResolveScreenHandle,			AutoResolveScreenShutdown		},
	{ SaveLoadScreenInit,					SaveLoadScreenHandle,					SaveLoadScreenShutdown			},
	{ OptionsScreenInit,					OptionsScreenHandle,					OptionsScreenShutdown				},
	{ ShopKeeperScreenInit,				ShopKeeperScreenHandle,				ShopKeeperScreenShutdown		},
	{ SexScreenInit,							SexScreenHandle,							SexScreenShutdown						},
	{ GameInitOptionsScreenInit,	GameInitOptionsScreenHandle,	GameInitOptionsScreenShutdown		},
	{ DemoExitScreenInit,					DemoExitScreenHandle,					DemoExitScreenShutdown			},
	{ IntroScreenInit,						IntroScreenHandle,						IntroScreenShutdown					},
	{ CreditScreenInit,						CreditScreenHandle,						CreditScreenShutdown				},

#ifdef ENABLE_CUSTOM_MAP_INTERFACE
	{ CustomMapInit,							CustomMapHandle,							CustomMapShutdown				},
	{ CMBriefingScreenInit,				CMBriefingScreenHandle,				CMBriefingScreenShutdown	},
	{ CMMercChoosingInit,					CMMercChoosingHandle,					CMMercChoosingShutdown				},
#endif

#ifdef JA2BETAVERSION
	{ AIViewerScreenInit,					AIViewerScreenHandle,					AIViewerScreenShutdown			},
#endif

	{ QuestDebugScreenInit,				QuestDebugScreenHandle,				QuestDebugScreenShutdown		},
	{ ImportJa2SaveScreenInit,		ImportJa2SaveScreenHandle,		ImportJa2SaveScreenShutdown		},
};