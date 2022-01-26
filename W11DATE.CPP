//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11date.cpp
//  Written by   : Ioan Ghip
//  Created      : 25.01.1995
//  Updated      : 10.03.1995
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

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dos.h>
#include <stdarg.h>
#include <stdlib.h>
#include "w11messg.h"
#include "w11date.h"

#if !defined(_WHP_)
extern int msg_lang;
#else
extern UINT msg_lang;
#endif

char *UI_DATE::_dateNumberFormat;
char *UI_DATE::_dateStringFormat;
// ----- UI_DATE ------------------------------------------------------------
char UI_DATE::_sMonthTable[12][5];
char UI_DATE::_lMonthTable[12][26];
char UI_DATE::_sDayTable[7][5];
char UI_DATE::_lDayTable[7][26];

static int dateFormat;
static char dateSeparator[4] = { '/',0 };
static char _dateBlankSeparator[] 	= { ' ', 0 };
static char _dateDashSeparator[] 	= { '-', 0 };
static char _dateSlashSeparator[] 	= { '/', 0 };
static char _dateCommaSeparator[] 	= { ',',' ', 0 };
static char _date1strFormat[] 	= { '%','s',' ', 0 };
static char _date02dFormat[] 	= { '%','0','2','d', 0 };
static char _datedFormat[] 		= { '%','d', 0 };

//			 Year sep Month sep Day
static char _dateAsiaFormat[] =
						 { '%','1','%','s','%','4','%','s',
							'%','2','%','s','%','5','%','s',
							'%','3','%','s', 0 };
//			 Day sep Month sep Year
static char _dateEuropeFormat[] =
						 { '%','3','%','s','%','5','%','s',
							'%','2','%','s','%','6','%','s',
							'%','1','%','s', 0 };
//			 Month sep Day sep Year
static char _dateUSFormat[] =
						 { '%','2','%','s','%','5','%','s',
							'%','3','%','s','%','6','%','s',
							'%','1','%','s', 0 };


static int _daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

static int LeapYear(int year)
{
	return ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)));
}

// ----- UI_DATE ------------------------------------------------------------

UI_DATE::UI_DATE(void)
{
	basisYear = 0;
	Import();
}

UI_DATE::UI_DATE(const UI_DATE &date)
{
	basisYear = 0;
	Import(date);
}

UI_DATE::UI_DATE(int year, int month, int day)
{
	basisYear = 0;
	Import(year, month, day);
}

UI_DATE::UI_DATE(const char *string, DTF_FLAGS dtFlags)
{
	basisYear = 0;
	Import(string, dtFlags);
}

UI_DATE::UI_DATE(int packedDate)
{
	basisYear = 0;
	Import(packedDate);
}

UI_DATE::~UI_DATE(void)
{
}

int UI_DATE::DayOfWeek(void)
{
	return ((int)(((value + 1) % 7) + 1));
}

int UI_DATE::DaysInMonth(void)
{
	int year, month;
	int oldBasis = basisYear;
	basisYear = 0;
	Export(&year, &month, NULLP(int));
	basisYear = oldBasis;
	if (month == 2 && LeapYear(year))
		return (29);
	return (_daysInMonth[month - 1]);
}

int UI_DATE::DaysInYear(void)
{
	int year;
	int oldBasis = basisYear;
	basisYear = 0;
	Export(&year, NULLP(int), NULLP(int));
	basisYear = oldBasis;
	return (LeapYear(year) ? 366 : 365);
}

void UI_DATE::Export(int *pYear, int *pMonth, int *pDay, int *pDayOfWeek)
{
	long year = 0, day = 0, month = 0;
	if (value >= 0)
	{
		// Compute the separate date values using algorithm 199 of
		// the CALGO of the ACM.
		long tValue = value - 1721119L;
		year = (tValue * 4 - 1) / 146097L;
		tValue = tValue * 4 - 1 - 146097L * year;
		day = tValue / 4;
		tValue = (day * 4 + 3) / 1461L;
		day = day * 4 + 3 - 1461L * tValue;
		day = (day + 4) / 4;
		month = (5 * day - 3) / 153;
		day = 5 * day - 3 - 153 * month;
		day = (day + 5) / 5;
		year = 100 * year + tValue;
		if (month < 10)
			month += 3;
		else
		{
			month -= 9;
			year++;
		}
	}
	// Set the integer variables.
	if (pYear)
		*pYear = (int)year - basisYear;
	if (pMonth)
		*pMonth = (int)month;
	if (pDay)
		*pDay = (int)day;
	if (pDayOfWeek)
		*pDayOfWeek = DayOfWeek();
}

