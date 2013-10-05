#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* a[0] :  _  
 * a[1] : | |  
 * a[2] :  -
 * a[3] : | | 
 * a[4] :  -  */

/*    -    -         -        -    -     -      -    *
 * |    |    |  | | |   |      | |   | |   |  |   |  *
 *    -    -     -   -    -        -     -           *
 * | |       |    |   | |   |  | |   |     |  |   |  *
 *    -    -         -    -        -     -      -    */

#define NO_OF_SEGMENTS 7

char a[2] = { '-', '|' };

static char* _on_segments[10] = {
     "1110111",
     "0010010",
     "1011101", 
     "1011011", 
     "0111010", 
     "1101011", 
     "0101111", 
     "1010010", 
     "1111111", 
     "1111011", 
};

static char* result[4];
/*   -  *
    | | *
     -  *
    | | *
     -  */

void generate_char_set(int *num, char *src,int src_len) {
     int k = 0;
     static char num_cp[10];
     strncpy(num_cp,src,src_len);
     int idx = *num;
     int old_k = 0;
     for(k = 0 ; k <= src_len ; k++) {
	  if(num_cp[k] == '1') {
	       int case_ctrl = 0;

	       /* Stupid if..else ladder  */
	       if(k == 0)
		    case_ctrl = 0;

	       else if((k >= 1) && (k <= 2)) {
		    case_ctrl = 1;
		    if((old_k >= 1) && (k <= 2))
			 case_ctrl = 5;
	       }
	       else if(k == 3) 
		    case_ctrl = 2;

	       else if((k >= 4) && (k <= 5)) {
		    case_ctrl = 3;
		    if((old_k >= 4) && (k <= 5))
			 case_ctrl = 5;
	       }

	       else 
		    case_ctrl = 4;
	       
	       switch(case_ctrl)
	       {
	       case 0:
		    result[0] = " - ";
		    break;
	       case 1:
	       	    if((k % 2) == 0)
	       		 result[1] ="|  ";
	       	    else
	       		 result[1] = "  |";
	       	    break;
	       case 2:
	       	    result[2] = " - ";
	       	    break;
	       case 3:
	       	    if((k % 2) == 0)
	       		 result[3] = "|  ";
	       	    else
	       		 result[3] = "  |";
	       	    break;
	       case 4:
	       	    result[4] = " - ";
	       	    break;
	       case 5:
	       	    if(k <= 2)
	       		 result[1] = "|  |";
	       	    else
	       		 result[3] = "|  |";
	       	    break;
	       default: break;
	       }
	       old_k = k;
	  }
     }
     int j = 0;
     for(j = 0; j <= 4; j++) {
	  if(result[j] == NULL)
	       result[j] = "\0";
	  printf("\n %s",result[j]);
     }
}
void main() {
     int _num;
     char *source[10];
     printf("\n Enter the number to be displayed as seven segment\n");
     scanf("%d",&_num);
     memcpy(source ,_on_segments[_num], strlen(_on_segments[_num]));
     int src_len = strlen(_on_segments[_num]);
     generate_char_set(&_num, &source, src_len);
}
