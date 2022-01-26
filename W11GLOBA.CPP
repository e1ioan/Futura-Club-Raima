//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11globa.cpp
//  Written by   : Ioan Ghip
//  Created      : 23.10.1994
//  Updated      : 10.09.1995
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
#include "w11globa.h"

extern int msg_lang;
// Cut string ( for write address on label )
void CutString(char *in,char *out1,char *out2)
{
	int len=strlen(in);
	if(len > 31)
	{
		int offset=31;
		for(offset;offset>=0;offset--)
		{
			 if(in[offset] == ' ')
				 break;
		};
		memcpy(out1,in,offset);
		(out1 + offset)[0] = '\0';
		memcpy(out2,in + offset,(len-offset > 30 ) ? 30 : len-offset);
	}
	else
	{
			memcpy(out1,in,strlen(in));
			(out1 + strlen(in))[0] = '\0';
	}
}
// Data codifying
unsigned int DataCodifyng(unsigned int iday , unsigned int imon ,
								  unsigned int iyear )
{
/*
	//  /d/d/d/d/d/m/m/m/m/y/y/y/y/y/y/y/  int format (codifyng)
	char day = '\0';
	char mon = '\0';
	char year = '\0';
	unsigned int DataCodate = 0, temp = 0;

	if(!iday)
	{
		struct tm *tbloc;
		time_t date;
		date = time(NULL);
		tbloc = localtime(&date);
		day = (char)tbloc->tm_mday;
		mon = (char)(tbloc->tm_mon + 1);
		year = (char)tbloc->tm_year;
		DataCodate = day;
		temp = mon;
		temp <<= 7;
		DataCodate <<= 11;
		DataCodate |= temp;
		temp = year;
		DataCodate |= temp;
	}
	else
	{
		day = (char)iday;
		mon = (char)imon;
		year = (char)iyear;
		DataCodate = day;
		temp = mon;
		temp <<= 7;
		DataCodate <<= 11;
		DataCodate |= temp;
		temp = year;
		DataCodate |= temp;
	}
	return DataCodate;
*/
}
// Data codifying
void DataDeCodifyng(unsigned int dataD,char *dataStr)
{
/*
  memset(dataStr,0,sizeof(dataStr));
  unsigned int temp = dataD;
  temp >>= 11;
  int day = temp;
  temp = dataD;
  temp <<= 5;
  temp >>= 12;
  int mon = temp;
  temp = dataD;
  temp <<= 9;
  temp >>= 9;
  int year = temp;
  club_data clubData;
  ptrFile->Getlw((char*)&clubData,CD_DONATION);
  switch(clubData.cd_date_type)
  {
	 case 0:
		  wsprintf(dataStr,"%02d.%02d.%02d",year,mon,day);
		  break;
	 case 1:
		  wsprintf(dataStr,"%02d.%02d.%02d",mon,day,year);
		  break;
	 case 2:
		  wsprintf(dataStr,"%02d.%02d.%02d",day,mon,year);
		  break;
  }
*/
}

//------------------------------------------------------------------------
// End File : w11globa.cpp
//------------------------------------------------------------------------

