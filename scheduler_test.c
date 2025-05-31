#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "scheduler.h"

#define TOLERANCE 0.1

// Helper function to compare floats within a tolerance.
int floatEquals(float a, float b, float tol) {
    return fabs(a - b) <= tol;
}

// Runs a single test case.
void run_test_case(const char *testName, Process procs[], int n, int quantum,
                   Metrics expectedFcfs, Metrics expectedSjf, Metrics expectedRr) {
    printf("==== %s ====\n", testName);

    Metrics mFcfs = fcfs_metrics(procs, n);
    Metrics mSjf  = sjf_metrics(procs, n);
    Metrics mRr   = rr_metrics(procs, n, quantum);

    // FCFS Results
    printf("FCFS: Calculated: Turnaround: %.2f, Waiting: %.2f, Response: %.2f\n",
           mFcfs.avgTurnaround, mFcfs.avgWaiting, mFcfs.avgResponse);
    printf("      Expected:   Turnaround: %.2f, Waiting: %.2f, Response: %.2f\n",
           expectedFcfs.avgTurnaround, expectedFcfs.avgWaiting, expectedFcfs.avgResponse);
    assert(floatEquals(mFcfs.avgTurnaround, expectedFcfs.avgTurnaround, TOLERANCE));
    assert(floatEquals(mFcfs.avgWaiting, expectedFcfs.avgWaiting, TOLERANCE));
    assert(floatEquals(mFcfs.avgResponse, expectedFcfs.avgResponse, TOLERANCE));

    // SJF Results
    printf("SJF:  Calculated: Turnaround: %.2f, Waiting: %.2f, Response: %.2f\n",
           mSjf.avgTurnaround, mSjf.avgWaiting, mSjf.avgResponse);
    printf("      Expected:   Turnaround: %.2f, Waiting: %.2f, Response: %.2f\n",
           expectedSjf.avgTurnaround, expectedSjf.avgWaiting, expectedSjf.avgResponse);
    assert(floatEquals(mSjf.avgTurnaround, expectedSjf.avgTurnaround, TOLERANCE));
    assert(floatEquals(mSjf.avgWaiting, expectedSjf.avgWaiting, TOLERANCE));
    assert(floatEquals(mSjf.avgResponse, expectedSjf.avgResponse, TOLERANCE));

    // RR Results
    printf("RR (Quantum = %d): Calculated: Turnaround: %.2f, Waiting: %.2f, Response: %.2f\n",
           quantum, mRr.avgTurnaround, mRr.avgWaiting, mRr.avgResponse);
    printf("         Expected:   Turnaround: %.2f, Waiting: %.2f, Response: %.2f\n",
           expectedRr.avgTurnaround, expectedRr.avgWaiting, expectedRr.avgResponse);
    assert(floatEquals(mRr.avgTurnaround, expectedRr.avgTurnaround, TOLERANCE));
    assert(floatEquals(mRr.avgWaiting, expectedRr.avgWaiting, TOLERANCE));
    assert(floatEquals(mRr.avgResponse, expectedRr.avgResponse, TOLERANCE));

    printf(">>> %s PASSED.\n\n", testName);
}

