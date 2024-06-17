#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int rem_time;
    int wait_time;
    int turnaround_time;
};

struct Execution {
    int pid;
    int start_time; 
    int end_time;
};

void calculate_wait_turn_time(vector<Process>& processes) {
    for (auto& p : processes) {
        p.turnaround_time = p.wait_time + p.burst_time;
    }
}

void print_avg_time(vector<Process>& processes, ofstream& outputFile) {
    int total_w = 0 , total_a = 0 ;

    for(const auto &p :processes){
        total_w+= p.wait_time;
        total_a += p.turnaround_time;
    }
   
    outputFile << "Average Waiting Time: " << (float)total_w / processes.size() << endl;
    outputFile << "Average Turnaround Time: " << (float)total_a / processes.size() << endl;
}

void print_gantt(vector<Execution>& executions, ofstream& outputFile) {
    outputFile << "Gantt Chart:" << endl;
    for (const auto& e : executions) {
        outputFile << "| P" << e.pid << " ";
    }
    outputFile << "|" << endl;
    for (const auto& e : executions) {
        outputFile << e.start_time << "\t";
    }
    outputFile << executions.back().end_time << endl << endl;
}
/*################################# FCFS ##########################################################################*/
void fcfs(vector<Process> processes, ofstream& outputFile) {
     
     auto comp=[](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    };
    sort(processes.begin(), processes.end(),comp );

    vector<Execution> exe;
    int curr_time = 0;

    for (auto& p : processes) {
        
        if (curr_time < p.arrival_time) {
            curr_time = p.arrival_time;
        }
        
        p.wait_time = max(0, curr_time - p.arrival_time);
        exe.push_back({p.pid, curr_time, curr_time + p.burst_time});
        curr_time += p.burst_time;
    }

    calculate_wait_turn_time(processes);
    outputFile << "FCFS Scheduling:" << endl;
    print_avg_time(processes, outputFile);
    print_gantt(exe, outputFile);
}
/*#############################################   SJF  ##############################################################*/
void sjf(vector<Process> processes, ofstream& outputFile) {

    auto comp_arrival = [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    };


    sort(processes.begin(), processes.end(), comp_arrival);

    vector<Execution> executions;
    vector<Process> ready_queue;
    int curr_time = 0;
    int idx = 0;
    int n = processes.size();

    while (idx < n || !ready_queue.empty()) {
       
        while (idx < n && processes[idx].arrival_time <= curr_time) {
            ready_queue.push_back(processes[idx]);
            idx++;
        }

       
        if (ready_queue.empty()) {
            curr_time = processes[idx].arrival_time;
            continue;
        }

        auto comp_burst = [](const Process& a, const Process& b) {
            return a.burst_time < b.burst_time;
        };
        sort(ready_queue.begin(), ready_queue.end(), comp_burst);

       
        Process p = ready_queue.front();
        ready_queue.erase(ready_queue.begin());

        p.wait_time = max(0, curr_time - p.arrival_time);
        executions.push_back({p.pid, curr_time, curr_time + p.burst_time});
        curr_time += p.burst_time;

        
        for (auto& process : processes) {
            if (process.pid == p.pid) {
                process.wait_time = p.wait_time;
                process.turnaround_time = process.wait_time + process.burst_time;
                break;
            }
        }
    }

    outputFile << "SJF Scheduling:" << endl;
    calculate_wait_turn_time(processes);
    print_avg_time(processes, outputFile);
    print_gantt(executions, outputFile);
}
/*############################################## LJF #####################################################################*/
void ljf(vector<Process> processes,ofstream& outputFile) {
    auto comp_arrival = [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    };

   sort(processes.begin(), processes.end(), comp_arrival);

    vector<Execution> executions;
   vector<Process> ready_queue;
    int curr_time = 0;
    int idx = 0;
    int n = processes.size();

    while (idx < n || !ready_queue.empty()) {
       
        while (idx < n && processes[idx].arrival_time <= curr_time) {
            ready_queue.push_back(processes[idx]);
            idx++;
        }

        if (ready_queue.empty()) {
            curr_time = processes[idx].arrival_time;
            continue;
        }

        auto comp_burst = [](const Process& a, const Process& b) {
            return a.burst_time > b.burst_time;
        };
       sort(ready_queue.begin(), ready_queue.end(), comp_burst);

        Process p = ready_queue.front();
        ready_queue.erase(ready_queue.begin());

        p.wait_time = max(0, curr_time - p.arrival_time);
        executions.push_back({p.pid, curr_time, curr_time + p.burst_time});
        curr_time += p.burst_time;

        for (auto& process : processes) {
            if (process.pid == p.pid) {
                process.wait_time = p.wait_time;
                process.turnaround_time = process.wait_time + process.burst_time;
                break;
            }
        }
    }

    outputFile << "LJF Scheduling:" << endl;
    calculate_wait_turn_time(processes);
    print_avg_time(processes, outputFile);
    print_gantt(executions, outputFile);
}
/*###################################################### SRTF(SJF premptive) #############################################*/
void srtf(vector<Process> processes, ofstream& outputFile) {


    int n = processes.size();
    vector<Execution> executions;
    int curr = 0, comp = 0;
    while (comp != n) {
        int shortest = -1;
        int mini = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= curr && processes[i].rem_time > 0 && processes[i].rem_time < mini) {
                mini = processes[i].rem_time;
                shortest = i;
            }
        }
        if (shortest == -1) {
            curr++;
            continue;
        }
        executions.push_back({processes[shortest].pid, curr, curr + 1});
        processes[shortest].rem_time--;
        if (processes[shortest].rem_time == 0) {
            comp++;
            processes[shortest].wait_time = curr + 1 - processes[shortest].arrival_time - processes[shortest].burst_time;
        }
        curr++;
    }
    calculate_wait_turn_time(processes);
    outputFile << "SRTF Scheduling:" << endl;
    print_avg_time(processes, outputFile);
    print_gantt(executions, outputFile);


}
/* ################################################################################### Round robin #############################*/
void queue_maintain(queue<int>& ready_queue, int processIndex) {
    ready_queue.push(processIndex);
}

