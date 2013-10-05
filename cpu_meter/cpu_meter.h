#ifndef _CPU_METER_H_
#define _CPU_METER_H_

typedef struct cpu_usage {
     int cpu_t;
     int nice_t;
     int sys_t;
     int idle_t;
} cpu_usage;

#endif
