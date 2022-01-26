//--------------------------------------------------------------------------
//  Project      : menutst.ide
//  File Name    : w11stdlg.h
//  Written by   : Ioan Ghip
//  Created      : 24.02.1995
//  Finished     : 05.03.1995
//--------------------------------------------------------------------------
//  Dest. System : windows
//--------------------------------------------------------------------------
//  Libraries    : none
//--------------------------------------------------------------------------
//  Data Files   :
//--------------------------------------------------------------------------
//  Remarks
//--------------------------------------------------------------------------
//  1994 by FUTURA Software s.r.l.
//--------------------------------------------------------------------------


#if !defined(__w11stdlg_h) // Sentry, use file only if it's not
#define __w11stdlg_h		  //  already included.

//{{TDialog = ClubStart}}
class ClubStart : public TDialog {
public:
	 ClubStart(TWindow *parent, TResId resId = _START_,
						TModule *module = 0);
	 virtual ~ClubStart ();

//{{ReadDlgVIRTUAL_BEGIN}}
public:
	 void SetupWindow ();
};

#endif
//--------------------------------------------------------------------------
// End File : w11stdlg.h
//--------------------------------------------------------------------------
