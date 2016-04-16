#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
	#include "_EditorEnglishtext.h"


#ifdef ENGLISH





/*
******************************************************************************************************
**                                  IMPORTANT TRANSLATION NOTES                                     **
******************************************************************************************************

GENERAL INSTRUCTIONS
- Always be aware that foreign strings should be of equal or shorter length than the English equivalent.
	I know that this is difficult to do on many occasions due to the nature of foreign languages when
	compared to English.  By doing so, this will greatly reduce the amount of work on both sides.  In
	most cases (but not all), JA2 interfaces were designed with just enough space to fit the English word.
	The general rule is if the string is very short (less than 10 characters), then it's short because of
	interface limitations.  On the other hand, full sentences commonly have little limitations for length.
	Strings in between are a little dicey.
- Never translate a string to appear on multiple lines.  All strings L"This is a really long string...",
	must fit on a single line no matter how long the string is.  All strings start with L" and end with ",
- Never remove any extra spaces in strings.  In addition, all strings containing multiple sentences only
	have one space after a period, which is different than standard typing convention.  Never modify sections
	of strings contain combinations of % characters.  These are special format characters and are always
	used in conjunction with other characters.  For example, %s means string, and is commonly used for names,
	locations, items, etc.  %d is used for numbers.  %c%d is a character and a number (such as A9).
	%% is how a single % character is built.  There are countless types, but strings containing these
	special characters are usually commented to explain what they mean.  If it isn't commented, then
	if you can't figure out the context, then feel free to ask SirTech.
- Comments are always started with // Anything following these two characters on the same line are
	considered to be comments.  Do not translate comments.  Comments are always applied to the following
	string(s) on the next line(s), unless the comment is on the same line as a string.
- All new comments made by SirTech will use "//@@@ comment" (without the quotes) notation.  By searching
	for @@@ everytime you recieve a new version, it will simplify your task and identify special instructions.
  Commonly, these types of comments will be used to ask you to abbreviate a string.  Please leave the
	comments intact, and SirTech will remove them once the translation for that particular area is resolved.
- If you have a problem or question with translating certain strings, please use "//!!! comment"
	(without the quotes).  The syntax is important, and should be identical to the comments used with @@@
	symbols.  SirTech will search for !!! to look for your problems and questions.  This is a more
	efficient method than detailing questions in email, so try to do this whenever possible.



FAST HELP TEXT -- Explains how the syntax of fast help text works.
**************

1) BOLDED LETTERS
	The popup help text system supports special characters to specify the hot key(s) for a button.
	Anytime you see a '|' symbol within the help text string, that means the following key is assigned
	to activate the action which is usually a button.

	EX:  L"|Map Screen"

	This means the 'M' is the hotkey.  In the game, when somebody hits the 'M' key, it activates that
	button.  When translating the text to another language, it is best to attempt to choose a word that
	uses 'M'.  If you can't always find a match, then the best thing to do is append the 'M' at the end
	of the string in this format:

	EX:  L"Ecran De Carte (|M)"  (this is the French translation)

	Other examples are used multiple times, like the Esc key  or "|E|s|c" or Space -> (|S|p|a|c|e)

2) NEWLINE
  Any place you see a \n within the string, you are looking at another string that is part of the fast help
	text system.  \n notation doesn't need to be precisely placed within that string, but whereever you wish
	to start a new line.

	EX:  L"Clears all the mercs' positions,\nand allows you to re-enter them manually."

	Would appear as:

				Clears all the mercs' positions,
				and allows you to re-enter them manually.

	NOTE:  It is important that you don't pad the characters adjacent to the \n with spaces.  If we did this
	       in the above example, we would see

	WRONG WAY -- spaces before and after the \n
	EX:  L"Clears all the mercs' positions, \n and allows you to re-enter them manually."

	Would appear as: (the second line is moved in a character)

				Clears all the mercs' positions,
 				 and allows you to re-enter them manually.


@@@ NOTATION
************

	Throughout the text files, you'll find an assortment of comments.  Comments are used to describe the
	text to make translation easier, but comments don't need to be translated.  A good thing is to search for
	"@@@" after receiving new version of the text file, and address the special notes in this manner.

!!! NOTATION
************

	As described above, the "!!!" notation should be used by you to ask questions and address problems as
	SirTech uses the "@@@" notation.

*/







