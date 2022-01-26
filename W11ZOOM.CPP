//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11zoom.cpp
//  Written by   : Ioan Ghip
//  Created      : 12.07.1995
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
#include "w11clubm.rh"
#include "w11print.h"
#include "w11listb.h"
#include "w11newmb.h"
#include "w11globa.h"
#include "w11zoom.rh"
#include "w11zoom.h"


extern  Px_File *pxMemb;
extern  Px_File *pxClub;

DEFINE_RESPONSE_TABLE1(TZoomDialog, TDialog)
//{{TZoomDialogRSP_TBL_BEGIN}}
	 EV_BN_CLICKED(IDOK, CmOk),
	 EV_EN_CHANGE(IDC_SRCH_NUMBER, ChangeInNumber),
	 EV_EN_CHANGE(IDC_SRCH_NAME, ChangeInName),
	 EV_BN_CLICKED(IDC_RADIOB_SORT_NUMBER, RBSortNumber),
	 EV_BN_CLICKED(IDC_RADIOB_SORT_NAME, RBSortName),
	 EV_BN_CLICKED(600, ClickedButtonSearch),
//{{TZoomDialogRSP_TBL_END}}
END_RESPONSE_TABLE;

//{{TZoomDialog Implementation}}
TZoomDialog::TZoomDialog (TWindow *parentW, TResId resId, TModule *module)
	 : TDialog(parentW, resId, module)
{
	unsigned short flags = 2+4+32;
	number = new TNumericInput(this,IDC_SRCH_NUMBER,flags,0,10);//0-999
	name   = new TTxInp(this,IDC_SRCH_NAME,30);
   parent = parentW;
}


TZoomDialog::~TZoomDialog ()
{
	 Destroy();
	 delete number;
    delete name;
}


void TZoomDialog::SetupWindow ()
{
	TDialog::SetupWindow();
	CheckDlgButton(IDC_RADIOB_SORT_NUMBER,1);
	CheckDlgButton(IDC_RADIOB_SORT_NAME,0);
	list = new TZoomList(this);
	list->Attr.Style;
	list->Create();
	list->SetFocus();
	list->CreateList(1L);
	list->SetActivItem(0);
}


void TZoomDialog::CmOk ()
{
  UINT index = list->GetSelIndex();
  TDialog::CmOk();
  SetParentDlg(index);
}


void TZoomDialog::ChangeInNumber ()
{
	char level1[11],item[50];
	club_memberST om;
	memset(&om,0,sizeof(club_memberST));

	GetDlgItemText(IDC_SRCH_NUMBER,level1,10);
	om.m_no = atol(level1);

	if(!pxMemb->Getge((char*)&om))
	{
		wsprintf(item,"%08ld | %-29.29s",om.m_no,om.m_first_name);
		list->SetSelString(item,-1);
	}
}


void TZoomDialog::ChangeInName ()
{
	char name[31],item[50];
	club_memberST om;
	GetDlgItemText(IDC_SRCH_NAME,name,30);
	wsprintf(om.m_first_name,"%s",name);
	if(!pxMemb->Getge((char*)&om,"key_name"))
	{
		wsprintf(item,"%08ld | %-29.29s",om.m_no,om.m_first_name);
		list->SetSelString(item,-1);
	}
}


void TZoomDialog::RBSortNumber ()
{
	club_memberST om;
	pxMemb->Getlw((char*)&om);
	list->CreateList(om.m_no);
	list->SetFocus();
	if(name->IsWindowVisible())
	{
		SetDlgItemText(IDC_SRCH_NAME,"");
		name->Show(SW_HIDE);
		number->Show(SW_SHOW);
		number->SetFocus();
	}
}


void TZoomDialog::RBSortName ()
{
	club_memberST om;
	pxMemb->Getlw((char*)&om,"key_name");
	list->CreateList(&om);
	list->SetFocus();
	if(number->IsWindowVisible())
	{
		SetDlgItemText(IDC_SRCH_NUMBER,"");
		number->Show(SW_HIDE);
		name->Show(SW_SHOW);
		name->SetFocus();
	}
}


