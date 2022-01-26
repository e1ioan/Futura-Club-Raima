//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : W11CLUBM.CPP
//  Written by   : Ioan Ghip
//  Created      : 25.10.1994
//  Updated      : 13.11.1995
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
#include "p_tekst.h"
#include "w11clubm.rh"
#include "w11clubm.h"
#include "w11start.h"
#include "w11read1.h"
#include "w11passw.h"
#include "w11depwa.h"
#include "w11setpw.h"
#include "w11listb.h"
#include "w11newmb.h"
#include "w11statx.rh"
#include "w11statx.h"
#include "w11stdlg.h"
#include "w11menu.rh"
#include "w11level.rh"
#include "w11listl.h"
#include "w11level.h"
#include "w11calc.rh"
#include "w11calc.h"
#include "w11opent.rh"
#include "w11listo.h"
#include "w11opent.h"
#include "w11ptacc.rh"
#include "w11ptacc.h"
#include "w11crini.rh"
#include "w11crini.h"

#pragma warn -inl
//------------------------------------------------------------------------
#define MSG_FILE                 11159
#define MSG_PRINT                10849
#define MSG_PRINT_SETUP          10565
#define MSG_PASSWORD             10610
#define MSG_EXIT                 10194
#define MSG_BANK_REGISTER        11977
#define MSG_READ_STATISTIC       11978
#define MSG_PRINT_STATISTIC      11979
#define MSG_BANK                 11973
#define MSG_DEPARTAMENT_REGISTER 10903
#define MSG_DEPARTAMENT          10608
#define MSG_TILL_REGISTER        11980
#define MSG_OPEN_TILL            10073
#define MSG_NEW_MEMBER           11981
#define MSG_DEPOSIT					11522
#define MSG_WITHDRAWAL      		11453
#define MSG_READ_TRANSACTION     11982
#define MSG_PRINT_TRANSACTION    11983
#define MSG_SETLEMENT            10601
#define MSG_TILL                 12014
#define MSG_READ_ACCOUNT         11524
#define MSG_PRINT_ACCOUNT        10818
#define MSG_START_DATA           10867
#define MSG_CLUB                 11974
#define MSG_MEMBER               12000
#define MSG_FUTURA               10869
#define MSG_HELP                 10806
#define MSG_DATE                 10094
#define MSG_TIME                 10095
#define MSG_CALCULATOR           11003
#define MSG_OPEN_TILL            10073

#define MAXLANGNO   26 // max. no of langages
#define _NO_ACTIV   10
#define TIMER_ID    20

DBIResult   rslt;               // Value returned from IDAPI functions
hDBIDb      hDb;                // Handle to the database

Px_File  *pxClub;
Px_File  *pxTill;
Px_File  *pxMemb;
char HelpFile[] = "CLUBHLP.HLP";
NewMemberDlg  *newDlg;
LevelDlg *LevelWin;
TTextGadget  *TimeDateText;
BOOL dbdNotEmpty = FALSE;
club_dataST clubDataGlobal;

extern int msg_lang;
extern int date_type;
extern int name_type;
extern DTF_FLAGS date_flags;
extern till_dataST OpenedTill;
extern Px_File *px_text;
extern int Access;
extern BOOL exitFlag;
TMyPrinter* Printer;

// Access = 1 for Club
// Access = 2 for Bank
// Access = 3 for Departament
// Access = 4 for Till
extern personST AccessPerson;
// for identifying the availabe languages in tekst database
BOOL  available_lang[MAXLANGNO];
void SoldInTill(); // new sold in till
extern int GetPathDBD(char *buff, char *path); // get path (data base)
                                               // from wclub.ini
void GetPxError(UINT16 r); // get paradox error (string)
//#define __SEND_TO_OSLO_   0x123  //enable / disable password dialog

