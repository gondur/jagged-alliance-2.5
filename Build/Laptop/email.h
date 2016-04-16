#ifndef __EMAIL_H
#define __EMAIL_H

#include "types.h"

// defines
#define MAX_EMAIL_LINES 10 //max number of lines can be shown in a message
#define MAX_MESSAGES_PAGE 18 // max number of messages per page



//JA25:  New emails
// email # 1
#define EMAIL_STARTGAME												0
#define EMAIL_STARTGAME_LENGTH								8

// email # 2
#define EMAIL_PILOTMISSING										(EMAIL_STARTGAME + EMAIL_STARTGAME_LENGTH)		
#define EMAIL_PILOTMISSING_LENGTH							2

// email # 3
#define EMAIL_MAKECONTACT											(EMAIL_PILOTMISSING + EMAIL_PILOTMISSING_LENGTH)	
#define EMAIL_MAKECONTACT_LENGTH							3

// email # 4
#define EMAIL_MANUEL													(EMAIL_MAKECONTACT + EMAIL_MAKECONTACT_LENGTH)
#define EMAIL_MANUEL_LENGTH										4

// # email # 5  - only if Miguel is alive!
#define EMAIL_MIGUELHELLO											(EMAIL_MANUEL + EMAIL_MANUEL_LENGTH)
#define EMAIL_MIGUELHELLO_LENGTH							3

// email # 6 - player not advancing fast enough
#define EMAIL_CONCERNED												(EMAIL_MIGUELHELLO + EMAIL_MIGUELHELLO_LENGTH)
#define EMAIL_CONCERNED_LENGTH								2

// email # 7 - player still not advancing fast enough
#define EMAIL_URGENT													(EMAIL_CONCERNED + EMAIL_CONCERNED_LENGTH)
#define EMAIL_URGENT_LENGTH										3

// email # 8a  - from Miguel
#define EMAIL_MIGUELSORRY											(EMAIL_URGENT + EMAIL_URGENT_LENGTH)
#define EMAIL_MIGUELSORRY_LENGTH							3

// email # 8b  - from Miguel, mentioning Manuel
#define EMAIL_MIGUELMANUEL										(EMAIL_MIGUELSORRY + EMAIL_MIGUELSORRY_LENGTH)
#define EMAIL_MIGUELMANUEL_LENGTH							4

// email # 9 - Miguel sick
#define EMAIL_MIGUELSICK											(EMAIL_MIGUELMANUEL + EMAIL_MIGUELMANUEL_LENGTH)
#define EMAIL_MIGUELSICK_LENGTH								3

// email # 10a
#define EMAIL_UNDERSTANDING										(EMAIL_MIGUELSICK + EMAIL_MIGUELSICK_LENGTH)
#define EMAIL_UNDERSTANDING_LENGTH						3

// email # 10b - if we need extra cash
#define EMAIL_EXTRACASH												(EMAIL_UNDERSTANDING + EMAIL_UNDERSTANDING_LENGTH)
#define EMAIL_EXTRACASH_LENGTH								4

// email # 11
#define EMAIL_PILOTFOUND											(EMAIL_EXTRACASH + EMAIL_EXTRACASH_LENGTH)
#define EMAIL_PILOTFOUND_LENGTH								2

// email # 12a - Miguel dead, Manuel never recruited
#define EMAIL_CONGRATS												(EMAIL_PILOTFOUND + EMAIL_PILOTFOUND_LENGTH)
#define EMAIL_CONGRATS_LENGTH									4

// email # 12b - Miguel alive, Manuel never recruited
#define EMAIL_CONGRATSICK											(EMAIL_CONGRATS + EMAIL_CONGRATS_LENGTH)
#define EMAIL_CONGRATSICK_LENGTH							5

// email # 12c - Miguel alive, Manuel dead
#define EMAIL_CONGRATMIGMANUELDEAD						(EMAIL_CONGRATSICK + EMAIL_CONGRATSICK_LENGTH)
#define EMAIL_CONGRATMIGMANUELDEAD_LENGTH			6

