#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;

// Structure to represent a Process (All arrival times are assumed 0)
struct Process {
    int id;
    int burst;
    int priority;
    int deadline;

    int completion = 0;
    int turnaround = 0;
    int waiting = 0;
    int response = -1;

    int remaining = 0;
};

struct Result {
    vector<Process> processes;
    vector<int> gantt;
    double avgWaiting;
    double avgTurnaround;
};

// With Arrival Time = 0:
// Turnaround Time (TAT) = Completion Time - Arrival Time = Completion Time
// Waiting Time (WT)     = Turnaround Time - Burst Time
void calculateMetrics(vector<Process>& p) {
    double totalWaiting = 0;
    double totalTurnaround = 0;

    for (auto& x : p) {
        x.turnaround = x.completion;
        x.waiting = x.turnaround - x.burst;
        totalWaiting += x.waiting;
        totalTurnaround += x.turnaround;
    }
}

void printResult(string name, const Result& result) {
    cout << "\n\n========================================\n";
    cout << name << "\n";
    cout << "========================================\n";

    cout << "\nGantt Chart:\n0 ";
    if (!result.gantt.empty()) {
        int currentId = result.gantt[0];
        for (size_t i = 1; i < result.gantt.size(); i++) {
            if (result.gantt[i] != currentId) {
                if (currentId == -1) cout << "| IDLE | " << i << " ";
                else cout << "| P" << currentId << " | " << i << " ";
                currentId = result.gantt[i];
            }
        }
        if (currentId == -1) cout << "| IDLE | " << result.gantt.size() << "\n";
        else cout << "| P" << currentId << " | " << result.gantt.size() << "\n";
    } else {
        cout << "\n";
    }

    cout << "\nProcess\tBT\tPriority\tDeadline\tCT\tTAT\tWT\tRT\n";

    double totalWT = 0;
    double totalTAT = 0;
    for (const auto& p : result.processes) {
        cout << "P" << p.id << "\t"
             << p.burst << "\t"
             << p.priority << "\t\t"
             << p.deadline << "\t\t"
             << p.completion << "\t"
             << p.turnaround << "\t"
             << p.waiting << "\t"
             << p.response << "\n";
        totalWT += p.waiting;
        totalTAT += p.turnaround;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time    = " << totalWT / result.processes.size() << "\n";
    cout << "Average Turnaround Time = " << totalTAT / result.processes.size() << "\n";
}

// 1. First-Come, First-Served (FCFS)
Result FCFS(const vector<Process>& input) {
    vector<Process> p = input;
    // When AT = 0, FCFS executes in order of process ID (or arrival order in input)
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });

    int time = 0;
    vector<int> gantt;

    for (auto& x : p) {
        x.response = time;
        for (int i = 0; i < x.burst; i++) {
            gantt.push_back(x.id);
            time++;
        }
        x.completion = time;
    }

    calculateMetrics(p);
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });
    return {p, gantt, 0, 0};
}

// 2. Shortest Job First (SJF) - Non-Preemptive
Result SJF(const vector<Process>& input) {
    vector<Process> p = input;
    int n = p.size();
    int completed = 0;
    int time = 0;
    vector<bool> done(n, false);
    vector<int> gantt;

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i]) {
                if (selected == -1 || 
                    p[i].burst < p[selected].burst ||
                    (p[i].burst == p[selected].burst && p[i].id < p[selected].id)) {
                    selected = i;
                }
            }
        }

        p[selected].response = time;
        for (int i = 0; i < p[selected].burst; i++) {
            gantt.push_back(p[selected].id);
            time++;
        }
        p[selected].completion = time;
        done[selected] = true;
        completed++;
    }

    calculateMetrics(p);
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });
    return {p, gantt, 0, 0};
}

// 3. Shortest Remaining Time First (SRTF) - Preemptive SJF
// (When all AT = 0, SRTF yields identical execution to SJF because no shorter job arrives later)
Result SRTF(const vector<Process>& input) {
    vector<Process> p = input;
    int n = p.size();
    for (auto& x : p) x.remaining = x.burst;
    
    int completed = 0;
    int time = 0;
    vector<int> gantt;

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                if (selected == -1 || 
                    p[i].remaining < p[selected].remaining ||
                    (p[i].remaining == p[selected].remaining && p[i].id < p[selected].id)) {
                    selected = i;
                }
            }
        }

        if (p[selected].response == -1) {
            p[selected].response = time;
        }

        gantt.push_back(p[selected].id);
        p[selected].remaining--;
        time++;

        if (p[selected].remaining == 0) {
            p[selected].completion = time;
            completed++;
        }
    }

    calculateMetrics(p);
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });
    return {p, gantt, 0, 0};
}

