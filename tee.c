/*
Zadanie 7
Polecenie tee czyta ze standardowego wejścia do napotkania końca pliku, zapisuje kopię wejścia na
standardowe wyjecie i do pliku podanego w wierszu wywołania. Domyślnie polecenie tee nadpisuje ten plik,
jeśli istnieje. Napisz program, który
a) działa zgodnie z domyślnym zachowaniem polecenia tee
b) obsługuje opcję –a plik , która powoduje dopisanie wczytywanych danych do końca pliku, jeśli ten istnieje.
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#define MAXBUF 4096


int main(int argc, char *argv[])
{
 FILE *plik;
 char buf[MAXBUF];

 //bez drugiego arg (pliku) tylko wypisuje
 if (argc==1) {while (gets(buf)) puts(buf);}
 
 //plik bez opcji
 if (argc==2)
 {
if ( (plik = fopen(argv[1], "w"))==NULL) {perror("Open: ");}

 //wczytuje po linii do znaku konca pliku
 //zapisuje do pliku i wypisuje na stdout
 
 while (gets(buf) ) {
   
   puts(buf);
     if(plik !=  NULL)
     {
       fputs(buf, plik);
       fputc('\n', plik);
     }
					}
    if(plik != NULL){ fclose(plik);}
 }
 
 //opcja a - dopisuje do istniejacego pliku lub tworzy nowy
 if (argc==3)
 {
	char opcje[]="a";
    int opcja;	 
    
    while ( (opcja = getopt(argc,argv,opcje)) != -1 )

	switch (opcja)
	 {
		case 'a': 
		 {
		  if ( (plik = fopen(argv[2], "a"))==NULL) {perror("Open: ");}
		  while (gets(buf) )
			{
   
		puts(buf);
		if(plik !=  NULL)
    			 { fputs(buf, plik);
     			  fputc('\n', plik); }
			}
		 break;
		}
		default: 
		printf("Nieznana opcja\n");  exit(1);
	 }
 }
 
 if (argc>3) {printf("Za duzo parametrow\n"); exit(1);}	//wersja uproszczona - tylko jeden plik
 
 return 0;
}

