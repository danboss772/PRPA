#include <stdio.h>
#include <ctype.h>
 
// Draw straight lines of X's
void draw_straight_line(int width){
  int i;
  for (i = 0; i < width; ++i) {
    printf("X");
  }
}
 
// Draw roof of the house
void draw_roof(int width, int height) {
  int i, j;
  for (i = 0; i < (width / 2); ++i) {
    printf(" ");
  }
  printf("X\n");
  for (i = 2; i < (width - 2); i = i + 2) {
    for (j = 0; j < (width - i) / 2; ++j) {
      printf(" ");
    }
    printf("X");
    for (j = 0; j < (i - 1); ++j) {
      printf(" ");
    }
    printf("X\n");
  }
  draw_straight_line(width);
  printf("\n");
}
 

// Draw inside of the house
void draw_inside_o_house(int cycle, int width) {
  int i;
  if (cycle % 2 == 0) {
    for (i = 0; i < (width - 3); i = i + 2) {
      printf("o*");
    }
    printf("o");
  } else {
    for (i = 0; i < (width - 3); i = i + 2) {
      printf("*o");
    }
    printf("*");
  }
}

// Draw only house without roof and fence
void draw_house_wo_fence(int width, int height) {
  int i, j;
  draw_roof(width, height);
  for (i = 0; i < (height - 2); ++i) {
    printf("X");
    if (width == height){
    	draw_inside_o_house(i, width);
    }
    else{
	    for (j = 0; j < (width - 2); ++j) {
	      printf(" ");
	    }
    }
    printf("X\n");
  }
 
  draw_straight_line(width);
  printf("\n");
}

 
// Draw only one line of fence (upper or
// lower). Can not be used without fence
void draw_fence_updown_lines(int fence) {
  int i;
  if ((fence % 2) != 0) {
    printf("|");
    --fence;
  }
  for (i = 0; i < fence; ++i) {
    if (i % 2 == 0) {
      printf("-");
    } else {
      printf("|");
    }
  }
}
 
// Draw middle part of the fence
void middle_fence_draw(int fence) {
  int i;
  // Function starts with 1 in order
  // to change the sequence of symbols.
  // 1 is added to the fence in
  // order to compensate the for cycle
  // length.
  if (fence % 2 != 0) {
    i = 1;
    ++fence;
  } else {
    i = 0;
  }
  for (; i < fence; ++i) {
    if (i % 2 != 0) {
      printf("|");
    } else {
      printf(" ");
    }
  }
}
 
// Draw house with fence
void draw_house_w_fence(int width, int height, int fence) {
  int i;
  draw_roof(width, height);
  for (i = 0; i < (height - 2); ++i) {
    printf("X");
    if (width == height){
    draw_inside_o_house(i, width);
    }
    else {
    	for (int j = 0; j < (width - 2); ++j) {
	      printf(" ");
	    }
    }
    printf("X");
    if (i == (height - fence - 1)) {
      draw_fence_updown_lines(fence);
    } else if (i >= (height - fence)) {
      middle_fence_draw(fence);
    }
    printf("\n");
  }
  draw_straight_line(width);
  draw_fence_updown_lines(fence);
  printf("\n");
}

int myFLush(void){
	char c;
	while ((c = getchar()) != EOF){
		if (c > 32 && !isdigit(c)){
			return 1;
		}
	}
	return 0;
}
 
int main() {
  int width = 0 , height, fence;
  int zadani = 0;
  int cnt = 0;
  cnt = scanf("%d %d %d", &width, &height, &fence);
  
  if (myFLush() != 0){
  	fprintf(stderr, "Error: Chybny vstup!\n");
  	return 100;
  }
  // Int on input control
  if(cnt == 1) {
  	zadani = 1;
  	if ((width < 3) || (width > 69)) {
    fprintf(stderr, "Error: Vstup mimo interval!\n");
    return 101;
  }
  }
  else if (cnt == 2) {       //#2
    zadani = 2;
    if ((width < 3) || (width > 69)) {
    fprintf(stderr, "Error: Vstup mimo interval!\n");
    return 101;
  }
  if ((height < 3) || (height > 69)) {
    fprintf(stderr, "Error: Vstup mimo interval!\n");
    return 101;
    }
    if (width % 2 == 0){
    	fprintf(stderr, "Error: Sirka neni liche cislo!\n");
    	return 102;
    	}
	
    }
   else if (cnt == 3) {       //#3
    zadani = 3;
    if ((width < 3) || (width > 69)) {
    fprintf(stderr, "Error: Vstup mimo interval!\n");
    return 101;
  }
  if ((height < 3) || (height > 69)) {
    fprintf(stderr, "Error: Vstup mimo interval!\n");
    return 101;
    }
    if (fence < 1){
    	fprintf(stderr, "Error: Vstup mimo interval!\n");
    return 101;
    }
    if (width % 2 == 0){
    	fprintf(stderr, "Error: Sirka neni liche cislo!\n");
    	return 102;
    	}
    if (fence >= height){
    	fprintf(stderr, "Error: Neplatna velikost plotu!\n");
    	return 103;
    }
    
  }
   else {
  	fprintf(stderr, "Error: Chybny vstup!\n");
    
    return 100;
  }
  
  //printf("Zadani %d %d\n", zadani, height);
  if (zadani == 1){
  draw_straight_line(width);
  printf("\n");
  	for (int i = 0; i < (width-2); ++i) {
    printf("X");
	    for (int j = 0; j < (width - 2); ++j) {
	      printf(" ");
	    }
    printf("X\n");
  }
 
  draw_straight_line(width);
  printf("\n");
  }
  /*
  // Input interval control
  if ((width < 3) || (width > 69) || (height < 3) || (height > 69)) {
    fprintf(stderr, "Error: Vstup mimo interval!\n");
    return 101;
  }
  // Control of width's oddness
  if (width % 2 == 0) {
    fprintf(stderr, "Error: Sirka neni liche cislo!\n");
    return 102;
  }
  */
  if (zadani == 2){
  	draw_house_wo_fence(width, height);
  }
  if (zadani == 3){
  	draw_house_w_fence(width, height, fence);
  }
  
  return 0;
}