// email # 12d - Miguel alive, Manuel recruited and alive
#define EMAIL_CONGRATMIGMANUELALIVE						(EMAIL_CONGRATMIGMANUELDEAD + EMAIL_CONGRATMIGMANUELDEAD_LENGTH)
#define EMAIL_CONGRATMIGMANUELALIVE_LENGTH		6

// email # 12e - Miguel dead, Manuel dead
#define EMAIL_CONGRATMANUELDEAD								(EMAIL_CONGRATMIGMANUELALIVE + EMAIL_CONGRATMIGMANUELALIVE_LENGTH)
#define EMAIL_CONGRATMANUELDEAD_LENGTH				5

// email # 12f -  Miguel dead, Manuel recruited and alive
#define EMAIL_CONGRATMANUELALIVE							(EMAIL_CONGRATMANUELDEAD + EMAIL_CONGRATMANUELDEAD_LENGTH)
#define EMAIL_CONGRATMANUELALIVE_LENGTH				5

// email # 13 - original AIM email
#define EMAIL_AIMDISCOUNT											(EMAIL_CONGRATMANUELALIVE + EMAIL_CONGRATMANUELALIVE_LENGTH)
#define EMAIL_AIMDISCOUNT_LENGTH							7

#define	MANUEL_AT_HOME_NOT_USED								( EMAIL_AIMDISCOUNT + EMAIL_AIMDISCOUNT_LENGTH )
#define	MANUEL_AT_HOME_NOT_USED_LENGTH				1

//Email #14 Initial IMP email
#define IMP_EMAIL_INTRO												(MANUEL_AT_HOME_NOT_USED + MANUEL_AT_HOME_NOT_USED_LENGTH )
#define IMP_EMAIL_INTRO_LENGTH								10

//Email #15 Imp follow up
#define IMP_EMAIL_AGAIN												(IMP_EMAIL_INTRO + IMP_EMAIL_INTRO_LENGTH)
#define IMP_EMAIL_AGAIN_LENGTH								5



// Email #16 - ??  merc left-me-a-message-and-now-I'm-back emails
#define	AIM_REPLY_BARRY												( IMP_EMAIL_AGAIN + IMP_EMAIL_AGAIN_LENGTH )
#define	AIM_REPLY_LENGTH_BARRY								2

#define AIM_REPLY_MELTDOWN										(AIM_REPLY_BARRY + ( 39 * AIM_REPLY_LENGTH_BARRY ))
#define AIM_REPLY_LENGTH_MELTDOWN							AIM_REPLY_LENGTH_BARRY


#define	AIM_REFUND														( AIM_REPLY_MELTDOWN + AIM_REPLY_LENGTH_MELTDOWN )
#define	AIM_REFUND_LENGTH											3

#define	MERC_REFUND														( AIM_REFUND + AIM_REFUND_LENGTH )
#define	MERC_REFUND_LENGTH										3



#define	EMAIL_AIM_PROMOTION_1										( MERC_REFUND + MERC_REFUND_LENGTH )
#define	EMAIL_AIM_PROMOTION_1_LENGTH						4

#define	EMAIL_MERC_PROMOTION_1									( EMAIL_AIM_PROMOTION_1 + EMAIL_AIM_PROMOTION_1_LENGTH )
#define	EMAIL_MERC_PROMOTION_1_LENGTH						5

#define	EMAIL_AIM_PROMOTION_2										( EMAIL_MERC_PROMOTION_1 + EMAIL_MERC_PROMOTION_1_LENGTH )
#define	EMAIL_AIM_PROMOTION_2_LENGTH						5


#define IMP_EMAIL_PROFILE_RESULTS								( EMAIL_AIM_PROMOTION_2 + EMAIL_AIM_PROMOTION_2_LENGTH )
#define IMP_EMAIL_PROFILE_RESULTS_LENGTH				1












