//--------------------------------------------------------------------------
//  Project      : *.IDE
//  File name    : W03INUMB.cpp
//  Written by   : Mihaela Popescu
//  Created      : 09.12.1994
//  Updated      : 08.06.1995
//--------------------------------------------------------------------------
//  Dest. system : Windows
//--------------------------------------------------------------------------
//  file for the test program - wich handle various types
//  of input fields. In the .CPP file where TNumericInput are
//  used must be defined  Uses_TNumericInput according to specific needs.
//  In the copy of D06MODIN.CPP included in the current project the
//  corresponding  Uses_TNumericInput must be defined. ( conditionated
//  compilation)
//--------------------------------------------------------------------------
//  DATAFILES: NONE
//--------------------------------------------------------------------------
//  1994, 1995 by Futura Software s.r.l.
//--------------------------------------------------------------------------
#include <owl\owlpch.h>
#include <owl\validate.h>
#include <owl\edit.h>
#include <owl\gdiobjec.h>

#include <mem.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#pragma hdrstop

#include "w03inumb.h"

void strscan(char *dest, char *format, char *src);
void dninput (char *dest,  int flags, int nr_dec, int s_leng, char *src);
int fninput (char *dest, int flags, int nr_dec, char *src);
void point(char* str);

const miNumericSign = 1,      // accept number with sign
		miNumericMarkTh = 2,    // mark thousands on exit
		miNumericDecSep = 4,    // decimal point marker is '.'
		miNumericCutTr = 8,     // "12.3400" -> "12.34"
		miNumericNTypeDec = 16, // enter '12345' -> setData '123.45'
		miNumericShEmpty = 32;  // "" -> "0.00"

#if !defined(SECTION) || SECTION == 1
// ======================================================
// Numeric input validator part
//  receive the decimal separator as an unsigned in
//  for 0 decimal separator is ','
//  for 1 decimal separator is '.'
TNumericValidator::TNumericValidator(unsigned int flags,
												 unsigned int nrdec,
												 UINT slen, double d1, double d2,
												 BOOL hasRange/*FALSE*/)
  : TFilterValidator("0-9 +,.-")
{
  n_flags = flags;
  nr_dec = nrdec;
  str_len = slen;
  d_min = min (d1, d2);
  d_max = max (d1, d2);
  has_range = (d_min == d_max) ? hasRange : TRUE;
  dec_sep = (n_flags & miNumericDecSep) ? ',' : '.';
  valid_out = TRUE;
  TValidator::SetOption(voTransfer);
}

void TNumericValidator::Error()
{
  ::MessageBeep (MB_ICONHAND);
  /*
  char* msg = new char[40];
  wsprintf(msg, "%s", "Invalid input.");
  HWND hWin = GetWindow (hWin, GW_OWNER);
  TWindow* w = GetWindowPtr (hWin);
  if (w)

	 w->MessageBox (msg, "NumericInput", MB_ICONEXCLAMATION|MB_OK);
  else
	 ::MessageBox(0, msg, "NumericInput", MB_ICONEXCLAMATION|MB_OK|MB_TASKMODAL);
  delete [] msg;
  */
}
// validate for each digit enterd at once
BOOL TNumericValidator::IsValidInput(char far* s, BOOL )
{
  if (TFilterValidator::IsValidInput(s, TRUE))
  { char *ptr = " ";
	 // don't allows to enter spaces
	 ptr = strpbrk (s, " ");
	 if (ptr)  return FALSE;
	 if (!(n_flags & miNumericSign))
	 { // signflag is OFF: don't accept neither '+' nor '-'
		ptr = strpbrk (s, "+-");
		if (ptr) return FALSE;
	 } else
	 { // signflag is ON: accept sign only once and only on the first position
		ptr = strpbrk (s, "+-");
		// accept only on the fist position
		if (ptr && (ptr-s > 1)) return FALSE;
		if (ptr)
		{  // accept only the first occurence
			ptr ++;
			if (strpbrk (ptr, "+-")) return FALSE;
		}
	 }
	 if (!nr_dec || (nr_dec && (n_flags & miNumericNTypeDec)))
	 { // if no decimals or don't type decimal separator
		// : don't accept neither ',' nor '.'
		if (strpbrk(s, ".,")) return FALSE;
	 } else
	 { // If decimals: accept only the decimal separator and only once
		char dsep[2]; dsep[0] = dec_sep;                     dsep[1] = '\x0';
		char tsep[2]; tsep[0] = (dec_sep == '.' ? ',': '.'); tsep[1] = '\x0';
		// allow only the decimal separator
		ptr = strpbrk(s, tsep);
		if (ptr) return FALSE;
		// accept only an occurence of decimal separator
		long nrdec = 0;
		ptr = strstr(s, dsep);
		if (ptr)
		{ ptr = ptr+1;
		  if (strstr(ptr, dsep)) return FALSE;
		  nrdec = strlen(s) - (ptr - s);
		}
		// accept no more than nr_dec decimals
		if (nrdec > nr_dec) return FALSE;
	 }
	 return TRUE;
  }
  return FALSE;
}

