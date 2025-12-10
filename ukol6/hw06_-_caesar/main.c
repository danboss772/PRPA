#include <stdio.h>
 
#include <stdlib.h>
 
// Function to get and check input
char *get_input(int size_of_arr) {
  char x; // charakter we are getiinng from input now
          // I call it c, something like "i"
  int i = 0;
 
  // Allocate some space
  char *array = calloc(size_of_arr, sizeof(char));
 
  while ((x = getchar()) != '\n') {
    // if the size is small-double it
    if (i >= size_of_arr) {
      size_of_arr = 2 * size_of_arr;
      array = realloc(array, sizeof(char) * size_of_arr);
    }
    array[i] = x; // write input to array
    if (x < 65 || (x > 90 && x < 97) || x > 122) {
    // Allocate array with wrong charakter
    // to check in main
    char *zero_arr = calloc(2, sizeof(char));
    zero_arr[0] = '-';
    zero_arr[1] = '\0';
    free(array);
      return zero_arr;
    }
    i++;
  }
  array[i] = '\0';
  return array;
}
// Function to check real length of input array()
// If not the same, stop program
int check_size(char *encoded, char *recieved) {
  int length1 = 0, length2 = 0, i;
 
  for (i = 0, length1 = 0; encoded[i] != '\0'; i++) {
    if (encoded[i] != 0) {
      length1++;
    } else {
      break;
    }
  }
 
  for (i = 0, length2 = 0; recieved[i] != '\0'; i++) {
    if (recieved[i] != 0) {
      length2++;
    } else {
      break;
    }
  }
  if (length1 != length2) {
 
    return 101;
  }
 
  return 0;
}
 
// Function to compare arrays
// Return count of similar
// characters in both strings
int compare(const char *encoded, const char *received) {
  int i;
  long int cnt_of_sim_char = 0;
 
  for (i = 0; encoded[i] != '\0' || received[i] != '\0'; i++) {
    if (encoded[i] == received[i]) {
      cnt_of_sim_char += 1;
    }
  }
 
  return cnt_of_sim_char;
}
 
// Function to rotate one char by offset
// I always set chat to abs value
// so that A to Z are 0-25
// and a to z are 26-51
char rotate(const char original, int offset) {
  int new_char, org;
 
  new_char = original + offset;
  // If is small
  if (original >= 'a' && original <= 'z') {
    org = ((original - 'a') % 26) + 26;
  }
  // If is capital
  else if (original >= 'A' && original <= 'Z') {
    org = (original - 'A') % 26;
  }
  // If not in alphabet
  else {
    return 0;
  }
  new_char = (org + offset) % 52;
  if (new_char > 25) {
    return 'a' + new_char - 26;
  } else {
    return 'A' + new_char;
  }
 
  return new_char;
}
 
// Funcions to shift an array by an offset
// We use a temporary array to store rotated
// No need to return it, because array is not copied
void shift(const char *src, char *dst, int offset) {
  int i;
  for (i = 0; src[i] != '\0'; i++) {
    dst[i] = rotate(src[i], offset);
  }
  return;
}
 
int main() {
  int i = 0;
  int size_of_enc = 20, size_of_rec = 20;
  char *encoded;
  char *recieved;
  int neco;
  if (scanf("%d", &neco) == 1) {
  	
  }
  getchar();
  encoded = get_input(size_of_enc);
  recieved = get_input(size_of_rec);
  // Check charachters
  // If wrong charakter, the first element
  // of array is '-'
  // Formatter does not take return -1
  // in get_input
  if (encoded[0] == '-' || recieved[0] == '-') {
    fprintf(stderr, "Error: Chybny vstup!");
    free(encoded);
  free(recieved);
    return 100;
  }
  // Check size
  if (check_size(encoded, recieved) == 101) {
  free(encoded);
  free(recieved);
    fprintf(stderr, "Error: Chybna delka vstupu!");
    return 101;
  }
 
  // Allocate array for 52 shifts
  // Not useful, but may be used in 03b
  //Get real size of encoded first
  long int size_of_encoded = 1;
  for(i=0;encoded[i] != '\0'; i++){
  size_of_encoded++;
  }
  char *dst = calloc(size_of_encoded, sizeof(char));
  // Why long int? Brute has int lenth of 2 bytes
  // and sometimes we need values more than 32 hundred
  int *field_of_answers = calloc(52, sizeof(long int));
  // try every shift
  for (i = 0; i < 52; i++) {
    shift(encoded, dst, i);
    // For every i count similar
    long int cnt_of_sim_char = compare(recieved, dst);
    field_of_answers[i] = cnt_of_sim_char;
  }
  int best_i = -1, the_biggest = 0;
  for (i = 0; i < 52; i++) {
    if (field_of_answers[i] > the_biggest) {
      best_i = i;
      the_biggest = field_of_answers[i];
    }
  }
 
  // Print the best value
  shift(encoded, dst, best_i);
  for (i = 0; dst[i] != '\0'; i++) {
    printf("%c", dst[i]);
  }
 
  printf("\n");
  // Free heap space
  free(encoded);
  free(recieved);
  free(dst);
  free(field_of_answers);
  return 0;
}
