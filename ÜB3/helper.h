// These two lines (+ the last line) are called a header guard. You can ignore this.
#ifndef HELPER_H
#define HELPER_H

#include <unistd.h>
#include <stdbool.h>

// This is the blueprint for a process
struct process {
    pid_t pid;
    int remaining_runtime; // in seconds
};

#define max_processes 25
extern struct process process_array[max_processes];
extern struct process process_array_backup[max_processes];
extern int num_processes;
extern int timer;

// Simulate "scheduling" a process
void schedule(struct process *p, int run_duration);

// check if all processes already finished
bool allProcessesFinished();

// get the shortest jsob in the array
struct process *findShortestJob();

/***** The functions below this point should not be changed.      ****/
/***** You also do not have to use them to complete the exercise. ****/

void reset();
int read_in();

#endif
