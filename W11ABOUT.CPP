//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11about.cpp
//  Written by   : Ioan Ghip
//  Created      : 25.10.1994
//  Updated      : 06.02.1995
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

#include "w11hdrsm.h"
#pragma hdrstop
#include "w11clubm.rh"
#include "w11about.h"
#include "dbd\club_dat.h"

// Reading the VERSIONINFO resource.
class ProjectRCVersion {
public:
	 ProjectRCVersion (TModule *module);
	 virtual ~ProjectRCVersion ();

	 BOOL GetProductName (LPSTR &prodName);
	 BOOL GetProductVersion (LPSTR &prodVersion);
	 BOOL GetCopyright (LPSTR &copyright);
	 BOOL GetDebug (LPSTR &debug);

protected:
	 LPBYTE      TransBlock;
	 void FAR    *FVData;

private:
	 // Don't allow this object to be copied.
	 ProjectRCVersion (const ProjectRCVersion &);
	 ProjectRCVersion & operator =(const ProjectRCVersion &);
};


ProjectRCVersion::ProjectRCVersion (TModule *module)
{
	 char    appFName[255];
	 DWORD   fvHandle;
	 UINT    vSize;

	 FVData = 0;

	 module->GetModuleFileName(appFName, sizeof(appFName));
	 DWORD dwSize = GetFileVersionInfoSize(appFName, &fvHandle);
	 if (dwSize) {
		  FVData  = (void FAR *)new char[(UINT)dwSize];
		  if (GetFileVersionInfo(appFName, fvHandle, dwSize, FVData))
				if (!VerQueryValue(FVData, "\\VarFileInfo\\Translation", (void FAR* FAR*)&TransBlock, &vSize)) {
					 delete FVData;
					 FVData = 0;
				}
	 }
}


ProjectRCVersion::~ProjectRCVersion ()
{
	 if (FVData)
		  delete FVData;
}


BOOL ProjectRCVersion::GetProductName (LPSTR &prodName)
{
	 UINT    vSize;
	 char    subBlockName[255];

	 wsprintf(subBlockName, "\\StringFileInfo\\%08lx\\%s", *(DWORD *)TransBlock, (LPSTR)"ProductName");
	 return FVData ? VerQueryValue(FVData, subBlockName, (void FAR* FAR*)&prodName, &vSize) : FALSE;
}


BOOL ProjectRCVersion::GetProductVersion (LPSTR &prodVersion)
{
	 UINT    vSize;
	 char    subBlockName[255];

	 wsprintf(subBlockName, "\\StringFileInfo\\%08lx\\%s", *(DWORD *)TransBlock, (LPSTR)"ProductVersion");
	 return FVData ? VerQueryValue(FVData, subBlockName, (void FAR* FAR*)&prodVersion, &vSize) : FALSE;
}


BOOL ProjectRCVersion::GetCopyright (LPSTR &copyright)
{
	 UINT    vSize;
	 char    subBlockName[255];

	 wsprintf(subBlockName, "\\StringFileInfo\\%08lx\\%s", *(DWORD *)TransBlock, (LPSTR)"LegalCopyright");
	 return FVData ? VerQueryValue(FVData, subBlockName, (void FAR* FAR*)&copyright, &vSize) : FALSE;
}


BOOL ProjectRCVersion::GetDebug (LPSTR &debug)
{
	 UINT    vSize;
	 char    subBlockName[255];

	 wsprintf(subBlockName, "\\StringFileInfo\\%08lx\\%s", *(DWORD *)TransBlock, (LPSTR)"SpecialBuild");
	 return FVData ? VerQueryValue(FVData, subBlockName, (void FAR* FAR*)&debug, &vSize) : FALSE;
}


// expertAboutDlg Implementation
// Construction/Destruction handling.
expertAboutDlg::expertAboutDlg (TWindow *parent, TResId resId, TModule *module)
	 : TDialog(parent, resId, module)
{
}


expertAboutDlg::~expertAboutDlg ()
{
	 Destroy();
}


void expertAboutDlg::SetupWindow ()
{
	 LPSTR prodName, prodVersion, copyright, debug;
	 // Get the static text who's value is based on VERSIONINFO.
	 TStatic *versionCtrl = new TStatic(this, IDC_VERSION, 255);
	 TStatic *copyrightCtrl = new TStatic(this, IDC_COPYRIGHT, 255);
	 TStatic *debugCtrl = new TStatic(this, IDC_DEBUG, 255);

	 TDialog::SetupWindow();
	 // Process the VERSIONINFO.
	 ProjectRCVersion applVersion(GetModule());

	 // Get the product name, product version and legal copyright strings.
	 applVersion.GetProductName(prodName);
	 applVersion.GetProductVersion(prodVersion);
	 applVersion.GetCopyright(copyright);

	 // IDC_VERSION is the product name and version number, the initial value of IDC_VERSION is
	 // the word Version (in whatever language) product name VERSION product version.
	 char    buffer[255];
	 char    versionName[128];
	 versionCtrl->GetText(versionName, sizeof(versionName));
	 wsprintf(buffer, "%s %s %s", prodName, versionName, prodVersion);
	 versionCtrl->SetText(buffer);

	 copyrightCtrl->SetText(copyright);

	 // Only get the SpecialBuild text if the VERSIONINFO resource is there.
	 if (applVersion.GetDebug(debug))
		  debugCtrl->SetText(debug);
}
//------------------------------------------------------------------------
// End File : w11about.cpp
//------------------------------------------------------------------------

