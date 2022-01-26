//--------------------------------------------------------------------------
//  Project      : ALL PROGECTS
//  File Name    : W04ITEXT.H
//  Written by   : GABRIELA OPRESCU
//  Created      : 27.10.1994
//  Updated      : 02.05.1995
//--------------------------------------------------------------------------
//  Dest. System : WINDOWS
//--------------------------------------------------------------------------
//  Libraries    : OWL 2.0
//--------------------------------------------------------------------------
//  Data Files   : NONE
//--------------------------------------------------------------------------
//  Remarks      : HEADER FOR W04ITEXT.CPP
//--------------------------------------------------------------------------
//  1994, 1995 by FUTURA Software s.r.l.
//--------------------------------------------------------------------------

#if !defined(__W04ITEXT_H)
#define __W04ITEXT_H

// Global include files
#if !defined(__OWL_EDIT_H)
#include <owl\edit.h>
#endif

class _OWLCLASS TValidator;


// TTextInput class definition
// special constants for modified input handling
		// gen_flags  in TTextInput and TNumericInput constructors
		// ON = no free column in front of text
const miGenFlagAutoExit = 1, // ON = visible cursor
		miGenFlagVisibleCr = 2, // ON = exit on CR ( and TAB)
		miGenFlagExitCR = 4;

// Attention:  if size.x < len : miGenFlagNoLeft and miGenFlagNoRight
//     are OFF if miGenFlagNoLeft OFF : 1 free column in front of field if
//     miGenFlagNoRight OFF : 2 free columns at the end of the field len
//     parameter in TTextInput si TNumeric Input: number of char to be
//     accepted  in field (without EOS position)
//     alpha_flags  parameter in TTextInput constructor defines the
//     accepted characteres if corresponding bit is ON  the chars. in that
//     interval is accepted

// 65 (A)- 90(Z) & 97(a)-122(z)
const miAlphaFlagAlpha = 1, // space (32)
		miAlphaFlagSpace = 2, // 48 (0) - 57 (9)
		miAlphaFlagNumber = 4, // 1 - 31, 127-...
		miAlphaFlagSign = 8,
		miAlphaFlagExt = 16; //33(!)-47(/) 58(:)-64(@) 91([)-96(') 123({)-126(~)

// letter_flags parameters in TTextInput constructor conversion attributs 							   */
// ( ASCII signs)

const miLetterFlagUpp = 1, // everything upper
		miLetterFlagLow = 2, // everything lower
		miLetterFlagFirstUp = 4, // first letter upper
		miLetterFlagEveryFirst = 8, // every first (after space) upper
		miLetterFlagCutSpace = 16, // cut redundant spaces
		miLetterFlagEmptyField = 32; // ask for non empty field

// defined constant for each keystroke
#if !defined (CT_INPUT)
#define CT_INPUT       20000 // get char
#endif
// defined constant for leaving the input by tab or enter
#if !defined (CT_INPUT_TAB)
#define CT_INPUT_TAB   20001
#endif
// defined constant for on focus input
#if !defined (CT_INPUT_FOCUS)
#define CT_INPUT_FOCUS 20002
#endif
// constant for event mouse left down button
#if !defined (CT_INPUT_LBD)
#define CT_INPUT_LBD   20003
#endif
// defined constant for leaving the input by enter
#if !defined (CT_INPUT_RETURN)
#define CT_INPUT_RETURN   20004
#endif

typedef BOOL (*TTextUserValid)(TEdit*); // user valid function

class _OWLCLASS TTextInput : public TEdit
{
  public:
	 TTextInput(TWindow* parent,
					 int id, const char far* text,
					 int x, int y, int w, int h,
					 unsigned int gen_flags, // position & exit miGenFlag...
					 unsigned char fill_char, // fills output data up to len
					 unsigned int alpha_flags, // accepted characters miAlphaFlag...
					 unsigned int letter_flags, // conv. attributes miLetterFlag...
					 UINT textLen = 0,
					 UINT font_size = 8,
					 BOOL bold = FALSE,
					 long min = 0,  long max = 0, // range for natural numbers
					 TTextUserValid valid_user = NULL,
					 BOOL spatiu = FALSE, // without space on first pos.
					 BOOL multiline = FALSE,
					 TModule* module = 0);

	 TTextInput(TWindow*   parent,
					 int        resourceId,
					 unsigned int gen_flags, // position & exit miGenFlag...
					 unsigned char fill_char, // fills output data up to len
					 unsigned int alpha_flags, // accepted characters miAlphaFlag...
					 unsigned int letter_flags, // conv. attributes miLetterFlag...
					 UINT       textLen = 0,
					 UINT font_size = 8,
					 BOOL bold = FALSE,
					 long min = 0,  long max = 0, // range for natural numbers
					 TTextUserValid valid_user = NULL,
					 BOOL spatiu = FALSE, // without space on first pos.
					 TModule*   module = 0);

	~TTextInput();
	 // Accessing
	 BOOL IsValid(BOOL reportErr = FALSE);
	 void SetValidator(TValidator* validator);
	 // improvements for the new input object
	 virtual void deleteSelect(/*BOOL ch = FALSE*/);
	 void acceptChar(UINT& key);
	 int keyFilter(UINT& key);
	 void rejectChar();
	 BOOL validExit();
	 void setValidUser(TTextUserValid u = NULL);

  protected:
	 unsigned short int curPos, startSel, endSel;
	 unsigned int genFlags, alphaFlags, letterFlags, fontSize;
	 unsigned char fillChar;
	 long min_digit, max_digit; // numeric  range
	 char far* data_buff; // data input string
	 BOOL InsCursor; // TRUE - insert mode, FALSE - overtype mode
	 BOOL sp, bold_face;
	 TFont *font;
	 TTextUserValid validUser;
	 BOOL End_Sel(); // for handling an already (blue) selected string
	 // Override TWindow virtual member functions
	 char far* GetClassName();
	 void SetupWindow();
	 // Input validation object
	 TValidator*  Validator;
	 void EvChar(UINT key, UINT repeatCount, UINT flags);
	 void EvKeyDown(UINT key, UINT repeatCount, UINT flags);
	 void EvLButtonDown(UINT modKeys, TPoint &point);
	 void EvSetFocus(HWND hWndLostFocus);
	 void EvKillFocus(HWND hWndGainFocus);
	 UINT EvGetDlgCode(MSG far*);
	 UINT Transfer (void *buffer, TTransferDirection direction);
	 BOOL CanClose();

  private:
	 // Used to prevent 'oscillation' when a validated window with invalid
	 // input is losing focus to another validated window with invalid input
	 // Without this flag, the two windows will fight for focus
	 static TTextInput* ValidatorReFocus;

  DECLARE_RESPONSE_TABLE(TTextInput);
  DECLARE_STREAMABLE(_OWLCLASS, TTextInput, 1);
};
#endif  // __W04ITEXT_H
//------------------------------------------------------------------------
// End of file: W04ITEXT.H
//------------------------------------------------------------------------

