#include <stdio.h>
#include <stdlib.h>

/* The main program */
int main(int argc, char *argv[])
{
  int number, even = 0, odd = 0, positive = 0, negative = 0, max = -1000000, min = 1000000, sum = 0;
  int cnt = 0;
  while (scanf("%d", &number) == 1){
  if (number > 10000 || number < -10000){
  	printf("\nError: Vstup je mimo interval!\n");
  	return 100;
  }
  if (cnt != 0){
  	printf(", ");
  }
  printf("%d", number);
  if (number > max){
  	max = number;
  }
  if (number < min){
  	min = number;
  }
  if ((number % 2) == 0){
  	even += 1;
  }
  else {
  	odd += 1;
  }
  if (number > 0){
  	positive += 1;
  }
  if (number < 0){
  	negative += 1;
  }
  sum += number;
  cnt += 1;
  }
  printf("\n");
  
  printf("Pocet cisel: %d\n", cnt);
  printf("Pocet kladnych: %d\n", positive);
  printf("Pocet zapornych: %d\n", negative);
  printf("Procento kladnych: %.2f\n", (float)positive*100/cnt);
  printf("Procento zapornych: %.2f\n", (float)negative*100/cnt);
  printf("Pocet sudych: %d\n", even);
  printf("Pocet lichych: %d\n", odd);
  printf("Procento sudych: %.2f\n", (float)even*100/cnt);
  printf("Procento lichych: %.2f\n", (float)odd*100/cnt);
  printf("Prumer: %.2f\n", (float)sum/(float)cnt);
  printf("Maximum: %d\n", max);
  printf("Minimum: %d\n", min);
  
  return 0;
}

