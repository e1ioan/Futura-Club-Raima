//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : W11LEVEL.CPP
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

#include "w11level.rh"
#include "w11listl.h"
#include "w11level.h"

#define MSG_TITLE		       11977
#define MSG_TILL		       12014
#define MSG_DEPARTAMENT		 10608
#define MSG_BANK	          11973
#define MSG_OK              10451
#define MSG_CLOSE			    11169
#define MSG_CREATE	       10392
#define MSG_CHANGE          10393
#define MSG_IDENTIFICATION  10999
#define MSG_PASSWORD		    10610
#define MSG_LAST_MODIFY	    10998
#define MSG_CREATION_DATE 	 10997
#define MSG_NAME            10366

extern  Px_File *pxTill;
extern  DTF_FLAGS date_flags;
extern  int msg_lang;
extern  hDBIDb hDb;                // Handle to the database
extern  DBIResult rslt;               // Value returned from IDAPI functions

DEFINE_RESPONSE_TABLE1(LevelDlg, TDialog)
	  EV_WM_PAINT,
	  EV_COMMAND(ID_OK,CmOk),
	  EV_COMMAND(IDCANCEL,CmCancel),
	  EV_COMMAND(LEVEL_HELP,CmHelp),
	  EV_COMMAND(600,CmSearch),
	  EV_BN_CLICKED(SORT_LEVEL,SortLevel),
	  EV_BN_CLICKED(SORT_NAME,SortName),
	  EV_CHILD_NOTIFY(RR_LEVEL1,CT_INPUT,ValidLevel1),
	  EV_CHILD_NOTIFY(RR_LEVEL2,CT_INPUT,ValidLevel2),
	  EV_CHILD_NOTIFY(RR_LEVEL3,CT_INPUT,ValidLevel3),
	  EV_CHILD_NOTIFY(S_LEVEL1,CT_INPUT,SearchLevel1),
	  EV_CHILD_NOTIFY(S_LEVEL2,CT_INPUT,SearchLevel2),
	  EV_CHILD_NOTIFY(S_LEVEL3,CT_INPUT,SearchLevel3),
	  EV_CHILD_NOTIFY(S_NAME,CT_INPUT,SearchName),
	  EV_BN_CLICKED(RR_CREATE,EnableInput),
	  EV_BN_CLICKED(RR_CHANGE,DisableInput),
	  EV_WM_RBUTTONDOWN,
END_RESPONSE_TABLE;

//{{LevelDlg Implementation}}
LevelDlg::LevelDlg (TWindow* parent, TResId resId, TModule* module):
	 TDialog(parent, resId, module)
{
	pxDept = new Px_File(&hDb,"deptdata");
	rslt = pxDept->Open();
	pxBank = new Px_File(&hDb,"bankdata");
	rslt = pxBank->Open();
	pxPers = new Px_File(&hDb,"passdata");
	rslt = pxPers->Open();
	pxTemp = new Px_File(&hDb,"tempdata");
	rslt = pxTemp->Open();

	TTxInp *edit;
	inName = new TTxInp(this,RR_NAME,15);
	edit = new TTxInp(this,RR_IDNTIFICATION,15);
	edit = new TTxInp(this,RR_RE_PASSWORD,10);
	edit = edit;

	pw = new TTxInp(this,RR_PASSWORD,10);
	rb = new TRadioButton(this,RR_CHANGE);

	unsigned short flags = 2+4+32;
	l1 = new TNumericInput(this,RR_LEVEL1,flags,0, 4,8,0,999);//0-999
	l2 = new TNumericInput(this,RR_LEVEL2,flags,0, 4,8,1,999);//0-999
	l3 = new TNumericInput(this,RR_LEVEL3,flags,0, 4,8,1,999);//0-999
	bOk = new TButton(this,ID_OK);
	lst = new ListLevel(pxTemp,(LevelDlg*)this);

	s_name = new TTxInp(this,S_NAME,15);
	s_l1 = new TNumericInput(this,S_LEVEL1,flags,0, 4);//0-999
	s_l2 = new TNumericInput(this,S_LEVEL2,flags,0, 4);//0-999
	s_l3 = new TNumericInput(this,S_LEVEL3,flags,0, 4);//0-999

	pResourceModule = new TModule("CLUBBMP.DLL");

	Msg = new Message(msg_lang);
	CreateTempDB();
}