/*

///////////////////////////////////////////////////////////////////////////////////
//
// OLD EMAILS
//
///////////////////////////////////////////////////////////////////////////////////

/*
#define IMP_EMAIL_INTRO					0
#define IMP_EMAIL_INTRO_LENGTH	10
* /
#define ENRICO_CONGRATS					(IMP_EMAIL_INTRO + IMP_EMAIL_INTRO_LENGTH)					
#define ENRICO_CONGRATS_LENGTH	3
/*
#define IMP_EMAIL_AGAIN					(ENRICO_CONGRATS + ENRICO_CONGRATS_LENGTH)
#define IMP_EMAIL_AGAIN_LENGTH	6
* /
#define MERC_INTRO              (IMP_EMAIL_AGAIN + IMP_EMAIL_AGAIN_LENGTH)
#define MERC_INTRO_LENGTH       5
#define MERC_NEW_SITE_ADDRESS   ( MERC_INTRO + MERC_INTRO_LENGTH )
#define MERC_NEW_SITE_ADDRESS_LENGTH 2
#define AIM_MEDICAL_DEPOSIT_REFUND ( MERC_NEW_SITE_ADDRESS + MERC_NEW_SITE_ADDRESS_LENGTH )
#define AIM_MEDICAL_DEPOSIT_REFUND_LENGTH 3
#define IMP_EMAIL_PROFILE_RESULTS ( AIM_MEDICAL_DEPOSIT_REFUND + AIM_MEDICAL_DEPOSIT_REFUND_LENGTH )
#define IMP_EMAIL_PROFILE_RESULTS_LENGTH 1
#define	MERC_WARNING							( IMP_EMAIL_PROFILE_RESULTS_LENGTH + IMP_EMAIL_PROFILE_RESULTS )
#define	MERC_WARNING_LENGTH				2
#define MERC_INVALID							( MERC_WARNING + MERC_WARNING_LENGTH )
#define MERC_INVALID_LENGTH				2							
#define	NEW_MERCS_AT_MERC					( MERC_INVALID + MERC_INVALID_LENGTH )
#define	NEW_MERCS_AT_MERC_LENGTH	2
#define	MERC_FIRST_WARNING				( NEW_MERCS_AT_MERC + NEW_MERCS_AT_MERC_LENGTH )
#define	MERC_FIRST_WARNING_LENGTH	2
// merc up a level emails
#define	MERC_UP_LEVEL_BIFF				( MERC_FIRST_WARNING + MERC_FIRST_WARNING_LENGTH )
#define	MERC_UP_LEVEL_LENGTH_BIFF	2
#define	MERC_UP_LEVEL_HAYWIRE				( MERC_UP_LEVEL_LENGTH_BIFF + MERC_UP_LEVEL_BIFF )
#define	MERC_UP_LEVEL_LENGTH_HAYWIRE	2
#define	MERC_UP_LEVEL_GASKET				( MERC_UP_LEVEL_LENGTH_HAYWIRE + MERC_UP_LEVEL_HAYWIRE )
#define	MERC_UP_LEVEL_LENGTH_GASKET	2
#define	MERC_UP_LEVEL_RAZOR				( MERC_UP_LEVEL_LENGTH_GASKET + MERC_UP_LEVEL_GASKET )
#define	MERC_UP_LEVEL_LENGTH_RAZOR	2
#define	MERC_UP_LEVEL_FLO				( MERC_UP_LEVEL_LENGTH_RAZOR + MERC_UP_LEVEL_RAZOR )
#define	MERC_UP_LEVEL_LENGTH_FLO	2
#define	MERC_UP_LEVEL_GUMPY				( MERC_UP_LEVEL_LENGTH_FLO + MERC_UP_LEVEL_FLO )
#define	MERC_UP_LEVEL_LENGTH_GUMPY	2
#define	MERC_UP_LEVEL_LARRY				( MERC_UP_LEVEL_LENGTH_GUMPY + MERC_UP_LEVEL_GUMPY )
#define	MERC_UP_LEVEL_LENGTH_LARRY	2
#define	MERC_UP_LEVEL_COUGAR				( MERC_UP_LEVEL_LENGTH_LARRY + MERC_UP_LEVEL_LARRY )
#define	MERC_UP_LEVEL_LENGTH_COUGAR	2
#define	MERC_UP_LEVEL_NUMB				( MERC_UP_LEVEL_LENGTH_COUGAR + MERC_UP_LEVEL_COUGAR )
#define	MERC_UP_LEVEL_LENGTH_NUMB	2
#define	MERC_UP_LEVEL_BUBBA				( MERC_UP_LEVEL_LENGTH_NUMB + MERC_UP_LEVEL_NUMB )
#define	MERC_UP_LEVEL_LENGTH_BUBBA		2

/*
// merc left-me-a-message-and-now-I'm-back emails
#define	AIM_REPLY_BARRY				( MERC_UP_LEVEL_LENGTH_BUBBA + MERC_UP_LEVEL_BUBBA )
#define	AIM_REPLY_LENGTH_BARRY		2
#define AIM_REPLY_MELTDOWN		(AIM_REPLY_BARRY + ( 39 * AIM_REPLY_LENGTH_BARRY ))
#define AIM_REPLY_LENGTH_MELTDOWN		AIM_REPLY_LENGTH_BARRY
* /

// old EXISTING emails when player starts game. They must look "read"
#define OLD_ENRICO_1					( AIM_REPLY_LENGTH_MELTDOWN + AIM_REPLY_MELTDOWN )
#define OLD_ENRICO_1_LENGTH		3
#define OLD_ENRICO_2					( OLD_ENRICO_1 + OLD_ENRICO_1_LENGTH )
#define OLD_ENRICO_2_LENGTH		3
#define RIS_REPORT						( OLD_ENRICO_2 + OLD_ENRICO_2_LENGTH )
#define RIS_REPORT_LENGTH			2
#define OLD_ENRICO_3					( RIS_REPORT + RIS_REPORT_LENGTH )
#define OLD_ENRICO_3_LENGTH		3

// emails that occur from Enrico once player accomplishes things
#define ENRICO_MIGUEL					( OLD_ENRICO_3 + OLD_ENRICO_3_LENGTH )
#define ENRICO_MIGUEL_LENGTH	3
#define ENRICO_PROG_20				( ENRICO_MIGUEL + ENRICO_MIGUEL_LENGTH )
#define ENRICO_PROG_20_LENGTH	3
#define ENRICO_PROG_55				( ENRICO_PROG_20 + ENRICO_PROG_20_LENGTH )
#define ENRICO_PROG_55_LENGTH	3
#define ENRICO_PROG_80				( ENRICO_PROG_55 + ENRICO_PROG_55_LENGTH )
#define ENRICO_PROG_80_LENGTH	3
#define ENRICO_SETBACK				( ENRICO_PROG_80 + ENRICO_PROG_80_LENGTH )
#define ENRICO_SETBACK_LENGTH	3
#define ENRICO_SETBACK_2			( ENRICO_SETBACK + ENRICO_SETBACK_LENGTH )
#define ENRICO_SETBACK_2_LENGTH	3
#define ENRICO_CREATURES			( ENRICO_SETBACK_2 + ENRICO_SETBACK_2_LENGTH )
#define ENRICO_CREATURES_LENGTH	3

// insurance company emails
#define INSUR_PAYMENT					( ENRICO_CREATURES + ENRICO_CREATURES_LENGTH )
#define INSUR_PAYMENT_LENGTH	3
#define INSUR_SUSPIC					( INSUR_PAYMENT + INSUR_PAYMENT_LENGTH )
#define INSUR_SUSPIC_LENGTH		3
#define INSUR_INVEST_OVER			( INSUR_SUSPIC + INSUR_SUSPIC_LENGTH )
#define INSUR_INVEST_OVER_LENGTH	3
#define INSUR_SUSPIC_2				( INSUR_INVEST_OVER + INSUR_INVEST_OVER_LENGTH )
#define INSUR_SUSPIC_2_LENGTH		3

#define	BOBBYR_NOW_OPEN					( INSUR_SUSPIC_2 + INSUR_SUSPIC_2_LENGTH )
#define BOBBYR_NOW_OPEN_LENGTH	3

#define KING_PIN_LETTER					( BOBBYR_NOW_OPEN + BOBBYR_NOW_OPEN_LENGTH )
#define KING_PIN_LETTER_LENGTH 4

#define	LACK_PLAYER_PROGRESS_1	( KING_PIN_LETTER + KING_PIN_LETTER_LENGTH )
#define	LACK_PLAYER_PROGRESS_1_LENGTH	3

#define	LACK_PLAYER_PROGRESS_2	( LACK_PLAYER_PROGRESS_1 + LACK_PLAYER_PROGRESS_1_LENGTH )
#define	LACK_PLAYER_PROGRESS_2_LENGTH	3

#define	LACK_PLAYER_PROGRESS_3	( LACK_PLAYER_PROGRESS_2 + LACK_PLAYER_PROGRESS_2_LENGTH )
#define	LACK_PLAYER_PROGRESS_3_LENGTH	3

//A package from bobby r has arrived in Drassen
#define	BOBBYR_SHIPMENT_ARRIVED	( LACK_PLAYER_PROGRESS_3 + LACK_PLAYER_PROGRESS_3_LENGTH )
#define	BOBBYR_SHIPMENT_ARRIVED_LENGTH	4

// John Kulba has left the gifts for theplayers in drassen
#define	JOHN_KULBA_GIFT_IN_DRASSEN	( BOBBYR_SHIPMENT_ARRIVED + BOBBYR_SHIPMENT_ARRIVED_LENGTH )
#define	JOHN_KULBA_GIFT_IN_DRASSEN_LENGTH	4

//when a merc dies on ANOTHER assignment ( ie not with the player )
#define	MERC_DIED_ON_OTHER_ASSIGNMENT	( JOHN_KULBA_GIFT_IN_DRASSEN + JOHN_KULBA_GIFT_IN_DRASSEN_LENGTH )
#define	MERC_DIED_ON_OTHER_ASSIGNMENT_LENGTH	5

#define INSUR_1HOUR_FRAUD ( MERC_DIED_ON_OTHER_ASSIGNMENT + MERC_DIED_ON_OTHER_ASSIGNMENT_LENGTH )
#define INSUR_1HOUR_FRAUD_LENGTH 3

//when a merc is fired, and is injured
#define AIM_MEDICAL_DEPOSIT_PARTIAL_REFUND ( INSUR_1HOUR_FRAUD + INSUR_1HOUR_FRAUD_LENGTH )
#define AIM_MEDICAL_DEPOSIT_PARTIAL_REFUND_LENGTH 3

//when a merc is fired, and is dead
#define AIM_MEDICAL_DEPOSIT_NO_REFUND ( AIM_MEDICAL_DEPOSIT_PARTIAL_REFUND + AIM_MEDICAL_DEPOSIT_PARTIAL_REFUND_LENGTH )
#define AIM_MEDICAL_DEPOSIT_NO_REFUND_LENGTH 3

#define	BOBBY_R_MEDUNA_SHIPMENT				( AIM_MEDICAL_DEPOSIT_NO_REFUND + AIM_MEDICAL_DEPOSIT_NO_REFUND_LENGTH )
#define	BOBBY_R_MEDUNA_SHIPMENT_LENGTH				4

*/


