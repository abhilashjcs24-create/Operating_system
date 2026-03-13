#include <stdio.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int priority;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
};

int main() {
    int n, choice;
    printf("USN:1BM24CS006\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess P%d\n", p[i].id);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
        printf("Priority: ");
        scanf("%d", &p[i].priority);

        p[i].remaining = p[i].burst;
        p[i].completion = 0;
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }

    printf("\nSelect Priority Rule:\n");
    printf("1. Lower number = Higher priority\n");
    printf("2. Higher number = Higher priority\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int current_time = 0, completed = 0;

    while (completed < n) {
        int best_priority = (choice == 1) ? 9999 : -9999;
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= current_time && p[i].remaining > 0) {
                if ((choice == 1 && p[i].priority < best_priority) ||
                    (choice == 2 && p[i].priority > best_priority)) {
                    best_priority = p[i].priority;
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            current_time++;
        } else {
            p[selected].remaining--;
            current_time++;

            if (p[selected].remaining == 0) {
                p[selected].completion = current_time;
                p[selected].turnaround = p[selected].completion - p[selected].arrival;
                p[selected].waiting = p[selected].turnaround - p[selected].burst;
                completed++;
            }
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id, p[i].arrival, p[i].burst, p[i].priority,
               p[i].completion, p[i].waiting, p[i].turnaround);
    }

    float avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) {
        avgWT += p[i].waiting;
        avgTAT += p[i].turnaround;
    }
    avgWT /= n;
    avgTAT /= n;

    printf("\nAverage Waiting Time: %.2f", avgWT);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT);

    return 0;
}
