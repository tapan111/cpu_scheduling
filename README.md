# cpu_scheduling


## Project Description
This project is a CPU scheduling simulator that allows users to simulate different CPU scheduling algorithms and compare their performance. It includes implementations of several popular scheduling algorithms such as FCFS (First-Come, First-Served), SJF (Shortest Job First), SRTF (Shortest Remaining Time First), Round Robin, and LJF (Longest Job First).

## How to Run the Project
To run the project, follow these steps:
1. Clone the repository: `git clone https://github.com/yourusername/cpu-scheduling-simulator.git`
2. Compile the code: `g++ -o scheduler scheduler.cpp`
3. Run the executable: `./scheduler input.txt output.txt`

## Internal Working
### FCFS (First-Come, First-Served)
- **Arrival:** Sort processes by arrival time.
- **Execution:** Execute processes in the order they arrive.
- **Completion:** Calculate waiting time and turnaround time for each process.
- **Output:** Output average waiting time and turnaround time.

### SJF (Shortest Job First)
- **Arrival:** Sort processes by arrival time.
- **Execution:** Select the process with the shortest burst time among the arrived processes.
- **Completion:** Calculate waiting time and turnaround time for each process.
- **Output:** Output average waiting time and turnaround time.

### SRTF (Shortest Remaining Time First)
- **Arrival:** Sort processes by arrival time.
- **Execution:** Select the process with the shortest remaining time among the arrived processes.
- **Preemption:** If a shorter job arrives, preempt the current job.
- **Completion:** Calculate waiting time and turnaround time for each process.
- **Output:** Output average waiting time and turnaround time.

### Round Robin
- **Arrival:** Maintain a ready queue.
- **Execution:** Execute each process for a fixed time quantum.
- **Preemption:** If the process's quantum expires, move it to the end of the queue.
- **Completion:** Calculate waiting time and turnaround time for each process.
- **Output:** Output average waiting time and turnaround time.

### LJF (Longest Job First)
- **Arrival:** Sort processes by arrival time.
- **Execution:** Select the process with the longest burst time among the arrived processes.
- **Completion:** Calculate waiting time and turnaround time for each process.
- **Output:** Output average waiting time and turnaround time.

## Learning Takeaways
- Understanding of different CPU scheduling algorithms and their implementation in C++.
- Hands-on experience with process management and scheduling in an operating system.
- Importance of algorithm choice in optimizing CPU utilization and response time.

## Resources/References
- Operating System Concepts by Abraham Silberschatz, Peter Baer Galvin, and Greg Gagne
- GeeksforGeeks articles on CPU Scheduling Algorithms
