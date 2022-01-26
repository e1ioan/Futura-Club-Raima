
//#include "w11hdrsm.h"
//#pragma hdrstop

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dos.h>
#include <stdarg.h>
#include "w11messg.h"
#include "w11time.h"

char *UI_TIME::_timeStringFormat;
char *UI_TIME::_amPtr;
char *UI_TIME::_pmPtr;

static char	decimalSeparator[]      = { '.', 0 };
static char	timeFormat[]            = { 0 };
static char	timeSeparator[]         = { ':', 0 };
static char _timeColonSeparator[] 	= { ':', 0 };
static char _timeSpaceString[] 		= { ' ', 0 };
static char _timedFormat[] 			= { '%','d', 0 };
static char _time02dFormat[] 		   = { '%','0','2','d', 0 };

// ----- UI_TIME ------------------------------------------------------------
UI_TIME::UI_TIME(void)
{
	Import();
}

UI_TIME::UI_TIME(const UI_TIME &time)
{
	Import(time);
}

UI_TIME::UI_TIME(int hour, int minute, int second, int hundredth)
{
	Import(hour, minute, second, hundredth);
}

UI_TIME::UI_TIME(const char *string, TMF_FLAGS tmFlags)
{
	Import(string, tmFlags);
}

UI_TIME::UI_TIME(int packedTime)
{
	Import(packedTime);
}

UI_TIME::~UI_TIME(void)
{
}

void UI_TIME::Export(int *hour, int *minute, int *second, int *hundredth)
{
	long value1 = value;
	if (value < 0)
		value1 = 0L;
	// Set the integer variables.
	long value2 = value1 / 360000L;
	if (hour)
		*hour = (int)value2;
	value1 -= value2 * 360000L;
	value2 = value1 / 6000L;
	if (minute)
		*minute = (int)value2;
	value1 -= value2 * 6000L;
	value2 = value1 / 100L;
	if (second)
		*second = (int)value2;
	value1 -= value2 * 100L;
	if (hundredth)
		*hundredth = (int)value1;
}

void UI_TIME::Export(char *string, TMF_FLAGS tmFlags)
{
	*string = 0;
	if (value < 0)
		// Unanswered value
		return;
	// Determine the seperator character.
	char *separator = timeSeparator;
	if (FlagSet(tmFlags, TMF_COLON_SEPARATOR))
		separator = _timeColonSeparator;
	else if (FlagSet(tmFlags, TMF_NO_SEPARATOR))
		separator = 0;

	// Determine the time format.
	long hourValue = -1;
	char *format = FlagSet(tmFlags, TMF_ZERO_FILL | TMF_NO_SEPARATOR) ? _time02dFormat : _timedFormat;

	// Format the string.
	int times[4];
	Export(&times[0], &times[1], &times[2], &times[3]);
	if (_timeStringFormat)
	{
		if (FlagSet(tmFlags, TMF_TWELVE_HOUR))
		{
			hourValue = times[0];
			times[0] %= 12;
			if (times[0] == 0)
				times[0] = 12;
		}
		sprintf(string, _timeStringFormat, times[0], times[1], times[2], times[3]);
	}
	else
		for (int i = 0; i < 4; i++)
		{
			// See if the string should contain the value.
			if ((i == 0 && !FlagSet(tmFlags, TMF_NO_HOURS)) ||
			    (i == 1 && !FlagSet(tmFlags, TMF_NO_MINUTES)) ||
			    (i == 2 && FlagSet(tmFlags, TMF_SECONDS)) ||
			    (i == 3 && FlagSet(tmFlags, TMF_HUNDREDTHS)))
			{
				// Append the number separator.
				if (*string)
					strcat(string, (i == 3) ? decimalSeparator : separator);
				// Check for the 12 hour timing.
				if (i == 0 && (FlagSet(tmFlags, TMF_TWELVE_HOUR) ||
							 (timeFormat == 0 && !FlagSet(tmFlags, TMF_TWENTY_FOUR_HOUR))))
				{
					hourValue = times[0];
					times[0] %= 12;
					if (times[0] == 0)
						times[0] = 12;
				}
				// Append the time value.
				char sValue[8];
				sprintf(sValue, *string ? _time02dFormat : format, times[i]);
				strcat(string, sValue);
			}
		}

	// Set the am/pm information.
	if (hourValue >= 0)
	{
		// Append the am/pm string.
		strcat(string, _timeSpaceString);
		strcat(string, (hourValue >= 12) ? _pmPtr : _amPtr);
	}
	// Convert to upper or lower case.
	if (FlagSet(tmFlags, TMF_UPPER_CASE))
		strupr(string);
	else if (FlagSet(tmFlags, TMF_LOWER_CASE))
		strlwr(string);
}

void UI_TIME::Export(int *packedTime)
{
	int hour, minute, second;
	
	if (value < 0)
		*packedTime = -1;
	else
	{
		Export(&hour, &minute, &second);
		*packedTime = (hour << 11) | (minute << 5) | second / 2;
	}
}

