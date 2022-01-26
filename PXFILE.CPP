//--------------------------------------------------------------------------
//  Project      : ALL PROJECTS
//  File Name    : PXFILE.CPP
//  Written by   : SORIN IONITA
//  Created      : 29.06.1995
//  Updated      : 19.09.1995  by Mihaela Popescu
//--------------------------------------------------------------------------
//  Dest. System : WINDOWS
//--------------------------------------------------------------------------
//  Libraries    : BDE
//--------------------------------------------------------------------------
//  Data Files   : NONE
//--------------------------------------------------------------------------
//  Remarks      : DEFINES THE FUNTIONS FOR HANDLING PARADOX DATABASES
//--------------------------------------------------------------------------
//  
//--------------------------------------------------------------------------

#include <dir.h>
#include "pxfile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#pragma hdrstop

DBIResult OpenBase
	(hDBIDb *hdb, char *dirwork,
	 DBIOpenMode eOpenMode, DBIShareMode eShareMode)
{
	DBIResult rslt;
	rslt = DbiOpenDatabase(NULL, NULL, eOpenMode, eShareMode,
								  NULL, 0, NULL, NULL, hdb);
	rslt = DbiSetDirectory(*hdb, dirwork);
//	if(rslt) return rslt;
//	return rslt;
//	rslt = DbiSetPrivateDir(dirwork);
	return rslt;
}
Px_File::Px_File(hDBIDb *hdb ,char *filename)
{
 phdb=hdb;
 FileName = NULL;
 FileName = new char[strlen(filename)+1];
 strcpy(FileName, filename);
}

Px_File::~Px_File() { delete[] FileName; }

DBIResult Px_File::Open(DBIOpenMode eOpenMode, DBIShareMode eShareMode)
{
	 DBIResult rslt;
	 rslt = DbiOpenTable(*phdb, (pCHAR) FileName, (pCHAR) szPARADOX,
								NULL, NULL, NULL, eOpenMode, eShareMode,
								xltFIELD, FALSE, NULL, &hCur);
	 if (rslt) return rslt;
	 rslt = DbiGetCursorProps(hCur, &curProps);
	 if (rslt) return rslt;
	 pRecBuf = (pBYTE) malloc(curProps.iRecBufSize);
	 descfield =(char *) malloc(sizeof(FLDDesc)*(curProps.iFields));
	 rslt=DbiGetFieldDescs(hCur, (pFLDDesc) descfield);
	 return rslt;
}

DBIResult Px_File::getrec(char *inreg)
{
		DBIResult rslt;
		BOOL fblank;
		UINT16 fdtype;
		int i;
		for(i=1;i<curProps.iFields+1;i++)
		{
		 fdtype=((pFLDDesc) (descfield+(i-1)*sizeof(FLDDesc)))->iFldType;
		 if((fdtype!=fldBLOB))
		 {
		 int idepl=((pFLDDesc) (descfield+(i-1)*sizeof(FLDDesc)))->iOffset;
		 rslt=DbiGetField
		  (hCur, i, pRecBuf, (pBYTE) inreg+idepl, &fblank);
		 }
		}
		return rslt;
}

DBIResult Px_File::putrec(char *inreg)
{
	DBIResult rslt;
	UINT16 fdtype;
	int i;
	for(i=1;i<curProps.iFields+1;i++)
	{
	 fdtype=((pFLDDesc) (descfield+(i-1)*sizeof(FLDDesc)))->iFldType;
	 if((fdtype!=fldBLOB))
	 {
		 int idepl=((pFLDDesc) (descfield+(i-1)*sizeof(FLDDesc)))->iOffset;
		 rslt=DbiPutField
		  (hCur, i, pRecBuf, inreg+idepl); // inreg+idepl
	 }
	}
	return rslt;
}

DBIResult Px_File::Close()
 {
	 delete descfield;
	 delete pRecBuf;
	 rslt = DbiCloseCursor(&hCur);
	 return(rslt);
 }