STR16	gzEditorStrings[]=
{
	L"DETAILED PLACEMENT",
	L"Starting Population",
	L"Easy",
	L"Normal",
	L"Diff",
	L"Admins",
	L"Troops",
	L"Elites",
	L"BloodCats",
	L"Invasion Data",
	L"Min Enemies",
	L"Attack Probability Rate",
	L"Grace period",
	L"Insertion GridNo (undergrnd)",
	L"Sector Description",																								// @@@ Changed
	L"Insertion Direction",
	L"Loading Screen",

	L"Snow",
	L"Guard Post",
	L"Power Plant",
	L"Generic",
	L"Town 1",
	L"Town 2",
	L"Forest",
	L"Mine",
	L"Cave",
	L"Pine",
	L"Mine Entrance",
	L"Wilderness",
	L"Generic Basement",
	L"Delete",
	L"north",
	L"northeast",
	L"east",
	L"southeast",
	L"south",
	L"southwest",
	L"west",
	L"northwest",
	L"Toggle viewing of players",
	L"Toggle viewing of enemies",
	L"Toggle viewing of creatures",
	L"General information mode",
	L"Attributes mode",
	L"Inventory mode",
	L"Schedule mode",
	L"Delete currently selected merc (DEL).",
	L"Find next merc (SPACE).",
	L"Toggle priority existance",
	L"STATIONARY",
	L"ON GUARD",
	L"ON CALL",
	L"SEEK ENEMY",
	L"CLOSE PATROL",
	L"FAR PATROL",
	L"POINT PATROL",
	L"RND PT PATROL",
	L"DEFENSIVE",
	L"BRAVE SOLO",
	L"BRAVE AID",
	L"AGGRESSIVE",
	L"CUNNING SOLO",
	L"CUNNING AID",
	L"Set merc to face %s",
	L"Find",
	L"Find selected merc",
	L"Previous color set",
	L"Next color set",
	L"Toggle time variance (+ or - 15 minutes)",
	L"No action",
	L"Clear Schedule",
	L"ROOFS",
	L"WALLS",
	L"ROOM INFO",
	L"Place walls using selection method\n",
	L"Place doors using selection method",
	L"Place roofs using selection method",
	L"Place windows using selection method",
	L"Place damaged walls using selection method.",
	L"Place furniture using selection method",
	L"Place wall decals using selection method",
	L"Place floors using selection method",
	L"Place generic furniture using selection method",
	L"Place walls using smart method",
	L"Place doors using smart method",
	L"Place windows using smart method",
	L"Place damaged walls using smart method",
	L"Add a new room",
	L"Edit cave walls.",
	L"Remove an area from existing building.",
	L"Remove a building",
	L"Add/replace building's roof with new flat roof.",
	L"Copy a building",
	L"Move a building",
	L"Draw room number",
	L"Erase room numbers",
	L"Toggle erase mode",
	L"Undo last change",
	L"Cycle brush size",
	L"Weapons",
	L"Ammo",
	L"Armor",
	L"Explosives",
	L"E1",
	L"E2",
	L"E3",
	L"Triggers",
	L"Add ambient light source",
	L"Toggle fake ambient lights.",
	L"Add exit grids (r-clk to query existing).",
	L"Specify north point for validation purposes.",
	L"Specify west point for validation purposes.",
	L"Specify east point for validation purposes.",
	L"Specify south point for validation purposes.",
	L"Specify center point for validation purposes.",
	L"Specify isolated point for validation purposes.",
	L"New map",
	L"New basement",
	L"New cave level",
	L"Save map",
	L"Load map",
	L"Select tileset",
	L"Leave Editor mode",
	L"Previous direction",
	L"Next direction",
	L"Draw ground textures",
	L"Set map ground textures",
	L"Place banks and cliffs",
	L"Draw roads",
	L"Draw debris",
	L"Place trees & bushes",
	L"Place rocks",
	L"Place barrels & other junk",
	L"Fill area",
	L"Raise brush density",
	L"Lower brush density",
	L"Terrain",
	L"Buildings",
	L"Items",
	L"Mercs",
	L"Map Info",
	L"Misc",
	L"North Entry Point",
	L"West Entry Point",
	L"East Entry Point",
	L"South Entry Point",
	L"Center Entry Point",
	L"Isolated Entry Point",
	L"Prime",
	L"Night",
	L"24Hour",
	L"Panic Trigger1",
	L"Panic Trigger2",
	L"Panic Trigger3",
	L"Panic Trigger4",
	L"Panic Trigger5",
	L"Panic Trigger6",
	L"Trigger%d",
	L"Pressure Action",
	L"Panic Action1",
	L"Panic Action2",
	L"Panic Action3",
	L"Panic Action4",
	L"Panic Action5",
	L"Panic Action6",
	L"Action%d",
	L"No Lock ID",
	L"Explosion Trap",
	L"Electric Trap",
	L"Siren Trap",
	L"Silent Alarm",
	L"Super Electric Trap",
	L"Trap Level %d",
	L"H", 	// One letter code for hidden items
	L"GridNo: %d  ", // shows current gridno on screen
	L"                ", // erases above gridno indicator
	L"No map currently loaded.",
	L"File:  %S, Current Tileset:  %s",
	L"Width: %d",
	L"Auto",
	L"Player",
	L"Enemy",
	L"Bloodcat",
	L"NEXT",
	L"TOGGLE",
	L"VIEWS",
	L"SELECTION METHOD",
	L"SMART METHOD",
	L"BUILDING METHOD",
	L"Room#",
	L"Okay",
	L"Cancel",
	L"Editing lock attributes at map index %d.",
	L"Lock ID",
	L"Trap Type",
	L"Trap Level",
	L"Locked",
	L"Status Info Line 1",
	L"Status Info Line 2",
	L"Status Info Line 3",
	L"Status Info Line 4",
	L"Status Info Line 5",
	L"R",	// R is for "red" color
	L"G",	// G is for "green" color
	L"B",	// B is for "blue" color
	L"Radius",	// size of light
	L"Underground",
	L"Light Level",
	L"Outdoors",
	L"Basement",
	L"Caves",
	L"Destination",
	L"Sector",
	L"Bsmt. Level",
	L"Dest.",
	L"GridNo",
	L"Merc Name:",
	L"Orders:",
	L"Combat Attitude:",
	L"Merc Colors",
	L"Done",
	L"Previous merc standing orders",
	L"Next merc standing orders",
	L"Previous merc combat attitude",
	L"Next merc combat attitude",
	L"Decrease merc stat",
	L"Increase merc stat",
	L"Random",
	L"Reg Male",
	L"Big Male",
	L"Stocky Male",
	L"Reg Female",
	L"Bloodcat",
	L" --=ORDERS=-- ",
	L"--=ATTITUDE=--",
	L"Army/Troops",																																		// @@ Changed
	L"Admin",
	L"Elite",

	L"Exp. Level",
	L"Health",																																				// @@ changed
	L"Current Health",																																// @@ Changed
	L"Marksmanship",
	L"Strength",
	L"Agility",
	L"Dexterity",
	L"Wisdom",
	L"Leadership",
	L"Explosives",
	L"Medical",
	L"Mechanical",
	L"Morale",

	L"Hair color:",
	L"Skin color:",
	L"Vest color:",
	L"Pant color:",

	L"RANDOM",
	L"Current Profile:  n/a                            ",

	L"STATIONARY",
	L"ON CALL",
	L"ON GUARD",
	L"SEEK ENEMY",
	L"CLOSE PATROL",
	L"FAR PATROL",
	L"POINT PATROL",
	L"RND PT PATROL",
	L"Slot #%d",
	L"Patrol orders with no waypoints",
	L"Waypoints with no patrol orders",
	L"Placement not copied because no placement selected.",
	L"Placement copied.",
	L"Placement not pasted as no placement is saved in buffer.",
	L"Placement pasted.",
	L"Placement not pasted as the maximum number of placements for this team is already used.",
	L"Small",
	L"Medium",
	L"Large",
	L"XLarge",
	L"Width: ",
	L"Area",
	L"Exit editor?",
	L"Are you sure you wish to remove all lights?",
	L"Are you sure you wish to reverse the schedules?",
	L"Are you sure you wish to clear all of the schedules?",
	L"Removing Treetops",
	L"Showing Treetops",
	L"Start a new basement level?",
	L"Start a new cave level?",
	L"Start a new outdoor level?",
	L" Wipe out ground textures? ",
	L"HOME",
	L"Toggle fake editor lighting ON/OFF",
	L"INSERT",
	L"Toggle fill mode ON/OFF",
	L"BKSPC",
	L"DEL",
	L"Quick erase object under mouse cursor",
	L"ESC",
	L"Exit editor",
	L"PGUP/PGDN",
	L"Change object to be pasted",
	L"F1",
	L"This help screen",
	L"F10",
	L"Save current map",
	L"F11",
	L"Load map as current",
	L"+/-",
	L"Change shadow darkness by .01",
	L"SHFT +/-",
	L"Change shadow darkness by .05",
	L"0 - 9",
	L"Change map/tileset filename",
	L"b",
	L"Change brush size",
	L"d",
	L"o",
	L"Draw obstacle",
	L"r",
	L"Draw rocks",
	L"t",
	L"Toggle trees display ON/OFF",
	L"g",
	L"Draw ground textures",
	L"w",
	L"Draw building walls",
	L"e",
	L"h",
	L"Toggle roofs ON/OFF",
	L"Map data has just been corrupted.  Don't save!",
	L"Enter gridno:",
	L"Toggle hide flag",
	L"No item selected.",
	L"Slot available for",
	L"random generation.",
	L"Keys not editable.",
	L"ProfileID of owner",
	L"Item class not implemented.",
	L"Slot locked as empty.",
	L"Status",
	L"Rounds",
	L"Trap Level",
	L"Quantity",
	L"Dollars",
	L"Tolerance",
	L"Alarm Trigger",
	L"Exist Chance",
	L"SILENCER",
	L"SNIPERSCOPE",
	L"LASERSCOPE",
	L"BIPOD",
	L"DUCKBILL",
	L"G-LAUNCHER",
	L"CERAMIC PLATES",
	L"DETONATOR",
	L"If the panic trigger is an alarm trigger,\nenemies won't attempt to use it if they\nare already aware of your presence.",
	L"%s Map (*.dat)",
	L"Save",
	L"Load",
	L"NO FILES IN CAMPAIGN DIRECTORY",																	
	L" Delete READ-ONLY file %s? ",
	L" Delete file %s? ",
	L" Illegal filename.  Try another filename?",
	L" File is read only!  Choose a different name? ",
	L" File exists, Overwrite? ",
	L"Loading map:  %s",
	L"Filename",
	L"Generate Radar Map",																								
	L"Saving map:  %s",
	L"Map data has just been corrupted!",
	L"Error loading file.",
	L".dat",
	L"Cancel selections",
	L"Accept selections",
	L"Scroll window up",
	L"Scroll window down",
	L"%S[%d] is from default tileset %s (%S)",
	L"File:  %S, subindex:  %d (%S)",
	L"Current Tileset:  %s",
	L"General enemy rank:",																										
	L"Enemy Placements:",																											
	L"Total:",																																
	L"(Missing %d)",																												
	L"Prev Loadscreen",																												
	L"Next Loadscreen",																											
	L"Num Bloodcats:",																												
	L"Current Campaign: %S",																								
	L"Check",
	L"droppable",
	L"items",








};


