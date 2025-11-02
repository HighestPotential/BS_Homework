#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process process_array[max_processes];
struct process process_array_backup[max_processes];
int num_processes = 0;
int timer = 0;

// Example implementation for the First-Come, First-Served scheduling algorithm
void fcfsScheduler()
{
    struct process *p;

    for (int i = 0; i < num_processes; i++)
    {
        p = &process_array[i];
        if (p->remaining_runtime > 0)
        {
            schedule(p, p->remaining_runtime);
        }
    }
}

// TODO: Implement the Round Robin scheduling algorithm you learned about in the lecture.
// HINT (For all scheduling algorithms): Use the schedule() function to simulate the execution of a process.
void roundRobinScheduler()
{
    // TODO
    // ...
    const int timeslice = 2;
    struct process *p;
    while (!allProcessesFinished())
    {
        for (size_t i = 0; i < num_processes; i++)
        {
            p = &process_array[i];
            if (p->remaining_runtime > 0)
            {
                if ( p->remaining_runtime >= 2)
                {
                    schedule(p, 2);
                }
                else if (p->remaining_runtime <2)
                {
                    schedule(p,p->remaining_runtime);
                }
            }
        }
    }

}

// TODO: Implement the Shortest Job First scheduling algorithm
void sjfScheduler()
{
    struct process* p;

    while (!allProcessesFinished())
    {
        p = findShortestJob();
        schedule(p, p->remaining_runtime);
    }
    
}

int main(int argc, char *argv[])
{
    // Read in processes from user
    num_processes = read_in();
    memcpy(process_array_backup, process_array, sizeof(struct process) * num_processes);

    // Run using FCFS
    fprintf(stderr, "Running F(irst)-C(ome), F(irst)-S(erved) Scheduler:\n");
    fcfsScheduler();

    // Run using SJF
    reset(); // Reset the process_array and the timer for the next scheduler
    fprintf(stderr, "Running S(hortest) J(ob) F(irst) Scheduler:\n");
    sjfScheduler();

    // Run using Round Robin
    reset(); // Reset the process_array and the timer for the next scheduler
    fprintf(stderr, "Running Round Robin Scheduler:\n");
    roundRobinScheduler();

    exit(EXIT_SUCCESS);
}
