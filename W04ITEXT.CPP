//--------------------------------------------------------------------------
//  Project      : ALL PROGECTS
//  File Name    : W04ITEXT.CPP
//  Written by   : GABRIELA OPRESCU
//  Created      : 27.10.1994
//  Updated      : 02.05.1995
//--------------------------------------------------------------------------
//  Dest. System : WINDOWS
//--------------------------------------------------------------------------
//  Libraries    : OWL 2.0
//--------------------------------------------------------------------------
//  Data Files   :
//--------------------------------------------------------------------------
//  Remarks      : DEFINES A NEW TEXT INPUT CLASS
//--------------------------------------------------------------------------
//  1994, 1995 by FUTURA Software s.r.l.
//--------------------------------------------------------------------------

//#pragma hdrignore SECTION
#include <owl\owlpch.h>
#include <owl\validate.h>
#include <owl\statusba.h>
#include <owl\edit.h>
#include <owl\gdiobjec.h>

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#pragma hdrstop

//#define Uses_TTextInput

#include "w04itext.h"

#define CONTROL_Y  25
#define TT_KEYUP  26

#if !defined(SECTION) || SECTION == 1
TTextInput* TTextInput::ValidatorReFocus = 0;
//extern far TStatusBar* statusBar;

DEFINE_RESPONSE_TABLE1(TTextInput, TEdit)
  EV_WM_CHAR,
  EV_WM_KEYDOWN,
  EV_WM_LBUTTONDOWN,
  EV_WM_GETDLGCODE,
  EV_WM_KILLFOCUS,
  EV_WM_SETFOCUS,
END_RESPONSE_TABLE;

// constructor for a TTextInput object
// by default, edit control has a border and its text is left-justified
TTextInput::TTextInput(TWindow* parent,
				 int             id,
				 const char far* text,
				 int x, int y, int w, int h,
				 unsigned int gen_flags, // position & exit miGenFlag...
				 unsigned char fill_char, // fills output data up to len
				 unsigned int alpha_flags, // accepted characters miAlphaFlag...
				 unsigned int letter_flags, // conv. attributes miLetterFlag...
				 UINT textLen,
				 UINT font_size,
				 BOOL bold,
				 long min, long max,
				 TTextUserValid valid_user, // user valid function
				 BOOL spatiu ,
				 BOOL multiline,
				 TModule* module )
  : TEdit(parent, id, text, x, y, w, h, textLen, multiline, module)
{
  // undo the styles set by TStatic, & addin edit styles
  Attr.Style &= ~SS_LEFT;
  Attr.Style |= ES_LEFT | WS_BORDER ;
  // improve for new input object
  genFlags = gen_flags;
  alphaFlags = alpha_flags;
  letterFlags = letter_flags;
  sp = spatiu;
  if( letterFlags & miLetterFlagUpp &&
		letterFlags & miLetterFlagLow ) letterFlags &=~miLetterFlagUpp;
  fillChar = fill_char;
  curPos = startSel = endSel = 0;
  min_digit = min;
  max_digit = max;
//  statusBar->SetModeIndicator(TStatusBar::Overtype, FALSE); // insert mode on staus line
  InsCursor = TRUE;
  validUser = valid_user;
  data_buff[0] = 0;
  Validator = 0;
  font = 0;
  fontSize = font_size;
  if(bold) bold_face = FW_BOLD;
  else     bold_face = FW_NORMAL;
  data_buff = new char[TextLen+1];
}

// constructor for TTextInput associated with a MS-Windows interface element
// created by MS-Windows from a resource definition
// by default, data transfer is enabled
TTextInput::TTextInput(TWindow*   parent,
				 int        resourceId,
				 unsigned int gen_flags, // position & exit miGenFlag...
				 unsigned char fill_char, // fills output data up to len
				 unsigned int alpha_flags, // accepted characters miAlphaFlag...
				 unsigned int letter_flags, // conv. attributes miLetterFlag...
				 UINT textLen,
				 UINT font_size,
				 BOOL bold,
				 long min, long max,
				 TTextUserValid valid_user, // user valid function
				 BOOL spatiu ,
				 TModule*   module)
  : TEdit(parent, resourceId, textLen, module)
{
  // improve for new input object
  genFlags = gen_flags;
  alphaFlags = alpha_flags;
  letterFlags = letter_flags;
  sp = spatiu;
  if( letterFlags & miLetterFlagUpp &&
		letterFlags & miLetterFlagLow ) letterFlags &=~miLetterFlagUpp;
  fillChar = fill_char;
  curPos = startSel = endSel = 0;
  min_digit = min;
  max_digit = max;
//  statusBar->SetModeIndicator(TStatusBar::Overtype, FALSE); // insert mode on staus line
  InsCursor = TRUE;
//  memset(data_buff,'\0', 80);
  Validator = 0;
  data_buff = new char[TextLen+1];
  font = 0;
  fontSize = font_size;
  if(bold) bold_face = FW_BOLD;
  else     bold_face = FW_NORMAL;
  EnableTransfer();
  validUser = valid_user;
}

