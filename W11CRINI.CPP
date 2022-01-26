//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : W11CRINI.CPP
//  Written by   : Ioan Ghip
//  Created      : 25.10.1994
//  Updated      : 13.11.1995
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
#include "w11crini.rh"
#include "w11crini.h"

BOOL exitFlag = TRUE;
char oldPath[50];
void GetMyPath(char *path);

DEFINE_RESPONSE_TABLE1(TIniDlg, TDialog)
	 EV_COMMAND(IDOK,CmOk),
	 EV_COMMAND(INI_BROWSE,Browse),
END_RESPONSE_TABLE;

//--------------------------------------------------------------------------
TIniDlg::TIniDlg(TWindow *parent, TResId resId, TModule *module)
			: TDialog(parent, resId, module),
			FilenameData(OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_PATHMUSTEXIST,
							 "Paradox Files (*.db)|*.db|",0, "", "*")

{
}

void TIniDlg::CmOk()
{
  char cale[30];
  GetDlgItemText(INI_EDIT,cale,25);
  //change the default file mode from text to binary
  _fmode = O_BINARY;
  // create a binary file for reading and writing
  int handle;
  char nameFile[60];
  wsprintf(nameFile,"%sclub.ini",oldPath);
  handle = creat(nameFile, S_IREAD |S_IWRITE);
  // write to the file
  write(handle, cale, strlen(cale));
  // close the file
  close(handle);
  exitFlag = FALSE;
  TDialog::CmOk();
}
//--------------------------------------------------------------------------
void TIniDlg::Browse()
{
  char  msg[80];
  if (TFileOpenDialog(this, FilenameData,0,"Browse").Execute() != IDOK) {
	 if (FilenameData.Error != 0) {   // 0 value means user selected Cancel
		wsprintf(msg, "Error: #%ld", FilenameData.Error);
		MessageBox(msg, "WARNING", MB_OK|MB_ICONSTOP);
	 }
	 PostMessage(WM_COMMAND,IDCANCEL,0);
  }
  else
  {
	 wsprintf(msg,"%s",FilenameData.FileName);
	 GetMyPath(msg);
	 SetDlgItemText(INI_EDIT,msg);
  }
  Invalidate();         // Repaint to display the new name
}
//--------------------------------------------------------------------------
void
TIniApp::InitMainWindow()
{
  EnableCtl3d();
  EnableBWCC();
  TWindow* calcWin = new TIniDlg((TWindow*)0);
  MainWindow = new TFrameWindow(0, Name, calcWin, TRUE);
  MainWindow->Attr.Style &= ~(WS_MAXIMIZEBOX | WS_THICKFRAME);
}

TIniApp::TIniApp(const char far* name,char* path) : TApplication(name)
{
	GetMyPath(path);
	wsprintf(oldPath,"%s",path);
}

// GetPathDBD function
int GetPathDBD(char *buff, char *path)
{
	FILE *handle;
	char nameFile[60];
	GetMyPath(path);
	wsprintf(nameFile,"%sclub.ini",path);
	if ((handle = fopen(nameFile, "rt")) == NULL)
		 return 1;
	int i = 0;
	while (!feof(handle))
		buff[i++] = fgetc(handle);
	buff[i-1] = 0;
	fclose(handle);
	return 0;
}
//--------------------------------------------------------------------------
void GetMyPath(char *msg)
{
	int offset = strlen(msg);
	char* end_of_string = msg + (--offset);
	while(end_of_string[0]!= '\\')
	{
		 end_of_string[0] = 0;
		 end_of_string = msg + (--offset);
	}
}
//--------------------------------------------------------------------------
//  End of File: W11CRINI.CPP
//--------------------------------------------------------------------------
