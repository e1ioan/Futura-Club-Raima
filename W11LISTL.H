//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11listl.h
//  Written by   : Ioan Ghip
//  Created      : 10.03.1995
//  Updated      : 17.09.1995
//--------------------------------------------------------------------------
//  Dest. System : windows
//--------------------------------------------------------------------------
//  Libraries    :
//--------------------------------------------------------------------------
//  Data Files   :
//--------------------------------------------------------------------------
//  Remarks
//--------------------------------------------------------------------------
//  
//--------------------------------------------------------------------------
// Sentry, use file only if it's not already included.
#if !defined(__w11listl_h)
#define __w11listl_h
class ListLevel : public TListBox {
public:
	 ListLevel (Px_File* px, TWindow* parent, int id = RR_LISTBOX);
	 virtual ~ListLevel ();
	 void SetupWindow();
	 void CreateList();
    void CreateListN();
protected:
	 TFont * font; // character's font in list
	 Px_File *pxBank;
	 Px_File *pxDept;
    Px_File *pxTemp;
	 void SetParentDlg();
	 void EvKeyDown(UINT,UINT,UINT);
	 void EvLButtonDown(UINT, TPoint&);
	 TWindow *parent;
private:
	 DECLARE_RESPONSE_TABLE(ListLevel);

};

#endif  // __w11listl_h sentry.

