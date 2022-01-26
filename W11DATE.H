//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11date.h
//  Written by   : Ioan Ghip
//  Created      : 25.01.1995
//  Finished     : 22.02.1995
//--------------------------------------------------------------------------
//  Dest. System : windows
//--------------------------------------------------------------------------
//  Libraries    :
//--------------------------------------------------------------------------
//  Data Files   :
//--------------------------------------------------------------------------
//  Remarks
//--------------------------------------------------------------------------
//  1994 by FUTURA Software s.r.l.
//--------------------------------------------------------------------------

// ----- Include file and environment definition ----------------------------
#if !defined(__Z_DATE_H)
#define __Z_DATE_H

// --------------------------------------------------------------------------
// ----- UI_DATE ------------------------------------------------------------
// --------------------------------------------------------------------------

// --- DTF_FLAGS ------------------------------------------------------------
typedef UIF_FLAGS DTF_FLAGS;
const DTF_FLAGS DTF_NO_FLAGS			= 0x0000;
const DTF_FLAGS DTF_US_FORMAT		 	= 0x0001;
const DTF_FLAGS DTF_EUROPEAN_FORMAT		= 0x0002;
const DTF_FLAGS DTF_JAPANESE_FORMAT		= 0x0004;
const DTF_FLAGS DTF_ASIAN_FORMAT		= 0x0004;
const DTF_FLAGS DTF_MILITARY_FORMAT		= 0x0008;
const DTF_FLAGS DTF_DASH				= 0x0010;
const DTF_FLAGS DTF_SLASH				= 0x0020;
const DTF_FLAGS DTF_ALPHA_MONTH			= 0x0040;
const DTF_FLAGS DTF_DAY_OF_WEEK			= 0x0080;
const DTF_FLAGS DTF_UPPER_CASE			= 0x0100;
const DTF_FLAGS DTF_SHORT_YEAR			= 0x0200;
const DTF_FLAGS DTF_SHORT_MONTH			= 0x0400;
const DTF_FLAGS DTF_SHORT_DAY			= 0x0800;
const DTF_FLAGS DTF_ZERO_FILL			= 0x1000;
const DTF_FLAGS DTF_SYSTEM				= 0x4000;

// --- DTI_RESULT -----------------------------------------------------------
enum DTI_RESULT
{
	DTI_OK = 0,				// Date successfully imported.
	DTI_INVALID,			// Invalid date value or format.
	DTI_AMBIGUOUS,			// Ambiguous month name.
	DTI_INVALID_NAME,		// Invalid month or day-of-week name.
	DTI_VALUE_MISSING, 		// Required date value not present.
	DTI_OUT_OF_RANGE  		// Date out of range.
};

class  UI_DATE
{
public:
	UI_DATE(void);
	UI_DATE(const UI_DATE &date);
	UI_DATE(int year, int month, int day);
	UI_DATE(const char *string, DTF_FLAGS dtFlags = DTF_NO_FLAGS);
	UI_DATE(int packedDate);
	virtual ~UI_DATE(void);
	int DayOfWeek(void);
	int DaysInMonth(void);
	int DaysInYear(void);
	void Export(int *year, int *month, int *day, int *dayOfWeek = NULLP(int));
	void Export(char *string, DTF_FLAGS dtFlags);
	void Export(int *packedDate);
	DTI_RESULT Import(void);
	DTI_RESULT Import(const UI_DATE &date);
	DTI_RESULT Import(int year, int month, int day);
	DTI_RESULT Import(const char *string, DTF_FLAGS dtFlags = DTF_NO_FLAGS);
	DTI_RESULT Import(int packedDate);

	long operator=(long days) { value = days; return (value); }
	long operator=(const UI_DATE &date) { value = date.value; return (value);}
	long operator+(long days) { return (value + days); }
	long operator-(long days) { return (value - days); }
	long operator-(const UI_DATE &date) { return (value - date.value); }
	long operator++(void) { value++; return (value); }
	long operator--(void) { value--; return (value); }
	void operator+=(long days) { value += days; }
	void operator-=(long days) { value -= days; }
	int operator==(const UI_DATE& date) { return (value == date.value); }
	int operator!=(const UI_DATE& date) { return (value != date.value); }
	int operator>(const UI_DATE &date) { return (value > date.value); }
	int operator>=(const UI_DATE &date) { return (value >= date.value); }
	int operator<(const UI_DATE &date) { return (value < date.value); }
	int operator<=(const UI_DATE &date) { return (value <= date.value); }

	void SetBasis(int _basisYear) { basisYear = _basisYear; }
	int GetBasis() { return basisYear; }
private:
	long value;
	int basisYear;

	static void SetString(char *str, int value, int flags);

	// I18N member variables and functions.
public:
	static char _sMonthTable[12][5];
	static char _lMonthTable[12][26];
	static char _sDayTable[7][5];
	static char _lDayTable[7][26];
	static char *_dateNumberFormat;
	static char *_dateStringFormat;

	static void I18NInitialize(int force = FALSE);
	static void I18NStatus(int intialized);
	static void I18NStore();
	static int I18NTraverse(int create = FALSE);
};

#endif
//------------------------------------------------------------------------
// End File : w11date.h
//------------------------------------------------------------------------

