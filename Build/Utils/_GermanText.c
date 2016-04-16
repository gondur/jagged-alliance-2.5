#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
#else
	#include "Language Defines.h"
	#ifdef ENGLISH
		#include "text.h"
		#include "Fileman.h"
		#include "JA2 Demo Ads.h"
	#endif
#endif

#ifdef GERMAN

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

UINT16 ItemNames[MAXITEMS][80] =
{
	L"",
};


UINT16 ShortItemNames[MAXITEMS][80] =
{
	L"",
};

// Different weapon calibres
// CAWS is Close Assault Weapon System and should probably be left as it is
// NATO is the North Atlantic Treaty Organization
// WP is Warsaw Pact
// cal is an abbreviation for calibre
UINT16 AmmoCaliber[][20] =
{
	L"0",
	L".38 Kal",
	L"9mm",
	L".45 Kal",
	L".357 Kal",
	L"12 Kal",
	L"CAWS",
	L"5.45mm",
	L"5.56mm",
	L"7.62mm NATO",
	L"7.62mm WP",
	L"4.7mm",
	L"5.7mm",
	L"Monster",
	L"Rakete",
	L"Pfeil", // dart
	L"Cannon Ball", // cannon ball
	L".50 Kal",
	L"",
	L"9mm Schwer",
};

// This BobbyRayAmmoCaliber is virtually the same as AmmoCaliber however the bobby version doesnt have as much room for the words.
// 
// Different weapon calibres
// CAWS is Close Assault Weapon System and should probably be left as it is
// NATO is the North Atlantic Treaty Organization
// WP is Warsaw Pact
// cal is an abbreviation for calibre
UINT16 BobbyRayAmmoCaliber[][20] =
{
	L"0",
	L".38 cal",
	L"9mm",
	L".45 cal",
	L".357 cal",
	L"12 gauge",
	L"CAWS",
	L"5.45mm",
	L"5.56mm",
	L"7.62mm N.",
	L"7.62mm WP",
	L"4.7mm",
	L"5.7mm",
	L"Monster",
	L"Rocket",
	L"", // dart
};


UINT16 WeaponType[][30] =
{
	L"Andere",
	L"Pistole",
	L"Maschinenpistole",
	L"Schwere Maschinenpistole",
	L"Gewehr",
	L"Scharfsch�tzengewehr",
	L"Sturmgewehr",
	L"Leichtes Maschinengewehr",
	L"Schrotgewehr",
};

UINT16 TeamTurnString[][STRING_LENGTH] =
{
	L"Spielzug Spieler",
	L"Spielzug Gegner",
	L"Spielzug Kreaturen",
	L"Spielzug Miliz",
	L"Spielzug Zivilisten",
	// planning turn
};

UINT16 Message[][STRING_LENGTH] =
{
	L"",

	// In the following 8 strings, the %s is the merc's name, and the %d (if any) is a number.

	L"%s am Kopf getroffen, verliert 1 Weisheitspunkt!",
	L"%s an Schulter getroffen, verliert 1 Geschicklichkeitspunkt!",
	L"%s an Brust getroffen, verliert 1 St�rkepunkt!",
	L"%s an Beinen getroffen, verliert 1 Beweglichkeitspunkt!",
	L"%s am Kopf getroffen, verliert %d Weisheitspunkte!",
	L"%s an Schulter getroffen, verliert %d Geschicklichkeitspunkte!",
	L"%s an Brust getroffen, verliert %d Kraftpunkte!",
	L"%s an Beinen getroffen, verliert %d Beweglichkeitspunkte!",
	L"Unterbrechung!",

	// The first %s is a merc's name, the second is a string from pNoiseVolStr,
	// the third is a string from pNoiseTypeStr, and the last is a string from pDirectionStr

	L"", //OBSOLETE
	L"Your reinforcements have arrived!",

	// In the following four lines, all %s's are merc names

	L"%s l�dt nach.",
	L"%s hat nicht gen�gend Action-Punkte!",
	L"%s leistet Erste Hilfe. (Abbruch mit beliebiger Taste.)",
	L"%s und %s leisten Erste Hilfe. (Abbruch mit beliebiger Taste.)",
	// the following 17 strings are used to create lists of gun advantages and disadvantages
	// (separated by commas)
	L"zuverl�ssig",
	L"unzuverl�ssig",
	L"leicht zu reparieren",
	L"schwer zu reparaieren",
	L"hohe Durchschlagskraft",
	L"geringe Durchschlagskraft",
	L"feuert schnell",
	L"feuert langsam",
	L"hohe Reichweite",
	L"geringe Reichweite",
	L"leicht",
	L"schwer",
	L"klein",
	L"schneller Feuersto�",
	L"kein Feuersto�",
	L"gro�es Magazin",
	L"kleines Magazin",
	L"lautlos",							//Ja25: New string
	// In the following two lines, all %s's are merc names

	L"%s's Tarnung ist verbraucht.",
	L"%s's Tarnung ist fortgewaschen.",

	// The first %s is a merc name and the second %s is an item name

	L"Zweit-Waffe ist ohne Munition!",
	L"%s hat %s gestohlen.",

	// The %s is a merc name

	L"%s's Waffe kann keinen Feuersto� abgeben.",

	L"Sie haben bereits eines davon angebracht.", 
	L"Gegenst�nde zusammenf�gen?",


	// Both %s's are item names

	L"Sie k�nnen %s nicht mit %s zusammenf�gen",

	L"Kein",
	L"Mun entfernen",
	L"Modifikationen",

	//You cannot use "item(s)" and your "other item" at the same time.
	//Ex:  You cannot use sun goggles and you gas mask at the same time.
	L"Sie k�nnen nicht gleichzeitig %s und %s benutzen.",	//

	L"Der Gegenstand an Ihrem Cursor kann mit anderen Gegenst�nden kombiniert werden, indem Sie ihn in einem der vier Slots platzieren",
	L"Der Gegenstand an Ihrem Cursor kann mit anderen Gegenst�nden kombiniert werden, indem Sie ihn in einem der vier Modifikations-Slots platzieren. (In diesem Fall sind die Gegenst�nde jedoch nicht kompatibel.)",
	L"Im Sektor befinden sich noch Gegner!",
	L"Sie m�ssen %s noch immer %s geben", 
	L"%s wurde am Kopf getroffen!",
	L"Den Kampf abbrechen?",
	L"Diese Modifikation w�re dauerhaft. Fortfahren?",
	L"%s f�hlt sich erfrischt!",
	L"%s ist auf Murmeln ausgerutscht!",
	L"%s konnte %s nicht erwischen!",
	L"%s hat %s repariert",
	L"Unterbrechung f�r ",
	L"Kapitulieren?",
	L"Diese Person will ihre Hilfe nicht.", 
	L"Ich glaube, lieber NICHT!",
	L"Um in Skyriders Helikopter zu fliegen, m�ssen Sie dem FAHRZEUG/HELIKOPTER zuerst S�ldner zuweisen.",
	L"%s kann nur EINE Waffe zu gleicher Zeit laden",
	L"Spielzug Bloodcats", 
};


// the names of the towns in the game

//Ja25: All new text
STR16 pTownNames[] =
{
	L"",
	L"Varrez",
	L"Verlassene Mine",			//name of the mine
};
/*
Ja25 Old towns, dont need anymore
	L"",
	L"Omerta",
	L"Drassen",
	L"Alma",
	L"Grumm",
	L"Tixa",
	L"Cambria",
	L"San Mona",
	L"Estoni",
	L"Orta",
	L"Balime",
	L"Meduna",
	L"Chitzena",
};
*/


// the types of time compression. For example: is the timer paused? at normal speed, 5 minutes per second, etc.
// min is an abbreviation for minutes

STR16 sTimeStrings[] =
{
	L"Pause",
	L"Normal",
	L"5 min",
	L"30 min",
	L"60 min",
	L"6 Std", 
};


// Assignment Strings: what assignment does the merc  have right now? For example, are they on a squad, training, 
// administering medical aid (doctor) or training a town. All are abbreviated. 8 letters is the longest it can be.

STR16 pAssignmentStrings[] =
{
	L"Trupp 1",
	L"Trupp 2",
	L"Trupp 3",
	L"Trupp 4",
	L"Trupp 5",
	L"Trupp 6",
	L"Trupp 7",
	L"Trupp 8",
	L"Trupp 9",
	L"Trupp 10",
	L"Trupp 11",
	L"Trupp 12",
	L"Trupp 13",
	L"Trupp 14",
	L"Trupp 15",
	L"Trupp 16",
	L"Trupp 17",
	L"Trupp 18",
	L"Trupp 19",
	L"Trupp 20",
	L"Im Dienst", // on active duty
	L"Doktor", // administering medical aid	
	L"Patient", // getting medical aid
	L"Fahrzeug", // in a vehicle
	L"Transit", // in transit - abbreviated form
	L"Reparat.", // repairing
	L"Training", // training themselves
	L"Miliz", // training a town to revolt 
	L"Trainer", // training a teammate
	L"Rekrut", // being trained by someone else 
	L"Tot", // dead
	L"Unf�hig", // abbreviation for incapacitated
	L"Gefangen", // Prisoner of war - captured
	L"Hospital", // patient in a hospital		
	L"Leer",	//Vehicle is empty
};


STR16 pMilitiaString[] =
{
	L"Miliz", // the title of the militia box
	L"Frei", //the number of unassigned militia troops
	L"Sie k�nnen bei Feinden im Sektor keine Miliz einsetzen!",
};


STR16 pMilitiaButtonString[] =
{
	L"Autom.", // auto place the militia troops for the player
	L"Fertig", // done placing militia troops
};

STR16 pConditionStrings[] = 
{
	L"Exzellent", //the state of a soldier .. excellent health
	L"Gut", // good health
	L"Normal", // fair health
	L"Verwundet", // wounded health
	L"Ersch�pft", // tired
	L"Blutend", // bleeding to death
	L"Bewusstlos", // knocked out 
	L"Sterbend", // near death
	L"Tot", // dead
};

STR16 pEpcMenuStrings[] =
{
	L"Im Dienst", // set merc on active duty
	L"Patient", // set as a patient to receive medical aid
	L"Fahrzeug", // tell merc to enter vehicle
	L"Unbewacht", // let the escorted character go off on their own
	L"Abbruch", // close this menu
};


// look at pAssignmentString above for comments

STR16 pPersonnelAssignmentStrings[] =
{
	L"Trupp 1",
	L"Trupp 2",
	L"Trupp 3",
	L"Trupp 4",
	L"Trupp 5",
	L"Trupp 6",
	L"Trupp 7",
	L"Trupp 8",
	L"Trupp 9",
	L"Trupp 10",
	L"Trupp 11",
	L"Trupp 12",
	L"Trupp 13",
	L"Trupp 14",
	L"Trupp 15",
	L"Trupp 16",
	L"Trupp 17",
	L"Trupp 18",
	L"Trupp 19",
	L"Trupp 20",
	L"Im Dienst",
	L"Doktor",
	L"Patient",
	L"Fahrzeug",
	L"Transit",
	L"Reparat.",
	L"Training", 
	L"Miliz-Training", 
	L"Trainer",
	L"Rekrut", 
	L"Tot",
	L"Unf�hig",
	L"Gefangen",
	L"Hospital", 
	L"Leer",	// Vehicle is empty
};


// refer to above for comments

STR16 pLongAssignmentStrings[] =
{
L"Trupp 1",
	L"Trupp 2",
	L"Trupp 3",
	L"Trupp 4",
	L"Trupp 5",
	L"Trupp 6",
	L"Trupp 7",
	L"Trupp 8",
	L"Trupp 9",
	L"Trupp 10",
	L"Trupp 11",
	L"Trupp 12",
	L"Trupp 13",
	L"Trupp 14",
	L"Trupp 15",
	L"Trupp 16",
	L"Trupp 17",
	L"Trupp 18",
	L"Trupp 19",
	L"Trupp 20",
	L"Im Dienst",
	L"Doktor",
	L"Patient",
	L"Fahrzeug",
	L"Im Transit",
	L"Reparat.",
	L"Training", 
	L"Miliz-Training",
	L"Kolleg. train.",
	L"Rekrut", 
	L"Tot",
	L"Unf�hig",
	L"Gefangen",
	L"Hospital", // patient in a hospital 
	L"Leer",	// Vehicle is empty
};

// the contract options

STR16 pContractStrings[] =
{
	L"Vertragsoptionen:", 
	L"", // a blank line, required
	L"Einen Tag anbieten", // offer merc a one day contract extension
	L"Eine Woche anbieten", // 1 week
	L"Zwei Wochen anbieten", // 2 week
	L"Entlassen", //end merc's contract (used to be "Terminate")
	L"Abbruch", // stop showing this menu
};

STR16 pPOWStrings[] =
{
	L"Gefangener",  //an acronym for Prisoner of War
	L"??",
};

STR16 pLongAttributeStrings[] =
{
L"KRAFT", 
	L"BEWEGLICHKEIT",
	L"GESCHICKLICHKEIT", 
	L"WEISHEIT", 
	L"TREFFSICHERHEIT",
	L"MEDIZIN",
	L"TECHNIK",
	L"F�HRUNGSQUALIT�T",
	L"SPRENGSTOFFE",
	L"ERFAHRUNGSSTUFE",
};

STR16 pInvPanelTitleStrings[] =
{
	L"R�stung", // the armor rating of the merc
	L"Gewicht", // the weight the merc is carrying
	L"Tarn", // the merc's camouflage rating
};

STR16 pShortAttributeStrings[] =
{
	L"Bew", // the abbreviated version of : agility
	L"Ges", // dexterity
	L"Krf", // strength
	L"Fhr", // leadership
	L"Wsh", // wisdom
	L"Erf", // experience level
	L"Trf", // marksmanship skill
	L"Spr", // explosive skill
	L"Tec", // mechanical skill
	L"Med", // medical skill
};


STR16 pUpperLeftMapScreenStrings[] =
{
	L"Aufgabe", // the mercs current assignment 
	L"Vertrag", // the contract info about the merc
	L"Gesundh.", // the health level of the current merc 
	L"Moral", // the morale of the current merc
	L"Zustand",	// the condition of the current vehicle
	L"Tankinh.", // the fuel level of the current vehicle
};

/*
Ja25: doesnt appear to be used
STR16 pTrainingStrings[] =
{
	L"�ben", // tell merc to train self 
	L"Miliz", // tell merc to train town // 
	L"Trainer", // tell merc to act as trainer
	L"Rekrut", // tell merc to be train by other 
};
*/

STR16 pGuardMenuStrings[] =
{
	L"Feuerrate:", // the allowable rate of fire for a merc who is guarding
	L" Aggr. feuern", // the merc can be aggressive in their choice of fire rates
	L" Mun sparen", // conserve ammo 
	L" Eingeschr. Feuer", // fire only when the merc needs to 
	L"Andere Optionen:", // other options available to merc
	L" R�ckzug erlaubt", // merc can retreat
	L" Deckung erlaubt", // merc is allowed to seek cover
	L" Darf Kameraden helfen", // merc can assist teammates
	L"Fertig", // done with this menu
	L"Abbruch", // cancel this menu
};

// This string has the same comments as above, however the * denotes the option has been selected by the player

STR16 pOtherGuardMenuStrings[] =
{
	L"Feuerrate:",
	L" *Aggr. feuern*",
	L" *Mun sparen*",
	L" *Eingeschr. Feuer*",
	L"Andere Optionen:",
	L" *R�ckzug erlaubt*",
	L" *Deckung erlaubt*",
	L" *Darf Kameraden helfen*",
	L"Fertig",
	L"Abbruch",
};

STR16 pAssignMenuStrings[] =
{
	L"Im Dienst", // merc is on active duty
	L"Doktor", // the merc is acting as a doctor
	L"Patient", // the merc is receiving medical attention
	L"Fahrzeug", // the merc is in a vehicle
	L"Reparat.", // the merc is repairing items 
	L"Training", // the merc is training
	L"Abbruch", // cancel this menu
};

STR16 pRemoveMercStrings[] =
{
	L"S�ldner entf.", // remove dead merc from current team
	L"Abbruch",
};

STR16 pAttributeMenuStrings[] =
{
	L"Kraft",
	L"Geschicklichkeit",
	L"Beweglichkeit",
	L"Gesundheit",
	L"Treffsicherheit",
	L"Medizin",
	L"Technik",
	L"F�hrungsqualit�t",
	L"Sprengstoffe",
	L"Abbruch",
};

STR16 pTrainingMenuStrings[] =
{
 L"Training", // train yourself 
//Ja25: no militia L"Militia", // train the town 
 L"Trainer", // train your teammates 
 L"Rekrut",  // be trained by an instructor 
 L"Abbruch", // cancel this menu
};


STR16 pSquadMenuStrings[] =
{
	L"Trupp  1",
	L"Trupp  2",
	L"Trupp  3",
	L"Trupp  4",
	L"Trupp  5",
	L"Trupp  6",
	L"Trupp  7",
	L"Trupp  8",
	L"Trupp  9",
	L"Trupp 10",
	L"Trupp 11",
	L"Trupp 12",
	L"Trupp 13",
	L"Trupp 14",
	L"Trupp 15",
	L"Trupp 16",
	L"Trupp 17",
	L"Trupp 18",
	L"Trupp 19",
	L"Trupp 20",
	L"Abbruch",
};

STR16 pPersonnelTitle[] =
{
	L"Personal", // the title for the personnel screen/program application
};

STR16 pPersonnelScreenStrings[] =
{
	L"Gesundheit: ", // health of merc
	L"Beweglichkeit: ", 
	L"Geschicklichkeit: ",
	L"Kraft: ",
	L"F�hrungsqualit�t: ",
	L"Weisheit: ",
	L"Erf.-Stufe: ", // experience level
	L"Treffsicherheit: ", 
	L"Technik: ",
	L"Sprengstoffe: ",
	L"Medizin: ",
	L"Med. Versorgung: ", // amount of medical deposit put down on the merc
	L"Vertr.-Laufzeit: ", // time remaining on current contract
	L"Get�tet: ", // number of kills by merc
	L"Assistenz: ", // number of assists on kills by merc
	L"Tgl. Kosten:", // daily cost of merc
	L"Gesamtkosten:", // total cost of merc
	L"Vertrag:", // cost of current contract
	L"Tage im Dienst:", // total service rendered by merc
	L"Offene Schuld:", // amount left on MERC merc to be paid
	L"Treffer-Prozent:", // percentage of shots that hit target
	L"Eins�tze:", // number of battles fought
	L"Verwundungen:", // number of times merc has been wounded
	L"F�higkeiten:", 
	L"Keine F�higkeiten:",
};


