
#define UNICODE
#include "types.h"
#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include <windows.h>
#include <stdarg.h>
#include <wchar.h>
#include "sgp.h"
#include "memman.h"
#include "fileman.h"
#include "Font.h"
#include "Debug.h"
#include "vsurface.h"
#include "vsurface_private.h"
#include "DirectX Common.h"
#include <ddraw.h>
#include "winfont.h"
#include "font.h"


INT32 FindFreeWinFont( void );
BOOLEAN gfEnumSucceed = FALSE;



#define         MAX_WIN_FONTS   10

// Private struct not to be exported
// to other modules
typedef struct
{
  HFONT       hFont;  
  COLORVAL    ForeColor;
  COLORVAL    BackColor;

} HWINFONT;


HWINFONT	WinFonts[ MAX_WIN_FONTS ];

void InitWinFonts( )
{
  memset( WinFonts, 0, sizeof( WinFonts ) );
}

void ShutdownWinFonts( )
{

}

INT32 FindFreeWinFont( void )
{
  INT32 iCount;

	for( iCount = 0; iCount < MAX_WIN_FONTS; iCount++ )
  {
		if( WinFonts[ iCount ].hFont == NULL )
    {
			return( iCount );
    }
  }

	return( -1 );
}


HWINFONT *GetWinFont( INT32 iFont )
{
  if ( iFont == -1 )
  {
    return( NULL );
  }

  if ( WinFonts[ iFont ].hFont == NULL )
  {
    return( NULL );
  }
  else
  {
    return( &( WinFonts[ iFont ] ) );
  }
}

INT32 CreateWinFont( INT32 iHeight, INT32 iWidth, INT32 iEscapement,  
                     INT32 iWeight, BOOLEAN fItalic,  BOOLEAN fUnderline,  BOOLEAN fStrikeOut, STR16 pTypeFaceName )
{
  INT32   iFont;
  HFONT   hFont;
  
  // Find free slot
  iFont = FindFreeWinFont( );

  if ( iFont == -1 )
  {
    return( iFont );
  }

  // Create new font...
  hFont = CreateFont( iHeight, iWidth, iEscapement, iWeight, FW_NORMAL, fItalic, fUnderline, fStrikeOut,
                            DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, pTypeFaceName );

  if ( hFont == NULL )
  {
    return( -1 );
  }

  
  // Set font....
  WinFonts[ iFont ].hFont = hFont;

  return( iFont );
}

void  DeleteWinFont( INT32 iFont )
{
  HWINFONT *pWinFont;
  
  pWinFont = GetWinFont( iFont );

  if ( pWinFont != NULL )
  {
    DeleteObject( pWinFont->hFont );
  }
}

  
void SetWinFontForeColor( INT32 iFont, COLORVAL *pColor )
{
  HWINFONT *pWinFont;
  
  pWinFont = GetWinFont( iFont );

  if ( pWinFont != NULL )
  {
    pWinFont->ForeColor = ( *pColor );
  }
}

  
void SetWinFontBackColor( INT32 iFont, COLORVAL *pColor )
{
  HWINFONT *pWinFont;
  
  pWinFont = GetWinFont( iFont );

  if ( pWinFont != NULL )
  {
    pWinFont->BackColor = ( *pColor );
  }
}


void PrintWinFont( UINT32 uiDestBuf, INT32 iFont, INT32 x, INT32 y, UINT16 *pFontString, ...)
{
  va_list                 argptr;
  wchar_t	                string[512];
  HVSURFACE               hVSurface;
  LPDIRECTDRAWSURFACE2    pDDSurface;
  HDC                     hdc;
  RECT                    rc;
  HWINFONT                *pWinFont;
  int                     len;
  SIZE                    RectSize;
  
  pWinFont = GetWinFont( iFont );

  if ( pWinFont == NULL )
  {
    return;
  }

	va_start(argptr, pFontString);       	// Set up variable argument pointer
	len = vswprintf(string, pFontString, argptr);	// process gprintf string (get output str)
	va_end(argptr);

  // Get surface...
  GetVideoSurface( &hVSurface, uiDestBuf );

  pDDSurface = GetVideoSurfaceDDSurface( hVSurface );

  IDirectDrawSurface2_GetDC( pDDSurface, &hdc );

  SelectObject(hdc, pWinFont->hFont );
  SetTextColor( hdc, pWinFont->ForeColor );
  SetBkColor(hdc, pWinFont->BackColor );
  SetBkMode(hdc, TRANSPARENT);

  GetTextExtentPoint32( hdc, string, len, &RectSize );
  SetRect(&rc, x, y, x + RectSize.cx, y + RectSize.cy );
  ExtTextOut( hdc, x, y, ETO_CLIPPED, &rc, string, len, NULL);
  IDirectDrawSurface2_ReleaseDC( pDDSurface, hdc );

}

INT16 WinFontStringPixLength( UINT16 *string, INT32 iFont )
{
  HWINFONT                *pWinFont;
  HDC                     hdc;
  SIZE                    RectSize;
  
  pWinFont = GetWinFont( iFont );

  if ( pWinFont == NULL )
  {
    return( 0 );
  }

  hdc = GetDC(NULL);
  SelectObject(hdc, pWinFont->hFont );
  GetTextExtentPoint32( hdc, string, wcslen(string), &RectSize );
  ReleaseDC(NULL, hdc);
  
  return( (INT16)RectSize.cx );
}


INT16 GetWinFontHeight( UINT16 *string, INT32 iFont )
{
  HWINFONT                *pWinFont;
  HDC                     hdc;
  SIZE                    RectSize;

  pWinFont = GetWinFont( iFont );

  if ( pWinFont == NULL )
  {
    return( 0 );
  }

  hdc = GetDC(NULL);
  SelectObject(hdc, pWinFont->hFont );
  GetTextExtentPoint32( hdc, string, wcslen(string), &RectSize );
  ReleaseDC(NULL, hdc);
  
  return( (INT16)RectSize.cy );
}

UINT32	WinFont_mprintf( INT32 iFont, INT32 x, INT32 y, UINT16 *pFontString, ...)
{
  va_list                 argptr;
  wchar_t	                string[512];

	va_start(argptr, pFontString);       	// Set up variable argument pointer
	vswprintf(string, pFontString, argptr);	// process gprintf string (get output str)
	va_end(argptr);

  PrintWinFont( FontDestBuffer, iFont, x,  y, string );

  return( 1 );
}

int CALLBACK EnumFontFamProc( CONST LOGFONT *lplf,  CONST TEXTMETRIC *lptm,  DWORD dwType, LPARAM lpData )
{
  gfEnumSucceed = TRUE;

  return( TRUE );
}

BOOLEAN DoesWinFontExistOnSystem( STR16 pTypeFaceName )
{
  HDC       hdc;

  hdc = GetDC(NULL);

  gfEnumSucceed = FALSE;
  EnumFonts( hdc, pTypeFaceName, EnumFontFamProc , 0 );

  ReleaseDC(NULL, hdc);

  return( gfEnumSucceed );
}