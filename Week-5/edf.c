#include <stdio.h>

typedef struct {
    int pid;
    int burst;
    int deadline; 
    int period;   
    int remaining;
    int absolute_deadline;
} Task;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int find_lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (a * b) / gcd(a, b);
}

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task t[n];
    int hyperperiod = 1;

    for (int i = 0; i < n; i++) {
        printf("Enter PID, Burst, Deadline, Period for task %d: ", i + 1);
        scanf("%d %d %d %d", &t[i].pid, &t[i].burst, &t[i].deadline, &t[i].period);
        t[i].remaining = 0;
        t[i].absolute_deadline = 0;
        hyperperiod = find_lcm(hyperperiod, t[i].period);
    }

    printf("\nPID\tBurst\tDeadline\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\n", t[i].pid, t[i].burst, t[i].deadline, t[i].period);
    }

    printf("Scheduling occurs for %d ms\n\n", hyperperiod);

    for (int time = 0; time < hyperperiod; time++) {

        for (int i = 0; i < n; i++) {
            if (time % t[i].period == 0) {
                t[i].remaining = t[i].burst;
                t[i].absolute_deadline = time + t[i].deadline;
            }
        }

        int selected = -1;
        int min_deadline = 99999;

        for (int i = 0; i < n; i++) {
            if (t[i].remaining > 0) {
                if (t[i].absolute_deadline < min_deadline) {
                    min_deadline = t[i].absolute_deadline;
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            printf("%dms : Task %d is running.\n", time, t[selected].pid);
            t[selected].remaining--;
        } else {
            printf("%dms : CPU is idle.\n", time);
        }
    }

    return 0;
}