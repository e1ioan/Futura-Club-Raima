//--------------------------------------------------------------------------
//  Project      : *.IDE
//  File Name    : W03INUMB.H
//  Written by   : Mihaela Popescu
//  Created      : 09.12.1994
//  Updated      : 08.06.1995 
//--------------------------------------------------------------------------
//  Dest. system : Windows
//--------------------------------------------------------------------------
//  Remarks      : Header file for numeric input  Validator function
//     This will be included in all programs that have TNumericInput type
//--------------------------------------------------------------------------
//  Datafiles    : NONE
//--------------------------------------------------------------------------
//  1994, 1995 by Futura Software s.r.l.
//--------------------------------------------------------------------------

#if !defined(__W03INUMB_H)
#define __W03INUMB_H

#include <owl\validate.h>
// defined constant for each keystroke
#if !defined (CT_INPUT)
#define CT_INPUT       20000 // get char
#endif
// defined constant for leaving the input
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

//
// class TNumericValidator
// ----- ---------------
//
class TNumericValidator : public TFilterValidator
{
  public:
	 TNumericValidator(unsigned int flags, unsigned int nrdec,
							 UINT strLen, double dMin = 0., double dMax = 0.,
							 BOOL hasRange = FALSE);

	 //
	 // override TValidator's virtuals
	 //
	 void  Error();
	 BOOL  IsValidInput(char far* str, BOOL boolean);
	 BOOL  IsValid(const char far* s);
	 // Miha's new functions
	 // Change the current values of d_min or d_max
	 // boo = TRUE => change d_max
	 // boo = FALSE => change d_min
	 // return value is FALSE if new values don't follow this
	 // condition d_min <= d_max
	 BOOL SetNewRange (double dd, BOOL boo = TRUE);
	 // Change current value of valid_out
	 inline void SetValidOut (BOOL boo = TRUE) { valid_out = boo; };
	 // Return the value of protected valid_out
    inline BOOL GetValidOut () { return valid_out; };
	 // Change current value of has_range
	 inline void SetHasRange (BOOL boo = TRUE) { has_range = boo; };

  protected:
	 char dec_sep;  // decimal separator
	 unsigned int nr_dec; // number of decimals
	 UINT str_len;   // length of string (sizeof())
	 double d_min;   // min value for range
	 double d_max;   // max value for range
	 // for default values of range(== 0.) there is no range
	 // to have as uniqe range 0. (the input can't be either than 0.)
	 // call SetHasRange(TRUE) function
	 BOOL has_range;
	 BOOL valid_out;
	 unsigned int n_flags;  // numeric flags

  DECLARE_STREAMABLE(_OWLCLASS, TNumericValidator, 1);
};
// end of valid definition

#include <owl\edit.h>

typedef BOOL (*TNumericValidUser) (TEdit*); // user valid function

class _OWLCLASS TNumericInput : public TEdit
{
  public:
	 UINT strLen;
	 unsigned short decLen;
	 unsigned short numFlags;

	 TNumericInput(TWindow* parent,
					 int id, const char far* text,
					 int x, int y, int w, int h,
					 unsigned short numeric_flag, // corresp. miNumeric
					 unsigned short dec_len, // number of decimals
					 UINT str_len, // length of string
					 UINT font_size = 8,
					 double amin = 0., double amax = 0., // range values
					 BOOL hasRange = FALSE,   // range setting for unique value
					 BOOL multiline = FALSE, TModule* module = 0);

	 TNumericInput(TWindow*   parent,
					 int        resourceId,
					 unsigned short numeric_flag, // corresp. miNumeric
					 unsigned short dec_len, // number of decimals
					 UINT str_len, // length of string
					 UINT font_size = 8,
					 double amin = 0., double amax = 0., // range values
					 BOOL hasRange = FALSE,  // range setting for unique value
					 TModule* module = 0);

	 ~TNumericInput();

	 UINT Transfer (void* buffer, TTransferDirection direction);
	 void GetNumBuff (char *);
	 void SetNumBuff (char far *);
	 void setValidUser(TNumericValidUser u = NULL);

	 // Functions for changing the current values from validator class
	 // --------------------------------------------------------------
	 // Call this function to change current values of range domain so:
	 // if boo = TRUE  => will be changed max value
	 // if boo = FALSE => will be changed min value
	 // if new value does not correspond to condition of (min <= max)
	 // the function will return False and will not proceed to changing
	 BOOL SetNewRange (double dd, BOOL boo = TRUE);
	 // validOut = True as default and if = False don't allow the exit from
	 // the numeric input with "TAB" or "ENTER"
	 // Call this function if you need to change the current value of validOut
	 void  SetValidOut (BOOL boo = TRUE);
	 void  SetHasRange (BOOL boo = TRUE);
	 inline void SetNewDecimals (unsigned int nrdec) { decLen = nrdec; };
	 // --------------------------------------------------------------
	 TFont *font;
	 UINT fontSize;
	 BOOL IsValid(BOOL reportError = FALSE);

	 // child id notification handled at the child
	 // Override TWindow virtual member functions
  protected:
	 char far* GetClassName();
	 void SetupWindow ();
	 void EvSetFocus (HWND hWndLostFocus);
	 void EvKillFocus (HWND hWndGetFocus);
	 UINT EvGetDlgCode (MSG far*);
	 void EvChar (UINT key, UINT repeatCount, UINT flags);
	 void EvKeyDown (UINT key, UINT repeatCount, UINT flags);
	 BOOL CanClose ();
  private:
	 TNumericValidUser validUser;
	 static TNumericInput *ValidatorReFocus;

	 DECLARE_RESPONSE_TABLE(TNumericInput);
	 DECLARE_STREAMABLE(_OWLCLASS, TNumericInput, 1);
};
#endif  // __W03INUMB_H
//------------------------------------------------------------------------
//                    W03INUMB.H
//------------------------------------------------------------------------