// validate on exit input
BOOL TNumericValidator::IsValid(const char far* s)
{ if (valid_out)
  { BOOL boo = TFilterValidator::IsValid(s);
	 if (boo && has_range)
	 { char *ptr;
		double value = strtod (s, &ptr);
		boo = (value >= d_min && value <= d_max) ? TRUE : FALSE;
	 }
	 return boo;
  }
  return valid_out;
}

// function return TRUE if the modification was made
BOOL TNumericValidator::SetNewRange (double dd, BOOL boo)
{
	if  (boo)  // boo = TRUE  => modify d_max
	  if (dd >= d_min) d_max = dd;
	  else             boo = FALSE; // modification not allowed
	else  // boo = FALSE => modify d_min
		if (dd <= d_max)
		{  d_min = dd;
			boo = TRUE;
		}
	return boo;
}
TNumericInput *TNumericInput::ValidatorReFocus = 0;

// Numeric Input functions definition
DEFINE_RESPONSE_TABLE1 (TNumericInput, TEdit)
  EV_WM_CHAR,
  EV_WM_KEYDOWN,
  EV_WM_GETDLGCODE,
  EV_WM_SETFOCUS,
  EV_WM_KILLFOCUS,
END_RESPONSE_TABLE;

// constructor for a TNumericInput object
// by default, edit control has a border and its text is left-justified
TNumericInput::TNumericInput (TWindow* parent,
				 int             id,
				 const char far* text,
				 int x, int y, int w, int h,
				 unsigned short num_flags, // fills output data up to len
				 unsigned short dec_len,  // number of decimals
				 UINT str_len,  // length of displayed string
				 UINT font_size,
				 double amin, double amax,
				 BOOL hasrange, BOOL multiline, TModule * module)    // range setting for unique value
			  : TEdit (parent, id, text, x, y, w, h, str_len, multiline, module)
{
  // undo the styles set by TStatic, & addin edit styles
  // improve for new input object
  numFlags = num_flags;  // numeric flags
  decLen = dec_len;  // number of decimals
  Validator = 0;
  strLen = str_len;
  EnableTransfer ();
  font = 0;
  fontSize = font_size;
  validUser = 0;
  SetValidator (new TNumericValidator (numFlags, dec_len, str_len,
													 amin, amax, hasrange));
}

// constructor for TNumericInput associated with a MS-Windows interface element
// created by MS-Windows from a resource definition
// by default, data transfer is enabled
TNumericInput::TNumericInput (TWindow*   parent,
				 int        resourceId,
				 unsigned short num_flags, // conv. attributes miLetterFlag...
				 unsigned short dec_len, // number of decimals
				 UINT str_len,  // length of displayed string
				 UINT font_size,
				 double amin, double amax,
				 BOOL hasrange, TModule* module)  // range setting for unique value
  : TEdit (parent, resourceId, str_len, module)
{
  // improve for new input object
  numFlags = num_flags;
  decLen = dec_len;
  strLen = str_len;
  Validator = 0;
  font = 0;
  fontSize = font_size;
  validUser = 0;
  this->SetValidator (new TNumericValidator (numFlags, dec_len, str_len,
													 amin, amax, hasrange));
}
// TnumericInput class destructor
TNumericInput::~TNumericInput ()
{
  delete font;
}