LevelDlg::~LevelDlg ()
{
	 Destroy();
	 DeleteTempDB();
	 delete Msg;
    pxTemp->Close();
	 delete pxTemp;
	 pxBank->Close();
	 delete pxBank;
	 pxDept->Close();
	 delete pxDept;
	 pxPers->Close();
	 delete pxPers;
	 if(tBitmap)
		 ::DeleteObject(tBitmap);
	 delete pResourceModule;
}


void LevelDlg::SetupWindow ()
{
	TDialog::SetupWindow();
	CheckDlgButton(RR_CREATE,1);
	CheckDlgButton(RR_CHANGE,0);
   CheckDlgButton(SORT_LEVEL,1);
	CheckDlgButton(SORT_NAME,0);

	SetCaption(Msg->GetMsg(MSG_TITLE,FALSE));

	SetDlgItemText(RRS_CH_DATE,Msg->GetMsg(MSG_LAST_MODIFY,FALSE));
	SetDlgItemText(RRS_CRE_DATE,Msg->GetMsg(MSG_CREATION_DATE,FALSE));
	SetDlgItemText(RRS_RPASSWORD,/*Msg->GetMsg(MSG_)*/"Re-Enter Password");
	SetDlgItemText(RRS_PASSWORD,Msg->GetMsg(MSG_PASSWORD));
	SetDlgItemText(RRS_ID,Msg->GetMsg(MSG_IDENTIFICATION));
	SetDlgItemText(RRS_NAME,Msg->GetMsg(MSG_NAME));
	SetDlgItemText(RRS_TILL,Msg->GetMsg(MSG_TILL));
	SetDlgItemText(RRS_DEPARTAMENT,Msg->GetMsg(MSG_DEPARTAMENT));
	SetDlgItemText(RRS_BANK,Msg->GetMsg(MSG_BANK));

	CmFBitmap(OK);
	UI_DATE dat;
	char sir[25];
	dat.Export(sir,date_flags);
	SetDlgItemText(CREATE_DATE,sir);
	SetDlgItemText(CHANGE_DATE,sir);
	lst->Attr.Style;
	lst->Create();
	lst->SetFocus();
	lst->CreateList();
	lst->SetSelIndex(0);
	l2->EnableWindow(FALSE);
	l3->EnableWindow(FALSE);
	bOk->Create();
	bOk->EnableWindow(FALSE);
	bank_dataST bd;
	if(pxBank->Getlw((char*)&bd))
		rb->EnableWindow(FALSE);
}


