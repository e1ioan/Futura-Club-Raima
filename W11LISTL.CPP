//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11listl.cpp
//  Written by   : Ioan Ghip
//  Created      : 10.03.1995
//  Updated      : 30.09.1995
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

#include "w11level.rh"
#include "w11listl.h"
#include "w11level.h"

extern  Px_File *pxTill;
extern  LevelDlg *LevelWin;
extern  hDBIDb hDb;                // Handle to the database
extern  DBIResult rslt;               // Value returned from IDAPI functions
//{{ListLevel Implementation}}

ListLevel::ListLevel (Px_File* px,TWindow* parentW, int id):
	 TListBox(parentW, id)
{
	 parent = parentW;
	 pxDept = new Px_File(&hDb,"deptdata");
	 rslt = pxDept->Open();
	 pxBank = new Px_File(&hDb,"bankdata");
	 rslt = pxBank->Open();
    pxTemp = px;
}

// DEFINE_RESPONSE_TABLE1 for TClubList class
DEFINE_RESPONSE_TABLE1(ListLevel,TListBox)
			EV_WM_KEYDOWN,
			EV_WM_LBUTTONDOWN,
END_RESPONSE_TABLE;

ListLevel::~ListLevel ()
{
	 Destroy();
	 pxDept->Close();
	 delete pxDept;
	 pxBank->Close();
	 delete pxBank;
	 if(font)
		 delete font;
}

// ListLevel SetupWindow function
void ListLevel::SetupWindow()
{
  TListBox::SetupWindow();
  // create a special font for the list box object
  font = new TFont("Courier New",
								  16, 8, 0, 0, FW_NORMAL,
								  FIXED_PITCH | FF_MODERN,
								  FALSE, FALSE, FALSE,
								  ANSI_CHARSET,
								  OUT_CHARACTER_PRECIS,
								  CLIP_DEFAULT_PRECIS,
								  PROOF_QUALITY);
  SetWindowFont(*font, TRUE); // activate the new font
}
void ListLevel::CreateList()
{
  if(GetCount())
	  ClearList();
  bank_dataST bankData;
  dept_dataST deptData;
  till_dataST tillData;
  char item[100];
  int index = 0,stat,stat1,stat2;
  stat = pxBank->Getlw((char*)&bankData);
  while(!stat)
  {
	  wsprintf(item,"%03d%11s%s",bankData.bd_level1," ",bankData.bd_name);
	  InsertString(item,index);
	  index++;
	  deptData.dd_level1 = bankData.bd_level1;
	  deptData.dd_level2 = 0;
	  stat1 = pxDept->Getge((char*)&deptData);
	  while( (bankData.bd_level1 == deptData.dd_level1) && !stat1 )
	  {
			wsprintf(item,"%03d.%03d%7s%s",deptData.dd_level1,
												 deptData.dd_level2," ",
												 deptData.dd_name);
			InsertString(item,index);
			index++;
			tillData.td_level1 = bankData.bd_level1;
			tillData.td_level2 = deptData.dd_level2;
			tillData.td_level3 = 0;
			stat2 = pxTill->Getge((char*)&tillData);
			while((tillData.td_level1 == deptData.dd_level1 &&
					tillData.td_level2 == deptData.dd_level2) && !stat2)
			{
				wsprintf(item,"%03d.%03d.%03d   %s",tillData.td_level1,
															tillData.td_level2,
															tillData.td_level3,
															tillData.td_name);
				InsertString(item,index);
				index++;
				stat2 = pxTill->Getnx((char*)&tillData);
			}
			stat1 = pxDept->Getnx((char*)&deptData);
	  }
	  stat = pxBank->Getnx((char*)&bankData);
  }
}


void ListLevel::CreateListN()
{
	if(GetCount())
		ClearList();
	tempST tmpd;
	int index = 0;
	char item[100];
	int stat = pxTemp->Getlw((char*)&tmpd,"temp_key");
	if(!stat)
	{
		do
		{
			if(!tmpd.t_level3 && tmpd.t_level2)
				wsprintf(item,"%03d.%03d       %s",tmpd.t_level1,
																tmpd.t_level2,
																tmpd.t_name);
			else if(!tmpd.t_level2)
				wsprintf(item,"%03d           %s",tmpd.t_level1,
																tmpd.t_name);
			else
			{
				wsprintf(item,"%03d.%03d.%03d   %s",tmpd.t_level1,
																tmpd.t_level2,
																tmpd.t_level3,
																tmpd.t_name);
			}
			InsertString(item,index);
			index++;
		}
		while(!pxTemp->Getnx((char*)&tmpd));
	}
}

// TClubList EvLButtonDown function
void ListLevel::EvLButtonDown(UINT i, TPoint& p)
{
  TListBox::EvLButtonDown(i,p);
  if(!parent->IsDlgButtonChecked(RR_CREATE))
	  SetParentDlg();
}
// TClubList EvKeyDown function
void ListLevel::EvKeyDown(UINT key, UINT repeatCount, UINT flags)
{
  TListBox::EvKeyDown(key,repeatCount,flags);
  if(!parent->IsDlgButtonChecked(RR_CREATE))
	  SetParentDlg();
}
// TClubList::SetParentDlg function
void ListLevel::SetParentDlg()
{
	if(!parent->IsDlgButtonChecked(RR_CREATE))
	{
		LevelWin->DataSet();
		LevelWin->inName->SetFocus();
		LevelWin->inName->SetSelection(0,14);
	}
}

