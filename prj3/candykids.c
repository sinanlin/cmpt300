#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bbuff.h"
#include "stats.h"

#include <semaphore.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <inttypes.h>






//implicited funciton decleartion.
/*
double current_time_in_ms(void);
void* dathread_function(void* arg);
void read_command(char *buff);

//Define function.


double current_time_in_ms(void)
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec * 1000.0 + now.tv_nsec/1000000.0;
}


// For Thread Signaling
_Bool stop_thread = false;
void* dathread_function(void* arg) {
    while (!stop_thread) {
        // Do the work of the thread
    }
    printf("Done!");
}

*/





int main(int argc, char* argv[]){

// 1.  Extract arguments
/*
  int fac_num = 0;
  int kids_num = 0;
  int seconds = 0;



if(argc <= 3){
  printf("Please provide with 3 input for #Factories, #Kids, #Seconds.\n");
  return -1;
}


for(int i = 1; i <= 3; i++){

  if(atoi(argv[i]) <= 0 ){
    printf("The given arguments should be larger than 3.\n");
    }
  }

fac_num = atoi(argv[1]);
kids_num = atoi(argv[2]);
seconds = atoi(argv[3]);

  // 2.  Initialize modules


*/





/*
  // 1.  Extract arguments
  // 2.  Initialize modules
  // 3.  Launch candy-factory threads
  // 4.  Launch kid threads
  // 5.  Wait for requested time
  // 6.  Stop candy-factory threads
  // 7.  Wait until no more candy
  // 8.  Stop kid threads
  // 9.  Print statistics
  // 10. Cleanup any allocated memory
    // Spawn thread
    pthread_id daThreadId;
    pthread_create(&daThreadId, ...)

    // Wait
    sleep(...)

    // Tell thread to stop itself, and then wait until it's done.
    stop_thread = true;
    pthread_join(daThreadID, NULL)

*/

return 0;
}
