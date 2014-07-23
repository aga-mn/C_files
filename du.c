/*
Zadanie 8
Napisz program, który jest uproszczoną wersją polecenia du:
a) działa tylko we wskazanym katalogu,
b) wyświetla albo wielkości poszczególnych plików albo ich sumę
c) wielkości mogą być wyświetlane w różnych jednostkach (patrz polecenie du) w zależności od podanej
opcji
*/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

long int du(char [],int, char );

int main(int argc, char *argv[])
{
    char opcje[]="sbkm";
    int opcja;
    long int sum;

    if (argc==1) printf("%ld\n", du(".",2,'k'));

    if (argc==2) //drugi argument to albo opcja albo katalog
    {
    //najpierw opcje - jesli opcja to biezacy katalog z opcjami
     while ( (opcja = getopt(argc,argv,opcje)) != -1 )

	switch (opcja)

    {
	case 's':

    sum=du(".",2, 'b');
    printf("Suma rozmiarow %ld\n", sum);
    break;

    case 'k':
    du(".",1,'k');
    break;

    case 'm':
    du (".",1,'m');
    break;

    case 'b':
    du (".",1,'b');
    break;

    //nie opcja - 2 arg to katalog
    default:
    if (chdir(argv[1])==0)   //chdir zwraca 0 jak sukces
    du (".",2,'k');

    else
    printf("Nieznany katalog\n");
	}
    }

if (argc==3)    //opcja i sciezka katalogu

{
    while ( (opcja = getopt(argc,argv,opcje)) != -1 )
    switch (opcja)
    {
    case 's':
     if (chdir(argv[2])==0) {sum=du(".",2,'b');
      printf("Suma rozmiarow %ld\n", sum);}
      else  printf("Nieznany katalog\n");
    break;

    case 'b':
    if (chdir(argv[2])==0) sum=du(".",1,'b');
    else  printf("Nieznany katalog\n");
    break;

    case 'k':
    if (chdir(argv[2])==0) sum=du(".",1,'k');
    else  printf("Nieznany katalog\n");
    break;

    case 'm':
    if (chdir(argv[2])==0) sum=du(".",1,'m');
    else  printf("Nieznany katalog\n");
    break;

    default:
    printf("Nieznany parametr\n");
	}

	}

	return 0;
}


long int du ( char dirname[], int opt, char rozm )    //czy wypisuje pliki i przez ile dzieli w zaleznosci od opcji
{
long int suma=0;
long int jedn;

switch (rozm)
{
    case 'k': jedn=1024; break;
    case 'b': jedn=1; break;
    case 'm': jedn=1024*1024; break;
    default: jedn=1;
}


struct stat info;
  DIR *katalog;
  struct dirent *pozycja;

  if ( ( katalog = opendir( dirname) ) == NULL )
    fprintf(stderr,"cannot open %s\n", dirname);

else
{
    while ((pozycja=readdir(katalog)))
    if( stat(pozycja->d_name, &info) != -1 )
    {
     if (opt==1)

         {   if (strncmp(pozycja->d_name, ".",1)!=0)
             printf("%ld\t%s\n", (info.st_size/jedn),pozycja->d_name);
             suma+=(info.st_size);
                    }


    if (opt==2) { if (strncmp(pozycja->d_name, ".",1)!=0)
             //printf("%ld\t%s\n", (info.st_size/jedn),pozycja->d_name);
             suma+=(info.st_size);}

    }
if (opt==1) printf("%ld\t.\n", suma/jedn); //na koncu drukuje sume

}
 closedir(katalog);
    return suma/jedn;

}
