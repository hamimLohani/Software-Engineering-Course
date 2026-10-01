#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int id;
    int arrival;
    int burst;
    int priority;
    int deadline;

    int completion;
    int turnaround;
    int waiting;
    int response;

    int remaining;
} Process;

typedef struct {
    int *data;
    int size;
    int capacity;
} GanttChart;

void gantt_init(GanttChart *g) {
    g->size = 0;
    g->capacity = 64;
    g->data = (int *)malloc(g->capacity * sizeof(int));
}

void gantt_push(GanttChart *g, int val) {
    if (g->size >= g->capacity) {
        g->capacity *= 2;
        g->data = (int *)realloc(g->data, g->capacity * sizeof(int));
    }
    g->data[g->size++] = val;
}

void gantt_free(GanttChart *g) {
    if (g->data) {
        free(g->data);
        g->data = NULL;
    }
    g->size = 0;
    g->capacity = 0;
}

typedef struct {
    Process *processes;
    int n;
    GanttChart gantt;
    double avgWaiting;
    double avgTurnaround;
} Result;

void freeResult(Result *res) {
    if (res->processes) {
        free(res->processes);
        res->processes = NULL;
    }
    gantt_free(&res->gantt);
}

void calculateMetrics(Process *p, int n) {

    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }
}

void printResult(const char *name, const Result *result) {
    printf("\n\n========================================\n");
    printf("%s\n", name);
    printf("========================================\n");

    printf("\nGantt Chart:\n0 ");
    if (result->gantt.size > 0) {
        int currentId = result->gantt.data[0];
        for (int i = 1; i < result->gantt.size; i++) {
            if (result->gantt.data[i] != currentId) {
                if (currentId == -1) printf("| IDLE | %d ", i);
                else printf("| P%d | %d ", currentId, i);
                currentId = result->gantt.data[i];
            }
        }
        if (currentId == -1) printf("| IDLE | %d\n", result->gantt.size);
        else printf("| P%d | %d\n", currentId, result->gantt.size);
    } else {
        printf("\n");
    }

    printf("\nProcess\tAT\tBT\tPriority\tDeadline\tCT\tTAT\tWT\tRT\n");

    double totalWT = 0;
    double totalTAT = 0;
    for (int i = 0; i < result->n; i++) {
        const Process *p = &result->processes[i];
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\t%d\t%d\n",
               p->id, p->arrival, p->burst, p->priority, p->deadline,
               p->completion, p->turnaround, p->waiting, p->response);
        totalWT += p->waiting;
        totalTAT += p->turnaround;
    }

    printf("\nAverage Waiting Time    = %.2f\n", totalWT / result->n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / result->n);
}

int compare_arrival(const void *a, const void *b) {
    const Process *p1 = (const Process *)a;
    const Process *p2 = (const Process *)b;
    if (p1->arrival != p2->arrival) return p1->arrival - p2->arrival;
    return p1->id - p2->id;
}

int compare_id(const void *a, const void *b) {
    const Process *p1 = (const Process *)a;
    const Process *p2 = (const Process *)b;
    return p1->id - p2->id;
}

Result FCFS(const Process *input, int n) {
    Process *p = (Process *)malloc(n * sizeof(Process));
    memcpy(p, input, n * sizeof(Process));
    qsort(p, n, sizeof(Process), compare_arrival);

    int time = 0;
    GanttChart gantt;
    gantt_init(&gantt);

    for (int i = 0; i < n; i++) {
        while (time < p[i].arrival) {
            gantt_push(&gantt, -1);
            time++;
        }
        p[i].response = time - p[i].arrival;
        for (int j = 0; j < p[i].burst; j++) {
            gantt_push(&gantt, p[i].id);
            time++;
        }
        p[i].completion = time;
    }

    calculateMetrics(p, n);
    qsort(p, n, sizeof(Process), compare_id);

    Result res;
    res.processes = p;
    res.n = n;
    res.gantt = gantt;
    res.avgWaiting = 0;
    res.avgTurnaround = 0;
    return res;
}

Result SJF(const Process *input, int n) {
    Process *p = (Process *)malloc(n * sizeof(Process));
    memcpy(p, input, n * sizeof(Process));
    int completed = 0;
    int time = 0;
    bool *done = (bool *)calloc(n, sizeof(bool));
    GanttChart gantt;
    gantt_init(&gantt);

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time) {
                if (selected == -1 || 
                    p[i].burst < p[selected].burst ||
                    (p[i].burst == p[selected].burst && p[i].arrival < p[selected].arrival) ||
                    (p[i].burst == p[selected].burst && p[i].arrival == p[selected].arrival && p[i].id < p[selected].id)) {
                    selected = i;
                }
            }
        }
        
        if (selected == -1) {
            gantt_push(&gantt, -1);
            time++;
            continue;
        }

        p[selected].response = time - p[selected].arrival;
        for (int i = 0; i < p[selected].burst; i++) {
            gantt_push(&gantt, p[selected].id);
            time++;
        }
        p[selected].completion = time;
        done[selected] = true;
        completed++;
    }

    free(done);
    calculateMetrics(p, n);

    Result res;
    res.processes = p;
    res.n = n;
    res.gantt = gantt;
    res.avgWaiting = 0;
    res.avgTurnaround = 0;
    return res;
}