void TZoomDialog::ClickedButtonSearch ()
{
	if(IsDlgButtonChecked(IDC_RADIOB_SORT_NUMBER))
	{
	  if(number->IsWindowVisible())
	  {
		  SetDlgItemText(IDC_SRCH_NUMBER,"");
		  number->Show(SW_HIDE);
	  }
	  else
	  {
		  number->Show(SW_SHOW);
		  number->SetFocus();
	  }
	}
	else
	{
	  if(name->IsWindowVisible())
	  {
		  SetDlgItemText(IDC_SRCH_NAME,"");
		  name->Show(SW_HIDE);
	  }
	  else
	  {
		  name->Show(SW_SHOW);
		  name->SetFocus();
	  }
	}
}

// TZoomList::SetParentDlg function
void TZoomDialog::SetParentDlg(int index)
{
	char sir[50],str[13];
	club_dataST clubData;
	list->GetString(sir,index);
	sir[9] = 0;
	pxClub->Getlw((char*)&clubData,NULL);
	wsprintf(str,"%03d%s",clubData.cd_country_no,sir);
	parent->SetDlgItemText(NEWMEMB_SEARCH,str);
	parent->PostMessage(WM_COMMAND,NEWMEMB_BUTTON_SEARCH,0);
}

#define LIST_LEN 22

// Construction/Destruction handling.
TZoomList::TZoomList (TWindow *parentW, int resId)
	 : TListBox(parentW, resId)
{
	memset(&item,0,sizeof(item));
	parent = parentW;
}
// DEFINE_RESPONSE_TABLE1 for TZoomList class
DEFINE_RESPONSE_TABLE1(TZoomList,TListBox)
			EV_WM_KEYDOWN,
			EV_WM_LBUTTONDOWN,
