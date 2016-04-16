#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
	#include "_EditorEnglishtext.h"


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







STR16	gzEditorStrings[]=
{
	L"DETAILIERT",
	L"Anfangsbev�lkerung",
	L"Leicht",
	L"Normal",
	L"Schwer",
	L"Miliz",
	L"Truppen",
	L"Elite",
	L"BloodCats",
	L"Invasionsdaten",
	L"Min Feinde",
	L"Angriffswahrscheinlichkeit",
	L"Gnadenfrist",
	L"Eintrittskoordinaten",
	L"Levelname",
	L"Eintrittsrichtung",
	L"Ladebildschirm",

	L"Schnee",
	L"Wachposten",
	L"Kraftwerk",
	L"Allgemein",
	L"Stadt 1",
	L"Stadt 2",
	L"Wald",
	L"Mine",
	L"H�hle",
	L"Pinie",
	L"Mineneingang",
	L"Wildnis",
	L"Kellergew�lbe",
	L"L�schen",
	L"Norden",
	L"Nordosten",
	L"Osten",
	L"S�dosten",
	L"S�den",
	L"S�dwesten",
	L"Westen",
	L"Nordwesten",
	L"Ansicht der Spieler umschalten",
	L"Ansicht der Feinde umschalten",
	L"Ansicht der Kreaturen umschalten",
	L"Allgemeiner Informationsmodus",
	L"Eigenschaftsmodus",
	L"Inventarmodus",
	L"Planungsmodus",
	L"Gew�hlten S�ldner l�schen (ENTF).",
	L"N�chsten S�ldner finden (SPACE).",
	L"Existenzpriorit�t umschalten",
	L"STATION�R",
	L"AUF WACHE",
	L"AUF ABRUF",
	L"FEIND SUCHEN",
	L"NAHE PATR.",
	L"WEITE PATR.",
	L"PUNKT PATR.",
	L"KREISPATR.",
	L"DEFENSIV",
	L"MUTIG ALLEIN",
	L"MUTIG HILFE",
	L"AGGRESSIV",
	L"SCHLAU ALLEINE",
	L"SCHLAU HELFEND",
	L"S�ldner soll nach %s blicken",
	L"Such",
	L"Gew�hlten S�ldner finden",
	L"Vorheriger Farbsatz",
	L"N�chster Farbsatz",
	L"Zeitvariante umschalten (+ oder - 15 Minuten)",
	L"Keine Aktion",
	L"Planung l�schen",
	L"D�CHER",
	L"W�NDE",
	L"RAUM INFO",
	L"W�nde �ber die Auswahlmethode setzen\n",
	L"T�ren �ber die Auswahlmethode setzen",
	L"D�cher �ber die Auswahlmethode setzen",
	L"Fenster �ber die Auswahlmethode setzen",
	L"Besch�digte W�nde �ber die Auswahlmethode setzen.",
	L"M�bel �ber die Auswahlmethode setzen",
	L"Wandklebebilder �ber die Auswahlmethode setzen",
	L"B�den �ber die Auswahlmethode setzen",
	L"Allgemeine M�bel �ber die Auswahlmethode setzen",
	L"W�nde �ber die Smartmethode setzen",
	L"T�ren �ber die Smartmethode einf�gen",
	L"Fenster �ber die Smartmethode einf�gen",
	L"Besch�digte W�nde �ber die Smartmethode setzen",
	L"Neuen Raum hinzuf�gen",
	L"H�hlenw�nde editieren.",
	L"Bereich von einem Geb�ude entfernen.",
	L"Ein Geb�ude entfernen",
	L"Hinzuf�gen/ersetzen eines Geb�udedaches durch ein neues Flachdach.",
	L"Ein Geb�ude kopieren",
	L"Ein Geb�ude bewegen",
	L"Raumnummer vergeben",
	L"Raumnummer l�schen",
	L"L�schmodus umschalten",
	L"Letzte �nderung verwerfen",
	L"Pinselgr��e ver�ndern",
	L"Waffen",
	L"Muni",
	L"Pnzrng",
	L"Sprengst.",
	L"E1",
	L"E2",
	L"E3",
	L"Trigger",
	L"Umgebungslicht hinzuf�gen",
	L"Falsche Umgebungslichter umschalten.",
	L"Gitter hinzuf�gen/entfernen (r-clk um abzufragen, ob vorhanden).",
	L"Spezifiziere n�rdlichen Eintrittspunkt.",
	L"Spezifiziere westlichen Eintrittspunkt.",
	L"Spezifiziere �stlichen Eintrittspunkt.",
	L"Spezifiziere s�dlichen Eintrittspunkt.",
	L"Spezifiziere mitteleren Eintrittspunkt.",
	L"Spezifiziere Isolations-Eintrittspunkt.",
	L"Neue Karte",
	L"Neues Kellergeschoss",
	L"Neue H�hlenebene",
	L"Karte speichern",
	L"Karte laden",
	L"Umgebung w�hlen",
	L"Editormodus verlassen",
	L"Vorherige Richtung",
	L"N�chste Richtung",
	L"Bodentexturen zeichnen",
	L"Bodentexturen der Karte festlegen",
	L"Sandb�nke und Kliffs platzieren",
	L"Strassen zeichnen",
	L"Schutt zeichnen",
	L"B�ume & Str�ucher platzieren",
	L"Felsen platzieren",
	L"F�sser & anderes Zeug platzieren",
	L"Gebiet f�llen",
	L"Pinseldichte erh�hen",
	L"Pinseldichte verringern",
	L"Gel�nde",
	L"Geb�ude",
	L"Gegenst�nde",
	L"S�ldner",
	L"Karteninfo",
	L"Sonstiges",
	L"N�rdlicher Eintrittspunkt",
	L"Westlicher Eintrittspunkt",
	L"�stlicher Eintrittspunkt",
	L"S�dlicher Eintrittspunkt",
	L"Zentraler Eintrittspunkt",
	L"Isolierter Eintrittspunkt",
	L"Tag",
	L"Nacht",
	L"24 Std.",
	L"Paniktrigger 1",
	L"Paniktrigger 2",
	L"Paniktrigger 3",
	L"Paniktrigger 4",
	L"Paniktrigger 5",
	L"Paniktrigger 6",
	L"Ausl�ser%d",
	L"Druckschalter",
	L"Panikaktion 1",
	L"Panikaktion 2",
	L"Panikaktion 3",
	L"Panikaktion 4",
	L"Panikaktion 5",
	L"Panikaktion 6",
	L"Aktion%d",
	L"Keine Schloss ID",
	L"Sprengfalle",
	L"Elektrofalle",
	L"Sirenenfalle",
	L"Stiller Alarm",
	L"Super Elektrofalle",
	L"Fallenstufe %d",
	L"H", 	// Ein-Buchstaben-Kode f�r versteckte Gegenst�nde
	L"GitterNr: %d  ", // zeigt aktuelle Gitternr. Auf dem Bildschirm
	L"                ", // l�scht obigen Gitternr. Indikator
	L"Momentan keine Karte geladen.",
	L"Datei:  %S, Umgebung:  %s",
	L"Breite: %d",
	L"Automatisch",
	L"Spieler",
	L"Feind",
	L"Bloodcat",
	L"WEITER",
	L"UMSCHALTEN",
	L"ANSICHTEN",
	L"AUSWAHLMETHODE",
	L"SMARTMETHODE",
	L"BAUMETHODE",
	L"Raum#",
	L"Okay",
	L"Abbruch",
	L"Bearbeiten der Schlossattribute am Kartenindex %d.",
	L"Schloss ID",
	L"Fallentyp",
	L"Fallenstufe",
	L"Verschlossen",
	L"Status Info Zeile 1",
	L"Status Info Zeile 2",
	L"Status Info Zeile 3",
	L"Status Info Zeile 4",
	L"Status Info Zeile 5",
	L"R",	// R is for "red" color
	L"G",	// G is for "green" color
	L"B",	// B is for "blue" color
	L"Radius",	// size of light
	L"Untergrund",
	L"Lichtstufe",
	L"Draussen",
	L"Keller",
	L"H�hlen",
	L"Zielort",
	L"Sektor",
	L"Kellerebene",
	L"Ziel",
	L"Gitternr.",
	L"S�ldnername:",
	L"Befehle:",
	L"Kampfhaltung:",
	L"S�ldnerfarben",
	L"Fertig",
	L"Vorheriger einsatzbereiter S�ldner",
	L"N�chster einsatzbereiter S�ldner",
	L"Kampfhaltung des vorherigen S�ldners",
	L"Kampfhaltung des n�chsten S�ldners",
	L"Statistik des S�ldners verringern",
	L"Statistik des S�ldners erh�hen",
	L"Zuf�llig",
	L"Normaler Mann",
	L"Gro�er Mann",
	L"Untersetzter Mann",
	L"Normale Frau",
	L"Bloodcat",
	L" --=BEFEHLE=-- ",
	L"--=HALTUNG=--",
	L"Armee",
	L"Miliz",
	L"Elite",

	L"Erf. Stufe",
	L"Leben",
	L"Max Leben",
	L"Treffsicherheit",
	L"St�rke",
	L"Gewandtheit",
	L"Geschicklichkeit",
	L"Klugheit",
	L"F�hrung",
	L"Sprengstoffe",
	L"Medizin",
	L"Mechanik",
	L"Moral",

	L"Haarfarbe:",
	L"Hautfarbe:",
	L"Westenfarbe:",
	L"Hosenfarbe:",

	L"ZUF�LLIG",
	L"Aktuelles Profil:  n/a                            ",

	L"STATION�R",
	L"AUF ABRUF",
	L"AUF WACHE",
	L"FEIND SUCHEN",
	L"NAHE PATROUILLE",
	L"WEITE PATROUILLE",
	L"WEGPUNKT PATROUILLE",
	L"RUNDEN PATROUILLE",
	L"Speicherplatz #%d",
	L"Patroillenbefehle ohne Wegpunkte",
	L"Wegpunkte ohne Patrouillenbefehle",
	L"Platzierung nicht kopiert da keine Platzierung ausgew�hlt wurde.",
	L"Platzierung kopiert.",
	L"Platzierung nicht eingef�gt da sich keine Platzierung im Zwischenspeicher befindet.",
	L"Platzierung eingef�gt.",
	L"Platzierung wurde nicht eingef�gt da die Maximalzahl f�r dieses Team bereits erreicht ist.",
	L"Klein",
	L"Mittel",
	L"Gross",
	L"�bergross",
	L"Breite: ",
	L"Gebiet",
	L"Editor verlassen?",
	L"Sind Sie sicher, dass Sie alle Lichter entfernen wollen?",
	L"Sind Sie sicher, dass Sie die Planung umkehren wollen?",
	L"Sind Sie sicher, dass Sie die Planung l�schen wollen?",
	L"Baumwipfel entfernen",
	L"Baumwipfel anzeigen",
	L"Neuen Bodenlevel starten?", // 
	L"Neuen H�hlenlevel starten?",     // 
	L"Neuen Outdoor-Level starten?",  // 
	L" Bodentexturen ausradieren? ",
	L"HOME",
	L"Editorbeleuchtung ein/ausschalten",
	L"EINF�GEN",
	L"F�llmodus ein/ausschalten",
	L"BKSPC",
	L"ENTF",
	L"Objekt unter Cursor schnell l�schen",
	L"ESC",
	L"Editor verlassen",
	L"Bild rauf/Bild runter",
	L"Einzuf�gendes Objekt wechseln",
	L"F1",
	L"Dieser Hilfe-Bildschirm",
	L"F10",
	L"Aktuelle Karte speichern",
	L"F11",
	L"Karte als aktuelle Karte laden",
	L"+/-",
	L"Schattendunkelheit um .01 ver�ndern",
	L"SHFT +/-",
	L"Schattendunkelheit um .05 ver�ndern",
	L"0 - 9",
	L"Dateiname der Karte/des Musters �ndern",
	L"b",
	L"Pinselgr��e �ndern",
	L"d",
	L"o",
	L"Hindernis zeichnen",
	L"r",
	L"Felsen zeichnen",
	L"t",
	L"Anzeige von B�umen an/abschalten",
	L"g",
	L"Bodentexturen zeichnen",
	L"w",
	L"Geb�udew�nde zeichnen",
	L"e",
	L"h",
	L"D�cher an/abschalten",
	L"Kartendaten wurden gerade besch�digt.  Nicht speichern!",
	L"Gitternr. eingeben:",
	L"Flagge an/abschalten",
	L"Kein Gegenstand gew�hlt.",
	L"Speicherplatz frei f�r",
	L"zuf�llige Generierung.",
	L"Schl�ssel nicht editierbar.",
	L"ProfilID des Eigent�mers",
	L"Gegenstandsklasse nicht implementiert.",
	L"Speicherplatz als frei gesperrt.",
	L"Status",
	L"Runden",
	L"Fallenstufe",
	L"Quantit�t",
	L"Dollar",
	L"Toleranz",
	L"Alarm Ausl�ser",
	L"Existenzwahrsch.",
	L"SCHALLD�MPF.",
	L"ZIELFERNR.",
	L"LASERZIEL.",
	L"ZWEIBEIN",
	L"SCHNABEL",
	L"GRANATW.",
	L"KERAMIKPL.",
	L"SPRENGK.",
	L"Wenn der Paniktrigger ein Alarmausl�ser ist,\nwerden Feinde nicht mehr versuchen, ihn zu benutzen, wenn sie \nbereits wissen, dass Sie hier sind.",
	L"%s Karte (*.dat)",
	L"Speichern",
	L"Laden",
	L"KEINE DATEIEN IM \\KARTEN VERZEICHNIS",
	L" Die nur-lesen Datei %s l�schen? ",
	L" Datei %s l�schen? ",
	L" Ung�ltiger Dateiname.  Versuchen Sie einen anderen Darteinamen?",
	L" Datei ist nur-lesen!  W�hlen Sie einen anderen Namen? ",
	L" Datei existiert, �berschreiben? ",
	L"Karte laden:  %s",
	L"Dateiname",
	L"Welt-Info aktualisieren",	
	L"Karte speichern:  %s",
	L"Kartendaten wurden soeben besch�digt!",
	L"Fehler beim Laden der Datei.",
	L".dat",
	L"Auswahl abbrechen",
	L"Auswahl akzeptieren",
	L"Fenster nach oben scrollen",
	L"Fenster nach unten scrollen",
	L"%S[%d] ist aus Tileset %s (%S)",
	L"Datei:  %S, Unterindex:  %d (%S)",
	L"Aktuelles Tileset:  %s",
	L"Rang des Gegners:",																											/// @@@ New
	L"Platzierung der Feinde:",																												// @@@ New
	L"Gesamt:",																																// @@@ New
	L"(Fehlen %d)",																													// @@@ New
	L"Vorheriger Ladebildschirm",																												// @@@ New
	L"N�chster Ladebildschirm",																												// @@@ New
	L"Bloodcats:",																												// @@@ New
	L"Aktuelle Kampagne: %S",																									// @@@ New
	L"�berpr�fe",
	L"Gegenst�nde",
	L"  ",
};