void LevelDlg::CmOk()
{
	int index = lst->GetSelIndex();
	if(index == -1)
      index = 0; 
	if(IsDlgButtonChecked(RR_CREATE))
	{  int stat;
		if((stat = DataGet())!=1 && stat != 2)
		{
			WARNING("    Worng password !     ");
			pw->SetFocus();
			pw->SetSelection(0,9);
		}
		else
		{
			char sir[5];
         memset(sir,0,sizeof(sir));
			GetDlgItemText(RR_LEVEL2,sir,4);
			int lll = atoi(sir);
			if(lll)
				l3->EnableWindow(TRUE);
			else
				l2->EnableWindow(TRUE);
			rb->EnableWindow(TRUE);
		}
	}
	else
	{
		if(!DataReGet())
		{
			WARNING("    Worng password !     ");
			pw->SetFocus();
			pw->SetSelection(0,9);
		}
	}
	if(IsDlgButtonChecked(SORT_LEVEL))
		lst->CreateList();
	else
      lst->CreateListN();
	lst->SetSelIndex(index);
}
// CreateDlg::DataGet function
int LevelDlg::DataReGet()
{
   int stat;
	char name[16];
	char id[16];
	char password[10];
	char r_password[10];
	personST pers;
	bank_dataST bd;
	dept_dataST dd;
	till_dataST td;
	memset(&pers,0,sizeof(personST));
	memset(&bd,0,sizeof(bank_dataST));
	memset(&dd,0,sizeof(dept_dataST));
	memset(&td,0,sizeof(till_dataST));

	int today;
	UI_DATE tod;
	tod.Export(&today);

	wsprintf(pers.p_id,"%s",person_key.p_id);
   wsprintf(pers.p_password,"%s",person_key.p_password);
	pxPers->Geteq((char*)&pers,"password_key");

	int lev1=0,lev2=0,lev3=0;
	char tmp[5];
	GetDlgItemText(RR_LEVEL1,tmp,4);
	lev1 = atoi(tmp);
	GetDlgItemText(RR_LEVEL2,tmp,4);
	lev2 = atoi(tmp);
	GetDlgItemText(RR_LEVEL3,tmp,4);
	lev3 = atoi(tmp);

	GetDlgItemText(RR_NAME,name,16);
	GetDlgItemText(RR_IDNTIFICATION,id,16);
	GetDlgItemText(RR_PASSWORD,password,10);
	GetDlgItemText(RR_RE_PASSWORD,r_password,10);

	if(strcmp(password,r_password))
		return FALSE;
	wsprintf(pers.p_id,"%s",id);
	Encrypt(password);
	wsprintf(pers.p_password,"%s",password);

	wsprintf(person_key.p_id,"%s",id);
	wsprintf(person_key.p_password,"%s",password);

	if(lev1 && !lev2 && !lev3)
		pers.p_club_acces = 2;
	if(lev1 && lev2 && !lev3)
		pers.p_club_acces = 3;
	if(lev1 && lev2 && lev3)
		pers.p_club_acces = 4;
	pxPers->Updrec((char*)&pers);

	if(lev1 && !lev2 && !lev3) // update bank
	{
		bd.bd_level1=lev1;
		stat=pxBank->Geteq((char*)&bd);
		bd.bd_last_date = today;
		wsprintf(bd.bd_name,"%s",name);
		pxBank->Updrec((char*)&bd);
	}
	else if(lev1 && lev2 && !lev3)//update departament
	{
		dd.dd_level1 = lev1;
		dd.dd_level2 = lev2;
		pxDept->Geteq((char*)&dd);
		dd.dd_last_date = today;
		wsprintf(dd.dd_name,"%s",name);
		pxDept->Updrec((char*)&dd);
	}
	else if(lev1 && lev2 && lev3)//update till
	{
		td.td_level1 = lev1;
		td.td_level2 = lev2;
		td.td_level3 = lev3;
		pxTill->Geteq((char*)&td);
		td.td_last_date = today;
		wsprintf(td.td_name,"%s",name);
		pxTill->Updrec((char*)&td);
	}
	tempST tp;
	tp.t_level1 = lev1;
	tp.t_level2 = lev2;
	tp.t_level3 = lev3;
	pxTemp->Geteq((char*)&tp);
	wsprintf(tp.t_name,"%s",name);
	pxTemp->Updrec((char*)&tp);

	return TRUE;
}