TTextInput::~TTextInput()
{
	 delete[] data_buff;
	 delete font;
}

void TTextInput::setValidUser(TTextUserValid valid_func)
{
  validUser = valid_func;
}

// rejectChar function
void TTextInput::rejectChar()
{
  MessageBeep(MB_ICONEXCLAMATION);
}

// TTextInput acceptChar
void TTextInput::acceptChar(UINT& key)
{
 int oldBuffLen = GetTextLen();

	  if( !InsCursor && (curPos+1) <= oldBuffLen)   // overtype mode
			strcpy( data_buff+startSel, data_buff+endSel+1);
	  if( oldBuffLen < TextLen-1 )
	  {
		  memmove( data_buff + curPos + 1, data_buff + curPos,
					  strlen(data_buff + curPos)+1 );
		  if(curPos && data_buff[curPos-1]==' ' && key == ' ' &&
				letterFlags & miLetterFlagCutSpace)
						return; // cut trailing space
													 // ext. key à - ü
		  if( key >= 'a' && key <= 'z' || key >= 224 && key <= 253)
		  {if( letterFlags & miLetterFlagEveryFirst ||
				 (!curPos && letterFlags & miLetterFlagFirstUp))
			  {
				if(!curPos || data_buff[curPos-1] == ' ' ) // insert mode
					key -= 32;
				if(data_buff[curPos+1]) // ins. on first pos. if string not null
				 if(data_buff[curPos+1] <= 'Z' && data_buff[curPos+1] >= 'A' ||
					  data_buff[curPos+1] <= (char)221 && // ext.ascii
					  data_buff[curPos+1] >= (char)192 )
							  data_buff[curPos+1] += 32; // uppercase->lowercase
			  }
			if(letterFlags & miLetterFlagUpp) key -= 32;
		  }
		  else
		  if( key >= 'A' && key <= 'Z' || key >= 192 && key <= 221)
		  {  if(curPos && data_buff[curPos-1] != ' ' &&
				 letterFlags & miLetterFlagEveryFirst ||
				 curPos && letterFlags & miLetterFlagFirstUp ||
				 letterFlags & miLetterFlagLow)
						  key+=32;
			  if((!curPos || data_buff[curPos-1] == ' ') &&
					letterFlags & miLetterFlagEveryFirst ||
					(!curPos && letterFlags & miLetterFlagFirstUp) )
				 if(data_buff[curPos+1] <= 'Z' && data_buff[curPos+1] >= 'A' ||
					  data_buff[curPos+1] <= (char)221 && // ext.ascii
					  data_buff[curPos+1] >= (char)192 )
							  data_buff[curPos+1] += 32; // uppercase->lowercase
		  }
		  else
		  if( key == ' ')
		  {  if(( data_buff[curPos+1] >= 'a' && data_buff[curPos+1] <= 'z' ||
					 data_buff[curPos+1] >= (char)224 &&
					 data_buff[curPos+1] <= (char)253 )&&
					(letterFlags & miLetterFlagEveryFirst||
					 letterFlags & miLetterFlagUpp ))
						data_buff[curPos+1] -= 32; // lowercase -> uppercase
		  }
		  data_buff[curPos++] = key;
		  endSel = startSel = curPos;
	  }
}

