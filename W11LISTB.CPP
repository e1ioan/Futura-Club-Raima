//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11listb.cpp
//  Written by   : Ioan Ghip
//  Created      : 24.11.1994
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
#include "w11messg.h"
#include "w11print.h"
#include "w11listb.h"
#include "w11newmb.h"
#include "w11globa.h"

#define LIST_LEN 10

extern  NewMemberDlg *newDlg;
extern  Px_File *pxMemb;
extern  DBIResult rslt;               // Value returned from IDAPI functions

// Construction/Destruction handling.
TClubList::TClubList (TWindow *parentW, int resId)
	 : TListBox(parentW, resId)
{
	memset(&item,0,sizeof(item));
	parent = parentW;
}
// DEFINE_RESPONSE_TABLE1 for TClubList class
DEFINE_RESPONSE_TABLE1(TClubList,TListBox)
			EV_WM_KEYDOWN,
			EV_WM_LBUTTONDOWN,
END_RESPONSE_TABLE;
// TClubList::~TClubList destructor
TClubList::~TClubList ()
{
}
// TClubList::CreateList function numeric key
void TClubList::CreateList(long start)
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
// TClubList::CreateList function for alfa key
void TClubList::CreateList(club_memberST *member)
{
  if(GetCount())
	  ClearList();
  if(!(rslt = pxMemb->Geteq((char*)member,"key_name")))
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
// TClubList::CreateList function for alfa key
void TClubList::CreateListEnd(int key)
{
  club_memberST member;
  if(GetCount())
	  ClearList();
  if(!pxMemb->Gethi((char*)&member,"key_name") && key)
  {
	  int index = LIST_LEN-2;
	  while(!pxMemb->Getpr((char*)&member) && (index > 0))
			  index--;
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
// TClubList EvLButtonDown function
void TClubList::EvLButtonDown(UINT i, TPoint& p)
{
  UINT index = GetSelIndex();
  TListBox::EvLButtonDown(i,p);
  SetParentDlg(index);
}
// TClubList EvKeyDown function
void TClubList::EvKeyDown(UINT key, UINT repeatCount, UINT flags)
{
#define VK_PGUP 33
#define VK_PGDOWN 34
	 UINT index;
	 int keyType = 0;
	 switch(key)
	 {
		case VK_DOWN:
					if(parent->IsDlgButtonChecked(NEWMEMB_SORT_NO))
						keyType = 0;
					if(parent->IsDlgButtonChecked(NEWMEMB_SORT_NAME))
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
					if(parent->IsDlgButtonChecked(NEWMEMB_SORT_NO))
							keyType = 0;
					if(parent->IsDlgButtonChecked(NEWMEMB_SORT_NAME))
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
					if(parent->IsDlgButtonChecked(NEWMEMB_SORT_NO))
						InsertPageHome(0);
					if(parent->IsDlgButtonChecked(NEWMEMB_SORT_NAME))
						InsertPageHome(0,1);

					break;
		case VK_PGDOWN:
					index = GetSelIndex();
					if(index < LIST_LEN - 1)
						break;
					if(parent->IsDlgButtonChecked(NEWMEMB_SORT_NO))
						InsertPageEnd(9);
					if(parent->IsDlgButtonChecked(NEWMEMB_SORT_NAME))
						InsertPageEnd(9,1);

					break;
		case VK_HOME:
					if(parent->IsDlgButtonChecked(NEWMEMB_SORT_NO))
						CreateList(1L);
					if(parent->IsDlgButtonChecked(NEWMEMB_SORT_NAME))
					{
						club_memberST om;
						pxMemb->Getlw((char*)&om,"key_name");
						CreateList(&om);
					}
					break;
		case VK_END:
					if(parent->IsDlgButtonChecked(NEWMEMB_SORT_NO))
						keyType = 0;
					if(parent->IsDlgButtonChecked(NEWMEMB_SORT_NAME))
						keyType = 1;
					CreateListEnd(keyType);
					break;
	 }
	 TListBox::EvKeyDown(key,repeatCount,flags);
	 SetParentDlg(index);
}
// TClubList::SetActivItem function
void TClubList::SetActivItem(char *str)
{
	SetSelString(str, -1);
}
// TClubList::InsertEnd function
void TClubList::InsertEnd(int index,int keyType)
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
// TClubList::InsertHome function
void TClubList::InsertHome(int index,int keyType)
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
			DeleteString(9);
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
			DeleteString(9);
			InsertString(sir,index);
			SetSelIndex(index);
		}
	}
}
// TClubList::InsertPageEnd function
void TClubList::InsertPageEnd(int ,int keyType)
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
// TClubList::InsertPageHome function
void TClubList::InsertPageHome(int index,int keyType)
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
// TClubList::SetParentDlg function
void TClubList::SetParentDlg(int )
{
	char str[10];
	memset(str,0,sizeof(str));
	GetSelString(str,8);
	club_memberST member;
	member.m_no = atol(str);
	if(!pxMemb->Geteq((char*)&member));
		newDlg->SetDataDlg(member);
	if(member.m_no > 0 && member.m_no < 10)
		newDlg->EnableControls(FALSE);
	else
		newDlg->EnableControls(TRUE);
	newDlg->newMember = FALSE;
}
//------------------------------------------------------------------------
// End File : w11newmb.cpp
//------------------------------------------------------------------------