// CreateDlg::DataGet function
int LevelDlg::DataGet()
{
	char name[16];
	char id[16];
	char password[10];
	char r_password[10];
	personST pers;
	bank_dataST bd;
	dept_dataST dd;
	till_dataST td;
	memset(&pers,0,sizeof(personST));
	memset(&bd,0,sizeof(bank_dataST));
	memset(&dd,0,sizeof(dept_dataST));
	memset(&td,0,sizeof(till_dataST));

	int today;
	UI_DATE tod;
	tod.Export(&today);
	int lev1=0,lev2=0,lev3=0;
	char tmp[5];
	GetDlgItemText(RR_LEVEL1,tmp,4);
	lev1 = atoi(tmp);
	GetDlgItemText(RR_LEVEL2,tmp,4);
	lev2 = atoi(tmp);
	GetDlgItemText(RR_LEVEL3,tmp,4);
	lev3 = atoi(tmp);
	int stat;
	char strStatus[60];
	if((stat=Validate(lev1,lev2,lev3)))
	{
		SetDlgItemText(RR_LEVEL1,"");
		SetDlgItemText(RR_LEVEL2,"");
		SetDlgItemText(RR_LEVEL3,"");
		switch(stat)
		{
			case 1:
				 wsprintf(strStatus,"STATUS : Bank %03d doesn't exist.",lev1);
				 SetDlgItemText(RR_STATUS,strStatus);
				 break;
			case 2:
				 wsprintf(strStatus,"STATUS : Dep. %03d.%03d doesn't exist.",
										 lev1,lev2);
				 SetDlgItemText(RR_STATUS,strStatus);
				 break;
			case 3:
				 wsprintf(strStatus,"STATUS : Dep. %03d.%03d is duplicated.",
										 lev1,lev2);
				 SetDlgItemText(RR_STATUS,strStatus);
				 break;
			case 4:
				 wsprintf(strStatus,"STATUS : Till %03d.%03d.%03d is duplicated.",
										 lev1,lev2,lev3);
				 SetDlgItemText(RR_STATUS,strStatus);
				 break;
			case 5:
				 wsprintf(strStatus,"STATUS : Bank %03d is duplicated.",lev1);
				 SetDlgItemText(RR_STATUS,strStatus);
				 break;
			case 6:
				 wsprintf(strStatus,"STATUS : Can't created %03d.%03d.%03d",
				                   lev1,lev2,lev3);
				 SetDlgItemText(RR_STATUS,strStatus);
				 break;
		}
		l1->SetFocus();
		CmFBitmap(EXCLAMATION);
		return 2;
	}
	wsprintf(strStatus,"STATUS : OK");
   CmFBitmap(OK);
	SetDlgItemText(RR_STATUS,strStatus);

	GetDlgItemText(RR_NAME,name,16);
	GetDlgItemText(RR_IDNTIFICATION,id,16);
	GetDlgItemText(RR_PASSWORD,password,10);
	GetDlgItemText(RR_RE_PASSWORD,r_password,10);
	if(strcmp(password,r_password))
		return FALSE;
	wsprintf(pers.p_id,"%s",id);
	Encrypt(password);
	wsprintf(pers.p_password,"%s",password);

	if(lev1 && !lev2 && !lev3) // create new bank
	{
		pers.p_club_acces = 2;
      pers.p_level1 = lev1;
		bd.bd_level1 = lev1;
		wsprintf(bd.bd_name,"%s",name);
		UI_DATE today;
		int tod;
		today.Export(&tod);
		bd.bd_first_date = bd.bd_last_date = tod;
		pxBank->Insrec((char*)&bd);
		tempST tmpd;
		wsprintf(tmpd.t_name,"%s",bd.bd_name);
		tmpd.t_level1 = bd.bd_level1;
		tmpd.t_level2 = 0;
		tmpd.t_level3 = 0;
		pxTemp->Insrec((char*)&tmpd);
	}
	else if(lev1 && lev2 && !lev3)//create new departament
	{
		pers.p_club_acces = 3;
		pers.p_level1 = lev1;
		pers.p_level2 = lev2;
		dd.dd_level1 = lev1;
		dd.dd_level2 = lev2;
		wsprintf(dd.dd_name,"%s",name);
		UI_DATE today;
		int tod;
		today.Export(&tod);
		dd.dd_first_date = dd.dd_last_date = tod;
		pxDept->Insrec((char*)&dd);
		tempST tmpd;
		wsprintf(tmpd.t_name,"%s",dd.dd_name);
		tmpd.t_level1 = dd.dd_level1;
		tmpd.t_level2 = dd.dd_level2;
		tmpd.t_level3 = 0;
		pxTemp->Insrec((char*)&tmpd);

	}
	else if(lev1 && lev2 && lev3)//create new till
	{
		pers.p_club_acces = 4;
		pers.p_level1 = lev1;
		pers.p_level2 = lev2;
		pers.p_level3 = lev3;
		td.td_level1 = lev1;
		td.td_level2 = lev2;
		td.td_level3 = lev3;
		wsprintf(td.td_name,"%s",name);
		UI_DATE today;
		int tod;
		today.Export(&tod);
		td.td_first_date = td.td_last_date = tod;
		pxTill->Insrec((char*)&td);
		tempST tmpd;
		wsprintf(tmpd.t_name,"%s",td.td_name);
		tmpd.t_level1 = td.td_level1;
		tmpd.t_level2 = td.td_level2;
		tmpd.t_level3 = td.td_level3;
		pxTemp->Insrec((char*)&tmpd);
	}
	l1->SetFocus();
	l1->SetSelection(0,3);
	pxPers->Insrec((char*)&pers);
	return TRUE;
}