int main(void) {
    // --- Test Case 1 ---
    // Three processes:
    //   P1: arrival = 0, burst = 10
    //   P2: arrival = 1, burst = 5
    //   P3: arrival = 2, burst = 8
    Process test1[3] = {
            {1, 0, 10, 0, 0, 0},
            {2, 1,  5, 0, 0, 0},
            {3, 2,  8, 0, 0, 0}
    };
    int n1 = 3;
    int quantum1 = 4;
    // Expected values (manual/simulation):
    // FCFS & SJF: Turnaround ≈ 15.0, Waiting ≈ 7.33, Response ≈ 7.33.
    // RR: Turnaround ≈ 19.33, Waiting ≈ 11.67, Response ≈ 3.0.
    Metrics expectedFcfs1 = {15.0, 7.33, 7.33};
    Metrics expectedSjf1  = expectedFcfs1;
    Metrics expectedRr1   = {19.33, 11.67, 3.0};
    run_test_case("Test Case 1", test1, n1, quantum1, expectedFcfs1, expectedSjf1, expectedRr1);

    // --- Test Case 2 ---
    // Processes with idle CPU time:
    //   P1: arrival = 2, burst = 6
    //   P2: arrival = 5, burst = 2
    //   P3: arrival = 8, burst = 4
    Process test2[3] = {
            {1, 2, 6, 0, 0, 0},
            {2, 5, 2, 0, 0, 0},
            {3, 8, 4, 0, 0, 0}
    };
    int n2 = 3;
    int quantum2 = 2;
    // Expected values:
    // FCFS & SJF: Turnaround ≈ 5.67, Waiting ≈ 1.67, Response ≈ 1.67.
    // RR: Turnaround ≈ 5.67, Waiting ≈ 1.67, Response ≈ 1.0.
    Metrics expectedFcfs2 = {5.67, 1.67, 1.67};
    Metrics expectedSjf2  = expectedFcfs2;
    Metrics expectedRr2   = {5.67, 1.67, 1.0};
    run_test_case("Test Case 2", test2, n2, quantum2, expectedFcfs2, expectedSjf2, expectedRr2);

    // --- Test Case 3 ---
    // Four processes:
    //   P1: arrival = 0, burst = 4
    //   P2: arrival = 1, burst = 3
    //   P3: arrival = 2, burst = 1
    //   P4: arrival = 3, burst = 2
    Process test3[4] = {
            {1, 0, 4, 0, 0, 0},
            {2, 1, 3, 0, 0, 0},
            {3, 2, 1, 0, 0, 0},
            {4, 3, 2, 0, 0, 0}
    };
    int n3 = 4;
    int quantum3 = 2;
    // Expected values:
    // FCFS: Turnaround ≈ 5.75, Waiting ≈ 3.25, Response ≈ 3.25.
    // SJF: Turnaround ≈ 5.0, Waiting ≈ 2.5, Response ≈ 2.5.
    // RR: Turnaround ≈ 6.25, Waiting ≈ 3.75, Response ≈ 1.75.
    Metrics expectedFcfs3 = {5.75, 3.25, 3.25};
    Metrics expectedSjf3  = {5.0, 2.5, 2.5};
    Metrics expectedRr3   = {6.25, 3.75, 1.75};
    run_test_case("Test Case 3", test3, n3, quantum3, expectedFcfs3, expectedSjf3, expectedRr3);

    // --- Test Case 4 ---
    // Five processes with overlapping arrivals:
    //   P1: arrival = 0, burst = 3
    //   P2: arrival = 2, burst = 6
    //   P3: arrival = 4, burst = 4
    //   P4: arrival = 6, burst = 5
    //   P5: arrival = 8, burst = 2
    Process test4[5] = {
            {1, 0, 3, 0, 0, 0},
            {2, 2, 6, 0, 0, 0},
            {3, 4, 4, 0, 0, 0},
            {4, 6, 5, 0, 0, 0},
            {5, 8, 2, 0, 0, 0}
    };
    int n4 = 5;
    int quantum4 = 3;
    // Expected values (hypothetical/simulation):
    // FCFS: {8.60, 4.60, 4.60}
    // SJF:  {7.60, 3.60, 3.60}
    // RR:   {10.6, 6.6, 2.6}
    Metrics expectedFcfs4 = {8.60, 4.60, 4.60};
    Metrics expectedSjf4  = {7.60, 3.60, 3.60};
    Metrics expectedRr4   = {10.6, 6.6, 2.6};
    run_test_case("Test Case 4", test4, n4, quantum4, expectedFcfs4, expectedSjf4, expectedRr4);

    // --- Test Case 5: Single Process (Edge Case) ---
    // Only one process is present.
    Process test5[1] = {
            {1, 0, 5, 0, 0, 0}
    };
    int n5 = 1;
    int quantum5 = 2;  // Quantum can be arbitrary since there is only one process.
    // Expected: turnaround = 5, waiting = 0, response = 0 for all algorithms.
    Metrics expectedFcfs5 = {5.0, 0.0, 0.0};
    Metrics expectedSjf5  = expectedFcfs5;
    Metrics expectedRr5   = expectedFcfs5;
    run_test_case("Test Case 5 (Single Process)", test5, n5, quantum5, expectedFcfs5, expectedSjf5, expectedRr5);

    // --- Test Case 6: Two Processes with Same Arrival Time ---
    // Two processes arriving at the same time.
    Process test6[2] = {
            {1, 0, 4, 0, 0, 0},
            {2, 0, 6, 0, 0, 0}
    };
    int n6 = 2;
    int quantum6 = 3;
    // FCFS/SJF:
    // P1: start=0, finish=4, turnaround=4, waiting=0.
    // P2: start=4, finish=10, turnaround=10, waiting=4.
    // Averages: turnaround = 7.0, waiting = 2.0, response = same as waiting = 2.0.
    // RR (quantum=3) simulation (approximate):
    // P1: first runs 3 (remaining 1), then finishes; P2: first runs 3 (remaining 3), then finishes.
    // Expected approximate: turnaround ≈ 8.5, waiting ≈ 3.5, response ≈ 1.5.
    Metrics expectedFcfs6 = {7.0, 2.0, 2.0};
    Metrics expectedSjf6  = expectedFcfs6;
    Metrics expectedRr6   = {8.5, 3.5, 1.5};
    run_test_case("Test Case 6 (Two Processes, Same Arrival)", test6, n6, quantum6, expectedFcfs6, expectedSjf6, expectedRr6);

    // --- Test Case 7: Multiple Processes with Varying Arrival Times ---
    // Four processes with varied arrival times.
    Process test7[4] = {
            {1, 0, 8, 0, 0, 0},
            {2, 1, 4, 0, 0, 0},
            {3, 2, 9, 0, 0, 0},
            {4, 3, 5, 0, 0, 0}
    };
    int n7 = 4;
    int quantum7 = 3;
    // Expected (approximate):
    // FCFS: Turnaround ≈ 15.25, Waiting ≈ 8.75, Response ≈ 8.75.
    // SJF:  Turnaround ≈ 14.25, Waiting ≈ 7.75, Response ≈ 7.75.
    // RR:   Turnaround ≈ 20.0, Waiting ≈ 13.5, Response ≈ 3.0.
    Metrics expectedFcfs7 = {15.25, 8.75, 8.75};
    Metrics expectedSjf7  = {14.25, 7.75, 7.75};
    Metrics expectedRr7   = {20.0, 13.5, 3.0};
    run_test_case("Test Case 7 (Varying Arrivals)", test7, n7, quantum7, expectedFcfs7, expectedSjf7, expectedRr7);

    // --- Test Case 8: Six Processes with Random Arrivals ---
    Process test8[6] = {
            {1, 0, 10, 0, 0, 0},
            {2, 2, 3,  0, 0, 0},
            {3, 4, 7,  0, 0, 0},
            {4, 6, 5,  0, 0, 0},
            {5, 7, 2,  0, 0, 0},
            {6, 9, 8,  0, 0, 0}
    };
    int n8 = 6;
    int quantum8 = 4;
    // Expected values (approximate):
    // FCFS: Turnaround ≈ 17.0, Waiting ≈ 11.17, Response ≈ 11.17.
    // SJF:  Turnaround ≈ 15.17, Waiting ≈ 9.33,  Response ≈ 9.33.
    // RR:   Turnaround ≈ 20.67, Waiting ≈ 14.83, Response ≈ 6.33.
    Metrics expectedFcfs8 = {17.0, 11.17, 11.17};
    Metrics expectedSjf8  = {15.17, 9.33, 9.33};
    Metrics expectedRr8   = {20.67, 14.83, 6.33};
    run_test_case("Test Case 8 (Six Processes)", test8, n8, quantum8, expectedFcfs8, expectedSjf8, expectedRr8);

    printf("ALL TESTS PASSED.\n");
    return 0;
}
