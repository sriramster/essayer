/* Trying CPU meter with opengl */

#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include "cpu_meter.h"

struct cpu_usage* c;

/* void cpu_meter_draw() { */
/* } */

int main() {
     int stat = 0;
     c = (struct cpu_usage*)(malloc(sizeof(struct cpu_usage)));
     c = get_cpu_usage();
     printf("\n cpu time = %d %d %d",c->cpu_t,c->idle_t,c->sys_t);
     return 0;
}
