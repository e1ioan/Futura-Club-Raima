//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11calc.cpp
//  Written by   : Ioan Ghip
//  Created      : 15.10.1994
//  Updated      : 30.09.1995
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

#include "w11calc.rh"
#include "w11calc.h"

#define MSG_CALCULATOR           11003

// DEFINE_RESPONSE_TABLE1
extern int msg_lang;

DEFINE_RESPONSE_TABLE1(TCalc,TDialog)
	EV_CHILD_NOTIFY_ALL_CODES(51,Tutu),
END_RESPONSE_TABLE;

// Calculator constructor.
TCalc::TCalc(TWindow *parent,TResId resId)
  : TDialog(parent, resId)
{
  Clear();
  Msg = new Message(msg_lang);
}
// Calculator destructor.
TCalc::~TCalc()
{
  Destroy();
  delete Msg;
}
// Calculator SetupWindow
void TCalc::SetupWindow()
{
  TDialog::SetupWindow();
  SetCaption(Msg->GetMsg(MSG_CALCULATOR,FALSE));
}

void TCalc::Tutu(WPARAM)
{
    return;
}
void TCalc::FlashButton(char key)
{
  if (key == 0x0D)
      key = '=';  // Treat Enter like '='

  HWND button = GetDlgItem(toupper(key));

  if (button) {
    ::SendMessage(button, BM_SETSTATE, 1, 0);

    for (int delay = 1; delay <= 30000; ++delay)
      ;

    ::SendMessage(button, BM_SETSTATE, 0, 0);
  }
}

LRESULT TCalc::EvCommand(UINT id, HWND hWndCtl, UINT notifyCode)
{
  if (hWndCtl != 0 && notifyCode == BN_CLICKED)
    CalcKey(char(id));  // button notification

  else if (hWndCtl == 0 && notifyCode == 1) {
	 // from an accelerator
    FlashButton(char(id));
    CalcKey(char(id));
  }

  return TDialog::EvCommand(id, hWndCtl, notifyCode);
}

// Set Display text to the current value.
void TCalc::UpdateDisplay()
{
  char  str[DisplayDigits + 2];

  if (Negative)
	 strcpy(str, "-");

  else
	 str[0] = '\0';

  ::SetWindowText(GetDlgItem(ID_DISPLAY), strcat(str, Number));
}

// Clear the calculator.
void TCalc::Clear()
{
  CalcStatus = CS_FIRST;
  strcpy(Number, "0");
  Negative = FALSE;
  Operator = '=';
}

void TCalc::Error()
{
  CalcStatus = CS_ERROR;
  strcpy(Number, "Error");
  Negative = FALSE;
}

void TCalc::SetDisplay(double r)
{
  char*  first;
  char*  last;
  int    charsToCopy;
  char   str[64];

  // limit results of calculations to 7 digits to the right of the dec. point
  r = (floor(r * 10000000L + .5)) / 10000000L;

  sprintf(str, "%0.10f", r);
  first = str;
  Negative = FALSE;

  if (str[0] == '-') {
	 first++;
	 Negative = TRUE;
  }

  if (strlen(first) > DisplayDigits + 1 + 10 )
	 Error();

  else {
	 last = strchr(first, 0);

	 while (last[-1] == '0')
		--last;

	 if (last[-1] == '.')
		--last;

	 charsToCopy = min(DisplayDigits + 1, int(last - first));
	 strncpy(Number, first, charsToCopy);
	 Number[charsToCopy] = 0;
  }
}

void TCalc::GetDisplay(double& r)
{
  r = atof(Number);

  if (Negative)
	 r = -r;
}

void TCalc::CheckFirst()
{
  if (CalcStatus == CS_FIRST) {
	 CalcStatus = CS_VALID;
	 strcpy(Number, "0");
	 Negative = FALSE;
  }
}

void TCalc::InsertKey(char key)
{
  int l = strlen(Number);

  if (l < DisplayDigits) {
	 Number[l] = key;
	 Number[l + 1] = 0;
  }
}

// Process calculator key.
void TCalc::CalcKey(char key)
{
  key = (char)toupper(key);

  if (CalcStatus == CS_ERROR && key != 'C')
	 key = ' ';

  if (key >= '0' && key <= '9') {
	 CheckFirst();

	 if (strcmp(Number, "0") == 0)
		Number[0] = '\0';

	 InsertKey(key);

  } else if (key == '+' || key == '-' || key == '*' ||
				 key == '/' || key == '=' || key == '%' || key == 0x0D) {

	 if (CalcStatus == CS_VALID) {
		CalcStatus = CS_FIRST;
		double  r;
		GetDisplay(r);

		if (key == '%') {
		  switch(Operator) {
			 case '+':
			 case '-':
				r = Operand * r / 100;
				break;

			 case '*':
			 case '/':
				r /= 100;
				break;
		  }
		}

		switch(Operator) {
		  case '+':
			 SetDisplay(Operand + r);
			 break;

		  case '-':
			 SetDisplay(Operand - r);
			 break;

		  case '*':
			 SetDisplay(Operand * r);
			 break;

		  case '/':
			 if (r == 0)
				Error();

			 else
				SetDisplay(Operand / r);
			 break;
		}
	 }

	 Operator = key;
	 GetDisplay(Operand);

  } else
	 switch(key) {
		case '.':
		  CheckFirst();
		  if (!strchr(Number, '.'))
			 InsertKey(key);
		  break;

		case 0x8:
		  CheckFirst();
		  if (strlen(Number) == 1)
			 strcpy(Number, "0");
		  else
			 Number[strlen(Number) - 1] = '\0';
		  break;

		case '_':
		  Negative = !Negative;
		  break;

		case 'C':
		  Clear();
		  break;
	 }
  UpdateDisplay();
}


