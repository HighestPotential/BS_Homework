#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulates the scheduling of a process for a given duration
void schedule(struct process *p, int run_duration){
    // Check if the parameters are valid
    if (run_duration > p->remaining_runtime) {
        fprintf(stderr, "Process %d cannot run for longer than its total duration (%d > %d).", p->pid, run_duration, p->remaining_runtime);
        exit(EXIT_FAILURE);
    }
    if (run_duration <= 0) {
        fprintf(stderr, "Can not run process for zero or negative duration.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Process %d is running for %d seconds...\n", p->pid, run_duration);
    p->remaining_runtime -= run_duration;
    timer += run_duration;
}


// Helper function to check if all processes have finished
bool allProcessesFinished(){
    for (int i = 0; i < num_processes; i++){
        struct process *p = &process_array[i];
        if (p->remaining_runtime > 0) {
            return false;
        }
    }
    return true;
}

// Helper function for finding the index of the job with the shortest remaining runtime
struct process *findShortestJob() {
    struct process *shortest = &process_array[0];
    struct process *current;
    for(int i = 1; i < num_processes; i++){
        current = &process_array[i];

        // In this case, the "shortest" is already finished. We don't want that one.
        if (shortest->remaining_runtime == 0) {
            shortest = current;
        }

        // In this case, the current process is already finished, so skip it.
        if (current->remaining_runtime == 0) {
            continue;
        }

        // If the current process needs less time than the "shortest", the current one is the shortest
        if (current->remaining_runtime < shortest->remaining_runtime) {
            shortest = current;
        }
    }
    if (shortest->remaining_runtime == 0) {
        fprintf(stderr, "You called \"findShortestJob\" even though all jobs are finished. Can't do that!\n");
        exit(EXIT_FAILURE);
    }
    return shortest;
}

/***** The functions below this point should not be changed.      ****/
/***** You also do not have to use them to complete the exercise. ****/


// Helper function to reset the state of the program for the next scheduler
void reset(){
    timer = 0;
    memcpy(process_array, process_array_backup, sizeof(struct process) * num_processes);
}

// Function to read in processes from user input
int read_in(){
    fprintf(stderr, "Enter duration for up to %d processes (one number per line).\n", max_processes);
    int process_count;
    for (process_count = 0; process_count < max_processes; process_count++) {
        int duration;
		pid_t pid = process_count + 1;
        fprintf(stderr, "Enter duration for process %d: ", pid);

        if(scanf("%d", &duration) != 1){
            fprintf(stderr, "Invalid input!\n");
            exit(EXIT_FAILURE);
        }

        if (duration == -1){
            break;
        }

        if(duration < 0){
            fprintf(stderr, "Duration must be non-negative (or -1 to stop)!\n");
            exit(EXIT_FAILURE);
        }

        process_array[process_count].pid = pid;
        process_array[process_count].remaining_runtime = duration;
        fprintf(stderr, "\n");
    }

    if (process_count == 0) {
        fprintf(stderr, "You entered no processes. This is not allowed.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "\n%d processes have been entered.\n\n", process_count);
    return process_count;
}