Result SRTF(const Process *input, int n) {
    Process *p = (Process *)malloc(n * sizeof(Process));
    memcpy(p, input, n * sizeof(Process));
    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;
    
    int completed = 0;
    int time = 0;
    GanttChart gantt;
    gantt_init(&gantt);

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (selected == -1 || 
                    p[i].remaining < p[selected].remaining ||
                    (p[i].remaining == p[selected].remaining && p[i].arrival < p[selected].arrival) ||
                    (p[i].remaining == p[selected].remaining && p[i].arrival == p[selected].arrival && p[i].id < p[selected].id)) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            gantt_push(&gantt, -1);
            time++;
            continue;
        }

        if (p[selected].response == -1) {
            p[selected].response = time - p[selected].arrival;
        }

        gantt_push(&gantt, p[selected].id);
        p[selected].remaining--;
        time++;

        if (p[selected].remaining == 0) {
            p[selected].completion = time;
            completed++;
        }
    }

    calculateMetrics(p, n);

    Result res;
    res.processes = p;
    res.n = n;
    res.gantt = gantt;
    res.avgWaiting = 0;
    res.avgTurnaround = 0;
    return res;
}

Result PriorityNP(const Process *input, int n) {
    Process *p = (Process *)malloc(n * sizeof(Process));
    memcpy(p, input, n * sizeof(Process));
    int completed = 0;
    int time = 0;
    bool *done = (bool *)calloc(n, sizeof(bool));
    GanttChart gantt;
    gantt_init(&gantt);

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time) {
                if (selected == -1 || 
                    p[i].priority < p[selected].priority ||
                    (p[i].priority == p[selected].priority && p[i].arrival < p[selected].arrival) ||
                    (p[i].priority == p[selected].priority && p[i].arrival == p[selected].arrival && p[i].id < p[selected].id)) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            gantt_push(&gantt, -1);
            time++;
            continue;
        }

        p[selected].response = time - p[selected].arrival;
        for (int i = 0; i < p[selected].burst; i++) {
            gantt_push(&gantt, p[selected].id);
            time++;
        }
        p[selected].completion = time;
        done[selected] = true;
        completed++;
    }

    free(done);
    calculateMetrics(p, n);

    Result res;
    res.processes = p;
    res.n = n;
    res.gantt = gantt;
    res.avgWaiting = 0;
    res.avgTurnaround = 0;
    return res;
}

Result PriorityP(const Process *input, int n) {
    Process *p = (Process *)malloc(n * sizeof(Process));
    memcpy(p, input, n * sizeof(Process));
    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;

    int completed = 0;
    int time = 0;
    GanttChart gantt;
    gantt_init(&gantt);

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (selected == -1 || 
                    p[i].priority < p[selected].priority ||
                    (p[i].priority == p[selected].priority && p[i].arrival < p[selected].arrival) ||
                    (p[i].priority == p[selected].priority && p[i].arrival == p[selected].arrival && p[i].id < p[selected].id)) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            gantt_push(&gantt, -1);
            time++;
            continue;
        }

        if (p[selected].response == -1) {
            p[selected].response = time - p[selected].arrival;
        }

        gantt_push(&gantt, p[selected].id);
        p[selected].remaining--;
        time++;

        if (p[selected].remaining == 0) {
            p[selected].completion = time;
            completed++;
        }
    }

    calculateMetrics(p, n);

    Result res;
    res.processes = p;
    res.n = n;
    res.gantt = gantt;
    res.avgWaiting = 0;
    res.avgTurnaround = 0;
    return res;
}

/* Dynamic circular queue for RoundRobin */
typedef struct {
    int *data;
    int front;
    int rear;
    int capacity;
    int count;
} Queue;

