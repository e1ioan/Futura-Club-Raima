//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : w11globa.h
//  Written by   : Ioan Ghip
//  Created      : 29.10.1994
//  Finished     : 10.03.1995
//--------------------------------------------------------------------------
//  Dest. System : windows
//--------------------------------------------------------------------------
//  Libraries    : raima
//--------------------------------------------------------------------------
//  Data Files   :
//--------------------------------------------------------------------------
//  Remarks
//--------------------------------------------------------------------------
//  1994 by FUTURA Software s.r.l.
//--------------------------------------------------------------------------

#if !defined(__w11globa_h) // Sentry, use file only if it's not
#define __w11globa_h		   //  already included.

// Cut string ( for write address on label )
void CutString(char *in,char *out1,char *out2);
// Data codifying
unsigned int DataCodifyng(unsigned int iday = 0, unsigned int imon = 0,
								  unsigned int iyear = 0);
// Data decodifying
void DataDeCodifyng(unsigned int dataD,char *dataStr);

#endif
//------------------------------------------------------------------------
// End File : w11globa.h
//------------------------------------------------------------------------
