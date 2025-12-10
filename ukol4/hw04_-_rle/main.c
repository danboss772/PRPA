#include <stdio.h>
#include <stdlib.h>

/* The main program */
int main(int argc, char *argv[]) {
  int cnt = -1, symc = 0, codec = 0;
  char znak = -1, last = -1;
  while (scanf("%c", &znak) == 1) {
  
  if (znak == 10){
  	if (cnt != -1) {
      if (cnt == 1) {
        printf("%c", last);
        codec += 1;
      } else if (cnt == 2) {
        printf("%c%c", last, last);
        codec += 2;
      } else {
        printf("%c%d", last, cnt);
        if (cnt < 10){
        	codec += 2;
        }
        else if (cnt < 100){
        	codec += 3;
        }
        else if (cnt < 1000){
        	codec += 4;
        }
        else {
        	codec += 5;
        }
      }
  }
  break;
  }
  
    if (((int)znak < 65 || (int)znak > 90) && znak != 10) {
      if (cnt == 1) {
        printf("%c", last);
        codec += 1;
      } else if (cnt == 2) {
        printf("%c%c", last, last);
        codec += 2;
      } else {
        printf("%c%d", last, cnt);
        if (cnt < 10){
        	codec += 2;
        }
        else if (cnt < 100){
        	codec += 3;
        }
        else if (cnt < 1000){
        	codec += 4;
        }
        else {
        	codec += 5;
        }
        
      }

      // printf("Znak %d", znak);
      fprintf(stderr, "Error: Neplatny symbol!\n");
      return 100;
    }
    if (znak == last) {
      cnt += 1;
    } else if (cnt != -1) {
      if (cnt == 1) {
        printf("%c", last);
        codec += 1;
      } else if (cnt == 2) {
        printf("%c%c", last, last);
        codec += 2;
      } else {
        printf("%c%d", last, cnt);
        if (cnt < 10){
        	codec += 2;
        }
        else if (cnt < 100){
        	codec += 3;
        }
        else if (cnt < 1000){
        	codec += 4;
        }
        else {
        	codec += 5;
        }
      }
      last = znak;
      cnt = 1;
    } else {
      last = znak;
      cnt = 1;
    }
    symc += 1;
    
    //printf("Zakodovano %d\n", codec);
  }
  printf("\n");
  fprintf(stderr, "Pocet vstupnich symbolu: %d\n", symc);
  fprintf(stderr, "Pocet zakodovanych symbolu: %d\n", codec);
  fprintf(stderr, "Kompresni pomer: %.2f\n", (float)codec / ((float)symc));
  return 0;
}

