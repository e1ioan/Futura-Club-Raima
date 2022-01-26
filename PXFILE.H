//--------------------------------------------------------------------------
//  Project      :
//  File Name    : PXFILE.H
//  Written by   : IONITA SORIN
//  Created      : 29.06.1995
//  Updated      : 19.09.1995 by Mihaela Popescu
//--------------------------------------------------------------------------
//  Dest. System : WINDOWS
//--------------------------------------------------------------------------
//  Libraries    : BDE
//--------------------------------------------------------------------------
//  Data Files   : NONE
//--------------------------------------------------------------------------
//  Remarks      : HEADER FILE FOR  PXFILE.CPP
//--------------------------------------------------------------------------
//  
//--------------------------------------------------------------------------

#if !defined(__PXFILE_H)
#define __PXFILE_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <idapi.h>

DBIResult OpenBase
	(hDBIDb *hdb, char *dirwork,
	 DBIOpenMode eOpenMode=dbiREADWRITE,
	 DBIShareMode eShareMode=dbiOPENSHARED);

class Px_File
{
public:
	 DBIResult   rslt;               // Value returned from IDAPI functions
	 hDBIDb      *phdb;              // Handle to the database
	 hDBICur     hCur;               // Handle to the table
	 pBYTE       pRecBuf;            // Pointer to the record buffer
	 CURProps    curProps;           // Properties of the table
	 char *descfield;

 char *FileName;

 DBIResult Open(DBIOpenMode eOpenMode=dbiREADWRITE,
					 DBIShareMode eShareMode=dbiOPENSHARED);
 DBIResult Close();
 DBIResult putrec(char *inreg);//char*
 DBIResult getrec(char *inreg);
 DBIResult Geteq(char *inreg, char *Namekey=NULL, DBILockType eLock=dbiNOLOCK);
 DBIResult Updrec(char *inreg);
 DBIResult Delrec();
 DBIResult Insrec(char *inreg);//char*
 DBIResult Getlt(char *inreg, char *Namekey=NULL, DBILockType eLock=dbiNOLOCK);
 DBIResult Getle(char *inreg, char *Namekey=NULL, DBILockType eLock=dbiNOLOCK);
 DBIResult Getgt(char *inreg, char *Namekey=NULL, DBILockType eLock=dbiNOLOCK);
 DBIResult Getge(char *inreg, char *Namekey=NULL, DBILockType eLock=dbiNOLOCK);
 DBIResult Getlw(char *inreg, char *Namekey=NULL, DBILockType eLock=dbiNOLOCK);
 DBIResult Gethi(char *inreg, char *Namekey=NULL, DBILockType eLock=dbiNOLOCK);
 DBIResult Getnx(char *inreg, DBILockType eLock=dbiNOLOCK);
 DBIResult Getpr(char *inreg, DBILockType eLock=dbiNOLOCK);
 // Begin - by Miha
 DBIResult InitRecord(char *inreg);
 DBIResult GetRelativeRec
 (char *inreg, char *Namekey, long iPosOffset, DBILockType eLock=dbiNOLOCK);
 long GetRecordCount();
 DBIResult BeginLinkMode (hDBICur *, int, int *, int*, char *); // by Miha
 DBIResult EndLinkMode (hDBICur *hCDetail);
 DBIResult SwitchToIndex(char *inreg, char *Namekey, DBILockType eLock=dbiNOLOCK);
 // End by Miha

 DBIResult Lockrec(DBILockType eLock);
 DBIResult Unlockrec();
 DBIResult Islock(BOOL &rlock);
 UINT16 getBlobNr(char *NameBlob);
 DBIResult OpenBlob(char *NameBlob,
						  UINT16 &iField,
						  DBIOpenMode eOpenMode=dbiREADWRITE);
 DBIResult WrBlob(UINT16 iField, UINT32 iLen, char *src);
 DBIResult RdBlob(UINT16 iField, UINT32 iOffset, UINT32 iLen,
						char *dest, UINT32 *iRead);
 DBIResult SizeBlob(UINT16 iField, UINT32 *iSize);
 DBIResult CloseBlob(UINT16 iField);
 DBIResult DelBlob(UINT16 iField);
 DBIResult EmptyFile();
// int Createdb();
// int Savedb();
// int Restdb();
 Px_File(hDBIDb *hdb ,char *filename);
 ~Px_File();
};


#endif
//-------------------------------------------------------------------------
// End of File : PXFILE.H
//-------------------------------------------------------------------------
