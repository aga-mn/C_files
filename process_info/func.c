//Agata Molda-Niewęgłowska gr IZ05IO1
//lab 6 - zad 9 (domowe) funkcje

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <wait.h>

void get_open_files(char *pid)	//deskryptory plikow z katalogu /proc/PID/fd
{
	char buf[64];
     struct dirent *dp;

     snprintf(buf, sizeof(buf), "/proc/%s/fd/", pid);	//katalog z deskryptorami plikow

      DIR *dir = opendir(buf);
     printf("Deskryptory: \t");	
     while ((dp = readdir(dir)) != NULL) {
     if( strtok(dp->d_name, "0123456789") ==0 )	
     printf("%s\t",dp->d_name);
       }
       printf("\n\n");
     closedir(dir);
}     

//info o procesie 

void get_process_info()
{
int pid;
char cpid[100];
char cwd[100];
pid = getpid();

printf("Process ID: %d\nParent Process ID: %d\nProcess Group ID: %d\nSession ID: %d\n",pid,getppid(),getpgrp(), getsid(0));
printf("\n\nUser ID: %d\nGroup ID: %d\nEffective User ID: %d\nEffective Group ID:%d\n",getuid(),getgid(),geteuid(), getegid());

getcwd (cwd, 100);
printf("Katalog biezacy: %s\n",cwd);

mode_t maska;
umask(maska=umask(0));
printf("Maska tworzenia pliku: %04o\n",maska);

printf("ENV: %s\n",getenv("PATH"));

snprintf (cpid, sizeof (cpid), "%d", (int) pid);	
get_open_files(cpid);	
	
}	
