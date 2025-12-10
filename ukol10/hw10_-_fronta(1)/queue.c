#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
  
enum {
  ERROR_FNAME = 101,
  ERROR_FOPEN = 101,
  ERROR_CMD = 101,
  ERROR_CAPACITY = 101,
  ERROR_MALLOC = 101
};
  
#define SIZE_OF_ALLOC 4
  
FILE *open_file(const char *fname);
  
int process_file(FILE *fd);
  
int read_queue_capacity(FILE *fd);
  
char read_queue_cmd(FILE *fd, int *v);
  
FILE *open_file(const char *fname) {
  FILE *fd = NULL;
  if (fname == NULL) {
    fprintf(stderr, "ERROR: Filename not given\n");
    //;
  }
  if ((fd = fopen(fname, "r")) == NULL) {
    fprintf(stderr, "ERROR: Cannot open file \"%s\"\n", fname);
  }
  return fd;
}
  
//int process_file(FILE *fd) {
 // int ret = 0;
 // assert(fd);
  //int capacity = read_queue_capacity(fd);
  //if (capacity <= 0) {
  //  fprintf(stderr, "ERROR: Capacity has to be >0\n");
  //  return ERROR_CAPACITY;
  //}
  //}
  
queue_t* create_queue(int capacity){
  queue_t *q = ((queue_t*)malloc(sizeof(queue_t)));
  q->length = SIZE_OF_ALLOC;
  q->allocation = malloc((SIZE_OF_ALLOC+1)*sizeof(int *));
  q->allocated = SIZE_OF_ALLOC;
  q->point_save = 0;
  q->point_pop = 0;
  q->saved = 0;
  return q;
}
  
bool push_to_queue(queue_t *queue, void *data){
  int **array = queue->allocation;
  int point_save = queue->point_save;
  int point_pop = queue->point_pop;
  int saved = queue->saved;
  if (saved >= queue->allocated-2){
    //printf("Bylo Allocated %d\n", queue->allocated);
    queue->length = queue->length*2;
    queue->allocated = (int)(queue->allocated)*2;
    //printf("Allocated %d, %d\n", queue->allocated, queue->length);
    queue->allocation = realloc(queue->allocation, ((queue->allocated)+1)*sizeof(int *));
    array = queue->allocation;
  }
  if ((point_save == queue->length) && (point_pop > 0)){
    point_save = 0;
  }
  else if (saved == queue->length){
    //fprintf(stderr, "Kapacita fronty je naplnena\n");
    return false;
  }
  else if (point_save < queue->length){
      
  }
    
  //int *copy = malloc(sizeof(int));
  //*copy = *((int *)data);
  array[point_save] = data;
  //printf("Pushnuto %d %d\n", *(array[point_save]), point_save);
  point_save += 1;
  queue->point_save = point_save;
  queue->saved +=1;
  //free(data);
  return true;
}
  
void* pop_from_queue(queue_t *queue){
  int **array = queue->allocation;
  int point = queue->point_pop;
    
  int saved = queue->saved;
  if (saved == 0){
    //printf("Saved %d\n", saved);
    return NULL;
  }
  int capacity = queue->length;
  if (point == capacity){
    point = 0;
  }
  int *return_point = array[point];
  //printf("Hodnota %d %d\n", *(return_point), point);
  queue->point_pop = point+1;
  queue->saved -=1;
  if ((queue->saved < (queue->allocated+1)/2) && (queue->allocated > 10)){
    //printf("Reallocated\n");
    int puvodni_length = queue->allocated;
    queue->allocated = (int)queue->allocated/2;
    queue->length = (int)queue->length/2;
  
    int **tmp = malloc((queue->length+1)*sizeof(int*));
    for (int i = queue->point_pop, e = 0; e < queue->saved; e++){
      tmp[e] = array[i];
      i = (i + 1) % puvodni_length;
    }
    free(queue->allocation);
    queue->allocation = tmp;
    queue->point_save = queue->saved;
    queue->point_pop = 0;
  }
  return return_point;
    
  //printf("Deletnuto %d %d\n", *(array[point]), point);
    
}
  
void* get_from_queue(queue_t *queue, int idx){
  int saved = queue->saved;
  int **array = queue->allocation;
  int point = queue->point_pop;
  int capacity = queue->length;
  if ((idx >= saved) || (point + idx < 0)){
    //printf("Point: %d, saved:%d\n", point, saved);
    return NULL;
  }
    return array[(point + idx)% capacity];
}
  
int get_queue_size(queue_t *queue){
  return queue->saved;
}
  
void delete_queue(queue_t *queue){
  for (int i = 0; i < queue->allocated; i++){
    if (queue->allocation[i] != NULL) {
      free(queue->allocation[i]);
    }
      
    }
    free(queue->allocation);
    free(queue);
  
}
  
int read_queue_capacity(FILE *fd) {
  assert(fd);
  int capacity;
  if (fscanf(fd, "%d", &capacity) != 1) {
    capacity = -1;
  }
  return capacity;
}