void TNumericInput::setValidUser(TNumericValidUser valid_func)
{
  validUser = valid_func;
}
// Call TNumericValidator functions to modify it's protected member
// Call this function to change current values of range domain so:
BOOL TNumericInput::SetNewRange (double dd, BOOL boo)
{
  TNumericValidator *numValidator =
	 TYPESAFE_DOWNCAST (Validator, TNumericValidator);
  return (numValidator->SetNewRange (dd, boo));
}
// Call this function if you need to change the current value of validOut
void  TNumericInput::SetValidOut (BOOL boo)
{
  TNumericValidator *numValidator =
	 TYPESAFE_DOWNCAST (Validator, TNumericValidator);
  numValidator->SetValidOut (boo);
};
// Call this function if you need to change the current value of HasRange
void  TNumericInput::SetHasRange (BOOL boo)
{
  TNumericValidator *numValidator =
	 TYPESAFE_DOWNCAST (Validator, TNumericValidator);
  numValidator->SetHasRange (boo);
};
// function that allow to get the buffer of numeric input
void TNumericInput::GetNumBuff (char *num_buff)
{
	char far* buff = LockBuffer ();
	strcpy (num_buff, buff);
	UnlockBuffer (buff, FALSE);
	fninput (num_buff, numFlags, decLen,num_buff);
	point(num_buff);
}

void TNumericInput::SetNumBuff (char far *str)
{
  dninput (str, numFlags, decLen, strLen, str);
  SetDlgItemText(TWindow::Attr.Id,  str);
}

// limits the amount of text that an edit control can have to the value of
// TextLen  & sets the text font for input object.
void TNumericInput::SetupWindow()
{
  TEdit::SetupWindow();
  if (TextLen != 0)
	 HandleMessage(EM_LIMITTEXT, TextLen - 1);

  delete font;
  font = new TFont("Courier New",
							  fontSize*2, fontSize, 0, 0, FW_NORMAL,
							  FIXED_PITCH | FF_MODERN,
							  FALSE, FALSE, FALSE,
							  ANSI_CHARSET,
							  OUT_CHARACTER_PRECIS,
							  CLIP_DEFAULT_PRECIS,
							  PROOF_QUALITY);

  SetWindowFont(*font, TRUE);
}

UINT TNumericInput::Transfer (void *buffer, TTransferDirection direction)
{
	if (direction == tdGetData)
	{ char *ptr;
	  char* text = new char[strLen];
	  char* text1 = new char[strLen];
	  int dec_sep = numFlags & miNumericDecSep;
	  char dSep[2]; dSep[0] = (dec_sep ? ',' : '.'); dSep[1] = '\x0';
	  // thousend separator
	  char tSep[2]; tSep[0] = (dec_sep ? '.' : ','); tSep[1] = '\x0';
	  // scan "car" and give up all spaces and thousend separators
	  char far* buff = LockBuffer (strLen);
	  strscan(text, " ", buff);
	  strscan (text1, tSep, text);
	  ptr = strpbrk (text1, dSep);
	  if (ptr) text1[ptr-text1] = '.';
	  sprintf(buff, "%*.*s", strLen-1, strLen-1, text1);
	  // close buffer
	  UnlockBuffer (buff, TRUE);
	  delete  [] text1;
	  delete [] text;
	}
	UINT ll = TEdit::Transfer (buffer, direction);
	if (direction == tdSetData)
	{ char* text = new char[strLen];
	  char* text1 = new char[strLen];
	  char far* buff = LockBuffer (strLen);
	  strscan (text, " ", buff);
	  char *ptr = strchr (text, '*');
	  if (ptr == NULL)
	  { dninput (buff, numFlags, decLen, strLen, text);
		 UnlockBuffer (buff, TRUE);
	  } else
		 UnlockBuffer (buff, FALSE);

	  delete [] text1;
	  delete [] text;
	}
	ll = TStatic::GetTextLen () + 1;
	return (ll);
}