// CreateDlg::DataSet function
void LevelDlg::DataSet()
{
	int stat = 0;
	char name[16];
	char id[16];
	char password[10];
	char sir[30];
	personST pers;
	bank_dataST bd;
	dept_dataST dd;
	till_dataST td;
	memset(&pers,0,sizeof(personST));
	memset(&bd,0,sizeof(bank_dataST));
	memset(&dd,0,sizeof(dept_dataST));
	memset(&td,0,sizeof(till_dataST));

	char str[15],temp[4];
	memset(str,0,sizeof(str));
	memset(temp,0,sizeof(temp));
	lst->GetSelString(str,12);
	memcpy(temp,str,3);
	int lev1 = atoi(temp);
	memcpy(temp,str + 4,3);
	int lev2 = atoi(temp);
	memcpy(temp,str + 8,3);
	int lev3 = atoi(temp);

	if(lev1 && !lev2 && !lev3) // bank
	{
      bd.bd_level1 = lev1;
		pxBank->Geteq((char*)&bd);

		UI_DATE dat(bd.bd_first_date);
		dat.Export(sir,date_flags);
		SetDlgItemText(CREATE_DATE,sir);

		UI_DATE dat1(bd.bd_last_date);
		dat1.Export(sir,date_flags);
		SetDlgItemText(CHANGE_DATE,sir);

		stat = pxPers->Getlw((char*)&pers,"password_key");
		if(!stat && pers.p_level1 == bd.bd_level1 &&
			pers.p_level2 == 0 && pers.p_level3 == 0)
		{
			wsprintf(name,"%s",bd.bd_name);
			wsprintf(id,"%s",pers.p_id);
			wsprintf(password,"%s",pers.p_password);
		}
		else
		while(!(stat = pxPers->Getnx((char*)&pers)))
		{
			if(!stat && pers.p_level1 == bd.bd_level1 &&
				pers.p_level2 == 0 && pers.p_level3 == 0)
			{
				wsprintf(name,"%s",bd.bd_name);
				wsprintf(id,"%s",pers.p_id);
				wsprintf(password,"%s",pers.p_password);
			}
		}
	}
	else if(lev1 && lev2 && !lev3)// departament
	{
		dd.dd_level1 = lev1;
		dd.dd_level2 = lev2;
		pxDept->Geteq((char*)&dd);

		UI_DATE dat(dd.dd_first_date);
		dat.Export(sir,date_flags);
		SetDlgItemText(CREATE_DATE,sir);

		UI_DATE dat1(dd.dd_last_date);
		dat1.Export(sir,date_flags);
		SetDlgItemText(CHANGE_DATE,sir);

		stat = pxPers->Getlw((char*)&pers,"password_key");
		if(!stat && pers.p_level1 == dd.dd_level1 &&
			pers.p_level2 == dd.dd_level2 && pers.p_level3 == 0)
		{
			wsprintf(name,"%s",dd.dd_name);
			wsprintf(id,"%s",pers.p_id);
			wsprintf(password,"%s",pers.p_password);
		}
		else
		while(!(stat = pxPers->Getnx((char*)&pers)))
		{
			if(!stat && pers.p_level1 == dd.dd_level1 &&
				pers.p_level2 == dd.dd_level2 && pers.p_level3 == 0)
			{
				wsprintf(name,"%s",dd.dd_name);
				wsprintf(id,"%s",pers.p_id);
				wsprintf(password,"%s",pers.p_password);
			}
		}
	}
	else if(lev1 && lev2 && lev3)// till
	{
		td.td_level1 = lev1;
		td.td_level2 = lev2;
		td.td_level3 = lev3;
		pxTill->Geteq((char*)&td);

		UI_DATE dat(td.td_first_date);
		dat.Export(sir,date_flags);
		SetDlgItemText(CREATE_DATE,sir);

		UI_DATE dat1(td.td_last_date);
		dat1.Export(sir,date_flags);
		SetDlgItemText(CHANGE_DATE,sir);

		stat = pxPers->Getlw((char*)&pers,"password_key");
		if(!stat && pers.p_level1 == td.td_level1 &&
			pers.p_level2 == td.td_level2 &&
			pers.p_level3 == td.td_level3)
		{
			wsprintf(name,"%s",td.td_name);
			wsprintf(id,"%s",pers.p_id);
			wsprintf(password,"%s",pers.p_password);
		}
		else
		while(!(stat = pxPers->Getnx((char*)&pers)))
		{
			if(!stat && pers.p_level1 == td.td_level1 &&
				pers.p_level2 == td.td_level2 &&
				pers.p_level3 == td.td_level3)
			{
				wsprintf(name,"%s",td.td_name);
				wsprintf(id,"%s",pers.p_id);
				wsprintf(password,"%s",pers.p_password);
			}
		}
	}
	wsprintf(person_key.p_id,"%s",id);
	wsprintf(person_key.p_password,"%s",password);

	Decrypt(password);
	SetDlgItemInt(RR_LEVEL1,lev1);
	SetDlgItemInt(RR_LEVEL2,lev2);
	SetDlgItemInt(RR_LEVEL3,lev3);
	SetDlgItemText(RR_NAME,name);
	SetDlgItemText(RR_IDNTIFICATION,id);
	Decrypt(password);
	SetDlgItemText(RR_PASSWORD,password);
	SetDlgItemText(RR_RE_PASSWORD,password);
}
// CreateDlg::Validate function
int LevelDlg::Validate(int lev1,int lev2,int lev3)
{
	bank_dataST bd;
	dept_dataST dd;
	till_dataST td;

	memset(&bd,0,sizeof(bank_dataST));
	memset(&dd,0,sizeof(dept_dataST));
	memset(&td,0,sizeof(till_dataST));


	dd.dd_level1 = lev1;
	dd.dd_level2 = lev2;

	td.td_level1 = lev1;
	td.td_level2 = lev2;
	td.td_level3 = lev3;

	if((!lev1 && !lev2 && !lev3) || (!lev2 && lev3) || !lev1)
		return 6; // can't created
	if(lev1 && !lev2 && !lev3)
	{
		bd.bd_level1 = lev1;
		if(!pxBank->Geteq((char*)&bd))
			return 5;// bank is duplicated
	}
	if(lev1 && lev2 && !lev3)
	{

		if(!pxDept->Geteq((char*)&dd))
			return 3;// dep is duplicated
		bd.bd_level1 = lev1;
		if(pxBank->Geteq((char*)&bd))
			return 1;// bank lev1 doesn't exist
		else
			return 0;
	}
	if(lev1 && lev2 && lev3)
	{
		if(!pxTill->Geteq((char*)&td))
			return 4;// till is duplicated
		if(pxDept->Geteq((char*)&dd))
			return 2; // dep. lev1.lev2 doesn't exist
		else
			return 0;
	}
	return 0;
}
// LevelDlg::CmHelp function
void LevelDlg::CmHelp()
{
  INFO("\nHelp isn't implemented yet.");
}