DBIResult Px_File::Geteq(char *inreg, char *Namekey, DBILockType eLock)
{
 DBIResult rslt;
 rslt = DbiInitRecord(hCur, pRecBuf);
 rslt=putrec(inreg);
 if(rslt) return rslt;
 rslt = DbiSwitchToIndex(&hCur, Namekey, NULL, NULL, FALSE);
 if(rslt) return rslt;
 rslt=DbiSetToKey(hCur, keySEARCHEQ, FALSE, 0, 0, pRecBuf);
 if(rslt) return rslt;
 rslt = DbiGetNextRecord(hCur, eLock, pRecBuf, NULL);
 if(rslt) return rslt;
 rslt=getrec(inreg);
 return rslt;
}
DBIResult Px_File::Getge(char *inreg, char *Namekey, DBILockType eLock)
{
 DBIResult rslt;
 rslt = DbiInitRecord(hCur, pRecBuf);
 rslt=putrec(inreg);
 if(rslt) return rslt;
 rslt = DbiSwitchToIndex(&hCur, Namekey, NULL, NULL, FALSE);
 if(rslt) return rslt;
 rslt=DbiSetToKey(hCur, keySEARCHGEQ, FALSE, 0, 0, pRecBuf);
 if(rslt) return rslt;
 rslt = DbiGetNextRecord(hCur, eLock, pRecBuf, NULL);
 if(rslt) return rslt;
 rslt=getrec(inreg);
 return rslt;
}

DBIResult Px_File::Getgt(char *inreg, char *Namekey, DBILockType eLock)
{
 DBIResult rslt;
 rslt = DbiInitRecord(hCur, pRecBuf);
 rslt=putrec(inreg);
 if(rslt) return rslt;
 rslt = DbiSwitchToIndex(&hCur, Namekey, NULL, NULL, FALSE);
 if(rslt) return rslt;
 rslt=DbiSetToKey(hCur, keySEARCHGT, FALSE, 0, 0, pRecBuf);
 if(rslt) return rslt;
 rslt = DbiGetNextRecord(hCur, eLock, pRecBuf, NULL);
 if(rslt) return rslt;
 rslt=getrec(inreg);
 return rslt;
}

DBIResult Px_File::Getle(char *inreg, char *Namekey, DBILockType eLock)
{
 DBIResult rslt;
 rslt = DbiInitRecord(hCur, pRecBuf);
 rslt=putrec(inreg);
 if(rslt) return rslt;
 rslt = DbiSwitchToIndex(&hCur, Namekey, NULL, NULL, FALSE);
 if(rslt) return rslt;
 rslt=DbiSetToKey(hCur, keySEARCHEQ, FALSE, 0, 0, pRecBuf);
 if (rslt == DBIERR_RECNOTFOUND)  // by Miha
 {
	DbiSetToKey(hCur, keySEARCHGT, FALSE, 0, 0, pRecBuf);
	rslt = DbiGetPriorRecord(hCur, eLock, pRecBuf, NULL);
 } else
	if(rslt) return rslt;
	else
	  rslt = DbiGetRecord(hCur, eLock, pRecBuf, NULL);
 if(rslt) return rslt;
 rslt=getrec(inreg);
 return rslt;
}

DBIResult Px_File::Getlt(char *inreg, char *Namekey, DBILockType eLock)
{
 DBIResult rslt;
 rslt = DbiInitRecord(hCur, pRecBuf);
 rslt=putrec(inreg);
 if(rslt) return rslt;
 rslt = DbiSwitchToIndex(&hCur, Namekey, NULL, NULL, FALSE);
 if(rslt) return rslt;
 rslt=DbiSetToKey(hCur, keySEARCHGEQ, FALSE, 0, 0, pRecBuf);
 if(rslt) return rslt;
 rslt = DbiGetPriorRecord(hCur, eLock, pRecBuf, NULL);
 if(rslt) return rslt;
 rslt=getrec(inreg);
 return rslt;
}

DBIResult Px_File::Getnx(char *inreg, DBILockType eLock)
{
 DBIResult rslt;
 rslt = DbiGetNextRecord(hCur, eLock, pRecBuf, NULL);
 if(rslt) return rslt;
 rslt=getrec(inreg);
 return rslt;
}

DBIResult Px_File::Getlw(char *inreg, char *Namekey, DBILockType eLock)
{
 DBIResult rslt;
 rslt = DbiInitRecord(hCur, pRecBuf);
 rslt=putrec(inreg);
 if(rslt) return rslt;
 rslt = DbiSwitchToIndex(&hCur, Namekey, NULL, NULL, FALSE);
 if(rslt) return rslt;
 rslt=DbiSetToBegin(hCur);
 if(rslt) return rslt;
 rslt = DbiGetNextRecord(hCur, eLock, pRecBuf, NULL);
 if(rslt) return rslt;
 rslt=getrec(inreg);
 return rslt;
}

