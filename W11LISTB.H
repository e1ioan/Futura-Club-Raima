//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11listb.h
//  Written by   : Ioan Ghip
//  Created      : 24.11.1994
//  Finished     : 15.12.1994
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

#if !defined(__w11listb_h) // Sentry, use file only if it's not
#define __w11listb_h		  //  already included.

//{{TDialog = TClubList}}
class TClubList : public TListBox {
public:
	 TClubList (TWindow *parent, int resId = NEWMEMB_LISTBOX);
	 virtual ~TClubList ();
	 char item[50];

	 void CreateList(long); // for numeric key
	 void CreateList(club_memberST*);// for alfa key
	 void CreateListEnd(int);
	 void InsertEnd(int ,int keyType = 0);
	 void InsertHome(int ,int keyType = 0);
	 void InsertPageEnd(int ,int keyType = 0);
	 void InsertPageHome(int ,int keyType = 0);
	 void SetParentDlg(int);
	 void EvKeyDown(UINT,UINT,UINT);
	 void EvLButtonDown(UINT, TPoint&);
	 void SetActivItem(char *);
	 DECLARE_RESPONSE_TABLE(TClubList);
	 TWindow *parent;
//{{TClubListVIRTUAL_END}}
};    //{{TClubList}}

#endif
//--------------------------------------------------------------------------
// End File : w11listb.h
//--------------------------------------------------------------------------
