#include <stdio.h>
#include <string.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    char type[10];
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int executed; 
};

int main() {
    int n, i, current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d:\n", p[i].id);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst_time);
        printf("Type (System/User): ");
        scanf("%s", p[i].type);
        p[i].executed = 0;
    }

    printf("\nExecution Order:\n");

    while (completed < n) {
        int found = 0;

        for (i = 0; i < n; i++) {
            if (strcmp(p[i].type, "System") == 0 && p[i].executed == 0 && p[i].arrival_time <= current_time) {
                current_time += p[i].burst_time;
                p[i].completion_time = current_time;
                p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
                p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                p[i].executed = 1;
                completed++;
                printf("P%d (System) executed at time %d\n", p[i].id, current_time);
                found = 1;

                break; 
            }
        }

        if (!found) {
            for (i = 0; i < n; i++) {
                if (strcmp(p[i].type, "User") == 0 && p[i].executed == 0 && p[i].arrival_time <= current_time) {
                    current_time += p[i].burst_time;
                    p[i].completion_time = current_time;
                    p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                    p[i].executed = 1;
                    completed++;
                    printf("P%d (User) executed at time %d\n", p[i].id, current_time);
                    found = 1;
                    break;
                }
            }
        }

        if (!found) {
            current_time++;
        }
    }

    printf("\nID\tType\tArrival\tBurst\tWait\tTAT\n");
    for (i = 0; i < n; i++) {
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        printf("%d\t%s\t%d\t%d\t%d\t%d\n", p[i].id, p[i].type, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
