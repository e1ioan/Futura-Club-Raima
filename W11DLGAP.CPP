//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : W11DLGAP.CPP
//  Written by   : Ioan Ghip
//  Created      : 25.10.1994
//  Updated      : 12.10.1995
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
#include <owl\owldefs.h>

#include <string.h>
#include <mem.h>
#include <ver.h>
#include <owl\owlpch.h>
#include <owl\applicat.h>
#include <owl\dialog.h>
#include <owl\static.h>
#pragma hdrstop

#include "w11dlgap.rh"
#include "w11dlgap.h"

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

BOOL ProjectRCVersion::GetFileDescription (LPSTR &fileDescription)
{
	 UINT    vSize;
	 char    subBlockName[255];

	 wsprintf(subBlockName, "\\StringFileInfo\\%08lx\\%s", *(DWORD *)TransBlock, (LPSTR)"FileDescription");
	 return FVData ? VerQueryValue(FVData, subBlockName, (void FAR* FAR*)&fileDescription, &vSize) : FALSE;
}


// AboutDlg Implementation
// Construction/Destruction handling.
AboutDlg::AboutDlg (TWindow *parent, TResId resId, TModule *module)
	 : TDialog(parent, resId, module)
{
}


AboutDlg::~AboutDlg ()
{
	 Destroy();
}


void AboutDlg::SetupWindow ()
{
	 LPSTR prodName, prodVersion, copyright, debug, fileDescription;
	 // Get the static text who's value is based on VERSIONINFO.
	 TStatic *descriptionCtrl = new TStatic(this, IDC_FDESCRIPTION, 255);
	 TStatic *versionCtrl = new TStatic(this, IDC_VERSION, 255);
	 TStatic *copyrightCtrl = new TStatic(this, IDC_COPYRIGHT, 255);
	 TStatic *debugCtrl = new TStatic(this, IDC_DEBUG, 255);

	 TDialog::SetupWindow();
	 // Process the VERSIONINFO.
	 ProjectRCVersion applVersion(GetModule());

	 // Get the product name, product version and legal copyright strings.
	 applVersion.GetFileDescription(fileDescription);
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
	 descriptionCtrl->SetText(fileDescription);

	 // Only get the SpecialBuild text if the VERSIONINFO resource is there.
	 if (applVersion.GetDebug(debug))
		  debugCtrl->SetText(debug);
}


// Encrypt function for encrypt password
void Encrypt(char *data)
{
		strupr(data);
		for(register i=0;i<strlen(data);i++)
			 if(i & 1)
					data[i]+= (i<<1) | 1;
			 else
					data[i]-= (i<<1) | 1;
}

// Decrypt function for decrypt password
void Decrypt(char *data)
{
		for(register i=0;i<strlen(data);i++)
			 if(i & 1)
	  data[i]-= (i<<1) | 1;
		 else
	  data[i]+= (i<<1) | 1;
}

// Cut end spaces
void CutSpace(char *sir)
{
	char *p=sir + strlen(sir)-1;
	while(*p==' ')
		 p--;
	p++;
	*p='\0';
}

// Construction/Destruction handling.
TMessageBox::TMessageBox(TWindow *parent,char *mess,char *tit,
								  TResId resId, TModule *module)
	 : TDialog(parent, resId, module)
{
  memset(title, '\0', 30);
  memset(message, '\0', 80);
  memcpy(title, tit, sizeof(title));  // by Gabi
  memcpy(message, mess, sizeof(message));
}

// TMessageBox::~TMessageBox destructor
TMessageBox::~TMessageBox ()
{
	 Destroy();
}

// TMessageBox::SetupWindow function
void TMessageBox::SetupWindow ()
{
  TDialog::SetupWindow();
  SetCaption(title);  // by Gabi
  SetDlgItemText(MESSAGE,message);
}
//------------------------------------------------------------------------
// End File : W11DLGAP.CPP
//------------------------------------------------------------------------
