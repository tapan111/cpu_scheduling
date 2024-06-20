# cpu_scheduling


## Project Description
This project is a CPU scheduling simulator that allows users to simulate different CPU scheduling algorithms and compare their performance. It includes implementations of several popular scheduling algorithms such as FCFS (First-Come, First-Served), SJF (Shortest Job First), SRTF (Shortest Remaining Time First), Round Robin, and LJF (Longest Job First).

## How to Run the Project
To run the project, follow these steps:
1. Clone the repository: `git clone https://github.com/tapan111/cpu_scheduling.git`
2. Compile the code: `g++ -o scheduler scheduler.cpp`
3. Run the executable: `./scheduler input.txt output.txt`

## Internal Working
### FCFS (First-Come, First-Served)
- **Arrival:** Sort processes by arrival time.
- **Execution:** Execute processes in the order they arrive.
- **Completion:** Calculate waiting time and turnaround time for each process.
- **Output:** Output average waiting time and turnaround time.
![image](https://github.com/tapan111/cpu_scheduling/assets/99003457/5f130f94-697f-4166-bd8b-0888896f4400)

#### Function Explanation

1. **Sorting Processes:**
   - The function begins by sorting the processes based on their arrival times to ensure they are scheduled in the order they arrive.

2. **Initializing Variables:**
   - A list is created to store the execution order, including start and end times.
   - The current time is initialized to 0.

3. **Scheduling Each Process:**
   - For each process, if the current time is less than the process's arrival time, the current time is updated to the process's arrival time (simulating idle CPU time).
   - The waiting time for each process is calculated as the difference between the current time and the arrival time.
   - The execution details (process ID, start time, end time) are recorded, and the current time is updated after the process's burst time (execution duration).

4. **Calculating Metrics and Writing Results:**
   - The function calculates the waiting and turnaround times for each process.
   - It writes the scheduling results, including the average waiting time, average turnaround time, and a Gantt chart (visual representation of the process execution order), to the output file.

### SJF (Shortest Job First)
- **Arrival:** Sort processes by arrival time.
- **Execution:** Select the process with the shortest burst time among the arrived processes.
- **Completion:** Calculate waiting time and turnaround time for each process.
- **Output:** Output average waiting time and turnaround time.
- ![image](https://github.com/tapan111/cpu_scheduling/assets/99003457/ade17460-6465-4826-b014-48636b9f4964)
#### Function Explanation

1. **Sorting Processes by Arrival Time:**
   - The function starts by sorting the processes based on their arrival times to determine the order of arrival.

2. **Initializing Variables:**
   - `executions` is a list to store the execution order with start and end times.
   - `ready_queue` holds processes that are ready to be executed.
   - `curr_time` tracks the current time in the scheduling simulation.
   - `idx` and `n` are used to iterate through the processes.

3. **Scheduling Each Process:**
   - The main loop continues until all processes are scheduled.
   - Processes that have arrived by the current time are added to the `ready_queue`.
   - If the `ready_queue` is empty, the current time is updated to the next process's arrival time.
   - The `ready_queue` is sorted by burst time to select the process with the shortest burst time.
   - The selected process is executed, and its waiting time is calculated as the difference between the current time and its arrival time.
   - Execution details (process ID, start time, end time) are recorded, and the current time is updated after execution.
   - The waiting and turnaround times are updated for each process.

4. **Calculating Metrics and Writing Results:**
   - The function calculates the waiting and turnaround times for each process.
   - It writes the scheduling results, including the average waiting time, average turnaround time, and a Gantt chart (visual representation of the process execution order), to the output file.


### SRTF (Shortest Remaining Time First)
- **Arrival:** Sort processes by arrival time.
- **Execution:** Select the process with the shortest remaining time among the arrived processes.
- **Preemption:** If a shorter job arrives, preempt the current job.
- **Completion:** Calculate waiting time and turnaround time for each process.
- **Output:** Output average waiting time and turnaround time.
- ![image](https://github.com/tapan111/cpu_scheduling/assets/99003457/e9d6a4eb-9706-4676-8acc-a94444b545c2)
#### Function Explanation

1. **Initializing Variables:**
   - `executions` is a list to store the execution order with start and end times.
   - `curr` tracks the current time in the scheduling simulation.
   - `comp` counts the number of completed processes.
   - `n` is the total number of processes.

2. **Scheduling Each Process:**
   - The main loop continues until all processes are completed.
   - For each time unit, the process with the shortest remaining time that has arrived by the current time is selected.
   - If no such process is found, the current time is incremented.
   - The selected process is executed for one time unit, and its remaining time is decremented.
   - Execution details (process ID, start time, end time) are recorded.
   - If a process completes (remaining time becomes zero), its waiting time is calculated as the difference between the current time (plus one), its arrival time, and its burst time.
   - The current time is incremented after each time unit of execution.

3. **Calculating Metrics and Writing Results:**
   - The function calculates the waiting and turnaround times for each process.
   - It writes the scheduling results, including the average waiting time, average turnaround time, and a Gantt chart (visual representation of the process execution order), to the output file.



### Round Robin
- **Arrival:** Maintain a ready queue.
- **Execution:** Execute each process for a fixed time quantum.
- **Preemption:** If the process's quantum expires, move it to the end of the queue.
- **Completion:** Calculate waiting time and turnaround time for each process.
- **Output:** Output average waiting time and turnaround time.
- ![image](https://github.com/tapan111/cpu_scheduling/assets/99003457/3539ab4b-dc4f-4cf3-a4c8-a035bac121e7)
#### Function Explanation

1. **Initialization:**
   - `executions` is a list to store the execution order with start and end times.
   - `currentTime` tracks the current time in the scheduling simulation.
   - `ready_queue` is a queue to hold processes that are ready to be executed.
   - `completed` counts the number of completed processes.
   - Each process's remaining time is initialized to its burst time.
   - An `arrival` array stores the arrival times of the processes.

2. **Main Loop:**
   - The main loop continues until all processes are completed.
   - The `check_new` function checks for new processes that have arrived by the current time and adds them to the `ready_queue`.
   - If the `ready_queue` is empty, the current time is incremented.
   - The process at the front of the `ready_queue` is selected and executed for a time slice equal to the minimum of the quantum and the process's remaining time.
   - Execution details (process ID, start time, end time) are recorded, and the process's remaining time is decremented by the time slice.
   - The current time is incremented by the time slice.
   - The `check_new` function is called again to add any new processes that have arrived during the time slice.
   - If the process's remaining time is greater than zero, it is re-added to the `ready_queue`. Otherwise, its waiting time is calculated.

3. **Calculating Metrics and Writing Results:**
   - The function calculates the waiting and turnaround times for each process.
   - It writes the scheduling results, including the average waiting time, average turnaround time, and a Gantt chart (visual representation of the process execution order), to the output file.


### LJF (Longest Job First)
- **Arrival:** Sort processes by arrival time.
- **Execution:** Select the process with the longest burst time among the arrived processes.
- **Completion:** Calculate waiting time and turnaround time for each process.
- **Output:** Output average waiting time and turnaround time.
- ![image](https://github.com/tapan111/cpu_scheduling/assets/99003457/e8d721f2-148b-4814-8e6d-a8cd5c4a27ed)
#### Function Explanation

1. **Sorting Processes by Arrival Time:**
   - The function starts by sorting the processes based on their arrival times to determine the order of arrival.

2. **Initializing Variables:**
   - `executions` is a list to store the execution order with start and end times.
   - `ready_queue` holds processes that are ready to be executed.
   - `curr_time` tracks the current time in the scheduling simulation.
   - `idx` and `n` are used to iterate through the processes.

3. **Scheduling Each Process:**
   - The main loop continues until all processes are scheduled.
   - Processes that have arrived by the current time are added to the `ready_queue`.
   - If the `ready_queue` is empty, the current time is updated to the next process's arrival time.
   - The `ready_queue` is sorted by burst time in descending order to select the process with the longest burst time.
   - The selected process is executed, and its waiting time is calculated as the difference between the current time and its arrival time.
   - Execution details (process ID, start time, end time) are recorded, and the current time is updated after execution.
   - The waiting and turnaround times are updated for each process.

4. **Calculating Metrics and Writing Results:**
   - The function calculates the waiting and turnaround times for each process.
   - It writes the scheduling results, including the average waiting time, average turnaround time, and a Gantt chart (visual representation of the process execution order), to the output file.
   - ![image](https://github.com/tapan111/cpu_scheduling/assets/99003457/01797d96-ff0b-4c0f-a93a-fd4578f71a57)


## Learning Takeaways
- Understanding of different CPU scheduling algorithms and their implementation in C++.
- Hands-on experience with process management and scheduling in an operating system.
- Importance of algorithm choice in optimizing CPU utilization and response time.

## Resources/References
- Operating System Concepts by Abraham Silberschatz, Peter Baer Galvin, and Greg Gagne
- GeeksforGeeks articles on CPU Scheduling Algorithms
