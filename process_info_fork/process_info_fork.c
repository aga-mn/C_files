/*Napisz program, który pokazuje, które atrybuty procesu macierzystego są dziedziczone przez proces potomny
uruchomiony za pomocą funkcji fork(), które zaś otrzymują nową wartość.*/

#include "func.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
pid_t pid;
pid=fork();

if (pid==0){

printf("\nInfo potomka");	
get_process_info();

}

if (pid>0){
wait(0);
printf("\nInfo rodzica");	
get_process_info();

}


return 0;
}                