// 4. Priority Scheduling - Non-Preemptive
Result PriorityNP(const vector<Process>& input) {
    vector<Process> p = input;
    int n = p.size();
    int completed = 0;
    int time = 0;
    vector<bool> done(n, false);
    vector<int> gantt;

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i]) {
                if (selected == -1 || 
                    p[i].priority < p[selected].priority ||
                    (p[i].priority == p[selected].priority && p[i].id < p[selected].id)) {
                    selected = i;
                }
            }
        }

        p[selected].response = time;
        for (int i = 0; i < p[selected].burst; i++) {
            gantt.push_back(p[selected].id);
            time++;
        }
        p[selected].completion = time;
        done[selected] = true;
        completed++;
    }

    calculateMetrics(p);
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });
    return {p, gantt, 0, 0};
}

// 5. Priority Scheduling - Preemptive
Result PriorityP(const vector<Process>& input) {
    vector<Process> p = input;
    int n = p.size();
    for (auto& x : p) x.remaining = x.burst;

    int completed = 0;
    int time = 0;
    vector<int> gantt;

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                if (selected == -1 || 
                    p[i].priority < p[selected].priority ||
                    (p[i].priority == p[selected].priority && p[i].id < p[selected].id)) {
                    selected = i;
                }
            }
        }

        if (p[selected].response == -1) {
            p[selected].response = time;
        }

        gantt.push_back(p[selected].id);
        p[selected].remaining--;
        time++;

        if (p[selected].remaining == 0) {
            p[selected].completion = time;
            completed++;
        }
    }

    calculateMetrics(p);
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });
    return {p, gantt, 0, 0};
}

// 6. Round Robin (RR)
Result RoundRobin(const vector<Process>& input, int quantum) {
    vector<Process> p = input;
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });

    int n = p.size();
    for (auto& x : p) x.remaining = x.burst;

    vector<int> gantt;
    queue<int> ready;

    // At time 0, all processes are immediately ready in order
    for (int i = 0; i < n; i++) {
        ready.push(i);
    }

    int time = 0;
    int completed = 0;

    while (completed < n) {
        if (ready.empty()) break;

        int current = ready.front();
        ready.pop();

        if (p[current].response == -1) {
            p[current].response = time;
        }

        int execution = min(quantum, p[current].remaining);
        for (int i = 0; i < execution; i++) {
            gantt.push_back(p[current].id);
            p[current].remaining--;
            time++;
        }

        if (p[current].remaining == 0) {
            p[current].completion = time;
            completed++;
        } else {
            ready.push(current);
        }
    }

    calculateMetrics(p);
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });
    return {p, gantt, 0, 0};
}

// 7. Earliest Deadline First (EDF) - Non-Preemptive
Result EDF_NP(const vector<Process>& input) {
    vector<Process> p = input;
    int n = p.size();
    int completed = 0;
    int time = 0;
    vector<bool> done(n, false);
    vector<int> gantt;

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i]) {
                if (selected == -1 || 
                    p[i].deadline < p[selected].deadline ||
                    (p[i].deadline == p[selected].deadline && p[i].id < p[selected].id)) {
                    selected = i;
                }
            }
        }

        p[selected].response = time;
        for (int i = 0; i < p[selected].burst; i++) {
            gantt.push_back(p[selected].id);
            time++;
        }
        p[selected].completion = time;
        done[selected] = true;
        completed++;
    }

    calculateMetrics(p);
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });
    return {p, gantt, 0, 0};
}

// 8. Earliest Deadline First (EDF) - Preemptive
Result EDF_P(const vector<Process>& input) {
    vector<Process> p = input;
    int n = p.size();
    for (auto& x : p) x.remaining = x.burst;

    int completed = 0;
    int time = 0;
    vector<int> gantt;

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                if (selected == -1 || 
                    p[i].deadline < p[selected].deadline ||
                    (p[i].deadline == p[selected].deadline && p[i].id < p[selected].id)) {
                    selected = i;
                }
            }
        }

        if (p[selected].response == -1) {
            p[selected].response = time;
        }

        gantt.push_back(p[selected].id);
        p[selected].remaining--;
        time++;

        if (p[selected].remaining == 0) {
            p[selected].completion = time;
            completed++;
        }
    }

    calculateMetrics(p);
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });
    return {p, gantt, 0, 0};
}

