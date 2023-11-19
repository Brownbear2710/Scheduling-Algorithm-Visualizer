# Scheduling-Algorithm-Visualizer

This is a console based visualizer. Given some processes' arrival time, burst time, and priority, it shows the different states of the processes at different time.

## How to use

Simply download the repo and run the `main.cpp` file.

## Customization
The visualization algorithms use the following structure written inside `common.cpp` file:

```cpp
struct ProcessState {
    int AT, BT, remaining, WT, priority;
};
```
```
AT        : Arrival Time of the Porcess
BT        : Burst Time of the Porcess
remaining : Remainig Process Execution Time
WT        : Wait Time of the Porcess
pririty   : Priority of the Process
```

Each algorithm has its own namespace. Inside each namespace there is a function called `simulate()` that simulates the algorithm. It takes `vector<ProcessState>` as parameter . When `simulate()` is called it visualizes the algorithm as well as shows the wait time for each process and average wait time. It also returns a `vector<int>` of process sequence where $i^{th}$ element indicates the process number that was being executed after the beginnig of time $i$ and before the end of time $i$. <br>
Inside each namespace, there are two boolean variables named `visual_output` and `show_wait_time` which are `true` by default. `visual_output` is `false` means `simulate()` will not show the visualization. `show_wait_time` is `false` means `simulate()` will not show the wait time. However, no matter what `simulate()` function will always return process seqence.<br>
For Round Robin algorithm there is a variable called `round_size` which is set to `3` by default. It indicates that a process will get max `3` consecutive slots for execution if there are other processes that have arrived but did not finish execution.<br>
See `main.cpp` to get a better idea.
