/*
Zadanie 9
Napisz program, który przegląda wybrany katalog wraz z podkatalogami i wyświetla informację o liczbie i
procentowym udziale plików różnych typów (zwykłe, katalogi, dowiązania symboliczne, itp.). Do przeglądania
katalogu użyj funkcji bibliotecznej nftw().
*/

#define _XOPEN_SOURCE 1
#define _XOPEN_SOURCE_EXTENDED 1 
#define MAXBUF 4096

#include <ftw.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>


static int FTW_F_count=0;
static int FTW_D_count=0;
static int FTW_SL_count=0;

long long FTW_F_sum=0;
long long FTW_D_sum=0;
long long FTW_SL_sum=0;
long long FTW_sum_total=0;



int list(const char *name, const struct stat *info, int type, struct FTW *ftwp);

int main(int argc, char *argv[])
{
	
	char buf[MAXBUF];
	getcwd(buf, sizeof(buf));
	
	 if(argc == 1)
		nftw(".", list, FOPEN_MAX, FTW_PHYS);
		
	 else{
		nftw(argv[1], list, FOPEN_MAX, FTW_PHYS);
		strcpy(buf, argv[1]);}
		
		
	printf("PODSUMOWANIE:\n Zawartosc katalogu %s\nPliki: %d\t  rozmiar: %lld\t Udzial proc. %f\n", buf, FTW_F_count, FTW_F_sum,(float)FTW_F_sum/FTW_sum_total*100);
	printf("Katalogi:  %d\t  rozmiar: %lld\t Udzial proc. %f\n", FTW_D_count, FTW_D_sum, (float)FTW_D_sum/FTW_sum_total*100);
	printf("Linki symb: %d\t rozmiar: %lld\t Udzial proc. %f\n", FTW_SL_count, FTW_SL_sum, (float)FTW_SL_sum/FTW_sum_total*100 );
	
	return 0;
}


int list(const char *name, const struct stat *info, int type, struct FTW *ftwp)
{

//printf("name: %s\n",name);

switch (type)
{
	case FTW_NS:
	printf("Can't stat %s\n", name);
	break;
	
	case FTW_DNR:
	printf("Can't read %s\n", name);
	break;
	
	case FTW_D:
	if(strcmp(".", name) != 0)
	printf("Katalog:\t%s\t rozmiar: %ld\n", name, (long) info->st_size);
	FTW_D_count++;
	FTW_D_sum+=(long)info->st_size;
	FTW_sum_total+=(long)info->st_size;
	break;
	
	case FTW_F:
	printf("Plik:\t %s\t rozmiar: %ld\n", name, (long) info->st_size);
	FTW_F_count++;
	FTW_F_sum+=(long)info->st_size;
	FTW_sum_total+=(long)info->st_size;
	break;
	
	case FTW_SL:
	printf("Link symb.:\t%s\t rozmiar: %ld\n", name, (long) info->st_size);
	FTW_SL_count++;
	FTW_SL_sum+=(long)info->st_size;
	FTW_sum_total+=(long)info->st_size;
	break;

}
return 0;
}