struct message{
	STR16 pString;
	struct message *Next;
	struct message *Prev;
};

typedef struct message EmailMessage;
typedef EmailMessage *MessagePtr;


struct email
{
	STR16		pSubject;
	UINT16	usOffset;
	UINT16	usLength;
	UINT8		ubSender;
	UINT32	iDate;
	INT32		iId;
	INT32		iFirstData;
	UINT32	uiSecondData;
	BOOLEAN fRead;
	BOOLEAN fNew;

	INT32		iThirdData;
	INT32		iFourthData;
	UINT32	uiFifthData;
	UINT32	uiSixData;

	struct	email *Next;
	struct	email *Prev;
};

typedef struct email Email;
typedef Email *EmailPtr;


// This used when saving the emails to disk.
typedef struct 
{
	UINT16	usOffset;
	UINT16	usLength;
	UINT8		ubSender;
	UINT32	iDate;
	INT32		iId;
	INT32		iFirstData;
	UINT32	uiSecondData;

	INT32		iThirdData;
	INT32		iFourthData;
	UINT32	uiFifthData;
	UINT32	uiSixData;

	BOOLEAN fRead;
	BOOLEAN fNew;
} SavedEmailStruct;



struct pagemessages{
	INT32 iIds[MAX_MESSAGES_PAGE];
	INT32 iPageId;
	struct pagemessages *Next;
	struct pagemessages *Prev;
};