//These string correspond to enums used in by the SkillTrait enums in SoldierProfileType.h
STR16 gzMercSkillText[] = 
{
	L"Keine F�higkeit",
	L"Schl�sser knacken",
	L"Mann gegen Mann",		//JA25: modified
	L"Elektronik",
	L"Nachtoperationen",			//JA25: modified
	L"Werfen",
	L"Unterrichten",
	L"Schwere Waffen",
	L"Autom. Waffen",
	L"Schleichen",
	L"Beidh�ndigkeit",
	L"Stehlen",
	L"Kampfsport",
	L"Messer",
	L"Scharfsch�tze",				//JA25: modified
	L"Tarnkunst",					//JA25: modified
	L"(Experte)",
};


// This is pop up help text for the options that are available to the merc

STR16 pTacticalPopupButtonStrings[] =
{
	L"|Stehen/Gehen",
	L"Ducken/Geduckt laufen (|C)",
	L"Stehen/|Rennen",
	L"Hinlegen/Kriechen (|P)",
	L"Schauen (|L)",
	L"Action",
	L"Sprechen",
	L"Untersuchen (|C|t|r|l)",

	//Pop up door menu
	L"Manuell �ffnen",
	L"Fallen aufsp�ren",
	L"Dietrich",
	L"Gewaltsam �ffnen",
	L"Falle entsch�rfen",
	L"Zusperren",
	L"Aufsperren",
	L"T�r aufsprengen",
	L"Brecheisen benutzen",
	L"Abbruch (|E|s|c)",
	L"Schlie�en",
};

// Door Traps. When we examine a door, it could have a particular trap on it. These are the traps.

STR16 pDoorTrapStrings[] =
{
	L"keine Falle",
	L"eine Sprengfalle",
	L"eine elektrische Falle",
	L"eine Alarm-Falle",
	L"eine Falle mit stummem Alarm",
};

// Contract Extension. These are used for the contract extension with AIM mercenaries.

STR16 pContractExtendStrings[] =
{
	L"Tag",
	L"Woche",
	L"zwei Wochen",
};

// On the map screen, there are four columns. This text is popup help text that identifies the individual columns.

STR16 pMapScreenMouseRegionHelpText[] =
{
	L"Charakter ausw�hlen",
	L"S�ldner einteilen",
	L"Plan-Marschroute",
	L"S�ldner |Vertrag",
	L"S�ldner entfernen",
	L"Schlafen", 
};

// volumes of noises 

STR16 pNoiseVolStr[] =
{
	L"LEISE",
	L"H�RBAR",
	L"LAUT",
	L"SEHR LAUT",
};

// types of noises 

STR16 pNoiseTypeStr[] = // OBSOLETE
{
	L"UNBEKANNT",
	L"BEWEGUNG",
	L"KNARREN",
	L"KLATSCHEN",
	L"AUFSCHLAG",
	L"SCHUSS",
	L"EXPLOSION",
	L"SCHREI",
	L"AUFSCHLAG",
	L"AUFSCHLAG",
	L"ZERBRECHEN",
	L"ZERSCHMETTERN",
};

// Directions that are used to report noises

STR16 pDirectionStr[] = 
{
	L"NORDOST",
	L"OST",
	L"S�DOST",
	L"S�D",
	L"S�DWEST",
	L"WEST",
	L"NORDWEST",
	L"NORD",
};

// These are the different terrain types. 

STR16 pLandTypeStrings[] =
{
	L"Geb�ude",
	L"Stra�e",
	L"Ebene",
	L"W�ste",
	L"Offener Wald",
	L"Dichter Wald",	 
	L"Sumpf",
	L"Wasser/See",	
	L"H�gel",
	L"Unpassierbar",
	L"Fluss",		//river from north to south
	L"Fluss",		//river from east to west
	L"Fremdland",
	//NONE of the following are used for directional travel, just for the sector description.
	L"Tropen",
	L"Farmland",
	L"Ebene, Stra�e",
	L"Wald, Stra�e", 
	L"Farm, Stra�e",
	L"Tropen, Stra�e",
	L"Wald, Stra�e", 
	L"K�ste",
	L"Berge, Stra�e",
	L"K�ste, Stra�e",
	L"W�ste, Stra�e",
	L"Sumpf, Stra�e",
	L"Wald, SAM-Stllg.",
	L"W�ste, SAM-Stllg.",
	L"Tropen, SAM-Stllg.",
	L"Meduna, SAM-Stllg.",
	
	L"Cambria Hospital",
	L"Drassen Flugplatz", 
	L"Meduna Flugplatz",
	L"SAM-Stellung",
	L"Rebellenlager", //The rebel base underground in sector A10
	L"Tixa, Katakmb.",	//The basement of the Tixa Prison (J9)
	L"Monsterh�hle",	//Any mine sector with creatures in it
	L"Orta, Keller",	//The basement of Orta (K4)
	L"Tunnel",				//The tunnel access from the maze garden in Meduna 
 									//leading to the secret shelter underneath the palace
	L"Bunker",				//The shelter underneath the queen's palace
	L"",							//Unused
	L"Komplex",				//Ja25: New Text
	L"Wachposten",		//Ja25: New Text
	L"Absturzstelle",		//Ja25: New Text  //!!! What's a Crash Site??? A scrap-yard? If yes, keep that translation.
	L"Kraftwerk",		//Ja25: New Text
	L"Berge",			//Ja25: New Text
	L"Unbekannt",				//Ja25: New Text

};

STR16 gpStrategicString[] =
{
	//     The first %s can either be bloodcats or enemies.
	L"",	//Unused
	L"%s wurden in Sektor %c%d entdeckt und ein weiterer Trupp wird in K�rze eintreffen.",	//STR_DETECTED_SINGULAR
	L"%s wurden in Sektor %c%d entdeckt und weitere Trupps werden in K�rze eintreffen.",	//STR_DETECTED_PLURAL
	L"Gleichzeitige Ankunft arrangieren?",													//STR_COORDINATE
	//Dialog strings for enemies.

	//The text that goes on the autoresolve buttons						
	L"Feind bietet Ihnen die Chance zur Aufgabe an.",			//STR_ENEMY_SURRENDER_OFFER
	L"Feind hat Ihre bewusstlosen S�ldner gefangengenommen.",	//STR_ENEMY_CAPTURED


	L"R�ckzug", 		//The retreat button				//STR_AR_RETREAT_BUTTON
	L"Fertig",		//The done button				//STR_AR_DONE_BUTTON

	//The headers are for the autoresolve type (MUST BE UPPERCASE)

	L"VERTEIDIGUNG",								//STR_AR_DEFEND_HEADER
	L"ANGRIFF",								//STR_AR_ATTACK_HEADER
	L"BEGEGNUNG",								//STR_AR_ENCOUNTER_HEADER
	L"Sektor",		//The Sector A9 part of the header		//STR_AR_SECTOR_HEADER

	//The battle ending conditions						

	L"SIEG!",								//STR_AR_OVER_VICTORY
	L"NIEDERLAGE!",								//STR_AR_OVER_DEFEAT
	L"KAPITULATION!",							//STR_AR_OVER_SURRENDERED
	L"GEFANGENNAHME!",								//STR_AR_OVER_CAPTURED
	L"ZUR�CKGEZOGEN!",								//STR_AR_OVER_RETREATED

	//These are the labels for the different types of enemies we fight in autoresolve.

	L"Miliz",							//STR_AR_MILITIA_NAME,
	L"Elite",								//STR_AR_ELITE_NAME,
	L"Trupp",								//STR_AR_TROOP_NAME,
	L"Verwal",								//STR_AR_ADMINISTRATOR_NAME,
	L"Monster",								//STR_AR_CREATURE_NAME,

	//Label for the length of time the battle took

	L"Vergangene Zeit",							//STR_AR_TIME_ELAPSED,

	//Labels for status of merc if retreating.  (UPPERCASE)			

	L"ZOG SICH ZUR�CK",								//STR_AR_MERC_RETREATED,
	L"ZIEHT SICH ZUR�CK",								//STR_AR_MERC_RETREATING,
	L"R�CKZUG",								//STR_AR_MERC_RETREAT,

	//PRE BATTLE INTERFACE STRINGS 
	//Goes on the three buttons in the prebattle interface.  The Auto resolve button represents
	//a system that automatically resolves the combat for the player without having to do anything.
	//These strings must be short (two lines -- 6-8 chars per line)

	L"Autom. Kampf",							//STR_PB_AUTORESOLVE_BTN,
	L"Gehe zu Sektor",							//STR_PB_GOTOSECTOR_BTN,
	L"R�ckzug",							//STR_PB_RETREATMERCS_BTN,

	//The different headers(titles) for the prebattle interface.
	L"FEINDBER�HRUNG",							//STR_PB_ENEMYENCOUNTER_HEADER,
	L"FEINDL. INVASION",							//STR_PB_ENEMYINVASION_HEADER, // 30
	L"FEINDL. HINTERHALT",								//STR_PB_ENEMYAMBUSH_HEADER
	L"FEINDLICHEN SEKTOR BETRETEN",				
	//STR_PB_ENTERINGENEMYSECTOR_HEADER
	L"MONSTERANGRIFF",							//STR_PB_CREATUREATTACK_HEADER
	L"BLOODCAT-�BERFALL",							//STR_PB_BLOODCATAMBUSH_HEADER
	L"BLOODCAT-H�HLE BETRETEN",			//STR_PB_ENTERINGBLOODCATLAIR_HEADER

	//Various single words for direct translation.  The Civilians represent the civilian
	//militia occupying the sector being attacked.  Limited to 9-10 chars

L"Ort",
	L"Feinde",
	L"S�ldner",
	L"Miliz",
	L"Monster",
	L"Bloodcats",
	L"Sektor",
	L"Keine",		//If there are no uninvolved mercs in this fight.
	L"(kein)",			//Acronym of Not Applicable
	L"T",			//One letter abbreviation of day
	L"h",			//One letter abbreviation of hour

	//TACTICAL PLACEMENT USER INTERFACE STRINGS
	//The four buttons 

	L"R�umen",
	L"Verteilen",
	L"Gruppieren",
	L"Fertig",

	//The help text for the four buttons.  Use \n to denote new line (just like enter).

	L"S�ldner r�umen ihre Positionen\n und k�nnen manuell neu platziert werden. (|C)", 
	L"S�ldner |schw�rmen �berall hin aus\n wenn der Button gedr�ckt wird.",
	L"Hiermit k�nnen Sie w�hlen, wo die S�ldner |gruppiert werden sollen.",
	L"Klicken Sie hier, wenn Sie die\n Positionen der S�ldner gew�hlt haben. (|E|n|t|e|r)",
	L"Sie m�ssen Ihre S�ldner positionieren\n bevor der Kampf beginnen kann.",

	//Various strings (translate word for word)

	L"Sektor",
	L"Anfangspositionen w�hlen",

	//Strings used for various popup message boxes.  Can be as long as desired.

	L"Sieht nicht gut aus. Gel�nde unzug�nglich. Versuchen Sie es an einem anderen Ort.",
	L"Platzieren Sie Ihre S�ldner im markierten Sektor auf der Karte.",

	//This message is for mercs arriving in sectors.  Ex:  Red has arrived in sector A9.
	//Don't uppercase first character, or add spaces on either end.

	L"ist angekommen: im Sektor", 

	//These entries are for button popup help text for the prebattle interface.  All popup help
	//text supports the use of \n to denote new line.  Do not use spaces before or after the \n.

	L"Wickelt Kampf |automatisch f�r Sie\nab, ohne Karte zu laden.",
	L"Sie k�nnen den Auto-Kampf-Modus nicht benutzen,\nwenn Sie selbst angreifen.",
	L"Sektor |betreten und Feind in Kampf verwickeln.",
	L"Gruppe in den vorherigen Sektor zu|r�ckziehen.",				//singular version
	L"Alle Gruppen in vorherigen Sektor zu|r�ckziehen.", //multiple groups with same previous sector

	//various popup messages for battle conditions.  

	//%c%d is the sector -- ex: A9
	L"Gegner attackieren Ihre Miliz im Sektor %c%d.",
	//%c%d is the sector -- ex: A9
	L"Monster attackieren Ihre Miliz im Sektor %c%d.",
	//1st %d refers to the number of civilians eaten by monsters, %c%d is the sector -- ex: A9
	//Note: the minimum number of civilians eaten will be two.
	L"Monster attackieren und t�ten %d Zivilisten im Sektor %s.",
	//%s is the sector -- ex: A9
	L"Gegner attackieren Ihre S�ldner im Sektor %s. Alle S�ldner sind bewusstlos!",
	//%s is the sector -- ex: A9
	L"Monster attackieren Ihre S�ldner im Sektor %s. Alle S�ldner sind bewusstlos!",
};

STR16 gpGameClockString[] = 
{
	//This is the day represented in the game clock.  Must be very short, 4 characters max.
	L"Tag",	
};

//When the merc finds a key, they can get a description of it which 
//tells them where and when they found it.
STR16 sKeyDescriptionStrings[2] =
{
	L"Gefunden im Sektor:",
	L"Gefunden am:",
};

//The headers used to describe various weapon statistics.

INT16		gWeaponStatsDesc[][ 14 ] =
{
	L"Gewicht (%s):", 
	L"Status:",
	L"Anzahl:", 		// Number of bullets left in a magazine
	L"Reichw.:",		// Range
	L"Schad.:",		// Damage
	L"AP:",			// abbreviation for Action Points
	L"",
	L"=",
	L"=",
};

//The headers used for the merc's money.

INT16 gMoneyStatsDesc[][ 13 ] =
{
	L"Betrag",
	L"Verbeib.:", //this is the overall balance
	L"Betrag",
	L"Teilen:", // the amount he wants to separate from the overall balance to get two piles of money

	L"Derzeit",
	L"Saldo",
	L"Betrag",
	L"Abheben",
};

//The health of various creatures, enemies, characters in the game. The numbers following each are for comment
//only, but represent the precentage of points remaining. 

UINT16 zHealthStr[][13] =
{
	L"STERBEND",		//	>= 0
	L"KRITISCH", 	//	>= 15
	L"SCHLECHT",	//	>= 30
	L"VERWUNDET",	//	>= 45
	L"GESUND",		//	>= 60
	L"STARK",			// 	>= 75
	L"EXZELLENT",	// 	>= 90	 
};

STR16	gzMoneyAmounts[6] = 
{ 
	L"$1000",
	L"$100",
	L"$10",
	L"O.K.",
	L"Teilen",
	L"Abheben",
};

// short words meaning "Advantages" for "Pros" and "Disadvantages" for "Cons." 
INT16		gzProsLabel[10] = 
{
	L"Pro:",
};

INT16		gzConsLabel[10] = 
{
	L"Kontra:",
};

//Conversation options a player has when encountering an NPC
UINT16 zTalkMenuStrings[6][ SMALL_STRING_LENGTH ] =
{
	L"Wie bitte?", 	//meaning "Repeat yourself" 
	L"Freundlich",		//approach in a friendly
	L"Direkt",		//approach directly - let's get down to business
	L"Drohen",		//approach threateningly - talk now, or I'll blow your face off
	L"Geben",		
	L"Rekrutieren",
};

//Some NPCs buy, sell or repair items. These different options are available for those NPCs as well.
UINT16 zDealerStrings[4][ SMALL_STRING_LENGTH ]=
{
	L"Handeln",	
	L"Kaufen",
	L"Verkaufen",
	L"Reparieren",
};

UINT16 zDialogActions[1][ SMALL_STRING_LENGTH ] = 
{
	L"Fertig",
};


//These are vehicles in the game.

STR16 pVehicleStrings[] =
{
 L"Eldorado",
 L"Hummer", // a hummer jeep/truck -- military vehicle
 L"Eiskrem-Laster",
 L"Jeep",
 L"Panzer",
 L"Helikopter",
};

STR16 pShortVehicleStrings[] =
{
	L"Eldor.",
	L"Hummer",			// the HMVV
	L"Laster",
	L"Jeep",
	L"Panzer",
	L"Heli", 				// the helicopter
};

STR16	zVehicleName[] =
{
	L"Eldorado",
	L"Hummer",		//a military jeep. This is a brand name.
	L"Laster",			// Ice cream truck
	L"Jeep",
	L"Panzer",
	L"Heli", 		//an abbreviation for Helicopter
};


//These are messages Used in the Tactical Screen

