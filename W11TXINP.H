//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11txinp.h
//  Written by   : Ioan Ghip
//  Created      : 26.01.1995
//  Finished     : 27.01.1995
//--------------------------------------------------------------------------
//  Dest. System : windows
//--------------------------------------------------------------------------
//  Libraries    : 
//--------------------------------------------------------------------------
//  Data Files   :
//--------------------------------------------------------------------------
//  Remarks
//--------------------------------------------------------------------------
//  1994 by FUTURA Software s.r.l.
//--------------------------------------------------------------------------

#if !defined(__W11TXINP_H)
#define __W11TXINP_H

// defined constant for each keystroke
#if !defined (CT_INPUT)
#define CT_INPUT       20000 // get char
#endif
// defined constant for leaving the input
#if !defined (CT_INPUT_TAB)
#define CT_INPUT_TAB   20001
#endif

class TTxInp : public TEdit
{
  public:
	TTxInp(TWindow* parent, int resourceID, UINT textLen = 0,
			TModule* module = 0);
	~TTxInp();
  protected:
	 TFont *font;
	 void SetupWindow();
	 UINT EvGetDlgCode(MSG far*);
	 BOOL CanClose();
	 void EvKillFocus (HWND hWndGetFocus);
	 void EvSetFocus (HWND hWndLostFocus);
	 void EvChar(UINT key, UINT repeatCount, UINT flags);
  private:
	 static TTxInp* ValidatorReFocus;
	 DECLARE_RESPONSE_TABLE(TTxInp);
};

#endif
//------------------------------------------------------------------------
// End File : w11txinp.h
//------------------------------------------------------------------------

