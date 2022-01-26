#if !defined(__W11TIME_H)
#define __W11TIME_H
// --- TMF_FLAGS ---
typedef UIF_FLAGS TMF_FLAGS;
const TMF_FLAGS TMF_NO_FLAGS			   = 0x0000;
const TMF_FLAGS TMF_SECONDS 			   = 0x0001;
const TMF_FLAGS TMF_HUNDREDTHS			= 0x0002;
const TMF_FLAGS TMF_NO_HOURS			   = 0x0004;
const TMF_FLAGS TMF_NO_MINUTES			= 0x0008;
const TMF_FLAGS TMF_TWELVE_HOUR			= 0x0010;
const TMF_FLAGS TMF_TWENTY_FOUR_HOUR	= 0x0020;
const TMF_FLAGS TMF_ZERO_FILL			   = 0x0040;
const TMF_FLAGS TMF_COLON_SEPARATOR		= 0x0080;
const TMF_FLAGS TMF_NO_SEPARATOR		   = 0x0100;
const TMF_FLAGS TMF_UPPER_CASE			= 0x0200;
const TMF_FLAGS TMF_LOWER_CASE			= 0x0400;
const TMF_FLAGS TMF_SYSTEM				   = 0x0800;

// --- TMI_RESULT ---
enum TMI_RESULT
{
	TMI_OK = 0,				// Time successfully imported.
	TMI_INVALID,			// Invalid time value or format.
	TMI_OUT_OF_RANGE,		// Time out of range (used by UIW_TIME)
	TMI_VALUE_MISSING		// Required value not present.
};

class UI_TIME
{
public:
	UI_TIME(void);
	UI_TIME(const UI_TIME &time);
	UI_TIME(int hour, int minute, int second = 0, int hundredth = 0);
	UI_TIME(const char *string, TMF_FLAGS tmFlags = TMF_NO_FLAGS);
	UI_TIME(int packedTime);
	virtual ~UI_TIME(void);
	void Export(int *hour, int *minute, int *second = NULLP(int),
		int *hundredth = NULLP(int));
	void Export(char *string, TMF_FLAGS tmFlags);
	void Export(int *packedTime);
	TMI_RESULT Import(void);
	TMI_RESULT Import(const UI_TIME &time);
	TMI_RESULT Import(int hour, int minute, int second = 0, int hundredth = 0);
	TMI_RESULT Import(const char *string, TMF_FLAGS tmFlags);
	TMI_RESULT Import(int packedTime);

	long operator=(long hundredths) { value = hundredths; return (value); }
	long operator=(const UI_TIME &time) { value = time.value; return (value); }
	long operator+(long hundredths) { return (value + hundredths); }
	long operator+(const UI_TIME &time) { return (value + time.value); }
	long operator-(long hundredths) { return (value - hundredths); }
	long operator-(const UI_TIME &time) { return (value - time.value); }
	long operator++(void) { value++; return (value); }
	long operator--(void) { value--; return (value); }
	void operator+=(long hundredths) { value += hundredths; }
	void operator-=(long hundredths) { value -= hundredths; }
	int operator==(UI_TIME& time) { return (value == time.value); }
	int operator!=(UI_TIME& time) { return (value != time.value); }
	int operator>(UI_TIME& time) { return (value > time.value); }
	int operator>=(UI_TIME& time) { return (value >= time.value); }
	int operator<(UI_TIME& time) { return (value < time.value); }
	int operator<=(UI_TIME& time) { return (value <= time.value); }

private:
	long value;

	// I18N member variables and functions.
public:
	static char *_amPtr;
	static char *_pmPtr;
	static char *_timeStringFormat;

	static void I18NInitialize(int force = FALSE);
	static void I18NStatus(int intialized);
	static void I18NStore();
	static int I18NTraverse(int create = FALSE);
};

#endif
