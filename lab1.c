
/*****************************************************************************\
* Laboratory Exercises COMP 3510                                              *
* Author: Saad Biaz                                                           *
* Date  : January 18, 2014                                                    *
\*****************************************************************************/

/*****************************************************************************\
*                             Global system headers                           *
\*****************************************************************************/


#include "common.h"

/*****************************************************************************\
*                             Global data types                               *
\*****************************************************************************/



/*****************************************************************************\
*                             Global definitions                              *
\*****************************************************************************/





/*****************************************************************************\
*                            Global data structures                           *
\*****************************************************************************/




/*****************************************************************************\
*                                  Global data                                *
\*****************************************************************************/




/*****************************************************************************\
*                               Function prototypes                           *
\*****************************************************************************/

void Control(void);



/*****************************************************************************\
* function: main()                                                            *
* usage:    Create an artificial environment for embedded systems. The parent *
*           process is the "control" process while children process will gene-*
*           generate events on devices                                        *
*******************************************************************************
* Inputs: ANSI flat C command line parameters                                 *
* Output: None                                                                *
*                                                                             *
* INITIALIZE PROGRAM ENVIRONMENT                                              *
* WHILE JOBS STILL RUNNING                                                    *
*    CREATE PROCESSES                                                         *
*    RUN LONG TERM SCHEDULER                                                  *
*    RUN SHORT TERM SCHEDULER                                                 *
*    DISPATCH NEXT PROCESS                                                    *
\*****************************************************************************/

int main (int argc, char **argv) {

   if (Initialization(argc,argv)){
     Control();
   }
} /* end of main function */

/***********************************************************************\
 * Input : none                                                          *
 * Output: None                                                          *
 * Function: Monitor Devices and process events                          *
 \***********************************************************************/
void Control(void){
  int i;
  Status LastStatus=0;
  while (1) {
    printf("%10.3f\tFlags = %d \n ", Now(), Flags);
    sleep(1); // Just to slow down to have time to see Flags
    if (Flags != LastStatus){
      LastStatus = Flags;
      printf("\n>>> When: %10.3f  Flags = %d\n", Now(),
	     Flags);
       printf("\n%%%% TESTING %%%%");
       int len = sizeof(BufferLastEvent) / sizeof(BufferLastEvent[0]);
       int x = len;
      for(x; x >= 0 && Flags > 0; x--) {
        int ex = exp2(x);
        printf("\n\tCHECK: %d -> %d", ex);
        printf("\n\tFLAGS: %d", Flags);

        // if the current flag is not set, don't handle an event
        if(Flags < ex) continue;

        Event * e = &BufferLastEvent[x];
        if(Show) {
          printf('\n');
          DisplayEvent('m', e);
        }
        Server(e);
        Flags -= ex;
      }
    }
  }
}


/***********************************************************************\
* Input : None                                                          *
* Output: None                                                          *
* Function: This must print out the number of Events buffered not yet   *
*           not yet processed (Server() function not yet called)        *
\***********************************************************************/
void BookKeeping(void){
  printf("\n >>>>>> Done\n");
}