UINT16 TacticalStr[][ MED_STRING_LENGTH ] =
{
	L"Luftangriff",
	L"Automatisch Erste Hilfe leisten?",
	
	// CAMFIELD NUKE THIS and add quote #66.
	
	L"%s bemerkt, dass Teile der Lieferung fehlen.",
	
	// The %s is a string from pDoorTrapStrings
	
	L"Das Schloss hat %s.", 
	L"Es gibt kein Schloss.",
	L"Erfolg!",
	L"Fehlschlag.",
	L"Erfolg!",
	L"Fehlschlag.",
	L"Das Schloss hat keine Falle.",
	L"Erfolg!",
	// The %s is a merc name
	L"%s hat nicht den richtigen Schl�ssel.",
	L"Die Falle am Schloss ist entsch�rft.",
	L"Das Schloss hat keine Falle.",
	L"Geschl.",
	L"T�R",
	L"FALLE",
	L"GESCHL.",
	L"OFFEN",
	L"ZERST�RT",
	L"Hier ist ein Schalter. Bet�tigen?",
	L"Falle entsch�rfen?",
	L"Zur�ck...",
	L"Weiter...",
	L"Mehr...",


	// In the next 2 strings, %s is an item name

	L"%s wurde auf dem Boden platziert.",
	L"%s ist jetzt bei %s.",

	// In the next 2 strings, %s is a name

	L"%s hat den vollen Betrag erhalten.",
	L"%s bekommt noch %d.",
	L"Detonationsfrequenz ausw�hlen:",		//in this case, frequency refers to a radio signal
	L"Wie viele Z�ge bis zur Explosion:",	//how much time, in turns, until the bomb blows
	L"Ferngesteuerte Z�ndung einstellen:",//in this case, frequency refers to a radio signal
	L"Falle entsch�rfen?",
	L"Blaue Flagge entfernen?",
	L"Blaue Flagge aufstellen?",
	L"Beende Zug",


	// In the next string, %s is a name. Stance refers to way they are standing.

	L"Wollen Sie %s wirklich angreifen?",
	L"Oh, Fahrzeuge k�nnen Position nicht �ndern.",
	L"Der Roboter kann Position nicht �ndern.",

	// In the next 3 strings, %s is a name

	L"%s kann die Haltung hier nicht �ndern.",
	L"%s kann hier nicht versorgt werden.",	
	L"%s braucht keine Erste Hilfe.",
	L"Kann sich nicht dorthin bewegen.",
	L"Ihr Team ist komplett. Kein Platz mehr f�r Rekruten.",	//there's no room for a recruit on the player's team


	// In the next string, %s is a name

	L"%s wurde rekrutiert",

	// Here %s is a name and %d is a number

	L"%s bekommt noch %d $.",

	// In the next string, %s is a name

	L"%s eskortieren?",

	// In the next string, the first %s is a name and the second %s is an amount of money (including $ sign)

	L"%s f�r einmaligen Betrag von %s anheuern?",      //Ja25: modified

	// This line is used repeatedly to ask player if they wish to participate in a boxing match. 

	L"Sie wollen k�mpfen?",

	// In the next string, the first %s is an item name and the 
	// second %s is an amount of money (including $ sign)

	L"%s f�r %s kaufen?",

	// In the next string, %s is a name

	L"%s wird von Trupp %d eskortiert.",

	// These messages are displayed during play to alert the player to a particular situation

	L"HEMMUNG",					//weapon is jammed.
	L"Roboter braucht %s Kaliber Mun.",		//Robot is out of ammo
	L"Dahin werfen? Wird nicht klappen.",		//Merc can't throw to the destination he selected


	// These are different buttons that the player can turn on and off.

	L"Stealth Modus (|Z)",
	L"Karten-Scree|n",
	L"Spielzug been|den",
	L"Sprechen",
	L"Stumm",
	L"Aufstehen (|P|g|U|p)",
	L"Cursor Level (|T|a|b)",
	L"Klettern / Springen",
	L"Ducken (|P|g|D|n)",
	L"Untersuchen (|C|t|r|l)",
	L"Vorheriger S�ldner",
	L"N�chster S�ldner (|S|p|a|c|e)",
	L"|Optionen",
	L"Feuersto� (|B)",
	L"B|lickwende",
	L"Gesundheit: %d/%d\nEnergie: %d/%d\nMoral: %s",
	L"Was?",					//this means "what?" 
	L"Forts.",					//an abbrieviation for "Continued" 
	L"Stumm aus f�r %s.",
	L"Stumm f�r %s.", //
	L"Gesdht.: %d/%d\nTank: %d/%d",
	L"Fahrzeug verlassen",
	L"Trupp wechseln ( |S|h|i|f|t |S|p|a|c|e )",
	L"Fahren",
	L" - - - ",						//this is an acronym for "Not Applicable." 
	L"Benutzen ( Nahkampf )",
	L"Benutzen ( Feuerwaffe )",
	L"Benutzen ( Klingenwaffe )",
	L"Benutzen ( Sprengstoff )",
	L"Benutzen ( Verbandskasten )",
	L"(Fangen)",
	L"(Nachladen)",
	L"(Geben)",
	L"%s wurde ausgel�st.", 
	L"%s ist angekommen.",
	L"%s hat keine Action-Punkte mehr.",
	L"%s ist nicht verf�gbar.",
	L"%s ist fertig verbunden.",
	L"%s sind die Verb�nde ausgegangen.",
	L"Feind im Sektor!",
	L"Keine Feinde in Sicht.",
	L"Nicht genug Action-Punkte.",
	L"Niemand benutzt die Fernbedienung.",
	L"Feuersto� hat Magazin geleert!",
	L"SOLDAT",
	L"MONSTER", 
	L"MILIZ",
	L"ZIVILIST",
	L"Sektor verlassen",
	L"OK",
	L"Abbruch",
	L"Gew�hlter S�ldner",
	L"Ganzer Trupp",
	L"Gehe zu Sektor",
	L"Gehe zu Karte", 
	L"Sie k�nnen den Sektor von dieser Seite aus nicht verlassen.",
	L"%s ist zu weit weg.",
	L"Baumkronen entfernen",
	L"Baumkronen zeigen",
	L"KR�HE",				//Crow, as in the large black bird
	L"NACKEN",
	L"KOPF",
	L"K�RPER",
	L"BEINE",
	L"Der Herrin sagen, was sie wissen will?",
	L"Fingerabdruck-ID gespeichert",
	L"Falsche Fingerabdruck-ID. Waffe au�er Betrieb",
	L"Ziel erfasst",
	L"Weg blockiert",
	L"Geld einzahlen/abheben",		//Help text over the $ button on the Single Merc Panel 
	L"Niemand braucht Erste Hilfe.",
	L"Klemmt.",			//Short form of JAMMED, for small inv slots
	L"Kann dort nicht hin.",					// used ( now ) for when we click on a cliff
	L"Weg versperrt. Den Platz mit dieser Person tauschen?",
	L"Person will sich nicht bewegen.",
	// In the following message, '%s' would be replaced with a quantity of money (e.g. $200)
	L"Mit der Zahlung von %s einverstanden?",
	L"Gratisversorgung akzeptieren?",
	L"Daryl heiraten?",
	L"Schl�sselring",
	L"Das ist mit einem EPC nicht m�glich.",
	L"Krott verschonen?",
	L"Au�er Reichweite",
	L"Arbeiter",	//People that work in mines to extract precious metals
	L"Fahrzeug kann nur zwischen Sektoren fahren",
	L"Autom. Erste Hilfe jetzt nicht m�glich",
	L"Weg f�r %s blockiert",
	L"Ihre von Deidrannas Truppe gefangenen Soldaten, sind hier eingesperrt", 		
	L"Schloss getroffen",
	L"Schloss zerst�rt",
	L"Jemand versucht, die T�r ebenfalls zu benutzen.",
	L"Gesundh.: %d/%d\nTank: %d/%d",
	L"%s kann %s nicht sehen.", // Cannot see person trying to talk to
};

//Varying helptext explains (for the "Go to Sector/Map" checkbox) what will happen given different circumstances in the "exiting sector" interface.
STR16 pExitingSectorHelpText[] =
{
	//Helptext for the "Go to Sector" checkbox button, that explains what will happen when the box is checked.
	L"Wenn Sie das K�stchen aktivieren, wird er n�chste Sektor sofort geladen.",
	L"Da die Reise Zeit braucht, kommen Sie sofort zum Kartenbildschirm,\nwenn Sie das K�stchen aktivieren.",

	//If you attempt to leave a sector when you have multiple squads in a hostile sector.
	L"Dieser Sektor wird vom Feind beherrscht. Sie k�nnen keine S�ldner hierlassen.\nRegeln Sie das, bevor Sie neue Sektoren laden.",

	//Because you only have one squad in the sector, and the "move all" option is checked, the "go to sector" option is locked to on. 
	//The helptext explains why it is locked.
	L"Wenn die restlichen S�ldner den Sektor verlassen haben,\nwird sofort der n�chste Sektor geladen.",
	L"Wenn die restlichen S�ldner den Sektor verlassen haben,\nkommen Sie sofort zum Kartenbildschirm,\nda die Reise Zeit braucht.",



	//If an EPC is the selected merc, it won't allow the merc to leave alone as the merc is being escorted.  The "single" button is disabled.
	L"%s kann den Sektor nicht allein bzw. ohne Eskorte verlassen.",

	//If only one conscious merc is left and is selected, and there are EPCs in the squad, the merc will be prohibited from leaving alone.
	//There are several strings depending on the gender of the merc and how many EPCs are in the squad.
	//DO NOT USE THE NEWLINE HERE AS IT IS USED FOR BOTH HELPTEXT AND SCREEN MESSAGES!

	L"%s kann Sektor nicht verlassen, da er %s eskortiert.", //male singular
	L"%s kann Sektor nicht verlassen, da sie %s eskortiert.", //female singular
	L"%s kann Sektor nicht verlassen, da er mehrere Personen eskortiert.", //male plural
	L"%s kann Sektor nicht verlassen, da sie mehrere Personen eskortiert.", //female plural

	//If one or more of your mercs in the selected squad aren't in range of the traversal area, then the  "move all" option is disabled,
	//and this helptext explains why.
	L"Alle S�ldner m�ssen in der N�he sein\ndamit der Trupp weiterreisen kann.",

	L"", //UNUSED

	//Standard helptext for single movement.  Explains what will happen (splitting the squad)
	L"Ist das K�stchen aktiviert, reist %s alleine und\nerzeugt automatisch einen neuen Trupp.",

	//Standard helptext for all movement.  Explains what will happen (moving the squad)
	L"Ist das K�stchen aktiviert, reist der ausgew�hlte Trupp\nweiter und verl�sst den Sektor.",

	//This strings is used BEFORE the "exiting sector" interface is created.  If you have an EPC selected and you attempt to tactically
	//traverse the EPC while the escorting mercs aren't near enough (or dead, dying, or unconscious), this message will appear and the
	//"exiting sector" interface will not appear.  This is just like the situation where
	//This string is special, as it is not used as helptext.  Do not use the special newline character (\n) for this string.
	L"%s wird von Ihren S�ldnern eskortiert und kann den Sektor nicht alleine verlassen. Ihre anderen S�ldner m�ssen in der N�he sein.",
};

STR16 pRepairStrings[] = 
{
	L"Gegenst�nde", 		// tell merc to repair items in inventory
	L"SAM-Stellung", 		// tell merc to repair SAM site - SAM is an acronym for Surface to Air Missile
	L"Abbruch", 		// cancel this menu
	L"Roboter", 		// repair the robot
};


// NOTE: combine prestatbuildstring with statgain to get a line like the example below.
// "John has gained 3 points of marksmanship skill." 

STR16 sPreStatBuildString[] =
{
	L"verlor", 		// the merc has lost a statistic
	L"gewann", 		// the merc has gained a statistic
	L"Punkt",	// singular
	L"Punkte",	// plural
	L"Level",	// singular
	L"Level",	// plural
};

STR16 sStatGainStrings[] =
{
	L"Gesundheit.",
	L"Beweglichkeit",
	L"Geschicklichkeit",
	L"Weisheit.",
	L"Medizin-F�hgkt.",
	L"Sprengstoff-F�hgkt.",
	L"Technik-F�hgkt.",
	L"Treffsicherheit.",
	L"Erfahrung.",
	L"Kraft.",
	L"F�hrungsqualit�t.",
};


STR16 pHelicopterEtaStrings[] =
{
	L"Gesamtdistanz: ", 			// total distance for helicopter to travel
	L" Sicher:  ", 		// Number of safe sectors
	L" Heikel:", 		// Number of unsafe sectors
	L"Gesamtkosten: ",// total cost of trip by helicopter
	L"Ankunft: ", 				// ETA is an acronym for "estimated time of arrival" 
	
	// warning that the sector the helicopter is going to use for refueling is under enemy control
	L"Der Heli hat kaum noch Sprit und muss im feindlichen Gebiet landen.",	
	L"Passagiere: ",
	L"Skyrider oder Absprungsort ausw�hlen?",
	L"Skyrider",
	L"Absprung", 
};

STR16 sMapLevelString[] =
{
	L"Ebene:", 			// what level below the ground is the player viewing in mapscreen
};

STR16 gsLoyalString[] =
{
	L"Loyalit�t", 			// the loyalty rating of a town ie : Loyal 53%
};


// error message for when player is trying to give a merc a travel order while he's underground.

STR16 gsUndergroundString[] =
{
	L"Kann unterirdisch keinen Marschbefehl empfangen.", 
};

STR16 gsTimeStrings[] =
{
	L"h",				// hours abbreviation
	L"m",				// minutes abbreviation
	L"s",				// seconds abbreviation
	L"T",				// days abbreviation
};

// text for the various facilities in the sector

STR16 sFacilitiesStrings[] =
{
	L"Keine",
	L"Hospital",
	L"Fabrik",
	L"Gef�ngnis",
	L"Milit�r",
	L"Flughafen",
	L"Reichweite",		// a field for soldiers to practise their shooting skills
};

// text for inventory pop up button

STR16 pMapPopUpInventoryText[] =
{
	L"Inventar",
	L"Exit",
};

// town strings

STR16 pwTownInfoStrings[] =
{
	L"Gr��e",					// 0 // size of the town in sectors
	L"", 						// blank line, required
	L"unter Kontrolle", 					// how much of town is controlled
	L"Keine", 					// none of this town
	L"Zugeh�rige Mine", 				// mine associated with this town
	L"Loyalit�t",					// 5 // the loyalty level of this town
	L"Trainiert", 					// the forces in the town trained by the player
	L"",
	L"Wichtigste Geb�ude", 				// main facilities in this town
	L"Level", 					// the training level of civilians in this town
	L"Zivilistentraining",				// 10 // state of civilian training in town
	L"Miliz", 					// the state of the trained civilians in the town
};

// Mine strings

STR16 pwMineStrings[] =
{
	L"Mine",						// 0
	L"Silber",
	L"Gold",
	L"Tagesproduktion",
	L"M�gl. Produktion",
	L"Verlassen",				// 5
	L"Geschlossen",
	L"Ersch�pft",
	L"Produziert",
	L"Status",
	L"Produktionsrate",
	L"Erz-Typ",				// 10
	L"Kontrolle �ber Stadt",
	L"Loyalit�t der Stadt",
//	L"Minenarbeiter",


};

// blank sector strings

STR16 pwMiscSectorStrings[] =
{
	L"Gegn. Kr�fte",
	L"Sektor",
	L"# der Gegenst�nde",
	L"Unbekannt",
	L"Kontrolliert",
	L"Ja",
	L"Nein",
};

// error strings for inventory

STR16 pMapInventoryErrorString[] =
{
	L"%s ist nicht nah genug.",	//Merc is in sector with item but not close enough
	L"Dieser S�ldner ist nicht w�hlbar.", 
	L"%s ist nicht im Sektor.",
	L"W�hrend eines Kampfes m�ssen Sie Gegenst�nde manuell nehmen.",
	L"W�hrend eines Kampfes m�ssen Sie Gegenst�nde manuell fallenlassen.",
	L"%s ist nicht im Sektor und kann Gegenstand nicht fallenlassen.",
};

STR16 pMapInventoryStrings[] =
{
	L"Ort", 			// sector these items are in
	L"Zahl der Gegenst�nde", 		// total number of items in sector
};


// help text for the user

STR16 pMapScreenFastHelpTextList[] =
{
	L"Klicken Sie in die 'Auftr�ge'-Spalte, um die Aufgabe eines S�ldners zu �ndern und ihn einem anderen Trupp, einem Reparatur- oder �rzteteam zuzuweisen,",
	L"Klicken Sie in die 'Auftr�ge'-Spalte, um einen S�ldner an einen anderen Zielort zu versetzen.",
	L"Hat ein S�ldner seinen Marschbefehl erhalten, kann er sich mit Hilfe des Zeitraffers schneller bewegen.",
	L"Die linke Maustaste w�hlt den Sektor aus. Ein zweiter Klick damit erteilt einen Marschbefehl. Mit der rechten Maustaste erhalten Sie Kurzinfos �ber den Sektor.",
	L"Mit der Taste 'h' k�nnen Sie jederzeit Hilfe aufrufen.",
	L"Testtext",
	L"Testtext",
	L"Testtext",
	L"Testtext",
	L"Mit diesem Bildschirm k�nnen Sie nicht viel anstellen, ehe Sie in Arulco ankommen. Wenn Sie Ihr Team erstellt haben, klicken Sie unten links auf den Zeitraffer-Button. Dadurch vergeht die Zeit schneller, bis Ihr Team Arulco erreicht.",
};

// movement menu text

STR16 pMovementMenuStrings[] =
{
	L"S�ldner in Sektor bewegen", 	// title for movement box 
	L"Reiseroute planen", 		// done with movement menu, start plotting movement
	L"Abbruch", 	// cancel this menu
	L"Andere",			// title for group of mercs not on squads nor in vehicles
};





STR16 pUpdateMercStrings[] =
{
	L"Oops:", 			// an error has occured
	L"S�ldnervertrag abgelaufen:", 	// this pop up came up due to a merc contract ending
	L"S�ldnerauftrag ausgef�hrt:", // this pop up....due to more than one merc finishing assignments
	L"Diese S�ldner arbeiten wieder:", // this pop up ....due to more than one merc waking up and returing to work
	L"Diese S�ldner schlafen:", // this pop up ....due to more than one merc being tired and going to sleep
	L"Vertrag l�uft bald aus:", 	//this pop up came up due to a merc contract ending
};

// map screen map border buttons help text

STR16 pMapScreenBorderButtonHelpText[] =
{
	L"St�dte zeigen (|W)",
	L"|Minen zeigen",
	L"|Teams & Feinde zeigen",
	L"Luftr|aum zeigen",
	L"Gegenst�nde zeigen (|I)",
	L"Miliz inaktiv",		//Ja25: new string
};


STR16 pMapScreenBottomFastHelp[] =
{
	L"|Laptop",
	L"Taktik (|E|s|c)",
	L"|Optionen",
	L"Zeitraffer (|+)", 	// time compress more
	L"Zeitraffer (|-)", 	// time compress less
	L"Vorherige Nachricht (|U|p)\nVorherige Seite (|P|g|U|p)", 	// previous message in scrollable list
	L"N�chste Nachricht (|D|o|w|n)\nN�chste Seite (|P|g|D|n)", 	// next message in the scrollable list
	L"Zeit Start/Stop (|S|p|a|c|e)",	// start/stop time compression
};

STR16 pMapScreenBottomText[] =
{
	L"Kontostand", 	// current balance in player bank account
};

STR16 pMercDeadString[] =
{
	L"%s ist tot.",
};


STR16 pDayStrings[] =
{
	L"Tag",
};

// the list of email sender names

