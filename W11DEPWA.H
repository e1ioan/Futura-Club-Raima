//--------------------------------------------------------------------------
//  Project      : menutst.ide
//  File Name    : dep_with.h
//  Written by   : Ioan Ghip
//  Created      : 15.10.1994
//  Finished     : 26.06.1995
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


#if !defined(__dep_with_h) // Sentry, use file only if it's not
#define __dep_with_h		  //  already included.

//{{TDialog = DepWithDlg}}
class DepWithDlg : public TDialog {
public:
	 DepWithDlg (TWindow *parent, TResId resId = READ_ACCOUNT,
						TModule *module = 0);
	 virtual ~DepWithDlg ();

protected:
	 void Search();
	 void SetDataDlg(club_memberST);
	 void EnableControls(BOOL);
	 void CmWithdraw();
	 void CmDeposit();
	 void CmOk();
	 int Validate();
	 void PrintStart();
	 void SetDataPrint(DataPrint *data);
	 Message *Msg;
	 TVbxSSView *list;
    club_memberST thisMember;
private:
	 HSS hss;
	 double newRange,oldBalance,newBalance,sumDW;
	 double WithFee;
	 long mnt;
	 long noFound;
	 char far strData[19][2][20];
	 char far dateTab[5][40];
	 long SearchNumber;
	 TEdit *edit0;
	 TNumericInput *edit1;
	 TButton *ok_button;
	 void SetupWindow ();
    void CmHelp();
	 DECLARE_RESPONSE_TABLE(DepWithDlg);
};

#endif
//--------------------------------------------------------------------------
// End File : dep_with.h
//--------------------------------------------------------------------------

