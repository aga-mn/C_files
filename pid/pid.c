//Agata Molda-Niewęgłowska gr IZ05IO1
//lab 6 - zad 12 (domowe) funkcja main

#include "func.h"
   
  
     int main (int argc, char *argv[])
     {
		 if (argc<2) search_usr_in_proc("root");	//wywolanie np. ./zad12 agata bez parametru wypisuje procesy roota
		 else search_usr_in_proc(argv[1]);

		return 0;
	 }  
     
  
