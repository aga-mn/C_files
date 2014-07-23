/*
Napisz funkcję, która oblicza czas wykonywania pewnej funkcji obliczeniowej. Funkcja obliczeniowa może być
na przykład reprezentowana za pomocą funkcji sleep(n), gdzie n jest liczbą sekund generowaną losowo.
*/

#include<time.h>
#include <stdio.h>
#include <stdlib.h>

void mysleep();

int main()
{
int i;

for (i=0;i<10;i++)
{
time_t czas_0, czas_1;
time(&czas_0);                        //czas biezacy

mysleep();

time(&czas_1);                        //czas biezacy po wykonaniu funkcji

int roznica=difftime(czas_1, czas_0);        //roznica czasow

printf ("%d czas wykonywania: %d sekund\n", i+1, roznica);
}
return 0;
}

//funkcja sleep(n) - n losowe z przedzialu 1-20

void mysleep()
{
int n, seed;
seed=time(NULL);
srand(seed);

n=(int)(rand() / (RAND_MAX + 1.0) * 20);

sleep(n);

}