// Responds to the GetDlgCode query according to the
// current state of the control.  If the edit control
// contains valid input, then TABs are allowed for
// changing focus.  Otherwise, requests that TABs be
// sent to Self, where we will generate the Invalid
// message (See WMKeyDown below).
UINT TNumericInput::EvGetDlgCode(MSG far* msg)
{
  int mm = 0;

  if(msg) // transform the ENTER and DOWN keys in TAB
	 if (msg->wParam == VK_RETURN || msg->wParam == VK_DOWN)
	 { msg->wParam = VK_TAB;
		mm = 1;
	 } else // Verify for TAB key
	 if (msg->wParam == VK_TAB) mm = 1;

  UINT retVal = (UINT)TEdit::EvGetDlgCode(msg);
  // if input is not valid  || if for existing validUser function, this
  // function returns FALSE than don't allow the leaving of field
  if (mm)
  { Parent->SendNotification(Attr.Id, CT_INPUT_TAB, HWindow);
	 IsValid ();
  } else
    retVal |= DLGC_WANTTAB;

  return retVal;
}

BOOL TNumericInput::IsValid (BOOL reportError)
{
  BOOL boo;
  boo = (validUser ? validUser (this) : TRUE);
  if (boo)
	 boo = TEdit::IsValid (reportError);
  return boo;
}

void TNumericInput::EvChar (UINT key, UINT repeatCount, UINT flags)
{
	TEdit::EvChar (key, repeatCount, flags);
	Parent->SendNotification(Attr.Id, CT_INPUT, HWindow);
}
void TNumericInput::EvKeyDown (UINT key, UINT repeatCount, UINT flags)
{
  TEdit::EvKeyDown(key, repeatCount, flags);
  if (key == VK_DELETE)
	 Parent->SendNotification(Attr.Id, CT_INPUT, HWindow);
}

void TNumericInput::EvSetFocus (HWND hWndLostFocus)
{
  // If we're getting focus back because of invalid input, then clear the
  // anti-oscillation flag
  int buffLen;
  char *mybuff = new char [strLen];
  // open buffer only for informations
  char far* buff = LockBuffer ();
  // display into focused format
  buffLen = fninput (mybuff, numFlags, decLen, buff);
  // close buffer without modifications
  UnlockBuffer (buff, FALSE);
  buffLen = strlen (mybuff);
  buff = LockBuffer (buffLen + 1);
  // write into buffer
  strncpy (buff, mybuff, buffLen); buff[buffLen] = 0;
  // close the buffer, modified & resized
  UnlockBuffer (buff, TRUE);
  SetSelection (0, buffLen);
  delete [] mybuff;

  ValidatorReFocus = 0;

  TEdit::EvSetFocus (hWndLostFocus);
  Parent->SendNotification(Attr.Id, CT_INPUT_FOCUS, HWindow);
}

void TNumericInput::EvKillFocus (HWND hWndGetFocus)
{
  BOOL boo = TRUE;
  Parent->SendNotification(Attr.Id, CT_INPUT_TAB, HWindow);
  TNumericValidator *numValidator =
	 TYPESAFE_DOWNCAST (Validator, TNumericValidator);
  if (numValidator)
	 boo = numValidator->GetValidOut ();
  if (boo && validUser)
	 boo = validUser (this);
  if (boo)  // For valid out perform allow loosing focus
  {
	 char *mybuff = new char [strLen];
	 // do the new buffer with mprint
	 char far* buff = LockBuffer (strLen);
	 wsprintf (mybuff, buff);
	 // use display format wity numFlags on
	 dninput (buff, numFlags, decLen, strLen, mybuff);
	 UnlockBuffer (buff, TRUE);
	 // call original function(described in TEdit) that calls IsValid()
	 TEdit::EvKillFocus (hWndGetFocus);
	 //	Parent->SendNotification(Attr.Id, CT_INPUT_TAB, HWindow);
	 delete  [] mybuff;
  } //else
/*  {
	 TEdit::EvKillFocus (hWndGetFocus);
	 this->SetFocus ();
  }
*/
}

