//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11listo.h
//  Written by   : Ioan Ghip
//  Created      : 05.05.1995
//  Updated      : 17.09.1995
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

// Sentry, use file only if it's not already included.
#if !defined(__w11listo_h)
#define __w11listo_h

class PasswordDlgOpenTill : public TDialog {
public:
	 PasswordDlgOpenTill (int,int,int,TWindow *parent,
								 TResId resId = PASSWORD,
						       TModule *module = 0);
	 virtual ~PasswordDlgOpenTill ();
public:
	 void SetupWindow ();
	 void  CmOk();
	 TTxInp *editID;
private:
	 Message *Msg;
	 int lev1,lev2,lev3;
	 Px_File *pxPers;// data base accesj
	 void CmHelp();
	 DECLARE_RESPONSE_TABLE(PasswordDlgOpenTill);
};


class ListOpenTill : public TListBox {
public:
	 ListOpenTill(TWindow* parent, int id, TModule* module = 0);
	 virtual ~ListOpenTill ();
	 void SetupWindow();
	 void CreateList();
	 void CreateListN();
	 void EvLButtonDblClk(uint modKeys, TPoint& point);
	 TFont * font; // character's font in list
	 TWindow *parentW;
private:
	 DECLARE_RESPONSE_TABLE(ListOpenTill);
};


#endif                                      // __w11listo_h sentry.
//------------------------------------------------------------------------
// End File : w11listo.h
//------------------------------------------------------------------------