UINT16 gszActionItemDesc[ NUM_ACTIONITEMS ][ 30 ] =
{
	L"Klaxon Mine",
	L"Flare Mine",
	L"Teargas Explosion",
	L"Stun Explosion",
	L"Smoke Explosion",
	L"Mustard Gas",
	L"Land Mine",
	L"Open Door",
	L"Close Door",
	L"Small Explosion",
	L"Medium Explosion",
	L"Large Explosion",
	L"Toggle Door",
	L"Reveal Room",
	L"Local Alarm",	
	L"Global Alarm",
	L"Klaxon Sound",
	L"Tog pressure items",
	L"Bloodcat alarm",
	L"Big teargas",
};




UINT16 *EditMercStat[12] =
{
	L"Max Health",
	L"Cur Health",
	L"Strength",
	L"Agility",
	L"Dexterity",
	L"Charisma",
	L"Wisdom",
	L"Marksmanship",
	L"Explosives",
	L"Medical",
	L"Scientific",
	L"Exp Level"
};


UINT16 *EditMercOrders[8] =
{
	L"Stationary",
	L"On Guard",
	L"Close Patrol",
	L"Far Patrol",
	L"Point Patrol",
	L"On Call",
	L"Seek Enemy",
	L"Random Point Patrol"
};

UINT16 *EditMercAttitudes[6] =
{
	L"Defensive",
	L"Brave Loner",
	L"Brave Buddy",
	L"Cunning Loner",
	L"Cunning Buddy",
	L"Aggressive"
};

