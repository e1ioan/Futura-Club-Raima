//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11zoom.h
//  Written by   : Ioan Ghip
//  Created      : 12.07.1997
//  Updated      : 12.07.1997
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
#if !defined(__w11zoom_h)
#define __w11zoom_h

class TZoomList : public TListBox
{
public:
	 TZoomList (TWindow *parent, int resId = IDC_LIST_MEMBER);
	 virtual ~TZoomList ();
	 char item[50];

	 void CreateList(long); // for numeric key
	 void CreateList(club_memberST*);// for alfa key
	 void CreateListEnd(int);
	 void InsertEnd(int ,int keyType = 0);
	 void InsertHome(int ,int keyType = 0);
	 void InsertPageEnd(int ,int keyType = 0);
	 void InsertPageHome(int ,int keyType = 0);
	 void EvKeyDown(UINT,UINT,UINT);
	 void EvLButtonDown(UINT, TPoint&);
	 void SetActivItem(char *);

	 DECLARE_RESPONSE_TABLE(TZoomList);
	 TWindow *parent;
};

class TZoomDialog : public TDialog
{
public:
	 TZoomDialog(TWindow *parent, TResId resId = ZOOM_DLG,
					 TModule *module = 0);
	 virtual ~TZoomDialog ();

public:
	 virtual void SetupWindow ();

protected:
	 TZoomList *list;
	 TNumericInput	*number;
	 TTxInp *name;
	 TWindow *parent;
	 void CmOk ();
	 void ChangeInNumber ();
	 void ChangeInName ();
	 void RBSortNumber ();
	 void RBSortName ();
	 void ClickedButtonSearch ();
	 void SetParentDlg(int);
DECLARE_RESPONSE_TABLE(TZoomDialog);
};


#endif

