#include "getint.h"
#include <stdlib.h>
#include <stdbool.h>

_Bool negative;

int printer(int number){
	negative = false;
	int spaces = 0;
	if (number < 0){
		spaces -= 1;
		number = -number;
		negative = true;
		
	}
	if (number < 10){
		spaces += 3;
	}
	else if (number < 100){
		spaces += 2;
	}
	else if (number < 1000){
		spaces += 1;
	}
	else if (number < 10000){
		spaces += 0;
	}
		
	for (int i = 0; i < spaces;i++){
		printf(" ");
	}
	if (negative){
		number = -number;
	}
	printf("%d", number);
	printf(" ");
	return 0;
}
/* The main program */
int main()
{
  int first, second, third;
  
  if (scanf("%d %d %d", &first, &second, &third)){
  	int diskriminant;
  	diskriminant = second*second-4*third*first;
  	if (diskriminant > 999 || diskriminant < -999){
  		printf("Diskriminant mimo povoleny interval!\n");
  		return 0;
  	}
  	printf("+-----+-----+-----+-----+\n");
  		printf("|");	
  		printer(first);
  		printf("|");
  		printer(second);
  		printf("|");
  		printer(third);
  		printf("|");
  		printer(diskriminant);
  		printf("|\n");
  	printf("+-----+-----+-----+-----+\n");
  	if (diskriminant > 0){
  	 	printf("|     Dva realne koreny |\n");
  	}
  	else if (diskriminant == 0){
  		printf("|           Jeden koren |\n");
  	}
  	else if (diskriminant < 0){
  		printf("| Dva imaginarni koreny |\n");
  	}
  	printf("+-----------------------+\n");
  }
  else{
  printf("Diskriminant mimo povoleny interval!\n");
  }
  
  return 0;
}

