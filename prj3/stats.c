#include "stats.h"
#include <stdlib.h>
#include <stdio.h>

factory_data_t *fac_data;
int producer;

void stats_init(int num_producers){
  producer = num_producers;

  fac_data = (factory_data_t*)malloc(sizeof(factory_data_t)*num_producers);

  for(int i=0; i<num_producers;i++){
    fac_data[i].factory_num = 0;
    fac_data[i].made_num = 0;
    fac_data[i].eaten_num =0;
    fac_data[i].min_deley =0.0;
    fac_data[i].avg_delay =0.0;
    fac_data[i].max_delay =0.0;

  }




}

void stats_cleanup(void){

  free(fac_data);


}

void stats_record_produced(int factory_number){
    fac_data[factory_number].factory_num++;
}

void stats_record_consumed(int factory_number, double delay_in_ms){

  for(int i =0; i<factory_num; i++){
    if(fac_data[i].factory_num == factory_number){
      if(delay_in_ms < fac_data[i].min_deley){
        fac_data[i].min_deley = delay_in_ms;
      }
      if(delay_in_ms > fac_data[i].max_delay){
        fac_data[i].max_delay = delay_in_ms;
      }

      fac_data[i].eaten_num++;
      fac_data[i].avg_delay =( (fac_data[i].avg_delay)*(fac_data[i].eaten_num)+ delay_in_ms )/ fac_data[i].eaten_num;
      return;
    }
  }




}

void stats_display(void){
  printf("%8s%8s%8s%14s%14s%14s\n","Factory#", "#Made", "#Eaten", "Min Delay[ms]", "Avg Delay[ms]", "Max Delay[ms]" );
  for(int i = 0; i< producer; i++){

    printf("%8d%8d%8d   %10.5f    %10.5f    %10.5f\n",fac_data[i].factory_num,fac_data[i].made_num,fac_data[i].eaten_num,fac_data[i].min_deley, fac_data[i].avg_delay,fac_data[i].max_delay)

  }


}
