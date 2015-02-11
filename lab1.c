
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
int len = sizeof(BufferLastEvent) / sizeof(BufferLastEvent[0]);

int handled[32] = { 0 };
int responseTimes[32] = { 0 };
int turnAroundTimes[32] = { 0 };


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
       int x = len;
      for(x; x >= 0 && Flags > 0; x--) {
        long unsigned int ex = exp2(x);

        // if the current flag is not set, don't handle an event
        if(Flags < ex) continue;

        Event * e = &BufferLastEvent[x];
        if(Show) {
          printf("\n");
          DisplayEvent('m', e);
        }
        responseTimes[x] += Now() - e->When;
        Server(e);
        turnAroundTimes[x] += Now() - e->When;
        handled[x]++;
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
  int x = 0;
  int totalEvents = 0;
  int totalHandled = 0;
  int totalResponseTime = 0;
  int totalTurnAroundTime = 0;

  printf("DEVICE RESULTS =====\n\n");

  for(x; x < len; x++) {
    if(handled[x] <= 0) continue;

    int totalEventsOnDevice = (int)&BufferLastEvent[x].EventID;

    totalEvents += totalEventsOnDevice;
    totalHandled += handled[x];
    totalResponseTime += responseTimes[x];
    totalTurnAroundTime += turnAroundTimes[x];

    printf("\tDevice %d ==========\n", x);
    printf("\t\tHandled %d events\n", handled[x]);
    printf("\t\tMissed %d events\n", totalEventsOnDevice - handled[x]);
    printf("\t\tMissed %10.3f%% of total events on this device\n",
      100*(float)(totalEventsOnDevice - handled[x])/totalEventsOnDevice);
    printf("\n");
    printf("\t\tAverage response time: \t%10.3f\n", (float)responseTimes[x]/handled[x]);
    printf("\t\tAverage turn-around time: \t%10.3f\n", (float)turnAroundTimes[x]/handled[x]);
    printf("\n");
  }

  printf("TOTAL RESULTS =====\n\n");

  printf("\tTotal events generated: %d\n", totalEvents);
  printf("\tTotal events handled: %d\n", totalHandled);
  printf("\tTotal events missed: %d\n", totalEvents - totalHandled);
  printf("\tMissed %10.3f%% of total events\n",
    100*(float)(totalEvents - totalHandled)/totalEvents);
  printf("\n");
  printf("\tAverage response time: \t%10.3f\n", (float)totalResponseTime/totalHandled);
  printf("\tAverage turn-around time: \t%10.3f\n", (float)totalTurnAroundTime/totalHandled);
  printf("\n");
}
