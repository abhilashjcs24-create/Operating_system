#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct {
    int pid;
    int burst;
    int period;
    int remaining;
} Process;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int find_lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (a * b) / gcd(a, b);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process p[n];
    int burst_times[n], periods[n];

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) scanf("%d", &burst_times[i]);

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) scanf("%d", &periods[i]);

    int lcm_val = periods[0];
    double utilization = 0;

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].burst = burst_times[i];
        p[i].period = periods[i];
        p[i].remaining = 0;
        if (i > 0) lcm_val = find_lcm(lcm_val, periods[i]);
        utilization += (double)p[i].burst / p[i].period;
    }

    printf("LCM=%d\n\n", lcm_val);
    printf("Rate Monotone Scheduling:\nPID\tBurst\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", p[i].pid, p[i].burst, p[i].period);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].period > p[j + 1].period) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    double bound = n * (pow(2.0, 1.0 / n) - 1);
    printf("\n%f <= %f =>%s\n", utilization, bound, (utilization <= bound) ? "true" : "false");
    printf("Scheduling occurs for %d ms\n\n", lcm_val);

    int last_pid = -1;

    for (int t = 0; t < lcm_val; t++) {
        int current_pid_idx = -1;

        for (int i = 0; i < n; i++) {
            if (t % p[i].period == 0) {
                p[i].remaining = p[i].burst;
            }
            if (current_pid_idx == -1 && p[i].remaining > 0) {
                current_pid_idx = i;
            }
        }

        if (current_pid_idx != -1) {
            if (p[current_pid_idx].pid != last_pid) {
                printf("%dms onwards: Process %d running\n", t, p[current_pid_idx].pid);
                last_pid = p[current_pid_idx].pid;
            }
            p[current_pid_idx].remaining--;
        } else {
            if (last_pid != 0) { 
                printf("%dms onwards: CPU is idle\n", t);
                last_pid = 0;
            }
        }
    }

    return 0;
}