DBIResult Px_File::Gethi(char *inreg, char *Namekey, DBILockType eLock)
{
 DBIResult rslt;
 rslt = DbiInitRecord(hCur, pRecBuf);
 rslt=putrec(inreg);
 if(rslt) return rslt;
 rslt = DbiSwitchToIndex(&hCur, Namekey, NULL, NULL, FALSE);
 if(rslt) return rslt;
 rslt=DbiSetToEnd(hCur);
 if(rslt) return rslt;
 rslt = DbiGetPriorRecord(hCur, eLock, pRecBuf, NULL);
 if(rslt) return rslt;
 rslt=getrec(inreg);
 return rslt;
}

DBIResult Px_File::Getpr(char *inreg, DBILockType eLock)
{
 DBIResult rslt;
 rslt = DbiGetPriorRecord(hCur, eLock, pRecBuf, NULL);
 if(rslt) return rslt;
 rslt=getrec(inreg);
 return rslt;
}

DBIResult Px_File::InitRecord(char *inreg)
{
	DBIResult rslt;
	rslt = DbiInitRecord(hCur, pRecBuf);
	if(rslt) return rslt;
	rslt=getrec(inreg);
	return rslt;
}

DBIResult Px_File::Insrec(char *inreg)
 {
	DBIResult rslt;
	rslt = DbiInitRecord(hCur, pRecBuf);
	if(rslt) return rslt;
	rslt=putrec(inreg);
	if(rslt) return rslt;
	rslt=DbiAppendRecord(hCur, pRecBuf);
	if(rslt) return rslt;
	rslt=DbiSaveChanges(hCur);
	return rslt;
 }

DBIResult Px_File::Updrec(char *inreg)
{
 DBIResult rslt;
 rslt = DbiInitRecord(hCur, pRecBuf);
 if(rslt) return rslt;
 rslt=putrec(inreg);
 if(rslt) return rslt;
 rslt=DbiModifyRecord(hCur, pRecBuf, TRUE);
 if(rslt) return rslt;
 rslt=DbiSaveChanges(hCur);
 return rslt;
}

DBIResult Px_File::Delrec()
{
 DBIResult rslt;
 rslt=DbiDeleteRecord(hCur, NULL);
 return rslt;
}

DBIResult Px_File::Lockrec(DBILockType eLock)
{
 DBIResult rslt;
 rslt=DbiGetRecord(hCur, eLock, NULL, NULL);
 return rslt;
}

DBIResult Px_File::Unlockrec()
{
 DBIResult rslt;
 rslt=DbiRelRecordLock(hCur, FALSE);
 return rslt;
}

DBIResult Px_File::Islock(BOOL &rlock)
{
 DBIResult rslt;
 rslt=DbiIsRecordLocked(hCur, &rlock);
 return rslt;
}

UINT16 Px_File::getBlobNr(char *NameBlob)
{
 UINT16 fdtype, ifield=0;
 char *nmblob;
 int i;
 for(i=1;i<curProps.iFields+1;i++)
 {
  fdtype=((pFLDDesc) (descfield+(i-1)*sizeof(FLDDesc)))->iFldType;
  if((fdtype==fldBLOB))
  {
	nmblob=((pFLDDesc) (descfield+(i-1)*sizeof(FLDDesc)))->szName;
	if(!strcmp(NameBlob, nmblob))
	{
	 ifield=i;
	 break;
	}
  }
 }
 return ifield;
}

DBIResult Px_File::OpenBlob(char *NameBlob,
						 UINT16 &iField,
						 DBIOpenMode eOpenMode)
{
 DBIResult rslt;
 iField = getBlobNr(NameBlob);
 rslt = DbiOpenBlob(hCur, pRecBuf, iField, eOpenMode);
 return rslt;
}

DBIResult Px_File::WrBlob(UINT16 iField, UINT32 iLen, char *src)
{
 UINT32 blobsz;
 DBIResult rslt = DbiGetBlobSize(hCur, pRecBuf, iField, &blobsz);
 if(rslt) return rslt;
 rslt = DbiPutBlob(hCur, pRecBuf, iField, blobsz, iLen, src);
 if(rslt) return rslt;
 rslt=DbiModifyRecord(hCur, pRecBuf, TRUE);
 return rslt;
}