void LevelDlg::EnableInput()
{
 l1->EnableWindow(TRUE);
 l2->EnableWindow(TRUE);
 l3->EnableWindow(TRUE);
 l1->SetFocus();
 l1->SetSelection(0,3);
 bOk->EnableWindow(TRUE);
}

void LevelDlg::DisableInput()
{
 l1->EnableWindow(FALSE);
 l2->EnableWindow(FALSE);
 l3->EnableWindow(FALSE);
 DataSet();
 inName->SetFocus();
 inName->SetSelection(0,14);
 bOk->EnableWindow(TRUE);
}

void LevelDlg::EvRButtonDown(UINT /*modkeys*/, TPoint& point)
{
  TPoint lp = point;
  TPopupMenu *menu = new TPopupMenu();
  menu->AppendMenu(MF_STRING, 200, "Help");
  menu->AppendMenu(MF_SEPARATOR, 0, 0);
  menu->AppendMenu(MF_STRING, IDCANCEL, "Close");
  ClientToScreen(lp);

  menu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, lp, 0, HWindow);
  delete menu;
}

void LevelDlg::CmFBitmap(UINT id)
{
  HDC t = GetDC(GetActiveWindow());  //HWND();
  TDC dc(t);
  ReleaseDC(HWindow,t);
  if(tBitmap) ::DeleteObject(tBitmap);
  tBitmap = pResourceModule->LoadBitmap(id);
  if(tBitmap)
  {
	 TMemoryDC memDC;
	 memDC.SelectObject(TBitmap(tBitmap));
	 dc.BitBlt(100, 360, 34, 37, memDC, 0, 0 );
  }
}

void LevelDlg::EvPaint()
{
  TDialog::EvPaint();
  CmFBitmap(OK);
}