BOOL TNumericInput::CanClose()
{
  UINT id = ::GetDlgCtrlID(GetFocus());
  if (IDOK == id )
  {
	 BOOL okToClose = TEdit::CanClose ();
	 if (okToClose)
	  if (IsWindowEnabled() && !IsValid(TRUE))// || !validExit()) )
	  {
		 ValidatorReFocus = this;
		 SetFocus();
		 return FALSE; // input invalid, keep the focus on the same input
	  }
	 return okToClose; // input ok, go to next
  }
  return FALSE; // ENTER was pressed on input; see EvGetDlgCode(MSG *msg)
}

char far*
TNumericInput::GetClassName()
{
  return "NUMERICINPUT";
}


#endif
#if !defined(SECTION) || SECTION == 2
// Validator
IMPLEMENT_STREAMABLE1(TNumericValidator, TFilterValidator);

void*
TNumericValidator::Streamer::Read(ipstream& is, uint32 ) const
{
  ReadBaseObject((TFilterValidator*)GetObject(), is);
  is >> GetObject()->n_flags >> GetObject()->nr_dec
	  >> GetObject()->str_len  >> GetObject()->d_min
	  >> GetObject()->d_max >> GetObject ()->has_range;
  return GetObject();
}

void
TNumericValidator::Streamer::Write(opstream& os) const
{
  WriteBaseObject((TFilterValidator*)GetObject(), os);
  os << GetObject()->n_flags << GetObject()->nr_dec
	  << GetObject()->str_len << GetObject()->d_min
	  << GetObject()->d_max << GetObject ()->has_range;
}

// Numeric input
IMPLEMENT_STREAMABLE1 (TNumericInput, TEdit);

// reads an instance of TNumericInput from the passed ipstream

void* TNumericInput::Streamer::Read (ipstream& is, uint32 ) const
{
  ReadBaseObject ( (TEdit*)GetObject (), is);
  is >> GetObject ()->Validator;
  return GetObject ();
}

// writes the TNumericInput to the passed opstream
void TNumericInput::Streamer::Write (opstream& os) const
{
  WriteBaseObject ( (TEdit*)GetObject (), os);
  os << GetObject ()->Validator;
}

#endif

//  New function strscan() described here, scan a string "src" for a given
//  format and put the scaned string in "dest". The function returns nothing
void strscan(char *dest, char *format, char *src)
{
  char work[80];
  char *ptr;
  long ll;
  memset (work, '\x0', 80);
  strcpy (work, src);
  do
  { ptr = strpbrk (work, format);
	 if (ptr)
	 { ll = ptr - work;
		ptr ++;
		work[ll] = 0;
		strcat (work, ptr);
	 }
  } while (ptr);
  strcpy (dest, work);
} // end strscan(..)

void point (char *str)
{
  char *ptr;
  int ll;
  ptr = strchr (str, ',');
  if (ptr)
  { ll = ptr - str;
	 str[ll] = '.';
  }
}

