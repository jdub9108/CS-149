# CS-149
Operating System

Ad mentioned in the class, you should have implemented a few more instructions (in addition to fetch and store). Try and implement 8 to 12 instructions. Using these instructions, write a program - which is basically a set of instructions, doesn't matter if these don't make any sense. We only need to keep track of where they are loaded in the memory and the program counter, registers etc.

We will treat this as a single user OS - no need to track user ownership of processes. We will also treat each program as a process. To show that there are multiple processes loaded, we will show multiple programs in memory.

Implement a process table to keep track of processes - use fields given on slide 15 unit IV and any other you think is necessary. Make sure to use one field for the names of programs (easier to follow than process id).

Upload several programs - at least six. Allocate stacks for each of these. Allocate a separate block of memory for a current running process - we will use this for displaying context switching. Display (print out) the contents of the process table, showing entries for each of these processes (programs). Print out the memory layout showing how the processes are loaded.

Create a null process - this should be in the current process block when you print the memory layout at this point.

Use a random number generator to assign priorities and process state to the processes. You will then check both these to determine which process will run next. You will then context switch this process with the null process - printing out the memory layout to indicate this is done properly.

Run a timer routine that gives out a random number of seconds. Generate a time slot. Wait until this time runs out and then run the schedule - meaning,  run the random numbers again to assign priority and process state values in the table. Determine which process will run next and context switch it with the current process. Make sure to print out the memory layout at each stage to show this is happening correctly.

Show output for five of these iterations - running random numbers, assigning priority and process state and context switching with current process.

You will also need to maintain a queue of processes that show eligibility to run next - does not show suspended or waiting processes.


process table implementation
20 pts
null process implementation
20 pts
process priority and state generator impementation
20 pts
process queue implementation
20 pts
demo runs
20 pts