void UI_DATE::SetString(char *str, int val, int flags)
{
	sprintf(str, (FlagSet(flags, DTF_ZERO_FILL) &&
			  val < 10 ? _date02dFormat : _dateNumberFormat), val);
}

void UI_DATE::Export(char *string, DTF_FLAGS dtFlags)
{
	if (value < 0)
	{
		// Unanswered value
		*string = 0;
		return;
	}

	// Determine the separator character.
	char *yearSeparator, *monthSeparator, *daySeparator;
	if (FlagSet(dtFlags, DTF_MILITARY_FORMAT))
	{
		dtFlags &= (DTF_MILITARY_FORMAT | DTF_UPPER_CASE | DTF_ZERO_FILL |
			DTF_SHORT_YEAR | DTF_SHORT_MONTH | DTF_SYSTEM);
		dtFlags |= DTF_ALPHA_MONTH;
		if (FlagSet(dtFlags, DTF_SHORT_YEAR | DTF_SHORT_MONTH))
			dtFlags |= DTF_SHORT_YEAR | DTF_SHORT_MONTH;
		yearSeparator = monthSeparator = daySeparator = _dateBlankSeparator;
	}
	else if (FlagSet(dtFlags, DTF_DASH))
		yearSeparator = monthSeparator = daySeparator = _dateDashSeparator;
	else if (FlagSet(dtFlags, DTF_SLASH))
		yearSeparator = monthSeparator = daySeparator = _dateSlashSeparator;
	else if (FlagSet(dtFlags, DTF_ALPHA_MONTH | DTF_SHORT_MONTH) &&
		 !FlagSet(dtFlags, DTF_ASIAN_FORMAT))
	{
		yearSeparator = dateSeparator;
		daySeparator = _dateCommaSeparator;
		monthSeparator = _dateBlankSeparator;
	}
	else
		yearSeparator = monthSeparator = daySeparator = dateSeparator;

	// Get the integer date values.
	char year[32], month[32], day[32];
	int yearValue, monthValue, dayValue, dayOfWeekValue;
	Export(&yearValue, &monthValue, &dayValue, &dayOfWeekValue);

	if (!_dateNumberFormat)
		_dateNumberFormat = _datedFormat;

	// Determine the year value.
	if (FlagSet(dtFlags, DTF_SHORT_YEAR))
		sprintf(year, _date02dFormat, yearValue % 100);
	else
		SetString(year, yearValue, dtFlags);

	// Determine the month value.
	if (FlagSet(dtFlags, DTF_SHORT_MONTH))
		strcpy(month, _sMonthTable[--monthValue]);
	else if (FlagSet(dtFlags, DTF_ALPHA_MONTH))
		strcpy(month, _lMonthTable[--monthValue]);
	else
		SetString(month, monthValue, dtFlags);
	if (FlagSet(dtFlags, DTF_MILITARY_FORMAT))
		month[3] = '\0';

	// Determine the day value.
	SetString(day, dayValue, dtFlags);

	char *tString = string;

	// Add the day of week value to the date.
	if (FlagSet(dtFlags, DTF_SHORT_DAY))
		sprintf(tString, _date1strFormat, _sDayTable[dayOfWeekValue - 1]);
	else if (FlagSet(dtFlags, DTF_DAY_OF_WEEK))
		sprintf(tString, _date1strFormat, _lDayTable[dayOfWeekValue - 1]);
	else
		*tString = 0;
	tString += strlen(tString);

	// Format the date according to the country information.
	char *_format = _dateStringFormat;
	if (!_format)
	{
		if (FlagSet(dtFlags, DTF_ASIAN_FORMAT))
		{
			_format = _dateAsiaFormat;
			sprintf(tString, "%s%s%s%s%s", year,yearSeparator, month,
					  monthSeparator,day);

		}
		else if (FlagSet(dtFlags, DTF_EUROPEAN_FORMAT | DTF_MILITARY_FORMAT))
		{
			_format = _dateEuropeFormat;
			sprintf(tString, "%s%s%s%s%s", day,daySeparator,month,
					  monthSeparator,year);

		}
		else if (FlagSet(dtFlags, DTF_US_FORMAT))
		{
			_format = _dateUSFormat;
			sprintf(tString, "%s%s%s%s%s",month,monthSeparator,day,
					  daySeparator,year);
		}
		else if (dateFormat == 2)		// Asian
		{
			_format = _dateAsiaFormat;
			sprintf(tString, "%s%s%s%s%s", year,yearSeparator, month,
					  monthSeparator,day);
		}
		else if (dateFormat == 1)		// European
		{
			_format = _dateEuropeFormat;
			sprintf(tString, "%s%s%s%s%s", day,daySeparator,month,
					  monthSeparator,year);
		}
		else					// US
		{
			_format = _dateUSFormat;
			sprintf(tString, "%s%s%s%s%s",month,monthSeparator,day,
					  daySeparator,year);
		}
	}
	if (FlagSet(dtFlags, DTF_UPPER_CASE))
		strupr(string);
}

