//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : W11CRINI.H
//  Written by   : Ioan Ghip
//  Created      : 25.10.1994
//  Updated      : 10.11.1995
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

class TIniDlg : public TDialog {
  public:
	 TIniDlg(TWindow *parent, TResId resId = DIALOG_INI, TModule *module = 0);
	 void CmOk();
	 void Browse();
    TOpenSaveDialog::TData   FilenameData;
  DECLARE_RESPONSE_TABLE(TIniDlg);
};

//--------------------------------------------------------------------------
class TIniApp : public TApplication {
  public:
	 TIniApp(const char far* name, char* path);
	 void   InitMainWindow();
};