DBIResult Px_File::RdBlob(UINT16 iField, UINT32 iOffset, UINT32 iLen,
					  char *dest, UINT32 *iRead)
{
 DBIResult rslt = DbiGetBlob(hCur, pRecBuf, iField, iOffset,
									  iLen, dest, iRead);
 return rslt;
}

DBIResult Px_File::SizeBlob(UINT16 iField, UINT32 *iSize)
{
 DBIResult rslt = DbiGetBlobSize(hCur, pRecBuf, iField, iSize);
 return rslt;
}

DBIResult Px_File::CloseBlob(UINT16 iField)
{
 DBIResult rslt = DbiFreeBlob(hCur, pRecBuf, iField);
 return rslt;
}

DBIResult Px_File::DelBlob(UINT16 iField)
{
 DBIResult rslt = DbiTruncateBlob(hCur, pRecBuf, iField, 0);
 if(rslt) return rslt;
 rslt=DbiModifyRecord(hCur, pRecBuf, TRUE);
 return rslt;
}

DBIResult Px_File::EmptyFile()
{
 DBIResult rslt = DbiEmptyTable(*phdb, hCur, FileName, (pCHAR) szPARADOX);
 return rslt;
}

// Added by Miha
DBIResult Px_File::
GetRelativeRec(char *inreg, char *Namekey, long iPos, DBILockType eLock)
{
  DBIResult rslt;
  rslt = DbiInitRecord (hCur, pRecBuf);
  if(rslt) return rslt;
  rslt = putrec (inreg);
  if(rslt) return rslt;
  // Set the cursor on the record corr. to the primary key
  rslt = DbiSwitchToIndex (&hCur, NULL, NULL, NULL, FALSE);
  if(rslt) return rslt;
  rslt=DbiSetToKey (hCur, keySEARCHGEQ, FALSE, 0, 0, pRecBuf);
  if(rslt) return rslt;
  rslt = DbiGetNextRecord (hCur, eLock, pRecBuf, NULL);
  if(rslt) return rslt;
  // Switch on reqested key & position cursor on record corr.
  // with the primary key
  rslt = DbiSwitchToIndex(&hCur, Namekey, NULL, NULL, TRUE);
  if(rslt) return rslt;
  rslt = DbiGetRelativeRecord (hCur, iPos, eLock, pRecBuf, NULL);
  switch (rslt)
  { case DBIERR_BOF  : // position on the begining of the file
		DbiSetToBegin (hCur);
		DbiGetNextRecord (hCur, eLock, pRecBuf, NULL);
	 break;
	 case DBIERR_EOF  : // position on the end of the file
		DbiSetToEnd (hCur);
		DbiGetPriorRecord (hCur, eLock, pRecBuf, NULL);
	 break;
	 case DBIERR_NONE : break;
	 default : return rslt;
  }
  // Is NOT recommended to decoment  next line - the author
  // if(rslt) return rslt;
  getrec(inreg);
  return rslt;
}
// Count the records
long Px_File::
GetRecordCount()
{
  UINT32 recCount = 0;
  DbiGetRecordCount (hCur, &recCount);
  return recCount;
}

DBIResult Px_File::
SwitchToIndex(char *inreg, char *Namekey, DBILockType eLock)
{
  DBIResult rslt;
  rslt = DbiInitRecord(hCur, pRecBuf);
  if(rslt) return rslt;
  rslt=putrec(inreg);
  if(rslt) return rslt;
  // Set the cursor on the record corr. to the primary key
  rslt = DbiSwitchToIndex(&hCur, NULL, NULL, NULL, FALSE);
  if(rslt) return rslt;
  rslt=DbiSetToKey(hCur, keySEARCHGEQ, FALSE, 0, 0, pRecBuf);
  if(rslt) return rslt;
  rslt = DbiGetNextRecord(hCur, eLock, pRecBuf, NULL);
  // Switch on reqested key & position cursor on record corr.
  // with the primary key
  if(rslt) return rslt;
  rslt = DbiSwitchToIndex(&hCur, Namekey, NULL, NULL, TRUE);
  if(rslt) return rslt;
  getrec(inreg);
  if(rslt) return rslt;
  return rslt;
}

// End of part introduced by Miha
//------------------------------------------------------------------------
// End File : PXFILE.CPP
//------------------------------------------------------------------------

