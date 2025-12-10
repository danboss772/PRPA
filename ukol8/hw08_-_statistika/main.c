#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

void printer_hist(long long int pocet_hist, long long int min, long long int max, long long int pocet){
	printf("Histogram:\n");
	double size = max-min/pocet_hist;
	double curr_x = min;
	while (curr_x != max){
		printf("%5.1lf-%5.1lf ");
		printf("|");
		while (){
			
		}
		curr_x += size;
	}
}

int compare_ints(const void* a, const void* b)
{
    long long int arg1 = *(const long long int*)a;
    long long int arg2 = *(const long long int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

void printer(long long int min, long long int max, double median, long long int pocet){
	printf("Median %.2lf\n", median);
	printf("Pocet cisel: %lld\n", pocet);
	printf("Min. hodnota: %lld\n", min);
	printf("Max. hodnota: %lld\n", max);
}

void zpracuj(long long int *pole, long long int len){
	long long int min = LLONG_MAX, max = LLONG_MIN;
	qsort(pole, len, sizeof(long long int), compare_ints);
	min = pole[0];
	max = pole[len-1];
	double median;
	if (len%2 != 0){
		median = pole[len/2];
	}
	else {
		median = (pole[(len/2)-1]+pole[(len/2)])/2.0;
	}
	printer(min, max, median, len);
}
int main(int argc, char *argv[])
{
  long long int delka_hist;
  long long int cislo, pocet_nact = 0, pocet_alloc = 20;
  long long int *pole = (long long int*)malloc(pocet_alloc*sizeof(long long int));
  if (scanf(" %lld", &delka_hist) != 1){
  	printf("Error: Chyba histogramu!\n");
  	return 100;
  }
  while (scanf(" %lld", &cislo) == 1){
  	pole[pocet_nact] = cislo;
  	pocet_nact += 1;
  	if (pocet_nact+2 >= pocet_alloc){
  		pocet_alloc += 30;
  		pole = (long long int*)realloc(pole, pocet_alloc*sizeof(long long int));
  	}
  }
  pole[pocet_nact] = '\0';
  //printf("Len: %lld\n", pocet_nact);
  zpracuj(pole, pocet_nact);
  free(pole);
  return 0;
}

