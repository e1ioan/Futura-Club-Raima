//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : W11CLUBM.H
//  Written by   : Ioan Ghip
//  Created      : 25.10.1994
//  Updated      : 31.10.1995
//--------------------------------------------------------------------------
//  Dest. System : windows
//--------------------------------------------------------------------------
//  Libraries    : raima
//--------------------------------------------------------------------------
//  Data Files   :
//--------------------------------------------------------------------------
//  Remarks
//--------------------------------------------------------------------------
//  1993 by FUTURA Software s.r.l.
//--------------------------------------------------------------------------
class TMyWindow : public TWindow
{
	public:
		TMyWindow(TWindow *parent,const char far *title);
		TModule*  pResourceModule;
		TMenu*    tMenu;
};
//------------------------------------------------------------------------
class TMyFrame : public TDecoratedFrame 
{
	
public:
		TMyFrame(const char far* title,TWindow*);
		~TMyFrame();
		void SetupWindow();
		void EvPaint();
		void EvTimer(UINT);
		void menuPrint();
		void menuPrintSetup();
		void menuAbout();
		void Calculator();
		void menuStatistic();
		void menuDeposit();
		void menuStartData();
		void menuReadAccount();
		void menuPassword();
		void menuSetPassword();
		void Start();
		void CreateNineNewEmptyMembers();
		void menuNewMember();
		void menuPrintAccount();
		void CreateBDT();
		void Create_Menu();
		void Change_Menu();
		void ChangeMenuDate();
		void ChangeMenuTime();
		void CmHelpOnHelp();
		void CmHelpClub();
		void CmOpenTill();
		BOOL CanClose();

protected:
		void CmEnableDep(TCommandEnabler &tce);
		void CmEnableNewMember(TCommandEnabler &tce);
		void CmEnableReadAccount(TCommandEnabler &tce);
		void CmEnableDeposit(TCommandEnabler &tce);
		void CmEnableTillRegister(TCommandEnabler &tce);
		void CmEnableOpenTill(TCommandEnabler &tce);
		void CmEnableTillStatistic(TCommandEnabler &tce);
		void CmEnableMPrintAccount(TCommandEnabler &tce);
private:
		BOOL out_mess;
		BOOL ora;
		BOOL ziua;
		UINT flagsMenuDate;
		UINT flagsMenuTime;
		Message *Msg;
		TMyFrame* MainWindow;
		TModule*  pResourceModule;
		TMenu *tmenu;
		TMenu*    tMenu;
		DECLARE_RESPONSE_TABLE(TMyFrame);
};
//------------------------------------------------------------------------
class TMyApp : public TApplication
{
	private:
		void SetupSpeedBar(TMyFrame *frame);
	public:
		TMyApp():TApplication(){};
		void InitMainWindow();
		TMyWindow *window;
		TControlBar* cb;
		TStatusBar *sb;
		TMyFrame* TMF;
};
//--------------------------------------------------------------------------
// End File : w11clubm.h
//--------------------------------------------------------------------------