void LevelDlg::ValidLevel1()
{
	int lev1=0;
	char tmp[5];
	bank_dataST bd;
   memset(&bd,0,sizeof(bank_dataST));
	GetDlgItemText(RR_LEVEL1,tmp,4);
	lev1 = atoi(tmp);
	if(!lev1)
		bOk->EnableWindow(FALSE);
	else
		bOk->EnableWindow(TRUE);
	bd.bd_level1 = lev1;
	if(!pxBank->Geteq((char*)&bd))
	{
		l2->EnableWindow(TRUE);
	}
	else
	{
		l2->EnableWindow(FALSE);
		l3->EnableWindow(FALSE);
		SetDlgItemText(RR_LEVEL2,"\0");
		SetDlgItemText(RR_LEVEL3,"\0");
	}
}
void LevelDlg::ValidLevel2()
{
	int lev1=0,lev2=0;
	char tmp[5];
	dept_dataST dd;
	GetDlgItemText(RR_LEVEL1,tmp,4);
	lev1 = atoi(tmp);
	GetDlgItemText(RR_LEVEL2,tmp,4);
	lev2 = atoi(tmp);
	dd.dd_level1 = lev1;
	dd.dd_level2 = lev2;
	if(!pxDept->Geteq((char*)&dd))
	{
		l3->EnableWindow(TRUE);
	}
	else
	{
		l3->EnableWindow(FALSE);
		SetDlgItemText(RR_LEVEL3,"\0");
	}
}
void LevelDlg::ValidLevel3()
{
	int lev1=0,lev2=0,lev3=0;
	char tmp[5];
	till_dataST td;
	GetDlgItemText(RR_LEVEL1,tmp,4);
	lev1 = atoi(tmp);
	GetDlgItemText(RR_LEVEL2,tmp,4);
	lev2 = atoi(tmp);
	GetDlgItemText(RR_LEVEL3,tmp,4);
	lev3 = atoi(tmp);
	td.td_level1 = lev1;
	td.td_level2 = lev2;
	td.td_level3 = lev3;
	if(!pxTill->Geteq((char*)&td))
	{
		 ::MessageBeep(MB_ICONEXCLAMATION);
	}
}

void LevelDlg::CmCancel()
{
	TDialog::CmCancel();
}

void LevelDlg::SortLevel()
{
  char str[50];
  lst->GetSelString(str,29);
  lst->CreateList();
  lst->SetSelString(str,-1);
  if(s_name->IsWindowVisible())
  {
	  s_l1->Show(SW_SHOW);
	  s_l2->Show(SW_SHOW);
	  s_l3->Show(SW_SHOW);
	  s_l1->SetFocus();
	  SetDlgItemText(S_NAME,"");
	  s_name->Show(SW_HIDE);
  }
  bOk->EnableWindow(TRUE);
}

void LevelDlg::SortName()
{
  char str[50];
  lst->GetSelString(str,29);
  lst->CreateListN();
  lst->SetSelString(str,-1);
  if(s_l1->IsWindowVisible())
  {
	  SetDlgItemText(S_LEVEL1,"");
	  SetDlgItemText(S_LEVEL2,"");
	  SetDlgItemText(S_LEVEL3,"");
	  s_l1->Show(SW_HIDE);
	  s_l2->Show(SW_HIDE);
	  s_l3->Show(SW_HIDE);
	  s_name->Show(SW_SHOW);
	  s_name->SetFocus();
  }
  bOk->EnableWindow(TRUE);
}

void LevelDlg::CreateTempDB()
{
	bank_dataST bd;
	dept_dataST dd;
	till_dataST td;

	memset(&bd,0,sizeof(bank_dataST));
	memset(&dd,0,sizeof(dept_dataST));
	memset(&td,0,sizeof(till_dataST));

	tempST tmpd;
	if(!pxBank->Getlw((char*)&bd,"bank_name"))
	{
		do
		{
			wsprintf(tmpd.t_name,"%s",bd.bd_name);
			tmpd.t_level1 = bd.bd_level1;
			tmpd.t_level2 = 0;
			tmpd.t_level3 = 0;
			pxTemp->Insrec((char*)&tmpd);
		}
		while(!pxBank->Getnx((char*)&bd));
	}

	if(!pxDept->Getlw((char*)&dd,"dept_name"))
	{
		do
		{
			wsprintf(tmpd.t_name,"%s",dd.dd_name);
			tmpd.t_level1 = dd.dd_level1;
			tmpd.t_level2 = dd.dd_level2;
			tmpd.t_level3 = 0;
			pxTemp->Insrec((char*)&tmpd);
		}
		while(!pxDept->Getnx((char*)&dd));
	}

	if(!pxTill->Getlw((char*)&td,"till_name"))
	{
		do
		{
			wsprintf(tmpd.t_name,"%s",td.td_name);
			tmpd.t_level1 = td.td_level1;
			tmpd.t_level2 = td.td_level2;
			tmpd.t_level3 = td.td_level3;
			pxTemp->Insrec((char*)&tmpd);
		}
		while(!pxTill->Getnx((char*)&td));
	}
}

