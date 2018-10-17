#ifndef STATS_H
#define STATS_H


typedef struct  {
    int factory_num;
    int made_num;
    int eaten_num;
    double min_deley;
    double avg_delay;
    double max_delay;

}factory_data_t;


void stats_init(int num_producers);
void stats_cleanup(void);
void stats_record_produced(int factory_number);
void stats_record_consumed(int factory_number, double delay_in_ms);
void stats_display(void);

#endif
