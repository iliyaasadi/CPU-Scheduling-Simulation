#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime; // For RR scheduling.
    int startTime;     // To compute response time.
    int completionTime;
} Process;

typedef struct {
    float avgTurnaround;
    float avgWaiting;
    float avgResponse;
} Metrics;

// Returns average metrics computed by FCFS scheduling algorithm.
Metrics fcfs_metrics(Process proc[], int n);

// Returns average metrics computed by non-preemptive SJF scheduling.
Metrics sjf_metrics(Process proc[], int n);

// Returns average metrics computed by Round Robin scheduling given a time quantum.
Metrics rr_metrics(Process proc[], int n, int timeQuantum);

#endif