STR16 pSenderNameList[] =
{
	L"Enrico",
	L"Psych Pro Inc",
	L"Help Desk",
	L"Psych Pro Inc",
	L"Speck",
	L"R.I.S.",		//5
	L"Barry",
	L"Blood",
	L"Lynx",
	L"Grizzly",
	L"Vicki",			//10
	L"Trevor",
	L"Grunty",
	L"Ivan",
	L"Steroid",
	L"Igor",			//15
	L"Shadow",
	L"Red",
	L"Reaper",
	L"Fidel",
	L"Fox",				//20
	L"Sidney",
	L"Gus",
	L"Buns",
	L"Ice",
	L"Spider",		//25
	L"Cliff",
	L"Bull",
	L"Hitman",
	L"Buzz",
	L"Raider",		//30
	L"Raven",
	L"Static",
	L"Len",
	L"Danny",
	L"Magic",
	L"Stephan",
	L"Scully",
	L"Malice",
	L"Dr.Q",
	L"Nails",
	L"Thor",
	L"Scope",
	L"Wolf",
	L"MD",
	L"Meltdown",
	//----------
	L"M.I.S. Versicherung",	
	L"Bobby Rays",
	L"Kingpin",
	L"John Kulba",
	L"A.I.M.",
	L"Miguel Cordona",		//Ja25:  New
};


// next/prev strings

STR16 pTraverseStrings[] =
{
	L"Vorherige",
	L"N�chste",
};

// new mail notify string 

STR16 pNewMailStrings[] =
{
 L"Sie haben neue eMails...",
};


// confirm player's intent to delete messages

STR16 pDeleteMailStrings[] =
{
	L"eMail l�schen?",
	L"UNGELESENE eMail l�schen?",
};


// the sort header strings

STR16 pEmailHeaders[] =
{
	L"Sender:",
	L"Betreff:",
	L"Datum:",
};

// email titlebar text

STR16 pEmailTitleText[] =
{
	L"Mailbox",
};


// the financial screen strings
STR16 pFinanceTitle[] =
{
	L"Buchhalter Plus",		//the name we made up for the financial program in the game
};

STR16 pFinanceSummary[] =
{
	L"Haben:", 				//the credits column (to ADD money to your account)
	L"Soll:", 				//the debits column (to SUBTRACT money from your account)
	L"Eink�nfte vom Vortag:",
	L"Sonstige Einzahlungen vom Vortag:",
	L"Soll vom Vortag:",
	L"Kontostand Ende des Tages:",
	L"Eink�nfte heute:",
	L"Sonstige Einzahlungen von heute:",
	L"Heutiges Soll:",
	L"Aktueller Kontostand:",
	L"Voraussichtliche Eink�nfte:",
	L"Gesch�tzter Kontostand:", 		// projected balance for player for tommorow
};


// headers to each list in financial screen

STR16 pFinanceHeaders[] =
{
	L"Tag", 					// the day column
	L"Haben", 				//the credits column (to ADD money to your account)
	L"Soll", 					//the debits column (to SUBTRACT money from your account)
	L"Kontobewegungen", 			// transaction type - see TransactionText below
	L"Kontostand", 				// balance at this point in time
	L"Seite", 				// page number
	L"Tag(e)", 				// the day(s) of transactions this page displays 
};


STR16 pTransactionText[] =
{
	L"Angesammelte Zinsen",			// interest the player has accumulated so far
	L"Anonyme Einzahlung",
	L"Bearbeitungsgeb�hr", 
	L"Angeheuert", 				// Merc was hired
	L"Erstattung an %s"			//Ja25: new
	L"Einkauf bei Bobby Rays",	 		// Bobby Ray is the name of an arms dealer
//Ja25: MERC now has a 1 time fee
//	L"Ausgeglichene Konten bei M.E.R.C.",
	L"%s von M.E.R.C. angeheuert",		//Ja25: new text
	L"Krankenversicherung f�r %s", 		// medical deposit for merc 
	L"BSE-Profilanalyse", 		// IMP is the acronym for International Mercenary Profiling
	L"Versicherung f�r %s abgeschlossen", 
	L"Versicherung f�r %s verringert",
	L"Versicherung f�r %s verl�ngert", 				// johnny contract extended
	L"Versicherung f�r %s gek�ndigt", 
	L"Versicherungsanspruch f�r %s", 		// insurance claim for merc
	L"1 Tag", 				// merc's contract extended for a day
	L"1 Woche", 				// merc's contract extended for a week
	L"2 Wochen", 				// ... for 2 weeks
	L"Minen-Einkommen", 
	L"", //String nuked
	L"Gekaufte Blumen",
	L"Volle med. R�ckzahlung f�r %s",
	L"Teilw. med. R�ckzahlung f�r %s",
	L"Keine med. R�ckzahlung f�r %s",
	L"Zahlung an %s",		// %s is the name of the npc being paid
	L"�berweisen an %s", 			// transfer funds to a merc
	L"�berweisen von %s", 		// transfer funds from a merc
	L"Miliz in %s ausr�sten", // initial cost to equip a town's militia
	L"Gekaufte Gegenst�nde von %s.",	//is used for the Shop keeper interface. The dealers name will be appended to the end of the string.
	L"%s angelegtes Geld.",
};



//!!! There were UGLY symbols (squares) here... likely to crash the file 
//!!! (made a copy, (see below) but kept this for checking) Are there some 
// characters or lines missing???
//;
//
//STR16 pTransactionAlternateText[] =
//{
//	L"Insurance for", 				// insur by one day.", 		
//		// entend mercs contract by a day
//	L"Ext. %s contract by 1 week.",
//	Ext. %s contract by 2 weeks.",
//};
//!!! (End of that passage with the ugly symbols...) /////////////////////////////////////////////////



//!!! Here comes the copy! PLEASE CHECK IT!!!! ///////////////////////
;

STR16 pTransactionAlternateText[] =
{
	L"Versicherung f�r", 				// insurance for a merc
	L"%ss Vertrag 1 Woche verl�ngern.",
	L"%ss Vertrag 2 Wochen verl�ngern.",
};

//!!! End of the copy! //////////////////////////////////////////////



// helicopter pilot payment 

STR16 pSkyriderText[] =
{
	L"Skyrider wurden $%d gezahlt", 			// skyrider was paid an amount of money
	L"Skyrider bekommt noch $%d", 		// skyrider is still owed an amount of money
	L"Skyrider hat tanken beendet",	// skyrider has finished refueling
	L"",//unused
	L"",//unused
	L"Skyrider ist bereit f�r weiteren Flug.", // Skyrider was grounded but has been freed
	L"Skyrider hat keine Passagiere. Wenn Sie S�ldner in den Sektor transportieren wollen, weisen Sie sie einem Fahrzeug/Helikopter zu.",
};


// strings for different levels of merc morale

STR16 pMoralStrings[] =
{
	L"Bestens", 
	L"Gut",
	L"Stabil",
	L"Schwach",
	L"Panik",
	L"Schlimm",
};

// Mercs equipment has now arrived and is now available in Omerta or Drassen.

STR16 pLeftEquipmentString[] =
{ 
	L"%ss Ausr�stung ist jetzt in Omerta verf�gbar (A9).", 
	L"%ss Ausr�stung ist jetzt in Drassen verf�gbar (B13).",
};

// Status that appears on the Map Screen

STR16 pMapScreenStatusStrings[] =
{
	L"Gesundheit",
	L"Energie",
	L"Moral",
	L"Zustand",	// the condition of the current vehicle (its "health")
	L"Tank",	// the fuel level of the current vehicle (its "energy")
};


STR16 pMapScreenPrevNextCharButtonHelpText[] =
{
	L"Vorheriger S�ldner (|L|e|f|t)", 			// previous merc in the list
	L"N�chster S�ldner (|R|i|g|h|t)", 				// next merc in the list
};


STR16 pEtaString[] =
{
	L"Ank:", 				// eta is an acronym for Estimated Time of Arrival
};

STR16 pTrashItemText[] =
{
	L"Sie werden es nie wiedersehen. Trotzdem wegwerfen?", 	// do you want to continue and lose the item forever
	L"Dieses Ding sieht SEHR wichtig aus. Sie sie GANZ SICHER, da� Sie es wegwerfen wollen?", // does the user REALLY want to trash this item
};


STR16 pMapErrorString[] = 
{
	L"Trupp kann nicht aufbrechen, wenn einer schl�ft.",

//1-5
	L"Wir m�ssen zuerst an die Oberfl�che.",
	L"Marschbefehle? Wir sind in einem feindlichen Sektor!",
	L"Wenn S�ldner reisen sollen, m�ssen sie einem Trupp oder Fahrzeug zugewiesen werden.",
	L"Sie haben noch keine Teammitglieder.", 		// you have no members, can't do anything 
	L"S�ldner kann das nicht erf�llen.",			 		// merc can't comply with your order
//6-10
	L"ben�tigt Eskorte. Platzieren Sie ihn in einem Trupp mit Eskorte.", // merc can't move unescorted .. for a male
	L"ben�tigt Eskorte. Platzieren Sie sie in einem Trupp mit Eskorte.", // for a female
	L"S�ldner hat Arulco noch nicht erreicht!",
	L"Sieht so aus, als m�sste zuerst ein Vertrag ausgehandelt werden.",
	L"",
//11-15
	L"Marschbefehl? Hier ist ein Kampf im Gange!",
	L"Sie sind in Sektor %s von Bloodcats umstellt!",
	L"Sie haben gerade eine Bloodcat-H�hle betreten in Sektor I16!", 
	L"", 
	L"Die SAM-Stellung in %s wurde erobert.",
//16-20
	L"Mine in %s wurde erobert. Ihre Tageseinnahmen wurden reduziert auf t�glich %s.",
	L"Gegner hat Sektor %s kampflos erobert.",
	L"Mind. 1 S�ldner konnte zu dieser Aufgabe nicht zugeteilt werden.",
	L"%s konnte sich nicht anschlie�en, weil %s voll ist", 
	L"%s konnte sich %s nicht anschlie�en, weil er zu weit entfernt ist.", 
//21-25
	L"Die Mine in %s wurde von gegnerischen Truppen erobert!",
	L"Gegnerische Truppen sind gerade in die SAM-Stellung in %s eingedrungen",
	L"Gegnerische Truppen sind gerade in %s eingedrungen",
	L"Gegnerische Truppen wurden gerade in %s gesichtet.",
	L"Gegnerische Truppen haben gerade %s erobert.",
//26-30
	L"Mindestens ein S�ldner ist nicht m�de.",
	L"Mindestens ein S�ldner konnte nicht geweckt werden.",
	L"Die Miliz erscheint erst, wenn ihr Training beendet ist.",
	L"%s kann derzeit kein Marschbefehl erteilt werden.",
	L"Milizen au�erhalb der Stadtgrenzen k�nnen nicht in andere Sektoren verlegt werden.",
//31-35
	L"Sie k�nnen in %s keine Miliz haben.",
	L"Leere Fahrzeuge k�nnen nicht aufbrechen!",
	L"%s ist nicht transportf�hig!",
	L"Sie m�ssen zuerst das Museum verlassen!",
	L"%s ist tot!",
//36-40
	L"%s kann w�hrend der Bewegung nicht zu %s wechseln", 
	L"%s kann auf diese Weise nicht einsteigen",
	L"%s kann sich %s nicht anschlie�en", 
	L"Zeitraffer erst benutzbar, wenn neue S�ldner angeheuert!",
	L"Dieses Fahrzeug kann nur auf Stra�en fahren!",
//41-45
	L"S�ldnern, die unterwegs sind, k�nnen Sie keine Auftr�ge erteilen.",
	L"Fahrzeug hat keinen Sprit mehr!",
	L"%s ist zu m�de zum reisen.",
	L"Niemand da, der das Fahrzeug steuern kann.",
	L"Einer oder mehrere S�ldner dieses Trupps k�nnen sich derzeit nicht bewegen.",
//46-50
	L"Einer/mehrere S�ldner des ANDEREN Trupps k�nnen sich derzeit nicht bewegen.",
	L"Fahrzeug ist zu stark besch�digt!",
	L"Nur zwei S�ldner pro Sektor k�nnen Milizen trainieren.",
	L"Roboter mu� bedient werden. Platzieren Sie beide im selben Trupp.",
};


// help text used during strategic route plotting
STR16 pMapPlotStrings[] =
{
	L"Klicken Sie nochmal auf das Ziel, um Route zu best�tigen. Klicken Sie auf andere Sektoren, um Route zu �ndern.",
	L"Reiseroute best�tigt.",
	L"Reiseziel unver�ndert.",
	L"Reiseroute verworfen.",
	L"Reiseroute gek�rzt.",
};


// help text used when moving the merc arrival sector
STR16 pBullseyeStrings[] =
{
	L"Klicken Sie auf den Sektor, in dem die S�ldner stattdessen ankommen sollen.",
	L"OK. S�ldner werden jetzt in %s abgesetzt",
	L"S�ldner k�nnen dorthin nicht fliegen; Luftraum unsicher!",
	L"Abbruch. Ankunftssektor unver�ndert,",
	L"Luftraum �ber %s ist nicht mehr sicher! Ankunftssektor jetzt %s.",
};


// help text for mouse regions

STR16 pMiscMapScreenMouseRegionHelpText[] =
{
	L"Ins Inventar gehen (|E|n|t|e|r)",
	L"Gegenstand wegwerfen",
	L"Inventar verlassen (|E|n|t|e|r)",
};



// male version of where equipment is left
STR16 pMercHeLeaveString[] =
{
	L"Soll %s seine Ausr�stung hier in (%s) lassen, oder sp�ter in Drassen (B13), wenn er Arulco verl�sst?",
	L"Soll %s seine Ausr�stung hier in (%s) lassen, oder sp�ter in Omerta (A9), wenn er Arulco verl�sst?",
	L"reist bald ab und l�sst seine Ausr�stung in Omerta (A9).",
	L"reist bald ab und l�sst seine Ausr�stung in Drassen (B13).",
	L"%s reist bald ab und l�sst seine Ausr�stung in %s.",
};


// female version
STR16 pMercSheLeaveString[] =
{
	L"Soll %s ihre Ausr�stung hier in (%s) lassen, oder sp�ter in Drassen (B13), wenn sie Arulco verl�sst?",
	L"Soll %s ihre Ausr�stung hier in (%s) lassen, oder sp�ter in Omerta (A9), wenn sie Arulco verl�sst?",
	L"reist bald ab und l�sst ihre Ausr�stung in Omerta (A9).",
	L"reist bald ab und l�sst ihre Ausr�stung in Drassen (B13).",
	L"%s reist bald ab und l�sst ihre Ausr�stung in %s.",
};


STR16 pMercContractOverStrings[] =
{
	L"s Vertrag lief ab, und er ist nach Hause abgereist.", 		// merc's contract is over and has departed
	L"s Vertrag lief ab, und sie ist nach Hause abgereist.", 		// merc's contract is over and has departed
	L"s Vertrag wurde gek�ndigt, und er ist gegangen.", 		// merc's contract has been terminated
	L"s Vertrag wurde gek�ndigt, und sie ist gegangen.",		// merc's contract has been terminated
	L"Sie schulden M.E.R.C. zuviel, also ist %s gegangen.", // Your M.E.R.C. account is invalid so merc left
};

// Text used on IMP Web Pages

STR16 pImpPopUpStrings[] =
{
	L"Ung�ltiger Autorisierungs-Code",
	L"Sie starten gerade den gesamten Profilierungsprozess von vorn. Sind Sie sicher?",
	L"Bitte geben Sie ihren vollen Namen und Ihr Geschlecht an",
	L"Die �berpr�fung Ihrer Finanzen hat ergeben, da� Sie sich keine Profilanalyse leisten k�nnen.",
	L"Option zur Zeit nicht verf�gbar.",
	L"Um eine genaue Profilierung durchzuf�hren, m�ssen Sie Platz f�r mindestens noch ein Teammitglied haben.",
	L"Profilanalyse bereits durchgef�hrt.",
};


// button labels used on the IMP site

STR16 pImpButtonText[] =
{
	L"Wir �ber uns", 			// about the IMP site
	L"BEGINNEN", 			// begin profiling
//	L"Pers�nlichkeit", 		// personality section
	L"Spezialit�ten",	//JA25 New:
	L"Eigenschaften", 		// personal stats/attributes section
	L"Portr�t", 			// the personal portrait selection
	L"Stimme %d", 			// the voice selection
	L"Fertig", 			// done profiling
	L"Noch mal von vorne",	 		// start over profiling
	L"Ja, ich w�hle die markierte Antwort!", 
	L"Ja", 
	L"Nein",
	L"Fertig", 			// finished answering questions
	L"Zur�ck", 			// previous question..abbreviated form
	L"Weiter", 			// next question
	L"JA, BIN ICH",		 		// yes, I am certain 
	L"NEIN, ICH M�CHTE VON VORNE ANFANGEN.", // no, I want to start over the profiling process
	L"JA",
	L"NEIN",
	L"Zur�ck", 			// back one page
	L"Abbruch", 			// cancel selection
	L"Ja, ich bin sicher.",
	L"Nein, ich m�chte es mir nochmal ansehen.",
	L"Registrieren", 			// the IMP site registry..when name and gender is selected
	L"Analysiere...",	// analyzing your profile results
	L"OK",
	L"Stimme",
};

STR16 pExtraIMPStrings[] =
{
/*
Old
	L"Um mit der Profilierung zu beginnen, Pers�nlichkeit ausw�hlen.", //Ja25 New:
	L"Nun, da Sie mit der Pers�nlichkeit fertig sind, w�hlen Sie Ihre Eigenschaften aus.",
	L"Nach Auswahl der Eigenschaften k�nnen Sie nun mit der Portr�tauswahl fortfahren.",
	L"W�hlen Sie zuletzt die Stimme aus, die Ihnen am besten gef�llt.",

*/
	L"Um mit der Profilierung zu beginnen, w�hlen Sie ein Portrait aus.", 
	L"Nun, da Sie ein Gesicht und einen Namen gew�hlt haben, suchen Sie eine Stimme aus.",
	L"Nach Auswahl der Stimme, k�nnen Sie nun mit der Spezialit�t fortfahren.",
	L"W�hlen Sie zuletzt die Attribute aus, die Ihren S�ldner am besten wiederspiegeln.",
};

STR16 pFilesTitle[] =
{
  L"File Viewer",
};

STR16 pFilesSenderList[] =
{
	L"Aufkl�rungsbericht", 		// the recon report sent to the player. Recon is an abbreviation for reconissance
	L"Intercept #1", 		// first intercept file .. Intercept is the title of the organization sending the file...similar in function to INTERPOL/CIA/KGB..refer to fist record in files.txt for the translated title
	L"Intercept #2",		// second intercept file
	L"Intercept #3",		// third intercept file
	L"Intercept #4",		// fourth intercept file
	L"Intercept #5",		// fifth intercept file
	L"Intercept #6",		// sixth intercept file
};