typedef struct pagemessages Page;
typedef Page *PagePtr;

struct messagerecord{
//  CHAR16 pRecord[ 320 ];
  CHAR16 pRecord[ 640 ];
	struct messagerecord *Next;
};

typedef struct messagerecord Record;
typedef Record *RecordPtr;

typedef struct
{
	RecordPtr pFirstRecord;
	RecordPtr pLastRecord;
	INT32 iPageNumber;
} EmailPageInfoStruct;

enum {
	SENDER=0,
	RECEIVED,
  SUBJECT,
	READ,
};

enum {
	MAIL_ENRICO=0,
	CHAR_PROFILE_SITE,
	GAME_HELP,
	IMP_PROFILE_RESULTS,
	SPECK_FROM_MERC,
	RIS_EMAIL,
	BARRY_MAIL,
	MELTDOWN_MAIL = BARRY_MAIL+ 39,
	INSURANCE_COMPANY,
	BOBBY_R,
	KING_PIN,
	JOHN_KULBA,
	AIM_SITE,
	MAIL_MIGUEL,
};

// the length of the subject in char
#define EMAIL_SUBJECT_LENGTH 128

extern BOOLEAN fUnReadMailFlag;
extern BOOLEAN fNewMailFlag;
extern BOOLEAN  fOldUnreadFlag;
extern BOOLEAN  fOldNewMailFlag;
extern BOOLEAN fDeleteMailFlag;
extern BOOLEAN fDisplayMessageFlag;
extern BOOLEAN fReDrawNewMailFlag; 
extern BOOLEAN fOpenMostRecentUnReadFlag;
extern EmailPtr pEmailList; 
extern UINT32 guiEmailWarning;


