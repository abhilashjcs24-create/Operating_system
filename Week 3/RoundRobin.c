#include <stdio.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
};

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess P%d\n", p[i].id);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        p[i].remaining = p[i].burst;
        p[i].completion = 0;
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }

    int current_time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;
    int inQueue[n];
    for (int i = 0; i < n; i++) inQueue[i] = 0;

    while (completed < n) {
        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= current_time && p[i].remaining > 0 && inQueue[i] == 0) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (front == rear) {
            current_time++;
            continue;
        }

        int idx = queue[front++];
        if (p[idx].remaining > tq) {
            p[idx].remaining -= tq;
            current_time += tq;

            // Add newly arrived processes during this time
            for (int i = 0; i < n; i++) {
                if (p[i].arrival <= current_time && p[i].remaining > 0 && inQueue[i] == 0) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }

            queue[rear++] = idx; // put back at end
        } else {
            current_time += p[idx].remaining;
            p[idx].remaining = 0;
            p[idx].completion = current_time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            completed++;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].arrival, p[i].burst,
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