// Text having to do with the History Log

STR16 pHistoryTitle[] =
{
	L"Logbuch",
};

STR16 pHistoryHeaders[] =
{
	L"Tag",	 			// the day the history event occurred
	L"Seite", 			// the current page in the history report we are in
	L"Tag", 			// the days the history report occurs over
	L"Ort",	 			// location (in sector) the event occurred
	L"Ereignis", 			// the event label
};

// various history events
// THESE STRINGS ARE "HISTORY LOG" STRINGS AND THEIR LENGTH IS VERY LIMITED.
// PLEASE BE MINDFUL OF THE LENGTH OF THESE STRINGS. ONE WAY TO "TEST" THIS
// IS TO TURN "CHEAT MODE" ON AND USE CONTROL-R IN THE TACTICAL SCREEN, THEN
// GO INTO THE LAPTOP/HISTORY LOG AND CHECK OUT THE STRINGS. CONTROL-R INSERTS
// MANY (NOT ALL) OF THE STRINGS IN THE FOLLOWING LIST INTO THE GAME.
STR16 pHistoryStrings[] =
{
	L"",																						// leave this line blank
	//1-5
	L"%s von A.I.M angeheuert.", 										// merc was hired from the aim site
	L"%s von M.E.R.C. angeheuert.", 									// merc was hired from the aim site
	L"%s ist tot.", 															// merc was killed
	L"Rechnung an M.E.R.C. bezahlt",								// paid outstanding bills at MERC
	L"Enrico Chivaldoris Auftrag akzeptiert",	
	//6-10
	L"BSE-Profil erstellt",
	L"Versicherung abgeschlossen f�r %s.", 				// insurance contract purchased
	L"Versicherung gek�ndigt f�r %s.", 				// insurance contract canceled
	L"Versicherung ausgezahlt f�r %s.", 							// insurance claim payout for merc
	L"%ss Vertrag um 1 Tag verl�ngert.", 						// Extented "mercs name"'s for a day
	//11-15
	L"%ss Vertrag um 1 Woche verl�ngert.", 					// Extented "mercs name"'s for a week
	L"%ss Vertrag um 2 Wochen verl�ngert.", 					// Extented "mercs name"'s 2 weeks
	L"%s wurde entlassen.", 													// "merc's name" was dismissed.
	L"%s geht.", 																		// "merc's name" quit.
	L"Mission begonnen.", 															// a particular quest started
	//16-20
	L"Mission gel�st.",
	L"Mit Vorarbeiter in %s geredet",									// talked to head miner of town
	L"Befreiung von %s",
	L"Cheat benutzt",
	L"Nahrung sollte morgen in Omerta sein",
	//21-25
	L"%s verl�sst Team um Daryl Hick zu heiraten",
	L"%ss Vertrag abgelaufen.",
	L"%s rekrutiert.",
	L"Enrico bekalgt mangelnde Fortschritte",
	L"Kampf gewonnen",
	//26-30
	L"Mine in %s beginnt sich zu ersch�pfen",
	L"Mine in %s ist ersch�pft",
	L"Mine in %s wurde geschlossen",
	L"Mine in %s ist wieder offen",
	L"Etwas �ber Gef�ngnis in Tixa erfahren.",
	//31-35
	L"Etwas �ber Waffenfabrik in Orta geh�rt.",
	L"Forscher in Orta gab uns etliche Raketengewehre.", 
	L"Deidranna hat Verwendung f�r Leichen.",
	L"Frank berichtete von K�mpfen in San Mona.",
	L"Ein Patient denkt, er sah etwas in den Minen.",
	//36-40
	L"Devin getroffen - er verkauft Sprengstoff",
	L"Ber�hmten Ex-AIM-S�ldner Mike getroffen!",
	L"Tony getroffen - er verkauft Waffen.",
	L"Bekam ein Raketengewehr von Sgt. Krott.",
	L"Gab Kyle die Urkunde f�r Angels Laden.",
	//41-45
	L"Madlab bot an, Roboter zu bauen.",
	L"Gabby kann Tarn-Mittel f�r K�fer machen.",
	L"Keith ist aus dem Rennen.",
	L"Howard lieferte Zyanid an Deidranna.",
	L"Keith ist jetzt H�ndler f�r alles in Cambria.",
	//46-50
	L"Traf Howard, ist jetzt Apotheker in Balime",
	L"Traf Perko, hat jetzt kleine Werkstatt.",
	L"Traf Sam aus Balime, hat Computerladen.",
	L"Franz macht in Elektronik und anderem.",
	L"Arnold hat eine Werkstatt in Grumm.",
	//51-55
	L"Fredo repariert Elektronik in Grumm.",
	L"Spende von Reichem aus Balime erhalten.",
	L"Hab Schrotth�ndler namens Jake getroffen.",
	L"Ein Idiot gab uns eine Codekarte.",
	L"Hab Walter bestochen, damit er Keller �ffnet.",
	//56-60
	L"Wenn Dave Sprit hat, kriegen wir ihn gratis.",
	L"Hab Pablo bestochen.",
	L"Kingpin hortet Geld in San Mona-Mine.",
	L"%s gewinnt Extremkampf",
	L"%s verliert Extremkampf",
	//61-65
	L"%s beim Extremkampf disqualifiziert",
	L"Fand ne Menge Geld in verlassener Mine.",
	L"Begegnete von Kingpin geheuertem M�rder", 
	L"Kontrolle �ber Sektor verloren",				
	L"Sektor verteidigt",		
	//66-70
	L"Kampf verloren",							//ENEMY_ENCOUNTER_CODE
	L"Fataler Hinterhalt",						//ENEMY_AMBUSH_CODE
	L"Hinterhalt getrotzt",
	L"Angriff fehlgeschlagen",			//ENTERING_ENEMY_SECTOR_CODE
	L"Angriff erfolgreich",
	//71-75
	L"Monster angegriffen",			//CREATURE_ATTACK_CODE
	L"Von Bloodcats get�tet",			//BLOODCAT_AMBUSH_CODE
	L"Bloodcats get�tet",
	L"%s wurde get�tet",	
	L"Gab Carmen den Kopf eines Terroristen",
	L"Slay ist gegangen", //Slay is a merc and has left the team
	L"%s get�tet",		//History log for when a merc kills an NPC or PC
};

STR16 pHistoryLocations[] =
{
	L"n.v.",						// N/A is an acronym for Not Applicable
};

// icon text strings that appear on the laptop

STR16 pLaptopIcons[] =
{
	L"eMail",
	L"Web",
	L"Finanzen",
	L"Personal",
	L"Logbuch",	
	L"Dateien",
	L"Schlie�en",
	L"sir-FER 4.0",			// our play on the company name (Sirtech) and web surFER
};

// bookmarks for different websites
// IMPORTANT make sure you move down the Cancel string as bookmarks are being added

STR16 pBookMarkStrings[] =
{
	L"A.I.M.",
	L"Bobby Ray's",
	L"B.S.E.",
	L"M.E.R.C.",
	L"Bestattungsinst.",	
	L"Florist",
	L"Versicherung",
	L"Abbruch",
};

STR16 pBookmarkTitle[] =
{
	L"Lesezeichen",
	L"Rechts klicken, um k�nftig in dieses Men� zu gelangen.",
};

// When loading or download a web page

STR16 pDownloadString[] =
{
	L"Download l�uft",
	L"Neuladen l�uft",
};

//This is the text used on the bank machines, here called ATMs for Automatic Teller Machine

STR16 gsAtmSideButtonText[] =
{
	L"OK",
	L"Nehmen", 			// take money from merc
	L"Geben", 			// give money to merc
	L"Abbruch", 			// cancel transaction
	L"L�schen", 			// clear amount being displayed on the screen
};

STR16 gsAtmStartButtonText[] =
{
	L"�berw. $", 		// transfer money to merc -- short form
	L"Statistik", 			// view stats of the merc
	L"Inventar", 			// view the inventory of the merc
	L"Anstellung",
};

STR16 sATMText[ ]=
{
	L"Geld �berws.?", 		// transfer funds to merc?
	L"Ok?", 			// are we certain?
	L"Betrag eingeben", 		// enter the amount you want to transfer to merc
	L"Typ ausw�hlen", 		// select the type of transfer to merc
	L"Nicht genug Geld", 	// not enough money to transfer to merc
	L"Betrag muss durch $10 teilbar sein", // transfer amount must be a multiple of $10
};

// Web error messages. Please use foreign language equivilant for these messages. 
// DNS is the acronym for Domain Name Server
// URL is the acronym for Uniform Resource Locator

STR16 pErrorStrings[] =
{
	L"Fehler",
	L"Server hat keinen DNS-Eintrag.",	
	L"URL-Adresse pr�fen und erneut versuchen.",
	L"OK",
	L"Verbindung zum Host wird oft unterbrochen. Rechnen Sie mit l�ngeren �bertragungszeiten.",
};

STR16 pPersonnelString[] =
{
	L"S�ldner:", 			// mercs we have
};


STR16 pWebTitle[ ]=
{
	L"sir-FER 4.0",		// our name for the version of the browser, play on company name
};


// The titles for the web program title bar, for each page loaded

STR16 pWebPagesTitles[] =
{
	L"A.I.M.",
	L"A.I.M. Mitglieder",
	L"A.I.M. Portrait",		// a mug shot is another name for a portrait
	L"A.I.M. Sortieren",
	L"A.I.M.",
	L"A.I.M. Veteranen",
	L"A.I.M. Politik",
	L"A.I.M. Geschichte",
	L"A.I.M. Links",
	L"M.E.R.C.",
	L"M.E.R.C. Konten",
	L"M.E.R.C. Registrierung",
	L"M.E.R.C. Index",
	L"Bobby Rays",
	L"Bobby Rays - Waffen",
	L"Bobby Rays - Munition",
	L"Bobby Rays - R�stungen",
	L"Bobby Rays - Sonst.",							//misc is an abbreviation for miscellaneous				
	L"Bobby Rays - Gebraucht",
	L"Bobby Rays - Mail Order",
	L"B.S.E.",
	L"B.S.E.",
	L"United Floral Service",
	L"United Floral Service - Sortiment",
	L"United Floral Service - Bestell-Formular",
	L"United Floral Service - Karten Sortiment",
	L"Malleus, Incus & Stapes Versicherungsmakler",
	L"Information",
	L"Vertrag",
	L"Bemerkungen",
	L"McGillicuttys Bestattungen",
	L"",
	L"URL nicht gefunden.",
	L"Bobby Rays - Letzte Lieferungen",
	L"",
	L"",
};

STR16 pShowBookmarkString[] =
{
	L"Sir-Help",
	L"Lesezeichen: Nochmal auf Web klicken.",
};

STR16 pLaptopTitles[] =
{
	L"E-Mail",
	L"Dateien",
	L"Personal",
	L"Buchhalter Plus",
	L"Logbuch",
};

STR16 pPersonnelDepartedStateStrings[] =
{
	//reasons why a merc has left.
	L"Get�tet",
	L"Entlassen",
	L"Sonstiges",
	L"Heirat",
	L"Vertrag zuende",
	L"Ende",
};
// personnel strings appearing in the Personnel Manager on the laptop

STR16 pPersonelTeamStrings[] =
{
	L"Aktuelles Team",
	L"Ausgeschieden",
	L"Tgl. Kosten:",
	L"H�chste Kosten:",
	L"Niedr. Kosten:",
	L"Im Kampf get�tet:",
	L"Entlassen:",
	L"Sonstiges:",
};


STR16 pPersonnelCurrentTeamStatsStrings[] =
{
	L"Niedrig.",
	L"Durchschn.",	
	L"H�chst.",
};


STR16 pPersonnelTeamStatsStrings[] =
{
	L"GSND",
	L"BEW",
	L"GES",
	L"KRF",
	L"FHR",
	L"WSH",
	L"ERF",
	L"TRF",
	L"TEC",
	L"SPR",
	L"MED",
};


// horizontal and vertical indices on the map screen

STR16 pMapVertIndex[] =
{
	L"X",
	L"A",
	L"B",
	L"C",
	L"D",
	L"E",
	L"F",
	L"G",
	L"H",
	L"I",
	L"J",
	L"K",
	L"L",
	L"M",
	L"N",
	L"O",
	L"P",
};

STR16 pMapHortIndex[] =
{
	L"X",
	L"1",
	L"2",
	L"3",
	L"4",
	L"5",
	L"6",
	L"7",
	L"8",
	L"9",
	L"10",
	L"11",
	L"12",
	L"13",
	L"14",
	L"15",
	L"16",
};

STR16 pMapDepthIndex[] =
{
	L"",
	L"-1",
	L"-2",
	L"-3",
};

// text that appears on the contract button

STR16 pContractButtonString[] =
{
	L"Vertrag",
};

// text that appears on the update panel buttons

STR16 pUpdatePanelButtons[] =
{
	L"Weiter",
	L"Stop",
};

// Text which appears when everyone on your team is incapacitated and incapable of battle

UINT16 LargeTacticalStr[][ LARGE_STRING_LENGTH ] =
{
	L"Sie sind in diesem Sektor besiegt worden!",
	L"Der Feind, ohne Erbarmen f�r die Seelen Ihrer Teammitglieder, verschlingt jeden einzelnen.",
	L"Ihre bewu�tlosen Teammitglieder wurden gefangengenommen!",
	L"Ihre Teammitglieder wurden vom Feind gefangengenommen.",
};


//Insurance Contract.c
//The text on the buttons at the bottom of the screen.

STR16			InsContractText[] = 
{ 
	L"Zur�ck",
	L"Vor",
	L"OK",
	L"L�schen",
};



//Insurance Info
// Text on the buttons on the bottom of the screen

STR16		InsInfoText[] = 
{ 
	L"Zur�ck", 
	L"Vor",
};



//For use at the M.E.R.C. web site. Text relating to the player's account with MERC

STR16			MercAccountText[] = 
{
	// Text on the buttons on the bottom of the screen
	L"Autorisiert",
	L"Home",
	L"Konto #:",
	L"S�ldner",
	L"Tage",
	L"Rate",		//5
	L"Belasten",
	L"Gesamt:",
	L"Die Zahlung von %s wirklich genehmigen?",		//the %s is a string that contains the dollar amount ( ex. "$150" )
};



//For use at the M.E.R.C. web site. Text relating a MERC mercenary


STR16			MercInfo[] =
{
	L"Gesundheit",
	L"Beweglichkeit",
	L"Geschicklichkeit",
	L"Kraft",
	L"F�hrungsqualit�t",
	L"Weisheit",
	L"Erfahrungsstufe",
	L"Treffsicherheit",
	L"Technik",
	L"Sprengstoffe",
	L"Medizin",

	L"Zur�ck",
	L"Anheuern",
	L"Weiter",
	L"Zusatzinfo",
	L"Home",
	L"Abwesend",	
	L"Sold:",
	L"Pro Tag",
	L"Verstorben",	

	L"Sie k�nnen nicht mehr als 18 S�ldner zugleich anheuern.",
	L"nicht verf�gbar",											
};


// For use at the M.E.R.C. web site. Text relating to opening an account with MERC

STR16			MercNoAccountText[] =
{
	//Text on the buttons at the bottom of the screen
	L"Konto er�ffnen",
	L"Abbruch",
	L"Sie haben kein Konto. M�chten Sie eins er�ffnen?",
};



// For use at the M.E.R.C. web site. MERC Homepage

STR16			MercHomePageText[] =
{
	//Description of various parts on the MERC page
	L"Speck T. Kline, Gr�nder/Eigent�mer",
	L"Hier klicken, um Konto zu er�ffnen",
	L"Hier klicken, um Konto einzusehen",
	L"Hier klicken, um Dateien einzusehen.",
	// The version number on the video conferencing system that pops up when Speck is talking
	L"Speck Com v3.2", 
};

// For use at MiGillicutty's Web Page.

STR16			sFuneralString[] =
{
	L"McGillicuttys Bestattungen: Seit 1983 helfen wir trauernden Familien.",
	L"Bestattungsunternehmer Murray \"Pops\" McGillicutty, fr�herer A.I.M.-S�ldner, ist ein f�higer wie auch erfahrener Bestatter.",
	L"Pops hat seinen Lebtag mit Todes- und Trauerf�llen verbracht. Er wei� aus erster Hand, wie problematisch das sein kann.",
	L"McGillicuttys Bestattungen bietet Ihnen einen erstklassigen Service, angefangen bei der Schulter zum Ausweinen bis hin zum Wieder-Zusammensetzen deplatzierter K�rperteile.",
	L"McGillicuttys Bestattungen - und Ihre Lieben ruhen in Frieden.",


	// Text for the various links available at the bottom of the page
	L"BLUMEN SENDEN",
	L"S�RGE UND URNEN",
	L"FEUERBE- STATTUNG",	
	L"PLANUNGS- SERVICE", 
	L"PIET�T",	

	// The text that comes up when you click on any of the links ( except for send flowers ).
	L"Leider wurde diese Website wegen eines Trauerfalles in der Familie noch nicht fertiggestellt. Sobald das Testament er�ffnet wurde und die Erben festgelegt sind, wird sie weiter bearbeitet.",
	L"Unser Mitgef�hl gilt trotzdem all jenen, die es uns zu kontaktieren versuchten. Schauen Sie wieder vorbei.",
};

// Text for the florist Home page

STR16			sFloristText[] = 
{
	//Text on the button on the bottom of the page

	L"Sortiment",

	//Address of United Florist

	L"\"Wir werfen �berall per Fallschirm ab\"",
	L"1-555-WOHLGERUCH",
	L"333 NoseGay Drive, Aroma City, CA USA 90210",
	L"http://www.wohlgeruch.com",

	// detail of the florist page

	L"Wir sind schnell und effizient",
	L"Lieferung am n�chsten Tag - mit einigen Ausnahmen in fast jedes Land der Welt.",
	L"Weltweit garantiert die niedrigsten Preise!",
	L"Zeigen Sie uns anderswo einen geringeren Preis, und Sie bekommen von uns ein Dutzend Rosen umsonst!",
	L"Fliegende Flora & Blumen seit 1981.",
	L"Unsere ausgezeichneten Ex-Bomber-Piloten werfen das Bouquet jederzeit in einem Zehn-Meilen-Radius um den Bestimmungsort ab!",
	L"Wir verwirklichen Ihre blumigsten Fantasien.",
	L"Unser weltber�hmter Designer-Florist Bruce verwendet nur die frischesten handverlesenen Blumen aus unserem eigenen Gew�chshaus.",
	L"Und denken Sie daran: Was wir nicht haben, z�chten wir f�r Sie - in Rekordzeit!",
};