void queue_init(Queue *q, int cap) {
    q->capacity = cap;
    q->data = (int *)malloc(cap * sizeof(int));
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

void queue_push(Queue *q, int val) {
    if (q->count == q->capacity) {
        int new_cap = q->capacity * 2;
        int *new_data = (int *)malloc(new_cap * sizeof(int));
        for (int i = 0; i < q->count; i++) {
            new_data[i] = q->data[(q->front + i) % q->capacity];
        }
        free(q->data);
        q->data = new_data;
        q->front = 0;
        q->rear = q->count;
        q->capacity = new_cap;
    }
    q->data[q->rear] = val;
    q->rear = (q->rear + 1) % q->capacity;
    q->count++;
}

int queue_pop(Queue *q) {
    if (q->count == 0) return -1;
    int val = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->count--;
    return val;
}

bool queue_is_empty(const Queue *q) {
    return q->count == 0;
}

void queue_free(Queue *q) {
    if (q->data) {
        free(q->data);
        q->data = NULL;
    }
}

Result RoundRobin(const Process *input, int n, int quantum) {
    Process *p = (Process *)malloc(n * sizeof(Process));
    memcpy(p, input, n * sizeof(Process));
    qsort(p, n, sizeof(Process), compare_arrival);

    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;

    GanttChart gantt;
    gantt_init(&gantt);

    Queue ready;
    queue_init(&ready, n > 0 ? n : 4);

    bool *added = (bool *)calloc(n, sizeof(bool));

    int time = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (!added[i] && p[i].arrival <= time) {
                queue_push(&ready, i);
                added[i] = true;
            }
        }

        if (queue_is_empty(&ready)) {
            gantt_push(&gantt, -1);
            time++;
            continue;
        }

        int current = queue_pop(&ready);

        if (p[current].response == -1) {
            p[current].response = time - p[current].arrival;
        }

        int execution = quantum < p[current].remaining ? quantum : p[current].remaining;
        for (int i = 0; i < execution; i++) {
            gantt_push(&gantt, p[current].id);
            p[current].remaining--;
            time++;
            
            for (int j = 0; j < n; j++) {
                if (!added[j] && p[j].arrival <= time) {
                    queue_push(&ready, j);
                    added[j] = true;
                }
            }
            if (p[current].remaining == 0) break;
        }

        if (p[current].remaining == 0) {
            p[current].completion = time;
            completed++;
        } else {
            queue_push(&ready, current);
        }
    }

    free(added);
    queue_free(&ready);

    calculateMetrics(p, n);
    qsort(p, n, sizeof(Process), compare_id);

    Result res;
    res.processes = p;
    res.n = n;
    res.gantt = gantt;
    res.avgWaiting = 0;
    res.avgTurnaround = 0;
    return res;
}

Result EDF_NP(const Process *input, int n) {
    Process *p = (Process *)malloc(n * sizeof(Process));
    memcpy(p, input, n * sizeof(Process));
    int completed = 0;
    int time = 0;
    bool *done = (bool *)calloc(n, sizeof(bool));
    GanttChart gantt;
    gantt_init(&gantt);

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time) {
                if (selected == -1 || 
                    p[i].deadline < p[selected].deadline ||
                    (p[i].deadline == p[selected].deadline && p[i].arrival < p[selected].arrival) ||
                    (p[i].deadline == p[selected].deadline && p[i].arrival == p[selected].arrival && p[i].id < p[selected].id)) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            gantt_push(&gantt, -1);
            time++;
            continue;
        }

        p[selected].response = time - p[selected].arrival;
        for (int i = 0; i < p[selected].burst; i++) {
            gantt_push(&gantt, p[selected].id);
            time++;
        }
        p[selected].completion = time;
        done[selected] = true;
        completed++;
    }

    free(done);
    calculateMetrics(p, n);

    Result res;
    res.processes = p;
    res.n = n;
    res.gantt = gantt;
    res.avgWaiting = 0;
    res.avgTurnaround = 0;
    return res;
}

Result EDF_P(const Process *input, int n) {
    Process *p = (Process *)malloc(n * sizeof(Process));
    memcpy(p, input, n * sizeof(Process));
    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;

    int completed = 0;
    int time = 0;
    GanttChart gantt;
    gantt_init(&gantt);

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (selected == -1 || 
                    p[i].deadline < p[selected].deadline ||
                    (p[i].deadline == p[selected].deadline && p[i].arrival < p[selected].arrival) ||
                    (p[i].deadline == p[selected].deadline && p[i].arrival == p[selected].arrival && p[i].id < p[selected].id)) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            gantt_push(&gantt, -1);
            time++;
            continue;
        }

        if (p[selected].response == -1) {
            p[selected].response = time - p[selected].arrival;
        }

        gantt_push(&gantt, p[selected].id);
        p[selected].remaining--;
        time++;

        if (p[selected].remaining == 0) {
            p[selected].completion = time;
            completed++;
        }
    }

    calculateMetrics(p, n);

    Result res;
    res.processes = p;
    res.n = n;
    res.gantt = gantt;
    res.avgWaiting = 0;
    res.avgTurnaround = 0;
    return res;
}

