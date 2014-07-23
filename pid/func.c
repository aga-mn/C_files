//Agata Molda-Niewęgłowska gr IZ05IO1
//lab 6 - zad 12 (domowe) - funkcje i struktury

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <pwd.h>

     struct procstat 	//tu wczytam dane z pliku /proc/PID/stat
     {
		long long int  pid;
		char comm[FILENAME_MAX];
		char state;
		long long int ppid;
		long long int pgrp;
		long long int session;
		long long int tty;
		long long int tpgid;
		unsigned flags;
		unsigned minflt;
		unsigned cminflt;
		unsigned majflt;
		unsigned cmajflt;
		long long int utime;
		long long int stime;
		long long int cutime;
		long long int cstime;
		long long int counter;
		long long int priority;
		unsigned timeout;
		unsigned itrealvalue;
		unsigned long  starttime;
		unsigned vsize;
		unsigned rss;
		unsigned rlim;
		unsigned startcode;
		unsigned endcode;
		unsigned startstack;
		unsigned kstkesp;
		unsigned kstkeip;
		long long int signal;
		long long int blocked;
		long long int sigignore;
		long long int sigcatch;
		unsigned wchan;
};
  
struct procstat  prs;

int print_process(void) {
	
printf("pid %lld \n comm %s \n state %c \n ppid %lld \n  pgrp %lld \n session %lld \n tty %lld \ntpgid %lld \n flags %u \n",
					   prs.pid, 
                       prs.comm,                
                       prs.state, 
                       prs.ppid, 
                       prs.pgrp, 
                       prs.session, 
                       prs.tty, 
                       prs.tpgid,
                       prs.flags );	//kilka atrybutow procesu

return 0;
}
    void get_procstat( char* path)	//czyta plik /proc/pid/stat, wypelnia strukture
{
       FILE* plik;
       char filename[100]; 
       
       snprintf (filename, sizeof (filename), "%s/stat",path);

       if( (plik = fopen( filename, "r" )) == NULL ) {perror (filename); exit(1);}
   
  fscanf(plik,"%lld %s %c %lld %lld %lld %lld %lld %u %u %u %u %u %lld %lld %lld %lld %lld %lld %u %u %lu %u %u %u %u %u %u %u %u %lld %lld %lld %lld %u",
                       &prs.pid, 
                       prs.comm,                
                       &prs.state, 
                       &prs.ppid, 
                       &prs.pgrp, 
                       &prs.session, 
                       &prs.tty, 
                       &prs.tpgid,
                       &prs.flags,
                       &prs.minflt,
                       &prs.cminflt,
                       &prs.majflt, 
                       &prs.cmajflt, 
                       &prs.utime,
                       &prs.stime,
                       &prs.cutime,
                       &prs.cstime,
                       &prs.counter,
                       &prs.priority,
                       &prs.timeout,
                       &prs.itrealvalue,
                       &prs.starttime,
                       &prs.vsize,
                       &prs.rss,
                       &prs.rlim,
                       &prs.startcode,
                       &prs.endcode,
                       &prs.startstack,
                       &prs.kstkesp,
                       &prs.kstkeip,
                       &prs.signal,
                       &prs.blocked,
                       &prs.sigignore,
                       &prs.sigcatch,
                       &prs.wchan);
    fclose(plik);
      
}
       
    void search_usr_in_proc (char *uid)	//w katalogu /proc szuka procesow uzytkownika
     {
       DIR *dp;
       struct passwd *pwdp;
       struct dirent *ep;
       struct stat info;
       
       char filename[100];
       	
       dp = opendir ("/proc");
       if (dp != NULL)
         {
           while ((ep=(readdir(dp))))
           
           {
            	//tylko cyfry - katalogi -PID procesów
				if( strtok(ep->d_name, "0123456789") ==0 )	
				{
				snprintf (filename, sizeof (filename), "/proc/%s", ep->d_name);	
				stat(filename, &info);
				 
				 pwdp = getpwuid(info.st_uid);
							 
				if(strcmp(uid, pwdp->pw_name) == 0)
					{
						   printf("------------>Proces uzytkownika: %d %s \n process info:\n" ,info.st_uid,pwdp->pw_name);
						   get_procstat(filename);
						   print_process();
					}
				
				}
             
            }
           (void) closedir (dp);
         }
       else
         perror ("Couldn't open the directory");
     
 
     }
 
