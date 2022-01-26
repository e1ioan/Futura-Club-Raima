#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <io.h>
#include <iostream.h>
#include <alloc.h>
#include <fcntl.h>
#include <process.h>
#include <sys\stat.h>

int main()
{
  int handle1;
  char buf1[11] = "0123456789";
  _fmode = O_BINARY;
  handle1 = creat("MAMARUTA.TMP", S_IREAD |S_IWRITE);
  write(handle1, buf1, strlen(buf1));
  close(handle1);

  char *buf[]=
	{
	 "//--------------------------------------------------------------------------\n",
	 "//  Project      : w11clubm.ide\n",
	 "//  File Name    : w11about.cpp\n",
	 "//  Written by   : Ioan Ghip\n",
	 "//  Created      : 25.10.1994\n",
	 "//  Updated      : !!!!!!!!!!\n\0"
	};
  int handle;
  clrscr();

  struct date d;
  char dat[20];
  getdate(&d);
  sprintf(dat,"%02d.%02d.%d", d.da_day, d.da_mon, d.da_year);

  struct find_t ffblk,ffblk1;
  int done,inc=0,inc1=0;
  done = _dos_findfirst("*.cpp",_A_NORMAL,&ffblk);
  _dos_findfirst("*.tmp",_A_NORMAL,&ffblk1);
  while (!done)
  {
		if(ffblk.wr_date==ffblk1.wr_date)
		{
			inc++;
			if ((handle =                             
				  open(ffblk.name, O_RDWR | O_TEXT, S_IWRITE | S_IREAD)) == -1)
			{
				printf("Error Opening File\n");
				exit(1);
			}
			cout<<ffblk.name<<"\n";   
			write(handle,buf[0],strlen(buf[0]));
			write(handle,buf[1],strlen(buf[1]));
			sprintf(buf[2],"//  File Name    : %s\n",ffblk.name);
			write(handle,buf[2],strlen(buf[2]));
			write(handle,buf[3],strlen(buf[3]));
			write(handle,buf[4],strlen(buf[4]));
			sprintf(buf[5],"//  Updated      : %s\n",dat);
			write(handle,buf[5],strlen(buf[5]));
			close(handle);
		}
		done = _dos_findnext(&ffblk);
  }
  done = _dos_findfirst("*.h",_A_NORMAL,&ffblk);
  while (!done)
  {
		if(ffblk.wr_date==ffblk1.wr_date)
		{
			inc1++;
			if ((handle =
				  open(ffblk.name, O_RDWR | O_TEXT, S_IWRITE | S_IREAD)) == -1)
			{
				printf("Error Opening File\n");
				exit(1);
			}
			cout<<ffblk.name<<"\n";
			write(handle,buf[0],strlen(buf[0]));
			write(handle,buf[1],strlen(buf[1]));
			sprintf(buf[2],"//  File Name    : %s\n",ffblk.name);
			write(handle,buf[2],strlen(buf[2]));
			write(handle,buf[3],strlen(buf[3]));
			write(handle,buf[4],strlen(buf[4]));
			sprintf(buf[5],"//  Updated      : %s\n",dat);
			write(handle,buf[5],strlen(buf[5]));
			close(handle);
		}
		done = _dos_findnext(&ffblk);
  }
	cout<<"CPP = "<<inc<<"\n H = "<<inc1;
	system("del MAMARUTA.TMP");
   delay(2000);
	return 0;
}