int TTextInput::keyFilter(UINT& key)
{
  int flag_ign = 0;
  if(key < ' ')
  {  // extended key  not allowed
	 if( !(alphaFlags & miAlphaFlagExt) || !key)  flag_ign--;
  }
  else
	if(key == ' ' )
	 if( alphaFlags & miAlphaFlagSpace)
	 {
	  if(sp) //  check space at the beginning of the input
	  {
		if(InsCursor)
		{
		 if(letterFlags & miLetterFlagCutSpace)
		  if(data_buff[curPos])
		  {
			if(data_buff[curPos-1] == ' ' || data_buff[curPos+1] == ' ')
						  flag_ign++;
		  }
		}
		else if( !startSel)
				{if(endSel || (letterFlags & miLetterFlagCutSpace &&
					  (data_buff[curPos] == ' ' ||
					  (curPos && data_buff[curPos-1] == ' '))))
										  flag_ign++;
				}
				else if((data_buff[startSel-1] == ' ' ||
							data_buff[endSel] == ' ') &&
							letterFlags & miLetterFlagCutSpace)
											  flag_ign++;
	  } // end if(sp)
	  else if(!curPos )  // space on first pos no allowed
				  flag_ign--;
	 } // end if( alphaFlags & miAlphaFlagSpace)
	 else flag_ign++; // space no allowed
	// end if(key == ' ')
	else // if key > ' '
	 if(key < '0')
	 {  if( !(alphaFlags & miAlphaFlagSign))
			flag_ign--;
	 }
	 else
	  if(key <= '9')
	  {if( !(alphaFlags & miAlphaFlagNumber))
			 flag_ign--;
	  }
	  else
		if(key < 'A')
		{if( !(alphaFlags & miAlphaFlagSign))
			  flag_ign--;
		}
		else
		 if(key <= 'Z')
		 { if(!(alphaFlags & miAlphaFlagAlpha))
				flag_ign--;
		 }
		 else
		  if(key < 'a')
		  {if(!(alphaFlags & miAlphaFlagSign))
			  flag_ign--;
		  }
		  else
			if(key <= 'z' )
			{
			 if(!(alphaFlags & miAlphaFlagAlpha))
					 flag_ign--;
			}
			else
				if(key < 127)
				{
				 if(!(alphaFlags & miAlphaFlagSign))
					  flag_ign--;
				}
				else
				{
				 if(!(alphaFlags & miAlphaFlagExt))
					  flag_ign--;
				}
  return(flag_ign);
}


// TTextInput deleteSelect
void  TTextInput::deleteSelect()
{
  if( startSel < endSel )
  {
	if( startSel)
	 if( data_buff[startSel-1] == ' ')
	 {
		if ( data_buff[endSel])
		 if( letterFlags & miLetterFlagEveryFirst)
		 {
			if((data_buff[endSel] >= 'a' && data_buff[endSel] <= 'z') ||
				(data_buff[endSel] >= (char)224 &&
				 data_buff[endSel] <= (char)253))
						  data_buff[endSel] -= 32;
		 }
	 }
	 else
	 {
		if((data_buff[endSel] != ' ' && letterFlags & miLetterFlagLow) ||
			(data_buff[endSel-1] = ' ' && letterFlags & miLetterFlagEveryFirst))
			 if((data_buff[endSel] >= 'A' && data_buff[endSel] <= 'Z') ||
			  (data_buff[endSel] >= (char)192 &&
				data_buff[endSel] <= (char)221))
						  data_buff[endSel] += 32;
	 }
	else
	{
	  if ( data_buff[endSel] == ' ' )
	  while( data_buff[endSel] == ' ') endSel++;
	  if( letterFlags & miLetterFlagEveryFirst ||
			  letterFlags & miLetterFlagFirstUp)
	  {
		 if((data_buff[endSel] >= 'a' && data_buff[endSel] <= 'z') ||
			 (data_buff[endSel] >= (char)224 &&
			  data_buff[endSel] <= (char)253))
					data_buff[endSel] -= 32;
	  }
	 }
	 strcpy( data_buff + startSel, data_buff + endSel);
	}
}

// TTextInput validExit
BOOL TTextInput::validExit()
{
  BOOL flag = TRUE;   //flag TRUE : input ok
  int dataLen = GetTextLen(); // get the length input data
  char  str[80];
  GetText(str, 80);
  // test if empty field  is allowed
  if( letterFlags &  miLetterFlagEmptyField &&  !dataLen)
		 flag =FALSE; // error
  //  range validation
  if( alphaFlags & miAlphaFlagNumber && min_digit != max_digit && str)
  {
	  long test_range = atol(str);
	  if(!(test_range >= min_digit &&  test_range <= max_digit))
		  flag = FALSE; // digit out of the range -> error
  }
  if(flag && validUser) flag = !validUser(this);
  return flag;
}

void TTextInput::EvLButtonDown(UINT modKeys, TPoint &point)
{ // updating the cursor current pos. according with the mouse click pos.
  int bufflen  = GetTextLen(); // no. of string chars
  TEdit::EvLButtonDown(modKeys, point);

  curPos = (point.x)/fontSize; // it is used new courier 10 pixels/char font
  if(curPos > bufflen)
		 curPos = bufflen;
  startSel = endSel = curPos;

  SetSelection(startSel, endSel);
}