void UI_DATE::Export(int *packedDate)
{
	int year, month, day;

	if (value < 0)
		*packedDate = -1;
	else
	{
		int oldBasis = basisYear;
		basisYear = 0;
		Export(&year, &month, &day);
		basisYear = oldBasis;
		*packedDate = ((year - 1980) << 9) | (month << 5) | day;
	}
}

DTI_RESULT UI_DATE::Import(void)
{
	// I18N initialization.
	UI_DATE::I18NInitialize();

	// Set the date values according to the system date.
	time_t t;
	(void)time(&t);
	struct tm *localTime = localtime(&t);
	// Date years are from 1900, don't change this for years past 2000
	Import(1900 + localTime->tm_year, localTime->tm_mon + 1,
			 localTime->tm_mday);
	struct date info;
	getdate(&info);
	Import(info.da_year, info.da_mon, info.da_day);
	return (DTI_OK);
}

DTI_RESULT UI_DATE::Import(const UI_DATE &date)
{
	// I18N initialization.
	UI_DATE::I18NInitialize();

	// Set the date value according to the passed date.
	value = date.value;
	basisYear = date.basisYear;
	return (DTI_OK);
}

DTI_RESULT UI_DATE::Import(int year, int month, int day)
{
	// I18N initialization.
	UI_DATE::I18NInitialize();

	// Make sure year, month and day are valid.
	year += basisYear;
	if (year < 100 && basisYear == 0)
	{
		// year += 1900;
		// Assume two digit years are offsets in the current century
		UI_DATE current;
		int y1;
		current.Export(&y1, NULLP(int), NULLP(int));
		year += y1 - (y1 % 100);
	}
	// Compute the julian date from three integer values using
	// algorithm 199 of CALGO of the ACM.
	if (year <= 0 || month < 1 || month > 12 || day < 1 ||
		(month == 2 && day == 29 && !LeapYear(year)) ||
		((month != 2 || day != 29) && day > _daysInMonth[month-1]))
		return (DTI_INVALID);
	if (month > 2)
		month -= 3;
	else
	{
		month += 9;
		year--;
	}
	value = ((146097L * (year / 100)) / 4) +
			  ((1461L * (year % 100)) / 4) +
			  (153L * month + 2) / 5 + day + 1721119L;

	return (DTI_OK);
}

