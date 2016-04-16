#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
	#include "_Ja25Englishtext.h"
#else
	#include "Language Defines.h"
	#ifdef ENGLISH
		#include "text.h"
		#include "Fileman.h"
		#include "JA2 Demo Ads.h"
	#endif
#endif

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







STR16	gzImportJa2ScreenText[]=
{
	L"Start New Game",
	L"There are two ways to begin a new game of Jagged Alliance 2 - Unfinished Business :",
	L"Starting with FRESH characters",
	L"This is similar to starting a new game of JAGGED ALLIANCE 2. You'll  be able to create a custom I.M.P mercenary and hire additional mercenaries from A.I.M and M.E.R.C. All characters' statistics begin at their normal base values.",
	L"Importing SAVED characters",
	L"If you have a saved game from JAGGED ALLIANCE 2, you can import your custom-created I.M.P. character as well as all statistic improvements to A.I.M and M.E.R.C. mercenaries. The characters' inventories will be reset and the game's difficulty will be increased slightly to accommodate your characters' improved abilities.",
	L"You'll begin the game with your I.M.P. mercenary. You can then hire mercenaries from A.I.M. and M.E.R.C. as usual.  Recruited characters from JAGGED ALLIANCE 2, such as Ira and Dynamo, have returned to their civilian lives and are no longer available.",
	L"START FRESH",
	L"IMPORT",
	L"CANCEL",
};

STR16 zNewButtonText[]=
{
	L"Start",
	L"Import",
	L"Cancel",
	L"Would you like, START fresh, IMPORT you characters from Ja2, or CANCEL back to the main menu?",
	L"To IMPORT your characters, you need to run the external program \"JA2UBSaveConverter.exe\".  Do you wish to do this now?",
	L"Succesfully imported the save.  Do you want to use the information from the save?",
	L"Error importing save.",
};

STR16	zNewTacticalMessages[]=
{
	L"Range to target: %d tiles",
	L"Attaching the transmitter to your laptop computer.",
	L"You cannot afford to hire %s",
	L"For a limited time, the above fee covers the cost of the entire mission and includes the equipment listed below.",
	L"Hire %s now and take advantage of our unprecedented 'one fee covers all' pricing.  Also included in this unbelievable offer is the mercenary's personal equipment at no charge.",
	L"Fee",
	L"There is someone else in the sector...",
	L"Gun Range: %d tiles, Range to target: %d tiles",
	L"Display Cover",
	L"Line of Sight",
	L"New Recruits cannot arrive there.",
	L"Since your laptop has no transmitter, you won't be able to hire new team members.  Perhaps this would be a good time to load a saved game or start over!",
	L"%s hears the sound of crumpling metal coming from underneath Jerry's body.  It sounds disturbingly like your laptop antenna being crushed.",  //the %s is the name of a merc.  @@@  Modified
	L"After scanning the note left behind by Deputy Commander Morris, %s senses an oppurtinity.  The note contains the coordinates for launching missiles against different towns in Arulco.  It also gives the coodinates of the origin - the missile facility.",
	L"Noticing the control panel, %s figures the numbers can be reveresed, so that the missile might destroy this very facility.  %s needs to find an escape route.  The elevator appears to offer the fastest solution...",
	L"This is an IRON MAN game and you cannot save when enemies are around.",	//	@@@  new text
	L"(Cannot save during combat)", //@@@@ new text
	L"The current campaign name is greater than 30 characters.",							// @@@ new text
	L"The current campaign cannot be found.",																	// @@@ new text
	L"Campaign: Default ( %S )",																							// @@@ new text
	L"Campaign: %S",																													// @@@ new text
	L"You have selected the campaign %S. This campaign is a player-modified version of the original Unfinished Business campaign. Are you sure you wish to play the %S campaign?",			// @@@ new text
	L"In order to use the editor, please select a campaign other than the default.",		///@@new
};


STR16	gzNewLaptopMessages[]=
{
	L"Ask about our special offer!",
	L"Temporarily Unavailable",
	L"This special press preview of Jagged Alliance 2: Unfinished Business contains the only first 6 sector maps. The final version of the game will feature many more - please see the included readme file for details.",
};

//these strings match up with the defines in IMP Skill trait.c
STR16 gzIMPSkillTraitsText[]=
{
	L"Lock picking",
	L"Hand to hand combat",
	L"Electronics",
	L"Night operations",
	L"Throwing",
	L"Teaching",
	L"Heavy Weapons",
	L"Auto Weapons",
	L"Stealth",
	L"Ambidextrous",
	L"Knifing",
	L"Rooftop Sniping",
	L"Camouflage",
	L"Martial Arts",

	L"None",
	L"I.M.P. Specialties",
};


//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"You have chosen IRON MAN mode. This setting makes the game considerably more challenging as you will not be able to save your game when in a sector occupied by enemies. This setting will affect the entire course of the game.  Are you sure want to play in IRON MAN mode?",
};


#endif