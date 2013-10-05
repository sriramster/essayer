/* Reading the CPU usage data */

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include "cpu_meter.h"

int open_stat_file() {
     FILE *fp;
     if(!(fp = fopen("/proc/stat","r"))) {
	  perror("\n can't open /proc/stat file \n");
	  exit(1);
     }
     return fp;
}

struct cpu_usage* get_cpu_usage() {
     FILE *fp;
     int cpu_t, nice_t,sys_t,idle_t;
     struct cpu_usage* tmp;

     tmp = (struct cpu_usage *)(malloc(sizeof(struct cpu_usage)));

     fp = open_stat_file();

     fscanf(fp, "%*s %d %d %d %d", &(tmp->cpu_t), &(tmp->nice_t), &(tmp->sys_t), &(tmp->idle_t));

     return tmp;
}



