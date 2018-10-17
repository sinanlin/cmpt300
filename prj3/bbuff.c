#include "bbuff.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>


void* buffer[BUFFER_SIZE];

sem_t mutex;
sem_t empty;
sem_t full;



void bbuff_init(void){

  // initialize semaphore
  sem_init(&mutex,0,1);
  sem_init(&empty,0,BUFFER_SIZE);
  sem_init(&full,0,0);

  candy_t *candy = malloc(sizeof(candy_t));
  candy->factory_number = 0;
  candy->time_stamp_in_ms = 0;

}




void bbuff_blocking_insert(void* item){
  if(item == NULL){
    perror("NULL INSERTION.\n ");
  }
  sem_wait(&empty);
  sem_wait(&mutex);

  for(int i=0; i<BUFFER_SIZE;i++){
    if(buffer[i] == NULL){
      buffer[i] = item;
      break;
    }
  }
  sem_post(&mutex);
  sem_post(&full);
}



void* bbuff_blocking_extract(void){
  void* val = malloc(sizeof(void*));
  sem_wait(&full);
  sem_wait(&mutex);

  for(int j=0; j<BUFFER_SIZE; j++){

    if(buffer[j]!=NULL){
      val = buffer[j];
      buffer[j] = NULL;
      break;

    }
  }
  sem_post(&mutex);
  sem_post(&empty);
  return val;
}

_Bool bbuff_is_empty(void){
  for(int k =0; k<= BUFFER_SIZE; k++){
      if(buffer[k] != NULL){
        return false;
      }
  }
  return true;
}