//Florist OrderForm

STR16			sOrderFormText[] = 
{
	//Text on the buttons

	L"Zur�ck",
	L"Senden",
	L"L�schen",
	L"Sortiment",

	L"Name des Bouquets:",
	L"Preis:",			//5
	L"Bestellnr.:",
	L"Liefertermin",
	L"Morgen",
	L"Ist da, wenn es da ist",
	L"Bestimmungsort",			//10
	L"Extraservice",
	L"Matschgesteck($10)",
	L"Schwarze Rosen($20)",
	L"Welkes Gesteck($10)",
	L"Obsttorte ($10)",		//15
	L"Kondolenz-Gru�:",
	L"Wegen der Kartengr��e darf Ihr Gru� nicht l�nger als 75 Zeichen sein.",
	L"...oder w�hlen Sie eine unserer",

	L"STANDARD-KARTEN",	
	L"Zahlungs-Modalit�ten",//20

	//The text that goes beside the area where the user can enter their name

	L"Name:",
};




//Florist Gallery.c

STR16		sFloristGalleryText[] =
{
	//text on the buttons

	L"Zur�ck",	//abbreviation for previous
	L"Weiter",	//abbreviation for next

	L"Klicken Sie auf das Bouquet Ihrer Wahl",
	L"Beachten Sie, da� wir f�r zermatschte oder welke Bouquets einen Aufpreis von $10 verlangen.",

	//text on the button

	L"Home",
};

//Florist Cards

STR16			sFloristCards[] =
{
	L"Klicken Sie auf Ihre Auswahl",
	L"Zur�ck",
};


// Text for Bobby Ray's Mail Order Site

STR16			BobbyROrderFormText[] = 
{
	L"Bestellformular",				//Title of the page
	L"Stck",					// The number of items ordered
	L"Gew. (%s)",			// The weight of the item
	L"Artikel",				// The name of the item
	L"Einzelpreis",				// the item's weight
	L"Summe",				//5	// The total price of all of items of the same type
	L"Zwischensumme",				// The sub total of all the item totals added
	L"Fracht (siehe Best.Ort)",		// S&H is an acronym for Shipping and Handling 
	L"Endbetrag",			// The grand total of all item totals + the shipping and handling
	L"Bestimmungsort",				
	L"Lieferzeit",			//10	// See below
	L"$ (pro %s)",			// The cost to ship the items
	L"�bernacht Express",			// Gets deliverd the next day
	L"2 Arbeitstage",			// Gets delivered in 2 days
	L"Standard",			// Gets delivered in 3 days
	L"Form l�schen",//15			// Clears the order page
	L"Bestellen",			// Accept the order
	L"Zur�ck",				// text on the button that returns to the previous page
	L"Home",				// Text on the button that returns to the home page
	L"* Gebr. Gegenst�nde anzeigen",		// Disclaimer stating that the item is used
	L"Sie haben nicht genug Geld.",		//20	// A popup message that to warn of not enough money
	L"<KEIN>",				// Gets displayed when there is no valid city selected
	L"Bestellung nach %s schicken? Sicher?",		// A popup that asks if the city selected is the correct one
	L"Verpack.-Gew.**",			// Displays the weight of the package
	L"** Min.-Gew.",				// Disclaimer states that there is a minimum weight for the package
	L"Lieferungen",	
};


// This text is used when on the various Bobby Ray Web site pages that sell items

STR16			BobbyRText[] = 
{
	L"Bestellen",				// Title
	// instructions on how to order
	L"Auf gew�nschten Gegenstand klicken. Linke Maustaste erh�ht, rechte vermindert St�ckzahl. Wenn Sie fertig sind, weiter mit dem Bestellformular.",			// instructions on how to order

	//Text on the buttons to go the various links

	L"Zur�ck",		// 
	L"Waffen", 			//3
	L"Munition",			//4
	L"R�stung",			//5
	L"Sonstiges",			//6	//misc is an abbreviation for miscellaneous
	L"2. Hand",			//7
	L"Mehr...",
	L"BESTELLEN",
	L"Home",			//10

	//The following 2 lines are used on the Ammunition page.  
	//They are used for help text to display how many items the player's merc has
	//that can use this type of ammo

	L"Ihr Team hat",//11
	L"Waffe(n), die dieses Kaliber benutzen", //12

	//The following lines provide information on the items

	L"Gew.:",			// Weight of all the items of the same type
	L"Kalib.:",			// the caliber of the gun
	L"Magaz.:",			// number of rounds of ammo the Magazine can hold
	L"Reichw.",				// The range of the gun
	L"Schaden",				// Damage of the weapon	
	L"Freq.:",			// Weapon's Rate Of Fire, acroymn ROF
	L"Preis:",			// Cost of the item
	L"Vorr�tig:",			// The number of items still in the store's inventory
	L"Bestellt:",		// The number of items on order
	L"Besch�digt",			// If the item is damaged
	L"Gew.:",			// the Weight of the item
	L"Zw.-Sum:",			// The total cost of all items on order
	L"* %% funktional",		// if the item is damaged, displays the percent function of the item

	//Popup that tells the player that they can only order 10 items at a time
	
	L"Pech!  Mit diesem Formular k�nnen Sie nur 10 Gegenst�nde bestellen. Falls Sie mehr wollen (wollen wir doch hoffen), f�llen Sie bitte noch ein Formular aus.",

	// A popup that tells the user that they are trying to order more items then the store has in stock

	L"Tut uns leid. Davon haben wir leider nichts mehr auf Lager. Versuchen Sie es sp�ter wieder.",

	//A popup that tells the user that the store is temporarily sold out

	L"Verzeihung, derzeit sind diese Sachen vollst�ndig ausverkauft.",

};


// Text for Bobby Ray's Home Page

STR16			BobbyRaysFrontText[] =
{
	//Details on the web site

	L"Dies ist die beste Site f�r Waffen und milit�risches Equipment jeder Art",
	L"Wir finden stets den richtigen Sprechstoff - f�r das Loch, das haben wollen.",
	L"Equipment aus 2. Hand",

	//Text for the various links to the sub pages

	L"Verschiedenes",
	L"FEUERWAFFEN",
	L"MUNITION",		//5
	L"R�STUNG",

	//Details on the web site

	L"Was WIR nicht haben - hat auch kein anderer!",
	L"In Arbeit...",
};


// Text for the AIM page.
// This is the text used when the user selects the way to sort the aim mercanaries on the AIM mug shot page

STR16			AimSortText[] =
{
	L"A.I.M. Mitglieder",				// Title
	// Title for the way to sort
	L"Sort. nach:",					// Title for the way to sort

	// sort by...

	L"Honorar",											
	L"Erfahrung",
	L"Treffsicherheit",
	L"Medizin",
	L"Sprengstoff",
	L"Technik",

	//Text of the links to other AIM pages

	L"S�ldner-Kurzverzeichnis ansehen",
	L"Personalakten der S�ldner ansehen",
	L"Die A.I.M.-Veteranengalerie ansehen",

	// text to display how the entries will be sorted

	L"Aufsteigend",
	L"Absteigend",
};


//Aim Policies.c
//The page in which the AIM policies and regulations are displayed

STR16		AimPolicyText[] =
{
	// The text on the buttons at the bottom of the page

	L"Zur�ck",
	L"AIM HomePage", 
	L"Regel-Index",
	L"N�chste Seite",
	L"Ablehnen",	
	L"Zustimmen",
};


//Aim Member.c
//The page in which the players hires AIM mercenaries

// Instructions to the user to either start video conferencing with the merc, or to go the mug shot index

STR16			AimMemberText[] =
{
	L"Linksklick",
	L"zum Kontaktieren.",
	L"Rechtsklick",
	L"zum Foto-Index.",
};					

//Aim Member.c
//The page in which the players hires AIM mercenaries

STR16			CharacterInfo[] =
{
	// The various attributes of the merc

	L"Gesundh.",										
	L"Beweglichkeit",										
	L"Geschicklichkeit",									
	L"Kraft",
	L"F�hrungsqualit�t",
	L"Weisheit",
	L"Erfahrungsstufe",
	L"Treffsicherheit",
	L"Technik",
	L"Sprengstoff",
	L"Medizin",				//10

	// the contract expenses' area

//JA25	L"Fee",							dont need anymore
	L"Missions-Honorar",							
	L"Vertrag",				
	L"Einmalig. Honor.",					
	L"Eine Woche",
	L"Zwei Wochen",

	// text for the buttons that either go to the previous merc, 
	// start talking to the merc, or go to the next merc

	L"Zur�ck",
	L"Kontakt",
	L"Weiter",

	L"Zusatzinfo",				// Title for the additional info for the merc's bio
	L"Aktive Mitglieder",		//20		// Title of the page
//Ja25:	L"Optionale Ausr�st:",				// Displays the optional gear cost
	L"Derzeit inbegriffene Ausr�stung:",	//Ja25: new
	L"VERSICHERUNG erforderlich",			// If the merc required a medical deposit, this is displayed
};


//Aim Member.c
//The page in which the player's hires AIM mercenaries

//The following text is used with the video conference popup

STR16			VideoConfercingText[] =
{
	L"Vertragskosten:",				//Title beside the cost of hiring the merc

	//Text on the buttons to select the length of time the merc can be hired

	L"1x-Honorar",	//Ja25 modified									
	L"1 Woche",
	L"2 Wochen",

	//Text on the buttons to determine if you want the merc to come with the equipment 

	L"Ohne Ausr�stung",
	L"Ausr�stung kaufen",

	// Text on the Buttons

	L"GELD �BERWEISEN",			// to actually hire the merc
	L"ABBRUCH",				// go back to the previous menu
	L"ENGAGIEREN",				// go to menu in which you can hire the merc
	L"AUFLEGEN",				// stops talking with the merc
	L"OK",									
	L"NACHRICHT",			// if the merc is not there, you can leave a message 

	//Text on the top of the video conference popup

	L"Videokonferenz mit",		
	L"Verbinde. . .",

	L"versichert",			// Displays if you are hiring the merc with the medical deposit
};



//Aim Member.c
//The page in which the player hires AIM mercenaries

// The text that pops up when you select the TRANSFER FUNDS button

STR16			AimPopUpText[] =
{
	L"ELEKTRONISCHE �BERWEISUNG AUSGEF�HRT",	// You hired the merc
	L"�BERWEISUNG KANN NICHT AUSGEF�HRT WERDEN",		// Player doesn't have enough money, message 1
	L"NICHT GENUG GELD",				// Player doesn't have enough money, message 2

	// if the merc is not available, one of the following is displayed over the merc's face

	L"Im Einsatz",											
	L"Bitte Nachricht hinterlassen",
	L"Verstorben",

	//If you try to hire more mercs than game can support

	L"Sie haben schon 18 S�ldner in Ihrem Team.",

	L"Mailbox",
	L"Nachricht aufgezeichnet",
};


//AIM Link.c

STR16			AimLinkText[] =
{
	L"A.I.M. Links",	//The title of the AIM links page
};



//Aim History

// This page displays the history of AIM

STR16			AimHistoryText[] =
{
	L"Die Geschichte von A.I.M.",					//Title

	// Text on the buttons at the bottom of the page

	L"Zur�ck",
	L"Home", 
	L"Veteranen",
	L"Weiter",
};


//Aim Mug Shot Index

//The page in which all the AIM members' portraits are displayed in the order selected by the AIM sort page.

STR16			AimFiText[] =
{
	// displays the way in which the mercs were sorted

	L"Honorar",
	L"Erfahrung",
	L"Treffsicherheit",
	L"Medizin",
	L"Sprengstoff",
	L"Technik",

	// The title of the page, the above text gets added at the end of this text

	L"A.I.M.-Mitglieder aufsteigend sortiert nach %s",
	L"A.I.M. Mitglieder absteigend sortiert nach %s",

	// Instructions to the players on what to do

	L"Linke Maustaste",
	L"um S�ldner zu w�hlen",			//10
	L"Rechte Maustaste",
	L"um Optionen zu w�hlen",

	// Gets displayed on top of the merc's portrait if they are...

	L"Abwesend",
	L"Verstorben",						//14
	L"Im Dienst",
};


//AimArchives.
// The page that displays information about the older AIM alumni merc... mercs who are no longer with AIM

STR16			AimAlumniText[] =
{
	// Text of the buttons

	L"SEITE 1",
	L"SEITE 2",
	L"SEITE 3",

	L"A.I.M.-Veteranen",	// Title of the page

	L"OK",		// Stops displaying information on selected merc
};

//AIM Home Page

STR16			AimScreenText[] =
{
	// AIM disclaimers
	
	L"A.I.M. und das A.I.M.-Logo sind als Warenzeichen in den meisten L�ndern eingetragen.",
	L"Also denken Sie lieber nicht mal daran, uns zu kopieren.",
	L"Copyright 2000 A.I.M., Ltd. Alle Rechte vorbehalten.", 	//Ja25 modified to 2000

	//Text for an advertisement that gets displayed on the AIM page

	L"United Floral Service",
	L"\"Wir werfen �berall per Fallschirm ab\"",				//10
	L"Treffen Sie GLEICH... ",
	L"... die richtige Wahl!",
	L"Waffen und Ausr�stung - was wir nicht haben, brauchen Sie auch nicht.",
};


//Aim Home Page

STR16			AimBottomMenuText[] =
{
	//Text for the links at the bottom of all AIM pages
	L"Home",
	L"Mitglieder",
	L"Veteranen",
	L"Regeln",
	L"Geschichte",
	L"Links",
};



//ShopKeeper Interface
// The shopkeeper interface is displayed when the merc wants to interact with 
// the various store clerks scattered through out the game.

STR16 SKI_Text[ ] = 
{
	L"VORR�TIGE WAREN",	//Header for the merchandise available
	L"SEITE",						//The current store inventory page being displayed
	L"KOSTEN",	//The total cost of the the items in the Dealer inventory area
	L"WERT",		//The total value of items player wishes to sell
	L"SCH�TZUNG",				//Button text for dealer to evaluate items the player wants to sell
	L"EINVERSTANDEN",			//Button text which completes the deal. Makes the transaction.
	L"FERTIG",						//Text for the button which will leave the shopkeeper interface.
	L"REP.KOSTEN",		//The amount the dealer will charge to repair the merc's goods
	L"1 STUNDE",			// SINGULAR! The text underneath the inventory slot when an item is given to the dealer to be repaired
	L"%d STUNDEN",		// PLURAL! The text underneath the inventory slot when an item is given to the dealer to be repaired
	L"REPARIERT",		// Text appearing over an item that has just been repaired by a NPC repairman dealer
	L"Kein Platz mehr in Ihrem Angeb.-Bereich.",	//Message box that tells the user there is no more room to put there stuff
	L"%d MINUTEN",		// The text underneath the inventory slot when an item is given to the dealer to be repaired
	L"Gegenstand fallenlassen.",
};

//ShopKeeper Interface
//for the bank machine panels. Referenced here is the acronym ATM, which means Automatic Teller Machine

STR16	SkiAtmText[] =
{
	//Text on buttons on the banking machine, displayed at the bottom of the page
	L"0",
	L"1",
	L"2",
	L"3",
	L"4",
	L"5",
	L"6",
	L"7",
	L"8",
	L"9",
	L"OK",						// Transfer the money
	L"Nehmen",					// Take money from the player
	L"Geben",					// Give money to the player
	L"Abbruch",					// Cancel the transfer
	L"L�schen",					// Clear the money display
};


//Shopkeeper Interface
STR16	gzSkiAtmText[] = 
{	

	// Text on the bank machine panel that....
	L"Typ w�hlen",			// tells the user to select either to give or take from the merc
	L"Betrag eingeben",			// Enter the amount to transfer
	L"Geld an S�ldner �berweisen",		// Giving money to the merc
	L"Geld von S�ldner �berweisen",		// Taking money from the merc
	L"Nicht genug Geld",			// Not enough money to transfer
	L"Kontostand",				// Display the amount of money the player currently has
};


STR16	SkiMessageBoxText[] =
{
	L"Wollen Sie %s von Ihrem Konto abbuchen, um die Differenz auszugleichen?",
	L"Nicht gen�gend Geld. Es fehlen Ihnen %s",
	L"Wollen Sie %s von Ihrem Konto abbuchen, um die Kosten abzudecken?",
	L"Den H�ndler bitten, die �berweisung zu t�tigen.",
	L"Den H�ndler um Reparatur der Gegenst�nde bitten",
	L"Gespr�ch beenden",
	L"Kontostand",
};


//OptionScreen.c

STR16	zOptionsText[] = 
{
	//button Text
	L"Spiel speichern",
	L"Spiel laden",
	L"Spiel beenden",	
	L"Fertig",

	//Text above the slider bars
	L"Effekte",
	L"Sprache",
	L"Musik",

	//Confirmation pop when the user selects..
	L"Spiel verlassen und zur�ck zum Hauptmen�?",

	L"Es muss entweder Sprache oder Untertitel aktiviert sein.",
};