UINT16 *zDiffNames[5] = 
{ 
	L"Wimp",
	L"Easy",
	L"Average",
	L"Tough",
	L"Steroid Users Only",
};

UINT16 *gTilesetNames[ 60 ] =
{
	L"GENERIC 1",													// 0
	L"CAVES 1",														// 1	
	L"DESERT 1",													// 2
	L"LUSH 1 (dirt roads)",								// 3
	L"TROPICAL 1",												// 4
	L"MOUNTAINS 1",												// 5
	L"COASTAL 1",													// 6
	L"SWAMP 1",														// 7
	L"FARM 1",														// 8
	L"OMERTA",														// 9
	L"GENERIC 2 (Dirtroads)",							// 10
	L"FARM 2 (ruined walls)",							// 11
	L"PRISON",														// 12
	L"HOSPITAL (Cambria)",								// 13
	L"DEMO BASEMENT",											// 14
	L"BURNT TREES",												// 15
	L"LAWLESS 1 (San Mona-d5)",						// 16
	L"AIRSTRIP (Drassen-b13)",						// 17
	L"LAWLESS 2 (burnt-c5)",							// 18
	L"DEAD AIRSTRIP(Drassen-c13)",				// 19
	L"BASEMENT",													// 20
	L"LAWLESS 3 (burnt-c6)",					  	// 21
	L"PRISON DUNGEON",								  	// 22
	L"ACTIVE DRASSEN (d13)",					  	// 23
	L"SAM SITES",											  	// 24
	L"LUSH2 (different trees)",					  // 25
	L"MILITARY BASE",											// 26
	L"MILITARY JAIL",									  	// 27
	L"MILITARY WAREHOUSE",						  	// 28
	L"MILITARY TOWN",									  	// 29
	L"OLD SCHOOL",										  	// 30
	L"CAMBRIA STRIP",									  	// 31
	L"CAMBRIA HOMES",									  	// 32
	L"PALACE!",												  	// 33
	L"TROPICAL SAM",									  	// 34
	L"GRUMM 1",													  // 35
	L"GRUMM 2",												  	// 36
	L"BALIME",												  	// 37
	L"BALIME MUSEUM",									  	// 38
	L"DESERT SAM",										  	// 39
	L"ORTA",													  	// 40
	L"ORTA WEAPONS",									  	// 41
	L"SWAMP BARETREES",								  	// 42
	L"ESTONI",												  	// 43
	L"QUEEN'S PRISON",								  	// 44
	L"QUEEN'S TROPICAL",							  	// 45
	L"MEDUNA INNER TOWN",							  	// 46
	L"QUEEN'S SAM",										  	// 47
	L"QUEEN'S AIRPORT",								  	// 48
	L"DEMO TILESET",									  	// 49
	L"HEAVY SNOW",										  	// 50
	L"MIXED SNOW",										  	// 51
	L"GRASS & SNOW",									  	// 52
	L"FALL TOWN",											  	// 53
	L"MINING TOWN",										  	// 54
	L"POWER PLANT",										  	// 55
	L"SEWERS",												  	// 56
	L"UNDERGROUND COMPLEX",						  	// 57
	L"UPPER COMPLEX",									  	// 58
	L"LOWEST LEVEL COMPLEX",					  	// 59
};



#endif

#endif
