# color-guard
Lab 1 for Embedded Systems. Watches and responds to flags.

Below is the Word doc describing the objectives.

## Lab Assignment 1
By Group (2 students at most per group)
(Due Date on Syllabus/Canvas)

**IMPORTANT:**

Your code will be tested and graded on the Engineering Unix (Tux) machines. If the code does not work on those machines, you will not get any credit even if your code works on any other machine.
A late submission will get a 50% penalty if submitted after 9:00pm on the due day. After 9:00pm the next day, you cannot submit the lab.
One submission per group.
Writing and presentation of your report are considered to grade your lab. Your conclusions must be supported by the data/measurements you collect.
The quality of your code will be evaluated.

First, it is assumed that by January 23, 

1. you have an engineering Unix account, 
2. you can edit, 
3. you can compile, and 
4. you can execute C programs on the Unix (Tux) machines. You can use any personal computer or computing lab to remotely access the Engineering Unix machines. 

Second, it is assumed that by January 23, you have your group partners. 

## Objectives: 
Look at “How to get started?” at the very end of the lab.
This lab has three parts: 

1. Write a code to control an embedded system, 
2. evaluate your code, and 
3. analyze your code.

The instructor developed a framework that allows the simulation of a system to monitor/control.  

The instructor wrote the code that randomly generates events from one to 31 devices. Events are generated on EACH device at an average inter-arrival (in seconds) lambda. Each event requires an average service time mu (provided in percentage of lambda). Your objective is to detect ALL events and service them. Depending on your software and hardware architecture, the frequency of your events (lambda), and the required service time (mu), you may miss events. You must minimize the number of missed events.

### 1) Control Program
Write a program to control an embedded system with Number_Devices devices. Events occur randomly on each device. When an event occurs on device i, the ith bit of the variable Flags (starting from the left) is raised. 

*Example: Suppose that Flags = 0 (0000 0000) and  Device 3 generates an event, the variable Flags takes the value 8 = (0000 1000). Later Device 1 gets an event and Flags becomes ((0000 1010).*  

When an event occurs on Device i, a flag is raised in the variable Flags and the corresponding event is stored in the buffer BufferLastEvent[i]. An event has the following structure:

``` C
typedef struct EventTag{
  Identifier EventID;
  Identifier DeviceID;
  Timestamp  When;
  char       msg[64];
  int      priority;
} Event;
```

When a device generates an event, you must display this event (you may use the function `DisplayEvent` in the file `common.h`) and you must call the function `Server(Event *whichEvent)` to process your event.
We assume that the devices do not generate interrupts: whenever an event occurs, the device raises a bit flag in the variable Flags and stores the last event in the buffer. There is storage for only one event on each device.   Note that devices raise the flags in the variable Flags, but the function Server does not reset the flags in Flags. It is your responsibility to reset the corresponding flag as/when appropriate.

Your code must process events such that you miss as few events without forking processes or threads: we assume that there is no real time OS support. You will be provided three files: common.h, devices.o, and lab1.c. You are not allowed to modify the file common.h or the main function in the lab1.c file. In the file lab1.c, you must develop your code INSIDE the function Control(). You may add global variables or routines (functions, methods) in the file lab1.c. To compile your program, 
you must type: `cc -o lab1 devices.o lab1.c -lm`
where  

- `devices.o` is the object file that emulates devices generating events
- `lab1`  is the executable.
- `lab1.c` is your source file

YOU CANNOT MODIFY common.h (the original file common.h will be used to compile your submitted code)
YOU CAN read and write the variable Flags. Flags is the only variable you can modify.
YOU CAN ONLY READ the array BufferLastEvent[i]. Do not write on this array.
YOU CAN create new variables, new types, new routines/functions …. in your lab1.c source.

### 2) Code Evaluation
Compile your code with `cc –o lab1 devices.o lab1.c -lm`.
Execute your code with `lab1 NbrDevices lambda mu Show`, where 

- NbrDevices is the number of devices, 
- lambda is the average interarrival (in seconds) of events on EACH device, 
- mu is the average service time (provided in percentage of lambda/NbreDevices) of an event (duration of the function Server()), 
- Show is a flag (0 or 1) to display and dump events to files. 

The code generates about 100 events per device and stops.
In order to evaluate your code, you must execute the program until it stops. You must “instrument” your code to collect the following values (A is the average percentage of missed events, B is the average response time, and C is the average turn around time):


For each combination, you must collect the number of missed events (events generated by the devices and that you did not process (serve)) for each device and compute the average number of missed events.

### 3) Code Analysis
- You must explain why your code misses events and how the number of misses is related to lambda and Mu. Explain also the variations of the response time and turn-around time.
- What could be done to decrease the number of missed events? What could be done to improve the response time? What could be done to improve the turnaround time?

## Get Started
- compile the code I provided you: cc-o lab1 devices.o lab1.c –lm
- Execute the code with two devices: ./lab1   2   1   10  0  
- Observe the variable Flags printed out on the screen
- Get a feel of the values that the variable Flags takes.
- Stop the execution with CTRL-C and see what you read.
- Execute with 4 devices:  ./lab1   4   1   10  0 
- Observe the variable Flags printed out on the screen
- Get a feel of the values that the variable Flags takes.
- Stop and execute: ./lab1 2 1 10 1
- Now, with the parameter 1 (highlighted in red), you should see events generated
- Stop with CTRL-C…..
- “Play” with code Control() in lab1.c for detecting all events, then try to process them.

## What to turn in?
Electronic copy of your report and the C source code lab1.c. These two files must be put in a zipped folder named `lab1-name1-name2` where `name1` and `name2` are the last names of the teammates (on Canvas). Zip the folder and post it on Canvas. Use Microsoft Word for the report to get feedback. A penalty of 10 points will be applied if these instructions are not followed.

**Your report must:**

- state whether your code works
- report/analyze the results about the missed events (based on the filled table above). The quality of analysis and writing is critical to your grade.
address Part 3) “Code Analysis” (quality of writing (content and form) is of utmost importance)

Good writing and presentation are expected.

IMPORTANT: 
Your code will be tested and graded on the Engineering Unix (Tux) machines. If the code does not work on those machines, you will not get any credit even if your code works on any other machine.
A late submission will get a 50% penalty if submitted after 9:00pm on the due day. After 9:00pm the next day, you cannot submit the lab.
One submission per group.
Writing and presentation of your report are considered to grade your lab. Your conclusions must be supported by the data/measurements you collect.
The quality of your code will be evaluated.