UINT16 gszActionItemDesc[ NUM_ACTIONITEMS ][ 30 ] =
{
    L"Klaxon Mine",
    L"Leuchtmine",
    L"Tr�nengas Explosion",
    L"Bet�ubungsgas Explosion",
    L"Rauch Explosion",
    L"Senfgas",
    L"Landmine",
    L"T�r �ffnen",
    L"T�r schlie�en",
    L"Kleine Explosion",
    L"Mittlere Explosion",
    L"Gro�e Explosion",
    L"T�r �ndern",
	L"Raum Entdecken",
    L"Lokaler Alarm",
    L"Globaler Alarm",
    L"Klaxon Sound",
    L"Druckgegenst�nde ziehen",
    L"Blutkatzenalarm",
    L"Gro�es Tr�nengas",
};




UINT16 *EditMercStat[12] =
{
    L"Max. Gesundheit",
    L"Gesundheit",
    L"St�rke",
    L"Gewandtheit",
    L"Geschicklichkeit",
    L"Charisma",
    L"Klugheit",
    L"Treffsicherheit",
    L"Sprengstoffe",
    L"Medizin",
    L"Wissenschaft",
    L"Erfahrungsstufe"
};


UINT16 *EditMercOrders[8] =
{
    L"Station�r",
    L"Auf Wache",
    L"Nahe Patrouille",
    L"Ferne Patrouille",
    L"Wegpunkt Patrouille",
    L"Auf Abruf",
    L"Feind suchen",
    L"Zuf�llige Patrouille"
};