Result RMS_NP(const Process *input, int n) {
    Process *p = (Process *)malloc(n * sizeof(Process));
    memcpy(p, input, n * sizeof(Process));
    int completed = 0;
    int time = 0;
    bool *done = (bool *)calloc(n, sizeof(bool));
    GanttChart gantt;
    gantt_init(&gantt);

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time) {
                if (selected == -1) {
                    selected = i;
                } else {
                    int period_i = p[i].deadline - p[i].arrival;
                    int period_selected = p[selected].deadline - p[selected].arrival;
                    if (period_i < period_selected ||
                        (period_i == period_selected && p[i].arrival < p[selected].arrival) ||
                        (period_i == period_selected && p[i].arrival == p[selected].arrival && p[i].id < p[selected].id)) {
                        selected = i;
                    }
                }
            }
        }

        if (selected == -1) {
            gantt_push(&gantt, -1);
            time++;
            continue;
        }

        p[selected].response = time - p[selected].arrival;
        for (int i = 0; i < p[selected].burst; i++) {
            gantt_push(&gantt, p[selected].id);
            time++;
        }
        p[selected].completion = time;
        done[selected] = true;
        completed++;
    }

    free(done);
    calculateMetrics(p, n);

    Result res;
    res.processes = p;
    res.n = n;
    res.gantt = gantt;
    res.avgWaiting = 0;
    res.avgTurnaround = 0;
    return res;
}

Result RMS_P(const Process *input, int n) {
    Process *p = (Process *)malloc(n * sizeof(Process));
    memcpy(p, input, n * sizeof(Process));
    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;

    int completed = 0;
    int time = 0;
    GanttChart gantt;
    gantt_init(&gantt);

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (selected == -1) {
                    selected = i;
                } else {
                    int period_i = p[i].deadline - p[i].arrival;
                    int period_selected = p[selected].deadline - p[selected].arrival;
                    if (period_i < period_selected ||
                        (period_i == period_selected && p[i].arrival < p[selected].arrival) ||
                        (period_i == period_selected && p[i].arrival == p[selected].arrival && p[i].id < p[selected].id)) {
                        selected = i;
                    }
                }
            }
        }

        if (selected == -1) {
            gantt_push(&gantt, -1);
            time++;
            continue;
        }

        if (p[selected].response == -1) {
            p[selected].response = time - p[selected].arrival;
        }

        gantt_push(&gantt, p[selected].id);
        p[selected].remaining--;
        time++;

        if (p[selected].remaining == 0) {
            p[selected].completion = time;
            completed++;
        }
    }

    calculateMetrics(p, n);

    Result res;
    res.processes = p;
    res.n = n;
    res.gantt = gantt;
    res.avgWaiting = 0;
    res.avgTurnaround = 0;
    return res;
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }

    int n;
    if (fscanf(file, "%d", &n) != 1) {
        printf("Error reading number of processes\n");
        fclose(file);
        return 1;
    }

    Process *processes = (Process *)malloc(n * sizeof(Process));
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d %d %d %d %d",
               &processes[i].id, 
               &processes[i].arrival, 
               &processes[i].burst, 
               &processes[i].priority, 
               &processes[i].deadline);
        processes[i].completion = 0;
        processes[i].turnaround = 0;
        processes[i].waiting = 0;
        processes[i].response = -1;
        processes[i].remaining = processes[i].burst;
    }
    fclose(file);

    printf("========================================\n");
    printf("      CPU SCHEDULING SIMULATOR\n");
    printf("========================================\n");

    printf("\nInput Processes:\n");
    printf("\nID\tAT\tBT\tPriority\tDeadline\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrival,
               processes[i].burst,
               processes[i].priority,
               processes[i].deadline);
    }
    
    Result fcfs = FCFS(processes, n);
    printResult("FCFS", &fcfs);
    freeResult(&fcfs);

    Result sjf = SJF(processes, n);
    printResult("SJF - Non-Preemptive", &sjf);
    freeResult(&sjf);

    Result srtf = SRTF(processes, n);
    //printResult("SRTF - Preemptive SJF", &srtf);
    freeResult(&srtf);

    Result priorityNP = PriorityNP(processes, n);
    printResult("Priority - Non-Preemptive", &priorityNP);
    freeResult(&priorityNP);

    Result priorityP = PriorityP(processes, n);
    //printResult("Priority - Preemptive", &priorityP);
    freeResult(&priorityP);

    Result rr = RoundRobin(processes, n, 2);
    printResult("Round Robin - Quantum = 2", &rr);
    freeResult(&rr);

    Result edfNP = EDF_NP(processes, n);
    printResult("EDF - Non-Preemptive", &edfNP);
    freeResult(&edfNP);

    Result edfP = EDF_P(processes, n);
    //printResult("EDF - Preemptive", &edfP);
    freeResult(&edfP);

    Result rmsNP = RMS_NP(processes, n);
    printResult("RMS - Non-Preemptive", &rmsNP);
    freeResult(&rmsNP);

    Result rmsP = RMS_P(processes, n);
    //printResult("RMS - Preemptive", &rmsP);
    freeResult(&rmsP);

    free(processes);
    return 0;
}