void GameInitEmail();
BOOLEAN EnterEmail();
void ExitEmail();
void HandleEmail();
void RenderEmail();

#define CHECK_X 15
#define CHECK_Y 13
#define VIEWER_X 155
#define VIEWER_Y 70 + 21
#define MAIL_STRING_SIZE 640


// message manipulation
void AddEmailMessage(INT32 iMessageOffset, INT32 iMessageLength,STR16 pSubject, INT32 iDate, UINT8 ubSender, BOOLEAN fAlreadyRead, INT32 uiFirstData, UINT32 uiSecondData );
void RemoveEmailMessage(INT32 iId);
EmailPtr GetEmailMessage(INT32 iId);
void LookForUnread();
void AddEmail(INT32 iMessageOffset, INT32 iMessageLength, UINT8 ubSender, INT32 iDate);
void AddPreReadEmail(INT32 iMessageOffset, INT32 iMessageLength, UINT8 ubSender, INT32 iDate);
BOOLEAN DisplayNewMailBox();
void CreateDestroyNewMailButton();
void CreateDestroyDeleteNoticeMailButton();
void AddDeleteRegionsToMessageRegion();
void DisplayEmailHeaders( void );
void ReDrawNewMailBox( void );
void ReDisplayBoxes( void );
void ShutDownEmailList();
void AddMessageToPages(INT32 iMessageId);
void AddEmailWithSpecialData(INT32 iMessageOffset, INT32 iMessageLength, UINT8 ubSender, INT32 iDate, INT32 iFirstData, UINT32 uiSecondData );

#ifdef JA2BETAVERSION
	void AddAllEmails();
#endif

#endif