void check_new(int timer, int arrival[], int n, queue<int>& ready_queue) {
    for (int i = 0; i < n; i++) {
        if (arrival[i] <= timer && arrival[i] != -1) {
            ready_queue.push(i);
            arrival[i] = -1; 
        }
    }
}

void roundRobin(vector<Process> processes, int quantum, ofstream& outputFile) {
    vector<Execution> executions;
    int currentTime = 0;
    queue<int> ready_queue;
    int completed = 0;


    for (auto& p : processes) {
        p.rem_time = p.burst_time;
    }

    int n = processes.size();
    int arrival[n];
    for (int i = 0; i < n; i++) {
        arrival[i] = processes[i].arrival_time;
    }

    while (completed != processes.size()) {
        check_new(currentTime, arrival, n, ready_queue);

        if (ready_queue.empty()) {
            currentTime++;
            continue;
        }

        int current = ready_queue.front();
        ready_queue.pop();
        
        int timeSlice = min(quantum, processes[current].rem_time);
        executions.push_back({processes[current].pid, currentTime, currentTime + timeSlice});
        processes[current].rem_time -= timeSlice;
        currentTime += timeSlice;

        check_new(currentTime, arrival, n, ready_queue);

        if (processes[current].rem_time > 0) {
            queue_maintain(ready_queue, current);
        } else {
            completed++;
            processes[current].wait_time = currentTime - processes[current].arrival_time - processes[current].burst_time;
        }
    }

    calculate_wait_turn_time(processes);
    outputFile << "Round Robin Scheduling (Quantum = " << quantum << "):" << endl;
    print_avg_time(processes, outputFile);
    print_gantt(executions, outputFile);
}
/*######################################################### ############################ Prediction ############################*/
string predictBestAlgorithm(vector<Process>& processes) {
    double total_burst_time = accumulate(processes.begin(), processes.end(), 0.0, 
        [](double sum, const Process& p) { return sum + p.burst_time; });
    double avg_burst_time = total_burst_time / processes.size();

    bool all_burst_times_same = all_of(processes.begin(), processes.end(), 
        [&](const Process& p) { return p.burst_time == processes[0].burst_time; });

    if (all_burst_times_same) {
        return "FCFS";
    }

    double burst_time_variance = 0;
    for (const auto& p : processes) {
        burst_time_variance += (p.burst_time - avg_burst_time) * (p.burst_time - avg_burst_time);
    }
    burst_time_variance /= processes.size();

    double total_arrival_time = accumulate(processes.begin(), processes.end(), 0.0, 
        [](double sum, const Process& p) { return sum + p.arrival_time; });
    double avg_arrival_time = total_arrival_time / processes.size();

    double arrival_time_variance = 0;
    for (const auto& p : processes) {
        arrival_time_variance += (p.arrival_time - avg_arrival_time) * (p.arrival_time - avg_arrival_time);
    }
    arrival_time_variance /= processes.size();

    int long_burst_count = count_if(processes.begin(), processes.end(), [&](const Process& p) {
        return p.burst_time > avg_burst_time;
    });

    if (burst_time_variance < avg_burst_time && arrival_time_variance < avg_arrival_time) {
        return "SJF";
    } else if (burst_time_variance < avg_burst_time) {
        return "SRTF";
    } else if (long_burst_count > processes.size() / 2) {
        return "LJF";
    } else {
        return "Round Robin";
    }
}

/*######################################################## MAIN CODE ##########################################################*/
void runScheduler() {
     ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        cerr << "Error reading input file 🥲" << endl;
        return ;
    }
    if (!outputFile.is_open()) {
        cerr << "Error reading output file 🥲" << endl;
        return ;
    }

    vector<Process> processes;
    int pid, burst_time, arrival_time;

    while (inputFile >> pid >> burst_time >> arrival_time) {
        processes.push_back({pid, burst_time, arrival_time, burst_time, 0, 0});
    }

   
    if (processes.empty()) {
       outputFile << "No processes found from input file" << endl;
        return ;
    } 
    else {
        for (const auto& p : processes) {
            cerr << "Loaded Process - PID: " << p.pid << ", Burst Time: " << p.burst_time << ", Arrival Time: " << p.arrival_time << endl;
        }
    }
/*#################### prediction based on process infromation ############################*/

    string pred = predictBestAlgorithm(processes);
    outputFile<<"Best algorithm predicted is " <<pred<<endl;
    outputFile <<endl;
/*##################### Execution of different algorithms ###############################*/
    fcfs(processes, outputFile);
    sjf(processes, outputFile);
    ljf(processes, outputFile);
    srtf(processes, outputFile);
    roundRobin(processes, 2, outputFile);

    inputFile.close();
    outputFile.close();
}
int main() {
     runScheduler();
    return 0;
}
