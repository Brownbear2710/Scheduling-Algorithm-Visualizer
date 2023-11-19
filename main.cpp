#include "fcfs.cpp"
#include "srtf.cpp"
#include "sjf.cpp"
#include "rr.cpp"
#include "ps.cpp"

void print(vector<int> &v)
{
    for(auto i : v)
        cout << i << " ";
    cout << "\n";
}

vector<ProcessState> take_input()
{
    setTextColor(Color::WHITE);
    cout << "Enter number of Processes: ";
    int n;
    cin >> n;
    vector<ProcessState> states(n);
    for(int i = 0; i < n; i++)
    {
        cout << "\n---- Process " << i << "----\n";
        int in;
        cout << "Arrival Time: ";
        cin >> in;
        states[i].AT = in;
        cout << "Burst Time: ";
        cin >> in;
        states[i].BT = in;
        cout << "Priority: ";
        cin >> in;
        states[i].priority = in;
        states[i].WT = 0;
    }
    for(auto &p : states)
        p.remaining = p.BT;
    return states;
}

int main()
{
    auto states = take_input();
    cout << "\nRound Size (For Round Robin): ";
    cin >> rr::round_size;

    vector<int> process_sequence;
    //!FCFS
    // fcfs::visual_output = false;
    // fcfs::show_wait_time = false;
    process_sequence = fcfs::simulate(states);
    // print(process_sequence);

    //!SJF
    // sjf::show_wait_time = false;
    // sjf::visual_output = false;
    process_sequence = sjf::simulate(states);
    // print(process_sequence);

    //!SRTF
    // srtf::show_wait_time = false;
    // srtf::visual_output = false;
    process_sequence = srtf::simulate(states);
    // print(process_sequence);

    //!RR
    // rr::show_wait_time = false;
    // rr::visual_output = false;
    process_sequence = rr::simulate(states);
    // print(process_sequence);
    
    //!PS
    // ps::show_wait_time = false;
    // ps::visual_output = false;
    process_sequence = ps::simulate(states);
    // print(process_sequence);
    
    system("pause");
    return 0;
}

// Sample Input
/*
5
0
10
2
5
13
0
8
5
1
12
4
2
15
6
3
3
*/
