//--------------------------------------------------------------------------
//  Project      : ALL PROGECTS
//  File Name    : W11DLGAP.H
//  Written by   : Ioan Ghip & Gabriela Oprescu
//  Created      : 12.12.1994
//  Update       : 06.02.1995
//--------------------------------------------------------------------------
//  Dest. System : WINDOWS
//--------------------------------------------------------------------------
//  Libraries    : OWL 2.0
//--------------------------------------------------------------------------
//  Data Files   :
//--------------------------------------------------------------------------
//  Remarks
//--------------------------------------------------------------------------
//  1994, 1995 by FUTURA Software s.r.l.
//--------------------------------------------------------------------------

#if !defined(__w11dlgap_h) // Sentry, use file only if it's not
#define __w11dlgap_h		   //  already included.

// Reading the VERSIONINFO resource.
class ProjectRCVersion {
public:
	 ProjectRCVersion (TModule *module);
	 virtual ~ProjectRCVersion ();

	 BOOL GetProductName (LPSTR &prodName);
	 BOOL GetProductVersion (LPSTR &prodVersion);
	 BOOL GetCopyright (LPSTR &copyright);
	 BOOL GetDebug (LPSTR &debug);
	 BOOL GetFileDescription (LPSTR &fileDescription);
protected:
	 LPBYTE      TransBlock;
	 void FAR    *FVData;

private:
	 // Don't allow this object to be copied.
	 ProjectRCVersion (const ProjectRCVersion &);
	 ProjectRCVersion & operator =(const ProjectRCVersion &);
};

// class for about dialog
class AboutDlg : public TDialog {
public:
	 AboutDlg (TWindow *parent, TResId resId = IDD_ABOUT, TModule *module = 0);
	 virtual ~AboutDlg ();

public:
	 void SetupWindow ();
};

// Encrypt function for encrypt password
void Encrypt(char *data);
// Decrypt function for decrypt password
void Decrypt(char *data);
// Cut end spaces
void CutSpace(char *sir);

// my message box dialog ( one button / two buttons )
class TMessageBox : public TDialog
{
public:
	 TMessageBox(TWindow *parent,char *mess,char *tit, // ONE BUTTON
					 TResId resId, TModule *module = 0);
	 char message[80], title[30];
	 virtual ~TMessageBox();
	 void SetupWindow();
};
// x = message
#define EXIT(x)      TMessageBox(this, x, "Exit", FUTURA_EXIT).Execute()
#define INFO(x)      TMessageBox(this, x, "Info", FUTURA_INFO).Execute()
#define QUESTION(x)  TMessageBox(this, x, "", FUTURA_QUESTION).Execute()
#define WARNING(x)   TMessageBox(this, x, "Warning", MESSAGE_BOX).Execute()
#endif
//--------------------------------------------------------------------------
// End File : W11DLGAP.H
//--------------------------------------------------------------------------