// TMyWindow constructor
TMyWindow::TMyWindow(TWindow *parent,const char far *title)
					:TWindow(parent,title)
{
	Init(parent, 0,0);
}
// DEFINE_RESPONSE_TABLE1 for main window
DEFINE_RESPONSE_TABLE1(TMyFrame, TDecoratedFrame)
		EV_WM_TIMER,
		EV_COMMAND(CM_FILEPRINT,menuPrint),
		EV_COMMAND(CM_FILEPRINT_SETUP, menuPrintSetup),
		EV_COMMAND(CM_HELPABOUT, menuAbout),
		EV_COMMAND(CM_CALCULATOR, Calculator),
		EV_COMMAND(CM_HELPINDEX, CmHelpClub),
		EV_COMMAND(CM_HELPUSING_HELP, CmHelpOnHelp),
		EV_COMMAND(READ_ACCOUNT, menuReadAccount),
		EV_COMMAND(STATISTIC, menuStatistic),
		EV_COMMAND(CM_START_REGISTER, menuStartData),
		EV_COMMAND(CM_TILLDEPOSIT_WITHDRAWAL,menuDeposit),
		EV_COMMAND(CM_FILEPASSWORD,menuPassword),
		EV_COMMAND(SET_PASSWORD,menuSetPassword),
		EV_COMMAND(_START_,Start),
		EV_COMMAND(CM_TILLNEW_MEMBER,menuNewMember),
		EV_COMMAND(CRE_5_MEMB,CreateNineNewEmptyMembers),
		EV_COMMAND(CM_BANKREGISTER,CreateBDT),
		EV_COMMAND(CM_DEPARTAMENTREGISTER,CreateBDT),
		EV_COMMAND(CM_TILLREGISTER,CreateBDT),
		EV_COMMAND(CM_FILEDATE,ChangeMenuDate),
		EV_COMMAND(CM_FILETIME,ChangeMenuTime),
		EV_COMMAND(CM_TILLOPEN_TILL,CmOpenTill),
      EV_COMMAND(CM_MEMBERPRINT_ACCOUNT,menuPrintAccount),
		EV_COMMAND_ENABLE(CM_START_REGISTER,CmEnableDep),
		EV_COMMAND_ENABLE(CM_TILLNEW_MEMBER,CmEnableNewMember),
		EV_COMMAND_ENABLE(READ_ACCOUNT,CmEnableReadAccount),
      EV_COMMAND_ENABLE(CM_MEMBERPRINT_ACCOUNT,CmEnableMPrintAccount),
		EV_COMMAND_ENABLE(CM_TILLDEPOSIT_WITHDRAWAL,CmEnableDeposit),
		EV_COMMAND_ENABLE(CM_TILLREGISTER,CmEnableTillRegister),
		EV_COMMAND_ENABLE(CM_TILLOPEN_TILL,CmEnableOpenTill),
		EV_COMMAND_ENABLE(STATISTIC,CmEnableTillStatistic),
		EV_WM_PAINT,
END_RESPONSE_TABLE;

// TMyFrame constructor
TMyFrame::TMyFrame(const char far* title,TWindow* client ) :
						 TDecoratedFrame((TWindow*)0,title, client,TRUE)
{
	flagsMenuTime = flagsMenuDate = MF_ENABLED | MF_STRING | MF_CHECKED;
	out_mess = ora = ziua = TRUE;
	Msg = new Message(msg_lang);
	// create print object
//	Printer = new TMyPrinter;
	pResourceModule = new TModule("CLUB.DLL");
	tMenu = new TMenu(pResourceModule -> LoadMenu(MENU_CLUB), AutoDelete);
	if(!HMENU(*tMenu))
		throw "Error loading menu";
}
// TMyFrame::~TMyFrame destructor
TMyFrame::~TMyFrame()
{
  KillTimer(TIMER_ID);
  delete tMenu;
  delete pResourceModule;
  delete Printer;
  delete Msg;
}
// TMyFrame::ChangeMenuDate function
void TMyFrame::ChangeMenuDate()
{
	TMenu menu(HWindow);
	static y = 1;
	if(y)
	{
		// UNCHECKED
		flagsMenuDate = MF_STRING | MF_UNCHECKED;
		menu.ModifyMenu(CM_FILEDATE,flagsMenuDate,CM_FILEDATE,
							 Msg->GetMsg(MSG_DATE));
		y = 0;
		ziua = FALSE;
	}
	else
	{
		// CHECKED
		flagsMenuDate = MF_STRING | MF_CHECKED;
		menu.ModifyMenu(CM_FILEDATE,flagsMenuDate,CM_FILEDATE,
							 Msg->GetMsg(MSG_DATE));
		y = 1;
		ziua = TRUE;
	}
}
// TMyFrame::ChangeMenuTime functions
void TMyFrame::ChangeMenuTime()
{
	TMenu menu(HWindow);
	static y = 1;
	if(y)
	{
		// UNCHECKED
		flagsMenuTime = MF_STRING | MF_UNCHECKED;
		menu.ModifyMenu(CM_FILETIME,flagsMenuTime,CM_FILETIME,
							 Msg->GetMsg(MSG_TIME));
		y = 0;
		ora = FALSE;
	}
	else
	{
		// CHECKED
		flagsMenuTime = MF_STRING | MF_CHECKED;
		menu.ModifyMenu(CM_FILETIME,flagsMenuTime,CM_FILETIME,
							 Msg->GetMsg(MSG_TIME));
		y = 1;
		ora = TRUE;
	}
}

void TMyFrame::CmEnableNewMember(TCommandEnabler &tce)
{
#if !defined(__SEND_TO_OSLO_)
	if( Access==0 || Access==1 || Access == 2 || Access == 3 )
		tce.Enable(FALSE);
	else
		tce.Enable(TRUE);
#endif
}

void TMyFrame::CmEnableReadAccount(TCommandEnabler &tce)
{
#if !defined(__SEND_TO_OSLO_)
	if( Access==0 || Access==1 || Access == 2 || Access == 3 )
		tce.Enable(FALSE);
	else
		tce.Enable(TRUE);
#endif
}

void TMyFrame::CmEnableMPrintAccount(TCommandEnabler &tce)
{
#if !defined(__SEND_TO_OSLO_)
	if( Access==0 || Access==1 || Access == 2 || Access == 3 )
		tce.Enable(FALSE);
	else
		tce.Enable(TRUE);
#endif
}