//SaveLoadScreen 
STR16			zSaveLoadText[] = 
{
	L"Spiel speichern",
	L"Spiel laden",
	L"Abbruch",
	L"Auswahl speichern",
	L"Auswahl laden",

	L"Spiel erfolgreich gespeichert",
	L"FEHLER beim Speichern!",
	L"Spiel erfolgreich geladen",
	L"FEHLER beim Laden!",

	L"Die Spiel-Version des gespeicherten Spielstands unterscheidet sich von der aktuellen Spiel-Version.  Wahrscheinlich wird nichts passieren. Fortfahren?",
	L"Die gespeicherten Spielst�nde k�nnten besch�digt sein.  Wollen Sie alle l�schen?", 

	//Translators, the next two strings are for the same thing.  The first one is for beta version releases and the second one
	//is used for the final version.  Please don't modify the "#ifdef JA2BETAVERSION" or the "#else" or the "#endif" as they are
	//used by the compiler and will cause program errors if modified/removed.  It's okay to translate the strings though.
#ifdef JA2BETAVERSION
	L"Gespeicherte Version ist ver�ndert. Bitte melden Sie etwaige Probleme. Weiter?",
#else
	L"Versuche, Spielstand einer �lteren Version zu laden. Automatisch aktualisieren und laden?",
#endif

	//Translators, the next two strings are for the same thing.  The first one is for beta version releases and the second one
	//is used for the final version.  Please don't modify the "#ifdef JA2BETAVERSION" or the "#else" or the "#endif" as they are
	//used by the compiler and will cause program errors if modified/removed.  It's okay to translate the strings though.
#ifdef JA2BETAVERSION
	L"Spielstand- und Spiel-Version wurden ge�ndert. Bitte melden Sie etwaige Probleme. Weiter?",
#else
	L"Versuche, Spielstand einer �lteren Version zu laden. Automatisch aktualisieren und laden?",
#endif
	L"Gespeichertes Spiel in Slot #%d wirklich �berschreiben?",
	L"Wollen Sie das Spiel aus Slot # laden?",

	//The first %d is a number that contains the amount of free space on the users hard drive,
	//the second is the recommended amount of free space.
	L"Zu wenig Festplatten-Speicher. Sie haben nur noch %d MB frei und JA2.5 ben�tigt mindestens %d MB.",

	L"Speichere...",		//When saving a game, a message box with this string appears on the screen
	
	L"Normale Waffen",
	L"Massen an Waffen",
	L"Real-Stil",
	L"SciFi-Stil",

	L"Schwierigkeit",
};



//MapScreen
STR16		zMarksMapScreenText[] =
{
	L"Karten-Level",
	L"Sie haben keine Miliz. Trainieren Sie Bewohner der Stadt, wenn Sie dort eine aufstellen wollen.",
	L"T�gl. Einkommen", 
	L"S�ldner hat Lebensversicherung", 
	L"%s ist nicht m�de.", 
	L"%s ist unterwegs und kann nicht schlafen.", 
	L"%s ist zu m�de. Versuchen Sie es sp�ter nochmal.",
	L"%s f�hrt.", 
	L"Der Trupp kann nicht weiter, wenn einer der S�ldner schl�ft.",

	// stuff for contracts
	L"Den Vertrag k�nnen Sie zwar bezahlen, haben aber nicht genug Geld f�r die Lebensversicherung.", 
	L"%s Pr�men der Lebensversicherung kosten %s pro %d Zusatztag(en). M�chten Sie das zahlen?",
	L"Sektor Inventar", 

	L"S�ldner ist krankenversichert.", 
	
	// other items
	L"Mediziner", // people acting a field medics and bandaging wounded mercs 
	L"Patienten", // people who are being bandaged by a medic 
	L"Fertig", // Continue on with the game after autobandage is complete 
	L"Stop", // Stop autobandaging of patients by medics now 
	L"Leider - diese Option gibt es im Demo nicht.", // informs player this option/button has been disabled in the demo 

	L"%s hat kein Repair-Kit",
	L"%s hat kein Verbandszeug.",
	L"Nicht genug Leute am Training interessiert.",
	L"%s ist voller Miliz.",
	L"S�ldner hat befristeten Vertrag.", 
	L"Vertrag des S�ldners ist nicht versichert",
};


STR16 pLandMarkInSectorString[] =
{
	L"Trupp %d hat jemanden in Sektor %s bemerkt",
};

// confirm the player wants to pay X dollars to build a militia force in town
STR16 pMilitiaConfirmStrings[] =
{
	L"Einen Miliztrupp f�r diese Stadt zu trainieren, kostet $", // telling player how much it will cost
	L"Invenstieren?", // asking player if they wish to pay the amount requested
	L"Sie haben nicht genug Geld.", // telling the player they can't afford to train this town
	L"Die Miliz in %s (%s %d) weitertrainieren?", // continue training this town?
	L"Preis $", // the cost in dollars to train militia
	L"( J/N )", // abbreviated yes/no
	L"",	// unused
	L"Trainig der Stadtmiliz in %d Sektoren kostet $ %d. %s", // cost to train sveral sectors at once
	L"Sie k�nnen sich keine $%d f�r die Stadtmiliz hier leisten.",
	L"%s ben�tigt eine Loyalit�t von %d Prozent, um mit dem Miliz-Training weiterzumachen.",
	L"Sie k�nnen die Miliz in %s nicht mehr weitertrainieren.", 
};

#ifdef JA2DEMOADS
STR16 gpDemoString[] = 
{
	//0-9
	L"DAS BESTE IN SACHEN STRATEGIE.",
	L"DAS BESTE IN SACHEN ROLLENSPIEL.",
	L"Nicht-lineare Spielhandlung",
	L"Komplett neue Story",
	L"Aufregende Feuergefechte",
	L"Dynamisches Lighting",
	L"Interaktion mit NSCs",
	L"Geheim- und Nachtman�ver",
	L"Kreieren Sie eigene S�ldner",
	L"Herausfordernde und kreative Missionen",
	L"Steuerbare Fahrzeuge",
	//10-19
	L"Mehr als 150 Charaktere",
	L"Hunderte von coolen Gegenst�nden",
	L"Mehr als 250 einzigartige Locations",
	L"Umwerfende Explosionen",
	L"Neue taktische Man�ver",
	L"Tonnenweise Animationen",
	L"Mehr als 9000 Zeilen an Dialogen",
	L"Tolle Musikst�cke von Kevin Manthei",
	L"Globale Strategie",
	L"K�mpfe w�hrend Luftangriffen",
	//20-29
	L"Bilden Sie eigene Milizen aus",
	L"Individuelles Gameplay",
	L"Realistische Schusslinien",
	L"Spektakul�re High-color Grafiken",
	L"Kaufen, verkaufen und handeln.",
	L"Gegner mit gef�hrlicher KI",
	L"Modernste Kampftechniken",
	L"Optionales Sci-Fi-Element",
	L"24-Stunden Uhr",
	L"�ber 60 Stunden Spielzeit",
	//30-34
	L"W�hlbare Schwierigkeitsgrade",
	L"Reales Ballistik-Modell",
	L"Physikalisch basierte Engine",
	L"Vollst�ndig interaktives Umfeld",
	L"... und noch vieles mehr...",
	//35 on are BOLD
	L"",
	L"",
	L"\"Eines der besten Spiele im Jahr 1998\"",
	L"PC Gamer",
	L"Bestellen Sie unter WWW.JAGGEDALLIANCE2.COM - noch heute!",
};

STR16 gpDemoIntroString[] = 
{
	L"Sie sind dabei, das Beste in Sachen Strategie und Rollenspiel zu erleben - mit �berw�ltigenden Kampftechniken:",
	//Point 1 (uses one string)
	L"F�hren Sie ein Team von echt durchgeknallten S�ldnern (hier gibt's keine langweiligen Standard-Einheiten).",
	//Point 2 (uses one string)
	L"Testen Sie eine Vielfalt von taktischen Man�vern. Rennen und kriechen Sie, klettern und springen Sie, f�hren Sie Nahk�mpfe und vieles mehr...",
	//Point 3 (uses one string)
	L"Es ist ein Spiel mit dem Feuer! Irres Spielzeug, t�dliche Waffen, unerh�rte Explosionen!",
	//Additional comment
	L"(...und das ist erst der Anfang)",
	//Introduction/instructions
	L"Willkommen in Demoville... (weiter mit beliebiger Taste)",
};
#endif

//Strings used in the popup box when withdrawing, or depositing money from the $ sign at the bottom of the single merc panel
STR16	gzMoneyWithdrawMessageText[] = 
{
	L"Sie k�nnen nicht mehr als 20,000 $ abheben.",
	L"Wollen Sie wirklich %s auf Ihr Konto einzahlen?",
};

STR16	gzCopyrightText[] = 
{
	L"Copyright (C) 2000 Sir-tech Canada Ltd.  Alle Rechte vorbehalten.",		//JA25 modified to 2000
};

//option Text
STR16		zOptionsToggleText[] = 
{
	L"Sprache",
	L"Best�tigungen stummschalten",
	L"Untertitel",
	L"Textdialoge Pause",
	L"Rauch animieren", 
	L"Verletzungen sichtbar",
	L"Maus nicht verschieben!",
	L"Alte Auswahl-Methode",
	L"Bewegungspfad anzeigen",
	L"Fehlsch�sse anzeigen",
	L"Best�tigung bei Echtzeit",
	L"Schlaf-/Wachmeldung anzeigen", 
	L"Metrisches System benutzen",
	L"S�ldner bei Beweg. beleuchten",
	L"Cursor auf S�ldner zentr.",
	L"Cursor auf T�ren zentr.",
	L"Gegenst�nde leuchten",
	L"Baumkronen einblenden",
	L"Drahtgitter einblenden",
	L"3D Cursor zeigen",
};

//This is the help text associated with the above toggles.
STR16	zOptionsScreenHelpText[] =
{
	//speech
	L"Mit dieser Option sind die Dialoge h�rbar.",

	//Mute Confirmation
	L"Schaltet gesprochene Best�tigungen an oder aus.",

		//Subtitles
	L"Schaltet die Untertitel der Dialoge ein oder aus.",

	//Key to advance speech
	L"Sind die Untertitel AN, bekommen Sie durch diese Option Zeit, die Dialoge der NSCs zu lesen.",

	//Toggle smoke animation
	L"Schalten Sie dies aus, wenn animierter Rauch Ihre Bildwiederholrate verlangsamt.",

	//Blood n Gore
	L"Schalten Sie diese Option aus, wenn Sie kein Blut sehen wollen.",

	//Never move my mouse
	L"Wenn Sie dies abschalten, wird der Mauszeiger automatisch �ber OK-Buttons (u.�.) von Pop-Fenstern bewegt.",

	//Old selection method
	L"Schalten Sie dies ein, wenn die Auswahl der S�ldner so wie in fr�heren JAGGED ALLIANCE-Spielen funktionieren soll (andersherum als jetzt).",

	//Show movement path
	L"Schalten Sie dies ein, um Wege der S�ldner in Echtzeit anzuzeigen (mit Hilfe der SHIFT-Taste geht das auch manuell).",

	//show misses
	L"Hiermit bekommen Sie gezeigt, wohin Ihre Kugeln fliegen, wenn Sie \"vorbeischie�en\".",

	//Real Time Confirmation
	L"Hiermit wird vor R�cksprung in den Echtzeit-Modus eine zus�tzliche \"Best�tigung\"-Klick verlangt.",

	//Sleep/Wake notification
	L"Wenn AN, werden Sie informiert, wann Ihre S�ldner, die sich im \"Dienst\" befinden, schlafen bzw. die Arbeit wieder aufnehmen.",

	//Use the metric system
	L"Mit dieser Option wird das metrische System im Spiel verwendet.",

	//Merc Lighted movement
	L"Ist diese Funktion aktiv, werden die S�ldner automatisch beleuchtet, sobald der Cursor in ihrer N�he ist.",

	//Smart cursor
	L"Ist diese Funktion aktiv, springt der Cursor automatisch auf T�ren, wenn sich eine in der N�he befindet.",

	//snap cursor to the door
	L"Wenn EIN,wird der Cursor automatisch auf eine in der N�he des Mauszeigers befindlichen T�r zentriert.",

	//glow items 
	L"Wenn EIN, leuchten |Gegenst�nde fortw�hrend",

	//toggle tree tops
	L"Wenn EIN, werden die Spitzen der B�ume eingeblendet.",

	//toggle wireframe
	L"Wenn EIN, werden f�r verdeckte W�nde Drahtgitter eingeblendet.",

	L"Wenn EIN, wird der Bewegungs-Cursor in 3D gezeigt. ( |Home )",

};


STR16	gzGIOScreenText[] =
{
	L"GRUNDEINSTELLUNGEN",
	L"Spielmodus",
	L"Jederzeit speichern",
	L"Iron Man",
	L"Waffenoptionen",													
	L"Massen von Waffen",
	L"Normal",
	L"Schwierigkeitsgrad",
	L"Einsteiger",				
	L"Erfahrener",
	L"JA-Veteran",
	L"Ok",
	L"Abbruch",
	L"Extraschwierig",
	L"Kein Zeitlimit",
	L"Zeitbegr. Z�ge",
	L"F�r Expansion-Pack inaktiv", 
};

STR16 pDeliveryLocationStrings[] =
{
	L"Austin",			//Austin, Texas, USA	
	L"Bagdad",			//Baghdad, Iraq (Suddam Hussein's home)
	L"Drassen",			//The main place in JA2 that you can receive items. The other towns are dummy names...
	L"Hong Kong",		//Hong Kong, Hong Kong
	L"Beirut",			//Beirut, Lebanon	(Middle East)
	L"London",			//London, England
	L"Los Angeles",	//Los Angeles, California, USA (SW corner of USA)
	L"Meduna",			//Meduna -- the other airport in JA2 that you can receive items.
	L"Metavira",		//The island of Metavira was the fictional location used by JA1
	L"Miami",				//Miami, Florida, USA (SE corner of USA)
	L"Moskau",			//Moscow, USSR
	L"New York",		//New York, New York, USA
	L"Ottawa",			//Ottawa, Ontario, Canada -- where JA2 was made!
	L"Paris",				//Paris, France
	L"Tripolis",		//Tripoli, Libya (eastern Mediterranean)
	L"Tokio",				//Tokyo, Japan
	L"Vancouver",		//Vancouver, British Columbia, Canada (west coast near US border)
};

STR16 pSkillAtZeroWarning[] =
{ //This string is used in the IMP character generation.  It is possible to select 0 ability
	//in a skill meaning you can't use it.  This text is confirmation to the player.

	L"Sind Sie sicher? Das bedeutet dass der Charakter in dieser F�higkeit einen Wert von absolut NULL besitzt.",
};

STR16 pIMPBeginScreenStrings[] =
{
	L"(max. 8 Buchstaben)",
};

STR16 pIMPFinishButtonText[ 1 ]=
{
	L"Analysiere....",
};

STR16 pIMPFinishStrings[ ]=
{
	L"Danke, %s",	//%s is the name of the merc
};

// the strings for imp voices screen
STR16 pIMPVoicesStrings[] =
{
	L"Stimme", 
};

STR16 pDepartedMercPortraitStrings[ ]=
{
	L"Im Einsatz get�tet",
	L"Entlassen",
	L"Sonstiges",
};

// title for program
STR16 pPersTitleText[] =
{
	L"Personal Manager",
};

// paused game strings
STR16 pPausedGameText[] =
{
	L"Spiel-Pause",
	L"Zur�ck zum Spiel (|P|a|u|s|e)",
	L"Spiel pausieren (|P|a|u|s|e)",
};


STR16 pMessageStrings[] =
{
	L"Spiel beenden?",
	L"OK",
	L"JA",
	L"NEIN",
	L"ABBRUCH",
	L"REHIRE",		//!!! Rehire? Unknown Word. Hiring a Mercenary annother time?
	L"LIE",			//!!! Lie? In which context?
	L"Keine Beschreibung", //Save slots that don't have a description.
	L"Spiel gespeichert.",	
	L"Spiel gespeichert.",	
	L"QuickSave", //The name of the quicksave file (filename, text reference)
	L"Spielstand",	//The name of the normal savegame file, such as SaveGame01, SaveGame02, etc.
	L"sve",		//Ja25:  Dont need to translate.  This the Saved Game extension  ( Changed so it wont ovewrite Ja2 saves ) //The 3 character dos extension (represents sav)
	L"..\\SavedGames", //The name of the directory where games are saved.
	L"Tag",
	L"S�ldner",
	L"Leerer Slot", //An empty save game slot
	L"Demo",				//Demo of JA2
	L"Debug",				//State of development of a project (JA2) that is a debug build
	L"Release",			//Release build for JA2
	L"KpM",					//Abbreviation for Rounds per minute -- the potential # of bullets fired in a minute.
	L"min",					//Abbreviation for minute.
	L"m",						//One character abbreviation for meter (metric distance measurement unit).
	L"Kgln",				//Abbreviation for rounds (# of bullets)
	L"kg",					//Abbreviation for kilogram (metric weight measurement unit)
	L"Pfd",					//Abbreviation for pounds (Imperial weight measurement unit)
	L"Home",				//Home as in homepage on the internet.
	L"US$",					//Abbreviation for US Dollars
	L"n.v.",					//Lowercase acronym for not applicable.
	L"Inzwischen",		//Meanwhile
	L"%s ist angekommen im Sektor %s%s", //Name/Squad has arrived in sector A9. Order must not change without notifying SirTech
	L"Version", 
	L"Leerer Quick-Save-Slot",
	L"Dieser Slot ist f�r Quick-Saves aus den Map Screens/Taktik-Bildschirm reserviert. Speichern mit ALT+S",
	L"Offen",
	L"Zu",
#ifdef JA2DEMO
	L"Hier sind Sie fertig. Vielleicht sollten Sie mit Gabby reden.",
	L"Vielleicht h�tten Sie ihn lieber nicht t�ten sollen.",
#endif
	L"Wennig Festplattenspeicher. Sie haben nur noch %sMB frei und Jagged Alliance 2.5 ben�tigt %sMB.",
	L"%s von AIM angeheuert", 
	L"%s hat sich %s geschnappt.",		//'Merc name' has caught 'item' -- let SirTech know if name comes after item.

	L"%s hat die Droge genommen.", //'Merc name' has taken the drug
	L"%s hat keine medizinischen F�higkeiten",//'Merc name' has no medical skill.

	//CDRom errors (such as ejecting CD while attempting to read the CD)
	L"Die Spiel-Integrit�t wurde verletzt.", //The integrity of the game has been compromised
	L"FEHLER: CD-ROM-Laufwerk offen",

	//When firing heavier weapons in close quarters, you may not have enough room to do so.
	L"Kein Platz, von hier aus zu feuern.",
	
	//Can't change stance due to objects in the way...
	L"Kann seine Position jetzt nicht �ndern.",

	//Simple text indications that appear in the game, when the merc can do one of these things.
	L"Ablegen",
	L"Werfen",
	L"Weitergeben",

	L"%s weitergegeben an %s.", //"Item" passed to "merc". Please try to keep the item %s before the merc %s, otherwise,
											 //must notify SirTech.
	L"Kein Platz, um %s an %s weiterzugeben.", //pass "item" to "merc". Same instructions as above.

	//A list of attachments appear after the items.  Ex:  Kevlar vest ( Ceramic Plate 'Attached )'
	L" angebracht )",

	//Cheat modes
	L"Cheat-Level EINS erreicht",
	L"Cheat-Level ZWEI erreicht",

	//Toggling various stealth modes
	L"Stealth Mode f�r Trupp ein.",
	L"Stealth Mode f�r Trupp aus.",
	L"Stealth Mode f�r %s ein.",
	L"Stealth Mode f�r %s aus.",

	//Wireframes are shown through buildings to reveal doors and windows that can't otherwise be seen in 
	//an isometric engine.  You can toggle this mode freely in the game.
	L"Drahtgitter ein",
	L"Drahtgitter aus",

	//These are used in the cheat modes for changing levels in the game.  Going from a basement level to
	//an upper level, etc.  
	L"Von hier geht es nicht aufw�rts...",
	L"Tiefere Level gibt es nicht...",
	L"Kellerlevel %d betreten...",
	L"Keller verlassen...",

	#ifdef JA2DEMO
	
	//For the demo, the sector exit interface, you'll be able to split your teams up, but the demo
	//has this feature disabled.  This string is fast help text that appears over "single" button.
	L"In der Vollversion k�nnen Sie Ihr Team\naufteilen, nicht aber im Demo.",

	//The overhead map is a map of the entire sector, which you can go into anytime, except in the demo.
	L"Im Demo steht die Overhead-Karte nicht zur Verf�gung.",

	#endif

	L"s",		// used in the shop keeper inteface to mark the ownership of the item eg Red's gun
	L"Autoscrollen AUS.",
	L"Autoscrollen EIN.",
	L"3D-Cursor AUS.",
	L"3D-Cursor EIN.",
	L"Trupp %d aktiv.",
	L"Sie k�nnen %ss Tagessold von %s nicht zahlen",	//first %s is the mercs name, the second is a string containing the salary
	L"Abbruch", 
	L"%s kann nicht alleine gehen.",
	L"Ein Spielstand namens 'SaveGame99.sav' wurde erzeugt. Wenn n�tig, in SaveGame01 - SaveGame10 umbenennen und �ber 'Laden' aufrufen.",
	L"%s hat %s getrunken.",
	L"Ein Paket ist in Drassen angekommen.",
	L"%s erreicht Zielort (Sektor %s), am Tag: %d, um ca. %s Uhr.",		//first %s is mercs name(OK), next is the sector location and name where they will be arriving in, lastely is the day an the time of arrival      
	L"Logbuch aktualisiert.",
#ifdef JA2BETAVERSION
	L"Spiel erfolgreich in Slot 'AutoSave Spielzug-Ende' gespeichert.",
#endif
};


