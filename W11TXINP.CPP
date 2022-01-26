//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11txinp.cpp
//  Written by   : Ioan Ghip
//  Created      : 26.01.1995
//  Updated      : 06.02.1995
//--------------------------------------------------------------------------
//  Dest. System : windows
//--------------------------------------------------------------------------
//  Libraries    : raima
//--------------------------------------------------------------------------
//  Data Files   :
//--------------------------------------------------------------------------
//  Remarks
//--------------------------------------------------------------------------
//  
//--------------------------------------------------------------------------

#include "w11hdrsm.h"
#pragma hdrstop
#include "w11txinp.h"

TTxInp* TTxInp::ValidatorReFocus = 0;

TTxInp::TTxInp(TWindow* parent, int resourceID, UINT textLen,
			TModule* module) : TEdit(parent,resourceID,textLen,module)
{
  // create a special font for the input object
  font = new  TFont("Courier New",
						  16, 8, 0, 0, FW_NORMAL,
						  FIXED_PITCH | FF_MODERN,
						  FALSE, FALSE, FALSE,
						  ANSI_CHARSET,
						  OUT_CHARACTER_PRECIS,
						  CLIP_DEFAULT_PRECIS,
						  PROOF_QUALITY);
}

// Input functions definition
DEFINE_RESPONSE_TABLE1 (TTxInp, TEdit)
  EV_WM_SETFOCUS,
  EV_WM_KILLFOCUS,
  EV_WM_GETDLGCODE,
  EV_WM_KEYDOWN,
  EV_WM_CHAR,
END_RESPONSE_TABLE;

TTxInp::~TTxInp()
{
  delete font;
}

void TTxInp::SetupWindow()
{
  TEdit::SetupWindow();
  SetWindowFont(*font, TRUE); // activate the new font
}

void TTxInp::EvKillFocus (HWND hWndGetFocus)
{
	// call original function(described in TEdit) that calls IsValid()
	TEdit::EvKillFocus (hWndGetFocus);
	Parent->SendNotification(Attr.Id, CT_INPUT_TAB, HWindow);
}

void TTxInp::EvSetFocus (HWND hWndLostFocus)
{
  TEdit::EvSetFocus (hWndLostFocus);
}

void TTxInp::EvChar (UINT key, UINT repeatCount, UINT flags)
{
	TEdit::EvChar (key, repeatCount, flags);
	Parent->SendNotification(Attr.Id, CT_INPUT, HWindow);
}

UINT TTxInp::EvGetDlgCode(MSG far* msg)
{ // transform the ENTER and DOWN keys in TAB
  if(msg && (msg->wParam == VK_RETURN || msg->wParam == VK_DOWN))
		msg->wParam = VK_TAB;
  UINT retVal = (UINT)TEdit::EvGetDlgCode(msg);
  if(!IsValid(FALSE))
	 retVal |= DLGC_WANTTAB;
  return retVal;
}

BOOL TTxInp::CanClose()
{
  UINT id = :: GetDlgCtrlID(GetFocus());
  if(IDOK == id )
  {
	 BOOL okToClose = TEdit::CanClose();
	 if(okToClose)
	  if( IsWindowEnabled() && !IsValid(TRUE))// || !validExit()) )
	  {
		 ValidatorReFocus = this;
		 SetFocus();
		 return FALSE; // input invalid, keep the focus on the same input
	  }
	 return okToClose; // input ok, go to next
  }
  return FALSE; // ENTER was pressed on input; see EvGetDlgCode(MSG *msg)
}

//------------------------------------------------------------------------
// End File : w11txinp.cpp
//------------------------------------------------------------------------