void TMyFrame::CmEnableDeposit(TCommandEnabler &tce)
{
#if !defined(__SEND_TO_OSLO_)
	if( Access==0 || Access==1 || Access == 2 || Access == 3 )
		tce.Enable(FALSE);
	else
		tce.Enable(TRUE);
#endif
}

// TMyFrame::CmEnableDep function
void TMyFrame::CmEnableDep(TCommandEnabler &tce)
{
#if !defined(__SEND_TO_OSLO_)
  if( Access==0 || Access >= 3 )
	  tce.Enable(FALSE);
  else
	  tce.Enable(TRUE);
#endif
}

void TMyFrame::CmEnableTillRegister(TCommandEnabler &tce)
{
#if !defined(__SEND_TO_OSLO_)
  if( Access==0 || Access == 4 )
	  tce.Enable(FALSE);
  else
	  tce.Enable(TRUE);
#endif
}

void TMyFrame::CmEnableOpenTill(TCommandEnabler &tce)
{
#if !defined(__SEND_TO_OSLO_)
//  if(Access<=3)
//	  tce.Enable(FALSE);
//  else
//	  tce.Enable(TRUE);
#endif
}

void TMyFrame::CmEnableTillStatistic(TCommandEnabler &tce)
{
#if !defined(__SEND_TO_OSLO_)
  if(Access<=3)
	  tce.Enable(FALSE);
  else
	  tce.Enable(TRUE);
#endif
}
// TMyFrame::Change_Menu function
void TMyFrame::Change_Menu()
{
	switch(Access)
	{
#if !defined(__SEND_TO_OSLO_)
		case 0:delete tMenu;
				 tMenu = new TMenu(pResourceModule->LoadMenu(MENU_START),
										 AutoDelete);
				 break;
#endif
		case 1:delete tMenu;
				 tMenu = new TMenu(pResourceModule->LoadMenu(MENU_CLUB),
										 AutoDelete);
				 break;
		case 2:delete tMenu;
				 tMenu = new TMenu(pResourceModule->LoadMenu(MENU_BANK),
										 AutoDelete);
				 break;
		case 3:delete tMenu;
				 tMenu = new TMenu(pResourceModule->LoadMenu(MENU_DEP),
										 AutoDelete);
				 break;
		case 4:delete tMenu;
				 tMenu = new TMenu(pResourceModule->LoadMenu(MENU_TILL),
										 AutoDelete);
				 break;
	}
	if(!HMENU(*tMenu))
		throw "Error loading menu";
	SetMenu(*tMenu);

	TMenu menu(HWindow);
	Msg->Lang = msg_lang;
	menu.ModifyMenu(0, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
						 (uint)menu.GetSubMenu(0),Msg->GetMsg(MSG_FILE));
#if !defined(__SEND_TO_OSLO_)
	if(Access == 0)
	{
		menu.ModifyMenu(1, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
						 (uint)menu.GetSubMenu(1),Msg->GetMsg(MSG_HELP));

		menu.ModifyMenu(CM_STARTNEW_PASSWORD,MF_STRING,CM_FILEPASSWORD,
							 Msg->GetMsg(MSG_PASSWORD));
		menu.ModifyMenu(CM_TILLOPEN_TILL,MF_STRING,CM_TILLOPEN_TILL,
							 Msg->GetMsg(MSG_OPEN_TILL));
		menu.ModifyMenu(CM_FILEPRINT,MF_STRING,CM_FILEPRINT,
							 Msg->GetMsg(MSG_PRINT));
		menu.ModifyMenu(CM_FILEPRINT_SETUP,MF_STRING,CM_FILEPRINT_SETUP,
							 Msg->GetMsg(MSG_PRINT_SETUP));
		menu.ModifyMenu(CM_FILEPASSWORD,MF_STRING,CM_FILEPASSWORD,
							 Msg->GetMsg(MSG_PASSWORD));
		menu.ModifyMenu(CM_FILEDATE,flagsMenuDate,CM_FILEDATE,
							 Msg->GetMsg(MSG_DATE));
		menu.ModifyMenu(CM_FILETIME,flagsMenuTime,CM_FILETIME,
							 Msg->GetMsg(MSG_TIME));
		menu.ModifyMenu(CM_CALCULATOR,MF_STRING,CM_CALCULATOR,
							 Msg->GetMsg(MSG_CALCULATOR));
		menu.ModifyMenu(CM_EXIT,MF_STRING,CM_EXIT,
							 Msg->GetMsg(MSG_EXIT));
	}
	else
#endif
	if(Access == 1)
	{
		menu.ModifyMenu(1, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(1),Msg->GetMsg(MSG_BANK));
		menu.ModifyMenu(2, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(2),Msg->GetMsg(MSG_DEPARTAMENT));
		menu.ModifyMenu(3, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(3),Msg->GetMsg(MSG_TILL));
		menu.ModifyMenu(4, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(4),Msg->GetMsg(MSG_CLUB));
		menu.ModifyMenu(5, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(5),Msg->GetMsg(MSG_MEMBER));
		menu.ModifyMenu(6, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(6),"F&UTURA");
		menu.ModifyMenu(7, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(7),Msg->GetMsg(MSG_START_DATA));
		menu.ModifyMenu(8, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(8),Msg->GetMsg(MSG_HELP));
	}
	else if(Access == 2)
	{
		menu.ModifyMenu(1, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(1),Msg->GetMsg(MSG_BANK));
		menu.ModifyMenu(2, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(2),Msg->GetMsg(MSG_DEPARTAMENT));
		menu.ModifyMenu(3, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(3),Msg->GetMsg(MSG_TILL));
		menu.ModifyMenu(4, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(4),Msg->GetMsg(MSG_MEMBER));
		menu.ModifyMenu(5, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(5),Msg->GetMsg(MSG_HELP));
	}
	else if(Access == 3)
	{
		menu.ModifyMenu(1, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(1),Msg->GetMsg(MSG_DEPARTAMENT));
		menu.ModifyMenu(2, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(2),Msg->GetMsg(MSG_TILL));
		menu.ModifyMenu(3, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(3),Msg->GetMsg(MSG_MEMBER));
		menu.ModifyMenu(4, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(4),Msg->GetMsg(MSG_HELP));
	}
	else if(Access == 4)
	{
		menu.ModifyMenu(1, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(1),Msg->GetMsg(MSG_TILL));
		menu.ModifyMenu(2, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(2),Msg->GetMsg(MSG_MEMBER));
		menu.ModifyMenu(3, MF_ENABLED | MF_BYPOSITION | MF_POPUP,
							 (uint)menu.GetSubMenu(3),Msg->GetMsg(MSG_HELP));
	}
//---- menu file ----------------------------------------------------------
		memset(Msg->tab,0,150);

		menu.ModifyMenu(CM_FILEPRINT,MF_STRING,CM_FILEPRINT,
							 Msg->GetMsg(MSG_PRINT));

		menu.ModifyMenu(CM_FILEPRINT,MF_STRING,CM_FILEPRINT,
							 Msg->GetMsg(MSG_PRINT));
		menu.ModifyMenu(CM_FILEPRINT_SETUP,MF_STRING,CM_FILEPRINT_SETUP,
							 Msg->GetMsg(MSG_PRINT_SETUP));
		menu.ModifyMenu(CM_FILEPASSWORD,MF_STRING,CM_FILEPASSWORD,
							 Msg->GetMsg(MSG_PASSWORD));
		menu.ModifyMenu(CM_FILEDATE,flagsMenuDate,CM_FILEDATE,
							 Msg->GetMsg(MSG_DATE));
		menu.ModifyMenu(CM_FILETIME,flagsMenuTime,CM_FILETIME,
							 Msg->GetMsg(MSG_TIME));
		menu.ModifyMenu(CM_CALCULATOR,MF_STRING,CM_CALCULATOR,
							 Msg->GetMsg(MSG_CALCULATOR));
		menu.ModifyMenu(CM_EXIT,MF_STRING,CM_EXIT,
							 Msg->GetMsg(MSG_EXIT));
//---- menu bank ----------------------------------------------------------
	if(Access == 1 || Access == 2)
	{
		memset(Msg->tab,0,150);
		menu.ModifyMenu(CM_BANKREGISTER,MF_STRING,CM_BANKREGISTER,
							 Msg->GetMsg(MSG_BANK_REGISTER));
		menu.ModifyMenu(CM_BANKREAD_STATISTIC,MF_STRING,CM_BANKREAD_STATISTIC,
							 Msg->GetMsg(MSG_READ_STATISTIC));
		menu.ModifyMenu(CM_BANKPRINT_STATISTIC,MF_STRING,CM_BANKPRINT_STATISTIC,
							 Msg->GetMsg(MSG_PRINT_STATISTIC));
	}
//---- menu departament ---------------------------------------------------
	if(Access == 1 || Access == 2 || Access == 3)
	{
		memset(Msg->tab,0,150);
		menu.ModifyMenu(CM_DEPARTAMENTREGISTER,MF_STRING,
							 CM_DEPARTAMENTREGISTER,
							 Msg->GetMsg(MSG_DEPARTAMENT_REGISTER));
		menu.ModifyMenu(CM_DEPARTAMENTREAD_STATISTIC,MF_STRING,
							 CM_DEPARTAMENTREAD_STATISTIC,
							 Msg->GetMsg(MSG_READ_STATISTIC));
		menu.ModifyMenu(CM_DEPARTAMENTPRINT_STATISTIC,MF_STRING,
							 CM_DEPARTAMENTPRINT_STATISTIC,
							 Msg->GetMsg(MSG_PRINT_STATISTIC));
	}
//---- menu till ----------------------------------------------------------
	memset(Msg->tab,0,150);
	menu.ModifyMenu(CM_TILLREGISTER,MF_STRING,CM_TILLREGISTER,
						 Msg->GetMsg(MSG_TILL_REGISTER));
	menu.ModifyMenu(CM_TILLOPEN_TILL,MF_STRING,CM_TILLOPEN_TILL,
						 Msg->GetMsg(MSG_OPEN_TILL));
	menu.ModifyMenu(CM_TILLREAD_STATISTIC,MF_STRING,STATISTIC,
						 Msg->GetMsg(MSG_READ_STATISTIC));
	menu.ModifyMenu(CM_TILLPRINT_STATISTIC,MF_STRING,CM_TILLPRINT_STATISTIC,
						 Msg->GetMsg(MSG_PRINT_STATISTIC));
	menu.ModifyMenu(CM_TILLNEW_MEMBER,MF_STRING,CM_TILLNEW_MEMBER,
						 Msg->GetMsg(MSG_NEW_MEMBER));
	menu.ModifyMenu(CM_TILLDEPOSIT_WITHDRAWAL,MF_STRING,
						 CM_TILLDEPOSIT_WITHDRAWAL,
						 Msg->GetMsg(MSG_DEPOSIT));
	// begin sub menu bank till  SETTLEMENT
	memset(Msg->tab,0,150);
	menu.ModifyMenu(CM_SETTLEMENTREAD_TRANSACTION,MF_STRING,
						 CM_SETTLEMENTREAD_TRANSACTION,
						 Msg->GetMsg(MSG_READ_TRANSACTION));
	menu.ModifyMenu(CM_SETTLEMENTPRINT_TRANSACTION,MF_STRING,
						 CM_SETTLEMENTPRINT_TRANSACTION,
						 Msg->GetMsg(MSG_PRINT_TRANSACTION));
//---- menu club ----------------------------------------------------------
	if(Access == 1)
	{
		memset(Msg->tab,0,150);
		menu.ModifyMenu(CM_CLUBREAD_STATISTIC,MF_STRING,CM_CLUBREAD_STATISTIC,
							 Msg->GetMsg(MSG_READ_STATISTIC));
		menu.ModifyMenu(CM_CLUBPRINT_STATISTIC,MF_STRING,CM_CLUBPRINT_STATISTIC,
							 Msg->GetMsg(MSG_PRINT_STATISTIC));
	}
//---- menu member --------------------------------------------------------
		memset(Msg->tab,0,150);
		menu.ModifyMenu(CM_MEMBERREAD_ACCOUNT,MF_STRING,READ_ACCOUNT,
							 Msg->GetMsg(MSG_READ_ACCOUNT));
		menu.ModifyMenu(CM_MEMBERPRINT_ACCOUNT,MF_STRING,CM_MEMBERPRINT_ACCOUNT,
							 Msg->GetMsg(MSG_PRINT_ACCOUNT));
		menu.ModifyMenu(CM_MEMBERWITHDRAWAL,MF_STRING,CM_TILLDEPOSIT_WITHDRAWAL,
							 Msg->GetMsg(MSG_WITHDRAWAL));
//---- menu futura --------------------------------------------------------
	if(Access == 1)
	{
		memset(Msg->tab,0,150);
		menu.ModifyMenu(CM_FUTURA_ACCOUNTREAD_STATISTIC,MF_STRING,
							 CM_FUTURA_ACCOUNTREAD_STATISTIC,
							 Msg->GetMsg(MSG_READ_STATISTIC));
		menu.ModifyMenu(CM_FUTURA_ACCOUNTPRINT_STATISTIC,MF_STRING,
							 CM_FUTURA_ACCOUNTPRINT_STATISTIC,
							 Msg->GetMsg(MSG_PRINT_STATISTIC));
//---- menu start data ----------------------------------------------------
		memset(Msg->tab,0,150);
		menu.ModifyMenu(CM_START_REGISTER,MF_STRING,CM_START_REGISTER,
							 Msg->GetMsg(MSG_START_DATA));
   }
//---- menu help ----------------------------------------------------------
	memset(Msg->tab,0,150);
	menu.ModifyMenu(CM_HELPABOUT,MF_STRING,CM_HELPABOUT,
						 /*Msg->GetMsg(MSG_ABOUT)*/"About");
	DrawMenuBar();
}
// TMyFrame::CanClose for close application
BOOL TMyFrame::CanClose()
{
  int stat;
  if(out_mess)
  {
	  stat = EXIT("\nThis will end your session.");
	  if(stat == IDOK)
		  return TRUE;
	  else
	  {
		 return FALSE;
	  }
  }
  return TRUE;
}
// Paint window's contents on any dc, screen or printer or whatever...
void TMyFrame::EvPaint()
{
	TDecoratedFrame::EvPaint();
}
// TMyFrame::CmOpenTill function
void TMyFrame::CmOpenTill()
{
	OpenTillDlg(this).Execute();
	Change_Menu();
}
// TMyFrame::menuPrint call printout class
void TMyFrame::menuPrint()
{
  char *label[] =
  {
		"\r\nFK\"*\"",
		"\nN",
		"\nQ100,0",
		"\nZT",
		"\nR0,0",
		"\nA68,10,0,2,2,1,N,\"Printer is OK\"",
		"\nP1",
		"\nFK\"*\"\r\n"
  };
  if (Printer)
  {
	 APXPrintOut printout("Printout test");
	 for(int i = 0; i < 8; i++)
		  wsprintf(printout.data.label[i],"%s",label[i]);
	 printout.data.len = 8;
	 Printer->Print(this, printout,TRUE);
  }
}
// TMyFrame::menuPrintSetup call setup printout class
void TMyFrame::menuPrintSetup()
{
  if (Printer)
	 Printer->Setup(this);
}
// TMyFrame::menuPrintSetup call setup printout class
void TMyFrame::menuPrintAccount()
{
	TPrintAccount(this).Execute();
}
// TMyFrame::menuNewMember call new member class
void TMyFrame::menuNewMember()
{
  NewMemberDlg *dlg;
  newDlg = dlg = new NewMemberDlg(this,NEW_MEMBER);
  dlg->Execute();
  delete dlg;
}
// TMyFrame::menuNewMember call new member class
void TMyFrame::CreateBDT()
{
	LevelDlg *dlg = new LevelDlg(this);
	LevelWin = dlg;
	dlg->Execute();
	delete dlg;
}
// TMyFrame::Start function
void TMyFrame::Start()
{
  ClubStart *st = new ClubStart(this,_START_);
  st->Create();
  // DELAY 2000 ms
  for(DWORD dwTicks = GetTickCount();dwTicks + 2000>GetTickCount(););
  st->CmOk();
  delete st;
}
// TMyFrame::CreateNineNewEmptyMembers function
void TMyFrame::CreateNineNewEmptyMembers()
{
	club_memberST member;
	if((rslt = pxMemb->Getlw((char*)&member)))
	{
		for(long i=0;i<9;i++)
		{
			memset(&member,0,sizeof(club_memberST));
			member.m_no=i+1;
			member.m_recruiter=i;
			member.m_mrecs[0]=(int)(i+2);
			wsprintf(member.m_first_name,"%-29.29s","Recruited by Club");
			int today;
			UI_DATE tod;
			tod.Export(&today);
			member.m_registr_date = today;
			for(long t=0;t<9-i-1;t++) (long)member.m_recruits[t]=1L;
			if(i == 8)
			{
				member.m_mrecs[0] = 10;
				member.m_mrecs[1] = 11;
				member.m_mrecs[2] = 12;
				member.m_mrecs[3] = 13;
				member.m_mrecs[4] = 14;
			}
			int stat = pxMemb->Insrec((char*)&member);
		}
		clubDataGlobal.cd_next_member_no = 15;
		clubDataGlobal.cd_members_no = 9;
		rslt = pxClub->Updrec((char*)&clubDataGlobal);
	}
//	else
//     GetPxError(rslt);
}
// TMyFrame::menuAbout function (call about dialog)
void TMyFrame::menuAbout()
{
	AboutDlg(this,IDD_ABOUT).Execute();
}
// TMyFrame::Calculator function
void TMyFrame::Calculator()
{
  TCalc(this,CALCULATOR_DLG).Execute();
}
// TMyFrame::menuStatistic function (call about dialog)
void TMyFrame::menuStatistic()
{
	StatisticDlg(this,STATISTIC).Execute();
}
// TMyFrame::menuStartData call start data dialog
void TMyFrame::menuStartData()
{
	if(StartDataDlg(this,START_DATA).Execute()==IDOK)
		PostMessage(WM_COMMAND,CRE_5_MEMB,0);
	Change_Menu();
}
// TMyFrame::menuReadAccount function (call read dialog)
void TMyFrame::menuReadAccount()
{
  ReadDlg(this,_READ_ACCOUNT_).Execute();
}
// TMyFrame::menuDeposit function (call deposit dialog)
void TMyFrame::menuDeposit()
{
  DepWithDlg(this,DEPOSIT).Execute();
}
// TMyFrame::menuPassword function (call password dialog)
void TMyFrame::menuPassword()
{
#if !defined(__SEND_TO_OSLO_)
  if(PasswordDlg(this,PASSWORD).Execute() == IDCANCEL)
  {
	  out_mess = FALSE;
	  TWindow::CmExit();
  }
  else
#endif
	  Change_Menu();
}
// TMyFrame::menuSetPassword function
void TMyFrame::menuSetPassword()
{
#if !defined(__SEND_TO_OSLO_)
  personST personData;
  memset(&personData,0,sizeof(personST));
  personData.p_club_acces = 1;
  SetPasswordDlg *PS = new SetPasswordDlg(&personData,this,SET_PASSWORD);
  PS->SetCaption("Set password for start data acces");
  int stat = PS->Execute();
  delete PS;
  if(stat == IDOK)
  {
	  PostMessage(WM_COMMAND,CM_START_REGISTER,0);
     Change_Menu();
  }
  else
  {
	  out_mess = FALSE;
	  TWindow::CmExit();
  }
#else
  Change_Menu();
  PostMessage(WM_COMMAND,CM_START_REGISTER,0);
#endif
}
// TMyFrame::EvTimer function
void TMyFrame::EvTimer(UINT)
{
 static oldLang = msg_lang;
 if(msg_lang != oldLang)
 {
	 oldLang = msg_lang;
    Change_Menu();
 }
 char tmp1[50]; // Temporary buffer .
 char tmp2[50]; // Temporary buffer .
 char tmp3[100];
 if(ziua)
 {
	 DTF_FLAGS f = date_flags | DTF_ALPHA_MONTH | DTF_SHORT_MONTH;
	 f &= ~DTF_SLASH;
	 UI_DATE dat;
	 dat.Export(tmp1,f);
 }
 if(ora)
 {
	 UI_TIME tim;
	 tim.Export(tmp2,TMF_UPPER_CASE | TMF_TWELVE_HOUR);
 }
 if(ora && ziua)
	 wsprintf(tmp3,"%s   %s ",tmp1,tmp2);
 if(ora && !ziua)
	 wsprintf(tmp3,"%s ",tmp2);
 if(ziua && !ora)
	 wsprintf(tmp3,"%s ",tmp1);
 if(ora || ziua)
	 // Put the new text in status bar .
	 TimeDateText->SetText(tmp3);
 else
	 TimeDateText->SetText("");
}
// TMyFrame::CmHelp function 
void TMyFrame::CmHelpOnHelp()
{
	WinHelp(HelpFile, HELP_HELPONHELP, 0L );
}
// TMyFrame::CmHelp function
void TMyFrame::CmHelpClub()
{
	WinHelp(HelpFile, HELP_INDEX, 0L );
}
// TMyFrame::SetupWindow function
void TMyFrame::SetupWindow()
{
		TDecoratedFrame::SetupWindow();
      Printer = new TMyPrinter;
		PostMessage(WM_COMMAND,_START_,0);
		SetTimer(TIMER_ID,1000);
		if(!dbdNotEmpty)
			PostMessage(WM_COMMAND,SET_PASSWORD,0);
		Change_Menu();
}
//------------------------------------------------------------------------
void TMyApp::SetupSpeedBar (TMyFrame *frame)
{
	 // Create default toolbar New and associate toolbar buttons with commands.
	 cb = new TControlBar(frame);
	 cb->Insert(*new TButtonGadget(CM_EXIT, CM_EXIT));
	 cb->Insert(*new TSeparatorGadget(10));
	 cb->Insert(*new TButtonGadget(PASSWORD,CM_FILEPASSWORD));
	 cb->Insert(*new TSeparatorGadget(10));
	 cb->Insert(*new TButtonGadget(CM_PRINT,CM_FILEPRINT));
	 cb->Insert(*new TButtonGadget(CM_PRINTSETUP,CM_FILEPRINT_SETUP));
	 cb->Insert(*new TSeparatorGadget(10));
	 cb->Insert(*new TButtonGadget(NEW_MEMBER,CM_TILLNEW_MEMBER));
	 cb->Insert(*new TButtonGadget(OPEN_TILL_BMP,CM_TILLOPEN_TILL));
	 cb->Insert(*new TButtonGadget(STATISTIC,STATISTIC));
	 cb->Insert(*new TButtonGadget(READ_ACCOUNT,READ_ACCOUNT));
	 cb->Insert(*new TButtonGadget(CM_MEMBERPRINT_ACCOUNT,CM_MEMBERPRINT_ACCOUNT));
	 cb->Insert(*new TButtonGadget(DEPOSIT,CM_TILLDEPOSIT_WITHDRAWAL));
	 cb->Insert(*new TSeparatorGadget(10));
	 cb->Insert(*new TButtonGadget(LEVEL_DLG,CM_TILLREGISTER));
	 cb->Insert(*new TButtonGadget(START_DATA,CM_START_REGISTER));
	 cb->Insert(*new TSeparatorGadget(10));
	 cb->Insert(*new TButtonGadget(CALCULATOR,CM_CALCULATOR));
	 TimeDateText = new TTextGadget(0,TGadget::None,
											  TTextGadget::Right,18,"");
	 cb->Insert(*TimeDateText);
	 cb->Insert(*new TButtonGadget(HELP,CM_HELPINDEX));
	 cb->Insert(*new TButtonGadget(CM_ABOUT, CM_HELPABOUT));
	 // Add fly-over help hints.
	 cb->SetHintMode(TGadgetWindow::EnterHints);
	 frame->Insert(*cb, TDecoratedFrame::Top);
}
// TMyApp::InitMainWindow function
void TMyApp::InitMainWindow()
{
	 EnableCtl3d();
	 EnableBWCC();
	 window = new TMyWindow(NULL,"shbt");
	 window->Attr.AccelTable = MENU_CLUB;
	 TMF = new TMyFrame("CLUB PROGRAM",window);
	 nCmdShow = (nCmdShow != SW_SHOWMINNOACTIVE) ? SW_SHOWMAXIMIZED :
																					nCmdShow;
	 sb = new TStatusBar(TMF, TGadget::Recessed,
												TStatusBar::CapsLock        |
												TStatusBar::NumLock         |
												TStatusBar::ScrollLock      |
												TStatusBar::Overtype);
	 TMF->Insert(*sb,TDecoratedFrame::Bottom);
	 MainWindow = TMF;
	 MainWindow->SetIcon(this,FUTURA);
	 SetMainWindow((TFrameWindow*)TMF);
	 SetupSpeedBar(TMF);
}

