/*
Napisz program, który sprawdza, czy proces może czytać, zapisywać lub uruchamiać plik w zależności od
podanego w wywołaniu parametru. Uwaga: uwzględnić fakt, że prawa dostępu są definiowane dla trzech
kategorii: user, group, other.
*/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])

{
int opcja;
char optstring[]="rwx";

struct stat info;
if ( stat(argv[1], &info) == -1 ){perror("Blad stat: "); return 1;}

printf("Plik: %s\n", argv[1]);

while ((opcja=getopt(argc,argv,optstring)) !=-1)

switch (opcja)

{
case 'r':
if (info.st_mode & S_IRUSR) printf("Wlasciciel ma prawo czytania\n");
if (info.st_mode & S_IRGRP) printf("Grupa ma prawo czytania\n");
if (info.st_mode & S_IROTH) printf("Pozostali maja prawo czytania\n");
break;

case 'w':
if (info.st_mode & S_IWUSR) printf("Wlasciciel ma prawo pisania\n");
if (info.st_mode & S_IWGRP) printf("Grupa ma prawo pisania\n");
if (info.st_mode & S_IWOTH) printf("Pozostali maja prawo pisania\n");
break;

case 'x':
if (info.st_mode & S_IXUSR) printf("Wlasciciel ma prawo wykonywania\n");
if (info.st_mode & S_IXGRP) printf("Grupa ma prawo wykonywania\n");
if (info.st_mode & S_IXOTH) printf("Pozostali maja prawo wykonywania\n");
break;

case'?':
fprintf(stderr, "Nieznana opcja -%c\n", optopt);
break;
}

return 0;

}
