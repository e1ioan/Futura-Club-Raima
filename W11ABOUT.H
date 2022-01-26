//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11about.h
//  Written by   : Ioan Ghip
//  Created      : 15.10.1994
//  Finished     : 18.11.1994
//--------------------------------------------------------------------------
//  Dest. System : windows
//--------------------------------------------------------------------------
//  Libraries    : raima
//--------------------------------------------------------------------------
//  Data Files   :
//--------------------------------------------------------------------------
//  Remarks
//--------------------------------------------------------------------------
//  1994 by FUTURA Software s.r.l.
//--------------------------------------------------------------------------


#if !defined(__xprtabtd_h)              // Sentry, use file only if it's not already included.
#define __xprtabtd_h


//{{TDialog = expertAboutDlg}}
class expertAboutDlg : public TDialog {
public:
	 expertAboutDlg (TWindow *parent, TResId resId = IDD_ABOUT, TModule *module = 0);
	 virtual ~expertAboutDlg ();

//{{expertAboutDlgVIRTUAL_BEGIN}}
public:
	 void SetupWindow ();
//{{expertAboutDlgVIRTUAL_END}}
};    //{{expertAboutDlg}}


#endif                                      // __xprtabtd_h sentry.
//--------------------------------------------------------------------------
// End File : w11about.h
//--------------------------------------------------------------------------