UINT16 ItemPickupHelpPopup[][40] =
{
	L"OK",
	L"Hoch scrollen",
	L"Alle ausw�hlen",
	L"Abw. scrollen",
	L"Abbruch",
};

STR16 pDoctorWarningString[] =
{
	L"%s ist zu weit weg, um geheilt zu werden",
	L"Ihre Sanit�ter haben noch nicht alle verbinden k�nnen.",
};

STR16 pMilitiaButtonsHelpText[] =
{
	L"Gr�ne Truppen aufnehmen(Rechtsklick)/absetzen(Linksklick)", // button help text informing player they can pick up or drop militia with this button
	L"Regul�re Truppen aufnehmen(Rechtsklick)/absetzen(Linksklick)",
	L"Elitetruppen aufnehmen(Rechtsklick)/absetzen(Linksklick)",
	L"Milizen gleichm��ig �ber alle Sektoren verteilen",
};

STR16 pMapScreenJustStartedHelpText[] =
{
	L"Zu AIM gehen und S�ldner anheuern ( *Tip*: Im Laptop )", // to inform the player to hired some mercs to get things going
	L"Wenn Sie f�r die Reise nach Arulco bereit sind, klicken Sie rechts unten im Bildschirm auf den Zeitraffer-Button .", // to inform the player to hit time compression to get the game underway
};

STR16 pAntiHackerString[] = 
{
	L"Fehler. Fehlende oder fehlerhafte Datei(en). Spiel wird beendet.",
};


STR16 gzLaptopHelpText[] =
{
	//Buttons:
	L"eMails ansehen",
	L"Websites durchsehen",
	L"Dateien und eMail-Anlagen einsehen",
	L"Logbuch lesen",
	L"Team-Info einsehen",
	L"Finanzen und Notizen einsehen", 
	L"Laptop schlie�en",

	//Bottom task bar icons (if they exist):
	L"Sie haben neue eMail(s)",
	L"Es sind neue Dateien da",

	//Bookmarks:
	L"Association of International Mercenaries",
	L"Bobby Rays Online-Waffenversand",
	L"Institut f�r S�ldnerprofilierung",
	L"More Economic Recruiting Center (MERC)",
	L"McGillicuttys Bestattungen",
	L"United Floral Service",
	L"Versicherungsmakler f�r A.I.M.-Vertr�ge",
};


STR16	gzHelpScreenText[] =
{
	L"Hilfe-Screen verlassen",	
};

STR16 gzNonPersistantPBIText[] =
{
	L"Ein Kampf ist im Gange. R�ckzug geht nur vom Taktikbildschirm aus.",
	L"Sektor betreten und Kampf fortsetzen (|E).",
	L"Kampf automatisch entscheiden (|A).",
	L"Sie k�nnen den Kampf nicht berechnen lassen, wenn Sie angreifen.",
	L"Sie k�nnen den Kampf nicht berechnen lassen, wenn Sie in einem Hinterhalt sind.",
	L"Sie k�nnen den Kampf nicht berechnen lassen, wenn Sie gegen Monster k�mpfen.",
	L"Sie k�nnen den Kampf nicht berechnen lassen, wenn feindliche Zivilisten da sind.",
	L"Sie k�nnen einen Kampf nicht berechnen lassen, wenn Bloodcats da sind.",
	L"KAMPF IM GANGE",
	L"Sie k�nnen sich im Moment nicht zur�ckziehen.",
};

STR16 gzMiscString[] =
{
	L"Ihre Milizen k�mpfen ohne die Hilfe der S�ldner weiter...",
	L"Das Fahrzeug mu� momentan nicht aufgetankt werden.",
	L"Der Tank ist %d%% voll.",
	L"Deidrannas Armee hat wieder die volle Kontrolle �ber %s.",
	L"Sie haben ein Tanklager verloren.",
};

STR16	gzIntroScreen[] = 
{
	L"Kann Introvideo nicht finden",
};

// These strings are combined with a merc name, a volume string (from pNoiseVolStr),
// and a direction (either "above", "below", or a string from pDirectionStr) to 
// report a noise.
// e.g. "Sidney hears a loud sound of MOVEMENT coming from the SOUTH."
STR16 pNewNoiseStr[] =
{
	L"%s h�rt %s aus %s.",
	L"%s h�rt eine BEWEGUNG (%s) aus %s.", 
	L"%s h�rt ein KNARREN (%s) aus %s.",
	L"%s h�rt ein KLATSCHEN (%s) aus %s.",
	L"%s h�rt einen AUFPRALL (%s) aus %s.",
	L"%s h�rt einen SCHUSS (%s) von %s.",								//@@@ added Feb21,2000, JA25: new string
	L"%s h�rt eine EXPLOSION (%s) von %s.", 
	L"%s h�rt einen SCHREI (%s) von %s.",
	L"%s h�rt einen AUFPRALL (%s) von %s.",
	L"%s h�rt einen AUFPRALL (%s) von %s.",
	L"%s h�rt ein ZERBRECHEN (%s) aus %s.",
	L"%s h�rt ein ZERSCHMETTERN (%s) aus %s.",
};

STR16 wMapScreenSortButtonHelpText[] =
{
	L"Nach Name sortieren(|F|1)",
	L"Nach Auftrag sortieren(|F|2)",
	L"Nach wach/schlafend sortieren(|F|3)",
	L"Nach Ort sortieren(|F|4)",
	L"Nach Ziel sortieren(|F|5)",
	L"Nach Abreisezeit sortieren(|F|6)",
};



STR16		BrokenLinkText[] = 
{
	L"Fehler 404",
	L"Site nicht gefunden.",
};


STR16 gzBobbyRShipmentText[] = 
{
	L"Letzte Lieferungen",
	L"Bestellung #",
	L"Artikelzahl",
	L"Bestellt am",
};


STR16	gzCreditNames[]=
{
	L"Chris Camfield",
	L"Shaun Lyng",
	L"Kris M�rnes",
	L"Ian Currie",
	L"Linda Currie",
	L"Eric \"WTF\" Cheng",
	L"Lynn Holowka",
	L"Norman \"NRG\" Olsen",
	L"George Brook",
	L"Andrew Stacey",
	L"Scot Loving",
	L"Andrew \"Big Cheese\" Emmons",
	L"Dave \"The Feral\" French",
	L"Alex Meduna",
	L"Joey \"Joeker\" Whelan",
};

//Ja25: @@@ this entire section changed
STR16	gzCreditNameTitle[]=
{
	L"Game-Internals Programmierer", 			// Chris Camfield
	L"Co-Designer/Texter",							// Shaun Lyng
	L"Strategic Systems & Editor",					//Kris \"The Cow Rape Man\" Marnes
	L"Produzent/Co-Designer",						// Ian Currie
	L"Co-Designer/Karten-Designer",				// Linda Currie
	L"Grafiker",													// Eric \"WTF\" Cheng
	L"Beta-Coordinator, Support",				// Lynn Holowka
	L"Grafik-Unterst�tzung",						// Norman \"NRG\" Olsen
	L"Sound Guru",											// George Brooks
	L"Screen-Designer/Grafiker",					// Andrew Stacey
	L"JA2 Chefgrafiker",						// Scot Loving
	L"JA2 Chef-Programmierer",									// Andrew \"Big Cheese Doddle\" Emmons
	L"JA2UB Chef-Programmierer",											// Dave French
	L"Strategic Systems & Game-Balance",					// Alex Meduna
	L"JA2UB Chef-Grafiker",								// Joey \"Joeker\" Whelan",
};

//Ja25: @@@ this entire section changed
STR16	gzCreditNameFunny[]=
{
	L"(JA3 Chef-Designer)", 																			// Chris Camfield
	L"(lernt noch Interpunktion)",					// Shaun Lyng
	L"(\"Ist tot und begraben. Nicht anfassen!\")",	//Kris \"The Cow Rape Man\" Marnes
	L"(werde viel zu alt f�r sowas)",				// Ian Currie
	L"(und arbeite an Wizardry 8)",						// Linda Currie
	L"(wurde verdonnert, die QA zu machen)",			// Eric \"WTF\" Cheng
	L"(�berlie� uns der CFSA - go figure...)",	// Lynn Holowka
	L"",																			// Norman \"NRG\" Olsen
	L"Bist du mein Papa?",																			// George Brooks
	L"(Dead Head und Jazz-Liebhaber)",						// Andrew Stacey
	L"(sein echte Name ist Robert)",							// Scot Loving
	L"(konzentriert sich jetzt auf JA3)",									// Andrew \"Big Cheese Doddle\" Emmons
	L"(kann jetzt wieder zum Motocross zur�ck)",	// Dave French
	L"(geklaut von Wizardry 8)",							// Alex Meduna
	L"(machte die Gegenst�nde und Lade-Screens!)",	// Joey \"Joeker\" Whelan",
};

STR16 sRepairsDoneString[] =
{
	L"%s hat eigene Gegenst�nde repariert",
	L"%s hat Waffen und R�stungen aller Teammitglieder repariert",
	L"%s hat aktiven Gegenst�nde aller Teammitglieder repariert",
	L"%s hat die mitgef�hrten Gegenst�nde aller Teammitglieder repariert",
};

STR16 zGioDifConfirmText[]=
{
	L"Dies ist der EINSTEIGER-Modus. Die richtige Entscheidung f�r Spieler, die noch nie Jagged Alliance oder �hnliches gespielt haben. Oder f�r Leute, die sich ganz einfach k�rzere K�mpfe w�nschen. Ihre Wahl wird den Verlauf des gesamten Spiels beeinflussen. Entscheiden Sie sich also in aller Ruhe. Sind Sie sicher, dass Sie im Einsteiger-Modus spielen wollen?",
	L"Dies ist der FORTGESCHRITTENEN-Modus. Dies ist die passende Einstellung f�r Spieler, die bereits Erfahrung mit Jagged Alliance oder �hnlichen Spielen haben. Ihre Wahl wird den Verlauf des gesamten Spiels beeinflussen. Entscheiden Sie sich also in aller Ruhe. Sind Sie sicher, dass Sie im Fortgeschrittenen-Modus spielen wollen?",
	L"Dies ist der PROFI-Modus. Na gut, wie Sie wollen. Aber meckern Sie nicht, wenn sie nachher im Sarg nach Hause kommen. Ihre Wahl wird den Verlauf des gesamten Spiels beeinflussen. Entscheiden Sie sich also in aller Ruhe. Sind Sie sicher, dass Sie im Profi-Modus spielen wollen?",
};

STR16 gzLateLocalizedString[] =
{
	L"%S Loadscreen-Datei nicht gefunden...",

	//1-5
	L"Der Roboter kann diesen Sektor nicht verlassen, wenn niemand den Controller bedient.",

	//This message comes up if you have pending bombs waiting to explode in tactical.
	L"Sie k�nnen den Zeitraffer jetzt nicht benutzen. Warten Sie das Feuerwerk ab!",

	//'Name' refuses to move.
	L"%s weigert sich zu bewegen.",

	//%s a merc name
	L"%s hat nicht genug Energie, um die Position zu �ndern.",

	//A message that pops up when a vehicle runs out of gas.
	L"%s hat kein Benzin mehr und steckt in %c%d fest.",

	//6-10

	// the following two strings are combined with the pNewNoise[] strings above to report noises
	// heard above or below the merc
	L"oben",
	L"unten",

	//The following strings are used in autoresolve for autobandaging related feedback.
	L"Keiner Ihrer S�ldner hat medizinische F�higkeiten.",
	L"Sie besitzen keinerlei Verbandszeug.",
	L"Sie haben nicht genug Verbandszeug, um alle zu versorgen.",
	L"Keiner der S�ldner muss verbunden werden.",
	L"S�ldner automatisch verarzten.",
	L"Alle S�ldner sind versorgt.",

	//14
	L"Arulco",

  L"(dach)",

	L"Gesundheit: %d/%d",

	//In autoresolve if there were 5 mercs fighting 8 enemies the text would be "5 vs. 8"
	//"vs." is the abbreviation of versus.
	L"%d gegen. %d",
	
	L"%s ist voll!",  //(ex "The ice cream truck is full")

	L"%s braucht keine schnelle Erste Hilfe, sondern eine ausgiebige medizinische Behandlung und/oder Erholung.",

	//20
	//Happens when you get shot in the legs, and you fall down.
	L"%s ist am Bein getroffen und gest�rzt!",
	//Name can't speak right now.
	L"%s kann im Moment nicht sprechen.",

	//22-24 plural versions 
	L"%d gr�ne Milizen wurden zu Elitemilizen bef�rdert.",
	L"%d gr�ne Milizen wurden zu regul�ren Milizen bef�rdert.",
	L"%d regul�re Milizen wurde zu Elitemilizen bef�rdert.",

	//25
	L"Schalter",

	//26
	//Name has gone psycho -- when the game forces the player into burstmode (certain unstable characters)
	L"%s spielt verr�ckt!",

	//27-28
	//Messages why a player can't time compress.
	L"Momentan ist es gef�hrlich den Zeitraffer zu benutzen, da noch S�ldner in Sektor %s sind.",
	L"Momentan ist es gef�hrlich den Zeitraffer zu benutzen, wenn sich noch S�ldner in monstern-verseuchten Minen befinden.",

	//29-31 singular versions 
	L"1 gr�ne Miliz wurde zur Elitemiliz bef�rdert.",
	L"1 gr�ne Miliz wurde zur regul�ren Miliz bef�rdert.",
	L"1 regul�re Miliz wurde zur Elitemiliz bef�rdert.",

	//32-34
	L"%s sagt gar nichts.",
	L"Zur Oberfl�che gehen?",
	L"(Trupp %d)",

	//35
	//Ex: "Red has repaired Scope's MP5K".  Careful to maintain the proper order (Red before Scope, Scope before MP5K)
	L"%s hat %ss %s repariert",

	//36
	L"BLOODCAT",

	//37-38 "Name trips and falls"
	L"%s stolpert und f�llt hin",
	L"Dieser Gegenstand kann von hier aus nicht aufgehoben werden.",

	//39
	L"Keiner Ihrer verbliebenen S�ldner ist in der Lage, zu k�mpfen. Die Miliz wird die Monster alleine bek�mpfen",

	//40-43
	//%s is the name of merc.
	L"%s hat keinen Verbandzeug mehr!",
	L"%s hat keine F�higkeiten, jemanden zu verarzten!",
	L"%s hat keinen Werkzeugset mehr!",
	L"%s hat keine F�higkeiten, irgend etwas zu reparieren!",

	//44-45
	L"Reparaturzeit",
	L"%s kann diese Person nicht sehen.", 

	//46-48
	L"%ss Gewehrlauf-Extender f�llt runter!",
	L"Pro Sektor sind nicht mehr als %d Milizausbilder erlaubt.",
  	L"Sind Sie sicher?", // 

	//49-50
	L"Zeitraffer", //time compression
	L"Der Fahrzeugtank ist jetzt voll.",

	//51-52 Fast help text in mapscreen.
	L"Zeitraffer fortsetzen (|S|p|a|c|e)",
	L"Zeitraffer anhalten (|E|s|c)",

	//53-54 "Magic has unjammed the Glock 18" or "Magic has unjammed Raven's H&K G11" 
	L"%s hat Ladehemmung von %s behoben",
	L"%s hat Ladehemmung von %ss %s behoben",

	//55 
	L"Can't compress time while viewing sector inventory.",

	L"Kann Zeit nicht komprimieren, w�hrend das Sektorinventar eingesehen wird.",

	L"Die Jagged Alliance 2.5 CD wurde nicht gefunden. Das Programm wird jetzt beendet.",

	L"Gegenst�nde wurden erfolgreich zusammengef�gt.",

	//58
	//Displayed with the version information when cheats are enabled.
	L"Aktueller/Max. Fortschritt: %d%%/%d%%",

	L"John und Mary eskortieren?",

	// 60
	L"Schalter aktiviert.",
	
 	L"%s's Keramic-Panzer wurde zerst�rt!",
};




#endif //ENGLISH