DTI_RESULT UI_DATE::Import(const char *string, DTF_FLAGS dtFlags)
{
	// I18N initialization.
	UI_DATE::I18NInitialize();

	// Check for a system date.
	if (!string || !string[0])
		if (FlagSet(dtFlags, DTF_SYSTEM))
			return (UI_DATE::Import());
		else
		{
			value = -1L;
			return DTI_OK;
		}
	// Set up the date variables and determine their proper order.
	unsigned date[3];
	date[0] = date[1] = date[2] = 0;
	int year, month, day;
	day = 0; month = 1; year = 2;
	if (FlagSet(dtFlags, DTF_ASIAN_FORMAT))
		day = 2, year = 0;
	else if (FlagSet(dtFlags, DTF_EUROPEAN_FORMAT | DTF_MILITARY_FORMAT))
		;// already set
	else if (FlagSet(dtFlags, DTF_US_FORMAT))
		day = 1, month = 0;
	else if (dateFormat == 2)	// Asia
		day = 2, year = 0;
	else if (dateFormat == 1)	// Europe
		;// already set
	else				// US
		day = 1, month = 0;

	// Parse out the string date.
	while (*string && !IsDigit(*string) && !IsAlpha(*string))
		string++;
	for (int i = 0; i < 3 && *string; i++)
	{
		if (IsDigit(*string))
		{
			char *endptr;
			date[i] = (unsigned)strtoul(string, &endptr, 10);
			string = endptr;
		}
		else if (IsAlpha(*string))
		{
			int found = FALSE;
			const char *tString = string;
			while (*string && IsAlpha(*string))
				string++;
			for (int j = 0; j < 12; j++)
				if (strnicmp(tString, _lMonthTable[j],
					 (int)(string - tString)) == 0 ||
					 stricmp(tString, _sMonthTable[j]) == 0)
				{
					if (found)
					{
						value = -1L;
						return DTI_AMBIGUOUS;
					}
					date[i] = j + 1;
					if (year == i)
						year = month;
					else if (day == i)
						day = month;
					month = i;
					found = TRUE;
				}
			if (!found)
				i--;
		}
		while (*string && !IsDigit(*string) && !IsAlpha(*string))
			string++;
	}
	if (i != 3)	// We didn't parse out a complete date...
		return (DTI_INVALID);

	// Set the date according to the parsed values.
	return (Import(date[year], date[month], date[day]));
}

DTI_RESULT UI_DATE::Import(int packedDate)
{
	// I18N initialization.
	UI_DATE::I18NInitialize();

	if (packedDate == -1)
	{
		value = -1;		// This can work only because -1 isn't
		return (DTI_OK);	// a valid packed date.
	}
	return(Import(1980 + (((int)(packedDate & 0xFE00)) >> 9),
				((int)(packedDate & 0x01E0)) >> 5, packedDate & 0x001F));
}

// ----- I18N functions -----------------------------------------------------
static char _initialized = FALSE;
#if !defined(_WHP_)
static int oldLang = msg_lang;
#else
static int oldLang = msg_lang;
#endif
void UI_DATE::I18NInitialize(int force)
{
#if !defined(_WHP_)
	if (_initialized && !force && (msg_lang == oldLang))
#else
	if (_initialized && !force && (msg_lang == oldLang))
#endif
		return;
	_initialized = TRUE;
	// definition of abbreviated month names.
	
#define START1 10432
#if !defined(_WHP_)
  oldLang = msg_lang;
  Message Msg(msg_lang);
#else
  oldLang = msg_lang;
  Message Msg(msg_lang);
#endif

	
	// definition of abbreviated month names.
	for(int i = 0;i < 12;i++)
		 wsprintf(_sMonthTable[i],"%-3.3s.",Msg.GetMsg(START1+i,FALSE));

	// definition of full month names.
	for(i = 0;i < 12;i++)
		 wsprintf(_lMonthTable[i],"%-s",Msg.GetMsg(START1+i,FALSE));

#define START2 10418
	// definition of abbreviated day names.
	for(i = 0;i < 7;i++)
		 wsprintf(_sDayTable[i],"%-3.3s.",Msg.GetMsg(START2+i,FALSE));

	// definition of full day names.
	for(i = 0;i < 7;i++)
		 wsprintf(_lDayTable[i],"%-s",Msg.GetMsg(START2+i,FALSE));
}

void UI_DATE::I18NStatus(int initialized)
{
	_initialized = initialized;
}

void UI_DATE::I18NStore()
{
}

int UI_DATE::I18NTraverse(int)
{
	return (TRUE);
}
//------------------------------------------------------------------------
// End File : w11date.cpp
//------------------------------------------------------------------------