UINT16 *EditMercAttitudes[6] =
{
    L"Verteidigung",
    L"Alleing�nger Tapfer",
    L"Kumpel Tapfer",
    L"Alleing�nger Schlau",
    L"Kumpel Schlau",
    L"Aggressiv"
};

UINT16 *zDiffNames[5] =
{
    L"K�mmerlich",
    L"Leicht",
    L"Normal",
    L"Hart",
    L"Nur f�r Benutzer von Steroid",
};

UINT16 *gTilesetNames[ 60 ] =
{
    L"ALLGEMEIN 1",                                                    // 0
    L"H�HLEN 1",                                                        // 1
    L"W�STE 1",                                                    // 2
    L"BESOFFEN 1 (Staubstr.)",                                // 3
    L"TROPISCH 1",                                                // 4
    L"BERGE 1",                                                // 5
    L"K�STE 1",                                                    // 6
    L"SUMPF 1",                                                        // 7
    L"FARM 1",                                                        // 8
    L"OMERTA",                                                        // 9
    L"ALLGEMEIN 2 (Dirtroads)",                            // 10
    L"FARM 2 (eingebr. W�nde)",                            // 11
    L"GEF�NGNIS",                                                        // 12
    L"KRANKENHAUS (Cambria)",                                // 13
    L"DEMO BASEMENT",                                            // 14
    L"ABGEBRANNTE B�UME",                                                // 15
    L"GESETZLOS 1 (San Mona-d5)",                        // 16
    L"LANDEPLATZ (Drassen-b13)",                        // 17
    L"GESETZLOS 2 (abgebrannt-c5)",                            // 18
    L"Zerst�rter Landeplatz",                // 19
    L"Kellergescho�",                                                    // 20
    L"GESETZLOS 3 (abgebrannt-c6)",                          // 21
    L"GEF�NGNIS DUNGEON",                                      // 22
    L"AKTIV DRASSEN (d13)",                          // 23
    L"SAM BASIS",                                                  // 24
    L"BESOFFEN2 (untersch. B�ume)",                      // 25
    L"MILIT�RISCHE BASIS",                                            // 26
    L"MILIT�RISCHES GEF�NGNIS",                                          // 27
    L"MILIT�RISCHES WARENLAGER",                              // 28
    L"MILIT�RISCHE STADT",                                          // 29
    L"ALTE SCHULE",                                              // 30
    L"CAMBRIA STREIFEN",                                          // 31
    L"CAMBRIA H�USER",                                          // 32
    L"PALAST!",                                                      // 33
    L"TROPISCHE SAM",                                          // 34
    L"GRUMM 1",                                                      // 35
    L"GRUMM 2",                                                      // 36
    L"BALIME",                                                      // 37
    L"BALIME MUSEUM",                                          // 38
    L"W�STE SAM",                                              // 39
    L"ORTA",                                                          // 40
    L"ORTA WAFFEN",                                          // 41
    L"SUMPF BARETREES",                                      // 42
    L"ESTONI",                                                      // 43
    L"K�NIGIN'S GEF�NGNIS",                                      // 44
    L"K�NIGIN'S TROPEN",                                  // 45
    L"MEDUNA INNENSTADT",                                  // 46
    L"K�NIGIN'S SAM",                                              // 47
    L"K�NIGIN'S FLUGHAFEN",                                      // 48
    L"DEMO TILESET",                                          // 49
    L"VIEL SCHNEE",                                              // 50
    L"SCHNEE GEMISCHT",                                              // 51
    L"GRAS & SCHNEE",                                          // 52
    L"GEFALLENE STADT",                                                  // 53
    L"BERGBAU STADT",                                              // 54
    L"KRAFTWERK",                                              // 55
    L"KANALISATION",                                                      // 56
    L"UNTERIRDISCHER KOMPLEX",                              // 57
    L"OBERIRDISCHER KOMPLEX",                                          // 58
    L"KOMPLEX UNTERSTE EBENE",                          // 59
};



#endif

#endif