// Main function
int OwlMain(int /*argc*/, char* argv[])
{
	TBIVbxLibrary vbxLib; // open LIB for VBX control
	int stat;
	DbiInit(NULL);
//---- begin (handle club.ini file) ----------------------------------------
	char path[40];
	if(GetPathDBD(path,argv[0]))
	{
		stat = TIniApp("club.ini",argv[0]).Run();
		if(exitFlag)
			return stat;
		exitFlag = TRUE;
		GetPathDBD(path,argv[0]);
	}
	rslt = OpenBase(&hDb,path, dbiREADWRITE, dbiOPENSHARED);
	do
	{
	  pxClub = new Px_File(&hDb,"clubdata");
	  rslt = pxClub->Open();
	  if(rslt)
	  {
		  delete pxClub;
		  DbiCloseDatabase(&hDb);
		  stat = TIniApp("club.ini",argv[0]).Run();
		  if(exitFlag)
			  return stat;
		  exitFlag = TRUE;
		  GetPathDBD(path,argv[0]);
		  OpenBase(&hDb,path, dbiREADWRITE, dbiOPENSHARED);
	  }
	}
	while(rslt);
//---- end (handle club.ini file) ------------------------------------------

	pxTill = new Px_File(&hDb,"tilldata");
	rslt = pxTill->Open();
	pxMemb = new Px_File(&hDb,"membdata");
	rslt = pxMemb->Open();
	px_text = new Px_File(&hDb,"p_tekst");
	rslt = px_text->Open();

	// create pointer for tekst access
	msg_lang = 2;
	px_tekst str_text; // messages struct
	str_text.text_no = 10001; // first short message in each language
	for(int i = 1; i <= MAXLANGNO; i++)
	{ // look for the available languages in the database
	  str_text.lang_no = i;
	  rslt = px_text->Geteq((char*)&str_text);
	  if(!rslt)
		  available_lang[i-1] = TRUE;
	  else
		  available_lang[i-1] = FALSE;
	}
	// get first record
	rslt = pxClub->Getlw((char*)&clubDataGlobal);
	if(!rslt)
	{
		dbdNotEmpty = TRUE;
		msg_lang = clubDataGlobal.cd_language;
		date_type = clubDataGlobal.cd_date_type;
		name_type = clubDataGlobal.cd_name_type;
		switch(date_type)
		{
		  case 0: date_flags = DTF_JAPANESE_FORMAT | DTF_SLASH | DTF_ZERO_FILL;
					 break;
		  case 1: date_flags = DTF_US_FORMAT | DTF_SLASH | DTF_ZERO_FILL;
					 break;
		  case 2: date_flags = DTF_EUROPEAN_FORMAT | DTF_SLASH | DTF_ZERO_FILL;
					 break;
		}
	}
	else
		dbdNotEmpty = FALSE;
	// run this program
#if defined(__SEND_TO_OSLO_)
	Access = 1;
#endif
	stat = TMyApp().Run();
	// close data base
	px_text->Close();
	delete px_text;
	// close data base
	pxMemb->Close();
	delete pxMemb;
	// close data base
	pxTill->Close();
	delete pxTill;
	// close data base
	pxClub->Close();
	delete pxClub;
	DbiCloseDatabase(&hDb);
	DbiExit();
	return stat;
}
//
//---- GLOBAL FUNCTIONS ----------------------------------------------------
//
void SoldInTill()
{
  // compute new sold (till)
  till_dataST tillData;
  tillData.td_level1 = OpenedTill.td_level1;
  tillData.td_level2 = OpenedTill.td_level2;
  tillData.td_level3 = OpenedTill.td_level3;

  pxTill->Geteq((char*)&tillData);
  tillData.td_sold = (tillData.td_donation_no * clubDataGlobal.cd_donation)+
							(tillData.td_paid_from_depo)+
							(tillData.td_paid_from_dept)+
							(tillData.td_paid_from_bank)-
							(tillData.td_paid_out_to_with)-
							(tillData.td_paid_out_to_dept)-
							(tillData.td_paid_out_to_bank);
  // write today date
  int today;
  UI_DATE tod;
  tod.Export(&today);
  tillData.td_last_date = today;

  pxTill->Updrec((char*)&tillData);
  memcpy(&OpenedTill,&tillData,sizeof(till_dataST));
}
// GetPathDBD function
int GetPathDBD(char *buff)
{
	FILE *handle;
	if ((handle = fopen("club.ini", "rt")) == NULL)
		 return 1;
	int i = 0;
	while (!feof(handle))
		buff[i++] = fgetc(handle);
	buff[i-1] = 0;
	fclose(handle);
   return 0;
}
// GetPxError function
void GetPxError(UINT16 r)
{
  if(r)
  {
	  char *str_err = new char [DBIMAXMSGLEN+1];
	  ::DbiGetErrorString (r, str_err);
	  ::MessageBox(0,str_err,"!!!",MB_OK);
	  delete [] str_err;
  }
}
//------------------------------------------------------------------------
// End File : d11clubm.cpp
//------------------------------------------------------------------------

