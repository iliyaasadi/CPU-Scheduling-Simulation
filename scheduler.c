#include "scheduler.h"
#include <stdio.h>

// ---------------- Scheduling Algorithms ----------------

// FCFS Scheduling
Metrics fcfs_metrics(Process proc[], int n) {
    int wt[n], tat[n], rt[n], total_wt = 0 , total_tat = 0 , total_rt = 0; 
    Metrics fcfs_metrics_calculated  ;

    wt[0] = 0;   // first proccess, has a waiting time of 0. 
    int total_time = 0 ; 

    for(int i = 0; i < n ; ++i){

        while(proc[i].arrivalTime > total_time){ // idle state
            total_time++ ; 
        }

        proc[i].startTime = total_time ; 
        proc[i].completionTime = proc[i].startTime + proc[i].burstTime ; 
        total_time += proc[i].burstTime ; 
        
        wt[i] = proc[i].startTime - proc[i].arrivalTime; 
        total_wt += wt[i] ;
        tat[i] = proc[i].completionTime - proc[i].arrivalTime ; 
        total_tat += tat[i] ;
        rt[i] = proc[i].startTime - proc[i].arrivalTime ; 
        total_rt += rt[i] ; 
    }

    printf(" FCFS Gantt Chart:\n");
    for (int i = 0; i < n; i++) {
    printf("| P%d (%d-%d) ", proc[i].pid, proc[i].startTime, proc[i].completionTime);
    }
    printf("|\n");
    printf("\n");

    fcfs_metrics_calculated.avgWaiting = (float) total_wt/n ; 
    fcfs_metrics_calculated.avgTurnaround = (float) total_tat/n ; 
    fcfs_metrics_calculated.avgResponse = (float) total_rt/n ; 

    return fcfs_metrics_calculated; 
}

// SJF Scheduling (Non-preemptive)
Metrics sjf_metrics(Process proc[], int n) {
    int wt[n], tat[n], rt[n], total_wt = 0 , total_tat = 0 , total_rt = 0;  
    Metrics fcfs_metrics_calculated  ;

    
    int temp_n = n ; 
    int total_time = 0;
    wt[0] = 0 ;       // first proccess, has a waiting time of 0.   
    int is_completed[n] ; 

    for (int i = 0; i < n; i++){
        is_completed[i] = 0 ; 
    }
    
    printf(" SJF Gantt Chart:\n");
    while(temp_n != 0){
        int min_burst = 1e9;
        int temp_index = -1;

        
        for (int i = 0; i < n; i++){
            if(proc[i].arrivalTime <= total_time && proc[i].burstTime < min_burst && !is_completed[i]){
                temp_index = i ; 
                min_burst = proc[i].burstTime ; 
            }
        }

        if(temp_index != - 1){    // process with minimum burst time and proper arrival time is executing
            temp_n-- ; 
            proc[temp_index].startTime = total_time ; 
            proc[temp_index].completionTime = proc[temp_index].startTime + proc[temp_index].burstTime ; 
            total_time += proc[temp_index].burstTime ; 
            is_completed[temp_index] = 1 ; 

            printf("| P%d (%d-%d) ", proc[temp_index].pid, proc[temp_index].startTime, proc[temp_index].completionTime);
            

            wt[temp_index] = proc[temp_index].startTime - proc[temp_index].arrivalTime; 
            total_wt += wt[temp_index] ;
            tat[temp_index] = proc[temp_index].completionTime - proc[temp_index].arrivalTime ; 
            total_tat += tat[temp_index] ;
            rt[temp_index] = proc[temp_index].startTime - proc[temp_index].arrivalTime ; 
            total_rt += rt[temp_index] ;
        }
        else{   // no process has arrived, idle state
            total_time++ ; 
        }

    } 

    printf("|\n");
    printf("\n");


    fcfs_metrics_calculated.avgWaiting = (float) total_wt/n ; 
    fcfs_metrics_calculated.avgTurnaround = (float) total_tat/n ; 
    fcfs_metrics_calculated.avgResponse = (float) total_rt/n ; 

    return fcfs_metrics_calculated; 
}


// Round Robin Scheduling (Revised)
Metrics rr_metrics(Process proc[], int n, int timeQuantum) {
    int queue[n];
    int front = 0, rear = 0;
    int visited[n];
    for (int i = 0; i < n; i++){
        visited[i] = 0 ; 
    }
    
    
    int total_wt = 0, total_tat = 0, total_rt = 0;
    int completed = 0, time = 0, tmp_time_slice = 0 ;
    Metrics fcfs_metrics_calculated  ;

    for (int i = 0; i < n; i++) {
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].startTime = -1;    // nothing has been started
    }

        for (int i = 0; i < n; i++) {
        if (proc[i].arrivalTime <= time && !visited[i]) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    if (rear == 0) {   // shift the time if there was no process 
        time = proc[0].arrivalTime;
        tmp_time_slice = time ; 
        queue[rear++] = 0;
        visited[0] = 1;
    }

    printf(" RR Gantt Chart:\n");
    while (completed < n) {
        if (front == rear) { // queue is empty, shift the time
            time++;
            tmp_time_slice++ ; 
            for (int i = 0; i < n; i++) {
                if (proc[i].arrivalTime <= time && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (proc[idx].startTime == -1)
            proc[idx].startTime = time;

        int execTime = (proc[idx].remainingTime > timeQuantum) ? timeQuantum : proc[idx].remainingTime;
        proc[idx].remainingTime -= execTime;
        time += execTime;
        

        for (int i = 0; i < n; i++) {   // new processes added during execution
            if (proc[i].arrivalTime <= time && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }


        if (proc[idx].remainingTime > 0) {
            queue[rear++] = idx; 
            printf("| P%d (%d-%d) ", proc[idx].pid, tmp_time_slice, time);
            tmp_time_slice = time ; 
        } 
        else {
            proc[idx].completionTime = time;
            printf("| P%d (%d-%d) ", proc[idx].pid, tmp_time_slice, proc[idx].completionTime);
            tmp_time_slice = time ; 
            int tat = proc[idx].completionTime - proc[idx].arrivalTime;
            int wt = tat - proc[idx].burstTime;
            int rt = proc[idx].startTime - proc[idx].arrivalTime;

            total_tat += tat;
            total_wt += wt;
            total_rt += rt;

            completed++;
        }
    }

    printf("|\n");
    printf("\n");

    fcfs_metrics_calculated.avgWaiting = (float) total_wt/n ; 
    fcfs_metrics_calculated.avgTurnaround = (float) total_tat/n ; 
    fcfs_metrics_calculated.avgResponse = (float) total_rt/n ; 

    return fcfs_metrics_calculated;

    }