// handling an already (blue) selected string
BOOL TTextInput::End_Sel()
{
  UINT sSel, eSel;
  GetSelection(sSel, eSel);
  if(sSel != eSel)// fix the cursor at the end of the existing string
  { startSel = endSel = curPos = eSel;
	 SetSelection(startSel, endSel);
	 return TRUE;
  }
  return FALSE;
}

// Responds to the GetDlgCode query according to the
// current state of the control.  If the edit control
// contains valid input, then TABs are allowed for
// changing focus.  Otherwise, requests that TABs be
// sent to Self, where we will generate the Invalid
// message (See WMKeyDown below).
UINT TTextInput::EvGetDlgCode(MSG far* msg)
{ // transform the ENTER and DOWN keys in TAB
  if(msg && (msg->wParam == VK_RETURN || msg->wParam == VK_DOWN))
  {
	  Parent->SendNotification(Attr.Id, CT_INPUT_RETURN, HWindow);
	  msg->wParam = VK_TAB;
  }
  UINT retVal = (UINT)TEdit::EvGetDlgCode(msg);
  if(!IsValid(FALSE))
	 retVal |= DLGC_WANTTAB;
  return retVal;
}

// Validates Self whenever a character is entered.  Allows
// the character entry to be processed normally, then validates
// the result and restores Self's text to its original state
// if there is an incorrect entry.
//
// By default, the SupressFill parameter of the IsValidInput
// method call to the Validator is set to False, so that it
// is free to modify the string, if it is so configured.
//
void TTextInput::EvChar(UINT key, UINT repeatCount, UINT flags)
{
  char far* olddata_buff = LockBuffer(TextLen);  // load olddata_buff
  strcpy(data_buff, olddata_buff); // init data_buff

	{ // the selected text will be deleted if we want to change it
	 UINT sSel, eSel;
	 GetSelection(sSel, eSel);
	 if(sSel < eSel && !sSel && (key != VK_LEFT || key != VK_RIGHT))
	 { Clear();
		olddata_buff[0] = data_buff[0] = '\0';
		startSel = endSel = curPos = 0;
	 }
	}

	if(key == VK_BACK) // delete the first char behind the cursor
	{
		if(curPos > 0)
		{
		  startSel--;
		  deleteSelect();
		  endSel = --curPos;
		  strcpy(olddata_buff, data_buff);
		}
	  UnlockBuffer(olddata_buff, TRUE);
	  SetSelection(startSel, endSel);
     Parent->SendNotification(Attr.Id, CT_INPUT, HWindow);
	  return;
	}
	if( key == CONTROL_Y) // delete whole the input
	{
		Clear();
		curPos = startSel = endSel = 0;
		olddata_buff[0] = data_buff[0] = '\0';
		UnlockBuffer(olddata_buff);
		return;
	}

  if(!keyFilter(key) && key != VK_TAB) // filter the char
  {
	  acceptChar(key); // accept & convert the new char as needed
	  strcpy(olddata_buff, data_buff);  // update olddata_buff
  }

  TEdit::EvChar(key, repeatCount, flags); // Process the new char...
  UnlockBuffer(olddata_buff, TRUE);  // free olddata_buff
  SetSelection(startSel, endSel);
  Parent->SendNotification(Attr.Id, CT_INPUT, HWindow);
}

// If the TAB key is sent to the Edit Control, check
// the validity before allowing the focus to change.
// The control will only get a TAB if WMGetDlgCode(above)
// allows it, which is done when the control contains
// invalid input (we re-validate here just for completeness,
// in case descendants redefine any of this behavior).
//
// We need to validate on TAB focus-changes because there
// is a case not handled by WMKillFocus: when focus is
// lost to an OK or CANCEL button by tabbing.
void
TTextInput::EvKeyDown(UINT key, UINT repeatCount, UINT flags)
{
  int buffLen = GetTextLen();
  switch( key )
  {
	case VK_LEFT:
	  if(!End_Sel())
		 if(curPos)
		 {	endSel = startSel = --curPos;
			SetSelection(startSel, endSel);}
	  return;
	case VK_RIGHT:
	  if(!End_Sel())
		 if(curPos < buffLen)
		 {	startSel = endSel = ++curPos;
	      SetSelection(startSel, endSel);}
	  return;
	case VK_ESCAPE: return;
	case VK_INSERT:
	  if(InsCursor) // insert mode -> overtype
	  {
//		 statusBar->SetModeIndicator(TStatusBar::Overtype, TRUE);
		 InsCursor = FALSE;
	  }
	  else  // overtype mode -> insert
	  {
//		 statusBar->SetModeIndicator(TStatusBar::Overtype, FALSE);
		 InsCursor = TRUE;
	  }
	  break;
	case VK_HOME:
		startSel = endSel = curPos = 0;
		SetSelection(startSel, endSel);
		return;
	case VK_END:
		startSel = endSel = curPos = buffLen;
		SetSelection(startSel, endSel);
		return;
	 case VK_DELETE:
		 if(startSel == endSel && curPos < buffLen)
		 {
			endSel++;
			char far* olddata_buff = LockBuffer();
			strcpy(data_buff, olddata_buff);
			deleteSelect();
			strcpy(olddata_buff, data_buff);
			UnlockBuffer(olddata_buff, TRUE);
			endSel--;
			SetSelection(startSel, endSel);
			Parent->SendNotification(Attr.Id, CT_INPUT, HWindow);
			return;
		 }
		 break;
  } // end switch key

  if( key == VK_TAB && !IsValid(TRUE) )
  {  rejectChar();
	  return;
  }

  if(key == VK_TAB) TEdit::EvKeyDown(key, repeatCount, flags);

  DefaultProcessing();
}

