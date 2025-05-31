# Process Scheduler Simulation

This project implements and tests three CPU scheduling algorithms: **First-Come-First-Serve (FCFS)**, **Shortest Job First (SJF, non-preemptive)**, and **Round Robin (RR)**. The code simulates process scheduling, calculates performance metrics (average turnaround time, waiting time, and response time), and visualizes the execution order using Gantt charts.

## Project Structure

- **scheduler.h**: Defines the `Process` and `Metrics` structures and function prototypes for the scheduling algorithms.
- **scheduler.c**: Implements the FCFS, SJF, and RR scheduling algorithms, including Gantt chart output and metric calculations.
- **scheduler_test.c**: Contains test cases to validate the scheduling algorithms against expected metrics.
- **Makefile**: Automates compilation and execution of the test program.

## Prerequisites

- **GCC**: A C compiler to build the project.
- **Make**: To use the provided Makefile for compilation and execution.
- **Linux/Unix-like environment** or any system with GCC and Make installed.

## How to Build and Run

1. **Clone or download the project** to your local machine.

2. **Navigate to the project directory**:

   ```bash
   cd /path/to/project
   ```

3. **Compile the project** using the Makefile:

   ```bash
   make
   ```

   This generates the executable `scheduler_test`.

4. **Run the tests**:

   ```bash
   make run
   ```

5. **Clean up** (remove the executable):

   ```bash
   make clean
   ```

## Input

The scheduling algorithms operate on an array of `Process` structures, each containing:

- `pid`: Process ID.
- `arrivalTime`: Time when the process arrives.
- `burstTime`: CPU time required to complete the process.
- `remainingTime`: Used by RR to track remaining execution time.
- `startTime`: Time when the process first starts (for response time).
- `completionTime`: Time when the process finishes.

The `scheduler_test.c` file defines eight test cases with varying numbers of processes, arrival times, burst times, and time quanta for RR. For example:

- **Test Case 1**: Three processes with arrival times 0, 1, 2 and burst times 10, 5, 8, with a quantum of 4 for RR.
- **Test Case 5**: A single process (edge case) with arrival time 0 and burst time 5.

The RR algorithm requires a `timeQuantum` parameter, which varies per test case (e.g., 2, 3, or 4).

## Output

The program outputs:

1. **Gantt Charts**: Visual representations of process execution order for each algorithm, showing process IDs and their start/end times.
   - Format: `| P<process_id> (start-end) | ... |`
   - Example (Test Case 1, FCFS): `| P1 (0-10) | P2 (10-15) | P3 (15-23) |`
2. **Metrics**: For each algorithm (FCFS, SJF, RR), the program calculates:
   - **Average Turnaround Time**: Time from arrival to completion.
   - **Average Waiting Time**: Time spent waiting in the ready queue.
   - **Average Response Time**: Time from arrival to first execution.
   - Example (Test Case 1, FCFS): `Turnaround: 15.00, Waiting: 7.33, Response: 7.33`
3. **Test Results**: Compares calculated metrics against expected values with a tolerance of 0.1. Each test case prints "PASSED" if all metrics match.

### Sample Output (Test Case 1)

```
==== Test Case 1 ====
 FCFS Gantt Chart:
| P1 (0-10) | P2 (10-15) | P3 (15-23) |

 SJF Gantt Chart:
| P1 (0-10) | P2 (10-15) | P3 (15-23) |

 RR Gantt Chart:
| P1 (0-4) | P2 (4-8) | P3 (8-12) | P1 (12-16) | P2 (16-17) | P3 (17-21) | P1 (21-23) |

FCFS: Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33
      Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33
SJF:  Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33
      Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33
RR (Quantum = 4): Calculated: Turnaround: 19.33, Waiting: 11.67, Response: 3.00
         Expected:   Turnaround: 19.33, Waiting: 11.67, Response: 3.00
>>> Test Case 1 PASSED.
```

## Notes

- **FCFS**: Processes are executed in the order of their arrival times. It’s simple but may lead to longer waiting times for short processes.
- **SJF (Non-preemptive)**: Selects the process with the shortest burst time among those that have arrived, minimizing waiting time but requiring knowledge of burst times.
- **RR**: Each process gets a fixed time slice (quantum). It ensures fairness and lower response times but may increase turnaround time due to context switching.
- The test cases cover various scenarios, including single processes, simultaneous arrivals, and idle CPU periods.
- The program assumes valid input (non-negative arrival and burst times, positive quantum).

## Limitations

- The SJF implementation is non-preemptive, meaning a running process cannot be interrupted.
- The program does not handle dynamic process input outside the test cases.
- Metrics are compared with a fixed tolerance (0.1) to account for floating-point inaccuracies.

## Extending the Project

To extend this project, you could:

- Add preemptive SJF or Priority Scheduling algorithms.
- Support dynamic process input via a file or user interface.
- Visualize Gantt charts graphically using a library like SDL or a plotting tool.
- Add error handling for invalid inputs (e.g., negative burst times).
