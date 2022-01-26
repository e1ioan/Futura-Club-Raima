//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : W11STDLG.CPP
//  Written by   : Ioan Ghip
//  Created      : 25.10.1994
//  Updated      : 12.10.1995
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
#include "w11clubm.rh"
#include "w11dlgap.h"
#include "w11stdlg.h"
// Construction/Destruction handling.
ClubStart::ClubStart (TWindow *parent, TResId resId, TModule *module)
	 : TDialog(parent, resId, module)
{
}
// ClubStart::~ClubStart destructor
ClubStart::~ClubStart ()
{
	 Destroy();
}
// ClubStart::SetupWindow function
void ClubStart::SetupWindow ()
{
//  LPSTR copyright;
  TDialog::SetupWindow();
//  ProjectRCVersion applVersion(GetModule());
//  applVersion.GetCopyright(copyright);
//  SetDlgItemText(COPYRIGHT_START,copyright);
}
//------------------------------------------------------------------------
// End File : w11stdlg.cpp
//------------------------------------------------------------------------