// 9. Rate Monotonic Scheduling (RMS) - Non-Preemptive
// For periodic tasks, period T = deadline - arrival. Since AT = 0, period = deadline.
Result RMS_NP(const vector<Process>& input) {
    vector<Process> p = input;
    int n = p.size();
    int completed = 0;
    int time = 0;
    vector<bool> done(n, false);
    vector<int> gantt;

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i]) {
                if (selected == -1) {
                    selected = i;
                } else {
                    int period_i = p[i].deadline;
                    int period_selected = p[selected].deadline;
                    if (period_i < period_selected ||
                        (period_i == period_selected && p[i].id < p[selected].id)) {
                        selected = i;
                    }
                }
            }
        }

        p[selected].response = time;
        for (int i = 0; i < p[selected].burst; i++) {
            gantt.push_back(p[selected].id);
            time++;
        }
        p[selected].completion = time;
        done[selected] = true;
        completed++;
    }

    calculateMetrics(p);
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });
    return {p, gantt, 0, 0};
}

// 10. Rate Monotonic Scheduling (RMS) - Preemptive
Result RMS_P(const vector<Process>& input) {
    vector<Process> p = input;
    int n = p.size();
    for (auto& x : p) x.remaining = x.burst;

    int completed = 0;
    int time = 0;
    vector<int> gantt;

    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                if (selected == -1) {
                    selected = i;
                } else {
                    int period_i = p[i].deadline;
                    int period_selected = p[selected].deadline;
                    if (period_i < period_selected ||
                        (period_i == period_selected && p[i].id < p[selected].id)) {
                        selected = i;
                    }
                }
            }
        }

        if (p[selected].response == -1) {
            p[selected].response = time;
        }

        gantt.push_back(p[selected].id);
        p[selected].remaining--;
        time++;

        if (p[selected].remaining == 0) {
            p[selected].completion = time;
            completed++;
        }
    }

    calculateMetrics(p);
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });
    return {p, gantt, 0, 0};
}

int main() {
    // Look for input_no_arrival.txt first, fallback to input.txt if not found
    string filename = "input_no_arrival.txt";
    ifstream file(filename);
    if (!file) {
        filename = "input.txt";
        file.open(filename);
    }

    if (!file) {
        cout << "Error: Could not open input_no_arrival.txt or input.txt\n";
        return 1;
    }

    int n;
    file >> n;
    vector<Process> processes(n);

    string line;
    getline(file, line); // consume newline after n

    for (int i = 0; i < n; i++) {
        while (getline(file, line)) {
            stringstream ss(line);
            vector<int> tokens;
            int val;
            while (ss >> val) {
                tokens.push_back(val);
            }
            if (tokens.empty()) continue; // skip empty line

            if (tokens.size() == 4) {
                // Format: ID Burst Priority Deadline (AT implicitly 0)
                processes[i].id = tokens[0];
                processes[i].burst = tokens[1];
                processes[i].priority = tokens[2];
                processes[i].deadline = tokens[3];
            } else if (tokens.size() >= 5) {
                // Format: ID Arrival Burst Priority Deadline (Arrival ignored, treated as 0)
                processes[i].id = tokens[0];
                processes[i].burst = tokens[2];
                processes[i].priority = tokens[3];
                processes[i].deadline = tokens[4];
            }
            processes[i].remaining = processes[i].burst;
            break;
        }
    }
    file.close();

    cout << "========================================\n";
    cout << "  CPU SCHEDULING SIMULATOR (AT = 0)\n";
    cout << "========================================\n";

    cout << "\nInput Processes (Arrival Time = 0 for all):\n";
    cout << "\nID\tBT\tPriority\tDeadline\n";

    for (const auto& p : processes) {
        cout << "P" << p.id << "\t"
             << p.burst << "\t"
             << p.priority << "\t\t"
             << p.deadline << "\n";
    }
    
    Result fcfs = FCFS(processes);
    printResult("FCFS", fcfs);

    Result sjf = SJF(processes);
    printResult("SJF - Non-Preemptive", sjf);

    Result srtf = SRTF(processes);
    // printResult("SRTF - Preemptive SJF", srtf);

    Result priorityNP = PriorityNP(processes);
    printResult("Priority - Non-Preemptive", priorityNP);

    Result priorityP = PriorityP(processes);
    // printResult("Priority - Preemptive", priorityP);

    Result rr = RoundRobin(processes, 2);
    printResult("Round Robin - Quantum = 2", rr);

    Result edfNP = EDF_NP(processes);
    printResult("EDF - Non-Preemptive", edfNP);

    Result edfP = EDF_P(processes);
    // printResult("EDF - Preemptive", edfP);

    Result rmsNP = RMS_NP(processes);
    printResult("RMS - Non-Preemptive", rmsNP);

    Result rmsP = RMS_P(processes);
    // printResult("RMS - Preemptive", rmsP);

    return 0;
}