void LevelDlg::DeleteTempDB()
{
	tempST tmpd;
	if(!pxTemp->Getlw((char*)&tmpd,"temp_key"))
	{
		do
		{
			pxTemp->Delrec();
		}
		while(!pxTemp->Getnx((char*)&tmpd));
	}
}

void LevelDlg::CmSearch()
{
	if(IsDlgButtonChecked(SORT_LEVEL))
	{
	  if(s_l1->IsWindowVisible())
	  {
		  SetDlgItemText(S_LEVEL1,"");
		  SetDlgItemText(S_LEVEL2,"");
		  SetDlgItemText(S_LEVEL3,"");
		  s_l1->Show(SW_HIDE);
		  s_l2->Show(SW_HIDE);
		  s_l3->Show(SW_HIDE);
	  }
	  else
	  {
		  s_l1->Show(SW_SHOW);
		  s_l2->Show(SW_SHOW);
		  s_l3->Show(SW_SHOW);
		  s_l1->SetFocus();
	  }
	}
	else
	{
	  if(s_name->IsWindowVisible())
	  {
		  SetDlgItemText(S_NAME,"");
		  s_name->Show(SW_HIDE);
	  }
	  else
	  {
		  s_name->Show(SW_SHOW);
		  s_name->SetFocus();
	  }
	}
   bOk->EnableWindow(TRUE);
}

void LevelDlg::SearchLevel1()
{
	char level1[5],item[50];
	bank_dataST bd;
	memset(&bd,0,sizeof(bank_dataST));

	GetDlgItemText(S_LEVEL1,level1,4);
	level1[3] = 0;
	bd.bd_level1 = atoi(level1);

	if(!pxBank->Getge((char*)&bd))
	{
		wsprintf(item,"%03d           %s",bd.bd_level1,
														bd.bd_name);
		lst->SetSelString(item,-1);
	}
}
void LevelDlg::SearchLevel2()
{
	char level1[5],level2[5],item[50];
	dept_dataST dd;
	GetDlgItemText(S_LEVEL1,level1,4);
	GetDlgItemText(S_LEVEL2,level2,4);
	level1[3] = 0;
	level2[3] = 0;
	dd.dd_level1 = atoi(level1);
	dd.dd_level2 = atoi(level2);

	if(!pxDept->Getge((char*)&dd))
	{
		wsprintf(item,"%03d.%03d       %s",dd.dd_level1,
														dd.dd_level2,
														dd.dd_name);
		lst->SetSelString(item,-1);
	}
}
void LevelDlg::SearchLevel3()
{
	char level1[5],level2[5],level3[5],item[50];
	till_dataST td;
	GetDlgItemText(S_LEVEL1,level1,4);
	GetDlgItemText(S_LEVEL2,level2,4);
	GetDlgItemText(S_LEVEL3,level3,4);
	level1[3] = 0;
	level2[3] = 0;
	level3[3] = 0;
	td.td_level1 = atoi(level1);
	td.td_level2 = atoi(level2);
	td.td_level3 = atoi(level3);

	if(!pxTill->Getge((char*)&td))
	{
		wsprintf(item,"%03d.%03d.%03d   %s",td.td_level1,
														td.td_level2,
														td.td_level3,
														td.td_name);
		lst->SetSelString(item,-1);
	}
}
void LevelDlg::SearchName()
{
	char name[16],item[50];
	tempST tp;
	GetDlgItemText(S_NAME,name,15);
	name[15] = 0;
	wsprintf(tp.t_name,"%s",name);
	if(!(rslt = pxTemp->Getge((char*)&tp,"temp_key")))
	{

		if(tp.t_level1 && tp.t_level2 && tp.t_level3)
		{
			wsprintf(item,"%03d.%03d.%03d   %s",tp.t_level1,
															tp.t_level2,
															tp.t_level3,
															tp.t_name);
		}
		else if(tp.t_level1 && tp.t_level2 && !tp.t_level3)
		{
			wsprintf(item,"%03d.%03d       %s", tp.t_level1,
															tp.t_level2,
															tp.t_name);
		}
		else if(tp.t_level1 && !tp.t_level2 && !tp.t_level3)
		{
			wsprintf(item,"%03d           %s",  tp.t_level1,
															tp.t_name);
		}
		lst->SetSelString(item,-1);
	}
}