TMI_RESULT UI_TIME::Import(void)
{
	// I18N initialization.
	UI_TIME::I18NInitialize();
	struct time info;
	gettime(&info);
	Import(info.ti_hour, info.ti_min, info.ti_sec, info.ti_hund);
	return (TMI_OK);
}

TMI_RESULT UI_TIME::Import(const UI_TIME &time)
{
	// I18N initialization.
	UI_TIME::I18NInitialize();

	// Set the time value according to the passed time.
	value = time.value;
	return (TMI_OK);
}

TMI_RESULT UI_TIME::Import(int hour, int minute, int second, int hundredth)
{
	// I18N initialization.
	UI_TIME::I18NInitialize();

	// Set the time values according to the specified integers.
	if (hour < 0 || hour > 23 || minute < 0 || minute > 59 ||
		second < 0 || second > 59 || hundredth < 0 || hundredth > 99)
		return (TMI_INVALID);
	value = (3600L * hour + 60L * minute + second) * 100 + hundredth;
	return (TMI_OK);
}

TMI_RESULT UI_TIME::Import(const char *string, TMF_FLAGS tmFlags)
{
	// I18N initialization.
	UI_TIME::I18NInitialize();

	// Check for a system time.
	if (!string || !string[0])
		if (FlagSet(tmFlags, TMF_SYSTEM))
			return (UI_TIME::Import());
		else
		{
			value = -1L;
			return TMI_OK;
		}

	// Parse out the string time.
	int time[4];
	time[0] = time[1] = time[2] = time[3] = 0;
	static int maxTime[4] = { 23, 59, 59, 99 };
	char *Separators[4];
	Separators[0] = Separators[1] = timeSeparator;
	Separators[2] = decimalSeparator;
	Separators[3] = 0;

	// The following breaks if there needs to be non-digit stuff before
	// a time (i.e. am 9:00)
	while (*string && !IsDigit(*string))
		string++;
	if (!string[0])
		return (TMI_INVALID); // An invalid time string was entered.
	for (int i = 0; i < 4 && *string && IsDigit(*string); i++)
	{
		int j = 0;
		int value = 0;
		while (IsDigit(*string) &&
			(j < 2 || !FlagSet(tmFlags, TMF_NO_SEPARATOR)))
		{
			value = value * 10 + *string - '0';
			if (value > maxTime[i])
				return (TMI_INVALID);
			string++;
			j++;
		}
		if ((i == 0 && !FlagSet(tmFlags, TMF_NO_HOURS)) ||
		    (i == 1 && !FlagSet(tmFlags, TMF_NO_MINUTES)) ||
		    (i == 2 && FlagSet(tmFlags, TMF_SECONDS)) ||
		    (i == 3 && FlagSet(tmFlags, TMF_HUNDREDTHS)))
			time[i] = value;
		if (!FlagSet(tmFlags, TMF_NO_SEPARATOR))
		{
			char *separator = Separators[i];
			if (*string == ':')
				string++;
			else while (*string == *separator)
				string++, separator++;
		}
	}

	// Find the am/pm string (if any).
	while (*string && !IsAlpha(*string))
		string++;
	if (*string && IsAlpha(*string))
	{
		if (strnicmp(string, _pmPtr, 1) == 0)
		{
			if (time[0] > 12)
				return (TMI_INVALID);
			if (time[0] < 12)
				time[0] += 12;
		}
		else if (strnicmp(string, _amPtr, 1) == 0)
		{
			if (time[0] > 12)
				return (TMI_INVALID);
			if (time[0] == 12)
				time[0] -= 12;
		}
		else
			return (TMI_INVALID); // An invalid time string was entered.
	}

	// Set the time according to the parsed values.
	return (Import(time[0], time[1], time[2], time[3]));
}

TMI_RESULT UI_TIME::Import(int packedTime)
{
	// I18N initialization.
	UI_TIME::I18NInitialize();

	if (packedTime == -1)
	{
		value = -1;		// This can work only because -1 isn't
		return (TMI_OK);	// a valid packed time.
	}
	return(Import((packedTime & 0xF800) >> 11, (packedTime & 0x07E0) >> 5, 2 * (packedTime & 0x001F)));
}

// ----- I18N functions -----------------------------------------------------
static char _initialized = FALSE;
static char _allocated = FALSE;

void UI_TIME::I18NInitialize(int force)
{
	if (_initialized && !force)
		return;
	else if (_allocated)
	{
		delete _amPtr;
		delete _pmPtr;
		_allocated = FALSE;
	}
	_initialized = TRUE;
	_amPtr = "a.m.";
	_pmPtr = "p.m.";
}

void UI_TIME::I18NStatus(int initialized)
{
	_initialized = initialized;
}

void UI_TIME::I18NStore()
{
}

int UI_TIME::I18NTraverse(int)
{
	return (TRUE);
}

