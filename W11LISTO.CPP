//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : W11LISTO.CPP
//  Written by   : Ioan Ghip
//  Created      : 25.10.1994
//  Updated      : 13.10.1995
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

#include "w11dlgap.rh"
#include "w11listo.h"
extern Px_File *pxTill;// data base accesj
extern int msg_lang;
extern DBIResult rslt;        // Value returned from IDAPI functions
extern  hDBIDb hDb;                // Handle to the database


ListOpenTill::ListOpenTill (TWindow* parent,int id, TModule* module):
	 TListBox(parent, id, module)
{
	parentW = parent;
}

// DEFINE_RESPONSE_TABLE1 for TClubList class
DEFINE_RESPONSE_TABLE1(ListOpenTill,TListBox)
			 EV_WM_LBUTTONDBLCLK,
END_RESPONSE_TABLE;

ListOpenTill::~ListOpenTill()
{
	 Destroy();
	 if(font)
		 delete font;
}

// ListLevel SetupWindow function
void ListOpenTill::SetupWindow()
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
void ListOpenTill::CreateList()
{
	if(GetCount())
		ClearList();
	till_dataST tillData;
	int index = 0;
	char item[100];
	int stat = pxTill->Getlw((char*)&tillData);
	if(!stat)
	{
		do
		{
			wsprintf(item,"%03d.%03d.%03d   %s",tillData.td_level1,
														tillData.td_level2,
														tillData.td_level3,
														tillData.td_name);
			InsertString(item,index);
			index++;
		}
		while(!pxTill->Getnx((char*)&tillData));
	}
}

void ListOpenTill::CreateListN()
{
	if(GetCount())
		ClearList();
	till_dataST tillData;
	int index = 0;
	char item[100];
	int stat = pxTill->Getlw((char*)&tillData,"till_name");
	if(!stat)
	{
		do
		{
			wsprintf(item,"%03d.%03d.%03d   %s",tillData.td_level1,
														tillData.td_level2,
														tillData.td_level3,
														tillData.td_name);
			InsertString(item,index);
			index++;
		}
		while(!pxTill->Getnx((char*)&tillData));
	}
}

void ListOpenTill::EvLButtonDblClk(uint modKeys, TPoint& point)
{
	TListBox::EvLButtonDblClk(modKeys,point);
	char str[15],temp[4];
	memset(str,0,sizeof(str));
	memset(temp,0,sizeof(temp));
	GetSelString(str,12);
	memcpy(temp,str,3);
	int lev1 = atoi(temp);
	memcpy(temp,str + 4,3);
	int lev2 = atoi(temp);
	memcpy(temp,str + 8,3);
	int lev3 = atoi(temp);
	if(PasswordDlgOpenTill(lev1,lev2,lev3,this,PASSWORD).Execute()==IDOK)
	{
		parentW->PostMessage(WM_COMMAND,IDCANCEL,0);
	}
}


//------------------------------------------------------------------------
#define MSG_IDENTIFICATION  10999
#define MSG_PASSWORD		    10610
#define MSG_OK              10451
#define MSG_CANCEL			 11043
#define MSG_HELP			    10806

extern int Access;
till_dataST OpenedTill;
extern personST AccessPerson;
// Construction/Destruction handling.
PasswordDlgOpenTill::PasswordDlgOpenTill (int l1,int l2,int l3,
														TWindow *parent,TResId resId,
														TModule *module)
	 : TDialog(parent, resId, module)
{
  lev1 = l1;
  lev2 = l2;
  lev3 = l3;
  TTxInp *edit;
  editID = new TTxInp(this,PSW_IDENTIFICATION,15);
  edit = new TTxInp(this,PSW_PASSWORD,10);
  pxPers = new Px_File(&hDb,"passdata");
  rslt = pxPers->Open();
  Msg = new Message(msg_lang);
}
// DEFINE_RESPONSE_TABLE1 for PasswordDlgOpenTill class
DEFINE_RESPONSE_TABLE1(PasswordDlgOpenTill,TDialog)
  EV_COMMAND(IDOK, CmOk),
  EV_COMMAND(PASSWORD_HELP, CmHelp),
END_RESPONSE_TABLE;
// PasswordDlgOpenTill::~PasswordDlgOpenTill destructor
PasswordDlgOpenTill::~PasswordDlgOpenTill ()
{
	 Destroy();
	 pxPers->Close();
	 delete pxPers;
	 delete Msg;
}
// PasswordDlgOpenTill::SetupWindow function
void PasswordDlgOpenTill::SetupWindow()
{
	TDialog::SetupWindow();
	SetCaption(Msg->GetMsg(MSG_PASSWORD,FALSE));
	SetDlgItemText(PSW_ST_IDENTIFICATION,Msg->GetMsg(MSG_IDENTIFICATION));
	SetDlgItemText(PSW_ST_PASSWORD,Msg->GetMsg(MSG_PASSWORD));
	SetDlgItemText(IDOK, Msg->GetMsg(MSG_OK));//ok
	SetDlgItemText(IDCANCEL,Msg->GetMsg(MSG_CANCEL));//cancel
}
// PasswordDlgOpenTill::CmOk function (OK is pressed)
void PasswordDlgOpenTill::CmOk()
{
  int stat = 0;
  char ident[25];
  char password[25];
  personST pers;
  memset(&pers,0,sizeof(personST));
  GetDlgItemText(PSW_IDENTIFICATION,ident,14);
  GetDlgItemText(PSW_PASSWORD,password,8);
  wsprintf(pers.p_id,"%s",ident);
  Encrypt(password);
  wsprintf(pers.p_password,"%s",password);

  if(pxPers->Geteq((char*)&pers,"password_key"))
  {
	  WARNING("    Worng password !     ");
	  editID->SetFocus();
	  editID->SetSelection(0,9);
	  return;
  }
  else
  {
	  while(!stat && !strcmp(pers.p_id,ident) &&
			  !strcmp(pers.p_password,password))
	  {
		  if(lev1 == pers.p_level1 &&
			  lev2 == pers.p_level2 &&
			  lev3 == pers.p_level3)
		  {
			  TDialog::CmOk();
			  OpenedTill.td_level1 = lev1;
			  OpenedTill.td_level2 = lev2;
			  OpenedTill.td_level3 = lev3;
			  pxTill->Geteq((char*)&OpenedTill);
			  Access = 4;
           memcpy(&AccessPerson,&pers,sizeof(personST));
			  return;
		  }
		  stat = pxPers->Getnx((char*)&pers);
	  }
  }
  WARNING("    Worng password !     ");
  editID->SetFocus();
  editID->SetSelection(0,9);
}
// PasswordDlgOpenTill::CmHelp function
void PasswordDlgOpenTill::CmHelp()
{
  INFO("\nHelp isn't implemented yet.");
}

//------------------------------------------------------------------------
// End File : w11listo.cpp
//------------------------------------------------------------------------