// Remake the string for focused numeric input
fninput (char *dest, int flags, int nr_dec, char *src)
{
  int dec_sep = flags & miNumericDecSep;
  int ntyp_dec = flags & miNumericNTypeDec;
  // -------------
  char work[80]; memset (work, 80, '\x0');
  char dwork[80]; memset (dwork, 80, '\x0');
  char *ptr;
  long ll;
  // --------------
	// decimal separator
  char dSep[2]; dSep[0] = (dec_sep ? ',' : '.'); dSep[1] = '\x0';
  // thousend separator
  char tSep[2]; tSep[0] = (dec_sep ? '.' : ','); tSep[1] = '\x0';
  // scan "car" and give up all spaces and thousend separators

  strscan (work, " ", src);
  strscan (dwork, tSep, work);
  strcpy (work, dwork);
  ptr = strpbrk (work, dSep);
  // --------- Cut suplimentary decimals
  if (ptr)
  { ll = ptr - work;
	 if (strlen(work)-ll-1 > nr_dec)
		work[strlen(work)-(ll-nr_dec)] = 0;
  }
  // --------------
  // --------- If not type decimal separator
  // Write the number without decimal sep.
  if (ntyp_dec)
  { strscan (dwork, dSep, work);
	 strcpy(work, dwork);
  }
  // cut leading zeroes unnecessary
  ptr = strpbrk (work, dSep);
  ll = ptr - work; // compute the length of entire part
  if (ll-1)
  {  strrev (work);
	  for (int i = strlen (work) - 1;  i > 0 && work[i] == '0'; work[i] = '\x0', i--);;
	  strrev (work);
  }
  // --------------
  strcpy(dest, work);
  return (strlen (work));
}  // end fninput (..)

