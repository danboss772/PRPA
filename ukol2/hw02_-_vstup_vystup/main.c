#include <stdio.h>
#include <stdlib.h>

int f_count(int number){
	int multiplier = 16;
	for (int i = 1; i < 8;i++){
		if (number < multiplier){
		//printf("Icko %d", i);
			return i;
		}
		multiplier *= 16;
	}
	return -1;
}
int to_letters_and_numbers(int number){
	int result;
	if (number < 10){
		result = number + 48;
	}
	else{
		result = number + 87;
	}
	return result;
}

int to_hexadecimal(int number){
	int x;
	if (number > -1){
	while (number>16){
		x = number / 16;
		//printf("%c", (char)to_letters_and_numbers(x));
		printf("%d", x);
		number = number - x*16;
	}
	printf("%c", (char)to_letters_and_numbers(number));
	}
	else{
		number = (number * -1)-1;
		for (int i = 0; i < 8-f_count(number); i++){
			printf("f");
		}
		while (number>16){
		x = number / 16;
		printf("%c", (char)to_letters_and_numbers(16-x-1));
		number = number - x*16;
		}
	printf("%c", (char)to_letters_and_numbers(16-number-1));
	
	}
	return 0;
}

/* The main program */
int main(int argc, char *argv[])
{
  int first, second;
  if (scanf("%d %d", &first, &second)){
  	if (first > 10000 || first < -10000 ||second > 10000 ||second<-10000){
  		printf("Vstup je mimo interval!\n");
  		return 0;
  	}
  	else {
  		printf("Desitkova soustava: %d %d\n", first, second);
  		printf("Sestnactkova soustava: %x %x\n", first, second); 
  		//to_hexadecimal(first);
  		//printf(" ");
  		//to_hexadecimal(second);
  		//printf("\n");
  		printf("Soucet: %d + %d = %d\n", first, second, first+second);
  		printf("Rozdil: %d - %d = %d\n", first, second, first-second);
  		printf("Soucin: %d * %d = %d\n", first, second, first*second);
  		if (second != 0){
  			printf("Podil: %d / %d = %d\n", first, second, first/second);
  		}
  		else{
  			printf("Nedefinovany vysledek!\n");
  		}
  		float x = ((float)first+(float)second)/2;
  		printf("Prumer: %.1f\n", x);
  	}
  }
  else {
  	printf("Vstup je mimo interval!\n");
  return 0;
  }
  
  return 0;
}

