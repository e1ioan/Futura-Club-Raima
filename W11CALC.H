//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11calc.h
//  Written by   : Ioan Ghip
//  Created      : 15.10.1994
//  Updated      : 12.04.1995
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

#if !defined(__W11CALC_H)
#define __W11CALC_H

#define min(a,b)   (((a) <(b)) ? (a) :(b))

const char AppName[] = "Calc"; // Name of app
const int DisplayDigits = 15;  // number of digits in calculator display
const int ID_DISPLAY = 400;    // control ID of display static text

enum TCalcState {CS_FIRST, CS_VALID, CS_ERROR};  // calculator state

// Calculator dialog window object
class TCalc : public TDialog {
  public:
    TCalcState  CalcStatus;
    char        Operator;
    char        Number[DisplayDigits + 1];
    BOOL        Negative;
    double      Operand;

    TCalc(TWindow*,TResId resId = CALCULATOR_DLG);
	 ~TCalc();
    void          SetupWindow();  
    void          FlashButton(char key);
    void          Error();

    void          SetDisplay(double r);
    void          GetDisplay(double& r);
    virtual void  UpdateDisplay();

    void          CheckFirst();
    void          InsertKey(char key);
    void          CalcKey(char key);
    void          Clear();
    void          Tutu(WPARAM);
  protected:
    Message       *Msg;
	 LRESULT       EvCommand(UINT, HWND, UINT);
    DECLARE_RESPONSE_TABLE(TCalc);
};
#endif
