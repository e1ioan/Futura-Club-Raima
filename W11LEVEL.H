//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11level.h
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
#if !defined(__w11level_h)
#define __w11level_h

class LevelDlg : public TDialog {
public:
	 LevelDlg (TWindow* parent, TResId resId = LEVEL_DLG, TModule* module = 0);
	 virtual ~LevelDlg ();
	 ListLevel *lst;
	 TTxInp *inName;
	 void DataSet();
protected:
	 TNumericInput *l1,*l2,*l3,*s_l1,*s_l2,*s_l3;
	 TTxInp *pw,*s_name;
	 TRadioButton *rb;
    TButton *bOk;
	 virtual void SetupWindow ();
	 void CmHelp();
    void CmSearch();
	 int Validate(int,int,int);
	 void ValidLevel1();
	 void ValidLevel2();
	 void ValidLevel3();
	 void CreateTempDB();
    void DeleteTempDB();
	 void SortLevel();
	 void SortName();
	 void SearchLevel1();
	 void SearchLevel2();
	 void SearchLevel3();
	 void SearchName();
	 int DataGet();
	 int DataReGet();
	 void CmOk();
    void CmCancel();
	 void EnableInput();
	 void DisableInput();
	 void EvRButtonDown(UINT,TPoint&);
	 void CmFBitmap(UINT); // Load a Bitmap resource from a DLL.
	 void EvPaint();
	 p_keyST person_key;
private:
	 Message *Msg;
	 Px_File *pxBank;
	 Px_File *pxDept;
	 Px_File *pxPers;
    Px_File *pxTemp;
	 TModule* pResourceModule;
	 HBITMAP tBitmap;     // Handle to Bitmap.
	 DECLARE_RESPONSE_TABLE(LevelDlg);
};


#endif  // __w11level_h sentry.

