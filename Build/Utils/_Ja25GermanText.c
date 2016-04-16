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







STR16	gzImportJa2ScreenText[]=
{
	L"Neues Spiel",
	L"Es gibt 2 Möglichkeiten, ein neues Spiel in 'Jagged Alliance 2 - Unfinished Business' zu beginnen:",
	L"Mit NEUEN Charakteren beginnen",
	L"Dies gleicht dem Neustart eines Spiels von JAGGED ALLIANCE 2. Sie können dann einen eigenen B.S.E. - Söldner kreieren und zusätzliche Söldner von A.I.M und M.E.R.C. anheuern. Alle Statistiken Ihrer Charaktere beginnen dann bei ihren normalen Basiswerten.",

	L"GESPEICHERTE Charaktere importieren",
	L"Sollten Sie einen gespeicherten Spielstand von JAGGED ALLIANCE 2 besitzen, können Sie selbsterzeugte B.S.E. Charaktere wie auch alle statistischen Verbesserungen Ihrer A.I.M und M.E.R.C. Söldner importieren. Die Inventorys (der pers. Besitz) Ihrer Söldner wird geleert und die Spielschwierigkeit wird etwas erhöht, um sich den fortgeschrittenen Fähigkeiten Ihrer Charaktere anzupassen.",

	L"Sie beginnen das Spiel mit Ihrem B.S.E. Söldner. Sie können wie gewohnt auch Söldner von A.I.M. und M.E.R.C. anheuern. Rekrutierte Charaktere aus  JAGGED ALLIANCE 2, wie z.B. Ira oder Dynamo, sind in ihr normales Leben zurückgekehrt und sind nicht mehr verfügbar.",
	L"NEUSTART",
	L"IMPORTIEREN",
	L"ABBRUCH",
};

STR16 zNewButtonText[]=
{
	L"Start",
	L"Import",
	L"Abbruch",
	L"Wollen Sie NEU starten, Charaktere ausJA2 IMPORTIEREN, oder ABBRECHEN und zurück zum Hauptmenü?",
	L"Um Charaktere zu IMPORTIEREN, müssen Sie zuerst das externe Programm  \"Ja25SaveConverter.exe\" starten. Möchten Sie das jetzt tun?",
	L"Alten Spielstand erfolgreich importiert. Möchten Sie die Information aus dem Spielstand verwenden?",
	L"Fehler beim Importieren.",
};

STR16	zNewTacticalMessages[]=
{
	L"Entfernung zum Ziel: %d Felder",
	L"Verbinden Sie den Transmitter mit Ihrem Laptop-Computer.",
	L"Sie haben nicht genug Geld, um %s anzuheuern",
	L"Das obenstehende Honorar deckt für einen begrenzten Zeitraum die Kosten der Gesamtmission, und schließt untenstehendes Equipment mit ein.",
	L"Engagieren Sie %s jetzt und nutzen Sie den Vorteil unseres beispiellosen 'Ein Betrag für alles'-Honorars. Das persönliche Equipment des Söldners ist gratis in diesem Preis mit inbegriffen.",
	L"Honorar",
	L"Da ist noch jemand im Sektor...",
	L"Waffen-Rchwt.: %d Felder, Entf. zum Ziel: %d Felder",
	L"Deckung anzeigen",
	L"Sichtfeld",
	L"Neue Rekruten können dort nicht hinkommen.",
	L"Da Ihr Laptop keinen Transmitter besitzt, können Sie keine neuen Teammitglieder anheuern. Vielleicht ist dies eine guter Zeitpunkt, ein gespeichertes  Spiel zu laden oder ein neues zu starten!",
	L"%s hört das Geräusch knirschenden Metalls unter Jerry hervordringen. Es klingt grässlich - die Antenne ihres Laptop-Computers ist  zerstört.",  //the %s is the name of a merc.  @@@  Modified
	L"Nach Ansehen des Hinweises, den Commander Morris hinterließ, erkennt %s eine einmalige Gelegenheit. Der Hinweis enthält Koordinaten für den Start von Raketen gegen verschiedene Städte in Arulco. Aber er enthält auch die Koordinaten des Startpunktes - der Raketenanlage.",
	L"Das Kontroll-Board studierend, entdeckt %s, dass die Zahlen umgedreht werden könnten, so dass die Raketen diese Anlage selbst zerstören. %s muss nun einen Fluchtweg finden. Der Aufzug scheint die schnellstmögliche Route zu bieten...",         //!!! The original reads:	L"Noticing the control panel %s, figures the numbers can be reversed..." That sounds odd for me, but I think the comma is placed one word too late... (correct?)
L"Dies ist ein IRON MAN-Spiel, und es kann nicht gespeichert werden, wenn sich Gegner in der Nähe befinden.",		
	L"(Kann während Kampf nicht speichern)", 
	L"Der Name der aktuellen Kampagne enthält mehr als 30 Buchstaben.",						
	L"Die aktuelle Kampagne kann nicht gefunden werden.",																	
	L"Kampagne: Standard ( %S )",																							
	L"Kampagne: %S",																													
	L"Sie haben die Kampagne %S gewählt. Diese ist eine vom Spieler modifizierte Version der Originalkampagne von JA2UB. Möchten Sie die Kampagne %S spielen?",			
	L"Um den Editor zu benutzen, müssen Sie eine andere als die Standardkampgane auswählen.",		
};


STR16	gzNewLaptopMessages[]=
{
	L"Fragen Sie nach dem Spezialangebot!",
	L"Derzeit nicht verfügbar",
};

//these strings match up with the defines in IMP Skill trait.c
STR16 gzIMPSkillTraitsText[]=
{
	L"Schlösser knacken",
	L"Mann gegen Mann",
	L"Elektronik",
	L"Nacht-Operationen",
	L"Werfen",
	L"Unterrichten",
	L"Schwere Waffen",
	L"Autom. Waffen",
	L"Schleichen",
	L"Beidhändigkeit",
	L"Messer",
	L"Dachtreffer-Bonus",
	L"Tarnkunst",
	L"Martial Arts",

	L"Kein",
	L"B.S.E. Spezialitäten",
};


//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"Sie haben den IRON MAN-Modus gewählt. Dies macht das Spiel eventuell schwieriger als Sie vielleicht möchten, denn Sie können so lange nicht abspeichern, wie Ihr Sektor von Feinden infiltriert ist. Dies beeinflusst das gesamte Spiel. Wollen Sie wirklich im IRON MAN-Modus spielen?",
};

#endif
