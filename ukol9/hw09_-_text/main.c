#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

typedef struct slovo{
	char* text;
	int pocet_vyskytu;
	int index;
}SLOVO;

int comp(const void* a, const void* b)
{
    const SLOVO* arg1 = (const SLOVO*)a;
    const SLOVO* arg2 = (const SLOVO*)b;
 
    if (arg1->pocet_vyskytu < arg2->pocet_vyskytu) return -1;
    if (arg1->pocet_vyskytu > arg2->pocet_vyskytu) return 1;
     return arg1->index - arg2->index;
}

int comp2(const void* a, const void* b)
{
    const SLOVO* arg1 = (const SLOVO*)a;
    const SLOVO* arg2 = (const SLOVO*)b;
    
    int c = strcmp(arg1->text, arg2->text);
     if (a != 0){
     	return c;
     }
     else {
     return arg1->index - arg2->index;
     }
}

void printer(SLOVO* slova, int pocet_slov, int elko, int esko){
	if (elko > 0){
	printf("Seznam slov:\n");
	}
	int i = 0, d = 0;
	if (esko == 1){
		qsort(slova, pocet_slov, sizeof(SLOVO), comp);
	}
	else if (esko == 2){
		qsort(slova, pocet_slov, sizeof(SLOVO), comp2);
	}
	while (i < pocet_slov){
		if (elko != INT_MAX){
			if (strlen(slova[i].text) != elko){
				i++;
				continue;
			}
		}
		printf("%-21s", slova[i].text);
		printf("%d\n", slova[i].pocet_vyskytu);
		i++;
	}
	printf("Pocet slov:          %d\n", pocet_slov);
	printf("Nejcastejsi:        ");
	int k;
	k = slova[pocet_slov-1].pocet_vyskytu;
	if (esko == 0){
		qsort(slova, pocet_slov, sizeof(SLOVO), comp);
		d = slova[0].pocet_vyskytu;
		k = slova[pocet_slov-1].pocet_vyskytu;
	}
	if (esko == 1){
		qsort(slova, pocet_slov, sizeof(SLOVO), comp);
		k = slova[pocet_slov-1].pocet_vyskytu;
		d = slova[0].pocet_vyskytu;
	}
	if (esko == 2){
		qsort(slova, pocet_slov, sizeof(SLOVO), comp);
		d = slova[0].pocet_vyskytu;
		k = slova[pocet_slov-1].pocet_vyskytu;
		qsort(slova, pocet_slov, sizeof(SLOVO), comp2);
	}
	i = 0;
	
	while (i < pocet_slov){
		if (slova[i].pocet_vyskytu == k){
		printf(" ");
		printf("%s", slova[i].text);
		}
		i++;
	}
	printf("\n");
	printf("Nejmene caste:      ");
	i = 0;
	k = slova[0].pocet_vyskytu;
	while (i < pocet_slov){
	if (slova[i].pocet_vyskytu == d){
		printf(" ");
		printf("%s", slova[i].text);
		}
		i++;
	}
	printf("\n");
}

int parse_str(char* str, int len, int cecko, int elko, int esko){
	int i = 0, k = 0, l =0, d = 0, x = 0, was_slovo = 0, index = 0;
	int pocet_slov_alloc = 20;
	SLOVO* slova = (SLOVO*)malloc(pocet_slov_alloc*sizeof(SLOVO));
	slova[0].text = (char*)malloc(21*sizeof(char));
	slova[0].pocet_vyskytu = 1;
	slova[0].index = index;
	index += 1;
	char c;
	while (i < len){
		if (isspace(str[i])){
			if (was_slovo == 0){
				i++;
				continue;
			}
			was_slovo = 0;
			slova[k].text[l] = '\0';
			//printf("%s\n", slova[k].text);
			l = 0;
			d = 0;
			x = 0;
			while (d < k){
				if (strcmp(slova[d].text, slova[k].text) == 0){
					slova[d].pocet_vyskytu += 1;
					x = 1;
				}
				d++;
			}
			if (x == 1){
				
			}
			else {
				k+= 1;
				slova[k].text = (char*)malloc(21*sizeof(char));
				slova[k].pocet_vyskytu = 1;
				slova[k].index = index;
				index += 1;
				if (k+1 >= pocet_slov_alloc){
					pocet_slov_alloc += 20; 
					slova = (SLOVO*)realloc(slova, pocet_slov_alloc*sizeof(SLOVO));
				}
			}
			
		}
		else{
			if (str[i] != ':' && str[i] != ';' && str[i] != ',' && str[i] != '.' && str[i] != '?'){
				was_slovo = 1;
				c = str[i];
				if (cecko == 0){
				if (c < 97){
					c+= 32;
				}
				}
				slova[k].text[l] = c;
				l++;
			}
		}
		i++;
	}
	//printf("Pocet sl: %d\n", k);
	printer(slova, k, elko, esko);
	return 0;
}

/* The main program */
int main(int argc, char *argv[])
{
  int pocet_alloc = 20;
  char* str = (char*)malloc(pocet_alloc*sizeof(char));
  int i = 0;
  int cislo;
  char c;
  int cecko = 0;
  int elko = INT_MAX;
  int esko = 0;
  while(i<argc){
  	if (strcmp(argv[i], "-c")==0){
  		cecko = 1;
  	}
  	if (strcmp(argv[i], "-l")==0){
  		if (i < argc-1){
  			i++;
  			if (sscanf(argv[i], " %d", &elko) != 1){
  				fprintf(stderr, "Warning: Chybna hodnota parametru -l!\n");
  				elko = INT_MAX;
  				
  			}
  			if (elko < 0){
  				fprintf(stderr, "Warning: Chybna hodnota parametru -l!\n");
  				elko = INT_MAX;
  			}
  			i--;
  		}
  	}
  	if (strcmp(argv[i], "-s")==0){
  		if (i < argc-1){
  			i++;
  			if (sscanf(argv[i], " %d", &esko) != 1){
  				fprintf(stderr, "Warning: Chybna hodnota parametru -s!\n");
  				esko = 0;
  				
  			}
  			if (esko!= 1 && esko != 2){
  				fprintf(stderr, "Warning: Chybna hodnota parametru -s!\n");
  				esko = 0;
  			}
  			i--;
  		}
  	}
  	i++;
  }
  
  i = 0;
  
  while((cislo = (c = getchar()))!= -1){
  	str[i] = c;
  	i++;
  	if (i+2 >= pocet_alloc){
  		pocet_alloc += 20;
  		str = (char*)realloc(str, pocet_alloc*sizeof(char));
  	}
  }
  str[i] = '\n';
  i++;
  parse_str(str, i, cecko, elko, esko);
  return 0;
}