void TTextInput::EvSetFocus(HWND hWndLostFocus)
{
  TEdit::EvSetFocus(hWndLostFocus);
  Parent->SendNotification(Attr.Id, CT_INPUT_FOCUS, HWindow);
}

void TTextInput::EvKillFocus(HWND hWndGainFocus)
{
  TEdit::EvKillFocus(hWndGainFocus);
  Parent->SendNotification(Attr.Id, CT_INPUT_TAB, HWindow);
}

BOOL TTextInput::CanClose()
{
  UINT id = :: GetDlgCtrlID(GetFocus());
  if(IDOK == id )
  {
	 BOOL okToClose = TEdit::CanClose();
	 if(okToClose)
	  if( IsWindowEnabled() && !IsValid(TRUE))// || !validExit()) )
	  { rejectChar();
		 ValidatorReFocus = this;
		 SetFocus();
		 return FALSE; // input invalid, keep the focus on the same input
	  }
	 return okToClose; // input ok, go to next
  }
  return FALSE; // ENTER was pressed on input; see EvGetDlgCode(MSG *msg)
}


// Return name of predefined Windows edit class
char far*
TTextInput::GetClassName()
{
  return "TEXTINPUT";
}

// limits the amount of text that an edit control can have to the value of
// TextLen  & sets the text font for input object.
void TTextInput::SetupWindow()
{
  TEdit::SetupWindow();

  if (TextLen != 0)
	 HandleMessage(EM_LIMITTEXT, TextLen - 1);
  // create a special font for the input object
  delete font;
  font = new  TFont("Courier New",              //FW_BOLD, FW_NORMAL
						  fontSize*2, fontSize, 0, 0, bold_face, 
						  FIXED_PITCH | FF_MODERN,
						  FALSE, FALSE, FALSE,
						  ANSI_CHARSET,
						  OUT_CHARACTER_PRECIS,
						  CLIP_DEFAULT_PRECIS,
						  PROOF_QUALITY);
  SetWindowFont(*font, TRUE); // activate the new font
}

BOOL TTextInput::IsValid(BOOL reportError)
{
  if (Validator)
  {
	 char far* buffer = LockBuffer();
	 BOOL valid = reportError ? Validator->Valid(buffer) :
										 Validator->IsValid(buffer);
	 UnlockBuffer(buffer);
	 return (valid && validExit());
  }
  return validExit();
}

void TTextInput::SetValidator(TValidator* validator)
{
  if(Validator)delete Validator;
  Validator = validator;
}

UINT TTextInput::Transfer (void *buffer, TTransferDirection direction)
{
	return( TEdit::Transfer (buffer, direction));
}
#endif
#if !defined(SECTION) || SECTION == 2

IMPLEMENT_STREAMABLE1(TTextInput, TEdit);

// reads an instance of TTextInput from the passed ipstream
void* TTextInput::Streamer::Read(ipstream& is, uint32 /*version*/) const
{
  ReadBaseObject((TEdit*)GetObject(), is);
  is >> GetObject()->Validator >> GetObject()->genFlags
	  >> GetObject()->alphaFlags >> GetObject()->letterFlags
	  >> GetObject()->fillChar;
  return GetObject();
}

// writes the TTextInput to the passed opstream
void TTextInput::Streamer::Write(opstream& os) const
{
  WriteBaseObject((TEdit*)GetObject(), os);
  os << GetObject()->Validator << GetObject()->genFlags
	  << GetObject()->alphaFlags << GetObject()->letterFlags
	  << GetObject()->fillChar;
}
#endif
//------------------------------------------------------------------------
// End of file: W04ITEXT.CPP
//------------------------------------------------------------------------