END_RESPONSE_TABLE;
// TZoomList::~TZoomList destructor
TZoomList::~TZoomList ()
{
}
// TZoomList::CreateList function numeric key
void TZoomList::CreateList(long start)
{
  club_memberST member;
  if(GetCount())
	  ClearList();
  member.m_no = start;
  if(!pxMemb->Geteq((char*)&member))
  {
	  wsprintf(item,"%08ld | %-29.29s",member.m_no,member.m_first_name);
	  InsertString(item,0);
	  int index = 1;
	  while(!pxMemb->Getnx((char*)&member) && (index < LIST_LEN))
	  {
			  wsprintf(item,"%08ld | %-29.29s",member.m_no,member.m_first_name);
			  InsertString(item,index++);
	  }
	  if(index < (LIST_LEN - 1))
		  CreateListEnd(0);
  }
  SetActivItem(0);
  SetSelIndex(0);
}
// TZoomList::CreateList function for alfa key
void TZoomList::CreateList(club_memberST *member)
{
  if(GetCount())
	  ClearList();
  if(!pxMemb->Geteq((char*)member,"key_name"))
  {
	  wsprintf(item,"%08ld | %-29.29s",member->m_no,member->m_first_name);
	  InsertString(item,0);
	  int index = 1;
	  while(!pxMemb->Getnx((char*)member) && (index < LIST_LEN))
	  {
			  wsprintf(item,"%08ld | %-29.29s",member->m_no,member->m_first_name);
			  InsertString(item,index++);
	  }
	  if(index < (LIST_LEN - 1))
		  CreateListEnd(1);
  }
  SetSelIndex(0);
}
// TZoomList::CreateList function for alfa key
void TZoomList::CreateListEnd(int key)
{
  club_memberST member;
  if(GetCount())
	  ClearList();
  if(!pxMemb->Gethi((char*)&member,"key_name") && key)
  {
	  int index = LIST_LEN-2;
	  while(!pxMemb->Getpr((char*)&member) && (index > 0))
			  index--;
	  pxMemb->Geteq((char*)&member,"key_name");
	  wsprintf(item,"%08ld | %-29.29s",member.m_no,member.m_first_name);
	  InsertString(item,0);
	  index = 1;
	  while(!pxMemb->Getnx((char*)&member) && (index < LIST_LEN))
	  {
			  wsprintf(item,"%08ld | %-29.29s",member.m_no,member.m_first_name);
			  InsertString(item,index++);
	  }
  }
  else if(!pxMemb->Gethi((char*)&member) && !key)
  {
	  int index = LIST_LEN-2;
	  while(!pxMemb->Getpr((char*)&member) && (index > 0))
			  index--;
	  pxMemb->Geteq((char*)&member);
	  wsprintf(item,"%08ld | %-29.29s",member.m_no,member.m_first_name);
	  InsertString(item,0);
	  index = 1;
	  while(!pxMemb->Getnx((char*)&member) && (index < LIST_LEN))
	  {
			  wsprintf(item,"%08ld | %-29.29s",member.m_no,member.m_first_name);
			  InsertString(item,index++);
	  }
  }
}
// TZoomList EvLButtonDown function
void TZoomList::EvLButtonDown(UINT i, TPoint& p)
{
  UINT index = GetSelIndex();
  TListBox::EvLButtonDown(i,p);
//  SetParentDlg(index);
}
// TZoomList EvKeyDown function
void TZoomList::EvKeyDown(UINT key, UINT repeatCount, UINT flags)
{
#define VK_PGUP 33
#define VK_PGDOWN 34
	 UINT index;
	 int keyType = 0;
	 switch(key)
	 {
		case VK_DOWN:
					if(parent->IsDlgButtonChecked(IDC_RADIOB_SORT_NUMBER))
						keyType = 0;
					if(parent->IsDlgButtonChecked(IDC_RADIOB_SORT_NAME))
						keyType = 1;
					index = GetSelIndex();
					if(index < LIST_LEN - 1)
						break;
					else if(!keyType)
						InsertEnd(index);
					else if(keyType)
						InsertEnd(index,1);
					break;
		case VK_UP:
					if(parent->IsDlgButtonChecked(IDC_RADIOB_SORT_NUMBER))
							keyType = 0;
					if(parent->IsDlgButtonChecked(IDC_RADIOB_SORT_NAME))
							keyType = 1;
					index = GetSelIndex();
					if(index)
						break;
					else if(!keyType)
						InsertHome(index);
					else if(keyType)
						InsertHome(index,1);
					break;
		case VK_PGUP:
					index = GetSelIndex();
					if(index)
						break;
					if(parent->IsDlgButtonChecked(IDC_RADIOB_SORT_NUMBER))
						InsertPageHome(0);
					if(parent->IsDlgButtonChecked(IDC_RADIOB_SORT_NAME))
						InsertPageHome(0,1);

					break;
		case VK_PGDOWN:
					index = GetSelIndex();
					if(index < LIST_LEN - 1)
						break;
					if(parent->IsDlgButtonChecked(IDC_RADIOB_SORT_NUMBER))
						InsertPageEnd(LIST_LEN - 1);
					if(parent->IsDlgButtonChecked(IDC_RADIOB_SORT_NAME))
						InsertPageEnd(LIST_LEN - 1,1);

					break;
		case VK_HOME:
					if(parent->IsDlgButtonChecked(IDC_RADIOB_SORT_NUMBER))
						CreateList(1L);
					if(parent->IsDlgButtonChecked(IDC_RADIOB_SORT_NAME))
					{
						club_memberST om;
						pxMemb->Getlw((char*)&om,"key_name");
						CreateList(&om);
					}
					break;
		case VK_END:
					if(parent->IsDlgButtonChecked(IDC_RADIOB_SORT_NUMBER))
						keyType = 0;
					if(parent->IsDlgButtonChecked(IDC_RADIOB_SORT_NAME))
						keyType = 1;
					CreateListEnd(keyType);
					break;
	 }
	 TListBox::EvKeyDown(key,repeatCount,flags);
//	 SetParentDlg(index);
}
// TZoomList::SetActivItem function
void TZoomList::SetActivItem(char *str)
{
	SetSelString(str, -1);
}
// TZoomList::InsertEnd function
void TZoomList::InsertEnd(int index,int keyType)
{
	char str[50],sir[50];
	memset(str,0,sizeof(str));
	if(!keyType)  // numeric key
	{
		GetSelString(str,8);
		club_memberST member;
		member.m_no = atol(str);
		if(!pxMemb->Getgt((char*)&member))
		{
			wsprintf(sir,"%08ld | %-29.29s",member.m_no,member.m_first_name);
			DeleteString(0);
			InsertString(sir,index);
			SetSelIndex(index);
		}
	}
	else  // alfa key
	{
      club_memberST member;
		GetSelString(str,41);
		wsprintf(member.m_first_name,"%-29.29s",str+11);
		char valNum[10];
		memset(valNum,0,sizeof(valNum));
		memcpy(valNum,str,8);
		member.m_no = atol(valNum);
		if(!pxMemb->Getgt((char*)&member,"key_name"))
		{
			wsprintf(sir,"%08ld | %-29.29s",member.m_no,member.m_first_name);
			DeleteString(0);
			InsertString(sir,index);
			SetSelIndex(index);
		}
	}

}
// TZoomList::InsertHome function
void TZoomList::InsertHome(int index,int keyType)
{
	char str[50],sir[50];
	memset(str,0,sizeof(str));
	if(!keyType) // numeric key
	{
		GetSelString(str,8);
		club_memberST member;
		member.m_no = atol(str);
		if(!pxMemb->Getlt((char*)&member))
		{
			wsprintf(sir,"%08ld | %-29.29s",member.m_no,member.m_first_name);
			DeleteString(LIST_LEN - 1);
			InsertString(sir,index);
			SetSelIndex(index);
		}
	}
	else // alfa key
	{
		club_memberST member;
		GetSelString(str,41);
		wsprintf(member.m_first_name,"%-29.29s",str+11);
		char valNum[10];
		memset(valNum,0,sizeof(valNum));
		memcpy(valNum,str,8);
		member.m_no = atol(valNum);
		if(!pxMemb->Getlt((char*)&member,"key_name"))
		{
			wsprintf(sir,"%08ld | %-29.29s",member.m_no,member.m_first_name);
			DeleteString(LIST_LEN - 1);
			InsertString(sir,index);
			SetSelIndex(index);
		}
	}
}
// TZoomList::InsertPageEnd function
void TZoomList::InsertPageEnd(int ,int keyType)
{
  if(!keyType) // number key
  {
		char str[10];
		memset(str,0,sizeof(str));
		GetSelString(str,8);
		club_memberST member;
		member.m_no = atol(str);
		if(!pxMemb->Getgt((char*)&member))
			CreateList(member.m_no);
  }
  else // name key
  {
		club_memberST member;
		char str[45];
		memset(str,0,sizeof(str));
		GetSelString(str,41);
		wsprintf(member.m_first_name,"%-29.29s",str+11);
		char valNum[10];
		memset(valNum,0,sizeof(valNum));
		memcpy(valNum,str,8);
		member.m_no = atol(valNum);
		if(!pxMemb->Getgt((char*)&member,"key_name"))
			CreateList(&member);
  }
}
// TZoomList::InsertPageHome function
void TZoomList::InsertPageHome(int index,int keyType)
{
  index = LIST_LEN-2;
  if(!keyType) // number key
  {
		char str[10];
		memset(str,0,sizeof(str));
		GetSelString(str,8);
		club_memberST member;
		member.m_no = atol(str);
		if(!pxMemb->Getlt((char*)&member))
		{
			while(!pxMemb->Getpr((char*)&member) && (index-- > 0));
			CreateList(member.m_no);
		}
  }
  else // name key
  {
		club_memberST member;
		char str[45];
		memset(str,0,sizeof(str));
		GetSelString(str,41);
		wsprintf(member.m_first_name,"%-29.29s",str+11);
		char valNum[10];
		memset(valNum,0,sizeof(valNum));
		memcpy(valNum,str,8);
		member.m_no = atol(valNum);
		if(!pxMemb->Getlt((char*)&member,"key_name"))
		{
			while(!pxMemb->Getpr((char*)&member) && (index-- > 0));
			CreateList(&member);
		}
  }
}
//------------------------------------------------------------------------
// End File : w11zoom.cpp
//------------------------------------------------------------------------