//  For numeric inputs are on request may be different displays,
//  remake initial display with fninput()
// if str[25] -> s_leng = sizeof(dest) (must be == 25)
void dninput (char *dest,  int flags, int nr_dec, int s_leng, char *src)
{
  int mark_th = flags & miNumericMarkTh;
  int dec_sep = flags & miNumericDecSep;
  int cut_tr = flags &  miNumericCutTr;
  int ntyp_dec = flags & miNumericNTypeDec;
  s_leng --;
  // don't let to have cut trailing zeroes if don't endter the
  // decimal separator
  if (ntyp_dec) cut_tr = 0;
  // -------------
  char sir1[80];   memset (sir1, '\x0', 80);
  char sir2[80];   memset (sir2, '\x0', 80);
  char is_sign[2]; memset (is_sign, '\x0', 2);
  char *ptr;
  long ll;
  // --------------
  char dSep[2];
  strcpy (&dSep[0], (dec_sep ? "," : ".")); // decimal separator
  char tSep[2];
  strcpy (&tSep[0], (dec_sep ? "." : ",")); // thousend separator
  // scan "car" and give up all spaces
  strscan (&sir2[0], " ", src);
  ll = strlen (sir2);
  if (ll || (!ll && (flags & miNumericShEmpty)))
  {  if (!ll) strcpy (&sir2[0], "0");
	  ptr = strpbrk (sir2, "+-");
	  if (ptr)
	  { is_sign[0] = sir2[0]; is_sign[1]=0;
		 strcpy (sir1, &sir2[1]);
		 // basic string is in sir2
	  } else
		 strcpy (sir1, sir2);
	  // if receive number shorter than nr_dec and dont type decimal point
	  // to do the number less than 1
	  if (flags & miNumericNTypeDec)
	  { ll = strlen (sir1);
		 if (ll <= nr_dec)
		 {  strrev (sir1);
			 for (int i = ll; i < nr_dec; i++)
				strcat (sir1, "0");
			 strcat (sir1, dSep);
			 strcat (sir1, "0");
			 strrev (sir1);
		 }
	  }
	  // if decimal sep is not correct
	  ptr = strpbrk (sir1, tSep);
	  if (ptr)
		 strncpy (&sir1[ptr - sir1], dSep, 1);
	  // --------- Not typed decimal separator
	  // remake the string with gived nr_dec for not type decimal sep.
	  // so if nr_dec = 3 and received string is "12345678"
	  // correct string will be "12345.678"
	  if(ntyp_dec)
	  { ptr = strpbrk (sir1, dSep);
		 if (!ptr)
		 { ll = strlen(sir1);
			strcpy (sir2, &sir1[ll-nr_dec]);
			sir1[ll-nr_dec] = 0;
			strncat (sir1, dSep, 1);
			strcat (sir1, sir2);
		 }
		 // basic string is in sir1
	  }
	  // cut leading zeroes unnecessary
	  ptr = strpbrk (sir1, dSep);
	  ll = (ptr ? ptr - sir1 : strlen(sir1)); // compute the length of entire part
	  if (ll-1 > 0)
	  {  strrev (sir1);
		  for (int i = strlen (sir1) - 1;  i > 0 && sir1[i] == '0'; sir1[i] = '\x0', i--);;
		  strrev (sir1);
	  }
	  // ---------
	  // --------- Put initial zero for numbers with decimals
	  // if the string is like ".67" becomes "0.67"
	  if (sir1[0] == dSep[0])
	  {  strrev(sir1);
		  strcat(sir1, "0");
		  strrev(sir1);
		 // basic string is sir1
	  }
	  // ---------
	  // --------- Format the number with correct number of decimals
	  // put the correct no of decimals
	  ptr = strpbrk (sir1, ",.");
	  int nrdec = 0; // is the number of decimals of inital string
	  if (ptr)
	  { ll = ptr - sir1;
		 nrdec = strlen (sir1) - ll - 1;
	  }
	  if (nr_dec != nrdec)
	  { if (nrdec > nr_dec) // cut string
			 sir1[ll+nr_dec+(nr_dec?1:0)] = 0;
		 else // append to string
		 { if (!ptr) strcat( sir1, dSep);
			for (int i = 0; !cut_tr && i < nr_dec-nrdec; i++)
				strcat (sir1, "0");
		 }
		 // basic string is in sir1
	  }
	  // ---------
	  strrev (sir1);
	  ptr = strpbrk (sir1, dSep);
	  ll = ( ptr ? ptr - sir1 : 0); // number of decimals
	  // --------- Cut trailing zeroes
	  if (ptr && cut_tr)// cut trailing zeroes
	  { int i;
		 for (i=0; i<=ll && (sir1[i]=='0' || sir1[i]==dSep[0]); i++);
		 strcpy(sir2, &sir1[i]);
		 strcpy(sir1, sir2);
		 ptr = strpbrk (sir1, dSep);
		 ll = ( ptr ? ptr - sir1 : 0); // number of decimals
		 // basic string is in sir1
	  }
	  // ---------
	  // --------- Format with mark of thousends
	  // compute the number of digits in integer
	  int lstart = strlen (sir1);
	  ptr = strpbrk(sir1, dSep);
	  ll = lstart;
	  if (ptr)
	  { ll = (ptr - sir1);
		 ll = lstart - 1 - ll;
	  }
	  // Even for markTh if integer part <= 3 no necessary
	  // to perform this part
	  if (mark_th && ll > 3)
	  {  ptr = strpbrk(sir1, dSep);
		  ll = (!ptr ? 0 : ptr - sir1 + 1);
		  lstart -= ll;
		  // copy integer part(reversed) beginning with utils digit
		  // for ex. if no. in "sir1" is "23.45678"
		  // in "sir2" will be copied "78"
		  // but for "23.4" in sir2 will be nothing
		  strcpy(sir2, sir1+ll+(lstart>3? 3 : lstart));
		  sir1[ll+3] = 0;
		  lstart -= 3;
		  for (ll = 0;lstart;)
		  { strcat(sir1, tSep);
			 strncat(sir1, &sir2[ll], (lstart>3 ? 3 : lstart));
			 ll += 3;
			 lstart -= (lstart>3 ? 3: lstart);
		  }
		  // basic string is in sir1
	  }
	  // ---------
	  // --------- Final and correct formatted numeric input
	  strcat(sir1, is_sign);
	  strrev(sir1);
	  ll = strlen(sir1);
	  // s_leng was already decreased with 1
	  if (ll <= s_leng)
		 sprintf(dest, "%*.*s", s_leng, s_leng, sir1);
	  else
		 sprintf(dest, "%*.*s", s_leng, s_leng, "*");
	  // ---------
  } else
	 strcpy(dest, sir2);
}  // end  dninput (..)


//------------------------------------------------------------------------
//                    W03INUMB.CPP
//------------------------------------------------------------------------

