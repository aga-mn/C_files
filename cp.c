/*Zadanie 5. Kopiowanie plików
a) Sprawdź jak działa polecenie cp.
b) Zapoznaj się ze uproszczoną wersją polecenia (plik cp1.c).
c) Jak sprawdzić czy utworzony plik jest kopią pliku źródłowego? Jakie prawa dostępu otrzymał utworzony
plik? Czy program dobrze obsługuje błędy? Spróbuj na przykład skopiować nieistniejący plik lub
skopiować plik do katalogu. Jakie inne błędy mogłyby wystąpić? Zapoznaj się z opisem użytych w
programie funkcji systemowych i spróbuj wygenerować inne błędy
d) Program w obecnej postaci nadpisuje istniejący plik. Uzupełnij program o obsługę opcji –i pozwalającej
użytkownikowi podjąć decyzję, czy chce napisać istniejący plik.*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE  4096
#define COPYMODE  0644

void err(char *, char *);

int main(int ac, char *av[])
{

if (ac!=3 && ac !=4)
{
    fprintf( stderr, "usage: %s source destination\n", *av);
    exit(1);
}

if (ac==3)  //bez opcji
{
    kopiuj(av[1],av[2]);
    return 0;
}

int opcja;
char opcje[] ="i";
int czy_jest;
char tak[]="t";
char TAK[]="T";
char odp[]=" ";

 while ( (opcja = getopt(ac,av,opcje)) != -1 ){
 switch(opcja)
 {
 case 'i':

  if ( (czy_jest = access(av[3], F_OK)) == 0){
			printf ("Plik %s istnieje. Czy chcesz go nadpisac t/n?\n", av[3]);
			scanf("%s",odp);
if ((strcmp(odp,tak)!=0) && strcmp(odp,TAK)!=0)
{
    err("Plik %s istnieje\n", av[3]);

}
else
kopiuj(av[2],av[3]);


   break;}

   default:
    {fprintf(stderr,"podano nieznany parametr: %c\n",(char)opcja);
    exit(1);}
   //else kopiuj(av[2],av[3]);
   }

 }

}

//funkcja kopiuj
int kopiuj(char*src, char*dst)
{
    int in_fd, out_fd, n_chars;
  char buf[BUFFERSIZE];

    if ( (in_fd=open(src, O_RDONLY)) == -1 )
    err("Cannot open ", src);

  if ( (out_fd=creat( dst, COPYMODE)) == -1 )
    err( "Cannot create", dst);

  while ( (n_chars = read(in_fd , buf, BUFFERSIZE)) > 0 )
    if ( write( out_fd, buf, n_chars ) != n_chars )
       err("Write error to ", dst);
	if ( n_chars == -1 )
          err("Read error from ", src);

  if ( close(in_fd) == -1 || close(out_fd) == -1 )
    err("Error closing files","");
  exit(0);

    }



void err(char *s1, char *s2)
{
  fprintf(stderr,"Error: %s ", s1);
  perror(s2);
  exit(1);
}

